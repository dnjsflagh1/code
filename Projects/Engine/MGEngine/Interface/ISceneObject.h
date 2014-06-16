/******************************************************************************/
#ifndef _ISCENEOBJECT_H_
#define _ISCENEOBJECT_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ILogicBinder.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //游戏对象类型
    /******************************************************************************/
    enum SceneObjectTypes
    {
        SOT_NULL= 0, 

        SOT_CAMERA,
        SOT_LIGHT,

        SOT_ENTITY,
        SOT_EFFECTENTITY,
		//CN_MODIFY
		SOT_EFFECTCOMPONENT,

        SOT_ENTITY_GROUP,
        SOT_ENTITY_GROUP_UNIT,

        SOT_GROUND,
        SOT_WATER,
        SOT_CLIFF,

        SOT_TREE,
		SOT_GRASS,

		// 特效对象类型
		EOT_PU,

		EOT_TIMELINE,

		EOT_MODEL_VISIBLE_EVENT,
		EOT_MODEL_ANIMATION_EVENT,
		EOT_MODEL_BIND_EVENT,

		EOT_PU_START_EVENT,
		EOT_PU_STOP_EVENT,
		EOT_PU_BIND_EVENT,

		EOT_WEAPON_LIGHT_EVENT,
		EOT_EFFECT_FADE_EVENT,
    };

    /******************************************************************************/
    //游戏对象类型
    /******************************************************************************/
    enum SceneVisibleFlags
    {
        SOV_NULL            = 0, 

        SOV_GROUND          = BIT(0), 
        SOV_WATER           = BIT(1), 

        SOV_ENTITY          = BIT(2), 
        SOV_EFFECTENTITY    = BIT(3), 
 
        SOV_STATIC_SHADOW   = BIT(4),
        SOV_DYNAMIC_SHADOW  = BIT(5),

        SOV_REFLECT         = BIT(6),
        SOV_REFRACT         = BIT(7),
    };


    /******************************************************************************/
    //游戏场景对象接口
    /******************************************************************************/
    class ISceneObject 
    {
    public:
        ISceneObject()
            :mQueryFlags(0)
        {

        }

        ///刷新
        virtual void                    refresh(){};

        ///得到名字
        virtual const Str&              getName(){return mName;};
        ///设置名字
        virtual void                    setName( Str name ){mName=name;};

        ///得到类型
        virtual SceneObjectTypes        getType() = 0;

        /// 得到组
        virtual Str                     getGroup() {return mGroup;};
        /// 设置组
        virtual void                    setGroup(Str group) {mGroup = group;};

        /// 设置查询标志位
        virtual void                    setQueryFlags(UInt flag){mQueryFlags=flag;};
        /// 设置查询标志位
        virtual UInt                    getQueryFlags(){return mQueryFlags;};

        /// 得到自定义数据
        virtual Str                     getCustomAttr(Str k) {return mCustomAttrs[k];};
        /// 设置组自定义数据
        virtual void                    setCustomAttr(Str k, Str v) {mCustomAttrs[k] = v;};
        /// 清空自定义数据
        virtual void                    clearCustomAttr() {mCustomAttrs.clear();};
		/// 拷贝自定义数据
		virtual void				    copyCustomAttrTo(ISceneObject* sceneObj) { if (sceneObj) sceneObj->mCustomAttrs = mCustomAttrs; }
        /// 得到自定义数据
        virtual std::map<Str,Str>&      getCustomAttrList() { return mCustomAttrs;};
        
        
        /// 得到逻辑绑定
        ILogicBinder*                   getLogicBinder(){return &mILogicBinder;}; 

        /// 得到节点对象
        virtual ISceneNode*             getSceneNode() = 0;

        /// 创建或取回障碍对象
        virtual IDynamicBlockObject*    createOrRetrieveDynamicBlockObject() { return NULL ; };

		virtual IDynamicBlockObject*    getDynamicBlockObject() { return NULL ; };

        /// 创建或取回碰撞对象
        virtual ICollisionObject*       createOrRetrieveCollisionObject() { return NULL ; };

    protected:

        /// 所属逻辑绑定
        ILogicBinder        mILogicBinder;
        /// 名字
        Str                 mName;
        /// 组
        Str                 mGroup;
        // 自定义数据
        std::map<Str,Str>   mCustomAttrs;
        // 设置查询标志位
        UInt                mQueryFlags;
    };

}

/******************************************************************************/
#endif
