/******************************************************************************/
#ifndef _TERRAINHEIGHTOPERATION_H_
#define _TERRAINHEIGHTOPERATION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "EditorOperation.h"
#include "ITerrain.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //游戏地形高度操作
    /******************************************************************************/
    class TerrainHeightOperation : public EditorOperation
    {
    public:
        TerrainHeightOperation(TerrainSurfaceType type);
        virtual ~TerrainHeightOperation();

		//响应一次操作
		virtual void    execute( TerrainChunk* chunk, Ogre::Rect& worldRect );
		//回退一次操作
		virtual void    rollback();
		//影响高度
		virtual void    influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity ) {};

    protected:

        TerrainSurfaceType mTerrainSurfaceType;
    };

    /******************************************************************************/
    //游戏地形高度升高操作
    /******************************************************************************/
    class TerrainRaiseHeightOperation : public TerrainHeightOperation
    {
    public:
        TerrainRaiseHeightOperation(TerrainSurfaceType type);
        virtual ~TerrainRaiseHeightOperation();

		virtual void    influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity );
    };

    /******************************************************************************/
    //游戏地形高度降低操作
    /******************************************************************************/
    class TerrainLowerHeightOperation : public TerrainHeightOperation
    {
    public:
        TerrainLowerHeightOperation(TerrainSurfaceType type);
        virtual ~TerrainLowerHeightOperation();

		virtual void    influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity );
    };

    /******************************************************************************/
    //游戏地形高度统一操作
    /******************************************************************************/
    class TerrainUniformHeightOperation : public TerrainHeightOperation
    {
    public:
        TerrainUniformHeightOperation(TerrainSurfaceType type);
        virtual ~TerrainUniformHeightOperation();

		virtual void	execute();

		virtual void    influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity );
    };

    /******************************************************************************/
    //游戏地形高度噪音操作
    /******************************************************************************/
    class TerrainNoiseHeightOperation : public TerrainHeightOperation
    {
    public:
        TerrainNoiseHeightOperation(TerrainSurfaceType type);
        virtual ~TerrainNoiseHeightOperation();

		virtual void    influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity );

	protected:

                Flt		coherentNoise(Vec2 vertex_frac, 
                                        Flt left_top, Flt left_buttom, Flt right_top, Flt right_buttom);
                Flt		perlinNoise(int octaves, Vec2 vertex_frac, 
                                        Flt left_top, Flt left_buttom, Flt right_top, Flt right_buttom);

    };

    /******************************************************************************/
    //游戏地形高度平滑操作
    /******************************************************************************/
    class TerrainSmoothHeightOperation : public TerrainHeightOperation
    {
    public:
        TerrainSmoothHeightOperation(TerrainSurfaceType type);
        virtual ~TerrainSmoothHeightOperation();

		virtual void    influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity );
    };

}

/******************************************************************************/

#endif

