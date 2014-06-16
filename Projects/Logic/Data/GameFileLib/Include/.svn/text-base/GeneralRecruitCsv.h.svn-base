//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: GeneralRecruitCsv.h
//        Author: yuanlinhu
//          Date: 2012-4-13
//          Time: 10:45
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-9-18      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _GENERAL_RECRUIT_CSV_H_
#define _GENERAL_RECRUIT_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//
//#define  MAX_RECUIT_NUM 5

namespace MG
{


	//*************************************************************************************************//
	//部分需要的枚举
	//*************************************************************************************************//
	

	//*************************************************************************************************//
	//单个副本实例信息
	//*************************************************************************************************//
	struct GeneralRecruitCsvInfo
	{
		U32		GeneralRecruitID;
		U32		GeneralRecruitType;
		U32		GeneralRecruitClanJudge;
		U32		GeneralRandomItemAmount;
		U32		GeneralRandomDegree;
		U32		GeneralRandomTimepieceId;
		U64		GeneralRandomTime;
		U32		GeneralGroupID[RECRUIT_POSITION_MAX];
		//U32		GeneralGroupID2;
		//U32		GeneralGroupID3;
		//U32		GeneralGroupID4;
		//U32		GeneralGroupID5;
		//U32		GeneralGroupID6;

		GeneralRecruitCsvInfo()
			:GeneralRecruitID(0)
			,GeneralRecruitType(0)
			,GeneralRecruitClanJudge(0)
			,GeneralRandomItemAmount(0)
			,GeneralRandomDegree(0)
			,GeneralRandomTimepieceId(0)
			,GeneralRandomTime(0)
			//,GeneralGroupID1(0)
			//,GeneralGroupID2(0)
			//,GeneralGroupID3(0)
			//,GeneralGroupID4(0)
			//,GeneralGroupID5(0)
			//,GeneralGroupID6(0)
		{
			memset(GeneralGroupID, 0, sizeof(GeneralGroupID));
		}
	};

	//*************************************************************************************************//
	class GeneralRecruitCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum GeneralRecruitCsvRow
		{
			GeneralRecruitCsvRow_GeneralRecruitID,
			GeneralRecruitCsvRow_Notes,
			GeneralRecruitCsvRow_GeneralRecruitType,
			GeneralRecruitCsvRow_GeneralRecruitClanJudge,
			GeneralRecruitCsvRow_GeneralRandomItem,
			GeneralRecruitCsvRow_GeneralRandomItemAmount,
			GeneralRecruitCsvRow_GeneralRandomDegree,
			GeneralRecruitCsvRow_GeneralRandomTimepieceId,
			GeneralRecruitCsvRow_GeneralRandomTime,
			GeneralRecruitCsvRow_GeneralGroupID1,
			GeneralRecruitCsvRow_GeneralGroupID2,
			GeneralRecruitCsvRow_GeneralGroupID3,
			GeneralRecruitCsvRow_GeneralGroupID4,
			GeneralRecruitCsvRow_GeneralGroupID5,
			GeneralRecruitCsvRow_GeneralGroupID6,

			GeneralRecruitCsvRow_Max
		};

	public:
		GeneralRecruitCsv();
		~GeneralRecruitCsv();
		SINGLETON_INSTANCE(GeneralRecruitCsv);

		Bool									load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		GeneralRecruitCsvInfo*					getInfoById(U32 id);
		std::map<U32, GeneralRecruitCsvInfo*>*	getList();

	private:
		SimpleMapDataSetManager<U32, GeneralRecruitCsvInfo>		mGeneralRecruitList;
	};
}

#endif	//_GENERAL_RECRUIT_CSV_H_
