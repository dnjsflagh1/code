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
    //��Ϸ��������
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

		// ��Ч��������
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
    //��Ϸ��������
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
    //��Ϸ��������ӿ�
    /******************************************************************************/
    class ISceneObject 
    {
    public:
        ISceneObject()
            :mQueryFlags(0)
        {

        }

        ///ˢ��
        virtual void                    refresh(){};

        ///�õ�����
        virtual const Str&              getName(){return mName;};
        ///��������
        virtual void                    setName( Str name ){mName=name;};

        ///�õ�����
        virtual SceneObjectTypes        getType() = 0;

        /// �õ���
        virtual Str                     getGroup() {return mGroup;};
        /// ������
        virtual void                    setGroup(Str group) {mGroup = group;};

        /// ���ò�ѯ��־λ
        virtual void                    setQueryFlags(UInt flag){mQueryFlags=flag;};
        /// ���ò�ѯ��־λ
        virtual UInt                    getQueryFlags(){return mQueryFlags;};

        /// �õ��Զ�������
        virtual Str                     getCustomAttr(Str k) {return mCustomAttrs[k];};
        /// �������Զ�������
        virtual void                    setCustomAttr(Str k, Str v) {mCustomAttrs[k] = v;};
        /// ����Զ�������
        virtual void                    clearCustomAttr() {mCustomAttrs.clear();};
		/// �����Զ�������
		virtual void				    copyCustomAttrTo(ISceneObject* sceneObj) { if (sceneObj) sceneObj->mCustomAttrs = mCustomAttrs; }
        /// �õ��Զ�������
        virtual std::map<Str,Str>&      getCustomAttrList() { return mCustomAttrs;};
        
        
        /// �õ��߼���
        ILogicBinder*                   getLogicBinder(){return &mILogicBinder;}; 

        /// �õ��ڵ����
        virtual ISceneNode*             getSceneNode() = 0;

        /// ������ȡ���ϰ�����
        virtual IDynamicBlockObject*    createOrRetrieveDynamicBlockObject() { return NULL ; };

		virtual IDynamicBlockObject*    getDynamicBlockObject() { return NULL ; };

        /// ������ȡ����ײ����
        virtual ICollisionObject*       createOrRetrieveCollisionObject() { return NULL ; };

    protected:

        /// �����߼���
        ILogicBinder        mILogicBinder;
        /// ����
        Str                 mName;
        /// ��
        Str                 mGroup;
        // �Զ�������
        std::map<Str,Str>   mCustomAttrs;
        // ���ò�ѯ��־λ
        UInt                mQueryFlags;
    };

}

/******************************************************************************/
#endif
