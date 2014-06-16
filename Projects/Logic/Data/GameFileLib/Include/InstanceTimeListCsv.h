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

#ifndef _INSTANCE_TIME_LIST_CSV_H_
#define _INSTANCE_TIME_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"
#include "InstanceListCsv.h"


//*************************************************************************************************//

namespace MG
{

	//*************************************************************************************************//
	//��������ʵ����Ϣ
	//*************************************************************************************************//
	struct InstanceTimeListCsvInfo
	{
		U32				instanceTimeId;
		InstanceType	instanceType;
		U32 			time1;	//"��ע��Time01����Ϊ������û�����ʱ�Զ��رյ�ʱ�������û�о�Ϊ��0����ʾû�����塿
								//��InstanceTypeΪ2ʱ��Time01Ϊ������û�����ʱ�Զ��رյ�ʱ��
								//��InstanceTypeΪ4ʱ��Time01Ϊ������û�����ʱ�Զ��رյ�ʱ��
								//��InstanceTypeΪ6ʱ��Time01Ϊ������û�����ʱ�Զ��رյ�ʱ��
								//����½������"
		
		U32 			time2;	//"��ע��Time02����Ϊ�������е���ʱ����ս��ʱ�䣬�磺60���ӣ������û�о�Ϊ��0����ʾû�����塿
								//��InstanceTypeΪ2ʱ��Time02û������
								//��InstanceTypeΪ4ʱ��Time02Ϊ�������е���ʱ��
								//��InstanceTypeΪ6ʱ��Time02Ϊ�������е���ʱ��
								//����½������"

		U32 			time3;	//"��InstanceTypeΪ2ʱ��Time03û������
								//��InstanceTypeΪ4ʱ��Time03û������
								//��InstanceTypeΪ6ʱ��Time03Ϊ����ս��ʼǰ�ĵȴ�ʱ��
								//����½������"

		U32 			time4;	//"��InstanceTypeΪ2ʱ��Time04û������
								//��InstanceTypeΪ4ʱ��Time04û������
								//��InstanceTypeΪ6ʱ��Time04Ϊͣ����ʤ����ʧ�ܽ����ʱ��
								//����½������"

		U32 			time5;	//"��InstanceTypeΪ2ʱ��Time05û������
								//��InstanceTypeΪ4ʱ��Time05û������
								//��InstanceTypeΪ6ʱ��Time05Ϊͣ������ȡ���������ʱ��
								//����½������"

		U32 			time6;	//"��InstanceTypeΪ2ʱ��Time06û������
								//��InstanceTypeΪ4ʱ��Time06û������
								//��InstanceTypeΪ6ʱ��Time06Ϊ�����Զ���������ʱ����ע��Time04+Time05<=Time06��
								//����½������"


		InstanceTimeListCsvInfo()
			:instanceTimeId(0)
			,instanceType(InstanceType_Null)
			,time1(0)
			,time2(0)
			,time3(0)
			,time4(0)
			,time5(0)
			,time6(0)
		{
		}
	};

	//*************************************************************************************************//
	class InstanceTimeListCsv
	{
		//*************************************************************************************************//
		//��Ӧ CSV���ÿ���ֶ�
		//*************************************************************************************************//
		enum InstanceTimeListCsvRow
		{
			InstanceTimeListCsvRow_InstanceTimeId	,			//	����ʱ��ID
			InstanceTimeListCsvRow_Notes			,
			InstanceTimeListCsvRow_InstanceType		,			//��������
			InstanceTimeListCsvRow_Time1			,			//"��InstanceTypeΪ6ʱ��Time01Ϊ����ս��ʼǰ�ĵȴ�ʱ��
			InstanceTimeListCsvRow_Time2			,			//"��InstanceTypeΪ6ʱ��Time02Ϊ����ս���Զ���������ʱ��
			InstanceTimeListCsvRow_Time3			,			//"��InstanceTypeΪ6ʱ��Time03Ϊͣ����ʤ����ʧ�ܽ����ʱ��
			InstanceTimeListCsvRow_Time4			,			//"��InstanceTypeΪ6ʱ��Time04Ϊͣ������ȡ���������ʱ��
			InstanceTimeListCsvRow_Time5			,			//"��InstanceTypeΪ6ʱ��Time05Ϊս����û�����ʱ�Զ��رյ�ʱ����ע��Time03+Time04<=Time05��
			InstanceTimeListCsvRow_Time6			,			//"��InstanceTypeΪ6ʱ��Time06û������

			InstanceTimeListCsvRow_Max,
		};
	public:
		InstanceTimeListCsv();
		~InstanceTimeListCsv();
		SINGLETON_INSTANCE(InstanceTimeListCsv);

		Bool							load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		InstanceTimeListCsvInfo*		getInfoById(U32 instanceTimeId);

		std::map<U32, InstanceTimeListCsvInfo*>*			getList();

	private:
		SimpleMapDataSetManager<U32, InstanceTimeListCsvInfo>		mInstanceTimeList;
	};
}

#endif	//_INSTANCE_TIME_LIST_CSV_H_