/******************************************************************************/
#include "stdafx.h"
#include "ClientMain.h"
#include "CPlayerCharacterEntity.h"
#include "CSceneManager.h"
#include "ISceneNode.h"
#include "CPlayer.h"
#include "PlayerCharacterData.h"
#include "ItemTemplate.h"
#include "CharacterList.h"
#include "CItemManager.h"
#include "GenrealEquip.h"
/******************************************************************************/

namespace MG
{
    //-----------------------------------------------------------------------
	CPlayerCharacterEntity::CPlayerCharacterEntity( IEntity* entity )
		:CCharacterSceneEntity( entity, GOT_PLAYERCHARACTER, GQT_PLAYERCHARACTER, (MG_NEW PlayerCharacterEntityData) )
		,mFlagEntity(NULL)
		,mRideActionGroup("none")
		,mWeaponActionGroup("none")
	{
	   initBindWordMap();
	}

    //-----------------------------------------------------------------------
	CPlayerCharacterEntity::~CPlayerCharacterEntity()
	{
		unInitialize();
	}

    //-----------------------------------------------------------------------
    void CPlayerCharacterEntity::initialize()
    {
        CCharacterSceneEntity::initialize();
		initializeEntity();
    }

    //-----------------------------------------------------------------------
    void CPlayerCharacterEntity::unInitialize()
    {
        destroyFlag();
        CCharacterSceneEntity::unInitialize();
    }

    //-----------------------------------------------------------------------
    void CPlayerCharacterEntity::update( Flt delta )
    {
        CCharacterSceneEntity::update(delta);

		if(mFlagEntity)
		{
			IScene* scene = ClientMain::getInstance().getScene();
			ICamera* camera = scene->getActiveCamera();
			if(camera)
			{
				Vec3 dir;
				camera->getDirection(dir);
				mFlagEntity->getSceneNode()->setDirection(Vec3(-dir.x,0,-dir.z));
			}

			mFlagEntity->getSceneNode()->setPosition(getPos());
			mFlagEntity->getSceneNode()->stickTerrain();
		}
    }

    //-----------------------------------------------------------------------
    void CPlayerCharacterEntity::initializeEntity()
    {
		//如果是玩家自己就读取背包内装备
		//如果不是就把外表装备信息全部置空

		GenrealEquip* equip = CItemManager::getInstance().getGenrealEquip( getID() );

		if ( equip || equip->getEquipItemArray()  )
		{
			PlayerItem** equipList = equip->getEquipItemArray();

			for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
			{
				if ( equipList[i] )
				{
					attachItem(equipList[i]->getItemTempID(), (ITEM_EQUIP_SLOT_TYPE)i);
				}
			} 
		}
		else
		{
			for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
			{
				attachItem(0, (ITEM_EQUIP_SLOT_TYPE)i);
			} 
		}
		
    }

