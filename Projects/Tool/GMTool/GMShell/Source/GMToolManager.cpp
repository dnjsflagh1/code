

/******************************************************************************/
#include "stdafx.h"
#include "GMToolManager.h"
/******************************************************************************/
using namespace MG;

/******************************************************************************/
//class GMToolManager 
/******************************************************************************/
GMToolManager::GMToolManager()
    :mLoadedStaticConfig(false)
 /*   ,GMClientInterface(NULL)
    ,EEWrapperInterface(NULL)*/
{
}
//-----------------------------------------------------------------------------
GMToolManager::~GMToolManager()
{

}
//-----------------------------------------------------------------------------
BOOLEAN GMToolManager::initialize()
{
    //init GlobleParameter
    GlobleParameter::getInstance();

    // Load GMClient.dll
    GET_GMClIENT_INTERFACE_PROC Proc_GetGMClient;
#ifdef _DEBUG
	if (mDllLoader.load(L"GMClient_d.dll",false)) 
#else
	if (mDllLoader.load(L"GMClient.dll",false)) 
#endif // _DEBUG
    { 
        Proc_GetGMClient = (GET_GMClIENT_INTERFACE_PROC) mDllLoader.getProcAddress("GET_GMCLIENT_INTERFACE"); 
        if (NULL != Proc_GetGMClient) 
        {
            GMClientInterface = (IGMClient*)Proc_GetGMClient(); 
            if (GMClientInterface==NULL)
            {
                Utility::showErrorMessage("Load GMClientInterface Failed!");
                return FALSE;
            }
        }else
        {
            Utility::showErrorMessage("Don't Find GMClientInterface Entry!");
            return FALSE;
        }
    }else
    {
        Utility::showErrorMessage("Don't Load DLL\\GMClient.DLL!");
        return FALSE;
    }
    
    //set native text
    if ( GMClientInterface->setNativeTextConfig(L"GMText.ini") == FALSE )
    {
        Utility::showErrorMessage("Don't Load GMText.ini!");
        return FALSE;
    }
    
    //set msg out callback
    GMClientInterface->setLogOut( gcCallback_Log );
    GMClientInterface->setWarningMessageOut( gcCallback_WarningMessage );
    GMClientInterface->setErrorMessageOut( gcCallback_ErrorMessage );
    GMClientInterface->setHintMessageOut( gcCallback_HintMessage );
    
    // Initialize GMClientInterface
    BOOLEAN initRlt = GMClientInterface->initialize(L"GMTool.ini");
    if ( initRlt == FALSE )
    {
        Utility::showErrorMessage("Initialize GMClientInterface Failed!");
        return FALSE;
    }

    // Initialize Window
    //// Enabling Windows XP visual effects before any controls are created
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false); 

    GMFormSet::MAIN_FORM    = gcnew MainForm();
    GMFormSet::LOGIN_FORM   = gcnew LoginForm();
    GMFormSet::LOADING_FORM = gcnew LoadingForm();
    
    GMFormSet::MAIN_FORM->CreateControl();
    GMFormSet::LOGIN_FORM->CreateControl();
    GMFormSet::LOADING_FORM->CreateControl();
    
    //GMFormSet::MAIN_FORM->CheckForIllegalCrossThreadCalls = false;
    //GMFormSet::LOGIN_FORM->CheckForIllegalCrossThreadCalls = false;
        
    /*GMFormSet::LOADING_FORM->loadGameTextConfig();
    GMFormSet::LOGIN_FORM->loadGameTextConfig();
    GMFormSet::MAIN_FORM->loadGameTextConfig();*/

    //set callback
    /*GMClientInterface->getMessageManager()->setChatLogCallback(gcCallback_recvChatLog);
    GMClientInterface->getMessageManager()->setChatForGMCallback(gcCallback_recvChatForGM);
    GMClientInterface->getMessageManager()->setUpdateAllAnnouncementCallback(gcCallback_UpdateAllAnnouncement);


    GMClientInterface->getServerManager()->setAddRegionCallback(gcCallback_AddRegion);
    GMClientInterface->getServerManager()->setUpdateGameServerCallback(gcCallback_updateGameServer);

    GMClientInterface->getSystemManager()->setDisconnectedCallback( gcCallback_Disconnected );
    GMClientInterface->getSystemManager()->setUpdateAllClosedNpcCallback( gcCallback_UpdateAllClosedNpc );

    GMClientInterface->getGMManager()->setUpdateAllGMCallback( gcCallback_UpdateAllGM );
    GMClientInterface->getGMManager()->setUpdateGMCallback( gcCallback_UpdateGM );

    GMClientInterface->getPlayerManager()->setUpdateAllForbiddenChatCallback( gcCallback_UpdateAllForbiddenChat );
    GMClientInterface->getPlayerManager()->setUpdateAllForbiddenLoginCallback( gcCallback_UpdateAllForbiddenLogin );
	GMClientInterface->getPlayerManager()->setUpdateAllForbiddenTransparentCallback( gcCallback_UpdateAllTransparent );
    GMClientInterface->getPlayerManager()->setUpdateAllGMPlayeCallback( gcCallback_UpdateGMPlayer );*/
    return TRUE;
 }

//-----------------------------------------------------------------------------
BOOLEAN GMToolManager::run()
{
    //// Create the main window and run it
    Application::Run(GMFormSet::LOGIN_FORM);
    return TRUE;
}
//-----------------------------------------------------------------------------
BOOLEAN GMToolManager::uninitialize()
{
     if (GMClientInterface)
        GMClientInterface->uninitialize();

     return TRUE;
}
//-----------------------------------------------------------------------------
void GMToolManager::loadMainFormStaticConfig()
{
    if (mLoadedStaticConfig==FALSE)
    {
        //GMToolManager::getInstance().getGMClient()->loadData();
        if (GMFormSet::MAIN_FORM)
            //GMFormSet::MAIN_FORM->loadGameData();
        mLoadedStaticConfig = true;
    }
}

