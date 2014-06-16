//**********************************************************************************************************
#ifndef _H_ITIME_TEXT_
#define _H_ITIME_TEXT_
//**********************************************************************************************************
#include "IWidget.h"
//**********************************************************************************************************
namespace MG
{
	class ITimeText
	{
	public:
		virtual IWidget*        getWidget() = 0;
		virtual void			setCoolDownTime(
			U32 totalTime,								//时间单位，毫秒
			MGTIMETEXT_SHOW_TYPE showtype = MGTIMETEXT_SHOW_TYPE_GAME,
			MGTIMETEXT_UNIT_TYPE unittype = MGTIMETEXT_UNIT_TYPE_SECOND
			) = 0;

	public:
		//从timeoutTime开始每隔spaceTime调用一次。
		//spaceTime 等于0 表示只调用一次。
		//timeoutTime 等于0 表示倒计时走完后调用。
		virtual void			setEventTimeOut(PVOIDINT_CALLBACK func, UInt timeoutTime = 0, UInt spaceTime = 0) = 0;		

	};
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************