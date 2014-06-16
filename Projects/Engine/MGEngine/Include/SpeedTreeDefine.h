
/******************************************************************************/
#ifndef __SPEEDTREEDEFINE_H__
#define __SPEEDTREEDEFINE_H__
/******************************************************************************/

#include "EnginePreqs.h"
#include "Renderers/DirectX9/DirectX9Renderer.h"
#include "Core/Core.h"
#include "Core/String.h"

namespace MG
{
#define DUMMY_TREE_NAME	"已删除"
#define MAX_GRASS_PRE_CELLS 1000

/*
	enum
	{
		TREE_RENDER_STANDARD = 0,
		TREE_RENDER_DEPTH_ONLY,
		TREE_RENDER_PASS_SHADOW,
        TREE_RENDER_PASS_NUM_TYPES,
        TREE_RENDER_REFLECT,
        TREE_RENDER_REFRACT,

		TREE_RENDER_NR,
	};*/


	enum
	{
		TREE_ID = 0,
		TREE_NAME,
		TREE_PATH,
		TREE_LOD_START,
		TREE_LOD_END,
		TREE_NOTE,
	};

	enum
	{
		GRASS_ID = 0,
		GRASS_IMAGE_ID,
		GRASS_NAME,
		GRASS_TOTAL_ROW,
		GRASS_TOTAL_COL,
		GRASS_WIDTH,
		GRASS_HEIGHT,
		GRASS_WMIN,
		GRASS_WMAX,
		GRASS_HMIN,
		GRASS_HMAX,
		GRASS_RTWINDWEIGHT,
		GRASS_LTWINDWEIGHT,
		GRASS_LBWINDWEIGHT,
		GRASS_RBWINDWEIGHT,
		GRASS_NOTE,
	};


	struct StViewPort
	{
		UInt		X;
		UInt		Y;            /* Viewport Top left */
		UInt		Width;
		UInt		Height;       /* Viewport Dimensions */
		Flt			MinZ;         /* Min/max of clip Volume */
		Flt			MaxZ;
	};

	struct SpeedTreeParam
	{
		IDirect3DDevice9*	pDevice;
/*
		float				fAspectRatio;

		//camera
		float				farClipValue;

		//light
		float				fGlobalLightNr;
		bool				bEnableSpecular;
		bool				bEnableTransmission;
		bool				bEnableDetailLayer;
		bool				bEnableDetailNormalMapping;
		bool				bEnableAO;
		float				fTransmissionValue;

		//fog
		float				fFogStartDistance;
		float				fFogEndDistance;

		//wind
		bool				bWindEnabled;
		bool				bFrondRippling;*/
	};

	struct STree
	{
		U32					uID;
		Vec3				vPos;
		Vec4				vOrientation;
		Vec3				vScale;
	};

	//struct SGrassInstance 
	//{
	//	UInt uIndex;
	//	Int row;
	//	Int col;
	//};

	struct CameraParam 
	{
		//st_float32		fovY;
		//st_float32		aspectRatio;
		SpeedTree::Vec3			cameraPos;
		SpeedTree::st_float32	nearClip;
		SpeedTree::st_float32	farClip;
		SpeedTree::Mat4x4		viewMatrix;
		SpeedTree::Mat4x4		projMatrix;

		CameraParam()
			: cameraPos(0.f, 0.f, 0.f)
			, nearClip(0.f)
			, farClip(0.f)
		{
			viewMatrix.SetIdentity();
			projMatrix.SetIdentity();
		}
	};

	///////////////////////////////////////////////////////////////////////  
	//  Structure SGrassVertex

	struct SGrassVertex
	{
		// position
		SpeedTree::Vec3			m_vPosition;
		SpeedTree::st_float32	m_fCornerIndex;

		// texcoord0
		SpeedTree::st_float32	m_afTexCoords[2];
		SpeedTree::st_float32	m_afTerrainTexCoords[2];

		// texcoord1
		SpeedTree::st_float32	m_fWidth;
		SpeedTree::st_float32	m_fHeight;
		SpeedTree::st_float32	m_fWindWeight;
		SpeedTree::st_float32	m_fAmbientOcclusion;

		// texcoord2
		//SpeedTree::st_float32	m_afNormalPerturb[2];
		//SpeedTree::Vec3			m_vPerturbPos;
		SpeedTree::st_float32	m_fPerturb[4]; //x = 最后一次更新时间, y = 当前晃动角度, z = 需要晃动的角度, w = 晃动系数
	};


}
#endif