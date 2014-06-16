//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: GeneralRandomCsv.h
//        Author: yuanlinhu
//          Date: 2012-11-17
//          Time: 10:45
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-11-17      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _GENERAL_RANDOM_CSV_H_
#define _GENERAL_RANDOM_CSV_H_

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
	struct GeneralRandomCsvInfo
	{
		U32 GeneralRandomId;
		U32 GeneralGroupID;
		U32 CharacterTemplateId;
		U32 GeneralRandomNum;
		U32 AbilityInit1;
		U32 AbilityInit2;
		Int	LifeSpanRandom;

		GeneralRandomCsvInfo()
			:GeneralRandomId(0)
			,GeneralGroupID(0)
			,CharacterTemplateId(0)
			,GeneralRandomNum(0)
			,AbilityInit1(0)
			,AbilityInit2(0)
			,LifeSpanRandom(0)
		{
		}
	};

	//*************************************************************************************************//
	class GeneralRandomCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum GeneralRandomCsvRow
		{
			GeneralRandomCsvRow_GeneralRandomId,
			GeneralRandomCsvRow_Notes,
			GeneralRandomCsvRow_GeneralGroupID,						//将领分组的组别ID
			GeneralRandomCsvRow_CharacterTemplateId,				//角色模版ID
			GeneralRandomCsvRow_GeneralRandomNum,					//随机将领招募的圆桌区间值
			GeneralRandomCsvRow_AbilityInit1,						//随机初始属性ID1
			GeneralRandomCsvRow_AbilityInit2,						//随机初始属性ID2
			GeneralRandomCsvRow_CharacterSkillId1,					//技能分组ID1
			GeneralRandomCsvRow_CharacterSkillId2,					//技能分组ID2
			GeneralRandomCsvRow_CharacterArtIconGroupId,			//随机角色头像分组ID
			GeneralRandomCsvRow_CharacterArtModelGroupId,			//随机角色模型分组ID
			GeneralRandomCsvRow_LifeSpanRandom,						//寿命上限
			GeneralRandomCsvRow_GeneralRandomPrice,					//将领招募所需要的花费的物品
			GeneralRandomCsvRow_GeneralRandomAmount,				//将领招募花费物品的数量
			GeneralRandomCsvRow_Max
		};

	public:
		GeneralRandomCsv();
		~GeneralRandomCsv();
		SINGLETON_INSTANCE(GeneralRandomCsv);

		Bool									load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		GeneralRandomCsvInfo*					getInfoById(U32 id);
		std::vector<const GeneralRandomCsvInfo*>*		getRandomListByGeneralGroupId(U32 GeneralGroupId);
		std::map<U32, GeneralRandomCsvInfo*>*	getList();

	private:
		SimpleMapDataSetManager<U32, GeneralRandomCsvInfo>							mGeneralRandomList;
		std::map<U32/*GeneralGroupID*/, std::vector<const GeneralRandomCsvInfo*> >	mGeneralRandomByGroupId;
	};
}

#endif	//_GENERAL_RECRUIT_CSV_H_
