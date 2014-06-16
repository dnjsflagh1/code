/******************************************************************************/
#ifndef _EFFECT_FADE_EVENT_H_
#define _EFFECT_FADE_EVENT_H_
/******************************************************************************/
#include "IEffectEvent.h"
#include "EnginePreqs.h"

namespace MG
{
	/***************************************************************/
	// ��Ч�����¼�
	/***************************************************************/
	class EffectFadeEvent : public IEffectFadeEvent
	{
	public:
		EffectFadeEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller);
		virtual ~EffectFadeEvent();

	public:
		virtual SceneObjectTypes getType() { return EOT_EFFECT_FADE_EVENT; };

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

		virtual void setFadeTimePoint(Flt fadetimePoint);

		virtual void setDurationTime(U32 durationTime);

		virtual void setFadeType(EffectFadeTypes fadetype);

		virtual void setFadeValue(Flt fadeValue);

		//////////////////////////////////////////////////////////////////////////
		Str&	getPUName();

		Flt		getFadeTimePoint();

		U32		getDurationTime();

		EffectFadeTypes getFadeType();

		Flt		getFadeValue();

		Str&	getFadeTypeStr();

		EffectFadeTypes getFadeTypeFromStr(Str& fadetype);
	private:
		// �Ƿ�ʼ
		Bool				mIsStart;
		// PU����
		Str8				mPUName;
		// �¼�����
		Str8				mEventName;
		// ������
		EffectComponent*	mEffectController;
		// �¼�������ʱ���
		Flt					mTimePoint;
		// �����ʱ���
		Flt					mFadeTimePoint;
		// �����¼�
		U32					mDurationTime;
		// ��������
		EffectFadeTypes		mFadeType;
		// ����ֵ
		Flt					mFadeValue;
	};
}

#endif