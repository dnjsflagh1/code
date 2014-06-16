#include "StdAfx.h"
#include "GlobalOptions.h"
#include "Utility.h"
#include "MapLoadForm.h"
#include "ArtMapResCsv.h"
#include "MapListCsv.h"

namespace GameMapEditor {
	
	//-----------------------------------------------------------------------
	void MapLoadForm::initialize()
	{
	}
	//-----------------------------------------------------------------------
	void MapLoadForm::unInitialize()
	{

	}
	//-----------------------------------------------------------------------
	void MapLoadForm::openForm()
	{
		BEGINDELEGATE(MapLoadForm,openForm)
		ENDDELEGATE

		loadMapList();

		map_info_tree_view->Enabled = true;

		//默认选中第一项
		if (map_info_tree_view->Nodes->Count > 0)
		{
			map_info_tree_view->SelectedNode = map_info_tree_view->Nodes[0]->Nodes[0]; 
		}

		this->CenterToScreen();
		this->ShowDialog();
	}
	//-----------------------------------------------------------------------
	void MapLoadForm::closeForm()
	{
		BEGINDELEGATE(MapLoadForm,closeForm)
		ENDDELEGATE

		//重置地图树形结构。
		map_info_tree_view->Nodes->Clear();
		map_info_tree_view->Enabled = false;
		this->Close();
	}
	//-----------------------------------------------------------------------
	void MapLoadForm::loadMapList()
	{
		BEGINDELEGATE(MapLoadForm,loadMapList)
		ENDDELEGATE

		//初始化地图读取树形结构。
		////////////////////////////////////////////////////////////
		map_info_tree_view->Nodes->Clear();
		////////////////////////////////////////////////////////////

		//获取MapList指针
		std::map<MapIdType, MapListCsvInfo*>* mapList = MapListCsv::getInstance().getList();

		
		typedef std::map<Str16,std::vector<MapListCsvInfo*>> MapGroupType;
		MapGroupType mapGroup;
		//根据MapGoupName对mapList的内容分组
		if ( mapList )
		{
			std::map<MapIdType, MapListCsvInfo*>::iterator iter = mapList->begin();
			for ( ; iter!=mapList->end(); ++iter )
			{
				MapListCsvInfo* mapInfo = iter->second;
				if ( !mapInfo )
					continue;

				MapGroupType::iterator iter = mapGroup.find(mapInfo->mapGroupName);
				if (iter == mapGroup.end())
				{
					std::vector<MapListCsvInfo*> tempList;
					tempList.push_back(mapInfo);
					mapGroup.insert(std::make_pair(mapInfo->mapGroupName, tempList));
				}
				else
				{
					std::vector<MapListCsvInfo*>& tempList = iter->second;
					tempList.push_back(mapInfo);
				}
			}
		}

		//遍历mapGroup
		MapGroupType::iterator iter = mapGroup.begin();
		for (; iter!= mapGroup.end(); ++iter)
		{
			const Str16& groupName = iter->first;
			const std::vector<MapListCsvInfo*>& tempList = iter->second;

			String^ treeNodeName = TypeConverter::Char16ToStr( groupName.c_str() );
			TreeNode^ currTreeNode = gcnew TreeNode(treeNodeName);

			Str16 node_desc = groupName;

			currTreeNode->Text  = TypeConverter::Char16ToStr(node_desc.c_str());
			map_info_tree_view->Nodes->Add( currTreeNode );

			//遍历每个mapGroup里的mapInfo
			std::vector<MapListCsvInfo*>::const_iterator infoIter = tempList.begin();
			for (; infoIter!=tempList.end(); ++infoIter)
			{
				MapListCsvInfo* mapInfo = *infoIter;
				if ( !mapInfo )
					continue;

				const ArtMapResCsvInfo* mapResInfo = ArtMapResCsv::getInstance().getArtMapResInfoById(mapInfo->artMapResId);
				if ( !mapResInfo )
					continue;

				///添加组成员
				String^ childNodeName = "MapListCsvNode" + TypeConverter::IntToStr( mapInfo->mapListId );
				TreeNode^ childTreeNode = gcnew TreeNode(childNodeName);
				currTreeNode->Nodes->Add( childTreeNode );
				Str16 node_desc = mapInfo->mapName + L"  " + mapInfo->mapText;

				childTreeNode->Text  = TypeConverter::Char16ToStr(node_desc.c_str());
				childTreeNode->Tag   = TypeConverter::IntToStr(mapInfo->mapListId);
			}
		}


		////遍历mapListCsv
		//std::map<MapIdType, MapListCsvInfo*>* mapList = MapListCsv::getInstance().getList();
		//if ( mapList )
		//{
		//	for ( std::map<MapIdType, MapListCsvInfo*>::iterator iter = mapList->begin(); iter != mapList->end() ; iter++ )
		//	{
		//		MapListCsvInfo* mapInfo = iter->second;
		//		if ( !mapInfo )
		//			continue;

		//		const ArtMapResCsvInfo* mapResInfo = ArtMapResCsv::getInstance().getArtMapResInfoById(mapInfo->artMapResId);
		//		if ( !mapResInfo )
		//			continue;

		//		///添加分组名
		//		String^ treeNodeName = "MapGroupNode" + TypeConverter::Char16ToStr( mapInfo->mapGroupName.c_str() );//"MapListCsvNode" + TypeConverter::IntToStr( mapInfo->mapListId );
		//		cli::array<TreeNode^>^ foundNodes = map_info_tree_view->Nodes->Find(treeNodeName,false);
		//		TreeNode^ currTreeNode;
		//		if (foundNodes->Length > 0)
		//			currTreeNode = foundNodes[0];
		//		else
		//		{
		//			currTreeNode = gcnew TreeNode(treeNodeName);

		//			Str16 node_desc = mapInfo->mapGroupName;

		//			currTreeNode->Text  = TypeConverter::Char16ToStr(node_desc.c_str());
		//			currTreeNode->Tag   = TypeConverter::Char16ToStr(node_desc.c_str());
		//			map_info_tree_view->Nodes->Add( currTreeNode );					
		//		}

		//		///添加组成员
		//		String^ childNodeName = "MapListCsvNode" + TypeConverter::IntToStr( mapInfo->mapListId );
		//		TreeNode^ childTreeNode = gcnew TreeNode(childNodeName);
		//		Str16 node_desc = mapInfo->mapName + L"  " + mapInfo->mapText;

		//		childTreeNode->Text  = TypeConverter::Char16ToStr(node_desc.c_str());
		//		childTreeNode->Tag   = TypeConverter::IntToStr(mapInfo->mapListId);
		//		currTreeNode->Nodes->Add( childTreeNode );

		//		
		//	}
		//}
	}
	//-----------------------------------------------------------------------
	void MapLoadForm::prepareLoadingMap()
	{
		BEGINDELEGATE(MapLoadForm,prepareLoadingMap)
		ENDDELEGATE

		mCurrMapID = 0;

		std::map<MapIdType, MapListCsvInfo*>* mapList = MapListCsv::getInstance().getList();
		if ( !mapList )
			return;
		
		if ( map_info_tree_view->SelectedNode != nullptr &&
			map_info_tree_view->SelectedNode->Tag != nullptr )
		{
			//获得选中的地图信息
			I32 mapId = TypeConverter::StrToInt(map_info_tree_view->SelectedNode->Tag->ToString());

			std::map<MapIdType, MapListCsvInfo*>::iterator iter = mapList->find((MapIdType)mapId);
			if ( iter == mapList->end() || iter->second == NULL )
				return;

			ArtMapResCsvInfo* mapInfo = ArtMapResCsv::getInstance().getArtMapResInfoById((ArtMapResIdType)iter->second->artMapResId);

			if ( mapInfo )
			{
				//在面板上显示信息
				Str16 msg;
				Str16 spliter = L"\n";

				msg += L"模版地图名称:";
				msg += ( mapInfo->name + spliter );

				msg += L"美术资源路径";
				msg += spliter;
				msg += ( mapInfo->BaseFilePath + spliter );

				msg += L"策划资源路径";
				msg += spliter;
				msg += ( iter->second->filePath + L"\\\\" + iter->second->fileName);

				prepare_load_map_text->Text = TypeConverter::Char16ToStr(msg.c_str());

				//记录了当前选中地图
				mCurrMapID = (I32)iter->second->mapListId;
			}
		}
	}
	//-----------------------------------------------------------------------
	void MapLoadForm::loadMap()
	{
		closeForm();

		if (mCurrMapID )
		{
			std::map<MapIdType, MapListCsvInfo*>* mapList = MapListCsv::getInstance().getList();

			if ( !mapList )
				return;

			std::map<MapIdType, MapListCsvInfo*>::iterator iter = mapList->find((MapIdType)mCurrMapID);
			if ( iter == mapList->end() || iter->second == NULL )
				return;
			
			FormSet::main_form->loadScene(mCurrMapID);
		}

		mCurrMapID = 0;
	}	
}

