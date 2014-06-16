
/******************************************************************************/

#include "stdafx.h"
#include "SMonster.h"
#include "MonsterData.h"
#include "InstanceListCsv.h"
#include "SPVEInstance.h"
#include "SPlayer.h"
#include "SPlayerCharacter.h"
#include "DropItemManager.h"
#include "SRegionNetPacketProcesser.h"
#include "SMonsterNetPacketProcesser.h"
#include "SAIController.h"
#include "BaseAIGroupTemplate.h"
#include "FightAiGroupTemplate.h"
#include "SActionManager.h"
#include "SSkillOwnManager.h"
#include "SBuffManager.h"
#include "SGameObjectFactory.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	void SMonsterPtr::destroy(void)
	{
		mFactory->destroySMonsterPtr( *this );
	}

	//-----------------------------------------------------------------------------
	SMonster::SMonster()
		:SCharacter(GOT_MONSTER, MG_NEW MonsterData())
		//,mAIController(MG_NEW SAIController(this))
		,mFightAIGroup(NULL)
	{
	}

	//-----------------------------------------------------------------------------
	SMonster::~SMonster()
	{
	}

	//-----------------------------------------------------------------------------
	//void SMonster::init()
	//{
	//	//SCharacter::init();

	//	const CharacterTempInfo* characterTempInfo = getCharacterTempInfo();
	//	if(!characterTempInfo)
	//	{
	//		return;
	//	}

	//	mFightAIGroup = FightAIGroupTemplate::getInstance().getFightAIGroup(characterTempInfo->getAIFightGroupId());
	//	mHeartBeatManager->addHeartBeatObject(mAIController);

	//	mAIController->Init();

	//	SRegionObjectBase* regionObjectBase = getCurrentRegionObject();
	//	if(!regionObjectBase)
	//	{
	//		return;
	//	}

	//	if(regionObjectBase->getGameType() == GameType_Rpg)
	//	{
	//		addOrUpdateInSceneGrid();
	//	}
	//}

	//-----------------------------------------------------------------------------
	MonsterData* SMonster::getMonsterData()
	{
		return (MonsterData*)(getCharacterData());
	}

	//-----------------------------------------------------------------------------
	void SMonster::dead(SCharacter* murderer)
	{
#if 0
		SCharacter::dead(murderer);

		//10秒后复活
		setAliveTime(20);

		SRegionObjectBase* myRegion = this->getCurrentRegionObject();
		DYNAMIC_ASSERT(NULL != myRegion);

		//怪物死后掉落物品
		U32 randItemId = getCharacterTempInfo()->getMonsterItemGroupId();
		myRegion->getDropItemManager()->handleDropItemMonster(randItemId, getCurrentRegionObject(), getPos(), murderer);
       
		
		//将怪物和杀死的它的玩家信息传递给frontserver做处理 如：任务
		SPlayerCharacter* killerTemp = (SPlayerCharacter*)murderer;
		SPlayerIdentifyInfoInPlayerCharacter* playerIdentify = killerTemp->getPlayerIdentifyInfo();

		MonsterData* monsterData = getMonsterData();
		DYNAMIC_ASSERT(monsterData);
		MonsterIdType monsterId  = monsterData->mCharacterTemplateID;
		PlayerCharacterIdType playerCharacterId = killerTemp->getID();
		PlayerIdType  playerId =  playerIdentify->accountId;
		NetIdType netFrontServerID = playerIdentify->frontServerId;
		NetIdType netClientInFrontId =  playerIdentify->clientNetIdInFrontServer;
		SMonsterNetPacketProcesser::getInstance().sendMonsterBeKilledByPlayerCharacter(netFrontServerID,monsterId,playerCharacterId,playerId,netClientInFrontId);



		//判断是否结束副本
		SInstanceRegion* myInstanceRegion = getCurrentRealRegionObject();
		DYNAMIC_ASSERT(NULL != myInstanceRegion);

		//DYNAMIC_ASSERT(InstanceType_PVE == myInstanceRegion->getInstanceType());

		SInstanceBase* instanceBase = myInstanceRegion->getNewInstanceBase();
		if (InstanceType_PVE != myInstanceRegion->getInstanceType())
		{
			return;
		}

		SPVEInstance* pveInstance = (SPVEInstance*)myInstanceRegion->getNewInstanceBase();
		if (getCharacterData()->mCharacterTemplateID == pveInstance->getFinishCharacter())
		{
			//此怪物死了，副本结束
			//DYNAMIC_ASSERT(murderer->getType() == GOT_PLAYERCHARACTER);
			SPlayerCharacter* killer = (SPlayerCharacter*)murderer;
			Int groupItemId = pveInstance->getPVECsv()->itemGroupId;
			myRegion->getDropItemManager()->handleRewardItemInRegion(myRegion, groupItemId);
			//获取奖励接口, 并在FrontServer负责通知客户端 获得哪些物品
			//sitem.getprize(pveInstance->);
		}
#endif
	}

	//-----------------------------------------------------------------------------
	void SMonster::print()
	{
		
	}

	//-----------------------------------------------------------------------------
	void SMonster::setAlive(AliveType aliveType)
	{
#if 0
		SCharacter::setAlive(aliveType);

		setMax_HpSpMp();

		SRegionObjectBase* regionObj = getCurrentRegionObject();
		if (NULL == regionObj)
		{
			DYNAMIC_ASSERT(0);
			return;
		}
	
		setPos(getBirthPos());

		//发送列表
		regionObj->setIsNeedCalcContorlMonsterAI(true);
		regionObj->calcControlMonsterAIByPlayerListAndSendToClient();

		SRegionNetPacketProcesser::getInstance().broadcastMonsterAliveToRegion(this, regionObj);
		

		mAIController->setBirthState();
#endif
	}

	//-----------------------------------------------------------------------------
	void SMonster::moveToPos( Vec3 startMovePos, Vec3 MoveToPos )
	{
		NetVec2 startMovePosdata = startMovePos;
		NetVec2 endMovePosdata = MoveToPos;

		SMonsterNetPacketProcesser::getInstance().broadcastMonsterMove(this, startMovePosdata, endMovePosdata);

		SCharacter::moveToPos(startMovePos, MoveToPos);
	}

	//-----------------------------------------------------------------------------
	void SMonster::instantMoveToPos( Vec3 moveToPos )
	{
		NetVec2 moveToPosdata = moveToPos;

		SMonsterNetPacketProcesser::getInstance().broadcastInstantMonsterMove(this, moveToPos);

		SCharacter::setPos(moveToPos);
	}
	
	//-----------------------------------------------------------------------------
	void SMonster::stopMove()
	{
		LinedStateObject* linedStateObject = mActionManager->getState("SCharacterMoveToAction", false);
		if(linedStateObject)
		{
			SMonsterNetPacketProcesser::getInstance().broadcastMonsterStopMove(this);
		}

		SCharacter::stopMove();
	}

	//--------------------------------------------------------------------------
	const FightAIGroup* SMonster::getFightAIGroup()
	{
		return mFightAIGroup;
	}

	//-----------------------------------------------------------------------
	void SMonster::addFightAITriggerCount( UInt fightAIId )
	{
		mFightAITriggerCountList[fightAIId]++;
	}

	//-----------------------------------------------------------------------
	UInt SMonster::getFightAITriggerCount( UInt fightAIId )
	{
		std::map<UInt, UInt>::iterator it = mFightAITriggerCountList.find(fightAIId);
		if(it == mFightAITriggerCountList.end())
		{
			return 0;
		}

		return it->second;
	}

	//-----------------------------------------------------------------------
	void SMonster::clearFightAITriggerCount()
	{
		mFightAITriggerCountList.clear();
	}

	//-----------------------------------------------------------------------
	SAIController* SMonster::getAIController()
	{
		return mAIController;
	}
	//-----------------------------------------------------------------------
	void SMonster::calAttrOther()
	{
		//计算技能。
		getSkillOwnManager()->calAttrAllBase();
		//计算状态。
		getSBuffManager()->calAttrAllBase();
	}
}