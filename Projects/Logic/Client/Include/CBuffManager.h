//***************************************************************************************
#ifndef _H_CBUFFMANAGER_
#define _H_CBUFFMANAGER_
//***************************************************************************************
#include "ClientPreqs.h"
#include "BuffManager.h"
//***************************************************************************************
namespace MG
{
	class CBuffManager : public BuffManager
	{
	public:
		CBuffManager(void* parent);
		virtual ~CBuffManager();

	public:
		virtual BuffObject*	createBuff(STATUS_TYPE type);

	public:
		//������ʧ�¼�ɾ��Buff
		void	deleteBuffByDisappearTypeEvent(STATUS_DISAPPEARTYPE type);
		//�Ƿ�������Ч��
		Bool	isHaveSpecialEffect(STATUS_STATUSSYSTYPE type);
		//�Ƿ�ĳһ��������
		Bool	isHaveVitiateFlag(STATUS_VITIATEFLAG type);
		//ĳ���ͻ���ֵ�ľ�
		void	deleteBuffByAbsorbType(STATUS_ABSORBTYPE type);
		//���buffData��
		void	getBuffData(std::map<U32, BuffData>& vecBuffData);
		//���¼�������buff������
		void	calAttrAllBase();

		
	};
}
//***************************************************************************************
#endif
//***************************************************************************************