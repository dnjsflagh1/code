/******************************************************************************/
#ifndef _LOGINMANAGER_H_
#define _LOGINMANAGER_H_
/******************************************************************************/
#include "Lock.h"
#include "Player.h"
#include "ServerManager.h"
#include "ObjectPool.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//客户端登入对象
	/******************************************************************************/
	class SPlayer : public Player
	{
	public:
		enum LoginState
		{
			LoginState_Disconnect,
			LoginState_SendNoFrontInfo,
			LoginState_SendFrontInfo,
		};
	public:
		SPlayer( I32 cientNetID, IdType accID, Char16* accName, Char16* accPsw,U32 logingingNo);
		virtual ~SPlayer();
		
		I32		getCreateTime(){return mCreateTime;}
		I32		getFrontServerNetID(){return mFrontServerNetID;}
		I32		getClientId(){return mClientNetID;}

		void	setFrontServerId( I32 netId );
		void	addLoginErrorCount();
		void	setLoginErrorCount(I32 count);
		I32		getLoginErrorCount();

		Bool	isInLogingList();
		void	setInLogingList(Bool inLoingingList = true);

		Bool	isInLoginedList();
		void	setInLoginedList(Bool inLoingedList = true);
		
		void		setLoginState(LoginState state);
		LoginState	getLoginState();
		U32			getStateStartTime();
		U32			getStateDestoryTime();
		
		void		addRefCount();
		I32			subRefCount();
		I32			getRefCount();

		U32			getLoginNo();

		U32			getLastSendQueueInfoTick();
		void		setLastSendQueueInfoTick(U32 tick);

		Bool		IsCheckDisConnect();
		Bool		IsCheckInFront();

		U32			getIp();
		void		setIP(U32 ip);

	protected:
		U32		volatile	mCreateTime;
		U32		volatile	mAccountCheckTime;
		I32		volatile	mFrontServerNetID;
		I32		volatile	mClientNetID;
		I32		volatile	mLoginErrorCount;

		Bool	volatile	mIsDisConnect;
		Bool	volatile	mIsInLogingList;
		Bool	volatile	mIsInLoginedList;

		Bool	volatile	mIsCheckDisConnect;
		Bool	volatile	mIsCheckInFrontServer;

		U32		volatile	mLogindex;

		LoginState	volatile		mLoginState;
		U32			volatile		mStateStartTime;
		// 当前状态生存时间（ms）超过了这个时间 会踢出该player， 0表示无限生存时间
		U32			volatile		mStateDestoryTime;

		// 被队列引用的计数 当被引用的计数降为0是才可以被回收
		InterLocked			mRefCount;

		U32			volatile mLogingNo;

		U32			volatile mLastSendLoginQueueInfoTick;

		//记住玩家的IP，日志服务器需要。
		U32					mIP;
		
	};

	/******************************************************************************/
	//错误的客户端登入对象
	/******************************************************************************/
	class ErrorLoginPlayer
	{
	public:
		ErrorLoginPlayer(Char16* accountName);
		~ErrorLoginPlayer();

	public:
		Int		getErrorCount();
		void	addErrorCount();
		U32		getCreateTime();
		void	setDirty(Bool dirty);
		Bool	getDirty();
		Char16*	getName();

	protected:
		Char16	mName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Int		mErrorCount;
		U32		mCreateTime;
		Bool	mDirty;
	};
	/******************************************************************************/
	/*帐号登入管理
		# 账号不能重登入，允许双开但是必须是不同账号。
		# 客户端连接后发送排队信息。
		# 验证客户端登入账号密码,如果正确则分配一个FrontServer给客户端。并且通知ClientManager断开连接。
		# 客户端收到FrontServer资源后，断开LoginServer，并连接FrontServer
		# FrontServer收到客户端登入消息后，通知LoginServer做验证,LoginServer验证通过后通知FrontServer。然后由FrontServer通知客户端登入结果。
		# LoginServer会检测 如果长时间没有接受到FrontServer对于已经分配资源的客户端登入的消息，则回收前面分配给该客户端的FrontServer资源。
	*/
	/******************************************************************************/
