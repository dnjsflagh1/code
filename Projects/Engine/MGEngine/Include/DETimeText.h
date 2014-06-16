//**********************************************************************************************************
#ifndef _H_DETIME_TEXT_
#define _H_DETIME_TEXT_
//**********************************************************************************************************
#include "ITimeText.h"
#include "DEWidget.h"
//**********************************************************************************************************
namespace MG
{
	class DETimeText : public ITimeText, public DEWidget
	{
	public:
		DETimeText();
		virtual ~DETimeText(){;}

	public:
		virtual IWidget*        getWidget();
		virtual void			setCoolDownTime(
			U32 totalTime,
			MGTIMETEXT_SHOW_TYPE showtype = MGTIMETEXT_SHOW_TYPE_GAME,
			MGTIMETEXT_UNIT_TYPE unittype = MGTIMETEXT_UNIT_TYPE_SECOND
			);

	public:
		virtual void			setEventTimeOut(PVOIDINT_CALLBACK func, UInt timeoutTime, UInt spaceTime);	

	public:
		//引擎事件
		Bool                setEGTimeText(MyGUI::Widget* p);
		MyGUI::Widget*      getEGTimeText(){return mpEGTimeText;}

	protected:
		//引擎事件
		void                notifyTimeTextTimeOut( MyGUI::TimeText* p, Int timeoutTime );

	protected:
		//记录引擎对象和对应的回调函数，当引擎的回调响应时可找到client的回调函数
		static std::map<MyGUI::TimeText*, PVOIDINT_CALLBACK>                    mMapTimeTextTimeOut;

	private:
		//引擎对象指针
		MyGUI::TimeText*                     mpEGTimeText;
	};
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************