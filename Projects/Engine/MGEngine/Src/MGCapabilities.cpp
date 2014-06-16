/******************************************************************************/
#include "stdafx.h"
#include "MGCapabilities.h"
#include "EngineMain.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    MGCapabilities::MGCapabilities()
    {
    }
    //-----------------------------------------------------------------------
    MGCapabilities::~MGCapabilities()
    {

    }
    //-----------------------------------------------------------------------
    Bool MGCapabilities::check()
    {
        const Ogre::RenderSystemCapabilities* caps = OgreMainInterface::root->getRenderSystem()->getCapabilities();

        if (!caps->hasCapability(Ogre::RSC_VERTEX_PROGRAM) || !caps->hasCapability(Ogre::RSC_FRAGMENT_PROGRAM))
        {
            MG_MESSAGE( "Your graphics card does not support vertex or fragment shaders");
        }
        
        return true;
    }

}

