//***********************************************************************************************************

#include "stdafx.h"
#include "FrontServerPreqs.h"
#include "ThreadTask.h"
#include "LoginNetPacket.h"
#include "ClientManager.h"
#include "SWorldManager.h"
#include "LoginNetPacketProcesser.h"
#include "FrontServerMain.h"
#include "LoginManager.h"
#include "PlayerNetPacketProcesser.h"
#include "SWorldManager.h"
#include "ServerManager.h"
#include "LoginNetPacket.h"
#include "ServerManager.h"
#include "FrontServerMain.h"
#include "ClientManager.h"
#include "LoginNetPacketProcesser.h"
#include "LoginManager.h"
#include "PlayerCharacterNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
#include "CommonGameDefine.h"
#include "NetTranspondPacketProcesser.h"
#include "ServerStateNetPacketProcesser.h"
#include "CampaignNetPacketProcesser.h"
#include "TroopNetPacketProcesser.h"
#include "ShopPacketProcesser.h"
#include "SCDNetPacketProcesser.h"
#include "SAttributeNetPacketProcesser.h"
#include "MonsterNetPacketProcesser.h"
#include "LogSystem.h"
#include "TimeNetPacketProcesser.h"
#include "ChatNetPacketProcesser.h"
#include "SWorldManager.h"
#include "RegionNetPacketProcesser.h"
#include "RegionDevideAlgorithm.h"
#include "ThreadTaskManager.h"
#include "ItemPacketProcesser.h"
#include "SPveNetPacketProcessor.h"
#include "ChatInterValCheckManager.h"
#include "CharacterResourceConfig.h"
#include "CharacterList.h"
#include "MapType2RegionObject.h"
#include "LineUpNetPacketProcesser.h"
#include "SBuffPacketProcesser.h"

//***********************************************************************************************************
namespace MG
{
	
	//***********************************************************************************************************
    // PrepareJoinGameTask
    //***********************************************************************************************************

    //----------------------------------------------------------------------
	PrepareJoinGameTask::PrepareJoinGameTask(NetEventRecv* netEvent,U32 key )
		: ModeTask( U32(TTT_PREPAREJOINGAME) ,key)
		
	{
		mNetEvent = netEvent;
	}

	//----------------------------------------------------------------------
	PrepareJoinGameTask::~PrepareJoinGameTask()
	{

	}

	//----------------------------------------------------------------------
	void PrepareJoinGameTask::free()
	{
		ThreadTaskManager::getInstance().freePrepareJoinGameTask(this);
	}

	//----------------------------------------------------------------------
	void PrepareJoinGameTask::process()
	{
		// 需要对用到的数据做 数据同步！！！

		if ( mNetEvent->getChannel() != GNPC_LOGIN  &&
			 mNetEvent->getType() != PT_LOGIN_L2F_CLIENT_CHECKED )
		{
			DYNAMIC_ASSERT(false);
			return;
		}

		PT_LOGIN_L2F_CLIENT_CHECKED_DATA* checkData = (PT_LOGIN_L2F_CLIENT_CHECKED_DATA*)((GameNetPacketData*)mNetEvent->getData())->data;
		
        ClientObject* clientPtr = ClientManager::getInstance().getClientObject( checkData->clientNetID );
        if (clientPtr)
        {
            if (checkData->result == LFCT_LOGIN_SUCCESS)
            {
                if ( (clientPtr)->isMatchAccount(checkData->data.accName,checkData->data.accPsw) )
                {
                    LoginManager::getInstance().onClientLoginSuccessedFromLoginServer( clientPtr, checkData->accID );
                }else
                {
                    // 验证失败 关闭连接
                    MG_LOG(out_error,"验证失败 关闭链接\n");
                    FrontServerMain::getInstance().getServerLauncher()->closeClient( checkData->clientNetID );
                }
            }else
            {
                // 发送客户端连接失败消息
                MG_LOG(out_error,"LoginServer帐号验证失败\n");
                LoginNetPacketProcesser::getInstance().sendClientConnectFrontServerResult( checkData->clientNetID, LCFT_LOGIN_FAIL, checkData->accID);
                
                // TODO:
                // 之后可以讨论考虑关闭连接的可能性
            }
        }
	}
	
    //***********************************************************************************************************
    // CreateClanTask
    //***********************************************************************************************************

    //----------------------------------------------------------------------
	CreateClanTask::CreateClanTask(NetEventRecv* netEvent,I32 netId,U32 key )
		: ModeTask( U32(TTT_CREATECLAN),key)

