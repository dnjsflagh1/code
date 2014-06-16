/******************************************************************************/
#ifndef _GMTOOLMANAGER_H_
#define _GMTOOLMANAGER_H_
/******************************************************************************/
#include "MainForm.h"
#include "LoginForm.h"
#include "LoadingForm.h"
#include "GMClientInterface.h"
/******************************************************************************/

namespace MG {

    /******************************************************************************/
    public ref class GMFormSet
    {
    public:
        static MainForm^    MAIN_FORM;
        static LoginForm^   LOGIN_FORM;
        static LoadingForm^ LOADING_FORM;
		//true guest,  false gm
#ifdef GUESTTOOL
        static BOOL bGMorGuestFlag = true;
#else
        static BOOL bGMorGuestFlag = false;
#endif
    };
    
    /******************************************************************************/
    class GMToolManager
    {
    public:
        SINGLETON_INSTANCE(GMToolManager)

    public: 
		/** UI Request  */
        void        loadMainFormStaticConfig();
            
    public: 
		/** GMClient Callback  */

        //log
        static void     gcCallback_Log(char* str);
        static void     gcCallback_ErrorMessage(char* str);
        static void     gcCallback_WarningMessage(char* str);
        static void     gcCallback_HintMessage(char* str);

        /*//account
        static void     gcCallback_UpdateAllGM();
        static void     gcCallback_UpdateGM(ULONGLONG gm_id);

        //system
        static void     gcCallback_Disconnected(DWORD reason);

        //server
        static void     gcCallback_updateGameServer(IGameServerDataForGM*data);
        static void     gcCallback_AddRegion(int id, char* str);

        //message
        static void     gcCallback_recvChatLog(void* ptr);
        static void     gcCallback_recvChatForGM(void* ptr);

        //forbidden chat
        static void     gcCallback_UpdateAllForbiddenChat();
        //forbidden login
        static void     gcCallback_UpdateAllForbiddenLogin();

		static void		gcCallback_UpdateAllTransparent();
        //closed npc
        static void     gcCallback_UpdateAllClosedNpc();

        //set announcement
        static void     gcCallback_UpdateAllAnnouncement();

		//gm player
		static void		gcCallback_UpdateGMPlayer();*/

    public:
        GMToolManager();
        ~GMToolManager();
        IGMClient*      getGMClient(){return GMClientInterface;}
        BOOLEAN         initialize();
        BOOLEAN         run();
        BOOLEAN         uninitialize();
    public:
        //IPlayerDataSetForGM::DataSetList    playerList;
        //INpcDataSetForGM::DataSetList       npcList;
        //ItemTypeDataSetForGM::DataSetList   itemTypeList;

    private:
        IGMClient*  GMClientInterface ;
        DllLoader   mDllLoader;
        BOOLEAN     mLoadedStaticConfig;
    };

}

/******************************************************************************/
#endif //_GMTOOLMANAGER_H_

