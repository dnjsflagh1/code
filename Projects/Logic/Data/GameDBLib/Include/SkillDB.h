/******************************************************************************/
#ifndef _SKILLDB_H_
#define _SKILLDB_H_
/******************************************************************************/

#define  SKILL_TABLE_NAME	"skill_info"
#include "CommonGameDefine.h"
/******************************************************************************/
#include "SkillObject.h"
/******************************************************************************/
namespace MG
{
	class SkillDBOp
	{
	public:
		static Bool checkOrCreateSkillTable( DBDriver& driver );
		static Bool createSkill( DBDriver& driver, U64 characterId, std::vector<IdType> skillList );
		//static Bool insertSkill( DBDriver& driver, U64 characterId, SkillData skillData );
		static Bool updateSkill( DBDriver& driver, U64 characterId, IdType skillId );
		static Bool getSkillsDataMap( DBDriver& driver, U64 characterId, std::vector<IdType>& skillList);
        static void	analysisSkillData( Str skillStr, std::vector<IdType>& skillList);

	private:
		static void	insertSkillData( std::vector<IdType>& skillList, IdType skillId );
		static Str8	composeSkillString( std::vector<IdType>& skillList );

	};
}
/******************************************************************************/
#endif  
/******************************************************************************/