//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_Log(char* str)
{
    String^ msg = Utility::convertAnsiToString(str);
    if (GMFormSet::MAIN_FORM)
        GMFormSet::MAIN_FORM->log(msg);
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_ErrorMessage(char* str)
{
    String^ msg = Utility::convertAnsiToString(str);
    if (GMFormSet::MAIN_FORM)
        GMFormSet::MAIN_FORM->log(msg);
    Utility::showErrorMessage(msg);
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_WarningMessage(char* str)
{
    String^ msg = Utility::convertAnsiToString(str);
    if (GMFormSet::MAIN_FORM)
        GMFormSet::MAIN_FORM->log(msg);
    Utility::showWarningMessage(msg);
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_HintMessage(char* str)
{
    String^ msg = Utility::convertAnsiToString(str);
    if (GMFormSet::MAIN_FORM)
        GMFormSet::MAIN_FORM->log(msg);
    Utility::showHintMessage(msg);
}
/*//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_UpdateAllGM()
{
    if (GMFormSet::MAIN_FORM)
        GMFormSet::MAIN_FORM->refreshAllGMList();
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_UpdateGM(ULONGLONG gm_id)
{
    if (GMFormSet::MAIN_FORM)
        GMFormSet::MAIN_FORM->refreshGMList(gm_id);
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_Disconnected(DWORD reason)
{
    IGMClient* gmClient = GMToolManager::getInstance().getGMClient();
    if (GMFormSet::LOGIN_FORM)
        GMFormSet::LOGIN_FORM->quitLogin(reason);
    gmClient->showWarningMessageByC(L"System",L"server_disconnected",L"server_disconnected!");
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_updateGameServer(IGameServerDataForGM*data)
{
    if (data&&GMFormSet::MAIN_FORM)
    {
        String^ name = Utility::convertAnsiToString(data->name);
        if (data->isOnline)
        {
            GMFormSet::MAIN_FORM->addOrUpdateGameServer(data->region_id,(INT)data->id,name,data->online_count);
        }else
        {
            GMFormSet::MAIN_FORM->removeGameServer(data->region_id,(INT)data->id);
        }
    }
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_AddRegion(int id, char* str)
{
    String^ name = Utility::convertAnsiToString(str);
    if (GMFormSet::MAIN_FORM)
        GMFormSet::MAIN_FORM->addRegion(id,name);
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_recvChatLog(void* ptr)
{
    GM_NET_PlayerChatLog* data = (GM_NET_PlayerChatLog*)ptr;
    
    DWORD region_id = data->region_id;
    ULONGLONG uin   = data->uin;
    DWORD id        = data->id;
    String^name     = Utility::convertAnsiToString(data->name);
    BYTE type       = data->type;
    String^content  = Utility::convertAnsiToString(data->content);
    
    if (GMFormSet::MAIN_FORM)
	{
        GMFormSet::MAIN_FORM->addChatLog(region_id, uin,id,name,type,content);
		//test
		GMFormSet::MAIN_FORM->addChatForGM_K(region_id, uin,id,name,name,content);
		GMFormSet::MAIN_FORM->addChatForSensitiveWord_K(region_id, uin,id,name,type,content);
		GMFormSet::MAIN_FORM->addChatForReply(region_id, uin,id,name,name,content);
	}
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_recvChatForGM(void* ptr)
{
    GM_NET_PlayerChatToGM* data = (GM_NET_PlayerChatToGM*)ptr;

    DWORD       region_id   = data->region_id;
    ULONGLONG   player_uin  = data->player_uin;
    DWORD       player_id   = data->player_id;
    String^     player_name = Utility::convertAnsiToString(data->player_name);
    String^     gm_name     = Utility::convertAnsiToString(data->gm_name);
    String^     content     = Utility::convertAnsiToString(data->content);

    if (GMFormSet::MAIN_FORM)
	{
        //GMFormSet::MAIN_FORM->addChatForGM(region_id,player_uin,player_id,player_name,gm_name,content);
		GMFormSet::MAIN_FORM->addChatForGM_K(region_id,player_uin,player_id,player_name,gm_name,content);
	}
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_UpdateAllForbiddenChat()
{
    if (GMFormSet::MAIN_FORM)
        GMFormSet::MAIN_FORM->refreshAllForbiddenChatList();
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_UpdateAllForbiddenLogin()
{
    if (GMFormSet::MAIN_FORM)
        GMFormSet::MAIN_FORM->refreshAllForbiddenLoginList();
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_UpdateAllClosedNpc()
{
    if (GMFormSet::MAIN_FORM)
        GMFormSet::MAIN_FORM->refreshClosedNpcList();
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_UpdateAllAnnouncement()
{
    if (GMFormSet::MAIN_FORM)
        GMFormSet::MAIN_FORM->refreshAnnouncementList();
}
//-----------------------------------------------------------------------------
void GMToolManager::gcCallback_UpdateAllTransparent()
{
	if (GMFormSet::MAIN_FORM)
		GMFormSet::MAIN_FORM->refreshAllHiddenList();
}
//------------------------------------------------------------------------------
void GMToolManager::gcCallback_UpdateGMPlayer()
{
	if (GMFormSet::MAIN_FORM)
		GMFormSet::MAIN_FORM->refreshGMPlayerList();
}
*/