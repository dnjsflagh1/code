//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\InstanceListCsv.h
//        Author: yuanlinhu
//          Date: 2012-4-13
//          Time: 10:45
//   Description: 
//			2.1	�����б�(InstanceList)����������
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-13      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _INSTANCE_LIST_CSV_H_
#define _INSTANCE_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//������Ҫ��ö��
	//*************************************************************************************************//
	enum InstanceType	//	������;����ѡ
	{
		InstanceType_Null		= 0,

		InstanceType_HomeLand	= 1,			//1	�����԰������InstanceHome)�������԰ֻ�е�һ��ҿɽ���(RPG)
		InstanceType_Tiro,						//2	�������ָ�����InstanceTiro����������ҽ���ĵ�¼ѹ������(RPG)
		InstanceType_PVP,						//3	�����ս������InstancePvP������ҿ��ƽ�������໥pkս��(RPG)
		InstanceType_PVE,						//4	����ð�ո�����InstancePvE������ҽ���͵��Թ������ð��(RPG)
		InstanceType_Growup,					//5	����ɳ�������InstanceGrowup��������ͨ��С�淨���ɳ��ĸ���(RPG)
		InstanceType_Atk,						//6	���ӹ��Ǹ�����InstanceAtk������ҿ��ƾ��ӹ�������(SLG)
		InstanceType_History,					//7	������ʷ����(InstanceHistory)����ҿ��ƾ��Ӿ�����ʷս��(SLG)
		InstanceType_Sport,						//8	���Ӿ���������InstanceSport������Ҿ����໥�����ĸ���(SLG)
		InstanceType_Fight,						//9	����ս��������InstanceFight������ҿ��ƾ��Ӻ͵��Ծ���ս��(SLG)
		InstanceType_Train,						//10 ����ѵ��������InstanceTrain��������ͨ��С�淨���ɳ��ĸ���(Slg)
	
		InstanceType_Max
	};


	//*************************************************************************************************//
	//��������ʵ����Ϣ
	//*************************************************************************************************//
	struct InstanceListCsvInfo
	{
		InstanceIdType			instanceId;
		Int						useType;
		InstanceType			instanceType;
		InstanceIdType			instanceListId;

		InstanceListCsvInfo()
			:instanceId(0)
			,useType(0)
			,instanceType(InstanceType_Null)
			,instanceListId(0)
		{
		}
	};

	//*************************************************************************************************//
	class InstanceListCsv
	{
		//*************************************************************************************************//
		//��Ӧ CSV���ÿ���ֶ�
		//*************************************************************************************************//
		enum InstanceListCsvRow
		{
			InstanceRow_InstanceId = 0,					//	�����ĵ���Id
			InstanceRow_Notes,
			InstanceRow_UseType,						//"����֧�ֵĹ��ܣ������ƶ�ѡ��1=�����ص�½,֮���½�����"
			InstanceRow_InstanceType,					//	������;����ѡ
			InstanceRow_InstanceListId,					//	���ϸ����Ķ�Ӧ��������id��

			InstanceRow_Max
		};

	public:
		InstanceListCsv();
		~InstanceListCsv();
		SINGLETON_INSTANCE(InstanceListCsv);
		
		Bool					load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		InstanceListCsvInfo*	getInfoById(InstanceIdType id);
		std::map<InstanceIdType, InstanceListCsvInfo*>	*	getList();

	private:
		SimpleMapDataSetManager<InstanceIdType, InstanceListCsvInfo>		mInstanceList;
	};
}

#endif	//_INSTANCE_LIST_CSV_H_
