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
    //��Ϸ��Դ����
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

        /// ����ģ�������ļ�, �Լ����������ļ�
        void                                        loadDeclarations( const EngineInitConfig& config ) ;

        /// ������Դ��
        void                                        loadResourceGroup(  Str group, Str path, Bool isReloaded = false );

        // ж����Դ
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

        /// �õ�ģ������
        virtual ModelDeclaration*                   getModelDeclaration( U32 modelDeclID, Bool isLoad = true ) ;
        /// �õ�ģ����������
        virtual UInt                                getModelDeclarationCount( );
        /// �õ�ģ������
        virtual ModelDeclaration*                   getModelDeclarationByIndex( UInt index, Bool isLoad = true ) ;
		/// �õ�ģ�������������
		virtual U32								    getNumEntityAccessories( U32 accessoryID );
		/// �õ�ģ���������
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

		/// �õ���������
		virtual MaterialDeclaration*			    getMaterialDeclaration(Str materialGroup, U32 index, Bool isLoad = true) ;
		/// �õ����ʲ�������
		virtual MaterialParamDeclaration*		    getMaterialParamDeclaration( U32 materialParamID );
		//ͨ��modelDeclID, �����ʹ�õĲ���ģ���б�
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

		/// �õ��µ���Ч�����Դ����
		virtual EffectComponentResourceDeclaration*	getEffectComponentResourceDeclaration( U32 effectElemResID, bool isLoad = true );
		/// ˳�����µ���Ч�������				
		virtual EffectComponentResourceDeclaration*	getEffectComponentResourceDeclarationByIndex ( UInt index, bool isLoad = true );
		/// ����µ���Ч�����Դ����
		virtual U32									getEffectComponentResourceDeclarationCount();

		//////////////////////////////////////////////////////////////////////////////////////
		/// �õ���ͨ��Ч��Դ����
		virtual EffectResourceDeclaration*		    getEffectResourceDeclaration( U32 effectElemResID, bool isLoad = true );
		/// ˳������Դ��Ч����				
		virtual EffectResourceDeclaration*			getEffectResourceDeclarationByIndex ( UInt index, bool isLoad = true );
		/// �����Ч��Դ����
		virtual U32									getEffectResourceDeclarationCount();

    protected:

        typedef std::map<U32, EffectResourceDeclaration> EffectElementResDeclsMaps;
        EffectElementResDeclsMaps mEffectElementResDecls;

    //-----------------------------------------------------------------------------------------------------
    // grass
    //-----------------------------------------------------------------------------------------------------

    public:

		/// �õ��ݴ���Ч����
		virtual GrassEffectResourceDeclaration*	    getGrassEffectResourceDeclaration( U32 grassEffectID );

    protected:

        //���ڲݴ���Ч��Դ
        typedef std::map<U32, GrassEffectResourceDeclaration> GrassEffectResDeclsMap;
        GrassEffectResDeclsMap mGrassEffectResDecls;


    //-----------------------------------------------------------------------------------------------------
    // water
    //-----------------------------------------------------------------------------------------------------

    public:

		/// �õ�ˮ��Ч����
		virtual WaterEffectResourceDeclaration*	    getWaterEffectResourceDeclaration( U32 waterEffectID );
		/// �õ�ˮ��Ч����
		virtual	WaterEffectResourceDeclaration*		getWaterEffectResourceDeclarationByIndex( U32 index );
		/// �õ�ˮ��Ч��������
		virtual	U32									getNumWaterEffectResourceDeclaration();
		/// ���¼���ˮ��Ч����
		virtual bool								reloadWaterEffectResourceDeclaration();
		/// �޸�ˮ��Ч�ļ�
		virtual void								saveWaterEffectResourceDeclaration( U32 waterEffectID);

    public:

        //����ˮ��Ч��Դ
        typedef std::map<U32, WaterEffectResourceDeclaration> WaterEffectResDeclsMap;
        WaterEffectResDeclsMap mWaterEffectResDecls;

    //-----------------------------------------------------------------------------------------------------
    // terrain
    //-----------------------------------------------------------------------------------------------------

    public:

        virtual Int                                 getTerrainTextureLayerDeclarationCount() ;
        virtual TerrainTextureLayerDeclaration*     getTerrainTextureLayerDeclaration( Int index);

        /// ���ص�����ͼ�����ļ�
        void                                        loadTerrainTextureLayerDeclarations( CChar* filename ) ;
        /// �õ�������ͼ����
        virtual TerrainTextureLayerDeclaration*     getTerrainTextureLayerDeclaration( CChar* name, Bool isLoad = true );
        /// �õ�������ͼ����Դ����
        virtual const tinyxml2::XMLDocument*		getTerrainTextureLayerDeclXmlDoc(){return mTerrainTextureXmlDoc;};

    protected:

        /// TerrainTexture Xml�ĵ�����.
        tinyxml2::XMLDocument*	mTerrainTextureXmlDoc;
        /// TerrainTexture �����б�
        std::map<Str, TerrainTextureLayerDeclaration> mTerrainTextureDecls;


    //-----------------------------------------------------------------------------------------------------
    // animation
    //-----------------------------------------------------------------------------------------------------

    public:

        /// ���ع�������
        SkeletonPtr                                 getSkeletonPtr(U32 parentModelDeclID, const String& name);

        /// �õ���������
        virtual ActionDeclaration*				    getActionDeclaration( U32 modelDeclID, Str action_name );

        /// ��ù������б�
        virtual void								getBoneList(U32 modelDeclID, std::vector<Str>& boneList);
        /// ��ö������б�
        virtual void								getActionList(U32 modelDeclID, std::vector<Str>& actionList);

        /// ж�����еĶ�����Ч��Դ
        void                                        unLoadActionDecls();
		// �µ���Ч���
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
		/// ��Ч�Ķ�������
		std::map<U32, SkeletonMap> mValidSkeletonGroupMap;
        /// ��Ч�Ķ�������
        std::map<U32, SkeletonMap> mInvalidSkeletonGroupMap;

    
    //-----------------------------------------------------------------------------------------------------
    // 
    //-----------------------------------------------------------------------------------------------------
    



    };

}

/******************************************************************************/

#endif
