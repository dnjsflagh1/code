//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: CharacterRandNameCsv.h
//        Author: yuanlinhu
//          Date: 2012-11-22
//          Time: 10:45
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-11-22      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _CHARACTER_RAND_NAME_CSV_H_
#define _CHARACTER_RAND_NAME_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{


	//*************************************************************************************************//
	//部分需要的枚举
	//*************************************************************************************************//
	enum CRN_UerType
	{
		CRN_UerType_Null,			// 0~无意义
		
		CRN_UerType_Male,			// 1~男性
		CRN_UerType_Female,			// 2~女性
		CRN_UerType_Common,			// 3~男女通用
		
		CRN_UerType_Max
	};

	enum CRN_NameType
	{
		CRN_NameType_Null,			// 0~无意义

		CRN_NameType_Xing,			// 1~姓
		CRN_NameType_Ming,			// 2~名
		CRN_NameType_JunWang,		// 3~郡望		

		CRN_NameType_Max
	};

	//*************************************************************************************************//
	//单个副本实例信息
	//*************************************************************************************************//
	struct CharacterRandNameCsvInfo
	{
		U32				RandNameId;
		CRN_UerType		UserType;
		CRN_NameType	NameType;
		Str16			Text;
	

		CharacterRandNameCsvInfo()
			:RandNameId(0)
			,UserType(CRN_UerType_Null)
			,NameType(CRN_NameType_Null)
		{
		}
	};

	//*************************************************************************************************//
	class CharacterRandNameCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum CharacterRandNameCsvRow
		{
			CharacterRandNameCsvRow_RandNameId,			//随机名字序号
			CharacterRandNameCsvRow_Notes,
			CharacterRandNameCsvRow_UserType,			//性别类型
			CharacterRandNameCsvRow_NameType,			//名字类型
			CharacterRandNameCsvRow_Text,				//文字

			CharacterRandNameCsvRow_Max
		};

	public:
		CharacterRandNameCsv();
		~CharacterRandNameCsv();
		SINGLETON_INSTANCE(CharacterRandNameCsv);

		Bool										load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		CharacterRandNameCsvInfo*					getInfoById(U32 id);
		std::map<U32, CharacterRandNameCsvInfo*>*	getList();

		Str16				getRandCommonXing(); 	//随机获取通用的【姓】
		
		Str16				getRandMaleMing(); 		//随机获取【男】性角色可用的【名】
		Str16				getRandFeMaleMing(); 	//随机获取【女】性角色可用的【名】

		//根据性别获取随机名字
		Str16				getRandMingBySexual(GENDER_TYPE type);
		std::vector<CharacterRandNameCsvInfo*>*				getJunWangList(){return &mJunWangList;};
		std::vector<CharacterRandNameCsvInfo*>*				getCommonMingList(){return &mCommonMingList;};
		std::vector<CharacterRandNameCsvInfo*>*				getCommonXingList(){return &mCommonXingList;};

	private:
		void				addToMaleXingList(CharacterRandNameCsvInfo*);
		void				addToMaleMingList(CharacterRandNameCsvInfo*);
		void				addToFeMaleXingList(CharacterRandNameCsvInfo*);
		void				addToFeMaleMingList(CharacterRandNameCsvInfo*);
		void				addToCommonXingList(CharacterRandNameCsvInfo*);
		void				addToCommonMingList(CharacterRandNameCsvInfo*);
		void				addToJunWangList(CharacterRandNameCsvInfo*);

	private:
		SimpleMapDataSetManager<U32, CharacterRandNameCsvInfo>		mCharacterRandNameList;
		std::vector<CharacterRandNameCsvInfo*>						mMaleXingList;		//男性角色可用的"姓"
		std::vector<CharacterRandNameCsvInfo*>						mMaleMingList;		//男性角色可用的"名"
		std::vector<CharacterRandNameCsvInfo*>						mFeMaleXingList;	//女性角色可用的"姓"
		std::vector<CharacterRandNameCsvInfo*>						mFeMaleMingList;	//女性角色可用的"名"
		std::vector<CharacterRandNameCsvInfo*>						mCommonXingList;	//通用的"姓"
		std::vector<CharacterRandNameCsvInfo*>						mCommonMingList;	//通用的"名"
		std::vector<CharacterRandNameCsvInfo*>						mJunWangList;

		Int mMaleXingNum;
		Int mMaleMingNum;
		Int mFeMaleXingNum;
		Int mFeMaleMingNum;
		Int mCommonXingNum;
		Int mCommonMingNum;
		Int mJunWangNum;
	};
}

#endif	//_CHARACTER_RAND_NAME_CSV_H_
