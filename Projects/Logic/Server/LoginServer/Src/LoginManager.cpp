/******************************************************************************/
#include "stdafx.h"
#include "LoginNetPacketProcesser.h"
#include "LoginManager.h"
#include "SServerSetting.h"
#include "LoginServerMain.h"
#include "RamAlloc.h"
#include "MGTimeOp.h"
#include "MGStrOp.h"
#include "AccountDB.h"
#include "PlayerCharacterDB.h"
#include "ClientManager.h"
#include "SysLogNetPacketProcesser.h"
#include "LoginConfig.h"
#include "LineUpNetPacketProcesser.h"
#include "PlatformCheckAccount.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//SPlayer
	/******************************************************************************/
	SPlayer::SPlayer(I32 cientNetID, IdType accID, Char16* accName, Char16* accPsw,U32 logingingNo)
		:mClientNetID(cientNetID)
		,mLoginErrorCount(0)
		,mLoginState(LoginState_Disconnect)
		,mStateDestoryTime(0)
		,mIsInLogingList(false)
		,mIsInLoginedList(false)
		,mLogingNo(logingingNo)
		,mLastSendLoginQueueInfoTick(0)
		,mIsCheckDisConnect(false)
		,mIsCheckInFrontServer(false)
		,mIP(0)
	{
		mCreateTime = MGTimeOp::getCurrTick();
		mAccountCheckTime = 0;
		mStateStartTime = mCreateTime;
		setAccountID( accID );
		setName(accName);
		setPassword(accPsw);

	}
	
	//-----------------------------------------------------------------------
	SPlayer::~SPlayer()
	{

	}
	//-----------------------------------------------------------------------
	void SPlayer::setFrontServerId( I32 netId )
	{
		mFrontServerNetID = netId;
	}
	//-----------------------------------------------------------------------
	void SPlayer::addLoginErrorCount()
	{
		mLoginErrorCount++;
	}
	//-----------------------------------------------------------------------
	void SPlayer::setLoginErrorCount( I32 count )
	{
		mLoginErrorCount = count;
	}
	//-----------------------------------------------------------------------
	MG::I32 SPlayer::getLoginErrorCount()
	{
		return mLoginErrorCount;
	}
	//-----------------------------------------------------------------------
	void SPlayer::setLoginState( SPlayer::LoginState state )
	{
		mLoginState = state;
		mStateStartTime = MGTimeOp::getCurrTick();
		// 设置各个状态的时间
		switch(state)
		{
		case LoginState_Disconnect:
			mStateDestoryTime = 0;
			break;
		case LoginState_SendNoFrontInfo:
			mStateDestoryTime = LoginManager::getInstance().getMaxLoginTimeout();
			break;
		case LoginState_SendFrontInfo:
			mStateDestoryTime = 20000;
			break;

		}
	}
	//-----------------------------------------------------------------------
	SPlayer::LoginState SPlayer::getLoginState()
	{
		return mLoginState;
	}
	//-----------------------------------------------------------------------
	U32 SPlayer::getStateStartTime()
	{
		return mStateStartTime;
	}
	//-----------------------------------------------------------------------
	U32 SPlayer::getStateDestoryTime()
	{
		return mStateDestoryTime;
	}
	//-----------------------------------------------------------------------
	Bool SPlayer::isInLogingList()
	{
		return mIsInLogingList;
	}
	//-----------------------------------------------------------------------
	void SPlayer::setInLogingList( Bool inLoingingList /*= true*/ )
	{
		mIsInLogingList = inLoingingList;
	}
	//-----------------------------------------------------------------------
	Bool SPlayer::isInLoginedList()
	{
		return mIsInLoginedList;
	}
	//-----------------------------------------------------------------------
	void SPlayer::setInLoginedList( Bool inLoingedList /*= true*/ )
	{
		mIsInLoginedList = inLoingedList;
	}
	//-----------------------------------------------------------------------
	U32 SPlayer::getLoginNo()
	{
		return mLogingNo;
	}
	//-----------------------------------------------------------------------
	U32 SPlayer::getLastSendQueueInfoTick()
	{	
		return mLastSendLoginQueueInfoTick;
	}
	//-----------------------------------------------------------------------
	void SPlayer::setLastSendQueueInfoTick( U32 tick )
	{
		mLastSendLoginQueueInfoTick = tick;
	}
	//-----------------------------------------------------------------------
	void SPlayer::addRefCount()
	{
		mRefCount++;
	}
	//-----------------------------------------------------------------------
	I32 SPlayer::subRefCount()
	{
		return --mRefCount;
	}
	//-----------------------------------------------------------------------
	I32 SPlayer::getRefCount()
	{
		return mRefCount;
	}
	//-----------------------------------------------------------------------
	Bool SPlayer::IsCheckDisConnect()
	{
		if (mIsCheckDisConnect)
		{
			return true;
		}
		else
		{
			mIsCheckDisConnect = true;
		}
		return false;
	}
	//-----------------------------------------------------------------------
	Bool SPlayer::IsCheckInFront()
	{
		if (mIsCheckInFrontServer )
		{
			return true;
		}
		else
		{
			mIsCheckInFrontServer = true;
		}
		return false;
	}

	MG::U32 SPlayer::getIp()
	{
		return mIP;
	}

	void SPlayer::setIP( U32 ip )
	{
		mIP = ip;
	}
	//-----------------------------------------------------------------------

	/******************************************************************************/
	//LoginManager
	/******************************************************************************/
	//-----------------------------------------------------------------------
	LoginManager::LoginManager()
	{
		mMaxLoginCount						= 5000;	
		mMaxLoginWaitCount					= 0;
		mMaxLoginTimeoutValue				= 10 * 60 * 1000; //10分钟
		mForbidedLoginTime					= 5 * 60 * 1000;  //5分钟	 
		mUpdateLoginQueueIntervalTime		= 10;	
		mUpdateForbidedLogintervalTime	= mForbidedLoginTime;
		mMaxErrorLoginCount					= 5;
		mMaxFrontServerLoginCount			= 1000;
	}

	//-----------------------------------------------------------------------
	LoginManager::~LoginManager()
	{
	}

	//-----------------------------------------------------------------------
	Bool LoginManager::initialize(DBDriver* Driver,SServerSetting* setting,LoginConfigInfo* loginConfigInfo)
	{
		//mMySqlDriver = Driver;
		//DYNAMIC_ASSERT(mMySqlDriver);
		//if (setting->getDbConnectInfo()->isCreate)
		//{
		//	AccountDBOp::checkOrCreateAccountTable(*(mMySqlDriver));
		//}

		if ( mCheckLogingPlayerThread.create( checkLogingClientThread,this) == false )
		{
			return false;
		}
		if ( mCheckLoginedPlayerThread.create( checkLoginedClientThread,this ) == false )
		{
			return false;
		}
		if ( mCheckErrorPlayerThread.create( checkErrorClientThread,this ) == false )
		{
			return false;
		}
#ifdef _DEBUG
		Thread::SetThreadName(mCheckLogingPlayerThread.getThreadId(),"LoginManager::mCheckLogingPlayerThread");
		Thread::SetThreadName(mCheckLoginedPlayerThread.getThreadId(),"LoginManager::mCheckLoginedPlayerThread");
		Thread::SetThreadName(mCheckErrorPlayerThread.getThreadId(),"LoginManager::mCheckErrorPlayerThread");
#endif // _DEBUG
		
//#ifdef _DEBUG
		Thread::SetThreadName(mCheckLogingPlayerThread.getThreadId(),"checkLogingClientThread");
		Thread::SetThreadName(mCheckLoginedPlayerThread.getThreadId(),"checkLoginedClientThread");
		Thread::SetThreadName(mCheckErrorPlayerThread.getThreadId(),"checkErrorClientThread");
//#endif
		/**************
		初始化登录配置
		***************/
        if (loginConfigInfo)
		{
			setMaxLoginCount(loginConfigInfo->mMaxLoginCount);
			setMaxWaitCount(loginConfigInfo->mMaxLoginWaitCount);
			setMaxLoginTimeout(loginConfigInfo->mMaxLoginTimeoutValue);
			setUpdateLoginQueueIntervalTime(loginConfigInfo->mUpdateLoginQueueIntervalTime);
			setUpdateForbidedLogintervalTime(loginConfigInfo->mUpdateForbidedLoginIntervalTime);
			setForbidedLoginTime(loginConfigInfo->mForbidedLoginTime);
			setMaxErrorLoginCount(loginConfigInfo->mMaxErrorLoginCount);
			setMaxFrontServerLoginCount(loginConfigInfo->mMaxFrontServerLoginCount);
		}
	

		return true;
	}
    
	//-----------------------------------------------------------------------
	void LoginManager::uninitialize()
	{
		mCheckLogingPlayerThread.destory();
		mCheckLoginedPlayerThread.destory();
		mCheckErrorPlayerThread.destory();

		mLogingMapByClientNetIdLock.lock();
		mLogingMapByClientNetId.clear();
		mLogingMapByClientNetIdLock.unlock();

		mLoginedMapByClientNetIdLock.lock();
		mLoginedMapByClientNetId.clear();
		mLoginedMapByClientNetIdLock.unlock();

		mLogingMapByAccNameLock.lock();
		mLogingMapByAccName.clear();
		mLogingMapByAccNameLock.unlock();

		mLoginedMapByAccNameLock.lock();
		mLoginedMapByAccName.clear();
		mLoginedMapByAccNameLock.unlock();
		
		SPlayer* player = getFromLogingQueuingQueue();
		while(player)
		{
			player = getFromLogingQueuingQueue();

            if ( player )
            {
                if (player->subRefCount() == 0)
                {
                    destoryPlayer(player);
                }
            }
		}

		player = getFromLoginedQueue();
		while(player)
		{
			player = getFromLoginedQueue();

            if ( player )
            {
                if (player->subRefCount() == 0)
                {
                    destoryPlayer(player);
                }
            }
		}

		mErrorLogingMapByAccNameLock.lock();
		mErrorLogingMapByAccName.clear();
		mErrorLogingMapByAccNameLock.unlock();

		ErrorLoginPlayer* errPlayer = getFromErrorLogingQueue();
		while(errPlayer)
		{
			errPlayer = getFromErrorLogingQueue();

            if ( errPlayer )
                destoryErrorPlayer(errPlayer);
		}
	}

	//-----------------------------------------------------------------------
	void LoginManager::update()
	{

	}

	//-----------------------------------------------------------------------
	void LoginManager::handleClientLogin(I32 id, Char16* accName, Char16* accPsw)
	{


		///查看是否存在于错误登陆队列中
		ErrorLoginPlayer* errPlayer = getErrorPlayerByAccName(accName);
		if (errPlayer && errPlayer->getErrorCount() > MG_LOGIN_ERROR_COUNT)
		{
			// 登陆错误次数达到上限 通知客户端 并断开链接
			{
				LoginNetPacketProcesser::getInstance().sendLoginErrorPacketToClient(id,LCFT_LOGIN_IDENTITY_ERROR_MAX);
				LoginServerMain::getInstance().getServerLauncher()->closeClient(id);
				return;
			}

		}
		
		Int waitCount = mCurrLogingNo - mFirstLogingPlayerNo;
		if (waitCount > LineUpSettingInfo::line_up_busy_lc_account_login_start_count)
		{
			///发送排队信息 
			LineUpNetPacketProcesser::getInstance().sendLineUpInfoToClient(id,line_up_busy_lc_account_login,waitCount);
		}
		
		
		SPlayer* playerLogined  = getFromLoginedMapByAccName( accName);
		if (playerLogined )
		{
			if ( playerLogined->getPassword().compare(accPsw) == 0)
			{
				removeLoginedPlayerByAccName(accName);
				removeLogingPlayerByAccName(accName);
				LoginNetPacketProcesser::getInstance().sendLoginErrorPacketToClient(id,LCFT_LOGIN_REDUPLICATE);
				//LoginNetPacketProcesser::getInstance().sendFrontServerKickoutClient(playerLogined->getFrontServerNetID(),playerLogined->getClientId());
				LoginServerMain::getInstance().getServerLauncher()->closeClient(id);
				return;
			}
			else
			{
				// 用户已经登录，当前正在登录的用户，密码不正确，为非法
				LoginServerMain::getInstance().getServerLauncher()->closeClient(id);
				return;
			}

		}


		SPlayer* playerLoging = getFromLogingMapByAccName( accName);
		if (playerLoging)
		{
			if ( playerLoging->getPassword().compare(accPsw) == 0)
			{
				removeLogingPlayerByAccName(accName);
				LoginNetPacketProcesser::getInstance().sendLoginErrorPacketToClient(id,LCFT_LOGIN_REDUPLICATE);
				LoginServerMain::getInstance().getServerLauncher()->closeClient(id);
				return;
			}
			else
			{
				// 用户已经正在登录中，当前正在登录的用户，密码不正确，为非法
				LoginServerMain::getInstance().getServerLauncher()->closeClient(id);
				return;
			}

		}
		

		addLogingPlayer(id,accName,accPsw,mCurrLogingNo++);
		//LoginNetPacketProcesser::sendLoginSuccessPacketToClient()
		
	}
	
	//-----------------------------------------------------------------------
	void LoginManager::handleClientLoginFrontServer(I32 id, I32 clientNetIdInFrontServer, Char16* accName, Char16* accPsw)
	{
		SPlayer* player = removeLogingPlayerForAccCheck(id, accName, accPsw);
		if ( player == NULL )
		{
			//发送身份验证失败消息
			LoginNetPacketProcesser::getInstance().sendClientLoginFrontServerResult(id, clientNetIdInFrontServer, accName,accPsw,0,LFCT_LOGIN_FAIL);
		}else
		{
			addLoginedPlayer( accName,player );

			LoginServerMain::getInstance().getServerLauncher()->closeClient( player->getClientId() );
			
			LoginNetPacketProcesser::getInstance().sendCheckClientInFrontServer(id,clientNetIdInFrontServer,player->getClientId());
			//发送身份验证成功消息
			LoginNetPacketProcesser::getInstance().sendClientLoginFrontServerResult(id, clientNetIdInFrontServer, accName,accPsw,player->getAccountID(),LFCT_LOGIN_SUCCESS);

			//向日志服务器发送玩家登入日志
			SysLogNetPacketProcesser::getInstance().sendAccountInfoToSysLogServer(
				ServerManager::getInstance().getSysLogServerNetID()
				, player->getClientId()
				, ACCOUNT_OPERATE_LOGIN
				, player->getAccountID()
				, player->getIp()
				);
            
		}
	}

	//-----------------------------------------------------------------------
	void LoginManager::handleClientLogoutFrontServer(Char16* accName)
	{
		removeLoginedPlayerByAccName( accName );
	}

	//-----------------------------------------------------------------------
	void LoginManager::handleFrontServerDisconnect(I32 id)
	{
		removePlayerByFrontNetId(id);
	}
	//-----------------------------------------------------------------------------
	void LoginManager::handleCheckClientInFrontServerResult( I32 clientNetId ,Bool result)
	{
		if (!result)
		{
			removeLoginedPlayerByNetId(clientNetId);
		}
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::createPlayer( I32 netId, Char16* accName, Char16* accPsw, IdType accID,U32 LogingNo )
	{
		SPlayer* player = NULL;
		mPlayerPool.threadLock();
		player = MG_POOL_NEW(mPlayerPool,SPlayer,(netId,accID,accName,accPsw,LogingNo));
		mPlayerPool.threadUnLock();
		return player;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::destoryPlayer(SPlayer* player)
	{
		DYNAMIC_ASSERT(player);
		mPlayerPool.threadLock();
		MG_POOL_DELETE(mPlayerPool,player);
		mPlayerPool.threadUnLock();
	}
	//-----------------------------------------------------------------------

	void LoginManager::checkLogingClientThread(Ptr ptr)
	{
		OneThreadHandle* thd = (OneThreadHandle* )ptr;
		if (thd && thd->getParam())
		{
			LoginManager* mgr = (LoginManager *)thd->getParam();
			if ( mgr )
			{
				SPlayer* player1 = NULL;
				//----while begin------------------------------------
				U32 lastTick =  MGTimeOp::getCurrTick();
				while( thd->isRun() )
				{
					player1 = mgr->getFromLogingQueuingQueue();
					while (!player1)
					{
                        if ( thd->isRun() == false )
                            return;

						player1 = mgr->getFromLogingQueuingQueue();

						Sleep(5);
					}
					
					Bool isContinue = true;
					if (player1)
					{
						if (player1->isInLogingList())
						{
							if (!player1->IsCheckDisConnect())
							{
								ClientManager::getInstance().getClientFromMap(player1->getClientId());
								mgr->removeErrorPlayerByAccName((Char16*)player1->getName().c_str());
							}

							I32 LogingCout = player1->getLoginNo() - mgr->mFirstLogingPlayerNo;
							
							
							// 等待游戏中有人退出 因为暂时没有考虑退出时LoginCount的变化 下面逻辑会出现问题 
							/*if (LogingCout + mgr->mLoginedQueue.size() > mgr->getMaxLoginCount())
							{
								if (player1->getLoginState() != SPlayer::LoginState_SendFrontInfo)
								{
									LoginServerMain::getInstance().getServerLauncher()->closeClient(player1->getClientId());
									ServerManager::getInstance().freeClientConnect(player1->getFrontServerNetID());
									mgr->removeLogingPlayerByAccName((Char16*)player1->getName().c_str(),false);
									isContinue = false;
								}
							}*/
							
							if (isContinue)
							{
								// 发送FrontServer信息给客户端
								if(player1->getLoginState() == SPlayer::LoginState_SendNoFrontInfo)
								{
									LineUpNetPacketProcesser::getInstance().sendLineUpInfoToClient(player1->getClientId(),line_up_busy_lc_account_login);
									
									AccountIdType accountId = 0;
									Bool isContinue = false;
									Bool errPsw = false;
									if (LoginConfig::getInstance().getLoginConfigInfo()->mUsePlatformAccount)
									//----------------------------------------------------------
									{
										// 平台帐号验证
			

										std::map<Str16,Str16> platformRetValue;

										//player1->mFrontServerId
										ClientObject* clientObj = ClientManager::getInstance().getClientFromMap(player1->getClientId());
										if (clientObj)
										{
											Int code = PlatformCheckAccount::getInstance().checkAccount((Char16*)player1->getName().c_str(),(Char16*)player1->getPassword().c_str(),clientObj->mAddr,platformRetValue);				

											if (code == 21)
											{
												if(!AccountDBOp::selectAccountByName(*(mgr->mMySqlDriver),(Char16*)player1->getName().c_str(),accountId))
												{
													if (AccountDBOp::createAccount(*(mgr->mMySqlDriver),(Char16*)player1->getName().c_str(),(Char16*)player1->getPassword().c_str(),accountId))
													{
														isContinue = true;	
													}
												}
												else
												{
													isContinue = true;
												}
											}
											else
											{
												if (code == 3)
												{
													errPsw = true;
												}
											}
										}

									}
									else
										//----------------------------------------------------------
									{
										if ( AccountDBOp::checkAccount(*(mgr->mMySqlDriver),accountId,(Char16*)player1->getName().c_str(),(Char16*)player1->getPassword().c_str()) )
										{
											isContinue = true;
											errPsw = false;
										}
										else
										{
											isContinue = false;
											errPsw = true;
										}
									}
									
									if ( isContinue )
									{
										player1->setAccountID(accountId);
										mgr->removeErrorPlayerByAccName((Char16*)player1->getName().c_str());
										FrontServerInfo* frontSvr = ServerManager::getInstance().allocClientConnect();
										if (frontSvr)
										{
											player1->setFrontServerId(frontSvr->netId);
											//发送登陆FrontServer消息给客户端
											player1->setLoginState(SPlayer::LoginState_SendFrontInfo);
											frontSvr->listenClientPort = 2002;	//testcode
											LoginNetPacketProcesser::getInstance().sendLoginSuccessPacketToClient(player1->getClientId(),frontSvr->listenClientIp.c_str(),frontSvr->listenClientPort);
										}
										else
										{
                                            DYNAMIC_EEXCEPT_LOG("LoginManager::checkLogingClientThread : not find front server");
											//发送没有登入服务器消息
											LoginNetPacketProcesser::getInstance().sendLoginErrorPacketToClient(player1->getClientId(),LCFT_LOGIN_NONE_FRONTSERVER);
											LoginServerMain::getInstance().getServerLauncher()->closeClient(player1->getClientId());
											mgr->removeLogingPlayerByAccName((Char16*)player1->getName().c_str());
										}
									}
									else
									// 帐号检测失败
									{
										// 移除该玩家
										mgr->removeLogingPlayerByAccName((Char16*)(player1->getName().c_str()));
										// 密码错误
										if (errPsw)
										{
											LoginNetPacketProcesser::getInstance().sendLoginErrorPacketToClient(player1->getClientId(),LCFT_LOGIN_IDENTITY_ERROR);
											ErrorLoginPlayer* errPlayer = mgr->getErrorPlayerByAccName((Char16*)(player1->getName().c_str()));
											//LoginServerMain::getInstance().getServerLauncher()->closeClient(player1->getClientId());
											if (errPlayer)
											{
												errPlayer->addErrorCount();
											}
											else
											{
												mgr->addErrorPlayer((Char16*)(player1->getName().c_str()));
											}
										}
						
									}

								}
							}
							mgr->addToLogingQueuingQueue(player1);
							player1->subRefCount();
						}
						else
						{

							//if (player1->getLoginNo() == mgr->mFirstLogingPlayerNo)
							{
								mgr->mFirstLogingPlayerNo++;
							}
							if (player1->subRefCount() == 0)
							{
								mgr->destoryPlayer(player1);
							}
						}
						
					}
				}
				//----while begin------------------------------------
			}
		}
	
		
#if 0		
		static U32 lastTick = MGTimeOp::getCurrTick();
		static U32 currTick = MGTimeOp::getCurrTick();

		static U32 lastErrorLoginUpdateTick = MGTimeOp::getCurrTick();
		static U32 lastLogingUpdateTick = MGTimeOp::getCurrTick();
		Bool isIdle1 = false;
		Bool isIdle2 = false;
		Bool isIdle3 = false;
		static I32 sendFrontInfoCount = 0;
		OneThreadHandle* thd = (OneThreadHandle* )ptr;
		if (thd && thd->getParam())
		{
			LoginManager* mgr = (LoginManager *)thd->getParam();
			if ( mgr )
			{
				while( thd->isRun())
				{
					SPlayer* player= NULL;
					Bool isErase = false;
					currTick = MGTimeOp::getCurrTick();
					I32 loginedCount = mgr->getLoginedCount();
					I32 LogingCount = 0;
					///定时发送排队信息
					///----------------------------------------------------------------------------------
					if (currTick - lastTick >= mgr->getUpdateLoginQueueIntervalTime())
					{
						isIdle1 = false;
						mgr->mLogingListLock.lock();
						{
							std::list<SPlayer* >::iterator iter = mgr->mLogingList.begin();
							for( ; iter != mgr->mLogingList.end(); iter++)
							{
								player = *iter;
								LogingCount++;
								I32 waittingCount = LogingCount + loginedCount - mgr->getMaxLoginCount();
								if (player)
								{
									if (waittingCount > 0)
									{
										if (waittingCount <= mgr->getMaxWaitCount())
										{
											//TODO:
											//你前面还有waittingCount人在等待登录
											//LoginNetPacketProcesser::getInstance().sendLoginQueueInfoToClient(player->getClientId(),login_line_up_waitting,waittingCount);
										}
										// 超过最大等待登录人数
										else
										{
											//TODO:
											//登录服务器繁忙，请稍后再登录
											LoginNetPacketProcesser::getInstance().sendLoginQueueInfoToClient(player->getClientId(),login_line_up_full);
										}
										
									}
									else
									{
										//TODO:
										//目前有多少人正在登录中请等待多长时间
										if (LogingCount > 10)
										{
											LoginNetPacketProcesser::getInstance().sendLoginQueueInfoToClient(player->getClientId(),login_line_up_busy,LogingCount);
										}
										
									}
									
								}
							}
						}
						mgr->mLogingListLock.unlock();
						lastTick = currTick;
					}
					else
					{
						isIdle1 = true;
					}
					///更新等待登陆队列（超时，客户端数）
					//----------------------------------------------------------------------------------
                    I32 waittingCount = 0;
					if (currTick - lastLogingUpdateTick >= 100)
					{
						isIdle2 = false;
						player = NULL;
						LogingCount = 0;
						loginedCount = mgr->getLoginedCount();
						mgr->mLogingListLock.lock();
						{
							std::list<SPlayer* >::iterator iter = mgr->mLogingList.begin();
							for( ;iter != mgr->mLogingList.end();)
							{
								isErase = false;
								player = *iter;
								//检测超时
								if (player->getStateDestoryTime() != 0 && currTick - player->getStateStartTime() > player->getStateDestoryTime() )
								{
									iter = mgr->mLogingList.erase( iter );
									isErase = true;
								}
								// 检测服务器人数是否已满
								else
								{
									waittingCount = LogingCount + loginedCount - mgr->getMaxLoginCount();
									if (waittingCount > 0)
									{
										//TODO:
										//服务器登陆人数已满
										iter = mgr->mLogingList.erase( iter );
										isErase = true;
									}
									else
									{
										iter++;
										LogingCount++;
										
									}

								}
								if ( isErase )
								{
									LoginServerMain::getInstance().getServerLauncher()->closeClient(player->getClientId());
									ServerManager::getInstance().freeClientConnect(player->getFrontServerNetID());
									MG_POOL_DELETE(mgr->mPlayerPool,player);
								}
							}
							//----------------------------------------------------------------------------------
                            std::list<SPlayer* >::iterator iter1 = mgr->mLogingList.begin();
                            {
                                for( ;iter1 != mgr->mLogingList.end();iter1++)
                                {
                                    player = *iter1;
                                    if (player)
                                    {
                                        if(player->getLoginState() == SPlayer::LoginState_SendNoFrontInfo)
                                        {
                                            //TODO:
                                            //发送FrontServer信息
                                            FrontServerInfo* frontSvr = ServerManager::getInstance().getFrontServer(player->getFrontServerNetID());
                                            if (!frontSvr)
                                            {
                                                frontSvr = ServerManager::getInstance().allocClientConnect();
                                                if (frontSvr)
                                                {
                                                    player->setFrontServerId(frontSvr->netId);
                                                    player->setLoginState(SPlayer::LoginState_SendFrontInfo);
													MG_LOG(out_game_logic,"发送FrintInfo次数%d\n",++sendFrontInfoCount);
                                                    LoginNetPacketProcesser::getInstance().sendLoginSuccessPacketToClient(player->getClientId(),frontSvr->listenClientIp.c_str(),frontSvr->listenClientPort);

                                                }
                                                else
                                                {
                                                    DYNAMIC_ASSERT(false);
                                                    //发送没有登入服务器消息
                                                    LoginNetPacketProcesser::getInstance().sendLoginErrorPacketToClient(player->getClientId(),LCFT_LOGIN_NONE_FRONTSERVER);

                                                }
                                            }
                                            else
                                            {
                                                //发送登陆FrontServer消息
                                                player->setLoginState(SPlayer::LoginState_SendFrontInfo);
												MG_LOG(out_game_logic,"发送FrintInfo次数%d\n",++sendFrontInfoCount);
                                                LoginNetPacketProcesser::getInstance().sendLoginSuccessPacketToClient(player->getClientId(),frontSvr->listenClientIp.c_str(),frontSvr->listenClientPort);
                                            }
                                            break;
                                        }
                                    }
                                }
                            }
                           
						}
						mgr->mLogingListLock.unlock();
						lastLogingUpdateTick = currTick;
					}
					else
					{
						isIdle2 = true;
					}
					
					
					//更新错误列表
					//----------------------------------------------------------------------------------
					if (currTick - lastErrorLoginUpdateTick > mgr->getUpdateForbidedLogintervalTime())
					{
						isIdle3 = false;

						mgr->mErrorLogingListLock.lock();
						{
							std::map< Str16, SPlayer* >::iterator iter = mgr->mErrorLogingList.begin();
							for (; iter != mgr->mErrorLogingList.end();)
							{
								SPlayer* player = iter->second;
								Bool isErase = false;
								if (player)
								{	
									// 超过50移除错误登陆账号
									if (currTick - player->getCreateTime() > mgr->getForbidedLoginTime())
									{
										iter = mgr->mErrorLogingList.erase(iter);
										isErase = true;
									}
								}
								else
								{
									DYNAMIC_ASSERT(false);
									iter = mgr->mErrorLogingList.erase(iter);
									isErase = true;
								}

								if (isErase)
								{
									if (player)
									{
										MG_POOL_DELETE(mgr->mPlayerPool,player);
									}
								}
								else
								{
									iter++;
								}
							}
						}
						mgr->mErrorLogingListLock.unlock();
						lastErrorLoginUpdateTick = currTick;
						//----------------------------------------------------------------------------------
					}
					else
					{
						isIdle3 = true;
					}
			
					if (isIdle1 && isIdle2 &&isIdle3 )
					{
						Sleep(5);
					}
				}
			}
		}
#endif

	}
	//-----------------------------------------------------------------------------
	void LoginManager::checkLoginedClientThread( Ptr ptr )
	{
		OneThreadHandle* thd = (OneThreadHandle* )ptr;
		if (thd && thd->getParam())
		{
			LoginManager* mgr = (LoginManager *)thd->getParam();
			if ( mgr )
			{
				SPlayer* player = NULL;
				U32 lastSendQueueInfoTick = MGTimeOp::getCurrTick();
				U32 currIndexInQueue = 0;
				//-------while begin------------
				while( thd->isRun())
				{
					player = mgr->getFromLoginedQueue();
					while (!player)
					{
                        if ( thd->isRun() == false )
                            return;

						player = mgr->getFromLoginedQueue();

						Sleep(10);
					}
					if (player)
					{
						if (player->isInLoginedList())
						{
							// 此逻辑放在等了验证成功处
							/*if( !player->IsCheckInFront() )
							{
								LoginNetPacketProcesser::getInstance().sendCheckClientInFrontServer(player->getFrontServerNetID(),(Char16*)player->getName().c_str());
							}*/
							
							mgr->addToLoginedQueue(player);
							player->subRefCount();
						}
						else
						{
							if (player->subRefCount() == 0)
							{
								mgr->destoryPlayer(player);
							}
						}
							
					}
					Sleep(5);
				}
				//-------while end------------
			}
		}
	}

	//-----------------------------------------------------------------------------
	void LoginManager::checkErrorClientThread( Ptr ptr )
	{
		OneThreadHandle* thd = (OneThreadHandle* )ptr;
		if (thd && thd->getParam())
		{
			LoginManager* mgr = (LoginManager *)thd->getParam();
			if ( mgr )
			{
				ErrorLoginPlayer* errorPlayer = NULL;
				//-------while begin------------
				while( thd->isRun())
				{
					//TODO: 是否要加锁
					//--------------------------------------------------------
					errorPlayer = mgr->getFromErrorLogingQueue();
					while (!errorPlayer)
					{
                        if ( thd->isRun() == false )
                            return;

						errorPlayer = mgr->getFromErrorLogingQueue();

						Sleep(10);
					}

					U32 currTick = MGTimeOp::getCurrTick();
					if (errorPlayer)
					{
						if (errorPlayer->getDirty())
						{
							mgr->destoryErrorPlayer(errorPlayer);
						}
						else
						{
							if (currTick - errorPlayer->getCreateTime() > mgr->getForbidedLoginTime())
							{
								mgr->removeErrorPlayerByAccName(errorPlayer->getName());
							}

						}
					}
					Sleep(5);
				}
				//-------while end------------
			}
		}
	}
	//-----------------------------------------------------------------------------
	ErrorLoginPlayer* LoginManager::createErrorPlayer( Char16* accName )
	{
		ErrorLoginPlayer* errorPlayer = NULL;
		mErrorLoginPlayerPool.threadLock();
		errorPlayer = MG_POOL_NEW(mErrorLoginPlayerPool,ErrorLoginPlayer,(accName));
		mErrorLoginPlayerPool.threadUnLock();
		DYNAMIC_ASSERT(errorPlayer);
		return errorPlayer;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::destoryErrorPlayer( ErrorLoginPlayer* errorPlayer )
	{
		DYNAMIC_ASSERT(errorPlayer);
		mErrorLoginPlayerPool.threadUnLock();
		MG_POOL_DELETE(mErrorLoginPlayerPool,errorPlayer)
		mErrorLoginPlayerPool.threadUnLock();
	}
	//-----------------------------------------------------------------------------
	MG::U32 LoginManager::getMaxLoginCount()
	{
		return mMaxLoginCount;
	}
	//-----------------------------------------------------------------------------
	MG::U32 LoginManager::getMaxWaitCount()
	{
		return mMaxLoginWaitCount;
	}
	//-----------------------------------------------------------------------------
	MG::U32 LoginManager::getMaxLoginTimeout()
	{
		return mMaxLoginTimeoutValue;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::setMaxLoginCount( U32 maxLoginCount )
	{
		mMaxLoginCount = maxLoginCount;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::setMaxWaitCount( U32 maxWaitCount )
	{
		mMaxLoginWaitCount = maxWaitCount;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::setMaxLoginTimeout( U32 loginTimeOutValue )
	{
		mMaxLoginTimeoutValue = loginTimeOutValue;
	}
	//-----------------------------------------------------------------------------
	U32 LoginManager::getUpdateLoginQueueIntervalTime()
	{
		return mUpdateLoginQueueIntervalTime;	
	}
	//-----------------------------------------------------------------------------
	void LoginManager::setUpdateLoginQueueIntervalTime(U32 intervalTime)
	{
		mUpdateLoginQueueIntervalTime = intervalTime;
	}
	//-----------------------------------------------------------------------------
	U32 LoginManager::getUpdateForbidedLogintervalTime()
	{
		return mUpdateForbidedLogintervalTime;
	}
	//-----------------------------------------------------------------------------
	U32 LoginManager::getForbidedLoginTime()
	{
		return mForbidedLoginTime;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::setUpdateForbidedLogintervalTime( U32 intervalTime )
	{
		mUpdateForbidedLogintervalTime = intervalTime;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::setForbidedLoginTime( U32 forbiddenTime )
	{
		mForbidedLoginTime = forbiddenTime;
	}
	//-----------------------------------------------------------------------------
	U32 LoginManager::getMaxErrorLoginCount()
	{
		return mMaxErrorLoginCount;
	}
	//-----------------------------------------------------------------------------
	U32 LoginManager::getMaxFrontServerLoginCount()
	{
		return mMaxFrontServerLoginCount;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::setMaxErrorLoginCount( U32 maxErrorLoginCount )
	{
		mMaxErrorLoginCount = mMaxErrorLoginCount;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::setMaxFrontServerLoginCount( U32 maxFrontServerLoginCount )
	{
		mMaxFrontServerLoginCount = maxFrontServerLoginCount;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::addLogingPlayer( I32 netId, Char16* accName, Char16* accPsw, U32 loginNo )
	{
		ClientObject* pClientObject = ClientManager::getInstance().getClientFromMap(netId);
		if (NULL == pClientObject)
		{
			return;
		}
		SPlayer* player = createPlayer( netId, accName,  accPsw, 0,loginNo );
		DYNAMIC_ASSERT(player);
		addToLogingMapByAccName(accName,player);
		addToLogingMapByClientNetId(netId,player);
		player->setInLogingList(true);
		player->setLoginState(SPlayer::LoginState_SendNoFrontInfo);
		player->setIP(pClientObject->mAddr.getIP());
		addToLogingQueuingQueue(player);
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::removeLogingPlayerByNetId( I32 clientNetId )
	{

		SPlayer* player = removeFromLogingMapByClientNetId(clientNetId);
		if (player)
		{
			SPlayer* player1 = removeFromLogingMapByAccName((Char16*)player->getName().c_str());
			DYNAMIC_ASSERT(player1);
			player->setInLogingList(false);

		}
		
		return player;
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::removeLogingPlayerByAccName( Char16* accName,Bool hasNextOp /*= true*/ )
	{
		SPlayer* player = removeFromLogingMapByAccName(accName);
		if (player)
		{
			SPlayer* player1 = removeFromLogingMapByClientNetId(player->getClientId());
			DYNAMIC_ASSERT(player1)
		
			player->setInLogingList(false);
		}
		
		return player;
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::removeLogingPlayerForAccCheck( I32 netId,Char16* accName, Char16* accPsw )
	{
		SPlayer *player = removeFromLogingMapByAccName(accName);
		if (player)
		{
			SPlayer *player1 = removeFromLogingMapByClientNetId(player->getClientId());
			DYNAMIC_ASSERT(player1);
			if (player->getName().compare(accName) == 0
				&& player->getPassword().compare(accPsw) == 0)
			{
				return player;
			}
			else
			{
				player->setInLogingList(false);
				return NULL;
			}
			
		}
	
		return NULL;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::addLoginedPlayer( Char16* accName,SPlayer* player )
	{
		addToLoginedMapByAccName(accName,player);
		addToLoginedMapByClientNetId(player->getClientId(),player);
		player->setInLoginedList(true);
		addToLoginedQueue(player);
		player->setInLogingList(false);
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::removeLoginedPlayerByNetId( I32 clientNetId )
	{
		SPlayer* player = removeFromLoginedMapByClientNetId(clientNetId);
		if (player)
		{
			SPlayer* player1 = removeFromLoginedMapByAccName((Char16*)player->getName().c_str());
			if (!player1)
			{
				DYNAMIC_ASSERT(false);
			}
			player->setInLoginedList(false);
		}
		
		return player;
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::removeLoginedPlayerByAccName( Char16* accName )
	{
		SPlayer* player = removeFromLoginedMapByAccName(accName);
		if (player)
		{
			SPlayer* player1 = removeFromLoginedMapByClientNetId(player->getClientId());
			if (!player1)
			{
				//DYNAMIC_ASSERT(false);
			}
			player->setInLoginedList(false);

			//向日志服务器发送玩家登出日志
			SysLogNetPacketProcesser::getInstance().sendAccountInfoToSysLogServer(
				ServerManager::getInstance().getSysLogServerNetID()
				, player->getClientId()
				, ACCOUNT_OPERATE_LOGOUT
				, player->getAccountID()
				, player->getIp()
				);
		}
		return player;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::removePlayerByFrontNetId( I32 frontServerNetId )
	{
		
	}
	//-----------------------------------------------------------------------------
	void LoginManager::addErrorPlayer( Char16* accName )
	{
		ErrorLoginPlayer* errPlayer = createErrorPlayer(accName);
		DYNAMIC_ASSERT(errPlayer);
		errPlayer->addErrorCount();
		mErrorLogingMapByAccNameLock.lock();
		mErrorLogingMapByAccName[accName] = errPlayer;
		mErrorLogingMapByAccNameLock.unlock();
	}
	//-----------------------------------------------------------------------------
	ErrorLoginPlayer* LoginManager::removeErrorPlayerByAccName( Char16* accName )
	{
		ErrorLoginPlayer* errPlayer = NULL;
		mErrorLogingMapByAccNameLock.lock();
		std::map< Str16,ErrorLoginPlayer* >::iterator it = mErrorLogingMapByAccName.find(accName);
		if (it != mErrorLogingMapByAccName.end())
		{
			errPlayer = it->second;
			mErrorLogingMapByAccName.erase(it);
			DYNAMIC_ASSERT(errPlayer);
			errPlayer->setDirty(true);
		}
		mErrorLogingMapByAccNameLock.unlock();
		return errPlayer;
	}
	//-----------------------------------------------------------------------------
	ErrorLoginPlayer* LoginManager::getErrorPlayerByAccName( Char16* accName )
	{
		ErrorLoginPlayer* errPlayer = NULL;
		mErrorLogingMapByAccNameLock.lock();
		std::map< Str16,ErrorLoginPlayer* >::iterator it = mErrorLogingMapByAccName.find(accName);
		if (it != mErrorLogingMapByAccName.end())
		{
			errPlayer = it->second;
			DYNAMIC_ASSERT(errPlayer);
			errPlayer->setDirty(true);
		}
		mErrorLogingMapByAccNameLock.unlock();
		return errPlayer;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::addToLogingMapByClientNetId( I32 clientNetID, SPlayer* player )
	{
		mLogingMapByClientNetIdLock.lock();
		mLogingMapByClientNetId[clientNetID] = player;
		mLogingMapByClientNetIdLock.unlock();
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::getFromLogingMapByClientNetId( I32 clientNetID )
	{
		SPlayer* player = NULL;
		mLogingMapByClientNetIdLock.lock();
		std::map< I32, SPlayer* >::iterator it = mLogingMapByClientNetId.find(clientNetID);
		if (it != mLogingMapByClientNetId.end())
		{
			player = it->second;
			DYNAMIC_ASSERT(player);
		}
		mLogingMapByClientNetIdLock.unlock();
		return player;
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::removeFromLogingMapByClientNetId( I32 clientNetID )
	{
		SPlayer* player = NULL;
		mLogingMapByClientNetIdLock.lock();
		std::map< I32, SPlayer* >::iterator it = mLogingMapByClientNetId.find(clientNetID);
		if (it != mLogingMapByClientNetId.end())
		{
			player = it->second;
			DYNAMIC_ASSERT(player);
			mLogingMapByClientNetId.erase(it);
		}
		mLogingMapByClientNetIdLock.unlock();
		return player;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::addToLogingMapByAccName( Char16* accName, SPlayer* player )
	{
		mLogingMapByAccNameLock.lock();
		mLogingMapByAccName[accName] = player;
		mLogingMapByAccNameLock.unlock();
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::getFromLogingMapByAccName( Char16* accName )
	{
		SPlayer* player = NULL;
		mLogingMapByAccNameLock.lock();
		std::map< Str16, SPlayer* >::iterator it = mLogingMapByAccName.find(accName);
		if (it != mLogingMapByAccName.end())
		{
			player = it->second;
			DYNAMIC_ASSERT(player);
		}
		mLogingMapByAccNameLock.unlock();
		return player;
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::removeFromLogingMapByAccName( Char16* accName )
	{
		SPlayer* player = NULL;
		mLogingMapByAccNameLock.lock();
		std::map< Str16, SPlayer* >::iterator it = mLogingMapByAccName.find(accName);
		if (it != mLogingMapByAccName.end())
		{
			player = it->second;
			DYNAMIC_ASSERT(player);
			mLogingMapByAccName.erase(it);
		}
		mLogingMapByAccNameLock.unlock();
		return player;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::addToLogingQueuingQueue( SPlayer* player )
	{
		mLogingQueuingQueueLock.lock();
		player->addRefCount();
		mLogingQueuingQueue.push(player);
		mLogingQueuingQueueLock.unlock();
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::getFromLogingQueuingQueue()
	{
		SPlayer* player = NULL;
		mLogingQueuingQueueLock.lock();
		if (!mLogingQueuingQueue.empty())
		{
			player = mLogingQueuingQueue.front();
			mLogingQueuingQueue.pop();
			DYNAMIC_ASSERT(player);
			//player->subRefCount();
			
		}
		mLogingQueuingQueueLock.unlock();
		return player;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::addToLoginedMapByClientNetId( I32 clientNetID, SPlayer* player )
	{
		mLoginedMapByClientNetIdLock.lock();
		mLoginedMapByClientNetId[clientNetID] = player;
		mLoginedMapByClientNetIdLock.unlock();
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::getFromLoginedMapByClientNetId( I32 clientNetID )
	{
		SPlayer* player = NULL;
		mLoginedMapByClientNetIdLock.lock();
		std::map< I32, SPlayer* >::iterator it = mLoginedMapByClientNetId.find(clientNetID);
		if (it != mLoginedMapByClientNetId.end())
		{
			player = it->second;
			DYNAMIC_ASSERT(player);
		}
		mLoginedMapByClientNetIdLock.unlock();
		return player;
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::removeFromLoginedMapByClientNetId( I32 clientNetID )
	{
		SPlayer* player = NULL;
		mLoginedMapByClientNetIdLock.lock();
		std::map< I32, SPlayer* >::iterator it = mLoginedMapByClientNetId.find(clientNetID);
		if (it != mLoginedMapByClientNetId.end())
		{
			player = it->second;
			DYNAMIC_ASSERT(player);
			mLoginedMapByClientNetId.erase(it);
		}
		mLoginedMapByClientNetIdLock.unlock();
		return player;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::addToLoginedMapByAccName( Char16* accName, SPlayer* player )
	{
		mLoginedMapByAccNameLock.lock();
		mLoginedMapByAccName[accName] = player;
		mLoginedMapByAccNameLock.unlock();
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::getFromLoginedMapByAccName( Char16* accName )
	{
		SPlayer* player = NULL;
		mLoginedMapByAccNameLock.lock();
		std::map< Str16, SPlayer* >::iterator it = mLoginedMapByAccName.find(accName);
		if (it != mLoginedMapByAccName.end())
		{
			player = it->second;
			DYNAMIC_ASSERT(player);
		}
		mLoginedMapByAccNameLock.unlock();
		return player;
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::removeFromLoginedMapByAccName( Char16* accName )
	{
		SPlayer* player = NULL;
		mLoginedMapByAccNameLock.lock();
		std::map< Str16, SPlayer* >::iterator it = mLoginedMapByAccName.find(accName);
		if (it != mLoginedMapByAccName.end())
		{
			player = it->second;
			DYNAMIC_ASSERT(player);
			mLoginedMapByAccName.erase(it);
		}
		mLoginedMapByAccNameLock.unlock();
		return player;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::addToLoginedQueue( SPlayer* player )
	{
		mLoginedQueueLock.lock();
		player->addRefCount();
		mLoginedQueue.push(player);
		mLoginedQueueLock.unlock();
	}
	//-----------------------------------------------------------------------------
	SPlayer* LoginManager::getFromLoginedQueue()
	{
		SPlayer* player = NULL;
		mLoginedQueueLock.lock();
		if (!mLoginedQueue.empty())
		{
			player = mLoginedQueue.front();
			mLoginedQueue.pop();
			DYNAMIC_ASSERT(player);
			//player->subRefCount();
		}
		mLoginedQueueLock.unlock();
		return player;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::addToErrorLogingQueue( ErrorLoginPlayer* errorPlayer )
	{
		mErrorLogingQueueLock.lock();
		mErrorLogingQueue.push(errorPlayer);
		mErrorLogingQueueLock.unlock();
	}
	//-----------------------------------------------------------------------------
	ErrorLoginPlayer* LoginManager::getFromErrorLogingQueue()
	{
		ErrorLoginPlayer* errPlayer = NULL;
		mErrorLogingQueueLock.lock();
		if (!mErrorLogingQueue.empty())
		{
			errPlayer = mErrorLogingQueue.front();
			mErrorLogingQueue.pop();
		}
		mErrorLogingQueueLock.unlock();
		return errPlayer;
	}
	//-----------------------------------------------------------------------------
	U32 LoginManager::getAllLoginCount()
	{
		return mLogingMapByAccName.size() + mLoginedMapByAccName.size();	
	}

	/******************************************************************************/
	//ErrorLoginPlayer
	/******************************************************************************/
	ErrorLoginPlayer::ErrorLoginPlayer(Char16* accountName)
	{
		WStrnCpyS(mName,accountName,MAX_ACCOUNT_LONGIN_NAME_LEN);
		mErrorCount = 0;
		mCreateTime = MGTimeOp::getCurrTick();
		mDirty = false;
	}
	//-----------------------------------------------------------------------------
	ErrorLoginPlayer::~ErrorLoginPlayer()
	{

	}
	//-----------------------------------------------------------------------------
	MG::Int ErrorLoginPlayer::getErrorCount()
	{
		return mErrorCount;
	}
	//-----------------------------------------------------------------------------
	void ErrorLoginPlayer::addErrorCount()
	{
		mErrorCount++;
	}
	//-----------------------------------------------------------------------------
	void ErrorLoginPlayer::setDirty( Bool dirty )
	{
		mDirty = dirty;
	}
	//-----------------------------------------------------------------------------
	Bool ErrorLoginPlayer::getDirty()
	{
		return mDirty;
	}
	//-----------------------------------------------------------------------------
	Char16* ErrorLoginPlayer::getName()
	{
		return mName;
	}
	//-----------------------------------------------------------------------------
	U32 ErrorLoginPlayer::getCreateTime()
	{
		return mCreateTime;
	}	
}
