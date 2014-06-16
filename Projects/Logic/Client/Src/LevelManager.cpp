//*********************************************************************************************************
#include "stdafx.h"
#include "LevelManager.h"
#include "CharacterLvlTemplate.h"
#include "GameJudge.h"
#include "CPlayer.h"
#include "CClan.h"
#include "CCharacter.h"
#include "CPlayerCharacter.h"
#include "UIGenrealPicture.h"
#include "UIClanInfo.h"
#include "MessageManager.h"
//*********************************************************************************************************
namespace MG
{
	void LevelManager::addExp( CCharacter* pCCharacter, Byte expType, U32 expNum )
	{
		U32 tempLevel;
		U32 tempCurExp;

		getLevelAndCurExp(pCCharacter, expType, tempLevel, tempCurExp);

		const CharLvlInfo* pCharLvlInfo = CharacterLvlTemplate::getInstance().getCharLvlInfo((CHAR_LVL_USETYPE)expType, tempLevel+1);
		if ( 
				expNum + tempCurExp  >=  pCharLvlInfo->SpendExp  
				&& 
				GameJudge::getInstance().checkGameJudge(
					CPlayer::getInstance().getActiveClan(),
					NULL,
					pCCharacter,
					pCharLvlInfo->ClanJudgeid,
					pCharLvlInfo->CharacterJudgeid
				) 
			)
		{
			//升级了
			pCCharacter->setLevel(tempLevel +1);
			setExp(pCCharacter, expType, 0);
			expNum -= (pCharLvlInfo->SpendExp - tempCurExp);

			addExp(pCCharacter, expType, expNum);
			pCCharacter->calAttr();
			pCCharacter->setMax_HpSpMp();

			UIGenrealPicture::getInstance().setLV((CPlayerCharacter*)pCCharacter);
			UIGenrealPicture::getInstance().setHp((CPlayerCharacter*)pCCharacter);
			UIGenrealPicture::getInstance().setMp((CPlayerCharacter*)pCCharacter);
			UIGenrealPicture::getInstance().setSp((CPlayerCharacter*)pCCharacter);
			UIClanInfo::getInstance().updateLevel();

			MessageManager::getInstance().addChatMsgForTest("角色升级 level[%d]", pCCharacter->getLevel());
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
	void LevelManager::getLevelAndCurExp( CCharacter* pCCharacter, Byte expType, U32& level, U32& curExp )
	{  
		switch (expType)
		{
		case CHAR_LVL_USETYPE_CHAR_LVL:		//～角色等级
			{
				CPlayerCharacter* pCPlayerCharacter = (CPlayerCharacter*)pCCharacter;
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
	void LevelManager::setExp( CCharacter* pCCharacter, Byte expType, U32 expNum )
	{
		switch (expType)
		{
		case CHAR_LVL_USETYPE_CHAR_LVL:		//～角色等级
			{
				CPlayerCharacter* pCPlayerCharacter = (CPlayerCharacter*)pCCharacter;
				pCPlayerCharacter->getData()->charExp1 = expNum;
				UIClanInfo::getInstance().updateExp();
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