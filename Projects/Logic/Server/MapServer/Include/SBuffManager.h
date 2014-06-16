//***************************************************************************************
#ifndef _H_SBUFFMANAGER_
#define _H_SBUFFMANAGER_
//***************************************************************************************
#include "MapServerPreqs.h"
#include "BuffManager.h"
//***************************************************************************************
namespace MG
{
	class SBuffManager : public BuffManager
	{
	public:
		SBuffManager(void* parent);
		~SBuffManager();

	public:
		//������Ӧ���ʹ���buff����
		virtual BuffObject* createBuff(STATUS_TYPE type);

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

	protected:
	private:

	};
}
//***************************************************************************************
#endif
//***************************************************************************************