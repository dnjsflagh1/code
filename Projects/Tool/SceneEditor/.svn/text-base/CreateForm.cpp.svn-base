#include "StdAfx.h"
#include "CreateForm.h"
#include "GlobalOptions.h"
#include "CoreManager.h"
#include "Utility.h"
#include "XmlHelper.h"
#include "OperationManager.h"
#include "ITerrain.h"
#include <msclr\marshal_cppstd.h>

namespace SceneEditor {

	//-----------------------------------------------------
	void CreateForm::initialize()
	{
		//初始化单位长度可选值和默认值
		ComboBox_UnitLength->Items->Clear();
		ComboBox_UnitLength->Items->Add(1);
		ComboBox_UnitLength->Items->Add(2);
		ComboBox_UnitLength->SelectedIndex = 0;

		//初始化chunk数量可选值和默认值
		ComboBox_ChunkNum->Items->Clear();
		for (int i=1; i<=3; i++)
		{
			ComboBox_ChunkNum->Items->Add(i*i);
		}
		ComboBox_ChunkNum->SelectedIndex = 0;

		//初始化地图大小可选值和默认值
		ComboBox_MapSize->Items->Clear();
		for (int i=7; i<=10; i++)
		{
			ComboBox_MapSize->Items->Add(int(pow(2.0,i)));
		}
		ComboBox_MapSize->SelectedIndex = 1;		

		//初始化最低海拔可选值和默认值
		ComboBox_MinHeight->Items->Clear();
		ComboBox_MinHeight->Items->Add(-512);
		ComboBox_MinHeight->SelectedIndex = 0;

		//初始化最高海拔可选值和默认值
		ComboBox_MaxHeight->Items->Clear();
		//for (int i=3; i<=6; i++)
		//{
		//	ComboBox_MaxHeight->Items->Add(int(pow(2.0,i)));
		//}
		ComboBox_MaxHeight->Items->Add(512);
		ComboBox_MaxHeight->SelectedIndex = 0;

		//初始化Tile边长可选值
		ComboBox_TileSize->Items->Clear();
		ComboBox_TileSize->Items->Add(128);
		ComboBox_TileSize->Items->Add(256);
		ComboBox_TileSize->Items->Add(512);
		ComboBox_TileSize->SelectedIndex = 1;

		//设置默认批处理方式
		RadioButton_BigBatch->Checked = true;

		//设置默认地图类型
		RadioButton_SLGMap->Checked = true;
	}

	//-----------------------------------------------------
	void CreateForm::unInitialize()
	{

	}

