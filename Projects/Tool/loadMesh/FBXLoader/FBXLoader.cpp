
#include "FBXLoader.hpp"

#include <assert.h>

#ifdef _DEBUG
#pragma comment(lib, "fbxsdk-2013.2-mtd.lib")
#else
#pragma comment(lib, "fbxsdk-2013.2-mt.lib")
#endif

#ifdef _DEBUG
#undef FBXSDK_printf
#define FBXSDK_printf(...)
#endif

static bool InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene)
{
	//The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
	pManager = FbxManager::Create();
	if (pManager == NULL)
	{
		return false;
	}
	else
	{
		FBXSDK_printf("Autodesk FBX SDK version %s\n", pManager->GetVersion());
	}

	//Create an IOSettings object. This object holds all import/export settings.
	FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(ios);

	//Load plugins from the executable directory (optional)
	FbxString lPath = FbxGetApplicationDirectory();
	pManager->LoadPluginsDirectory(lPath.Buffer());

	//Create an FBX scene. This object holds most objects imported/exported from/to files.
	pScene = FbxScene::Create(pManager, "FBX_Import_Scene");
	if (pScene == NULL)
	{
		FBXSDK_printf("Error: Unable to create FBX scene!\n");

		pManager->Destroy();
		pManager = NULL;
		return false;
	}

	return true;
}

