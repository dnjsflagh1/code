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
	//角色所属的技能管理器
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
		//计算属性的累加
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