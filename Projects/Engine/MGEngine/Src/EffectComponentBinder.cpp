#include "stdafx.h"
#include "IEntity.h"
#include "IModelObject.h"
#include "EffectComponentBinder.h"
#include "EffectComponent.h"

namespace MG
{
	//////////////////////////////////////////////////////////////////////////
	EffectComponentBinderSceneNode::EffectComponentBinderSceneNode(IEffectComponent* component, ISceneNode* binder, 
		ISceneNode* beBindeder, IEntity* parentEntity, Vec3 offsetpos, Qua offsetqua)
		: mParentComponent(component)
		, mParentEntity(parentEntity)
		, mBinder(binder)
		, mBeBindeder(beBindeder)
		, mOffsetpos(offsetpos)
		, mOffsetqua(offsetqua)
	{

	}

	EffectComponentBinderSceneNode::~EffectComponentBinderSceneNode()
	{

	}

	void EffectComponentBinderSceneNode::setParentEntity(IEntity* parentEntity)
	{
		mParentEntity = parentEntity;
	}

	void EffectComponentBinderSceneNode::setBinder( ISceneNode* binder )
	{
		mBinder = binder;
	}

	void EffectComponentBinderSceneNode::setBeBinder( ISceneNode* beBinder )
	{
		mBeBindeder = beBinder;
	}

	void EffectComponentBinderSceneNode::setOffsetpos( Vec3& offsetpos )
	{
		mOffsetpos = offsetpos;
	}

	void EffectComponentBinderSceneNode::setOffsetQua( Qua& offsetqua )
	{
		mOffsetqua = offsetqua;
	}

	void EffectComponentBinderSceneNode::update()
	{
		if (!mBinder || !mBeBindeder)
			return;

		// ��ø��ڵ�λ��
		Vec3 parentPos;
		Qua  parentQua;
		if (mParentEntity)
		{
			mParentEntity->getSceneNode()->getPosition(parentPos);
			mParentEntity->getSceneNode()->getOrientation(parentQua);
		}
		else
		{
			mParentComponent->getSceneNode()->getPosition(parentPos);
			mParentComponent->getSceneNode()->getOrientation(parentQua);
		}

		// ���ñ�����λ��
		mBeBindeder->setPosition(parentPos);
		mBeBindeder->setOrientation(parentQua);

		// ���ð���λ��
		mBinder->setPosition(parentPos + parentQua * mOffsetpos);
		mBinder->setOrientation(parentQua * mOffsetqua);
	}

	//////////////////////////////////////////////////////////////////////////
	EffectComponentBinderBonePos::EffectComponentBinderBonePos(IEffectComponent* component, 
		ISceneNode* binder, IEntity* beBinder, IEntity* parentEntity, Str boneName)
		: mParentComponent(component)
		, mParentEntity(parentEntity)
		, mBinder(binder)
		, mBeBinder(beBinder)
		, mBoneName(boneName)
		, bIsBindRootComponent(false)
	{

	}

	EffectComponentBinderBonePos::~EffectComponentBinderBonePos()
	{

	}

	void EffectComponentBinderBonePos::setParentEntity( IEntity* parentEntity )
	{
		mParentEntity = parentEntity;
	}

	void EffectComponentBinderBonePos::setBinder( ISceneNode* binder )
	{
		mBinder = binder;
	}

	void EffectComponentBinderBonePos::setbeBinder( IEntity* beBinder )
	{
		mBeBinder = beBinder;
	}

	void EffectComponentBinderBonePos::setBoneName( Str& boneName )
	{
		mBoneName = boneName;
	}

	void EffectComponentBinderBonePos::update()
	{
		if (!mBinder || !mBeBinder || mBoneName.empty())
			return;

		Vec3 localPos, parentPos;
		Qua  localQuaternion, parentQuaternion;

		// �ⲿʵ����ڵĻ�.������Ϊ�ⲿʵ�������,����Ϊ�ڲ�ʵ�������
		if (mParentEntity)
		{
			// �Ȼ�ȡ�ⲿʵ���λ�õĳ���
			parentPos = mParentEntity->getModelObject()->getBoneWorldPosition(mBoneName.c_str());
			parentQuaternion = mParentEntity->getModelObject()->getBoneWorldOrientation(mBoneName.c_str());

			// ���ñ�����λ�úͳ���
			//mBeBinder->getSceneNode()->setPosition(parentPos);
			//mBeBinder->getSceneNode()->setOrientation(parentQuaternion);

			// ���ð��ߵ�λ�úͳ���,(����ƫ����)
			mBinder->setPosition(parentPos);
			mBinder->setOrientation(parentQuaternion);
		}
		else
		{
			// ������Ϊ�ڲ�ʵ�������

			// �ⲿʵ�岻����.parentλ����ΪComponent��λ��
			mParentComponent->getSceneNode()->getPosition(parentPos);
			mParentComponent->getSceneNode()->getOrientation(parentQuaternion);

			// ��Component��λ�����ø�������
			mBeBinder->getSceneNode()->setPosition(parentPos);
			mBeBinder->getSceneNode()->setOrientation(parentQuaternion);

			// ��ȡ����ģ�͵Ĺ�����λ��
			Vec3 bebinderbonePos;
			Qua bebinderboneQua;

			bebinderbonePos = mBeBinder->getModelObject()->getBoneWorldPosition(mBoneName.c_str());
			bebinderboneQua = mBeBinder->getModelObject()->getBoneWorldOrientation(mBoneName.c_str());

			// ���ð��ߵ�λ�úͳ���(����ƫ����)

			mBinder->setPosition(bebinderbonePos);
			mBinder->setOrientation(bebinderboneQua);
		}

	}

}