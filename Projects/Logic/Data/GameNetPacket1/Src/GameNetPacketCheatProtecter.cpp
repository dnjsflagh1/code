/******************************************************************************/
#include "stdafx.h"
#include "GameNetPacketFilter.h"
#include "GameNetPacketCheatProtecter.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------------
    GameNetPacketCheatProtecter::GameNetPacketCheatProtecter()
    {
    }

    //-----------------------------------------------------------------------------
    GameNetPacketCheatProtecter::~GameNetPacketCheatProtecter()
    {
    }

    //-----------------------------------------------------------------------------
    Bool GameNetPacketCheatProtecter::initialize()
    {

        return true;
    }

    //-----------------------------------------------------------------------------
    Bool GameNetPacketCheatProtecter::update()
    {

        return false;
    }

    //-----------------------------------------------------------------------------
    Bool GameNetPacketCheatProtecter::unInitialize()
    {

        return false;
    }


}


