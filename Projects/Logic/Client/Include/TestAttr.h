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

            FIGHT_ROUND_TYPE_HIT,                   //命中
            FIGHT_ROUND_TYPE_DODGE,                 //躲避
            FIGHT_ROUND_TYPE_THUMP,                 //重击
            FIGHT_ROUND_TYPE_WITHSTAND,             //招架

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
        ///属性计算相关
	public://计算属性
		// 伤害计算
		void                        obtainDamage( CCharacter* hurtPeople, CCharacter* master,  AttackType attacktype, DamageType damageType, ATTACK_POS attackPos, U32 formulaParaID, Int fixedHateValue, UInt buffId, UInt addNum, UInt permillage, FILE* fp );
		
	private:
		//战斗————伤害计算
		//---------------------------------------------------------------------------------------------------------------------

		//计算我对释放者的仇恨
		void                        calStartHatredOD(AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, Int& fixedHateValue, Flt otherPara[ATTR_PARA_NUM]);

		//将攻击类型转换为防御免伤类型
		STATUS_VITIATEFLAG			changeToSVFTypeOD(AttackType type);
		//检查是否是免疫状态
		Bool                        checkImmunoStatusOD(CCharacter* pSCharacter, AttackType attackType);

		//圆桌判定。
		FIGHT_ROUND_TYPE            calRoundTabOD( CCharacter* pMasterSCharacter, CCharacter* pHurtSCharacter, Flt otherPara[ATTR_PARA_NUM] );
		//将得到的索引值转换为FIGHT_ROUND_TYPE
		FIGHT_ROUND_TYPE            changeToFRTypeOD(UInt index);
		//根据FIGHT_ROUND_TYPE计算伤害值。
		Bool                        calHitByFRTypeOD(AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, Flt& hitValue, FIGHT_ROUND_TYPE type, Flt otherPara[ATTR_PARA_NUM]);

		//计算防御减伤
		void                        calDefenseReduceHurtOD(AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, AttackType attackType, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM]);

		//计算方向伤害
		void                        calDirectionHurtOD(AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, ATTACK_POS attackPos, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM]);

		//将角色类型转化为兵种类型
		TROOPTEMPLATE_TYPE			changeToArmyTypeOD(CCharacter* pMasterSCharacter);
		//计算兵种伤害
		void						calCorpsHurtOD(CCharacter* pMasterSCharacter, CCharacter* pHurtSCharacter, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM]);

		//全伤害吸收
		Bool                        calCompleteAbsorbHurtOD(CCharacter* pHurtSCharacter, Flt& hitValue);
		//计算作用者法力护盾吸收
		Bool                        calMagicShieldAbsorbHurtOD(CCharacter* pHurtSCharacter, Flt& hitValue );
		//将攻击类型转换为伤害吸收类型
		STATUS_ABSORBTYPE			changeToSAbsorbType(AttackType attackType);
		//计算作用者对应伤害类型吸收
		Bool                        calAttTypeAbsorbHurtOD( CCharacter* pHurtSCharacter, Flt& hitValue, AttackType attackType );

		//计算作用者对释放者的仇恨值
		void                        calToMasterHatredOD(AttributeSet* pMasterAttr, DamageType effectType, Flt hitValue, Flt otherPara[ATTR_PARA_NUM], Int& hateValue);

		//发送战斗伤害计算消息
		void						sendObjAttr(CCharacter* hurtSCharacter, CCharacter* masterSCharacter, DamageType damageType, Int value, ATTACK_RESULT_TYPE arType, Int hateVal, UInt buffId = 0, UInt addNum = 0, UInt permillage = 0  );
		//战斗————伤害计算
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