//**************************************************************************************************
#ifndef _H_TESTATTR_
#define _H_TESTATTR_
//**************************************************************************************************

#include "ClientPreqs.h"

//**************************************************************************************************
namespace MG
{


    class  TestAttr
    {
    public:
        enum  FIGHT_ROUND_TYPE
        {
            FIGHT_ROUND_TYPE_NULL,

            FIGHT_ROUND_TYPE_HIT,                   //����
            FIGHT_ROUND_TYPE_DODGE,                 //���
            FIGHT_ROUND_TYPE_THUMP,                 //�ػ�
            FIGHT_ROUND_TYPE_WITHSTAND,             //�м�

            FIGHT_ROUND_TYPE_MAX
        };
    public:
        TestAttr(){;}
        ~TestAttr(){;}
        SINGLETON_INSTANCE(TestAttr);

    public:
        Bool init();
        Bool update( Flt delta );

    private:
        Bool TestCalAttr();
        Bool TestFightAttr();

        void CreateClan();
        void CreateCharacter();

        ///------------------------------------------------------------------------------------------------------------------
        ///���Լ������
	public://��������
		// �˺�����
		void                        obtainDamage( CCharacter* hurtPeople, CCharacter* master,  AttackType attacktype, DamageType damageType, ATTACK_POS attackPos, U32 formulaParaID, Int fixedHateValue, UInt buffId, UInt addNum, UInt permillage, FILE* fp );
		
	private:
		//ս�����������˺�����
		//---------------------------------------------------------------------------------------------------------------------

		//�����Ҷ��ͷ��ߵĳ��
		void                        calStartHatredOD(AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, Int& fixedHateValue, Flt otherPara[ATTR_PARA_NUM]);

		//����������ת��Ϊ������������
		STATUS_VITIATEFLAG			changeToSVFTypeOD(AttackType type);
		//����Ƿ�������״̬
		Bool                        checkImmunoStatusOD(CCharacter* pSCharacter, AttackType attackType);

		//Բ���ж���
		FIGHT_ROUND_TYPE            calRoundTabOD( CCharacter* pMasterSCharacter, CCharacter* pHurtSCharacter, Flt otherPara[ATTR_PARA_NUM] );
		//���õ�������ֵת��ΪFIGHT_ROUND_TYPE
		FIGHT_ROUND_TYPE            changeToFRTypeOD(UInt index);
		//����FIGHT_ROUND_TYPE�����˺�ֵ��
		Bool                        calHitByFRTypeOD(AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, Flt& hitValue, FIGHT_ROUND_TYPE type, Flt otherPara[ATTR_PARA_NUM]);

		//�����������
		void                        calDefenseReduceHurtOD(AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, AttackType attackType, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM]);

		//���㷽���˺�
		void                        calDirectionHurtOD(AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, ATTACK_POS attackPos, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM]);

		//����ɫ����ת��Ϊ��������
		TROOPTEMPLATE_TYPE			changeToArmyTypeOD(CCharacter* pMasterSCharacter);
		//��������˺�
		void						calCorpsHurtOD(CCharacter* pMasterSCharacter, CCharacter* pHurtSCharacter, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM]);

		//ȫ�˺�����
		Bool                        calCompleteAbsorbHurtOD(CCharacter* pHurtSCharacter, Flt& hitValue);
		//���������߷�����������
		Bool                        calMagicShieldAbsorbHurtOD(CCharacter* pHurtSCharacter, Flt& hitValue );
		//����������ת��Ϊ�˺���������
		STATUS_ABSORBTYPE			changeToSAbsorbType(AttackType attackType);
		//���������߶�Ӧ�˺���������
		Bool                        calAttTypeAbsorbHurtOD( CCharacter* pHurtSCharacter, Flt& hitValue, AttackType attackType );

		//���������߶��ͷ��ߵĳ��ֵ
		void                        calToMasterHatredOD(AttributeSet* pMasterAttr, DamageType effectType, Flt hitValue, Flt otherPara[ATTR_PARA_NUM], Int& hateValue);

		//����ս���˺�������Ϣ
		void						sendObjAttr(CCharacter* hurtSCharacter, CCharacter* masterSCharacter, DamageType damageType, Int value, ATTACK_RESULT_TYPE arType, Int hateVal, UInt buffId = 0, UInt addNum = 0, UInt permillage = 0  );
		//ս�����������˺�����
		//---------------------------------------------------------------------------------------------------------------------
    private:
        AttributeSet*       mAttributeSet;
        UInt                mHurtRoleIndex;
        UInt                mSpeed;
    };
}

//**************************************************************************************************
#endif
//**************************************************************************************************