/******************************************************************************/
#ifndef _TERRAINTEXTUREOPERATION_H_
#define _TERRAINTEXTUREOPERATION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "EditorOperation.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //游戏地形贴图操作
    /******************************************************************************/
    class TerrainTextureOperation : public EditorOperation
    {
    public:
        TerrainTextureOperation();
        virtual ~TerrainTextureOperation();

		//响应一次操作
		virtual void    execute( TerrainChunk* chunk, Ogre::Rect& worldRect ) ;
		//回退一次操作
		virtual void    rollback();

                void    execute( TerrainTile* tile , Ogre::Rect& blendMapRect, Flt pixelSize );

		//影响混合图片
        virtual void    influenceBlendMap( TerrainTile* tile, Int blendImgX, Int blendImgY, Flt influence,Bool isEdge) {};
    };

    /******************************************************************************/
    //游戏地形贴图升高操作
    /******************************************************************************/
    class TerrainAddTextureOperation : public TerrainTextureOperation
    {
    public:
        TerrainAddTextureOperation();
        virtual ~TerrainAddTextureOperation();

		virtual void    influenceBlendMap(TerrainTile* tile, Int blendImgX, Int blendImgY, Flt influence,Bool isEdge);
    };

    /******************************************************************************/
    //游戏地形贴图降低操作
    /******************************************************************************/
    class TerrainRemoveTextureOperation : public TerrainTextureOperation
    {
    public:
        TerrainRemoveTextureOperation();
        virtual ~TerrainRemoveTextureOperation();

    };

    /******************************************************************************/
    //游戏地形贴图统一操作
    /******************************************************************************/
    class TerrainUniformTextureOperation : public TerrainTextureOperation
    {
    public:
        TerrainUniformTextureOperation();
        virtual ~TerrainUniformTextureOperation();

    };

    /******************************************************************************/
    //游戏地形贴图抹涂操作
    /******************************************************************************/
    class TerrainMopTextureOperation : public TerrainTextureOperation
    {
    public:
        TerrainMopTextureOperation();
        virtual ~TerrainMopTextureOperation();

    };

    /******************************************************************************/
    //游戏地形贴图模糊操作
    /******************************************************************************/
    class TerrainBlurTextureOperation : public TerrainTextureOperation
    {
    public:
        TerrainBlurTextureOperation();
        virtual ~TerrainBlurTextureOperation();

    };


}

/******************************************************************************/

#endif

