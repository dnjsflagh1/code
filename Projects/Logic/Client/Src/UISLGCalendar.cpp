//***************************************************************************************************
#include "stdafx.h"
#include "UISLGCalendar.h"
#include "ArtIconResCsv.h"
#include "CGameTimeSystem.h"
#include "CalendarInfo.h"
//***************************************************************************************************
namespace MG
{
    //----------------------------------------------------------------------------------------
	UISLGCalendar::UISLGCalendar()
	{

	}
    //----------------------------------------------------------------------------------------
	UISLGCalendar::~UISLGCalendar()
	{

	}
    //----------------------------------------------------------------------------------------
	void UISLGCalendar::setEvent()
	{


	}
	//----------------------------------------------------------------------------------------
	void UISLGCalendar::setCurrentDate()
	{
		U32 year,season,month,day,hour;		
		if (!CGameTimeSystem::getInstance().getCurrGameTime(year,season,month,day,hour))
		{
			return;
		}
		const CalendarInfo* calendarInfo = CalendarInfos::getInstance().getCalendarInfo(1);
		if (!calendarInfo)
		{
			return;
		}
		//Str16 curYearNo = calendarInfo->name;
		//Str16 curYearNum = NumberToChinese::convertNumToChineseW(year);
		//Str16 curDateTime = NumberToChinese::convertNumToChineseW(month) + L"月" + calendarInfo->dayName[day - 1];
		//
		////时辰的界面显示要根据配置表读图片
		//getLayout()->getText("NianHao")->getWidget()->setCaption(curYearNo);
		//getLayout()->getText("NianShu")->getWidget()->setCaption(curYearNum);
		//getLayout()->getText("RiQi")->getWidget()->setCaption(curDateTime);
	}
    //----------------------------------------------------------------------------------------
	void UISLGCalendar::setCurrentDate( U8 seasonType,CChar16* dateInfo )
	{
		//getLayout()->getText("text_dateinfo")->getWidget()->setCaption(Str16(dateInfo));
		//const ArtIconResCsvInfo* tempResInfo = NULL;
		//switch(seasonType)
		//{
		//case 1:
		//	{
		//		//spring
		//		tempResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(110001);
		//		IImage *headimg = getLayout()->getImage("img_season");
		//		headimg->setItemGroup(tempResInfo->GroupName);
		//		headimg->setItemResource(tempResInfo->ResName);
		//		headimg->setItemName(tempResInfo->ItemName);
		//	 
		//	}
		//	break;
		//case 2:
		//	{
		//		//summer
		//		tempResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(110002);
		//		IImage *headimg = getLayout()->getImage("img_season");
		//		headimg->setItemGroup(tempResInfo->GroupName);
		//		headimg->setItemResource(tempResInfo->ResName);
		//		headimg->setItemName(tempResInfo->ItemName);
		//	}
		//	break;
		//case 3:
		//	{
		//		//autumn
		//		tempResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(110003);
		//		IImage *headimg = getLayout()->getImage("img_season");
		//		headimg->setItemGroup(tempResInfo->GroupName);
		//		headimg->setItemResource(tempResInfo->ResName);
		//		headimg->setItemName(tempResInfo->ItemName);

		//	}
		//	break;
		//case 4:
		//	{
		//		//winter
		//		tempResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(110004);
		//		IImage *headimg = getLayout()->getImage("img_season");
		//		headimg->setItemGroup(tempResInfo->GroupName);
		//		headimg->setItemResource(tempResInfo->ResName);
		//		headimg->setItemName(tempResInfo->ItemName);

		//	}
		//	break;
		//default:
		//	{
		//		DYNAMIC_ASSERT(false);

		//	}
  //          break;

		//}

	}

	void UISLGCalendar::setArtResInfo()
	{
		/*if (mArtResInfo.empty())
		{
			ArtIconResCsv::getInstance().getIconArtResInfo(IOCN_ART_TYPE_SEASON,mArtResInfo);
		}*/
	}

	bool UISLGCalendar::isOpen()
	{
         setArtResInfo();
		 return UIObject::openGui();

	}

	void UISLGCalendar::update(Flt delta)
	{
		//setCurrentDate();
	}
	//----------------------------------------------------------------------------------------

}