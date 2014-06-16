//***************************************************************************************
#include "stdafx.h"
#include "CBuffCharacterObject.h"
#include "CCharacterSceneEntity.h"
#include "CPlayer.h"
#include "CClan.h"
#include "CCharacter.h"
#include "CharacterList.h"
#include "AttributeAppend.h"
#include "CAttributeSystem.h"
#include "HeadDamageManage.h"
#include "CBuffManager.h"
//***************************************************************************************
namespace MG
{
	CBuffCharacterObject::CBuffCharacterObject(void* parent)
		:mParentEnt((CCharacterSceneEntity*)parent)
	{
		mParentLgc = CPlayer::getInstance().getActiveClan()->getCharacter( mParentEnt->getID(), mParentEnt->getType() );
	}
	//-----------------------------------------------------------------------
	CBuffCharacterObject::~CBuffCharacterObject()
	{
		mParentEnt = NULL;
		mParentLgc = NULL;
	}
	//-----------------------------------------------------------------------
	void CBuffCharacterObject::updateBuffOther( Flt delta )
	{
		//检查周期性事件。
		const StatusCharacterData* pStatusCharacterData = getBuffData()->getStatusBaseInfo<StatusCharacterData>();
		if ( pStatusCharacterData->CycleNum )
		{
			switch (pStatusCharacterData->CycleType)
			{
			case STATUS_CYCLETYPE_FIXED_DAMAGE:
				cycleDamage(
					pStatusCharacterData->CycleParameter1, 
					pStatusCharacterData->CycleParameter2,
					pStatusCharacterData->CycleParameter3,
					pStatusCharacterData->CycleParameter4
					);
				break;
			case STATUS_CYCLETYPE_FIXED_ABSORB:
				cycleAbsorb(
					pStatusCharacterData->CycleParameter1, 
					pStatusCharacterData->CycleParameter2,
					pStatusCharacterData->CycleParameter3,
					pStatusCharacterData->CycleParameter4
					);
				break;
			case STATUS_CYCLETYPE_PERMILLAGE_DAMAGE:
				cycleDamage(
					pStatusCharacterData->CycleParameter1, 
					pStatusCharacterData->CycleParameter2*PERMILLAGE_VALUE*mParentEnt->getHp(),
					pStatusCharacterData->CycleParameter3*PERMILLAGE_VALUE*mParentEnt->getMp(),
					pStatusCharacterData->CycleParameter4*PERMILLAGE_VALUE*mParentEnt->getSp()
					);
				break;
			case STATUS_CYCLETYPE_PERMILLAGE_ABSORB:
				cycleAbsorb(
					pStatusCharacterData->CycleParameter1, 
					pStatusCharacterData->CycleParameter2*PERMILLAGE_VALUE*mParentEnt->getHp(),
					pStatusCharacterData->CycleParameter3*PERMILLAGE_VALUE*mParentEnt->getMp(),
					pStatusCharacterData->CycleParameter4*PERMILLAGE_VALUE*mParentEnt->getSp()
					);
				break;
			case STATUS_CYCLETYPE_MAX_PERMILLAGE_DAMAGE:
				cycleDamage(
					pStatusCharacterData->CycleParameter1,
					pStatusCharacterData->CycleParameter2*PERMILLAGE_VALUE*mParentEnt->getHpMax(), 
					pStatusCharacterData->CycleParameter3*PERMILLAGE_VALUE*mParentEnt->getMpMax(),
					pStatusCharacterData->CycleParameter4*PERMILLAGE_VALUE*mParentEnt->getSpMax()
					);
				break;
			case STATUS_CYCLETYPE_MAX_PERMILLAGE_ABSORB:
				cycleAbsorb(
					pStatusCharacterData->CycleParameter1, 
					pStatusCharacterData->CycleParameter2*PERMILLAGE_VALUE*mParentEnt->getHpMax(), 
					pStatusCharacterData->CycleParameter3*PERMILLAGE_VALUE*mParentEnt->getMpMax(),
					pStatusCharacterData->CycleParameter4*PERMILLAGE_VALUE*mParentEnt->getSpMax()
					);
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void CBuffCharacterObject::clearBuffOther(Bool isCal)
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		DYNAMIC_ASSERT(pStatusCharacterData);
		//如果是自己，更新属性
		//如果是自己，更新护盾值。
		if ( mParentLgc )
		{
			if ( pStatusCharacterData->AbilityAppendId )
				updateAttribute(pStatusCharacterData->AbilityAppendId, pStatusCharacterData->GroupLevel, false);
			if ( pStatusCharacterData->AbsorbType )
				updateAbsorbNum(pStatusCharacterData->AbsorbType, pStatusCharacterData->AbsorbNum, false);
		}
		//改变外观。
		updateFace(false);
	}
	//-----------------------------------------------------------------------
	void CBuffCharacterObject::addBuffOther()
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		DYNAMIC_ASSERT(pStatusCharacterData);
		//如果是自己，更新属性
		//如果是自己，更新护盾值。
		if ( mParentLgc )
		{
			if ( pStatusCharacterData->AbilityAppendId )
				updateAttribute(pStatusCharacterData->AbilityAppendId, pStatusCharacterData->GroupLevel, true);
			if ( pStatusCharacterData->AbsorbType )
				updateAbsorbNum(pStatusCharacterData->AbsorbType, pStatusCharacterData->AbsorbNum, true);
		}
		//改变外观。
		updateFace(true);
	}
	//-----------------------------------------------------------------------
	MG::Bool CBuffCharacterObject::isCanDisappear( STATUS_DISAPPEARTYPE type )
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		if ( pStatusCharacterData )
			return pStatusCharacterData->DisappearType & type;

		return false;
	}
	//-----------------------------------------------------------------------
	MG::Bool CBuffCharacterObject::isHaveSpecialEffect( STATUS_STATUSSYSTYPE type )
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		if ( pStatusCharacterData )
			return pStatusCharacterData->StatusSysType == type;

