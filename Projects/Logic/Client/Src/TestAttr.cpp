//**************************************************************************************************
#include "stdafx.h"
#include "TestAttr.h"
#include "CPlayer.h"
#include "CClan.h"
#include "CPlayerCharacter.h"
#include "CCharacter.h"
#include "AttributeList.h"
#include "CharacterList.h"
#include "AttributeFormula.h"
#include "AttributePara.h"
#include "AttributeSystem.h"
#include "ClientMain.h"
#include "AttributeAppend.h"
#include "GeneralRecruitSystem.h"
#include "GeneralRandomCsv.h"
#include "GeneralRecruitCsv.h"
//**************************************************************************************************

namespace MG
{
    MG::Bool TestAttr::init()
    {
		GeneralRandomCsv::getInstance().load(L"Config\\Game\\Character\\GeneralRandom.csv");
		GeneralRecruitCsv::getInstance().load(L"Config\\Game\\Character\\GeneralRecruit.csv");
        mHurtRoleIndex = 1;
        mSpeed = 1;
        CreateClan();

        return true;
    }
	//-----------------------------------------------------------------------------------------
	void TestAttr::CreateClan()
	{
		ClanData clandata;
		clandata.clanId = 1;
		clandata.clanbagSize = 40;

		CPlayer::getInstance().addClan(&clandata);
		CPlayer::getInstance().setActive(1);
	}
	//-----------------------------------------------------------------------------------------
	void TestAttr::CreateCharacter()
	{
		//ɾ�����н�ɫ
		CPlayer::getInstance().getActiveClan()->removeAllPlayerCharacter();

		//������
		PlayerCharacterData tempData;
		CPlayerCharacter* pCharacter = NULL;
		int tempLv = 1;
		char filename[64] = "";
		char msg[128] = "";
		CClan* activeClan = CPlayer::getInstance().getActiveClan();

		std::map<U32, CharacterTempInfo*>::iterator front = CharacterTemplate::getInstance().mMapCharacterTempInfoNew.begin();
		std::map<U32, CharacterTempInfo*>::iterator back = CharacterTemplate::getInstance().mMapCharacterTempInfoNew.end();
		while (front != back)
		{
			if ( front->second->CharacterType != CHARACTER_TYPE_GENREAL )
			{	
				++front;
				continue;
			}

			GeneralRecruitSystem::getInstance().reFresh((RECRUIT_POSITION)1);
			CharAttrInfo* charAttrInfo = GeneralRecruitSystem::getInstance().getCharAttrInfoByIndex((RECRUIT_POSITION)1);

			//�������
			tempData.mCharacterTemplateID = front->first;
			tempData.mId = front->first;
			tempData.mLevel = 1;
			/*if ( tempData.mLevel > 100 )
			{
				tempData.mLevel = 1;
				tempLv = 2;
			}*/
			tempData.charAttrAppendId		=	charAttrInfo->charAttrAppendId;
			tempData.charAttrAppendLvlAddId	=	charAttrInfo->charAttrAppendLvlAddId;

			for (Int i=0; i<DB_RECORD_ATTR_NUM; ++i)
			{
				tempData.charAttrRand[i] = charAttrInfo->charAttrRand[i];
				tempData.charAttrRandAdd[i] = charAttrInfo->charAttrRandAdd[i];
			}

			

			//������ɫ
			Bool isfirst = true;
			pCharacter = activeClan->addPlayerCharacter(&tempData, isfirst);
			DYNAMIC_ASSERT(isfirst == true);

			//�������ԡ�
			
			pCharacter->init(&tempData);

			++front;
		}
	}
    //-----------------------------------------------------------------------------------------
    MG::Bool TestAttr::update( Flt delta )
    {
        if(ClientMain::getInstance().getEngine()->input()->isCtrlOn() == false)
        {
            return true;
        }

        if(ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_X ))
        {
            CreateCharacter();
        }

