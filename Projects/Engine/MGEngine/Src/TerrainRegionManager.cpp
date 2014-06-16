/******************************************************************************/
#include "stdafx.h"
#include "TerrainChunk.h"
#include "TerrainManager.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainRegionManager.h"
#include "ResourceManager.h"
#include "Display.h"

/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    TerrainRegionManager::TerrainRegionManager(TerrainManager* mgr,Scene* scene)
        :mOwner(mgr)
        ,mScene(scene)
        ,mBlockRegionVisible(false)
    {
        
    }

    //-----------------------------------------------------------------------
    TerrainRegionManager::~TerrainRegionManager()
    {
        
    }

    //-----------------------------------------------------------------------
    void TerrainRegionManager::clear()
    {
        clearCustomRegion();
        mTerrainChunkRegionsList.clear();
    }
    
    //-----------------------------------------------------------------------
    TerrainChunkRegions* TerrainRegionManager::createTerrainChunkRegions(TerrainChunk* chunk)
    {
        TerrainChunkRegions* regions = MG_NEW TerrainChunkRegions( mOwner, mScene, chunk );
        mTerrainChunkRegionsList.push_back( regions );
        return regions;
    }
    
    //-----------------------------------------------------------------------
    void TerrainRegionManager::destroyTerrainChunkRegions(TerrainChunkRegions* regions)
    {
        std::list<TerrainChunkRegions*>::iterator iter = mTerrainChunkRegionsList.begin();
        for ( ; iter != mTerrainChunkRegionsList.end(); iter++ )
        {
            if ( *iter == regions )
            {
                mTerrainChunkRegionsList.erase( iter );
                break;
            }
        }

        MG_SAFE_DELETE( regions );
    }

    //-----------------------------------------------------------------------
    void TerrainRegionManager::setBlockRegionVisible(Bool visible)
    {
        mBlockRegionVisible = visible;
    }

    //-----------------------------------------------------------------------
    Bool TerrainRegionManager::getBlockRegionVisible()
    {
        return mBlockRegionVisible;
    }

    //-----------------------------------------------------------------------
    void TerrainRegionManager::setCustomRegionVisible( Int index, Bool visible )
    {
        CustomRegionDeclaration* decl = getCustomRegionDeclaration(index);
        if (decl)
        {
            decl->visible = visible;
        }
    }

    //-----------------------------------------------------------------------
    Int TerrainRegionManager::getVisibledCustomRegionIndex()
    {
        for ( UInt i=0; i<mTerrainCustomRegionsDecl.size(); i++ )
        {
            if ( mTerrainCustomRegionsDecl[i].visible )
                return i;
        }
        return -1;
    }

    //-----------------------------------------------------------------------
    CustomRegionDeclaration* TerrainRegionManager::getVisibledCustomRegion()
    {
        for ( UInt i=0; i<mTerrainCustomRegionsDecl.size(); i++ )
        {
            if ( mTerrainCustomRegionsDecl[i].visible )
                return &(mTerrainCustomRegionsDecl[i]);
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    void TerrainRegionManager::clearCustomRegion()
    {
        std::list<TerrainChunkRegions*>::iterator iter = mTerrainChunkRegionsList.begin();
        for ( ; iter != mTerrainChunkRegionsList.end(); iter++ )
        {
            ( *iter )->clearCustomRegion();
        }
        mTerrainCustomRegionsDecl.clear();
    }
    
    //-----------------------------------------------------------------------
    void TerrainRegionManager::addCustomRegion()
    {
        if ( mTerrainCustomRegionsDecl.size() >=6 )
            return;

        CustomRegionDeclaration decl;
        decl.name      = "";
        decl.visible   = false;

        mTerrainCustomRegionsDecl.push_back( decl );

        //////////////////////////////////////////////////////////////////////////////

        std::list<TerrainChunkRegions*>::iterator iter = mTerrainChunkRegionsList.begin();
        for ( ; iter != mTerrainChunkRegionsList.end(); iter++ )
        {
            ( *iter )->addCustomRegion();
        }
    }

    //-----------------------------------------------------------------------
    void TerrainRegionManager::removeCustomRegion( Int index )
    {
        //////////////////////////////////////////////////////////////////////////////

        {
            std::list<TerrainChunkRegions*>::iterator iter = mTerrainChunkRegionsList.begin();
            for ( ; iter != mTerrainChunkRegionsList.end(); iter++ )
            {
                ( *iter )->removeCustomRegion( index );
            }
        }


        //////////////////////////////////////////////////////////////////////////////
        {
            std::vector<CustomRegionDeclaration>::iterator iter = mTerrainCustomRegionsDecl.begin();
            for ( UInt i=0; iter<mTerrainCustomRegionsDecl.end(); iter++,i++ )
            {
                if (i==index)
                {
                    mTerrainCustomRegionsDecl.erase( iter );
                    break;
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    Int TerrainRegionManager::getCustomRegionCount()
    {
        return mTerrainCustomRegionsDecl.size();
    }

    //-----------------------------------------------------------------------
    CustomRegionDeclaration* TerrainRegionManager::getCustomRegionDeclaration( UInt index )
    {
        if ( index <  mTerrainCustomRegionsDecl.size() )
        {
            return &(mTerrainCustomRegionsDecl[index]);
        }

        return NULL;
    }

    //-----------------------------------------------------------------------
    void TerrainRegionManager::applyRegionVisible()
    {
        std::list<TerrainChunkRegions*>::iterator iter = mTerrainChunkRegionsList.begin();
        for ( ; iter != mTerrainChunkRegionsList.end(); iter++ )
        {
            ( *iter )->applyRegionVisible();
        }
    }


}