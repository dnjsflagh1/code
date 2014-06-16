/******************************************************************************/
#ifndef _H_CCHARACTER_
#define _H_CCHARACTER_
/******************************************************************************/
#include "ClientPreqs.h"
#include "CharacterData.h"
#include "GameObject.h"
#include "CAttributeSystem.h"
/******************************************************************************/
namespace MG
{
    class CCharacter : public GameObject
    {
        friend CAttributeSystem;
    public:
        CCharacter(GAMEOBJ_TYPE type, GameObjectData* data, PlayerCharacterIdType id = 0);
        virtual ~CCharacter();

    public:
        CharacterData*				getCharacterData();

    public: // 【基础属性】
        // 设置和获得角色模板
        U32                         getCharacterTemplateID();
        void                        setCharacterTemplateID(U32 id);

        //得到和设置区域
        void			            setRegion(REGION_OBJ_TYPE type, U32 id,InstanceIdType instanceId,  Bool isCalBelongMapID=false) ;
        REGION_OBJ_TYPE	            getRegionType() ;
        U32			                getRegionID() ;
		InstanceIdType              getInstanceUId();

        //得到和获得角色模板指针
        void                        setCharacterTempInfo();
        const CharacterTempInfo*    getCharacterTempInfo();

        AttributeSet*               getAttributeSet(){return mCAttributeSystem.getCalAttrInfo();}
        CAttributeSystem*           getAttributeSystem(){return &mCAttributeSystem;}

    ///----------------------------------------------------------------------------------------------
    /// 属性计算相关
    public: // 【战斗属性计算】
        //属性计算时需调用。
        virtual UInt                getHp();
        virtual UInt                getMp();
        virtual UInt                getSp();
		virtual UInt				getMaxHp();
		virtual UInt				getMaxMp();
		virtual UInt				getMaxSp();
        virtual UInt                getLineageNum();
        virtual void                setHp(Int val);
        virtual void                setMp(Int val);
		virtual void                setSp(Int val);
		void						setMax_HpSpMp();
		//设置和获得等级
		U32                         getLevel();
		void                        setLevel(U32 level);

        // 根据id 获得战斗属性
        Int                         getFanalValue(U32 id);
        // 根据id设置战斗属性
        void                        setFanalValue(U32 id, Flt val);
        /// 改变血 或 蓝 或 怒气值
        void                        setHpMpSp(Flt num, DamageType type, ATTACK_RESULT_TYPE resType);
        
    public:
        // 计算最终属性
        void                        calAttr();

	protected:
        //属性计算时需调用。
        virtual Flt                 getDBAttrInit(UInt index){return 0.f;}
        virtual Flt                 getDBAttrLvlAdd(UInt index){return 0.f;}
		virtual UInt				getDBAttrInitID(){return 0;}
		virtual UInt				getDBAttrLvlAddID(){return 0;}
        // 计算其他属性
        virtual void                calOtherAttr(){}

    /// 属性计算相关 -- end
    ///----------------------------------------------------------------------------------------------

    public:  /// 得到技能管理器, 此管理器只负责技能逻辑数据保存
        CSkillOwnManager*				getSkillOwnManager(); 

    private:

		CSkillOwnManager*				mSkillOwnManager;
        CAttributeSystem                mCAttributeSystem;
        const CharacterTempInfo*        mCharacterTempInfo;
		

    };

}
/******************************************************************************/
#endif
/******************************************************************************/