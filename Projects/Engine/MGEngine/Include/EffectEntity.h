/******************************************************************************/
#ifndef _EFFECTENTITY_H_
#define _EFFECTENTITY_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IEffectEntity.h"
#include "ILogicBinder.h"
#include "OgreEntity.h"
#include "ParticleUniverseSystemManager.h"
/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //特效实体对象
    /******************************************************************************/
    class EffectEntity : public IEffectEntity
    {
        friend class Scene;

    public:

        EffectEntity(CChar* entityName, U32 effectResID, Scene* scene,Bool isAutoDestroy,Bool isAutoStart);
        virtual ~EffectEntity();

        /// 得到类型
        virtual SceneObjectTypes        getType();
        /// 得到空间节点
        virtual MGSceneNode*            getSceneNode();
		/// 绑定到模型
		virtual Bool					bind(IEntity* entity, Bool attachToParent = false);
		/// 是否创建成功
		virtual Bool					initialised();


        /// 开始一个特效
        virtual void                    start();

		/// 设置下大小
		virtual void					setScale( Vec3 scale );

		virtual U32						getEffectResourceID() { return mEffectResID; }

    protected:
        
        /// 创建特效
        void                            createOgreEffect(U32 effectResID);
        /// 销毁特效
        void                            destroyOgreEffect();

        /// 创建PU特效
        void                            createPUEffect(U32 effectResID,Bool isAutoStart);
        /// 销毁PU特效
        void                            destroyPUEffect();

        /// 更新
        virtual Bool                    update( Flt delta );

    protected:

        ///节点对象
        MGSceneNode* mSceneNode;
        /// 所属场景对象
        Scene* mScene;
        /// Ogre的粒子对象 
        Ogre::ParticleSystem* mOgreParticleSystem;
        /// PU粒子对象
        ParticleUniverse::ParticleSystem* mPUParticleSystem;
        /// 是否自动销毁
        Bool mIsAutoDestroy;
		/// 特效资源模版号
		U32  mEffectResID;

        // 是否开始
        Bool mIsStart;
        // 累计时间
        Flt mStartDelta;

        // 特效创建数量
        static UInt EffectCreateCount;
        // 特效销毁数量
        static UInt EffectDestroyCount;
    };

}

/******************************************************************************/

#endif
