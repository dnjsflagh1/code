//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\RelationPlaceMapCharacterCsv.h
//        Author: yuanlinhu
//          Date: 2012-3-9
//          Time: 14:30
//   Description: 
//			RelationPlaceMapCharacterCsv ∂¡»°
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-9      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _RELATION_PLACE_MAP_CHARACTER_CSV_
#define _RELATION_PLACE_MAP_CHARACTER_CSV_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "RelationCsvBase.h"

//*************************************************************************************************//

namespace MG
{

	class RelationPlaceMapCharacterCsv
	{
	public:
		RelationPlaceMapCharacterCsv();
		~RelationPlaceMapCharacterCsv();
		SINGLETON_INSTANCE(RelationPlaceMapCharacterCsv);
		// MG_CN_MODIFY
		bool load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

	private:
		RelationCsvBase			mBase;
	};
}

#endif	//_RELATION_PLACE_MAP_CHARACTER_CSV_