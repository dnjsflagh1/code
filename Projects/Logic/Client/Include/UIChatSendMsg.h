//***************************************************************************************************
#ifndef _H_UICHATSENDMSG_
#define _H_UICHATSENDMSG_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{

	struct ChannelInfo;
	class UIChatSendMsg : public UIObject
	{
	public:
		UIChatSendMsg();
		~UIChatSendMsg();
		SINGLETON_INSTANCE(UIChatSendMsg);
	public:
		virtual   void         setEvent();


		//事件
		static   void          onComboAccept(void* widget,Int i);
		static   void          onComboChangePosition(void* widget,Int i);
        static   void          onSend(void* widget);
		static   void          onSelectAcceptEvent(void* widget);        //回车发送
		static   void          onClickExpression(void* widget);

		//
		void                   setIputFocus();

		//
		virtual  Bool		   openGui();
        virtual  void          update(Flt delta);
        virtual  void          restore();
		
       
		
	private:
		Bool                initComboItem(IComboBox* icombo);
		void                sendMsg();
       

	};

	

}


//***************************************************************************************************
#endif
//***************************************************************************************************