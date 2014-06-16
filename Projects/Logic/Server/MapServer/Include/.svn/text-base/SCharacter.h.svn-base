
//*************************************************************************************************

#ifndef _H_SCHARACTER_
#define _H_SCHARACTER_

//*************************************************************************************************

#include "MapServerPreqs.h"
#include "GameObject.h"
#include "SAttributeSystem.h"
#include "CharacterData.h"
#include "CharacterSceneObj.h"
#include "CharacterList.h"
#include "BattleStatics.h"
#include "SceneFileLoader.h"

//*************************************************************************************************
namespace MG
{

	/******************************************************************************/
	//MapServer的 对象 基类, 可以派生
	/******************************************************************************/
    class SCharacter : public GameObject, public CharacterSceneObj
    {
    public:
		SCharacter(SCharacter& rhs);
        SCharacter(GAMEOBJ_TYPE type, GameObjectData* data);
        virtual ~SCharacter();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                            initialize();
        virtual Bool                            unInitialize();
        virtual void                            clear();

	    virtual	void							update(Flt delta);

        //-----------------------------------------------------------------------------------
        // Debug
        //-----------------------------------------------------------------------------------

		void									killMySelfForTest();
		virtual void							print();

        //-----------------------------------------------------------------------------------
        // Base Info
        //-----------------------------------------------------------------------------------

		// 由子类的 SPlayerIdentifyInfo 实现
		virtual AccountIdType	                getAccountId();
		virtual NetIdType 		                getFrontServerId();
		virtual NetIdType 		                getClientNetIdInFrontServer();
		virtual ClanIdType		                getClanId();


		GameObjectIndexIdInSceneType			getIndexIdInScene() const;
        CharacterData*			    			getCharacterData();
        // 设置和获得角色模板
        U32                        				getCharacterTemplateID();
        void                       				setCharacterTemplateID(U32 id);

        //得到和获得角色模板指针
        void                        			setCharacterTempInfo();
        const CharacterTempInfo*    			getCharacterTempInfo();

        void									setForce(FORCE force);
        FORCE									getForce() const;

        U32                        				getLevel();
        void                       				setLevel(U32 level);

        //-----------------------------------------------------------------------------------
        // Alive
        //-----------------------------------------------------------------------------------

        virtual void                			dead(SCharacter* murderer);
				Bool							isDead();
		virtual void							setAlive(AliveType aliveType);	//复活操作

        //复活相关操作
        void		                            setAliveTime(const Int aliveTimeSecond);
        U64			                            getAliveTime() const;
        void		                            setAlivePos(const Vec3& pos);
        Vec3		                            getAlivePos() const;

        //-----------------------------------------------------------------------------------
        // Region  Base
        //-----------------------------------------------------------------------------------
	
        // 设置和得到所属场景
        void                                    setBelongScene( SSceneObjectPtr& ptr, GameObjectIndexIdInSceneType index );
        void                                    getBelongScene( SSceneObjectPtr& ptr );
        GameObjectIndexIdInSceneType            getIndexInBelongScene();

        //-----------------------------------------------------------------------------------
        // Skill
        //-----------------------------------------------------------------------------------
	
		SSkillUseManager*						getSkillUseManager() const;
		SSkillOwnManager*						getSkillOwnManager() const;

        //-----------------------------------------------------------------------------------
        // CD
        //-----------------------------------------------------------------------------------

		SCDManager*								getSCDManager() ;
		void									setSCDManager(CD_MASTER_TYPE type, SCharacter* parent) ;

        //-----------------------------------------------------------------------------------
        // Buff
        //-----------------------------------------------------------------------------------

		SBuffManager*							getSBuffManager();

        //-----------------------------------------------------------------------------------
        // Attr Info
        //-----------------------------------------------------------------------------------

		Int										getMaxHp();
		Int										getMaxMp();
		Int										getMaxSp();
		Int										getHp();
		Int										getMp();
		Int										getSp();
		void									setHp(Int value, SCharacter* pMaster = NULL);
		void									setMp(Int value);
		void									setSp(Int value);

        ///属性计算相关
        //计算属性
        virtual UInt                            getLineageNum(){return 0;}
        virtual Flt                             getDBAttrInit(UInt index){return 0.f;}
        virtual Flt                				getDBAttrLvlAdd(UInt index){return 0.f;}
        virtual UInt							getDBAttrInitID(){return 0;}
        virtual UInt							getDBAttrLvlAddID(){return 0;}

