
#pragma once

#ifndef __FBXLOADER_HPP__
#define __FBXLOADER_HPP__

#include <fbxsdk.h>
#include <Ogre.h>
#include <vector>

class CFBXLoader
{
private:
	enum {
		eMaxSemantic = 32,
		eMaxFbxMesh = 512,
		eMaxFbxBone = 256,
		eMaxFbxMaterial = 64,
	};

	typedef std::vector<Ogre::VertexBoneAssignment> MeshBone;

	typedef struct __STMeshVertexInfo__
	{
		const char* m_lpszMeshName;
		float m_fValue;
		bool m_bProcessed;
		FbxMesh* m_lpMesh;
		size_t m_nVertexBase;
	} STMeshVertexInfo, *LPSTMeshVertexInfo;

	//Mesh生成LOD信息
	class CMeshLodInfo
	{
	public:
		typedef std::vector<size_t> MeshIndex;
		typedef struct __STMeshLodInfo__
		{
			float m_fValue;
			MeshIndex m_nMeshIndex;
		} STMeshLodInfo, *LPSTMeshLodInfo;
		typedef std::vector<STMeshLodInfo> MeshLodInfo;

	private:
		CMeshLodInfo(const CMeshLodInfo&);
		CMeshLodInfo& operator= (const CMeshLodInfo&);
	public:
		CMeshLodInfo(void) {};
		~CMeshLodInfo(void) { m_nMeshLodInfo.clear(); };

		//Lod信息管理
		inline size_t getLods(void) const
		{
			return m_nMeshLodInfo.size();
		}
		inline void generateLod(const float fValue)
		{
			//生成新Lod信息
			STMeshLodInfo stMeshLodInfo;
			stMeshLodInfo.m_fValue = fValue;
			m_nMeshLodInfo.push_back(stMeshLodInfo);
		}
		inline MeshIndex* getLod(const float fValue)
		{
			for (MeshLodInfo::const_iterator it = m_nMeshLodInfo.begin(); it != m_nMeshLodInfo.end(); ++it)
			{
				const STMeshLodInfo& stMeshLodInfo = *it;
				if (fabs((fValue - stMeshLodInfo.m_fValue)) < FLT_EPSILON)
				{
					return (MeshIndex*)&stMeshLodInfo.m_nMeshIndex;
				}
			}

			assert(false);
			return NULL;
		}
		inline MeshIndex* getLodByIdx(const size_t nIdx) const
		{
			if (m_nMeshLodInfo.size() > nIdx)
			{
				return (MeshIndex*)&m_nMeshLodInfo[nIdx].m_nMeshIndex;
			}

			assert(false);
			return NULL;
		}

	private:
		MeshLodInfo m_nMeshLodInfo;
	};

	//FBX模型信息
	class CFbxMeshInfo
	{
	public:
		CFbxMeshInfo(void)
		{
			::memset(m_nVertexElementSemanticInfo, 0, sizeof(m_nVertexElementSemanticInfo));
		};
		~CFbxMeshInfo(void) {};

		size_t getVertexElementSemanticInfo(const size_t nSemanticIdx) const
		{
			return nSemanticIdx < eMaxSemantic ? m_nVertexElementSemanticInfo[nSemanticIdx] : 0;
		}

		bool isValidSemanticInfo(const size_t nSemanticIdx) const
		{
			return nSemanticIdx < eMaxSemantic ? m_nVertexElementSemanticInfo[nSemanticIdx] != false : false;
		}
		void setSemanticInfo(const size_t nSemanticIdx, size_t nSemanticInfo = 1)
		{
			if (nSemanticIdx < eMaxSemantic)
			{
				m_nVertexElementSemanticInfo[nSemanticIdx] = nSemanticInfo;
			}
		}

	private:
		size_t m_nVertexElementSemanticInfo[eMaxSemantic];
	};

public:
	CFBXLoader(void);
	~CFBXLoader(void);

	bool convertFbxToMesh(const char* lpszFile, Ogre::Mesh* lpMesh);

	bool loadMeshFromFile(const char* lpszFile);

	bool getMeshInfo(void);

private:
	void convertMesh(void);

	//读取顶点信息
	bool readGeometry(Ogre::Mesh* lpMesh);

	//根据材质生成submesh
	bool generateSubMesh(Ogre::Mesh* lpMesh);

	void loadSubMesh(const size_t nMeshIdx, CMeshLodInfo* lpSubMesh);
	int getMaterialIdx(const FbxSurfaceMaterial* lpFbxSurfaceMaterial);

	//获取场景内骨骼索引
	int getBoneIdx(const FbxNode* lpFbxNode) const;
private:
	FbxManager* m_lpSdkManager;
	FbxScene* m_lpScene;
	CFbxMeshInfo m_nFbxMeshInfo;

	STMeshVertexInfo m_stMeshVertexInfo[eMaxFbxMesh];
	size_t m_nMeshVertexInfo;

	const FbxObject* m_nBones[eMaxFbxBone];
	size_t m_nMaxBoneCount;

	MeshBone m_nMeshBone;

	size_t m_nControlPointsCount;
};

#endif
