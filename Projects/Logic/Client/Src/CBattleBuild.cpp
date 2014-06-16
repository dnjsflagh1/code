/******************************************************************************/
#include "stdafx.h"
#include "CBattleBuild.h"
#include "AttributeSet.h"
#include "BuildingData.h"
/******************************************************************************/
namespace MG
{
    CBattleBuild::CBattleBuild()
        :CCharacter(GOT_BUILDING, MG_NEW BuildingData())
    {
    }
    //-------------------------------------------------------------------
    CBattleBuild::~CBattleBuild()
    {
      
    }
    //-------------------------------------------------------------------
    BuildingData* CBattleBuild::getData()
    {
        return (BuildingData*)GameObject::getGameObjectData();
    }
    //-------------------------------------------------------------------
    void CBattleBuild::init( BuildingData* pData )
    {
        *getData() = *pData;

        setCharacterTempInfo();

        calAttr();

		//设置最大血量和魔量
    }
    //-------------------------------------------------------------------
    void CBattleBuild::calOtherAttr( )
    {

    }
    //-------------------------------------------------------------------
    MG::UInt CBattleBuild::getHp()
    {
		return 0;
    }
    //-------------------------------------------------------------------
    MG::UInt CBattleBuild::getMp()
    {
		return 0;
    }
    //-------------------------------------------------------------------
    void CBattleBuild::setHp( UInt val )
    {
        
    }
    //-------------------------------------------------------------------
    void CBattleBuild::setMp( UInt val )
    {
        
    }
}