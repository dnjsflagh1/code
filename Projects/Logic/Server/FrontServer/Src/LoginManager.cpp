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
        //֪ͨ����������

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

        //֪ͨ��������֤������
        ChatIntervalCheckManager::getInstance().addClientChatTickRecord( clientPtr->getNetID() );


        //-----------------------------------------------------------------------------.
        // create player
        //-----------------------------------------------------------------------------.


        SPlayerPtr playerPtr;

        SPlayerManager::getInstance().addPlayer( playerPtr, accID, clientPtr->getNetID(), clientPtr->getAccountNAme() );

        clientPtr->setPlayer( playerPtr );

        clientPtr->setAccountActive( true );

        //-----------------------------------------------------------------------------

        //����FrontServer�ɹ�
        LoginNetPacketProcesser::getInstance().sendClientConnectFrontServerResult( clientPtr->getNetID(), LCFT_LOGIN_SUCCESS, playerPtr->getAccountID());
        


        //-----------------------------------------------------------------------------.
        // load DB
        //-----------------------------------------------------------------------------.


        // load Clan DB
        //ClanDBProcessor::getInstance().loadAndCreateAllClanInPlayer( playerPtr );

        // ���û��������֪ͨ�ͻ��˴�������
        if ( playerPtr->hasClan() == false )
        {
            LoginNetPacketProcesser::getInstance().sendClientOpenClanCreateUI( clientPtr->getNetID() );
            return;
        }

        // ����������
        playerPtr->setFirstMainClan();
		//���ס���壬����������
		SClanPtr clanPtr;
		if ( playerPtr->getMainClan(clanPtr) )
		{
			DYNAMIC_ASSERT_LOG(0, "�Ҳ�����ǰ����");
			//����˳�
			return;
		}

        //-----------------------------------------------------------------------------.

		// load PlayerCharacter DB
		//PlayerCharacterDBProcessor::getInstance().loadAndCreateAllPlayerCharacterInPlayer( playerPtr );

		//���ؽ�ɫ��Ϣ��
		if ( false == clanPtr->checkMainGenreal() )
		{
			LoginNetPacketProcesser::getInstance().sendClientOpenGenrealCreateUI( clientPtr->getNetID() );
			return;
		}

        //-----------------------------------------------------------------------------.
        // send data to Client
        //-----------------------------------------------------------------------------.


        // ��ͻ��˷���������Ϣ
        LoginNetPacketProcesser::getInstance().sendClientClanInfo( clientPtr->getNetID(), clanPtr->getData() );

        // ���ͼ򵥽�ɫlist��Ϣ
        PlayerNetPacketProcesser::getInstance().sendPlayerCharacterListToClient( clientPtr->getNetID(), playerPtr.getPointer() );

        // ����������Ϣ
        //QuestNetPacketProcesser::getInstance().sendAllQuestInfoToClient( clientPtr->getNetID(), playerPtr );

        //-----------------------------------------------------------------------------.
        
       
        
        // ������Ʒ��Ϣ
        //ItemPacketProcesser::getInstance().sendAllClanItemInfoToClient( clientPtr->getNetID(), clanPtr );
        
        // ���ͼ�����Ϣ
        //PlayerCharacterNetPacketProcesser::getInstance().sendPlayerCharacterSkillInfoToClient( clientPtr->getNetID(),  clanPtr );
        
        //-----------------------------------------------------------------------------.
        
        //��ͻ��˷��ʹ򿪼���������;
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
    //        //�쳣,�账��.
    //        DYNAMIC_ASSERT(0);
    //        return SelectClanResult_OtherError;
    //    } 

    //    //�ж��Ƿ�����ɾ���С�
    //    //��
    //    SClan* mainClan = pPlayer->getClanFromList(clanId);
    //    if ( mainClan )
    //    {  
    //        pPlayer->setMainClan(mainClan);

    //        PlayerNetPacketProcesser::getInstance().sendPlayerCharacterListToClient(clientID, pPlayer.getPointer());  
    //        return  SelectClanResult_Succeed;
    //    }
    //    else
    //    {
    //        //����selectʧ�ܵ���Ϣ
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
    //    //�ոմ��������佫��Ϣ��
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
		//�ȼ���������Ƿ����, ClanData�Ƿ�Ϸ���
		SPlayerPtr pSPlayerPtr;
		CreateClanResult createclanresultType = checkClanDataLawful(&_clanData, pSPlayerPtr);
		if ( CreateClanResult_Succeed != createclanresultType )
		{	
			return createclanresultType;
		}
		
		SClanPtr sclan;

		//�ڴ��д������塣
		if ( false == pSPlayerPtr->addClan(sclan, _clanData) )
		{	
			DYNAMIC_ASSERT_LOG(0, "���崴�������ڴ�ʧ��");
			//�Ƴ���½
			return CreateClanResult_CreateMemory_Error;
		}

		//���õ�ǰ�������
		pSPlayerPtr->setMainClan(_clanData.clanId);

		//DB�в���������Ϣ
		if ( ClanDBProcessor::getInstance().insertClanDataInfo(&_clanData) )
		{	
			DYNAMIC_ASSERT_LOG(0, "���崴���洢DBʧ��");
			//�Ƴ���½
			return CreateClanResult_DB_Error;
		}

		//��ʱд���⣬
		LoginNetPacketProcesser::getInstance().sendClientClanInfo(id, &_clanData);
		LoginNetPacketProcesser::getInstance().sendClientOpenGenrealCreateUI(id);
		
		return CreateClanResult_Succeed;
	}
	//-----------------------------------------------------------------------------
	void LoginManager::handleClientJoinGame( I32 id, PlayerIdType accountId )
	{
		//����Ƿ���ڡ�
		SPlayerPtr pSPlayerPtr;
		if ( SPlayerManager::getInstance().getPlayer(pSPlayerPtr, accountId) )
		{
			DYNAMIC_ASSERT_LOG(0, "��½ʱ�Ҳ�����Ҷ���");
			//�˳���½
			return;
		}

		//���͸�mapsever ��ҵ���Ϣ;
		PlayerNetPacketProcesser::getInstance().broadcastPlayerLoginToMapServer( pSPlayerPtr );
		//���͸�mapsever ��ɫ�б����Ϣ;
		PlayerNetPacketProcesser::getInstance().broadcastPlayerCharacterListToMapServer( pSPlayerPtr );

		//�����佫��½��Ϣ����־��������
		//SysLogNetPacketProcesser::getInstance().sendCharacterListInfoToSysLogServer( pSPlayerPtr );


		//��ǰ�佫��ת��ͼ

		//�ҵ���ǰ����
		SClanPtr pSClanPtr;
		if ( false == pSPlayerPtr->getMainClan(pSClanPtr) )
		{
			DYNAMIC_ASSERT_LOG(0, "��½ʱ�Ҳ����������");
			//�˳���½
			return;
		}

		//�ҵ���ǰ�佫
		SPlayerCharacterPtr pSPlayerCharacterPtr;
		if ( false == pSClanPtr->getCurGenreal( pSPlayerCharacterPtr ) )
		{
			DYNAMIC_ASSERT_LOG(0, "�Ҳ�����ǰ�佫");
			if ( false == pSClanPtr->getMainPlayerCharacter( pSPlayerCharacterPtr ) )
			{
				DYNAMIC_ASSERT_LOG(0, "�Ҳ������佫");
				//�˳���½
				return;
			}
			pSClanPtr->setCurGenreal( pSPlayerCharacterPtr->getID() );
		}

		//���Ŀ��MapServer�Ƿ�����
		const REGION_OBJ_TYPE	regionType	= pSPlayerCharacterPtr->getData()->mRegionType;
		const RegionIdType		regionId	= pSPlayerCharacterPtr->getData()->mRegionID;
		const InstanceUIdType	instanceUId = pSPlayerCharacterPtr->getData()->mInstanceUId;
		PlayerCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpToRegionNewVer(
			pSPlayerCharacterPtr.getPointer(), regionType,  regionId, instanceUId
			);

		//֪ͨChatServer�ͻ��˽�����Ϸ
		Str16 tempName =  pSClanPtr->getClanHomeLandName() + pSClanPtr->getName() + Str16(L"��");
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

		//������ִ��regionId
		//MapType2RegionObject::MapTypeChangeRegionObject(_pCreateChar->maplisttype, _pCreateChar->maplistid, _PlayerCharacterData.mRegionType, _PlayerCharacterData.mRegionID);

		SClanPtr pSClanPtr;
		if ( false == pSPlayerPtr->getMainClan(pSClanPtr) )
		{
			DYNAMIC_ASSERT_LOG(0, "�Ҳ�������");
			//�Ƴ���½
			return CreateGenrealResult_Error_NotClan;
		}
		//�ڴ��д������佫��
		SPlayerCharacterPtr pSPlayerCharacterPtr;
		if ( false == pSClanPtr->addPlayerCharacter(pSPlayerCharacterPtr, _PlayerCharacterData) )
		{
			DYNAMIC_ASSERT_LOG(0, "�佫���������ڴ�ʧ��");
			//�˳���½
			return CreateGenrealResult_Error_Memory;
		}
		//�������佫
		//���õ�ǰ����佫

		//DB�и����佫��Ϣ
		if ( false == PlayerCharacterDBProcessor::getInstance().insertGenrealDataInfo(&_PlayerCharacterData) )
		{
			DYNAMIC_ASSERT_LOG(0, "�佫��������DBʧ��");
			//�˳���½
			return CreateGenrealResult_Error_DB;
		}
		//DB����clan��Ϣ�����佫����ǰ�佫��
		if ( false == ClanDBProcessor::getInstance().updateClanDataInfo(pSClanPtr->getData()) )
		{
			DYNAMIC_ASSERT_LOG(0, "�佫��������DBʧ��");
			//�˳���½
			return CreateGenrealResult_Error_DB;
		}

		//���͸��ͻ����佫��Ϣ�����ɿ��ǲ�����
		//֪ͨ�ͻ��˴����������档���ɿ��ǲ�����
		PlayerNetPacketProcesser::getInstance().sendPlayerCharacterToClient(id, pSPlayerCharacterPtr.getPointer());
		LoginNetPacketProcesser::getInstance().sendClientOpenClanControlUI(id);
		
		return CreateGenrealResult_Succeed;
	}
	//-----------------------------------------------------------------------------
	MG::CreateClanResult LoginManager::checkClanDataLawful( ClanData* _clandata, SPlayerPtr& pSPlayerPtr )
	{
		if ( false == SPlayerManager::getInstance().getPlayer(pSPlayerPtr, _clandata->accountId) )
		{	
			DYNAMIC_ASSERT_LOG(0, "�Ҳ������");
			//�˳���½
			return CreateClanResult_NoPlayer;
		}

		// ���ֵĳ��ȡ�
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
			DYNAMIC_ASSERT_LOG(0, "�Ҳ������");
			//�˳���½
			return CreateGenrealResult_Error_NotPlayer;
		}

		// ���ֵĳ��ȡ�
		Int nLength = _PlayerCharacterData->charSurName.length();
		if ( nLength <= 0  ||  nLength > MAX_CHARACTER_NAME_LEN )
			return CreateGenrealResult_Error_Name;

		nLength = _PlayerCharacterData->mName.length();
		if ( nLength <= 0  ||  nLength > MAX_CHARACTER_NAME_LEN )
			return CreateGenrealResult_Error_Name;
	}
}