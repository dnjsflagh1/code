/******************************************************************************/
#include "stdafx.h"
#include "Application.h"
#include "EngineMain.h"
#include "Display.h"
/******************************************************************************/

namespace MG
{

    SINGLETON_DEFINE( Application )
    //-----------------------------------------------------------------------
    Application::Application()
    {
        
    }
    //-----------------------------------------------------------------------
    Application::~Application()
    {
        
    }
    //-----------------------------------------------------------------------
    void Application::createWindow( CChar* name, Int width, Int height, Bool fullScreen, HWND handle )
    {
        mWindowName = name;
        Ogre::Root *root = Ogre::Root::getSingletonPtr();
        if ( !root )
            return;

        if( handle ) {
			OgreMainInterface::renderWindow = root->initialise(false);
			Ogre::NameValuePairList miscParams;
			miscParams["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)handle);
			miscParams["FSAA"] = Ogre::StringConverter::toString(Display::getSingleton().getFSAA());
			miscParams["FSAAHint"] = Display::getSingleton().getFSAAHint();
			OgreMainInterface::renderWindow = root->createRenderWindow( mWindowName, width, height, fullScreen, &miscParams );
			OgreMainInterface::renderWindow->setDeactivateOnFocusChange(false);
            Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		} else {
			OgreMainInterface::renderWindow = root->initialise(true, mWindowName);
			OgreMainInterface::renderWindow->setDeactivateOnFocusChange(false);
		}
    }
	//-----------------------------------------------------------------------
	U32 Application::getWindowHandle()
	{
		U32 windowHnd = 0;

		if ( OgreMainInterface::renderWindow )
		{	
			OgreMainInterface::renderWindow->getCustomAttribute( "WINDOW", &windowHnd );
		}

		return windowHnd;
	}
}

