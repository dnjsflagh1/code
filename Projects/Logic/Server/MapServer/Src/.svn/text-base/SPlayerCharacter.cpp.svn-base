
/******************************************************************************/

#include "stdafx.h"
#include "SPlayerCharacter.h"
#include "PlayerCharacterData.h"
#include "SCharacter.h"
#include "SPlayer.h"
#include "SCDManager.h"
#include "SRegionNetPacketProcesser.h"
#include "SPlayerCharacterNetPacketProcesser.h"
#include "SActionManager.h"
#include "SSkillOwnManager.h"
#include "SBuffManager.h"
#include "SGameObjectFactory.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //SPlayerCharacter智能指针
    /******************************************************************************/

    //-----------------------------------------------------------------------------
    void SPlayerCharacterPtr::destroy(void)
    {
        mFactory->destroySPlayerCharacterPtr( *this );
    }

    /******************************************************************************/
    //SPlayerCharacter
    /******************************************************************************/

    //-----------------------------------------------------------------------------
	SPlayerCharacter::SPlayerCharacter()
		:SCharacter(GOT_PLAYERCHARACTER, &mPlayerCharacterData)
		,mIsBattleLeader(false)
	{
	}

	//-----------------------------------------------------------------------------
	SPlayerCharacter::~SPlayerCharacter()
	{
	}

    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------
    Bool SPlayerCharacter::initialize(PlayerCharacterIdType playerCharacterId, PlayerCharacterData& pData )
    {
        SCharacter::initialize();

        mPlayerCharacterData = pData;

        //TODO:
        {
            setSCDManager(CD_MASTER_TYPE_CHARACTER, this);

            //设置基本数据
            *getPlayerCharacterData() = pData;
            //设置模版信息
            setCharacterTempInfo();
            //计算属性
            calAttr();
        }


        SCharacter::initialize();

		return true;
    }

    //-----------------------------------------------------------------------------
    Bool SPlayerCharacter::unInitialize()
    {
        SCharacter::unInitialize();

        return true;
    }

    //-----------------------------------------------------------------------------
    void SPlayerCharacter::clear()
    {
        SCharacter::clear();

        mSPlayerPtr.setNull();
        mSPlayerIdentifyInfo.clear();
        setIsBattleLeader(false);
    }

    //-----------------------------------------------------------------------------
    void SPlayerCharacter::update(Flt delta)
    {
        SCharacter::update( delta );

        
    }

    //-----------------------------------------------------------------------------
    void SPlayerCharacter::print()
    {
        //SCharacter::print();
        //MG_LOG(out_sys, "【SPlayerCharacterNew】 暂空\n");

        
        return;
    }

    //-----------------------------------------------------------------------------------
    // Base Data
    //-----------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	PlayerCharacterData* SPlayerCharacter::getPlayerCharacterData()
	{
		return &mPlayerCharacterData;
	}

    //-----------------------------------------------------------------------------
    void SPlayerCharacter::getPlayer( SPlayerPtr& ptr )
    {
        ptr = mSPlayerPtr;
    }

    //-----------------------------------------------------------------------------
    void SPlayerCharacter::setPlayer( SPlayerPtr& ptr )
    {
        mSPlayerPtr = ptr;

        if ( mSPlayerPtr.isNull() == false )
        {
			mSPlayerIdentifyInfo.accountId					= ptr->getIdentifyInfo()->accountId;
			mSPlayerIdentifyInfo.frontServerId				= ptr->getIdentifyInfo()->frontServerId;
			mSPlayerIdentifyInfo.clientNetIdInFrontServer	= ptr->getIdentifyInfo()->clientNetIdInFrontServer;
			mSPlayerIdentifyInfo.clanId						= ptr->getIdentifyInfo()->clanId;
        }else
        {
            mSPlayerIdentifyInfo.clear();
        }
    }

    //-----------------------------------------------------------------------------
    SPlayerIdentifyInfo* SPlayerCharacter::getPlayerIdentifyInfo()
    {
        return &mSPlayerIdentifyInfo;
    }


    //-----------------------------------------------------------------------------------
    // Equip
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------------------
    // Alive
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------
    void SPlayerCharacter::dead(SCharacter* murderer)
    {
        SCharacter::dead(murderer);

        SRegionObjectBase* regionObj = NULL;//getCurrentRegionObject();
        if(NULL == regionObj)
        {
            return;
        }

        const InstanceType instanceType = InstanceType_Null;//regionObj->getInstanceType();
        if (instanceType == InstanceType_HomeLand	|| 
            instanceType == InstanceType_Tiro		|| 
            instanceType == InstanceType_PVP		|| 
            instanceType == InstanceType_PVE)
        {
            //RPG模式
            setAliveTime(30);
        }
        else if(instanceType == InstanceType_Atk)
        {
            //SLG模式
            setAliveTime(30);
        }
        else
        {
            DYNAMIC_ASSERT(0)
        }
    }
    //-----------------------------------------------------------------------
    void SPlayerCharacter::setAlive(AliveType aliveType)
    {

        //移动到复活点
        if (AliveType_TimeOut == aliveType ||
            AliveType_User_AlivePos == aliveType)
        {
            //SRegionObjectBase* regionObj = getCurrentRegionObject();
            //PointXml alivePoint = regionObj->getSceneFileObject()->getRandAlivePoint();
            //setAlivePos(alivePoint.pos);
            //setPos(alivePoint.pos);
        }
        else if(AliveType_User_CurPos == aliveType)
        {
            setAlivePos(getPos());
        }
        else
        {
            DYNAMIC_ASSERT(0);
        }

        //设置复活时间
        SCharacter::setAlive(aliveType);
        //初始化属性
        setMax_HpSpMp();

        //发送列表
        SRegionNetPacketProcesser::getInstance().sendPlayerCharacterAliveToFrontServer(this);
        //SRegionNetPacketProcesser::getInstance().broadcastPlayerCharacterAliveToRegion(this, getCurrentRegionObject());
    }



    //-----------------------------------------------------------------------------------
    // Attr
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------
    MG::UInt SPlayerCharacter::getLineageNum()
    {
        return getPlayerCharacterData()->mLineageNum;
    }
    //-----------------------------------------------------------------------
    MG::Flt SPlayerCharacter::getDBAttrLvlAdd( UInt index )
    {
        return getPlayerCharacterData()->charAttrRandAdd[index];	
    }
    //-----------------------------------------------------------------------
    MG::Flt SPlayerCharacter::getDBAttrInit( UInt index )
    {
        return getPlayerCharacterData()->charAttrRand[index];
    }

    //-----------------------------------------------------------------------
    MG::UInt SPlayerCharacter::getDBAttrInitID()
    {
        return getPlayerCharacterData()->charAttrAppendId;
    }
    //-----------------------------------------------------------------------
    MG::UInt SPlayerCharacter::getDBAttrLvlAddID()
    {
        return getPlayerCharacterData()->charAttrAppendLvlAddId;
    }
    //-----------------------------------------------------------------------
    void SPlayerCharacter::calAttrOther()
    {
        //计算装备。
        mEquipItem.calAttrAllBase(this);
        //计算技能。
        getSkillOwnManager()->calAttrAllBase();
        //计算状态。
        getSBuffManager()->calAttrAllBase();
    }


    //-----------------------------------------------------------------------------------
    // Battle
    //-----------------------------------------------------------------------------------


	//-----------------------------------------------------------------------
	Bool SPlayerCharacter::getIsBattleLeader() const
	{
		return mIsBattleLeader;
	}

	//-----------------------------------------------------------------------
	void SPlayerCharacter::setIsBattleLeader(Bool isBattleLeader)
	{
		mIsBattleLeader = isBattleLeader;
	}

    //-----------------------------------------------------------------------------------
    // Move
    //-----------------------------------------------------------------------------------


	//-----------------------------------------------------------------------
	void SPlayerCharacter::moveToPos( Vec3 startMovePos, Vec3 MoveToPos, Bool isBlockCheck )
	{
		NetVec2 startMovePosdata;
		startMovePosdata = startMovePos;

		NetVec2 endMovePosdata;
		endMovePosdata = MoveToPos;

		SPlayerCharacterNetPacketProcesser::getInstance().broadcastPlayerCharacterMove(this, (NetVec2)startMovePosdata, (NetVec2)endMovePosdata, isBlockCheck);

		SCharacter::moveToPos(startMovePos, MoveToPos);
	}

	//-----------------------------------------------------------------------
	void SPlayerCharacter::stopMove()
	{
		LinedStateObject* linedStateObject = mActionManager->getState("SCharacterMoveToAction", false);

		if(linedStateObject)
		{
			SPlayerCharacterNetPacketProcesser::getInstance().broadcastPlayerCharacterStopMove(this);
		}

		SCharacter::stopMove();
	}


}