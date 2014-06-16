//*********************************************************************************************************
#include "stdafx.h"
#include "SCDManager.h"
#include "SPlayer.h"
#include "SCharacter.h"
//*********************************************************************************************************
namespace MG
{
	SCDManager::SCDManager(CD_MASTER_TYPE type, SCharacter* parent)
		:mParent(parent)
		,mType(type)
	{
	}
	//--------------------------------------------------------------------------------------
	SCDManager::~SCDManager()
	{
		clear();
	}
	//--------------------------------------------------------------------------------------
	void SCDManager::init()
	{
		
	}
	//--------------------------------------------------------------------------------------
	MG::Bool SCDManager::checkCD( CD_MASTER_TYPE type, U32 cdid )
	{
		const CDTempInfo* pCDTempInfo = CDTemplate::getInstance().getCDTempInfo(cdid);
		if ( pCDTempInfo == NULL )
			return false;
		if ( pCDTempInfo->SaveEntityType == mType )
			return mCDTimer.ifGoing(cdid);
		else if (pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CLAN)
		{
			if ( mParent )
			{
				SPlayer* tempSPlayer = NULL;//mParent->getOwnerPlayer();
				return tempSPlayer->getSCDManager()->checkCD(type, cdid);
			}
		}
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CITY )
		{
			;
		}
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_FROCE )
		{
			;
		}

		return false;
	}
	//--------------------------------------------------------------------------------------
	void SCDManager::addCD( CD_MASTER_TYPE type, U32 cdid, U32 liveTime, U32 totalTime )
	{
		const CDTempInfo* pCDTempInfo = CDTemplate::getInstance().getCDTempInfo(cdid);
		if ( pCDTempInfo == NULL )
			return ;
		if ( pCDTempInfo->SaveEntityType == mType )
			mCDTimer.addTimer(cdid, liveTime, totalTime);
		else if (pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CLAN)
		{
			if ( mParent )
			{
				SPlayer* tempSPlayer = NULL;//mParent->getOwnerPlayer();
				tempSPlayer->getSCDManager()->addCD(type, cdid, liveTime, totalTime);
			}
		}
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CITY )
		{
			;
		}
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_FROCE )
		{
			;
		}

	}
	//--------------------------------------------------------------------------------------
	void SCDManager::removeCD( CD_MASTER_TYPE type, U32 cdid )
	{
		const CDTempInfo* pCDTempInfo = CDTemplate::getInstance().getCDTempInfo(cdid);
		if ( pCDTempInfo == NULL )
			return ;
		if ( pCDTempInfo->SaveEntityType == mType )
			 mCDTimer.removeTimer(cdid);
		else if (pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CLAN)
		{
			if ( mParent )
			{
				SPlayer* tempSPlayer = NULL;//mParent->getOwnerPlayer();
				tempSPlayer->getSCDManager()->removeCD(type, cdid);
			}
		}
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CITY )
		{
			;
		}
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_FROCE )
		{
			;
		}

	}
	//--------------------------------------------------------------------------------------
	void SCDManager::removeGroupCD( CD_MASTER_TYPE type, U32 cdGroupId )
	{
		const CDTempInfo* pCDTempInfo = CDTemplate::getInstance().getCDTempInfo(cdGroupId);
		if ( pCDTempInfo == NULL )
			return ;
		if ( pCDTempInfo->SaveEntityType == mType )
			mCDTimer.removeGroupTimer(cdGroupId);
		else if (pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CLAN)
		{
			if ( mParent )
			{
				SPlayer* tempSPlayer = NULL;//mParent->getOwnerPlayer();
				tempSPlayer->getSCDManager()->removeGroupCD(type, cdGroupId);
			}
		}
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CITY )
		{
			;
		}
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_FROCE )
		{
			;
		}

	}
	//--------------------------------------------------------------------------------------
	void SCDManager::clear()
	{
	}
}