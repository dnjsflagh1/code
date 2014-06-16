/******************************************************************************/

#ifndef _GMCLIENTINTERFACE_H_
#define _GMCLIENTINTERFACE_H_

/******************************************************************************/
//#include <PlayerDataSetForGM.h>
//#include <RegionDataSetForGM.h>
//#include <ServerDataSetForGM.h>
//#include <MapDataSetForGM.h>
//#include <MapAttrDataSetForGM.h>

//#include <NpcDataSetForGM.h>
//#include <ItemDataSetForGM.h>
//#include <MessageDataSetForGM.h>
#include "GMAccountNetPacket.h"
/******************************************************************************/
typedef void* (__cdecl *GET_GMClIENT_INTERFACE_PROC)(void); 
#define DLL_ENTRY_GMCIENT_PROC GET_GMCLIENT_INTERFACE
/******************************************************************************/
//typedef void (__cdecl *IGMCLIENT_CALLBACK_GAMESERVER)(IGameServerDataForGM*); 
typedef void (__cdecl *IGMCLIENT_CALLBACK)(); 
typedef void (__cdecl *IGMCLIENT_CALLBACK_DWORD)(DWORD); 
typedef void (__cdecl *IGMCLIENT_CALLBACK_ULONGLONG)(ULONGLONG); 
typedef void (__cdecl *IGMCLIENT_CALLBACK_BOOLEAN)(bool); 
typedef void (__cdecl *IGMCLIENT_CALLBACK_PTR)(void*); 
typedef void (__cdecl *IGMCLIENT_CALLBACK_STR)(char*); 
typedef void (__cdecl *IGMCLIENT_CALLBACK_ID_STR)(int,char*); 
typedef void (__cdecl *IGMCLIENT_CALLBACK_WSTR)(wchar_t*); 
/******************************************************************************/
//manager interface 
/******************************************************************************/
namespace MG
{
	class GMClientInfo;
	class IPlayerManager
	{
	public:
		/*
		typedef std::map<INT, PlayerDataSetForGM*> PlayerDataSetGroups;

		virtual IPlayerDataSetForGM*        getPlayerDataSet() = 0;
		virtual bool                        loadPlayerDataSetFromServer(PlayerDataFilterForGM& filter)=0;//block

		//@gmplayer
		virtual void                        setUpdateAllGMPlayeCallback(IGMCLIENT_CALLBACK callback) = 0; 
		virtual PlayerDataSetGroups&		getGMPlayeDataSetGroup() = 0;
		virtual PlayerDataSetForGM&         getGMPlayerDataSet(int region_id) = 0;
		//@move
		virtual GM_MOVEPLAYER_RESULT        movePlayer(DWORD region_id,ULONGLONG uin,DWORD id,const char* name,
		float x,float y,float z,BOOLEAN isOffset,
		BOOLEAN isJumpMap,IMapTypeDataForGM* map_group,
		WORD map_id,
		BOOLEAN isJumpMaze, BYTE maze_x, BYTE maze_y, 
		WORD jump_id)=0;
		virtual GM_MOVEPLAYER_RESULT        movePlayerToPlayer(DWORD region_id,ULONGLONG uin,DWORD id,const char* name,
		ULONGLONG to_player_uin,DWORD to_player_id,const char* to_player_name)=0;
		virtual GM_MOVEPLAYER_RESULT        movePlayerToNpc(DWORD region_id,ULONGLONG uin,DWORD id,const char* name,
		DWORD to_npc_id,const char* to_npc_name)=0;

		virtual GM_MOVEPLAYER_RESULT        movePlayerNew(DWORD region_id,ULONGLONG uin,DWORD id,const char* name,DWORD to_map_id,DWORD to_jmp_pt_id) = 0;

		//forbidden chat
		virtual GM_FORBIDDEN_CHAT_RESULT    forbiddenChat(DWORD region_id,ULONGLONG uin,DWORD id,const char* name,DWORD minutes,const char* reason=0)=0;
		virtual void                        setUpdateAllForbiddenChatCallback(IGMCLIENT_CALLBACK callback) = 0;
		virtual PlayerDataSetGroups&        getForbiddenChatPlayerDataSetGroup() = 0;
		virtual PlayerDataSetForGM&         getForbiddenChatPlayerDataSet(int region_id) = 0;

		//forbidden login
		virtual GM_FORBIDDEN_LOGIN_RESULT   forbiddenLogin(DWORD region_id,ULONGLONG uin,const char* account_name,DWORD hour,const char* reason=0)=0;
		virtual void                        setUpdateAllForbiddenLoginCallback(IGMCLIENT_CALLBACK callback) = 0;
		virtual PlayerDataSetGroups&        getForbiddenLoginPlayerDataSetGroup() = 0;
		virtual PlayerDataSetForGM&         getForbiddenLoginPlayerDataSet(int region_id) = 0;

		//forbidden transparents
		virtual void                        setUpdateAllForbiddenTransparentCallback(IGMCLIENT_CALLBACK callback) = 0;
		virtual PlayerDataSetGroups&		getForbiddenTransparentPlayerDataSetGroup() = 0;
		virtual PlayerDataSetForGM&         getForbiddenTransparentPlayerDataSet(int region_id) = 0;

		virtual GM_SET_TRANSPARENT_RESULT   setTransparent(DWORD region_id, ULONGLONG uin,DWORD id, const char* name, BOOLEAN valid, DWORD hour,const char* reason=0)=0;
		virtual GM_SET_GMPLAYER_RESULT      setGMPlayer(DWORD region_id, ULONGLONG uin,DWORD id,const char* name,BOOLEAN valid)=0;
		virtual GM_SEND_ITEM_RESULT         sendItem(DWORD region_id,ULONGLONG player_uin,DWORD id, const char* name, DWORD item_id,  WORD duraOrDup, DWORD attr,time_t deadline,const char* reason=0)=0;           
		virtual GM_SEND_MONEY_RESULT        sendMoney(DWORD region_id,ULONGLONG player_uin,DWORD id,const char* name,DWORD money,bool isAdd, const char* reason=0)=0;
		virtual GM_SEND_ITEM_RESULT         sendItemAll(DWORD region_id,DWORD item_id,  WORD duraOrDup, DWORD attr,time_t deadline,const char* reason=0)=0;           
		virtual GM_SEND_MONEY_RESULT        sendMoneyAll(DWORD region_id,DWORD money,bool isAdd, const char* reason=0)=0;
		virtual GM_KILL_ALL_NPC_RESULT      sendKillAllNpc(DWORD region_id, ULONGLONG uin,DWORD id,const char* name,BOOLEAN valid)=0;
		*/
	};
	class IServerManager
	{
	public:

