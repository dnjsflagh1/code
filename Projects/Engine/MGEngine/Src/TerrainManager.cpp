/******************************************************************************/
#include "stdafx.h"
#include "TerrainChunk.h"
#include "EngineMain.h"
#include "MGEngineUtility.h"
#include "Scene.h"
#include "TerrainManager.h"
#include "TerrainGroundSurface.h"
#include "TerrainWaterSurface.h"
#include "TerrainWaterMaterial.h"
#include "boost/tr1/tr1/tuple"
/******************************************************************************/

namespace MG
{

    Flt TerrainManager::MaxHeight = 10000;
    //-----------------------------------------------------------------------
    TerrainManager::TerrainManager(Scene* scene)
        :mScene(scene)
        ,mChunkSize(2)
        ,mChunkHalfSize(1)
		,mTerrainWidth(0)
		,mTerrainHeight(0)
		,mTerrainChunkBlockGridSize(0)
    {
        mSurfaceMgr                 = MG_NEW TerrainSurfaceManager( this ,mScene );
        mRegionMgr                  = MG_NEW TerrainRegionManager( this, mScene );

        mCenterPos                  = Vec3(0,0,0);
        mIndexCenterPos             = Vec3(0,0,0);
    }   
    //-----------------------------------------------------------------------
    TerrainManager::~TerrainManager()
    {
        destroyAllTerrainChunk();

        MG_SAFE_DELETE( mSurfaceMgr );
        MG_SAFE_DELETE( mRegionMgr );
    }

    //-----------------------------------------------------------------------
    Bool TerrainManager::update( Flt delta )
    {
        mSurfaceMgr->update( delta );
        updateTerrainChunk( delta );
        return true;
    }

    //-----------------------------------------------------------------------
    void TerrainManager::load(Str path)
    {
        //////////////////////////////////////////////////////////////////
		if ( EngineMain::getInstance().getMode() == EM_EDITOR )
		{
			if (!FileOp::isExistDirectory(path))
			{
				FileOp::createDirectory( path );
				Str terrainFilePath = path+"\\Terrain";
				if (!FileOp::isExistDirectory(terrainFilePath))
				{
					FileOp::createDirectory( terrainFilePath );
					path = terrainFilePath;
				}
			}
		}

        //////////////////////////////////////////////////////////////////

        loadTerrainChunk( path );
    }

    //-----------------------------------------------------------------------
    void TerrainManager::unLoad()
    {
        destroyAllTerrainChunk();
        mRegionMgr->clear();
    }

    //-----------------------------------------------------------------------
    void TerrainManager::applyRenderConfig()
    {
        std::map<U32 ,TerrainChunk*>::iterator iter =  mTerrainChunks.begin();
        for ( ;iter != mTerrainChunks.end();iter++ )
        {
            iter->second->getTerrainGroundSurface()->applyRenderConfig();
        }

        mSurfaceMgr->getTerrainWaterMaterial()->applyRenderConfig();
    }

    //-----------------------------------------------------------------------
    void TerrainManager::reset()
    {
        std::map<U32 ,TerrainChunk*>::iterator iter =  mTerrainChunks.begin();
        for ( ;iter != mTerrainChunks.end();iter++ )
        {
            iter->second->getTerrainGroundSurface()->reset();
            iter->second->getTerrainWaterSurface()->reset();
        }

        mSurfaceMgr->getTerrainWaterMaterial()->reset();
    }

