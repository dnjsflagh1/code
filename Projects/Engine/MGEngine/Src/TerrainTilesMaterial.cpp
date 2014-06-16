/******************************************************************************/
#include "stdafx.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainTilesGpu.h"
#include "TerrainTiles.h"
#include "TerrainTilesMaterial.h"
#include "TerrainTilesOptions.h"

#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "OgreSceneManagerEnumerator.h"
#include "OgreTextureManager.h"
#include "OgreTexture.h"
#include "OgreManualObject.h"
#include "OgreCamera.h"
#include "OgreViewport.h"
#include "OgreRenderTexture.h"
#include "OgreHardwarePixelBuffer.h"
#include "OgreRenderSystem.h"

/******************************************************************************/

#if OGRE_COMPILER == OGRE_COMPILER_MSVC
// we do lots of conversions here, casting them all is tedious & cluttered, we know what we're doing
#   pragma warning (disable : 4244)
#endif

namespace MG
{
    //---------------------------------------------------------------------
    TerrainMaterialGenerator::TerrainMaterialGenerator() 
        : mActiveProfile(0)
        , mChangeCounter(0)
        , mDebugLevel(0) 
    {

    }
    //---------------------------------------------------------------------
    TerrainMaterialGenerator::~TerrainMaterialGenerator()
    {
        for (ProfileList::iterator i = mProfiles.begin(); i != mProfiles.end(); ++i)
            OGRE_DELETE *i;
    }

}