#include "stdafx.h"
#include "EffectComponentBinder.h"
#include "ModelEffectEvent.h"
#include "EffectXmlSerializer.h"
#include "EffectComponent.h"
#include "Entity.h"
#include "Scene.h"
#include "EngineMain.h"

namespace MG
{
	/***************************************************************/
	// ģ����ʾ�¼�
	/***************************************************************/
	ModelVisibleEffectEvent::ModelVisibleEffectEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller)
		: mEventName(eventname)
		, mEffectController(controller)
		, bVisible(FALSE)
		, mTimePoint(timePoint)
	{
		setName(name);
	}

	ModelVisibleEffectEvent::~ModelVisibleEffectEvent()
	{

	}

	void ModelVisibleEffectEvent::start()
	{
		if (!mEffectController)
			return;

		IEntity* entity = mEffectController->getModelEffect(mModelName);
		if (!entity)
			return;

		// ����ģ���Ƿ�ɼ�
		entity->getSceneNode()->setVisible(bVisible);
	}

	void ModelVisibleEffectEvent::stop()
	{
		if (!mEffectController)
			return;

		IEntity* entity = mEffectController->getModelEffect(mModelName);
		if (!entity)
			return;

		// ����ģ���Ƿ�ɼ�
		entity->getSceneNode()->setVisible(false);
	}

	void ModelVisibleEffectEvent::update( Flt delta )
	{

	}

	Str8& ModelVisibleEffectEvent::getEventName()
	{
		return mEventName;
	}

	EffectComponent* ModelVisibleEffectEvent::getController()
	{
		return mEffectController;
	}

	void ModelVisibleEffectEvent::setVisible( bool visible )
	{
		bVisible = visible;
	}

	void ModelVisibleEffectEvent::setModelName( const Str& name )
	{
		mModelName = name;
	}

	MG::Flt ModelVisibleEffectEvent::getEventTimePoint()
	{
		return mTimePoint;
	}

	void ModelVisibleEffectEvent::setEventTimePoint( Flt timePoint )
	{
		mTimePoint = timePoint;
	}

	ISceneNode* ModelVisibleEffectEvent::getSceneNode()
	{
		if (mEffectController)
			return mEffectController->getSceneNode();
		else
			return NULL;
	}
	/***************************************************************/
	// ģ�Ͷ����¼�
	/***************************************************************/
	ModelAnimationEffectEvent::ModelAnimationEffectEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller)
		: mEventName(eventname)
		, mEffectController(controller)
		, bLoopAnim(FALSE)
		, mTimePoint(timePoint)
	{
		setName(name);
	}

	ModelAnimationEffectEvent::~ModelAnimationEffectEvent()
	{

	}

	void ModelAnimationEffectEvent::start()
	{
		if (!mEffectController)
			return;

		IEntity* entity = mEffectController->getModelEffect(mModelName);
		if (!entity)
			return;

		// ����ģ�Ͷ�����(�Ƿ�ѭ��), �������ⲿ����stop��ֹͣѭ��
		IAnimationController* animationController =
			entity->getAnimationController();
		if (animationController)
		{
			animationController->play(mAnimationName.c_str());
			animationController->setLoop(mAnimationName.c_str(), bLoopAnim);
		}
	}

	void ModelAnimationEffectEvent::stop()
	{
		if (!mEffectController)
			return;

		IEntity* entity = mEffectController->getModelEffect(mModelName);
		if (!entity)
			return;

		// ����ģ�Ͷ�����(�Ƿ�ѭ��), �������ⲿ����stop��ֹͣѭ��
		IAnimationController* animationController =
			entity->getAnimationController();
		if (animationController)
			animationController->stop(mAnimationName.c_str());

		entity->getSceneNode()->setVisible(false);
	}

	void ModelAnimationEffectEvent::update( Flt delta )
	{

	}

	Str8& ModelAnimationEffectEvent::getEventName()
	{
		return mEventName;
	}

	EffectComponent* ModelAnimationEffectEvent::getController()
	{
		return mEffectController;
	}

	void ModelAnimationEffectEvent::setAnimationName( const Str8& animname)
	{
		mAnimationName = animname;
	}

	MG::Flt ModelAnimationEffectEvent::getEventTimePoint()
	{
		return mTimePoint;
	}

	void ModelAnimationEffectEvent::setEventTimePoint( Flt timePoint )
	{
		mTimePoint = timePoint;
	}

	ISceneNode* ModelAnimationEffectEvent::getSceneNode()
	{
		if (mEffectController)
			return mEffectController->getSceneNode();
		else
			return NULL;
	}
	/***************************************************************/
	// ģ�Ͱ��¼�
	/***************************************************************/
	ModelBindEffectEvent::ModelBindEffectEvent(const Str& name, const Str8& eventname, Flt timePoint, EffectComponent* controller)
		: mEventName(eventname)
		, mEffectController(controller)
		, bBindRootComponent(FALSE)
		, mIsStart(false)
		, mTimePoint(timePoint)
		, mSceneNodeBinder(NULL)
		, mBonePosBinder(NULL)
		, mBinderNode(NULL)
		, mBeBinderNode(NULL)
		, mBeBinderEntity(NULL)
		, mHasBoneName(false)
		, mBindPos(Vec3(0, 0, 0))
		, mBindQua(Qua(1, 0, 0, 0))
		, mBindExternalEntitySlot(0)
	{
		setName(name);

		mSceneNodeBinder = MG_NEW EffectComponentBinderSceneNode(mEffectController);
		mBonePosBinder = MG_NEW EffectComponentBinderBonePos(mEffectController);
	}

	ModelBindEffectEvent::~ModelBindEffectEvent()
	{
		MG_SAFE_DELETE(mSceneNodeBinder);
		MG_SAFE_DELETE(mBonePosBinder);
	}

	void ModelBindEffectEvent::start()
	{
		startBind();

		mIsStart = true;
	}

	void ModelBindEffectEvent::stop()
	{
		mIsStart = false;

		detachBind();
	}

	void ModelBindEffectEvent::update( Flt delta )
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

	Str8& ModelBindEffectEvent::getEventName()
	{
		return mEventName;
	}

	EffectComponent* ModelBindEffectEvent::getController()
	{
		return mEffectController;
	}

	void ModelBindEffectEvent::setIsBindRootComponent( bool bindrootcomponent )
	{
		bBindRootComponent = bindrootcomponent;
	}

	void ModelBindEffectEvent::setBindExternalEntityName( const Str8& name )
	{
		mBindExternalEntitySlot = atoi(name.c_str());
	}

	void ModelBindEffectEvent::setBindModelName( const Str8& name )
	{
		mBindModelName = name;
	}

	void ModelBindEffectEvent::setBindPUName( const Str8& name )
	{
		mBindPUName = name;
	}

	void ModelBindEffectEvent::setBindBoneName( const Str8& name )
	{
		mBindBoneName = name;
	}

	void ModelBindEffectEvent::setPosOffset( const Vec3& pos )
	{
		mPositionOffset = pos;
	}

	void ModelBindEffectEvent::setOriOffset( const Vec4& ori )
	{
		mOrientationOffset = ori;
	}

	MG::Flt ModelBindEffectEvent::getEventTimePoint()
	{
		return mTimePoint;
	}

	void ModelBindEffectEvent::setEventTimePoint( Flt timePoint )
	{
		mTimePoint = timePoint;
	}

	void ModelBindEffectEvent::startBind()
	{
		Scene* scene = mEffectController->getScene();
		if (!scene)
			return;

		if (!mEffectController)
			return;

		Entity* entity = mEffectController->getModelEffect(mModelName);
		if (!entity)
			return;

		//////////////////////////////////////////////////////////////////////////
		// ��Ҫ�󶨵Ľڵ�
		mBinderNode = entity->getSceneNode();
		mBinderNode->setVisible(true);

		// �ڰ�����������Ҫ�󶨵Ľڵ�
		mSceneNodeBinder->setBinder(mBinderNode);
		mBonePosBinder->setBinder(mBinderNode);

		//////////////////////////////////////////////////////////////////////////
		/// ���ø��ڵ�.Component�ڲ���ģ�ͻ���PU�Ǹ����ⲿ�ڵ��ƶ����߸�������Component�ƶ�

		// ���Ǹ��������Component�󶨵Ļ�
		if (!bBindRootComponent)
		{
			IEntity* exbindEntity = NULL;

			if (mBindExternalEntitySlot > 0 )
			{
				// �༭��ģʽ��ȡ�ⲿʵ��Ľӿڸ��ͻ��˲�һ��
				if (EngineMain::getInstance().getMode() == EM_EDITOR)
					exbindEntity = scene->getEntityfromSlot(mBindExternalEntitySlot-1);
				else
					exbindEntity = mEffectController->getSlotEntity(mBindExternalEntitySlot-1);
			}

			// ���ⲿģ�����ֲ�Ϊ��
			if (exbindEntity)
			{
				// ���ø��ڵ�ʵ��
				mSceneNodeBinder->setParentEntity(exbindEntity);
				mBonePosBinder->setParentEntity(exbindEntity);

				mBeBinderNode = exbindEntity->getSceneNode();
				if (!mBindBoneName.empty())
				{
					mBeBinderEntity = exbindEntity;
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
			mBonePosBinder->setbeBinder(mBeBinderEntity);

		if (!mBindBoneName.empty())
			mBonePosBinder->setBoneName(mBindBoneName);

	}

	void ModelBindEffectEvent::detachBind()
	{
		if (!mEffectController)
			return;

		Entity* insideBindEntity = mEffectController->getModelEffect(mBindModelName);
		if (insideBindEntity)
			insideBindEntity->getSceneNode()->setVisible(false);

		PUEffect* bindPUEffect = mEffectController->getPUEffect(mBindPUName);
		if (bindPUEffect)
			bindPUEffect->stop();

		Entity* entity = mEffectController->getModelEffect(mModelName);
		if (entity)
			entity->getSceneNode()->setVisible(false);
	}

	ISceneNode* ModelBindEffectEvent::getSceneNode()
	{
		if (mEffectController)
			return mEffectController->getSceneNode();
		else
			return NULL;
	}

	Str ModelBindEffectEvent::getBindExternalEntityName()
	{
		char name[100];
		itoa(mBindExternalEntitySlot, name, 10);
		return Str(name);
	}
}