#define MG_LOGIN_ERROR_COUNT 5
#define MG_LOGINSERVER_MAX_CLIENT_COUNT 5000
	class LoginConfigInfo;
	class LoginManager
	{
	public:
		SINGLETON_INSTANCE(LoginManager);
		LoginManager();
		virtual	~LoginManager();

		/// 初始化和反初始化
		Bool			initialize(DBDriver* Driver,SServerSetting* setting,LoginConfigInfo* loginConfigInfo);
		void			uninitialize();

		/// 主进程更新
		void			update();

		///客户端登入验证
		///TODO: 以后需要修改为线程处理
		///TODO: 数据库验证以后需要修改为批量获取验证
		void			handleClientLogin(I32 id, Char16* accName, Char16* accPsw);

		///客户端登入FrontServer验证
		void			handleClientLoginFrontServer(I32 id, I32 clientNetIdInFrontServer, Char16* accName, Char16* accPsw);
		///客户端登出FrontServer
		void			handleClientLogoutFrontServer(Char16* accName);
		///处理FrontServer断开
		void			handleFrontServerDisconnect(I32 id);
		///处理检测客户端是否存在FrontServer中
		void			handleCheckClientInFrontServerResult(I32 clientNetId,Bool relult);
	public:
		// 逻辑调用
		//--------------------------------------------------
		void					addLogingPlayer(I32 netId, Char16* accName, Char16* accPsw,U32 loginNo);
		SPlayer*				removeLogingPlayerByNetId(I32 clientNetId);
		SPlayer*				removeLogingPlayerByAccName(Char16* accName,Bool hasNextOp = true);
		SPlayer*				removeLogingPlayerForAccCheck(I32 netId,Char16* accName, Char16* accPsw);

		void					addLoginedPlayer(Char16* accName,SPlayer* player);
		SPlayer*				removeLoginedPlayerByNetId(I32 clientNetId);
		SPlayer*				removeLoginedPlayerByAccName(Char16* accName);
		void					removePlayerByFrontNetId(I32 frontServerNetId);

		void					addErrorPlayer(Char16* accName);
		ErrorLoginPlayer*		removeErrorPlayerByAccName(Char16* accName);
		ErrorLoginPlayer*		getErrorPlayerByAccName(Char16* accName);

		//--------------------------------------------------
		U32						getAllLoginCount();

	protected:
		// 对象创建与回收
		//--------------------------------------------------
		SPlayer*				createPlayer(I32 netId, Char16* accName, Char16* accPsw, IdType accID,U32 LogingNo);
		void					destoryPlayer(SPlayer* player);
		//--------------------------------------------------
		ErrorLoginPlayer*		createErrorPlayer(Char16* accName);
		void					destoryErrorPlayer(ErrorLoginPlayer* errorPlayer);
		
		// 对链表的操作 5个Map，4个Queue
		//--------------------------------------------------
		void					addToLogingMapByClientNetId(I32 clientNetID, SPlayer* player);
		SPlayer*				getFromLogingMapByClientNetId(I32 clientNetID);
		SPlayer*				removeFromLogingMapByClientNetId(I32 clientNetID);
		//-------------------------------------------------- 		
		void					addToLogingMapByAccName(Char16* accName, SPlayer* player);
		SPlayer*				getFromLogingMapByAccName(Char16* accName);
		SPlayer*				removeFromLogingMapByAccName(Char16* accName);
		//--------------------------------------------------
		//void					addToLogingQueue(SPlayer* player);
		//SPlayer*				getFromLogingQueue();
		//--------------------------------------------------
		void					addToLogingQueuingQueue(SPlayer* player);
		SPlayer*				getFromLogingQueuingQueue();
		//--------------------------------------------------
		void					addToLoginedMapByClientNetId(I32 clientNetID, SPlayer* player);
		SPlayer*				getFromLoginedMapByClientNetId(I32 clientNetID);
		SPlayer*				removeFromLoginedMapByClientNetId(I32 clientNetID);
		//-------------------------------------------------- 		
		void					addToLoginedMapByAccName(Char16* accName, SPlayer* player);
		SPlayer*				getFromLoginedMapByAccName(Char16* accName);
		SPlayer*				removeFromLoginedMapByAccName(Char16* accName);
		
		//--------------------------------------------------
		void					addToLoginedQueue(SPlayer* player);
		SPlayer*				getFromLoginedQueue();	
		//-------------------------------------------------- 		
		//void					addToErrorLogingMapByAccName(Char16* accName, SPlayer* player);
		//ErrorLoginPlayer*		getFromErrorLogingMapByAccName(Char16* accName);
		//ErrorLoginPlayer*		removeFromErrorLogingMapByAccName(Char16* accName);
		//--------------------------------------------------
		void					addToErrorLogingQueue(ErrorLoginPlayer* errorPlayer);
		ErrorLoginPlayer*		getFromErrorLogingQueue();
		//--------------------------------------------------
		
		// 检测登录中的客户短
		static void				checkLogingClientThread(Ptr ptr);
	
		// 检测登录完成的客户短
		static void				checkLoginedClientThread(Ptr ptr);

		// 检测错误客户短
		static void				checkErrorClientThread(Ptr ptr);
		
	public:
		/*
			# 登录相关配置
		*/
		U32					getMaxLoginCount();
		U32					getMaxWaitCount();
		U32					getMaxLoginTimeout();
		U32					getUpdateLoginQueueIntervalTime();
		U32					getUpdateForbidedLogintervalTime();	
		U32					getForbidedLoginTime();	
		U32					getMaxErrorLoginCount();	
		U32					getMaxFrontServerLoginCount();	

		void				setMaxLoginCount(U32 maxLoginCount);
		void				setMaxWaitCount(U32  maxWaitCount);
		void				setMaxLoginTimeout(U32 loginTimeOutValue);
		void				setUpdateLoginQueueIntervalTime(U32 intervalTime);
		void				setUpdateForbidedLogintervalTime(U32 intervalTime);
		void				setForbidedLoginTime(U32 forbiddenTime);
		void				setMaxErrorLoginCount(U32 maxErrorLoginCount);
		void				setMaxFrontServerLoginCount(U32 maxFrontServerLoginCount);

	private:

		ObjectPool<SPlayer,false>   mPlayerPool;

		//数据库对象
		DBDriver*					mMySqlDriver;
		OneThreadHandle				mCheckLogingPlayerThread;
		OneThreadHandle				mCheckLoginedPlayerThread;
		OneThreadHandle				mCheckErrorPlayerThread;
		
		/*
			# 准备登入FrontServer的客户端
			# 根据连接LoginServer的客户端网络id划分
		*/
		std::map< I32, SPlayer* >	mLogingMapByClientNetId;
		Critical					mLogingMapByClientNetIdLock;

		/*
		# 准备登入FrontServer的客户端
		# 根据账号名划分
		*/
		std::map< Str16, SPlayer* >	mLogingMapByAccName;
		Critical					mLogingMapByAccNameLock;

		/*
		# 准备登入的队列
		# 用做排队使用
		*/
		std::queue<SPlayer*>		mLogingQueuingQueue;
		Critical					mLogingQueuingQueueLock;


		////////////////////////////////////////////////////////////
		/*
			# 已经登入FrontServer的客户端
			# 根据连接LoginServer的客户端网络id划分
			# 供外部使用
		*/
		std::map< I32, SPlayer* >	mLoginedMapByClientNetId;
		Critical					mLoginedMapByClientNetIdLock;


		/*
			# 已经登入FrontServer成功的客户端
			# 根据账号名划分.
		*/
		std::map< Str16, SPlayer* >	mLoginedMapByAccName;	
		Critical					mLoginedMapByAccNameLock;

		/*
		# 已经登入的队列
		# 用做遍历跟新
		*/
		std::queue<SPlayer*>		mLoginedQueue;
		Critical					mLoginedQueueLock;

		////////////////////////////////////////////////////////////

		/*
			# 错误登入的客户端队列
			# 根据账号名划分.
		*/
		std::map< Str16,ErrorLoginPlayer* >			mErrorLogingMapByAccName;
		Critical									mErrorLogingMapByAccNameLock;

		std::queue<ErrorLoginPlayer*>				mErrorLogingQueue;
		Critical									mErrorLogingQueueLock;

		ObjectPool<ErrorLoginPlayer,false>			mErrorLoginPlayerPool;

	protected:

			//	第一个准备登录的玩家序号
			U32		mFirstLogingPlayerNo;

			//	当前
			U32		mCurrLogingNo;		

	private:
	
		/*
			# 登录相关配置 
		*/
		// 最大登录人数
		U32				mMaxLoginCount;
		// 最大等待登录人数
		U32				mMaxLoginWaitCount;
		// 登录超时时间(ms)
		U32				mMaxLoginTimeoutValue;
		// 通知客户端登录排队信息的更新时间间隔(ms)
		U32				mUpdateLoginQueueIntervalTime;
		// 更新恢复禁止登录帐号的登录权限时间间隔（ms）
		U32				mUpdateForbidedLogintervalTime;
		// 错误登录上限 禁止登录时间
		U32				mForbidedLoginTime;
		// 最大登录错误次数
		U32				mMaxErrorLoginCount;
		// FrontServer最大登录人数
		U32				mMaxFrontServerLoginCount;
	};
}
#endif