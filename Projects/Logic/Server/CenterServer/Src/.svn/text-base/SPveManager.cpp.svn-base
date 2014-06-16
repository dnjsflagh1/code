/******************************************************************************/

#include "stdafx.h"
#include "SPveManager.h"


/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	SPveManager::SPveManager()
	{

	}

	//-----------------------------------------------------------------------------
	SPveManager::~SPveManager()
	{

	}

	std::map<AccountIdType, SPveRoom*>* SPveManager::getPveRoomList()
	{
		return mPveRoomManager.getDataSet();
	}
	
	SPveRoom* SPveManager::createPveRoom(AccountIdType accountId, const Char16* pveRoomName)
	{
		SPveRoom* newRoom = mPveRoomManager.createOrRetrieve<AccountIdType, const Char16*>(accountId, accountId, pveRoomName);
		DYNAMIC_ASSERT(NULL != newRoom);
		return newRoom;
	}

	SPveRoom* SPveManager::getPveRoom(AccountIdType accountId)
	{
		return mPveRoomManager.getData(accountId);
	}

	SPveRoom* SPveManager::popPveRoom(AccountIdType accountId)
	{
		return mPveRoomManager.popData(accountId);
	}

	void SPveManager::delPveRoom(AccountIdType accountId)
	{
		mPveRoomManager.destroy(accountId);
	}
}
