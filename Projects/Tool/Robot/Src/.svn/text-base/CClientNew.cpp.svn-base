/******************************************************************************/
#include "stdafx.h"
#include "CClientNew.h"
#include "ClientNetApplyManager.h"
#include "LoginNetPacketProcesser.h"
#include "PlayCharacterNetPacketProcesser.h"
//#include "SkillNetPacketProcesser.h"
#include "CClan.h"
#include "TestNetPacketProcesser.h"
#include "RegionNetPacketProcesser.h"
#include "CTroopSoldier.h"
#include "TroopNetPacketProcesser.h"
#include "SkillNetPacketProcesser.h"
#include "CharacterResourceConfig.h"
#include "ChannelInfo.h"
#include "ChatNetPacketProcesser.h"
#include "ThreadTaskManager.h"

#include "CloseState.h"
#include "LoginState.h"
#include "ConnectLoginServerState.h"
#include "LoginLoginServerState.h"
#include "ConnectFrontServerState.h"
#include "LoginFrontServerState.h"
#include "CreateClanState.h"
#include "ClanCtrlState.h"
#include "CreateCharacterState.h"
#include "InTiroState.h"
#include "CreateCampaginState.h"
#include "InCampaginState.h"
#include "AccountCheckState.h"
#include "CCampaignManagerNew.h"

