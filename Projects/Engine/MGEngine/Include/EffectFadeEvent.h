/******************************************************************************/
#ifndef _EFFECT_FADE_EVENT_H_
#define _EFFECT_FADE_EVENT_H_
/******************************************************************************/
#include "IEffectEvent.h"
#include "EnginePreqs.h"

namespace MG
{
	/***************************************************************/
	// 特效渐变事件
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
		// 是否开始
		Bool				mIsStart;
		// PU名字
		Str8				mPUName;
		// 事件名字
		Str8				mEventName;
		// 控制者
		EffectComponent*	mEffectController;
		// 事件触发的时间点
		Flt					mTimePoint;
		// 渐变的时间点
		Flt					mFadeTimePoint;
		// 持续事件
		U32					mDurationTime;
		// 渐变类型
		EffectFadeTypes		mFadeType;
		// 渐变值
		Flt					mFadeValue;
	};
}

#endif