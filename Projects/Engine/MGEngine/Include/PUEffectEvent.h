/******************************************************************************/
#ifndef _PU_EFFECTEVENT_H_
#define _PU_EFFECTEVENT_H_
/******************************************************************************/
#include "IEffectEvent.h"
#include "EnginePreqs.h"

namespace MG
{
	/***************************************************************/
	// PU开始事件
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
		// PU名字
		Str8				mPUName;
		// 事件名字
		Str8				mEventName;
		// 控制者
		EffectComponent*	mEffectController;

		Flt					mTimePoint;
	};

	/***************************************************************/
	// PU停止事件
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
		// PU名字
		Str8				mPUName;
		// 事件名字
		Str8				mEventName;
		// 控制者
		EffectComponent*	mEffectController;

		Flt					mTimePoint;
	};

	/***************************************************************/
	// PU绑定事件
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
		// 是否开始
		Bool	mIsStart;
		// PU名字
		Str8	mPUName;
		// 是否绑定在自身的Component上.(是的话,设置位置什么的都是去Component的矩阵再相乘)
		BOOL	bBindRootComponent;
		// 绑定外部实体的名称.
		Int		mBindExternalEntitySlot;
		// 绑定模型的名称(特效内部)
		Str8	mBindModelName;
		// 绑定PU的名称(特效内部)
		Str8	mBindPUName;
		// 绑定骨骼的名称(特效内部)
		Str8	mBindBoneName;
		// 位置的偏移量
		Vec3	mPositionOffset;
		// 朝向的偏移量
		Vec4	mOrientationOffset;

		// 事件名字
		Str8				mEventName;
		// 控制者
		EffectComponent*	mEffectController;

		Flt					mTimePoint;

		// 绑定器
		EffectComponentBinderSceneNode* mSceneNodeBinder;
		EffectComponentBinderBonePos* mBonePosBinder;

		// 绑定者
		ISceneNode*			mBinderNode;
		// 被绑定者
		ISceneNode*			mBeBinderNode;
		//
		IEntity*			mBeBinderEntity;
		// 绑定的位置
		Vec3				mBindPos;
		// 绑定的朝向
		Qua					mBindQua;
		// 是否有骨骼名
		Bool				mHasBoneName;
	};
}

#endif