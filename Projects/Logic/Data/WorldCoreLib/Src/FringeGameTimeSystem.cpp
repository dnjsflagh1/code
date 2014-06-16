/******************************************************************************/
#include "stdafx.h"
#include "FringeGameTimeSystem.h"
#include "CalendarInfo.h"
/******************************************************************************/
namespace MG
{
	
	//-----------------------------------------------------------------------------
	FringeGameTimeSystem::FringeGameTimeSystem()
	{
		mIsValid = false;
		mCalendarInfo = NULL;
		mGameStartActualTime = 0;
	}
	//-----------------------------------------------------------------------------
	FringeGameTimeSystem::~FringeGameTimeSystem()
	{
		mCalendarInfo = NULL;
	}
	//-----------------------------------------------------------------------------
	Bool FringeGameTimeSystem::initialize()
	{
		mCalendarInfo = CalendarInfos::getInstance().getCalendarInfo(1);
		if (!mCalendarInfo)
		{
			return false;
		}
		mGameStartActualTime = MGTimeOp::createtimestamp(
			mCalendarInfo->trueTimeBegin[0],mCalendarInfo->trueTimeBegin[1],
			mCalendarInfo->trueTimeBegin[2],mCalendarInfo->trueTimeBegin[3],
			mCalendarInfo->trueTimeBegin[4],mCalendarInfo->trueTimeBegin[5]);

		return true;
	}
	//-----------------------------------------------------------------------------
	void FringeGameTimeSystem::update()
	{
		static U32 lastTick = MGTimeOp::getCurrTick();
		static U32 currTick = lastTick;
		static Str8 temp;
		mSystemTick = currTick = MGTimeOp::getCurrTick();
		static U32 diff =  mCalendarInfo->timeUnit * 1000;
		if (currTick - lastTick >= diff)
		{
			lastTick = currTick;
			MG::MGStrOp::toString(getCurrGameTime().c_str(),temp);
			printf("%s\n",temp.c_str());
			onTimer();
			
		}
		
	}
	//-----------------------------------------------------------------------------
	Bool FringeGameTimeSystem::unInitialize()
	{
		return true;
	}
	//-----------------------------------------------------------------------------
	U64 FringeGameTimeSystem::getCurrActualTime(  )
	{
		if (mIsValid)
		{
			return mBaseTime + U64( ( MGTimeOp::getCurrTick() - mSystemTick ) * 0.001 );
		}
		else
		{
			return 0;
		}
	}
	//-----------------------------------------------------------------------------
	void FringeGameTimeSystem::setCurrActualTime( U64 actualTime )
	{
		mBaseTime = actualTime;
		mSystemTick = MGTimeOp::getCurrTick();
		mIsValid = true;
	}
	//-----------------------------------------------------------------------------
	Bool FringeGameTimeSystem::getCurrGameTime( U32& year,U32&season,U32& mon,U32& day,U32& hour )
	{
		if (mCalendarInfo && mIsValid)
		{
			U64 timeOffect = getCurrActualTime() - mGameStartActualTime;
			year  =		 (U32)(timeOffect / (mCalendarInfo->year  * mCalendarInfo->timeUnit) ) + mCalendarInfo->calendarBegin[0];
			season =	((U32)(timeOffect / (mCalendarInfo->season * mCalendarInfo->timeUnit) ) + mCalendarInfo->calendarBegin[1] ) % CALENDARINFO_SEASON_MAX_COUNT;
			mon =		((U32)(timeOffect / (mCalendarInfo->month * mCalendarInfo->timeUnit) ) + mCalendarInfo->calendarBegin[2] ) % CALENDARINFO_MONTH_MAX_COUNT;
			
			if (season == 0)
			{
				season = CALENDARINFO_SEASON_MAX_COUNT;
			}
			if (mon == 0)
			{
				mon = CALENDARINFO_MONTH_MAX_COUNT;
			}
			day = ((U32)(timeOffect / (mCalendarInfo->day   * mCalendarInfo->timeUnit) ) + mCalendarInfo->calendarBegin[3] ) % CALENDARINFO_DAY_MAX_COUNT;
			if (day == 0)
			{
				day = CALENDARINFO_DAY_MAX_COUNT;
			}
			hour =((U32)(timeOffect / (mCalendarInfo->hour  * mCalendarInfo->timeUnit) ) + mCalendarInfo->calendarBegin[4] ) % CALENDARINFO_HOUR_MAX_COUNT;
			if (hour == 0)
			{
				hour = CALENDARINFO_HOUR_MAX_COUNT;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	//-----------------------------------------------------------------------------
	Str16 FringeGameTimeSystem::getCurrGameTime()
	{
		Str16 tempTime = L"";
		Char16 gameTime[64] = {0};
		U32 year,season,mon,day,hour;
		if (getCurrGameTime(year,season,mon,day,hour))
		{
			//U32 dizhiIndex = (year) % CALENDARINFO_DIZHI_MAX_COUNT;
			//U32 tianganIndex = (year) % CALENDARINFO_HOUR_MAX_COUNT;

			MGStrOp::sprintf(gameTime,64,L"%s%s年%s月%s%s时",
				mCalendarInfo->name.c_str(),
				NumberToChinese::convertNumToChineseW(year).c_str(),
				//mCalendarInfo->diZhiName[dizhiIndex].c_str(),
				//mCalendarInfo->hourName[tianganIndex].c_str(),
				//mCalendarInfo->seasonName[season - 1].c_str(),
				NumberToChinese::convertNumToChineseW(mon).c_str(),
				mCalendarInfo->dayName[day - 1].c_str(),
				mCalendarInfo->hourName[hour - 1].c_str());
			tempTime = gameTime;
		}
		return tempTime;
		
	}
	//-----------------------------------------------------------------------------
	Bool FringeGameTimeSystem::getGameTimeByActualTime( U64 actualTime,U32& year,U32&season,U32& mon,U32& day,U32& hour )
	{
		U64 timeOffect = actualTime - mGameStartActualTime;
		if (timeOffect < 0)
		{
			return false;
		}
		year  =		 (U32)(timeOffect / (mCalendarInfo->year  * mCalendarInfo->timeUnit) ) + mCalendarInfo->calendarBegin[0];
		season =	((U32)(timeOffect / (mCalendarInfo->season * mCalendarInfo->timeUnit) ) + mCalendarInfo->calendarBegin[1] ) % CALENDARINFO_SEASON_MAX_COUNT;
		mon =		((U32)(timeOffect / (mCalendarInfo->month * mCalendarInfo->timeUnit) ) + mCalendarInfo->calendarBegin[2] ) % CALENDARINFO_MONTH_MAX_COUNT;
		
		if (season == 0)
		{
			season = CALENDARINFO_SEASON_MAX_COUNT;
		}		
		if (mon == 0)
		{
			mon = CALENDARINFO_MONTH_MAX_COUNT;
		}
		day = ((U32)(timeOffect / (mCalendarInfo->day   * mCalendarInfo->timeUnit) ) + mCalendarInfo->calendarBegin[2] ) % CALENDARINFO_DAY_MAX_COUNT;
		if (day == 0)
		{
			day = CALENDARINFO_DAY_MAX_COUNT;
		}
		hour =((U32)(timeOffect / (mCalendarInfo->hour  * mCalendarInfo->timeUnit) ) + mCalendarInfo->calendarBegin[3] ) % CALENDARINFO_HOUR_MAX_COUNT;
		if (hour == 0)
		{
			hour = CALENDARINFO_HOUR_MAX_COUNT;
		}
		return true;
	}
	//-----------------------------------------------------------------------------
	Str16 FringeGameTimeSystem::getGameTimeByActualTime( U64 actualTime )
	{
		Str16 tempTime = L"";
		Char16 gameTime[64] = {0};
		U32 year,season,mon,day,hour;
		if (getGameTimeByActualTime(actualTime,year,season,mon,day,hour))
		{
			//U32 dizhiIndex = (year) % CALENDARINFO_DIZHI_MAX_COUNT;
			//U32 tianganIndex = (year) % CALENDARINFO_HOUR_MAX_COUNT;

			MGStrOp::sprintf(gameTime,64,L"%s%s年%s月%s%s时",
				mCalendarInfo->name.c_str(),
				NumberToChinese::convertNumToChineseW(year).c_str(),
				//mCalendarInfo->diZhiName[dizhiIndex].c_str(),
				//mCalendarInfo->hourName[tianganIndex].c_str(),
				//mCalendarInfo->seasonName[season - 1].c_str(),
				NumberToChinese::convertNumToChineseW(mon).c_str(),
				mCalendarInfo->dayName[day - 1].c_str(),
				mCalendarInfo->hourName[hour - 1].c_str());
			tempTime = gameTime;
		}
		return tempTime;
	}
	//-----------------------------------------------------------------------------
	void FringeGameTimeSystem::getCenterActualTime()
	{

	}
}
