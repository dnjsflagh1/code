
/******************************************************************************/
#include "stdafx.h"
#include "CSkillObject.h"
#include "CLuaSkillSystem.h"
#include "CSkillEffectSystem.h"
#include "CPlayer.h"
#include "SkillNetPacketProcesser.h"
#include "CCharacterSceneEntity.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "SkillBaseInfo.h"
#include "CSceneManager.h"
#include "CGoUpAndDownSkillEffect.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    CSkillObject::CSkillObject( CCharacterSceneEntity* owner )
        : mOwner(owner)
		,mIsExecScript(true)
		,mIsEndBehind(true)
    {
		mOwnerType = owner->getType();
		if(mOwnerType != GOT_SOLDIER)
		{
			mOwnerId = owner->getID();
			mOwnerIndex = 0;
		}
		else
		{
			mOwnerId = ((CTroopSoldierEntity*)owner)->getTroopEntity()->getID();
			mOwnerIndex = owner->getID();
		}
    }

    //-----------------------------------------------------------------------
    CSkillObject::~CSkillObject()
    {

    }

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillStartClantLogic()
	{

	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillClantUpdateLogic()
	{

	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillEndClantLogic()
	{

	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillStartClantScript()
	{
		CLuaSkillSystem::getInstance().execClientStartClantScript( this );
	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillClantUpdateScript()
	{
		CLuaSkillSystem::getInstance().execClientUpdateClantScript( this, mCurrTiming );
	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillEndClantScript()
	{
		CLuaSkillSystem::getInstance().execClientEndClantScript( this );
	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillStartFrontLogic()
	{

	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillEndFrontLogic()
	{

	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillStartBehindLogic()
	{
		//mOwner->getActionStateManager().setIsPush(false);
		//mOwner->getAIStateManager().setIsPush(false);
	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillEndBehindLogic()
	{
		//mOwner->getActionStateManager().setIsPush(true);
		//mOwner->getAIStateManager().setIsPush(true);
	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillStartInjectLogic()
	{

	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillInjectUpdateLogic()
	{

	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillEndInjectLogic()
	{

	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillStartFrontScript()
	{
		CLuaSkillSystem::getInstance().execClientStartFrontScript( this );
	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillEndFrontScript()
	{
		CLuaSkillSystem::getInstance().execClientEndFrontScript( this );
	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillStartBehindScript()
	{
		CLuaSkillSystem::getInstance().execClientStartBehindScript( this );
	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillEndBehindScript()
	{
		CLuaSkillSystem::getInstance().execClientEndBehindScript( this );
	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillStartInjectScript()
	{
		CLuaSkillSystem::getInstance().execClientStartInjectScript( this );
	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillInjectUpdateScript()
	{
		CLuaSkillSystem::getInstance().execClientUpdateInjectScript( this, mCurrTiming );
	}

	//-----------------------------------------------------------------------
	void CSkillObject::execClientSkillEndInjectScript()
	{
		CLuaSkillSystem::getInstance().execClientEndInjectScript( this );
	}


	//-----------------------------------------------------------------------
	void CSkillObject::setIsExecScript( Bool isExecScript )
	{
		mIsExecScript = isExecScript; 
	}

	//-----------------------------------------------------------------------
	void CSkillObject::startInject( Bool isUpdate )
	{
		SkillObject::startInject(isUpdate);

		Flt attackFrontTime = (Flt)((InitiativeSkillBasicInfo*)mSkillInfo->skillInfo)->attackFrontTime /*/ 1000*/;

		setStopUpdateTime(attackFrontTime);

		onSkillStartFront();
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillFinished()
	{
		SkillObject::onSkillFinished();
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillEnd()
	{
		SkillObject::onSkillEnd();

		onSkillEndBehind();
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillStartClant()
	{
		if(mIsExecScript)
		{
			execClientSkillStartClantScript();
		}
		else
		{
			execClientSkillStartClantLogic();
		}
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillUpdateClant( Flt delta )
	{
		if(mIsExecScript)
		{
			execClientSkillClantUpdateScript();
		}
		else
		{
			execClientSkillClantUpdateLogic();
		}
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillEndClant()
	{
		if(mIsExecScript)
		{
			execClientSkillEndClantScript();
		}
		else
		{
			execClientSkillEndClantLogic();
		}
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillClantFinished()
	{

	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillStartFront()
	{
		mIsEndBehind = true;

		if(mIsExecScript)
		{
			execClientSkillStartFrontScript();
		}
		else
		{
			execClientSkillStartFrontLogic();
		}
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillEndFront()
	{
		if(mIsExecScript)
		{
			execClientSkillEndFrontScript();
		}
		else
		{
			execClientSkillEndFrontLogic();
		}
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillStartBehind()
	{
		mIsEndBehind = false;
		//暂时只执行逻辑
		//if(mIsExecScript)
		//{
		//	execClientSkillStartBehindScript();
		//}
		//else
		//{
			execClientSkillStartBehindLogic();
		//}
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillEndBehind()
	{
		//暂时只执行逻辑
		//if(mIsExecScript)
		//{
		//	execClientSkillEndBehindScript();
		//}
		//else
		//{
			execClientSkillEndBehindLogic();
		//}

		mIsEndBehind = true;
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillStartInject()
	{
		if(mIsExecScript)
		{
			execClientSkillStartInjectScript();
		}
		else
		{
			execClientSkillStartInjectLogic();
		} 
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillUpdateInject( Flt delta )
	{
		if(mIsExecScript)
		{
			execClientSkillInjectUpdateScript();
		}
		else
		{
			execClientSkillInjectUpdateLogic();
		}
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillEndInject()
	{
		if(mIsExecScript)
		{
			execClientSkillEndInjectScript();
		}
		else
		{
			execClientSkillEndInjectLogic();
		} 
	}

	//-----------------------------------------------------------------------
	void CSkillObject::onSkillInjectFinished()
	{
		Flt attackBehindTime = (Flt)((InitiativeSkillBasicInfo*)mSkillInfo->skillInfo)->attackBehindTime /*/ 1000*/;

		setStopUpdateTime(attackBehindTime);

		onSkillStartBehind();
	}

	//-----------------------------------------------------------------------
	Bool CSkillObject::getIsEndBehind()
	{
		return mIsEndBehind;
	}

	//-----------------------------------------------------------------------
	CCharacterSceneEntity* CSkillObject::getOwner()
	{
		return mOwner;
	}


}