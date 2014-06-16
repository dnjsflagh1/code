/******************************************************************************/
#include "stdafx.h"
#include "LoginNetPacketProcesser.h"
#include "ClientManager.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	LoginNetPacketProcesser::LoginNetPacketProcesser()
	{

	}
	//--------------------------------------------------------------------------
	LoginNetPacketProcesser::~LoginNetPacketProcesser()
	{

	}
	//--------------------------------------------------------------------------
	Bool LoginNetPacketProcesser::processFrontPacket( I32 id, NetEventRecv* packet )
	{
		if(packet->getChannel() == GNPC_LOGIN)
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_LOGIN_F2A_JOINGAME:
				onRecvClientJoinGameFromFrontServer(id, (PT_LOGIN_F2A_JOINGAME_DATA*)(data->data));
				return true;
			case PT_LOGIN_F2A_EXITGAME:
				onRecvClientExitGameFromFrontServer(id, (PT_LOGIN_F2A_EXITGAME_DATA*)(data->data));
				return true;
			case PT_LOGIN_F2A_CLIENTLIST_INGAME:
				onRecvClientListInGameFromFrontServer(id, (PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA*)(data->data));
				return true;
			}
		}
		return false;

	}
	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::onRecvClientJoinGameFromFrontServer( I32 id, PT_LOGIN_F2A_JOINGAME_DATA* data )
	{
		ClientManager::getInstance().addClientObject(data->clanName,data->clientNetId,id,data->accountId);
	}
	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::onRecvClientExitGameFromFrontServer( I32 id, PT_LOGIN_F2A_EXITGAME_DATA* data )
	{
		ClientManager::getInstance().removeClientObject(data->clanName);
	}
	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::onRecvClientListInGameFromFrontServer( I32 id, PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA* data )
	{
		for (Int i = 0; i < data->count; i++)
		{
			ClientManager::getInstance().addClientObject(data->data[i].clanName,data->data[i].clientNetId,id,data->data[i].accountId);
		}
	}
	//--------------------------------------------------------------------------
}