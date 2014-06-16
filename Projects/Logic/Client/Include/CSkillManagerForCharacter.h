/******************************************************************************/
#ifndef _CSKILLMANAGERFORCHARACTER_H_
#define _CSKILLMANAGERFORCHARACTER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "SkillManagerForCharacter.h"
#include "CSkillObject.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //角色所属的技能管理器
    /******************************************************************************/
	class CSkillManagerForCharacter : public SkillManagerForCharacter
	{
	public:
		CSkillManagerForCharacter( CCharacterSceneEntity* character );
		virtual ~CSkillManagerForCharacter();

    public:
        CCharacterSceneEntity*  getCharacterEntity();

    public:
        //创建一个技能对象
        virtual CSkillObject*   createSkillObject(IdType id);
		
    private:


	};
}

#endif