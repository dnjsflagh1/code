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
    //��Ϸ������ͼ����
    /******************************************************************************/
    class TerrainTextureOperation : public EditorOperation
    {
    public:
        TerrainTextureOperation();
        virtual ~TerrainTextureOperation();

		//��Ӧһ�β���
		virtual void    execute( TerrainChunk* chunk, Ogre::Rect& worldRect ) ;
		//����һ�β���
		virtual void    rollback();

                void    execute( TerrainTile* tile , Ogre::Rect& blendMapRect, Flt pixelSize );

		//Ӱ����ͼƬ
        virtual void    influenceBlendMap( TerrainTile* tile, Int blendImgX, Int blendImgY, Flt influence,Bool isEdge) {};
    };

    /******************************************************************************/
    //��Ϸ������ͼ���߲���
    /******************************************************************************/
    class TerrainAddTextureOperation : public TerrainTextureOperation
    {
    public:
        TerrainAddTextureOperation();
        virtual ~TerrainAddTextureOperation();

		virtual void    influenceBlendMap(TerrainTile* tile, Int blendImgX, Int blendImgY, Flt influence,Bool isEdge);
    };

    /******************************************************************************/
    //��Ϸ������ͼ���Ͳ���
    /******************************************************************************/
    class TerrainRemoveTextureOperation : public TerrainTextureOperation
    {
    public:
        TerrainRemoveTextureOperation();
        virtual ~TerrainRemoveTextureOperation();

    };

    /******************************************************************************/
    //��Ϸ������ͼͳһ����
    /******************************************************************************/
    class TerrainUniformTextureOperation : public TerrainTextureOperation
    {
    public:
        TerrainUniformTextureOperation();
        virtual ~TerrainUniformTextureOperation();

    };

    /******************************************************************************/
    //��Ϸ������ͼĨͿ����
    /******************************************************************************/
    class TerrainMopTextureOperation : public TerrainTextureOperation
    {
    public:
        TerrainMopTextureOperation();
        virtual ~TerrainMopTextureOperation();

    };

    /******************************************************************************/
    //��Ϸ������ͼģ������
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

