//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\InstanceHomeListCsv.h
//        Author: yuanlinhu
//          Date: 2012-4-13
//          Time: 11:43
//   Description: 
//			家园副本设置表
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-13      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _INSTANCE_HOME_LIST_CSV_H_
#define _INSTANCE_HOME_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//单个副本实例信息
	//*************************************************************************************************//
	struct InstanceHomeListCsvInfo
	{
			InstanceIdType	instanceHomeId			;
			Str16			name					;
			Str16			text					;
			Int				artIconResId			;
			ItemIdType		needItemId				;
			Int				mapListId				;
			Int				maxBuildLv				;
			Int				maxBuildNum				;
			Int				maxNpcNum				;
			Int				maxObjectNum			;
			Int				maxUsageTime			;

		InstanceHomeListCsvInfo()
			:instanceHomeId(0)
			,artIconResId(0)
			,needItemId(0)
			,mapListId(0)
			,maxBuildLv(0)
			,maxBuildNum(0)
			,maxNpcNum(0)
			,maxObjectNum(0)
			,maxUsageTime(0)
		{
		}
	};

	//*************************************************************************************************//
	class InstanceHomeListCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum InstanceHomeListCsvRow
		{
			InstanceHomeRow_InstanceHomeId		= 0	,			//副本的调用序号
			InstanceHomeRow_Notes					,			//策划维护表格的备注说明，16个汉字内
			InstanceHomeRow_Name					,			//家园副本在购买前默认名称
			InstanceHomeRow_Text					,			//家园副本的策划说明，大概64个汉字以内
			InstanceHomeRow_ArtIconResId			,			//家园副本的图标Id
			InstanceHomeRow_NeedItemId				,			//购买家园时需要的物品ID
			InstanceHomeRow_MapListId				,			//家园副本使用的地图ID
			InstanceHomeRow_MaxBuildLv				,			//家园中建筑升级可达的最高上限
			InstanceHomeRow_MaxBuildNum				,			//家园中可以放置的建筑数量上限
			InstanceHomeRow_MaxNpcNum				,			//家园中可以放置的NPC数量上限
			InstanceHomeRow_MaxObjectNum			,			//家园中可以放置的场景物件数量上限
			InstanceHomeRow_MaxUsageTime			,			//家园的使用时限
			
			InstanceHomeRow_Max
		};
	public:
		InstanceHomeListCsv();
		~InstanceHomeListCsv();
		SINGLETON_INSTANCE(InstanceHomeListCsv);
		
		Bool						load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		InstanceHomeListCsvInfo*	getInfoById(InstanceIdType id);

		std::map<InstanceIdType, InstanceHomeListCsvInfo*>	*	getList();

	private:
		SimpleMapDataSetManager<InstanceIdType, InstanceHomeListCsvInfo>		mInstanceHomeList;
	};
}

#endif	//_INSTANCE_HOME_LIST_CSV_H_