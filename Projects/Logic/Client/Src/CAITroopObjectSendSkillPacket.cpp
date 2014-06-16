/******************************************************************************/
#include "stdafx.h"
#include "CAITroopObjectSendSkillPacket.h"
#include "CSkillObject.h"
#include "SkillBaseInfo.h"
#include "SkillNetPacketProcesser.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAITroopObjectSendSkillPacket::STATE_NAME = "CAITroopObjectSendSkillPacket";

	//--------------------------------------------------------------------------
	CAITroopObjectSendSkillPacket::CAITroopObjectSendSkillPacket()
		:LinedStateObject(STATE_NAME)
		,mIsSendPacket(true)
		,mIntervalTime(0)
	{

	}

	//--------------------------------------------------------------------------
	CAITroopObjectSendSkillPacket::~CAITroopObjectSendSkillPacket()
	{

	}

	//-----------------------------------------------------------------------
	void CAITroopObjectSendSkillPacket::update( Flt delta )
	{

		if(mSendSkillList.size() > 0)
		{
			mIntervalTime += delta;
		}

		if(mIntervalTime >= 2 && mIsSendPacket == true)
		{
			sendSkillPacket();
			mIntervalTime = 0;
			mIsSendPacket = false;
		}

	}

	//-----------------------------------------------------------------------
	Bool CAITroopObjectSendSkillPacket::isFinished()
	{
		return false;
	}

	//-----------------------------------------------------------------------
	void CAITroopObjectSendSkillPacket::onEnter()
	{
		UInt a = 0;
	}

	//-----------------------------------------------------------------------
	void CAITroopObjectSendSkillPacket::onLeave()
	{
		UInt a = 0;
	}

	//-----------------------------------------------------------------------
	void CAITroopObjectSendSkillPacket::addSendSkill(UInt soldierId, CSkillObject *skillObject)
	{
		std::map<UInt, CSkillObject*>::iterator it = mSendSkillList.find(soldierId);

		if(it == mSendSkillList.end() && mIsSendPacket == false)
		{
			return;
		}
		else if(it != mSendSkillList.end() && mIsSendPacket == false)
		{
			sendSkillPacket();
			mSendSkillList.clear();
			mIsSendPacket = true;
			mIntervalTime = 0;
		}


		mSendSkillList[soldierId] = skillObject;
	}

	//-----------------------------------------------------------------------
	void CAITroopObjectSendSkillPacket::sendSkillPacket()
	{
		SkillInfo* skillInfo = NULL;
		for(std::map<UInt, CSkillObject*>::iterator it = mSendSkillList.begin(); it != mSendSkillList.end(); ++it)
		{
			if(it == mSendSkillList.begin())
			{
				skillInfo = it->second->getSkillInfo();
			}
			if(skillInfo->skillType == SKT_LONGRANGEGENERAL || skillInfo->skillType == SKT_SHORTRANGEGENERAL)
			{
				SkillNetPacketProcesser::getInstance().sendTroopInjectSkillRequestPacketToPackBuffer(it->second);
			}
			else
			{
				SkillNetPacketProcesser::getInstance().sendTroopClantSkillRequestPacketToPackBuffer(it->second);
			}

		}
	}


}