	{
		mNetEvent = netEvent;
		mClientNetId = netId;
	}

	//----------------------------------------------------------------------
	CreateClanTask::~CreateClanTask()
	{
	}

	//----------------------------------------------------------------------
	void CreateClanTask::free()
	{
		ThreadTaskManager::getInstance().freeCreateClanTask(this);
	}

	//----------------------------------------------------------------------
	void CreateClanTask::process()
	{
		//TODO:
		// 需要对用到的数据做 数据同步！！！
		//TODO:
		// 需要对用到的数据做 数据同步！！！
		if (mNetEvent->getChannel() != GNPC_LOGIN 
			&& mNetEvent->getType() != PT_LOGIN_C2F_CREATE_CLAN)
		{
			return;
		}
		LineUpNetPacketProcesser::getInstance().sendLineUpInfoToClient(mNetEvent->getID(),line_up_busy_fc_create_clan);
		LoginNetPacketProcesser::getInstance().onClientCreateClan(
			mNetEvent->getID(), 
			(PT_LOGIN_C2F_CREATE_CLAN_DATA*)((GameNetPacketData*)mNetEvent->getData())->data
			);
	}
	
    //***********************************************************************************************************
    // DeleteClanTask
    //***********************************************************************************************************

    //----------------------------------------------------------------------
	DeleteClanTask::DeleteClanTask(I32 clientNetId,NetEventRecv* netEvent,U32 key)
		: ModeTask( U32(TTT_DELETECLAN),key)

	{
		mNetEvent = netEvent;
		mClientNetId = clientNetId;
	}

	//----------------------------------------------------------------------
	DeleteClanTask::~DeleteClanTask()
	{
	}

	//----------------------------------------------------------------------
	void DeleteClanTask::free()
	{
		ThreadTaskManager::getInstance().freeDeleteClanTask(this);
	}

	//----------------------------------------------------------------------
	void DeleteClanTask::process()
	{
		LineUpNetPacketProcesser::getInstance().sendLineUpInfoToClient(mNetEvent->getID(),line_up_busy_fc_del_clan);
		GameNetPacketData* data = (GameNetPacketData*)(mNetEvent->getData());
		DYNAMIC_ASSERT(data);
		//TODO:
		// 需要对用到的数据做 数据同步！！！
		LoginNetPacketProcesser::getInstance().onClientDeleteClan(mNetEvent->getID(), (PT_LOGIN_C2F_DELETE_CLAN_DATA*)data->data);
		
	}
	
    //***********************************************************************************************************
    // CreateGeneralTask
    //***********************************************************************************************************

    //----------------------------------------------------------------------
	CreateGeneralTask::CreateGeneralTask(NetEventRecv* netEvent,I32 id,U32 key )
		: ModeTask( U32(TTT_CREATEGENERAL),key)

	{
		mNetEvent = netEvent;
		mClientNetId = id;
	}

	//----------------------------------------------------------------------
	CreateGeneralTask::~CreateGeneralTask()
	{
		
	}

	//----------------------------------------------------------------------
	void CreateGeneralTask::free()
	{
		ThreadTaskManager::getInstance().freeCreateGeneralTask(this);
	}

	//----------------------------------------------------------------------
	void CreateGeneralTask::process()
	{
		LineUpNetPacketProcesser::getInstance().sendLineUpInfoToClient(mNetEvent->getID(),line_up_busy_fc_create_character);
		if (mNetEvent->getChannel() != GNPC_LOGIN 
			&& mNetEvent->getType() != PT_LOGIN_C2F_CREATE_GENERAL)
		{
			return;
		}

		LoginNetPacketProcesser::getInstance().onClientCreateGenreal(
			mNetEvent->getID(),
			(PT_LOGIN_C2F_CREATE_GENERAL_DATA*)((GameNetPacketData*)mNetEvent->getData())->data
			);
	}
	

    //***********************************************************************************************************
    // JoinGameTask
    //***********************************************************************************************************

    //----------------------------------------------------------------------
	JoinGameTask::JoinGameTask(NetEventRecv* netEvent,I32 clientNetId,U32 key )
		: ModeTask( U32(TTT_JOINGAMETASK),key)
		,mClientNetId(clientNetId)

	{
		mNetEvent = netEvent;
	}

	//----------------------------------------------------------------------
	JoinGameTask::~JoinGameTask()
	{

	}

