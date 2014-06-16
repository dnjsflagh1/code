/******************************************************************************/
#ifndef _IEFFECTEVENT_H_
#define _IEFFECTEVENT_H_
/******************************************************************************/
#include "MGEngineInterfacePreqs.h"
#include "ISceneObject.h"

namespace MG
{
	class EffectComponent;
	class IEffectEvent : public ISceneObject
	{
	public:
		virtual Str8& getEventName() = 0;
		virtual EffectComponent* getController() = 0;

		virtual void start()  = 0;
		virtual void stop()	  = 0;
		virtual void update( Flt delta ) = 0;

		virtual Flt  getEventTimePoint() = 0;

		virtual void setEventTimePoint(Flt timePoint) = 0;
	};

	enum EffectFadeTypes
	{
		EFT_NULL = 0,

		EFT_SCALE,

		EFT_VELOCITY,
	};


	class IModelVisibleEffectEvent: public IEffectEvent
	{
	public:
		virtual void setVisible(bool visible) = 0;

		virtual void setModelName(const Str& name) = 0;
	};

	class IModelAnimationEffectEvent: public IEffectEvent
	{
	public:
		virtual void setAnimationName(const Str8& animname) = 0;

		virtual void setModelName(const Str& name) = 0;

		virtual void setIsLoop(Bool loop) = 0;
	};

	class IModelBindEffectEvent: public IEffectEvent
	{
	public:
		virtual void setIsBindRootComponent(bool bindrootcomponent) = 0;

		virtual void setBindExternalEntityName(const Str8& name) = 0;

		virtual void setBindModelName(const Str8& name) = 0;

		virtual void setBindPUName(const Str8& name) = 0;

		virtual void setBindBoneName(const Str8& name) = 0;

		virtual void setPosOffset(const Vec3& pos) = 0;

		virtual void setOriOffset(const Vec4& ori) = 0;

		virtual void setModelName(const Str8& name) = 0;
	};

	class IPUStartEffectEvent: public IEffectEvent
	{
	public:
		virtual void setPUName(const Str& name) = 0;
	};

	class IPUStopEffectEvent: public IEffectEvent
	{
	public:
		virtual void setPUName(const Str& name) = 0;
	};

	class IPUBindEffectEvent: public IEffectEvent
	{
	public:
		virtual void setIsBindRootComponent(bool bindrootcomponent) = 0;

		virtual void setBindExternalEntityName(const Str8& name) = 0;

		virtual void setBindModelName(const Str8& name) = 0;

		virtual void setBindPUName(const Str8& name) = 0;

		virtual void setBindBoneName(const Str8& name) = 0;

		virtual void setPosOffset(const Vec3& pos) = 0;

		virtual void setOriOffset(const Vec4& ori) = 0;

		virtual void setPUName(const Str& name) = 0;
	};

	class IWeaponLightEvent: public IEffectEvent
	{
	public:
		virtual void setPUName(const Str& name) = 0;

		virtual void setBindExternalEntityName(const Str8& name) = 0;

		virtual void setPosOffset(const Vec3& pos) = 0;

		virtual void setTrailLength(U32 length) = 0;

		virtual void setTrailWidth(U32 width) = 0;

		virtual void setTrailLiveTime(Flt time) = 0;
	};

	class IEffectFadeEvent : public IEffectEvent
	{
	public:
		virtual void setPUName(const Str& name) = 0;

		virtual void setFadeTimePoint(Flt fadetimePoint) = 0;

		virtual void setDurationTime(U32 durationTime) = 0;

		virtual void setFadeType(EffectFadeTypes fadetype) = 0;

		virtual void setFadeValue(Flt fadeValue) = 0;
	};
}

#endif