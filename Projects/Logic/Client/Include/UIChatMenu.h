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
		
		/// �¼�
		static	void		onSend( void* widget );
		static	void		onClickChannel( void* widget );
		static	void		onShutDownChannel( void* widget );
		
		///��ui
		virtual	Bool		openGui(); 

		/// ��������������Ϣ
		void				addChatMsg(Byte channelId,CChar16* senderName,Char16* data,I32 count);

		/// ���õ�ǰƵ����Ϣ ������������UI������
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