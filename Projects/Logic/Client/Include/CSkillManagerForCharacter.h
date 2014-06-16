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
    //��ɫ�����ļ��ܹ�����
    /******************************************************************************/
	class CSkillManagerForCharacter : public SkillManagerForCharacter
	{
	public:
		CSkillManagerForCharacter( CCharacterSceneEntity* character );
		virtual ~CSkillManagerForCharacter();

    public:
        CCharacterSceneEntity*  getCharacterEntity();

    public:
        //����һ�����ܶ���
        virtual CSkillObject*   createSkillObject(IdType id);
		
    private:


	};
}

#endif