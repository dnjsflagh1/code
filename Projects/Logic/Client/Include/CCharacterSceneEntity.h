/******************************************************************************/
#ifndef _H_CCHARACTER_SCENE_ENTITY_
#define _H_CCHARACTER_SCENE_ENTITY_
/******************************************************************************/
#include "ClientPreqs.h"
#include "GameObject.h"
#include "CharacterSceneEntity.h"
#include "CSceneEntity.h"
#include "CSceneObject.h"
/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //CCharacterSceneEntity
    /******************************************************************************/

    class CCharacterSceneEntity : public CSceneEntity, public CharacterSceneEntity
    {
    public:
        CCharacterSceneEntity(IEntity* entity, GAMEOBJ_TYPE type, GAMEOBJ_QUERY_TYPE queryType, CharacterEntityData* dynamicData);
        virtual ~CCharacterSceneEntity();

    public:

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //  [主要方法]
    //×××××××××××××××××××××××××××××××××××××××××××××××××
        // 初始化
        virtual void				        initialize();
        // 反初始化
        virtual void				        unInitialize();
        // 更新
        virtual void				        update( Flt delta );

        /// 得到技能使用管理者
        CSkillUseManager*	                getSkillUseManager(){return mSkillUseManager;};

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //  [基本属性]
    //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 得到基础数据
        //CharacterData*				        getBaseData();
        
        // 得到动态数据
        CharacterEntityData*				getDynamicData();

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //  [实体行为]
    //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 停止所有主要Action
        virtual void                        stopAllMainAction();
		
		// 设置战斗状图， 和平状态
		virtual void						setBattleState(Bool battleState, Bool isPlayIdle = false );

        //---------------------------------------------------------------------------------------

        // 开始死亡行为
        void                                doDieAction();
        // 停止死亡行为
        void                                stopDieAction();

		void								setIsMoving(Bool isMoving);
		Bool								getIsMoving();


        //---------------------------------------------------------------------------------------

        // 开始吟唱技能行为
        void                                doClantSkillAcion(IdType skillid);
        // 停止吟唱技能行为
        void                                stopClantSkillAcion();

		//---------------------------------------------------------------------------------------
		void								addEffect(UInt effectFileId, Bool isAutoDestroy = true );

		void								endEffect(UInt effectFileId);

        //---------------------------------------------------------------------------------------

        // 开始释放技能行为
        void                                doInjectSkillAction(IdType skillid);
        void                                doInjectSkillAction(IdType skillid, Vec3 target);
        void                                doInjectSkillAction(IdType skillid, GAMEOBJ_TYPE targetType, IdType targetId);
        // 停止释放技能行为
        void                                stopInjectSkillAction();

        //---------------------------------------------------------------------------------------

		void								setAIEnable( Bool enable );

		//---------------------------------------------------------------------------------------

		void								setAIController( Bool enable );

		//---------------------------------------------------------------------------------------
	//×××××××××××××××××××××××××××××××××××××××××××××××××
	// [characterentitydata]
	//×××××××××××××××××××××××××××××××××××××××××××××××××
		void								setHp(Int val);
		void								setMp(Int val);
		void								setSp(Int val);
		void								setHpMax(Int val);
		void								setMpMax(Int val);
		void								setSpMax(Int val);
		Int									getHp();
		Int									getMp();
		Int									getSp();
		Int									getHpMax();
		Int									getMpMax();
		Int									getSpMax();

    //×××××××××××××××××××××××××××××××××××××××××××××××××
    //  [头顶字]
    //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 显示伤血
        void                                showReduceHP(UInt num);
        // 显示加血
        void                                showRecoverHP(UInt num);

		virtual void						setPos(Vec3 pos);
		virtual void						setDir(Vec3 dir);

		virtual Vec3						getPos(Bool isIgnoreHeight = true);
		virtual Vec3						getDir();

		void								setIsCanMove(Bool isCanMove);
		Bool								getIsCanMove();

		void								die();

	public:
		//状态管理器的销毁
		CBuffManager*						getCBuffManager();
		///////////////////////////////////////////////////////////////////////////////////////////

		//得到角色模板指针
		const CharacterTempInfo*            getCharacterTempInfo();
		void								setCharacterTempInfo();

		//状态管理器的销毁

		///////////////////////////////////////////////////////////////////////////////////////////
		const FightAIGroup*					getFightAIGroup();

		const BaseAIGroup*					getBaseAIGroup();

		///////////////////////////////////////////////////////////////////////////////////////////

		void								addFightAITriggerCount( UInt fightAIId );

		UInt								getFightAITriggerCount( UInt fightAIId );

		void								clearFightAITriggerCount();

	public:

		CAIController*						getAIController();
		//FightManager*						getFightManager();

		///////////////////////////////////////////////////////////////////////////////////////////
		

    protected:

		CBuffManager*						mpCBuffManager;

        CSkillUseManager*					mSkillUseManager;
		//FightManager*						mFightManager;
		//角色模版信息
		const CharacterTempInfo*			mCharacterTempInfo;

		const BaseAIGroup*					mBaseAIGroup;
		const FightAIGroup*					mFightAIGroup;

		CAIController*						mAIController;

		std::map<UInt, UInt>				mFightAITriggerCountList;

		Bool								mIsMoving;
		Bool								mIsCanMove;

		IEffectComponent*					mEffectComponent;
        Str     						    mEffectName;
		UInt								mEffectFileId;
    };
}
/******************************************************************************/
#endif // _H_CCHARACTER_SCENE_ENTITY_
/******************************************************************************/