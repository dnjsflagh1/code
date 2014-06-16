//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\InstanceAtrListCsv.h
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

#ifndef _INSTANCE_ATK_LIST_CSV_H_
#define _INSTANCE_ATK_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{


	enum AtkOpenType
	{
		AtkOpenType_Unlimited,		//������
		AtkOpenType_EveryHour,		//ÿСʱ
		AtkOpenType_EveryDay,		//ÿ��
		AtkOpenType_EveryWeek,		//ÿ��
		
		AtkOpenType_Max
	};

	enum AtkOverdueType
	{
		AtkOverdueType_Unlimited,		//������
		AtkOverdueType_EveryHour,		//ÿСʱ
		AtkOverdueType_EveryDay,		//ÿ��
		AtkOverdueType_EveryWeek,		//ÿ��
	};
	//*************************************************************************************************//
	//��������ʵ����Ϣ
	//*************************************************************************************************//
	struct InstanceAtkListCsvInfo
	{
		InstanceIdType		instanceAtkId;
		AtkOpenType			openType;
		U64 				openTimeStart;
		U64 				openTimeEnd;
		I32					timepieceID;
		AtkOverdueType		overdueType;
		U64					overdueTime;
		CampIdType			campListId1;
		CampIdType			campListId2;
		CampIdType			campListId3;
		CampIdType			campListId4;
		QuestIdType			finishQuest;
		GameObjectIdType	finishCharacter;
		ArmyIdType			finishArmy;
		BuildingIdType		finishBuilding;
		Str16				finishScript;
		I32					itemGroupId1;		//ʤ��������ʹ����Ʒ��������id
		I32					itemGroupId2;		//ʧ�ܽ�����ʹ����Ʒ��������id
		I32					itemGroupId3;		//ƽ�ֽ�����ʹ����Ʒ��������id
		Str16				rewardScript;
		U32					intanceTimeId;		//���id���Ӹ���ʱ�����ñ��ȡ

		InstanceAtkListCsvInfo()
			:instanceAtkId(0)
			,openType(AtkOpenType_Unlimited)
			,openTimeStart(0)
			,openTimeEnd(0)
			,timepieceID(0)
			,overdueType(AtkOverdueType_Unlimited)
			,overdueTime(0)
			,campListId1(0)
			,campListId2(0)
			,campListId3(0)
			,campListId4(0)
			,finishQuest(0)
			,finishCharacter(0)
			,finishArmy(0)
			,finishBuilding(0)
			,itemGroupId1(0)
			,itemGroupId2(0)
			,itemGroupId3(0)
			,intanceTimeId(0)
		{
		}
	};

	//*************************************************************************************************//
	class InstanceAtkListCsv
	{
		//*************************************************************************************************//
		//��Ӧ CSV���ÿ���ֶ�
		//*************************************************************************************************//
		enum InstanceAtkListCsvRow
		{
			InstanceAtkListCsvRow_InstanceAtkId	,			//	�����ĵ���Id
			InstanceAtkListCsvRow_Notes			,
			InstanceAtkListCsvRow_OpenType		,					//����ʱ�� 1~�����ƣ�2~ÿСʱ, 3~ÿ�죬4~ÿ��
			InstanceAtkListCsvRow_OpenTimeStart,					//��ʼ����ʱ��
			InstanceAtkListCsvRow_OpenTimeEnd,						//��������ʱ��
			InstanceAtkListCsvRow_TimepieceID,						//ʱ������ID
			InstanceAtkListCsvRow_OverdueType,						//���ü������	1~�����ƣ�2~ÿСʱ,3~ÿ�죬4~ÿ��
			InstanceAtkListCsvRow_OverdueTime,						//���ü��ʱ��
			InstanceAtkListCsvRow_CampListId1,						//��������ID
			InstanceAtkListCsvRow_CampListId2,						//����Ԯ������ID
			InstanceAtkListCsvRow_CampListId3,						//�ط�����ID
			InstanceAtkListCsvRow_CampListId4,						//�ط�Ԯ������ID
			InstanceAtkListCsvRow_FinishQuest,						//����ͨ��
			InstanceAtkListCsvRow_FinishCharacter,					//�����ɱͨ��
			InstanceAtkListCsvRow_FinishArmy,						//���ӻ�ɱͨ��
			InstanceAtkListCsvRow_FinishBuilding,					//������ɱͨ��
			InstanceAtkListCsvRow_FinishScript,						//�ű�ͨ��
			InstanceAtkListCsvRow_ItemGroupId1,						//ʤ��������ʹ����Ʒ��������id
			InstanceAtkListCsvRow_ItemGroupId2,						//ʧ�ܽ�����ʹ����Ʒ��������id
			InstanceAtkListCsvRow_ItemGroupId3,						//ƽ�ֽ�����ʹ����Ʒ��������id
			InstanceAtkListCsvRow_RewardScript,						//�ű�����
			InstanceAtkListCsvRow_IntanceTimeId,					//����ʱ��ID

			InstanceAtkListCsvRow_Max,
		};
	public:
		InstanceAtkListCsv();
		~InstanceAtkListCsv();
		SINGLETON_INSTANCE(InstanceAtkListCsv);
		// MG_CN_MODIFY
		Bool							load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		InstanceAtkListCsvInfo*			getInfoById(InstanceIdType id);

		std::map<InstanceIdType, InstanceAtkListCsvInfo*>*			getList();

	private:
		SimpleMapDataSetManager<InstanceIdType, InstanceAtkListCsvInfo>		mInstanceAtkList;
	};
}

#endif	//_INSTANCE_ATK_LIST_CSV_H_