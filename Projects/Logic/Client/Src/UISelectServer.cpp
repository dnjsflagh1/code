//*************************************************************************************
#include "stdafx.h"
#include "UISelectServer.h"
#include "CSelectServerConfig.h"
#include "UIAccountLogin.h"
#include "LoginManager.h"
#include "ClientNetApplyManager.h"
#include "NetAddress.h"
#include "UIMessageBox.h"
#include "PlayerNetPacketProcesser.h"
//*************************************************************************************
namespace MG
{

	//--------------------------------------------------------------------------------
    void UISelectServer::setEvent()
    {
       init();
	   getLayout()->getButton("btn_login")->getWidget()->setMouseButtonClickEvent(onClickLogin);
    }
  /*
	//--------------------------------------------------------------------------------
    void UISelectServer::onClickServer( void* widget )
    {
        IWidget* pMenu = (IWidget*)widget;
        assert ( pMenu );

        UISelectServer::getInstance().setCurServer( pMenu->getCaption() );
    }

	//--------------------------------------------------------------------------------
    void UISelectServer::onClickButton( void* widget )
    {
        IWidget* pMenu = (IWidget*)widget;
        assert ( pMenu );

        UISelectServer::getInstance().sendServer( pMenu->getCaption() );
    }
*/
    #define MAIN_ZONE_NAME L"测试一区"
	#define MAIN_ZONE_NAME_T L"测试一区>>>"

