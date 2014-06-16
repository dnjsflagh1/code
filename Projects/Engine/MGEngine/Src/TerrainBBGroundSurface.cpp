/******************************************************************************/
#include "stdafx.h"

#include "TerrainBBGroundSurface.h"
#include "TerrainGroundTiles.h"
#include "TerrainBBGroundTiles.h"
#include "TerrainGroundSurface.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "Scene.h"
#include "TerrainTiles.h"
#include "TerrainTilesGpu.h"
#include "TerrainTilesLayerBlendMap.h"
#include "TerrainTilesMaterial.h"
#include "TerrainTilesMaterialA.h"
#include "TerrainTilesOptions.h"
#include "MGSceneNode.h"
#include "MGEngineUtility.h"

#include "TerrainNode.h"

#include "OgreStreamSerialiser.h"
#include "OgreMath.h"
#include "OgreImage.h"
#include "OgrePixelFormat.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OgreException.h"
#include "OgreBitwise.h"
#include "OgreStringConverter.h"
#include "OgreViewport.h"
#include "OgreLogManager.h"
#include "OgreHardwarePixelBuffer.h"
#include "OgreTextureManager.h"
#include "OgreRoot.h"
#include "OgreRenderSystem.h"
#include "OgreRay.h"
#include "OgrePlane.h"
#include "OgreMaterialManager.h"
#include "OgreHardwareBufferManager.h"
#include "Display.h"


