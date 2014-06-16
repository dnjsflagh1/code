/******************************************************************************/
#include "stdafx.h"
#include "Scene.h"
#include "CompositorManager.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    CompositorManager::CompositorManager( Scene* scene )
        :mScene(scene)
    {
    }

    //-----------------------------------------------------------------------
    CompositorManager::~CompositorManager()
    {

    }

    //-----------------------------------------------------------------------
    void CompositorManager::update( Flt delta )
    {
        
    }

    //-----------------------------------------------------------------------
    void CompositorManager::addCompositor(Str name, Int addPosition)
    {
        Viewport* viewPort = mScene->getMainViewport();

        if ( viewPort )
        {
            std::map<Str, CompositorInstance*>::iterator iter = mCompositorList.find( name );

            if ( iter == mCompositorList.end() )
            {
                CompositorInstance* instance = Ogre::CompositorManager::getSingleton().addCompositor(viewPort, name, addPosition);
                if ( instance )
                    mCompositorList[ name ] = instance;
            }
        }
    }

    //-----------------------------------------------------------------------
    Bool CompositorManager::hasCompositor(Str name)
    {
        std::map<Str, CompositorInstance*>::iterator iter = mCompositorList.find( name );

        if ( iter != mCompositorList.end() )
        {
            return true;
        }

        return false;
    }

    //-----------------------------------------------------------------------
    void CompositorManager::setCompositorEnable(Str name, Bool enable)
    {
        Viewport* viewPort = mScene->getMainViewport();

        if ( viewPort )
        {
            if ( enable == true )
            {
                addCompositor( name );
            }else
            {
                if ( hasCompositor( name ) == false )
                    return;
            }
   
            Ogre::CompositorManager::getSingleton().setCompositorEnabled( viewPort, name, enable );
        }
    }

    //-----------------------------------------------------------------------
    void CompositorManager::setCompositorEnable(Bool enable)
    {
        Viewport* viewPort = mScene->getMainViewport();

        if ( viewPort )
        {
            std::map<Str, CompositorInstance*>::iterator iter = mCompositorList.begin();
            for ( ; iter != mCompositorList.end(); iter++ )
            {
                Ogre::CompositorManager::getSingleton().setCompositorEnabled( viewPort, iter->first, enable );
            }
        }
    }

}