        void                       				calAttr();
        virtual void							calAttrOther(){;}
        void									setMax_HpSpMp();

        void                       				obtainDamage( SCharacter* master, AttackType attacktype, DamageType damageType, ATTACK_POS attackPos, U32 formulaParaID, Int fixHateValue = 0, UInt buffId = 0, UInt addNum = 0, UInt permillage = 0);
        void									itemTreat( DamageType type, Int treatValue);
        void									skillTreat( SCharacter* treatSCharacter, SCharacter* masterSCharacter, DamageType type, U32 formulaParaID, Int& fixedHateValue, UInt buffId = 0, UInt addNum = 0, UInt permillage =0);
        AttributeSet*              				getAttributeSet(); 
        SAttributeSystem*          				getSAttributeSystem(){return &mSAttributeSystem;}

        //jijingjing专用，此函数用于同步hp，mp，sp。
        void									syncAddOrReduceHp(Int val);
        void									syncAddOrReduceMp(Int val);
        void									syncAddOrReduceSp(Int val);

        //-----------------------------------------------------------------------------------
        // World Info
        //-----------------------------------------------------------------------------------

        void									setCanSeeByCamera(Bool canSee);		//ylh
        Bool									getCanSeeByCamera() const;			//ylh

		void									setMoveSpeed(Flt speed);
		Flt										getMoveSpeed();

		Vec3 									getDir();
		void 									setDir(Vec3 dir);

		void									setBirthPos(Vec3& pos);				//出生点
		Vec3&									getBirthPos();

		void									setPos(Flt x, Flt z);
		void									setPos(Vec3& pos);
		Vec3&									getPos();

        virtual void							moveToPos( Vec3 startMovePos, Vec3 MoveToPos );

        virtual void							instantMoveToPos( Vec3 moveToPos );

        virtual void							stopMove();


        //-----------------------------------------------------------------------------------
        // Fight Info
        //-----------------------------------------------------------------------------------

        //是否正在和非武将战斗
        Bool									ifFightNoPlayerCharacter(){return false;}
		BattleStatics*							getBattleStatics() { return &mBattleStatics; };

        SFightManager*							getFightManager();
        virtual void							addFightAITriggerCount( UInt fightAIId );
        virtual UInt							getFightAITriggerCount( UInt fightAIId );
        virtual void							clearFightAITriggerCount();

        //-----------------------------------------------------------------------------------
        // AI & Action Info
        //-----------------------------------------------------------------------------------

		SActionManager*							getActionManager();
		SAIManager*								getAIManager(){return mAIManager;};
        virtual const BaseAIGroup*				getBaseAIGroup();
        virtual const FightAIGroup*				getFightAIGroup();

		virtual SAIController*					getAIController();

        //-----------------------------------------------------------------------------------
        //-----------------------------------------------------------------------------------
        
	protected:

		SActionManager*							mActionManager;	

		SAIManager*								mAIManager;

		HeartBeatManager*						mHeartBeatManager;

		const BaseAIGroup*						mBaseAIGroup;

		SSceneObjectInSceneGridsManager*		mSceneObjectInSceneGridsManager;

		Flt										mMoveSpeed;

    private:

		SBuffManager*							mpSBuffManager;

		//技能
		SSkillUseManager*						mSkillUseManager;
		SSkillOwnManager*						mSkillOwnManager;
		SFightHeartBeatManager*					mFightHeartBeatManager;

		//CD
		SCDManager*								mSCDManager;
        SAttributeSystem                		mSAttributeSystem;
        const CharacterTempInfo*        		mCharacterTempInfo;

        // 当player在同一个区域的时候可见， 否则不可见
		Bool									mCanSeeByCamera;			

		//所属玩家角色
		SPlayer*								mOwnerPlayer;

		FORCE									mForce;

        //战斗统计
		BattleStatics							mBattleStatics;			

        //复活时间
		U64										mAliveTime;				
		Vec3									mAlivePos;

		GameObjectIndexIdInSceneType			mIndexIdInScene;

	private:

		SCharacter();
		SCharacter& operator=(const SCharacter&);
    };
}


//*************************************************************************************************
#endif
//*************************************************************************************************