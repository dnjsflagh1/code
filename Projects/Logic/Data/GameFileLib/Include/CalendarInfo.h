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
		U32			id;					///�������
		Str16		name;				///��������
		U32			trueTimeBegin[6];	///������ʼʱʱ�����ʵʱ��
		U32			calendarBegin[5];	///��������ʼʱ��
		U32			timeUnit;			///��������С��λʱ�䣨��ʵʱ������룩
		U32			hour;				///������ʱ��������С��λ��
		U32			day;				///�������죨������С��λ��
		U32			month;				///�������£�������С��λ��
		U32			season;				///�����ļ��ڣ�������С��λ��
		U32			year;				///�������꣨������С��λ��

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
        //���� Calendar.csv
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