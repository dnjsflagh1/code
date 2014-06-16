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
    //��Чʵ�����
    /******************************************************************************/
    class EffectEntity : public IEffectEntity
    {
        friend class Scene;
    public:
        EffectEntity(CChar* entityName, CChar* effectFileName, Scene* scene,Bool isAutoDestroy);
        virtual ~EffectEntity();

        /// �õ�����
        virtual SceneObjectTypes        getType();
        /// �õ��ռ�ڵ�
        virtual ISceneNode*             getSceneNode();

        /// ��ʼһ����Ч
        virtual void                    start();

    protected:
        /// ������Ⱦ��
		void							setRenderGroup(uint8 groupid);

        /// ������Ч
        void                            createOgreEffect(CChar* effectFileName);
        /// ������Ч
        void                            destroyOgreEffect();

        /// ����PU��Ч
        void                            createPUEffect(CChar* effectFileName);
        /// ����PU��Ч
        void                            destroyPUEffect();

        /// ����
        virtual Bool                    update( Flt delta );

    protected:

        ///�ڵ����
        MGSceneNode* mSceneNode;
        /// ������������
        Scene* mScene;
        /// ģ��������
        Str mEffectFileName;
        /// Ogre�����Ӷ��� 
        Ogre::ParticleSystem* mOgreParticleSystem;
        /// PU���Ӷ���
        ParticleUniverse::ParticleSystem* mPUParticleSystem;
        /// �Ƿ��Զ�����
        Bool mIsAutoDestroy;
    };

}

/******************************************************************************/

#endif
