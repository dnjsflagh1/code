/******************************************************************************/
#ifndef _CSKILLMANAGERFORCHARACTER_H_
#define _CSKILLMANAGERFORCHARACTER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "SkillUseManager.h"
#include "CSkillObject.h"
#include "ObjectPool.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //角色所属的技能管理器
	//世界场景中的技能对象，用于显示等操作
    /******************************************************************************/
	class CSkillUseManager : public SkillUseManager
	{
	public:
		enum AddAndCheckSkillCDType
		{
			AACSCT_ALL,
			AACSCT_PUBLIC,
			AACSCT_OWNER,
		};


		CSkillUseManager( CCharacterSceneEntity* character );
		virtual ~CSkillUseManager();

    public:

		//////////////////////////////////////////////////////////////////////////////////

        CCharacterSceneEntity*  getCharacterEntity();

		virtual Bool			isCanUseSkill( IdType skillId, CCharacter* targetCharacter );

		virtual Bool			isCanUseSkill( SkillInfo* skillInfo, CCharacter* targetCharacter );

		// 准备使用技能
		SkillObject*            prepareUseSkill( IdType skillId );

		/////////////////////////////////////////////////////////////////////////////////
		//检测CD
		virtual Bool			checkCD( IdType skillId, AddAndCheckSkillCDType addSkillCDType = AACSCT_ALL );

		virtual void			addCD( IdType skillId, AddAndCheckSkillCDType addSkillCDType = AACSCT_ALL );

		//添加CD
		virtual Bool			checkCD( SkillInfo* skillInfo, AddAndCheckSkillCDType addSkillCDType = AACSCT_ALL );

		virtual void			addCD( SkillInfo* skillInfo, AddAndCheckSkillCDType addSkillCDType = AACSCT_ALL );

    public:
        //创建一个技能对象
        virtual CSkillObject*   createSkillObject( IdType skillId );

		virtual void			destroySkillObject( SkillObject*& skillObject );
		
    private:
		ObjectPool<CSkillObject>	mSkillObjectPool;
		CD_MASTER_TYPE				mCDMasterType;
	};
}

#endif