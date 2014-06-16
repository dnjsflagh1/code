/******************************************************************************/
#include "stdafx.h"
#include "CCharacterSceneEntity.h"
#include "CharacterList.h"
#include "CSkillUseManager.h"
#include "PlayerCharacterData.h"
#include "CActionManager.h"
#include "CharacterSceneEntityAction.h"
#include "CAIManager.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "FightManager.h"
#include "FightAiGroupTemplate.h"
#include "BaseAIGroupTemplate.h"
#include "CAIController.h"
#include "IEffectEntity.h"
#include "CBuffManager.h"
/******************************************************************************/
namespace MG
{
    CCharacterSceneEntity::CCharacterSceneEntity(IEntity* entity, GAMEOBJ_TYPE type, GAMEOBJ_QUERY_TYPE queryType, CharacterEntityData* dynamicData)
        :CSceneEntity(entity, type, queryType, dynamicData)
		,mIsMoving(false)
		,mEffectComponent(NULL)
		,mEffectFileId(0)
		,mIsCanMove(true)
        ,mCharacterTempInfo(NULL)
		//,mFightManager(NULL)
		,mFightAIGroup(NULL)
		,mBaseAIGroup(NULL)
		,mAIController(NULL)
    {
        mSkillUseManager = MG_NEW CSkillUseManager(this);
		//状态管理器的创建
		mpCBuffManager = MG_NEW CBuffManager(this);
    }
    //---------------------------------------------------------------------------------
    CCharacterSceneEntity::~CCharacterSceneEntity()
    {
		getActionStateManager().clear();
		getAIStateManager().clear();
    
        endEffect(mEffectFileId);

        MG_SAFE_DELETE(mSkillUseManager);
		MG_SAFE_DELETE(mAIController);
		//状态管理器的销毁
		MG_SAFE_DELETE(mpCBuffManager);
    }

    //---------------------------------------------------------------------------------
    void CCharacterSceneEntity::update( Flt delta )
    {
        CSceneEntity::update( delta );
		mSkillUseManager->update(delta);
		//状态管理器的更新
		mpCBuffManager->update(delta);

		if(mAIController)
		{
			if(getAIStateManager().isEmpty() && mAIController->getIsPause())
			{
				mAIController->setIsPause(false);
			}

			mAIController->update(delta);
		}
    }

    ////---------------------------------------------------------------------------------
    //CharacterData* CCharacterSceneEntity::getBaseData()
    //{
    //    return (CharacterData*)(GameObject::getGameObjectData());
    //}

    //---------------------------------------------------------------------------------
    CharacterEntityData* CCharacterSceneEntity::getDynamicData()
    {
        return dynamic_cast<CharacterEntityData*>(getGameObjectData());
    }
    //---------------------------------------------------------------------------------
    void CCharacterSceneEntity::stopAllMainAction()
    {
        CSceneEntity::stopAllMainAction();

        stopDieAction();
        stopClantSkillAcion();
        stopInjectSkillAction();
    }

    //---------------------------------------------------------------------------------------
    void CCharacterSceneEntity::doDieAction()
    {
        
    }

    //---------------------------------------------------------------------------------------
    void CCharacterSceneEntity::stopDieAction()
    {

    }

  
    //---------------------------------------------------------------------------------------
    void CCharacterSceneEntity::doClantSkillAcion(IdType skillid)
    {

    }

    //---------------------------------------------------------------------------------------
    void CCharacterSceneEntity::stopClantSkillAcion()
    {

    }

    //---------------------------------------------------------------------------------------
    void CCharacterSceneEntity::doInjectSkillAction(IdType skillid)
    {

    }

    //---------------------------------------------------------------------------------------
    void CCharacterSceneEntity::doInjectSkillAction(IdType skillid, Vec3 target)
    {

    }

    //---------------------------------------------------------------------------------------
    void CCharacterSceneEntity::doInjectSkillAction(IdType skillid, GAMEOBJ_TYPE targetType, IdType targetId)
    {

    }

    //---------------------------------------------------------------------------------------
    void CCharacterSceneEntity::stopInjectSkillAction()
    {

    }

    //---------------------------------------------------------------------------------------
    void CCharacterSceneEntity::showReduceHP(UInt num)
    {

    }

    //---------------------------------------------------------------------------------------
    void CCharacterSceneEntity::showRecoverHP(UInt num)
    {

    }

	//---------------------------------------------------------------------------------------
	void CCharacterSceneEntity::setPos(Vec3 pos)
	{
		mEntity->getSceneNode()->setPosition(pos);
	}

	//---------------------------------------------------------------------------------------
	void CCharacterSceneEntity::setDir(Vec3 dir)
	{
		mEntity->getSceneNode()->setDirection(dir);
	}

	//---------------------------------------------------------------------------------------
	Vec3 CCharacterSceneEntity::getPos(Bool isIgnoreHeight)
	{
		Vec3 pos;
		mEntity->getSceneNode()->getPosition(pos);
		if(isIgnoreHeight)
		{
			pos.y = 0;
		}

		return pos;
	}

