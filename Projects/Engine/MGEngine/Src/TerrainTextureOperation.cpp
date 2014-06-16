/******************************************************************************/
#include "stdafx.h"
#include "TerrainTextureOperation.h"
#include "Scene.h"
#include "TerrainChunk.h"
#include "BrushSystem.h"
#include "TerrainTiles.h"
#include "TerrainTextureOperationManager.h"
#include "BrushStyle.h"
#include "BrushShape.h"
#include "EngineUtil.h"
#include "TerrainGroundTiles.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //TerrainTextureOperation
    /******************************************************************************/
    TerrainTextureOperation::TerrainTextureOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainTextureOperation::~TerrainTextureOperation()
    {

    }

	//-----------------------------------------------------------------------
	void TerrainTextureOperation::execute( TerrainChunk* chunk, Ogre::Rect& worldRect )
	{
        TerrainSurface* surface = chunk->getTerrainGroundSurface();
        if ( surface )
        {

			Vec3 brushPos   = BrushSystem::getInstance().getStartPos();
			Flt brushSize   = BrushSystem::getInstance().getSize();

            /* // 世界坐标

            -z
            |
            |
            w0---------w1
            |          |
            | [brush]  |
            |          |
            w2---------w3----+x
            */

            // 世界坐标Rect
            Vec2 w0 = Vec2( worldRect.left,   worldRect.top );
            Vec2 w1 = Vec2( worldRect.right,  worldRect.top );
            Vec2 w2 = Vec2( worldRect.left,   worldRect.bottom );
            Vec2 w3 = Vec2( worldRect.right,  worldRect.bottom );

			/* // 地形Tile坐标
			+y
			|
			|
			t0---------t1
			|          |
			| [brush]  |
			|          |
			t2---------t3----+x
			*/
			// 地形坐标Rect
			
			Vec2 t0,t1,t2,t3; 
			surface->convertWorldPositionToGridPoint(w0, t0);
			surface->convertWorldPositionToGridPoint(w1, t1);
			surface->convertWorldPositionToGridPoint(w2, t2);
			surface->convertWorldPositionToGridPoint(w3, t3);

			// loop node in surface
            for (uint16 y = t2.y; y <= t0.y; y ++)
            {
                for (uint16 x = t0.x; x <= t1.x; x ++)
                {
                    TerrainNodeGrid* node = surface->getGridDataByIndex(x,y);
                    if ( node && node->node )
					{
						Vec2 n0,n1,n2,n3; 

						node->node->convertWorldPositionToGridPoint(w0, n0);
						node->node->convertWorldPositionToGridPoint(w1, n1);
						node->node->convertWorldPositionToGridPoint(w2, n2);
						node->node->convertWorldPositionToGridPoint(w3, n3);

						// loop tile in node
						for (uint16 y2 = n2.y; y2 <= n0.y; y2 ++)
						{
							for (uint16 x2 = n0.x; x2 <= n1.x; x2 ++)
							{
								TerrainTile* tile = node->node->getGridDataByIndex(x2,y2);

								if ( tile && tile->render )
								{
									Ogre::Rect tileRect     = tile->render->getWorldBoundingRect();
									Ogre::Rect renderRect   = worldRect.intersect( tileRect );

									if ( renderRect.isNull() == false )
									{
										TerrainGroundTileRender* render = (TerrainGroundTileRender*)tile->render;

										UInt texSize    = render->getBlendTexturSize();
										Flt worldSize   = tile->radius * 2;
										Flt factor      = texSize / worldSize;
										Flt pixelSize   = worldSize / texSize + 0.01;
										Ogre::Rect blendMapRect;

										// 转换成 贴图坐标

										blendMapRect.left   = (renderRect.left      - tileRect.left) * factor ;
										blendMapRect.right  = (renderRect.right     - tileRect.left) * factor ;
										blendMapRect.top    = (renderRect.top       - tileRect.top) * factor  ;
										blendMapRect.bottom = (renderRect.bottom    - tileRect.top) * factor  ;

										// 放大检测的贴图坐标一个象素
										blendMapRect.left   -= 1 ;
										blendMapRect.right  += 1 ;
										blendMapRect.top    -= 1 ;
										blendMapRect.bottom += 1 ;

										blendMapRect.left   = Ogre::Math::Clamp(blendMapRect.left,    (long)0, (long)texSize-1);
										blendMapRect.right  = Ogre::Math::Clamp(blendMapRect.right,   (long)0, (long)texSize-1);
										blendMapRect.top    = Ogre::Math::Clamp(blendMapRect.top,     (long)0, (long)texSize-1);
										blendMapRect.bottom = Ogre::Math::Clamp(blendMapRect.bottom,  (long)0, (long)texSize-1);

										this->execute( tile, blendMapRect, pixelSize );
									}
								}
							}
						}
					}
                }
            }
        }
	}

    //-----------------------------------------------------------------------
    void TerrainTextureOperation::execute( TerrainTile* tile , Ogre::Rect& blendMapRect, Flt pixelSize )
    {
        TerrainGroundTileRender* render = (TerrainGroundTileRender*)tile->render;

        UInt texSize            = render->getBlendTexturSize();
        Ogre::Rect tileRect     = tile->render->getWorldBoundingRect();
        Flt worldSize           = tile->radius * 2;


        IBrushShape* brushShape = BrushSystem::getInstance().getActiveShape();
        IBrushStyle* brushStyle = BrushSystem::getInstance().getActiveStyle();

        Vec2 margin;
        for (uint16 y = blendMapRect.top; y <= blendMapRect.bottom; y ++)
        {
            for (uint16 x = blendMapRect.left; x <= blendMapRect.right; x ++)
            {
                // 得到世界坐标
                Vec2 terrainPos( Flt(x) / Flt(texSize), Flt(y) / Flt(texSize) );
                Vec2 world2DPos;
                world2DPos.x = tileRect.left +  terrainPos.x * worldSize ;
                world2DPos.y = tileRect.top  +  terrainPos.y * worldSize ;
                
                // 判断是否在笔刷范围内
                if ( brushShape->isValidPos( world2DPos, margin ) )
                {
                    // 得到笔刷的影响系数
                    Flt influence = brushStyle->getIntensity( world2DPos );

                    influenceBlendMap( tile, x, y, influence, false);
                }else
                {
                    // 解决边缘混合插值造成的过渡问题
                    Flt marginLen = margin.length();
                    if ( pixelSize > marginLen )
                    {
                        // 得到笔刷的影响系数
                        Flt influence = brushStyle->getIntensity( world2DPos );

                        influence *= (pixelSize-marginLen) / pixelSize;
                        influenceBlendMap( tile, x, y, influence, true );
                    }
                }
            }
        }

        /////////////////////////////////////////////////////////////////////////////

        /*String name = tile->render->getValidDiffuseSpecularTextureAtlasNameList()[0];
        Ogre::Image img;
        TextureManager& texMgr = TextureManager::getSingleton();
        TexturePtr texSet = texMgr.getByName(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        if (texSet.isNull()==false)
        {

            Ogre::Image tempImg;
            texSet->convertToImage(tempImg,false);

            TexturePtr textestSet = texMgr.getByName("test_TerrainTilesManager_copyTextureToSet");
            if (textestSet.isNull())
            {
                textestSet = texMgr.createManual("test_TerrainTilesManager_copyTextureToSet", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                    TEX_TYPE_2D,1024,1024, MIP_DEFAULT, PF_A8R8G8B8, TU_STATIC | TU_AUTOMIPMAP);
            }
            textestSet->getBuffer()->blitFromMemory(tempImg.getPixelBox());
            textestSet->convertToImage(tempImg,false);
            tempImg.save("C:\\texSet.png");

        }*/

        /////////////////////////////////////////////////////////////////////////////
        //{
        //    TexturePtr texPtr = tile->render->getBlendTexture(0);
        //    Ogre::Image img;
        //    if (texPtr.isNull()==false)
        //    {
        //        texPtr->convertToImage(img,false);
        //        img.save("C:\\blend.png");
        //    }
        //}

    }

	//-----------------------------------------------------------------------
	void TerrainTextureOperation::rollback()
	{

	}

    /******************************************************************************/
    //TerrainAddTextureOperation
    /******************************************************************************/
    TerrainAddTextureOperation::TerrainAddTextureOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainAddTextureOperation::~TerrainAddTextureOperation()
    {

    }


	//-----------------------------------------------------------------------
	void TerrainAddTextureOperation::influenceBlendMap(TerrainTile* tile, Int blendImgX, Int blendImgY, Flt influence,Bool isEdge)
	{
		if ( influence < 0.0f )
			influence = 0.0f;

        TerrainGroundTileRender* render = (TerrainGroundTileRender*)tile->render;

		Int count = render->getTextureLayerCount();
		Int globleIndex = BrushSystem::getInstance().getActiveTextureLayerIndex();
        Int texIndex = render->createOrRetriveTextureLayer( globleIndex, true );

		Flt amplitude = TerrainAddTextureOperationManager::getInstance().getAmplitude();
		amplitude *= influence;

        // 修改各个混合层的比例
        Flt lastAboveBlendLayersRate = 1;
        Flt currAboveBlendLayersRate = 1;
        Flt currAmp = 0;
		for ( Int i=count-1;i>=texIndex;i--)
		{
            TerrainLayerBlendMap* layer = NULL;
            if ( i==0 )
            {
                layer = render->createOrRetriveTextureBlendLayer(1);
            }
            else
            {
                layer = render->createOrRetriveTextureBlendLayer(i);
            }
            Flt val = layer->getBlendValue(blendImgX, blendImgY);

            //修改上面层
            if ( (texIndex != i) && (i != 1) )
            {
                //通过上层和下层的比例算出该层上面的颜色层占有总颜色的比例
                Flt lastTotalRate = val * lastAboveBlendLayersRate;

                //计算修改前上层混合比例给下个循环用
                lastAboveBlendLayersRate = lastAboveBlendLayersRate*(1-val);

                //根据总的比例得到自己需要减去的混合值
                currAmp = amplitude * lastTotalRate;

                if (currAboveBlendLayersRate>0)
                {
                    val = ( lastTotalRate - currAmp ) / currAboveBlendLayersRate;
                }else
                {
                    break;
                }

                //计算修改后上层混合比例给下个循环用
                currAboveBlendLayersRate = currAboveBlendLayersRate*(1-val);
            }else
            {
                //根据总的比例加上自己的混合值
                if ( texIndex>0 )
                {
                    if (currAboveBlendLayersRate>0)
                    {
                        val = ( amplitude + lastAboveBlendLayersRate*val ) / currAboveBlendLayersRate;
                    }else
                    {
                        val += amplitude; 
                    }
                }else
                {
                    if (currAboveBlendLayersRate>0)
                    {
                        val = 1 - ( ( lastAboveBlendLayersRate*(1-val) + amplitude ) / currAboveBlendLayersRate );
                    }else
                    {
                        break;
                    }    
                }
            }
          
            if (val>1.0f)
                val = 1.0f;
            if (val<0.0f)
                val = 0.0f;

            layer->setBlendValue(blendImgX,blendImgY,val);
		}
	}
    /******************************************************************************/
    //TerrainRemoveTextureOperation
    /******************************************************************************/
    TerrainRemoveTextureOperation::TerrainRemoveTextureOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainRemoveTextureOperation::~TerrainRemoveTextureOperation()
    {

    }

    /******************************************************************************/
    //TerrainUniformTextureOperation
    /******************************************************************************/
    TerrainUniformTextureOperation::TerrainUniformTextureOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainUniformTextureOperation::~TerrainUniformTextureOperation()
    {

    }


    /******************************************************************************/
    //TerrainMopTextureOperation
    /******************************************************************************/
    TerrainMopTextureOperation::TerrainMopTextureOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainMopTextureOperation::~TerrainMopTextureOperation()
    {

    }


    /******************************************************************************/
    //TerrainBlurTextureOperation
    /******************************************************************************/
    TerrainBlurTextureOperation::TerrainBlurTextureOperation()
    {

    }

    //-----------------------------------------------------------------------
    TerrainBlurTextureOperation::~TerrainBlurTextureOperation()
    {
		
    }



}


