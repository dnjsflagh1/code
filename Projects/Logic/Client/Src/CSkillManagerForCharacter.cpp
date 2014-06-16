/******************************************************************************/
#include "stdafx.h"
#include "CSkillManagerForCharacter.h"
#include "CLuaSkillSystem.h"
#include "CCharacterSceneEntity.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------
    CSkillManagerForCharacter::CSkillManagerForCharacter( CCharacterSceneEntity* character )
        :SkillManagerForCharacter( character )
    {

    }

    //-----------------------------------------------------------------------
    CSkillManagerForCharacter::~CSkillManagerForCharacter()
    {
        
    }

    //-----------------------------------------------------------------------
    CSkillObject* CSkillManagerForCharacter::createSkillObject(IdType id)
    {
        SkillBaseInfo* skillBaseInfo = CLuaSkillSystem::getInstance().getSkillBaseInfo( id );
		CCharacterSceneEntity* character = getCharacterEntity();

		if(skillBaseInfo && character)
		{
			CSkillObject* skillObject = MG_NEW CSkillObject(character);
			skillObject->setBaseInfo(skillBaseInfo);
			return skillObject;
		}
		
		return NULL;
    }
    //-----------------------------------------------------------------------
    CCharacterSceneEntity* CSkillManagerForCharacter::getCharacterEntity()
    {
        return dynamic_cast<CCharacterSceneEntity*>( SkillManagerForCharacter::getCharacter() );
    }
}