	//-----------------------------------------------------------------------
	Bool CPlayerCharacterEntity::attachEntityAccessory(Str name, U32 modelID, I32 bindPoint)
	{
		IEntityAccessory* accessory = MG_NEW IEntityAccessory;

		if ( bindPoint >= ATTACH_POINT_RIGHT_HAND && bindPoint < ATTACH_POINT_RIDE + 1 )
			accessory->bindBoneName = mBindPointMap[bindPoint];

		accessory->isDepositLifeTime = true;
		accessory->isSyncAnimation = true;
		accessory->relativePosition = Vec3(0.0f,0.0f,0.0f);
		accessory->relativeQuaternion = Qua(1.0f, 0.0f, 0.0f, 0.0f);
		accessory->sceneObject = NULL;

		std::map<U32, Str>::iterator iter = mEntityAccessories.find( bindPoint );
		if ( iter != mEntityAccessories.end() )
		{
			detachEntityAccessory( iter->second.c_str() );
		}

		if ( ClientMain::getInstance().getScene()->createEntityDynamicAccessorys( mEntity, name.c_str(), modelID, SOT_ENTITY, accessory, true) )
		{
			if ( accessory->sceneObject )
			{
				mEntityAccessories[bindPoint] = accessory->sceneObject->getName();
				return true;
			}
		}

		MG_DELETE accessory;

		return false;
	}
	//-----------------------------------------------------------------------
	void CPlayerCharacterEntity::detachEntityAccessory(Str name)
	{
		 ClientMain::getInstance().getScene()->destroyEntityDynamicAccessorys( mEntity, name.c_str() );
	}
	//-----------------------------------------------------------------------
	bool CPlayerCharacterEntity::detachItem(ITEM_EQUIP_SLOT_TYPE item_slot_type, bool forceDetach/* = false*/)
	{
		player_character_attach_point attach_point;

		if ( item_slot_type == ITEM_EQUIP_SLOT_TYPE_MAIN )
			attach_point = ATTACH_POINT_RIGHT_HAND;
		else if ( item_slot_type == ITEM_EQUIP_SLOT_TYPE_DEPUTY )
			attach_point = ATTACH_POINT_LEFT_HAND;
		else if ( item_slot_type == ITEM_EQUIP_SLOT_TYPE_HORSE )
			attach_point = ATTACH_POINT_RIDE;
		else
			return false;

		// 如果是双手武器先去掉左手
		if ( mWeaponActionGroup.compare("shuang") == 0 )
		{
			detachItem(ITEM_EQUIP_SLOT_TYPE_DEPUTY, true);
		}	

		std::map<U32, Str>::iterator iter = mEntityAccessories.find( attach_point );
		if ( iter != mEntityAccessories.end() )
		{
			detachEntityAccessory( iter->second );
			mEntityAccessories.erase(iter);

			if ( mWeaponActionGroup.compare("shuang") )
			
			if ( !forceDetach && 
				( item_slot_type == ITEM_EQUIP_SLOT_TYPE_MAIN ||
				item_slot_type == ITEM_EQUIP_SLOT_TYPE_HORSE ) )
			{
				return attachItem(0, item_slot_type);
			}
			else
			{
				return true;
			}
		}
		return false;
	}
	//-----------------------------------------------------------------------
	bool CPlayerCharacterEntity::attachItem(U32 itemID, ITEM_EQUIP_SLOT_TYPE item_slot_type)
	{
		Bool	succeed = false;
		U32		modelID = 0;
		U32		weaponGroupID = 0;
		
		//是否能够添加装备
		const CharacterTempInfo* charInfo = getCharacterTempInfo();
		if ( !charInfo || charInfo->CharacterType != CHAR_TYPE_GENREAL )
			return succeed;

		if ( itemID != 0 )
		{
			// 如果道具ID不为0， 则获取道具信息。
			const ItemInfo* itemInfo = NULL;
			itemInfo = ItemTemplate::getInstance().getItemInfo(itemID);

			if ( itemInfo && itemInfo->getItemEquipInfo() )
			{
				if ( GENDER_TYPE_MAN == charInfo->getGenrealGenderType() )
					modelID = itemInfo->getItemEquitMaleMash();
				else if ( GENDER_TYPE_WOMAN == charInfo->getGenrealGenderType() )
					modelID = itemInfo->getItemEquitFemaleMash();

				weaponGroupID = itemInfo->getItemEquitWeaponActionId();
			}			
		}
		else
		{
			// 如果道具ID为0，则获取默认模型ID。
			if ( item_slot_type == ITEM_EQUIP_SLOT_TYPE_MAIN )
				modelID = charInfo->getCharacterArtMashId(1);
			else if ( item_slot_type == ITEM_EQUIP_SLOT_TYPE_HORSE )
				modelID = charInfo->getCharacterArtMashId(2);
		}

		// 生成模型
		if ( modelID != 0 )
		{
			// 获得绑定位置
			player_character_attach_point attach_point;

			if ( item_slot_type == ITEM_EQUIP_SLOT_TYPE_MAIN )
				attach_point = ATTACH_POINT_RIGHT_HAND;
			else if ( item_slot_type == ITEM_EQUIP_SLOT_TYPE_DEPUTY )
				attach_point = ATTACH_POINT_LEFT_HAND;
			else if ( item_slot_type == ITEM_EQUIP_SLOT_TYPE_HORSE )
				attach_point = ATTACH_POINT_RIDE;
			else
				return succeed;

			// 获得模型名称
			Str8 itemName;
			MG::MGStrOp::toString( modelID, itemName );
			itemName = mBindPointMap[attach_point] + "_" + itemName;

			if ( attach_point > 0 && !itemName.empty() )
			{
				succeed = attachEntityAccessory( itemName, modelID, attach_point );

				// 双手武器
				if ( weaponGroupID == 3 && item_slot_type == ITEM_EQUIP_SLOT_TYPE_MAIN )
					succeed = attachEntityAccessory( itemName, modelID, ATTACH_POINT_LEFT_HAND );
			}
		}

		// 记录绑定的道具ID
		mItemSkins[item_slot_type] = itemID;

		return succeed;
	}
	//-----------------------------------------------------------------------
	bool CPlayerCharacterEntity::attachItem(U32 itemID)
	{
		Bool	succeed = false;
		U32		modelID = 0;
		U32		weaponGroupID = 0;

		const ItemInfo* itemInfo = ItemTemplate::getInstance().getItemInfo(itemID);

		if ( itemInfo && itemInfo->getItemEquipInfo() )
		{
			// 获得道具模型ID
			const CharacterTempInfo* charInfo = getCharacterTempInfo();
			
			if ( charInfo && charInfo->CharacterType == CHAR_TYPE_GENREAL )
			{
				if ( GENDER_TYPE_MAN == charInfo->getGenrealGenderType() )
					modelID = itemInfo->getItemEquitMaleMash();
				else if ( GENDER_TYPE_WOMAN == charInfo->getGenrealGenderType() )
					modelID = itemInfo->getItemEquitFemaleMash();

				weaponGroupID = itemInfo->getItemEquitWeaponActionId();
			}

			// 获得绑定位置
			player_character_attach_point attach_point;

			MG::ITEM_EQUIP_SLOT_TYPE item_slot_type = itemInfo->getItemEquitEquipSlotType();

			if ( item_slot_type == ITEM_EQUIP_SLOT_TYPE_MAIN )
				attach_point = ATTACH_POINT_RIGHT_HAND;
			else if ( item_slot_type == ITEM_EQUIP_SLOT_TYPE_DEPUTY )
				attach_point = ATTACH_POINT_LEFT_HAND;
			else if ( item_slot_type == ITEM_EQUIP_SLOT_TYPE_HORSE )
				attach_point = ATTACH_POINT_RIDE;
			else 
				return succeed;

			// 获得模型名称
			Str8 itemName;
			MG::MGStrOp::toString( itemInfo->getItemBaseTemplateID(), itemName );
			itemName = mBindPointMap[attach_point] + "_" + itemName;

			if ( !itemName.empty() && modelID != 0 )
			{
				succeed = attachEntityAccessory( itemName, modelID, attach_point );

				// 双手武器
				if ( weaponGroupID == 3 && item_slot_type == ITEM_EQUIP_SLOT_TYPE_MAIN )
					succeed = attachEntityAccessory( itemName, modelID, ATTACH_POINT_LEFT_HAND );
			}

			// 记录绑定的道具ID
			mItemSkins[item_slot_type] = itemID;
		}

		return succeed;
	}
	//-----------------------------------------------------------------------
	void CPlayerCharacterEntity::initBindWordMap()
	{
		mBindPointMap[ATTACH_POINT_LEFT_HAND] = "weapon_L";
		mBindPointMap[ATTACH_POINT_RIGHT_HAND] = "weapon_R";
		mBindPointMap[ATTACH_POINT_RIDE] = "";

		mItemSkins[ITEM_EQUIP_SLOT_TYPE_MAIN] = 0;
		mItemSkins[ITEM_EQUIP_SLOT_TYPE_HORSE] = 0;
	}
	//-----------------------------------------------------------------------
	bool CPlayerCharacterEntity::isRiding()
	{
		std::map<U32, Str>::iterator iter = mEntityAccessories.find( ATTACH_POINT_RIDE );
		return iter != mEntityAccessories.end();
	}