// Triangulate all NURBS, patch and mesh under this node recursively.
static void TriangulateRecursive(FbxNode* pNode)
{
	FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();
	if (lNodeAttribute != NULL)
	{
		if ((lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
			|| (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eNurbs)
			|| (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eNurbsSurface)
			|| (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::ePatch))
		{
			const char* lpName = pNode->GetName();
			FbxGeometryConverter lConverter(pNode->GetFbxManager());
			lConverter.TriangulateInPlace(pNode);
		}
	}

	const int lChildCount = pNode->GetChildCount();
	for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
	{
		TriangulateRecursive(pNode->GetChild(lChildIndex));
	}
}

// Get the geometry offset to a node. It is never inherited by the children.
inline static FbxAMatrix GetGeometry(FbxNode* pNode)
{
	pNode->EvaluateLocalTransform(0);
	FbxVector4 prV = pNode->LclRotation.Get();
	return FbxAMatrix(pNode->LclTranslation.Get(), pNode->LclRotation.Get(), pNode->LclScaling.Get());
}

CFBXLoader::CFBXLoader(void)
{
	InitializeSdkObjects(m_lpSdkManager, m_lpScene);
	assert(m_lpScene != NULL);
}


CFBXLoader::~CFBXLoader(void)
{
	m_lpScene->Destroy(true);
	m_lpScene = NULL;
	m_lpSdkManager->Destroy();
	m_lpSdkManager = NULL;
}

bool CFBXLoader::convertFbxToMesh(const char* lpszFile, Ogre::Mesh* lpMesh)
{
	if (lpMesh != NULL)
	{
		if ((loadMeshFromFile(lpszFile) != false) && (getMeshInfo() != false))
		{
			lpMesh->sharedVertexData = new Ogre::VertexData;
			if (readGeometry(lpMesh) != false)
			{
				return generateSubMesh(lpMesh);
			}
		}
	}

	return false;
};

bool CFBXLoader::loadMeshFromFile(const char* lpszFile)
{
	assert(m_lpScene != NULL);
	assert((lpszFile != NULL) && (lpszFile[0] != 0));

	bool bResult = false;

	m_nControlPointsCount = 0;
	m_nMeshVertexInfo = 0;
	m_nMaxBoneCount = 0;
	m_nMeshBone.clear();

	if ((m_lpScene != NULL) && (lpszFile != NULL) && (lpszFile[0] != 0))
	{
		// Create the importer.
		FbxImporter* lpImporter = FbxImporter::Create(m_lpSdkManager, "");
		if (lpImporter != NULL)
		{
			int lFileFormat = -1;
			if (m_lpSdkManager->GetIOPluginRegistry()->DetectReaderFileFormat(lpszFile, lFileFormat) == false)
			{
				// Unrecognizable file format. Try to fall back to FbxImporter::eFBX_BINARY
				lFileFormat = m_lpSdkManager->GetIOPluginRegistry()->FindReaderIDByDescription( "FBX binary (*.fbx)" );;
			}

			m_lpScene->Clear();
			if ((lpImporter->Initialize(lpszFile, lFileFormat) != false) && (lpImporter->Import(m_lpScene) != false))
			{
				//convertMesh();
				bResult = true;
			}

			lpImporter->Destroy(true);
		}
	}
	return bResult;
};

bool CFBXLoader::getMeshInfo(void)
{
	assert(m_lpScene != NULL);

	if ((m_lpScene != NULL) && (m_lpScene->GetNodeCount() > 0))
	{
		int nNodeIdx = 0;
		FbxNode* lpNode = m_lpScene->GetNode(nNodeIdx++);

		while (lpNode != NULL)
		{
			const FbxNodeAttribute* lpNodeAttribute = lpNode->GetNodeAttribute();
			const FbxNodeAttribute::EType nAttributeType = lpNodeAttribute != NULL ? lpNodeAttribute->GetAttributeType() : FbxNodeAttribute::eUnknown;
			if (nAttributeType == FbxNodeAttribute::eMesh)
			{
				FbxMesh* lpMesh = lpNode->GetMesh();

				if ((lpMesh != NULL) && (lpMesh->GetControlPointsCount() > 0))
				{
					m_nFbxMeshInfo.setSemanticInfo(Ogre::VES_POSITION);

					for (int nLayer = 0; nLayer < lpMesh->GetElementNormalCount(); ++nLayer)
					{
						const FbxGeometryElement::EMappingMode nMappingMode = lpMesh->GetElementNormal(nLayer)->GetMappingMode();
						if ((nMappingMode == FbxGeometryElement::eByControlPoint) || (nMappingMode == FbxGeometryElement::eByPolygonVertex))
						{
							m_nFbxMeshInfo.setSemanticInfo(Ogre::VES_NORMAL);
							break;
						}
					}

					for (int nLayer = 0; nLayer < lpMesh->GetElementBinormalCount(); ++nLayer)
					{
						const FbxGeometryElement::EMappingMode nMappingMode = lpMesh->GetElementBinormal(nLayer)->GetMappingMode();
						if ((nMappingMode == FbxGeometryElement::eByControlPoint) || (nMappingMode == FbxGeometryElement::eByPolygonVertex))
						{
							m_nFbxMeshInfo.setSemanticInfo(Ogre::VES_BINORMAL);
							break;
						}
					}

					for (int nLayer = 0; nLayer < lpMesh->GetElementTangentCount(); ++nLayer)
					{
						const FbxGeometryElement::EMappingMode nMappingMode = lpMesh->GetElementTangent(nLayer)->GetMappingMode();
						if ((nMappingMode == FbxGeometryElement::eByControlPoint) || (nMappingMode == FbxGeometryElement::eByPolygonVertex))
						{
							m_nFbxMeshInfo.setSemanticInfo(Ogre::VES_TANGENT);
							break;
						}
					}

					for (int nIdx = 0; nIdx < lpMesh->GetDeformerCount(); ++nIdx)
					{
						FbxDeformer* lpFbxDeformer = lpMesh->GetDeformer(nIdx);
						FbxSkin* lpFBXSkin = (lpFbxDeformer != NULL) && (lpFbxDeformer->GetDeformerType() == FbxDeformer::eSkin) ? (FbxSkin*)lpFbxDeformer : NULL;
						if (lpFBXSkin != NULL)
						{
							m_nFbxMeshInfo.setSemanticInfo(Ogre::VES_BLEND_INDICES);
							break;
						}
					}

					if (lpMesh->GetElementVertexColorCount() > 0)
					{
						//m_nFbxMeshInfo.setSemanticInfo(Ogre::VES_)
					}

					//纹理贴图
					size_t nTextureLayers = 0;
					for (int nLayer = 0; nLayer < lpMesh->GetElementUVCount(); ++nLayer)
					{
						const FbxGeometryElement::EMappingMode nMappingMode = lpMesh->GetElementUV(nLayer)->GetMappingMode();
						if ((nMappingMode == FbxGeometryElement::eByControlPoint) || (nMappingMode == FbxGeometryElement::eByPolygonVertex))
						{
							++nTextureLayers;
						}
					}

					if (nTextureLayers > 4)
					{
						nTextureLayers = 4;
					}
					if (nTextureLayers > m_nFbxMeshInfo.getVertexElementSemanticInfo(Ogre::VES_TEXTURE_COORDINATES))
					{
						m_nFbxMeshInfo.setSemanticInfo(Ogre::VES_TEXTURE_COORDINATES, nTextureLayers);
					}

					//lpMesh->GetMaterialIndices();
					//lpMesh->GetElementMaterial()->GetIndexArray()

					const char* lpszMeshName = lpNode->GetName();
					if ((lpszMeshName == NULL) || (lpszMeshName[0] == 0))
					{
						lpszMeshName = lpMesh->GetName();
					}
					if ((lpszMeshName == NULL) || (lpszMeshName[0] == 0))
					{//mesh无名称
						continue;;
					}

					float fValue = .0f;
					if (sscanf_s(lpszMeshName, "%*[^0-9]%f", &fValue) != 1)
					{//mesh名称非法
						continue;;
					}

					m_stMeshVertexInfo[m_nMeshVertexInfo].m_lpszMeshName = lpszMeshName;
					m_stMeshVertexInfo[m_nMeshVertexInfo].m_fValue = fValue;
					m_stMeshVertexInfo[m_nMeshVertexInfo].m_bProcessed = false;
					m_stMeshVertexInfo[m_nMeshVertexInfo].m_nVertexBase = m_nControlPointsCount;
					m_nControlPointsCount += lpMesh->GetControlPointsCount();
					m_stMeshVertexInfo[m_nMeshVertexInfo].m_lpMesh = lpMesh;
					++m_nMeshVertexInfo;
					if (m_nMeshVertexInfo >= eMaxFbxMesh)
					{
						break;;
					}
				}
			}
			else if (nAttributeType == FbxNodeAttribute::eSkeleton)
			{
				const FbxSkeleton* lpFbxSkeleton = lpNode->GetSkeleton();
				const char* lp = lpNode->GetName();
				m_nBones[m_nMaxBoneCount++] = lpNode;
			}

			lpNode = m_lpScene->GetNode(nNodeIdx++);
		}

		return m_nControlPointsCount > 0;
	}

	return false;
};

void CFBXLoader::convertMesh(void)
{
	assert(m_lpScene != NULL);
	if (m_lpScene != NULL)
	{
		// Convert mesh, NURBS and patch into triangle mesh
		TriangulateRecursive(m_lpScene->GetRootNode());
	}
};

bool CFBXLoader::readGeometry(Ogre::Mesh* lpMesh)
{
	size_t nVertexSize = 0;
	Ogre::VertexDeclaration* decl = lpMesh->sharedVertexData->vertexDeclaration;
	Ogre::VertexBufferBinding* bind = lpMesh->sharedVertexData->vertexBufferBinding;

	assert(decl != NULL);
	assert(bind != NULL);

	//顶点
	if (m_nFbxMeshInfo.isValidSemanticInfo(Ogre::VES_POSITION) != false)
	{
		decl->addElement(0, nVertexSize, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
		nVertexSize += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
	}

	//蒙皮权重
	if (m_nFbxMeshInfo.isValidSemanticInfo(Ogre::VES_BLEND_WEIGHTS) != false)
	{
		decl->addElement(0, nVertexSize, Ogre::VET_FLOAT4, Ogre::VES_BLEND_WEIGHTS);
		nVertexSize += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT4);
	}

	//蒙皮
	if (m_nFbxMeshInfo.isValidSemanticInfo(Ogre::VES_BLEND_INDICES) != false)
	{
		decl->addElement(0, nVertexSize, Ogre::VET_UBYTE4, Ogre::VES_BLEND_INDICES);
		nVertexSize += Ogre::VertexElement::getTypeSize(Ogre::VET_UBYTE4);
	}

	//法线
	if (m_nFbxMeshInfo.isValidSemanticInfo(Ogre::VES_NORMAL) != false)
	{
		decl->addElement(0, nVertexSize, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
		nVertexSize += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
	}

	//diffuse
	if (m_nFbxMeshInfo.isValidSemanticInfo(Ogre::VES_DIFFUSE) != false)
	{
		decl->addElement(0, nVertexSize, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
		nVertexSize += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);
	}

	//高光
	if (m_nFbxMeshInfo.isValidSemanticInfo(Ogre::VES_SPECULAR) != false)
	{
		decl->addElement(0, nVertexSize, Ogre::VET_FLOAT1, Ogre::VES_SPECULAR);
		nVertexSize += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT1);
	}

	//Texture
	for (size_t nIdx = 0; nIdx < m_nFbxMeshInfo.getVertexElementSemanticInfo(Ogre::VES_TEXTURE_COORDINATES); ++nIdx)
	{
		// Add element
		decl->addElement(0, nVertexSize, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES, nIdx);
		nVertexSize += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);
	}

	//次法线
	if (m_nFbxMeshInfo.isValidSemanticInfo(Ogre::VES_BINORMAL) != false)
	{
		decl->addElement(0, nVertexSize, Ogre::VET_FLOAT3, Ogre::VES_BINORMAL);
		nVertexSize += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
	}

	//切线
	if (m_nFbxMeshInfo.isValidSemanticInfo(Ogre::VES_TANGENT) != false)
	{
		decl->addElement(0, nVertexSize, Ogre::VET_FLOAT3, Ogre::VES_TANGENT);
		nVertexSize += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
	}

	//生成顶点数据
	lpMesh->sharedVertexData->vertexCount = m_nControlPointsCount;
	// Now create the vertex buffer
	Ogre::HardwareVertexBufferSharedPtr vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(nVertexSize, m_nControlPointsCount, 
		Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);

	// Bind it
	bind->setBinding(0, vbuf);
	// Lock it
	unsigned char* lpVert = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
	// Get the element list for this buffer alone
	Ogre::VertexDeclaration::VertexElementList elems = decl->findElementsBySource(0);

	// Information for calculating bounds
	Ogre::Vector3 min = Ogre::Vector3::ZERO, max = Ogre::Vector3::UNIT_SCALE, pos = Ogre::Vector3::ZERO;
	Ogre::Real maxSquaredRadius = -1;
	bool first = true;
	int nVertexBase = 0;

	for (size_t nIdx = 0; nIdx < m_nMeshVertexInfo; ++ nIdx)
	{
		FbxMesh* lpFbxMesh = m_stMeshVertexInfo[nIdx].m_lpMesh;
		FbxAMatrix nTransform = GetGeometry(lpFbxMesh->GetNode());
		const int lControlPointsCount = lpFbxMesh->GetControlPointsCount();
		const FbxSkin* lpSkeletonSkin = NULL;
		const int nDeformerCount = lpFbxMesh->GetDeformerCount();

		//获取骨骼蒙皮
		for (int nIdx = 0; nIdx < nDeformerCount; ++nIdx)
		{
			const FbxDeformer* lpFbxDeformer = lpFbxMesh->GetDeformer(nIdx);
			if ((lpFbxDeformer != NULL) && (lpFbxDeformer->GetDeformerType() == FbxDeformer::eSkin))
			{
				lpSkeletonSkin = (FbxSkin*)lpFbxDeformer;
				break;
			}
		}

		for (int i = 0; i < lControlPointsCount; i++)
		{
			// Now parse the elements, ensure they are all matched
			int nTextureLayer = 0;
			Ogre::VertexDeclaration::VertexElementList::const_iterator ielem, ielemend;
			ielemend = elems.end();
			for (ielem = elems.begin(); ielem != ielemend; ++ielem)
			{
				const Ogre::VertexElement& elem = *ielem;
				// Find child for this element
				switch(elem.getSemantic())
				{
				case Ogre::VES_POSITION:
					{
						float *pFloat;
						const FbxVector4 nControlPoint = nTransform.MultT(lpFbxMesh->GetControlPointAt(i));
						elem.baseVertexPointerToElement(lpVert, &pFloat);

						pos.x = static_cast<float>(nControlPoint[0]);
						pos.y = static_cast<float>(nControlPoint[1]);
						pos.z = static_cast<float>(nControlPoint[2]);

						*pFloat++ = pos.x;
						*pFloat++ = pos.y;
						*pFloat++ = pos.z;

						if (first != false)
						{
							min = max = pos;
							maxSquaredRadius = pos.squaredLength();
							first = false;
						}
						else
						{
							min.makeFloor(pos);
							max.makeCeil(pos);
							maxSquaredRadius = std::max(pos.squaredLength(), maxSquaredRadius);
						}
					}
					break;

				case Ogre::VES_NORMAL:
					{
						float *pFloat;
						FbxVector4 nCurrentNormal;
						const int nNormalCount = lpFbxMesh->GetElementNormalCount();

						for (int nLayer = 0; nLayer < nNormalCount; ++nLayer)
						{
							FbxGeometryElementNormal* lpGeometryElement = lpFbxMesh->GetElementNormal(nLayer);
							const FbxGeometryElement::EMappingMode nMappingMode = lpGeometryElement->GetMappingMode();
							if ((nMappingMode == FbxGeometryElement::eByPolygonVertex) || (nMappingMode == FbxGeometryElement::eByControlPoint))
							{
								int nIdx = (lpGeometryElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect) ? lpGeometryElement->GetIndexArray().GetAt(i) : i;
								nCurrentNormal += lpGeometryElement->GetDirectArray().GetAt(nIdx);
							}
						}

						nCurrentNormal.Normalize();
						elem.baseVertexPointerToElement(lpVert, &pFloat);
						*pFloat++ = static_cast<float>(nCurrentNormal[0]);
						*pFloat++ = static_cast<float>(nCurrentNormal[1]);
						*pFloat++ = static_cast<float>(nCurrentNormal[2]);
					}
					break;

				case Ogre::VES_BINORMAL:
					{
						float *pFloat;
						FbxVector4 nCurrentBiNormal(.0f, .0f, .0f);
						const int nNormalCount = lpFbxMesh->GetElementBinormalCount();

						for (int nLayer = 0; nLayer < nNormalCount; ++nLayer)
						{
							FbxGeometryElementBinormal* lpGeometryElement = lpFbxMesh->GetElementBinormal(nLayer);
							const FbxGeometryElement::EMappingMode nMappingMode = lpGeometryElement->GetMappingMode();
							if ((nMappingMode == FbxGeometryElement::eByPolygonVertex) || (nMappingMode == FbxGeometryElement::eByControlPoint))
							{
								int nIdx = (lpGeometryElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect) ? lpGeometryElement->GetIndexArray().GetAt(i) : i;
								nCurrentBiNormal += lpGeometryElement->GetDirectArray().GetAt(nIdx);
							}
						}

						nCurrentBiNormal.Normalize();
						elem.baseVertexPointerToElement(lpVert, &pFloat);
						*pFloat++ = static_cast<float>(nCurrentBiNormal[0]);
						*pFloat++ = static_cast<float>(nCurrentBiNormal[1]);
						*pFloat++ = static_cast<float>(nCurrentBiNormal[2]);
					}
					break;

				case Ogre::VES_TANGENT:
					{
						float *pFloat;
						FbxVector4 nCurrentTangent(.0f, .0f, .0f);
						const int nNormalCount = lpFbxMesh->GetElementTangentCount();

						for (int nLayer = 0; nLayer < nNormalCount; ++nLayer)
						{
							FbxGeometryElementTangent* lpGeometryElement = lpFbxMesh->GetElementTangent(nLayer);
							const FbxGeometryElement::EMappingMode nMappingMode = lpGeometryElement->GetMappingMode();
							if ((nMappingMode == FbxGeometryElement::eByPolygonVertex) || (nMappingMode == FbxGeometryElement::eByControlPoint))
							{
								int nIdx = (lpGeometryElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect) ? lpGeometryElement->GetIndexArray().GetAt(i) : i;
								nCurrentTangent += lpGeometryElement->GetDirectArray().GetAt(nIdx);
							}
						}

						nCurrentTangent.Normalize();
						elem.baseVertexPointerToElement(lpVert, &pFloat);
						*pFloat++ = static_cast<float>(nCurrentTangent[0]);
						*pFloat++ = static_cast<float>(nCurrentTangent[1]);
						*pFloat++ = static_cast<float>(nCurrentTangent[2]);
					}
					break;

				case Ogre::VES_DIFFUSE:
					{
						FbxColor nCurrentVertexColor(.0f, .0f, .0f, .0f);
						const int nVertexColorCount = lpFbxMesh->GetElementVertexColorCount();
						for (int nLayer = 0; nLayer < nVertexColorCount; ++nLayer)
						{
							FbxGeometryElementVertexColor* lpGeometryElement = lpFbxMesh->GetElementVertexColor(nLayer);
							const FbxGeometryElement::EMappingMode nMappingMode = lpGeometryElement->GetMappingMode();
							if ((nMappingMode == FbxGeometryElement::eByPolygonVertex) || (nMappingMode == FbxGeometryElement::eByControlPoint))
							{
								int nIdx = (lpGeometryElement->GetReferenceMode() == FbxLayerElement::eIndexToDirect) ? lpGeometryElement->GetIndexArray().GetAt(i) : i;
								FbxColor val = lpGeometryElement->GetDirectArray().GetAt(nIdx);
								nCurrentVertexColor.mRed += val.mRed;
								nCurrentVertexColor.mGreen += val.mGreen;
								nCurrentVertexColor.mBlue += val.mBlue;
								nCurrentVertexColor.mAlpha += val.mAlpha;
							}
						}

						static Ogre::ARGB* s_lpColor;
						elem.baseVertexPointerToElement(lpVert, &s_lpColor);
						Ogre::ColourValue cv(float(nCurrentVertexColor.mRed), float(nCurrentVertexColor.mGreen), float(nCurrentVertexColor.mBlue), float(nCurrentVertexColor.mAlpha));
						Ogre::int32 val = Ogre::VertexElement::convertColourValue(cv, Ogre::VertexElement::getBestColourVertexElementType());
						*s_lpColor = Ogre::VertexElement::convertColourValue(cv, Ogre::VertexElement::getBestColourVertexElementType());
					}
					break;

				case Ogre::VES_TEXTURE_COORDINATES:
					{
						assert(nTextureLayer < lpFbxMesh->GetElementUVCount());
						float *pFloat;
						const FbxGeometryElementUV* lpElementTexturUV = lpFbxMesh->GetElementUV(nTextureLayer++);
						FbxGeometryElement::EMappingMode nMappingMode = lpElementTexturUV->GetMappingMode();

						while ((nMappingMode != FbxGeometryElement::eByControlPoint) && (nMappingMode != FbxGeometryElement::eByPolygonVertex))
						{
							lpElementTexturUV = lpFbxMesh->GetElementUV(nTextureLayer++);
							if (lpElementTexturUV == NULL)
							{
								return false;
							}
							nMappingMode = lpElementTexturUV->GetMappingMode();
						}

						int nIdx = (lpElementTexturUV->GetReferenceMode() == FbxLayerElement::eIndexToDirect) ? lpElementTexturUV->GetIndexArray().GetAt(i) : i;
						FbxVector2 nFbxUV = lpElementTexturUV->GetDirectArray().GetAt(nIdx);
						elem.baseVertexPointerToElement(lpVert, &pFloat);
						*pFloat++ = static_cast<float>(nFbxUV[0]);
						*pFloat++ = static_cast<float>(nFbxUV[1]);
					}
					break;

				default:
					break;
				}
			}

			lpVert+= vbuf->getVertexSize();

			if (lpSkeletonSkin != NULL)
			{//处理蒙皮信息
				const int nClusterCount = lpSkeletonSkin->GetClusterCount();
				for (int nClusterIdx = 0; nClusterIdx < nClusterCount; ++nClusterIdx)
				{
					const FbxCluster* lpFbxCluster = lpSkeletonSkin->GetCluster(nClusterIdx);
					const int nBoneIdx = getBoneIdx(lpFbxCluster != NULL ? lpFbxCluster->GetLink() : NULL);
					if ((nBoneIdx != -1) && (i < lpFbxCluster->GetControlPointIndicesCount()))
					{
						Ogre::VertexBoneAssignment bone;
						const int* lpControlPointIndices = lpFbxCluster->GetControlPointIndices();
						const double* lpControlPointWeights = lpFbxCluster->GetControlPointWeights();
						int nControlPointIndicesCount = lpFbxCluster->GetControlPointIndicesCount();
						bone.boneIndex = nBoneIdx;
						bone.vertexIndex = lpControlPointIndices[i] + nVertexBase;
						bone.weight = Ogre::Real(lpControlPointWeights[i]);
						m_nMeshBone.push_back(bone);
					}
				}
			}
		}

		nVertexBase += lControlPointsCount;
	}

	vbuf->unlock();

	// Set bounds
	const Ogre::AxisAlignedBox& currBox = lpMesh->getBounds();
	Ogre::Real currRadius = lpMesh->getBoundingSphereRadius();
	if (currBox.isNull())
	{
		//do not pad the bounding box
		lpMesh->_setBounds(Ogre::AxisAlignedBox(min, max), false);
		lpMesh->_setBoundingSphereRadius(Ogre::Math::Sqrt(maxSquaredRadius));
	}
	else
	{
		Ogre::AxisAlignedBox newBox(min, max);
		newBox.merge(currBox);
		//do not pad the bounding box
		lpMesh->_setBounds(newBox, false);
		lpMesh->_setBoundingSphereRadius(std::max(Ogre::Math::Sqrt(maxSquaredRadius), currRadius));
	}

	return true;
};

