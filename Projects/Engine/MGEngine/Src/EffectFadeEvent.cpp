#include "stdafx.h"
#include "EffectFadeEvent.h"
#include "EffectComponent.h"
#include "Scene.h"


namespace MG
{

	EffectFadeEvent::EffectFadeEvent( const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller )
		: mEventName(eventname)
		, mEffectController(controller)
		, mTimePoint(timePoint)
		, mIsStart(false)
		, mFadeTimePoint(0)
		, mDurationTime(0)
		, mFadeType(EFT_NULL)
		, mFadeValue(0)
	{
		setName(name);
	}

	EffectFadeEvent::~EffectFadeEvent()
	{

	}

	ISceneNode* EffectFadeEvent::getSceneNode()
	{
		if (mEffectController)
			return mEffectController->getSceneNode();
		else
			return NULL;
	}

	void EffectFadeEvent::start()
	{

	}

	void EffectFadeEvent::stop()
	{

	}

	void EffectFadeEvent::update( Flt delta )
	{

	}

	Str8& EffectFadeEvent::getEventName()
	{
		return mEventName;
	}

	EffectComponent* EffectFadeEvent::getController()
	{
		return mEffectController;
	}

	Flt EffectFadeEvent::getEventTimePoint()
	{
		return mTimePoint;
	}

	void EffectFadeEvent::setEventTimePoint( Flt timePoint )
	{
		mTimePoint = timePoint;
	}

	void EffectFadeEvent::setPUName( const Str& name )
	{
		mPUName = name;
	}

	void EffectFadeEvent::setFadeTimePoint( Flt fadetimePoint )
	{
		mFadeTimePoint = fadetimePoint;
	}

	void EffectFadeEvent::setDurationTime( U32 durationTime )
	{
		mDurationTime = durationTime;
	}

	void EffectFadeEvent::setFadeType( EffectFadeTypes fadetype )
	{
		mFadeType = fadetype;
	}

	void EffectFadeEvent::setFadeValue( Flt fadeValue )
	{
		mFadeValue = fadeValue;
	}

	Str& EffectFadeEvent::getPUName()
	{
		return mPUName;
	}

	Flt EffectFadeEvent::getFadeTimePoint()
	{
		return mFadeTimePoint;
	}

	U32 EffectFadeEvent::getDurationTime()
	{
		return mDurationTime;
	}

	EffectFadeTypes EffectFadeEvent::getFadeType()
	{
		return mFadeType;
	}

	Flt EffectFadeEvent::getFadeValue()
	{
		return mFadeValue;
	}

	Str& EffectFadeEvent::getFadeTypeStr()
	{
		Str typeStr;
		switch (mFadeType)
		{
		case EFT_NULL:
			typeStr = "";
			break;
		case EFT_SCALE:
			typeStr = "Scale";
			break;
		case EFT_VELOCITY:
			typeStr = "Velocity";
			break;
		default:
			break;
		}

		return typeStr;
	}

	EffectFadeTypes EffectFadeEvent::getFadeTypeFromStr( Str& fadetype )
	{
		Str typeName = fadetype;
		if (StrCmp(typeName.c_str(), "") == 0)
			return EFT_NULL;
		else 
		if (StrCmp(typeName.c_str(), "Scale") == 0)
			return EFT_SCALE;
		else
		if (StrCmp(typeName.c_str(), "Velocity") == 0)
			return EFT_VELOCITY;
	}
}