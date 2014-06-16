#include "stdafx.h"
#include "EffectComponentBinder.h"
#include "WeaponLightEvent.h"
#include "EffectComponent.h"
#include "Scene.h"
#include "EngineMain.h"

namespace MG
{
	WeaponLightEvent::WeaponLightEvent( const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller )
		: mEventName(eventname)
		, mEffectController(controller)
		, mTimePoint(timePoint)
		, mBinderNode(NULL)
		, mBeBinderNode(NULL)
		, mIsStart(false)
		, mBindExternalEntitySlot(0)
		, mTrailLength(0)
		, mTrailWidth(0)
		, mTrailLiveTime(0.0f)
	{
		setName(name);

		mSceneNodeBinder = MG_NEW EffectComponentBinderSceneNode(mEffectController);
	}

	WeaponLightEvent::~WeaponLightEvent()
	{
		MG_SAFE_DELETE(mSceneNodeBinder);
	}

	ISceneNode* WeaponLightEvent::getSceneNode()
	{
		if (mEffectController)
			return mEffectController->getSceneNode();
		else
			return NULL;
	}

	void WeaponLightEvent::start()
	{
		mIsStart = true;

		startBind();
	}

	void WeaponLightEvent::stop()
	{
		mIsStart = false;

		detachBind();
	}

	void WeaponLightEvent::update( Flt delta )
	{
		if (mIsStart)
		{
			if (!mBinderNode)
				return;

			mSceneNodeBinder->update();
		}
	}

	Str8& WeaponLightEvent::getEventName()
	{
		return mEventName;
	}

	EffectComponent* WeaponLightEvent::getController()
	{
		return mEffectController;
	}

	Flt WeaponLightEvent::getEventTimePoint()
	{
		return mTimePoint;
	}

	void WeaponLightEvent::setEventTimePoint( Flt timePoint )
	{
		mTimePoint = timePoint;
	}

	void WeaponLightEvent::setPUName( const Str& name )
	{
		mPUName = name;
	}

	void WeaponLightEvent::setBindExternalEntityName( const Str8& name )
	{
		mBindExternalEntitySlot = atoi(name.c_str());
	}

	void WeaponLightEvent::setPosOffset( const Vec3& pos )
	{
		mPositionOffset = pos;
	}

	void WeaponLightEvent::setTrailLength( U32 length )
	{
		if (!mEffectController)
			return;

		IPUEffect* pueffect = NULL;
		if (!mPUName.empty())
			pueffect = mEffectController->getPUEffect(mPUName);

		if (!pueffect)
			return;
		
		mTrailLength = length;

		pueffect->setTrailLength(mTrailLength);
	}

	void WeaponLightEvent::setTrailWidth( U32 width )
	{
		if (!mEffectController)
			return;

		IPUEffect* pueffect = NULL;
		if (!mPUName.empty())
			pueffect = mEffectController->getPUEffect(mPUName);

		if (!pueffect)
			return;

		mTrailWidth = width;

		pueffect->setTrailWidth(mTrailWidth);
	}

	void WeaponLightEvent::setTrailLiveTime( Flt time )
	{
		if (!mEffectController)
			return;

		IPUEffect* pueffect = NULL;
		if (!mPUName.empty())
			pueffect = mEffectController->getPUEffect(mPUName);

		if (!pueffect)
			return;

		mTrailLiveTime = time;

		pueffect->setTrailLiveTime(mTrailLiveTime);
	}

	void WeaponLightEvent::startBind()
	{
		Scene* scene = mEffectController->getScene();
		if (!scene)
			return;

		if (!mEffectController)
			return;

		PUEffect* effect = mEffectController->getPUEffect(mPUName);
		if (!effect)
			return;

		effect->start();
		//////////////////////////////////////////////////////////////////////////
		// ��Ҫ�󶨵Ľڵ�
		mBinderNode = effect->getSceneNode();

		// �ڰ�����������Ҫ�󶨵Ľڵ�
		mSceneNodeBinder->setBinder(mBinderNode);


		//////////////////////////////////////////////////////////////////////////
		//
		IEntity* exEntity = NULL;

		if (mBindExternalEntitySlot > 0)
		{
			// �༭��ģʽ��ȡ�ⲿʵ��Ľӿڸ��ͻ��˲�һ��
			if (EngineMain::getInstance().getMode() == EM_EDITOR)
				exEntity = scene->getEntityfromSlot(mBindExternalEntitySlot-1);
			else
				exEntity = mEffectController->getSlotEntity(mBindExternalEntitySlot-1);
		}

		// ���ⲿģ�����ֲ�Ϊ��
		if (exEntity)
		{
			// ���ø��ڵ�ʵ��
			mSceneNodeBinder->setParentEntity(exEntity);
			// ���ñ�����
			mBeBinderNode = exEntity->getSceneNode();
			mSceneNodeBinder->setBeBinder(mBeBinderNode);
			// ����ƫ����
			mSceneNodeBinder->setOffsetpos(mPositionOffset);
		}

	}

	void WeaponLightEvent::detachBind()
	{
		if (!mEffectController)
			return;

		PUEffect* effect = mEffectController->getPUEffect(mPUName);
		if (!effect)
			return;

		effect->stop();
	}

	Str WeaponLightEvent::getBindExternalEntityName()
	{
		char name[100];
		itoa(mBindExternalEntitySlot, name, 10);
		return Str(name);
	}

}
