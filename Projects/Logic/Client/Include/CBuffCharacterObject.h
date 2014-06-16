//***************************************************************************************
#ifndef _H_CBUFFCHARACTEROBJECT_
#define _H_CBUFFCHARACTEROBJECT_
//***************************************************************************************
#include "ClientPreqs.h"
#include "BuffObject.h"
//***************************************************************************************
namespace MG
{
	class CBuffCharacterObject : public BuffObject
	{
	public:
		CBuffCharacterObject(void* parent);
		virtual  ~CBuffCharacterObject();

	public:
		//是否符合配置表指定的消失类型。
		Bool			isCanDisappear(STATUS_DISAPPEARTYPE type);
		//是否符合配置表指定的特殊效果类型。
		Bool			isHaveSpecialEffect(STATUS_STATUSSYSTYPE type);
		//是否符合配置表指定的攻击免伤类型。
		Bool			isHaveVitiateFlag(STATUS_VITIATEFLAG type);
		//是否符合配置表指定的攻击护盾类型。
		Bool			isHaveAbsorbType(STATUS_ABSORBTYPE type);
		//计算属性
		virtual void	calAttrBase();

	protected:
		virtual	void	updateBuffOther(Flt delta);
		virtual void	clearBuffOther(Bool isCal = true);
		virtual void	addBuffOther();
		virtual void	initBuffOther(const StatusData* pStatusData, Int timeUse);

	private:
		void			updateAbsorbNum(STATUS_ABSORBTYPE type, Int num, Bool isAdd);
		void			updateAttribute(UInt id, UInt bufflvl, Bool isAdd);
		void			getMapAttrValue(std::map<UInt, Flt>& mapValue, UInt id, Int bufflvl);
		void			updateFace(Bool isAdd);
		//周期性伤害
		void			cycleDamage(U32 damage, U32 hpValue, U32 mpValue, U32 spValue);
		//周期性治疗
		void			cycleAbsorb(U32 probability, U32 hpValue, U32 mpValue, U32 spValue);



	private:
		CCharacterSceneEntity*		mParentEnt;
		CCharacter*					mParentLgc;
	};
}
//***************************************************************************************
#endif
//***************************************************************************************