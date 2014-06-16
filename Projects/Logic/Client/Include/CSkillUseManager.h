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
    //��ɫ�����ļ��ܹ�����
	//���糡���еļ��ܶ���������ʾ�Ȳ���
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

		// ׼��ʹ�ü���
		SkillObject*            prepareUseSkill( IdType skillId );

		/////////////////////////////////////////////////////////////////////////////////
		//���CD
		virtual Bool			checkCD( IdType skillId, AddAndCheckSkillCDType addSkillCDType = AACSCT_ALL );

		virtual void			addCD( IdType skillId, AddAndCheckSkillCDType addSkillCDType = AACSCT_ALL );

		//���CD
		virtual Bool			checkCD( SkillInfo* skillInfo, AddAndCheckSkillCDType addSkillCDType = AACSCT_ALL );

		virtual void			addCD( SkillInfo* skillInfo, AddAndCheckSkillCDType addSkillCDType = AACSCT_ALL );

    public:
        //����һ�����ܶ���
        virtual CSkillObject*   createSkillObject( IdType skillId );

		virtual void			destroySkillObject( SkillObject*& skillObject );
		
    private:
		ObjectPool<CSkillObject>	mSkillObjectPool;
		CD_MASTER_TYPE				mCDMasterType;
	};
}

#endif