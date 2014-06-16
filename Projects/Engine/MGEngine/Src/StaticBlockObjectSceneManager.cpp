#include "stdafx.h"
#include "BlockObject.h"
#include "StaticBlockObjectSceneManager.h"
#include "MGEngineUtility.h"
#include "Scene.h"

namespace MG
{

	/**********************************************************************************************/

	StaticBlockObjectSceneManager::StaticBlockObjectSceneManager(Scene* scene)
		:BlockObjectSceneManager(scene)
	{

	}

	//------------------------------------------------------------------------------------------
	StaticBlockObjectSceneManager::~StaticBlockObjectSceneManager()
	{

	}

	//------------------------------------------------------------------------------------------
	void StaticBlockObjectSceneManager::Init( Vec2 leftBottomPos, Vec2 rightUpPos, Flt regineGridSize )
	{
		TerrainManager* terrainManager = mScene->getTerrainManager();
		if(!terrainManager)
		{
			return;
		}

		TerrainChunk* terrainChunk = NULL;
		TerrainRegionGridData* gridData = NULL;
		TerrainRegion* terrainBlockRegion = NULL;
		Rect terrainChunkRect;
		VecU2 blockPoint;
		Vec2 terrainRegionIndex;

		Flt gridSize = terrainManager->getTerrainChunkBlockGridSize();
		//Int terrainWidth = terrainManager->getTerrainWidth();
		//Int terrainHeight = terrainManager->getTerrainHeight();
		//Int terrainBlockMapWidth = terrainWidth / gridSize;
		//Int terrainBlockMapHeight = terrainHeight / gridSize;

		Int terrainWidth = abs(rightUpPos.x - leftBottomPos.x);
		Int terrainHeight = abs(rightUpPos.y - leftBottomPos.y);
		Int terrainBlockMapWidth = terrainWidth / gridSize;
		Int terrainBlockMapHeight = terrainHeight / gridSize;


		UInt staticBlockMapWidth = terrainWidth / regineGridSize;
		if(staticBlockMapWidth * regineGridSize < terrainWidth)
		{
			staticBlockMapWidth++;
		}

		UInt staticBlockMapHeight = terrainHeight / regineGridSize;
		if(staticBlockMapHeight * regineGridSize < terrainHeight)
		{
			staticBlockMapHeight++;
		}

		mRegionGridList.createGrids(staticBlockMapWidth, staticBlockMapHeight, regineGridSize, leftBottomPos);

		std::vector<Rect> blockRectList;

		// º”‘ÿµÿ–Œ’œ∞≠
		for(UInt i = 0; i < terrainManager->getTerrainChunkCount(); ++i)
		{
			terrainChunk = terrainManager->getTerrainChunkByIndex(i);
			terrainChunkRect = terrainChunk->getBoundingRect();
			terrainRegionIndex = terrainChunk->getTerrainGroupIndex();

			terrainBlockRegion = terrainChunk->getTerrainRegion()->getTerrainBlockBaseRegion();

			for(Int z = terrainChunkRect.top; z < terrainChunkRect.bottom; ++z)
			{
				for(Int x = terrainChunkRect.left; x < terrainChunkRect.right; ++x)
				{
					gridData = terrainBlockRegion->getGridByWorldPosition(x, z);
					if(!gridData || gridData->mask == 0)
					{
						continue;
					}
					//mMapStaticBlock.convertWorldPositionToGridPoint(Vec2(x,z), blockPoint);
					//setStaticBlockByPoint(blockPoint.x, blockPoint.y, BLF_TERRAIN_BLOCK);
				}	
			}
		}
	}

	//------------------------------------------------------------------------------------------
	void StaticBlockObjectSceneManager::combinationBlockRect( UInt x, UInt y, std::vector<Rect>& blockRectList )
	{
		//Int worldGridWidth = mRegionGridList.getWorldGridWidth();
		//Int worldGridHeight = mRegionGridList.getWorldGridHeight();

		//Rect tempRect;
		//if(x - 1 >= 0)
		//{
		//	tempRect.left = x - 1;
		//}
		//else
		//{
		//	tempRect.left = x;
		//}

		//tempRect.right = x;

		//if(y - 1 >= 0)
		//{
		//	tempRect.top = y - 1;
		//}
		//else
		//{
		//	tempRect.top = y ;
		//}

		//tempRect.bottom = y;

		//Rect blockRect;
		//for(UInt i = 0; i < blockRectList.size(); ++i)
		//{
		//	if(!tempRect.Intersect(blockRect).isNUll)
		//	{
		//		
		//	}
		//}
	}
}