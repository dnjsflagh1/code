//////////////////////////////////////////////////////////////////////////////////////////////////
// OgreXMLCombine.cpp : Defines the entry point for the console application.
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tinyxml.h"
#include <math.h>
#include <atlbase.h>
#include <iostream>
#include <sys/stat.h>
#include <vector>
#include "MGQuaternion.h"
//*************************************************************************************************
using namespace MG;
//*************************************************************************************************
#define OUTPUT_DIR ".\\CombineOutPut"
#define INPUT_DIR ".\\CombineInput"
#define PARENT_BONE "BoneRoot"
#define ANIMATION_NAME "crash"

static	const TCHAR* g_InputDir;
static	const TCHAR* g_OutputDir;

typedef struct __myQua__{

	__myQua__(){}
	__myQua__(double _x, double _y, double _z, double _w)
		:x(_x),y(_y),z(_z),w(_w)
	{}

	double x;
	double y;
	double z;
	double w;

} myQua;

typedef struct __myVec3__{

	__myVec3__(){}
	__myVec3__(double _x, double _y, double _z)
		:x(_x),y(_y),z(_z)
	{}

	double x;
	double y;
	double z;

} myVec3;

typedef struct {

	myQua		boneQua;
	myVec3		bonePos;
	myVec3		boneScale;
	std::string	boneName;

} BoneInfo;

static	std::vector<BoneInfo> gs_BoneIdx;

//*************************************************************************************************

bool		convertSkeleton(_TCHAR* lpFinalName, _TCHAR* lpAnimation); //���ɹ����ļ�skeleton.xml�ļ�;
bool		combineSubMesh(_TCHAR* lpFinalName, bool bMeshHasSkeleton); //����mesh.xml�ļ�;
void		optimizeSubmesh(TiXmlNode* lpXmlNode); //�ϲ���ͬ���ʵ�submesh;

int			getBoneIdx(LPCTSTR lpBone, BoneInfo& boneInfo); //���ݹ����ļ�����ȡ��������;
void		addBoneInfo(LPCSTR lpBoneName, myQua boneQua, myVec3 boneScale, myVec3 bonePos); //��������Ϣ����ȫ���б�

bool		hasAnimations(TiXmlNode* lpNode);
bool		hasAnimation(TiXmlNode* lpNode);
bool		hasSubEntity(TiXmlNode* lpNode);

void		ToAngleAxis(const myQua& q, myVec3& rkAxis, double& fAngle);
myQua		getDeltaQua( myQua q1, myQua q2 );

