//******************************************************************************************
#ifndef _H_SATTRIBUTESYSTEM_
#define _H_SATTRIBUTESYSTEM_
//******************************************************************************************
#include "MapServerPreqs.h"
#include "AttributeSystem.h"
//******************************************************************************************
namespace MG
{
    class SAttributeSystem : public AttributeSystem
    {
    public:
        SAttributeSystem(){;}
        virtual ~SAttributeSystem(){;}

    public:
        //计算基本属性
        void                        calAttrBase( SCharacter* pCharacter );

    public://计算属性
        // 伤害计算
        void                        obtainDamage( SCharacter* hurtPeople, SCharacter* master,  AttackType attacktype, DamageType damageType, ATTACK_POS attackPos, U32 formulaParaID, Int& fixedHateValue, UInt buffId, UInt addNum, UInt permillage );
        // 技能治疗
        void                        skillTreat( SCharacter* treatSCharacter, SCharacter* masterSCharacter, DamageType type, U32 formulaParaID, Int& fixedHateValue, UInt buffId, UInt addNum, UInt permillage);
        // 道具治疗
        void                        itemTreat( SCharacter* treatPeople, DamageType type, Int treatValue);
    
    private:
        //战斗————伤害计算
        //---------------------------------------------------------------------------------------------------------------------
       
        //计算我对释放者的仇恨
        void                        calStartHatredOD(AttributeSet* pMasterAttr, Int& fixedHateValue, Flt otherPara[ATTR_PARA_NUM]);
		
		//将攻击类型转换为防御免伤类型
		STATUS_VITIATEFLAG			changeToSVFTypeOD(AttackType type);
        //检查是否是免疫状态
        Bool                        checkImmunoStatusOD(SCharacter* pSCharacter, AttackType attackType);

        //圆桌判定。
        FIGHT_ROUND_TYPE            calRoundTabOD( SCharacter* pMasterSCharacter, SCharacter* pHurtSCharacter, Flt otherPara[ATTR_PARA_NUM] );
        //将得到的索引值转换为FIGHT_ROUND_TYPE
        FIGHT_ROUND_TYPE            changeToFRTypeOD(UInt index);
        //根据FIGHT_ROUND_TYPE计算伤害值。
        Bool                        calHitByFRTypeOD(AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, Flt& hitValue, FIGHT_ROUND_TYPE type, Flt otherPara[ATTR_PARA_NUM]);
        
		//计算防御减伤
        void                        calDefenseReduceHurtOD(AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, AttackType attackType, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM]);
        
		//计算方向伤害
        void                        calDirectionHurtOD(AttributeSet* pHurtAttr, AttributeSet* pMasterAttr, ATTACK_POS attackPos, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM]);
        
		//将角色类型转化为兵种类型
		TROOPTEMPLATE_TYPE			changeToArmyTypeOD(SCharacter* pMasterSCharacter);
		//计算兵种伤害
		void						calCorpsHurtOD(SCharacter* pMasterSCharacter, SCharacter* pHurtSCharacter, Flt& hitValue, Flt otherPara[ATTR_PARA_NUM]);
		
		//全伤害吸收
        Bool                        calCompleteAbsorbHurtOD(SCharacter* pHurtSCharacter, Flt& hitValue);
        //计算作用者法力护盾吸收
        Bool                        calMagicShieldAbsorbHurtOD(SCharacter* pHurtSCharacter, Flt& hitValue );
		//将攻击类型转换为伤害吸收类型
		STATUS_ABSORBTYPE			changeToSAbsorbType(AttackType attackType);
        //计算作用者对应伤害类型吸收
        Bool                        calAttTypeAbsorbHurtOD( SCharacter* pHurtSCharacter, Flt& hitValue, AttackType attackType );
        
		//计算作用者对释放者的仇恨值
        void                        calToMasterHatredOD(AttributeSet* pMasterAttr, DamageType effectType, Flt hitValue, Flt otherPara[ATTR_PARA_NUM], Int& hateValue);
        
		//发送战斗伤害计算消息
		void						sendObjAttr(SCharacter* hurtSCharacter, SCharacter* masterSCharacter, DamageType damageType, Int value, ATTACK_RESULT_TYPE arType, Int hateVal, UInt buffId = 0, UInt addNum = 0, UInt permillage = 0  );
        //战斗————伤害计算
        //---------------------------------------------------------------------------------------------------------------------

        //技能--------治疗
        //---------------------------------------------------------------------------------------------------------------------
        
        //  计算非武将对释放者的仇恨值
        void                        calToMasterHatredST( AttributeSet* pMasterAttr, Flt otherPara[ATTR_PARA_NUM], Int& fixedHateValue );
        // 计算施展者造成的治疗量
        void                        calSkillTreatST(AttributeSet* pMasterAttr, Flt& valST, U32 formulaParaID);
        //圆桌判定。
        TREAT_ROUND_TYPE            calRoundTabST( AttributeSet* pMasterAttr, Flt otherPara[ATTR_PARA_NUM] );
        //将得到的索引值转换为SKILL_TREAT_ROUND_TYPE
        TREAT_ROUND_TYPE            changeToSTRTypeST(UInt index);
        //根据SKILL_TREAT_ROUND_TYPE计算治疗量。
        void                        calTreatBySTRTypeST(AttributeSet* pMasterAttr, AttributeSet* pTreatAttr, Flt& valST, TREAT_ROUND_TYPE strType, Flt otherPara[ATTR_PARA_NUM]);
        // 计算最终 治疗量
        void                        calFinalSkillTreatST(AttributeSet* pMasterAttr, AttributeSet* pTreatAttr, Flt& valST, Flt otherPara[ATTR_PARA_NUM]);
        //同步 治疗量
        void                        syncSkillTreatST( SCharacter* treatSCharacter, SCharacter* masterSCharacter, DamageType type, Flt valST, Int fixedHateValue, UInt buffId, UInt addNum, UInt permillage );
        //计算非武将对释放者的仇恨值
        void                        calToMasterHatredEndST( AttributeSet* pMasterAttr, DamageType type, Flt valST, Flt otherPara[ATTR_PARA_NUM], Int& fixedHateValue );

        //技能--------治疗
        //---------------------------------------------------------------------------------------------------------------------
        //道具--------治疗
        //---------------------------------------------------------------------------------------------------------------------
        
        //圆桌判定。
        TREAT_ROUND_TYPE            calRoundTabIT( Flt otherPara[ATTR_PARA_NUM] );
        //将得到的索引值转换为SKILL_TREAT_ROUND_TYPE
        TREAT_ROUND_TYPE            changeToSTRTypeIT(UInt index);
        //根据SKILL_TREAT_ROUND_TYPE计算治疗量。
        void                        calTreatBySTRTypeIT(Int& valST, TREAT_ROUND_TYPE itrType, Flt otherPara[ATTR_PARA_NUM]);
        //同步 治疗量
        void                        syncItemTreatIT(SCharacter* treatSCharacter, DamageType type, Int valST, Int fixedHateValuevalST);
        //计算非武将对释放者的仇恨值
        void                        calToMasterHatredIT( SCharacter* treatPeople, DamageType type, Int valST, Flt otherPara[ATTR_PARA_NUM], Int& fixedHateValue );


        //道具--------治疗
        //---------------------------------------------------------------------------------------------------------------------

    };
}
//******************************************************************************************
#endif
//******************************************************************************************