	//----------------------------------------------------------------------
	void JoinGameTask::free()
	{
		ThreadTaskManager::getInstance().freeJoinGameTask(this);
	}

	//----------------------------------------------------------------------
	void JoinGameTask::process()
	{

		if (mNetEvent->getChannel() != GNPC_LOGIN 
			&& mNetEvent->getType() != PT_LOGIN_C2F_JOINGAME)
		{
			return;
		}
		LineUpNetPacketProcesser::getInstance().sendLineUpInfoToClient(mNetEvent->getID(),line_up_busy_fc_join_game);

		LoginNetPacketProcesser::getInstance().onClientJoinGame(
			mNetEvent->getID(), 
			(PT_LOGIN_C2F_JOINGAME_DATA*)((GameNetPacketData*)mNetEvent->getData())->data
			);
	}

    //***********************************************************************************************************
    // ServerNormalTask
    //***********************************************************************************************************

    //----------------------------------------------------------------------
	ServerNormalTask::ServerNormalTask( NetEventRecv* netEvent,I32 serverNetId, U32 key /*= 0*/ )
		:ModeTask( U32(TTT_NORMAL_SERVER),key)
	{
		mNetEvent = netEvent;
		mServerNetId = serverNetId;
	}

    //----------------------------------------------------------------------
	ServerNormalTask::~ServerNormalTask()
	{

	}

    //----------------------------------------------------------------------
	void ServerNormalTask::process()
	{
		//根据ID分派不同服务器消息处理
		if ( ServerManager::getInstance().getLoginServerNetId() == mServerNetId )
		{
			if ( LoginNetPacketProcesser::getInstance().processLoginServerPacket( mServerNetId, mNetEvent ) == true )
                return ;
		}
		else 
        if ( ServerManager::getInstance().getCenterServerNetId() == mServerNetId )
		{
			if (NetTranspondPacketProcesser::getInstance().processCenterServerPacket( mServerNetId, mNetEvent  ) == true )
                return;
				
			if ( ServerStateNetPacketProcesser::getInstance().processCenterServerPacket( mServerNetId, mNetEvent  ) == true )
				return;

			if ( CampaignNetPacketProcesser::getInstance().processCenterServerPacket(mServerNetId, mNetEvent ) == true )
				return;

			if (TimeNetPacketProcesser::getInstance().processCenterServerPacket( mServerNetId, mNetEvent  ) == true )
                return;

			if (SPveNetPacketProcessor::getInstance().processCenterServerPacket( mServerNetId, mNetEvent  ) == true)
				return;
		}
		else 
        if ( ServerManager::getInstance().getChatServerNetId() == mServerNetId )
		{
			if ( ChatNetPacketProcesser::getInstance().processChatServerPacket(mServerNetId, mNetEvent ) == true )
				return;

			if ( NetTranspondPacketProcesser::getInstance().processChatServerPacket( mServerNetId, mNetEvent  ) == true )
                return;
		}
		else 
        if (NULL != ServerManager::getInstance().getMapServer(mServerNetId))
		{
			if ( LoginNetPacketProcesser::getInstance().processMapServerPacket( mServerNetId, mNetEvent ) == true )
				return ;
			if (PlayerCharacterNetPacketProcesser::getInstance().processMapServerPacket(mServerNetId, mNetEvent  ) == true)
                return;

			if ( CampaignNetPacketProcesser::getInstance().processMapServerPacket(mServerNetId, mNetEvent  ) == true)
                return;

			if (TroopNetPacketProcesser::getInstance().processMapServerPacket(mServerNetId, mNetEvent ) == true)
                return;

			if (PlayerNetPacketProcesser::getInstance().processMapServerPacket(mServerNetId, mNetEvent ) == true)
                return;

			if (ItemPacketProcesser::getInstance().processMapServerPacket(mServerNetId, mNetEvent) == true)
                return;

			if (SCDNetPacketProcesser::getInstance().processMapServerPacket(mServerNetId, mNetEvent ) == true)
                return;

			if (SAttributeNetPacketProcesser::getInstance().processMapServerPacket(mServerNetId, mNetEvent ) == true)
                return;

			if (RegionNetPacketProcesser::getInstance().processMapServerPacket(mServerNetId, mNetEvent ) == true)
                return;
            
			if (MonsterNetPacketProcesser::getInstance().processMapServerPacket(mServerNetId, mNetEvent ) == true)
				return;
			
			if (SBuffPacketProcesser::getInstance().processMapServerPacket(mServerNetId, mNetEvent) == true)
				return;
		}
      
        // 转发包处理
        if ( ServerManager::getInstance().getCenterServerNetId() == mServerNetId )
        {
            if (NetTranspondPacketProcesser::getInstance().processCenterServerPacket( mServerNetId, mNetEvent  ) == true )
                return;
        }
        else 
        if ( ServerManager::getInstance().getChatServerNetId() == mServerNetId )
        {
            if (NetTranspondPacketProcesser::getInstance().processChatServerPacket( mServerNetId, mNetEvent  ) == true )
                return;
        }
        else 
        if (NULL != ServerManager::getInstance().getMapServer(mServerNetId))
        {
            if (NetTranspondPacketProcesser::getInstance().processMapServerPacket( mServerNetId, mNetEvent  ) == true )
                return;
        }
	}