/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------------
	CClient::CClient()
		:mFrontServerId(-1)
		,mLoginServerId(-1)
		,mUiIndex(-1)
		,mSelectClanIndex(0)
		,mNetTestSendNum(0)
		,mThreadIndex(-1)
		,mIsOperateFinish(true)
	{
		mCampagin					= NULL;
		mCampaignManager			= NULL;
		mUiOperateManager			= MG_NEW UiOperateManager(this);

		mCloseState					= MG_NEW CloseState(this);
		mLoginState					= MG_NEW LoginState(this);

		mConnectLoginServerState	= MG_NEW ConnectLoginServerState(this);
		mLoginLoginServerState		= MG_NEW LoginLoginServerState(this);
		mConnectFrontServerState	= MG_NEW ConnectFrontServerState(this);
		mLoginFrontServerState		= MG_NEW LoginFrontServerState(this);

		mCreateClanState			= MG_NEW CreateClanState(this);
		mClanCtrlState				= MG_NEW ClanCtrlState(this);
		mCreateCharacterState		= MG_NEW CreateCharacterState(this);

		mInTiroState				= MG_NEW InTiroState(this);	
		mCreateCampaginState		= MG_NEW CreateCampaginState(this);
		mInCampaginState			= MG_NEW InCampaginState(this);

		mCurrState					= mCloseState;
	}

	CClient::CClient( I32 index, Char* service,Char16* accountName,Char16* password,I32 nClan,Int threadIndex )
		:mFrontServerId(-1)
		,mLoginServerId(-1)
		,mUiIndex(index)
		,mSelectClanIndex(nClan)
		,mNetTestSendNum(0)
		,mThreadIndex(threadIndex)
		,mTaskNumber(0)
		,mIsOperateFinish(true)
	{
		setPlayerName(accountName);
		setPlayerPsw(password);
		setIp(service);

		mCampagin					= NULL;
		mCampaignManager			= NULL;
		mPackManager				= MG_NEW NetPacketPackManager(this);
		mUiOperateManager			= MG_NEW UiOperateManager(this);
		
		mCloseState					= MG_NEW CloseState(this);
		mLoginState					= MG_NEW LoginState(this);

		mConnectLoginServerState	= MG_NEW ConnectLoginServerState(this);
		mLoginLoginServerState		= MG_NEW LoginLoginServerState(this);
		mConnectFrontServerState	= MG_NEW ConnectFrontServerState(this);
		mLoginFrontServerState		= MG_NEW LoginFrontServerState(this);
		mAccountCheckState			= MG_NEW AccountCheckState(this);
		mCreateClanState			= MG_NEW CreateClanState(this);
		mClanCtrlState				= MG_NEW ClanCtrlState(this);
		mCreateCharacterState		= MG_NEW CreateCharacterState(this);

		mInTiroState				= MG_NEW InTiroState(this);	
		mCreateCampaginState		= MG_NEW CreateCampaginState(this);
		mInCampaginState			= MG_NEW InCampaginState(this);

		mCurrState					= mCloseState;

	}

	//--------------------------------------------------------------------------------
	CClient::~CClient()
	{
		mFrontServerId = -1;
		mLoginServerId = -1;

		MG_SAFE_DELETE(mCampagin);
		//MG_SAFE_DELETE(mCampaignManager);
		mCampaignManager = NULL;
		MG_SAFE_DELETE(mPackManager);
		MG_SAFE_DELETE(mUiOperateManager);
		mCurrState = NULL;
		MG_SAFE_DELETE(mCloseState);
		MG_SAFE_DELETE(mLoginState);
		MG_SAFE_DELETE(mConnectLoginServerState);
		MG_SAFE_DELETE(mLoginLoginServerState);
		MG_SAFE_DELETE(mConnectFrontServerState);
		MG_SAFE_DELETE(mLoginFrontServerState);
		MG_SAFE_DELETE(mCreateClanState	);
		MG_SAFE_DELETE(mClanCtrlState);
		MG_SAFE_DELETE(mCreateCharacterState);
		MG_SAFE_DELETE(mInTiroState);
		MG_SAFE_DELETE(mCreateCampaginState);
		MG_SAFE_DELETE(mInCampaginState	);
		MG_SAFE_DELETE(mAccountCheckState);


	}
	//--------------------------------------------------------------------------------
	I32 CClient::stateConnectLoginServer( NetAddress& addr )
	{
		if (mLoginServerId > -1)
		{
			stateDisconnectLoginServer();
		}
        return ClientNetApplyManager::getInstance().connectLoginServer(addr);

	}
	//--------------------------------------------------------------------------------
	I32 CClient::stateConnectFrontServer( NetAddress& addr )
	{
		if (mFrontServerId > -1)
		{
			stateDisconnectLoginServer();
		}
        return ClientNetApplyManager::getInstance().connectFrontServer(addr);
	}
	//--------------------------------------------------------------------------------
	void CClient::stateDisconnectLoginServer()
	{
		if (mLoginServerId < 0)
		{
			return ;
		}
		ClientNetApplyManager::getInstance().disconnectLoginServer(mLoginServerId);
	}
	//--------------------------------------------------------------------------------
	void CClient::stateDisconnectFrontServer()
	{
		if ( mFrontServerId < 0)
		{
			return;
		}
		ClientNetApplyManager::getInstance().disconnectFrontServer(mFrontServerId);
	}
	//--------------------------------------------------------------------------------
	void CClient::update(Flt delta)
	{
		if(mPackManager)
		{
			mPackManager->update(delta);
		}
		if (UIOperateMode_Once == mUiOperateManager->getOperateMode())
		{
			if (mUiOperateManager)
			{
				BaseUiOperate* uiOperate = mUiOperateManager->getCurrOperate();
				if (uiOperate)
				{
					uiOperate->exe(this);
				}
			}	
		}
		else
		{
			if (mIsOperateFinish == true)
			{
				if (mUiOperateManager)
				{
					BaseUiOperate* uiOperate = mUiOperateManager->getCurrOperate();
					if (uiOperate)
					{
						uiOperate->exe(this);
					}

				}
			}
			
		}
		

		/*if(mManager)
		{
			mManager->update();
		}
		else
		{
			mMessage->AddErrorMsg("操作管理器为空");
		}*/
	}
	//--------------------------------------------------------------------------------
	void CClient::setFrontServerAddr( NetAddress& addr )
	{
		mFrontServerAddr = addr;
	}
	//--------------------------------------------------------------------------------
	NetAddress& CClient::getFrontServerAddr()
	{
		return mFrontServerAddr;
	}
	//--------------------------------------------------------------------------------
	I32 CClient::getFrontServerNetId()
	{
		return mFrontServerId;
	}
	//--------------------------------------------------------------------------------
	void CClient::setFrontServerNetId(I32 netId)
	{
		mFrontServerId = netId;
	}
	//--------------------------------------------------------------------------------
	I32 CClient::getLoginServerNetId()
	{
		return mLoginServerId;
	}
	//--------------------------------------------------------------------------------
	void CClient::setLoginServerNetId(I32 netId)
	{
		mLoginServerId = netId;
	}
	//--------------------------------------------------------------------------------
	void CClient::setPlayerName( Char16* name )
	{
		MG::MGStrOp::sprintf(mAccountName,sizeof(mAccountName)/sizeof(mAccountName[0]),name);
	}
	//--------------------------------------------------------------------------------
	Char16* CClient::getPlayerName()
	{
		return mAccountName;
	}
	//--------------------------------------------------------------------------------
	void CClient::getPlayerNameA(Char8* accountName)
	{
		Str8 tempName ;
		MGStrOp::toString(mAccountName,tempName);
		StrCpy(accountName,tempName.c_str());
	}
	//--------------------------------------------------------------------------------
	void CClient::setPlayerPsw( Char16* psw )
	{
		MG::MGStrOp::sprintf(mPassword,sizeof(mPassword)/sizeof(mPassword[0]),psw);
	}
	//--------------------------------------------------------------------------------
	Char16* CClient::getPlayerPsw()
	{
		return mPassword;
	}
	//--------------------------------------------------------------------------------
	void CClient::setIp( Char* ip )
	{
		MG::MGStrOp::sprintf(mServerIp,sizeof(mServerIp),ip);
	}
	//--------------------------------------------------------------------------------
	Char* CClient::getIp()
	{
		return mServerIp;
	}
	//--------------------------------------------------------------------------------
	CPlayer* CClient::getPlayerObj()
	{
		return &mPlayerObj;
	}
	//--------------------------------------------------------------------------------
	void CClient::stateNetCreateClan()
	{
		CClan tempClan;
		Str16 tempname;
		Str16 temphomehandname;
		U32 partName = MGRandom::getInstance().rand_ab_One(0,32676);
		MGStrOp::toString(partName,tempname);
		tempname += mAccountName;

		partName = MGRandom::getInstance().rand_ab_One(0,32676);
		MGStrOp::toString(partName,temphomehandname);
		temphomehandname += mAccountName;

		tempClan.setClanHomeLandName( temphomehandname );
		tempClan.setName( tempname );

		//assert(pClan);
		
		//// 获得一个发送【服务端】缓存
		//GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		//// 转换成标准包格式
		//GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		//if ( packet )
		//{
		//	// 设置标签
		//	packet->channel = GNPC_LOGIN;
		//	packet->type    = PT_LOGIN_C2F_CREATE_CLAN;

		//	// 转换逻辑包
		//	PT_LOGIN_C2F_CREATE_CLAN_DATA* sendData = (PT_LOGIN_C2F_CREATE_CLAN_DATA*)(packet->data);
		//	if ( sendData )
		//	{
		//		// 填充逻辑包
		//		MGStrOp::sprintf( sendData->clanDatabase.clanhomelandname,MAX_CHARACTER_NAME_LEN, (Char16*)tempClan.getClanHomeLandName().c_str());
		//		MGStrOp::sprintf( sendData->clanDatabase.clanname, MAX_CHARACTER_NAME_LEN, (Char16*)tempClan.getName().c_str() );
		//		sendData->clanDatabase.clandatabaseid = 0;
		//		sendData->clanDatabase.status = 0;
		//		sendData->clanDatabase.ancestry = 0;
		//		sendData->clanDatabase.armyemblem = 0;
		//		sendData->clanDatabase.armyemblemcolor = 0;
		//		sendData->clanDatabase.bg = 0;
		//		sendData->clanDatabase.bgcolor = 0;
		//		// 发送数据
		//		ClientNetApplyManager::getInstance().sendFrontServerPacket(mFrontServerId, dataPtr , 
		//			GameNetPacketData_INFO::headSize + PT_LOGIN_C2F_CREATE_CLAN_DATA_INFO::dataSize );
		//	}
		//}

		LoginNetPacketProcesser::getInstance().sendClanInfoToFrontServer(mFrontServerId,&tempClan);
	}
	//--------------------------------------------------------------------------------
	void CClient::stateNetCreateCharacter()
	{
		U32 partName = MGRandom::getInstance().rand_ab_One(1,30000);
		Str16 name;
		MGStrOp::toString(partName,name);
		name += mAccountName;

		//随机角色templateID
		I32   templateSize = CharacterResourceConfig::getInstance().getCharacterResourceInfoList().size();
		I32   templateID = MGRandom::getInstance().rand_ab_One(1,templateSize);
		const CharacterResInfo* resInfo = CharacterResourceConfig::getInstance().getCharacterResourceInfo(templateID);

		PlayerCharacterData charData;
		charData.charSurName = name;
		charData.mName = mAccountName;
		charData.charArtIcon = 30014;
		charData.mCharacterTemplateID = resInfo->templateid;

		charData.mRegionID = resInfo->maplistid;
        charData.mRegionType = (REGION_OBJ_TYPE)resInfo->maplisttype;
		LoginNetPacketProcesser::getInstance().sendCreateGenrealToFrontServer(mFrontServerId,&charData);
	
	}
	//--------------------------------------------------------------------------------
	void CClient::stateNetAccountloginLoginServer()
	{
		
		LoginNetPacketProcesser::getInstance().sendLoginPacketToLoginServer(mLoginServerId,mAccountName,mPassword);
	}
	//--------------------------------------------------------------------------------
	void CClient::stateNetAccountloginFrontServer()
	{
		
		Str8 tempName = "";
		Str8 tempPsw = "";
		MGStrOp::toString(mAccountName,tempName);
		MGStrOp::toString(mPassword,tempPsw);
		MG_LOG(out_debug,"用户名%s,密码%s\n",tempName.c_str(),tempPsw.c_str());
		LoginNetPacketProcesser::getInstance().sendLoginPacketToFrontServer(mFrontServerId,mAccountName,mPassword);
	}
	//--------------------------------------------------------------------------------
	void CClient::stateNetClose()
	{	
		stateDisconnectLoginServer();
		stateDisconnectFrontServer();
	}
	//--------------------------------------------------------------------------------
	void CClient::stateNetJoinGame()
	{
		LoginNetPacketProcesser::getInstance().sendJoingameToFrontServer(mFrontServerId);
	}
	//--------------------------------------------------------------------------------
	void CClient::onLoginServerClose()
	{
		
		if (mFrontServerId == -1)
		{
			mPlayerObj.deleteAllClan();
		}
		//mManager->onCloseByLoginServer();
		ThreadTaskManager::getInstance().removeLoginClient(mLoginServerId);
		//ClientManager::getInstance().removeClientFormLoginMap(mLoginServerId);
		mLoginServerId = -1;
	
	}
	//--------------------------------------------------------------------------------
	void CClient::onFrontServerClose()
	{
		
		if (mLoginServerId == -1)
		{
			mPlayerObj.deleteAllClan();
		}
	
		//mManager->onCloseByFrontServer();
		//ClientManager::getInstance().removeClientFormFrontMap(mFrontServerId);
		ThreadTaskManager::getInstance().removeFrontClient(mFrontServerId);
		mFrontServerId = -1;
	}
	//--------------------------------------------------------------------------------
	void CClient::stateRandMove()
	{
		static Bool isMove = true;
		CClan* clan = getPlayerObj()->getActiveClan();
		if (!clan)
		{
			return;
		}
		CPlayerCharacter* character = clan->getMainGenreal();
		if (!character || !character->getJoinRegion())
		{
			return;
		}
		if (isMove)
		{
			
			Vec3 pos = character->getCharacterData()->mPos;
			Int temp = MGRandom::getInstance().rand_ab_One(0,1);
			if (temp)
			{
				pos.x += MGRandom::getInstance().rand_ab_One(1,2);
			}
			else
			{
				pos.x -= MGRandom::getInstance().rand_ab_One(1,2);
			}
			temp = MGRandom::getInstance().rand_ab_One(0,1);
			if (temp)
			{
				pos.z += MGRandom::getInstance().rand_ab_One(1,2);
			}
			else
			{
				pos.z -= MGRandom::getInstance().rand_ab_One(1,2);
			}


			PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterMoveToPackBuffer(this,character->getID(),character->getCharacterData()->mPos,pos);

			Vec3 tempPos(0.0f,0.0f,0.0f);
			temp = MGRandom::getInstance().rand_ab_One(0,1);
			if (temp)
			{
				tempPos.x += MGRandom::getInstance().rand_ab_One(1,2);
			}
			else
			{
				tempPos.x -= MGRandom::getInstance().rand_ab_One(1,2);
			}
			temp = MGRandom::getInstance().rand_ab_One(0,1);
			if (temp)
			{
				tempPos.z += MGRandom::getInstance().rand_ab_One(1,2);
			}
			else
			{
				tempPos.z -= MGRandom::getInstance().rand_ab_One(1,2);
			}	
			for (CPlayerCharacter::TroopObjectListIt it = character->getTroopList()->begin(); it != character->getTroopList()->end(); it++)
			{
				CTroopObject* troopObj = it->second;
				Vec3 troopPos = troopObj->getBaseData()->mPos;

				TroopNetPacketProcesser::getInstance().sendTroopEntityMoveToPackBuffer(
							this,
							mPlayerObj.getActiveClan()->getMainGenreal()->getRegionType(),
							mPlayerObj.getActiveClan()->getMainGenreal()->getRegionID(),
							mPlayerObj.getInstanceUid(), 
							troopObj->getID(),
							troopPos,troopPos + tempPos);
				//for (CTroopObject::TroopSoldierIt itSoldier = troopObj->getTroopSoldiers()->begin(); itSoldier != troopObj->getTroopSoldiers()->end(); itSoldier++)
				//{
				//	//TroopNetPacketProcesser::getInstance().sendTroopSoldierStopMoveToPackBuffer(CPlayer::getInstance().getActiveClan()->getFocusRegionType(), CPlayer::getInstance().getActiveClan()->getFocusRegionID(), CPlayer::getInstance().getInstanceUid(), troopSoldierEntity->getTroopEntity()->getID(), troopSoldierEntity->getID());
				//	Vec3 pos = itSoldier->second->getPos();
				//	pos.x = pos.x + tempPos.x;
				//	pos.z = pos.z + tempPos.z;
				//	MG_LOG(out_error,"getRegionID = %d ---- getInstanceUid =  %d \n",mPlayerObj.getActiveClan()->getMainGenreal()->getRegionID(),mPlayerObj.getInstanceUid());
				//	TroopNetPacketProcesser::getInstance().sendTroopSoldierMoveToPackBuffer(this,
				//		mPlayerObj.getActiveClan()->getMainGenreal()->getRegionType(),
				//		mPlayerObj.getActiveClan()->getMainGenreal()->getRegionID(),
				//		mPlayerObj.getInstanceUid(),troopObj->getID(),itSoldier->second->getID(),
				//		itSoldier->second->getPos(),pos);
				//}
			}
		}
		else
		{
			for (CPlayerCharacter::TroopObjectListIt it = character->getTroopList()->begin(); it != character->getTroopList()->end(); it++)
			{
				CTroopObject* troopObj = it->second;
				if (!troopObj)
				{
					continue;
				}
				TroopNetPacketProcesser::getInstance().sendTroopEntityStopMoveToPackBuffer(this,
					mPlayerObj.getActiveClan()->getMainGenreal()->getRegionType(),
					mPlayerObj.getActiveClan()->getMainGenreal()->getRegionID(),
					mPlayerObj.getInstanceUid(), 
					troopObj->getID());
			}
			
		}
		//isMove = !isMove;

		

		
	}
	//--------------------------------------------------------------------------------
	void CClient::stateSendClantSkillRequest()
	{
		SkillNetPacketProcesser::getInstance().sendPlayCharacterClantSkillRequestPacketToPackBuffer(this);
	}
	//--------------------------------------------------------------------------------
	void CClient::stateSendEmitterSkillRequest()
	{
		SkillNetPacketProcesser::getInstance().sendPlayCharacterInjectSkillRequestPacketToPackBuffer(this);
	}
	//--------------------------------------------------------------------------------
	void CClient::stateSendCollisionAffectRequest()
	{
		SkillNetPacketProcesser::getInstance().sendSkillPlayerCharacterCollisionAffectPlayerCharacterPacket(this);
	}
	//--------------------------------------------------------------------------------
	void CClient::stateTestNet(U32 size)
	{
		//PT_TEST_BASE_DATA data;
		CPlayer* player = getPlayerObj();
		if (!player)
		{
			//DYNAMIC_ASSERT(false);
			return;
		}
		CClan* clan = player->getActiveClan();
		if (!clan)
		{
			//DYNAMIC_ASSERT(false);
			return;
		}
		if (!clan->getMainGenreal())
		{
			return;
		}
		TestNetPacketProcesser::getInstance().sendCFMBaseTestToFrontServer(mFrontServerId,player->getAccountID(),clan->getMainGenrealID(),mNetTestSendNum,size);
		//ClientNetApplyManager::getInstance().sendFrontServerPacket(mFrontServerId,GNPC_TEST,PT_TEST_CFM_BASE,(Char*)&data,sizeof(data));
	}
	//--------------------------------------------------------------------------------
	void CClient::stateTestSendDataToLoginServer(U32 size)
	{
		TestNetPacketProcesser::getInstance().sendCLBaseTestToLoginServer(mLoginServerId,size);
	}
	//--------------------------------------------------------------------------------
	void CClient::stateTestSendDataToFrontServer(U32 size)
	{
		CPlayer* player = getPlayerObj();
		if (!player)
		{
			//DYNAMIC_ASSERT(false);
			return;
		}
		CClan* clan = player->getActiveClan();
		if (!clan)
		{
			//DYNAMIC_ASSERT(false);
			return;
		}
		if (!clan->getMainGenreal())
		{
			return;
		}
		TestNetPacketProcesser::getInstance().sendCFBaseTestToFrontServer(mFrontServerId,player->getAccountID(),clan->getMainGenrealID(),mNetTestSendNum,size);
		//TestNetPacketProcesser::getInstance().sendCFBaseTestToFrontServer(mFrontServerId,getPlayerObj->getAccountID(),size);
	}
	//--------------------------------------------------------------------------------
	MG::U8 CClient::getSelectClanIndex()
	{
		return mSelectClanIndex;
	}
	//--------------------------------------------------------------------------------
	CClan* CClient::getSelectClan()
	{
		//TODO: 此处将要做修改
		//mSelectClanIndex
		return getPlayerObj()->getActiveClan();
	}
	//--------------------------------------------------------------------------------
	MG::I32 CClient::getIndex()
	{
		return mUiIndex;
	}
	//--------------------------------------------------------------------------------
	void CClient::setIndex(I32 index)
	{
		mUiIndex = index;
	}
	//--------------------------------------------------------------------------------
	MG::Bool CClient::isDisconnect()
	{
		if (mLoginServerId < 0 && mFrontServerId < 0)
		{
			return true;
		}
		return false;
	}
	//--------------------------------------------------------------------------------
	NetPacketPackManager* CClient::getPackManager()
	{
		return mPackManager;
	}
	//--------------------------------------------------------------------------------
	void CClient::stateCreateTroop()
	{
		RegionNetPacketProcesser::getInstance().sendAddTroopTest(mFrontServerId,mPlayerObj.getAccountID());
	}
	//--------------------------------------------------------------------------------
	CCampaign* CClient::getCampaign()
	{
		return mCampagin;
	}
	//--------------------------------------------------------------------------------
	void CClient::setCampaign( CCampaign* campaign )
	{
		mCampagin = campaign;
	}
	//--------------------------------------------------------------------------------
	CCampaignManager* CClient::getCampaignManger()
	{
		return mCampaignManager;
	}
	//--------------------------------------------------------------------------------
	void CClient::setCampaignManger( CCampaignManager* campaignMgr )
	{
		mCampaignManager = campaignMgr;
	}
	//--------------------------------------------------------------------------------
	void CClient::setThreadIndex(Int index)
	{
		DYNAMIC_ASSERT(mThreadIndex == index);
		mThreadIndex = index;
	}
	//--------------------------------------------------------------------------------
	Int CClient::getThreadIndex()
	{
		return mThreadIndex;
	}
	//--------------------------------------------------------------------------------
	void CClient::stateNetChat(U32 chatId ,I32 size)
	{
		//根据广播范围进行发包
		ChannelInfo* info = ChannelInfos::getInstance().getChannelInfo(chatId);
        DYNAMIC_ASSERT(info);
		switch(info->broadcast)
		{
		case chat_full_server:
			{   
				//mMessage->AddMsg("【全服聊天】：进入-----操作中-----");
				ChatNetPacketProcesser::getInstance().sendFullServerChatToFrontServer(chatId,size,mFrontServerId);
			}
			break;
		case chat_one_world:
			{

			}
			break;
		case chat_one_zhou:
			{

			}
			break;
		case chat_one_jun:
			{
                 
			}
			break;
		case chat_one_xian:
			{

			}
			break;
		case chat_one_city:
			{

			}
			break;
		case chat_one_force:
			{

			}
			break;
		case chat_one_alliance:
			{

			}
			break;
		case chat_one_group:
			{

			}
			break;
		case chat_two_person:
			{
				//
				
			}
			break;
		case chat_one_region:
			{   
				//mMessage->AddMsg("【同地图聊天】：进入-----操作中-----");
                CClan* clan = mPlayerObj.getActiveClan();
				DYNAMIC_ASSERT(clan);
                CPlayerCharacter* playerChar = clan->getMainGenreal();
				DYNAMIC_ASSERT(playerChar);
				ChatNetPacketProcesser::getInstance().sendOneRegionChatToFrontServer(chatId,playerChar->getRegionID(),playerChar->getRegionType(),size,mFrontServerId);
			}
			break;
		case chat_one_view:
			{

			}
			break;
		default:
			{
				DYNAMIC_ASSERT(false);
			}
			break;
		}

	}
	//--------------------------------------------------------------------------------
	void CClient::setTaskNumber()
	{
		Str8 tempName;
		MGStrOp::toString(getPlayerName(),tempName);
		mTaskNumber++;
		//MG_LOG(out_game_logic,"用户名:%s 设置编号:%d\n",tempName.c_str(),mTaskNumber);
	}
	//--------------------------------------------------------------------------------
	MG::Int CClient::getTaskNumber()
	{
		return mTaskNumber;
	}
	//--------------------------------------------------------------------------------
	void CClient::setState( BaseState* state )
	{		
		if (state == mCloseState)
		{
			mLoginState->reset();
			mAccountCheckState->reset();
			/*mLoginState->setCurrChildState(mLoginState->getAccountCheckState());
			mLoginState->getAccountCheckState()->setCurrChildState(mLoginState->getAccountCheckState()->getConnectLoginServerState());
			mAccountCheckState->setCurrChildState(mAccountCheckState->getConnectLoginServerState());*/
		}
		mCurrState = state;
		if (mCurrOp == OpType_close && state == mCloseState)
		{
			setOperateFinish(true);
		}
		if (mCurrOp == OpType_autoJoinGame && state == mInTiroState)
		{
			setOperateFinish(true);
		}
		
	}
	//--------------------------------------------------------------------------------
	void CClient::onNetEvent( INetEvent* netEvent )
	{
		//FUNDETECTION(__MG_FUNC__)
		if (netEvent->getType() == NET_RECV)
		{
			NetEventRecv* recvEvent = (NetEventRecv*)netEvent;
			if (recvEvent->getChannel() == GNPC_MONSTER)
			{
				return;
			}
		}
		DYNAMIC_ASSERT(mCurrState);
		if (mCurrState)
		{
			mCurrState->onNetEvent(netEvent);
		}
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getCloseState()
	{
		return mCloseState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getLoginState()
	{
		return mLoginState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getAccountCheckState()
	{
		return mAccountCheckState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getConnectLoginServerState()
	{
		return mConnectLoginServerState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getLoginLoginServerState()
	{
		return mLoginLoginServerState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getConnectFrontServerState()
	{
		return mConnectFrontServerState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getLoginFrontServerState()
	{
		return mLoginFrontServerState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getCreateClanState()
	{
		return mCreateClanState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getClanCtrlState()
	{
		return mClanCtrlState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getCreateCharacterState()
	{
		return mCreateCharacterState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getInTiroState()
	{
		return mInTiroState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getCreateCampaginState()
	{
		return mCreateCampaginState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getInCampaginState()
	{
		return mInCampaginState;
	}
	//--------------------------------------------------------------------------------
	BaseState* CClient::getCurrState()
	{
		return mCurrState;
	}
	//--------------------------------------------------------------------------------
	void CClient::connectLoginServer()
	{
		mCurrState->connectLoginServer();
	}
	//--------------------------------------------------------------------------------
	void CClient::connectFrontServer()
	{
		mCurrState->connectFrontServer();
	}
	//--------------------------------------------------------------------------------
	void CClient::accountLoginLoginServer()
	{
		mCurrState->accountLoginLoginServer();
	}
	//--------------------------------------------------------------------------------
	void CClient::accountLoginFrontServer()
	{
		mCurrState->accountLoginFrontServer();
	}
	//--------------------------------------------------------------------------------
	void CClient::accountLogin()
	{
		mCurrState->accountLogin();
	}
	//--------------------------------------------------------------------------------
	void CClient::joinGame()
	{
		mCurrState->joinGame();	
	}
	//--------------------------------------------------------------------------------
	void CClient::autoJoinGame()
	{
		mCurrOp = OpType_autoJoinGame;
		setOperateFinish(false);
		mCurrState->autoJoinGame();
	}
	//--------------------------------------------------------------------------------
	void CClient::createClan()
	{
		mCurrState->createClan();
	}
	//--------------------------------------------------------------------------------
	void CClient::createCharacter()
	{
		mCurrState->createCharacter();
	}
	//--------------------------------------------------------------------------------
	void CClient::closeNet()
	{
		mCurrOp = OpType_close;
		mCurrState->closeNet();
	}
	//--------------------------------------------------------------------------------
	void CClient::randMove()
	{
		mCurrState->randMove();
	}
	//--------------------------------------------------------------------------------
	void CClient::createTroop()
	{
		mCurrState->createTroop();
	}
	//--------------------------------------------------------------------------------
	void CClient::sendDataToLoginServer(U32 size)
	{
		mCurrState->sendDataToLoginServer( size);
	}
	//--------------------------------------------------------------------------------
	void CClient::sendDataToFrontServer(U32 size)
	{
		mCurrState->sendDataToFrontServer(size);
	}
	//--------------------------------------------------------------------------------
	void CClient::testSkill()
	{
		mCurrState->testSkill();
	}
	//--------------------------------------------------------------------------------
	void CClient::createCampagin()
	{
		mCurrState->createCampagin();
	}
	//--------------------------------------------------------------------------------
	void CClient::jumpMap()
	{
		mCurrState->jumpMap();
	}
	//--------------------------------------------------------------------------------
	UiOperateManager* CClient::getUiOperateManger()
	{
		return mUiOperateManager;
	}
	//--------------------------------------------------------------------------------
	Bool CClient::isOperateFinish()
	{
		return mIsOperateFinish;
	}

	void CClient::setOperateFinish( Bool isFinish /*= true*/ )
	{
		mIsOperateFinish = isFinish;
	}

	std::string& CClient::getStateName()
	{
		return mCurrState->getClassName();
	}

	//--------------------------------------------------------------------------------

}