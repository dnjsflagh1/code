/******************************************************************************/
#ifndef	_CHATINFO_H_
#define	_CHATINFO_H_
/******************************************************************************/
namespace MG
{
	enum chatusetype
	{
		chat_null_use,		        //无意义
		chat_read_write,	        //可发送，可接收
		chat_read,			        //可接收
		chat_not_write_read			//不可接受和发送
	};

	enum chatbroadcasttpye
	{
		chat_null_broadcast,//无意义
		chat_full_server,	//全服
		chat_one_world,		//同界
		chat_one_zhou,		//同州
		chat_one_jun,		//同郡
		chat_one_xian,		//同县
		chat_one_city,		//同城
		chat_one_force,		//同势力
		chat_one_alliance,	//同盟
		chat_one_group,		//同队
		chat_two_person,	//两人聊天
		chat_one_region,	//同地图
		chat_one_view		//同视野
	};
	/******************************************************************************/
	//聊天频道信息 和策划文档对应
	/******************************************************************************/
	struct ChannelInfo
	{
		U32					id;				//聊天频道ID
		//Str16				note;			//策划备注
		Str16				fullName;		//频道全称
		Str16				shortName;		//频道简称
		Str16				instruct;		//快捷指令
		Color				color;			//频道字体颜色
		chatusetype			useType;		//普通玩家使用权限（看或发）
		Int					shutDown;		//是否可关闭	（0无意义，1可关闭，2不可关闭）
		Int					showSenderName;	//是否显示发送者的名字（0无意义，1显示，2不显示）
		Int					showPlace;		//显示的位置	（0无意义，1界面1,2界面2,3界面3） 
		chatbroadcasttpye	broadcast;		//广播范围
		UInt				useLevel;		//使用等级下限
		UInt				interval;		//发送时间间隔
		UInt				consumeItemId;	//消耗物品ID 
		UInt				consumeItemNum;	//消耗物品数量 （0持有即可）
		Int					support;		//频道支持功能（1位表情，2位角色链接，3物品链接，4任务链接）
        UInt                maxChar;         //一次发送最大字符数

		//以下是变化记录
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
	//玩家退出游戏时的面板配置
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