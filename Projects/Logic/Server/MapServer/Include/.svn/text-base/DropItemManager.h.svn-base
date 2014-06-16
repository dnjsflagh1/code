//*************************************************************************************************************
#ifndef _H_DROP_ITEM_MANGER_
#define _H_DROP_ITEM_MANGER_
//*************************************************************************************************************
#include "MapServerPreqs.h"
//*************************************************************************************************************
namespace MG
{
	struct dropItemData
	{
		U32		index;
		U32		itemTempId;
		U32		num;
		Vec2	pos;
		U64		disappearTime;				//消失时间
	};
	//-----------------------------------------------------------------------------------------------
	class DropItemManager
	{
	public:
		DropItemManager(){;}
		~DropItemManager();

		void		update();

		void				setRegionObject(SRegionObjectBase* regionObj);
		SRegionObjectBase*	getRegionObject();

	public:
		//地图的所有人都获得此奖励  ylh
		void		handleRewardItemInRegion(SRegionObjectBase* regionObject, U32 groupItemId);
		void		handleRewardItem(AccountIdType accountId, PlayerCharacterIdType playerCharId, U32 groupItemId );
		void		handleDropItemMonster( U32 randItemId, SRegionObjectBase* regionObject, Vec3& pos, SCharacter* murderer);
		void		handleCheckRewardItem(SPlayer* pSPlayer, PlayerCharacterIdType playerCharId, U32 groupItemId);
		void		handleCheckPickItem(SPlayerCharacter* pSPlayerCharacter, SPlayer* pSPlayer, PlayerCharacterIdType playerCharId, U32 index);

	public:
		Bool		getDropItemData( U32 index, U32& itemTmpId, U32& num );
		Bool		getRewardItem(PlayerCharacterIdType playerCharId);

	private:
		void		clear();

	private:
		//ylh  临时std::vector<ItemNum>
		void		checkMoneyAndAddExpToFrontServer(std::vector<ItemNum>* tempVectorDropItem, SCharacter* playerCharacter);

	private:
		std::map<U32, dropItemData*> mMapDropItemData;
		std::map<PlayerCharacterIdType, U32>  mMapRewardItem;
		SRegionObjectBase*				mRegionObject;				//所属的区域

	};
}
//*************************************************************************************************************
#endif
//*************************************************************************************************************