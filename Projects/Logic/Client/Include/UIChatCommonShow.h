//***************************************************************************************************
#ifndef _H_UIChatCommonShow_
#define _H_UIChatCommonShow_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{

    struct ChatFaceplateConfig;
	class  MessageManager;
	class UIChatCommonShow : public UIObject
	{
		
	public:
		friend class MessageManager;
		UIChatCommonShow();
		~UIChatCommonShow();
		SINGLETON_INSTANCE(UIChatCommonShow);
	public:
        //聊天显示面板 普通区，喇叭区 
		enum SHOW_PLACE
		{
           SHOW_PLACE_COMMON = 1,
		   SHOW_PLACE_LABA 
		};

		//设置默认综合面板标签 包含所有聊天频道
		void                InitDefaultFaceplate();
		virtual void		setEvent();

		//事件
		static  void        onChangeTag( void* widget );
        static  void        onRightClickTag( void* widget );

		//打开ui
		virtual	Bool		openGui(); 
		virtual void        restore();
		
	protected:
		
		
		//向聊天面板添加消息
		void				addChatMsg(Byte channelId,CChar16* dataSender,Char16* data,I32 count);
		void                addChatResultMsg( U32 channelid,Byte result,Char16* data,I32 count );
		void                addChatMsgForTest(Char16* data);
		//根据聊天配置记录设置聊天面板
		Bool                setChatFaceplate();
		void                setTextColour(Int _start, Int _count, const Color& value,SHOW_PLACE _showplace);

		void                clearCommonArea();
		void                clearLaBaArea();

		U32					getTextLength(SHOW_PLACE _showplace);

    protected:
	    U32                 getWidthStrAddBreak(Str16& src, Int width, Str8 fontName = "");   //计算宽度增加换行符

	private:
        Int                 getEditBoxWidth(SHOW_PLACE _showplace);
		Int                 getEditBoxHeight(SHOW_PLACE _showplace);

	private:
		//玩家上次的聊天面板配置
        ChatFaceplateConfig* mChatfplatecfg;
		
	};




}








#endif