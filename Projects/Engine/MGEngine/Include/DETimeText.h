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
		//�����¼�
		Bool                setEGTimeText(MyGUI::Widget* p);
		MyGUI::Widget*      getEGTimeText(){return mpEGTimeText;}

	protected:
		//�����¼�
		void                notifyTimeTextTimeOut( MyGUI::TimeText* p, Int timeoutTime );

	protected:
		//��¼�������Ͷ�Ӧ�Ļص�������������Ļص���Ӧʱ���ҵ�client�Ļص�����
		static std::map<MyGUI::TimeText*, PVOIDINT_CALLBACK>                    mMapTimeTextTimeOut;

	private:
		//�������ָ��
		MyGUI::TimeText*                     mpEGTimeText;
	};
}

//**********************************************************************************************************
#endif
//**********************************************************************************************************