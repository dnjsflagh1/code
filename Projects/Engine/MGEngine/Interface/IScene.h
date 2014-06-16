/******************************************************************************/
#ifndef _ISCENE_H_
#define _ISCENE_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "IGui.h"
#include "ITerrain.h"
#include "ISceneObject.h"
#include "ISceneObjectController.h"
#include "IDecal.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //LOD ��Ϣ
    /******************************************************************************/
    class ResourceLoadListener
    {
    public:
        
		virtual void onInitResourceLoadListener(){};
		virtual void onClearResourceLoadListener(){}

        virtual void preLoadTerrainChunk( UInt index, UInt total ) {};
        virtual void postLoadTerrainChunk( UInt index, UInt total ) {};

        virtual void preloadObject( UInt index, UInt total ) {};
        virtual void postloadObject( ISceneObject* entity, UInt index, UInt total ) {};

	protected:

		Flt			 mFreshTime;

		Flt			 mTerrainTotalProgress;
		Flt			 mObjectTotalProgress;
    };

	class ResourceSaveListener
	{
	public:

		virtual void preSaveObject() {};
	};


    /******************************************************************************/
    //LOD ��Ϣ
    /******************************************************************************/
    struct LodInfo
    {
        UInt index;
        Flt distance;
    };
    
	/******************************************************************************/
	//��Ϸ�������ӿ�
	/******************************************************************************/
	class IScene
	{
	public:
        ///////////////////////////////////////////////////////////////////////////////////////

		/// ���õ�λ���� //�ο���λΪ��
		virtual void                    setUnitScale( Flt scale ) = 0;
		/// �õ���λ���� //�ο���λΪ��
		virtual Flt						getUnitScale() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

		/// �õ��������л�����
		virtual ISceneXmlSerializer*    getXmlSerializer() = 0;

        /// ������Դ���ؼ�����
        virtual void                    setResourceLoadListener(ResourceLoadListener* listener) = 0;

		/// ������Դ�洢������
		virtual void                    setResourceSaveListener(ResourceSaveListener* listener) = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

		/// �õ��������������
		virtual ISceneObjectController* getSceneObjectController(Bool isCreateController = true) = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// ɾ����������. 
        virtual void                    destroySceneObject(CChar* name, SceneObjectTypes type) = 0; 
		/// ������ж���.
		virtual void					clear() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// ����һ��LOD
        virtual void                    addLod(UInt index, Flt distance) = 0; 
        virtual void                    clearLod() = 0; 

        ///////////////////////////////////////////////////////////////////////////////////////

        /// ���������. 
        virtual ICamera*                createCamera(CChar* name) = 0; 
        /// ж�����������. 
        virtual void                    destroyAllCamera() = 0;
		/// �õ������
		virtual ICamera*                getCamera(CChar* name) = 0; 
        /// ���û�������. 
        virtual void                    setActiveCamera(CChar* name) = 0;
		/// ��û�������. 
		virtual ICamera*                getActiveCamera() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

        // �����ƹ� 
        virtual ILight*                 createLight(CChar* name) = 0; 
        /// ����Ĭ�ϵƹ� 
        //virtual ILight*                 createDefaultLight() = 0; 
        /// �õ�Ĭ�ϵƹ�
        virtual ILight*                 getDefaultLight() = 0; 
        /// �õ��ƹ� 
        virtual ILight*                 getLight(CChar* name) = 0; 
		/// ���ٵƹ�
		virtual void					destroyLight(CChar* name) = 0;
        /// ж�صƹ� 
        virtual void                    destroyAllLight() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// ����ʵ�� 
        virtual IEntity*                createEntity(CChar* name, U32 modelDeclID) = 0; 
        /// ����ʵ�� 
        virtual IEntity*                createEntity(U32 modelDeclID,CChar* prefixName=NULL) = 0; 
		/// ������λʵ��,����Ч��ʹ��
		virtual IEntity*                createSlotEntity(U32 modelDeclID,CChar* prefixName=NULL) = 0; 
        /// ����ʵ�� 
        virtual void                    destroyEntity(CChar* name) = 0; 
		/// ���ٲ�λʵ��
		virtual void                    destroySlotEntity(CChar* name) = 0;
        /// �õ�ʵ�� 
        virtual IEntity*                getEntity(CChar* name) = 0; 
		/// ˳�����Entity
		virtual IEntity*				getEntity(U32 index) = 0;
		/// ���ݲ�λ��ȡEntity
		virtual IEntity*				getEntityfromSlot(U32 slot) = 0;
		/// �õ�ָ����ʵ������
		virtual UInt					getEntityCount() = 0;
        /// �õ�ָ����ʵ������
        virtual UInt                    getEntityCount(CChar* group) = 0;
        /// �õ�ָ����ʵ��
        virtual void                    getEntityList(CChar* group, IEntity** buff, UInt count) = 0;
        /// ж��ʵ�� 
        virtual void                    destroyAllEntity() = 0;

        /// ����ʵ�帽����,�����ñ��ȡ
        virtual void                    createEntityStaticAccessorys( IEntity* entity, U32 componentID  ) = 0;
		/// ��̬����ʵ�帽����
		virtual bool					createEntityDynamicAccessorys( IEntity* entity, CChar* suffix, U32 resourceID, SceneObjectTypes resourceType, IEntityAccessory* accessoryInfo, Bool isCreateEntity = false ) = 0;
		/// ��̬����ʵ�帽����
		virtual void					destroyEntityDynamicAccessorys( IEntity* entity, CChar* name ) = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

		/// ����ʵ����
		virtual IEntityGroup*			createEntityGroup(CChar* name,U32 ModelDeclID, UInt num) = 0; 
		/// ����ʵ����
		virtual IEntityGroup*			createEntityGroup(U32 ModelDeclID, UInt num, CChar* prefix = NULL) = 0; 
		/// ����ʵ����
		virtual void                    destroyEntityGroup(CChar* name) = 0; 
		/// ж��ʵ����
		virtual void                    destroyAllEntityGroup() = 0;

        /// ����ʵ���鸽����
        virtual void                    createEntityGroupAccessorys( IEntityGroup* entity, U32 componentID  ) = 0;

		///////////////////////////////////////////////////////////////////////////////////////
		// �µ���Ч CN_MODIFY
		virtual IEffectComponent*		createEffectComponent(CChar* name, U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;

		virtual IEffectComponent*		createEffectComponent(U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;

		virtual IEffectComponent*		createEffectComponent(CChar* name, CChar* fullfilename, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;

		virtual IEffectComponent*		createEffectComponent(CChar* fullfilename, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;

		virtual IEffectComponent*		createEmptyEffectComponent(CChar* name) = 0;

		virtual IEffectComponent*		createEmptyEffectComponent() = 0;
		/// �����µ���Ч
		virtual void                    destroyEffectComponent(CChar* name) = 0; 
		/// �õ��µ���Ч
		virtual IEffectComponent*       getEffectComponent(CChar* name) = 0; 
		/// �õ��µ���Ч
		virtual IEffectComponent*       getEffectComponent(U32 index) = 0; 
		/// ж���µ���Ч
		virtual void                    destroyAllEffectComponent() = 0;
		/// �����µ���Ч 
		virtual void                    updateAllEffectComponent( Flt delta ) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		/// ����EffectComponent���PU
		virtual IPUEffect*				createPUEffect(CChar* name, CChar* effectTemplate, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;
		/// ����EffectComponent���PU
		virtual IPUEffect*				createPUEffect(CChar* effectTemplate, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;
		/// ����EffectComponent���PU
		virtual IPUEffect*				createPUEffect(U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;
		/// ����EffectComponent���PU
		virtual IPUEffect*				createPUEffect(CChar* name, U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;
		/// ����EffectComponent���PU
		virtual void					destroyPUEffect(CChar* name) = 0; 
		/// �õ�EffectComponent���PU
		virtual IPUEffect*				getPUEffect(CChar* name) = 0; 
		/// ж��EffectComponent���PU
		virtual void		            destroyAllPUEffect() = 0;
		/// ����EffectComponent���PU 
		virtual void		            updateAllPUEffect( Flt delta ) = 0;
        ///////////////////////////////////////////////////////////////////////////////////////

        /// ������Ч
        virtual IEffectEntity*          createEffectEntity(CChar* name, U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0; 
        /// ������Ч
        virtual IEffectEntity*          createEffectEntity(U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0; 
        /// ������Ч
        virtual void                    destroyEffectEntity(CChar* name) = 0; 
        /// �õ���Ч
        virtual IEffectEntity*          getEffectEntity(CChar* name) = 0; 
        /// ж����Ч
        virtual void                    destroyAllEffectEntity() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

        ///// ����������������
        //virtual ITerrainDecalSet*       createTerrainDecalSet(CChar* name, UInt num, CChar* texFileName) = 0;
        ///// ����������������
        //virtual ITerrainDecalSet*       createTerrainDecalSet(UInt num, CChar* texFileName) = 0;
        ///// ���ٵ�������
        //virtual void                    destroyTerrainDecalSet(CChar* name) = 0; 
        ///// �õ���������
        //virtual ITerrainDecalSet*       getTerrainDecalSet(CChar* name) = 0; 
        ///// ж�ص�������
        //virtual void                    destroyAllTerrainDecalSet() = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		/// �����߾�����������
		virtual IDecalSet*				createDecalSet(CChar* name, UInt num, CChar* texFileName, IDecalType type) = 0;
		/// �����߾�����������
		virtual IDecalSet*				createDecalSet(UInt num, CChar* texFileName, IDecalType type) = 0;
		/// ���ٸ߾�������
		virtual void                    destroyDecalSet(CChar* name) = 0; 
		/// �õ��߾�������
		virtual IDecalSet*				getDecalSet(CChar* name) = 0; 
		/// ж�ظ߾�������
		virtual void                    destroyAllDecalSet() = 0;

		///////////////////////////////////////////////////////////////////////////////////////

        /// ����Gui. 
        virtual IGui*                   createGui(CChar* resourceFileName, CChar* coreFileName, Str8 fontName, IPointer*& pIPointer, IFont*& pIFont) = 0; 
        /// ж��Gui. 
        virtual void                    destroyGui() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// �õ�С��ͼ������
        virtual IMiniMapManager*        getMiniMapManager() = 0;

        /// �õ���Ӱ������
        virtual IShadowManager*         getShadowManager() = 0;

        /// �õ��߿������
        virtual IWireframeManager*      getWireframeManager() = 0;

        /// �õ����ζ���. 
        virtual ITerrainManager*        getTerrainManager() = 0;

        /// �õ���ײϵͳ����
        virtual ICollisionSystem*       getCollisionSystem() = 0;

        /// �õ���Ϊ�������
        virtual IActionManager*         getActionManager() = 0;

        /// �õ�Ѱ·������
		virtual IPathFindingManager*    getPathFindingManager() = 0;

		virtual IBlockObjectSceneManager*getDynamicBlockObjectSceneManager() = 0;

        /// �õ��ϰ�������
		virtual IBlockManager*          getBlockManager() = 0;
        
        /// �õ��ϳ���������
        virtual ICompositorManager*     getCompositorManager() = 0;

        /// �õ�ֲ������
        virtual ITreeManager*			getTreeManager() = 0;

        /// �õ�������
        virtual ISceneDebuger*			getSceneDebuger() = 0;


        ///////////////////////////////////////////////////////////////////////////////////////

        /// ���û�����
        virtual void                    setAmbientLight(const Color& colour) = 0;
        /// �õ�������
        virtual Color                   getAmbientLight() = 0;
		/// ��������
		virtual void					createEffectGrid() = 0;
	};



}

/******************************************************************************/
#endif
