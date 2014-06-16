/******************************************************************************/
#include "stdafx.h"
#include "CAIEntitySelectSkill.h"
#include "CSceneManager.h"
#include "CCharacterSceneEntity.h"
#include "SkillBaseInfo.h"
#include "CSkillUseManager.h"
#include "SkillNetPacketProcesser.h"
#include "SkillInfoList.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "CAIManager.h"
#include "ClientMain.h"
#include "CAITroopObjectSendSkillPacket.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "CharacterSkillTempLate.h"
#include "SkillBaseInfo.h"
#include "CPlayer.h"
#include "CSkillOwnManager.h"
#include "CharacterList.h"
#include "CAIController.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAIEntitySelectSkill::STATE_NAME = "CAIEntitySelectSkill";

	//--------------------------------------------------------------------------
	CAIEntitySelectSkill::CAIEntitySelectSkill( CCharacterSceneEntity* characterSceneEntity )
		:LinedStateObject(STATE_NAME)
		,CAI(characterSceneEntity)
		,mMaxRatio(0)

	{
		mAIType = AIT_SELECTSKILL;
	}

	//--------------------------------------------------------------------------
	CAIEntitySelectSkill::~CAIEntitySelectSkill()
	{

	}

	//-----------------------------------------------------------------------
	void CAIEntitySelectSkill::update( Flt delta )
	{
	}				 

	//-----------------------------------------------------------------------
	Bool CAIEntitySelectSkill::isFinished()
	{
		return true;
	}

	//-----------------------------------------------------------------------
	void CAIEntitySelectSkill::onEnter()
	{
		UInt skillId = 0;

		if(mMaxRatio == 0)
		{
			notifySelectSkill(skillId);
			return;
		}

		UInt ratioVal = MGRandom::getInstance().rand_ab_One(0, mMaxRatio);	

		for(UInt i = 0; i < mSkillIntervalList.size(); ++i)
		{
			if(ratioVal <= mSkillIntervalList[i].maxVal && ratioVal >= mSkillIntervalList[i].minVal)
			{
				skillId = mSkillIntervalList[i].skillId;
				break;
			}
		}

		if(skillId == 0 && mSkillIntervalList.size() != 0)
		{
			skillId = mSkillIntervalList[0].skillId;
		}

		notifySelectSkill(skillId);
	}

	//-----------------------------------------------------------------------
	void CAIEntitySelectSkill::onLeave()
	{
	}

	void CAIEntitySelectSkill::setSelectSkill( std::vector<SkillRatio>& skillRatioList )
	{
		UInt startIntervalVal = 0;
		SkillInterval skillInterval;

		for(UInt i = 0; i < skillRatioList.size(); ++i)
		{
			skillInterval.skillId = skillRatioList[i].skillId;
			skillInterval.minVal = startIntervalVal;
			skillInterval.maxVal = skillRatioList[i].ratioVal;
			startIntervalVal = skillInterval.maxVal + 1;

			mMaxRatio += skillRatioList[i].ratioVal;

			mSkillIntervalList.push_back(skillInterval);
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntitySelectSkill::notifySelectSkill( UInt skillId )
	{
		if(mAIListener)
		{
			mAIListener->onSelectSkillResult(skillId);
		}
	}
}