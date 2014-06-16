//***************************************************************************************
#include "stdafx.h"
#include "SBuffCharacterObject.h"
#include "SCharacter.h"
#include "SBuffPacketProcesser.h"
#include "SPlayer.h"
#include "AttributeAppend.h"
#include "SAttributePacketProcesser.h"
//***************************************************************************************
namespace MG
{
	SBuffCharacterObject::SBuffCharacterObject(void* parent)
		:mParent((SCharacter*)parent)
	{

	}
	//----------------------------------------------------------------------
	SBuffCharacterObject::~SBuffCharacterObject()
	{

	}
	//----------------------------------------------------------------------
	void SBuffCharacterObject::updateBuffOther( Flt delta )
	{
		//检查周期性事件。
		const StatusCharacterData* pStatusCharacterData = getBuffData()->getStatusBaseInfo<StatusCharacterData>();
		DYNAMIC_ASSERT(pStatusCharacterData);
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
					pStatusCharacterData->CycleParameter2*PERMILLAGE_VALUE*mParent->getHp(),
					pStatusCharacterData->CycleParameter3*PERMILLAGE_VALUE*mParent->getMp(),
					pStatusCharacterData->CycleParameter4*PERMILLAGE_VALUE*mParent->getSp()
					);
				break;
			case STATUS_CYCLETYPE_PERMILLAGE_ABSORB:
				cycleAbsorb(
					pStatusCharacterData->CycleParameter1, 
					pStatusCharacterData->CycleParameter2*PERMILLAGE_VALUE*mParent->getHp(),
					pStatusCharacterData->CycleParameter3*PERMILLAGE_VALUE*mParent->getMp(),
					pStatusCharacterData->CycleParameter4*PERMILLAGE_VALUE*mParent->getSp()
					);
				break;
			case STATUS_CYCLETYPE_MAX_PERMILLAGE_DAMAGE:
				cycleDamage(
					pStatusCharacterData->CycleParameter1,
					pStatusCharacterData->CycleParameter2*PERMILLAGE_VALUE*mParent->getMaxHp(), 
					pStatusCharacterData->CycleParameter3*PERMILLAGE_VALUE*mParent->getMaxMp(),
					pStatusCharacterData->CycleParameter4*PERMILLAGE_VALUE*mParent->getMaxSp()
					);
				break;
			case STATUS_CYCLETYPE_MAX_PERMILLAGE_ABSORB:
				cycleAbsorb(
					pStatusCharacterData->CycleParameter1, 
					pStatusCharacterData->CycleParameter2*PERMILLAGE_VALUE*mParent->getMaxHp(), 
					pStatusCharacterData->CycleParameter3*PERMILLAGE_VALUE*mParent->getMaxMp(),
					pStatusCharacterData->CycleParameter4*PERMILLAGE_VALUE*mParent->getMaxSp()
					);
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
			}
		}
	}
	//----------------------------------------------------------------------
	void SBuffCharacterObject::clearBuffOther(Bool isCal)
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		DYNAMIC_ASSERT(pStatusCharacterData);
		if ( isCal )
		{
			//根据AbilityAppendId更新属性值。
			if ( pStatusCharacterData->AbilityAppendId )
				calAttribute(pStatusCharacterData->AbilityAppendId, pStatusCharacterData->GroupLevel, false);
		}

		//该类型的护盾值清零
		if ( pStatusCharacterData->AbsorbType )
		{	
			clearAbsorbNum(pStatusCharacterData->AbsorbType);
		}
		
		//检查是否更新DB
		if (	mParent->getType() == GOT_PLAYERCHARACTER  && 
			pStatusCharacterData->DisappearType & STATUS_DISAPPEARTYPE_OFFLINE == false )
		{	
			updateDB();
		}
	}
	//----------------------------------------------------------------------
	void SBuffCharacterObject::addBuffOther()
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		DYNAMIC_ASSERT(pStatusCharacterData);
		//add护盾，（如果护盾为0，去掉相关护盾）
		if ( pStatusCharacterData->AbsorbType ) 
		{
			addAbsorbNum(pStatusCharacterData->AbsorbType, pStatusCharacterData->AbsorbNum);
		}
		//根据AbilityAppendId更新属性值。
		if ( pStatusCharacterData->AbilityAppendId )
		{
			calAttribute(pStatusCharacterData->AbilityAppendId, pStatusCharacterData->GroupLevel);
		}

		//检查是否更新DB
		if (	mParent->getType() == GOT_PLAYERCHARACTER  && 
				pStatusCharacterData->DisappearType & STATUS_DISAPPEARTYPE_OFFLINE == false )
		{	
			updateDB();
		}

		//同步给client
		BuffData* pBuffData = getBuffData();
		if ( mParent->getType() == GOT_PLAYERCHARACTER )
			SBuffPacketProcesser::getInstance().syncPlayerCharacterBuffDataToClient(
				(SPlayerCharacter*)mParent, pBuffData->mBuffId, pBuffData->mCurAddNum, pBuffData->mTimeUse
			);
	}
	//----------------------------------------------------------------------
	MG::Bool SBuffCharacterObject::isCanDisappear( STATUS_DISAPPEARTYPE type )
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		if ( pStatusCharacterData )
			return pStatusCharacterData->DisappearType & type;

		return false;
	}
	//----------------------------------------------------------------------
	MG::Bool SBuffCharacterObject::isHaveSpecialEffect( STATUS_STATUSSYSTYPE type )
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		if ( pStatusCharacterData )
			return pStatusCharacterData->StatusSysType == type;

		return false;
	}
	//----------------------------------------------------------------------
	MG::Bool SBuffCharacterObject::isHaveVitiateFlag( STATUS_VITIATEFLAG type )
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		if ( pStatusCharacterData )
			return pStatusCharacterData->VitiateFlag & type;

		return false;
	}
	//----------------------------------------------------------------------
	MG::Bool SBuffCharacterObject::isHaveAbsorbType( STATUS_ABSORBTYPE type )
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		if ( pStatusCharacterData )
			return pStatusCharacterData->AbsorbType == type;

		return false;
	}
	//----------------------------------------------------------------------
	void SBuffCharacterObject::addAbsorbNum( STATUS_ABSORBTYPE type, Int num )
	{
		mParent->getSAttributeSystem()->addShieldByType(type, num);
	}
	//----------------------------------------------------------------------
	void SBuffCharacterObject::calAttribute(UInt abilityAppendId, UInt buffLvl, Bool isAdd)
	{
		SAttributeSystem*  pCAttributeSystem = mParent->getSAttributeSystem();

		//先找到基本属性。
		std::map<UInt, Flt> mapValue;
		getMapAttrValue(mapValue, abilityAppendId, buffLvl);

		std::map<UInt, Flt>::iterator frontIter = mapValue.begin();
		std::map<UInt, Flt>::iterator endIter = mapValue.end();
		if ( isAdd )
		{
			while (frontIter != endIter)
			{
				pCAttributeSystem->calRelateAttr(
					frontIter->first, frontIter->second, 
					mParent->getCharacterTempInfo()->getCharacterFormulaType(),
					mParent->getCharacterData()
					);
				++frontIter;
			}
		}
		else
		{
			while (frontIter != endIter)
			{
				pCAttributeSystem->calRelateAttr(
					frontIter->first, frontIter->second*(-1), 
					mParent->getCharacterTempInfo()->getCharacterFormulaType(),
					mParent->getCharacterData()
					);
				++frontIter;
			}
		}
	}
	//----------------------------------------------------------------------
	void SBuffCharacterObject::updateDB()
	{
		SBuffPacketProcesser::getInstance().sendBuffDataToFrontServer(
				mParent->getFrontServerId(), 
				mParent->getAccountId(),
				mParent->getID(),
				getBuffData() 
				);
	}
	//----------------------------------------------------------------------
	void SBuffCharacterObject::clearAbsorbNum( STATUS_ABSORBTYPE type )
	{
		mParent->getSAttributeSystem()->setShieldByType(type, 0);
	}
	//----------------------------------------------------------------------
	void SBuffCharacterObject::getMapAttrValue( std::map<UInt, Flt>& mapValue, UInt id, Int bufflvl )
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
					continue;
			}
		}
	}
	//----------------------------------------------------------------------
	void SBuffCharacterObject::cycleDamage( U32 damage, U32 hpValue, U32 mpValue, U32 spValue )
	{
		//走状态伤害流程
		//..........
		//扣血。
		if ( hpValue )
		{	
			mParent->setHp(mParent->getHp() - (Int)hpValue);
			SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(
				mParent->getFrontServerId(), mParent, DT_HP, hpValue, ATTACK_RESULT_TYPE_HURT
				);
		}
		if ( mpValue )
		{	
			mParent->setMp(mParent->getMp() - (Int)mpValue);
			SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(
				mParent->getFrontServerId(), mParent, DT_MP, mpValue, ATTACK_RESULT_TYPE_HURT
				);
		}
		if ( spValue )
		{	
			mParent->setSp(mParent->getSp() - (Int)mpValue);
			SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(
				mParent->getFrontServerId(), mParent, DT_SP, spValue, ATTACK_RESULT_TYPE_HURT
				);
		}
	}
	//----------------------------------------------------------------------
	void SBuffCharacterObject::cycleAbsorb( U32 probability, U32 hpValue, U32 mpValue, U32 spValue )
	{
		//走状态治疗流程
		//..........
		//加血。
		if ( hpValue )
		{	
			mParent->setHp(mParent->getHp() + (Int)hpValue);
			SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(
				mParent->getFrontServerId(), mParent, DT_HP, hpValue, ATTACK_RESULT_TYPE_RECOVER
				);
		}
		if ( mpValue )
		{	
			mParent->setMp(mParent->getMp() + (Int)mpValue);
			SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(
				mParent->getFrontServerId(), mParent, DT_MP, mpValue, ATTACK_RESULT_TYPE_RECOVER
				);
		}
		if ( spValue )
		{	
			mParent->setSp(mParent->getSp() + (Int)mpValue);
			SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(
				mParent->getFrontServerId(), mParent, DT_SP, spValue, ATTACK_RESULT_TYPE_RECOVER
				);
		}
	}
	//-----------------------------------------------------------------------
	void SBuffCharacterObject::initBuffOther( const StatusData* pStatusData, Int timeUse )
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
	//-----------------------------------------------------------------------
	void SBuffCharacterObject::calAttrBase()
	{
		const StatusCharacterData* pStatusCharacterData = getBuffTmpData<StatusCharacterData>();
		DYNAMIC_ASSERT(pStatusCharacterData);
		SAttributeSystem*  pCAttributeSystem = mParent->getSAttributeSystem();

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