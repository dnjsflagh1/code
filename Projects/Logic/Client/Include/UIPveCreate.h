//*************************************************************************************

#ifndef _UI_PVE_CREATE_H_
#define _UI_PVE_CREATE_H_

//*************************************************************************************

#include "ClientPreqs.h"
#include "UIObject.h"
#include "PveNetPacket.h"

//*************************************************************************************

namespace MG
{
	struct UIPveRoomInfo
	{
		Str16	strPveRoomName;
		Str16	strTargetRegionName;
		Bool	isMe;
		Int		pveRoomId;
		Str16	strPveRoomId;
		Str16	strMemberNum;

		UIPveRoomInfo()
			:isMe(false)
			,pveRoomId(0)
		{

		}
	};

	struct UIPveMemberInfo
	{
		AccountIdType	accountId;
		Int				charArtIcon;
		Str16			charName;
		Str16			charLevel;
		Pve_Position	position;
		Bool			isMe;

		UIPveMemberInfo()
			:accountId(0)
			,charArtIcon(0)
			,position(Pve_Position_Init)
			,isMe(false)
		{

		}

		void clear()
		{
			accountId = 0;
			charArtIcon = 0;
			charName = L"";
			charLevel= L"";
			position = Pve_Position_Init;
			isMe = false;
		}

		Bool empty()
		{
			if (0 == accountId ||
				0 == charArtIcon ||
				true == charName.empty() ||
				true == charLevel.empty() ||
				position == Pve_Position_Init)
			{
				return true;
			}

			return false;
		}
	};

	//-------------------------------------------------------------------------------
	class  UIPveCreate : public UIObject
	{
	public:
		UIPveCreate();
		~UIPveCreate();
		SINGLETON_INSTANCE(UIPveCreate);

	public:
		virtual void setEvent();
		virtual Bool openGui();
		virtual void restore();

	public:
		void UIReFreshTargetRegionList();
		void UIReFreshRoomList();
		void UIReFreshCreate();
		void UIReFreshMemberInfo();
		void UIReFreshMemberByPos(Pve_Position pos, UIPveMemberInfo* memberInfo);
		

		static void onClickButtonCreatePve(void* widget);
		static void onClickEnterRoom(void* widget, Int index);
		static void onClickLeaveRoom(void* widget);
		static void onClickConfirm(void* widget);

		static void onClickKick2(void* widget);
		static void onClickKick3(void* widget);
		static void onClickKick4(void* widget);
		static void onClickKick5(void* widget);

	public:
		//内存操作
		void		addPveRoom(Int addPveRoomNum, const NetPveRoomInfo* addPveRoomInfo);
		void		delPveRoom(Int roomId);
		void		clearPveRoom();

		//创建者的信息
		void		addPveMember(Int addPveMemberNum, const NetPveMemberInfo* addPveMemberInfo);
		void		modifyMemberInfo(Pve_Position pos, UIPveMemberInfo* memberInfo);
		void		delPveMember(const AccountIdType accountId);
		void		clearPveMember();

		UIPveMemberInfo*	getPveMemberByPosition(const Pve_Position position);

	private:
		Bool		isLeader();
	private:
		void		createTest();

	private:
		std::vector<UIPveRoomInfo>									mPveRoomList;
		SimpleMapDataSetManager<Pve_Position, UIPveMemberInfo>		mPveMemberList;
	};
}

#endif	//_UI_PVE_CREATE_H_