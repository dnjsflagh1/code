/******************************************************************************/
#ifndef _MODEL_EFFECTEVENT_H_
#define _MODEL_EFFECTEVENT_H_
/******************************************************************************/
#include "IEffectEvent.h"

class EffectComponentBinderSceneNode;
class EffectComponentBinderBonePos;

namespace MG
{
	/***************************************************************/
	// 模型显示事件
	/***************************************************************/
	class ModelVisibleEffectEvent : public IModelVisibleEffectEvent
	{
	public:
		ModelVisibleEffectEvent(const Str& name, const Str8& eventname, Flt timePoint,EffectComponent* controller);
		virtual ~ModelVisibleEffectEvent();

	public:
		virtual SceneObjectTypes getType() { return EOT_MODEL_VISIBLE_EVENT; };

		virtual ISceneNode* getSceneNode();

	public:
		// 
		virtual void start();
		
		virtual void stop();

		virtual void update( Flt delta );

		virtual Str8& getEventName();

		virtual EffectComponent* getController();

		virtual void setVisible(bool visible);

		virtual void setModelName(const Str& name);

		virtual Flt	 getEventTimePoint();

		virtual void setEventTimePoint(Flt timePoint);
		////////////////////////////////////////////////////////////////

		Bool	getVisible() { return bVisible; }

		Str		getModelName() { return mModelName; }
	private:
		// 模型名字
		Str8				mModelName;
		// 是否显示
		BOOL				bVisible;
		// 事件名字
		Str8				mEventName;
		// 控制者
		EffectComponent*	mEffectController;

		Flt					mTimePoint;
	};

	/***************************************************************/
	// 模型动画事件
	/***************************************************************/
	class ModelAnimationEffectEvent : public IModelAnimationEffectEvent
	{
	public:
		ModelAnimationEffectEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller);
		virtual ~ModelAnimationEffectEvent();

	public:
		virtual SceneObjectTypes getType() { return EOT_MODEL_ANIMATION_EVENT; };

		virtual ISceneNode* getSceneNode();
	public:
		virtual void start();

		virtual void stop();

		virtual void update( Flt delta );

		virtual Str8& getEventName();

		virtual EffectComponent* getController();
	
		virtual void setAnimationName(const Str8& animname);

		virtual void setModelName(const Str& name) { mModelName = name; }

		virtual void setIsLoop(Bool loop) { bLoopAnim = loop;}

		virtual Flt	 getEventTimePoint();

		virtual void setEventTimePoint(Flt timePoint);
		//////////////////////////////////////////////////////////////////

		Str		getAnimationName() { return mAnimationName; }
		Str		getModelName() { return mModelName; }
		Bool	getLoop() { return bLoopAnim; }
	private:
		// 模型名字
		Str8				mModelName;
		// 动画名字
		Str8				mAnimationName;
		// 是否循环
		BOOL				bLoopAnim;

		// 事件名字
		Str8				mEventName;
		// 控制者
		EffectComponent*	mEffectController;

		Flt					mTimePoint;
	};

	/***************************************************************/
	// 模型绑定事件
	/***************************************************************/
	class ModelBindEffectEvent : public IModelBindEffectEvent
	{
	public:
		ModelBindEffectEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller);
		virtual ~ModelBindEffectEvent();

	public:
		virtual SceneObjectTypes getType() { return EOT_MODEL_BIND_EVENT; };

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

		virtual void setModelName(const Str8& name) { mModelName = name; }

		virtual Flt	 getEventTimePoint();

		virtual void setEventTimePoint(Flt timePoint);
		///////////////////////////////////////////////////////////////////
		void startBind();

		void detachBind();

		Bool getIsBindRootComponent() { return bBindRootComponent; }

		Str getBindExternalEntityName();

		Str& getBindModelName() { return mBindModelName; }

		Str& getBindPUName() { return mBindPUName; }

		Str& getBindBoneName() { return mBindBoneName; }

		Vec3& getPosOffset() { return mPositionOffset; } 

		Vec4& getOriOffset() { return mOrientationOffset; }

		Str8& getModelName() { return mModelName; }
	private:
		// 是否开始
		Bool	mIsStart;
		// 模型名字
		Str8	mModelName;
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

		ISceneNode*			mBinderNode;
		ISceneNode*			mBeBinderNode;
		IEntity*			mBeBinderEntity;
		Vec3				mBindPos;
		Qua					mBindQua;
		Bool				mHasBoneName;

	};
}

#endif