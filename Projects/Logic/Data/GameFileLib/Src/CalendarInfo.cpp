//******************************************************************************************
#include "stdafx.h"
#include "CalendarInfo.h"
//******************************************************************************************
namespace MG
{

	//-------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool CalendarInfos::load(Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
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
			CalendarInfo* tempInfo = MG_NEW CalendarInfo;

			MGStrOp::toU32(csvdata->mData[calendarinfoid].c_str(),tempInfo->id);
			tempInfo->name = csvdata->mData[calendarinfocalendarname];
			
			///现实起始日期
			Str16 tempStr1 = csvdata->mData[calendarinfotruetimebegin];
			Str16 tempStr2 ;
			I32 pos1 = -1;
			I32 pos2 = -1;
			pos2 = tempStr1.find(L'、');
			Int j = 0;
			for (j = 0; pos2 != -1; j++)
			{
				tempStr1.replace(pos2 ,1,1,L'@');
				tempStr2 = tempStr1.substr(pos1 + 1,pos2 - pos1 - 1);
				pos1 = pos2;
				pos2 = tempStr1.find(L'、');
				MGStrOp::toU32(tempStr2.c_str(),tempInfo->trueTimeBegin[j]);

                DEBUG_ASSERT_LOG((j < 5), "MGStrOp::toU32(tempStr2.c_str(),tempInfo->trueTimeBegin[j]);");
			}
			tempStr2 = tempStr1.substr(pos1 + 1,tempStr1.size() - pos1 - 1);
			MGStrOp::toU32(tempStr2.c_str(),tempInfo->trueTimeBegin[j]);

			///历法起始日期
			tempStr1 = csvdata->mData[calendarinfocalendarbegin];
			pos1 = -1;
			pos2 = tempStr1.find(L'、');
			for (j = 0; pos2 != -1; j++)
			{
				tempStr1.replace(pos2 ,1,1,L'@');
				tempStr2 = tempStr1.substr(pos1 + 1,pos2 - pos1 - 1);
				pos1 = pos2;
				pos2 = tempStr1.find(L'、');
				MGStrOp::toU32(tempStr2.c_str(),tempInfo->calendarBegin[j]);
                DEBUG_ASSERT_LOG((j < 4), "MGStrOp::toU32(tempStr2.c_str(),tempInfo->calendarBegin[j]);");
			}
			tempStr2 = tempStr1.substr(pos1 + 1,tempStr1.size() - pos1 - 1);
			MGStrOp::toU32(tempStr2.c_str(),tempInfo->calendarBegin[j]);
			
			MGStrOp::toU32(csvdata->mData[calendarinfotimeunit].c_str(),tempInfo->timeUnit);
			MGStrOp::toU32(csvdata->mData[calendarinfohour].c_str(),tempInfo->hour);
			MGStrOp::toU32(csvdata->mData[calendarinfoday].c_str(),tempInfo->day);
			MGStrOp::toU32(csvdata->mData[calendarinfomonth].c_str(),tempInfo->month);
			MGStrOp::toU32(csvdata->mData[calendarinfoseason].c_str(),tempInfo->season);
			MGStrOp::toU32(csvdata->mData[calendarinfoyear].c_str(),tempInfo->year);
			
			///hour name
			tempStr1 = csvdata->mData[calendarinfohourname];
			pos1 = -1;
			pos1 = -1;
			pos2 = tempStr1.find(L'、');
			for (j = 0; pos2 != -1; j++)
			{
				tempStr1.replace(pos2 ,1,1,L'@');
				tempStr2 = tempStr1.substr(pos1 + 1,pos2 - pos1 - 1);
				pos1 = pos2;
				pos2 = tempStr1.find(L'、');
				tempInfo->hourName[j] = tempStr2;
				DYNAMIC_ASSERT(j < CALENDARINFO_HOUR_MAX_COUNT - 1);
			}
			tempStr2 = tempStr1.substr(pos1 + 1,tempStr1.size() - pos1 - 1);
			tempInfo->hourName[j] = tempStr2;


			///day name
			tempStr1 = csvdata->mData[calendarinfodayname];
			pos1 = -1;
			pos2 = tempStr1.find(L'、');
			for (j = 0; pos2 != -1; j++)
			{
				tempStr1.replace(pos2 ,1,1,L'@');
				tempStr2 = tempStr1.substr(pos1 + 1,pos2 - pos1 - 1);
				pos1 = pos2;
				pos2 = tempStr1.find(L'、');
				tempInfo->dayName[j] = tempStr2;
				DYNAMIC_ASSERT(j < CALENDARINFO_DAY_MAX_COUNT - 1);
			}
			tempStr2 = tempStr1.substr(pos1 + 1,tempStr1.size() - pos1 - 1);
			tempInfo->dayName[j] = tempStr2;


