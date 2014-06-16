/******************************************************************************/
#include "stdafx.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainTilesOptions.h"
#include "TerrainTiles.h"
#include "ShadowManager.h"
#include "TerrainTilesMaterialA.h"
#include "TerrainTilesMaterialA2.h"
#include "TerrainTilesMaterialB.h"
#include "Display.h"
/******************************************************************************/

namespace MG
{

    //---------------------------------------------------------------------
    TerrainTilesGlobalOptions::TerrainTilesGlobalOptions()
        : mRenderQueueGroup(RENDER_QUEUE_MAIN)
        , mVisibilityFlags(0xFFFFFFFF)
        , mQueryFlags(0xFFFFFFFF)
        , mResourceGroup(ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME)
    {
    }
    //---------------------------------------------------------------------
    TerrainMaterialGeneratorPtr TerrainTilesGlobalOptions::getDefaultMaterialGenerator( TerrainGroundMaterialType matType )
    {
        ShadowType st = Display::getSingleton().getShadowType();

        // default
        if ( matType == TMS_SMALL )
        {
            if (mDefaultMaterialBGenerator.isNull())
            {
                mDefaultMaterialBGenerator.bind(MG_NEW TerrainMaterialGeneratorB());
            }
            return mDefaultMaterialBGenerator;
        }else
        {
            if ( ShadowManager::isUsePSSM() )
            {
                if (mDefaultMaterialAGenerator.isNull())
                {
                    mDefaultMaterialAGenerator.bind(MG_NEW TerrainMaterialGeneratorA());
                }
                return mDefaultMaterialAGenerator;
            }else
            {
                if (mDefaultMaterialA2Generator.isNull())
                {
                    mDefaultMaterialA2Generator.bind(MG_NEW TerrainMaterialGeneratorA2());
                }
                return mDefaultMaterialA2Generator;
            }
        }

        return mDefaultMaterialAGenerator;
    }
    

}