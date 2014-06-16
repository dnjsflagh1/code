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
        EffectEntity(CChar* entityName, CChar* effectFileName, Scene* scene,Bool isAutoDestroy);
        virtual ~EffectEntity();

        /// 得到类型
        virtual SceneObjectTypes        getType();
        /// 得到空间节点
        virtual ISceneNode*             getSceneNode();

        /// 开始一个特效
        virtual void                    start();

    protected:
        /// 设置渲染组
		void							setRenderGroup(uint8 groupid);

        /// 创建特效
        void                            createOgreEffect(CChar* effectFileName);
        /// 销毁特效
        void                            destroyOgreEffect();

        /// 创建PU特效
        void                            createPUEffect(CChar* effectFileName);
        /// 销毁PU特效
        void                            destroyPUEffect();

        /// 更新
        virtual Bool                    update( Flt delta );

    protected:

        ///节点对象
        MGSceneNode* mSceneNode;
        /// 所属场景对象
        Scene* mScene;
        /// 模型描述名
        Str mEffectFileName;
        /// Ogre的粒子对象 
        Ogre::ParticleSystem* mOgreParticleSystem;
        /// PU粒子对象
        ParticleUniverse::ParticleSystem* mPUParticleSystem;
        /// 是否自动销毁
        Bool mIsAutoDestroy;
    };

}

/******************************************************************************/

#endif
