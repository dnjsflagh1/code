/******************************************************************************/
#ifndef _SSKILLOWNMANAGER_H_
#define _SSKILLOWNMANAGER_H_
/******************************************************************************/
#include "MapServerPreqs.h"
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
		void							calAttrAll();
		//�������Ե��ۼ�
		void							calAttrAllBase();
		void							addOwnerSkill( IdType skillId );

		///////////////////////////////////////////////////////////////////////////

		Flt								getMinSkillAttackDis();

	protected:
		void                            getTempSkill( std::vector<IdType>& tempVSkillData, const CharacterTempInfo* pTempInfo );
		void							addOwnerSkill( std::vector<IdType> skillList );
		void							calAttr( IdType skillId );
		void							getAttrMap(std::map<U32, Flt>* pAttrMap, U32 skillId);

	protected:
		Flt								mMinSkillAttackDis;

	};
}


#endif