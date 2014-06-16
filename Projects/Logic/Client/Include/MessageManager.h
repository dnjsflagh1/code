//***************************************************************************************************
#ifndef _H_MessageManager_
#define _H_MessageManager_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{

	struct ChannelInfo;
    struct ChatTag;
	struct RecChatData;
	class  UIChatSendMsg;
	class  UIChatCommonShow;

    const static U32 CHAT_CONTENT_ONCE_DELETE_COUNT = 500;       //聊天显示行到最大值之后，一次删除的删除的行数

	class MessageManager
	{
	public:
        friend class UIChatSendMsg;
		friend class UIChatCommonShow;
        MessageManager();
		~MessageManager();
		SINGLETON_INSTANCE(MessageManager);
		/// 初始化.
		Bool                            initialize();
		//清空链表,并释放资源
		void                            clear();
		//聊天
		void                            sendChatMsg( Str16& chatData,CChar16* receiveClanName = NULL );
		void                            addChatMsg( U32 channelid,CChar16* dataSender,Char16* data,I32 count );
		void                            addChatResultMsg( U32 channelid,Byte result,Char16* data,I32 count );
       // void                            setTextColour(Int _start, Int _count, const Color& value);
		//test 
		void                            addChatMsgForTest( Char* data, ... );
		void                            addChatMsgForTest( Char16* data, ... );
         int							  mTestCount;

		//test end
		Bool                            addRecChatDateToList( RecChatData *data );


		//聊天标签处理
		Bool                            addChatTag(CChar16* tagName);
		Bool                            removeChatTag(CChar16* tagName);
		ChatTag*                        getChatTagByName(CChar16* tagName);
		std::list<ChatTag*>             getChatTagList();
        
		//如果有快捷字符,和选中频道 则按快捷字符所对应的频道
        void                            setSelectChannel( CChar16* selectChannel);                             
		void                            setSelectChatTag( CChar16* selectChatTag); 
		ChannelInfo*                    getSelectChannel();
		ChatTag*                        getSelectChatTag();
        
		//获取当前发送的频道的信息
		//ChannelInfo*                    getSendChannelInfo() const;
		//

		//获取聊天频道对象
		ChannelInfo*		            getChannelInfoByInsruct(Char16* &msg);
		std::list<ChannelInfo*>         getChannelInfoByUseType(const I32& useType);
		std::list<ChannelInfo*>         getChannelInfoByShowType(const I32& useType);
		ChannelInfo*                    getChannelInfo(CChar16 *channelName);
		ChannelInfo*                    getChannelInfo(U32 chatId);

		//
		std::list<RecChatData*>         getRefreshChatData();
		Int                             getRecChatDataListSize() const;

	private:
        void                            deletecContentRow();
        void                            refreshChatData(Bool isAuto);
		void                            _refreshChatData(Bool isAuto);

	private:
		//聊天标签列表
		std::list<ChatTag*>               mChatTagList;
		std::list<ChatTag*>::iterator     mChatTagIt;
        

        //当前选中的聊天频道,
        ChannelInfo*                      mSelectChannel;
		//当前选中的聊天标签,
		ChatTag*                          mSelectChatTag;
		std::list<RecChatData*>           mRecChatDataList;  
		std::list<RecChatData*>::iterator mRecChatDataIt;
		//
	
	    //chat configuration
	public:
        void    setAllServerChatInterval(const U32 serverChatInterval);
		void    setOneRegionChatInterval(const U32 oneRegionChatInterval);
		U32     getAllServerChatInterval() const;
		U32     getOneRegionChatInterval() const;
        
	private:
		U32    mAllServerChatInterval; // units  ms
		U32    mOneRegionChatInterval; // units  ms

	};


}


#endif