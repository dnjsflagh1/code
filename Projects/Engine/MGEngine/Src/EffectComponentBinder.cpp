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

		// 获得父节点位置
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

		// 设置被绑定着位置
		mBeBindeder->setPosition(parentPos);
		mBeBindeder->setOrientation(parentQua);

		// 设置绑定者位置
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

		// 外部实体存在的话.骨骼名为外部实体骨骼名,否则为内部实体骨骼名
		if (mParentEntity)
		{
			// 先获取外部实体的位置的朝向
			parentPos = mParentEntity->getModelObject()->getBoneWorldPosition(mBoneName.c_str());
			parentQuaternion = mParentEntity->getModelObject()->getBoneWorldOrientation(mBoneName.c_str());

			// 设置被绑定者位置和朝向
			//mBeBinder->getSceneNode()->setPosition(parentPos);
			//mBeBinder->getSceneNode()->setOrientation(parentQuaternion);

			// 设置绑定者的位置和朝向,(加上偏移量)
			mBinder->setPosition(parentPos);
			mBinder->setOrientation(parentQuaternion);
		}
		else
		{
			// 骨骼名为内部实体骨骼名

			// 外部实体不存在.parent位置则为Component的位置
			mParentComponent->getSceneNode()->getPosition(parentPos);
			mParentComponent->getSceneNode()->getOrientation(parentQuaternion);

			// 把Component的位置设置给被绑定者
			mBeBinder->getSceneNode()->setPosition(parentPos);
			mBeBinder->getSceneNode()->setOrientation(parentQuaternion);

			// 获取被绑定模型的骨骼点位置
			Vec3 bebinderbonePos;
			Qua bebinderboneQua;

			bebinderbonePos = mBeBinder->getModelObject()->getBoneWorldPosition(mBoneName.c_str());
			bebinderboneQua = mBeBinder->getModelObject()->getBoneWorldOrientation(mBoneName.c_str());

			// 设置绑定者的位置和朝向(加上偏移量)

			mBinder->setPosition(bebinderbonePos);
			mBinder->setOrientation(bebinderboneQua);
		}

	}

}