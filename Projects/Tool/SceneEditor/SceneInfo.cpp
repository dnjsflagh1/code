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
			System::Double accurancy = mapHeight/pow(2.0,16);//pow(2.0,16)����16bit��ʽͼ���ܴ����������ر仯ֵ
			System::Int32 mapSize = chunkLength * (Int32)sqrt(float(chunkNum));

			System::String^ infos;
			System::String^ strMapNameEn = "��ͼӢ������EnglishName\n"; 
			System::String^ strMapNameCn = "��ͼ����������������\n"; 
			System::String^ strMapSize   = "��ͼ��С��" + mapSize.ToString() + " �� " + mapSize.ToString() +"��\n";
			infos += strMapSize;
			System::String^ strGridSize  = "ÿ��߳���" + gridSize.ToString() + "��\n";
			infos += strGridSize;
			System::String^ strMinHeight  = "��ͺ��Σ�" + minHeight.ToString() + "��\n";
			infos += strMinHeight;
			System::String^ strMapHeight  = "��ͼ�ܸߣ�" + mapHeight.ToString() + "��\n";
			infos += strMapHeight;
			System::String^ strMaxHeight  = "��ߺ��Σ�" + maxHeight.ToString() + "��\n";
			infos += strMaxHeight;
			System::String^ strAccurancy  = "�߶Ⱦ��ȣ�" + accurancy.ToString() + "��\n";
			infos += strAccurancy;
			System::String^ strChunkNum  = "Chunk������" + chunkNum.ToString() + "��\n";
			infos += strChunkNum;
			System::String^ strTileSize  = "Tile��С��" + tileSize.ToString() + "��\n";
			infos += strTileSize;
			richTextBox1->Text = infos;
		}
	}

	void SceneInfo::closeForm()
	{
		FormSet::SceneInfo_form = nullptr;
	}
}