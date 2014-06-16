//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: RelationWorldMapTriggerCsv.h
//        Author: yuanlinhu
//          Date: 2012-3-9
//          Time: 14:22
//   Description: 
//			∂¡»° RelationWorldMapTrigger.csv±Ì
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-9      add
//////////////////////////////////////////////////////////////


//*************************************************************************************************//

#ifndef _RELATION_WORLD_MAP_TRIGGER_CSV_
#define _RELATION_WORLD_MAP_TRIGGER_CSV_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "RelationCsvBase.h"

//*************************************************************************************************//

namespace MG
{
	class RelationWorldMapTriggerCsv
	{
	public:
		RelationWorldMapTriggerCsv();
		~RelationWorldMapTriggerCsv();
		SINGLETON_INSTANCE(RelationWorldMapTriggerCsv);
		// MG_CN_MODIFY
		bool load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

	private:
		RelationCsvBase			mBase;
	};
}

#endif	//_RELATION_WORLD_MAP_TRIGGER_CSV_