/******************************************************************************/

#include "stdafx.h"
#include "SPveMember.h"


/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	SPveMember::SPveMember(Pve_Position position)
		:mFrontServerNetId(0)
		,mClientNetId(0)
		,mAccountId(0)
		,mPosition(position)
		,mCharIcon(0)
	{
		DYNAMIC_ASSERT(position > Pve_Position_Init && position < Pve_Position_Max);
	}

	//-----------------------------------------------------------------------------
	SPveMember::~SPveMember()
	{

	}

	void SPveMember::setFrontServerNetId(NetIdType netId)
	{
		mFrontServerNetId = netId;
	}

	void SPveMember::setClientNetId(NetIdType netId)
	{
		mClientNetId = netId;
	}

	void SPveMember::setAccountId(AccountIdType accountId)
	{
		mAccountId = accountId;
	}


	NetIdType SPveMember::getFrontServerNetId() const
	{
		return mFrontServerNetId;
	}

	NetIdType SPveMember::getClientNetId() const
	{
		return mClientNetId;
	}

	AccountIdType SPveMember::getAccountId() const
	{
		return mAccountId;
	}

	Pve_Position SPveMember::getPosition() const
	{
		return mPosition;
	}

	void SPveMember::init(Int charIcon, Int level, const Char16* charName)
	{
		mCharIcon = charIcon;
		mLevel	  = level;
		mCharName = charName;
	}

	Int SPveMember::getCharIcon() const
	{
		return mCharIcon;
	}

	Int SPveMember::getLevel() const
	{
		return mLevel;
	}

	Str16& SPveMember::getCharName()
	{
		return mCharName;
	}
}