bool CFBXLoader::generateSubMesh(Ogre::Mesh* lpMesh)
{
	assert(lpMesh != NULL);

	if (lpMesh != NULL)
	{
		const size_t nMaterialCount = m_lpScene->GetMaterialCount();
		if (nMaterialCount > 0)
		{
			std::vector<float> nLodList;
			CMeshLodInfo* lpSubMeshInfo = new CMeshLodInfo[nMaterialCount];

			for (size_t nIdx = 0; nIdx < m_nMeshVertexInfo; ++nIdx)
			{
				bool bIsValid = true;
				for (std::vector<float>::const_iterator it = nLodList.begin(); it != nLodList.end(); ++it)
				{
					if (fabs(*it - m_stMeshVertexInfo[nIdx].m_fValue) < FLT_EPSILON)
					{
						bIsValid = false;
						break;;
					}
				}

				if (bIsValid != false)
				{
					nLodList.push_back(m_stMeshVertexInfo[nIdx].m_fValue);
				}
			}

			std::sort(nLodList.begin(), nLodList.end());

			if (nLodList.size() > 1)
			{//存在多级LOD
				Ogre::MeshLodUsage usage;
				lpMesh->_setLodInfo(nLodList.size(), false);
				for (size_t nIdx = 1; nIdx < nLodList.size(); ++nIdx)
				{
					usage.userValue = nLodList[nIdx];
					lpMesh->_setLodUsage(nIdx, usage);
				}
			}

			for (size_t nIdx = 0; nIdx < nMaterialCount; ++nIdx)
			{
				for (std::vector<float>::const_iterator it = nLodList.begin(); it != nLodList.end(); ++it)
				{
					lpSubMeshInfo[nIdx].generateLod(*it);
				}
			}
			for (size_t nIdx = 0; nIdx < m_nMeshVertexInfo; ++nIdx)
			{
				loadSubMesh(nIdx, lpSubMeshInfo);
			}

			//检查mesh的Lod是否一致
			size_t nSubMeshLods = lpSubMeshInfo->getLods();
			bool bIsValid = true;
			for (size_t nIdx = 0; nIdx < nMaterialCount; ++nIdx)
			{
				if (nSubMeshLods != lpSubMeshInfo[nIdx].getLods())
				{
					bIsValid = false;
					break;
				}
			}
			if (bIsValid != false)
			{
				for (size_t nSubMeshIdx = 0; nSubMeshIdx < nMaterialCount; ++nSubMeshIdx)
				{
					const FbxSurfaceMaterial* lpFbxSurfaceMaterial = m_lpScene->GetMaterial(nSubMeshIdx);
					FBX_ASSERT(lpFbxSurfaceMaterial != NULL);
					if (lpFbxSurfaceMaterial != NULL)
					{
						Ogre::SubMesh* lpSubMesh = lpMesh->createSubMesh(lpFbxSurfaceMaterial->GetName());
						FBX_ASSERT(lpSubMesh != NULL);
						if (lpSubMesh != NULL)
						{
							//生成模型最高效果
							const CMeshLodInfo::MeshIndex& meshIndex = *lpSubMeshInfo[nSubMeshIdx].getLodByIdx(0);
							bool use32BitIndexes = meshIndex.size() > 65530 ? true : false;

							lpSubMesh->setMaterialName(lpFbxSurfaceMaterial->GetName());
							lpSubMesh->operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
							lpSubMesh->useSharedVertices = true;
							lpSubMesh->indexData->indexCount = meshIndex.size();

							// Allocate space
							Ogre::HardwareIndexBufferSharedPtr ibuf = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
								use32BitIndexes ? Ogre::HardwareIndexBuffer::IT_32BIT : Ogre::HardwareIndexBuffer::IT_16BIT, meshIndex.size(), Ogre::HardwareBuffer::HBU_DYNAMIC, false);
							lpSubMesh->indexData->indexBuffer = ibuf;
							if (use32BitIndexes)
							{
								unsigned int* lpVal = static_cast<unsigned int*>(ibuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
								for (CMeshLodInfo::MeshIndex::const_iterator it = meshIndex.begin(); it != meshIndex.end(); ++it)
								{
									*lpVal++ = (unsigned int)*it;
								}
							}
							else
							{
								unsigned short* lpVal = static_cast<unsigned short*>(ibuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
								for (CMeshLodInfo::MeshIndex::const_iterator it = meshIndex.begin(); it != meshIndex.end(); ++it)
								{
									*lpVal++ = (unsigned short)*it;
								}
							}
							ibuf->unlock();

							//生成模型LOD数据
							lpSubMesh->mLodFaceList.resize(nSubMeshLods - 1);
							for (size_t nLodIdx = 1; nLodIdx < nSubMeshLods; ++nLodIdx)
							{
								Ogre::IndexData* indexData = new Ogre::IndexData();
								lpSubMesh->mLodFaceList[nLodIdx - 1] = indexData;

								const CMeshLodInfo::MeshIndex& meshIndex = *lpSubMeshInfo[nSubMeshIdx].getLodByIdx(nLodIdx);
								indexData->indexCount = meshIndex.size();
								bool use32BitIndexes = meshIndex.size() > 65530 ? true : false;
									// Allocate space
								Ogre::HardwareIndexBufferSharedPtr ibuf = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
									use32BitIndexes ? Ogre::HardwareIndexBuffer::IT_32BIT : Ogre::HardwareIndexBuffer::IT_16BIT, meshIndex.size(), Ogre::HardwareBuffer::HBU_DYNAMIC, false);
								if (use32BitIndexes)
								{
									unsigned int* lpVal = static_cast<unsigned int*>(ibuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
									for (CMeshLodInfo::MeshIndex::const_iterator it = meshIndex.begin(); it != meshIndex.end(); ++it)
									{
										*lpVal++ = (unsigned int)*it;
									}
								}
								else
								{
									unsigned short* lpVal = static_cast<unsigned short*>(ibuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
									for (CMeshLodInfo::MeshIndex::const_iterator it = meshIndex.begin(); it != meshIndex.end(); ++it)
									{
										*lpVal++ = (unsigned short)*it;
									}
								}

								ibuf->unlock();

								indexData->indexBuffer = ibuf;
							}

							//
						}
					}

				}

				//设置骨骼信息
				for (MeshBone::const_iterator it = m_nMeshBone.begin(); it != m_nMeshBone.end(); ++it)
				{
					lpMesh->addBoneAssignment(*it);
					lpMesh->setSkeletonName("shared.skeleton");
				}

				delete[] lpSubMeshInfo;
				return true;
			}
			else
			{
				delete[] lpSubMeshInfo;
			}
		}
	}

	return false;
};

void CFBXLoader::loadSubMesh(const size_t nMeshIdx, CMeshLodInfo* lpSubMesh)
{
	if ((nMeshIdx < eMaxFbxMesh) && (lpSubMesh != NULL))
	{
		const FbxMesh* lpFbxMesh = m_stMeshVertexInfo[nMeshIdx].m_lpMesh;
		const float fValue = m_stMeshVertexInfo[nMeshIdx].m_fValue;
		const int nVertexBase = m_stMeshVertexInfo[nMeshIdx].m_nVertexBase;
		const int nMaterialCount = lpFbxMesh->GetElementMaterialCount();
		const FbxGeometryElementMaterial* lpFbxGeometryElementMaterial = NULL;

		for (int nIdx = 0; nIdx < nMaterialCount; ++nIdx)
		{
			const FbxGeometryElementMaterial* lMaterialElement = lpFbxMesh->GetElementMaterial(nIdx);
			if (lMaterialElement->GetMappingMode() == FbxGeometryElement::eAllSame)
			{
				lpFbxGeometryElementMaterial = lMaterialElement;
				break;
			}
		}

		if (lpFbxGeometryElementMaterial != NULL)
		{
			const FbxLayerElementArrayTemplate<int>& nFbxMaterialElementArray = lpFbxGeometryElementMaterial->GetIndexArray();
			const FbxSurfaceMaterial* lpFbxSurfaceMaterial = NULL;
			for (int nIdx = 0; nIdx < nFbxMaterialElementArray.GetCount(); ++nIdx)
			{
				lpFbxSurfaceMaterial = lpFbxMesh->GetNode()->GetMaterial(nIdx);
				if (lpFbxSurfaceMaterial != NULL)
				{
					break;
				}
			}

			const int nMaterialIdx = getMaterialIdx(lpFbxSurfaceMaterial);
			if (nMaterialIdx >= 0)
			{
				CMeshLodInfo::MeshIndex& meshIndex = *lpSubMesh[nMaterialIdx].getLod(fValue);
				for (int nIdx = 0; nIdx < lpFbxMesh->GetPolygonCount(); ++nIdx)
				{
					for (int i = 0; i < 3; ++i)
					{
						const int nVertexIdx = lpFbxMesh->GetPolygonVertex(nIdx, i);
						meshIndex.push_back(nVertexIdx + nVertexBase);
					}
				}
			}
		}
		else
		{
			for (int nTriangleIndex = 0; nTriangleIndex < lpFbxMesh->GetPolygonCount(); ++nTriangleIndex)
			{
				const FbxSurfaceMaterial* lpFbxSurfaceMaterial = NULL;

				for (int nIdx = 0; nIdx < nMaterialCount; ++nIdx)
				{
					lpFbxGeometryElementMaterial = lpFbxMesh->GetElementMaterial(nIdx);
					if (lpFbxGeometryElementMaterial->GetMappingMode() == FbxGeometryElement::eByPolygon)
					{
						const FbxLayerElementArrayTemplate<int>& nFbxMaterialElementArray = lpFbxGeometryElementMaterial->GetIndexArray();
						const int nMaterialId = nFbxMaterialElementArray.GetAt(nTriangleIndex);
						lpFbxSurfaceMaterial = lpFbxMesh->GetNode()->GetMaterial(nMaterialId);
						if (lpFbxSurfaceMaterial != NULL)
						{
							break;
						}
					}
				}

				const int nMaterialIdx = getMaterialIdx(lpFbxSurfaceMaterial);
				if (nMaterialIdx >= 0)
				{
					CMeshLodInfo::MeshIndex& meshIndex = *lpSubMesh[nMaterialIdx].getLod(fValue);
					for (int i = 0; i < 3; ++i)
					{
						//meshIndex.push_back(lpFbxMesh->GetPolygonVertex(nTriangleIndex, i) + nVertexBase);
						const int nVertexIdx = lpFbxMesh->GetPolygonVertex(nTriangleIndex, i);
						meshIndex.push_back(nVertexIdx + nVertexBase);
					}
				}
			}

		}
	}
};

int CFBXLoader::getMaterialIdx(const FbxSurfaceMaterial* lpFbxSurfaceMaterial)
{
	for (int nIdx = 0; nIdx < m_lpScene->GetMaterialCount(); ++nIdx)
	{
		if (m_lpScene->GetMaterial(nIdx) == lpFbxSurfaceMaterial)
		{
			return nIdx;
		}
	}

	return -1;
};

int CFBXLoader::getBoneIdx(const FbxNode* lpFbxNode) const
{
	for (size_t nIdx = 0; nIdx < m_nMaxBoneCount; ++nIdx)
	{
		if (m_nBones[nIdx] == lpFbxNode)
		{
			return nIdx;
		}
	}

	return -1;
};
