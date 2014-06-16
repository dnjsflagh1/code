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
    //LOD 信息
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
    //LOD 信息
    /******************************************************************************/
    struct LodInfo
    {
        UInt index;
        Flt distance;
    };
    
	/******************************************************************************/
	//游戏场景主接口
	/******************************************************************************/
	class IScene
	{
	public:
        ///////////////////////////////////////////////////////////////////////////////////////

		/// 设置单位缩放 //参考单位为米
		virtual void                    setUnitScale( Flt scale ) = 0;
		/// 得到单位缩放 //参考单位为米
		virtual Flt						getUnitScale() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

		/// 得到场景序列化对象
		virtual ISceneXmlSerializer*    getXmlSerializer() = 0;

        /// 设置资源加载监听器
        virtual void                    setResourceLoadListener(ResourceLoadListener* listener) = 0;

		/// 设置资源存储监听器
		virtual void                    setResourceSaveListener(ResourceSaveListener* listener) = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

		/// 得到场景对象控制器
		virtual ISceneObjectController* getSceneObjectController(Bool isCreateController = true) = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// 删除场景对象. 
        virtual void                    destroySceneObject(CChar* name, SceneObjectTypes type) = 0; 
		/// 清空所有对象.
		virtual void					clear() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// 增加一个LOD
        virtual void                    addLod(UInt index, Flt distance) = 0; 
        virtual void                    clearLod() = 0; 

        ///////////////////////////////////////////////////////////////////////////////////////

        /// 创建摄像机. 
        virtual ICamera*                createCamera(CChar* name) = 0; 
        /// 卸载所有摄像机. 
        virtual void                    destroyAllCamera() = 0;
		/// 得到摄像机
		virtual ICamera*                getCamera(CChar* name) = 0; 
        /// 设置活动的摄像机. 
        virtual void                    setActiveCamera(CChar* name) = 0;
		/// 获得活动的摄像机. 
		virtual ICamera*                getActiveCamera() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

        // 创建灯光 
        virtual ILight*                 createLight(CChar* name) = 0; 
        /// 创建默认灯光 
        //virtual ILight*                 createDefaultLight() = 0; 
        /// 得到默认灯光
        virtual ILight*                 getDefaultLight() = 0; 
        /// 得到灯光 
        virtual ILight*                 getLight(CChar* name) = 0; 
		/// 销毁灯光
		virtual void					destroyLight(CChar* name) = 0;
        /// 卸载灯光 
        virtual void                    destroyAllLight() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// 创建实体 
        virtual IEntity*                createEntity(CChar* name, U32 modelDeclID) = 0; 
        /// 创建实体 
        virtual IEntity*                createEntity(U32 modelDeclID,CChar* prefixName=NULL) = 0; 
		/// 创建槽位实体,供特效绑定使用
		virtual IEntity*                createSlotEntity(U32 modelDeclID,CChar* prefixName=NULL) = 0; 
        /// 销毁实体 
        virtual void                    destroyEntity(CChar* name) = 0; 
		/// 销毁槽位实体
		virtual void                    destroySlotEntity(CChar* name) = 0;
        /// 得到实体 
        virtual IEntity*                getEntity(CChar* name) = 0; 
		/// 顺序访问Entity
		virtual IEntity*				getEntity(U32 index) = 0;
		/// 根据槽位获取Entity
		virtual IEntity*				getEntityfromSlot(U32 slot) = 0;
		/// 得到指定组实体数量
		virtual UInt					getEntityCount() = 0;
        /// 得到指定组实体数量
        virtual UInt                    getEntityCount(CChar* group) = 0;
        /// 得到指定组实体
        virtual void                    getEntityList(CChar* group, IEntity** buff, UInt count) = 0;
        /// 卸载实体 
        virtual void                    destroyAllEntity() = 0;

        /// 创建实体附属物,从配置表读取
        virtual void                    createEntityStaticAccessorys( IEntity* entity, U32 componentID  ) = 0;
		/// 动态创建实体附属物
		virtual bool					createEntityDynamicAccessorys( IEntity* entity, CChar* suffix, U32 resourceID, SceneObjectTypes resourceType, IEntityAccessory* accessoryInfo, Bool isCreateEntity = false ) = 0;
		/// 动态销毁实体附属物
		virtual void					destroyEntityDynamicAccessorys( IEntity* entity, CChar* name ) = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

		/// 创建实体组
		virtual IEntityGroup*			createEntityGroup(CChar* name,U32 ModelDeclID, UInt num) = 0; 
		/// 创建实体组
		virtual IEntityGroup*			createEntityGroup(U32 ModelDeclID, UInt num, CChar* prefix = NULL) = 0; 
		/// 销毁实体组
		virtual void                    destroyEntityGroup(CChar* name) = 0; 
		/// 卸载实体组
		virtual void                    destroyAllEntityGroup() = 0;

        /// 创建实体组附属物
        virtual void                    createEntityGroupAccessorys( IEntityGroup* entity, U32 componentID  ) = 0;

		///////////////////////////////////////////////////////////////////////////////////////
		// 新的特效 CN_MODIFY
		virtual IEffectComponent*		createEffectComponent(CChar* name, U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;

		virtual IEffectComponent*		createEffectComponent(U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;

		virtual IEffectComponent*		createEffectComponent(CChar* name, CChar* fullfilename, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;

		virtual IEffectComponent*		createEffectComponent(CChar* fullfilename, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;

		virtual IEffectComponent*		createEmptyEffectComponent(CChar* name) = 0;

		virtual IEffectComponent*		createEmptyEffectComponent() = 0;
		/// 销毁新的特效
		virtual void                    destroyEffectComponent(CChar* name) = 0; 
		/// 得到新的特效
		virtual IEffectComponent*       getEffectComponent(CChar* name) = 0; 
		/// 得到新的特效
		virtual IEffectComponent*       getEffectComponent(U32 index) = 0; 
		/// 卸载新的特效
		virtual void                    destroyAllEffectComponent() = 0;
		/// 更新新的特效 
		virtual void                    updateAllEffectComponent( Flt delta ) = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		/// 创建EffectComponent里的PU
		virtual IPUEffect*				createPUEffect(CChar* name, CChar* effectTemplate, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;
		/// 创建EffectComponent里的PU
		virtual IPUEffect*				createPUEffect(CChar* effectTemplate, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;
		/// 创建EffectComponent里的PU
		virtual IPUEffect*				createPUEffect(U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;
		/// 创建EffectComponent里的PU
		virtual IPUEffect*				createPUEffect(CChar* name, U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0;
		/// 销毁EffectComponent里的PU
		virtual void					destroyPUEffect(CChar* name) = 0; 
		/// 得到EffectComponent里的PU
		virtual IPUEffect*				getPUEffect(CChar* name) = 0; 
		/// 卸载EffectComponent里的PU
		virtual void		            destroyAllPUEffect() = 0;
		/// 更新EffectComponent里的PU 
		virtual void		            updateAllPUEffect( Flt delta ) = 0;
        ///////////////////////////////////////////////////////////////////////////////////////

        /// 创建特效
        virtual IEffectEntity*          createEffectEntity(CChar* name, U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0; 
        /// 创建特效
        virtual IEffectEntity*          createEffectEntity(U32 effectResID, Bool isAutoDestroy = true, Bool isAutoStart = true) = 0; 
        /// 销毁特效
        virtual void                    destroyEffectEntity(CChar* name) = 0; 
        /// 得到特效
        virtual IEffectEntity*          getEffectEntity(CChar* name) = 0; 
        /// 卸载特效
        virtual void                    destroyAllEffectEntity() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

        ///// 创建地形贴花集合
        //virtual ITerrainDecalSet*       createTerrainDecalSet(CChar* name, UInt num, CChar* texFileName) = 0;
        ///// 创建地形贴花集合
        //virtual ITerrainDecalSet*       createTerrainDecalSet(UInt num, CChar* texFileName) = 0;
        ///// 销毁地形贴花
        //virtual void                    destroyTerrainDecalSet(CChar* name) = 0; 
        ///// 得到地形贴花
        //virtual ITerrainDecalSet*       getTerrainDecalSet(CChar* name) = 0; 
        ///// 卸载地形贴花
        //virtual void                    destroyAllTerrainDecalSet() = 0;

		///////////////////////////////////////////////////////////////////////////////////////

		/// 创建高精度贴花集合
		virtual IDecalSet*				createDecalSet(CChar* name, UInt num, CChar* texFileName, IDecalType type) = 0;
		/// 创建高精度贴花集合
		virtual IDecalSet*				createDecalSet(UInt num, CChar* texFileName, IDecalType type) = 0;
		/// 销毁高精度贴花
		virtual void                    destroyDecalSet(CChar* name) = 0; 
		/// 得到高精度贴花
		virtual IDecalSet*				getDecalSet(CChar* name) = 0; 
		/// 卸载高精度贴花
		virtual void                    destroyAllDecalSet() = 0;

		///////////////////////////////////////////////////////////////////////////////////////

        /// 创建Gui. 
        virtual IGui*                   createGui(CChar* resourceFileName, CChar* coreFileName, Str8 fontName, IPointer*& pIPointer, IFont*& pIFont) = 0; 
        /// 卸载Gui. 
        virtual void                    destroyGui() = 0;

        ///////////////////////////////////////////////////////////////////////////////////////

        /// 得到小地图管理器
        virtual IMiniMapManager*        getMiniMapManager() = 0;

        /// 得到阴影管理器
        virtual IShadowManager*         getShadowManager() = 0;

        /// 得到线框管理器
        virtual IWireframeManager*      getWireframeManager() = 0;

        /// 得到地形对象. 
        virtual ITerrainManager*        getTerrainManager() = 0;

        /// 得到碰撞系统对象
        virtual ICollisionSystem*       getCollisionSystem() = 0;

        /// 得到行为管理对象
        virtual IActionManager*         getActionManager() = 0;

        /// 得到寻路管理器
		virtual IPathFindingManager*    getPathFindingManager() = 0;

		virtual IBlockObjectSceneManager*getDynamicBlockObjectSceneManager() = 0;

        /// 得到障碍管理器
		virtual IBlockManager*          getBlockManager() = 0;
        
        /// 得到合成器管理者
        virtual ICompositorManager*     getCompositorManager() = 0;

        /// 得到植被管理
        virtual ITreeManager*			getTreeManager() = 0;

        /// 得到调试器
        virtual ISceneDebuger*			getSceneDebuger() = 0;


        ///////////////////////////////////////////////////////////////////////////////////////

        /// 设置环境光
        virtual void                    setAmbientLight(const Color& colour) = 0;
        /// 得到环境光
        virtual Color                   getAmbientLight() = 0;
		/// 创建网格
		virtual void					createEffectGrid() = 0;
	};



}

/******************************************************************************/
#endif
