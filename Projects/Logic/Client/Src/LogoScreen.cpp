/******************************************************************************/
#include "stdafx.h"
#include "LogoScreen.h"
#include "ClientMain.h"
#include "GameMain.h"

/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------------
    Str LogoScreen::STATE_NAME = "LogoScreen";
    //-----------------------------------------------------------------------------
    LogoScreen::LogoScreen()
        :IScreen( STATE_NAME )
    {
        setManagedLifeTime( false );
    }

    //-----------------------------------------------------------------------------
    LogoScreen::~LogoScreen()
    {
        
    }

    //-----------------------------------------------------------------------------
    void LogoScreen::update( Flt delta )
    {

    }

    //-----------------------------------------------------------------------------
    Bool LogoScreen::isFinished()
    {

        return true;
    }

    //-----------------------------------------------------------------------------
    void LogoScreen::onEnter()
    {

    }

    //-----------------------------------------------------------------------------
    void LogoScreen::onLeave()
    {
        GameMain::getInstance().enterLoginScreen();
    }

    //-----------------------------------------------------------------------------
    void LogoScreen::loadVideo()
    {

    }

    //-----------------------------------------------------------------------------
    void LogoScreen::deleteVideo()
    {

    }
    
    //-----------------------------------------------------------------------------
    void LogoScreen::onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {

    }

    //-----------------------------------------------------------------------------
    void LogoScreen::onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {

    }

    //-----------------------------------------------------------------------------
    void LogoScreen::onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {

    }


}


