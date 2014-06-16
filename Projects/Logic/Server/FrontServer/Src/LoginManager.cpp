/******************************************************************************/

#include "stdafx.h"
#include "LoginNetPacketProcesser.h"
#include "LoginManager.h"
#include "SServerSetting.h"
#include "FrontServerMain.h"
#include "RamAlloc.h"
#include "AccountDB.h"
#include "ClientManager.h"
#include "ServerManager.h"
#include "PlayerNetPacketProcesser.h"
#include "PlayerCharacterNetPacketProcesser.h"
#include "LoginNetPacketProcesser.h"
#include "CommonGameDefine.h"
#include "SPlayer.h"
#include "SPlayerCharacter.h"
#include "SClan.h"
#include "SWorldManager.h"
#include "ChatInterValCheckManager.h"
#include "CampaignNetPacketProcesser.h"
#include "SPveNetPacketProcessor.h"
#include "PlayerDBProcessor.h"
#include "ClanDBProcessor.h"
#include "PlayerCharacterDBProcessor.h"
#include "QuestDBProcessor.h"
#include "ItemDBProcessor.h"
#include "SPlayerManager.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	LoginManager::LoginManager()
	{
	}
	//-----------------------------------------------------------------------------
	LoginManager::~LoginManager()
	{
	}

    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------


	//-----------------------------------------------------------------------------
	Bool LoginManager::initialize(DBDriver* Driver,SServerSetting* setting)
	{
		return true;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::uninitialize()
	{
	}
	//-----------------------------------------------------------------------------
	void LoginManager::update()
	{
	}

    //-----------------------------------------------------------------------------------
    // Account
    //-----------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	void LoginManager::handleClientLogin( I32 id, Char16* accName, Char16* accPsw )
	{
        ClientObject* clientPtr = ClientManager::getInstance().getClientObject( id );
		
        if (clientPtr)
        {
            (clientPtr)->setAccountInfo( accName, accPsw );
            //LoginNetPacketProcesser::getInstance().sendClientLoginCheckToLoginServer( id, accName, accPsw );
			LoginManager::onClientLoginSuccessedFromLoginServer(clientPtr, id );
        }
	}

	//-----------------------------------------------------------------------------
	void LoginManager::handleClientLogout( ClientObject* clientPtr )
	{
#if 0
        //通知各个服务器

        SPlayerPtr playerPtr;
        clientPtr->getPlayer( playerPtr );

        //LoginServer
        LoginNetPacketProcesser::getInstance().sendClientLogoutToLoginServer(clientPtr->getAccountNAme().c_str() );

		if ( playerPtr.isNull() == false )
		{
            // SysLogServer
            SysLogNetPacketProcesser::getInstance().sendCharacterListInfoToSysLogServer(playerPtr, false);
            
            // MapServer
            PlayerNetPacketProcesser::getInstance().broadcastPlayerLogoutToMapServer( playerPtr );

            // CenterServer
            CampaignNetPacketProcesser::getInstance().sendCampaignDisconnectToCenterServer(playerPtr);

            // CenterServer
            SPveNetPacketProcessor::getInstance().sendPveDisconnectToCenterServer(playerPtr);

            // ChatServer
            ChatIntervalCheckManager::getInstance().removeClientChatTickRecordBytNetID(clientPtr->getNetID());

            //-----------------------------------------------------------------------------

            // remove player
            SPlayerManager::getInstance().removePlayer( playerPtr->getAccountID() );
		}
#endif
	}

    //-----------------------------------------------------------------------------
    void LoginManager::onClientLoginSuccessedFromLoginServer( ClientObject* clientPtr, AccountIdType accID )
    {
        //-----------------------------------------------------------------------------

        //通知聊天间隔验证管理器
        ChatIntervalCheckManager::getInstance().addClientChatTickRecord( clientPtr->getNetID() );


        //-----------------------------------------------------------------------------.
        // create player
        //-----------------------------------------------------------------------------.


        SPlayerPtr playerPtr;

        SPlayerManager::getInstance().addPlayer( playerPtr, accID, clientPtr->getNetID(), clientPtr->getAccountNAme() );

        clientPtr->setPlayer( playerPtr );

        clientPtr->setAccountActive( true );

        //-----------------------------------------------------------------------------

        //连接FrontServer成功
        LoginNetPacketProcesser::getInstance().sendClientConnectFrontServerResult( clientPtr->getNetID(), LCFT_LOGIN_SUCCESS, playerPtr->getAccountID());
        


        //-----------------------------------------------------------------------------.
        // load DB
        //-----------------------------------------------------------------------------.


        // load Clan DB
        //ClanDBProcessor::getInstance().loadAndCreateAllClanInPlayer( playerPtr );

        // 如果没有氏族则通知客户端创建氏族
        if ( playerPtr->hasClan() == false )
        {
            LoginNetPacketProcesser::getInstance().sendClientOpenClanCreateUI( clientPtr->getNetID() );
            return;
        }

        // 设置主氏族
        playerPtr->setFirstMainClan();
		//获得住氏族，并做错误处理
		SClanPtr clanPtr;
		if ( playerPtr->getMainClan(clanPtr) )
		{
			DYNAMIC_ASSERT_LOG(0, "找不到当前氏族");
			//玩家退出
			return;
		}

        //-----------------------------------------------------------------------------.

		// load PlayerCharacter DB
		//PlayerCharacterDBProcessor::getInstance().loadAndCreateAllPlayerCharacterInPlayer( playerPtr );

		//加载角色信息，
		if ( false == clanPtr->checkMainGenreal() )
		{
			LoginNetPacketProcesser::getInstance().sendClientOpenGenrealCreateUI( clientPtr->getNetID() );
			return;
		}

        //-----------------------------------------------------------------------------.
        // send data to Client
        //-----------------------------------------------------------------------------.


        // 向客户端发送氏族信息
        LoginNetPacketProcesser::getInstance().sendClientClanInfo( clientPtr->getNetID(), clanPtr->getData() );

        // 发送简单角色list信息
        PlayerNetPacketProcesser::getInstance().sendPlayerCharacterListToClient( clientPtr->getNetID(), playerPtr.getPointer() );

        // 发送任务信息
        //QuestNetPacketProcesser::getInstance().sendAllQuestInfoToClient( clientPtr->getNetID(), playerPtr );

        //-----------------------------------------------------------------------------.
        
       
        
        // 发送物品信息
        //ItemPacketProcesser::getInstance().sendAllClanItemInfoToClient( clientPtr->getNetID(), clanPtr );
        
        // 发送技能信息
        //PlayerCharacterNetPacketProcesser::getInstance().sendPlayerCharacterSkillInfoToClient( clientPtr->getNetID(),  clanPtr );
        
        //-----------------------------------------------------------------------------.
        
        //向客户端发送打开家族控制面板;
        LoginNetPacketProcesser::getInstance().sendClientOpenClanControlUI( clientPtr->getNetID() );
        
    }

    //-----------------------------------------------------------------------------
    void LoginManager::handleLoginServerDisconnect()
    {
        FrontServerMain::getInstance().getServerLauncher()->closeAllClient();
    }
    
    //-----------------------------------------------------------------------------------
    //  Clan
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    //U8 LoginManager::handleClanSelect( I32 clientID, I32 clanId )
    //{
    //    SPlayerPtr pPlayer = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(clientID);
    //    if ( pPlayer.isNull())
    //    {
    //        //异常,需处理.
    //        DYNAMIC_ASSERT(0);
    //        return SelectClanResult_OtherError;
    //    } 

    //    //判断是否正在删除中。
    //    //？
    //    SClan* mainClan = pPlayer->getClanFromList(clanId);
    //    if ( mainClan )
    //    {  
    //        pPlayer->setMainClan(mainClan);

    //        PlayerNetPacketProcesser::getInstance().sendPlayerCharacterListToClient(clientID, pPlayer.getPointer());  
    //        return  SelectClanResult_Succeed;
    //    }
    //    else
    //    {
    //        //发送select失败的信息
    //        return SelectClanResult_ClanUnexist;
    //    }
    //}

    //-----------------------------------------------------------------------------
    void LoginManager::sendClientOpenCreateClan( I32 id )
    {
        LoginNetPacketProcesser::getInstance().sendClientOpenClanCreateUI(id);
    }
    //-----------------------------------------------------------------------------
    //void LoginManager::sendClientOpenControlClan( I32 id )
    //{
    //    LoginNetPacketProcesser::getInstance().sendClientOpenClanControlUI(id);
    //    //刚刚创建，无武将信息。
    //}
    //-----------------------------------------------------------------------------
    void LoginManager::sendClientDeleteClanResult( I32 id, U8 result )
    {
        LoginNetPacketProcesser::getInstance().sendClientClanDeleteResult(id, result);
    }


    //-----------------------------------------------------------------------------------
    //  Check
    //-----------------------------------------------------------------------------------


	//-----------------------------------------------------------------------------
	void LoginManager::handleCheckClientInServerFromLs( I32 loginServerNetId,I32 clientNetId ,I32 clientNetIdInFs)
	{
		//ClientObject* clientObj = ClientManager::getInstance().getWaitingLoginClient(clientNetId);
		//if (clientObj)
		//{
		//	LoginNetPacketProcesser::getInstance().sendCheckClientInServerRelultToLs(loginServerNetId,clientNetIdInFs,true);
		//}
		//else
		//{

		//	LoginNetPacketProcesser::getInstance().sendCheckClientInServerRelultToLs(loginServerNetId,clientNetIdInFs,false);
		//}
	}

	//-----------------------------------------------------------------------------
	void LoginManager::handleCheckClientInServerFromMs( I32 mapServerNetId,I32 clientNetId )
	{
		//ClientObject* clientObj = ClientManager::getInstance().getWaitingLoginClient(clientNetId);
		//if (clientObj)
		//{
		//	LoginNetPacketProcesser::getInstance().sendCheckClientInServerRelultToMs(mapServerNetId,clientNetId,true);
		//}
		//else
		//{
		//	LoginNetPacketProcesser::getInstance().sendCheckClientInServerRelultToMs(mapServerNetId,clientNetId,false);
		//}
	}
	//-----------------------------------------------------------------------------
	CreateClanResult LoginManager::handleClientCreateClan(I32 id,  ClanData& _clanData )
	{
		//先检查这个玩家是否存在, ClanData是否合法。
		SPlayerPtr pSPlayerPtr;
		CreateClanResult createclanresultType = checkClanDataLawful(&_clanData, pSPlayerPtr);
		if ( CreateClanResult_Succeed != createclanresultType )
		{	
			return createclanresultType;
		}
		
		SClanPtr sclan;

		//内存中创建氏族。
		if ( false == pSPlayerPtr->addClan(sclan, _clanData) )
		{	
			DYNAMIC_ASSERT_LOG(0, "氏族创建分配内存失败");
			//推出登陆
			return CreateClanResult_CreateMemory_Error;
		}

		//设置当前活动的氏族
		pSPlayerPtr->setMainClan(_clanData.clanId);

		//DB中插入氏族信息
		if ( ClanDBProcessor::getInstance().insertClanDataInfo(&_clanData) )
		{	
			DYNAMIC_ASSERT_LOG(0, "氏族创建存储DB失败");
			//推出登陆
			return CreateClanResult_DB_Error;
		}

		//暂时写在这，
		LoginNetPacketProcesser::getInstance().sendClientClanInfo(id, &_clanData);
		LoginNetPacketProcesser::getInstance().sendClientOpenGenrealCreateUI(id);
		
		return CreateClanResult_Succeed;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::handleClientJoinGame( I32 id, PlayerIdType accountId )
	{
		//玩家是否存在。
		SPlayerPtr pSPlayerPtr;
		if ( SPlayerManager::getInstance().getPlayer(pSPlayerPtr, accountId) )
		{
			DYNAMIC_ASSERT_LOG(0, "登陆时找不到玩家对象");
			//退出登陆
			return;
		}

		//发送给mapsever 玩家的信息;
		PlayerNetPacketProcesser::getInstance().broadcastPlayerLoginToMapServer( pSPlayerPtr );
		//发送给mapsever 角色列表的信息;
		PlayerNetPacketProcesser::getInstance().broadcastPlayerCharacterListToMapServer( pSPlayerPtr );

		//发送武将登陆信息到日志服务器。
		//SysLogNetPacketProcesser::getInstance().sendCharacterListInfoToSysLogServer( pSPlayerPtr );


		//当前武将跳转地图

		//找到当前氏族
		SClanPtr pSClanPtr;
		if ( false == pSPlayerPtr->getMainClan(pSClanPtr) )
		{
			DYNAMIC_ASSERT_LOG(0, "登陆时找不到氏族对象");
			//退出登陆
			return;
		}

		//找到当前武将
		SPlayerCharacterPtr pSPlayerCharacterPtr;
		if ( false == pSClanPtr->getCurGenreal( pSPlayerCharacterPtr ) )
		{
			DYNAMIC_ASSERT_LOG(0, "找不到当前武将");
			if ( false == pSClanPtr->getMainPlayerCharacter( pSPlayerCharacterPtr ) )
			{
				DYNAMIC_ASSERT_LOG(0, "找不到主武将");
				//退出登陆
				return;
			}
			pSClanPtr->setCurGenreal( pSPlayerCharacterPtr->getID() );
		}

		//检查目标MapServer是否正常
		const REGION_OBJ_TYPE	regionType	= pSPlayerCharacterPtr->getData()->mRegionType;
		const RegionIdType		regionId	= pSPlayerCharacterPtr->getData()->mRegionID;
		const InstanceUIdType	instanceUId = pSPlayerCharacterPtr->getData()->mInstanceUId;
		PlayerCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpToRegionNewVer(
			pSPlayerCharacterPtr.getPointer(), regionType,  regionId, instanceUId
			);

		//通知ChatServer客户端进入游戏
		Str16 tempName =  pSClanPtr->getClanHomeLandName() + pSClanPtr->getName() + Str16(L"氏");
		LoginNetPacketProcesser::getInstance().sendClientJoinGameToChatServer(
				pSPlayerPtr->getClientNetID(), pSClanPtr->getAccountID(), tempName.c_str()
			);

	}
	//-----------------------------------------------------------------------------
	CreateGenrealResult LoginManager::handleClientCreateGenreal( I32 id, PlayerCharacterData& _PlayerCharacterData, const CharacterResInfo* _pCreateChar )
	{
		SPlayerPtr pSPlayerPtr;
		CreateGenrealResult creategenrealresult;// = checkGenrealDataLawful(_PlayerCharacterData, pSPlayerPtr);
		if ( CreateGenrealResult_Succeed != creategenrealresult )
		{
			return creategenrealresult;
		}

		//获得新手村的regionId
		//MapType2RegionObject::MapTypeChangeRegionObject(_pCreateChar->maplisttype, _pCreateChar->maplistid, _PlayerCharacterData.mRegionType, _PlayerCharacterData.mRegionID);

		SClanPtr pSClanPtr;
		if ( false == pSPlayerPtr->getMainClan(pSClanPtr) )
		{
			DYNAMIC_ASSERT_LOG(0, "找不到氏族");
			//推出登陆
			return CreateGenrealResult_Error_NotClan;
		}
		//内存中创建主武将。
		SPlayerCharacterPtr pSPlayerCharacterPtr;
		if ( false == pSClanPtr->addPlayerCharacter(pSPlayerCharacterPtr, _PlayerCharacterData) )
		{
			DYNAMIC_ASSERT_LOG(0, "武将创建分配内存失败");
			//退出登陆
			return CreateGenrealResult_Error_Memory;
		}
		//设置主武将
		//设置当前活动的武将

		//DB中更新武将信息
		if ( false == PlayerCharacterDBProcessor::getInstance().insertGenrealDataInfo(&_PlayerCharacterData) )
		{
			DYNAMIC_ASSERT_LOG(0, "武将创建更新DB失败");
			//退出登陆
			return CreateGenrealResult_Error_DB;
		}
		//DB更新clan信息（主武将，当前武将）
		if ( false == ClanDBProcessor::getInstance().updateClanDataInfo(pSClanPtr->getData()) )
		{
			DYNAMIC_ASSERT_LOG(0, "武将创建更新DB失败");
			//退出登陆
			return CreateGenrealResult_Error_DB;
		}

		//发送给客户端武将信息。（可考虑不发）
		//通知客户端打开氏族管理界面。（可考虑不发）
		PlayerNetPacketProcesser::getInstance().sendPlayerCharacterToClient(id, pSPlayerCharacterPtr.getPointer());
		LoginNetPacketProcesser::getInstance().sendClientOpenClanControlUI(id);
		
		return CreateGenrealResult_Succeed;
	}
	//-----------------------------------------------------------------------------
	MG::CreateClanResult LoginManager::checkClanDataLawful( ClanData* _clandata, SPlayerPtr& pSPlayerPtr )
	{
		if ( false == SPlayerManager::getInstance().getPlayer(pSPlayerPtr, _clandata->accountId) )
		{	
			DYNAMIC_ASSERT_LOG(0, "找不到玩家");
			//退出登陆
			return CreateClanResult_NoPlayer;
		}

		// 名字的长度。
		Int nLength = _clandata->clanHomeLandName.length();
		if ( nLength <= 0  ||  nLength > MAX_CHARACTER_NAME_LEN )
			return CreateClanResult_NameExistOrUnlaw;

		nLength = _clandata->clanName.length();
		if ( nLength <= 0  ||  nLength > MAX_CHARACTER_NAME_LEN )
			return CreateClanResult_NameExistOrUnlaw;
	}
	//-----------------------------------------------------------------------------
	MG::CreateGenrealResult LoginManager::checkGenrealDataLawful( PlayerCharacterData* _PlayerCharacterData, SPlayerPtr& pSPlayerPtr )
	{
		if ( false == SPlayerManager::getInstance().getPlayer(pSPlayerPtr, _PlayerCharacterData->charAccountId) )
		{	
			DYNAMIC_ASSERT_LOG(0, "找不到玩家");
			//退出登陆
			return CreateGenrealResult_Error_NotPlayer;
		}

		// 名字的长度。
		Int nLength = _PlayerCharacterData->charSurName.length();
		if ( nLength <= 0  ||  nLength > MAX_CHARACTER_NAME_LEN )
			return CreateGenrealResult_Error_Name;

		nLength = _PlayerCharacterData->mName.length();
		if ( nLength <= 0  ||  nLength > MAX_CHARACTER_NAME_LEN )
			return CreateGenrealResult_Error_Name;
	}
}