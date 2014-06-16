//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\CenterServer\Include\SCampaignManager.h
//        Author: yuanlinhu
//          Date: 2012-5-14
//          Time: 15:24
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-5-14      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _S_PVE_MEMBER_H_
#define _S_PVE_MEMBER_H_
/******************************************************************************/

#include "CenterServerPreqs.h"

/******************************************************************************/

/******************************************************************************/
namespace MG
{
	/**********************************************************************/
	class SPveMember
	{
	public:
		explicit SPveMember(Pve_Position position);
		~SPveMember();

		void		setFrontServerNetId(NetIdType netId);
		void		setClientNetId(NetIdType netId);
		void		setAccountId(AccountIdType accountId);
		void		init(Int charIcon, Int level, const Char16* charName);

		NetIdType		getFrontServerNetId() const;
		NetIdType		getClientNetId() const;
		AccountIdType	getAccountId() const;
		Pve_Position	getPosition() const;
		Int				getCharIcon() const;
		Int				getLevel() const;
		Str16&			getCharName();

	private:
		NetIdType		mFrontServerNetId;
		NetIdType		mClientNetId;
		AccountIdType	mAccountId;
		Pve_Position	mPosition;
		Int				mCharIcon;					//Í·Ïñ
		Int				mLevel;
		Str16			mCharName;

	private:
		SPveMember();
	};
}

#endif	//_S_PVE_MEMBER_H_