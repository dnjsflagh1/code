/******************************************************************************/
#include "stdafx.h"
#include "SimplePlayerCharacter.h"
#include "LoginNetPacket.h"
#include "ClientMain.h"
#include "IEntity.h"

#include "PlayerCharacterData.h"

/******************************************************************************/

namespace MG
{
     
	//--------------------------------------------------------------------------------
	void SimplePlayerCharacter::init( U32 tempid[] )
	{
		PlayerCharacterData tempData;
		for (U32 i = 0;i<SPCHARACTER_COUNT;i++)
		{
			tempData.mCharacterTemplateID = tempid[i];
             mPlayerCharacter[i].init(&tempData);

			 AttributeSet* pAttributeSet = mPlayerCharacter[i].getAttributeSet();
			 mPlayerCharacterData[i].mPower           		 = pAttributeSet->getFanalValue(ATTR_ID_Talent1);
			 mPlayerCharacterData[i].mAgile           		 = pAttributeSet->getFanalValue(ATTR_ID_Talent2);
			 mPlayerCharacterData[i].mIntellect       		 = pAttributeSet->getFanalValue(ATTR_ID_Talent3);
			 mPlayerCharacterData[i].mSpirt           		 = pAttributeSet->getFanalValue(ATTR_ID_Talent4);
			 mPlayerCharacterData[i].mPhysicalStrength		 = pAttributeSet->getFanalValue(ATTR_ID_Talent5);
			 mPlayerCharacterData[i].mEnergy          		 = pAttributeSet->getFanalValue(ATTR_ID_Talent6);
		}
	}

	//--------------------------------------------------------------------------------
	
}