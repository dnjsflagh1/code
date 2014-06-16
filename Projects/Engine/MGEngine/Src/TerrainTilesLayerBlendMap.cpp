/******************************************************************************/
#include "stdafx.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainTilesGpu.h"
#include "TerrainTiles.h"
#include "TerrainTilesLayerBlendMap.h"

#include "OgreImage.h"
#include "OgreHardwarePixelBuffer.h"
/******************************************************************************/

namespace MG
{
    //---------------------------------------------------------------------
    TerrainLayerBlendMap::TerrainLayerBlendMap(TerrainTileRender* parent, uint8 layerIndex, 
        HardwarePixelBuffer* buf)
        : mParent(parent)
        , mLayerIdx(layerIndex)
        , mChannel((layerIndex-1) % 4)
        , mDirty(false)
        , mBuffer(buf)
        , mData(0)
    {
        mData = static_cast<float*>(OGRE_MALLOC(mBuffer->getWidth() * mBuffer->getHeight() * sizeof(float), MEMCATEGORY_RESOURCE));
        DYNAMIC_ASSERT_LOG( mData!=NULL, "TerrainLayerBlendMap mData failed" );

        // we know which of RGBA we need to look at, now find it in the format
        // because we can't guarantee what precise format the RS gives us
        unsigned char rgbaShift[4];
        PixelFormat fmt = mBuffer->getFormat();
        PixelUtil::getBitShifts(fmt, rgbaShift);
        mChannelOffset = rgbaShift[mChannel] / 8; // /8 to convert to bytes
       // mChannelOffset = mChannel; // /8 to convert to bytes
#if OGRE_ENDIAN == OGRE_ENDIAN_BIG
        // invert (dealing bytewise)
        mChannelOffset = PixelUtil::getNumElemBytes(fmt) - mChannelOffset - 1;
#endif
        download();

    }
    //---------------------------------------------------------------------
    TerrainLayerBlendMap::~TerrainLayerBlendMap()
    {
        OGRE_FREE(mData, MEMCATEGORY_RESOURCE);
        mData = 0;
    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::download()
    {
        float* pDst = mData;
        // Download data
        Image::Box box(0, 0, mBuffer->getWidth(), mBuffer->getHeight());
        uint8* pSrc = static_cast<uint8*>(mBuffer->lock(box, HardwareBuffer::HBL_READ_ONLY).data);
        pSrc += mChannelOffset;
        size_t srcInc = PixelUtil::getNumElemBytes(mBuffer->getFormat());
        for (size_t y = box.top; y < box.bottom; ++y)
        {
            for (size_t x = box.left; x < box.right; ++x)
            {
                *pDst++ = static_cast<float>(*pSrc) / 255.0f;
                pSrc += srcInc;
            }
        }
        mBuffer->unlock();

    }

    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::convertUVToImageSpace(Real x, Real y, size_t* outX, size_t* outY)
    {
        *outX = (unsigned long)(x * (mBuffer->getWidth() - 1));
        *outY = (unsigned long)(y * (mBuffer->getHeight() - 1));
    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::convertImageToUVSpace(size_t x, size_t y, Real* outX, Real* outY)
    {
        *outX = x / (Real)(mBuffer->getWidth() - 1);
        *outY = y / (Real)(mBuffer->getHeight() - 1);
    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::convertImageToTerrainSpace(size_t x, size_t y, Real* outX, Real* outY)
    {
        convertImageToUVSpace(x, y, outX, outY);
        *outY = 1.0f - *outY;
    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::convertTerrainToImageSpace(Real x, Real y, size_t* outX, size_t* outY)
    {
        convertUVToImageSpace(x, 1.0f - y, outX, outY);
    }
    //---------------------------------------------------------------------
    float TerrainLayerBlendMap::getBlendValue(size_t x, size_t y)
    {
        return *(mData + y * mBuffer->getWidth() + x);
    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::setBlendValue(size_t x, size_t y, float val)
    {
        *(mData + y * mBuffer->getWidth() + x) = val;
        dirtyRect(Rect(x, y, x+1, y+1));

    }
    //---------------------------------------------------------------------
    float* TerrainLayerBlendMap::getBlendPointer()
    {
        return mData;
    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::dirty()
    {
        Rect rect;
        rect.top = 0; rect.bottom = mBuffer->getHeight();
        rect.left = 0; rect.right = mBuffer->getWidth();
        dirtyRect(rect);

    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::dirtyRect(const Rect& rect)
    {
        if (mDirty)
        {
            mDirtyBox.left = min(mDirtyBox.left, (size_t)rect.left);
            mDirtyBox.top = min(mDirtyBox.top, (size_t)rect.top);
            mDirtyBox.right = max(mDirtyBox.right, (size_t)rect.right);
            mDirtyBox.bottom = max(mDirtyBox.bottom, (size_t)rect.bottom);
        }
        else
        {
            mDirtyBox.left = rect.left;
            mDirtyBox.right = rect.right;
            mDirtyBox.top = rect.top;
            mDirtyBox.bottom = rect.bottom;
            mDirty = true;
        }
    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::update()
    {
        if (mData && mDirty)
        {
            // Upload data
            float* pSrcBase = mData + mDirtyBox.top * mBuffer->getWidth() + mDirtyBox.left;
            uint8* pDstBase = static_cast<uint8*>(mBuffer->lock(mDirtyBox, HardwarePixelBuffer::HBL_NORMAL).data);
            pDstBase += mChannelOffset;
            size_t dstInc = PixelUtil::getNumElemBytes(mBuffer->getFormat());
            for (size_t y = 0; y < mDirtyBox.getHeight(); ++y)
            {
                float* pSrc = pSrcBase + y * mBuffer->getWidth();
                uint8* pDst = pDstBase + y * mBuffer->getWidth() * dstInc;
                for (size_t x = 0; x < mDirtyBox.getWidth(); ++x)
                {
                    *pDst = static_cast<uint8>(*pSrc++ * 255);
                    pDst += dstInc;
                }
            }
            mBuffer->unlock();

            mDirty = false;
        }
    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::blit(const PixelBox &src, const Box &dstBox)
    {
        const PixelBox* srcBox = &src;

        if (srcBox->getWidth() != dstBox.getWidth() || srcBox->getHeight() != dstBox.getHeight())
        {
            // we need to rescale src to dst size first (also confvert format)
            void* tmpData = OGRE_MALLOC(dstBox.getWidth() * dstBox.getHeight(), MEMCATEGORY_GENERAL);
            srcBox = OGRE_NEW PixelBox(dstBox.getWidth(), dstBox.getHeight(), 1, PF_L8, tmpData);
            DYNAMIC_ASSERT_LOG( srcBox!=NULL, "TerrainLayerBlendMap::blit srcBox failed" );

            Image::scale(src, *srcBox);
        }

        // pixel conversion
        PixelBox dstMemBox(dstBox, PF_L8, mData);
        PixelUtil::bulkPixelConversion(*srcBox, dstMemBox);

        if (srcBox != &src)
        {
            // free temp
            OGRE_FREE(srcBox->data, MEMCATEGORY_GENERAL);
            OGRE_DELETE srcBox;
            srcBox = 0;
        }

        Rect dRect(dstBox.left, dstBox.top, dstBox.right, dstBox.bottom);
        dirtyRect(dRect);

    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::blit(const PixelBox &src)
    {
        blit(src, Box(0,0,0,mBuffer->getWidth(),mBuffer->getHeight(),1));
    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::loadImage(const Image& img)
    {
        blit(img.getPixelBox());
    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::loadImage(DataStreamPtr& stream, const String& ext)
    {
        Image img;
        img.load(stream, ext);
        loadImage(img);
    }
    //---------------------------------------------------------------------
    void TerrainLayerBlendMap::loadImage(const String& filename, const String& groupName)
    {
        Image img;
        img.load(filename, groupName);
        loadImage(img);
    }

}