
/******************************************************************************/

#include "stdafx.h"
#include "SCharacter.h"
#include "CharacterList.h"
#include "SPlayer.h"
#include "MapListCsv.h"
#include "SAttributePacketProcesser.h"
#include "SSkillOwnManager.h"
#include "SSkillUseManager.h"
#include "SCDManager.h"
#include "SWorldManager.h"
#include "SFightManager.h"
#include "SFightMainManager.h"
#include "BaseAIGroupTemplate.h"
#include "FightAiGroupTemplate.h"
#include "SAIController.h"
#include "SActionManager.h"
#include "SActionObjectManager.h"
#include "SCharacterMoveToAction.h"
#include "SAIManager.h"
#include "SFightHeartBeatManager.h"
#include "SSceneGridManager.h"
#include "MGStrOp.h"
#include "SBuffManager.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SCharacter::SCharacter(SCharacter& rhs)
		:GameObject(rhs)
		,mSkillUseManager(NULL)
		,mSkillOwnManager(NULL)
		,mSCDManager(NULL)
		,mCharacterTempInfo(rhs.mCharacterTempInfo)
		,mCanSeeByCamera(rhs.mCanSeeByCamera)
		,mOwnerPlayer(rhs.mOwnerPlayer)
		,mForce(FORCE_INIT)
		,mFightHeartBeatManager(NULL)
		,mActionManager(NULL)
		,mAIManager(NULL)
		,mBaseAIGroup(NULL)
		,mAliveTime(0)
		,mSceneObjectInSceneGridsManager(NULL)
		,mMoveSpeed(0)
		,mIndexIdInScene(rhs.mIndexIdInScene)
	{
		mBattleStatics.clearData();
		mpSBuffManager = rhs.getSBuffManager();
	}

	//-----------------------------------------------------------------------------
    SCharacter::SCharacter(GAMEOBJ_TYPE type, GameObjectData* data)
        :GameObject(type, GQT_UNKNOWN, data, 0)
        ,mCharacterTempInfo(NULL)
		,mCanSeeByCamera(false)
		,mForce(FORCE_INIT)
		,mAliveTime(0)
		,mMoveSpeed(0)
    {
    }

    //-----------------------------------------------------------------------------
    SCharacter::~SCharacter()
    {
    }

	//-----------------------------------------------------------------------------
	AccountIdType SCharacter::getAccountId()
	{
		DYNAMIC_ASSERT(0);
		return 0;
	}

	//-----------------------------------------------------------------------------
	NetIdType SCharacter::getFrontServerId()
	{
		DYNAMIC_ASSERT(0);
		return 0;
	}

	//-----------------------------------------------------------------------------
	NetIdType SCharacter::getClientNetIdInFrontServer()
	{
		DYNAMIC_ASSERT(0);
		return 0;
	}

	//-----------------------------------------------------------------------------
	ClanIdType SCharacter::getClanId()
	{
		DYNAMIC_ASSERT(0);
		return 0;
	}
    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    Bool SCharacter::initialize()
    {
        mSkillUseManager = MG_NEW SSkillUseManager(this);
        mSkillOwnManager = MG_NEW SSkillOwnManager(this);
		mpSBuffManager   = MG_NEW SBuffManager(this);

        mHeartBeatManager   = NULL;
        mActionManager      = NULL;
        mAIManager          = NULL;
        mSCDManager         = NULL;

        mSceneObjectInSceneGridsManager    = NULL;
        mFightHeartBeatManager              = NULL;
        mBaseAIGroup                        = NULL;
        
        return true;
    }
    
    //-----------------------------------------------------------------------------
    Bool SCharacter::unInitialize()
    {
        //TODO:
        {
            SFightMainManager::getInstance().delAllFightInfo(this);

            //SRegionObjectBase* regionObjectBase = NULL;//getCurrentRegionObject();
            //if(!regionObjectBase)
            //{
            //    return false;
            //}

            //if(regionObjectBase->getGameType() == GameType_Rpg)
            //{
            //    removeInSceneGrid();
            //}

            MG_SAFE_DELETE(mHeartBeatManager);
            MG_SAFE_DELETE(mSkillOwnManager);
            MG_SAFE_DELETE(mSkillUseManager);
            MG_SAFE_DELETE(mSCDManager);
            MG_SAFE_DELETE(mActionManager);
            MG_SAFE_DELETE(mAIManager);
            MG_SAFE_DELETE(mFightHeartBeatManager);
            MG_SAFE_DELETE(mSceneObjectInSceneGridsManager);
            MG_SAFE_DELETE(mpSBuffManager);
        }

        return true;
    }

    //-----------------------------------------------------------------------------
    void SCharacter::update(Flt delta)
    {
        //if(mHeartBeatManager)
        //{
        //    mHeartBeatManager->update();
        //}

        const U64 curTime = GetCurrentTime();
        const U64 aliveTime = getAliveTime();
        if (isDead() == true && aliveTime > 0)
        {
            if (aliveTime <= curTime)
            {
                //复活时间到
                setAlive(AliveType_TimeOut);
            }
        }

        mpSBuffManager->update(delta);
    }

    //-----------------------------------------------------------------------------
    void SCharacter::killMySelfForTest()
    {
        SAttributePacketProcesser::getInstance().syncCharacterHPMPSPToClient(this, this, DT_HP, 0, ATTACK_RESULT_TYPE_DEAD);
        setHp(0);
    }

    //-----------------------------------------------------------------------
    void SCharacter::print()
    {
        //GameObject::print();

        //std::string strOnwnerPlayer("空");
        //if (NULL != getOwnerPlayer())
        //{
        //    //MGStrOp::toString(getOwnerPlayer()->getAccountID(), strOnwnerPlayer);
        //}

        //MG_LOG(out_sys, "【SCharacterNew】mCanSeeByCamera[%d], mOwnerPlayerAccountId[%s]\n",
        //    getCanSeeByCamera(), strOnwnerPlayer.c_str());
    }


    //-----------------------------------------------------------------------------------
    // Base Info
    //-----------------------------------------------------------------------------------
	GameObjectIndexIdInSceneType SCharacter::getIndexIdInScene() const
	{
		return mIndexIdInScene;
	}

    //-----------------------------------------------------------------------------
    CharacterData* SCharacter::getCharacterData()
    {
        return (CharacterData*)getGameObjectData();
    }

    //-----------------------------------------------------------------------------
    MG::U32 SCharacter::getCharacterTemplateID()
    {
        return getCharacterData()->mCharacterTemplateID;
    }

    //-----------------------------------------------------------------------------
    void SCharacter::setCharacterTemplateID( U32 id )
    {
        getCharacterData()->mCharacterTemplateID = id;
    }

    //-----------------------------------------------------------------------------
    void SCharacter::setCharacterTempInfo()
    {
        mCharacterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(getCharacterData()->mCharacterTemplateID);
        DYNAMIC_ASSERT(NULL != mCharacterTempInfo);
    }
    //-----------------------------------------------------------------------------
    const CharacterTempInfo* SCharacter::getCharacterTempInfo()
    {
        return mCharacterTempInfo;
    }

    //-----------------------------------------------------------------------------
    void SCharacter::setLevel( U32 level )
    {
        getCharacterData()->mLevel = level;
        calAttr();
    }

    //-----------------------------------------------------------------------------
    MG::U32 SCharacter::getLevel()
    {
        return getCharacterData()->mLevel;
    }


    //-----------------------------------------------------------------------
    void SCharacter::setForce(FORCE force)
    {
        mForce = force;
    }

    //-----------------------------------------------------------------------
    FORCE SCharacter::getForce() const
    {
        return mForce;
    }


    //-----------------------------------------------------------------------------------
    // Alive
    //-----------------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    void SCharacter::setAlive(AliveType aliveType)
    {
        mAliveTime = 0;
    }


    //--------------------------------------------------------------------------
    void SCharacter::dead(SCharacter* murderer)
    {
        if (NULL != murderer)
        {
            //
            murderer->getBattleStatics()->incrementKillGeneralPoint(NULL);

            //我自己死了
            getBattleStatics()->incrementDeathPoint();
        }

        SFightMainManager::getInstance().delAllFightInfo(this);
    }

    //-----------------------------------------------------------------------------
    Bool SCharacter::isDead()
    {
        Int hp = (Int)getHp();
        return hp <= 0;
    }

    //-----------------------------------------------------------------------------
    void SCharacter::setAliveTime(const Int aliveTimeSecond)
    {
        mAliveTime = aliveTimeSecond * 1000 + GetCurrentTime();
    }
    //-----------------------------------------------------------------------------
    U64 SCharacter::getAliveTime() const
    {
        return mAliveTime;
    }
    //-----------------------------------------------------------------------------
    void SCharacter::setAlivePos(const Vec3& pos)
    {
        mAlivePos = pos;
    }
    //-----------------------------------------------------------------------------
    Vec3 SCharacter::getAlivePos() const
    {
        return mAlivePos;
    }

    //-----------------------------------------------------------------------------------
    // Region  Base
    //-----------------------------------------------------------------------------------



    //-----------------------------------------------------------------------------------
    // Region Grid
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    // Skill
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    SSkillOwnManager* SCharacter::getSkillOwnManager() const
    {
        return mSkillOwnManager;
    }
    //-----------------------------------------------------------------------------
    SSkillUseManager* SCharacter::getSkillUseManager() const
    {
        return mSkillUseManager;
    }

    //-----------------------------------------------------------------------------------
    // CD
    //-----------------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    SCDManager* SCharacter::getSCDManager()
    {
        return mSCDManager;
    }
    //--------------------------------------------------------------------------
    void SCharacter::setSCDManager( CD_MASTER_TYPE type, SCharacter* parent )
    {
        mSCDManager = new SCDManager(type, parent);
    }


    //-----------------------------------------------------------------------------------
    // Buff
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------
    SBuffManager* SCharacter::getSBuffManager()
    {
        return mpSBuffManager;
    }


    //-----------------------------------------------------------------------------------
    // Attr Info
    //-----------------------------------------------------------------------------------


	//-----------------------------------------------------------------------------
	Int SCharacter::getMaxHp()
	{
		return mSAttributeSystem.getMaxHp();
	}
	//-----------------------------------------------------------------------------
	Int SCharacter::getMaxMp()
	{
		return mSAttributeSystem.getMaxMp();
	}

	//-----------------------------------------------------------------------------
	Int SCharacter::getHp()
	{
		return getCharacterData()->mHp;
	}

	//-----------------------------------------------------------------------------
	Int SCharacter::getMp()
	{
		return getCharacterData()->mMp;
	}

	//-----------------------------------------------------------------------------
	Int SCharacter::getSp()
	{
		return getCharacterData()->mSp;
	}
	//-----------------------------------------------------------------------------
	void SCharacter::setHp(Int value, SCharacter* pMaster)
	{
		Int maxHp = getMaxHp();
		if ( value > maxHp )
			getCharacterData()->mHp = maxHp;
		else if ( value <= 0 )
		{	
			getCharacterData()->mHp = 0;
			if ( pMaster == NULL )
				pMaster = this;
			dead(pMaster);
		}
		else
			getCharacterData()->mHp = value;
		
	}
	//-----------------------------------------------------------------------------
	void SCharacter::setMp(Int value)
	{
		UInt maxMp = getMaxMp();
		if ( value > maxMp )
			getCharacterData()->mMp = maxMp;
		else if ( value < 0 )
		{	
			getCharacterData()->mMp = 0;
			//移除法力护盾
			mpSBuffManager->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
		}
		else
			getCharacterData()->mMp = value;
	}
	//-----------------------------------------------------------------------------
	void SCharacter::setSp(Int value)
	{
		UInt maxSp = getMaxSp();
		if ( value > maxSp )
			getCharacterData()->mSp = maxSp;
		else if ( value < 0 )
			getCharacterData()->mSp = 0;
		else
			getCharacterData()->mSp = value;
	}

    //-----------------------------------------------------------------------------------
    // World Info
    //-----------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	void SCharacter::setMoveSpeed(Flt speed)
	{
		mMoveSpeed = speed;
	}

    //-----------------------------------------------------------------------------
	Flt SCharacter::getMoveSpeed()
	{
		return mMoveSpeed;
	}

	//-----------------------------------------------------------------------
	void SCharacter::setCanSeeByCamera(Bool canSee)
	{
		mCanSeeByCamera = canSee;
	}

	//-----------------------------------------------------------------------
	Bool SCharacter::getCanSeeByCamera() const
	{
		return mCanSeeByCamera;
	}

	//--------------------------------------------------------------------------
	void SCharacter::setDir(Vec3 dir)
	{
		getCharacterData()->mDir = dir;
	}

	//--------------------------------------------------------------------------
	Vec3 SCharacter::getDir()
	{
		return getCharacterData()->mDir;
	}

    //--------------------------------------------------------------------------
	void SCharacter::setBirthPos(Vec3& pos)
	{
		getCharacterData()->mBirthPos = pos;
	}

    //--------------------------------------------------------------------------
	Vec3& SCharacter::getBirthPos()
	{
		return getCharacterData()->mBirthPos;
	}

	//--------------------------------------------------------------------------
	void SCharacter::setPos(Vec3& pos)
	{
		DYNAMIC_ASSERT(pos.x <= 0x7fff && pos.x >= -0x7fff);
		DYNAMIC_ASSERT(pos.z <= 0x7fff && pos.z>= -0x7fff);
		getCharacterData()->mPos = pos;
	}

	//--------------------------------------------------------------------------
	void SCharacter::setPos(Flt x, Flt z)
	{
		Vec3 pos(x, 0, z);
		setPos(pos);
	}

	//--------------------------------------------------------------------------
	Vec3& SCharacter::getPos()
	{
		return getCharacterData()->mPos;
	}

    //--------------------------------------------------------------------------
    void SCharacter::obtainDamage( SCharacter* master,  AttackType attacktype, DamageType damageType, ATTACK_POS attackPos, U32 formulaParaID, Int fixHateValue, UInt buffId, UInt addNum, UInt permillage )
    {
		Int hateValue = fixHateValue;
        mSAttributeSystem.obtainDamage(this, master, attacktype, damageType, attackPos, formulaParaID, hateValue, buffId, addNum, permillage);
    }

    //--------------------------------------------------------------------------
    AttributeSet* SCharacter::getAttributeSet()
    {
        return mSAttributeSystem.getCalAttrInfo();
    }

	//--------------------------------------------------------------------------
	void SCharacter::syncAddOrReduceHp(Int val)
	{
        //改变内存血量
		setHp(getHp() + val);
        //同步消息
        if ( val > 0 )
        {
            SAttributePacketProcesser::getInstance().syncCharacterHPMPSPToClient(this, this, DT_HP, val, ATTACK_RESULT_TYPE_RECOVER);
            SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(getFrontServerId(), this, DT_HP, 0, ATTACK_RESULT_TYPE_RECOVER);
        }
        else
        {
            SAttributePacketProcesser::getInstance().syncCharacterHPMPSPToClient(this, this, DT_HP, val, ATTACK_RESULT_TYPE_HURT);
            SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(getFrontServerId(), this, DT_HP, 0, ATTACK_RESULT_TYPE_HURT);
        }
	}

	//--------------------------------------------------------------------------
	void SCharacter::syncAddOrReduceMp(Int val)
	{
        //改变内存MP
        setMp(getMp() + val);
        //同步消息
        if ( val > 0 )
        {
            SAttributePacketProcesser::getInstance().syncCharacterHPMPSPToClient(this, this, DT_MP, val, ATTACK_RESULT_TYPE_RECOVER);
            SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(getFrontServerId(), this, DT_MP, 0, ATTACK_RESULT_TYPE_RECOVER);
        }
        else
        {
            SAttributePacketProcesser::getInstance().syncCharacterHPMPSPToClient(this, this, DT_MP, -val, ATTACK_RESULT_TYPE_HURT);
            SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(getFrontServerId(), this, DT_MP, -val, ATTACK_RESULT_TYPE_HURT);
        }
	}

	//--------------------------------------------------------------------------
	void SCharacter::syncAddOrReduceSp(Int val)
	{
        //改变内存SP
        setSp(getSp() + val);
        //同步消息
        if ( val > 0 )
        {
            SAttributePacketProcesser::getInstance().syncCharacterHPMPSPToClient(this, this, DT_SP, val, ATTACK_RESULT_TYPE_RECOVER);
            SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(getFrontServerId(), this, DT_SP, 0, ATTACK_RESULT_TYPE_RECOVER);
        }
        else
        {
            SAttributePacketProcesser::getInstance().syncCharacterHPMPSPToClient(this, this, DT_SP, val, ATTACK_RESULT_TYPE_HURT);
            SAttributePacketProcesser::getInstance().sendCharacterHPMPSPToFrontServer(getFrontServerId(), this, DT_SP, 0, ATTACK_RESULT_TYPE_HURT);
        }
	}

    //--------------------------------------------------------------------------
    void SCharacter::calAttr()
    {
		
        mSAttributeSystem.calAttrBase(this);
        //计算其他属性。
        calAttrOther();
        mSAttributeSystem.calFinalAttr(mCharacterTempInfo->getCharacterFormulaType(), getCharacterData());

		//特殊属性。
		setMax_HpSpMp();
    }

    //--------------------------------------------------------------------------
	void SCharacter::setMax_HpSpMp()
	{
		setHp(getMaxHp());
		setMp(getMaxMp());
		setSp(getMaxSp());
	}


    //-----------------------------------------------------------------------------------
    // Fight Info
    //-----------------------------------------------------------------------------------



	//--------------------------------------------------------------------------
	SFightManager* SCharacter::getFightManager()
	{
		SFightManager* fightManager = NULL;

		if(mFightHeartBeatManager)
		{		
			fightManager = mFightHeartBeatManager->getFightManager();
		}

		return fightManager;
	}

	//--------------------------------------------------------------------------
	SActionManager* SCharacter::getActionManager()
	{
		return mActionManager;
	}

	//--------------------------------------------------------------------------
	const BaseAIGroup* SCharacter::getBaseAIGroup()
	{
		return mBaseAIGroup;
	}

	//--------------------------------------------------------------------------
	const FightAIGroup* SCharacter::getFightAIGroup()
	{
		return NULL;
	}

	//--------------------------------------------------------------------------
	void SCharacter::clear()
	{
		//if(getType() != GOT_SOLDIER)
		//{
		//	const CharacterTempInfo* characterTempInfo = getCharacterTempInfo();
		//	if(characterTempInfo)
		//	{
		//		mBaseAIGroup = BaseAIGroupTemplate::getInstance().getBaseAIGroup(characterTempInfo->getAIBaseGroupId());
		//	}
		//	
		//	//mSceneGridInteractionList = MG_NEW SSceneGridInteractionList;

		//	mHeartBeatManager = MG_NEW HeartBeatManager;
		//
		//	mActionManager = MG_NEW SActionManager;
		//	mHeartBeatManager->addHeartBeatObject(mActionManager);

		//	mAIManager = MG_NEW SAIManager;
		//	mHeartBeatManager->addHeartBeatObject(mAIManager);

		//	mFightHeartBeatManager = MG_NEW SFightHeartBeatManager(this);
		//	mFightHeartBeatManager->init();
		//	mHeartBeatManager->addHeartBeatObject(mFightHeartBeatManager);

		//	mHeartBeatManager->setHeartBeatTimeLength(10000);

		//	mSceneObjectInSceneGridsManager = MG_NEW SSceneObjectInSceneGridsManager;

		//	mMoveSpeed = mSAttributeSystem.getMoveSpeed();
		//}

	}

	//-----------------------------------------------------------------------
	void SCharacter::addFightAITriggerCount( UInt fightAIId )
	{
		
	}

	//-----------------------------------------------------------------------
	UInt SCharacter::getFightAITriggerCount( UInt fightAIId )
	{
		return 0;
	}

	//-----------------------------------------------------------------------
	void SCharacter::clearFightAITriggerCount()
	{
		
	}

	//-----------------------------------------------------------------------
	SAIController* SCharacter::getAIController()
	{
		return NULL;
	}

	//-----------------------------------------------------------------------
	void SCharacter::moveToPos( Vec3 startMovePos, Vec3 MoveToPos )
	{
		if(!mActionManager)
		{
			return;
		}

		SCharacterMoveToAction* characterMoveToAction = SActionObjectManager::getInstance().createSCharacterMoveToAction(this, startMovePos, MoveToPos);
		characterMoveToAction->setMoveSpeed(getMoveSpeed());
		mActionManager->push(characterMoveToAction);
	}

	//-----------------------------------------------------------------------
	void SCharacter::instantMoveToPos( Vec3 moveToPos )
	{
	}

	//-----------------------------------------------------------------------
	void SCharacter::stopMove()
	{
		if(!mActionManager)
		{
			return;
		}

		mActionManager->removeState("SCharacterMoveToAction", false);
	}

	//-----------------------------------------------------------------------------
	MG::Int SCharacter::getMaxSp()
	{
		return getSAttributeSystem()->getMaxSp();
	}

	//-----------------------------------------------------------------------------
	void SCharacter::itemTreat( DamageType type, Int treatValue )
	{
		mSAttributeSystem.itemTreat(this, type, treatValue);
	}

	//-----------------------------------------------------------------------------
	void SCharacter::skillTreat( SCharacter* treatSCharacter, SCharacter* masterSCharacter, DamageType type, U32 formulaParaID, Int& fixedHateValue, UInt buffId /*= 0*/, UInt addNum /*= 0*/, UInt permillage /*=0*/ )
	{
		mSAttributeSystem.skillTreat(treatSCharacter, masterSCharacter, type, formulaParaID, fixedHateValue, buffId, addNum, permillage);
	}

	//-----------------------------------------------------------------------------

    







}