	//---------------------------------------------------------------------------------------
	Vec3 CCharacterSceneEntity::getDir()
	{
		Vec3 dir;
		mEntity->getSceneNode()->getDirection(dir);

		return dir;
	}

	//---------------------------------------------------------------------------------------
	void CCharacterSceneEntity::die()
	{
		getDynamicData()->isDied = true;

		stopAllMainAction();

		getAIStateManager().setIsPush(true);
		getActionStateManager().setIsPush(true);

		CAIEntityDie* aiEntityDie = CAIManager::getInstance().createCAIEntityDie(this);

        getAIStateManager().push( aiEntityDie, true );
	}

	//---------------------------------------------------------------------------------------
	void CCharacterSceneEntity::setIsMoving( Bool isMoving)
	{
		mIsMoving = isMoving;
	}

	//---------------------------------------------------------------------------------------
	Bool CCharacterSceneEntity::getIsMoving()
	{
		return mIsMoving;
	}

	//---------------------------------------------------------------------------------------
    void CCharacterSceneEntity::initialize()
    {
		setCharacterTempInfo();
        CSceneEntity::initialize();

		if(getType() != GOT_SOLDIER)
		{
			//mFightManager = new FightManager(getType(), getID());
			mFightAIGroup = FightAIGroupTemplate::getInstance().getFightAIGroup(mCharacterTempInfo->getAIFightGroupId());
			mBaseAIGroup = BaseAIGroupTemplate::getInstance().getBaseAIGroup(mCharacterTempInfo->getAIBaseGroupId());
		}

		// 重设置动画
    }

    //---------------------------------------------------------------------------------------
    void CCharacterSceneEntity::unInitialize()
    {
        CSceneEntity::unInitialize();
		//MG_SAFE_DELETE(mFightManager);

        endEffect( mEffectFileId );
    }

	//---------------------------------------------------------------------------------------
	void CCharacterSceneEntity::addEffect( UInt effectFileId, Bool isAutoDestroy )
	{
        endEffect( mEffectFileId );

		// CN_MODIFY
		mEffectComponent = CSceneManager::getInstance().getEngineScene()->createEffectComponent(effectFileId, isAutoDestroy);
        //DYNAMIC_ASSERT_LOG( mEffectEntity != NULL , "createEffectComponent failed!" );

		if(mEffectComponent)
		{
			Vec3 pos;
			mEntity->getSceneNode()->getPosition(pos);
			mEffectComponent->getSceneNode()->setPosition(pos);
			mEffectComponent->setBindSlot(0, mEntity);
			mEffectFileId   = effectFileId;
            mEffectName     = mEffectComponent->getName();
		}
	}

	//---------------------------------------------------------------------------------------
	void CCharacterSceneEntity::endEffect(UInt effectFileId)
	{
		if(mEffectComponent)
		{
           // DYNAMIC_ASSERT_LOG( mEffectFileId == effectFileId , "endEffect diff effect id" );
		   // DYNAMIC_ASSERT(mEffectFileId == effectFileId );

			// CN_MODIFY
			CSceneManager::getInstance().getEngineScene()->destroyEffectComponent(mEffectName.c_str());
			mEffectComponent = NULL;
			mEffectFileId = 0;
            mEffectName   = "";
		}
	}
	//---------------------------------------------------------------------------------
	const CharacterTempInfo* CCharacterSceneEntity::getCharacterTempInfo()
    {
        if ( mCharacterTempInfo == NULL )
            setCharacterTempInfo();
		return mCharacterTempInfo;
	}
	//---------------------------------------------------------------------------------
	void CCharacterSceneEntity::setCharacterTempInfo()
	{
		mCharacterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(getDynamicData()->mCharacterTemplateID);
	}

	//---------------------------------------------------------------------------------
	void CCharacterSceneEntity::setIsCanMove(Bool isCanMove)
	{
		mIsCanMove = isCanMove;
	}

	//---------------------------------------------------------------------------------
	Bool CCharacterSceneEntity::getIsCanMove()
	{
		return mIsCanMove;
	}

	//---------------------------------------------------------------------------------
	//FightManager* CCharacterSceneEntity::getFightManager()
	//{
	//	return mFightManager;
	//}

	//---------------------------------------------------------------------------------
	const FightAIGroup*	CCharacterSceneEntity::getFightAIGroup()
	{
		return mFightAIGroup;
	}

	//---------------------------------------------------------------------------------
	const BaseAIGroup* CCharacterSceneEntity::getBaseAIGroup()
	{
		return mBaseAIGroup;
	}

	//-----------------------------------------------------------------------
	void CCharacterSceneEntity::addFightAITriggerCount( UInt fightAIId )
	{
		mFightAITriggerCountList[fightAIId]++;
	}

	//-----------------------------------------------------------------------
	UInt CCharacterSceneEntity::getFightAITriggerCount( UInt fightAIId )
	{
		std::map<UInt, UInt>::iterator it = mFightAITriggerCountList.find(fightAIId);
		if(it == mFightAITriggerCountList.end())
		{
			return 0;
		}

		return it->second;
	}

