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
#ifndef _S_PVE_ROOM_H_
#define _S_PVE_ROOM_H_
/******************************************************************************/

#include "CenterServerPreqs.h"
#include "SPveMember.h"

/******************************************************************************/

/******************************************************************************/
namespace MG
{
	/**********************************************************************/
	class SPveRoom
	{
	public:
		SPveRoom(AccountIdType accountId, const Char16* pveRoomName);
		~SPveRoom();

		Int				getRoomId() const;
		AccountIdType	getCreatorAccountId() const;
		Str16&			getPveRoomName();
		RegionIdType	getTargetRegionId() const;
		void			setTargetRegionId(RegionIdType regionId);

		void			setCreatorName(const Char16* charName);
		Str16&			getCreatorName();

		Int				getMemberNum() const;

		//member的操作
		std::map<Pve_Position, SPveMember*>*		getMemberList();

		SPveMember*									addMember(AccountIdType accountId);
		SPveMember*									getMember(const AccountIdType accountId);
		Bool										hasMember(const AccountIdType accountId);
		void										delMember(const AccountIdType accountId);
		

	private:
		Int				mRoomId;
		AccountIdType	mCreatorAccountId;		//创建者的id
		Str16			mCreatorName;			//创建者的名字
		Str16			mPveRoomName;
		RegionIdType	mTargetRegionId;

		Int				mMemberNum;				//房间里的人数
	
		SimpleMapDataSetManager<Pve_Position, SPveMember>	mMemberList;

	private:
		SPveRoom();
	};
}

#endif	//_S_PVE_ROOM_H_