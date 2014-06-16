#include "StdAfx.h"
#include "SceneInfo.h"
#include "CoreManager.h"
#include "GlobalOptions.h"

namespace SceneEditor {
	void SceneEditor::SceneInfo::initialize()
	{
		IScene* scene = CoreManager::getInstance().getScene();
		if (scene)
		{
			TerrainDeclare decl = scene->getTerrainManager()->getConfig();
			System::Int32 chunkLength = decl.gridSideNumInChunk;
			System::Int32 chunkNum = decl.trunkIndexList.size();
			System::Int32 tileSize = decl.chunkDecl.gridSideNumInTile;
			System::Int32 gridSize = (System::Int32)decl.gridSize;
			System::Int32 minHeight = (System::Int32)decl.minHeight;
			System::Int32 maxHeight = (System::Int32)decl.maxHeight;
			System::Int32 mapHeight = maxHeight - minHeight;
			System::Double accurancy = mapHeight/pow(2.0,16);//pow(2.0,16)代表16bit格式图所能代表的最大像素变化值
			System::Int32 mapSize = chunkLength * (Int32)sqrt(float(chunkNum));

			System::String^ infos;
			System::String^ strMapNameEn = "地图英文名：EnglishName\n"; 
			System::String^ strMapNameCn = "地图中文名：中文名字\n"; 
			System::String^ strMapSize   = "地图大小：" + mapSize.ToString() + " × " + mapSize.ToString() +"格\n";
			infos += strMapSize;
			System::String^ strGridSize  = "每格边长：" + gridSize.ToString() + "米\n";
			infos += strGridSize;
			System::String^ strMinHeight  = "最低海拔：" + minHeight.ToString() + "米\n";
			infos += strMinHeight;
			System::String^ strMapHeight  = "地图总高：" + mapHeight.ToString() + "米\n";
			infos += strMapHeight;
			System::String^ strMaxHeight  = "最高海拔：" + maxHeight.ToString() + "米\n";
			infos += strMaxHeight;
			System::String^ strAccurancy  = "高度精度：" + accurancy.ToString() + "米\n";
			infos += strAccurancy;
			System::String^ strChunkNum  = "Chunk数量：" + chunkNum.ToString() + "块\n";
			infos += strChunkNum;
			System::String^ strTileSize  = "Tile大小：" + tileSize.ToString() + "格\n";
			infos += strTileSize;
			richTextBox1->Text = infos;
		}
	}

	void SceneInfo::closeForm()
	{
		FormSet::SceneInfo_form = nullptr;
	}
}