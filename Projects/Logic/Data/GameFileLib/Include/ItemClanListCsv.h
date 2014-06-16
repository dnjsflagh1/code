//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\ItemClanListCsv.h
//        Author: yuanlinhu
//          Date: 2012-4-13
//          Time: 10:45
//   Description: 
//			101.ͨ�þ�������Ʒ�б�-ItemExpList
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
	//������Ҫ��ö��
	//*************************************************************************************************//

	//*************************************************************************************************//
	//��������ʵ����Ϣ
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
		//��Ӧ CSV���ÿ���ֶ�
		//*************************************************************************************************//
		enum ItemClanListCsvRow
		{
			//��ɼ��2012.9.19
			ItemClanListCsvRow_ItemClanId,			//����ʹ������Ʒ�ĵ���Id
			ItemClanListCsvRow_Notes,
			ItemClanListCsvRow_Name,				//����ʹ������Ʒ����������
			ItemClanListCsvRow_Text,				//"����ʹ������Ʒ�������ı� ֧��ת�壬�ṩָ����ɫ�����еȹ���"
			ItemClanListCsvRow_ArtIconId,			//����ʹ������Ʒ��ArtIcon��������Ӧ��IconId
			ItemClanListCsvRow_ArtMeshId,			//����ʹ������Ʒ��Mesh��������Ӧ����ʾģ��Id�����ڵ��������ʾ��ģ��
			ItemClanListCsvRow_Price,				//����ʹ������Ʒ�Ļ�����ֵ
			ItemClanListCsvRow_BuyPrice,			//����ʹ������Ʒ�Ĺ��򻨷ѣ�������Ϸ��
			ItemClanListCsvRow_SellPrice,			//����ʹ������Ʒ�ĳ��ۻ��ѣ�������Ϸ��
			ItemClanListCsvRow_MaxPlieNum,			//����ʹ������Ʒ�����ѵ�����
			ItemClanListCsvRow_Score,				//����ʹ������Ʒ�����ֵȼ�
			ItemClanListCsvRow_Rank,				//"����ʹ������Ʒ��Ʒ����𣬵�ѡ1~�ף�2~�̣�3~����4~�� ����4��"
			ItemClanListCsvRow_Class,				//"����ʹ������Ʒ�����ͣ���ѡ ����������"
			ItemClanListCsvRow_BindType,			//"����ʹ������Ʒ�İ󶨷�ʽ����ѡ
			ItemClanListCsvRow_DisapprearType,		//"����ʹ������Ʒ����ʧ��ʽ�������ƶ�ѡ ��ѡ����ʧ��������Ʒ�����Զ���ʧ"
			ItemClanListCsvRow_ForbidType,			//"��������ʹ������Ʒ��֧�ֹ��ܣ������ƶ�ѡ
			ItemClanListCsvRow_CastTime,			//����ʹ������Ʒ��׼��ʱ��������ʱ���������徫ȷ���ٺ���
			ItemClanListCsvRow_ExistanceTimeType,	//"����ʹ������Ʒ���ڵ�ʱ�����ͣ���ѡ 1����ʵʱ�䣬2������ʱ�� ����2��"
			ItemClanListCsvRow_ExistanceTime,		//"ʹ������Ʒ���ڵ�ʱ�䣬���徫ȷ���ٺ��� ʱ�䵽����Ʒ����ʧ��ʧЧ"
			ItemClanListCsvRow_PublicTimePieceId,	//����ʹ�ú������õĹ�����ʱ��id
			ItemClanListCsvRow_PublicTimePieceDelay,//"����ʹ�ú������µļ�ʱ��ʱ�������徫ȷ���ٺ��� ���˼�ʱ��id����ʱ����Ʒ�޷���ʹ��"
			ItemClanListCsvRow_OwnerTimePieceId,	//����ʹ�ú������õ������ʱ��id
			ItemClanListCsvRow_OwnerTimePieceDelay,	//"����ʹ�ú������µļ�ʱ��ʱ�������徫ȷ���ٺ��� ���˼�ʱ��id����ʱ����Ʒ�޷���ʹ��"
			ItemClanListCsvRow_ResetTimePieceId,	//����ʹ�ú󣬽����õļ�ʱ��ʱ����Ϊ0
			ItemClanListCsvRow_ResetTimePieceGroupId,//����ʹ�ú󣬽����õļ�ʱ������ͬ���ʱ��ʱ����Ϊ0
			ItemClanListCsvRow_ClanJudgeId,			//����ʹ��ʱ���������Ҫ��
			ItemClanListCsvRow_StateId,				//����ʹ�ú�������״̬��״̬Id
			ItemClanListCsvRow_StateNum,			//����ʹ�ú󣬿ɸ����״̬����
			ItemClanListCsvRow_GiveQuestId,			//����ʹ�ú󣬿ɽӵ���������Id
			ItemClanListCsvRow_GiveItemGroupId,		//����ʹ�ú󣬿ɿ�������Ʒ����Id
			
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
