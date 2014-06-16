/******************************************************************************/
#ifndef _CCHARACTER_H_
#define _CCHARACTER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CCharacter.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //玩家控制的角色
    //只和逻辑相关，和显示无关
    /******************************************************************************/
	class CSkillOwnManager;
    class CPlayerCharacter : public CCharacter
	{
	public:
		CPlayerCharacter();
		virtual ~CPlayerCharacter();

		void			setJoinRegion(Bool isJoinRegion);
		Bool			getJoinRegion();


		
    public:
        PlayerCharacterData*            getData();

    ///----------------------------------------------------------------------------------------------
    /// 属性计算相关
    public:
        //属性计算时需调用。
        virtual UInt                        getHp();
        virtual UInt                        getMp();
        /*virtual UInt                        getSp();*/
        virtual UInt                        getLineageNum();
        virtual void                        setHp(UInt val);
        virtual void                        setMp(UInt val);
        virtual void                        setSp(UInt val);

    protected:
        //属性计算时需调用。
        virtual Flt                         getDBAttrInit(UInt index);
        virtual Flt                         getDBAttrLvlAdd(UInt index);
        // 计算其他属性
        virtual void                        calOtherAttr();

    /// 属性计算相关 -- end
    ///----------------------------------------------------------------------------------------------

    public:
        void                                init(PlayerCharacterData* pData);

		//--------------------------------------------------------------
		Bool								mIsJoinRegion;


		//--------------------------------------------------------------
		CSkillOwnManager*					getSkillOwnManager(){return mSkillOwerMgr;}
		UInt								getCurrSkillId(){return mCurrSkillId;}
		void								setCurrSkillId(UInt skillId){mCurrSkillId = skillId;}
//		void								addSkill( SkillData skillData );
	private:
		CSkillOwnManager*					mSkillOwerMgr;
		UInt								mCurrSkillId;
	};
}

#endif