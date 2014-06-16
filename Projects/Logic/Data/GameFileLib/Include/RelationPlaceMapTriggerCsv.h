//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\RelationPlaceMapTriggerCsv.h
//        Author: yuanlinhu
//          Date: 2012-3-9
//          Time: 14:31
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-9      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _RELATION_PLACE_MAP_TRIGGER_CSV_
#define _RELATION_PLACE_MAP_TRIGGER_CSV_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "RelationCsvBase.h"

//*************************************************************************************************//

namespace MG
{

	class RelationPlaceMapTriggerCsv
	{
	public:
		RelationPlaceMapTriggerCsv();
		~RelationPlaceMapTriggerCsv();
		SINGLETON_INSTANCE(RelationPlaceMapTriggerCsv);
		// MG_CN_MODIFY
		bool load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

	private:
		RelationCsvBase			mBase;
	};
}

#endif	//_RELATION_PLACE_MAP_TRIGGER_CSV_