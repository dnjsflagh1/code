/******************************************************************************/
#ifndef _H_CCHARACTER_
#define _H_CCHARACTER_
/******************************************************************************/
#include "ClientPreqs.h"
#include "CharacterData.h"
#include "GameObject.h"
#include "CAttributeSystem.h"
#include "GameFilePreqs.h"
#include "SkillObject.h"
/******************************************************************************/
namespace MG
{
	class CTroopObject;
	struct TroopData;
	struct CCharacterSceneEntityDynamicData;
    class CCharacter : public GameObject
    {
        friend class CAttributeSystem;
    public:
        CCharacter(GAMEOBJ_TYPE type, GameObjectData* data, PlayerCharacterIdType id = 0);
        virtual ~CCharacter();

    public:
        CharacterData*				getCharacterData();

    public: // 【基础属性】
        // 设置和获得角色模板
        U32                         getCharacterTemplateID();
        void                        setCharacterTemplateID(U32 id);

        //设置和获得等级
        U32                         getLevel();
        void                        setLevel(U32 level);

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
        virtual UInt                getHp(){return 0;}
        virtual UInt                getMp(){return 0;}
        virtual UInt                getSp(){return 0;}
        virtual UInt                getLineageNum(){return 0;}
        virtual void                setHp(UInt val){}
        virtual void                setMp(UInt val){}
        virtual void                setSp(UInt val){}

        // 根据id 获得战斗属性
        Int                         getFanalValue(U32 id);
        // 根据id设置战斗属性
        void                        setFanalValue(U32 id, Flt val);
        /// 改变血 或 蓝 或 怒气值
        void                        setHpMpSp(Flt num, DamageType type, ATTACK_RESULT_TYPE resType);
        
    protected:
        // 计算最终属性
        void                        calAttr();

        //属性计算时需调用。
        virtual Flt                 getDBAttrInit(UInt index){return 0.f;}
        virtual Flt                 getDBAttrLvlAdd(UInt index){return 0.f;}
        // 计算其他属性
        virtual void                calOtherAttr(){}

    /// 属性计算相关 -- end
    ///----------------------------------------------------------------------------------------------

    public:  /// 得到技能管理器, 此管理器只负责技能逻辑数据保存
        //CSkillManagerForCharacter* getSkillManager(); 

      
	public:
		// 创建Troop
		CTroopObject*				createTroopObject( TroopData* data, CCharacterSceneEntityDynamicData* dynamicData);
		CTroopObject*				getTroopObject(IdType id);
		std::map<IdType, CTroopObject*>*	getTroopList(){return &mCTroopObjectList;}
		typedef std::map<IdType, CTroopObject*>::iterator  TroopObjectListIt;
		
    private:
        CAttributeSystem                mCAttributeSystem;
        const CharacterTempInfo*        mCharacterTempInfo;

		
		std::map<IdType, CTroopObject*> mCTroopObjectList;

    };

}
/******************************************************************************/
#endif
/******************************************************************************/