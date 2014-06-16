/******************************************************************************/
#ifndef _TERRAINTILESLAYERBLENDMAP_H_
#define _TERRAINTILESLAYERBLENDMAP_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "OgreCommon.h"
#include "OgreVector3.h"
#include "OgreDataStream.h"

/******************************************************************************/

namespace MG
{
    class Ogre::Image;
    /** \addtogroup Optional Components
    *  @{
    */
    /** \addtogroup Terrain
    *  Some details on the terrain component
    *  @{
    */


    /** Class exposing an interface to a blend map for a given layer. 
    Each layer after the first layer in a terrain has a blend map which 
    expresses how it is alpha blended with the layers beneath. Internally, this
    blend map is packed into one channel of an RGB or RGBA texture in
    order to use the smallest number of samplers, but this class allows
    a caller to manipulate the data more easily without worrying about
    this packing. Also, the values you use to interact with the blend map are
    floating point, which gives you full precision for updating, but in fact the
    values are packed into 8-bit integers in the actual blend map.
    @par
    You shouldn't construct this class directly, use Terrain::getLayerBlendMap().
    */
    class TerrainLayerBlendMap : public GeneralAllocatedObject
    {
    protected:
        TerrainTileRender* mParent;
        uint8 mLayerIdx;
        uint8 mChannel; // RGBA
        uint8 mChannelOffset; // in pixel format
        Box mDirtyBox;
        bool mDirty;
        HardwarePixelBuffer* mBuffer;
        float* mData;

        void download();
        void upload();

    public:
        /** Constructor
        @param parent The parent terrain
        @param layerIndex The layer index (should be 1 or higher)
        @param box The region of the blend map to address (in image space)
        @param buf The buffer holding the data
        */
        TerrainLayerBlendMap(TerrainTileRender* parent, uint8 layerIndex, HardwarePixelBuffer* buf);
        ~TerrainLayerBlendMap();
        /// Get the parent terrain
        TerrainTileRender* getParent() const { return mParent; }
        /// Get the index of the layer this is targetting
        uint8 getLayerIndex() const { return mLayerIdx; }


        /** Convert local space values (0,1) to image space (0, imageSize).
        */
        void convertUVToImageSpace(Real x, Real y, size_t* outX, size_t* outY);
        /** Convert image space (0, imageSize) to local space values (0,1).
        */
        void convertImageToUVSpace(size_t x, size_t y, Real* outX, Real* outY);
        /** Convert image space (0, imageSize) to terrain space values (0,1).
        */
        void convertImageToTerrainSpace(size_t x, size_t y, Real* outX, Real* outY);
        /** Convert terrain space values (0,1) to image space (0, imageSize).
        */
        void convertTerrainToImageSpace(Real x, Real y, size_t* outX, size_t* outY);

        /** Get a single value of blend information, in image space.
        @param x,y Coordinates of the point of data to get, in image space (top down)
        @returns The blend data
        */
        float getBlendValue(size_t x, size_t y);

        /** Set a single value of blend information (0 = transparent, 255 = solid)
        @param x,y Coordinates of the point of data to get, in image space (top down)
        @param val The blend value to set (0..1)
        */
        void setBlendValue(size_t x, size_t y, float val);

        /** Get a pointer to the whole blend data. 
        @remarks
        This method allows you to get a raw pointer to all the blend data, to 
        update it as you like. However, you must then call dirtyRect manually 
        if you want those changes to be recognised. 
        */
        float* getBlendPointer();

        /** Indicate that all of the blend data is dirty and needs updating.
        */
        void dirty();

        /** Indicate that a portion of the blend data is dirty and needs updating.
        @param rect Rectangle in image space
        */
        void dirtyRect(const Rect& rect);

        /** Blits a set of values into a region on the blend map. 
        @param src		PixelBox containing the source pixels and format 
        @param dstBox	Image::Box describing the destination region in this map
        @remarks The source and destination regions dimensions don't have to match, in which
        case scaling is done. 
        @note You can call this method in a background thread if you want.
        You still need to call update() to commit the changes to the GPU. 
        */
        void blit(const PixelBox &src, const Box &dstBox);

        /** Blits a set of values into the entire map. The source data is scaled if needed.
        @param src		PixelBox containing the source pixels and format
        @note You can call this method in a background thread if you want.
        You still need to call update() to commit the changes to the GPU. 

        */
        void blit(const PixelBox &src);

        /** Load an image into this blend layer. 
        */
        void loadImage(const Image& img);

        /** Load an image into this blend layer. 
        @param stream Stream containing the image data
        @param ext Extension identifying the image type, if the stream data doesn't identify
        */
        void loadImage(DataStreamPtr& stream, const String& ext = StringUtil::BLANK);

        /** Load an image into this blend layer. 
        */
        void loadImage(const String& filename, const String& groupName);

        /** Publish any changes you made to the blend data back to the blend map. 
        @note
        Can only be called in the main render thread.
        */
        void update();


    };
    
    typedef Ogre::vector<TerrainLayerBlendMap*>::type TerrainLayerBlendMapList;
    
    /** @} */
    /** @} */ 

}

/******************************************************************************/

#endif
