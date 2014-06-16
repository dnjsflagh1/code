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
	// ģ����ʾ�¼�
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
		// ģ������
		Str8				mModelName;
		// �Ƿ���ʾ
		BOOL				bVisible;
		// �¼�����
		Str8				mEventName;
		// ������
		EffectComponent*	mEffectController;

		Flt					mTimePoint;
	};

	/***************************************************************/
	// ģ�Ͷ����¼�
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
		// ģ������
		Str8				mModelName;
		// ��������
		Str8				mAnimationName;
		// �Ƿ�ѭ��
		BOOL				bLoopAnim;

		// �¼�����
		Str8				mEventName;
		// ������
		EffectComponent*	mEffectController;

		Flt					mTimePoint;
	};

	/***************************************************************/
	// ģ�Ͱ��¼�
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
		// �Ƿ�ʼ
		Bool	mIsStart;
		// ģ������
		Str8	mModelName;
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

		ISceneNode*			mBinderNode;
		ISceneNode*			mBeBinderNode;
		IEntity*			mBeBinderEntity;
		Vec3				mBindPos;
		Qua					mBindQua;
		Bool				mHasBoneName;

	};
}

#endif