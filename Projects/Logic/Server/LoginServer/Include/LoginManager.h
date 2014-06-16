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
	//�ͻ��˵������
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
		// ��ǰ״̬����ʱ�䣨ms�����������ʱ�� ���߳���player�� 0��ʾ��������ʱ��
		U32			volatile		mStateDestoryTime;

		// ���������õļ��� �������õļ�����Ϊ0�ǲſ��Ա�����
		InterLocked			mRefCount;

		U32			volatile mLogingNo;

		U32			volatile mLastSendLoginQueueInfoTick;

		//��ס��ҵ�IP����־��������Ҫ��
		U32					mIP;
		
	};

	/******************************************************************************/
	//����Ŀͻ��˵������
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
	/*�ʺŵ������
		# �˺Ų����ص��룬����˫�����Ǳ����ǲ�ͬ�˺š�
		# �ͻ������Ӻ����Ŷ���Ϣ��
		# ��֤�ͻ��˵����˺�����,�����ȷ�����һ��FrontServer���ͻ��ˡ�����֪ͨClientManager�Ͽ����ӡ�
		# �ͻ����յ�FrontServer��Դ�󣬶Ͽ�LoginServer��������FrontServer
		# FrontServer�յ��ͻ��˵�����Ϣ��֪ͨLoginServer����֤,LoginServer��֤ͨ����֪ͨFrontServer��Ȼ����FrontServer֪ͨ�ͻ��˵�������
		# LoginServer���� �����ʱ��û�н��ܵ�FrontServer�����Ѿ�������Դ�Ŀͻ��˵������Ϣ�������ǰ�������ÿͻ��˵�FrontServer��Դ��
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

		/// ��ʼ���ͷ���ʼ��
		Bool			initialize(DBDriver* Driver,SServerSetting* setting,LoginConfigInfo* loginConfigInfo);
		void			uninitialize();

		/// �����̸���
		void			update();

		///�ͻ��˵�����֤
		///TODO: �Ժ���Ҫ�޸�Ϊ�̴߳���
		///TODO: ���ݿ���֤�Ժ���Ҫ�޸�Ϊ������ȡ��֤
		void			handleClientLogin(I32 id, Char16* accName, Char16* accPsw);

		///�ͻ��˵���FrontServer��֤
		void			handleClientLoginFrontServer(I32 id, I32 clientNetIdInFrontServer, Char16* accName, Char16* accPsw);
		///�ͻ��˵ǳ�FrontServer
		void			handleClientLogoutFrontServer(Char16* accName);
		///����FrontServer�Ͽ�
		void			handleFrontServerDisconnect(I32 id);
		///������ͻ����Ƿ����FrontServer��
		void			handleCheckClientInFrontServerResult(I32 clientNetId,Bool relult);
	public:
		// �߼�����
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
		// ���󴴽������
		//--------------------------------------------------
		SPlayer*				createPlayer(I32 netId, Char16* accName, Char16* accPsw, IdType accID,U32 LogingNo);
		void					destoryPlayer(SPlayer* player);
		//--------------------------------------------------
		ErrorLoginPlayer*		createErrorPlayer(Char16* accName);
		void					destoryErrorPlayer(ErrorLoginPlayer* errorPlayer);
		
		// ������Ĳ��� 5��Map��4��Queue
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
		
		// ����¼�еĿͻ���
		static void				checkLogingClientThread(Ptr ptr);
	
		// ����¼��ɵĿͻ���
		static void				checkLoginedClientThread(Ptr ptr);

		// ������ͻ���
		static void				checkErrorClientThread(Ptr ptr);
		
	public:
		/*
			# ��¼�������
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

		//���ݿ����
		DBDriver*					mMySqlDriver;
		OneThreadHandle				mCheckLogingPlayerThread;
		OneThreadHandle				mCheckLoginedPlayerThread;
		OneThreadHandle				mCheckErrorPlayerThread;
		
		/*
			# ׼������FrontServer�Ŀͻ���
			# ��������LoginServer�Ŀͻ�������id����
		*/
		std::map< I32, SPlayer* >	mLogingMapByClientNetId;
		Critical					mLogingMapByClientNetIdLock;

		/*
		# ׼������FrontServer�Ŀͻ���
		# �����˺�������
		*/
		std::map< Str16, SPlayer* >	mLogingMapByAccName;
		Critical					mLogingMapByAccNameLock;

		/*
		# ׼������Ķ���
		# �����Ŷ�ʹ��
		*/
		std::queue<SPlayer*>		mLogingQueuingQueue;
		Critical					mLogingQueuingQueueLock;


		////////////////////////////////////////////////////////////
		/*
			# �Ѿ�����FrontServer�Ŀͻ���
			# ��������LoginServer�Ŀͻ�������id����
			# ���ⲿʹ��
		*/
		std::map< I32, SPlayer* >	mLoginedMapByClientNetId;
		Critical					mLoginedMapByClientNetIdLock;


		/*
			# �Ѿ�����FrontServer�ɹ��Ŀͻ���
			# �����˺�������.
		*/
		std::map< Str16, SPlayer* >	mLoginedMapByAccName;	
		Critical					mLoginedMapByAccNameLock;

		/*
		# �Ѿ�����Ķ���
		# ������������
		*/
		std::queue<SPlayer*>		mLoginedQueue;
		Critical					mLoginedQueueLock;

		////////////////////////////////////////////////////////////

		/*
			# �������Ŀͻ��˶���
			# �����˺�������.
		*/
		std::map< Str16,ErrorLoginPlayer* >			mErrorLogingMapByAccName;
		Critical									mErrorLogingMapByAccNameLock;

		std::queue<ErrorLoginPlayer*>				mErrorLogingQueue;
		Critical									mErrorLogingQueueLock;

		ObjectPool<ErrorLoginPlayer,false>			mErrorLoginPlayerPool;

	protected:

			//	��һ��׼����¼��������
			U32		mFirstLogingPlayerNo;

			//	��ǰ
			U32		mCurrLogingNo;		

	private:
	
		/*
			# ��¼������� 
		*/
		// ����¼����
		U32				mMaxLoginCount;
		// ���ȴ���¼����
		U32				mMaxLoginWaitCount;
		// ��¼��ʱʱ��(ms)
		U32				mMaxLoginTimeoutValue;
		// ֪ͨ�ͻ��˵�¼�Ŷ���Ϣ�ĸ���ʱ����(ms)
		U32				mUpdateLoginQueueIntervalTime;
		// ���»ָ���ֹ��¼�ʺŵĵ�¼Ȩ��ʱ������ms��
		U32				mUpdateForbidedLogintervalTime;
		// �����¼���� ��ֹ��¼ʱ��
		U32				mForbidedLoginTime;
		// ����¼�������
		U32				mMaxErrorLoginCount;
		// FrontServer����¼����
		U32				mMaxFrontServerLoginCount;
	};
}
#endif