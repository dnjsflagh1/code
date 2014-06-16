/******************************************************************************/
#ifndef _PU_EFFECT_H_
#define _PU_EFFECT_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IPUEffect.h"
#include "ParticleUniverseSystemManager.h"
/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//��Чʵ�����
	/******************************************************************************/
	class PUEffect : public IPUEffect
	{
		friend class Scene;

	public:

		PUEffect(CChar* PUName, CChar* effectTemplateName, Scene* scene,Bool isAutoDestroy = true, Bool isAutoStart = true);
		PUEffect(CChar* PUName, U32 effectResID, Scene* scene,Bool isAutoDestroy = true, Bool isAutoStart = true);
		virtual ~PUEffect();

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
		/// ֹͣһ����Ч
		virtual void					stop();

		/// �����´�С
		virtual void					setScale( Vec3 scale );

		virtual U32						getEffectResourceID() { return mEffectResID; }

		virtual void					setTrailLength(U32 length);

		virtual void					setTrailWidth(U32 width);

		virtual void					setTrailLiveTime(Flt time);

		Scene*							getScene() { return mScene; }

		CChar*							getEffectTemplateName() { return mEffectTemplateName; }
	protected:
		/// ����PU��Ч
		void                            createPUEffect(CChar* effectTemplateName, Bool isAutoStart);
		/// ����PU��Ч
		void                            createPUEffect(U32 effectResID, Bool isAutoStart);
		/// ����PU��Ч
		void                            destroyPUEffect();

		/// ����
		virtual Bool                    update( Flt delta );

	protected:

		///�ڵ����
		MGSceneNode* mSceneNode;
		/// ������������
		Scene* mScene;
		/// PU���Ӷ���
		ParticleUniverse::ParticleSystem* mPUParticleSystem;
		/// �Ƿ��Զ�����
		Bool mIsAutoDestroy;
		/// PUģ������
		CChar* mEffectTemplateName;
		/// ��Ч��Դģ���
		U32  mEffectResID;
		// �Ƿ�ʼ
		Bool mIsStart;
		// �ۼ�ʱ��
		Flt mStartDelta;
	};

}

/******************************************************************************/

#endif
