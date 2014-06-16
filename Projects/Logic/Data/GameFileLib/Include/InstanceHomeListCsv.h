//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\InstanceHomeListCsv.h
//        Author: yuanlinhu
//          Date: 2012-4-13
//          Time: 11:43
//   Description: 
//			��԰�������ñ�
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
	//��������ʵ����Ϣ
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
		//��Ӧ CSV���ÿ���ֶ�
		//*************************************************************************************************//
		enum InstanceHomeListCsvRow
		{
			InstanceHomeRow_InstanceHomeId		= 0	,			//�����ĵ������
			InstanceHomeRow_Notes					,			//�߻�ά�����ı�ע˵����16��������
			InstanceHomeRow_Name					,			//��԰�����ڹ���ǰĬ������
			InstanceHomeRow_Text					,			//��԰�����Ĳ߻�˵�������64����������
			InstanceHomeRow_ArtIconResId			,			//��԰������ͼ��Id
			InstanceHomeRow_NeedItemId				,			//�����԰ʱ��Ҫ����ƷID
			InstanceHomeRow_MapListId				,			//��԰����ʹ�õĵ�ͼID
			InstanceHomeRow_MaxBuildLv				,			//��԰�н��������ɴ���������
			InstanceHomeRow_MaxBuildNum				,			//��԰�п��Է��õĽ�����������
			InstanceHomeRow_MaxNpcNum				,			//��԰�п��Է��õ�NPC��������
			InstanceHomeRow_MaxObjectNum			,			//��԰�п��Է��õĳ��������������
			InstanceHomeRow_MaxUsageTime			,			//��԰��ʹ��ʱ��
			
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