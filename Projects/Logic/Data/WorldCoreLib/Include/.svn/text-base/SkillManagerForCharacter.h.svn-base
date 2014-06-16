/******************************************************************************/
#ifndef _SKILLMANAGERFORCHARACTER_H_
#define _SKILLMANAGERFORCHARACTER_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "SkillFileConfig.h"
/******************************************************************************/
namespace MG
{
	
    /******************************************************************************/
    //角色所属的技能管理器
    /******************************************************************************/

	class SkillManagerForCharacter
	{
	public:
		SkillManagerForCharacter( GameObject* character );
		virtual ~SkillManagerForCharacter();

    public:
        //得到角色对象
        GameObject*                      		        getCharacter();

    public:
        // 更新
        virtual	void										update( Flt delta );

        // 是否能学习技能
        virtual Bool										isCanLearnSkill(IdType id);
        // 是否能使用技能
        // 是否在CD时间，是否有蓝，是否拥有此技能
        virtual Bool                    					isCanUseSkill(IdType id);

	public:

        //增加或得到一个技能
		SkillObject*                    					addOrGetSkill(IdType id);

        //得到配置
		SkillObject*										getSkill(IdType id);

		SkillObject*										getSkill(UInt index);

		UInt												getSkillNum();

	protected:
		typedef std::map<IdType, SkillObject*>::iterator	SkillObjListIt;

	protected:
        //创建一个技能对象，由子类实现
        virtual SkillObject*								createSkillObject(IdType id) = NULL;

        //销毁所有技能对象
		void												destroyAllSkill();
        //更新所有技能对象
        void												updateAllSkill( Flt delta );

	private:

		std::map<IdType, SkillObject*>						    mSkillObjList;
		//Character*											mOwnerCharacter;
        GameObject*											mOwnerCharacter;
	};
}


#endif