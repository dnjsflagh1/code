#include "stdafx.h"
#include "EffectComponentBinder.h"
#include "PUEffectEvent.h"
#include "EffectXmlSerializer.h"
#include "EffectComponent.h"
#include "ParticleUniverseSystemManager.h"
#include "Scene.h"
#include "EngineMain.h"
#include "PUEffect.h"

namespace MG
{
	/***************************************************************/
	// PU��ʼ�¼�
	/***************************************************************/
	PUStartEffectEvent::PUStartEffectEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller)
		: mEventName(eventname)
		, mEffectController(controller)
		, mTimePoint(timePoint)
	{
		setName(name);
	}

	PUStartEffectEvent::~PUStartEffectEvent()
	{

	}

	void PUStartEffectEvent::start()
	{
		if (!mEffectController)
			return;

		IPUEffect* effect = mEffectController->getPUEffect(mPUName);
		if (!effect)
			return;

		// ��ȡPU,Ȼ��start
		effect->start();
	}

	void PUStartEffectEvent::stop()
	{
		if (!mEffectController)
			return;

		IPUEffect* effect = mEffectController->getPUEffect(mPUName);
		if (!effect)
			return;

		// ��ȡPU,Ȼ��start
		effect->stop();
	}

	void PUStartEffectEvent::update( Flt delta )
	{
		IPUEffect* effect = mEffectController->getPUEffect(mPUName);
		if (!effect)
			return;

		if (effect)
			effect->update(delta);

		Vec3 pos;
		mEffectController->getSceneNode()->getPosition(pos);
		effect->getSceneNode()->setPosition(pos);

		Qua qua;
		mEffectController->getSceneNode()->getOrientation(qua);
		effect->getSceneNode()->setOrientation(qua);
	}

	Str8& PUStartEffectEvent::getEventName()
	{
		return mEventName;
	}

	EffectComponent* PUStartEffectEvent::getController()
	{
		return mEffectController;
	}

	MG::Flt PUStartEffectEvent::getEventTimePoint()
	{
		return mTimePoint;
	}

	void PUStartEffectEvent::setEventTimePoint( Flt timePoint )
	{
		mTimePoint = timePoint;
	}

	ISceneNode* PUStartEffectEvent::getSceneNode()
	{
		if (mEffectController)
			return mEffectController->getSceneNode();
		else
			return NULL;
	}
	/***************************************************************/
	// PUֹͣ�¼�
	/***************************************************************/
	PUStopEffectEvent::PUStopEffectEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller)
		: mEventName(eventname)
		, mEffectController(controller)
		, mTimePoint(timePoint)
	{
		setName(name);
	}

	PUStopEffectEvent::~PUStopEffectEvent()
	{

	}

	void PUStopEffectEvent::start()
	{
		if (!mEffectController)
			return;

		IPUEffect* effect = mEffectController->getPUEffect(mPUName);
		if (!effect)
			return;

		// ��ȡPU,Ȼ��stop
		effect->stop();

	}

	void PUStopEffectEvent::stop()
	{

	}

	void PUStopEffectEvent::update( Flt delta )
	{

	}

	Str8& PUStopEffectEvent::getEventName()
	{
		return mEventName;
	}

	EffectComponent* PUStopEffectEvent::getController()
	{
		return mEffectController;
	}

	MG::Flt PUStopEffectEvent::getEventTimePoint()
	{
		return mTimePoint;
	}

	void PUStopEffectEvent::setEventTimePoint( Flt timePoint )
	{
		mTimePoint = timePoint;
	}

	ISceneNode* PUStopEffectEvent::getSceneNode()
	{
		if (mEffectController)
			return mEffectController->getSceneNode();
		else
			return NULL;
	}
	/***************************************************************/
	// PU���¼�
	/***************************************************************/
	PUBindEffectEvent::PUBindEffectEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller)
		: mEventName(eventname)
		, mEffectController(controller)
		, bBindRootComponent(FALSE)
		, mIsStart(false)
		, mTimePoint(timePoint)
		, mBinderNode(NULL)
		, mBeBinderNode(NULL)
		, mSceneNodeBinder(NULL)
		, mBonePosBinder(NULL)
		, mHasBoneName(false)
		, mBindPos(Vec3(0, 0, 0))
		, mBindQua(Qua(1, 0, 0, 0))
		, mBindExternalEntitySlot(0)
	{
		setName(name);

		mSceneNodeBinder = MG_NEW EffectComponentBinderSceneNode(mEffectController);
		mBonePosBinder = MG_NEW EffectComponentBinderBonePos(mEffectController);
	}

	PUBindEffectEvent::~PUBindEffectEvent()
	{
		MG_SAFE_DELETE(mSceneNodeBinder);
		MG_SAFE_DELETE(mBonePosBinder);
	}

	void PUBindEffectEvent::start()
	{
		mIsStart = true;

		startBind();
	}

	void PUBindEffectEvent::stop()
	{
		mIsStart = false;

		detachBind();
	}

	void PUBindEffectEvent::update( Flt delta )
	{

		if (mIsStart)
		{
			if (!mBinderNode)
				return;

			if (!mHasBoneName)
				mSceneNodeBinder->update();
			else
				mBonePosBinder->update();
		}

	}

	Str8& PUBindEffectEvent::getEventName()
	{
		return mEventName;
	}

	EffectComponent* PUBindEffectEvent::getController()
	{
		return mEffectController;
	}

	void PUBindEffectEvent::setIsBindRootComponent( bool bindrootcomponent )
	{
		bBindRootComponent = bindrootcomponent;
	}

	void PUBindEffectEvent::setBindExternalEntityName( const Str8& name )
	{
		mBindExternalEntitySlot = atoi(name.c_str());
	}

	void PUBindEffectEvent::setBindModelName( const Str8& name )
	{
		mBindModelName = name;
	}

	void PUBindEffectEvent::setBindPUName( const Str8& name )
	{
		mBindPUName = name;
	}

	void PUBindEffectEvent::setBindBoneName( const Str8& name )
	{
		mBindBoneName = name;
	}

	void PUBindEffectEvent::setPosOffset( const Vec3& pos )
	{
		mPositionOffset = pos;
	}

	void PUBindEffectEvent::setOriOffset( const Vec4& ori )
	{
		mOrientationOffset = ori;
	}

	MG::Flt PUBindEffectEvent::getEventTimePoint()
	{
		return mTimePoint;
	}

	void PUBindEffectEvent::setEventTimePoint( Flt timePoint )
	{
		mTimePoint = timePoint;
	}

	void PUBindEffectEvent::startBind()
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
		mBonePosBinder->setBinder(mBinderNode);

		//////////////////////////////////////////////////////////////////////////
		/// ���ø��ڵ�.Component�ڲ���ģ�ͻ���PU�Ǹ����ⲿ�ڵ��ƶ����߸�������Component�ƶ�

		// ���Ǹ��������Component�󶨵Ļ�
		if (!bBindRootComponent)
		{
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
				mBonePosBinder->setParentEntity(exEntity);

				mBeBinderNode = exEntity->getSceneNode();
				if (!mBindBoneName.empty())
				{
					mBeBinderEntity = exEntity;
					mHasBoneName = true;
				}
				else
				{
					mBeBinderEntity = NULL;
					mHasBoneName = false;
				}
			}

		}
		else // ���������Component��,ParentEntity�Ͳ���Ҫ��.��������Component�ƶ�
		{

		}

		//////////////////////////////////////////////////////////////////////////
		/// ���ñ��󶨵�����
		Entity* insideBindEntity = mEffectController->getModelEffect(mBindModelName);
		PUEffect* bindPUEffect = mEffectController->getPUEffect(mBindPUName);

		// �󶨵��ڲ�ģ��
		if (insideBindEntity)
		{
			mBeBinderNode = insideBindEntity->getSceneNode();
			if (!mBindBoneName.empty())
			{
				mBeBinderEntity = insideBindEntity;
				mHasBoneName = true;
			}
			else
			{
				mBeBinderEntity = NULL;
				mHasBoneName = false;
			}
		}
		// �󶨵��ڲ�PU
		else 
		if (bindPUEffect)
		{
			mBeBinderNode = bindPUEffect->getSceneNode();
			bindPUEffect->start();
		}


		if (mBeBinderNode)
		{
			mBeBinderNode->setVisible(true);
			mSceneNodeBinder->setBeBinder(mBeBinderNode);
			mSceneNodeBinder->setOffsetpos(mPositionOffset);
		}

		if (mBeBinderEntity)
		{
			mBonePosBinder->setbeBinder(mBeBinderEntity);
		}

		if (!mBindBoneName.empty())
		{
			mBonePosBinder->setBoneName(mBindBoneName);
		}
	}

	void PUBindEffectEvent::detachBind()
	{
		if (!mEffectController)
			return;

		PUEffect* effect = mEffectController->getPUEffect(mPUName);
		if (effect)
			effect->stop();

		Entity* insideBindEntity = mEffectController->getModelEffect(mBindModelName);
		if (insideBindEntity)
			insideBindEntity->getSceneNode()->setVisible(false);

		PUEffect* bindPUEffect = mEffectController->getPUEffect(mBindPUName);
		if (bindPUEffect)
			bindPUEffect->stop();

	}

	ISceneNode* PUBindEffectEvent::getSceneNode()
	{
		if (mEffectController)
			return mEffectController->getSceneNode();
		else
			return NULL;
	}

	Str PUBindEffectEvent::getBindExternalEntityName()
	{
		char name[100];
		itoa(mBindExternalEntitySlot, name, 10);
		return Str(name);
	}
}