		return false;
	}
	//-----------------------------------------------------------------------
	MG::Bool CBuffCharacterObject::isHaveVitiateFlag( STATUS_VITIATEFLAG type )
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		if ( pStatusCharacterData )
			return pStatusCharacterData->VitiateFlag & type;

		return false;
	}
	//-----------------------------------------------------------------------
	MG::Bool CBuffCharacterObject::isHaveAbsorbType( STATUS_ABSORBTYPE type )
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		if ( pStatusCharacterData )
			return pStatusCharacterData->AbsorbType == type;

		return false;
	}
	//-----------------------------------------------------------------------
	void CBuffCharacterObject::updateAbsorbNum( STATUS_ABSORBTYPE type, Int num, Bool isAdd )
	{
		CAttributeSystem*  pCAttributeSystem = mParentLgc->getAttributeSystem();

		if ( isAdd )
		{
			pCAttributeSystem->setShieldByType(type, num);
			
		}
		else
		{
			pCAttributeSystem->setShieldByType(type, 0);
		}
		
	}
	//-----------------------------------------------------------------------
	void CBuffCharacterObject::updateAttribute( UInt id, UInt bufflvl, Bool isAdd )
	{
		CAttributeSystem*  pCAttributeSystem = mParentLgc->getAttributeSystem();

		//先找到基本属性。
		std::map<UInt, Flt> mapValue;
		getMapAttrValue(mapValue, id, bufflvl);

		std::map<UInt, Flt>::iterator frontIter = mapValue.begin();
		if ( isAdd )
		{
			while (frontIter != mapValue.end())
			{
				pCAttributeSystem->calRelateAttr(
					frontIter->first, frontIter->second, 
					mParentLgc->getCharacterTempInfo()->getCharacterFormulaType(),
					mParentLgc->getCharacterData()
					);
				++frontIter;
			}
		}
		else
		{
			while (frontIter != mapValue.end())
			{
				pCAttributeSystem->calRelateAttr(
					frontIter->first, frontIter->second*(-1), 
					mParentLgc->getCharacterTempInfo()->getCharacterFormulaType(),
					mParentLgc->getCharacterData()
					);
				++frontIter;
			}
		}
		
	}
	//-----------------------------------------------------------------------
	void CBuffCharacterObject::updateFace( Bool isAdd )
	{

	}
	//-----------------------------------------------------------------------
	void CBuffCharacterObject::getMapAttrValue( std::map<UInt, Flt>& mapValue, UInt id, Int bufflvl )
	{
		//先找到基本属性。
		const AttributeAppendInfo* tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(id);
		if ( tempAppendAttr )
		{
			for (Int i=0; i<APPENDATTR_NUM; i++)
			{
				if ( tempAppendAttr->AppendAttrList[i].id )
				{  
					if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
					{	
						mapValue[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
					}
					else
					{	
						mapValue[tempAppendAttr->AppendAttrList[i].id] += 
							tempAppendAttr->AppendAttrList[i].value*bufflvl*getBuffData()->mCurAddNum*PERMILLAGE_VALUE;
					}
				}
				else
					break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void CBuffCharacterObject::cycleDamage( U32 damage, U32 hpValue, U32 mpValue, U32 spValue )
	{
		//走状态伤害流程
		//..........
		//扣血。
		Vec3 pos;
		mParentEnt->getEntity()->getSceneNode()->getPosition(pos);
		float height = mParentEnt->getEntity()->getModelObject()->getHeight();

		if ( hpValue )
		{	
			HeadDamageManage::getInstance().addNum( pos, height, DT_HP, hpValue, false );
			mParentEnt->setHp(mParentEnt->getHp() - hpValue);
		}
		if ( mpValue )
		{
			HeadDamageManage::getInstance().addNum( pos, height, DT_MP, mpValue, false );
			mParentEnt->setMp(mParentEnt->getMp() - mpValue);
		}
		if ( spValue )
		{
			HeadDamageManage::getInstance().addNum( pos, height, DT_SP, spValue, false );
			mParentEnt->setSp(mParentEnt->getSp() - spValue);
		}
		
	}
	//-----------------------------------------------------------------------
	void CBuffCharacterObject::cycleAbsorb( U32 probability, U32 hpValue, U32 mpValue, U32 spValue )
	{
		Vec3 pos;
		mParentEnt->getEntity()->getSceneNode()->getPosition(pos);
		float height = mParentEnt->getEntity()->getModelObject()->getHeight();

		if ( hpValue )
		{	
			if ( mParentEnt->getHp() + hpValue > mParentEnt->getHpMax()  )
			{
				if ( mParentEnt->getHp() >= mParentEnt->getHpMax() )
					return;
				HeadDamageManage::getInstance().addNum( pos, height, DT_HP, mParentEnt->getHpMax()-mParentEnt->getHp(), true );
				mParentEnt->setHp(mParentEnt->getHpMax());
			}
			else
			{
				HeadDamageManage::getInstance().addNum( pos, height, DT_HP, hpValue, true );
				mParentEnt->setHp(mParentEnt->getHp() + hpValue);
			}	
		}
		if ( mpValue )
		{
			if ( mParentEnt->getMp() + mpValue > mParentEnt->getMpMax()  )
			{
				if ( mParentEnt->getMp() >= mParentEnt->getMpMax() )
					return;
				HeadDamageManage::getInstance().addNum( pos, height, DT_MP, mParentEnt->getMpMax()-mParentEnt->getMp(), true );
				mParentEnt->setMp(mParentEnt->getMpMax());
			}
			else
			{
				HeadDamageManage::getInstance().addNum( pos, height, DT_MP, mpValue, true );
				mParentEnt->setMp(mParentEnt->getMp() + mpValue);
			}
		}
		if ( spValue )
		{
			if ( mParentEnt->getSp() + spValue > mParentEnt->getSpMax()  )
			{
				if ( mParentEnt->getSp() >= mParentEnt->getSpMax() )
					return;
				HeadDamageManage::getInstance().addNum( pos, height, DT_SP, mParentEnt->getSpMax()-mParentEnt->getSp(), true );
				mParentEnt->setSp(mParentEnt->getSpMax());
			}
			else
			{
				HeadDamageManage::getInstance().addNum( pos, height, DT_SP, spValue, true );
				mParentEnt->setSp(mParentEnt->getSp() + spValue);
			}
		}
	}
	//-----------------------------------------------------------------------
	void CBuffCharacterObject::initBuffOther( const StatusData* pStatusData, Int timeUse )
	{
		//虚函数。
		BuffData* pBuffData = getBuffData();
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>(); 

		//时间间隔
		if ( pStatusCharacterData->CycleNum != 0 )
			pBuffData->mTimeSpace = pStatusCharacterData->HoldTime/pStatusCharacterData->CycleNum;
		else
			pBuffData->mTimeSpace = 0.f;

		//剩余时间间隔
		if ( pBuffData->mTimeSpace )
		{
			if ( pBuffData->mTimeSpace > pBuffData->mTimeUse )
				pBuffData->mTimeSpaceLast = pBuffData->mTimeUse;
			else
				pBuffData->mTimeSpaceLast = pBuffData->mTimeSpace;
		}
	}

	void CBuffCharacterObject::calAttrBase()
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		DYNAMIC_ASSERT(pStatusCharacterData);
		CAttributeSystem*  pCAttributeSystem = mParentLgc->getAttributeSystem();

		//先找到基本属性。
		std::map<UInt, Flt> mapValue;
		getMapAttrValue(mapValue, pStatusCharacterData->AbilityAppendId, pStatusCharacterData->GroupLevel);

		std::map<UInt, Flt>::iterator frontIter = mapValue.begin();
		std::map<UInt, Flt>::iterator endIter = mapValue.end();
		while (frontIter != endIter)
		{
			pCAttributeSystem->addValue(
				frontIter->first,
				frontIter->second 
				);
			++frontIter;
		}
	}

}