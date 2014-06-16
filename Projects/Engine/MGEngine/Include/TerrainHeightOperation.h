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
    //��Ϸ���θ߶Ȳ���
    /******************************************************************************/
    class TerrainHeightOperation : public EditorOperation
    {
    public:
        TerrainHeightOperation(TerrainSurfaceType type);
        virtual ~TerrainHeightOperation();

		//��Ӧһ�β���
		virtual void    execute( TerrainChunk* chunk, Ogre::Rect& worldRect );
		//����һ�β���
		virtual void    rollback();
		//Ӱ��߶�
		virtual void    influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity ) {};

    protected:

        TerrainSurfaceType mTerrainSurfaceType;
    };

    /******************************************************************************/
    //��Ϸ���θ߶����߲���
    /******************************************************************************/
    class TerrainRaiseHeightOperation : public TerrainHeightOperation
    {
    public:
        TerrainRaiseHeightOperation(TerrainSurfaceType type);
        virtual ~TerrainRaiseHeightOperation();

		virtual void    influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity );
    };

    /******************************************************************************/
    //��Ϸ���θ߶Ƚ��Ͳ���
    /******************************************************************************/
    class TerrainLowerHeightOperation : public TerrainHeightOperation
    {
    public:
        TerrainLowerHeightOperation(TerrainSurfaceType type);
        virtual ~TerrainLowerHeightOperation();

		virtual void    influenceHeight( TerrainChunk* chunk, TerrainSurface* surface, Int x, Int y, Flt intensity );
    };

    /******************************************************************************/
    //��Ϸ���θ߶�ͳһ����
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
    //��Ϸ���θ߶���������
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
    //��Ϸ���θ߶�ƽ������
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

