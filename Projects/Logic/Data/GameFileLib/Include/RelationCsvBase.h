//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: RelationCsvBase.h
//        Author: yuanlinhu
//          Date: 2012-3-6
//          Time: 15:00
//   Description: 
//			取其他Relation表 提供 公共方法
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-6      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _RELATION_CSV_BASE_H_
#define _RELATION_CSV_BASE_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{

	//*************************************************************************************************//
	//对应 CSV表的每个字段
	//*************************************************************************************************//
	enum RelationCsvBaseRow
	{
		RCB_RelationId = 0,			//关系序列id,除排序外无意义
		RCB_MapId,					//以下对应内容所归属的地图id
		RCB_ArtName,				//根据以上类型，记录美术的对应id 【EntityName】
		RCB_GameDataId,				//根据以上类型，记录策划指定的对应数据id

		RCB_Max,
	};

	//*************************************************************************************************//
	//单个地图关系信息
	//*************************************************************************************************//
	struct RelationInfo
	{
		RelationIdType		relationId;
		MapIdType			mapId;
		Str16				artName;
		GameObjectIdType	gameDataId;
	};

	//--------------------------------------------------------------------------
	class RelationCsvBase
	{
	public:
		RelationCsvBase();
		~RelationCsvBase();
		// MG_CN_MODIFY
		Bool				load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

		RelationInfo*		getRelationInfoByGameDataId(const GameObjectIdType gameObjectId);

	private:
		SimpleMapDataSetManager<RelationIdType, RelationInfo>		mRelationList;
	};
}

#endif	//_RELATION_CSV_BASE_H_