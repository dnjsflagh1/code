/******************************************************************************/
#include "stdafx.h"
#include "LoginNetPacketProcesser.h"
#include "DbServerMain.h"
#include "ServerDllInterface.h"
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
	Bool LoginNetPacketProcesser::processLoginServerPacket( I32 id, NetEventRecv* packet )
	{
		if(packet->getChannel() == GNPC_DB)
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_DB_S2D_SEL_ACCOUNT:
				onLoginServerSelAccount(id,(PT_DB_S2D_SEL_ACCOUNT_DATA*)data->data);
				break;
			}
			return true;
		}
		return false;

	}

	void LoginNetPacketProcesser::onLoginServerSelAccount( I32 id, PT_DB_S2D_SEL_ACCOUNT_DATA* data )
	{
		
	}

	void LoginNetPacketProcesser::sendSelAccountResultToLoginServer( PackAccountSelRelultData* data,I32 accCount )
	{

	}
}