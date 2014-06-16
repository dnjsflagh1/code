/******************************************************************************/
#ifndef _SKILLUSEMANAGER_H_
#define _SKILLUSEMANAGER_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
/******************************************************************************/
namespace MG
{
	
    /******************************************************************************/
    //角色所属的技能管理器
    /******************************************************************************/

	class SkillUseManager
	{
	public:
		SkillUseManager( GameObject* character );
		virtual ~SkillUseManager();

    public:

        //得到角色对象
        GameObject*                      						getCharacter();

    public:

        // 更新
        virtual	void											update( Flt delta );

	public:

        // 准备使用技能
		SkillObject*                    						prepareUseSkill( IdType skillId );

        // 得到准备中的技能
		SkillObject*											getPreparedUseSkill();

        // 是否可以使用技能
		//virtual Bool											isCanUseSkill( IdType skillId ) = NULL;
										
	protected:

        //创建一个技能对象，由子类实现
        virtual SkillObject*									createSkillObject( IdType skillId ) = NULL;

		virtual void											destroySkillObject(SkillObject*& skillObject) = NULL;

	protected:

		IdType													mLastUseSkillId;
		SkillObject*											mCurrUseSkill;
        GameObject*												mOwnerCharacter;
	};
}


#endif