/******************************************************************************/
#ifndef _SSKILLOWNMANAGER_H_
#define _SSKILLOWNMANAGER_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SkillOwnManager.h"

/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//��ɫ�����ļ��ܹ�����
	/******************************************************************************/

	class SSkillOwnManager : public SkillOwnManager
	{
	public:
		SSkillOwnManager( SCharacter* character );
		virtual ~SSkillOwnManager();

	public:
		void                            getDefultSkill();
		void                            getDBSkill();

	protected:
		void                            getTempSkill(vector<IdType>& tempVSkillData, const CharacterTempInfo* pTempInfo);
		void							addOwnerSkill(std::vector<IdType> skillList);

	};
}


#endif