/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    TerrainBBGroundSurface::TerrainBBGroundSurface(TerrainManager* terrainMgr, Scene* scene, TerrainChunk* chunk)
        : TerrainGroundSurface(terrainMgr,scene,chunk)
    {
    }   
    //-----------------------------------------------------------------------
    TerrainBBGroundSurface::~TerrainBBGroundSurface()
    {
        unLoad();
    }

    //-----------------------------------------------------------------------
    TerrainTileRender* TerrainBBGroundSurface::createTerrainTileRender( TerrainManager* mgr, TerrainChunk* chunk, 
        TerrainNode* node, TerrainTile* tile, UInt index )
    {
        return MG_NEW TerrainBBGroundTileRender( mgr, chunk, node, tile, index );
    }



    //---------------------------------------------------------------------
    void TerrainBBGroundSurface::loadBlendLayerMap(Str& path)
    {
        //////////////////////////////////////////////////////////////////////////////////////

        mLayerBlendMapSizeActual = mLayerBlendMapSize; // for now, until we check

        PixelFormat blendFormat = TerrainGroundTileRender::getBlendTexturFormat();

        /////////////////////////////////////////////////////////////////////

        String blendTexName = "BlendLayerMapTemplate";
        TextureManager& texMgr = TextureManager::getSingleton();
        TexturePtr blendMapTex = texMgr.getByName(blendTexName,ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        if (blendMapTex.isNull())
        {
            Int mipmap = MGEngineUtility::getMipMapNum( mBlendMapSizeInTile );
            blendMapTex = texMgr.createManual(blendTexName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                TEX_TYPE_2D, mLayerBlendMapSizeActual, mLayerBlendMapSizeActual, mipmap, blendFormat, TU_STATIC | TU_AUTOMIPMAP);
        }

        /////////////////////////////////////////////////////////////////////

        UInt numMax = 2;

        for (UInt i = 0; i < numMax; ++i)
        {
            std::ostringstream s;
            s << "BlendMap" << i << ".png";
            Str filename = s.str();
            if ( Ogre::ResourceGroupManager::getSingleton().resourceExists(path,filename) )
            {
                Ogre::Image img;
                img.load(filename, path);
                if (img.getWidth() != mLayerBlendMapSizeActual || img.getHeight() != mLayerBlendMapSizeActual)
                    img.resize(mLayerBlendMapSizeActual, mLayerBlendMapSizeActual);

                if ( img.getFormat() == blendFormat )
                {
                    blendMapTex->getBuffer()->blitFromMemory( img.getPixelBox() );

                    // ����Tile
                    Image::Box srcBox ;
                    Image::Box desBox = Image::Box( 0, 0, mBlendMapSizeInTile, mBlendMapSizeInTile);
                    for (size_t y = 0; y < mTextureIndexMapSize; ++y)
                    {
                        for (size_t x = 0; x < mTextureIndexMapSize; ++x)
                        {
                            TerrainTile* tile = this->getTileGridDataByIndex(x,y);
                            if ( tile == NULL )
                                break;
                            if ( tile->render == NULL )
                                break;

                            TerrainGroundTileRender* render = (TerrainGroundTileRender*)tile->render;

                            TexturePtr tileBlendTexMap = render->getBlendTexture( i );
                            if ( tileBlendTexMap.isNull() == false )
                            {
                                srcBox.left     = x * mBlendMapSizeInTile;
                                srcBox.top      = (mTextureIndexMapSize-y-1) * mBlendMapSizeInTile;
                                srcBox.right    = srcBox.left + mBlendMapSizeInTile  ;
                                srcBox.bottom   = srcBox.top + mBlendMapSizeInTile ;

                                tileBlendTexMap->getBuffer()->blit( blendMapTex->getBuffer(), srcBox, desBox );
                            }
                        }
                    }
                }
            }
        }

        /////////////////////////////////////////////////////////////////////


        if (blendMapTex.isNull()==false)
        {
            texMgr.remove( blendMapTex->getHandle() );
        }


        /////////////////////////////////////////////////////////////////////

    }

    //---------------------------------------------------------------------
    void TerrainBBGroundSurface::unLoadBlendLayerMap()
    {

    }               

    //---------------------------------------------------------------------
    void TerrainBBGroundSurface::saveBlendLayerMap( Str& path )
    {
        mLayerBlendMapSizeActual = mLayerBlendMapSize; // for now, until we check

        PixelFormat blendFormat = TerrainGroundTileRender::getBlendTexturFormat();

        /////////////////////////////////////////////////////////////////////

        String blendTexName = "BlendLayerMapTemplate";
        TextureManager& texMgr = TextureManager::getSingleton();
        TexturePtr blendMapTex = texMgr.getByName(blendTexName,ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        if (blendMapTex.isNull())
        {   
            Int mipmap = MGEngineUtility::getMipMapNum( mBlendMapSizeInTile );
            blendMapTex = texMgr.createManual(blendTexName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                TEX_TYPE_2D, mLayerBlendMapSizeActual, mLayerBlendMapSizeActual, mipmap, blendFormat, TU_STATIC | TU_AUTOMIPMAP);
        
            DYNAMIC_ASSERT_LOG( blendMapTex.isNull() == false, "saveBlendLayerMap blendMapTex failed" );
        }

        /////////////////////////////////////////////////////////////////////

        UInt numMax = 2;

        for (UInt i = 0; i < numMax; ++i)
        {
            // ����Tile
            Image::Box srcBox = Image::Box( 0, 0, mBlendMapSizeInTile, mBlendMapSizeInTile);
            Image::Box desBox ;
            for (size_t y = 0; y < mTextureIndexMapSize; ++y)
            {
                for (size_t x = 0; x < mTextureIndexMapSize; ++x)
                {
                    TerrainTile* tile = this->getTileGridDataByIndex(x,y);
                    if ( tile == NULL )
                        break;
                    if ( tile->render == NULL )
                        break;

                    TerrainGroundTileRender* render = (TerrainGroundTileRender*)tile->render;

                    TexturePtr tileBlendTexMap = render->getBlendTexture( i );
                    if ( tileBlendTexMap.isNull() == false )
                    {
                        desBox.left     = x * mBlendMapSizeInTile;
                        desBox.top      = (mTextureIndexMapSize-y-1) * mBlendMapSizeInTile;
                        desBox.right    = desBox.left + mBlendMapSizeInTile ;
                        desBox.bottom   = desBox.top + mBlendMapSizeInTile ;

                        blendMapTex->getBuffer()->blit( tileBlendTexMap->getBuffer(), srcBox, desBox );
                    }
                }
            }

            Image img;
            blendMapTex->convertToImage(img);

            std::ostringstream s;
            s << "BlendMap" << i << ".png";
            Str filename = s.str();
            Str filePath   = FileOp::getFullFilePath( path, filename );
            img.save( filePath );

			///for test--------------
			//std::ostringstream bs;
			//bs << "BlendMap" << i << ".bmp";
			//filename = bs.str();
			//filePath   = FileOp::getFullFilePath( path, filename );
			//img.save( filePath );
			///--end for test
        }

        /////////////////////////////////////////////////////////////////////


        if (blendMapTex.isNull()==false)
        {
            texMgr.remove( blendMapTex->getHandle() );
        }


        /////////////////////////////////////////////////////////////////////
    }


	//---------------------------------------------------------------------
	void TerrainBBGroundSurface::_reorderBlendLayerMap( const Str& path )
	{
		Str tempPath = path;
		mLayerBlendMapSizeActual = mLayerBlendMapSize; // for now, until we check

		UInt numMax = 2;

		PixelFormat blendFormat = TerrainGroundTileRender::getBlendTexturFormat();

		/////////////////////////////////////////////////////////////////////

		TextureManager& texMgr = TextureManager::getSingleton();

		std::vector<TexturePtr> blendMapTexs;
		for (int i=0; i<numMax; ++i)
		{
			std::ostringstream s;
			s << "BlendLayerMapTemplate" << i;
			String blendTexName = s.str();
			TexturePtr blendMapTex = texMgr.getByName(blendTexName,ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			if (blendMapTex.isNull())
			{   
				Int mipmap = MGEngineUtility::getMipMapNum( mBlendMapSizeInTile );
				blendMapTex = texMgr.createManual(blendTexName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
					TEX_TYPE_2D, mLayerBlendMapSizeActual, mLayerBlendMapSizeActual, mipmap, blendFormat, TU_STATIC | TU_AUTOMIPMAP);

				DYNAMIC_ASSERT_LOG( blendMapTex.isNull() == false, "saveBlendLayerMap blendMapTex failed" );
			}

			blendMapTexs.push_back(blendMapTex);
		}

		/////////////////////////////////////////////////////////////////////
		//����Tile
		for (size_t y = 0; y < mTextureIndexMapSize; ++y)
		{
			for (size_t x = 0; x < mTextureIndexMapSize; ++x)
			{
				TerrainTile* tile = this->getTileGridDataByIndex(x,y);
				if ( tile == NULL )
					break;
				if ( tile->render == NULL )
					break;

				TerrainGroundTileRender* render = (TerrainGroundTileRender*)tile->render;

				Image::Box srcBox(0,0,mBlendMapSizeInTile,mBlendMapSizeInTile);
				Image::Box desBox;
				desBox.left     = x * mBlendMapSizeInTile;
				desBox.top      = (mTextureIndexMapSize-y-1) * mBlendMapSizeInTile;
				desBox.right    = desBox.left + mBlendMapSizeInTile ;
				desBox.bottom   = desBox.top + mBlendMapSizeInTile ;

				typedef std::map<int, pair<int,std::vector<float> > > layerPixelType;
				layerPixelType layersPixels;

				int firstIndex = 0;

				float one = 0.999999f;
				float zero = 0.000001f;

				//����layer���ҷ��ϵ�ͨ��
				for (UInt i = 0; i < numMax; ++i)
				{
					TexturePtr tileBlendTexMap = render->getBlendTexture( i );

					///for test -------------------------------
					//Image img;
					//tileBlendTexMap->convertToImage(img);

					//std::ostringstream s;
					//s << "TileBlend" << i << ".bmp";
					//Str filename = s.str();
					//Str filePath   = FileOp::getFullFilePath( tempPath, filename );
					//img.save( filePath );
					///--end for test
					

					for (int layerIndex=0; layerIndex<4; ++layerIndex)
					{
						int globalLayerIndex = layerIndex + i*4;
						TerrainGroundTileRender::TextureLayerInstance*  instance = instance = render->getTextureLayer( globalLayerIndex );

						if (instance == NULL)
							continue;

						int globalIndex = instance->globleIndex;

						//����һ����ʱVector���ڴ洢��ǰͨ��ֵ
						std::vector<float> chanelValues(mBlendMapSizeInTile*mBlendMapSizeInTile);

						//���ԭͼ�㱣����0ͼ�㣬��Ҫ�����ͼ��ͨ��ֵȫ��Ϊ1
						if ( globalLayerIndex == 0 )
						{
							//�����ڴ�TileBlendMap
							firstIndex = globalIndex;
							HardwarePixelBufferSharedPtr pixelPtr = tileBlendTexMap->getBuffer();
							PixelBox tilePb = pixelPtr->lock(srcBox,HardwareBuffer::LockOptions::HBL_NORMAL);

							size_t width = tilePb.getWidth();
							size_t height = tilePb.getHeight();
							size_t pitch = tilePb.rowPitch;

							//����TileBlendMap��ÿ������,�����Ӧͨ��ֵ
							for (size_t m=0; m<width; ++m)
							{
								size_t rowindex = m*width;
								for (size_t n=0; n<height; ++n)
								{
									float chanelValue = one;
									//chanelValues.push_back(chanelValue);
									chanelValues[rowindex+n] = chanelValue;
								}
							}

							//�����ڴ�TileBlendMap
							pixelPtr->unlock();
						}
						else
						{
							//���ԭͼ�㱣���ڵ�5��(�ڵڶ���TileBlendMap),��Ҫ����ͼ��ͨ��ֵ���浽��һ����ͼ
							if ( globalLayerIndex == 4)
							{
								//�����ڴ�TileBlendMap
								TexturePtr tileBlendTexMap0 = render->getBlendTexture( 0 );
								HardwarePixelBufferSharedPtr pixelPtr = tileBlendTexMap0->getBuffer();
								PixelBox tilePb = pixelPtr->lock(srcBox,HardwareBuffer::LockOptions::HBL_NORMAL);

								size_t width = tilePb.getWidth();
								size_t height = tilePb.getHeight();
								size_t pitch = tilePb.rowPitch;


								//����TileBlendMap��ÿ������,�����Ӧͨ��ֵ
								for (size_t m=0; m<width; ++m)
								{
									size_t rowindex = m*width;
									for (size_t n=0; n<height; ++n)
									{
										ColourValue tileColor = tilePb.getColourAt(m,n,0);
										float chanelValue = tileColor[3];
										//chanelValues.push_back(chanelValue);
										chanelValues[rowindex+n] = chanelValue;
									}
								}

								//�����ڴ�TileBlendMap
								pixelPtr->unlock();
							}
							else
							{
								//�����ڴ�TileBlendMap
								HardwarePixelBufferSharedPtr pixelPtr = tileBlendTexMap->getBuffer();
								PixelBox tilePb = pixelPtr->lock(srcBox,HardwareBuffer::LockOptions::HBL_NORMAL);

								size_t width = tilePb.getWidth();
								size_t height = tilePb.getHeight();
								size_t pitch = tilePb.rowPitch;


								//����TileBlendMap��ÿ������,�����Ӧͨ��ֵ
								for (size_t m=0; m<width; ++m)
								{
									size_t rowindex = m*width;
									for (size_t n=0; n<height; ++n)
									{
										ColourValue tileColor = tilePb.getColourAt(m,n,0);
										float chanelValue = tileColor[layerIndex-1];
										//chanelValues.push_back(chanelValue);
										chanelValues[rowindex+n] = chanelValue;
									}
								}

								//�����ڴ�TileBlendMap
								pixelPtr->unlock();
							}
						}

						//��deque��swap�����Ż�����
						std::vector<float> tempDeque;
						layersPixels.insert(std::make_pair(instance->globleIndex,std::make_pair(globalLayerIndex,tempDeque)));
						layersPixels[instance->globleIndex].second.swap(chanelValues);
					}
				}

				//////////////////////////////////////////////////////////////////////////////
				//����������ͼ������д���µ�BlendMapTexure��
				int maxLayerNum = numMax*4;
				int curIndex = layersPixels.size()-1;
				//��������ͼ��
				for (int l=maxLayerNum-1; l>=0; --l,--curIndex)
				{
					bool found = false;
					layerPixelType::iterator itr = layersPixels.find(l);
					if ( itr == layersPixels.end() )
						continue;

					////�ɵ�ͼ������
					int oldLayerIndex = itr->second.first;

					//�ݴ浱ǰͼ������
					std::vector<float>& chanelValues = itr->second.second;

					//�����0������
					if (l==0)
					{
						//���firstIndex����0�����ô�����ΪĬ�ϵ�ͼ�ײ�Ϊ����Ϊ0����ͼ
						if (firstIndex == 0)
							continue;

						//��ס��0��BlendMapTex��Tile����
						HardwarePixelBufferSharedPtr blendMapTexPixelPtr = blendMapTexs[0]->getBuffer();
						PixelBox blendPb = blendMapTexPixelPtr->lock(desBox,HardwareBuffer::LockOptions::HBL_NORMAL);

						//��ס��1��BlendMapTex��Tile����
						HardwarePixelBufferSharedPtr blendMapTexPixelPtr1 = blendMapTexs[1]->getBuffer();
						PixelBox blendPb1 = blendMapTexPixelPtr1->lock(desBox,HardwareBuffer::LockOptions::HBL_NORMAL);

						//����BlendMapTex�����ݴ�С����һ����
						size_t width = blendPb.getWidth();
						size_t height = blendPb.getHeight();
						size_t pitch = blendPb.rowPitch;

						//����BlendMapTex��ÿ������
						for (size_t m=0; m<width; ++m)
						{
							size_t rowindex = m*width;
							for (size_t n=0; n<height; ++n)
							{
								//��ȡ��ǰ���ص�Ӧ��д���ֵ
								// float chanelValue = chanelValues.front();
								// chanelValues.pop_front();
								float chanelValue = chanelValues[rowindex+n];

								//ֻ��д��ֵ����0ʱ�Ŵ���
								if (chanelValue > 0.0f)
								{
									//�����ɵ�ͼ����Ϣ���ҵ�ԭ���ڵ�ǰͼ���±ߵ�ͼ�㣬����Щͼ��ͨ��ֵ��ȥ��ǰͼ��ͨ��ֵ(ʹ��ǰͼ��ɼ�)
									for ( itr=layersPixels.begin() ; itr!=layersPixels.end(); ++itr)
									{
										if (itr->second.first < oldLayerIndex && itr->first > l)
										{
											int uplayerIndex = itr->first;
											if (uplayerIndex < 5)
											{
												ColourValue blendColor = blendPb.getColourAt(m,n,0);
												blendColor[uplayerIndex-1] -= chanelValue;
												blendPb.setColourAt(blendColor,m,n,0);
											}
											else
											{
												ColourValue blendColor1 = blendPb1.getColourAt(m,n,0);
												blendColor1[(uplayerIndex-1)%4] -= chanelValue;
												blendPb1.setColourAt(blendColor1,m,n,0);
											}
										}
									}
								}
							}
						}

						//����BlendMapTex
						blendMapTexPixelPtr->unlock();
						blendMapTexPixelPtr1->unlock();						
					}
					else //�����1~7������
					{
						//�����1~4������
						if (l < 5)
						{
							//��ס��0��BlendMapTex��Tile����
							HardwarePixelBufferSharedPtr blendMapTexPixelPtr = blendMapTexs[0]->getBuffer();
							PixelBox blendPb = blendMapTexPixelPtr->lock(desBox,HardwareBuffer::LockOptions::HBL_NORMAL);

							//��ס��1��BlendMapTex��Tile����
							HardwarePixelBufferSharedPtr blendMapTexPixelPtr1 = blendMapTexs[1]->getBuffer();
							PixelBox blendPb1 = blendMapTexPixelPtr1->lock(desBox,HardwareBuffer::LockOptions::HBL_NORMAL);

							//����BlendMapTex�����ݴ�С����һ����
							size_t width = blendPb.getWidth();
							size_t height = blendPb.getHeight();
							size_t pitch = blendPb.rowPitch;

							//����BlendMapTex��ÿ������
							for (size_t m=0; m<width; ++m)
							{
								size_t rowindex = m*width;
								for (size_t n=0; n<height; ++n)
								{
									//��ȡ��ǰ���ص�Ӧ��д���ֵ
									// float chanelValue = chanelValues.front();
									// chanelValues.pop_front();
									float chanelValue = chanelValues[rowindex+n];

									//ֻ��д��ֵ����0ʱ�Ŵ���
									if (chanelValue)
									{
										//��ȡ��ǰͼ��Ӧ��д���ֵ
										ColourValue blendColor = blendPb.getColourAt(m,n,0);
										//д�뵱ǰͼ��ֵ
										blendColor[l-1] = chanelValue;

										//��ΪfirstIndex���������ǿ��д��ȥ�ģ�ԭ��ͼû�еģ�
										//���Ե���ǰ���ص�д��ֵ����0ʱҪ��firstIndex��Ӧ�Ĳ�����ϴ���
										if (l != firstIndex)
										{
											//�����ɵ�ͼ����Ϣ���ҵ�ԭ���ڵ�ǰͼ���±ߵ�ͼ�㣬����Щͼ��ͨ��ֵ��ȥ��ǰͼ��ͨ��ֵ(ʹ��ǰͼ��ɼ�)
											for ( itr=layersPixels.begin() ; itr!=layersPixels.end(); ++itr)
											{
												if (itr->second.first < oldLayerIndex && itr->first > l)
												{
													int uplayerIndex = itr->first;
													if (uplayerIndex < 5)
													{
														blendColor[uplayerIndex-1] -= chanelValue;
													}
													else
													{
														ColourValue blendColor1 = blendPb1.getColourAt(m,n,0);
														blendColor1[(uplayerIndex-1)%4] -= chanelValue;
														blendPb1.setColourAt(blendColor1,m,n,0);
													}
												}
											}

										}

										blendPb.setColourAt(blendColor,m,n,0);

									}
								}
							}

							blendMapTexPixelPtr->unlock();
							blendMapTexPixelPtr1->unlock();
						}
						else //�����5~7������
						{
							HardwarePixelBufferSharedPtr blendMapTexPixelPtr = blendMapTexs[1]->getBuffer();
							PixelBox blendPb = blendMapTexPixelPtr->lock(desBox,HardwareBuffer::LockOptions::HBL_NORMAL);

							HardwarePixelBufferSharedPtr blendMapTexPixelPtr0 = blendMapTexs[0]->getBuffer();
							PixelBox blendPb0 = blendMapTexPixelPtr0->lock(desBox,HardwareBuffer::LockOptions::HBL_NORMAL);

							size_t width = blendPb.getWidth();
							size_t height = blendPb.getHeight();
							size_t pitch = blendPb.rowPitch;

							for (size_t m=0; m<width; ++m)
							{
								size_t rowindex = m*width;
								for (size_t n=0; n<height; ++n)
								{
									// float chanelValue = chanelValues.front();
									// chanelValues.pop_front();
									float chanelValue = chanelValues[rowindex+n];

									if (chanelValue)
									{
										ColourValue blendColor = blendPb.getColourAt(m,n,0);
										if (l != firstIndex)
										{
											for ( itr=layersPixels.begin() ; itr!=layersPixels.end(); ++itr)
											{
												if (itr->second.first < oldLayerIndex && itr->first > l)
												{
													int uplayerIndex = itr->first;
													if (uplayerIndex < 5)
													{
														ColourValue blendColor0 = blendPb0.getColourAt(m,n,0);
														blendColor0[uplayerIndex-1] -= chanelValue;
														blendPb0.setColourAt(blendColor0,m,n,0);
													}
													else
													{
														blendColor[(uplayerIndex-1)%4] -= chanelValue;
													}
												}
											}

										}

										blendColor[(l-1)%4] = chanelValue;
										blendPb.setColourAt(blendColor,m,n,0);
									}
								}
							}

							blendMapTexPixelPtr->unlock();
							blendMapTexPixelPtr0->unlock();
						}
					}
				}
			}
		}


		//////////////////////////////////////////////////
		//��������BlendTexture
		for (int i=0; i<numMax; ++i)
		{
			TexturePtr blendMapTex = blendMapTexs[i];
			Image img;
			blendMapTex->convertToImage(img);

			std::ostringstream s;
			s << "BlendMap" << i << ".png";
			Str filename = s.str();
			Str filePath   = FileOp::getFullFilePath( tempPath, filename );
			img.save( filePath );


			///for test -------------------------------
			//std::ostringstream bs;
			//bs << "BlendMap" << i << ".bmp";
			//filename = bs.str();
			//filePath   = FileOp::getFullFilePath( tempPath, filename );
			//img.save( filePath );
			///--end for test

			if (blendMapTex.isNull()==false)
			{
				texMgr.remove( blendMapTexs[i]->getHandle() );
			}
		}

	}

}