		/*
		virtual IRegionDataSetForGM*        getRegionDataSet() = 0;
		virtual IGameServerDataSetForGM*    getGameServerDataSet(int region_id) = 0;

		virtual void                        setAddRegionCallback(IGMCLIENT_CALLBACK_ID_STR callback) = 0;
		virtual void                        setUpdateGameServerCallback(IGMCLIENT_CALLBACK_GAMESERVER callback) = 0;
		virtual void                        updateGameServerList() = 0;

		virtual int                         getRegionID(char* name) = 0;
		virtual char*                       getRegionName(int region_id) = 0;
		*/
	};
	class IGMManager
	{
	public:
		virtual std::map<U32,GMClientInfo*>*getGMDataSet() = 0;
		virtual std::map<Int,std::string>&  getAuthorityList() = 0;
		virtual Int							getAuthorityID(CChar8* name) = 0;
		virtual CChar8*						getAuthorityName(Int auId) = 0;
		virtual void                        setUpdateAllGMCallback(IGMCLIENT_CALLBACK callback)=0;
		virtual void                        setUpdateGMCallback(IGMCLIENT_CALLBACK_ULONGLONG callback)=0;

		virtual gm_account_operate_result	login(CChar8* username, CChar8* password) = 0;
		virtual void						logout() = 0;

		virtual gm_account_operate_result   createGM(CChar8* name, CChar8* password, Int au_id) = 0;
		virtual gm_account_operate_result   updateGM(Int gmId, CChar8* name, 
			Bool updatePsw, CChar8* oldPsw,CChar8* newPsw, 
			Bool updateAu,Int auId) = 0;
		virtual gm_account_operate_result   deleteGM(Int gmId, CChar8* name) = 0;

