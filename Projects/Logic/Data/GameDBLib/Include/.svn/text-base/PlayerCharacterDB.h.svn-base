/******************************************************************************/
#ifndef _CHARACTERDB_H_
#define _CHARACTERDB_H_
/******************************************************************************/

#define  CHAR_TABLE_NAME	"player_character_info"
#include "CommonGameDefine.h"
/******************************************************************************/
#include "PlayerCharacterData.h"
#include "WorldCorePreqs.h"
#include "BuffData.h"
/******************************************************************************/
namespace MG
{
	//class PlayerItem;
	//class ItemRecord;
	class PlayerCharacterDBOp
	{
		#define  DB_RECORDS_SEPARATOR ','
		#define  DB_FIELDS_SEPARATOR '.'
	public:
		static Bool checkOrCreatePlayerCharacterTable( DBDriver& driver );
		static Bool createPlayerCharacter( DBDriver& driver, const PlayerCharacterData* characterDB, U64& uid);
		static Bool getPlayerCharactersNameMap( 
			DBDriver& driver, U64 clanId, PlayerCharacterIdType id,
			std::vector<PlayerCharacterData>& nameList, 
			std::vector<ItemRecord>& itemRecordList, 
			std::map<IdType, std::map<UInt, BuffData>>& mapPlayerCharBuff
			);
        
        static Bool updatePlayerCharacterHP( DBDriver& driver, U64 charId, UInt hp );
        static Bool updatePlayerCharacterMP( DBDriver& driver, U64 charId, UInt mp );
		static Bool updatePlayerCharacterLevel( DBDriver& driver, U64 charId, UInt level );
		static Bool updatePlayerCharacterExp( DBDriver& driver, U64 charId, UInt exp );
        static Bool updatePlayerCharacterInfo( DBDriver& driver, const PlayerCharacterData* characterDB );
		static Bool deletePlayerCharacter(DBDriver& driver,U64 clanID);
	    
		//////////////////////////////////////////////////////////////////////////
		static bool updatePlayerCharacterItem( DBDriver& driver, U64 charId, std::vector<PlayerItem*>* itemList);
		static bool updatePlayerCharacterBuff( DBDriver& driver, U64 charId, std::map<UInt, BuffData>* buffDataList);

	private:
        static void loadPlayerCharacterItem(Str8 dbCharacterRecordString,std::vector<ItemRecord>& recordList);
		static void loadPlayerCharacterBuff(Str8 dbCharacterRecordString,std::map<UInt, BuffData>& recordList);
	};
}

#endif