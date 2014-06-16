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
	//单个副本实例信息
	//*************************************************************************************************//
	struct InstanceTimeListCsvInfo
	{
		U32				instanceTimeId;
		InstanceType	instanceType;
		U32 			time1;	//"【注：Time01必须为副本在没有玩家时自动关闭的时长，如果没有就为“0”表示没有意义】
								//当InstanceType为2时，Time01为副本在没有玩家时自动关闭的时长
								//当InstanceType为4时，Time01为副本在没有玩家时自动关闭的时长
								//当InstanceType为6时，Time01为副本在没有玩家时自动关闭的时长
								//其他陆续补充"
		
		U32 			time2;	//"【注：Time02必须为副本进行的总时长（战斗时间，如：60分钟），如果没有就为“0”表示没有意义】
								//当InstanceType为2时，Time02没有意义
								//当InstanceType为4时，Time02为副本进行的总时长
								//当InstanceType为6时，Time02为副本进行的总时长
								//其他陆续补充"

		U32 			time3;	//"当InstanceType为2时，Time03没有意义
								//当InstanceType为4时，Time03没有意义
								//当InstanceType为6时，Time03为攻城战开始前的等待时长
								//其他陆续补充"

		U32 			time4;	//"当InstanceType为2时，Time04没有意义
								//当InstanceType为4时，Time04没有意义
								//当InstanceType为6时，Time04为停留在胜利或失败界面的时长
								//其他陆续补充"

		U32 			time5;	//"当InstanceType为2时，Time05没有意义
								//当InstanceType为4时，Time05没有意义
								//当InstanceType为6时，Time05为停留在领取奖励界面的时长
								//其他陆续补充"

		U32 			time6;	//"当InstanceType为2时，Time06没有意义
								//当InstanceType为4时，Time06没有意义
								//当InstanceType为6时，Time06为副本自动结束的总时长（注：Time04+Time05<=Time06）
								//其他陆续补充"


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
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum InstanceTimeListCsvRow
		{
			InstanceTimeListCsvRow_InstanceTimeId	,			//	副本时间ID
			InstanceTimeListCsvRow_Notes			,
			InstanceTimeListCsvRow_InstanceType		,			//副本类型
			InstanceTimeListCsvRow_Time1			,			//"当InstanceType为6时，Time01为攻城战开始前的等待时长
			InstanceTimeListCsvRow_Time2			,			//"当InstanceType为6时，Time02为攻城战役自动结束的总时长
			InstanceTimeListCsvRow_Time3			,			//"当InstanceType为6时，Time03为停留在胜利或失败界面的时长
			InstanceTimeListCsvRow_Time4			,			//"当InstanceType为6时，Time04为停留在领取奖励界面的时长
			InstanceTimeListCsvRow_Time5			,			//"当InstanceType为6时，Time05为战场在没有玩家时自动关闭的时长（注：Time03+Time04<=Time05）
			InstanceTimeListCsvRow_Time6			,			//"当InstanceType为6时，Time06没有意义

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