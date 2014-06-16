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
		//�Ƿ�������ñ�ָ������ʧ���͡�
		Bool			isCanDisappear(STATUS_DISAPPEARTYPE type);
		//�Ƿ�������ñ�ָ��������Ч�����͡�
		Bool			isHaveSpecialEffect(STATUS_STATUSSYSTYPE type);
		//�Ƿ�������ñ�ָ���Ĺ����������͡�
		Bool			isHaveVitiateFlag(STATUS_VITIATEFLAG type);
		//�Ƿ�������ñ�ָ���Ĺ����������͡�
		Bool			isHaveAbsorbType(STATUS_ABSORBTYPE type);
		//��������
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
		//�������˺�
		void			cycleDamage(U32 damage, U32 hpValue, U32 mpValue, U32 spValue);
		//����������
		void			cycleAbsorb(U32 probability, U32 hpValue, U32 mpValue, U32 spValue);



	private:
		CCharacterSceneEntity*		mParentEnt;
		CCharacter*					mParentLgc;
	};
}
//***************************************************************************************
#endif
//***************************************************************************************