	//--------------------------------------------------------------------------------
    void UISelectServer::addServer()
    {

        Int nCount = CSelectServerConfig::getInstance().getServerConfigNum();
		IMixList* listMainZone = getLayout()->getMixList("mlist_subzone");
		DYNAMIC_ASSERT(listMainZone);
		listMainZone->removeAllLine();
		IText* pMainZoneName = getLayout()->getText("text_mainzonename");
		DYNAMIC_ASSERT(pMainZoneName);
		pMainZoneName->getWidget()->setCaption(MAIN_ZONE_NAME_T);
        Char16 addName[32] = L"";
        //Int nheight = 0;
        for (Int i=0; i<nCount; i++)
        {
			swprintf_s(addName,32,L"server%d", i+1 );
			listMainZone->addLine(i,Str16(addName));
			IMixListRow* pListRow = listMainZone->getMixListRow(i);
            listMainZone->setClickMixListRow(onClickSubZone);
			listMainZone->setDoubleClickMixListRow(onDobuleClikSubZone);
            CSelectServerConfig::ServerConfig* serverConfig = CSelectServerConfig::getInstance().getServerConfigByIndex(i);
            assert( serverConfig );
			
			
			std::string tempIP = "";
			MGStrOp::toString(serverConfig->mServerIP.c_str(), tempIP);
			SelectServerData dataInfo;
			dataInfo.mSelectServerIp = tempIP;
			dataInfo.mSelectServerPort =  serverConfig->mPort;

            pListRow->getWidget()->setUserData(dataInfo);
			pListRow->getChildWidget(0)->getText()->setTextAlign(Center);
            pListRow->getChildWidget(0)->setCaption(serverConfig->mServerName);
			
			pListRow->getChildWidget(2)->getText()->setTextAlign(Center);
			pListRow->getChildWidget(2)->setCaption(L"56ms");

			pListRow->getChildWidget(3)->getText()->setTextAlign(Center);
			pListRow->getChildWidget(3)->setCaption(L"空闲");
        }
       
    }
 
    
	//--------------------------------------------------------------------------------
	void UISelectServer::init()
	{
		IMixList* listMainZone = getLayout()->getMixList("mlist_mainzone");
		DYNAMIC_ASSERT(listMainZone);
		
		//以后读表
		Int index = 0;
		listMainZone->addLine(index,L"testzone1");
		
		IWidget* pName = listMainZone->getMixListRow(index)->getChildWidget(0);
		pName->getText()->setTextAlign(Center);
		pName->setCaption(MAIN_ZONE_NAME);
		listMainZone->setSelectIndex(0);
		UISelectServer::getInstance().setSelectMainZoneName(MAIN_ZONE_NAME);
		addServer();
		listMainZone->setClickMixListRow(onClickMainZone);



	}
	//--------------------------------------------------------------------------------
	void UISelectServer::onClickMainZone( void* widget,Int index )
	{
		DYNAMIC_ASSERT(widget);
		UISelectServer::getInstance().addServer();
        
		//
		IMixList* listMainZone = UISelectServer::getInstance().getLayout()->getMixList("mlist_mainzone");
		DYNAMIC_ASSERT(listMainZone);
        IWidget* pName = listMainZone->getMixListRow(index)->getChildWidget(0);
        Str16 tempMainZoneName = pName->getCaption();
		UISelectServer::getInstance().setSelectMainZoneName(tempMainZoneName);
		
	}
	//--------------------------------------------------------------------------------
	void UISelectServer::onClickSubZone( void* widget,Int index )
	{
		//DYNAMIC_ASSERT(widget);
		if (widget)
		{
			IMixList* pMixList = (IMixList*)widget;
			SelectServerData* dataInfo = pMixList->getMixListRowByIndex(index)->getWidget()->getUserData()->castType<SelectServerData>();
			UISelectServer::getInstance().setSelectServerData(dataInfo->mSelectServerIp,dataInfo->mSelectServerPort);
			Str16 tempSubZone = pMixList->getMixListRowByIndex(index)->getChildWidget(0)->getCaption();
			UISelectServer::getInstance().setSelectSubZoneName(tempSubZone);

		}
        

	}
	//--------------------------------------------------------------------------------
	void UISelectServer::onDobuleClikSubZone( void* widget,Int index )
	{
		//DYNAMIC_ASSERT(widget);
		if (widget)
		{
			IMixList* pMixList = (IMixList*)widget;
			SelectServerData* dataInfo = pMixList->getMixListRowByIndex(index)->getWidget()->getUserData()->castType<SelectServerData>();
			UISelectServer::getInstance().setSelectServerData(dataInfo->mSelectServerIp,dataInfo->mSelectServerPort);
			Str16 tempSubZone = pMixList->getMixListRowByIndex(index)->getChildWidget(0)->getCaption();
			UISelectServer::getInstance().setSelectSubZoneName(tempSubZone);
			UISelectServer::getInstance().handlClickLogin();

		}


	}
	//--------------------------------------------------------------------------------
	void UISelectServer::handlClickLogin()
	{
		//Vec3 pos(103.09, 0.04, -68.59);
		//Vec3 dir(0,0,0);
		//PT_PLAYER_F2C_JUMP_REGION_DATA jump_data;
		//jump_data.regionType	= ROT_MAP_DISTRIBUTION;
		//jump_data.regionId		= 1;
		//jump_data.instanceUid	= 0;
		//jump_data.jumpResult	= PlayerJump_Success;
		//jump_data.force			= 0;
		//jump_data.pos			= ((NetVec2)pos).getData();
		//jump_data.dir			= ((NetVec2)dir).getData();
		//
		//PlayerNetPacketProcesser::getInstance().onRecvPlayerJumpMap( 1, &jump_data );
		//return;

		NetAddress addr(mSelectServerIp.c_str(),mSelectServerPort);	
		if (ClientNetApplyManager::getInstance().connectLoginServer(addr) == false)
		{
			//弹出不能连接提示
			UIMessageBox::getInstance().showHint(L"服务器无法连接!");
			return;
		}else
		{
			LoginManager::getInstance().startAccountLogin();
		}
	
	}

	void UISelectServer::setSelectServerData( Str8 selectServerIp,I32 selectServerPort )
	{
		mSelectServerIp = selectServerIp;
		mSelectServerPort = selectServerPort;

	}

	void UISelectServer::onClickLogin( void* widget )
	{
		if (widget)
		{
			UISelectServer::getInstance().handlClickLogin();
		}

	}

	MG::Str16 UISelectServer::getSelectMainZoneName() const
	{
       return mSelectMainZoneName;
	}

	MG::Str16 UISelectServer::getSelectSubZoneName() const
	{
        return mSelectSubZoneName;
	}

	void UISelectServer::setSelectMainZoneName( Str16 mainZoneName )
	{
             mSelectMainZoneName = mainZoneName;
	}

	void UISelectServer::setSelectSubZoneName( Str16 subZoneName )
	{
           mSelectSubZoneName = subZoneName;
		
	}
}