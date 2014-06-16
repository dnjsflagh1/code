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
		//�Ƿ�������ñ�ָ������ʧ���͡�
		Bool			isCanDisappear(STATUS_DISAPPEARTYPE type);
		//�Ƿ�������ñ�ָ��������Ч�����͡�
		Bool			isHaveSpecialEffect(STATUS_STATUSSYSTYPE type);
		//�Ƿ�������ñ�ָ���Ĺ����������͡�
		Bool			isHaveVitiateFlag(STATUS_VITIATEFLAG type);
		//�Ƿ�������ñ�ָ���Ĺ����������͡�
		Bool			isHaveAbsorbType(STATUS_ABSORBTYPE type);
		

	protected:
		virtual	void	updateBuffOther(Flt delta);
		virtual void	clearBuffOther(Bool isCal = true);
		virtual void	addBuffOther();
		virtual	void	initBuffOther( const StatusData* pStatusData, Int timeUse );
		//��������
		virtual void	calAttrBase();

	private:
		//�ӻ���ֵ
		void			addAbsorbNum(STATUS_ABSORBTYPE type, Int num);
		//��������
		void			clearAbsorbNum(STATUS_ABSORBTYPE type);
		//����buff���������
		void			calAttribute(UInt abilityAppendId, UInt buffLvl, Bool isAdd = true);
		void			getMapAttrValue(std::map<UInt, Flt>& mapValue, UInt id, Int bufflvl);
		//����DB����buff��Ҫ�洢��DB��
		void			updateDB();
		//�������˺�
		void			cycleDamage(U32 damage, U32 hpValue, U32 mpValue, U32 spValue);
		//����������
		void			cycleAbsorb(U32 probability, U32 hpValue, U32 mpValue, U32 spValue);

	private:
		SCharacter*			mParent;

	};
}
//***************************************************************************************
#endif
//***************************************************************************************