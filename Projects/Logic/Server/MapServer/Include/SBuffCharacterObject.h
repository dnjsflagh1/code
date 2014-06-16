//***************************************************************************************
#ifndef _H_SBUFFCHARACTEROBJECT_
#define _H_SBUFFCHARACTEROBJECT_
//***************************************************************************************
#include "MapServerPreqs.h"
#include "BuffObject.h"
//***************************************************************************************
namespace MG
{
	class SBuffCharacterObject : public BuffObject
	{
	public:
		SBuffCharacterObject(void* parent);
		~SBuffCharacterObject();

	public:
		//是否符合配置表指定的消失类型。
		Bool			isCanDisappear(STATUS_DISAPPEARTYPE type);
		//是否符合配置表指定的特殊效果类型。
		Bool			isHaveSpecialEffect(STATUS_STATUSSYSTYPE type);
		//是否符合配置表指定的攻击免伤类型。
		Bool			isHaveVitiateFlag(STATUS_VITIATEFLAG type);
		//是否符合配置表指定的攻击护盾类型。
		Bool			isHaveAbsorbType(STATUS_ABSORBTYPE type);
		

	protected:
		virtual	void	updateBuffOther(Flt delta);
		virtual void	clearBuffOther(Bool isCal = true);
		virtual void	addBuffOther();
		virtual	void	initBuffOther( const StatusData* pStatusData, Int timeUse );
		//计算属性
		virtual void	calAttrBase();

	private:
		//加护盾值
		void			addAbsorbNum(STATUS_ABSORBTYPE type, Int num);
		//消除护盾
		void			clearAbsorbNum(STATUS_ABSORBTYPE type);
		//计算buff给予的属性
		void			calAttribute(UInt abilityAppendId, UInt buffLvl, Bool isAdd = true);
		void			getMapAttrValue(std::map<UInt, Flt>& mapValue, UInt id, Int bufflvl);
		//更新DB（该buff需要存储到DB）
		void			updateDB();
		//周期性伤害
		void			cycleDamage(U32 damage, U32 hpValue, U32 mpValue, U32 spValue);
		//周期性治疗
		void			cycleAbsorb(U32 probability, U32 hpValue, U32 mpValue, U32 spValue);

	private:
		SCharacter*			mParent;

	};
}
//***************************************************************************************
#endif
//***************************************************************************************