	//-----------------------------------------------------------------------
	void CPlayerCharacterEntity::createFlag(UInt flgModleId)
	{
		mFlagEntity = CSceneManager::getInstance().getEngineScene()->createEntity(flgModleId);
		if(!mFlagEntity)
		{
			return;
		}

		Color flagColor;
		if(CSceneObject::getDynamicData()->force == FORCE_ATTACK)
		{
			flagColor = Color(1.f, 0, 0, 1.f);
		}
		else
		{
			flagColor = Color(0, 0, 1.f, 1.f);
		}

		mFlagEntity->getModelObject()->setEmissive(flagColor);
		mFlagEntity->getAnimationController()->setIsIdle(true, "none_none_stand");
		mFlagEntity->getAnimationController()->play("none_none_stand");
	}

	//-----------------------------------------------------------------------
	void CPlayerCharacterEntity::destroyFlag()
	{
		if( !mFlagEntity )
		{
			return;
		}

		CSceneManager::getInstance().getEngineScene()->destroyEntity(mFlagEntity->getName().c_str());
        mFlagEntity = NULL;
	}
	//-----------------------------------------------------------------------
	void CPlayerCharacterEntity::setActionGroup( U32 actionGroup, Bool isRide )
	{
		// 要先停止原有idle动作
		if ( isBattleState() )
		{
			setIdleAnimation("guard", false);
		}
		else
		{
			setIdleAnimation("stand", false);
		}

		// 映射武器名称
		switch ( actionGroup )
		{
		case 1:
			mWeaponActionGroup = "qiang";
			break;
		case 2:
			mWeaponActionGroup = "dao";
			break;
		case 3:
			mWeaponActionGroup = "shuang";
			break;
		case 4:
			mWeaponActionGroup = "zhang";
			break;
		case 5:
			mWeaponActionGroup = "shan";
			break;
		case 6:
			mWeaponActionGroup = "jian";
			break;
		default:
			mWeaponActionGroup = "none";
		}

		// 是否是骑乘动作
		if ( isRide )
			mRideActionGroup = "kua";
		else
			mRideActionGroup = "none";

		// 更换默认idle动作
		if ( isBattleState() )
		{
			setIdleAnimation("guard", true);
		}
		else
		{
			setIdleAnimation("stand", true);
		}
	}
	//-----------------------------------------------------------------------
	void CPlayerCharacterEntity::getActionGroup( Str& weaponAction, Str& rideAction )
	{
		weaponAction = "none";
		rideAction = "none";

		weaponAction = mWeaponActionGroup;
		weaponAction += '_';

		rideAction = mRideActionGroup;
		rideAction += '_';
	}
	//-----------------------------------------------------------------------
	Bool CPlayerCharacterEntity::isBattleState()
	{
		PlayerCharacterEntityData* data = getDynamicData();
		if ( data )
			return data->isFightState;

		return false;
	}

	//-----------------------------------------------------------------------
	void CPlayerCharacterEntity::applyActionGroup()
	{
		U32 actionGroup = 0;

		if ( mCharacterTempInfo && mCharacterTempInfo->CharacterType == CHARACTER_TYPE_GENREAL )
		{
			actionGroup = mCharacterTempInfo->getGenrealWeaponAcction();
		}

		std::map<U32, U32>::iterator iter = mItemSkins.find(ITEM_EQUIP_SLOT_TYPE_MAIN);
		if ( iter != mItemSkins.end() )
		{
			const ItemInfo* itemInfo = ItemTemplate::getInstance().getItemInfo(iter->second);

			if ( itemInfo )
				actionGroup = itemInfo->getItemEquitWeaponActionId();
		}

		setActionGroup( actionGroup, isRiding() );
	}

	//-----------------------------------------------------------------------
	void CPlayerCharacterEntity::onRelive()
	{
		CCharacterSceneEntity::initialize();
	}
	//-----------------------------------------------------------------------
	PlayerCharacterEntityData* CPlayerCharacterEntity::getDynamicData()
	{
		return dynamic_cast<PlayerCharacterEntityData*>(getGameObjectData());
	}
}