	//-----------------------------------------------------------------------
	void CCharacterSceneEntity::clearFightAITriggerCount()
	{
		mFightAITriggerCountList.clear();
	}

	//-----------------------------------------------------------------------
	CAIController* CCharacterSceneEntity::getAIController()
	{
		return mAIController;
	}

	//-----------------------------------------------------------------------
	void CCharacterSceneEntity::setAIEnable( Bool enable )
	{
		CSceneObject::setAIEnable(enable);

		if(enable && !mAIController)
		{
			//mAIController = MG_NEW CAIController(this);
			//mAIController->Init();
		}
		else if(!enable)
		{
			MG_SAFE_DELETE(mAIController);
		}
	}

	//-----------------------------------------------------------------------
	void CCharacterSceneEntity::setAIController( Bool enable )
	{
		if(enable && !mAIController)
		{
			mAIController = MG_NEW CAIController(this);
			mAIController->Init();
		}
		else if(!enable)
		{
			MG_SAFE_DELETE(mAIController);
		}
	}

	//-----------------------------------------------------------------------
	void CCharacterSceneEntity::setBattleState( Bool isBattle, Bool isPlayIdle )
	{
		CharacterEntityData* data = getDynamicData();
		if ( data )
		{
			data->isFightState = isBattle;
		}

		if ( isBattle )
		{
			setIdleAnimation("stand", false, isPlayIdle);
			setIdleAnimation("guard", true, isPlayIdle);
		}
		else
		{
			setIdleAnimation("guard", false, isPlayIdle);
			setIdleAnimation("stand", true, isPlayIdle);
		}
	}
	//-----------------------------------------------------------------------
	CBuffManager* CCharacterSceneEntity::getCBuffManager()
	{
		DYNAMIC_ASSERT(mpCBuffManager);
		return mpCBuffManager;
	}
	//-----------------------------------------------------------------------
	void CCharacterSceneEntity::setHp( Int val )
	{
		if ( val > getDynamicData()->hpmax )
			getDynamicData()->hp = getDynamicData()->hpmax;
		else if ( val <= 0 )
		{
			getDynamicData()->hp = 0;
			//die();
		}
		else
			getDynamicData()->hp = val;
	}
	//-----------------------------------------------------------------------
	void CCharacterSceneEntity::setMp( Int val )
	{
		if ( val > getDynamicData()->mpmax )
			getDynamicData()->mp = getDynamicData()->mpmax;
		else if ( val <= 0 )
		{
			getDynamicData()->mp = 0;
			//法力护盾耗尽。
			mpCBuffManager->deleteBuffByAbsorbType(STATUS_ABSORBTYPE_MAGIC);
		}
		else
			getDynamicData()->mp = val;
	}
	//-----------------------------------------------------------------------
	void CCharacterSceneEntity::setSp( Int val )
	{
		if ( val > getDynamicData()->spmax )
			getDynamicData()->sp = getDynamicData()->spmax;
		else if ( val <= 0 )
		{
			getDynamicData()->sp = 0;
		}
		else
			getDynamicData()->sp = val;
	}
	//-----------------------------------------------------------------------
	void CCharacterSceneEntity::setHpMax( Int val )
	{
		DYNAMIC_ASSERT(val > 0);
		getDynamicData()->hpmax = val;
		if ( getDynamicData()->hp > val )
			getDynamicData()->hp = val;
	}
	//-----------------------------------------------------------------------
	void CCharacterSceneEntity::setMpMax( Int val )
	{
		DYNAMIC_ASSERT(val > 0);
		getDynamicData()->mpmax = val;
		if ( getDynamicData()->mp > val )
			getDynamicData()->mp = val;
	}
	//-----------------------------------------------------------------------
	void CCharacterSceneEntity::setSpMax( Int val )
	{
		DYNAMIC_ASSERT(val > 0);
		getDynamicData()->spmax = val;
		if ( getDynamicData()->sp > val )
			getDynamicData()->sp = val;
	}
	//-----------------------------------------------------------------------
	MG::Int CCharacterSceneEntity::getHp()
	{
		return getDynamicData()->hp;
	}
	//-----------------------------------------------------------------------
	MG::Int CCharacterSceneEntity::getMp()
	{
		return getDynamicData()->mp;
	}
	//-----------------------------------------------------------------------
	MG::Int CCharacterSceneEntity::getSp()
	{
		return getDynamicData()->sp;
	}
	//-----------------------------------------------------------------------
	MG::Int CCharacterSceneEntity::getHpMax()
	{
		return getDynamicData()->hpmax;
	}
	//-----------------------------------------------------------------------
	MG::Int CCharacterSceneEntity::getMpMax()
	{
		return getDynamicData()->mpmax;
	}
	//-----------------------------------------------------------------------
	MG::Int CCharacterSceneEntity::getSpMax()
	{
		return getDynamicData()->spmax;
	}
}