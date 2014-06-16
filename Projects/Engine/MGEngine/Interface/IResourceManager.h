/******************************************************************************/
#ifndef _IRESOURCEMANAGER_H_
#define _IRESOURCEMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//The format of memories which saves single record of model CSV table  
	/******************************************************************************/
	enum
	{
		MODEL_USEAGE_CHAR = 1,
		MODEL_USEAGE_EQUIP,
		MODEL_USEAGE_BUILDING,
		MODEL_USEAGE_OBJECT,
		MODEL_USEAGE_EFFECT,
		MODEL_USEAGE_LAKE,
		MODEL_USEAGE_GRASS,
		MODEL_USEAGE_POINT,
		MODEL_USEAGE_DOOR,
		MODEL_USEAGE_WALL,
		MODEL_USEAGE_TERRAIN_DETAIL,
	};

	struct ModelDeclaration
	{
		U32		id;
		U32		replaceId;
		U32		resPackID;
		U8		preloadType;
		U8		modelUsage;

		Flt		patherRadius;

		Str		name;
		Str		group;
		Str		path;
		Str		meshFileName;
		Str		meshHighLevelFileName;
		Str		blockAllSideMeshFileName;
		Str		blockInSideMeshFileName;
		Str		blockOutSideMeshFileName;
		Str		RoadMeshFileName;
		Str		PassageMeshFileName;
		Str		materialFileName;
		Str		skeletonFileName;
		Str		actionFileName;
		Flt		zoonX; //X轴缩放
		Flt		zoonY; //Y轴缩放
		Flt		zoonZ; //Z轴缩放
		Flt		offsetY; //模型悬空
	};


	/******************************************************************************/
	//The format of memories which saves single record of material CSV table  
	/******************************************************************************/
    
	struct MaterialDeclaration
	{
		U32		                matDeclID;

		//////////////////////////////////////////////////////////////////////////
		//culling mode
		//////////////////////////////////////////////////////////////////////////
		U8		                cullingHardWare;
		U8		                cullingSoftWare;
		
		//////////////////////////////////////////////////////////////////////////
		//blend mode
		//////////////////////////////////////////////////////////////////////////
		Bool	                isIgnoreBlendType;	
		U8		                sceneBlendType;
		U8		                sceneBlendFactorSrc;
		U8		                sceneBlendFactorDest;

		//////////////////////////////////////////////////////////////////////////
		//alpha rejection
		//////////////////////////////////////////////////////////////////////////
		U8		                alphaRejectionCmpFunc;
		U8		                alphaRejectionValue;
        
		//////////////////////////////////////////////////////////////////////////
		//material effect
		//////////////////////////////////////////////////////////////////////////
		U32						effectGrassID;
		U32		                effectWaterID;
		
		//////////////////////////////////////////////////////////////////////////
		//resource reference
		//////////////////////////////////////////////////////////////////////////
		Str		                texturePath;
		Str		                diffuseTextureName;
		Str		                normalTextureName;
		Str						aoTextureName;
		Str		                materialTemplateName;

        //////////////////////////////////////////////////////////////////////

        Bool hasGrassEffect()
        {
            return effectGrassID > 0;
        }

        Bool hasWaterEffect()
        {
            return effectWaterID > 0;
        }
	};

	/******************************************************************************/
	//The format of memories which saves single record of material param CSV table  
	/******************************************************************************/
	struct MaterialParamDeclaration
	{
		U32		matParamID;

		Color	ambient;
		Color	diffuse;

		Color	specular;
		Flt		specularShininess;
	};

	/******************************************************************************/
	//The format of memories which saves single 
	//record of effect element resource declaration CSV table  
	/******************************************************************************/
	// 新的特效组件
	struct EffectComponentResourceDeclaration
	{
		U32		ResID;

		U8		preloadType;
		U8		useage;

		U32		respackID;
		U32		replaceResID;

		Str		name;
		Str		filePath;
		Str		fileName;
	};

	struct EffectResourceDeclaration
	{
		U32		ResID;

		U8		preloadType;
		U8		useage;
		U8		loopType;

		U32		respackID;
		U32		replaceResID;
		U32		bindBoxHeightRate;

		Str		name;
		Str		filePath;
		Str		fileName;
		Str		bindBoneName;
	};

	struct WaterEffectResourceDeclaration
	{
        U32		waterEffectID;
        Str		waterEffectDesc;
		U32		waterEffectUsage;

        Vec3    waterDeepColor;
        Vec4    waterReflectColor;
        Vec4    waterReflectScalses;
        Vec3    waterSpecularColor;
        Vec4    waterSpecularScalses;
        Vec4    waterRefractScalses;
        Vec4    waterBumpTexParams;

        Str     waterSkyCubeTexName;
        U32     waterBumpTexType;
        Str     waterBumpTexName1;
        Str     waterBumpTexName2;
        Str     waterBumpTexName3;
        Vec4    waterBumpTexAnim;

        WaterEffectResourceDeclaration()
            :waterEffectID(0)
            ,waterEffectUsage(1)
            ,waterDeepColor(0, 0.3, 0.5)
            ,waterReflectColor(0.5,0.5,0.5,1)
            ,waterReflectScalses(1,1,1,1)
            ,waterSpecularColor(0.5,0.5,0.5)
            ,waterSpecularScalses(512,1,1,1)
            ,waterRefractScalses(0,1,1,1)
            ,waterBumpTexParams(1,1,0.2,1)
            ,waterBumpTexType(0)
            ,waterBumpTexAnim(60,3,1,1)
        {
        }
	};

	struct GrassEffectResourceDeclaration
	{
		U32		grassEffectID;

		Flt		grassSwingFactor;
		Vec2	grassSwingVelocity;
	};
	/******************************************************************************/
	//The format of memories which 
	//saves single record of entity accessory CSV table  
	/******************************************************************************/
	struct EntityAccessoryDeclaration
	{
		U32		accessoryID;
		U32		parentID;
		U32		resourceID;

		U8		resourceType;
		Bool	isSyncAnimation;
		Bool	isDepositLifeTime;

		Vec3	derivedPos;
		Qua		derivedQuaternion;

		Str     bindBoneName;
	};

	/******************************************************************************/
	//The format of memories for saving action table in model folder 
	/******************************************************************************/
	struct ActionDeclaration
	{
		Str		name;
		Str		resource;
		Str		resourcePath;
		
		Flt		time;
		Flt		speed;

		Bool	isLoop;
		Bool	isReverse;
		Bool	isStopLastFrame;
	};

    /******************************************************************************/
    //地形贴图声明
    /******************************************************************************/
    struct TerrainTextureLayerDeclaration
    {
        Str     name;
        Str     thumbnailsFileName;
        Str     describe;
        Flt     worldSize;

        Bool    hasDiffuseSpecular;
        Str     diffuseSpecularFileName;

        Bool    hasNormalHeight;
        Str     normalHeightFileName;

        void clear()
        {
            hasDiffuseSpecular = false;
            hasNormalHeight = false;
        }

        TerrainTextureLayerDeclaration()
        {
            clear();
        }
    };


    /******************************************************************************/
    //游戏资源管理
    /******************************************************************************/
    class IResourceManager
    {
    public:

        //-----------------------------------------------------------------------------------------------------

        virtual void                            unLoadAllResource() = 0;

        virtual void                            unLoadAllSkeletonResource() = 0;
        virtual void                            unLoadAllTextureResource() = 0;
        virtual void                            unLoadAllMeshResource() = 0;
        virtual void                            unLoadAllMaterialResource() = 0;

        //-----------------------------------------------------------------------------------------------------

        /// 得到模型声明
        virtual ModelDeclaration*               getModelDeclaration( U32 modelDeclID, Bool isLoad = true ) = 0 ;
        /// 得到模型声明数量
        virtual UInt                            getModelDeclarationCount() = 0 ;
        /// 得到模型声明
        virtual ModelDeclaration*               getModelDeclarationByIndex( UInt index, Bool isLoad = true ) = 0 ;

        //-----------------------------------------------------------------------------------------------------

		/// 获得骨骼名列表
		virtual void							getBoneList(U32 modelDeclID, std::vector<Str>& boneList) = 0;
		/// 获得动作名列表
		virtual void							getActionList(U32 modelDeclID, std::vector<Str>& actionList) = 0;

		//------------------------------------------------------------------------------------------------------

		/// 得到新的特效组件资源声明
		virtual EffectComponentResourceDeclaration*	getEffectComponentResourceDeclaration( U32 effectElemResID, bool isLoad = true ) = 0;
		/// 顺序获得新的特效组件声明				
		virtual EffectComponentResourceDeclaration*	getEffectComponentResourceDeclarationByIndex ( UInt index, bool isLoad = true ) = 0;
		/// 获得新的特效组件资源数量
		virtual U32								getEffectComponentResourceDeclarationCount() = 0;

        //-----------------------------------------------------------------------------------------------------

		/// 得到普通特效资源声明
		virtual EffectResourceDeclaration*		getEffectResourceDeclaration( U32 effectElemResID, bool isLoad = true ) = 0;
		/// 顺序获得资源特效声明				
		virtual EffectResourceDeclaration*		getEffectResourceDeclarationByIndex ( UInt index, bool isLoad = true ) = 0;
		/// 获得特效资源数量
		virtual U32								getEffectResourceDeclarationCount() = 0;

        //-----------------------------------------------------------------------------------------------------

		/// 得到水特效声明
		virtual WaterEffectResourceDeclaration*	getWaterEffectResourceDeclaration( U32 waterEffectID ) = 0;
		/// 得到水特效声明
		virtual	WaterEffectResourceDeclaration*	getWaterEffectResourceDeclarationByIndex( U32 index ) = 0;
		/// 得到水特效声明总数
		virtual	U32								getNumWaterEffectResourceDeclaration() = 0;
		/// 修改水特效
		virtual	void							saveWaterEffectResourceDeclaration( U32 waterEffectID ) = 0;
		/// 重新加载所有水特效
		virtual bool							reloadWaterEffectResourceDeclaration() = 0;

        //-----------------------------------------------------------------------------------------------------
		
		virtual void							getMaterialDeclsByModelDeclID( U32 modelDeclID, std::vector<MaterialDeclaration*>& matDecls ) = 0;
		
        //-----------------------------------------------------------------------------------------------------

        /// 得到地形贴图声明
        virtual Int                             getTerrainTextureLayerDeclarationCount() = 0 ;
        virtual TerrainTextureLayerDeclaration* getTerrainTextureLayerDeclaration( Int index) = 0 ;

        /// 得到地形贴图声明
        virtual TerrainTextureLayerDeclaration* getTerrainTextureLayerDeclaration( CChar* name, Bool isLoad = true ) = 0 ;
        
        /// 得到地形贴图数据源声明
        virtual const tinyxml2::XMLDocument*    getTerrainTextureLayerDeclXmlDoc() = 0 ;
        
        //-----------------------------------------------------------------------------------------------------

    };

}

/******************************************************************************/

#endif
