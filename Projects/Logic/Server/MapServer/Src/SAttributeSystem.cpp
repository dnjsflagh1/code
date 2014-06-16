//******************************************************************************************
#include "stdafx.h"
#include "SAttributeSystem.h"
#include "SCharacter.h"
#include "AttributeFormula.h"
#include "AttributePara.h"
#include "SAttributePacketProcesser.h"
#include "AttributeInit.h"
#include "AttributeAppend.h"
#include "SPlayer.h"
#include "CharacterList.h"
#include "SBuffManager.h"
#include "SBuffPacketProcesser.h"
#include "MGRandom.h"
//******************************************************************************************
namespace MG
{
#define ATTR_RAND_INDEX 3
#define LVADD_RAND_INDEX 4
    //-----------------------------------------------------------------------------
    void SAttributeSystem::calAttrBase( SCharacter* pCharacter )
    {
		AttributeSet* mCalAttrInfo = getCalAttrInfo();
		mCalAttrInfo->resetAllValue();

		//根据tempID加上附加值。
		const CharacterTempInfo* mCharacterTempInfo = pCharacter->getCharacterTempInfo();
		assert(mCharacterTempInfo);

		//初始化属性
		for (Int i=0; i<CHAR_ABILITYAPPEND_ID_NUM-1; i++)
		{
			Flt tempVal = 0;

			U32 id = mCharacterTempInfo->getCharacterAbilityAppendId(i);
			if ( id == 0 )
				continue;
			const AttributeInitInfo* pAAinfo = AttributeInit::getInstance().getAttributeInitInfo( id );
			DYNAMIC_ASSERT(pAAinfo);
			for ( Int j=0; j<APPENDATTR_NUM; j++ )
			{
				if ( 0 == pAAinfo->AppendAttrList[j].id )
					continue;

				//先判断类型，在选择计算方法。
				tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
				mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
			}
		}

		//附加属性
		U32 id = mCharacterTempInfo->getCharacterAbilityAppendId(CHAR_ABILITYAPPEND_ID_NUM-1);
		if ( id != 0 )
		{
			Flt tempVal = 0;

			const AttributeAppendInfo* pAttributeAppendInfo = AttributeAppend::getInstance().getAttributeAppendInfo(id);
			DYNAMIC_ASSERT(pAttributeAppendInfo);

			for ( Int j=0; j<APPENDATTR_NUM; j++ )
			{
				if ( 0 == pAttributeAppendInfo->AppendAttrList[j].id )
					continue;

				//先判断类型，在选择计算方法。
				tempVal =  mCalAttrInfo->getFanalValue( pAttributeAppendInfo->AppendAttrList[j].id );
				if ( pAttributeAppendInfo->AppendType == APPEND_TYPE_REAL )
				{	
					tempVal += pAttributeAppendInfo->AppendAttrList[j].value;
				}
				else
				{	
					tempVal += 
						pAttributeAppendInfo->AppendAttrList[j].value*pCharacter->getLevel()*PERMILLAGE_VALUE;
				}
				mCalAttrInfo->setFanalValue( pAttributeAppendInfo->AppendAttrList[j].id, tempVal );
			}
		}

		//随机属性
		{
			Flt tempVal = 0;
			const AttributeInitInfo* pAAinfo = NULL;

			//随机基础属性
			UInt randId = pCharacter->getDBAttrInitID();
			if ( 0 != randId )
			{
				pAAinfo = AttributeInit::getInstance().getAttributeInitInfo( randId );
				DYNAMIC_ASSERT(pAAinfo);
				for ( Int j=0; j<APPENDATTR_NUM; j++ )
				{
					if ( 0 == pAAinfo->AppendAttrList[j].id )
						continue;
					//先判断类型，在选择计算方法。
					tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
					mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pCharacter->getDBAttrInit(j) + tempVal );
				}
			}

			//随机附加属性
			UInt randAddId = pCharacter->getDBAttrLvlAddID();
			if ( 0 != randAddId )
			{	
				pAAinfo = AttributeInit::getInstance().getAttributeInitInfo( randAddId );
				DYNAMIC_ASSERT(pAAinfo);
				for ( Int j=0; j<APPENDATTR_NUM; j++ )
				{
					if ( 0 == pAAinfo->AppendAttrList[j].id )
						continue;
					//先判断类型，在选择计算方法。
					tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
					mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pCharacter->getDBAttrLvlAdd(j) + tempVal );
				}
			}			
		} 

		//for (Int i=0; i<CHAR_ABILITYAPPEND_ID_NUM; i++)
		//{
		//	Flt tempVal = 0;

		//	U32 id = mCharacterTempInfo->getCharacterAbilityAppendId(i);
		//	if ( id == 0 )
		//		break;
		//	const AttributeInitInfo* pAAinfo = AttributeInit::getInstance().getAttributeInitInfo( id );
		//	assert(pAAinfo);

		//	//if ( CHAR_ATTRRAND_TYPE_YES == mCharacterTempInfo->getCharacterAbilityRandomType() )
		//	//{
		//	//	Flt tempRandVal = 0;
		//	//	char msg[128] = "";

		//	//	if ( ATTR_RAND_INDEX == i )
		//	//	{
		//	//		for ( Int j=0; j<APPENDATTR_NUM; j++ )
		//	//		{
		//	//			if ( 0 == pAAinfo->AppendAttrList[j].id )
		//	//				continue;
		//	//			//自己的本来值
		//	//			tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
		//	//			//随机值
		//	//			if ( j < DB_RECORD_ATTR_NUM )
		//	//				tempRandVal = pCharacter->getDBAttrInit(j);
		//	//			else
		//	//				tempRandVal = 0;
		//	//			//最终值
		//	//			mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, tempRandVal + tempVal );
		//	//		}
		//	//	}
		//	//	else if ( LVADD_RAND_INDEX == i )
		//	//	{
		//	//		for ( Int j=0; j<APPENDATTR_NUM; j++ )
		//	//		{
		//	//			if ( 0 == pAAinfo->AppendAttrList[j].id )
		//	//				continue;
		//	//			//自己的本来值
		//	//			tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
		//	//			//随机值
		//	//			if ( j < DB_RECORD_ATTR_NUM )
		//	//				tempRandVal = pCharacter->getDBAttrLvlAdd(j);
		//	//			else
		//	//				tempRandVal = 0;
		//	//			//最终值
		//	//			mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, tempRandVal + tempVal );
		//	//		}
		//	//	}
		//	//	else
		//	//	{
		//	//		for ( Int j=0; j<APPENDATTR_NUM; j++ )
		//	//		{
		//	//			//先判断类型，在选择计算方法。
		//	//			tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
		//	//			mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
		//	//		}
		//	//	}
		//	//}
		//	//else
		//	{
		//		//不随机
		//		for ( Int j=0; j<APPENDATTR_NUM; j++ )
		//		{
		//			//先判断类型，在选择计算方法。
		//			tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
		//			mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
		//		}
		//	} 
		//}

		////在根据血脉加上附加值
		//const LineageInfo* pLginfo = LineageTemplate::getInstance().getAttrAppendInfo(lineageAppendAttrid);
		//assert(pLginfo);
		//if ( pLginfo->abilityGroupAppendId != 0 )
		//{
		//    const AttributeAppendInfo* pAAinfo = AttributeAppend::getInstance().getAttributeAppendInfo( pLginfo->abilityGroupAppendId );
		//    assert(pAAinfo);
		//    for ( Int j=0; j<APPENDATTR_NUM; j++ )
		//    {
		//        //先判断类型，在选择计算方法。
		//        Flt tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
		//        mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
		//    }
		//}
    }