	//-----------------------------------------------------
	void CreateForm::validateForm()
	{
		//获取地图名字
		System::String^ mapNameEn = TextBox_MapNameEN->Text->Trim();
		System::String^ mapNameCn = TextBox_MapNameCN->Text->Trim();

		//获取地图单位长度
		String^ str = ComboBox_UnitLength->SelectedItem->ToString();
		double unitLength = TypeConverter::StrToDouble(str);

		//获取地图chunk数量
		int    chunkNum = TypeConverter::StrToU32(ComboBox_ChunkNum->SelectedItem->ToString());

		//获取地图宽度(高度)
		int    mapSize = TypeConverter::StrToU32(ComboBox_MapSize->SelectedItem->ToString());

		//获取地图最高和最低值
		int    minHeight = TypeConverter::StrToInt(ComboBox_MinHeight->SelectedItem->ToString());
		int    maxHeight = TypeConverter::StrToInt(ComboBox_MaxHeight->SelectedItem->ToString());

		//获取选择的批次类型
		int batch = SMALLBATCH;
		if (RadioButton_BigBatch->Checked)
		{
			batch = BIGBATCH;
		}
		else if (RadioButton_SmallBatch->Checked)
		{
			batch = SMALLBATCH;
		}

		//获取选择的地图类型
		int mapType = SLG;
		if (RadioButton_SLGMap->Checked)
		{
			mapType = SLG;
		}else if (RadioButton_RPGMap->Checked)
		{
			mapType = RPG;
		}else if (RadioButton_IntegratedMap->Checked)
		{
			mapType = INTEGRATED;
		}

		if (System::String::IsNullOrEmpty(mapNameEn))
		{
			System::Windows::Forms::MessageBox::Show("地图英文名不能为空！");
			return;
		}

		if (System::String::IsNullOrEmpty(mapNameCn))
		{
			System::Windows::Forms::MessageBox::Show("地图中文名不能为空！");
			return;
		}

		///验证合法性
		if (System::Text::RegularExpressions::Regex::IsMatch(mapNameEn,"[^a-zA-Z_0-9]+"))
		{
			System::Windows::Forms::MessageBox::Show("地图英文名包含非法字符(只能包含英文字母、下划线和数字)！");
			return;
		}

		if (System::Text::RegularExpressions::Regex::IsMatch(mapNameCn,"[^\u4e00-\u9fa5_0-9]+"))
		{
			System::Windows::Forms::MessageBox::Show("地图中文名包含非法字符(自能包含中文、下划线和数字)!");
			return;
		}

		Close();
		closeForm();

		FormSet::main_form->clearAll();


		////////////////////////////////////////////////////////////////////////
		///根据获取的参数创建地图文件
		//128*128地图1个 chunk,1个 Tile
		//256*256地图1个 chunk,1个 Tile
		//512*512地图1个 chunk,4个 Tile
		//1024*1024地图4个 chunk,4个 Tile

		TerrainDeclare decl;
		TerrainChunkDeclare chunkDecl;
		decl.reset();
		decl.gridSize = (int)unitLength;
		if (mapSize == 1024)
		{
			decl.gridSideNumInChunk = 512;
			decl.trunkIndexList.clear();
			decl.trunkIndexList.push_back(VecI2(1,1));
			decl.trunkIndexList.push_back(VecI2(1,2));
			decl.trunkIndexList.push_back(VecI2(2,1));
			decl.trunkIndexList.push_back(VecI2(2,2));

			chunkDecl.gridSideNumInTile = decl.gridSideNumInChunk;
			chunkDecl.blendMapSizeInTile = chunkDecl.gridSideNumInTile;
			chunkDecl.gridSideNumInNode = decl.gridSideNumInChunk;
			decl.chunkDecl = chunkDecl;
		}
		else if (mapSize == 512)
		{
			decl.gridSideNumInChunk = 512;
			chunkDecl.gridSideNumInTile = decl.gridSideNumInChunk/2;
			chunkDecl.blendMapSizeInTile = chunkDecl.gridSideNumInTile;
			chunkDecl.gridSideNumInNode = decl.gridSideNumInChunk;
			decl.chunkDecl = chunkDecl;
		}
		else if (mapSize == 256)
		{
			decl.gridSideNumInChunk = 256;
			chunkDecl.gridSideNumInTile = decl.gridSideNumInChunk;
			chunkDecl.blendMapSizeInTile = chunkDecl.gridSideNumInTile;
			chunkDecl.gridSideNumInNode = decl.gridSideNumInChunk;
			decl.chunkDecl = chunkDecl;
		} 
		else if (mapSize == 128)
		{
			decl.gridSideNumInChunk = 128;
			chunkDecl.gridSideNumInTile = decl.gridSideNumInChunk;
			chunkDecl.blendMapSizeInTile = chunkDecl.gridSideNumInTile;
			chunkDecl.gridSideNumInNode = decl.gridSideNumInChunk;
			decl.chunkDecl = chunkDecl;
		} 
		decl.lightingMapSize = decl.gridSideNumInChunk;


		decl.maxHeight = maxHeight;
		decl.minHeight = minHeight;
		decl.heightScale = max(abs(maxHeight),abs(minHeight));

		String^ appPath = System::Windows::Forms::Application::StartupPath;
		FolderBrowserDialog^  folderBrowserDialog1 = gcnew FolderBrowserDialog();
		folderBrowserDialog1->SelectedPath = appPath + "\\Media\\Scene";
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
		{
			String^ filePath = folderBrowserDialog1->SelectedPath + "\\" + mapNameEn;
			FormSet::main_form->mLastFocusDir = filePath;

			Str path = StrToChar8(filePath).getChar8();

			CoreManager::getInstance().getScene()->getXmlSerializer()->createSceneContent(&decl, path);
			CoreManager::getInstance().getScene()->getXmlSerializer()->saveContent(path.c_str());

			refreshForm();
		}
	}

	//-----------------------------------------------------
	void CreateForm::refreshForm()
	{
		FormSet::main_form->loadTerrainTextureList();
		FormSet::main_form->loadWaterGroupList();
	}
	//-----------------------------------------------------
	void SceneEditor::CreateForm::closeForm()
	{
		FormSet::create_form = nullptr;
	}


};