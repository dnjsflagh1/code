#include "stdafx.h"

#include "Entity.h"
#include "IModelObject.h"
#include "IEntityAccessory.h"
#include "MGSceneNode.h"
#include "PUEffect.h"
#include "Scene.h"

#include "EffectEventUtil.h"
#include "EffectXmlSerializer.h"
#include "EffectComponent.h"

namespace MG
{

	EffectEventUtil::EffectEventUtil( EffectComponent* component )
		: mComponent(component)
	{

	}

	EffectEventUtil::~EffectEventUtil()
	{

	}
	//-----------------------------------------------------------------------
	Bool EffectEventUtil::execModelbindModel(Entity* childEntity, Entity* parentEntity, Bool attachToParent, Int bindBoxHeightRate, Str8 boneName)
	{
		bool result = false;

		if ( parentEntity && parentEntity->getModelObject() &&  
			childEntity && childEntity->getModelObject() &&
			mComponent->getSceneNode() )
		{
			IEntityAccessory* entityAccessory = MG_NEW IEntityAccessory;
			entityAccessory->isDepositLifeTime = false;
			entityAccessory->isSyncAnimation = false;
			entityAccessory->relativePosition = Vec3(0,0,0);
			entityAccessory->relativeQuaternion = Qua(1,0,0,0);
			entityAccessory->bindBoneName.clear();
			entityAccessory->sceneObject = childEntity;

			if ( bindBoxHeightRate > 0 )
			{
				Vec3 pos = parentEntity->getModelObject()->getCenterPosition(bindBoxHeightRate / 1000.0f, attachToParent);
				entityAccessory->relativePosition = pos;
				result = true;
			}
			else if ( !boneName.empty() )
			{
				entityAccessory->bindBoneName = boneName;
				result = true;
			}

			if ( result )
			{
				if ( attachToParent )
				{
					result = mComponent->getScene()->createEntityDynamicAccessorys( 
						parentEntity, mComponent->getName().c_str()
						, mComponent->getEffectResourceID()
						, SOT_EFFECTENTITY, entityAccessory);
				}
				else
				{
					mComponent->getSceneNode()->setPosition( entityAccessory->relativePosition );
				}
			}

			MG_DELETE entityAccessory;

		}
		return result;
	}	

	//-----------------------------------------------------------------------
	Bool EffectEventUtil::execModelbindPU( Entity* childEntity, PUEffect* parentPU )
	{
		if ( parentPU && childEntity && childEntity->getModelObject())
		{
			MGSceneNode* sceneNode = parentPU->getSceneNode();
			Vec3 pos;
			sceneNode->getPosition(pos);
			childEntity->getModelObject()->attachOtherSceneNode(sceneNode);
			childEntity->getSceneNode()->setPosition(Vec3(pos.x, pos.y, pos.z));

			return true;
		}
		else
			return false;
	}

	//-----------------------------------------------------------------------
	Bool EffectEventUtil::execPUbindModel( PUEffect* childPU, Entity* parentEntity, Bool attachToParent /*= false*/, Int bindBoxHeightRate /*= 500*/, Str8 boneName /*=""*/ )
	{
		bool result = false;

		if ( parentEntity && 
			parentEntity->getModelObject() &&  
			childPU && 
			childPU->getSceneNode() )
		{
			IEntityAccessory* entityAccessory = MG_NEW IEntityAccessory;
			entityAccessory->isDepositLifeTime = false;
			entityAccessory->isSyncAnimation = false;
			entityAccessory->relativePosition = Vec3(0,0,0);
			entityAccessory->relativeQuaternion = Qua(1,0,0,0);
			entityAccessory->bindBoneName.clear();
			entityAccessory->sceneObject = childPU;

			if ( bindBoxHeightRate > 0 )
			{
				Vec3 pos = parentEntity->getModelObject()->getCenterPosition((Flt)bindBoxHeightRate / 1000.0f, attachToParent);
				entityAccessory->relativePosition = pos;
				result = true;
			}
			else if ( !boneName.empty() )
			{
				entityAccessory->bindBoneName = boneName;
				result = true;
			}

			if ( result )
			{
				if ( attachToParent )
				{
					result = childPU->getScene()->createEntityDynamicAccessorys( parentEntity, childPU, entityAccessory);
				}
				else
				{
					childPU->getSceneNode()->setPosition( entityAccessory->relativePosition );
				}
			}

			MG_DELETE entityAccessory;

		}
		return result;
	}

	//-----------------------------------------------------------------------
	Bool EffectEventUtil::execPUbindPU( PUEffect* childPU, PUEffect* parentPU )
	{
		if (childPU && parentPU)
		{
			MGSceneNode* parentNode = parentPU->getSceneNode();
			MGSceneNode* childNode = childPU->getSceneNode();
		
			childPU->attachOtherSceneNode(parentNode);

			Vec3 pos;
			parentNode->getPosition(pos);
			childNode->setPosition(pos);

			return true;
		}
		else
			return false;
	}
}