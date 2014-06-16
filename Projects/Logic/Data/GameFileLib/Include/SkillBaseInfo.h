//************************************************************************************************************
#ifndef _SKILLBASICINFO_H_
#define _SKILLBASICINFO_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
//************************************************************************************************************
namespace MG
{

	//cd时间单位，毫秒
	//逻辑层面cd时间单位以毫秒为准
	//配置文件CD单位。毫秒

	enum  SKILL_SHOW_TYPE
	{
		SKILL_SHOW_TYPE_NULL,

		SKILL_SHOW_TYPE_ONE,
		SKILL_SHOW_TYPE_TWO,

		SKILL_SHOW_TYPE_MAX
	};
	enum SpendType
	{
		ST_NULL,
		ST_HP,
		ST_MP,
		ST_HPMP,
		ST_SP,
		ST_PROMILLE_HP, 
		ST_PROMILLE_MP,
		ST_PROMILLE_HPMP,
		ST_PROMILLE_SP,
	};

	enum SkillType
	{
		SKT_NULL,
		SKT_LIFE,
		SKT_PASSIVENESS,
		SKT_SHORTRANGEGENERAL,
		SKT_LONGRANGEGENERAL,
		SKT_SINGLETARGET,
		SKT_SINGLEEMITTER,
		SKT_SELFAREA,
		SKT_TARGETPOSAREA,
		SKT_LONGRANGEAUXILIARY,
		SKT_SKILL10,
		SKT_SKILL11,
		SKT_SKILL12,
		SKT_GOUPANDDOWN,
		SKT_PARABOLAAREA,
	};

	enum SkillFlyType
	{
		SFT_NULL,
		SFT_MODLE,
		SFT_EFFECT,
	};

	struct SkillExpression
	{
		Str16				action					;
		UInt				artEffectId				;
		UInt				audioResId				;
	};

	struct SkillBaseInfo
	{
		UInt         		skillTypeId				;
		UInt         		skillTypeGroupId		;
		UInt				skillLevel				;
		Str16       		name					;
		Str16         		text					;
		Str16         		kindName				;
		UInt         		artIconId				;
		AttackType			attackType				;
		DamageType			damageType				;
		UInt				formulaParameterId		;
		SkillBaseInfo()
		{
			damageType = DT_HP;
			skillLevel = 0;
		}
	};

	struct SkillInfo
	{
		IdType				skillId					;
		SkillType			skillType				;
		UInt				skillListId				;
		SKILL_SHOW_TYPE		skillShowType			;

		SkillBaseInfo*		skillInfo				;
	};

	struct SkillLearnInfo
	{
		UInt				skillLearnId			;
		UInt				clanJudgeid				;
		UInt				characterJudgeid		;
		UInt				skillFrontId			;
		UInt				itemId					;
		UInt				itemNum					;
		UInt				delItemId				;
		Str16				artAction				;
		UInt				artEffectResId			;
		UInt				audioResId				;
	};

	struct PassivenessSkillBasicInfo : public SkillBaseInfo
	{
		UInt				artEffectId				;
		UInt				abilityAppendId			;
	};

	struct InitiativeSkillBasicInfo : public SkillBaseInfo
	{
		SkillExpression		skillExpression[4]		;
		Flt					attackFrontTime			;
		Flt					attackBehindTime		;
		UInt				publicTimepieceId		;	
		UInt				publicTimepieceDelay	;
		Flt					range					;
		Flt					maxRange				;
		UInt				formulaParameterId2		;
		UInt				characterJudgeId1		;	
		UInt				characterJudgeId2		;
		Flt					actionTime				;
		UInt				ownerTimepieceId		;
		UInt				ownerTimepieceDelay		;
		SpendType			spendType				;
		UInt				randomState				;
		UInt				stateId					;
		UInt				stateNum				;
		UInt				hate					;
		
		InitiativeSkillBasicInfo()
		{
			actionTime				= 0;
			attackFrontTime			= 0;	
			attackBehindTime		= 0;	
			publicTimepieceId		= 0;	
			publicTimepieceDelay	= 0;
			range					= 0;			
			maxRange				= 0;			
			formulaParameterId2		= 0;
			characterJudgeId1		= 0;
			characterJudgeId2		= 0;
			actionTime				= 0;
			ownerTimepieceId		= 0;
			ownerTimepieceDelay		= 0;
			spendType				= ST_NULL;
			randomState				= 0;
			stateId					= 0;
			stateNum				= 0;
			hate					= 0;
		}
	};

}
//************************************************************************************************************
#endif
//************************************************************************************************************