    //-----------------------------------------------------------------------
    void TerrainManager::save(Str path)
    {
        //////////////////////////////////////////////////////////////////

        FileOp::cleanDirectory( path );

        //////////////////////////////////////////////////////////////////

        saveTerrainChunk( path );

        //////////////////////////////////////////////////////////////////
    }
	//-----------------------------------------------------------------------
	void TerrainManager::clip(Str path, RectF clipRect)
	{
		//////////////////////////////////////////////////////////////////

		if ( EngineMain::getInstance().getMode() != EM_EDITOR )
			return;
		
		//////////////////////////////////////////////////////////////////

		FileOp::cleanDirectory( path );

		if (!FileOp::isExistDirectory(path))
			FileOp::createDirectory(path);

		//新地图chunk数量(n)跟原地图的一致
		//新地图Tile数量跟原地图的一致
		TerrainDeclare& decl = mTerrainDeclare;
		TerrainChunkDeclare& chunkDecl = decl.chunkDecl;
		U32 chunkSideNum = (I32)sqrt(double(decl.trunkIndexList.size()));
		U32 chunkTileSideNum = decl.gridSideNumInChunk/decl.chunkDecl.gridSideNumInTile;
		if (chunkSideNum < 1)
			return;
		Dbl curMapSize = decl.gridSideNumInChunk*chunkSideNum;
		UInt curChunkSize = decl.gridSideNumInChunk;
		UInt curTileSize = decl.chunkDecl.gridSideNumInTile;
		UInt curNodeSize = decl.chunkDecl.gridSideNumInNode;
		UInt curBatchSize = decl.gridSideNumInBatch;
		Dbl curLightMapSize = decl.lightingMapSize;

		Dbl scale = abs(clipRect.width())/mTerrainWidth;
		Dbl newMapSize = curMapSize*scale;
		U32 newChunkSize = U32(newMapSize/chunkSideNum);
		UInt newTileSize = newChunkSize/chunkTileSideNum;
		UInt newBatchSize = newTileSize/2;
		UInt newBlendMapSizeInTile = newTileSize;
		UInt newNodeSize = newChunkSize;
		UInt newLightMapSize = curLightMapSize*scale;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//预先计算各需要的数据,将需要的信息存到一个tuple中,然后以图的名字为key将各图的信息保存一个map中;
		typedef std::tr1::tuple<PixelFormat,UInt,UInt> MapInfoType;
		std::map<Str,MapInfoType> mapInfos;

		//Normal map
		std::map<Str,PixelFormat> nameAndFormats;
		nameAndFormats.insert(std::pair<Str,PixelFormat>("HeightMap",PF_L16));
		nameAndFormats.insert(std::pair<Str,PixelFormat>("NormalMap",PF_BYTE_BGR));
		nameAndFormats.insert(std::pair<Str,PixelFormat>("WaterColorMap",PF_BYTE_BGRA));
		nameAndFormats.insert(std::pair<Str,PixelFormat>("WaterHeightMap",PF_L16));
		nameAndFormats.insert(std::pair<Str,PixelFormat>("WaterNormalMap",PF_BYTE_BGR));
		std::map<Str,PixelFormat>::iterator iter = nameAndFormats.begin();
		for (; iter!=nameAndFormats.end(); ++iter)
		{
			PixelFormat normalImageFormat = iter->second;
			UInt curChunkNormalImageSize = curChunkSize+1;
			UInt newChunkNormalImageSize = newChunkSize+1;
			MapInfoType normalImageInfo = std::tr1::make_tuple(normalImageFormat, curChunkNormalImageSize, newChunkNormalImageSize);
			mapInfos.insert(std::make_pair<Str,MapInfoType>(iter->first,normalImageInfo));
		}

		//TileMap
		for (int i=0; i<2; ++i)
		{
			std::ostringstream ts;
			ts << "TileTextureIndexMap" << i;
			Str tileImageName = ts.str();
			PixelFormat tileImageFormat = PF_BYTE_BGRA;
			UInt curChunkTileImageSize = curChunkSize/curTileSize;
			UInt newChunkTileImageSize = newChunkSize/newTileSize;
			MapInfoType tileImageInfo = std::tr1::make_tuple(tileImageFormat, curChunkTileImageSize, newChunkTileImageSize);
			mapInfos.insert(std::make_pair<Str,MapInfoType>(tileImageName,tileImageInfo));

			std::ostringstream bs;
			bs << "BlendMap" << i;
			Str blendImageName = bs.str();
			PixelFormat blendImageFormat = PF_BYTE_BGRA;
			UInt curChunkBlendImageSize = curChunkSize;
			UInt newChunkBlendImageSize = newChunkSize;
			MapInfoType blendImageInfo = std::tr1::make_tuple(blendImageFormat, curChunkBlendImageSize, newChunkBlendImageSize);
			mapInfos.insert(std::make_pair<Str,MapInfoType>(blendImageName,blendImageInfo));
		}

		//Light map
		Str lightImageName = "Lightmap";
		PixelFormat lightImageFormat = PF_L8;
		UInt curChunkLightImageSize = decl.lightingMapSize;
		UInt newChunkLightImageSize = decl.lightingMapSize*(newMapSize/curMapSize);
		MapInfoType lightImageInfo = std::tr1::make_tuple(lightImageFormat, curChunkLightImageSize, newChunkLightImageSize);
		mapInfos.insert(std::make_pair<Str,MapInfoType>(lightImageName,lightImageInfo));

		//BlockMap map
		Str blockImageName = "BlockMap";
		PixelFormat blockImageFormat = PF_L8;
		UInt curChunkBlockImageSize = curChunkSize;
		UInt newChunkBlockImageSize = curChunkSize*(newMapSize/curMapSize);
		MapInfoType blockImageInfo = std::tr1::make_tuple(blockImageFormat, curChunkBlockImageSize, newChunkBlockImageSize);
		mapInfos.insert(std::make_pair<Str,MapInfoType>(blockImageName,blockImageInfo));

		////已经取消------------------------------------------------------------------------
		////CustomRegion map
		//Str customRegionImageName = "CustomRegionMap";
		//PixelFormat customRegionImageFormat = PF_L8;
		//UInt curChunkCustomRegionImageSize = curChunkSize;
		//UInt newChunkCustomRegionImageSize = curChunkSize*(newMapSize/curMapSize);
		//MapInfoType customRegionImageInfo = std::tr1::make_tuple(customRegionImageFormat, \
		//	curChunkCustomRegionImageSize, newChunkCustomRegionImageSize);
		//mapInfos.insert(std::make_pair<Str,MapInfoType>(customRegionImageName,customRegionImageInfo));

		//WaterGroupInfo map
		//Str waterGroupInfoImageName = "WaterGroupInfoMap";
		//PixelFormat waterGroupInfoImageFormat = PF_BYTE_BGRA;
		//UInt curChunkWaterGroupInfoImageSize = curChunkSize/curBatchSize;
		//UInt newChunkWaterGroupInfoImageSize = newChunkSize/newBatchSize;
		//MapInfoType waterGroupInfoImageInfo = std::tr1::make_tuple(waterGroupInfoImageFormat,\
		//	curChunkWaterGroupInfoImageSize, newChunkWaterGroupInfoImageSize);
		//mapInfos.insert(std::make_pair<Str,MapInfoType>(waterGroupInfoImageName,waterGroupInfoImageInfo));

		////已取消
		////WaterLight map
		//Str waterLightImageName = "WaterLightMap";
		//PixelFormat waterLightImageFormat = PF_L8;
		//UInt curChunkWaterLightImageSize = curChunkSize;
		//UInt newChunkWaterLightImageSize = curChunkWaterLightImageSize*scale;
		//MapInfoType waterLightImageInfo = std::tr1::make_tuple(waterLightImageFormat,\
		//	curChunkWaterLightImageSize, newChunkWaterLightImageSize);
		//mapInfos.insert(std::make_pair<Str,MapInfoType>(waterLightImageName,waterLightImageInfo));
		


		////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//剪切地图
		std::map<Str,MapInfoType>::iterator mapInfoIter = mapInfos.begin();
		for (; mapInfoIter != mapInfos.end(); ++mapInfoIter)
		{
			Str imageName = mapInfoIter->first;
			MapInfoType mapInfo = mapInfoIter->second;
			PixelFormat imgFormat = std::tr1::get<0>(mapInfo);
			UInt curChunkImageSize  = std::tr1::get<1>(mapInfo);
			UInt curImageSize  = curChunkImageSize*chunkSideNum;
			UInt newChunkImageSize  = std::tr1::get<2>(mapInfo);
			UInt newImageSize  = newChunkImageSize*chunkSideNum;

			//新建一张大图用于存放各chunk合并的贴图
			TextureManager& texMgr = TextureManager::getSingleton();
			TexturePtr curMapTex = texMgr.getByName(imageName,ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			if (curMapTex.isNull())
			{   
				Int mipmap = MGEngineUtility::getMipMapNum( curImageSize );
				curMapTex = texMgr.createManual(imageName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
					TEX_TYPE_2D, curImageSize, curImageSize, mipmap, imgFormat, TU_STATIC | TU_AUTOMIPMAP);

				DYNAMIC_ASSERT_LOG( curMapTex.isNull() == false, "ClipMap HeightMapTex failed" );
			}

			//读取各chunk贴图并拷贝到新建的大贴图
			for (int row=0; row<chunkSideNum; ++row)
			{
				for (int col=0; col<chunkSideNum; ++col)
				{
					std::ostringstream directName;
					directName << row+1 << "_" << col+1;
					Str chunkPath = FileOp::getFullFilePath( path, directName.str() );
					if (FileOp::isExistDirectory(chunkPath))
					{
						std::ostringstream s;
						s << imageName << ".png";
						Str filename = s.str();
						if ( Ogre::ResourceGroupManager::getSingleton().resourceExists(chunkPath,filename) )
						{
							Ogre::Image img;
							img.load(filename, chunkPath);
							if (img.getWidth() != curChunkImageSize || img.getHeight() != curChunkImageSize)
								img.resize(curChunkImageSize, curChunkImageSize);

							PixelFormat f = img.getFormat();
							if ( f == imgFormat )
							{
								Image::Box destBox ;
								destBox.left = row*curChunkImageSize;
								destBox.top = (chunkSideNum-1-col)*curChunkImageSize;
								destBox.right = destBox.left+curChunkImageSize;
								destBox.bottom = destBox.top+curChunkImageSize;
								curMapTex->getBuffer()->blitFromMemory( img.getPixelBox(), destBox);
							}
						}
					}
				}
			}

			////-----------------------------------------------------------
			////begin test
			//Ogre::Image img;
			//curMapTex->convertToImage(img);

			//std::ostringstream s;
			//s << "Big" << imageName << ".png";
			//Str filename = s.str();
			//Str filePath   = FileOp::getFullFilePath( path, filename );
			//img.save( filePath );
			////--end test

			//从新的大贴图中拷贝数据
			std::ostringstream ns;
			ns << "New" << imageName << ".png";
			Str newMapName = ns.str();
			TexturePtr newMapTex = texMgr.getByName(newMapName,ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			if (newMapTex.isNull())
			{   
				Int mipmap = MGEngineUtility::getMipMapNum( newImageSize );
				newMapTex = texMgr.createManual(newMapName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
					TEX_TYPE_2D, newImageSize, newImageSize, mipmap, imgFormat, TU_STATIC | TU_AUTOMIPMAP);

				DYNAMIC_ASSERT_LOG( newMapTex.isNull() == false, "clipMap heightMapTex failed" );
			}

			Vec3 curMapTopLeftPos(mCenterPos.x-mTerrainWidth/2,mCenterPos.y,mCenterPos.z-mTerrainHeight/2);
			Dbl srcLeft = curImageSize*(abs(curMapTopLeftPos.x-clipRect.left)/mTerrainWidth);
			Dbl srcTop = curImageSize*(abs(curMapTopLeftPos.z-clipRect.top)/mTerrainHeight);
			if (srcLeft >1.0)
				srcLeft = ceil(srcLeft);
			if (srcTop >1.0)
				srcTop = ceil(srcTop);
			Image::Box srcBox = Image::Box(srcLeft,srcTop,srcLeft+newImageSize,srcTop+newImageSize);
			Image::Box destBox = Image::Box(0,0,newImageSize,newImageSize);
			newMapTex->getBuffer()->blit(curMapTex->getBuffer(),srcBox,destBox);

			////-----------------------------------------------------------
			////begin test
			//Ogre::Image newimg;
			//newMapTex->convertToImage(newimg);

			//Str newImgfilePath   = FileOp::getFullFilePath( path, newMapName );
			//newimg.save( newImgfilePath );
			////--end test

			if (curMapTex.isNull()==false)
			{
				texMgr.remove( curMapTex->getHandle() );
			}

			//切分
			for (int row=0; row<chunkSideNum; ++row)
			{
				for (int col=0; col<chunkSideNum; ++col)
				{
					std::ostringstream directName;
					directName << row+1 << "_" << col+1;
					Str chunkPath = FileOp::getFullFilePath( path, directName.str() );
					if (FileOp::isExistDirectory(chunkPath))
					{
						String chunkImageTexName = "chunkImageTemplate";
						TexturePtr chunkImageTex = texMgr.getByName(chunkImageTexName,ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
						if (chunkImageTex.isNull())
						{   
							Int mipmap = MGEngineUtility::getMipMapNum( newChunkImageSize );
							chunkImageTex = texMgr.createManual(chunkImageTexName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
								TEX_TYPE_2D, newChunkImageSize, newChunkImageSize, mipmap, imgFormat, TU_STATIC | TU_AUTOMIPMAP);

							DYNAMIC_ASSERT_LOG( chunkImageTex.isNull() == false, "clipMap heightMapTex failed" );
						}
						Dbl srcLeft = row*newChunkImageSize;
						Dbl srcTop = (chunkSideNum-1-col)*newChunkImageSize;
						Image::Box srcBox = Image::Box(srcLeft,srcTop,srcLeft+newChunkImageSize,srcTop+newChunkImageSize);
						Image::Box destBox = Image::Box(0,0,newChunkImageSize,newChunkImageSize);
						chunkImageTex->getBuffer()->blit(newMapTex->getBuffer(),srcBox,destBox);
						Ogre::Image img;
						chunkImageTex->convertToImage(img);

						std::ostringstream s;
						s << imageName << ".png";
						Str filename = s.str();
						Str filePath   = FileOp::getFullFilePath( chunkPath, filename );
						img.save( filePath );

						if (chunkImageTex.isNull()==false)
						{
							texMgr.remove( chunkImageTex->getHandle() );
						}
					}
				}
			}

			if (newMapTex.isNull()==false)
			{
				texMgr.remove( newMapTex->getHandle() );
			}
		}


		//更新裁剪后的chunk信息
		mTerrainDeclare.gridSideNumInChunk = newChunkSize;
		mTerrainDeclare.lightingMapSize = newLightMapSize;
		mTerrainDeclare.chunkDecl.blendMapSizeInTile = newBlendMapSizeInTile;
		mTerrainDeclare.chunkDecl.gridSideNumInNode = newNodeSize;
		mTerrainDeclare.chunkDecl.gridSideNumInTile = newTileSize;
		mTerrainDeclare.gridSideNumInBatch = newBatchSize;
	}

	//-----------------------------------------------------------------------
	void TerrainManager::_reorderTextureLayer(Str& path)
	{
		std::map<U32 ,TerrainChunk*>::iterator iter =  mTerrainChunks.begin();
		for ( ;iter != mTerrainChunks.end();iter++ )
		{
			Str tempPath = path + "//Terrain//" + iter->second->getDirectionName(); 
			iter->second->_reorderTextureLayer(tempPath);
		}
	}

    //-----------------------------------------------------------------------
    Bool TerrainManager::getMouseRayIntersection(Vec3& intersectPos,Bool isPrecise)
    {
        Bool result = false;

        Vec3 pos,dir;
        mScene->getActiveCamera()->getMouseViewportRay(pos,dir);
        result = getRayIntersection(pos, dir, intersectPos,isPrecise );

        return result;
    }

    //-----------------------------------------------------------------------
    Bool TerrainManager::getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise)
    {
        Vec3 intersectTempPos;
        Flt  lastIntersecteLenSqu;
        Flt  currIntersecteLenSqu;
        Bool isIntersected = false;
        std::map<U32 ,TerrainChunk*>::iterator iter =  mTerrainChunks.begin();
        for ( ;iter != mTerrainChunks.end();iter++ )
        {
            Ogre::Ray ray(Vector3(pos.x,pos.y,pos.z),Vector3(dir.x,dir.y,dir.z));
            TerrainChunk* chunk = iter->second;
            std::pair< bool, Real > intersect = ray.intersects( chunk->getBoundingBox() );
            if ( intersect.first )
            {
                if ( chunk->getTerrainGroundSurface()->getRayIntersection( pos, dir, intersectTempPos, isPrecise ) )
                {
                    if ( isPrecise == false )
                    {
                        intersectPos    = intersectTempPos;
                        return true;
                    }else
                    {
                        if ( isIntersected  )
                        {
                            // 和上次碰撞点比较
                            // 取距离离射线点最近的点
                            currIntersecteLenSqu = (pos - intersectTempPos).lengthSquare();

                            if ( currIntersecteLenSqu < lastIntersecteLenSqu )
                            {
                                intersectPos            = intersectTempPos;
                                lastIntersecteLenSqu    = currIntersecteLenSqu;
                            }
                        }else
                        {
                            intersectPos            = intersectTempPos;
                            lastIntersecteLenSqu    = (pos - intersectPos).lengthSquare();
                        }

                        isIntersected = true;
                    }
                } 
            }
        }

        return isIntersected;
    }

    //-----------------------------------------------------------------------
    Bool TerrainManager::getStickHeight( Vec2 worldPos , Flt& height )
    {
        height = 0;
        TerrainChunk* chunk = getTerrainChunkByWorldPos( worldPos );
        if ( chunk )
        {
            height = chunk->getTerrainGroundSurface()->getHeightAtWorldPosition( worldPos.x, worldPos.y );
            return true;
        }
        return false;
    }

    //-----------------------------------------------------------------------
    U32 TerrainManager::getTerrainChunkUID( I8 x, I8 y )
    {
        U16 ux = x + 128;
        U16 uy = y + 128;
        U32 uid = ux * 1000 +  uy;
        return uid;
    }

    //-----------------------------------------------------------------------
    TerrainChunk* TerrainManager::createTerrainChunk( I8 x, I8 y, TerrainChunkDeclare& decl )
    {
        U32 uid = getTerrainChunkUID( x, y );
        TerrainChunk* chunk = NULL;
        std::map<U32 ,TerrainChunk*>::iterator iter =  mTerrainChunks.find( uid );
        if ( iter != mTerrainChunks.end() )
        {
            chunk = iter->second;
        }else
        {
            Vec2 indexPos       = Vec2(x,y);
            mChunkSize          = mTerrainDeclare.gridSideNumInChunk * mTerrainDeclare.gridSize;
            mChunkHalfSize      = mChunkSize * 0.5;
            Vec2 worldCenterPos;
            
            if ( x > 0 )
                worldCenterPos.x    = x * mChunkSize - mChunkHalfSize ;
            else
            if ( x < 0 )
                worldCenterPos.x    = x * mChunkSize + mChunkHalfSize ;
            else
                DYNAMIC_ASSERT( false );
            
            y = -y;
            if ( y > 0 )
                worldCenterPos.y    = y * mChunkSize - mChunkHalfSize ;
            else
            if ( y < 0 )
                worldCenterPos.y    = y * mChunkSize + mChunkHalfSize ;
            else
                DYNAMIC_ASSERT( false );

            chunk = MG_NEW TerrainChunk( this, mScene, indexPos, worldCenterPos, decl );

            mTerrainChunks[uid] = chunk;
        }

        return chunk;
    }

    //-----------------------------------------------------------------------
    TerrainChunk* TerrainManager::getTerrainChunk( I8 x, I8 y )
    {
        U32 uid = getTerrainChunkUID( x, y );
        std::map<U32 ,TerrainChunk*>::iterator iter =  mTerrainChunks.find( uid );
        if ( iter != mTerrainChunks.end() )
        {
            return iter->second;
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    void TerrainManager::destroyAllTerrainChunk()
    {
        std::map<U32 ,TerrainChunk*>::iterator iter =  mTerrainChunks.begin();
        for ( ;iter != mTerrainChunks.end();iter++ )
        {
            MG_SAFE_DELETE( iter->second );
        }
        mTerrainChunks.clear();
    }

    //-----------------------------------------------------------------------
    void TerrainManager::loadTerrainChunk(Str path)
    {
		Rect minRect;
		Rect maxRect;

		Rect tempRect;

        std::map<U32 ,TerrainChunk*>::iterator iter =  mTerrainChunks.begin();

        UInt total = mTerrainChunks.size();
        UInt index = 0;
        ResourceLoadListener* listener = mScene->getResourceLoadListener();

        for ( ;iter != mTerrainChunks.end();iter++,index++ )
        {
            if ( listener )
            {
                listener->preLoadTerrainChunk( index, total );
            }

            iter->second->load( path );

            if ( listener )
            {
                listener->postLoadTerrainChunk( index, total );
            }

			tempRect = iter->second->getBoundingRect();

			if(iter == mTerrainChunks.begin() || (tempRect.top <= minRect.top && tempRect.left <= minRect.left))
			{
				minRect = tempRect;
				mTerrainChunkBlockGridSize = iter->second->getTerrainRegion()->getTerrainBlockBaseRegion()->getGridSize();
			}

			if(iter == mTerrainChunks.begin() || (tempRect.top >= maxRect.top && tempRect.left >= maxRect.left))
			{
				maxRect = tempRect;
			}
        }

		mTerrainWidth = abs(minRect.left - maxRect.right);
		mTerrainHeight = abs(minRect.top - maxRect.bottom);
		setCenterPosition(Vec3((minRect.left + maxRect.right) / 2, 0, (minRect.top + maxRect.bottom) / 2));
    }

    //-----------------------------------------------------------------------
    void TerrainManager::saveTerrainChunk(Str path)
    {
        std::map<U32 ,TerrainChunk*>::iterator iter =  mTerrainChunks.begin();
        for ( ;iter != mTerrainChunks.end();iter++ )
        {
            iter->second->save( path );
        }
    }

    //-----------------------------------------------------------------------
    void TerrainManager::unLoadTerrainChunk()
    {
        std::map<U32 ,TerrainChunk*>::iterator iter =  mTerrainChunks.begin();
        for ( ;iter != mTerrainChunks.end();iter++ )
        {
            iter->second->unLoad();
        }
    }

    //-----------------------------------------------------------------------
    void TerrainManager::updateTerrainChunk( Flt delta )
    {
        std::map<U32 ,TerrainChunk*>::iterator iter =  mTerrainChunks.begin();
        for ( ;iter != mTerrainChunks.end();iter++ )
        {
            iter->second->update( delta );
        }
    }

    //-----------------------------------------------------------------------
    UInt TerrainManager::getTerrainChunkCount()
    {
        return mTerrainChunks.size();
    }

    //-----------------------------------------------------------------------
    TerrainChunk* TerrainManager::getTerrainChunkByIndex(UInt index)
    {
        if ( mTerrainChunks.size() == 0 )
            return NULL;
        
        if (index>mTerrainChunks.size() - 1)
            return NULL;
        
        std::map<U32 ,TerrainChunk*>::iterator iter =  mTerrainChunks.begin();
        std::advance(iter, index);
        
        if ( iter == mTerrainChunks.end() )
            return NULL;
        
        return iter->second;
    }

    //-----------------------------------------------------------------------
    TerrainChunk* TerrainManager::getTerrainChunkByWorldPos( Vec2 worldPos )
    {
        Vec2 indexPos;

        if ( worldPos.x > 0 )
            indexPos.x = Int(( worldPos.x  - mIndexCenterPos.x ) / mChunkSize) + 1; 
        else
            indexPos.x = Int(( worldPos.x  - mIndexCenterPos.x ) / mChunkSize) - 1;

        if ( worldPos.y > 0 )
            indexPos.y = Int(( worldPos.y  - mIndexCenterPos.z ) / mChunkSize) + 1; 
        else
            indexPos.y = Int(( worldPos.y  - mIndexCenterPos.z ) / mChunkSize) - 1;
        indexPos.y = -indexPos.y;

        return getTerrainChunk( indexPos.x, indexPos.y );

    }

	//-----------------------------------------------------------------------
	Int TerrainManager::getTerrainWidth()
	{
		return mTerrainWidth;
	}
	
	//-----------------------------------------------------------------------
	Int TerrainManager::getTerrainHeight()
	{
		return mTerrainHeight;
	}

	//-----------------------------------------------------------------------
	Flt TerrainManager::getTerrainChunkBlockGridSize()
	{
		return mTerrainChunkBlockGridSize;
	}

}

