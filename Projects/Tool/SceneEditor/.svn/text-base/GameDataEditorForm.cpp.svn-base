#include "StdAfx.h"
#include "GameDataEditorForm.h"
#include "GlobalOptions.h"
#include "CoreManager.h"
#include "Utility.h"
#include "XmlHelper.h"
#include "OperationManager.h"
//#include "MapObjectInfo.h"
//#include "MapResourceInfo.h"
//#include "DistrictObjectInfo.h"
//#include "DistrictTemplateInfo.h"
//#include "PlaceObjectInfo.h"
//#include "PlaceTemplateInfo.h"

namespace SceneEditor {

    //-----------------------------------------------------------------------
    void GameDataEditorForm::initialize()
    {
		m_SelCityArtID = 0;
		loadArtResList();
		loadDistObjList();
		loadMapObjectList();
		loadPlaceObjectList();
    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::unInitialize()
    {

    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::closeForm()
    {
        FormSet::gameData_form = nullptr;
    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::load()
    {
        clearAll();
        CoreManager::getInstance().loadGameFile();
        refresh();
    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::clearAll()
    {
        clearMapUI();
        clearPlaceUI();
    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::refresh()
    {
        loadArtResList();
        loadPlaceObjectList();
    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::loadArtResList()
    {
#if 0
		Art_Res_list->Items->Clear();
		MapResourceInfo* MapResInfo = NULL;
	   
		for(int i = 0; i < MapResourceInfos::getInstance().getMapResCnt(); ++i)
		{
			MapResInfo = MapResourceInfos::getInstance().getMapResourceInfoByIndex(i);
			if(MapResInfo)
			{
				ListViewItem ^ item = gcnew ListViewItem;
				String^ str = TypeConverter::U64ToStr(MapResInfo->id);
				Map_ArtRes_Edit->Items->Add(str);
				item->SubItems->default[0]->Text = str;
				item->SubItems->default[0]->Name = "ArtResCol_ID";
				str = TypeConverter::Char16ToStr(MapResInfo->filePath.c_str());
				item->SubItems->Add(str)->Name    = "ArtResCol_Path";

				Art_Res_list->Items->Add(item);
			}
		}
#endif
    }
    //----------------------------------------------------------------------- 
	void GameDataEditorForm::loadDistObjList()
	{
#if 0
		Map_District_List->Items->Clear();

		DistrictObjectInfo* districtobjinfo = NULL;

		for(int i = 0; i < DistrictObjectInfos::getInstance().getDistrictObjInfoCnt(); ++i)
		{
			districtobjinfo = DistrictObjectInfos::getInstance().getDistrictObjInfo(i);
			if(districtobjinfo)
			{
				ListViewItem ^ item = gcnew ListViewItem;
				String^ str = TypeConverter::U64ToStr(districtobjinfo->id);
				Map_Distrct_ID_Edit->Items->Add(str);
				MapPlace_District_Id_Edit->Items->Add(str);
				item->SubItems->default[0]->Text = str;
				item->SubItems->default[0]->Name = "MapDistrictCol_ID";
				str = TypeConverter::Char16ToStr(districtobjinfo->name.c_str());
				item->SubItems->Add(str)->Name    = "MapDistrictCol_Name";

				Map_District_List->Items->Add(item);
			}
		}

		Map_find_type_edit->Items->Add("世界");
		Map_find_type_edit->Items->Add("国");
		Map_find_type_edit->Items->Add("州");
		Map_find_type_edit->Items->Add("郡");
		Map_find_type_edit->Items->Add("县");
		Map_find_type_edit->Items->Add("乡");

		comboBox3->Items->Add("世界");
		comboBox3->Items->Add("国");
		comboBox3->Items->Add("州");
		comboBox3->Items->Add("郡");
		comboBox3->Items->Add("县");
		comboBox3->Items->Add("乡");
#endif
	}
	//-----------------------------------------------------------------------
    void GameDataEditorForm::loadMapObjectList()
    {
#if 0
		map_load_list->Items->Clear();

		MapObjectInfo* mapobjinfo= NULL;

		std::map<IdType, CMapObject*>* mapObjInfoList = CoreManager::getInstance().mMapObjInfoList;
		if(!mapObjInfoList)
		{
			return;
		}

		for (CoreManager::MapObjInfoIt it = mapObjInfoList->begin(); it != mapObjInfoList->end(); ++it)
		{
			mapobjinfo = it->second;
			if(mapobjinfo)
			{
				//String^ str = Utility::Char8ToStr("sdsd");

				//ListViewItem ^ item = gcnew ListViewItem;
				//item->SubItems->default[0]->Text = str;
				//item->SubItems->default[0]->Name = "MapPlaceCol_ID";
				//str = Utility::Char16ToStr(mapobjinfo->MapObjName);
				//item->SubItems->Add(str)->Name    = "MapPlaceCol_Name";
				//str = Utility::Char16ToStr(mapobjinfo->);
				//item->SubItems->Add(str)->Name    = "MapPlaceCol_SceneObjectName";
				//str = Utility::Char16ToStr(mapobjinfo->MapObjName);
				//item->SubItems->Add(str_formatType)->Name    = "MapPlaceCol_DistrictID";

				ListViewItem ^ item = gcnew ListViewItem;
				String^ str = TypeConverter::U64ToStr(mapobjinfo->id);
				item->SubItems->default[0]->Text = str;
				item->SubItems->default[0]->Name = "MapCol_ID";
				MapPlace_MapID_Edit->Items->Add(str);
				str = TypeConverter::Char16ToStr(mapobjinfo->name.c_str());
				item->SubItems->Add(str)->Name    = "MapCol_Name";
				str = TypeConverter::U64ToStr(mapobjinfo->districtObjectId);
				item->SubItems->Add(str)->Name    = "MapCol_DistrictID";
				//str = TypeConverter::IntToStr(mapobjinfo->MapObjType);
				//item->SubItems->Add(str)->Name    = "MapPlaceCol_Type";


				//Map_District_List->Items->Add(item);
				map_load_list->Items->Add(item);
			}
		}
#endif
    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::searchMapObjectList()
    {
#if 0
		Bool IsDistIdNull = false;
		//Bool IsDistlvNull = false;
		MapObjectInfo*  mapobjinfo = NULL;
		DistrictObjectInfo* districtobjinfo = NULL;
		DistrictTemplateInfo* districtinfo = NULL;

		if (String::IsNullOrEmpty(Map_find_district_id_edit->Text) /*|| Map_find_district_id_edit->Text == L""*/) 
		{
			IsDistIdNull = true;
		}

		Int lvl = 0;
		if(Map_find_type_edit->Text == "世界")
		{
			lvl = 1;
		}
		else if(Map_find_type_edit->Text == "国")
		{
			lvl = 2;
		}
		else if(Map_find_type_edit->Text == "州")
		{
			lvl = 3;
		}
		else if(Map_find_type_edit->Text == "郡")
		{
			lvl = 4;
		}
		else if(Map_find_type_edit->Text == "县")
		{
			lvl = 5;
		}
		else if(Map_find_type_edit->Text == "乡")
		{
			lvl = 6;
		}

		//if(String::IsNullOrEmpty(Map_find_type_edit->SelectedText))
		//{
		//	IsDistlvNull = true;
		//}
		if(IsDistIdNull)
		{
			map_load_list->Items->Clear();

			std::map<IdType, MapObjectInfo*>* mapObjInfoList = CoreManager::getInstance().mMapObjInfoList;
			if(!mapObjInfoList)
			{
				return;
			}


			for(CoreManager::MapObjInfoIt it = mapObjInfoList->begin(); it != mapObjInfoList->end(); ++it)
			{
				mapobjinfo = it->second;

				if(mapobjinfo)
				{
					districtobjinfo = DistrictObjectInfos::getInstance().getDistrictObjInfo(mapobjinfo->districtObjectId);
					if(districtobjinfo)
					{
						districtinfo = DistrictInfos::getInstance().getDistrictInfo(districtobjinfo->templateId);
						if(districtinfo && districtinfo->rank == lvl)
						{
							ListViewItem ^ item = gcnew ListViewItem;
							String^ str = TypeConverter::U64ToStr(mapobjinfo->id);
							item->SubItems->default[0]->Text = str;
							item->SubItems->default[0]->Name = "MapCol_ID";
							str = TypeConverter::Char16ToStr(mapobjinfo->name.c_str());
							item->SubItems->Add(str)->Name    = "MapCol_Name";
							str = TypeConverter::U64ToStr(mapobjinfo->districtObjectId);
							item->SubItems->Add(str)->Name    = "MapCol_DistrictID";
							//str = TypeConverter::IntToStr(mapobjinfo->MapObjType);
							//item->SubItems->Add(str)->Name    = "MapPlaceCol_Type";


							map_load_list->Items->Add(item);
						}
					}
				}
				
			}
					
		}
		else
		{
			IdType id = TypeConverter::StrToU64(Map_find_district_id_edit->Text);
			districtobjinfo = DistrictObjectInfos::getInstance().getDistrictObjInfo(id/*mapobjinfo->DistObjId*/);
			map_load_list->Items->Clear();
			if(districtobjinfo)
			{
				std::map<IdType, MapObjectInfo*>* mapObjInfoList = CoreManager::getInstance().mMapObjInfoList;
				if(!mapObjInfoList)
				{
					return;
				}

				for(CoreManager::MapObjInfoIt it = mapObjInfoList->begin(); it != mapObjInfoList->end(); ++it)
				{
					mapobjinfo = it->second;

					if(mapobjinfo && mapobjinfo->districtObjectId == id)
					{
						ListViewItem ^ item = gcnew ListViewItem;
						String^ str = TypeConverter::U64ToStr(mapobjinfo->id);
						item->SubItems->default[0]->Text = str;
						item->SubItems->default[0]->Name = "MapCol_ID";
						str = TypeConverter::Char16ToStr(mapobjinfo->name.c_str());
						item->SubItems->Add(str)->Name    = "MapCol_Name";
						str = TypeConverter::U64ToStr(mapobjinfo->districtObjectId);
						item->SubItems->Add(str)->Name    = "MapCol_DistrictID";
						//str = TypeConverter::IntToStr(mapobjinfo->MapObjType);
						//item->SubItems->Add(str)->Name    = "MapPlaceCol_Type";

						map_load_list->Items->Add(item);
					}
				}
			}

		}
				
#endif
    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::saveSelMapObject()
    {
#if 0
		if(String::IsNullOrEmpty(Map_ID_Edit->Text) || Map_ID_Edit->Text == "XXX")
			return;

		IdType id = TypeConverter::StrToU64(Map_ID_Edit->Text);
		std::map<IdType, MapObjectInfo*>* mapObjInfoList = CoreManager::getInstance().mMapObjInfoList;
		if(!mapObjInfoList)
		{
			return;
		}

		MapObjectInfo* mapobjinfo = (*mapObjInfoList)[id];
		if(mapobjinfo)
		{
			id = TypeConverter::StrToU32(Map_Distrct_ID_Edit->Text);
			mapobjinfo->districtObjectId = id;
			id = TypeConverter::StrToU32(Map_ArtRes_Edit->Text);
			mapobjinfo->artMapResId = id;
			CChar16* title = TypeConverter::StrToChar16(Map_Name_Edit->Text);
			mapobjinfo->name = title;
			title = TypeConverter::StrToChar16(Map_Test_Edit->Text);
			mapobjinfo->description = title;
			//title = TypeConverter::StrToChar16(Map_Note_edit->Text);
			//mapobjinfo->MapObjNote = title;

			MapObjectInfos::getInstance().saveFile(L"Config\\World\\MapObject.csv", mapObjInfoList);
			loadMapObjectList();
		}
#endif
    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::clearMapUI()
    {

    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::selMapObjectFromList()
    {
#if 0
		if (map_load_list->SelectedItems->Count <=0)
			return;

		//First selected item
		ListViewItem^ item = map_load_list->SelectedItems[0];  

		//String^ str_formatType  = item->SubItems["col_elm_type"]->Text;
		String^ str = item->SubItems["MapCol_ID"]->Text;
		UInt id = TypeConverter::StrToU32(str);

		std::map<IdType, MapObjectInfo*>* mapObjInfoList = CoreManager::getInstance().mMapObjInfoList;
		if(!mapObjInfoList)
		{
			return;
		}

		MapObjectInfo* mapobjinfo = (*mapObjInfoList)[id];
		if(mapobjinfo)
		{
			Map_ID_Edit->Text = str;
			str = TypeConverter::U64ToStr(mapobjinfo->districtObjectId);
			Map_Distrct_ID_Edit->Text = str;
			str = TypeConverter::U64ToStr(mapobjinfo->artMapResId);
			Map_ArtRes_Edit->Text = str;
			str	= TypeConverter::Char16ToStr(mapobjinfo->name.c_str());
			Map_Name_Edit->Text = str;
			str	= TypeConverter::Char16ToStr(mapobjinfo->description.c_str());
			Map_Test_Edit->Text = str;
			//str	= TypeConverter::Char16ToStr(mapobjinfo->MapObjNote.c_str());
			//Map_Note_edit->Text = str;

			m_SelCityArtID = mapobjinfo->artMapResId;
		}
#endif
    }

    //-----------------------------------------------------------------------
    void GameDataEditorForm::loadPlaceObjectList()
    {
#if 0
		Map_place_list->Items->Clear();

		PlaceObjectInfo* placeobjinfo = NULL;

		std::map<IdType, PlaceObjectInfo*>* placeObjInfoList = CoreManager::getInstance().mPlaceObjInfoList;
		if(!placeObjInfoList)
		{
			return;
		}

		for(CoreManager::PlaceObjInfoIt it = placeObjInfoList->begin(); it != placeObjInfoList->end(); ++it)
		{
			placeobjinfo = it->second;
			if(placeobjinfo)
			{
				ListViewItem ^ item = gcnew ListViewItem;
				String ^ str = TypeConverter::U64ToStr(placeobjinfo->id);
				item->SubItems->default[0]->Text = str;
				item->SubItems->default[0]->Name = "MapPlaceCol_ID";
				str = TypeConverter::Char16ToStr(placeobjinfo->name.c_str());
				item->SubItems->Add(str)->Name = "MapPlaceCol_Name";
				str = TypeConverter::Char16ToStr(placeobjinfo->entityNameInScene.c_str());
				item->SubItems->Add(str)->Name = "MapPlaceCol_SceneObjectName";
				str = TypeConverter::U64ToStr(placeobjinfo->districtObjectId);
				item->SubItems->Add(str)->Name = "MapPlaceCol_DistrictID";

				Map_place_list->Items->Add(item);
			}
		}

		PlaceTemplateInfo* placeinfo = NULL;

		for(int i = 0; i < PlaceTemplateInfos::getInstance().getPlaceInfoCnt(); ++i)
		{
			placeinfo = PlaceTemplateInfos::getInstance().getPlaceInfo(i);
			if(placeinfo)
			{
				String^ str = TypeConverter::U64ToStr(placeinfo->id);
				MapPlace_Template_Edit->Items->Add(str);
			}
		}
#endif
    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::searchPlaceObjectList()
    {
#if 0
		if(String::IsNullOrEmpty(textBox1->Text))
		{
			return;
		}

		PlaceObjectInfo* placeobjinfo = NULL;
		UInt id = TypeConverter::StrToU32(textBox1->Text);
		
		Map_place_list->Items->Clear();

		std::map<IdType, PlaceObjectInfo*>* placeObjInfoList = CoreManager::getInstance().mPlaceObjInfoList;
		if(!placeObjInfoList)
		{
			return;
		}

		for(CoreManager::PlaceObjInfoIt it = placeObjInfoList->begin(); it != placeObjInfoList->end(); ++it)
		{
			placeobjinfo = it->second;
			if(placeobjinfo && placeobjinfo->mapObjectId == id)
			{
				ListViewItem ^ item = gcnew ListViewItem;
				String ^ str = TypeConverter::U64ToStr(placeobjinfo->id);
				item->SubItems->default[0]->Text = str;
				item->SubItems->default[0]->Name = "MapPlaceCol_ID";
				str = TypeConverter::Char16ToStr(placeobjinfo->name.c_str());
				item->SubItems->Add(str)->Name = "MapPlaceCol_Name";
				str = TypeConverter::Char16ToStr(placeobjinfo->entityNameInScene.c_str());
				item->SubItems->Add(str)->Name = "MapPlaceCol_SceneObjectName";
				str = TypeConverter::U64ToStr(placeobjinfo->districtObjectId);
				item->SubItems->Add(str)->Name = "MapPlaceCol_DistrictID";

				Map_place_list->Items->Add(item);
			}
		}
		
		//PlaceObjInfo* placeobjinfo = PlaceObjInfos::getInstance().getPlaceObjInfo(id);
		//if(placeobjinfo)
		//{
		//	Map_place_list->Items->Clear();

		//	ListViewItem ^ item = gcnew ListViewItem;
		//	String ^ str = TypeConverter::U32ToStr(placeobjinfo->PlaceObjId);
		//	item->SubItems->default[0]->Text = "MapPlaceCol_ID";
		//	item->SubItems->default[0]->Name = str;
		//	str = TypeConverter::Char16ToStr(placeobjinfo->PlaceObjName.c_str());
		//	item->SubItems->Add(str)->Name = "MapPlaceCol_Name";
		//	str = TypeConverter::Char16ToStr(placeobjinfo->PlaceEditName.c_str());
		//	item->SubItems->Add(str)->Name = "MapPlaceCol_SceneObjectName";
		//	str = TypeConverter::U32ToStr(placeobjinfo->DistrictObjId);
		//	item->SubItems->Add(str)->Name = "MapPlaceCol_DistrictID";

		//	Map_place_list->Items->Add(item);
		//}
#endif
    }
	//-----------------------------------------------------------------------
	void GameDataEditorForm::searchDistObjList()
	{
#if 0
		if(String::IsNullOrEmpty(comboBox3->Text))
		{
			return;
		}

		Int lvl = 0;
		if(comboBox3->Text == "世界")
		{
			lvl = 1;
		}
		else if(comboBox3->Text == "国")
		{
			lvl = 2;
		}
		else if(comboBox3->Text == "州")
		{
			lvl = 3;
		}
		else if(comboBox3->Text == "郡")
		{
			lvl = 4;
		}
		else if(comboBox3->Text == "县")
		{
			lvl = 5;
		}
		else if(comboBox3->Text == "乡")
		{
			lvl = 6;
		}

		Map_District_List->Items->Clear();
		DistrictObjectInfo* districtObj = NULL;
		DistrictTemplateInfo* districtInfo = NULL;

		for(Int i = 0; i < DistrictObjectInfos::getInstance().getDistrictObjInfoCnt(); ++i)
		{
			districtObj = DistrictObjectInfos::getInstance().getDistrictObjInfo(i);
			if(districtObj)
			{
				districtInfo = DistrictInfos::getInstance().getDistrictInfo(districtObj->templateId);
				if(districtInfo && districtInfo->rank == lvl)
				{
					ListViewItem ^ item = gcnew ListViewItem;
					String^ str = TypeConverter::U64ToStr(districtObj->id);
					item->SubItems->default[0]->Text = str;
					item->SubItems->default[0]->Name = "MapDistrictCol_ID";
					str = TypeConverter::Char16ToStr(districtObj->name.c_str());
					item->SubItems->Add(str)->Name    = "MapDistrictCol_Name";
					//item->SubItems->Add(str);
					//str = TypeConverter::Char16ToStr(distobjinfo->DistObjName);
					//item->SubItems->Add(str)->Name    = "MapCol_Name";

					Map_District_List->Items->Add(item);	
				}
			}
		}
#endif
	}
    //-----------------------------------------------------------------------
    void GameDataEditorForm::saveSelPlaceObject()
    {
#if 0
		if(String::IsNullOrEmpty(MapPlace_ID_Text->Text) || MapPlace_ID_Text->Text == "XXX")
			return;
		UInt id = TypeConverter::StrToU32(MapPlace_ID_Text->Text);

		std::map<IdType, PlaceObjectInfo*>* placeObjInfoList = CoreManager::getInstance().mPlaceObjInfoList;
		if(!placeObjInfoList)
		{
			return;
		}

		PlaceObjectInfo* placeobjinfo = (*placeObjInfoList)[id];
		if(placeobjinfo)
		{
			id = TypeConverter::StrToU32(MapPlace_District_Id_Edit->Text);
			placeobjinfo->districtObjectId = id;
			id = TypeConverter::StrToU32(MapPlace_MapID_Edit->Text);
			placeobjinfo->mapObjectId = id;
			id = TypeConverter::StrToU32(MapPlace_Template_Edit->Text);
			placeobjinfo->templateId= id;
			CChar16* title = TypeConverter::StrToChar16(MapPlace_SceneObjectName_edit->Text);
			placeobjinfo->entityNameInScene = title;
			title = TypeConverter::StrToChar16(MapPlace_Name_Edit->Text);
			placeobjinfo->name = title;
			title = TypeConverter::StrToChar16(MapPlace_Text_Edit->Text);
			placeobjinfo->description = title;
			//title = TypeConverter::StrToChar16(MapPlace_Note_Edit->Text);
			//placeobjinfo->PlaceObjNote = title;
			title = TypeConverter::StrToChar16(MapPlace_SceneObjectName_edit->Text);
			placeobjinfo->entityNameInScene = title;

			//PlaceObjectInfos::getInstance().saveFile(L"Config\\World\\CityObject.csv", placeObjInfoList);

			loadPlaceObjectList();
		}

#endif
    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::loadPlaceScene()
    {
#if 0
		MapPlace_SceneObjectName_edit->Items->Clear();
		MapResourceInfo* MapResInfo = NULL;

		for(int i = 0; i < MapResourceInfos::getInstance().getMapResCnt(); ++i)
		{
			MapResInfo = MapResourceInfos::getInstance().getMapResourceInfoByIndex(i);
			if(MapResInfo && m_SelCityArtID == MapResInfo->id)
			{
				for(std::list<MapPointInfo*>::iterator it = MapResInfo->pointInfo.MapPlaceInfo.begin(); it != MapResInfo->pointInfo.MapPlaceInfo.end(); ++it)
				{
					if((*it))
					{
						String^ str = TypeConverter::Char8ToStr((*it)->name.c_str());
						MapPlace_SceneObjectName_edit->Items->Add(str);
					}
				}

				String^ strMapPath = TypeConverter::Char16ToStr(MapResInfo->filePath.c_str());
				FormSet::main_form->mLastFocusDir = strMapPath;
				StrToChar8 pathStr(strMapPath);
				FormSet::main_form->clearAll();
				CoreManager::getInstance().getScene()->getXmlSerializer()->loadContent(pathStr.getChar8(), FormSet::main_form->isEditorMode());
				FormSet::main_form->loadSceneEntityList();
				CoreManager::getInstance().initScene();

				break;
			}
		}
#endif
    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::clearPlaceUI()
    {

    }
    //-----------------------------------------------------------------------
    void GameDataEditorForm::selPlaceObjectFromList()
    {
#if 0
		if(Map_place_list->SelectedItems->Count < 0)
			return;
		
		ListViewItem^ item = Map_place_list->SelectedItems[0];  
		String ^ str = item->SubItems["MapPlaceCol_ID"]->Text;
		UInt id = TypeConverter::StrToU32(str);

		std::map<IdType, PlaceObjectInfo*>* placeObjInfoList = CoreManager::getInstance().mPlaceObjInfoList;
		if(!placeObjInfoList)
		{
			return;
		}

		PlaceObjectInfo* placeobjinfo = (*placeObjInfoList)[id];
		if(placeobjinfo)
		{
			String^ str = TypeConverter::U64ToStr(placeobjinfo->id);
			MapPlace_ID_Text->Text = str;
			str = TypeConverter::U64ToStr(placeobjinfo->districtObjectId);
			MapPlace_District_Id_Edit->Text = str;
			str = TypeConverter::U64ToStr(placeobjinfo->mapObjectId);
			MapPlace_MapID_Edit->Text = str;
			str = TypeConverter::U64ToStr(placeobjinfo->templateId);
			MapPlace_Template_Edit->Text = str;
			str = TypeConverter::Char16ToStr(placeobjinfo->entityNameInScene.c_str());
			MapPlace_SceneObjectName_edit->Text = str;
			str = TypeConverter::Char16ToStr(placeobjinfo->name.c_str());
			MapPlace_Name_Edit->Text = str;
			str = TypeConverter::Char16ToStr(placeobjinfo->description.c_str());
			MapPlace_Text_Edit->Text = str;
			//str = TypeConverter::Char16ToStr(placeobjinfo->PlaceObjNote.c_str());
			//MapPlace_Note_Edit->Text = str;

			std::map<IdType, MapObjectInfo*>* mapObjInfoList = CoreManager::getInstance().mMapObjInfoList;
			if(!mapObjInfoList)
			{
				return;
			}

			MapObjectInfo* mapobjinfo = (*mapObjInfoList)[id];
			if(mapobjinfo)
			{
				m_SelCityArtID = mapobjinfo->artMapResId;
			}
		}
#endif
    }


}