		//virtual IGMLogDataSetForSendItem*   searchLogForSendItem(IGMLogDataFilterForSendItem*filter)=0;
	};
	class ISystemManager
	{
	public:
		/* 
		typedef std::map<INT, NpcDataSetForGM*> NpcDataSetGroups;

		virtual INpcDataSetForGM*           getNpcDataSet() = 0;

		//set npc closed state
		virtual GM_SET_NPC_CLOSED_RESULT    setNpcClosed(DWORD region_id,DWORD npc_id, BOOLEAN closed, const char* reason=0)=0;
		virtual NpcDataSetForGM&            getClosedNpcDataSet(int region_id) = 0;
		virtual void                        setUpdateAllClosedNpcCallback(IGMCLIENT_CALLBACK callback)=0;

		virtual IItemTypeDataSetForGM*      getItemTypeDataSet() = 0;
		virtual IItemValueDataSetForGM*     getItemValueDataSet() = 0;
		virtual IItemValueDataSetController*getItemValueDataSetController() = 0;

		virtual IMapDataSetForGM*           getMapDataSet() =0;
		virtual IMapDataForGM*              getMapData(ULONGLONG map_id)=0;

		virtual	IMapAttrDataSetForGM*		getMapAttrDataSet() = 0;
		virtual	IMapAttrDataForGM*			getMapAttrData(ULONGLONG map_id)= 0;


		virtual IMapTypeDataSetForGM*       getCityMapDataSet() = 0;
		virtual IMapTypeDataSetForGM*       getInstanceMapDataSet() = 0;
		virtual IMapTypeDataForGM*          getCityMapData(const char* name) = 0;
		virtual IMapTypeDataForGM*          getInstanceMapData(const char* name) = 0;

		virtual GMData*                     getLocalGM() = 0;

		virtual void                        setDisconnectedCallback(IGMCLIENT_CALLBACK_DWORD callback) = 0;
		*/
	};
	class IMessageManager
	{
	public:
		/* 
		typedef std::vector<std::string>    CommonAnswerMap;
		//log
		virtual void                        setChatLogCallback(IGMCLIENT_CALLBACK_PTR callback) = 0;

		//replay
		virtual void                        setChatForGMCallback(IGMCLIENT_CALLBACK_PTR callback) = 0;
		virtual GM_REPLY_CHAT_RESULT        replyPlayerChat(DWORD region_id, ULONGLONG player_uin ,DWORD player_id, const char* player_name, const char* title, const char* reply) = 0;
		virtual CommonAnswerMap&            getCommonAnswerList() = 0;

		//@Announcement
		virtual GM_SET_ANNO_RESULT          setAnnouncement(BOOLEAN isNew,WORD region_count,WORD* region_id,BOOLEAN isOnce,ULONGLONG id,WORD play_hours,WORD play_minutes,WORD play_num,
		time_t start_time,time_t end_time, const char*title,const char*content,BOOLEAN isPause,BOOLEAN isRepeat,WORD end_play_hours,WORD end_play_minutes,WORD time_distance) = 0;
		virtual GM_SET_ANNO_RESULT          deleteAnnouncement(ULONGLONG id) = 0;
		virtual void                        setUpdateAllAnnouncementCallback(IGMCLIENT_CALLBACK callback) = 0;
		virtual AnnouncementDataSetForGM*   getAnnouncementDataSet() = 0;
		*/
	};
	/******************************************************************************/
	//GMClient interface 
	/******************************************************************************/
	class IGMClient
	{
	public:
		virtual Bool						initialize(const wchar_t* config) = 0;
		virtual Bool						uninitialize() = 0;
		virtual IPlayerManager*             getPlayerManager() = 0;
		virtual IServerManager*             getServerManager() = 0;
		virtual ISystemManager*             getSystemManager() = 0;
		virtual IMessageManager*            getMessageManager() = 0;
		virtual IGMManager*                 getGMManager() = 0;

		virtual Bool						loadData() = 0;

		virtual void                        setNativeGroupByC(const wchar_t* name) = 0;
		virtual const char*                 getNativeValueByC(const wchar_t* key,const wchar_t* default_value) = 0;

		virtual Bool						setNativeTextConfig(const wchar_t* config) = 0;

		virtual void                        setLogOut(IGMCLIENT_CALLBACK_STR callback=NULL) = 0;

		virtual void                        setErrorMessageOut(IGMCLIENT_CALLBACK_STR callback=NULL) = 0;
		virtual void                        setWarningMessageOut(IGMCLIENT_CALLBACK_STR callback=NULL) = 0;
		virtual void                        setHintMessageOut(IGMCLIENT_CALLBACK_STR callback=NULL) = 0;

		virtual void                        showErrorMessageByC(const wchar_t* group,const wchar_t* key,const wchar_t* default_value) = 0;
		virtual void                        showWarningMessageByC(const wchar_t* group,const wchar_t* key,const wchar_t* default_value) = 0;
		virtual void                        showHintMessageByC(const wchar_t* group,const wchar_t* key,const wchar_t* default_value) = 0;
		virtual void                        logByC(const wchar_t* group,const wchar_t* key,const wchar_t* default_value) = 0;

		virtual U64							getCurrTimestamp() = 0;
	};

}


/******************************************************************************/

#endif //_GMCLIENTINTERFACE_H_

