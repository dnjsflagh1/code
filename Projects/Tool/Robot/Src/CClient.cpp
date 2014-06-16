/******************************************************************************/
#include "stdafx.h"
#include "CClient.h"
#include "ClientNetApplyManager.h"
#include "LoginNetPacketProcesser.h"
#include "PlayCharacterNetPacketProcesser.h"
//#include "SkillNetPacketProcesser.h"
#include "CClan.h"
#include "TestNetPacketProcesser.h"
#include "ClientManager.h"
#include "RegionNetPacketProcesser.h"
#include "CTroopSoldier.h"
#include "TroopNetPacketProcesser.h"
#include "SkillNetPacketProcesser.h"
#include "CharacterResourceConfig.h"
#include "ChannelInfo.h"
#include "ChatNetPacketProcesser.h"
#include "ThreadTaskManager.h"
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
	{
		mMessage = MG_NEW CClientMessage(this);
		mManager = MG_NEW OperateManager(this);
		mCampagin = NULL;
	}

	CClient::CClient( I32 index, Char* service,Char16* accountName,Char16* password,I32 nClan,Int threadIndex )
		:mFrontServerId(-1)
		,mLoginServerId(-1)
		,mUiIndex(index)
		,mSelectClanIndex(nClan)
		,mNetTestSendNum(0)
		,mThreadIndex(threadIndex)
		,mTaskNumber(0)
	{
		setPlayerName(accountName);
		setPlayerPsw(password);
		setIp(service);
		mMessage = MG_NEW CClientMessage(this);
		mManager = MG_NEW OperateManager(this);
		mPackManager = MG_NEW NetPacketPackManager(this);
		mCampagin = NULL;
	}

	//--------------------------------------------------------------------------------
	CClient::~CClient()
	{
		mFrontServerId = -1;
		mLoginServerId = -1;
		MG_SAFE_DELETE(mMessage);
		MG_SAFE_DELETE(mManager);
		MG_SAFE_DELETE(mPackManager);
	}
	//--------------------------------------------------------------------------------
	I32 CClient::connectLoginServer( NetAddress& addr )
	{
		if (mLoginServerId > -1)
		{
			disconnectLoginServer();
		}
        return ClientNetApplyManager::getInstance().connectLoginServer(addr);

	}
	//--------------------------------------------------------------------------------
	I32 CClient::connectFrontServer( NetAddress& addr )
	{
		if (mFrontServerId > -1)
		{
			disconnectLoginServer();
		}
        return ClientNetApplyManager::getInstance().connectFrontServer(addr);
	}
	//--------------------------------------------------------------------------------
	void CClient::disconnectLoginServer()
	{
		if (mLoginServerId < 0)
		{
			return ;
		}
		ClientNetApplyManager::getInstance().disconnectLoginServer(mLoginServerId);
	}
	//--------------------------------------------------------------------------------
	void CClient::disconnectFrontServer()
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
		//FUNDETECTION(__MG_FUNC__)
		if(mPackManager)
		{
			mPackManager->update(delta);
		}
		if(mManager)
		{
			mManager->update();
		}
		else
		{
			mMessage->AddErrorMsg("操作管理器为空");
		}
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

	CPlayer* CClient::getPlayerObj()
	{
		return &mPlayerObj;
	}
	//--------------------------------------------------------------------------------
	CClientMessage* CClient::getClientMessage()
	{
		return mMessage;
	}
	//--------------------------------------------------------------------------------
	void CClient::netCreateClan()
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
		//NetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		//// 转换成标准包格式
		//GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
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
	void CClient::netCreateCharacter()
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
		charData.charZiName = name;
		charData.mName = mAccountName;
		charData.charArtIcon = 30016;
		charData.mCharacterTemplateID = resInfo->templateid;
		charData.mRegionID = resInfo->maplistid;
        charData.mRegionType = (REGION_OBJ_TYPE)resInfo->maplisttype;
		LoginNetPacketProcesser::getInstance().sendCreateGenrealToFrontServer(mFrontServerId,&charData);
	
	}
	//--------------------------------------------------------------------------------
	void CClient::netAccountloginLoginServer()
	{
		
		LoginNetPacketProcesser::getInstance().sendLoginPacketToLoginServer(mLoginServerId,mAccountName,mPassword);
	}
	//--------------------------------------------------------------------------------
	void CClient::netAccountloginFrontServer()
	{
		
		Str8 tempName = "";
		Str8 tempPsw = "";
		MGStrOp::toString(mAccountName,tempName);
		MGStrOp::toString(mPassword,tempPsw);
		MG_LOG(out_debug,"用户名%s,密码%s\n",tempName.c_str(),tempPsw.c_str());
		LoginNetPacketProcesser::getInstance().sendLoginPacketToFrontServer(mFrontServerId,mAccountName,mPassword);
	}
	//--------------------------------------------------------------------------------
	void CClient::netClose()
	{	
		disconnectLoginServer();
		disconnectFrontServer();
	}
	//--------------------------------------------------------------------------------
	void CClient::netJoinGame()
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
	void CClient::randMove()
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
				for (CTroopObject::TroopSoldierIt itSoldier = troopObj->getTroopSoldiers()->begin(); itSoldier != troopObj->getTroopSoldiers()->end(); itSoldier++)
				{
					//TroopNetPacketProcesser::getInstance().sendTroopSoldierStopMoveToPackBuffer(CPlayer::getInstance().getActiveClan()->getFocusRegionType(), CPlayer::getInstance().getActiveClan()->getFocusRegionID(), CPlayer::getInstance().getInstanceUid(), troopSoldierEntity->getTroopEntity()->getID(), troopSoldierEntity->getID());
					Vec3 pos = itSoldier->second->getPos();
					pos.x = pos.x + tempPos.x;
					pos.z = pos.z + tempPos.z;
					MG_LOG(out_error,"getRegionID = %d ---- getInstanceUid =  %d \n",mPlayerObj.getActiveClan()->getMainGenreal()->getRegionID(),mPlayerObj.getInstanceUid());
					TroopNetPacketProcesser::getInstance().sendTroopSoldierMoveToPackBuffer(this,
						mPlayerObj.getActiveClan()->getMainGenreal()->getRegionType(),
						mPlayerObj.getActiveClan()->getMainGenreal()->getRegionID(),
						mPlayerObj.getInstanceUid(),troopObj->getID(),itSoldier->second->getID(),
						itSoldier->second->getPos(),pos);
				}
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
				TroopNetPacketProcesser::getInstance().sendTroopGroupStopMove(mFrontServerId,troopObj->getID());
			}
			
		}
		//isMove = !isMove;

		

		
	}
	//--------------------------------------------------------------------------------
	void CClient::sendClantSkillRequest()
	{
		SkillNetPacketProcesser::getInstance().sendPlayCharacterClantSkillRequestPacketToPackBuffer(this);
	}
	//--------------------------------------------------------------------------------
	void CClient::sendEmitterSkillRequest()
	{
		SkillNetPacketProcesser::getInstance().sendPlayCharacterInjectSkillRequestPacketToPackBuffer(this);
	}
	//--------------------------------------------------------------------------------
	void CClient::sendCollisionAffectRequest()
	{
		SkillNetPacketProcesser::getInstance().sendSkillPlayerCharacterCollisionAffectPlayerCharacterPacket(this);
	}
	//--------------------------------------------------------------------------------
	void CClient::testNet()
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
		TestNetPacketProcesser::getInstance().sendCFMBaseTestToFrontServer(mFrontServerId,player->getAccountID(),clan->getMainGenrealID(),mNetTestSendNum);
		//ClientNetApplyManager::getInstance().sendFrontServerPacket(mFrontServerId,GNPC_TEST,PT_TEST_CFM_BASE,(Char*)&data,sizeof(data));
	}
	//--------------------------------------------------------------------------------
	void CClient::testSendDataToLoginServer(U32 size)
	{
		TestNetPacketProcesser::getInstance().sendCLBaseTestToLoginServer(mLoginServerId,size);
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
	ClientState& CClient::getState()
	{
		return mState;
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
	OperateManager* CClient::getOperateManager()
	{
		return mManager;
	}
	//--------------------------------------------------------------------------------
	NetPacketPackManager* CClient::getPackManager()
	{
		return mPackManager;
	}
	//--------------------------------------------------------------------------------
	void CClient::createTroop()
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
	void CClient::netChat(U32 chatId ,I32 size)
	{
		//根据广播范围进行发包
		ChannelInfo* info = ChannelInfos::getInstance().getChannelInfo(chatId);
        DYNAMIC_ASSERT(info);
		switch(info->broadcast)
		{
		case chat_full_server:
			{   
				mMessage->AddMsg("【全服聊天】：进入-----操作中-----");
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
				mMessage->AddMsg("【同地图聊天】：进入-----操作中-----");
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

	void CClient::setTaskNumber()
	{
		Str8 tempName;
		MGStrOp::toString(getPlayerName(),tempName);
		mTaskNumber++;
		MG_LOG(out_game_logic,"用户名:%s 设置编号:%d\n",tempName.c_str(),mTaskNumber);
	}

	MG::Int CClient::getTaskNumber()
	{
		return mTaskNumber;
	}
	//--------------------------------------------------------------------------------

}