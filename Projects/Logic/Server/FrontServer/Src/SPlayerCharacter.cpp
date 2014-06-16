/******************************************************************************/
#include "stdafx.h"
#include "SPlayerCharacter.h"
#include "SClan.h"
#include "SPlayer.h"
#include "FrontServerMain.h"
#include "PlayerCharacterDB.h"
#include "PlayerCharacterNetPacketProcesser.h"
#include "CharacterList.h"
#include "SAttributeNetPacketProcesser.h"
#include "SSkillUseManager.h"
#include "SSkillOwnManager.h"
#include "CalendarInfo.h"
#include "AttributeFormula.h"
#include "PlayerNetPacketProcesser.h"
#include "SPlayer.h"
#include "SWorldManager.h"
#include "ItemPacketProcesser.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------
    SPlayerCharacter::SPlayerCharacter()
        :SCharacter(GOT_PLAYERCHARACTER, &mPlayerCharacterData)
    { 
    }
    //-----------------------------------------------------------------------
    SPlayerCharacter::~SPlayerCharacter()
    {
    }

    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------
    Bool SPlayerCharacter::initialize( PlayerCharacterData& charData )
    {
        SCharacter::initialize();

        mPlayerCharacterData = charData;

        //TODO:

        setCharacterTempInfo();

        calAttr(true);

        setBaseAttr();
      
        getSkillOwnManager()->getDefultSkill();
		return true;
    }

    //-----------------------------------------------------------------------
    Bool SPlayerCharacter::unInitialize()
    {
        SCharacter::unInitialize();
		return true;
    }

    //-----------------------------------------------------------------------
    void SPlayerCharacter::update(Flt delta)
    {
        SCharacter::update( delta );

        if(NULL != mSkillUseManager)
        {
            mSkillUseManager->update(0);
        }

    }

    //-----------------------------------------------------------------------
    void SPlayerCharacter::clear()
    {
        SCharacter::clear();
		mMapServerNetId = -1;
		mLastMapServerNetId = -1;
    }


    //-----------------------------------------------------------------------------------
    // Debug
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------
    void SPlayerCharacter::print()
    {
        //SCharacter::print();

        //MG_LOG(out_sys, "¡¾SPlayerCharacter¡¿¿Õ\n");
        return;
    }

    //-----------------------------------------------------------------------------------
    // Server Info
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------
    void SPlayerCharacter::setMapServerNetId(NetIdType mapServerNetId)
    {
        mLastMapServerNetId = mMapServerNetId;
        mMapServerNetId = mapServerNetId;
    }
    //-----------------------------------------------------------------------
    NetIdType SPlayerCharacter::getMapServerNetId() const
    {
        return mMapServerNetId;
    }

    //-----------------------------------------------------------------------
    NetIdType SPlayerCharacter::getLastMapServerNetId() const
    {
        return mLastMapServerNetId;
    }

    //-----------------------------------------------------------------------------------
    // Base Info
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------
    PlayerCharacterData* SPlayerCharacter::getData()
    {
        return &mPlayerCharacterData;
    }

    //-----------------------------------------------------------------------------------
    // Alive
    //-----------------------------------------------------------------------------------


    //-----------------------------------------------------------------------
	void SPlayerCharacter::setAlive()
	{
		setMax_HpSpMp();

		//¸üÐÂDB¡£
		PlayerCharacterDBOp::updatePlayerCharacterInfo( *FrontServerMain::getInstance().getDBDriver(), getData() );
	}


	void SPlayerCharacter::setParentClan(SClan* parentClan)
	{
		mParentClan = parentClan;
	}
    //-----------------------------------------------------------------------------------
    // Attr
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------
    void SPlayerCharacter::setDBAttrInit( UInt index, Flt value )
    {
        getData()->charAttrRand[index] = value;
    }

    //-----------------------------------------------------------------------
    MG::Flt SPlayerCharacter::getDBAttrInit( UInt index )
    {
        return getData()->charAttrRand[index];
    }

    //-----------------------------------------------------------------------
    void SPlayerCharacter::setDBAttrLvlAdd( UInt index, Flt value )
    {
        getData()->charAttrRandAdd[index] = value;
    }

    //-----------------------------------------------------------------------
    MG::Flt SPlayerCharacter::getDBAttrLvlAdd( UInt index )
    {
        return getData()->charAttrRandAdd[index];
    }

    //-----------------------------------------------------------------------
    void SPlayerCharacter::setBaseAttr()
    {
		setMax_HpSpMp();
    }

	//-----------------------------------------------------------------------
	MG::UInt SPlayerCharacter::getDBAttrInitID()
	{
		return getData()->charAttrAppendId;
	}

	//-----------------------------------------------------------------------
	MG::UInt SPlayerCharacter::getDBAttrLvlAddID()
	{
		return getData()->charAttrAppendLvlAddId;
	}

	//-----------------------------------------------------------------------
	void SPlayerCharacter::setDBAttrInitID( UInt id )
	{
		getData()->charAttrAppendId = id;
	}

	//-----------------------------------------------------------------------
	void SPlayerCharacter::setDBAttrLvlAddID( UInt id )
	{
		getData()->charAttrAppendLvlAddId = id;
	}

	//-----------------------------------------------------------------------
	MG::U32 SPlayerCharacter::setGenrealAge( const CalendarInfo* pCalendarInfo, U32 age )
	{
		return AttributeFormula::getInstance().calValueCharacterAge(
			age,
			pCalendarInfo->year,
			pCalendarInfo->day
			);
	}
	
	//-----------------------------------------------------------------------

	void SPlayerCharacterPtr::destroy(void)
	{
		mFactory->destroySPlayerCharacterPtr( *this );
	}
}