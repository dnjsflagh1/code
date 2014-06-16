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

    const static U32 CHAT_CONTENT_ONCE_DELETE_COUNT = 500;       //������ʾ�е����ֵ֮��һ��ɾ����ɾ��������

	class MessageManager
	{
	public:
        friend class UIChatSendMsg;
		friend class UIChatCommonShow;
        MessageManager();
		~MessageManager();
		SINGLETON_INSTANCE(MessageManager);
		/// ��ʼ��.
		Bool                            initialize();
		//�������,���ͷ���Դ
		void                            clear();
		//����
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


		//�����ǩ����
		Bool                            addChatTag(CChar16* tagName);
		Bool                            removeChatTag(CChar16* tagName);
		ChatTag*                        getChatTagByName(CChar16* tagName);
		std::list<ChatTag*>             getChatTagList();
        
		//����п���ַ�,��ѡ��Ƶ�� �򰴿���ַ�����Ӧ��Ƶ��
        void                            setSelectChannel( CChar16* selectChannel);                             
		void                            setSelectChatTag( CChar16* selectChatTag); 
		ChannelInfo*                    getSelectChannel();
		ChatTag*                        getSelectChatTag();
        
		//��ȡ��ǰ���͵�Ƶ������Ϣ
		//ChannelInfo*                    getSendChannelInfo() const;
		//

		//��ȡ����Ƶ������
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
		//�����ǩ�б�
		std::list<ChatTag*>               mChatTagList;
		std::list<ChatTag*>::iterator     mChatTagIt;
        

        //��ǰѡ�е�����Ƶ��,
        ChannelInfo*                      mSelectChannel;
		//��ǰѡ�е������ǩ,
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