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
			U32 totalTime,								//ʱ�䵥λ������
			MGTIMETEXT_SHOW_TYPE showtype = MGTIMETEXT_SHOW_TYPE_GAME,
			MGTIMETEXT_UNIT_TYPE unittype = MGTIMETEXT_UNIT_TYPE_SECOND
			) = 0;

	public:
		//��timeoutTime��ʼÿ��spaceTime����һ�Ρ�
		//spaceTime ����0 ��ʾֻ����һ�Ρ�
		//timeoutTime ����0 ��ʾ����ʱ�������á�
		virtual void			setEventTimeOut(PVOIDINT_CALLBACK func, UInt timeoutTime = 0, UInt spaceTime = 0) = 0;		

	};
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************