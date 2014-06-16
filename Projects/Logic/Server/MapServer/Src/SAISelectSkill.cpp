/******************************************************************************/
#include "stdafx.h"
#include "SAISelectSkill.h"
#include "SCharacter.h"
#include "SkillBaseInfo.h"
#include "SSkillUseManager.h"
#include "SkillInfoList.h"
#include "ShortRangeGeneralAttackSkillTemplate.h"
#include "LongRangeGeneralAttackSkillTemplate.h"
#include "SingleTargetSkillTemplate.h"
#include "SAIManager.h"
#include "CharacterSkillTempLate.h"
#include "SkillBaseInfo.h"
#include "SSkillOwnManager.h"
#include "CharacterList.h"
#include "SAIController.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str SAISelectSkill::STATE_NAME = "SAISelectSkill";

	//--------------------------------------------------------------------------
	SAISelectSkill::SAISelectSkill( SCharacter* owner )
		:LinedStateObject(STATE_NAME)
		,SAI(owner)
		,mMaxRatio(0)

	{
		mAIType = AIT_SELECTSKILL;
	}

	//--------------------------------------------------------------------------
	SAISelectSkill::~SAISelectSkill()
	{

	}

	//-----------------------------------------------------------------------
	void SAISelectSkill::update( Flt delta )
	{
	}				 

	//-----------------------------------------------------------------------
	Bool SAISelectSkill::isFinished()
	{
		return true;
	}

	//-----------------------------------------------------------------------
	void SAISelectSkill::onEnter()
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
	void SAISelectSkill::onLeave()
	{
	}

	void SAISelectSkill::setSelectSkill( std::vector<SkillRatio>& skillRatioList )
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
	void SAISelectSkill::notifySelectSkill( UInt skillId )
	{
		if(mAIListener)
		{
			mAIListener->onSelectSkillResult(skillId);
		}
	}
}