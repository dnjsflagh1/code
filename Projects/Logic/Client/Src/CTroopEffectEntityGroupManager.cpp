/******************************************************************************/
#include "stdafx.h"
#include "CTroopEffectEntityGroupManager.h"
#include "CSceneManager.h"
#include "ClientMain.h"

/******************************************************************************/

#define  CREATE_EFFECTENTITY_NUM 50

namespace MG
{

	//-----------------------------------------------------------------------
	CTroopEffectEntityGroupManager::CTroopEffectEntityGroupManager()
	{

	}

	//-----------------------------------------------------------------------
	CTroopEffectEntityGroupManager::~CTroopEffectEntityGroupManager()
	{
		destroyAllEffectComponent();
	}

	//-----------------------------------------------------------------------
	IEntity* CTroopEffectEntityGroupManager::getEffectComponent(UInt effectID)
	{
		EffectComponentGroup* effectEntityGroup = NULL;
		IEntityGroup* entityGroup = NULL;
		std::map<UInt, EffectComponentGroup*>::iterator it = mEffectComponentGroupList.find(effectID);
		if(it == mEffectComponentGroupList.end())
		{
			effectEntityGroup = MG_NEW EffectComponentGroup;
			entityGroup = createEffectComponentGroup(effectID);
			if(!entityGroup)
			{
				return NULL;
			}

			effectEntityGroup->effectEntityGroupList.push_back(entityGroup);
			mEffectComponentGroupList[effectID] = effectEntityGroup;
		}
		else
		{
			effectEntityGroup = it->second;
		}

		if(!effectEntityGroup)
		{
			return NULL;
		}

		IEntity* entity = getInVisibleEffectComponent(effectID);
		if(entity)
		{
			return entity;
		}

		entityGroup = createEffectComponentGroup(effectID);
		if(!entityGroup)
		{
			return NULL;
		}
		
		effectEntityGroup->effectEntityGroupList.push_back(entityGroup);

		return entityGroup->getEntity(0);
	}

	//-----------------------------------------------------------------------
	IEntity* CTroopEffectEntityGroupManager::getInVisibleEffectComponent(UInt effectID)
	{
		std::map<UInt, EffectComponentGroup*>::iterator it = mEffectComponentGroupList.find(effectID);
		if(it == mEffectComponentGroupList.end())
		{
			return false;
		}

		EffectComponentGroup* effectEntityGroup = it->second;
		if(!effectEntityGroup)
		{
			return false;
		}

		IEntityGroup* entityGroup = NULL;
		IEntity* entity = NULL;
		for(UInt i = 0; i < effectEntityGroup->effectEntityGroupList.size(); ++i)
		{
			entityGroup = effectEntityGroup->effectEntityGroupList[i];
			for(UInt j = 0; j < entityGroup->getEntityNum(); ++j)
			{
				entity = entityGroup->getEntity(j);
				if(!entity || entity->getSceneNode()->getVisible())
				{
					continue;
				}

				return entity;
			}
		}

		return NULL;
	}

	//-----------------------------------------------------------------------
	IEntityGroup* CTroopEffectEntityGroupManager::createEffectComponentGroup(UInt effectID)
	{
		IEntityGroup* entityGroup = ClientMain::getInstance().getScene()->createEntityGroup(effectID, CREATE_EFFECTENTITY_NUM);
		
		IEntity* entity = NULL;
		for(UInt i = 0; i < entityGroup->getEntityNum(); ++i)
		{
			entity = entityGroup->getEntity(i);
			if(!entity)
			{	
				continue;
			}

			entity->getSceneNode()->setVisible(false);
		}

		return entityGroup;
	}

	//-----------------------------------------------------------------------
	void CTroopEffectEntityGroupManager::destroyEffectComponent(UInt effectID, IEntity* entity)
	{
		if(!entity)
		{
			return;
		}

		std::map<UInt, EffectComponentGroup*>::iterator it = mEffectComponentGroupList.find(effectID);
		if(it == mEffectComponentGroupList.end())
		{
			return;
		}

		EffectComponentGroup* effectEntityGroup = it->second;
		if(!effectEntityGroup)
		{
			return;
		}

		IEntityGroup* entityGroup = NULL;
		IEntity* tempEntity = NULL;
		for(UInt i = 0; i < effectEntityGroup->effectEntityGroupList.size(); ++i)
		{
			entityGroup = effectEntityGroup->effectEntityGroupList[i];
			for(UInt j = 0; j < entityGroup->getEntityNum(); ++j)
			{
				tempEntity = entityGroup->getEntity(j);
				if(!tempEntity || tempEntity != entity)
				{
					continue;
				}

				entity->getSceneNode()->setVisible(false);
				return;
			}
		}
	}

	//-----------------------------------------------------------------------
	void CTroopEffectEntityGroupManager::destroyAllEffectComponent()
	{
		EffectComponentGroup* effectEntityGroup = NULL;
		IEntityGroup* entityGroup = NULL;
		for(std::map<UInt, EffectComponentGroup*>::iterator it = mEffectComponentGroupList.begin(); it != mEffectComponentGroupList.end(); ++it)
		{
			effectEntityGroup = it->second;
			if(!effectEntityGroup)
			{
				continue;
			}

			for(UInt i = 0; i < effectEntityGroup->effectEntityGroupList.size(); ++i)
			{
				entityGroup = effectEntityGroup->effectEntityGroupList[i];
				if(!entityGroup)
				{
					ClientMain::getInstance().getScene()->destroyEntityGroup(entityGroup->getName().c_str());
					entityGroup = NULL;
				}
			}

			effectEntityGroup->effectEntityGroupList.clear();
		}

		mEffectComponentGroupList.clear();
	}

}