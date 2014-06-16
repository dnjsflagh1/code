/******************************************************************************/
#ifndef _EFFECTCOMPONENT_H_
#define _EFFECTCOMPONENT_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "EnginePreqs.h"
#include "IEffectComponent.h"
#include "ILogicBinder.h"
#include "OgreEntity.h"
#include "ParticleUniverseSystemManager.h"
#include "MGSceneNode.h"
#include "PUEffect.h"
#include "Entity.h"
#include "EffectComponentTimeLine.h"
/******************************************************************************/
namespace MG
{
	typedef std::map<U32, IEntity*> SlotEntityMap;
	/******************************************************************************/
	//��Чʵ�����
	/******************************************************************************/
	class EffectComponent : public IEffectComponent
	{
		friend class Scene;

	public:
		EffectComponent(CChar* name, Scene* scene);
		EffectComponent(CChar* entityName, U32 effectResID, Scene* scene, Bool isAutoDestroy,Bool isAutoStart);
		EffectComponent(CChar* entityName, CChar* fullfilename, Scene* scene, Bool isAutoDestroy,Bool isAutoStart);
		virtual ~EffectComponent();

		///// �õ�����
		virtual SceneObjectTypes			getType();
		///// �õ��ռ�ڵ�
		virtual ISceneNode*					getSceneNode();
		/// �Ƿ񴴽��ɹ�
		virtual Bool						initialised();


		/// ��ʼһ����Ч
		virtual void						start();

		/// �����´�С
		virtual void						setScale( Vec3 scale );

		virtual U32							getEffectResourceID() { return mEffectResID; }

	public:
		/// ����PU��Ч
		virtual PUEffect*					createPUEffect(CChar* templateName, Str name = "");
		/// ����PU��Ч
		virtual PUEffect*					createPUEffect(U32 effectResID, Str name = "");
		/// �������ַ���PU����
		virtual PUEffect*					getPUEffect(const Str8& puName);
		/// ����pu����map
		virtual PUEffectMap					getPUEffectMap();
		/// ����PU��Ч
		virtual void						destroyPUEffect(const Str8& puName);
		/// ��������PU��Ч
		virtual void						destroyAllPUEffect();
		/// ���PU��Component�������
		virtual Str							getEffectName(IPUEffect* effect);

		/// ����ģ��
		virtual Entity*						createModelEffect(U32 resID, Str name = "");
		/// �����ⲿģ��(�༭��ʹ��)
		virtual Entity*						createSlotModelEffect(U32 resID);
		/// �������ַ���ʵ�����
		virtual Entity*						getModelEffect(const Str8& entityName);
		/// ����ʵ������б�
		virtual EntityMap					getModelEffectMap();
		/// �������ַ��ز�λʵ�����(�༭��ʹ��)
		virtual Entity*						getSlotModelEffect(const Str8& entityName);
		/// ����ģ��
		virtual void						destroyModelEffect(const Str8& entityName);
		/// ��������ģ��
		virtual void						destroyAllModelEffect();
		/// ���ģ����Component�������
		virtual Str							getModelName(IEntity* entity);

		/// ���ð󶨲�λ��ָ��(�ͻ���ʹ��)
		virtual void						setBindSlot(U32 slotindex, IEntity* bindEntity);

		/// ���ʱ����
		virtual EffectComponentTimeLine*	getTimeLine();

		/// �����¼�
		virtual IEffectEvent*				createEffectEvent(const Str& eventname, Flt timePoint);
		/// ����¼�
		virtual IEffectEvent*				getEffectEvent(const Str& eventname);
		/// ��ȡ�¼��б�
		virtual	TimeList					getTimeEventList();
		/// �����¼�
		virtual void						destroyEffectEvent(const Str& eventname);

		virtual Scene*						getScene() { return mScene; }

		virtual IEffectXmlSerializer*		getEffectXmlSerializer();
	public:
		/// ����ʱ���¼��б�
		TimeList&							getTimeEventMap(){ return mTimeList; }

		/// ��ȡ��λʵ��(�ͻ�����ʹ��)
		IEntity*								getSlotEntity(U32 index);
	protected:

		/// ����Effect�ļ�
		void								loadEffectFile(U32 effectResID);
		
		void								loadEffectFile(CChar* fullfilename);

		/// ����
		virtual Bool						update( Flt delta );

	protected:
		///�ڵ����
		MGSceneNode*						mSceneNode;
		/// ������������
		Scene*								mScene;
		/// �Ƿ��Զ���ʼ
		Bool								mIsAutoStart;
		/// �Ƿ��Զ�����
		Bool								mIsAutoDestroy;
		/// ��Ч��Դģ���
		U32									mEffectResID;
		/// ��Ч�ļ�����·��
		Str									mEffectFullPath;

		//////////////////////////////////////////////////////////////////////////

		/// ��map��,EventҪ���������Ҷ���
		/// PU���Ӷ���
		PUEffectMap							mPUEffectList;
		/// �ڲ�ģ�Ͷ���
		EntityMap							mEntityList;
		/// ʱ���¼���
		TimeList							mTimeList;
		/// ��Ч������
		EffectXmlSerializer*				mEffectSerialzer;
		//EffectComponentSerialization*		mEffectSerialzer;
		/// ʱ����
		EffectComponentTimeLine*			mEffectComponentTimeLine;

		/// �󶨵Ĳ�λ�Ͷ���map
		SlotEntityMap						mSlotEntityMap;
	private:
		/// ʵ������
		NameGenerator						mEntityNameGenerator;
		/// ʵ������
		NameGenerator						mPUNameGenerator;
	};

}

/******************************************************************************/

#endif
