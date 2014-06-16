/******************************************************************************/
#ifndef _SSKILLUSEMANAGER_H_
#define _SSKILLUSEMANAGER_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SkillUseManager.h"
#include "SkillNetPacket.h"
#include "SSkillObject.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //角色所属的技能管理器
    /******************************************************************************/
	class SSkillUseManager: public SkillUseManager
	{
	public:
		SSkillUseManager( SCharacter* character );
		virtual ~SSkillUseManager();
    
    public:
        //void                            getDefultSkill();
        //void                            getDBSkill();

    public:
        //学习技能
        //void                            learnSkill(I32 netID, IdType id);
		virtual Bool						isCanUseSkill(IdType id);
        
    protected:
        // 创建技能对象
        virtual SkillObject*            	createSkillObject(IdType id);

		virtual void						destroySkillObject(SkillObject*& skillObject);

		SCharacter*                     	getSCharacter();

    private:
		ObjectPool<SSkillObject,false>      mSkillObjectPool;

	};
}

#endif