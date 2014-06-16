/******************************************************************************/

#include "stdafx.h"
#include "SPveRoom.h"


/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	SPveRoom::SPveRoom(AccountIdType accountId, const Char16* pveRoomName)
		:mCreatorAccountId(accountId)
		,mPveRoomName(pveRoomName)
		,mRoomId(accountId)
		,mMemberNum(0)
	{

	}

	//-----------------------------------------------------------------------------
	SPveRoom::~SPveRoom()
	{

	}

	Int SPveRoom::getRoomId() const
	{
		return mRoomId;
	}

	AccountIdType SPveRoom::getCreatorAccountId() const
	{
		return mCreatorAccountId;
	}

	Str16& SPveRoom::getPveRoomName()
	{
		return mPveRoomName;
	}

	RegionIdType SPveRoom::getTargetRegionId() const
	{
		return mTargetRegionId;
	}

	void SPveRoom::setTargetRegionId( RegionIdType regionId )
	{
		mTargetRegionId = regionId;
	}

	void SPveRoom::setCreatorName(const Char16* charName)
	{
		mCreatorName = charName;
	}

	Str16& SPveRoom::getCreatorName()
	{
		return mCreatorName;
	}

	Int SPveRoom::getMemberNum() const
	{
		return mMemberNum;
	}

	SPveMember* SPveRoom::addMember( AccountIdType accountId)
	{
		
		Pve_Position targetPos = Pve_Position_Init;
		for (Int pos = Pve_Position_1; pos != Pve_Position_Max; ++pos)
		{
			if(NULL == mMemberList.getData((Pve_Position)pos))
			{
				targetPos = (Pve_Position)pos;
				break;
			}
		}

		DYNAMIC_ASSERT(targetPos > Pve_Position_Init && targetPos < Pve_Position_Max);

		SPveMember* newMember = mMemberList.createOrRetrieve<Pve_Position>(targetPos, targetPos);
		DYNAMIC_ASSERT(NULL != newMember);
		newMember->setAccountId(accountId);

		mMemberNum++;
		return newMember;
	}

	SPveMember* SPveRoom::getMember(const AccountIdType accountId)
	{
		std::map<Pve_Position, SPveMember*>* memberList = mMemberList.getDataSet();
		for (std::map<Pve_Position, SPveMember*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
		{
			if (iter->second->getAccountId() == accountId)
			{
				return iter->second;
			}
		}

		return NULL;
	}

	Bool SPveRoom::hasMember(const AccountIdType accountId)
	{
		return (NULL != getMember(accountId));
	}

	void SPveRoom::delMember(const AccountIdType accountId)
	{
		std::map<Pve_Position, SPveMember*>* memberList = mMemberList.getDataSet();
		for (std::map<Pve_Position, SPveMember*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
		{
			if (iter->second->getAccountId() == accountId)
			{
				mMemberList.destroy(iter->first);
				mMemberNum--;
				return;
			}
		}
		
	}
	std::map<Pve_Position, SPveMember*>* SPveRoom::getMemberList()
	{
		return mMemberList.getDataSet();
	}
}
