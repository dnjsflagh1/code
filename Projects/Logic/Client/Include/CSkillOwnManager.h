/******************************************************************************/
#ifndef _CSKILLOWNMANAGER_H_
#define _CSKILLOWNMANAGER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "SkillOwnManager.h"

/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//��ɫ�����ļ��ܹ�����
	//�����߼���صļ��ܶ��������
	/******************************************************************************/

	class CSkillOwnManager : public SkillOwnManager
	{
	public:
		CSkillOwnManager( CCharacter* character );
		virtual ~CSkillOwnManager();

	public:
		virtual void	addOwnerSkill( IdType skillId );
		UInt			getDefaultSkill();

	public:
		//����
		void							calAttrAll();
		//�������Ե��ۼ�
		void							calAttrAllBase();

	private:
		void							calAttr( IdType skillId );
		void							getAttrMap(std::map<U32, Flt>* pAttrMap, U32 skillId);

	protected:
		UInt			mDefaultSkill;

	};
}


#endif