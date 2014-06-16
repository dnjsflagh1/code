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
	// 刀光事件
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
		// 是否开始
		Bool	mIsStart;
		// PU名字
		Str8				mPUName;
		// 事件名字
		Str8				mEventName;
		// 控制者
		EffectComponent*	mEffectController;
		// 事件触发的时间点
		Flt					mTimePoint;
		// 绑定外部实体的名称.
		Int		mBindExternalEntitySlot;
		// 绑定武器位置的偏移量
		Vec3	mPositionOffset;

		// 丝带长度
		U32					mTrailLength;
		// 丝带宽度
		U32					mTrailWidth;
		// 丝带的生存时间
		Flt					mTrailLiveTime;


		// 绑定者
		ISceneNode*			mBinderNode;
		// 被绑定者
		ISceneNode*			mBeBinderNode;

		// 绑定器
		EffectComponentBinderSceneNode* mSceneNodeBinder;
	};
}

#endif