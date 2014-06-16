//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\ItemExpListCsv.h
//        Author: yuanlinhu
//          Date: 2012-4-13
//          Time: 10:45
//   Description: 
//			101.通用经验类物品列表-ItemExpList
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-9-18      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _ITEM_EXP_LIST_CSV_H
#define _ITEM_EXP_LIST_CSV_H

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{


	//*************************************************************************************************//
	//部分需要的枚举
	//*************************************************************************************************//
	enum ITEM_EXP_CLASS		//经验的物品分类，单选
	{
		ITEM_EXP_CLASS_NONE,

		ITEM_EXP_CLASS_CLAN_EXP,						//1～氏族经验
		ITEM_EXP_CLASS_CLAN_POS_EXP,					//2～氏族官品经验
		ITEM_EXP_CLASS_CLAN_FEATS_EXP,					//3～氏族功绩经验
		ITEM_EXP_CLASS_CLAN_SPARE_EXP,					//4～氏族备用经验
		
		ITEM_EXP_CLASS_CHAR_LVL_EXP,					//5～角色升级经验
		ITEM_EXP_CLASS_CHAR_TRUN_EXP,					//6～角色转生经验
		ITEM_EXP_CLASS_CHAR_SKILL_EXP,					//7～角色技能经验
		ITEM_EXP_CLASS_CHAR_SPARE_EXP,					//8～角色备用经验
		
		ITEM_EXP_CLASS_AYM_LVL_EXP,						//9～军队升级经验
		ITEM_EXP_CLASS_AYM_SPARE_EXP,					//10～军队备用经验

		ITEM_EXP_CLASS_BUILD_LVL_EXP,					//11～建筑升级经验
		ITEM_EXP_CLASS_BUILD_SPARE_EXP,					//12～建筑备用经验

		ITEM_EXP_CLASS_OTHER_SPARE_EXP1,				//13～其他备用经验1
		ITEM_EXP_CLASS_OTHER_SPARE_EXP2,				//14～其他备用经验2
		ITEM_EXP_CLASS_OTHER_SPARE_EXP3,				//15～其他备用经验3
		ITEM_EXP_CLASS_OTHER_SPARE_EXP4,				//16～其他备用经验4

		ITEM_EXP_CLASS_MAX
	};

	//*************************************************************************************************//
	//单个副本实例信息
	//*************************************************************************************************//
	struct ItemExpListCsvInfo
	{
		ItemIdType		itemExpId;
		Str16			name;
		Str16			text;
		Int				atrIconId;
		Int				price;
		ITEM_EXP_CLASS	itemType;
		
		ItemExpListCsvInfo()
			:itemExpId(0)
			,atrIconId(0)
			,price(0)
			,itemType(ITEM_EXP_CLASS_NONE)
		{
		}
	};

	//*************************************************************************************************//
	class ItemExpListCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum ItemExpListCsvRow
		{
			ItemExpListCsvRow_ItemExpId	= 0,			//经验物品的调用Id
			ItemExpListCsvRow_Notes			,
			ItemExpListCsvRow_Name			,			//升级经验的中文名称
			ItemExpListCsvRow_Text			,			//"经验的描述文本 支持转义，提供指定颜色、换行等功能"
			ItemExpListCsvRow_ArtIconId		,			//经验在ArtIcon表中所对应的IconId
			ItemExpListCsvRow_Price			,			//经验的基础价值
			ItemExpListCsvRow_Class			,			//"经验的物品分类，单选
												
			ItemExpListCsvRow_Max
		};

	public:
		ItemExpListCsv();
		~ItemExpListCsv();
		SINGLETON_INSTANCE(ItemExpListCsv);
	
		Bool					load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		ItemExpListCsvInfo*		getInfoById(ItemIdType id);
		std::map<ItemIdType, ItemExpListCsvInfo*>*	getList();

	private:
		SimpleMapDataSetManager<ItemIdType, ItemExpListCsvInfo>		mItemExpList;
	};
}

#endif	//_INSTANCE_LIST_CSV_H_
