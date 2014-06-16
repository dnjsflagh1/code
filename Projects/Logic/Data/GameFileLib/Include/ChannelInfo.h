/******************************************************************************/
#ifndef	_CHATINFO_H_
#define	_CHATINFO_H_
/******************************************************************************/
namespace MG
{
	enum chatusetype
	{
		chat_null_use,		        //������
		chat_read_write,	        //�ɷ��ͣ��ɽ���
		chat_read,			        //�ɽ���
		chat_not_write_read			//���ɽ��ܺͷ���
	};

	enum chatbroadcasttpye
	{
		chat_null_broadcast,//������
		chat_full_server,	//ȫ��
		chat_one_world,		//ͬ��
		chat_one_zhou,		//ͬ��
		chat_one_jun,		//ͬ��
		chat_one_xian,		//ͬ��
		chat_one_city,		//ͬ��
		chat_one_force,		//ͬ����
		chat_one_alliance,	//ͬ��
		chat_one_group,		//ͬ��
		chat_two_person,	//��������
		chat_one_region,	//ͬ��ͼ
		chat_one_view		//ͬ��Ұ
	};
	/******************************************************************************/
	//����Ƶ����Ϣ �Ͳ߻��ĵ���Ӧ
	/******************************************************************************/
	struct ChannelInfo
	{
		U32					id;				//����Ƶ��ID
		//Str16				note;			//�߻���ע
		Str16				fullName;		//Ƶ��ȫ��
		Str16				shortName;		//Ƶ�����
		Str16				instruct;		//���ָ��
		Color				color;			//Ƶ��������ɫ
		chatusetype			useType;		//��ͨ���ʹ��Ȩ�ޣ����򷢣�
		Int					shutDown;		//�Ƿ�ɹر�	��0�����壬1�ɹرգ�2���ɹرգ�
		Int					showSenderName;	//�Ƿ���ʾ�����ߵ����֣�0�����壬1��ʾ��2����ʾ��
		Int					showPlace;		//��ʾ��λ��	��0�����壬1����1,2����2,3����3�� 
		chatbroadcasttpye	broadcast;		//�㲥��Χ
		UInt				useLevel;		//ʹ�õȼ�����
		UInt				interval;		//����ʱ����
		UInt				consumeItemId;	//������ƷID 
		UInt				consumeItemNum;	//������Ʒ���� ��0���м��ɣ�
		Int					support;		//Ƶ��֧�ֹ��ܣ�1λ���飬2λ��ɫ���ӣ�3��Ʒ���ӣ�4�������ӣ�
        UInt                maxChar;         //һ�η�������ַ���

		//�����Ǳ仯��¼
		//----------------------------------------------------------------------------------
		Bool				isShutDown;
		//----------------------------------------------------------------------------------
		ChannelInfo()
			:id(0),
			fullName(L""),
			shortName(L""),
			color(255,255,255,1),
			useType(chat_null_use),
			shutDown(0),
			showPlace(0),
			showSenderName(0),
			isShutDown(false)
		{

		}

		
		


	};


	/******************************************************************************/
	//����˳���Ϸʱ���������
	/******************************************************************************/
    struct ChatFaceplateConfig
	{



	};
	
	// MG_CN_MODIFY
	class IMGFileSystem;

	class ChannelInfos
	{
	public:
		ChannelInfos();
		~ChannelInfos();
		SINGLETON_INSTANCE(ChannelInfos);

		enum
		{
			chatid,
			note,
			chatfullname,
			chatshortname,
			chatinstruct,
			chatcolor,
			chatuse,
			chatshutdown,
			chatshowsender,
			chatshowplace,
			chatbroadcast,
			chatuselevel,
			chatinterval,
			chatconsumeitemid,
			chatconsumeitemnum,
			chatsupport,
			maxchar

		};
		
	public:
		// MG_CN_MODIFY
		Bool									loadFile(CChar16* fileName, IMGExternalPackManager* packManager = NULL);

		std::list<ChannelInfo*>                 getChannelInfoByUseType(const Int& type);
		std::list<ChannelInfo*>                 getChannelInfoByShowType(const Int& showType);
		Int										getChatCnt(){ return mListChatInfo.size(); }										
		ChannelInfo*							getChannelInfo(U32 chatId);
		ChannelInfo*							getChannelInfo(CChar16* chatName);
		ChannelInfo*							getChatInfoByInstruct(Char16* &msg);
        

	protected:
		typedef std::list<ChannelInfo*>::iterator	ChatInfoIt;

	private:
		std::list<ChannelInfo*>					mListChatInfo;
		//instruct channelInfo
		//std::map<Str16,ChannelInfo*>			mMapChatInfo;
	};



}

#endif