/******************************************************************************/
#include "stdafx.h"
#include "SFightHeartBeatManager.h"
#include "SCharacter.h"
#include "FightManager.h"
#include "BaseAIGroupTemplate.h"
#include "SFightMainManager.h"
#include "SFightManager.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	SFightHeartBeatManager::SFightHeartBeatManager( SCharacter* owner )
		:mFightManager(MG_NEW SFightManager(owner))
		,mOwner(owner)
		,mPursueRadius(0)
	{
	}

	//-----------------------------------------------------------------------------
	SFightHeartBeatManager::~SFightHeartBeatManager()
	{
		SFightMainManager::getInstance().delAllFightInfo(mOwner);
		MG_SAFE_DELETE(mFightManager);
	}

	//-----------------------------------------------------------------------------

	void SFightHeartBeatManager::init()
	{
		BaseAIGroup* baseAIGroup = (BaseAIGroup*)mOwner->getBaseAIGroup();
		if(!baseAIGroup)
		{	
			return;
		}

		std::map<BaseAIType, BaseAIInfo*>::iterator it = baseAIGroup->aiBaseAIInfoList[BAH_FIGHT].find(BAT_PURSUE);
		if(it != baseAIGroup->aiBaseAIInfoList[BAH_FIGHT].end())
		{
			mPursueRadius = (Flt)it->second->paramList[0];
		}
	}

	//-----------------------------------------------------------------------
	SFightManager* SFightHeartBeatManager::getFightManager()
	{
		return mFightManager;
	}

	//-----------------------------------------------------------------------
	void SFightHeartBeatManager::update()
	{
		IdType currTime = MGTimeOp::getCurrTick();
		IdType intervalTime = 0;

		Flt dis = 0;
		Vec3 pointPos = mFightManager->getEnterFightPos();

		SFightManager* fightManager = NULL;
	
		std::map<IdType, FightInfo>* fightInfoList = mFightManager->getFightInfoList();
		SCharacter* fightOtherCharacter = NULL;
		Vec3 fightOtherPos;

		IdType fightInfoID = 0;

		for(std::map<IdType, FightInfo>::iterator it = fightInfoList->begin(); it != fightInfoList->end();)
		{
			if(!it->second.isInitiative)
			{
				++it;
				continue;
			}

			intervalTime = currTime - it->second.endTime;
			fightOtherCharacter = (SCharacter*)it->second.fightObject;
			fightOtherPos = fightOtherCharacter->getPos();
			
			dis = (pointPos - fightOtherPos).length();

			if(intervalTime >= FIGHTINFOINTERVALTIME || (mPursueRadius != 0 && dis > mPursueRadius))
			{
				fightInfoID = it->second.fightID;
				it = fightInfoList->erase(it);

				if(fightInfoList->size() == 0)
				{
					mFightManager->notifyEndFight(mOwner);
				}

				fightManager = fightOtherCharacter->getFightManager();
				if(!fightManager)
				{
					continue;
				}

				fightManager->delFightInfo(fightInfoID);
			}
			else
			{
				++it;
			}
		}
	}


}