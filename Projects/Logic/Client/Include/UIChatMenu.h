//***************************************************************************************************
#ifndef _H_UICHATMENU_
#define _H_UICHATMENU_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
	struct ChannelInfo; 
    class UIChatMenu  : public UIObject
    {
    public:
        UIChatMenu();
        ~UIChatMenu();
        SINGLETON_INSTANCE(UIChatMenu);

    public:
        virtual void		setEvent();
		
		/// 事件
		static	void		onSend( void* widget );
		static	void		onClickChannel( void* widget );
		static	void		onShutDownChannel( void* widget );
		
		///打开ui
		virtual	Bool		openGui(); 

		/// 向聊天面板添加消息
		void				addChatMsg(Byte channelId,CChar16* senderName,Char16* data,I32 count);

		/// 设置当前频道信息 包括配置聊天UI，数据
		void				setCurrentChannel(ChannelInfo* channelInfo);

		ChannelInfo*		getChannelInfoByInsruct(Char16* &msg);
		ChannelInfo*		getSelectChannelInfo();
		ChannelInfo*		getChannelInfo(Byte channel);
		
    private:
		ChannelInfo*		mSelectChannel;
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************