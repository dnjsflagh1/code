/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "LoginNetPacketProcesser.h"
#include "LoginManager.h"
#include "CPlayer.h"
#include "CPlayerCharacter.h"
#include "UICharacterLogin.h"
#include "UISelectServer.h"
#include "UIAccountLogin.h"
#include "ClientMain.h"
#include "UIClanControl.h"
#include "UIClanCreate.h"
#include "UICreateCharacter.h"
#include "UIManage.h"
#include "CSceneManager.h"
#include "UIMessageBox.h"
#include "UIManage.h"
#include "CItemManager.h"
#include "UIGenrealPicture.h"
#include "GameSoundManager.h"
#include "UIYesNoMsgBox.h"
#include "UILoginLineUp.h"
#include "GameMain.h"
#include "LoginScreen.h"
#include "VersionSwitch.h"
#include "UIClanInfo.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------------
    LoginManager::LoginManager()
        :mLoginState( LS_IDLE )
        ,mPasswordErrorNum(0)
        ,mPasswordErrorMax(0)
    {
    }
    
    //--------------------------------------------------------------------------------
    LoginManager::~LoginManager()
    {
    }

    //--------------------------------------------------------------------------------
    void LoginManager::start()
    {
        mLoginState = LS_SEL_SERVER;

        UISelectServer::getInstance().openGui();
        UISelectServer::getInstance().addServer();
    }

    //--------------------------------------------------------------------------------
    void LoginManager::restore()
    {
        mLoginState = LS_SEL_SERVER;

        //CPlayer::getInstance().restore();
		UIAccountLogin::getInstance().closeGui();
        UISelectServer::getInstance().openGui();
        //CItemManager::getInstance().unInitialize();
        //UIManager::getInstance().restore();
    }

    //--------------------------------------------------------------------------------
    void LoginManager::startAccountLogin()
    {
        mLoginState = LS_LOGIN_ACCOUNT;

        UISelectServer::getInstance().closeGui(); 
        UIAccountLogin::getInstance().openGui();

		//����������
		//GameSoundManager::getInstance().play(10001);
    }

    //--------------------------------------------------------------------------------
    void LoginManager::loginToLoginServer(Str16& accName, Str16& accPsw)
    {
        CPlayer::getInstance().setName( accName.c_str() );
        CPlayer::getInstance().setPassword( accPsw.c_str() );

        LoginNetPacketProcesser::getInstance().sendLoginPacketToLoginServer(accName.c_str(), accPsw.c_str(),CLIENT_VERSION_NUMBER);
    }

    //--------------------------------------------------------------------------------
    void LoginManager::onLoginToLoginServerFailed( I8 errorResult )
    {
        //����������ʾ, 
        //���ȷ�����½����ʺŵ�¼����
        //�����������������벻��ȷ���رտͻ��ˡ�
        Char16  errorMsg[64] = L"";
        MGStrOp::sprintf(errorMsg, _countof(errorMsg), L"loginserverfailerror%d", errorResult);
      
        UIMessageBox::getInstance().showHint(
                                        L"loginserverfail", L"loginserverfailtitle", L"loginserverfailtitle=", 
                                        L"loginserverfail", errorMsg, errorMsg,
                                        this, onClickMsgBoxLoginFailError
                                            );
    }

    //--------------------------------------------------------------------------------
    void LoginManager::onLoginToLoginServerSuccessed( CChar* frontSvrIP, I32 frontSvrPort )
    {
		UIAccountLogin::getInstance().closeGui();

        mFrontServerIp = frontSvrIP;
        mFrontServerPort = frontSvrPort;
        
        loginToFrontServer();
    }
    
    //--------------------------------------------------------------------------------
    void LoginManager::loginToFrontServer()
    {
        NetAddress addr(mFrontServerIp.c_str(),mFrontServerPort);
        if ( ClientNetApplyManager::getInstance().connectFrontServer(addr) )
        {
            CChar16* accName = CPlayer::getInstance().getName().c_str();
            CChar16* accPsw = CPlayer::getInstance().getPassword().c_str();
            LoginNetPacketProcesser::getInstance().sendLoginPacketToFrontServer(accName,accPsw);
        }else
        {
            //����������ʾ
            UIMessageBox::getInstance().showHint(
                L"loginserverfail", L"loginserverfailtitle", L"loginserverfailtitle",
                L"loginserverfail", L"loginserverfailerror3", L"loginserverfailerror3",
                this, onClickMsgBoxLoginFailError
                );
        }
    }
    
    //--------------------------------------------------------------------------------
    void LoginManager::onRecvLoginToFrontServerResult( I8 result, PlayerIdType accountId )
    {
        if ( result==LCFT_LOGIN_SUCCESS )
        {
            mLoginState = LS_READY_GAME;

            //�Ͽ����������
            ClientNetApplyManager::getInstance().disconnectLoginServer();

            //׼��������Ϸ
			UIManager::getInstance().closeAllLayout();

			//������ҵ��˺�ID
			CPlayer::getInstance().setAccountID(accountId);

        }
		else if(LCFT_LOGIN_FAIL == result)
        {
            //����������ʾ
            GameMain::getInstance().stopAndRestore();
        }
		else
		{
			//δ֪����
			DYNAMIC_ASSERT(0);
		}
    }

    //--------------------------------------------------------------------------------
    void LoginManager::onLoginServerDisconnect()
    {
        if ( mLoginState == LS_LOGIN_ACCOUNT )
        {
            restore();
        }
    }
    //--------------------------------------------------------------------------------
    void LoginManager::openClanCreateUI()
    {
		//UISelectServer::getInstance().closeGui();
		//UIAccountLogin::getInstance().closeGui();
		//
		UIClanCreate::getInstance().openGui();
    }
    //--------------------------------------------------------------------------------
    void LoginManager::openClanControlUI()
    {
		CPlayerCharacter* playerCharacter = NULL;

		CClan* clan = CPlayer::getInstance().getActiveClan();
		if ( clan )
		{				
			playerCharacter = clan->getMainGenreal();	
		}

		if ( playerCharacter )
		{
			DYNAMIC_ASSERT(false == clan->getPlayerCharacterList()->empty());
			// �����Ѿ�ѡ��������, ѡ������UI����
			UIManager::getInstance().closeAllLayout();
			UIClanControl::getInstance().openGui();
		}
		else
		{
			DYNAMIC_ASSERT(true == clan->getPlayerCharacterList()->empty());
			// ���û������, ���ʹ����佫����
			UIManager::getInstance().closeAllLayout();
			UIClanControl::getInstance().joinGame();
		}
    }
    //--------------------------------------------------------------------------------
    void LoginManager::handleCreateClanResult( CreateClanResult index )
    {
        if ( index != CreateClanResult_Succeed )
        {
            Char16  errorMsg[64] = L"";
            MGStrOp::sprintf(errorMsg, _countof(errorMsg), L"createclanerror%d", index);
            UIMessageBox::getInstance().showHint(
                L"createclanfail", L"createclanfailtitle", L"createclanfailtitle",
                L"createclanfail", errorMsg, errorMsg,
                NULL, NULL
                );
        }
		else
		{
			;
		}
        
    }
    //--------------------------------------------------------------------------------
    void LoginManager::handleClanDeleteResult( DeleteClanResult result )
    {
        switch ( result )
        {
        case DeleteClanResult_Succeed:
			//Char16 msg[64];
			//swprintf_s(msg, _countof(msg), L"deleteclanerrok%d", result);
			{	

				UIClanControl::getInstance().closeGui();

				//��ΪloadCreateClanScene�л��UISelectServer�򿪣�
				//�����ֶ��ر���
				LoginScreen::getInstance().loadCreateClanScene();
				UISelectServer::getInstance().closeGui();
                //��Ҫ����佫��Ϣ
				UIClanInfo::getInstance().restore();
				UIClanCreate::getInstance().openGui();
			}
            break;
        case DeleteClanResult_PswdError:
            break;
        case DeleteClanResult_ClanUnexist:
            break;
        case DeleteClanResult_ClanOndelete:
            break;
        case DeleteClanResult_OtherError:
            break;
        default:
            break;
        };
    }
    //--------------------------------------------------------------------------------
    void LoginManager::sendToFrontServerDeleteClan( U64 clanId )
    {
        LoginNetPacketProcesser::getInstance().sendDeleteClanToFrontServer(clanId);
    }
    //--------------------------------------------------------------------------------
    void LoginManager::sendToFrontServerCreateClan( CClan* pClan )
    {
        LoginNetPacketProcesser::getInstance().sendClanInfoToFrontServer( pClan );
    }
    //--------------------------------------------------------------------------------
    void LoginManager::handleCreateGenrealResult( CreateGenrealResult index, PlayerCharacterIdType genrealID )
    {
        switch ( index )
        {
        case CreateGenrealResult_Succeed:
            {   
				LoginManager::getInstance().openClanControlUI();
            }
            break;
        case CreateGenrealResult_Error_NotPlayer:
		case CreateGenrealResult_Error_NotClan:
		case CreateGenrealResult_Error_Memory:
		case CreateGenrealResult_Error_DB:
            {
                DYNAMIC_ASSERT(0);
                //���⴦��
            }
            break;
        default:
            break;
        };
    }
    //--------------------------------------------------------------------------------
    void LoginManager::handleGenrealInfo()
    {
        UICreateCharacter::getInstance().closeGui();
        UIClanControl::getInstance().closeGui();      
    }
    //--------------------------------------------------------------------------------
    void LoginManager::sendToFrontServerJoingame()
    {
        LoginNetPacketProcesser::getInstance().sendJoingameToFrontServer();
    }
    //--------------------------------------------------------------------------------
    void LoginManager::sendToFrontServerCreateGenreal(U32 resID, PlayerCharacterData* pPlayerCharacterData )
    {
        LoginNetPacketProcesser::getInstance().sendCreateGenrealToFrontServer(resID,pPlayerCharacterData);
    }

    void LoginManager::onClickMsgBoxLoginFailError( void* user )
    {
        if (  user )
        {
            UIMessageBox::getInstance().closeGui();
           // UIAccountLogin::getInstance().openGui();
        }
    }
    //--------------------------------------------------------------------------------
    void LoginManager::sendToFrontServerExitgame(  )
    {
        LoginNetPacketProcesser::getInstance().sendToFrontServerExitgame();
    }
    //--------------------------------------------------------------------------------
    void LoginManager::openGenrealCreateUI()
    {
		UIManager::getInstance().closeAllLayout();
        UICreateCharacter::getInstance().openGui();
    }
    //--------------------------------------------------------------------------------
    /*void LoginManager::handleSelectClanResult( SelectClanResult index )
    {
        Bool isSuc = true;
        if ( SelectClanResult_Succeed != index )
        {
            isSuc = false;
            Char16 msg[64];
            swprintf_s(msg, _countof(msg), L"selectclanerror%d", index);
            UIMessageBox::getInstance().showHint(
                            L"clanControl", L"selectclanfailtitle", L"selectclanfailtitle"
                            , L"clanControl", msg, msg
            );
        }

    }*/
    //--------------------------------------------------------------------------------
    void LoginManager::sendToFrontServerSelectClan( U64 clanId )
    {
  //      LoginNetPacketProcesser::getInstance().sendSelectClanToFrontServer(clanId);
    }
	 //--------------------------------------------------------------------------------
	//void LoginManager::handleClientLoginQueueInfo( Byte type, I32 waitAccount )
	//{
	//   
	//	switch (type)
	//	{
	//	case login_line_up_busy:
	//		{

	//			UILoginLineUp::getInstance().adjustUI(LINE_UP_TYPE_BUSY);
	//			Str16 waitAccountStr;
	//			MGStrOp::toString(waitAccount,waitAccountStr);
	//			UILoginLineUp::getInstance().setRanKed(waitAccountStr);
	//			UILoginLineUp::getInstance().openGui();
	//		}
	//		break;
	//	case login_line_up_full:
	//		{
	//			UILoginLineUp::getInstance().adjustUI(LINE_UP_TYPE_FULL);
	//			UILoginLineUp::getInstance().openGui();
	//		}
	//		
	//		break;
	//	default:
	//		{
	//			// TODO: ��Ҫ�Ŷ�UI ��ʱ�������Ŷ�UI����
	//			UILoginLineUp::getInstance().adjustUI(LINE_UP_TYPE_BUSY);
	//			Str16 waitAccountStr;
	//			MGStrOp::toString(waitAccount,waitAccountStr);
	//			UILoginLineUp::getInstance().setRanKed(waitAccountStr);
	//			UILoginLineUp::getInstance().openGui();
	//		}
	//	}
	//}
}