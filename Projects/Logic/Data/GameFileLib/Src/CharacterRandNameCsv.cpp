/******************************************************************************/

#include "stdafx.h"
#include "CharacterRandNameCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	CharacterRandNameCsv::CharacterRandNameCsv()
		:mMaleXingNum(0)
		,mMaleMingNum(0)
		,mFeMaleXingNum(0)
		,mFeMaleMingNum(0)
		,mCommonXingNum(0)
		,mCommonMingNum(0)
		,mJunWangNum(0)
	{

	}

	//--------------------------------------------------------------------------
	CharacterRandNameCsv::~CharacterRandNameCsv()
	{

	}

	//--------------------------------------------------------------------------
	Bool CharacterRandNameCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == CharacterRandNameCsvRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}


			U32		RandNameId = 0;
			MGStrOp::toU32(csvdata->mData[CharacterRandNameCsvRow_RandNameId].c_str(), RandNameId);
			if (true == mCharacterRandNameList.hasData(RandNameId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}


			I32		UserType = 0;
			MGStrOp::toI32(csvdata->mData[CharacterRandNameCsvRow_UserType].c_str(), UserType);


			I32		NameType = 0;
			MGStrOp::toI32(csvdata->mData[CharacterRandNameCsvRow_NameType].c_str(), NameType);


			CharacterRandNameCsvInfo* newInfo = mCharacterRandNameList.createOrRetrieve(RandNameId, false);
			newInfo->RandNameId		= RandNameId;
			newInfo->UserType		= (CRN_UerType)UserType;
			newInfo->NameType		= (CRN_NameType)NameType;
			newInfo->Text			= csvdata->mData[CharacterRandNameCsvRow_Text];
			
			DYNAMIC_ASSERT(newInfo->UserType > CRN_UerType_Null && newInfo->UserType < CRN_UerType_Max );
			DYNAMIC_ASSERT(newInfo->NameType > CRN_NameType_Null && newInfo->NameType < CRN_NameType_Max );
			//姓 只能通用
			if (newInfo->NameType == CRN_NameType_Xing)
			{
				DYNAMIC_ASSERT(newInfo->UserType == CRN_UerType_Common);
			}
			DYNAMIC_ASSERT(newInfo->Text.empty() == false);

			std::map<U32, CharacterRandNameCsvInfo>::iterator iter;
			if (newInfo->UserType == CRN_UerType_Male)
			{
				//男用
				if (CRN_NameType_Xing == newInfo->NameType)
				{
					//姓
					addToMaleXingList(newInfo);
				}
				else if(CRN_NameType_Ming == newInfo->NameType)
				{
					//名
					addToMaleMingList(newInfo);
				}
				else
				{
					DYNAMIC_ASSERT(0);
				}
			}
			else if(newInfo->UserType == CRN_UerType_Female)
			{
				//女用
				if (CRN_NameType_Xing == newInfo->NameType)
				{
					//姓
					addToFeMaleXingList(newInfo);
				}
				else if(CRN_NameType_Ming == newInfo->NameType)
				{
					//名
					addToFeMaleMingList(newInfo);
				}
				else
				{
					DYNAMIC_ASSERT(0);
				}

			}
			else if(newInfo->UserType == CRN_UerType_Common)
			{
				//通用
				if (CRN_NameType_Xing == newInfo->NameType)
				{
					//姓
					addToCommonXingList(newInfo);
				}
				else if(CRN_NameType_Ming == newInfo->NameType)
				{
					//名
					addToCommonMingList(newInfo);
				}
				else if (CRN_NameType_JunWang == newInfo->NameType)
				{
					addToJunWangList(newInfo);
				}
				else
				{
					DYNAMIC_ASSERT(0);
				}

			}
			else
			{
				DYNAMIC_ASSERT(0);
			}
		}

		DYNAMIC_ASSERT(mMaleXingList.empty() == false);
		DYNAMIC_ASSERT(mMaleMingList.empty() == false);
		DYNAMIC_ASSERT(mFeMaleXingList.empty() == false);
		DYNAMIC_ASSERT(mFeMaleMingList.empty() == false);
		DYNAMIC_ASSERT(mCommonXingList.empty() == false);
		//DYNAMIC_ASSERT(mCommonMingList.empty() == false);
		DYNAMIC_ASSERT(mMaleXingNum > 0);
		DYNAMIC_ASSERT(mMaleMingNum > 0);
		DYNAMIC_ASSERT(mFeMaleXingNum > 0);
		DYNAMIC_ASSERT(mFeMaleMingNum > 0);
		DYNAMIC_ASSERT(mCommonXingNum > 0);
		//DYNAMIC_ASSERT(mCommonMingNum > 0);
		DYNAMIC_ASSERT(mMaleXingNum == mCommonXingNum && mFeMaleXingNum == mCommonXingNum);

		return true;
	}

	//--------------------------------------------------------------------------
	CharacterRandNameCsvInfo* CharacterRandNameCsv::getInfoById(U32 id)
	{
		return mCharacterRandNameList.getData(id);
	}

	//--------------------------------------------------------------------------
	std::map<U32, CharacterRandNameCsvInfo*>* CharacterRandNameCsv::getList()
	{
		return mCharacterRandNameList.getDataSet();
	}

	//--------------------------------------------------------------------------
	void CharacterRandNameCsv::addToMaleXingList(CharacterRandNameCsvInfo* newInfo)
	{
		//std::vector<CharacterRandNameCsvInfo*>::iterator iter = mMaleXingList.find(newInfo->RandNameId);
		//if (iter != mMaleXingList.end())
		//{
		//	//重复
		//	DYNAMIC_ASSERT(0);
		//}

		mMaleXingList.push_back(newInfo);
		mMaleXingNum++;
	}

	//--------------------------------------------------------------------------
	void CharacterRandNameCsv::addToMaleMingList(CharacterRandNameCsvInfo* newInfo)
	{
		//std::vector<CharacterRandNameCsvInfo*>::iterator iter = mMaleMingList.find(newInfo->RandNameId);
		//if (iter != mMaleMingList.end())
		//{
		//	//重复
		//	DYNAMIC_ASSERT(0);
		//}

		mMaleMingList.push_back(newInfo);
		mMaleMingNum++;
	}

	//--------------------------------------------------------------------------
	void CharacterRandNameCsv::addToFeMaleXingList(CharacterRandNameCsvInfo* newInfo)
	{
		//std::vector<CharacterRandNameCsvInfo*>::iterator iter = mFeMaleXingList.find(newInfo->RandNameId);
		//if (iter != mFeMaleXingList.end())
		//{
		//	//重复
		//	DYNAMIC_ASSERT(0);
		//}

		mFeMaleXingList.push_back(newInfo);
		mFeMaleXingNum++;
	}

	//--------------------------------------------------------------------------
	void CharacterRandNameCsv::addToFeMaleMingList(CharacterRandNameCsvInfo* newInfo)
	{
		//std::vector< CharacterRandNameCsvInfo*>::iterator iter = mFeMaleMingList.find(newInfo->RandNameId);
		//if (iter != mFeMaleMingList.end())
		//{
		//	//重复
		//	DYNAMIC_ASSERT(0);
		//}

		mFeMaleMingList.push_back(newInfo);
		mFeMaleMingNum++;
	}

	//--------------------------------------------------------------------------
	void CharacterRandNameCsv::addToCommonXingList(CharacterRandNameCsvInfo* newInfo)
	{
		//std::vector<CharacterRandNameCsvInfo*>::iterator iter = mCommonXingList.find(newInfo->RandNameId);
		//if (iter != mCommonXingList.end())
		//{
		//	//重复
		//	DYNAMIC_ASSERT(0);
		//}

		mCommonXingList.push_back(newInfo);
		mCommonXingNum++;

		addToMaleXingList(newInfo);
		addToFeMaleXingList(newInfo);
	}
	//--------------------------------------------------------------------------
	void CharacterRandNameCsv::addToJunWangList(CharacterRandNameCsvInfo* newInfo)
	{
		mJunWangList.push_back(newInfo);
		mJunWangNum++;
	}
	//--------------------------------------------------------------------------
	void CharacterRandNameCsv::addToCommonMingList(CharacterRandNameCsvInfo* newInfo)
	{
		//std::vector<CharacterRandNameCsvInfo*>::iterator iter = mCommonMingList.find(newInfo->RandNameId);
		//if (iter != mCommonMingList.end())
		//{
		//	//重复
		//	DYNAMIC_ASSERT(0);
		//}

		mCommonMingList.push_back(newInfo);
		mCommonMingNum++;
		addToMaleMingList(newInfo);
		addToFeMaleMingList(newInfo);
	}

	//--------------------------------------------------------------------------
	Str16 CharacterRandNameCsv::getRandCommonXing()
	{
		Int tempRandom = MGRandom::getInstance().rand_ab_One(0, mCommonXingNum);
		return mCommonXingList[tempRandom]->Text;
	}

	//--------------------------------------------------------------------------
	Str16 CharacterRandNameCsv::getRandMaleMing()
	{
		Int tempRandom = MGRandom::getInstance().rand_ab_One(0, mMaleMingNum);
		return mMaleMingList[tempRandom]->Text;
	}

	//--------------------------------------------------------------------------
	Str16 CharacterRandNameCsv::getRandFeMaleMing()
	{
		Int tempRandom = MGRandom::getInstance().rand_ab_One(0, mFeMaleMingNum);
		return mFeMaleMingList[tempRandom]->Text;
	}

	Str16 CharacterRandNameCsv::getRandMingBySexual(GENDER_TYPE type)
	{
		if (GENDER_TYPE_MAN == type)
		{
			return getRandMaleMing();
		}
		else if (GENDER_TYPE_WOMAN == type)
		{
			return getRandFeMaleMing();
		}
		else if (GENDER_TYPE_NONE_SEX == type)
		{
			DYNAMIC_ASSERT(0);
			return L"";
		}
		else
		{
			DYNAMIC_ASSERT(0);
			return L"";
		}

		return L"";
	}
}