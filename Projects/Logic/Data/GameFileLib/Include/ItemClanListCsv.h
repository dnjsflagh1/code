//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\ItemClanListCsv.h
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

#ifndef _ITEM_CLAN_LIST_CSV_H
#define _ITEM_CLAN_LIST_CSV_H

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//部分需要的枚举
	//*************************************************************************************************//

	//*************************************************************************************************//
	//单个副本实例信息
	//*************************************************************************************************//
	struct ItemClanListCsvInfo
	{
		ItemIdType			ItemClanId;
		Str16				Name;
		Str16				Text;
		Int					ArtIconId;
		Int					ArtMeshId;
		U64					Price;
		U64					BuyPrice;
		U64					SellPrice;
		U64					MaxPlieNum;
		U64					Score;
		ITEM_RANK			Rank;
		ITEM_USE_CLASS		Class;
		ITEM_BIND_TYPE		BindType;
		U32					DisappearType;
		U32					ForbidType;
		U64	 				CastTime;
		Int	 				ExistanceTimeType;
		U64	 				ExistanceTime;
		U32					PublicTimePieceId;
		long				PublicTimePieceDelay;
		U32					OwnerTimePieceId;
		long				OwnerTimePieceDelay;
		U32	 				ResetTimePieceId;
		U32	 				ResetTimePieceGroupId;
		U32	 				ClanJudgeId;
		U32	 				StateId;
		long				StateNum;
		QuestIdType	 		GiveQuestId;
		ItemIdType	 		GiveItemGroupId;

		ItemClanListCsvInfo()
			:ItemClanId(0)
			,ArtIconId(0)
			,ArtMeshId(0)
			,Price(0)
			,BuyPrice(0)
			,SellPrice(0)
			,MaxPlieNum(0)
			,Score(0)
			,Rank(ITEM_RANK_NONE)
			,Class(ITEM_USE_CLASS_NONE)
			,BindType(ITEM_BIND_TYPE_NULL)
			,DisappearType(0)
			,ForbidType(0)
			,CastTime(0)
			,ExistanceTimeType(0)
			,ExistanceTime(0)
			,PublicTimePieceId(0)
			,PublicTimePieceDelay(0)
			,OwnerTimePieceId(0)
			,OwnerTimePieceDelay(0)
			,ResetTimePieceId(0)
			,ResetTimePieceGroupId(0)
			,ClanJudgeId(0)
			,StateId(0)
			,StateNum(0)
			,GiveQuestId(0)
			,GiveItemGroupId(0)
			
		{
		}
	};

	//*************************************************************************************************//
	class ItemClanListCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum ItemClanListCsvRow
		{
			//完成检测2012.9.19
			ItemClanListCsvRow_ItemClanId,			//氏族使用类物品的调用Id
			ItemClanListCsvRow_Notes,
			ItemClanListCsvRow_Name,				//氏族使用类物品的中文命名
			ItemClanListCsvRow_Text,				//"氏族使用类物品的描述文本 支持转义，提供指定颜色、换行等功能"
			ItemClanListCsvRow_ArtIconId,			//氏族使用类物品在ArtIcon表中所对应的IconId
			ItemClanListCsvRow_ArtMeshId,			//氏族使用类物品在Mesh表中所对应的显示模型Id，用于地面掉落显示的模型
			ItemClanListCsvRow_Price,				//氏族使用类物品的基础价值
			ItemClanListCsvRow_BuyPrice,			//氏族使用类物品的购买花费，消耗游戏币
			ItemClanListCsvRow_SellPrice,			//氏族使用类物品的出售花费，消耗游戏币
			ItemClanListCsvRow_MaxPlieNum,			//氏族使用类物品的最大堆叠数量
			ItemClanListCsvRow_Score,				//氏族使用类物品的评分等级
			ItemClanListCsvRow_Rank,				//"氏族使用类物品的品质类别，单选1~白，2~绿，3~蓝，4~紫 仅有4种"
			ItemClanListCsvRow_Class,				//"氏族使用类物品的类型，单选 具体分类待定"
			ItemClanListCsvRow_BindType,			//"氏族使用类物品的绑定方式，单选
			ItemClanListCsvRow_DisapprearType,		//"氏族使用类物品的消失方式，二进制多选 不选择消失条件，物品不会自动消失"
			ItemClanListCsvRow_ForbidType,			//"氏族氏族使用类物品的支持功能，二进制多选
			ItemClanListCsvRow_CastTime,			//氏族使用类物品的准备时长（吟唱时长），具体精确到百毫秒
			ItemClanListCsvRow_ExistanceTimeType,	//"氏族使用类物品存在的时间类型，单选 1～真实时间，2～在线时间 仅有2种"
			ItemClanListCsvRow_ExistanceTime,		//"使用类物品存在的时间，具体精确到百毫秒 时间到后，物品将消失或失效"
			ItemClanListCsvRow_PublicTimePieceId,	//氏族使用后，所引用的公共计时器id
			ItemClanListCsvRow_PublicTimePieceDelay,//"氏族使用后，所导致的计时器时长，具体精确到百毫秒 当此计时器id存在时，物品无法被使用"
			ItemClanListCsvRow_OwnerTimePieceId,	//氏族使用后，所引用的自身计时器id
			ItemClanListCsvRow_OwnerTimePieceDelay,	//"氏族使用后，所导致的计时器时长，具体精确到百毫秒 当此计时器id存在时，物品无法被使用"
			ItemClanListCsvRow_ResetTimePieceId,	//氏族使用后，将引用的计时器时钟设为0
			ItemClanListCsvRow_ResetTimePieceGroupId,//氏族使用后，将引用的计时器及其同组计时器时钟设为0
			ItemClanListCsvRow_ClanJudgeId,			//氏族使用时，对氏族的要求
			ItemClanListCsvRow_StateId,				//氏族使用后，所给予状态的状态Id
			ItemClanListCsvRow_StateNum,			//氏族使用后，可给予的状态层数
			ItemClanListCsvRow_GiveQuestId,			//氏族使用后，可接的氏族任务Id
			ItemClanListCsvRow_GiveItemGroupId,		//氏族使用后，可开启的物品分组Id
			
			ItemClanListCsvRow_Max
		};

	public:
		ItemClanListCsv();
		~ItemClanListCsv();
		SINGLETON_INSTANCE(ItemClanListCsv);

		Bool					load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		ItemClanListCsvInfo*	getInfoById(ItemIdType id);
		std::map<ItemIdType, ItemClanListCsvInfo*>*	getList();

	private:
		SimpleMapDataSetManager<ItemIdType, ItemClanListCsvInfo>		mItemClanList;
	};
}

#endif	//_INSTANCE_LIST_CSV_H_
