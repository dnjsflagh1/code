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

		//����tempID���ϸ���ֵ��
		const CharacterTempInfo* mCharacterTempInfo = pCharacter->getCharacterTempInfo();
		assert(mCharacterTempInfo);

		//��ʼ������
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

				//���ж����ͣ���ѡ����㷽����
				tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
				mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
			}
		}

		//��������
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

				//���ж����ͣ���ѡ����㷽����
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

		//�������
		{
			Flt tempVal = 0;
			const AttributeInitInfo* pAAinfo = NULL;

			//�����������
			UInt randId = pCharacter->getDBAttrInitID();
			if ( 0 != randId )
			{
				pAAinfo = AttributeInit::getInstance().getAttributeInitInfo( randId );
				DYNAMIC_ASSERT(pAAinfo);
				for ( Int j=0; j<APPENDATTR_NUM; j++ )
				{
					if ( 0 == pAAinfo->AppendAttrList[j].id )
						continue;
					//���ж����ͣ���ѡ����㷽����
					tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
					mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pCharacter->getDBAttrInit(j) + tempVal );
				}
			}

			//�����������
			UInt randAddId = pCharacter->getDBAttrLvlAddID();
			if ( 0 != randAddId )
			{	
				pAAinfo = AttributeInit::getInstance().getAttributeInitInfo( randAddId );
				DYNAMIC_ASSERT(pAAinfo);
				for ( Int j=0; j<APPENDATTR_NUM; j++ )
				{
					if ( 0 == pAAinfo->AppendAttrList[j].id )
						continue;
					//���ж����ͣ���ѡ����㷽����
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
		//	//			//�Լ��ı���ֵ
		//	//			tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
		//	//			//���ֵ
		//	//			if ( j < DB_RECORD_ATTR_NUM )
		//	//				tempRandVal = pCharacter->getDBAttrInit(j);
		//	//			else
		//	//				tempRandVal = 0;
		//	//			//����ֵ
		//	//			mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, tempRandVal + tempVal );
		//	//		}
		//	//	}
		//	//	else if ( LVADD_RAND_INDEX == i )
		//	//	{
		//	//		for ( Int j=0; j<APPENDATTR_NUM; j++ )
		//	//		{
		//	//			if ( 0 == pAAinfo->AppendAttrList[j].id )
		//	//				continue;
		//	//			//�Լ��ı���ֵ
		//	//			tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
		//	//			//���ֵ
		//	//			if ( j < DB_RECORD_ATTR_NUM )
		//	//				tempRandVal = pCharacter->getDBAttrLvlAdd(j);
		//	//			else
		//	//				tempRandVal = 0;
		//	//			//����ֵ
		//	//			mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, tempRandVal + tempVal );
		//	//		}
		//	//	}
		//	//	else
		//	//	{
		//	//		for ( Int j=0; j<APPENDATTR_NUM; j++ )
		//	//		{
		//	//			//���ж����ͣ���ѡ����㷽����
		//	//			tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
		//	//			mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
		//	//		}
		//	//	}
		//	//}
		//	//else
		//	{
		//		//�����
		//		for ( Int j=0; j<APPENDATTR_NUM; j++ )
		//		{
		//			//���ж����ͣ���ѡ����㷽����
		//			tempVal =  mCalAttrInfo->getFanalValue( pAAinfo->AppendAttrList[j].id );
		//			mCalAttrInfo->setFanalValue( pAAinfo->AppendAttrList[j].id, pAAinfo->AppendAttrList[j].value + tempVal );
		//		}
		//	} 
		//}

		////�ڸ���Ѫ�����ϸ���ֵ
		//const LineageInfo* pLginfo = LineageTemplate::getInstance().getAttrAppendInfo(lineageAppendAttrid);
		//assert(pLginfo);
		//if ( pLginfo->abilityGroupAppendId != 0 )
		//{
		//    const AttributeAppendInfo* pAAinfo = AttributeAppend::getInstance().getAttributeAppendInfo( pLginfo->abilityGroupAppendId );
		//    assert(pAAinfo);
		//    for ( Int j=0; j<APPENDATTR_NUM; j++ )
		//    {
		//        //���ж����ͣ���ѡ����㷽����
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
		//ֱ�Ӽ��Ŀ���ɫ����Ѫ�������û�оͽ����������̡�
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

        /*Sprintf_s(tempMsg, 128, "�˺������� = %d\n", hurtPeoper->getType());
        MG_LOG(out_sys, tempMsg);
        Sprintf_s(tempMsg, 128, "���������� = %d\n", master->getType());
        MG_LOG(out_sys, tempMsg);*/
        //-------------------------------------------------------------------

        AttributeSet* pHurtAttributeSet = getCalAttrInfo();
        AttributeSet* pMasterAttributeSet = masterSCharacter->getAttributeSet();
        const AttrParaInfo* pAttrParaInfo = NULL;

        //��ʼ��
        Flt otherPara[ATTR_PARA_NUM];
        for (Int i=0; i<ATTR_PARA_NUM; i++)
            otherPara[i] = 0.f;

        //�����޹�ʽ101
        calStartHatredOD(pMasterAttributeSet, fixedHateValue, otherPara);

        //�Ƿ�������״̬
        if ( checkImmunoStatusOD(hurtSCharacter, attacktype) )
        {
			sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_INVALID, fixedHateValue);
            return;
        }

        //��ó�������ֵ��
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(formulaParaID);
        DYNAMIC_ASSERT(pAttrParaInfo);
        Flt hurtValue = AttributeFormula::getInstance().calValue( pMasterAttributeSet, masterSCharacter->getCharacterData(), pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId );
        /*Sprintf_s(tempMsg, 128, "�״μ���Ĺ���ֵ = %f\n", tempValue);
        MG_LOG(out_sys, tempMsg);*/
        
        //Բ���ж���
        FIGHT_ROUND_TYPE frType = calRoundTabOD(masterSCharacter, hurtSCharacter, otherPara);
        /*Sprintf_s(tempMsg, 128, "Բ���ж��ж����� = %d\n", frType);
        MG_LOG(out_sys, tempMsg);*/

		//���������߷����Թ����ļ��⼰�˺�����
		calDefenseReduceHurtOD(pHurtAttributeSet, pMasterAttributeSet, attacktype, hurtValue, otherPara);

        //����FIGHT_ROUND_TYPE�����˺�ֵ��
        if ( calHitByFRTypeOD(pHurtAttributeSet, pMasterAttributeSet, hurtValue, frType, otherPara) )
        {   
            //���Ͷ����Ϣ��
			sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_DODGE, fixedHateValue);
            return;
        }
        /*Sprintf_s(tempMsg, 128, "Բ���ж�����˺�ֵ = %f\n", tempValue);
        MG_LOG(out_sys, tempMsg);*/

        

       /* Sprintf_s(tempMsg, 128, "���������߷����Թ����ļ��⼰�˺����� = %f\n", tempValue);
        MG_LOG(out_sys, tempMsg);*/

        //���������߷����˺�
        calDirectionHurtOD(pHurtAttributeSet, pMasterAttributeSet, attackPos, hurtValue, otherPara);

        //Sprintf_s(tempMsg, 128, "���������߷����˺� = %f\n", tempValue);
        //MG_LOG(out_sys, tempMsg);
		//�����˺���
		calCorpsHurtOD(masterSCharacter, hurtSCharacter, hurtValue, otherPara);

		//�˺�������ϡ�
		//---------------------------------------------------------------------------------

        //����������ȫ�˺�����
        if ( calCompleteAbsorbHurtOD(hurtSCharacter, hurtValue) ) 
        { 
            //����������Ϣ
			sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_ABSORB, fixedHateValue);
            /*Sprintf_s(tempMsg, 128, "����������ȫ�˺����� = %f\n", tempValue);
            MG_LOG(out_sys, tempMsg);*/

            return;
        }

        //���������߷�����������
        if ( calMagicShieldAbsorbHurtOD(hurtSCharacter, hurtValue) )
        {
            //����������Ϣ
			sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_ABSORB, fixedHateValue);
            
           /* Sprintf_s(tempMsg, 128, "���������߷����������� = %f\n", tempValue);
            MG_LOG(out_sys, tempMsg);*/
            
            return;
        }

        //���������߶�Ӧ�˺���������
        if ( calAttTypeAbsorbHurtOD(hurtSCharacter, hurtValue, attacktype) )
        {
            //����������Ϣ
			sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_ABSORB, fixedHateValue);
            
            /*Sprintf_s(tempMsg, 128, "���������߶�Ӧ�˺��������� = %f\n", tempValue);
            MG_LOG(out_sys, tempMsg);*/

            return;
        }

		//״̬������Ѫ��������
		//?

		//���������߶��ͷ��ߵĳ��ֵ
		calToMasterHatredOD(pMasterAttributeSet, damageType, hurtValue, otherPara, fixedHateValue);

		//���������߿ۼ�Ѫ����Ϣ
		sendObjAttr(hurtSCharacter, masterSCharacter, damageType, hurtValue, ATTACK_RESULT_TYPE_HURT, fixedHateValue);

        
        //----------------------------------------------------------------------------------------
       /* Sprintf_s(tempMsg, 128, "���Լ������\n");
        MG_LOG(out_sys, tempMsg);*/
        //----------------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::calStartHatredOD(AttributeSet* pMasterAttr, Int& fixedHateValue, Flt otherPara[ATTR_PARA_NUM])
    {
		////1001��ʽ��
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

        //�����ʽ1002
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

        ////�̶����� ��ʽ1003
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1003);
		memcpy(&otherPara[1], pAttrParaInfo->para, sizeof(Flt)*3);

        ////������� ��ʽ1004
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

        ////�ػ����� ��ʽ1005
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1005);
        otherPara[5] = AttributeFormula::getInstance().calValue(
			pMasterSCharacter->getAttributeSet(),
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId,
			pHurtSCharacter->getAttributeSet(),
			otherPara,
			NULL
			);

        ////ʣ������ ��ʽ1006
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

        ////������䡣��ʽ1007
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1007);
        Int randValue = AttributeFormula::getInstance().calValue(
			pMasterSCharacter->getAttributeSet(),
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId
			);

        ////�������
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

		//ȫ�˺����ջ���
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
				//״̬�Ƴ�
				pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_ALL);
				//���̽���
				return true;
			}
			else
			{
				pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_ALL, 0);
				hitValue -= allAbsorbVal;
				//״̬�Ƴ�
				pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_ALL);
				//���̼���
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

		//��������
		Int magicAbsorbVal = pHurtAttrSys->getShieldByType(STATUS_ABSORBTYPE_MAGIC);
		if (magicAbsorbVal > 0)
		{
			if ( magicAbsorbVal > pCharacterData->mMp )
			{
				if ( pCharacterData->mMp > (Int)hitValue  )
				{
					pCharacterData->mMp -= (Int)hitValue;
					pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_MAGIC,magicAbsorbVal-(Int)hitValue);
					//�Ƿ���Ҫ��ͻ��˷�������MP����Ϣ
					//?
					hitValue = 0;
					//���̽���
					return true;
				}
				else if ( pCharacterData->mMp == (Int)hitValue )
				{
					pCharacterData->mMp = 0;
					pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_MAGIC,0);
					//�Ƿ���Ҫ��ͻ��˷�������MP����Ϣ
					//?
					hitValue = 0;
					//״̬�Ƴ�
					pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
					//���̽���
					return true;
				}
				else
				{
					hitValue -= pCharacterData->mMp;
					pCharacterData->mMp = 0;
					pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_MAGIC,0);
					//�Ƿ���Ҫ��ͻ��˷�������MP����Ϣ
					//?
					//״̬�Ƴ�
					pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
					//���̼���
					return false;
				}
			}
			else
			{
				if ( magicAbsorbVal > (Int)hitValue )
				{
					pCharacterData->mMp -= (Int)hitValue;
					pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_MAGIC,magicAbsorbVal-(Int)hitValue);
					//�Ƿ���Ҫ��ͻ��˷�������MP����Ϣ
					//?
					hitValue = 0;
					//���̽���
					return true;
				}
				else if ( magicAbsorbVal == (Int)hitValue )
				{
					pCharacterData->mMp -= (Int)hitValue;
					pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_MAGIC,0);
					//�Ƿ���Ҫ��ͻ��˷�������MP����Ϣ
					//?
					hitValue = 0;
					//״̬�Ƴ�
					pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
					//���̽���
					return true;
				}
				else
				{
					hitValue -= magicAbsorbVal;
					pCharacterData->mMp -= magicAbsorbVal;
					pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_MAGIC,0);
					//�Ƿ���Ҫ��ͻ��˷�������MP����Ϣ
					//?
					//״̬�Ƴ�
					pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
					//���̼���
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

		//�˺��������ջ���
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
				//״̬�Ƴ�
				pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(absorbType);
				//���̽���
				return true;
			}
			else
			{
				pHurtAttrSys->setShieldByType(absorbType, 0);
				hitValue -= attackAbsorbVal;
				//״̬�Ƴ�
				pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(absorbType);
				//���̼���
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

        //������佫���ͷ��ߵĳ��ֵ��
        calToMasterHatredST(pMasterAttrSet, otherPara, fixedHateValue);

        Flt valueST = 0.f;
        // ����ʩչ����ɵ�������
        calSkillTreatST(pMasterAttrSet, valueST, formulaParaID);

        // ����Բ���ж�
        TREAT_ROUND_TYPE strType = calRoundTabST(pMasterAttrSet, otherPara);

        //���� TREAT_ROUND_TYPE ����������
        calTreatBySTRTypeST(pMasterAttrSet, ptreatAttrSet, valueST, strType, otherPara);

        // �������� ������
        calFinalSkillTreatST(pMasterAttrSet, ptreatAttrSet, valueST, otherPara); 

        //������佫���ͷ��ߵĳ��ֵ
        calToMasterHatredEndST(pMasterAttrSet, type, valueST, otherPara, fixedHateValue);

		//ͬ�� ������ 
		syncSkillTreatST(treatSCharacter, masterSCharacter, type, valueST, fixedHateValue, buffId, addNum, permillage);
    }
    //--------------------------------------------------------------------------
    void SAttributeSystem::calToMasterHatredST( AttributeSet* pMasterAttr, Flt otherPara[ATTR_PARA_NUM], Int& fixedHateValue  )
    {
        //�Ӽ���ģ���ȡ�̶����ֵ��1051
		otherPara[0] = fixedHateValue;
        //������ֵ
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
        //��ʼ��
        const AttrParaInfo* pAttrParaInfo = NULL;
        //Flt region[4];
        //for (Int i=0; i<4; i++)
        //    region[i] = 0.f;

        //��ù̶�����
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1052);
        memcpy(otherPara, pAttrParaInfo->para, sizeof(Flt)*2);

        //����ػ����䡣
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1053);
        otherPara[2] = AttributeFormula::getInstance().calValue(
			pMasterAttr, 
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			NULL,
			otherPara
			);

        //���ʣ�����䡣
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1054);
        otherPara[3] = AttributeFormula::getInstance().calValue(
			pMasterAttr, 
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			NULL,
			otherPara
			);

        //����������
        pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1055);
        Int randVal = AttributeFormula::getInstance().calValue(
			pMasterAttr, 
			NULL,
			pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, 
			NULL,
			otherPara
			);

        //�������
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

        //����
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

  //      //����Բ���ж�
  //      TREAT_ROUND_TYPE itrType = calRoundTabIT(otherPara);

  //      ////���� TREAT_ROUND_TYPE ����������
  //      calTreatBySTRTypeIT(treatValue, itrType, otherPara);

		//Int fixHeatVal = 0;
		////������佫���ͷ��ߵĳ��ֵ
		//calToMasterHatredIT(treatPeople, type, treatValue, otherPara, fixHeatVal);

        //ͬ�� ������
        syncItemTreatIT(treatSCharacter, type, treatValue, 0);  

    }
	

    //--------------------------------------------------------------------------
    MG::TREAT_ROUND_TYPE SAttributeSystem::calRoundTabIT( Flt otherPara[ATTR_PARA_NUM] )
    {
        ////��ʼ��
        //const AttrParaInfo* pAttrParaInfo = NULL;
        //Flt region[4];
        //for (Int i=0; i<4; i++)
        //    region[i] = 0.f;

        ////�̶�����
        //pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(251);
        //memcpy((void*)region, (void*)pAttrParaInfo->para, sizeof(Flt)*2);
        //
        ////ʣ������
        //pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(252);
        //memcpy((void*)otherPara, (void*)region, sizeof(Flt)*2);
        //region[2] = AttributeFormula::getInstance().calValue(getCalAttrInfo(), pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, getCalAttrInfo(), otherPara);

        ////�����
        //pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(253);
        //Flt randVal = AttributeFormula::getInstance().calValue(getCalAttrInfo(), pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId);

        ////�������
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
        //����
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

        //������ֵ
        //��
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
			//������ֵ
			if ( damageType == DT_MP )
			{
				hurtSCharacter->setMp(hurtSCharacter->getMp() - value);
			}
			//����Ѫֵ
			else if ( damageType == DT_HP )
			{
				hurtSCharacter->setHp(hurtSCharacter->getHp() - value, masterSCharacter);
				if ( hurtSCharacter->getHp() == 0 )
					arType = ATTACK_RESULT_TYPE_DEAD;
			} 
			else if ( damageType == DT_HPMP )    
			{
				//����Ѫֵ
				hurtSCharacter->setHp(hurtSCharacter->getHp() - value, masterSCharacter);
				if ( hurtSCharacter->getHp() == 0 )
					arType = ATTACK_RESULT_TYPE_DEAD;
				//������ֵ
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