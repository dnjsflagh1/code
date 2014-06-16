/******************************************************************************/
#ifndef _WEAPON_LIGHT_EVENT_H_
#define _WEAPON_LIGHT_EVENT_H_
/******************************************************************************/
#include "IEffectEvent.h"
#include "EnginePreqs.h"

class EffectComponentBinderSceneNode;
namespace MG
{
	/***************************************************************/
	// �����¼�
	/***************************************************************/
	class WeaponLightEvent : public IWeaponLightEvent
	{
	public:
		WeaponLightEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller);
		virtual ~WeaponLightEvent();

	public:
		virtual SceneObjectTypes getType() { return EOT_WEAPON_LIGHT_EVENT; };

		virtual ISceneNode* getSceneNode();
	public:
		// 
		virtual void start();

		virtual void stop();

		virtual void update( Flt delta );

		virtual Str8& getEventName();

		virtual EffectComponent* getController();

		virtual Flt	 getEventTimePoint();

		virtual void setEventTimePoint(Flt timePoint);

		virtual void setPUName(const Str& name);

		virtual void setBindExternalEntityName(const Str8& name);

		virtual void setPosOffset(const Vec3& pos);

		virtual void setTrailLength(U32 length);

		virtual void setTrailWidth(U32 width);

		virtual void setTrailLiveTime(Flt time);
		//////////////////////////////////////////////////////////////////////////
		Str&	getPUName() { return mPUName; }

		U32		getTrailLength() { return mTrailLength; }

		U32		getTrailWidth() { return mTrailWidth; }

		Flt		getTrailLiveTime() { return mTrailLiveTime; }

		Vec3&	getPosOffset() { return mPositionOffset; } 

		Str		getBindExternalEntityName();

		void	startBind();

		void	detachBind();
	private:
		// �Ƿ�ʼ
		Bool	mIsStart;
		// PU����
		Str8				mPUName;
		// �¼�����
		Str8				mEventName;
		// ������
		EffectComponent*	mEffectController;
		// �¼�������ʱ���
		Flt					mTimePoint;
		// ���ⲿʵ�������.
		Int		mBindExternalEntitySlot;
		// ������λ�õ�ƫ����
		Vec3	mPositionOffset;

		// ˿������
		U32					mTrailLength;
		// ˿�����
		U32					mTrailWidth;
		// ˿��������ʱ��
		Flt					mTrailLiveTime;


		// ����
		ISceneNode*			mBinderNode;
		// ������
		ISceneNode*			mBeBinderNode;

		// ����
		EffectComponentBinderSceneNode* mSceneNodeBinder;
	};
}

#endif