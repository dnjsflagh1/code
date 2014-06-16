/******************************************************************************/
#ifndef _TERRAINTILESOPTIONS_H_
#define _TERRAINTILESOPTIONS_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "TerrainTilesMaterialA.h"
/******************************************************************************/
namespace MG
{

    /** Options class which just stores default options for the terrain.
    @remarks
    None of these options are stored with the terrain when saved. They are
    options that you can use to modify the behaviour of the terrain when it
    is loaded or created. 
    @note
    You should construct a single instance of this class per application and
    do so before you start working with any other terrain classes.
    */
    class TerrainTilesGlobalOptions : public GeneralAllocatedObject
    {
    protected:
        uint8   mRenderQueueGroup;
        uint32  mVisibilityFlags;
        uint32  mQueryFlags;
        TerrainMaterialGeneratorPtr mDefaultMaterialAGenerator;
        TerrainMaterialGeneratorPtr mDefaultMaterialA2Generator;
        TerrainMaterialGeneratorPtr mDefaultMaterialBGenerator;

        String  mResourceGroup;

    public:
        SINGLETON_INSTANCE(TerrainTilesGlobalOptions)
        TerrainTilesGlobalOptions();
        virtual ~TerrainTilesGlobalOptions() {}

        /// Get the render queue group that this terrain will be rendered into
        uint8 getRenderQueueGroup(void) { return mRenderQueueGroup; }
        /** Set the render queue group that terrains will be rendered into.
        @remarks This applies to newly created terrains, after which they will
        maintain their own queue group settings
        */
        void setRenderQueueGroup(uint8 grp) { mRenderQueueGroup = grp; }

        /// Get the visbility flags that terrains will be rendered with
        uint32 getVisibilityFlags(void) { return mVisibilityFlags; }
        /** Set the visbility flags that terrains will be rendered with
        @remarks This applies to newly created terrains, after which they will
        maintain their own settings
        */
        void setVisibilityFlags(uint32 flags) { mVisibilityFlags = flags; }

        /** Set the default query flags for terrains.
        @remarks This applies to newly created terrains, after which they will
        maintain their own settings
        */
        void  setQueryFlags(uint32 flags) { mQueryFlags = flags; }
        /** Get the default query flags for terrains.
        */
        uint32 getQueryFlags(void) { return mQueryFlags; }

        /** As setQueryFlags, except the flags passed as parameters are appended to the existing flags on this object. */
        void addQueryFlags(uint32 flags) { mQueryFlags |= flags; }

        /* As setQueryFlags, except the flags passed as parameters are removed from the existing flags on this object. */
        void removeQueryFlags(uint32 flags) { mQueryFlags &= ~flags; }

        /** Get the default material generator.
        */
        TerrainMaterialGeneratorPtr getDefaultMaterialGenerator( TerrainGroundMaterialType matType );

        /** Set the default resource group to use to load / save terrains.
        */
        void setDefaultResourceGroup(const String& grp) { mResourceGroup = grp; }

        /** Get the default resource group to use to load / save terrains.
        */
        const String& getDefaultResourceGroup() { return mResourceGroup; }

    };

}

/******************************************************************************/

#endif
