/******************************************************************************/
#include "stdafx.h"
#include "Dialog.h"
/******************************************************************************/
namespace MG
{
	

	DialogInfos::DialogInfos()
	{


	}

	DialogInfos::~DialogInfos()
	{

	}

	// MG_CN_MODIFY
	MG::Bool DialogInfos::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(fileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int rowCount = csvreader.count();
		for(Int i = 0; i < rowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}
			DialogInfo* tempInfo = MG_NEW DialogInfo;

			MGStrOp::toU32(csvdata->mData[id].c_str(),tempInfo->id);
            tempInfo->modestNameForSelf = csvdata->mData[modestnameformyself].c_str();
            tempInfo->prideNameForSelf = csvdata->mData[pridenameformyself].c_str();
            tempInfo->respectNameForOther = csvdata->mData[respectnameforother].c_str();
            tempInfo->slandeNameForOther = csvdata->mData[slandernameforother].c_str();
			tempInfo->specialRespectNameForOther = csvdata->mData[specialrespectnameforother].c_str();
			tempInfo->specialSlandeNameForOther = csvdata->mData[specialslandernameforother].c_str();
            
			tempInfo->normalContent1 = csvdata->mData[normaldialog1].c_str();
			tempInfo->normalContent2 = csvdata->mData[normaldialog2].c_str();
			tempInfo->fightContent1 = csvdata->mData[fightdialog1].c_str();
			tempInfo->fightContent2 = csvdata->mData[fightdialog2].c_str();
			tempInfo->woundContent1 = csvdata->mData[wounddialog1].c_str();
			tempInfo->woundContent2 = csvdata->mData[wounddialog2].c_str();
			tempInfo->winContent1 = csvdata->mData[windialog1].c_str();
			tempInfo->winContent2 = csvdata->mData[windialog2].c_str();
			tempInfo->failContent1 = csvdata->mData[faildialog1].c_str();
			tempInfo->failContent2 = csvdata->mData[faildialog2].c_str();
            //////////////////////////////////////////////////////////////////////////
			mDialogMap[tempInfo->id] = tempInfo;
		}
		return true;
	}

	DialogInfo* DialogInfos::getDialogInfo( U32 id )
	{
		std::map<U32, DialogInfo*>::iterator it = mDialogMap.find(id);
		if (it != mDialogMap.end())
		{
			return it->second;
		}
		return NULL;
	}

	void DialogInfos::clear()
	{

	}

}