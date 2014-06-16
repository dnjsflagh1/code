//******************************************************************************************
#ifndef _CALENDARINFO_H_
#define _CALENDARINFO_H_
//******************************************************************************************
#include "GameFilePreqs.h"
//******************************************************************************************
namespace MG
{
    //-----------------------------------------------------------------------------
    enum 
    {
		calendarinfoid,
		calendarinfonote,
		calendarinfocalendarname,
		calendarinfotruetimebegin,
		calendarinfocalendarbegin,
		calendarinfotimeunit,
		calendarinfohour,
		calendarinfoday,
		calendarinfomonth,
		calendarinfoseason,
		calendarinfoyear,
		calendarinfohourname,
		calendarinfodayname,
		calendarinfomonthname,
		calendarinfoseasonname,
		calendarinfoyearname,
		calendarinfodizhiname,
    };
    //-----------------------------------------------------------------------------
    struct CalendarInfo
    {
		U32			id;					///历法编号
		Str16		name;				///历法名称
		U32			trueTimeBegin[6];	///历法开始时时间的真实时间
		U32			calendarBegin[5];	///历法的起始时间
		U32			timeUnit;			///历法的最小单位时间（真实时间多少秒）
		U32			hour;				///历法的时（多少最小单位）
		U32			day;				///历法的天（多少最小单位）
		U32			month;				///历法的月（多少最小单位）
		U32			season;				///历法的季节（多少最小单位）
		U32			year;				///历法的年（多少最小单位）

		Str16		hourName[CALENDARINFO_HOUR_MAX_COUNT];
		Str16		yearName[CALENDARINFO_YEAR_MAX_COUNT];
		Str16		monthName[CALENDARINFO_MONTH_MAX_COUNT];
		Str16		seasonName[CALENDARINFO_SEASON_MAX_COUNT];
		Str16		dayName[CALENDARINFO_DAY_MAX_COUNT];
		Str16		diZhiName[CALENDARINFO_DIZHI_MAX_COUNT];

		CalendarInfo()
			:id(0)
		{
			name.resize(16);
			for (I32 i = 0; i < CALENDARINFO_HOUR_MAX_COUNT; i++)
			{
				hourName[i].resize(8);
				yearName[i].resize(8);
				seasonName[i].resize(8);
				monthName[i].resize(8);
			}
			for (I32 i = 0; i < CALENDARINFO_DIZHI_MAX_COUNT; i++)
			{
				diZhiName[i].resize(8);
			}
			for (I32 i = 0; i < CALENDARINFO_DAY_MAX_COUNT; i++)
			{
				dayName[i].resize(8);
			}
		}

    };
    //-----------------------------------------------------------------------------
    class CalendarInfos
    {
	public:
		CalendarInfos();
		~CalendarInfos();
		SINGLETON_INSTANCE(CalendarInfos);
      
    public:
		// MG_CN_MODIFY
        //加载 Calendar.csv
        Bool						load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const CalendarInfo*			getCalendarInfo(U32 id);
	
	protected:
		void                        clear();

	private:
		  std::map<U32, CalendarInfo*> mCalendarInfoMap;
    };
}
//******************************************************************************************
#endif //_CALENDARINFO_H_
//******************************************************************************************