    //----------------------------------------------------------------------
    
	void ServerNormalTask::free()
	{
		ThreadTaskManager::getInstance().freeServerNormalTask(this);
	}

    //***********************************************************************************************************
    // ServerNetTranspondSendTask
    //***********************************************************************************************************

    //----------------------------------------------------------------------
    ServerNetTranspondSendTask::ServerNetTranspondSendTask( NetEventRecv* netEvent,I32 serverNetId, U32 key /*= 0*/ )
        :ModeTask( U32(TTT_NETTRANSPOND_SEND_SERVER),key)
    {
        mNetEvent = netEvent;
        mServerNetId = serverNetId;
    }

    //----------------------------------------------------------------------
    ServerNetTranspondSendTask::~ServerNetTranspondSendTask()
    {

    }

    //----------------------------------------------------------------------
    void ServerNetTranspondSendTask::process()
    {
        // 暂时放到void ServerNormalTask::process()处理
        // 如果要开放需要开会讨论


        //if ( ServerManager::getInstance().getCenterServerNetID() == mServerNetId )
        //{
        //    if (NetTranspondPacketProcesser::getInstance().processCenterServerPacket( mServerNetId, mNetEvent  ) == true )
        //        return;
        //}
        //else 
        //if ( ServerManager::getInstance().getChatServerNetId() == mServerNetId )
        //{
        //    if (NetTranspondPacketProcesser::getInstance().processChatServerPacket( mServerNetId, mNetEvent  ) == true )
        //        return;
        //}
        //else 
        //if (NULL != ServerManager::getInstance().getActiveMapServerByNetId(mServerNetId))
        //{
        //    if (NetTranspondPacketProcesser::getInstance().processMapServerPacket( mServerNetId, mNetEvent  ) == true )
        //        return;
        //}
    }

    //----------------------------------------------------------------------

    void ServerNetTranspondSendTask::free()
    {
        ThreadTaskManager::getInstance().freeServerNetTranspondSendTask(this);
    }

    //***********************************************************************************************************
    // ServerNetTranspondSaveTask
    //***********************************************************************************************************

    //----------------------------------------------------------------------
    ServerNetTranspondSaveTask::ServerNetTranspondSaveTask( NetEventRecv* netEvent,I32 serverNetId, U32 key )
        :ModeTask( U32(TTT_NETTRANSPOND_SAVE_SERVER),key)
    {
        mNetEvent = netEvent;
        mServerNetId = serverNetId;
    }

    //----------------------------------------------------------------------
    ServerNetTranspondSaveTask::~ServerNetTranspondSaveTask()
    {

    }

    //----------------------------------------------------------------------
    void ServerNetTranspondSaveTask::process()
    {
        if ( ServerManager::getInstance().getCenterServerNetId() == mServerNetId )
        {
            if (NetTranspondPacketProcesser::getInstance().processCenterServerPacket( mServerNetId, mNetEvent  ) == true )
                return;
        }
        else 
        if ( ServerManager::getInstance().getChatServerNetId() == mServerNetId )
        {
            if (NetTranspondPacketProcesser::getInstance().processChatServerPacket( mServerNetId, mNetEvent  ) == true )
                return;
        }
        else 
        if (NULL != ServerManager::getInstance().getMapServer(mServerNetId))
        {
            if (NetTranspondPacketProcesser::getInstance().processMapServerPacket( mServerNetId, mNetEvent  ) == true )
                return;
        }
    }

    //----------------------------------------------------------------------
    void ServerNetTranspondSaveTask::free()
    {
        ThreadTaskManager::getInstance().freeServerNetTranspondSaveTask(this);
    }


}
//***********************************************************************************************************