        if (ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_K ))
        {
            TestCalAttr();
        }

        if (ClientMain::getInstance().getEngine()->input()->isKeyReleased( KC_C ))
        {
            TestFightAttr();
        }

        return true;
    }
    //-----------------------------------------------------------------------------------------
    MG::Bool TestAttr::TestCalAttr()
    {
        char filename[64] = "";
        char msg[128] = "";
        Str8 name;
        CClan* activeClan = CPlayer::getInstance().getActiveClan();
        CPlayerCharacter* pCharacter = NULL;

        std::map<U64, CPlayerCharacter*>* pCharacterList =	activeClan->getPlayerCharacterList();
        std::map<U64, CPlayerCharacter*>::iterator front = pCharacterList->begin();
        std::map<U64, CPlayerCharacter*>::iterator back = pCharacterList->end();
        while (front != back)
        {
            pCharacter = front->second;

            //�����ı�
            sprintf( filename, "CharAttr%d.test",  front->first);
            FILE* fp = NULL;
            fopen_s(&fp, filename, "w");
            assert(fp);

            //��д����
            sprintf(msg, "��ɫ�ȼ� = %d, ��ɫģ�� = %d.\n\n", pCharacter->getData()->mLevel, front->first);
            fputs(msg, fp);

            //��ӡ����
            for (Int i=1; i<ATTR_ID_MAX; i++)
            {
                const AttrInfo* tempAttrInfo = AttributeList::getInstance().getAttrInfo((ATTR_ID)i);
                MGStrOp::toString( tempAttrInfo->attrChName.c_str(), name );
                sprintf(msg, "%25s = %5d, value = %10d.\n", name.c_str(), i, pCharacter->getFanalValue(i));
                fputs(msg, fp);
            }

            //�ص��ı�
            fclose(fp);

            ++front;
        }

        return true;
    }
	
    //-----------------------------------------------------------------------------------------
    MG::Bool TestAttr::TestFightAttr()
    {
		U32 formulaParaID = 0;
        char filename[64] = "";
        char msg[128] = "";
        CPlayerCharacter* pCharacter = NULL;
        CClan* activeClan = CPlayer::getInstance().getActiveClan();

        //���ò���
        std::map<U64, CPlayerCharacter*>* pCharacterList =	activeClan->getPlayerCharacterList();   

        //for (Int i=1; i<9; i++)
        {
            //�������ͣ�����ID�Ͳ�����
            formulaParaID = 90001;

            std::map<U64, CPlayerCharacter*>::iterator front1 = pCharacterList->begin();
            std::map<U64, CPlayerCharacter*>::iterator back1 = pCharacterList->end();
            std::map<U64, CPlayerCharacter*>::iterator iter = front1;
            while (front1 != back1)
            {
                //�����ı�
                sprintf( filename, "CharHurt%I64d_%d.test",  front1->first, 1);
                FILE* fp = NULL;
                fopen_s(&fp, filename, "w");
                assert(fp);

                //���ñ���
                sprintf(msg, "��ɫ�ȼ� = %d, ��ɫģ�� = %d.\n\n", front1->second->getData()->mLevel, front1->first);
                fputs(msg, fp);

                sprintf(msg, "��ɫ�������� = %d, ��ɫ��ʽID = %d, ��ɫ�������� = ����, ��ɫ�˺����� = Ѫ.\n\n", 1, formulaParaID);
                fputs(msg, fp);

                
                obtainDamage(iter->second, front1->second, (AttackType)1, DT_HP, ATTACK_POS_FRONT, formulaParaID, 0, 0, 0, 0, fp);

                fclose(fp);
                ++front1;
            }
        }

        return true;
    }
	//--------------------------------------------------------------------------
	void TestAttr::obtainDamage( CCharacter* hurtSCharacter, CCharacter* masterSCharacter, AttackType attacktype, DamageType damageType, ATTACK_POS attackPos, U32 formulaParaID, Int fixedHateValue, UInt buffId, UInt addNum, UInt permillage, FILE* fp   )
	{
		//ֱ�Ӽ��Ŀ���ɫ����Ѫ�������û�оͽ����������̡�
		//Int curHp = hurtSCharacter->getHp();
		//if ( curHp <= 0 )
		//{	
		//	DYNAMIC_ASSERT(0);
		//	//hurtSCharacter->dead(masterSCharacter);
		//	return;
		//}
		//-------------------------------------------------------------------
		//print
		Char8 tempMsg[128]  = "";

		/*Sprintf_s(tempMsg, 128, "�˺������� = %d\n", hurtPeoper->getType());
		MG_LOG(out_sys, tempMsg);
		Sprintf_s(tempMsg, 128, "���������� = %d\n", master->getType());
		MG_LOG(out_sys, tempMsg);*/
		//-------------------------------------------------------------------

		AttributeSet* pHurtAttributeSet = hurtSCharacter->getAttributeSet();
		AttributeSet* pMasterAttributeSet = masterSCharacter->getAttributeSet();
		const AttrParaInfo* pAttrParaInfo = NULL;

		//��ʼ��
		Flt otherPara[ATTR_PARA_NUM];
		for (Int i=0; i<ATTR_PARA_NUM; i++)
			otherPara[i] = 0.f;

		//�����޹�ʽ101
		calStartHatredOD(pHurtAttributeSet, pMasterAttributeSet, fixedHateValue, otherPara);

		//�Ƿ�������״̬
		//if ( checkImmunoStatusOD(hurtSCharacter, attacktype) )
		//{
		//	//sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_INVALID, fixedHateValue);
		//	return;
		//}

		//��ó�������ֵ��
		pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(formulaParaID);
		DYNAMIC_ASSERT(pAttrParaInfo);
		Flt hurtValue = AttributeFormula::getInstance().calValue( pMasterAttributeSet, masterSCharacter->getCharacterData(), pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId );

		sprintf_s(tempMsg, 128, "��ʽId = %d���״μ���Ĺ���ֵ = %f\n", formulaParaID, hurtValue);
		fputs(tempMsg, fp);

		//Բ���ж���
		FIGHT_ROUND_TYPE frType = calRoundTabOD(masterSCharacter, hurtSCharacter, otherPara);

		sprintf_s(tempMsg, 128, "Բ���ж��ж����� = %d\n", frType);
		fputs(tempMsg, fp);

		//���������߷����Թ����ļ��⼰�˺�����
		calDefenseReduceHurtOD(pHurtAttributeSet, pMasterAttributeSet, attacktype, hurtValue, otherPara);

		sprintf_s(tempMsg, 128, "���������߷����Թ����ļ��⼰�˺����� = %f\n", hurtValue);
		fputs(tempMsg, fp);

		//����FIGHT_ROUND_TYPE�����˺�ֵ��
		if ( calHitByFRTypeOD(pHurtAttributeSet, pMasterAttributeSet, hurtValue, frType, otherPara) )
		{   
			//���Ͷ����Ϣ��
			//sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_DODGE, fixedHateValue);
			return;
		}

		sprintf_s(tempMsg, 128, "Բ���ж�����˺�ֵ = %f\n", hurtValue);
		fputs(tempMsg, fp);

		

		//���������߷����˺�
		calDirectionHurtOD(pHurtAttributeSet, pMasterAttributeSet, attackPos, hurtValue, otherPara);

		sprintf_s(tempMsg, 128, "���������߷����˺� = %f\n", hurtValue);
		fputs(tempMsg, fp);

		//�����˺���
		calCorpsHurtOD(masterSCharacter, hurtSCharacter, hurtValue, otherPara);

		sprintf_s(tempMsg, 128, "��������˺� = %f\n", hurtValue);
		fputs(tempMsg, fp);


		sprintf_s(tempMsg, 128, "------------------�˺��������-------------------------\n");
		fputs(tempMsg, fp);
		//�˺�������ϡ�
		//---------------------------------------------------------------------------------

		//����������ȫ�˺�����
		if ( calCompleteAbsorbHurtOD(hurtSCharacter, hurtValue) ) 
		{ 
			//����������Ϣ
			//sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_ABSORB, fixedHateValue);
			/*Sprintf_s(tempMsg, 128, "����������ȫ�˺����� = %f\n", tempValue);
			MG_LOG(out_sys, tempMsg);*/

			return;
		}

		//���������߷�����������
		if ( calMagicShieldAbsorbHurtOD(hurtSCharacter, hurtValue) )
		{
			//����������Ϣ
			//sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_ABSORB, fixedHateValue);

			/* Sprintf_s(tempMsg, 128, "���������߷����������� = %f\n", tempValue);
			MG_LOG(out_sys, tempMsg);*/

			return;
		}

		//���������߶�Ӧ�˺���������
		if ( calAttTypeAbsorbHurtOD(hurtSCharacter, hurtValue, attacktype) )
		{
			//����������Ϣ
			//sendObjAttr(hurtSCharacter, masterSCharacter, damageType, 0, ATTACK_RESULT_TYPE_ABSORB, fixedHateValue);

			/*Sprintf_s(tempMsg, 128, "���������߶�Ӧ�˺��������� = %f\n", tempValue);
			MG_LOG(out_sys, tempMsg);*/

			return;
		}

		//״̬������Ѫ��������
		//?

		//���������߶��ͷ��ߵĳ��ֵ
		calToMasterHatredOD(pMasterAttributeSet, damageType, hurtValue, otherPara, fixedHateValue);

		//���������߿ۼ�Ѫ����Ϣ
		//sendObjAttr(hurtSCharacter, masterSCharacter, damageType, hurtValue, ATTACK_RESULT_TYPE_HURT, fixedHateValue);

		sprintf_s(tempMsg, 128, "�����˺� = %f\n", hurtValue);
		fputs(tempMsg, fp);


		sprintf_s(tempMsg, 128, "���Լ������\n");
		fputs(tempMsg, fp);
		//----------------------------------------------------------------------------------------
		/* Sprintf_s(tempMsg, 128, "���Լ������\n");
		MG_LOG(out_sys, tempMsg);*/
		//----------------------------------------------------------------------------------------
	}
	//--------------------------------------------------------------------------
	void TestAttr::calStartHatredOD(AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, Int& fixedHateValue, Flt otherPara[ATTR_PARA_NUM])
	{
		////1001��ʽ��
		otherPara[0] = fixedHateValue;
		const AttrParaInfo* pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1001);
		DYNAMIC_ASSERT(pAttrParaInfo);
		fixedHateValue = AttributeFormula::getInstance().calValue(pMasterAttr, NULL, pAttrParaInfo->para, pAttrParaInfo->attrID, pAttrParaInfo->FormulaId, pHurtAttr, otherPara);
	}
	//--------------------------------------------------------------------------
	MG::Bool TestAttr::checkImmunoStatusOD(CCharacter* pSCharacter, AttackType attackType)
	{
		/*STATUS_VITIATEFLAG vitiateFlag = changeToSVFTypeOD(attackType);
		DYNAMIC_ASSERT(vitiateFlag);*/
		//return pSCharacter->getSBuffManager()->isHaveVitiateFlag(vitiateFlag);

		return false;
	}
	//--------------------------------------------------------------------------
	TestAttr::FIGHT_ROUND_TYPE TestAttr::calRoundTabOD( CCharacter* pMasterSCharacter, CCharacter* pHurtSCharacter, Flt otherPara[ATTR_PARA_NUM] )
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
	MG::Bool TestAttr::calHitByFRTypeOD( AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, Flt& hitValue, FIGHT_ROUND_TYPE type, Flt otherPara[ATTR_PARA_NUM] )
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
	void TestAttr::calDefenseReduceHurtOD( AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, AttackType attackType, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM] )
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
	void TestAttr::calDirectionHurtOD( AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, ATTACK_POS attackPos, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM] )
	{
		const AttrParaInfo* pAttrParaInfo = AttributePara::getInstance().getAttrParaInfo(1018 + attackPos); 
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
	MG::Bool TestAttr::calCompleteAbsorbHurtOD( CCharacter* pHurtSCharacter, Flt& hitValue )
	{
		CAttributeSystem* pHurtAttrSys = pHurtSCharacter->getAttributeSystem();

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
				//pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_ALL);
				//���̽���
				return true;
			}
			else
			{
				pHurtAttrSys->setShieldByType(STATUS_ABSORBTYPE_ALL, 0);
				hitValue -= allAbsorbVal;
				//״̬�Ƴ�
				//pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_ALL);
				//���̼���
				return false;
			}
		}
		else
			return false;
	}
	//--------------------------------------------------------------------------
	MG::Bool TestAttr::calMagicShieldAbsorbHurtOD( CCharacter* pHurtSCharacter, Flt& hitValue )
	{
		CAttributeSystem* pHurtAttrSys = pHurtSCharacter->getAttributeSystem();
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
					//pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
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
					//pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
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
					//pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
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
					//pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
					//���̼���
					return false;
				}
			}
		}
		else
			return false; 
	}
	//--------------------------------------------------------------------------
	MG::Bool TestAttr::calAttTypeAbsorbHurtOD( CCharacter* pHurtSCharacter, Flt& hitValue, AttackType attackType )
	{
		CAttributeSystem* pHurtAttrSys = pHurtSCharacter->getAttributeSystem();
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
				//pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(absorbType);
				//���̽���
				return true;
			}
			else
			{
				pHurtAttrSys->setShieldByType(absorbType, 0);
				hitValue -= attackAbsorbVal;
				//״̬�Ƴ�
				//pHurtSCharacter->getSBuffManager()->deleteBuffByAbsorbType(absorbType);
				//���̼���
				return false;
			}
		}
		else
			return false;
	}
	//--------------------------------------------------------------------------
	void TestAttr::calToMasterHatredOD( AttributeSet* pMasterAttr, DamageType effectType, Flt hitValue, Flt otherPara[ATTR_PARA_NUM], Int& hateValue )
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
	TestAttr::FIGHT_ROUND_TYPE TestAttr::changeToFRTypeOD( UInt index )
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

	void TestAttr::sendObjAttr( CCharacter* hurtSCharacter, CCharacter* masterSCharacter, DamageType damageType, Int value, ATTACK_RESULT_TYPE arType, Int hateVal, UInt buffId /*= 0*/, UInt addNum /*= 0*/, UInt permillage /*= 0 */ )
	{

	}

	MG::STATUS_VITIATEFLAG TestAttr::changeToSVFTypeOD( AttackType type )
	{
		return STATUS_VITIATEFLAG_FIGHT;
	}

	MG::STATUS_ABSORBTYPE TestAttr::changeToSAbsorbType( AttackType attackType )
	{
		return STATUS_ABSORBTYPE((Int)(attackType));
	}

	void TestAttr::calCorpsHurtOD( CCharacter* pMasterSCharacter, CCharacter* pHurtSCharacter, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM] )
	{
		//1021--1026
		TROOPTEMPLATE_TYPE armyType = pMasterSCharacter->getCharacterTempInfo()->getCharacterArmyType();
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
}
