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

        EffectEntity(CChar* entityName, U32 effectResID, Scene* scene,Bool isAutoDestroy,Bool isAutoStart);
        virtual ~EffectEntity();

        /// �õ�����
        virtual SceneObjectTypes        getType();
        /// �õ��ռ�ڵ�
        virtual MGSceneNode*            getSceneNode();
		/// �󶨵�ģ��
		virtual Bool					bind(IEntity* entity, Bool attachToParent = false);
		/// �Ƿ񴴽��ɹ�
		virtual Bool					initialised();


        /// ��ʼһ����Ч
        virtual void                    start();

		/// �����´�С
		virtual void					setScale( Vec3 scale );

		virtual U32						getEffectResourceID() { return mEffectResID; }

    protected:
        
        /// ������Ч
        void                            createOgreEffect(U32 effectResID);
        /// ������Ч
        void                            destroyOgreEffect();

        /// ����PU��Ч
        void                            createPUEffect(U32 effectResID,Bool isAutoStart);
        /// ����PU��Ч
        void                            destroyPUEffect();

        /// ����
        virtual Bool                    update( Flt delta );

    protected:

        ///�ڵ����
        MGSceneNode* mSceneNode;
        /// ������������
        Scene* mScene;
        /// Ogre�����Ӷ��� 
        Ogre::ParticleSystem* mOgreParticleSystem;
        /// PU���Ӷ���
        ParticleUniverse::ParticleSystem* mPUParticleSystem;
        /// �Ƿ��Զ�����
        Bool mIsAutoDestroy;
		/// ��Ч��Դģ���
		U32  mEffectResID;

        // �Ƿ�ʼ
        Bool mIsStart;
        // �ۼ�ʱ��
        Flt mStartDelta;

        // ��Ч��������
        static UInt EffectCreateCount;
        // ��Ч��������
        static UInt EffectDestroyCount;
    };

}

/******************************************************************************/

#endif
