//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\InstanceAtkStrengthListCsv.h
//        Author: yuanlinhu
//          Date: 2012-4-23
//          Time: 18:38
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-23      add
//////////////////////////////////////////////////////////////


//*************************************************************************************************//

#ifndef _INSTANCE_ATK_STRENGTH_LIST_CSV_
#define _INSTANCE_ATK_STRENGTH_LIST_CSV_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//
namespace MG
{

	//*************************************************************************************************//
	//单个副本实例信息
	//*************************************************************************************************//
	struct InstanceAtkStrengthListCsvInfo
	{
		CampIdType		campId;
		U32				buildTemplateId;		//兵营建筑模版ID
		U32				campPoint;				//兵营坐标点
		U32				generalRefreshPoint;	//将领刷新坐标点
		U32				generalAlivePoint;		//将领复活坐标点
		U32				armyPoint[TROOP_GROUP_NUM];			//军队出兵坐标点01

		InstanceAtkStrengthListCsvInfo()
			:campId(0)
			,buildTemplateId(0)
			,campPoint(0)
			,generalRefreshPoint(0)
			,generalAlivePoint(0)
		{
			memset(armyPoint, 0, sizeof(armyPoint));
		}
	};

	class InstanceAtkStrengthListCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum InstanceAtkStrengthListCsvRow
		{
			InstanceAtkStrengthListCsvRow_CampId,					//序列Id
			InstanceAtkStrengthListCsvRow_Notes,
			InstanceAtkStrengthListCsvRow_CharacterBuildId,			//兵营建筑模版ID
			InstanceAtkStrengthListCsvRow_CampPointId,				//兵营坐标点
			InstanceAtkStrengthListCsvRow_GeneraRefreshpoint,		//将领刷新坐标点
			InstanceAtkStrengthListCsvRow_GeneraSpawnPoint,			//将领复活坐标点
			InstanceAtkStrengthListCsvRow_ArmyPlayedPoint01,		//军队出兵坐标点1
			InstanceAtkStrengthListCsvRow_ArmyPlayedPoint02,		//军队出兵坐标点2
			InstanceAtkStrengthListCsvRow_ArmyPlayedPoint03,		//军队出兵坐标点3
			InstanceAtkStrengthListCsvRow_ArmyPlayedPoint04,		//军队出兵坐标点4
			InstanceAtkStrengthListCsvRow_ArmyPlayedPoint05,		//军队出兵坐标点5

			InstanceAtkStrengthListCsvRow_Max,
		};
	public:
		InstanceAtkStrengthListCsv();
		~InstanceAtkStrengthListCsv();
		SINGLETON_INSTANCE(InstanceAtkStrengthListCsv);
		// MG_CN_MODIFY
		Bool								load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		InstanceAtkStrengthListCsvInfo*		getInfoById(CampIdType campListId);

		std::map<CampIdType, InstanceAtkStrengthListCsvInfo*>*			getList();

	private:
		SimpleMapDataSetManager<CampIdType, InstanceAtkStrengthListCsvInfo>		mInstanceAtkStrengthList;
	};
}

#endif	//_INSTANCE_ATK_CAMP_LIST_CSV_H_