/******************************************************************************/
#include "stdafx.h"
#include "CharacterSceneEntityAction.h"
#include "CCharacterSceneEntity.h"
#include "CSceneManager.h"
#include "CSkillObject.h"
#include "SkillNetPacketProcesser.h"
#include "CPlayer.h"
#include "SkillBaseInfo.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //对象吟唱技能行为
    /******************************************************************************/

    Str CCSEntityClantSkillAcion::STATE_NAME = "CCSEntityClantSkillAcion";

    //-----------------------------------------------------------------------
    CCSEntityClantSkillAcion::CCSEntityClantSkillAcion(CSkillObject* object)
        :LinedStateObject(STATE_NAME)
        ,mSkillObject(object)
    {
		// 检测是否为本机控制的实体
		// mIsBelongSelf
    }

    //-----------------------------------------------------------------------
    CCSEntityClantSkillAcion::~CCSEntityClantSkillAcion()
    {

    }

    //-----------------------------------------------------------------------
    void CCSEntityClantSkillAcion::update( Flt delta )
    {

    }

    //-----------------------------------------------------------------------
    Bool CCSEntityClantSkillAcion::isFinished()
    {
        if ( mSkillObject->isClanting() )
            return false;

        //是否移动结束
        return true;
    }

    //-----------------------------------------------------------------------
    void CCSEntityClantSkillAcion::onEnter()
    {
		CCharacterSceneEntity* owner = mSkillObject->getOwner();
		if(owner)
		{
			if(owner->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
			{
				mIsBelongSelf = true;
			}
		}
		
        if ( mIsBelongSelf  )
        {
            // 当玩家角色属与自己时，需要开启计时检查
            mSkillObject->startClant( true );
        }else
        {
            // 当玩家角色不属与自己时，不需要开启计时检查
            mSkillObject->startClant( false );
        }
    }

    //-----------------------------------------------------------------------
    void CCSEntityClantSkillAcion::onLeave()
    {
        if ( mIsBelongSelf )
        {
            if ( mSkillObject->isFinished() )
            {
                // 当玩家角色属与自己时，需要通知服务器释放技能
                GAMEOBJ_TYPE type = mSkillObject->getOwnerType();
                if(type == GOT_PLAYERCHARACTER)
                {
                    SkillNetPacketProcesser::getInstance().sendPlayCharacterInjectSkillRequestPacketToPackBuffer( mSkillObject );
                }
                else if(type == GOT_TROOP)
                {
                    SkillNetPacketProcesser::getInstance().sendTroopInjectSkillRequestPacketToPackBuffer( mSkillObject );
                }
            }
        }

        mSkillObject->stopUse();
    }



    /******************************************************************************/
    //对象发射技能行为
    /******************************************************************************/

    Str CCSEntityInjectSkillAcion::STATE_NAME = "CCSEntityInjectSkillAcion";
    

    //-----------------------------------------------------------------------
    CCSEntityInjectSkillAcion::CCSEntityInjectSkillAcion(CSkillObject* object)
        :LinedStateObject(STATE_NAME)
        , mSkillObject(object)
        , mIsBelongSelf(false)
    {


    }

    //-----------------------------------------------------------------------
    CCSEntityInjectSkillAcion::~CCSEntityInjectSkillAcion()
    {

    }

    //-----------------------------------------------------------------------
    void CCSEntityInjectSkillAcion::update( Flt delta )
    {


    }

    //-----------------------------------------------------------------------
    Bool CCSEntityInjectSkillAcion::isFinished()
    {
        if ( mSkillObject->isInjecting() )
            return false;

        return true;
    }

    //-----------------------------------------------------------------------
    void CCSEntityInjectSkillAcion::onEnter()
    {
		SkillInfo* skillInfo = mSkillObject->getSkillInfo();
		if(!skillInfo)
		{
			destroy();
			return;
		}
        CCharacterSceneEntity* characterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getOwnerIndex());
        if(!characterSceneEntity)
        {
			destroy();
            return;
        }

		Vec3 targetPos;
		
		if(mSkillObject->getTargetObjectID() != 0)
		{
			CCharacterSceneEntity* targetEntity = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getTargetObjectType(), mSkillObject->getTargetObjectID(), mSkillObject->getTargetObjectIndex());
			if(!targetEntity)
			{
				destroy();
				return;
			}

			targetPos = targetEntity->getPos();
		}
		else
		{
			targetPos = mSkillObject->getTargetPosition();
		}

		if(skillInfo->skillType != SKT_SELFAREA)
		{
			Vec3 dir = targetPos - characterSceneEntity->getPos();
			dir.normalise();

			characterSceneEntity->setDir(dir);
		}

        if(CPlayer::getInstance().getAccountID() ==  characterSceneEntity->getDynamicData()->belongPlayerID)
        {
            mIsBelongSelf = true;
        }

        //FUNDETECTION(__MG_FUNC__);
        //mSkillObject->getOwner()
        if ( mIsBelongSelf  )
        {
            // 当玩家角色属与自己时，需要开启计时检查
            mSkillObject->startInject( true );
            //((CCharacterSceneEntity*)mSkillObject->getOwner())->addSkillCD(mSkillObject->getBaseInfo());
        }else
        {
            // 当玩家角色不属与自己时，不需要开启计时检查
            mSkillObject->startInject( false );
        }
    }

    //-----------------------------------------------------------------------
    void CCSEntityInjectSkillAcion::onLeave()
    {
		mSkillObject->stopUse();
    }

}