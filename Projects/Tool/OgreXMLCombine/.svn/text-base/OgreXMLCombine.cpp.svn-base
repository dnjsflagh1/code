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

bool		convertSkeleton(_TCHAR* lpFinalName, _TCHAR* lpAnimation); //生成骨骼文件skeleton.xml文件;
bool		combineSubMesh(_TCHAR* lpFinalName, bool bMeshHasSkeleton); //生成mesh.xml文件;
void		optimizeSubmesh(TiXmlNode* lpXmlNode); //合并相同材质的submesh;

int			getBoneIdx(LPCTSTR lpBone, BoneInfo& boneInfo); //根据骨骼文件名获取骨骼索引;
void		addBoneInfo(LPCSTR lpBoneName, myQua boneQua, myVec3 boneScale, myVec3 bonePos); //将骨骼信息加入全局列表

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

		// 输入路径
		if ( argc > 2)
		{
			g_InputDir = argv[2];
		}

		// 输出路径
		if ( argc > 3 )
		{
			g_OutputDir = argv[3];
		}

		// 确认动画名称
		if ( argc > 4)
		{
			_stprintf_s( szAnimName, _countof(szAnimName) - 1, _T("%s"), argv[4] );	
		}

		///////////////////////////////////////////////////////////////////////////////////////////////

		// 创建输入输出文件路径

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

		// 创建骨骼文件
		bool bMeshHasSkeleton = convertSkeleton(argv[1], szAnimName);

		// 创建网格文件
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
		// 在目标doc中创建骨骼信息。
		TiXmlElement* lpSkeleton = doc.InsertEndChild(TiXmlElement("skeleton"))->ToElement();
		// 当前骨骼的混合模式
		lpSkeleton->SetAttribute("blendmode", "average");
		// 将bones节点加入目标doc的skeleton节点
		TiXmlElement* lpBones = lpSkeleton->InsertEndChild(TiXmlElement("bones"))->ToElement();
		// 将bonehierarchy节点加入目标的doc的skeleton节点
		TiXmlElement* lpBonehierarchy = lpSkeleton->InsertEndChild(TiXmlElement("bonehierarchy"))->ToElement();

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//进行骨骼定义，在bones节点首先插入一个根骨骼
		TiXmlElement* lpBone = lpBones->InsertEndChild(TiXmlElement("bone"))->ToElement();
		lpBone->SetAttribute("id", nBoneIdx++);
		lpBone->SetAttribute("name", PARENT_BONE);

		//开始进行动作文件处理，开始读取model文件
		TiXmlDocument node;
		_stprintf_s(szFileName, _countof(szFileName) - 1, _T("%s\\%s"), g_InputDir, fd.cFileName);
		node.LoadFile(CT2A(szFileName));

		if (node.Error() == false)
		{
			//定义父骨骼位置信息。
			TiXmlElement* lpNode = node.FirstChildElement("node");
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			TiXmlElement* lpAnimations = NULL;

			if ( hasAnimations(lpNode) )
			{
				// 将animations节点加入目标doc的skeleton节点
				lpAnimations = lpSkeleton->InsertEndChild(TiXmlElement("animations"))->ToElement();
				// 将animation节点加入目标doc的animations节点
				TiXmlElement* lpAnimation = lpAnimations->InsertEndChild(TiXmlElement("animation"))->ToElement();
				// 将tracks节点加入animation节点
				lpAnimation->InsertEndChild(TiXmlElement("tracks"))->ToElement();
				// 当前animation的名称
				lpAnimation->SetAttribute("name", animName);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// 创建根骨骼

			if (lpNode != NULL)
			{
				// 完全拷贝node的位置信息
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

					//定义骨骼父子关系
					lpBone = lpBonehierarchy->InsertEndChild(TiXmlElement("boneparent"))->ToElement();
					lpBone->SetAttribute("bone", lpNode->Attribute("name"));
					lpBone->SetAttribute("parent", PARENT_BONE );
					
					//创建骨骼
					lpBone = lpBones->InsertEndChild(TiXmlElement("bone"))->ToElement();
					lpBone->SetAttribute("id", nBoneIdx++);
					lpBone->SetAttribute("name", lpNode->Attribute("name"));

					//获取骨骼空间pos和orientation信息
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

					//加入boneList
					addBoneInfo(lpNode->Attribute("name"), q, scale, pos);

					//将四元数信息转化为旋转轴以及角度
					ToAngleAxis(q, axis, fAngle);

					//初始化骨骼信息
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

						//转化动作序列
						TiXmlElement* lpAnimationElement = lpNode->FirstChild("animations")->ToElement();
						lpAnimationElement = lpAnimationElement->FirstChild("animation")->ToElement();

						//获取节点动画的长度
						lpAnimationElement->Attribute("length", &fNodeLength);

						//初始化该动画的动画长度， 因为节点动画文件中， 每个节点都有一个动画时间。
						//但是骨骼动画文件中所有骨骼的动画时间是公用的。
						TiXmlElement* lpAnimation = lpAnimations->FirstChildElement("animation");
						if (lpAnimation->Attribute("length", &fSkeletonLength) == NULL)
						{
							fSkeletonLength = .0f;
						}

						//写入动画长度
						if (fNodeLength > fSkeletonLength)
						{
							char szValue[64];
							sprintf_s(szValue, "%f", fNodeLength);
							lpAnimation->SetAttribute("length", szValue);
						}

						//构建tracks和track
						TiXmlElement* lpTrack = lpAnimation->FirstChild("tracks")->ToElement();
						lpTrack = lpTrack->InsertEndChild(TiXmlElement("track"))->ToElement();
						lpTrack->SetAttribute("bone", lpNode->Attribute("name"));

						//在track下面构建keyFrames
						lpTrack = lpTrack->InsertEndChild(TiXmlElement("keyframes"))->ToElement();
						//读取model文件中，对应node的keyFrame文件
						TiXmlNode* lpKeyFrame = lpAnimationElement->FirstChild("keyframe");

						while (lpKeyFrame != NULL)
						{
							CA2T szboneName(lpNode->Attribute("name"));
							BoneInfo boneInfo;
							getBoneIdx( szboneName, boneInfo );

							//直接拷贝了node文件的keyFrame过来。
							TiXmlElement* lpSkeletonKeyFrame = lpTrack->InsertEndChild(*lpKeyFrame->Clone())->ToElement();

							//处理动画帧的位移信息， 获取和骨骼绑定位置的相对位移.
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

							//处理动画帧节点的rotate信息，获取和绑定点的相对方向
							TiXmlElement* lpSkeletonKeyFrameRotation = lpSkeletonKeyFrame->FirstChildElement("rotation");

							lpSkeletonKeyFrameRotation->Attribute("qx", &q.x);
							lpSkeletonKeyFrameRotation->Attribute("qy", &q.y);
							lpSkeletonKeyFrameRotation->Attribute("qz", &q.z);
							lpSkeletonKeyFrameRotation->Attribute("qw", &q.w);

							ToAngleAxis(getDeltaQua(q, boneInfo.boneQua), axis, fAngle);

							lpSkeletonKeyFrame->RemoveChild(lpSkeletonKeyFrameRotation);
							lpSkeletonKeyFrame->RemoveChild(lpSkeletonKeyFrame->FirstChild("scale")->ToElement());

							// 建立新的rotate格式的节点
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
			// 整合后的mesh文件建立
			TiXmlElement* lpTargetSubMesh = doc.InsertEndChild(TiXmlElement("mesh"))->ToElement();
			TiXmlElement* lpTargetSubMeshName = lpTargetSubMesh;
			// 加入submeshes子节点
			lpTargetSubMesh = lpTargetSubMesh->InsertEndChild(TiXmlElement("submeshes"))->ToElement();
			// 加入submeshnames子节点
			lpTargetSubMeshName = lpTargetSubMeshName->InsertEndChild(TiXmlElement("submeshnames"))->ToElement();

			do 
			{
				// 遍历读取所有的mesh.xml文件， 将每个mesh文件中的submesh合并到
				_stprintf_s(szFileName, _countof(szFileName) - 1, _T("%s\\%s"), g_InputDir, fd.cFileName);
				TiXmlDocument mesh;
				CT2A strFile(szFileName);
				mesh.LoadFile(strFile);
				if (mesh.Error() == false)
				{
					// 读取骨骼信息
					BoneInfo boneInfo;
					// 如果无法获取骨骼信息， 则继续遍历下个文件
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
						// 拷贝整个submesh节点
						TiXmlElement* lpSubMesh = lpTargetSubMesh->InsertEndChild(*lpSrouceSubMesh->Clone())->ToElement();

						// 寻找到拷贝完之后的geometry节点
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
									// 每个submesh里面加上骨骼信息
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

						// 将此mesh放入submeshs中
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
		// 获取两个主要节点 submeshs 和 submeshnames.	
		TiXmlElement* lpSubmeshes = lpXmlNode->FirstChildElement("submeshes");
		TiXmlElement* lpSubmeshnames = lpXmlNode->FirstChildElement("submeshnames");
		if ((lpSubmeshes != NULL) && (lpSubmeshnames != NULL))
		{
			// 遍历每一个submesh
			int nCurrentSubmeshIdx = 0;
			TiXmlElement* lpCurrentSubmesh = lpSubmeshes->FirstChildElement("submesh");
			TiXmlElement* lpCurrentSubmeshName = lpSubmeshnames->FirstChildElement("submeshname");

			while (lpCurrentSubmesh != NULL)
			{
				// 将该submesh的材质信息取出
				const char* lpszMaterial = lpCurrentSubmesh->Attribute("material");
				// 同时遍历同级的其他submesh
				TiXmlElement* lpXmlElement = lpCurrentSubmesh->NextSiblingElement("submesh");
				TiXmlElement* lpXmlElementName = lpCurrentSubmeshName->NextSiblingElement("submeshname");

				while (lpXmlElement != NULL)
				{
					// 获取到和当前的submesh材质相同的submesh
					if (strcmp(lpXmlElement->Attribute("material"), lpszMaterial) == 0)
					{
						break;
					}
					lpXmlElement = lpXmlElement->NextSiblingElement("submesh");
					lpXmlElementName = lpXmlElementName->NextSiblingElement("submeshname");
				}

				if (lpXmlElement != NULL)
				{//相同材质
					TiXmlElement* lpFace0 = lpCurrentSubmesh->FirstChildElement("faces");
					TiXmlElement* lpFace1 = lpXmlElement->FirstChildElement("faces");
					TiXmlElement* lpGeometry0 = lpCurrentSubmesh->FirstChildElement("geometry");
					TiXmlElement* lpGeometry1 = lpXmlElement->FirstChildElement("geometry");
					TiXmlElement* lpBone0 = lpCurrentSubmesh->FirstChildElement("boneassignments");
					TiXmlElement* lpBone1 = lpXmlElement->FirstChildElement("boneassignments");

					//将当前submesh的facecount和vertexcount扩容
					int nStartIdx;
					lpFace0->SetAttribute("count", strtol(lpFace0->Attribute("count"), NULL, 0) + strtol(lpFace1->Attribute("count"), NULL, 0));
					if (lpGeometry0->Attribute("vertexcount", &nStartIdx) == NULL)
					{
						nStartIdx = 0;
					}
					lpGeometry0->SetAttribute("vertexcount", strtol(lpGeometry0->Attribute("vertexcount"), NULL, 0) + strtol(lpGeometry1->Attribute("vertexcount"), NULL, 0));

					//复制面信息
					//遍历目标submesh的每一个face
					lpFace1 = lpFace1->FirstChildElement("face");
					while (lpFace1 != NULL)
					{
						// 将面信息拷贝塞入当前submesh的face中
						TiXmlElement* lpValue = lpFace0->InsertEndChild(*lpFace1->Clone())->ToElement();
						// 顶点编号增加
						int v;
						lpValue->Attribute("v1", &v);
						lpValue->SetAttribute("v1", v + nStartIdx);
						lpValue->Attribute("v2", &v);
						lpValue->SetAttribute("v2", v + nStartIdx);
						lpValue->Attribute("v3", &v);
						lpValue->SetAttribute("v3", v + nStartIdx);

						lpFace1 = lpFace1->NextSiblingElement("face");
					}

					// 复制顶点信息
					// 获取当前对象的vertexbuffer节点
					lpGeometry0 = lpGeometry0->FirstChildElement("vertexbuffer");
					lpGeometry1 = lpGeometry1->FirstChildElement("vertexbuffer");
					// 获取目标对象的vertex节点
					lpGeometry1 = lpGeometry1->FirstChildElement("vertex");
					// 便利目标对象的每一个vertex节点
					while (lpGeometry1 != NULL)
					{
						// 将目标对象的vertex节点放入当前对象的vertexbuffer节点
						lpGeometry0->InsertEndChild(*lpGeometry1->Clone());
						lpGeometry1 = lpGeometry1->NextSiblingElement("vertex");
					}

					//复制骨骼定义
					lpBone1 = lpBone1->FirstChildElement("vertexboneassignment");
					while (lpBone1 != NULL)
					{
						TiXmlElement* lpValue = lpBone0->InsertEndChild(*lpBone1->Clone())->ToElement();
						int v;
						lpValue->Attribute("vertexindex", &v);
						lpValue->SetAttribute("vertexindex", v + nStartIdx);

						lpBone1 = lpBone1->NextSiblingElement("vertexboneassignment");
					}

					//删除节点
					lpSubmeshes->RemoveChild(lpXmlElement);
					lpSubmeshnames->RemoveChild(lpXmlElementName);
				}
				else
				{
					//如果没有无法遍历到相同材质的submesh, 就将当前submesh往前遍历。
					++nCurrentSubmeshIdx;
					lpCurrentSubmesh = lpCurrentSubmesh->NextSiblingElement("submesh");
				}
			}
		}
	}
};

