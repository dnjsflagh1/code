//*********************************************************************************************************
#include "stdafx.h"
#include "LevelManager.h"
#include "CharacterLvlTemplate.h"
#include "GameJudge.h"
#include "SCharacter.h"
#include "SClan.h"
#include "SPlayerCharacter.h"
//*********************************************************************************************************
namespace MG
{
	Bool LevelManager::addExp( SCharacter* pCCharacter, Byte expType, U32 expNum, Bool& isUp )
	{
		if ( pCCharacter->isDead() ) return false;

		U32 tempLevel;
		U32 tempCurExp;

		getLevelAndCurExp(pCCharacter, expType, tempLevel, tempCurExp);

		const CharLvlInfo* pCharLvlInfo = CharacterLvlTemplate::getInstance().getCharLvlInfo((CHAR_LVL_USETYPE)expType, tempLevel+1);
		if (NULL == pCharLvlInfo)
		{
			//满级了
			return false;
		}
		if ( 
				expNum + tempCurExp  >=  pCharLvlInfo->SpendExp  
/*				&& 
				GameJudge::getInstance().checkGameJudge(
					((*SPlayerCharacter)pCCharacter)->setParentClan(),
					pCCharacter,
					pCharLvlInfo->ClanJudgeid,
					pCharLvlInfo->CharacterJudgeid
				)*/ 
			)
		{
			isUp = true;
			pCCharacter->setLevel(tempLevel +1);
			setExp(pCCharacter, expType, 0);
			expNum -= (pCharLvlInfo->SpendExp - tempCurExp);

			addExp(pCCharacter, expType, expNum, isUp);
			pCCharacter->calAttr(false);
			//设置最多血量
			pCCharacter->setMax_HpSpMp();
		}
		else
		{
			if ( expNum + tempCurExp  >=  pCharLvlInfo->SpendExp )
				tempCurExp = pCharLvlInfo->SpendExp;
			else
				tempCurExp += expNum;
			setExp(pCCharacter, expType, tempCurExp);
			
		}
	}
	//-------------------------------------------------------------------------------------------------------
	void LevelManager::getLevelAndCurExp( SCharacter* pCCharacter, Byte expType, U32& level, U32& curExp )
	{              
		switch (expType)
		{
		case CHAR_LVL_USETYPE_CHAR_LVL:		//～角色等级
			{
				SPlayerCharacter* pCPlayerCharacter = (SPlayerCharacter*)pCCharacter;
				level = pCPlayerCharacter->getData()->mLevel;
				curExp = pCPlayerCharacter->getData()->charExp1;
			}
			break;
		case CHAR_LVL_USETYPE_CHAR_TRUN:	
			break;
		case CHAR_LVL_USETYPE_CHAR_SKILL:	
			break;
		case CHAR_LVL_USETYPE_CHAR_SPARE:	
			break;
		case CHAR_LVL_USETYPE_CLAN:	
			break;
		case CHAR_LVL_USETYPE_CLAN_POS:	
			break;
		case CHAR_LVL_USETYPE_CLAN_FEATS:	
			break;
		case CHAR_LVL_USETYPE_CLAN_SPARE:	
			break;	
		case CHAR_LVL_USETYPE_AYM_LVL:	
			break;
		case CHAR_LVL_USETYPE_AYM_SPARE:	
			break;		
		case CHAR_LVL_USETYPE_BUILD_LVL:	
			break;
		case CHAR_LVL_USETYPE_BUILD_SPARE:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE1:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE2:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE3:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE4:	
			break;	
		}
	}
	//-------------------------------------------------------------------------------------------------------
	void LevelManager::setExp( SCharacter* pCCharacter, Byte expType, U32 expNum )
	{
		switch (expType)
		{
		case CHAR_LVL_USETYPE_CHAR_LVL:		//～角色等级
			{
				SPlayerCharacter* pCPlayerCharacter = (SPlayerCharacter*)pCCharacter;
				pCPlayerCharacter->getData()->charExp1 = expNum;
			}
			break;
		case CHAR_LVL_USETYPE_CHAR_TRUN:	
			break;
		case CHAR_LVL_USETYPE_CHAR_SKILL:	
			break;
		case CHAR_LVL_USETYPE_CHAR_SPARE:	
			break;
		case CHAR_LVL_USETYPE_CLAN:	
			break;
		case CHAR_LVL_USETYPE_CLAN_POS:	
			break;
		case CHAR_LVL_USETYPE_CLAN_FEATS:	
			break;
		case CHAR_LVL_USETYPE_CLAN_SPARE:	
			break;	
		case CHAR_LVL_USETYPE_AYM_LVL:	
			break;
		case CHAR_LVL_USETYPE_AYM_SPARE:	
			break;		
		case CHAR_LVL_USETYPE_BUILD_LVL:	
			break;
		case CHAR_LVL_USETYPE_BUILD_SPARE:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE1:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE2:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE3:	
			break;
		case CHAR_LVL_USETYPE_OTHER_SPARE4:	
			break;	
		}
	}
}