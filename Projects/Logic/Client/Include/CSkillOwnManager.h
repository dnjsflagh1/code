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
	//角色所属的技能管理器
	//数据逻辑相关的技能对象管理器
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
		//属性
		void							calAttrAll();
		//计算属性的累加
		void							calAttrAllBase();

	private:
		void							calAttr( IdType skillId );
		void							getAttrMap(std::map<U32, Flt>* pAttrMap, U32 skillId);

	protected:
		UInt			mDefaultSkill;

	};
}


#endif