			///month name
			tempStr1 = csvdata->mData[calendarinfomonthname];
			pos1 = -1;
			pos2 = tempStr1.find(L'、');
			for (j = 0; pos2 != -1; j++)
			{
				tempStr1.replace(pos2 ,1,1,L'@');
				tempStr2 = tempStr1.substr(pos1 + 1,pos2 - pos1 - 1);
				pos1 = pos2;
				pos2 = tempStr1.find(L'、');
				tempInfo->monthName[j] = tempStr2;
				DYNAMIC_ASSERT(j < CALENDARINFO_MONTH_MAX_COUNT - 1);
			}

			///season name
			tempStr1 = csvdata->mData[calendarinfoseasonname];
			pos1 = -1;
			pos2 = tempStr1.find(L'、');
			for (j = 0; pos2 != -1; j++)
			{
				tempStr1.replace(pos2 ,1,1,L'@');
				tempStr2 = tempStr1.substr(pos1 + 1,pos2 - pos1 - 1);
				pos1 = pos2;
				pos2 = tempStr1.find(L'、');
				tempInfo->seasonName[j] = tempStr2;
				DYNAMIC_ASSERT(j < CALENDARINFO_SEASON_MAX_COUNT - 1);
			}
			tempStr2 = tempStr1.substr(pos1 + 1,tempStr1.size() - pos1 - 1);
			tempInfo->seasonName[j] = tempStr2;

			///year name
			tempStr1 = csvdata->mData[calendarinfoyearname];
			pos1 = -1;
			pos2 = tempStr1.find(L'、');
			for (j = 0; pos2 != -1; j++)
			{
				tempStr1.replace(pos2 ,1,1,L'@');
				tempStr2 = tempStr1.substr(pos1 + 1,pos2 - pos1 - 1);
				pos1 = pos2;
				pos2 = tempStr1.find(L'、');
				tempInfo->yearName[j] = tempStr2;
				DYNAMIC_ASSERT(j < CALENDARINFO_YEAR_MAX_COUNT - 1);
			}
			tempStr2 = tempStr1.substr(pos1 + 1,tempStr1.size() - pos1 - 1);
			tempInfo->yearName[j] = tempStr2;
			

			///地支
			tempStr1 = csvdata->mData[calendarinfodizhiname];
			pos1 = -1;
			pos2 = tempStr1.find(L'、');
			for (j = 0; pos2 != -1; j++)
			{
				tempStr1.replace(pos2 ,1,1,L'@');
				tempStr2 = tempStr1.substr(pos1 + 1,pos2 - pos1 - 1);
				pos1 = pos2;
				pos2 = tempStr1.find(L'、');
				tempInfo->diZhiName[j] = tempStr2;
				DYNAMIC_ASSERT(j < CALENDARINFO_DIZHI_MAX_COUNT - 1);
			}
			tempStr2 = tempStr1.substr(pos1 + 1,tempStr1.size() - pos1 - 1);
			tempInfo->diZhiName[j] = tempStr2;
			

			if (getCalendarInfo(tempInfo->id))
			{
				DYNAMIC_ASSERT(false);
				MG_SAFE_DELETE(tempInfo);
				continue;
			}
			mCalendarInfoMap[tempInfo->id] = tempInfo;
		}
		return true;
	}
	//-------------------------------------------------------------------------------------------
	const CalendarInfo* CalendarInfos::getCalendarInfo( U32 id )
	{
		std::map<U32, CalendarInfo*>::iterator it = mCalendarInfoMap.find(id);
		if (it != mCalendarInfoMap.end())
		{
			return it->second;
		}
		return NULL;
	}
	//-------------------------------------------------------------------------------------------
	void CalendarInfos::clear()
	{
		std::map<U32, CalendarInfo*>::iterator it = mCalendarInfoMap.begin();
		for (; it != mCalendarInfoMap.end(); it++)
		{
			MG_SAFE_DELETE(it->second);
		}
		mCalendarInfoMap.clear();
	}
	//-------------------------------------------------------------------------------------------
	CalendarInfos::CalendarInfos()
	{

	}
	//-------------------------------------------------------------------------------------------
	CalendarInfos::~CalendarInfos()
	{
        clear();
	}

}
//******************************************************************************************