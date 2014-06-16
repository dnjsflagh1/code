/******************************************************************************/
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "Singleton.h"

#include "IEngineMain.h"

#include "IResourceManager.h"

#include "ModelResourceConfig.h"
#include "EffectResourceConfig.h"
#include "ActionResourceConfig.h"
#include "MaterialResourceConfig.h"
#include "EntityAccessoryResourceConfig.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //游戏资源管理
    /******************************************************************************/
    class ResourceManager : public MGSingleton<ResourceManager>, public IResourceManager
    {
		friend class ModelResourceConfig;
		friend class ActionResourceConfig;
		friend class MaterialResourceConfig;
		friend class EffectResourceConfig;
        friend class EntityAccessoryResourceConfig;

    public:
        SINGLETON_DECLARE( ResourceManager )
        ResourceManager();
        virtual ~ResourceManager();

    //-----------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------

    public:

		void									    unloadAll();

        /// 加载模型声明文件, 以及动作声明文件
        void                                        loadDeclarations( const EngineInitConfig& config ) ;

        /// 加载资源组
        void                                        loadResourceGroup(  Str group, Str path, Bool isReloaded = false );

        // 卸载资源
        virtual void                                unLoadAllResource();

        virtual void                                unLoadAllResourceGroup();
        virtual void                                unLoadAllSkeletonResource();
        virtual void                                unLoadAllTextureResource();
        virtual void                                unLoadAllMeshResource();
        virtual void                                unLoadAllMaterialResource();

    protected:

        std::map<Str,Str>                           mResourceMap;

    //-----------------------------------------------------------------------------------------------------
    // model
    //-----------------------------------------------------------------------------------------------------

    public:

        /// 得到模型声明
        virtual ModelDeclaration*                   getModelDeclaration( U32 modelDeclID, Bool isLoad = true ) ;
        /// 得到模型声明数量
        virtual UInt                                getModelDeclarationCount( );
        /// 得到模型声明
        virtual ModelDeclaration*                   getModelDeclarationByIndex( UInt index, Bool isLoad = true ) ;
		/// 得到模型配件声明数量
		virtual U32								    getNumEntityAccessories( U32 accessoryID );
		/// 得到模型配件声明
		virtual const EntityAccessoryDeclaration*   getEntityAccessoryDeclaration( U32 accessoryID, U32 index, Bool isLoad = true );

    protected:

        std::map<U32, ModelDeclaration> mModelDecls;

        typedef std::vector<EntityAccessoryDeclaration> EntityAccessoryDecls;

        typedef std::map<U32, EntityAccessoryDecls> EntityAcessoryDeclMap;
        EntityAcessoryDeclMap   mEntityAccessoryDeclMap;

    //-----------------------------------------------------------------------------------------------------
    // material
    //-----------------------------------------------------------------------------------------------------

    public:

		/// 得到材质声明
		virtual MaterialDeclaration*			    getMaterialDeclaration(Str materialGroup, U32 index, Bool isLoad = true) ;
		/// 得到材质参数声明
		virtual MaterialParamDeclaration*		    getMaterialParamDeclaration( U32 materialParamID );
		//通过modelDeclID, 获得所使用的材质模版列表
		virtual void								getMaterialDeclsByModelDeclID( U32 modelDeclID, std::vector<MaterialDeclaration*>& matDecls );
        
    protected:

        /// material file which placed in each model files
        typedef std::vector<MaterialDeclaration> MaterialDecls;

        typedef std::map<Str, MaterialDecls> MaterialDeclsMap;

        MaterialDeclsMap mMaterialDeclsGroups;


    //-----------------------------------------------------------------------------------------------------
    // effect
    //-----------------------------------------------------------------------------------------------------

    public:

		/// 得到新的特效组件资源声明
		virtual EffectComponentResourceDeclaration*	getEffectComponentResourceDeclaration( U32 effectElemResID, bool isLoad = true );
		/// 顺序获得新的特效组件声明				
		virtual EffectComponentResourceDeclaration*	getEffectComponentResourceDeclarationByIndex ( UInt index, bool isLoad = true );
		/// 获得新的特效组件资源数量
		virtual U32									getEffectComponentResourceDeclarationCount();

		//////////////////////////////////////////////////////////////////////////////////////
		/// 得到普通特效资源声明
		virtual EffectResourceDeclaration*		    getEffectResourceDeclaration( U32 effectElemResID, bool isLoad = true );
		/// 顺序获得资源特效声明				
		virtual EffectResourceDeclaration*			getEffectResourceDeclarationByIndex ( UInt index, bool isLoad = true );
		/// 获得特效资源数量
		virtual U32									getEffectResourceDeclarationCount();

    protected:

        typedef std::map<U32, EffectResourceDeclaration> EffectElementResDeclsMaps;
        EffectElementResDeclsMaps mEffectElementResDecls;

    //-----------------------------------------------------------------------------------------------------
    // grass
    //-----------------------------------------------------------------------------------------------------

    public:

		/// 得到草丛特效声明
		virtual GrassEffectResourceDeclaration*	    getGrassEffectResourceDeclaration( U32 grassEffectID );

    protected:

        //后期草丛特效资源
        typedef std::map<U32, GrassEffectResourceDeclaration> GrassEffectResDeclsMap;
        GrassEffectResDeclsMap mGrassEffectResDecls;


    //-----------------------------------------------------------------------------------------------------
    // water
    //-----------------------------------------------------------------------------------------------------

    public:

		/// 得到水特效声明
		virtual WaterEffectResourceDeclaration*	    getWaterEffectResourceDeclaration( U32 waterEffectID );
		/// 得到水特效声明
		virtual	WaterEffectResourceDeclaration*		getWaterEffectResourceDeclarationByIndex( U32 index );
		/// 得到水特效声明总数
		virtual	U32									getNumWaterEffectResourceDeclaration();
		/// 重新加载水特效参数
		virtual bool								reloadWaterEffectResourceDeclaration();
		/// 修改水特效文件
		virtual void								saveWaterEffectResourceDeclaration( U32 waterEffectID);

    public:

        //后期水特效资源
        typedef std::map<U32, WaterEffectResourceDeclaration> WaterEffectResDeclsMap;
        WaterEffectResDeclsMap mWaterEffectResDecls;

    //-----------------------------------------------------------------------------------------------------
    // terrain
    //-----------------------------------------------------------------------------------------------------

    public:

        virtual Int                                 getTerrainTextureLayerDeclarationCount() ;
        virtual TerrainTextureLayerDeclaration*     getTerrainTextureLayerDeclaration( Int index);

        /// 加载地形贴图声明文件
        void                                        loadTerrainTextureLayerDeclarations( CChar* filename ) ;
        /// 得到地形贴图声明
        virtual TerrainTextureLayerDeclaration*     getTerrainTextureLayerDeclaration( CChar* name, Bool isLoad = true );
        /// 得到地形贴图数据源声明
        virtual const tinyxml2::XMLDocument*		getTerrainTextureLayerDeclXmlDoc(){return mTerrainTextureXmlDoc;};

    protected:

        /// TerrainTexture Xml文档对象.
        tinyxml2::XMLDocument*	mTerrainTextureXmlDoc;
        /// TerrainTexture 声明列表
        std::map<Str, TerrainTextureLayerDeclaration> mTerrainTextureDecls;


    //-----------------------------------------------------------------------------------------------------
    // animation
    //-----------------------------------------------------------------------------------------------------

    public:

        /// 加载骨骼动画
        SkeletonPtr                                 getSkeletonPtr(U32 parentModelDeclID, const String& name);

        /// 得到动作声明
        virtual ActionDeclaration*				    getActionDeclaration( U32 modelDeclID, Str action_name );

        /// 获得骨骼名列表
        virtual void								getBoneList(U32 modelDeclID, std::vector<Str>& boneList);
        /// 获得动作名列表
        virtual void								getActionList(U32 modelDeclID, std::vector<Str>& actionList);

        /// 卸载所有的动作特效资源
        void                                        unLoadActionDecls();
		// 新的特效组件
		typedef std::map<U32, EffectComponentResourceDeclaration> EffectComponentElementResDeclsMaps;
		EffectComponentElementResDeclsMaps mEffectComponentElementResDecls;

	protected:

		/// Action file which placed in each model files 
		typedef std::map<Str, ActionDeclaration*> ActionDecls;

        //---------------------------------------------------
		
		struct ActionDeclsInfo
		{
			/// Action declaration list
			ActionDecls decls;
		};
		/// Searching animation groups by model id
		typedef std::map<U32, ActionDeclsInfo> ActionDeclsInfos;
		ActionDeclsInfos mActionDeclInfos;

        //---------------------------------------------------

        struct SkeletonMap
        {
            std::map<Str, SkeletonPtr> skeletonMap;
        };
		/// 有效的动画名字
		std::map<U32, SkeletonMap> mValidSkeletonGroupMap;
        /// 无效的动画名字
        std::map<U32, SkeletonMap> mInvalidSkeletonGroupMap;

    
    //-----------------------------------------------------------------------------------------------------
    // 
    //-----------------------------------------------------------------------------------------------------
    



    };

}

/******************************************************************************/

#endif
