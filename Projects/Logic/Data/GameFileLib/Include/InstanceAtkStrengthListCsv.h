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
	//��������ʵ����Ϣ
	//*************************************************************************************************//
	struct InstanceAtkStrengthListCsvInfo
	{
		CampIdType		campId;
		U32				buildTemplateId;		//��Ӫ����ģ��ID
		U32				campPoint;				//��Ӫ�����
		U32				generalRefreshPoint;	//����ˢ�������
		U32				generalAlivePoint;		//���츴�������
		U32				armyPoint[TROOP_GROUP_NUM];			//���ӳ��������01

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
		//��Ӧ CSV���ÿ���ֶ�
		//*************************************************************************************************//
		enum InstanceAtkStrengthListCsvRow
		{
			InstanceAtkStrengthListCsvRow_CampId,					//����Id
			InstanceAtkStrengthListCsvRow_Notes,
			InstanceAtkStrengthListCsvRow_CharacterBuildId,			//��Ӫ����ģ��ID
			InstanceAtkStrengthListCsvRow_CampPointId,				//��Ӫ�����
			InstanceAtkStrengthListCsvRow_GeneraRefreshpoint,		//����ˢ�������
			InstanceAtkStrengthListCsvRow_GeneraSpawnPoint,			//���츴�������
			InstanceAtkStrengthListCsvRow_ArmyPlayedPoint01,		//���ӳ��������1
			InstanceAtkStrengthListCsvRow_ArmyPlayedPoint02,		//���ӳ��������2
			InstanceAtkStrengthListCsvRow_ArmyPlayedPoint03,		//���ӳ��������3
			InstanceAtkStrengthListCsvRow_ArmyPlayedPoint04,		//���ӳ��������4
			InstanceAtkStrengthListCsvRow_ArmyPlayedPoint05,		//���ӳ��������5

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