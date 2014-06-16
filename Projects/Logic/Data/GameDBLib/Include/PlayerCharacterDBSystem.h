/******************************************************************************/
#ifndef _PLAYER_CHARACTER_DB_SYSTEM_H_
#define _PLAYER_CHARACTER_DB_SYSTEM_H_
/******************************************************************************/

#include "CommonGameDefine.h"
/******************************************************************************/
#include "PlayerCharacterData.h"
#include "WorldCorePreqs.h"
#include "BuffData.h"
/******************************************************************************/

#define  CHAR_TABLE_NAME	"player_character_info"


#define 		Account_Id					"Account_Id"
#define 		Clan_id						"Clan_id"
#define 		char_id						"char_id"
#define 		char_name					"char_name"
#define 		char_surname				"char_surname"
#define 		char_template_id			"char_template_id"
#define 		char_cur_age				"char_cur_age"
#define 		char_life_span				"char_life_span"
#define 		char_add_life_span			"char_add_life_span"
#define 		char_cur_lvl				"char_cur_lvl"
#define 		char_cur_exp1				"char_cur_exp1"
#define 		char_cur_exp2				"char_cur_exp2"
#define 		char_cur_exp3				"char_cur_exp3"
#define 		char_cur_hp					"char_cur_hp"
#define 		char_cur_mp					"char_cur_mp"
#define 		char_lineage_num			"char_lineage_num"
#define 		char_art_mash_id_1			"char_art_mash_id_1"
#define 		char_art_mash_id_2			"char_art_mash_id_2"
#define 		char_icon_id				"char_icon_id"
#define 		char_infuence_id			"char_infuence_id"
#define 		char_skill_point_all		"char_skill_point_all"	
#define 		char_no_assign_skill_point	"char_no_assign_skill_point"
#define 		char_state					"char_state"
#define 		char_life_state				"char_life_state"
#define 		char_region_type			"char_region_type"
#define 		char_region_id				"char_region_id"
#define 		char_pos_x 					"char_pos_x"
#define 		char_pos_y 					"char_pos_y"
#define 		char_pos_z 					"char_pos_z"
#define 		char_dir_x 					"char_dir_x"
#define 		char_dir_y 					"char_dir_y"
#define 		char_dir_z 					"char_dir_z"
#define 		char_attr_Id				"char_attr_Id"
#define 		char_attr_add_Id			"char_attr_add_Id"
#define 		char_attr_rand1 			"char_attr_rand1"
#define 		char_attr_rand2 			"char_attr_rand2"
#define 		char_attr_rand3 			"char_attr_rand3"
#define 		char_attr_rand4 			"char_attr_rand4"
#define 		char_attr_rand5 			"char_attr_rand5"
#define 		char_attr_rand6 			"char_attr_rand6"
#define 		char_attr_add_rand1 		"char_attr_add_rand1"
#define 		char_attr_add_rand2 		"char_attr_add_rand2"
#define 		char_attr_add_rand3 		"char_attr_add_rand3"
#define 		char_attr_add_rand4 		"char_attr_add_rand4"
#define 		char_attr_add_rand5 		"char_attr_add_rand5"
#define 		char_attr_add_rand6 		"char_attr_add_rand6"
#define 		char_item					"char_item"
#define 		char_buff					"char_buff"
#define			skill_data					"skill_data"

enum charDBRow
{
		charDBRow_Account_Id				,	
		charDBRow_Clan_id					,	
		charDBRow_char_id					,	
		charDBRow_char_name					,
		charDBRow_char_surname				,
		charDBRow_char_template_id			,
		charDBRow_char_cur_age				,
		charDBRow_char_life_span			,	
		charDBRow_char_add_life_span		,	
		charDBRow_char_cur_lvl				,
		charDBRow_char_cur_exp1				,
		charDBRow_char_cur_exp2				,
		charDBRow_char_cur_exp3				,
		charDBRow_char_cur_hp				,	
		charDBRow_char_cur_mp				,	
		charDBRow_char_lineage_num			,
		charDBRow_char_art_mash_id_1		,	
		charDBRow_char_art_mash_id_2		,	
		charDBRow_char_icon_id				,
		charDBRow_char_infuence_id			,
		charDBRow_char_skill_point_all		,
		charDBRow_char_no_assign_skill_point,	
		charDBRow_char_state				,	
		charDBRow_char_life_state			,	
		charDBRow_char_region_type			,
		charDBRow_char_region_id			,	
		charDBRow_char_pos_x 				,	
		charDBRow_char_pos_y 				,	
		charDBRow_char_pos_z 				,	
		charDBRow_char_dir_x 				,	
		charDBRow_char_dir_y 				,	
		charDBRow_char_dir_z 				,	
		charDBRow_char_attr_Id				,
		charDBRow_char_attr_add_Id			,
		charDBRow_char_attr_rand1 			,
		charDBRow_char_attr_rand2 			,
		charDBRow_char_attr_rand3 			,
		charDBRow_char_attr_rand4 			,
		charDBRow_char_attr_rand5 			,
		charDBRow_char_attr_rand6 			,
		charDBRow_char_attr_add_rand1 		,
		charDBRow_char_attr_add_rand2 		,
		charDBRow_char_attr_add_rand3 		,
		charDBRow_char_attr_add_rand4 		,
		charDBRow_char_attr_add_rand5 		,
		charDBRow_char_attr_add_rand6 		,
		charDBRow_char_item					,
		charDBRow_char_buff					,
		charDBRow_skill_data				,
		charDBRow_Max

};
/******************************************************************************/
namespace MG
{
	class PlayerCharacterDBSystem
	{
#define  DB_RECORDS_SEPARATOR ','
#define  DB_FIELDS_SEPARATOR '.'
	public:
		static Bool checkOrCreatePlayerCharacterTable( DBDriver* driver );
		static Bool createPlayerCharacter( DBDriver* driver, const PlayerCharacterData* characterDB, AccountIdType accountId);
		
		static Bool getPlayerCharactersNameMap( DBDriver* driver, 
												AccountIdType accountId,
												ClanIdType clanId, 
												std::vector<PlayerCharacterData>* charList, 
												std::vector<ItemRecord>* itemRecordList, 
												std::map<IdType, std::map<UInt, BuffData> >* mapPlayerCharBuff
												);

		static Bool deletePlayerCharacter(DBDriver* driver, AccountIdType accountId, ClanIdType clanId, PlayerCharacterIdType charId);


	private:
		static void loadPlayerCharacterItem(Str8 dbCharacterRecordString,std::vector<ItemRecord>* recordList);
		static void loadPlayerCharacterBuff(Str8 dbCharacterRecordString,std::map<UInt, BuffData>& recordList);
	};
}

#endif	//_PLAYER_CHARACTER_DB_SYSTEM_H_