#undef  ATTR_RAND_INDEX
#undef LVADD_RAND_INDEX

    //--------------------------------------------------------------------------
    void SAttributeSystem::obtainDamage( SCharacter* hurtSCharacter, SCharacter* masterSCharacter, AttackType attacktype, DamageType damageType, ATTACK_POS attackPos, U32 formulaParaID, Int& fixedHateValue, UInt buffId, UInt addNum, UInt permillage  )
    {
		//直接检测目标角色有无血量，如果没有就进入死亡流程。
		Int curHp = hurtSCharacter->getHp();
		if ( curHp <= 0 )
		{	
			DYNAMIC_ASSERT(0);
			hurtSCharacter->dead(masterSCharacter);
			return;
		}
        //-------------------------------------------------------------------
        //print
        Char8 tempMsg[128]  = "";

        /*Sprintf_s(tempMsg, 128, "伤害者类型 = %d\n", hurtPeoper->getType());
        MG_LOG(out_sys, tempMsg);
        Sprintf_s(tempMsg, 128, "攻击者类型 = %d\n", master->getType());
        MG_LOG(out_sys, tempMsg);*/
        //-------------------------------------------------------------------

        AttributeSet* pHurtAttributeSet = getCalAttrInfo();
        AttributeSet* pMasterAttributeSet = masterSCharacter->getAttributeSet();
        const AttrParaInfo* pAttrParaInfo = NULL;

        //初始化
        Flt otherPara[ATTR_PARA_NUM];
        for (Int i=0; i<ATTR_PARA_NUM; i++)
            otherPara[i] = 0.f;

        //计算仇恨公式101
        calStartHatredOD(pMasterAttributeSet, fixedHateValue, otherPara);

        //是否有免疫状态
        if ( checkImmunoStatusOD(hurtSCharacter, attacktype) )
        {
			sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_INVALID, fixedHateValue);
            return;
        }

        //获得初步攻击值。
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(formulaParaID);
        DYNAMIC_ASSERT(pAttrParaInfo);
        Flt hurtValue = AttributeFormula::getInstance().calValue( pMasterAttributeSet, masterSCharacter->getCharacterData(), pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId );
        /*Sprintf_s(tempMsg, 128, "首次计算的攻击值 = %f\n", tempValue);
        MG_LOG(out_sys, tempMsg);*/
        
        //圆桌判定。
        FIGHT_ROUND_TYPE frType = calRoundTabOD(masterSCharacter, hurtSCharacter, otherPara);
        /*Sprintf_s(tempMsg, 128, "圆桌判定判断类型 = %d\n", frType);
        MG_LOG(out_sys, tempMsg);*/

		//计算作用者防御对攻击的减免及伤害附加
		calDefenseReduceHurtOD(pHurtAttributeSet, pMasterAttributeSet, attacktype, hurtValue, otherPara);

        //根据FIGHT_ROUND_TYPE计算伤害值。
        if ( calHitByFRTypeOD(pHurtAttributeSet, pMasterAttributeSet, hurtValue, frType, otherPara) )
        {   
            //发送躲避消息。
			sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_DODGE, fixedHateValue);
            return;
        }
        /*Sprintf_s(tempMsg, 128, "圆桌判定后的伤害值 = %f\n", tempValue);
        MG_LOG(out_sys, tempMsg);*/

        

       /* Sprintf_s(tempMsg, 128, "计算作用者防御对攻击的减免及伤害附加 = %f\n", tempValue);
        MG_LOG(out_sys, tempMsg);*/

        //计算作用者方向伤害
        calDirectionHurtOD(pHurtAttributeSet, pMasterAttributeSet, attackPos, hurtValue, otherPara);

        //Sprintf_s(tempMsg, 128, "计算作用者方向伤害 = %f\n", tempValue);
        //MG_LOG(out_sys, tempMsg);
		//兵科伤害。
		calCorpsHurtOD(masterSCharacter, hurtSCharacter, hurtValue, otherPara);

		//伤害计算完毕。
		//---------------------------------------------------------------------------------

        //计算作用者全伤害吸收
        if ( calCompleteAbsorbHurtOD(hurtSCharacter, hurtValue) ) 
        { 
            //发送吸收消息
			sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_ABSORB, fixedHateValue);
            /*Sprintf_s(tempMsg, 128, "计算作用者全伤害吸收 = %f\n", tempValue);
            MG_LOG(out_sys, tempMsg);*/

            return;
        }

        //计算作用者法力护盾吸收
        if ( calMagicShieldAbsorbHurtOD(hurtSCharacter, hurtValue) )
        {
            //发送吸收消息
			sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_ABSORB, fixedHateValue);
            
           /* Sprintf_s(tempMsg, 128, "计算作用者法力护盾吸收 = %f\n", tempValue);
            MG_LOG(out_sys, tempMsg);*/
            
            return;
        }

        //计算作用者对应伤害类型吸收
        if ( calAttTypeAbsorbHurtOD(hurtSCharacter, hurtValue, attacktype) )
        {
            //发送吸收消息
			sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_ABSORB, fixedHateValue);
            
            /*Sprintf_s(tempMsg, 128, "计算作用者对应伤害类型吸收 = %f\n", tempValue);
            MG_LOG(out_sys, tempMsg);*/

            return;
        }

		//状态处理吸血，反弹等
		//?

		//计算作用者对释放者的仇恨值
		calToMasterHatredOD(pMasterAttributeSet, damageType, hurtValue, otherPara, fixedHateValue);

		//发送作用者扣减血量信息
		sendObjAttr(hurtSCharacter, masterSCharacter, damageType, hurtValue, ATTACK_RESULT_TYPE_HURT, fixedHateValue);

        
        //----------------------------------------------------------------------------------------
       /* Sprintf_s(tempMsg, 128, "属性计算结束\n");
        MG_LOG(out_sys, tempMsg);*/
        //----------------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::calStartHatredOD(AttributeSet* pMasterAttr, Int& fixedHateValue, Flt otherPara[ATTR_PARA_NUM])
    {
		////1001公式。
		otherPara[0] = fixedHateValue;
		const AttrParaInfo* pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1001);
		DYNAMIC_ASSERT(pAttrParaInfo);
		fixedHateValue = AttributeFormula::getInstance().calValue(pMasterAttr, NULL, pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, getCalAttrInfo(), otherPara);
    }
    //--------------------------------------------------------------------------
    MG::Bool SAttributeSystem::checkImmunoStatusOD(SCharacter* pSCharacter, AttackType attackType)
    {
		STATUS_VITIATEFLAG vitiateFlag = changeToSVFTypeOD(attackType);
		DYNAMIC_ASSERT(vitiateFlag);
	    return pSCharacter->getSBuffManager()->isHaveVitiateFlag(vitiateFlag);
    }
    //--------------------------------------------------------------------------
    FIGHT_ROUND_TYPE SAttributeSystem::calRoundTabOD( SCharacter* pMasterSCharacter, SCharacter* pHurtSCharacter, Flt otherPara[ATTR_PARA_NUM] )
    {
        const AttrParaInfo* pAttrParaInfo = NULL;
        Flt regionPara[ATTR_PARA_NUM] ;
        memset(regionPara, 0, sizeof(regionPara));

        //级差。公式1002
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1002);
        DYNAMIC_ASSERT(pAttrParaInfo);
        Int lvlgap = AttributeFormula::getInstance().calValue( 
			pMasterSCharacter->getAttributeSet(),
			pMasterSCharacter->getCharacterData(),
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			pHurtSCharacter->getAttributeSet(),
			otherPara,
			pHurtSCharacter->getCharacterData()
			);

        ////固定区间 公式1003
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1003);
		memcpy(&otherPara[1], pAttrParaInfo->para, sizeof(Flt)*3);

        ////躲避区间 公式1004
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1004);
        otherPara[0] = lvlgap;
        otherPara[4] = AttributeFormula::getInstance().calValue(
			pMasterSCharacter->getAttributeSet(), 
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId,
			pHurtSCharacter->getAttributeSet(),
			otherPara,
			NULL
			);

        ////重击区间 公式1005
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1005);
        otherPara[5] = AttributeFormula::getInstance().calValue(
			pMasterSCharacter->getAttributeSet(),
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId,
			pHurtSCharacter->getAttributeSet(),
			otherPara,
			NULL
			);

        ////剩余区间 公式1006
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1006);
        memcpy(regionPara, &(otherPara[1]), sizeof(Flt)*5);
        regionPara[5] = AttributeFormula::getInstance().calValue(
			pMasterSCharacter->getAttributeSet(),
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			pHurtSCharacter->getAttributeSet(),
			regionPara,
			NULL
			);

        ////随机区间。公式1007
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1007);
        Int randValue = AttributeFormula::getInstance().calValue(
			pMasterSCharacter->getAttributeSet(),
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId
			);

        ////随机类型
        Int randRefe = 0;
        for (Int i=0; i<ATTR_PARA_NUM; i++)
        {
            randRefe += (Int)regionPara[i];
            if ( randValue < randRefe )
                return changeToFRTypeOD(i);
        }

        return  FIGHT_ROUND_TYPE_HIT;
    }
    //--------------------------------------------------------------------------
    MG::Bool SAttributeSystem::calHitByFRTypeOD( AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, Flt& hitValue, FIGHT_ROUND_TYPE type, Flt otherPara[ATTR_PARA_NUM] )
    {
        const AttrParaInfo* pAttrParaInfo = NULL;

        switch (type)
        {
        case FIGHT_ROUND_TYPE_HIT:
			{
				pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1008);
				otherPara[0] = hitValue;
				hitValue = AttributeFormula::getInstance().calValue(
					pMasterAttr,
					NULL,
					pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId,
					pHurtAttr, 
					otherPara
					);
			}
			break;
        case FIGHT_ROUND_TYPE_DODGE:
            return true;
            break;
        case FIGHT_ROUND_TYPE_THUMP:
			{
				pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1009);
				otherPara[0] = hitValue;
				hitValue = AttributeFormula::getInstance().calValue(
					pMasterAttr, 
					NULL,
					pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId,
					pHurtAttr, 
					otherPara
					);
			}
			break;
		default:
			DYNAMIC_ASSERT(0);
			break;
        }

        return false;
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::calDefenseReduceHurtOD( AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, AttackType attackType, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM] )
    {
		DYNAMIC_ASSERT( attackType>AT_NULL  &&  attackType<AT_MAX );
		const AttrParaInfo* pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1010 + attackType);  
        otherPara[0] = hitValue;
        hitValue = AttributeFormula::getInstance().calValue(
			pMasterAttr, 
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			pHurtAttr, 
			otherPara
			);
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::calDirectionHurtOD( AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, ATTACK_POS attackPos, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM] )
    {
        const AttrParaInfo* pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1018 + attackPos); 
        otherPara[0] = hitValue;
        hitValue = AttributeFormula::getInstance().calValue(
			pMasterAttr,
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId,
			getCalAttrInfo(), 
			otherPara
			);
    }
    //--------------------------------------------------------------------------
    MG::Bool SAttributeSystem::calCompleteAbsorbHurtOD( SCharacter* pHurtSCharacter, Flt& hitValue )
    {
		SAttributeSystem* pHurtAttrSys = pHurtSCharacter->getSAttributeSystem();

		//全伤害吸收护盾
        Int allAbsorbVal = pHurtAttrSys->getShieldByType(STATUS_ABSORBTYPE_ALL);
		if ( allAbsorbVal > 0 )
		{
			if ( allAbsorbVal > (Int)hitValue )
			{
				pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_ALL, allAbsorbVal-(Int)hitValue);
				hitValue = 0;
				return true;
			}
			else if ( allAbsorbVal == (Int)hitValue )
			{
				pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_ALL, 0);
				hitValue = 0;
				//状态移除
				pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_ALL);
				//流程结束
				return true;
			}
			else
			{
				pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_ALL, 0);
				hitValue -= allAbsorbVal;
				//状态移除
				pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_ALL);
				//流程继续
				return false;
			}
		}
		else
			return false;
    }
    //--------------------------------------------------------------------------
    MG::Bool SAttributeSystem::calMagicShieldAbsorbHurtOD( SCharacter* pHurtSCharacter, Flt& hitValue )
    {
		SAttributeSystem* pHurtAttrSys = pHurtSCharacter->getSAttributeSystem();
		CharacterData* pCharacterData = pHurtSCharacter->getCharacterData();

		//法力护盾
		Int magicAbsorbVal = pHurtAttrSys->getShieldByType(STATUS_ABSORBTYPE_MAGIC);
		if (magicAbsorbVal > 0)
		{
			if ( magicAbsorbVal > pCharacterData->mMp )
			{
				if ( pCharacterData->mMp > (Int)hitValue  )
				{
					pCharacterData->mMp -= (Int)hitValue;
					pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_MAGIC,magicAbsorbVal-(Int)hitValue);
					//是否需要向客户端发送消耗MP的消息
					//?
					hitValue = 0;
					//流程结束
					return true;
				}
				else if ( pCharacterData->mMp == (Int)hitValue )
				{
					pCharacterData->mMp = 0;
					pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_MAGIC,0);
					//是否需要向客户端发送消耗MP的消息
					//?
					hitValue = 0;
					//状态移除
					pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
					//流程结束
					return true;
				}
				else
				{
					hitValue -= pCharacterData->mMp;
					pCharacterData->mMp = 0;
					pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_MAGIC,0);
					//是否需要向客户端发送消耗MP的消息
					//?
					//状态移除
					pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
					//流程继续
					return false;
				}
			}
			else
			{
				if ( magicAbsorbVal > (Int)hitValue )
				{
					pCharacterData->mMp -= (Int)hitValue;
					pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_MAGIC,magicAbsorbVal-(Int)hitValue);
					//是否需要向客户端发送消耗MP的消息
					//?
					hitValue = 0;
					//流程结束
					return true;
				}
				else if ( magicAbsorbVal == (Int)hitValue )
				{
					pCharacterData->mMp -= (Int)hitValue;
					pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_MAGIC,0);
					//是否需要向客户端发送消耗MP的消息
					//?
					hitValue = 0;
					//状态移除
					pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
					//流程结束
					return true;
				}
				else
				{
					hitValue -= magicAbsorbVal;
					pCharacterData->mMp -= magicAbsorbVal;
					pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_MAGIC,0);
					//是否需要向客户端发送消耗MP的消息
					//?
					//状态移除
					pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
					//流程继续
					return false;
				}
			}
		}
		else
			return false; 
    }
    //--------------------------------------------------------------------------
    MG::Bool SAttributeSystem::calAttTypeAbsorbHurtOD( SCharacter* pHurtSCharacter, Flt& hitValue, AttackType attackType )
    {
		SAttributeSystem* pHurtAttrSys = pHurtSCharacter->getSAttributeSystem();
		STATUS_ABSORBTYPE absorbType = changeToSAbsorbType(attackType);
		DYNAMIC_ASSERT(absorbType>STATUS_ABSORBTYPE_NULL  &&  absorbType <STATUS_ABSORBTYPE_ALL);

		//伤害类型吸收护盾
		Int attackAbsorbVal = pHurtAttrSys->getShieldByType(absorbType);
		if ( attackAbsorbVal > 0 )
		{
			if ( attackAbsorbVal > (Int)hitValue )
			{
				pHurtAttrSys->setShieldByType(absorbType, attackAbsorbVal-(Int)hitValue);
				hitValue = 0;
				return true;
			}
			else if ( attackAbsorbVal == (Int)hitValue )
			{
				pHurtAttrSys->setShieldByType(absorbType, 0);
				hitValue = 0;
				//状态移除
				pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(absorbType);
				//流程结束
				return true;
			}
			else
			{
				pHurtAttrSys->setShieldByType(absorbType, 0);
				hitValue -= attackAbsorbVal;
				//状态移除
				pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(absorbType);
				//流程继续
				return false;
			}
		}
		else
			return false;
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::calToMasterHatredOD( AttributeSet* pMasterAttr, DamageType effectType, Flt hitValue, Flt otherPara[ATTR_PARA_NUM], Int& hateValue )
    {
        if (effectType == DT_HP)
        {    
            otherPara[0] = hitValue;
            otherPara[1] = 0.f;
        }
        else if ( effectType == DT_MP )
        {
            otherPara[0] = 0.f;
            otherPara[1] = hitValue;
        }
        else if ( effectType == DT_HPMP )
        {
            otherPara[0] = hitValue;
            otherPara[1] = hitValue;
        }
        else
        {
			DYNAMIC_ASSERT(0);
			return;
        }

        const AttrParaInfo* pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1027);
        hateValue += AttributeFormula::getInstance().calValue(
			pMasterAttr,
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId,
			NULL, 
			otherPara
			);
    }
    //--------------------------------------------------------------------------
    MG::FIGHT_ROUND_TYPE SAttributeSystem::changeToFRTypeOD( UInt index )
    {
        if ( 0 == index  ||  5 == index )
            return FIGHT_ROUND_TYPE_HIT;
        else if ( 1 == index  ||  3 == index )
            return FIGHT_ROUND_TYPE_DODGE;
        else if ( 2 == index  ||  4 == index )
            return FIGHT_ROUND_TYPE_THUMP;
        else
		{  
			DYNAMIC_ASSERT(0);
			return FIGHT_ROUND_TYPE_HIT;
		}
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::skillTreat( SCharacter* treatSCharacter, SCharacter* masterSCharacter, DamageType type, U32 formulaParaID, Int& fixedHateValue, UInt buffId, UInt addNum, UInt permillage )
    {
        AttributeSet* pMasterAttrSet = masterSCharacter->getAttributeSet();
		AttributeSet* ptreatAttrSet = treatSCharacter->getAttributeSet();
        Flt otherPara[ATTR_PARA_NUM];
        for (Int i=0; i<ATTR_PARA_NUM; i++)
            otherPara[i] = 0.f;

        //计算非武将对释放者的仇恨值。
        calToMasterHatredST(pMasterAttrSet, otherPara, fixedHateValue);

        Flt valueST = 0.f;
        // 计算施展者造成的治疗量
        calSkillTreatST(pMasterAttrSet, valueST, formulaParaID);

        // 治疗圆桌判定
        TREAT_ROUND_TYPE strType = calRoundTabST(pMasterAttrSet, otherPara);

        //根据 TREAT_ROUND_TYPE 计算治疗量
        calTreatBySTRTypeST(pMasterAttrSet, ptreatAttrSet, valueST, strType, otherPara);

        // 计算最终 治疗量
        calFinalSkillTreatST(pMasterAttrSet, ptreatAttrSet, valueST, otherPara); 

        //计算非武将对释放者的仇恨值
        calToMasterHatredEndST(pMasterAttrSet, type, valueST, otherPara, fixedHateValue);

		//同步 治疗量 
		syncSkillTreatST(treatSCharacter, masterSCharacter, type, valueST, fixedHateValue, buffId, addNum, permillage);
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::calToMasterHatredST( AttributeSet* pMasterAttr, Flt otherPara[ATTR_PARA_NUM], Int& fixedHateValue  )
    {
        //从技能模板获取固定仇恨值。1051
		otherPara[0] = fixedHateValue;
        //计算仇恨值
        const AttrParaInfo* pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1051);
        fixedHateValue = AttributeFormula::getInstance().calValue(
			pMasterAttr,
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			NULL, 
			otherPara
			);
    }
 
    //--------------------------------------------------------------------------
    void SAttributeSystem::calSkillTreatST( AttributeSet* pMasterAttr, Flt& valST, U32 formulaParaID )
    {
        const AttrParaInfo* pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(formulaParaID);
        valST = AttributeFormula::getInstance().calValue(
			pMasterAttr, 
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId
			);
    }
    //--------------------------------------------------------------------------
    MG::TREAT_ROUND_TYPE SAttributeSystem::calRoundTabST( AttributeSet* pMasterAttr, Flt otherPara[ATTR_PARA_NUM] )
    {
        //初始化
        const AttrParaInfo* pAttrParaInfo = NULL;
        //Flt region[4];
        //for (Int i=0; i<4; i++)
        //    region[i] = 0.f;

        //获得固定区间
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1052);
        memcpy(otherPara, pAttrParaInfo->para, sizeof(Flt)*2);

        //获得重击区间。
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1053);
        otherPara[2] = AttributeFormula::getInstance().calValue(
			pMasterAttr, 
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			NULL,
			otherPara
			);

        //获得剩余区间。
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1054);
        otherPara[3] = AttributeFormula::getInstance().calValue(
			pMasterAttr, 
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			NULL,
			otherPara
			);

        //获得随机数。
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1055);
        Int randVal = AttributeFormula::getInstance().calValue(
			pMasterAttr, 
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			NULL,
			otherPara
			);

        //随机类型
        Int randRefe = 0;
        for (Int i=0; i<4; i++)
        {
            randRefe += otherPara[i];
            if ( randVal < randRefe )
                return changeToSTRTypeST(i);
        }

        return  TREAT_ROUND_TYPE_HIT;
    }
    //--------------------------------------------------------------------------
    MG::TREAT_ROUND_TYPE SAttributeSystem::changeToSTRTypeST( UInt index )
    {
        if ( 0 == index  ||  3 == index )
            return TREAT_ROUND_TYPE_HIT;
        else if ( 1 == index  ||  2 == index )
            return TREAT_ROUND_TYPE_THUMP;
		else
			DYNAMIC_ASSERT(0);
		return TREAT_ROUND_TYPE_HIT;
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::calTreatBySTRTypeST( AttributeSet* pMasterAttr, AttributeSet* pTreatAttr, Flt& valST, TREAT_ROUND_TYPE strType, Flt otherPara[ATTR_PARA_NUM] )
    {
		const AttrParaInfo* pAttrParaInfo = NULL;

        if ( TREAT_ROUND_TYPE_HIT == strType )
        {
            pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1057);
        }
        else
        {
            pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1056);
        }

        otherPara[0] = valST;
        valST = AttributeFormula::getInstance().calValue(
			pMasterAttr, 
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			pTreatAttr,
			otherPara
			);
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::calFinalSkillTreatST( AttributeSet* pMasterAttr, AttributeSet* pTreatAttr, Flt& valST, Flt otherPara[ATTR_PARA_NUM] )
    {
        otherPara[0] = valST;
        const AttrParaInfo* pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1058);
		valST = AttributeFormula::getInstance().calValue(
			pMasterAttr, 
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			pTreatAttr,
			otherPara
			);
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::syncSkillTreatST( SCharacter* treatSCharacter, SCharacter* masterSCharacter, DamageType type, Flt valST, Int fixedHateValue, UInt buffId, UInt addNum, UInt permillage )
    {
		if (type == DT_HP)
		{    
			treatSCharacter->setHp(treatSCharacter->getHp() + valST);
		}
		else if ( type == DT_MP )
		{
			treatSCharacter->setMp(treatSCharacter->getMp() + valST);
		}
		else if ( type == DT_HPMP )
		{
			treatSCharacter->setHp(treatSCharacter->getHp() + valST);
			treatSCharacter->setMp(treatSCharacter->getMp() + valST);
		}
		else
		{
			DYNAMIC_ASSERT(0);
			return;
		}

        //发送
        SAttributePacketProcesser::getInstance().syncCharacterHPMPSPToClient(treatSCharacter, masterSCharacter, type, valST, ATTACK_RESULT_TYPE_RECOVER, fixedHateValue);
		if ( valST )
		{	
			SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(treatSCharacter->getFrontServerId(), treatSCharacter, type, valST, ATTACK_RESULT_TYPE_RECOVER);
			if ( buffId  == 0 ) return;
			if ( addNum == 0 ) return;
			if ( permillage == 0 ) return;
			UInt tempRandom = MGRandom::getInstance().rand_ab_One(0, THOUSAND_VALUE);
			if ( tempRandom <= permillage )
				treatSCharacter->getSBuffManager()->addNewBuff(buffId, addNum, treatSCharacter->getLevel());
		}
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::calToMasterHatredEndST( AttributeSet* pMasterAttr, DamageType type, Flt valST, Flt otherPara[ATTR_PARA_NUM], Int& fixedHateValue )
    {
        if (type == DT_HP)
        {    
            otherPara[0] = valST;
            otherPara[1] = 0.f;
        }
        else if ( type == DT_MP )
        {
            otherPara[0] = 0.f;
            otherPara[1] = valST;
        }
        else if ( type == DT_HPMP )
        {
            otherPara[0] = valST;
            otherPara[1] = valST;
        }
        else
        {
			DYNAMIC_ASSERT(0);
            return;
        }

        const AttrParaInfo* pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1059);
        fixedHateValue += AttributeFormula::getInstance().calValue(
			pMasterAttr, 
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			NULL,
			otherPara
			);

    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::itemTreat( SCharacter* treatSCharacter, DamageType type, Int treatValue )
    {
  //      Flt otherPara[ATTR_PARA_NUM];
  //      for (Int i=0; i<ATTR_PARA_NUM; i++)
  //          otherPara[i] = 0.f;

  //      AttributeSet* pMasterAttributeSet =  treatPeople->getAttributeSet();

  //      //治疗圆桌判定
  //      TREAT_ROUND_TYPE itrType = calRoundTabIT(otherPara);

  //      ////根据 TREAT_ROUND_TYPE 计算治疗量
  //      calTreatBySTRTypeIT(treatValue, itrType, otherPara);

		//Int fixHeatVal = 0;
		////计算非武将对释放者的仇恨值
		//calToMasterHatredIT(treatPeople, type, treatValue, otherPara, fixHeatVal);

        //同步 治疗量
        syncItemTreatIT(treatSCharacter, type, treatValue, 0);  

    }
	

    //--------------------------------------------------------------------------
    MG::TREAT_ROUND_TYPE SAttributeSystem::calRoundTabIT( Flt otherPara[ATTR_PARA_NUM] )
    {
        ////初始化
        //const AttrParaInfo* pAttrParaInfo = NULL;
        //Flt region[4];
        //for (Int i=0; i<4; i++)
        //    region[i] = 0.f;

        ////固定区间
        //pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(251);
        //memcpy((void*)region, (void*)pAttrParaInfo->para, sizeof(Flt)*2);
        //
        ////剩余区间
        //pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(252);
        //memcpy((void*)otherPara, (void*)region, sizeof(Flt)*2);
        //region[2] = AttributeFormula::getInstance().calValue(getCalAttrInfo(), pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, getCalAttrInfo(), otherPara);

        ////随机数
        //pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(253);
        //Flt randVal = AttributeFormula::getInstance().calValue(getCalAttrInfo(), pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId);

        ////随机类型
        //Int randRefe = 0;
        //for (Int i=0; i<4; i++)
        //{
        //    randRefe += region[i];
        //    if ( randVal < randRefe )
        //        return changeToSTRTypeST(i);
        //}

        return  TREAT_ROUND_TYPE_HIT;
    }
    //--------------------------------------------------------------------------
    MG::TREAT_ROUND_TYPE SAttributeSystem::changeToSTRTypeIT( UInt index )
    {
        if ( 0 == index  ||  3 == index )
            return TREAT_ROUND_TYPE_HIT;
        else if ( 1 == index )
            return TREAT_ROUND_TYPE_THUMP;
		else
			return TREAT_ROUND_TYPE_HIT;
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::calTreatBySTRTypeIT( Int& valST, TREAT_ROUND_TYPE itrType, Flt otherPara[ATTR_PARA_NUM] )
    {
       ///* const AttrParaInfo* pAttrParaInfo = NULL;

       // if ( TREAT_ROUND_TYPE_HIT == itrType )
       // {
       //     pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(254);
       // }
       // else
       // {
       //     pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(255);
       // }

       // otherPara[0] = valST;
       // valST = AttributeFormula::getInstance().calValue(getCalAttrInfo(), pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, getCalAttrInfo(), otherPara);*/

    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::syncItemTreatIT( SCharacter* treatSCharacter, DamageType type, Int valST, Int fixedHateValue )
    {
		if (type == DT_HP)
		{    
			treatSCharacter->setHp(treatSCharacter->getHp() + valST);
		}
		else if ( type == DT_MP )
		{
			treatSCharacter->setMp(treatSCharacter->getMp() + valST);
		}
		else
		{
			DYNAMIC_ASSERT(0);
			return;
		}
        //发送
        SAttributePacketProcesser::getInstance().syncCharacterHPMPSPToClient(treatSCharacter, treatSCharacter, type, valST, ATTACK_RESULT_TYPE_RECOVER, fixedHateValue);
		if ( valST )
		{
			SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(treatSCharacter->getFrontServerId(), treatSCharacter, type, valST, ATTACK_RESULT_TYPE_RECOVER);
		}	
		
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::calToMasterHatredIT( SCharacter* treatPeople, DamageType type, Int valST, Flt otherPara[ATTR_PARA_NUM], Int& fixedHateValue )
    {
        if (type == DT_HP)
        {    
            otherPara[0] = valST;
            otherPara[1] = 0.f;
        }
        else if ( type == DT_MP )
        {
            otherPara[0] = 0.f;
            otherPara[1] = valST;
        }
        else if ( type == DT_HPMP )
        {
            otherPara[0] = valST;
            otherPara[1] = valST;
        }
        else
        {
            return;
        }

        const AttrParaInfo* pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(256);
        //fixedHateValue = AttributeFormula::getInstance().calValue(getCalAttrInfo(), pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, getCalAttrInfo(), otherPara);

        //处理仇恨值
        //？
    }
	//--------------------------------------------------------------------------
	MG::STATUS_VITIATEFLAG SAttributeSystem::changeToSVFTypeOD( AttackType type )
	{
		//DYNAMIC_ASSERT(0);
		return (STATUS_VITIATEFLAG)((Int)type);
	}
	//--------------------------------------------------------------------------
	void SAttributeSystem::calCorpsHurtOD( SCharacter* pMasterSCharacter, SCharacter* pHurtSCharacter, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM] )
	{
		//1021--1026
		TROOPTEMPLATE_TYPE armyType = changeToArmyTypeOD(pMasterSCharacter);
		DYNAMIC_ASSERT(armyType>TROOPTEMPLATE_TYPE_NULL  &&  armyType<TROOPTEMPLATE_TYPE_MAX);

		const AttrParaInfo* pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1020+armyType);
		DYNAMIC_ASSERT(pAttrParaInfo);
		
		otherPara[0] = hitValue;
		hitValue = AttributeFormula::getInstance().calValue(
			pMasterSCharacter->getAttributeSet(),
			pMasterSCharacter->getCharacterData(),
			pAttrParaInfo->para,
			pAttrParaInfo->attrID,
			pAttrParaInfo->FormulaId,
			pHurtSCharacter->getAttributeSet(),
			otherPara,
			pHurtSCharacter->getCharacterData()
			);
	}
	//--------------------------------------------------------------------------
	MG::TROOPTEMPLATE_TYPE SAttributeSystem::changeToArmyTypeOD( SCharacter* pMasterSCharacter )
	{
		if ( pMasterSCharacter->getType() == GOT_TROOP  ||  pMasterSCharacter->getType() == GOT_SOLDIER )
		{
			TROOPTEMPLATE_TYPE armyType = pMasterSCharacter->getCharacterTempInfo()->getArmyArmyType();
			if ( armyType > TROOPTEMPLATE_TYPE_OTHER )
				return TROOPTEMPLATE_TYPE_OTHER;
			else
				return armyType;
		}
		else
			return TROOPTEMPLATE_TYPE_OTHER;
	}
	//--------------------------------------------------------------------------
	MG::STATUS_ABSORBTYPE SAttributeSystem::changeToSAbsorbType( AttackType attackType )
	{
		//DYNAMIC_ASSERT(0);
		return STATUS_ABSORBTYPE((Int)(attackType));
	}
	//--------------------------------------------------------------------------
	void SAttributeSystem::sendObjAttr( SCharacter* hurtSCharacter, SCharacter* masterSCharacter, DamageType damageType, Int value, ATTACK_RESULT_TYPE arType, Int hateVal, UInt buffId, UInt addNum, UInt permillage  )
	{
	    if ( arType == ATTACK_RESULT_TYPE_HURT )
		{
			//修正蓝值
			if ( damageType == DT_MP )
			{
				hurtSCharacter->setMp(hurtSCharacter->getMp() - value);
			}
			//修正血值
			else if ( damageType == DT_HP )
			{
				hurtSCharacter->setHp(hurtSCharacter->getHp() - value, masterSCharacter);
				if ( hurtSCharacter->getHp() == 0 )
					arType = ATTACK_RESULT_TYPE_DEAD;
			} 
			else if ( damageType == DT_HPMP )    
			{
				//修正血值
				hurtSCharacter->setHp(hurtSCharacter->getHp() - value, masterSCharacter);
				if ( hurtSCharacter->getHp() == 0 )
					arType = ATTACK_RESULT_TYPE_DEAD;
				//修正蓝值
				hurtSCharacter->setMp(hurtSCharacter->getMp() - value);
			}
			else
				DYNAMIC_ASSERT(0);
		}
	    
	   SAttributePacketProcesser::getInstance().syncCharacterHPMPSPToClient(hurtSCharacter, masterSCharacter, damageType, value, arType, hateVal);
	   SAttributePacketProcesser::getInstance().sendCharacterDamageToFrontServer(hurtSCharacter, damageType, value, arType);  
	   if ( buffId  == 0 ) return;
	   if ( addNum == 0 ) return;
	   if ( permillage == 0 ) return;
	   UInt tempRandom = MGRandom::getInstance().rand_ab_One(0, THOUSAND_VALUE);
	   if ( tempRandom <= permillage )
			hurtSCharacter->getSBuffManager()->addNewBuff(buffId, addNum, hurtSCharacter->getLevel());    
	}
}