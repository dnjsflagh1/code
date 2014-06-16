//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\InstanceTiroListCsv.h
//        Author: yuanlinhu
//          Date: 2012-4-13
//          Time: 11:43
//   Description: 
//			���ָ������ñ�
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-13      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _INSTANCE_TIRO_LIST_CSV_H_
#define _INSTANCE_TIRO_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//��������ʵ����Ϣ
	//*************************************************************************************************//
	struct InstanceTiroListCsvInfo
	{
		InstanceIdType	instanceTiroId;
		Int				characterMaxNum;
		Int				newNum;
		QuestIdType		questId;
		MapIdType		mapListId;

		InstanceTiroListCsvInfo()
			:instanceTiroId(0)
			,characterMaxNum(0)
			,newNum(0)
			,questId(0)
			,mapListId(0)
		{
		}
	};

	//*************************************************************************************************//
	class InstanceTiroListCsv
	{
		//*************************************************************************************************//
		//��Ӧ CSV���ÿ���ֶ�
		//*************************************************************************************************//
		enum InstanceTiroListCsvRow
		{
			InstanceTiroRow_InstanceTiroId		= 0,			//	�����ĵ���Id
			InstanceTiroRow_Note,
			InstanceTiroRow_CharacterMaxNum,				//	�����ܹ����ɵ�����ɫ����
			InstanceTiroRow_NewNum,							//	�����¿�������բֵ��������������ϵͳ���Զ��¿������������ֱ�ȻС�ڸ����ܹ����ɵ�����ɫ����"
			InstanceTiroRow_QuestId,						//	��������id����ɴ�����Ľ�ɫ�޷��ٻص��������
			InstanceTiroRow_mapListId,						//ð�ո���ʹ�õĵ�ͼID
			InstanceTiroRow_InstanceTimeId,
			
			InstanceTiroRow_Max
		};
	public:
		InstanceTiroListCsv();
		~InstanceTiroListCsv();
		SINGLETON_INSTANCE(InstanceTiroListCsv);
		// MG_CN_MODIFY
		Bool				load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		InstanceTiroListCsvInfo*	getInfoById(InstanceIdType id);

		std::map<InstanceIdType, InstanceTiroListCsvInfo*>	*	getList();

	private:
		SimpleMapDataSetManager<InstanceIdType, InstanceTiroListCsvInfo>		mInstanceTiroList;
	};
}

#endif	//_INSTANCE_TIRO_LIST_CSV_H_