/******************************************************************************/
#ifndef _PU_EFFECTEVENT_H_
#define _PU_EFFECTEVENT_H_
/******************************************************************************/
#include "IEffectEvent.h"
#include "EnginePreqs.h"

namespace MG
{
	/***************************************************************/
	// PU��ʼ�¼�
	/***************************************************************/
	class PUStartEffectEvent : public IPUStartEffectEvent
	{
	public:
		PUStartEffectEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller);
		virtual ~PUStartEffectEvent();

	public:
		virtual SceneObjectTypes getType() { return EOT_PU_START_EVENT; };

		virtual ISceneNode* getSceneNode();
	public:
		// 
		virtual void start();

		virtual void stop();

		virtual void update( Flt delta );

		virtual Str8& getEventName();

		virtual EffectComponent* getController();

		virtual void setPUName(const Str& name) { mPUName = name; }

		virtual Flt	 getEventTimePoint();

		virtual void setEventTimePoint(Flt timePoint);
		/////////////////////////////////////////////////////////////////
		Str&	getPUName() { return mPUName; }
	private:
		// PU����
		Str8				mPUName;
		// �¼�����
		Str8				mEventName;
		// ������
		EffectComponent*	mEffectController;

		Flt					mTimePoint;
	};

	/***************************************************************/
	// PUֹͣ�¼�
	/***************************************************************/
	class PUStopEffectEvent : public IPUStopEffectEvent
	{
	public:
		PUStopEffectEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller);
		virtual ~PUStopEffectEvent();

	public:
		virtual SceneObjectTypes getType() { return EOT_PU_STOP_EVENT; };

		virtual ISceneNode* getSceneNode();

	public:
		virtual void start();

		virtual void stop();

		virtual void update( Flt delta );

		virtual Str8& getEventName();

		virtual EffectComponent* getController();

		virtual void	setPUName(const Str& name) { mPUName = name; }

		virtual Flt	 getEventTimePoint();

		virtual void setEventTimePoint(Flt timePoint);
		/////////////////////////////////////////////////////////////////
		Str&	getPUName() { return mPUName; }
	private:
		// PU����
		Str8				mPUName;
		// �¼�����
		Str8				mEventName;
		// ������
		EffectComponent*	mEffectController;

		Flt					mTimePoint;
	};

	/***************************************************************/
	// PU���¼�
	/***************************************************************/
	class PUBindEffectEvent : public IPUBindEffectEvent
	{
	public:
		PUBindEffectEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller);
		virtual ~PUBindEffectEvent();

	public:
		virtual SceneObjectTypes getType() { return EOT_PU_BIND_EVENT; };

		virtual ISceneNode* getSceneNode();

	public:
		virtual void start();

		virtual void stop();

		virtual void update( Flt delta );

		virtual Str8& getEventName();

		virtual EffectComponent* getController();

		virtual void setIsBindRootComponent(bool bindrootcomponent);

		virtual void setBindExternalEntityName(const Str8& name);

		virtual void setBindModelName(const Str8& name);

		virtual void setBindPUName(const Str8& name);

		virtual void setBindBoneName(const Str8& name);

		virtual void setPosOffset(const Vec3& pos);

		virtual void setOriOffset(const Vec4& ori);

		virtual void setPUName(const Str& name) { mPUName = name; }

		virtual Flt	 getEventTimePoint();

		virtual void setEventTimePoint(Flt timePoint);
		////////////////////////////////////////////////////////////////
		void startBind();

		void detachBind();
		
		Bool getIsBindRootComponent() { return bBindRootComponent; }
		
		Str getBindExternalEntityName();

		Str& getBindModelName() { return mBindModelName; }
		
		Str& getBindPUName() { return mBindPUName; }

		Str& getBindBoneName() { return mBindBoneName; }

		Vec3& getPosOffset() { return mPositionOffset; } 

		Vec4& getOriOffset() { return mOrientationOffset; }

		Str&  getPUName() { return mPUName; }

	private:
		// �Ƿ�ʼ
		Bool	mIsStart;
		// PU����
		Str8	mPUName;
		// �Ƿ���������Component��.(�ǵĻ�,����λ��ʲô�Ķ���ȥComponent�ľ��������)
		BOOL	bBindRootComponent;
		// ���ⲿʵ�������.
		Int		mBindExternalEntitySlot;
		// ��ģ�͵�����(��Ч�ڲ�)
		Str8	mBindModelName;
		// ��PU������(��Ч�ڲ�)
		Str8	mBindPUName;
		// �󶨹���������(��Ч�ڲ�)
		Str8	mBindBoneName;
		// λ�õ�ƫ����
		Vec3	mPositionOffset;
		// �����ƫ����
		Vec4	mOrientationOffset;

		// �¼�����
		Str8				mEventName;
		// ������
		EffectComponent*	mEffectController;

		Flt					mTimePoint;

		// ����
		EffectComponentBinderSceneNode* mSceneNodeBinder;
		EffectComponentBinderBonePos* mBonePosBinder;

		// ����
		ISceneNode*			mBinderNode;
		// ������
		ISceneNode*			mBeBinderNode;
		//
		IEntity*			mBeBinderEntity;
		// �󶨵�λ��
		Vec3				mBindPos;
		// �󶨵ĳ���
		Qua					mBindQua;
		// �Ƿ��й�����
		Bool				mHasBoneName;
	};
}

#endif