//*************************************************************************************************

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc > 1)
	{
		///////////////////////////////////////////////////////////////////////////////////////////////

		TCHAR szAnimName[32] = _T(ANIMATION_NAME);

		g_InputDir = _T(INPUT_DIR);
		g_OutputDir = _T(OUTPUT_DIR);

		///////////////////////////////////////////////////////////////////////////////////////////////

		// ����·��
		if ( argc > 2)
		{
			g_InputDir = argv[2];
		}

		// ���·��
		if ( argc > 3 )
		{
			g_OutputDir = argv[3];
		}

		// ȷ�϶�������
		if ( argc > 4)
		{
			_stprintf_s( szAnimName, _countof(szAnimName) - 1, _T("%s"), argv[4] );	
		}

		///////////////////////////////////////////////////////////////////////////////////////////////

		// ������������ļ�·��

		WIN32_FIND_DATA wfd;
		FindFirstFile(g_InputDir,&wfd);
		if( ( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == 0 )
		{
			CreateDirectory(g_InputDir, NULL);
		}

		FindFirstFile(g_OutputDir, &wfd);
		if ( ( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )  == 0 )
		{
			CreateDirectory(g_OutputDir, NULL);
		}

		///////////////////////////////////////////////////////////////////////////////////////////////

		// ���������ļ�
		bool bMeshHasSkeleton = convertSkeleton(argv[1], szAnimName);

		// ���������ļ�
		if (combineSubMesh(argv[1], bMeshHasSkeleton))
		{
			return 0;
		}

		return -1;
	}
	else
	{
		std::cout << "Please specify mesh source path............" << std::endl;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////

	return 0;
}


bool convertSkeleton(_TCHAR* lpFinalName, _TCHAR* lpAnimation)
{
	TCHAR szFileName[MAX_PATH];
	WIN32_FIND_DATA fd;
	HANDLE hFile;
	_stprintf_s(szFileName, _countof(szFileName) - 1, _T("%s\\*.model"), g_InputDir);
	hFile = ::FindFirstFile(szFileName, &fd);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		CT2A	animName(lpAnimation); 
		int		nBoneIdx = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		TiXmlDocument doc;
		// ��Ŀ��doc�д���������Ϣ��
		TiXmlElement* lpSkeleton = doc.InsertEndChild(TiXmlElement("skeleton"))->ToElement();
		// ��ǰ�����Ļ��ģʽ
		lpSkeleton->SetAttribute("blendmode", "average");
		// ��bones�ڵ����Ŀ��doc��skeleton�ڵ�
		TiXmlElement* lpBones = lpSkeleton->InsertEndChild(TiXmlElement("bones"))->ToElement();
		// ��bonehierarchy�ڵ����Ŀ���doc��skeleton�ڵ�
		TiXmlElement* lpBonehierarchy = lpSkeleton->InsertEndChild(TiXmlElement("bonehierarchy"))->ToElement();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//���й������壬��bones�ڵ����Ȳ���һ��������
		TiXmlElement* lpBone = lpBones->InsertEndChild(TiXmlElement("bone"))->ToElement();
		lpBone->SetAttribute("id", nBoneIdx++);
		lpBone->SetAttribute("name", PARENT_BONE);

		//��ʼ���ж����ļ�������ʼ��ȡmodel�ļ�
		TiXmlDocument node;
		_stprintf_s(szFileName, _countof(szFileName) - 1, _T("%s\\%s"), g_InputDir, fd.cFileName);
		node.LoadFile(CT2A(szFileName));

		if (node.Error() == false)
		{
			//���常����λ����Ϣ��
			TiXmlElement* lpNode = node.FirstChildElement("node");
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			TiXmlElement* lpAnimations = NULL;

			if ( hasAnimations(lpNode) )
			{
				// ��animations�ڵ����Ŀ��doc��skeleton�ڵ�
				lpAnimations = lpSkeleton->InsertEndChild(TiXmlElement("animations"))->ToElement();
				// ��animation�ڵ����Ŀ��doc��animations�ڵ�
				TiXmlElement* lpAnimation = lpAnimations->InsertEndChild(TiXmlElement("animation"))->ToElement();
				// ��tracks�ڵ����animation�ڵ�
				lpAnimation->InsertEndChild(TiXmlElement("tracks"))->ToElement();
				// ��ǰanimation������
				lpAnimation->SetAttribute("name", animName);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// ����������

			if (lpNode != NULL)
			{
				// ��ȫ����node��λ����Ϣ
				TiXmlElement* transElem =	lpBone->InsertEndChild(*lpNode->FirstChild("position"))->ToElement();
				TiXmlElement* rotElem	=	lpBone->InsertEndChild(TiXmlElement("rotation"))->ToElement();
				TiXmlElement* lpAxis	=	rotElem->InsertEndChild(TiXmlElement("axis"))->ToElement();

				transElem->SetAttribute("x", "0.0");
				transElem->SetAttribute("y", "0.0");
				transElem->SetAttribute("z", "0.0");

				lpAxis->SetAttribute("x", "0.0");
				lpAxis->SetAttribute("y", "1.0");
				lpAxis->SetAttribute("z", "0.0");

				rotElem->SetAttribute("angle", "0.0");

				addBoneInfo( PARENT_BONE, myQua(0.0f, 0.0f, 0.0f, 1.0f), myVec3(1.0f, 1.0f, 1.0f), myVec3(0.0f, 0.0f, 0.0f) );

				lpNode = lpNode->FirstChildElement("node");
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			while (lpNode != NULL)
			{
				if ( hasSubEntity(lpNode) )
				{
					/////////////////////////////////////////////////////////////////////////////////////////////////////

					myQua	q;
					myVec3	scale;
					myVec3	pos;
					myVec3	axis;
					double	fAngle;
					char	szValue[64];

					//����������ӹ�ϵ
					lpBone = lpBonehierarchy->InsertEndChild(TiXmlElement("boneparent"))->ToElement();
					lpBone->SetAttribute("bone", lpNode->Attribute("name"));
					lpBone->SetAttribute("parent", PARENT_BONE );
					
					//��������
					lpBone = lpBones->InsertEndChild(TiXmlElement("bone"))->ToElement();
					lpBone->SetAttribute("id", nBoneIdx++);
					lpBone->SetAttribute("name", lpNode->Attribute("name"));

					//��ȡ�����ռ�pos��orientation��Ϣ
					TiXmlElement* transElem = lpNode->FirstChildElement("position");
					transElem->Attribute("x", &pos.x);
					transElem->Attribute("y", &pos.y);
					transElem->Attribute("z", &pos.z);
					
					TiXmlElement* rotElem =	lpNode->FirstChildElement("rotation");
					rotElem->Attribute("qx", &q.x);
					rotElem->Attribute("qy", &q.y);
					rotElem->Attribute("qz", &q.z);
					rotElem->Attribute("qw", &q.w);

					TiXmlElement* scaleElem = lpNode->FirstChildElement("scale");
					scaleElem->Attribute("x", &scale.x);
					scaleElem->Attribute("y", &scale.y);
					scaleElem->Attribute("z", &scale.z);

					//����boneList
					addBoneInfo(lpNode->Attribute("name"), q, scale, pos);

					//����Ԫ����Ϣת��Ϊ��ת���Լ��Ƕ�
					ToAngleAxis(q, axis, fAngle);

					//��ʼ��������Ϣ
					transElem =	lpBone->InsertEndChild(*lpNode->FirstChild("position"))->ToElement();
					rotElem	=	lpBone->InsertEndChild(TiXmlElement("rotation"))->ToElement();
					TiXmlElement* lpAxis	=	rotElem->InsertEndChild(TiXmlElement("axis"))->ToElement();

					sprintf_s(szValue, _countof(szValue) - 1, "%f", pos.x);
					transElem->SetAttribute("x", szValue);

					sprintf_s(szValue, _countof(szValue) - 1, "%f", pos.y);
					transElem->SetAttribute("y", szValue);

					sprintf_s(szValue, _countof(szValue) - 1, "%f", pos.z);
					transElem->SetAttribute("z", szValue);

					sprintf_s(szValue, _countof(szValue) - 1, "%f", axis.x);
					lpAxis->SetAttribute("x", szValue);

					sprintf_s(szValue, _countof(szValue) - 1, "%f", axis.y);
					lpAxis->SetAttribute("y", szValue);

					sprintf_s(szValue, _countof(szValue) - 1, "%f", axis.z);
					lpAxis->SetAttribute("z", szValue);

					sprintf_s(szValue, _countof(szValue) - 1, "%f", fAngle);
					rotElem->SetAttribute("angle", szValue);

					/////////////////////////////////////////////////////////////////////////////////////////////////////

					if ( hasAnimation(lpNode) )
					{
						double	fNodeLength = .0f;
						double	fSkeletonLength = .0f;

						//ת����������
						TiXmlElement* lpAnimationElement = lpNode->FirstChild("animations")->ToElement();
						lpAnimationElement = lpAnimationElement->FirstChild("animation")->ToElement();

						//��ȡ�ڵ㶯���ĳ���
						lpAnimationElement->Attribute("length", &fNodeLength);

						//��ʼ���ö����Ķ������ȣ� ��Ϊ�ڵ㶯���ļ��У� ÿ���ڵ㶼��һ������ʱ�䡣
						//���ǹ��������ļ������й����Ķ���ʱ���ǹ��õġ�
						TiXmlElement* lpAnimation = lpAnimations->FirstChildElement("animation");
						if (lpAnimation->Attribute("length", &fSkeletonLength) == NULL)
						{
							fSkeletonLength = .0f;
						}

						//д�붯������
						if (fNodeLength > fSkeletonLength)
						{
							char szValue[64];
							sprintf_s(szValue, "%f", fNodeLength);
							lpAnimation->SetAttribute("length", szValue);
						}

						//����tracks��track
						TiXmlElement* lpTrack = lpAnimation->FirstChild("tracks")->ToElement();
						lpTrack = lpTrack->InsertEndChild(TiXmlElement("track"))->ToElement();
						lpTrack->SetAttribute("bone", lpNode->Attribute("name"));

						//��track���湹��keyFrames
						lpTrack = lpTrack->InsertEndChild(TiXmlElement("keyframes"))->ToElement();
						//��ȡmodel�ļ��У���Ӧnode��keyFrame�ļ�
						TiXmlNode* lpKeyFrame = lpAnimationElement->FirstChild("keyframe");

						while (lpKeyFrame != NULL)
						{
							CA2T szboneName(lpNode->Attribute("name"));
							BoneInfo boneInfo;
							getBoneIdx( szboneName, boneInfo );

							//ֱ�ӿ�����node�ļ���keyFrame������
							TiXmlElement* lpSkeletonKeyFrame = lpTrack->InsertEndChild(*lpKeyFrame->Clone())->ToElement();

							//������֡��λ����Ϣ�� ��ȡ�͹�����λ�õ����λ��.
							TiXmlElement* lpSkeletonKeyFrameTranslate = lpSkeletonKeyFrame->FirstChildElement("translation");
							lpSkeletonKeyFrameTranslate->SetValue("translate");

							lpSkeletonKeyFrameTranslate->Attribute("x", &pos.x);
							lpSkeletonKeyFrameTranslate->Attribute("y", &pos.y);
							lpSkeletonKeyFrameTranslate->Attribute("z", &pos.z);

							pos.x -= boneInfo.bonePos.x;
							pos.y -= boneInfo.bonePos.y;
							pos.z -= boneInfo.bonePos.z;

							sprintf_s(szValue, _countof(szValue) - 1, "%f", pos.x);
							lpSkeletonKeyFrameTranslate->SetAttribute("x", szValue);
							sprintf_s(szValue, _countof(szValue) - 1, "%f", pos.y);
							lpSkeletonKeyFrameTranslate->SetAttribute("y", szValue);
							sprintf_s(szValue, _countof(szValue) - 1, "%f", pos.z);
							lpSkeletonKeyFrameTranslate->SetAttribute("z", szValue);

							//������֡�ڵ��rotate��Ϣ����ȡ�Ͱ󶨵����Է���
							TiXmlElement* lpSkeletonKeyFrameRotation = lpSkeletonKeyFrame->FirstChildElement("rotation");

							lpSkeletonKeyFrameRotation->Attribute("qx", &q.x);
							lpSkeletonKeyFrameRotation->Attribute("qy", &q.y);
							lpSkeletonKeyFrameRotation->Attribute("qz", &q.z);
							lpSkeletonKeyFrameRotation->Attribute("qw", &q.w);

							ToAngleAxis(getDeltaQua(q, boneInfo.boneQua), axis, fAngle);

							lpSkeletonKeyFrame->RemoveChild(lpSkeletonKeyFrameRotation);
							lpSkeletonKeyFrame->RemoveChild(lpSkeletonKeyFrame->FirstChild("scale")->ToElement());

							// �����µ�rotate��ʽ�Ľڵ�
							lpSkeletonKeyFrameRotation = lpSkeletonKeyFrame->InsertEndChild(TiXmlElement("rotate"))->ToElement();
							TiXmlElement* lpSkeletonKeyFrameAxis = lpSkeletonKeyFrameRotation->InsertEndChild(TiXmlElement("axis"))->ToElement();

							sprintf_s(szValue, _countof(szValue) - 1, "%f", axis.x);
							lpSkeletonKeyFrameAxis->SetAttribute("x", szValue);
							sprintf_s(szValue, _countof(szValue) - 1, "%f", axis.y);
							lpSkeletonKeyFrameAxis->SetAttribute("y", szValue);
							sprintf_s(szValue, _countof(szValue) - 1, "%f", axis.z);
							lpSkeletonKeyFrameAxis->SetAttribute("z", szValue);
							sprintf_s(szValue, _countof(szValue) - 1, "%f", fAngle);
							lpSkeletonKeyFrameRotation->SetAttribute("angle", szValue);

							lpKeyFrame = lpKeyFrame->NextSibling("keyframe");
						}
					}

					/////////////////////////////////////////////////////////////////////////////////////////////////////
				}

				lpNode = lpNode->NextSiblingElement("node");
			}
		}

		::FindClose(hFile);

		_stprintf_s(szFileName, _countof(szFileName) - 1, _T("%s\\%s.skeleton.xml"), g_OutputDir, lpFinalName);
		CT2A strFile(szFileName);
		doc.SaveFile(strFile);

		return true;
	}

	return false;
};

bool combineSubMesh(_TCHAR* lpFinalName, bool bMeshHasSkeleton)
{
	if (lpFinalName != NULL)
	{
		TCHAR szFileName[MAX_PATH];
		WIN32_FIND_DATA fd;
		HANDLE hFile;
		BOOL bRet = TRUE;
		_stprintf_s(szFileName, _countof(szFileName) - 1, _T("%s\\*.mesh.xml"), g_InputDir);
		hFile = ::FindFirstFile(szFileName, &fd);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			int nSubmeshNameIdx = 0;
			TiXmlDocument doc;
			// ���Ϻ��mesh�ļ�����
			TiXmlElement* lpTargetSubMesh = doc.InsertEndChild(TiXmlElement("mesh"))->ToElement();
			TiXmlElement* lpTargetSubMeshName = lpTargetSubMesh;
			// ����submeshes�ӽڵ�
			lpTargetSubMesh = lpTargetSubMesh->InsertEndChild(TiXmlElement("submeshes"))->ToElement();
			// ����submeshnames�ӽڵ�
			lpTargetSubMeshName = lpTargetSubMeshName->InsertEndChild(TiXmlElement("submeshnames"))->ToElement();

			do 
			{
				// ������ȡ���е�mesh.xml�ļ��� ��ÿ��mesh�ļ��е�submesh�ϲ���
				_stprintf_s(szFileName, _countof(szFileName) - 1, _T("%s\\%s"), g_InputDir, fd.cFileName);
				TiXmlDocument mesh;
				CT2A strFile(szFileName);
				mesh.LoadFile(strFile);
				if (mesh.Error() == false)
				{
					// ��ȡ������Ϣ
					BoneInfo boneInfo;
					// ����޷���ȡ������Ϣ�� ����������¸��ļ�
					int nBoneIdx = getBoneIdx(fd.cFileName, boneInfo);
					if ( nBoneIdx < 0 )
						continue;

					TiXmlNode* lpSrouceSubMesh = mesh.FirstChild("mesh");

					if ( lpSrouceSubMesh )
					{
						lpSrouceSubMesh = lpSrouceSubMesh->FirstChild("submeshes");
					}

					if ( lpSrouceSubMesh )
					{
						lpSrouceSubMesh = lpSrouceSubMesh->FirstChild("submesh");
					}

					while (lpSrouceSubMesh != NULL)
					{
						// ��������submesh�ڵ�
						TiXmlElement* lpSubMesh = lpTargetSubMesh->InsertEndChild(*lpSrouceSubMesh->Clone())->ToElement();

						// Ѱ�ҵ�������֮���geometry�ڵ�
						TiXmlElement* lpGeometryElem = lpSubMesh->FirstChildElement("geometry");

						int	nVertexcount;

						if ( lpGeometryElem && 
							lpGeometryElem->Attribute("vertexcount", &nVertexcount) != NULL )
						{
							TiXmlElement* lpVertexBuffer = lpGeometryElem->FirstChildElement("vertexbuffer");
							if ( lpVertexBuffer )
							{
								TiXmlElement *lpVertexElement = lpVertexBuffer->FirstChildElement("vertex");
								while ( lpVertexElement )
								{
									char   szValue[256];
									myVec3 pos;
									myVec3 normal;

									TiXmlElement *lpPosElement = lpVertexElement->FirstChildElement("position");
									//TiXmlElement *lpNormal = lpVertexElement->FirstChildElement("normal");

									lpPosElement->Attribute("x", &pos.x);
									lpPosElement->Attribute("y", &pos.y);
									lpPosElement->Attribute("z", &pos.z);

									//lpNormal->Attribute("x", &normal.x);
									//lpNormal->Attribute("y", &normal.y);
									//lpNormal->Attribute("z", &normal.z);

									pos.x *= boneInfo.boneScale.x;
									pos.y *= boneInfo.boneScale.y;
									pos.z *= boneInfo.boneScale.z;

									pos.x += boneInfo.bonePos.x;
									pos.y += boneInfo.bonePos.y;
									pos.z += boneInfo.bonePos.z;

									sprintf_s(szValue, _countof(szValue) - 1, "%f", pos.x);
									lpPosElement->SetAttribute("x", szValue);
									sprintf_s(szValue, _countof(szValue) - 1, "%f", pos.y);
									lpPosElement->SetAttribute("y", szValue);
									sprintf_s(szValue, _countof(szValue) - 1, "%f", pos.z);
									lpPosElement->SetAttribute("z", szValue);

									lpVertexElement = lpVertexElement->NextSiblingElement("vertex");
								}
							}

							if (bMeshHasSkeleton != false)
							{
								if (nBoneIdx > 0  )
								{
									// ÿ��submesh������Ϲ�����Ϣ
									TiXmlElement* lpBoneAssign = lpSubMesh->InsertEndChild(TiXmlElement("boneassignments"))->ToElement();
									for (int nIdx = 0; nIdx < nVertexcount; ++nIdx)
									{
										TiXmlElement* lpXmlElement = lpBoneAssign->InsertEndChild(TiXmlElement("vertexboneassignment"))->ToElement();
										lpXmlElement->SetAttribute("vertexindex", nIdx);
										lpXmlElement->SetAttribute("boneindex", nBoneIdx);
										lpXmlElement->SetAttribute("weight", 1);
									}
								}
							}
						}

						// ����mesh����submeshs��
						char szVal[128];
						sprintf_s(szVal, "submesh%d", nSubmeshNameIdx);
						TiXmlElement* lpXmlElement = lpTargetSubMeshName->InsertEndChild(TiXmlElement("submeshname"))->ToElement();
						lpXmlElement->SetAttribute("name", szVal);
						lpXmlElement->SetAttribute("index", nSubmeshNameIdx++);

						lpSrouceSubMesh = lpSrouceSubMesh->NextSibling("submesh");
					}
				}
			} while (::FindNextFile(hFile, &fd));
			::FindClose(hFile);

			if (bMeshHasSkeleton != false)
			{
				TCHAR szSkeleton[128];
				_stprintf_s(szSkeleton, _countof(szSkeleton) - 1, _T("%s.skeleton"), lpFinalName);
				CT2A szSkeleton1(szSkeleton);
				TiXmlElement* lpXmlElement = doc.FirstChildElement("mesh");
				lpXmlElement = lpXmlElement->InsertEndChild(TiXmlElement("skeletonlink"))->ToElement();
				lpXmlElement->SetAttribute("name", szSkeleton1);
			}

			optimizeSubmesh(doc.FirstChild());

			_stprintf_s(szFileName, _countof(szFileName) - 1, _T("%s\\%s.mesh.xml"), g_OutputDir, lpFinalName);
			CT2A strFile(szFileName);
			doc.SaveFile(strFile);

			return true;
		}
	}
	return false;
}

int getBoneIdx(LPCTSTR lpBone, BoneInfo &boneInfo)
{
	if (gs_BoneIdx.size() > 0)
	{
		TCHAR szBone[MAX_PATH];
		_tcsncpy_s(szBone, MAX_PATH, lpBone, MAX_PATH);
		LPTSTR lpTemp = _tcschr(szBone, '.');
		if (lpTemp != NULL)
		{
			*lpTemp = 0;
		}
		CT2A szBone1(szBone);

		for (std::vector<BoneInfo>::const_iterator it = gs_BoneIdx.begin(); it != gs_BoneIdx.end(); ++it)
		{
			if (it->boneName.compare(szBone1) == 0)
			{
				boneInfo = *it;
				return it - gs_BoneIdx.begin();
			}
		}
	}
	return -1;
};

void addBoneInfo(LPCSTR lpBoneName, myQua boneQua, myVec3 boneScale, myVec3 bonePos)
{
	BoneInfo boneInfo;
	boneInfo.boneName	= lpBoneName;
	boneInfo.boneQua	= boneQua;
	boneInfo.bonePos	= bonePos;
	boneInfo.boneScale	= boneScale;

	gs_BoneIdx.push_back( boneInfo );
}

bool hasSubEntity(TiXmlNode* lpNode)
{
	if ( lpNode && 
		lpNode->FirstChildElement("entity") )
	{
		return true;
	}

	return false;
}

bool hasAnimation(TiXmlNode* lpNode)
{
	if ( lpNode && 
		lpNode->FirstChildElement("animations") )
	{
		return true;
	}

	return false;
}

bool hasAnimations(TiXmlNode* lpParentNode)
{
	if ( lpParentNode )
	{
		if ( lpParentNode->FirstChildElement("animations") )
		{
			return true;
		}

		TiXmlNode* lpNode = lpParentNode->FirstChild();
		while ( lpNode )
		{
			if ( hasAnimations(lpNode) )
			{
				return true;
			}

			lpNode = lpNode->NextSibling();
		}
	}

	return false;
}

myQua getDeltaQua( myQua q1, myQua q2 )
{
	MG::Qua mgq1;
	MG::Qua mgq2;

	mgq1.x = (Flt)q1.x;
	mgq1.y = (Flt)q1.y;
	mgq1.z = (Flt)q1.z;
	mgq1.w = (Flt)q1.w;

	mgq2.x = (Flt)q2.x;
	mgq2.y = (Flt)q2.y;
	mgq2.z = (Flt)q2.z;
	mgq2.w = (Flt)q2.w;

	MG::Qua mgq3 = mgq1 * mgq2.Inverse();

	myQua resQua;

	resQua.x = (double)mgq3.x;
	resQua.y = (double)mgq3.y;
	resQua.z = (double)mgq3.z;
	resQua.w = (double)mgq3.w;

	return resQua;
}

void ToAngleAxis(const myQua& q, myVec3& rkAxis, double& fAngle)
{
	double fSqrLength = q.x*q.x + q.y*q.y + q.z*q.z;
	if (fSqrLength > 0.0)
	{
		////////////////////////////////////////////////////

		if (-1.0 < q.w)
		{
			if (q.w < 1.0)
			{
				fAngle = acos(q.w);
			}
			else
			{
				fAngle = .0f;
			}
		}
		else
		{
			fAngle = 2.0 * atan( 1.0 ) ;
		}

		fAngle *= 2.0f;

		//////////////////////////////////////////////////////////////////////////

		double fInvLength = 1.0f / sqrt(fSqrLength);
		rkAxis.x = q.x * fInvLength;
		rkAxis.y = q.y * fInvLength;
		rkAxis.z = q.z * fInvLength;
	}
	else
	{
		// angle is 0 (mod 2*pi), so any axis will do
		fAngle = .0f;
		rkAxis.x = 1.0;
		rkAxis.y = 0.0;
		rkAxis.z = 0.0;
	}
};

void optimizeSubmesh(TiXmlNode* lpXmlNode)
{
	if (lpXmlNode != NULL)
	{
		// ��ȡ������Ҫ�ڵ� submeshs �� submeshnames.	
		TiXmlElement* lpSubmeshes = lpXmlNode->FirstChildElement("submeshes");
		TiXmlElement* lpSubmeshnames = lpXmlNode->FirstChildElement("submeshnames");
		if ((lpSubmeshes != NULL) && (lpSubmeshnames != NULL))
		{
			// ����ÿһ��submesh
			int nCurrentSubmeshIdx = 0;
			TiXmlElement* lpCurrentSubmesh = lpSubmeshes->FirstChildElement("submesh");
			TiXmlElement* lpCurrentSubmeshName = lpSubmeshnames->FirstChildElement("submeshname");

			while (lpCurrentSubmesh != NULL)
			{
				// ����submesh�Ĳ�����Ϣȡ��
				const char* lpszMaterial = lpCurrentSubmesh->Attribute("material");
				// ͬʱ����ͬ��������submesh
				TiXmlElement* lpXmlElement = lpCurrentSubmesh->NextSiblingElement("submesh");
				TiXmlElement* lpXmlElementName = lpCurrentSubmeshName->NextSiblingElement("submeshname");

				while (lpXmlElement != NULL)
				{
					// ��ȡ���͵�ǰ��submesh������ͬ��submesh
					if (strcmp(lpXmlElement->Attribute("material"), lpszMaterial) == 0)
					{
						break;
					}
					lpXmlElement = lpXmlElement->NextSiblingElement("submesh");
					lpXmlElementName = lpXmlElementName->NextSiblingElement("submeshname");
				}

				if (lpXmlElement != NULL)
				{//��ͬ����
					TiXmlElement* lpFace0 = lpCurrentSubmesh->FirstChildElement("faces");
					TiXmlElement* lpFace1 = lpXmlElement->FirstChildElement("faces");
					TiXmlElement* lpGeometry0 = lpCurrentSubmesh->FirstChildElement("geometry");
					TiXmlElement* lpGeometry1 = lpXmlElement->FirstChildElement("geometry");
					TiXmlElement* lpBone0 = lpCurrentSubmesh->FirstChildElement("boneassignments");
					TiXmlElement* lpBone1 = lpXmlElement->FirstChildElement("boneassignments");

					//����ǰsubmesh��facecount��vertexcount����
					int nStartIdx;
					lpFace0->SetAttribute("count", strtol(lpFace0->Attribute("count"), NULL, 0) + strtol(lpFace1->Attribute("count"), NULL, 0));
					if (lpGeometry0->Attribute("vertexcount", &nStartIdx) == NULL)
					{
						nStartIdx = 0;
					}
					lpGeometry0->SetAttribute("vertexcount", strtol(lpGeometry0->Attribute("vertexcount"), NULL, 0) + strtol(lpGeometry1->Attribute("vertexcount"), NULL, 0));

					//��������Ϣ
					//����Ŀ��submesh��ÿһ��face
					lpFace1 = lpFace1->FirstChildElement("face");
					while (lpFace1 != NULL)
					{
						// ������Ϣ�������뵱ǰsubmesh��face��
						TiXmlElement* lpValue = lpFace0->InsertEndChild(*lpFace1->Clone())->ToElement();
						// ����������
						int v;
						lpValue->Attribute("v1", &v);
						lpValue->SetAttribute("v1", v + nStartIdx);
						lpValue->Attribute("v2", &v);
						lpValue->SetAttribute("v2", v + nStartIdx);
						lpValue->Attribute("v3", &v);
						lpValue->SetAttribute("v3", v + nStartIdx);

						lpFace1 = lpFace1->NextSiblingElement("face");
					}

					// ���ƶ�����Ϣ
					// ��ȡ��ǰ�����vertexbuffer�ڵ�
					lpGeometry0 = lpGeometry0->FirstChildElement("vertexbuffer");
					lpGeometry1 = lpGeometry1->FirstChildElement("vertexbuffer");
					// ��ȡĿ������vertex�ڵ�
					lpGeometry1 = lpGeometry1->FirstChildElement("vertex");
					// ����Ŀ������ÿһ��vertex�ڵ�
					while (lpGeometry1 != NULL)
					{
						// ��Ŀ������vertex�ڵ���뵱ǰ�����vertexbuffer�ڵ�
						lpGeometry0->InsertEndChild(*lpGeometry1->Clone());
						lpGeometry1 = lpGeometry1->NextSiblingElement("vertex");
					}

					//���ƹ�������
					lpBone1 = lpBone1->FirstChildElement("vertexboneassignment");
					while (lpBone1 != NULL)
					{
						TiXmlElement* lpValue = lpBone0->InsertEndChild(*lpBone1->Clone())->ToElement();
						int v;
						lpValue->Attribute("vertexindex", &v);
						lpValue->SetAttribute("vertexindex", v + nStartIdx);

						lpBone1 = lpBone1->NextSiblingElement("vertexboneassignment");
					}

					//ɾ���ڵ�
					lpSubmeshes->RemoveChild(lpXmlElement);
					lpSubmeshnames->RemoveChild(lpXmlElementName);
				}
				else
				{
					//���û���޷���������ͬ���ʵ�submesh, �ͽ���ǰsubmesh��ǰ������
					++nCurrentSubmeshIdx;
					lpCurrentSubmesh = lpCurrentSubmesh->NextSiblingElement("submesh");
				}
			}
		}
	}
};

