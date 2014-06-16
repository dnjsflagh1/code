#include "StdAfx.h"
#include "MainForm.h"
#include "GlobalOptions.h"
#include "CoreManager.h"
#include "Utility.h"
#include "XmlHelper.h"
#include "OperationManager.h"
#include "CharacterList.h"
#include "PointTemplate.h"
#include "PlaceListCsv.h"
#include "ArtMapResCsv.h"
#include "CharacterArmyList.h"
#include "CharacterBuildList.h"
#include "CharacterMonsterList.h"
#include "CharacterNpcList.h"
#include "CharacterGenrealList.h"
#include "CharacterObjectList.h"
#include "GameCameraConfig.h"
#include "ICollisionSystem.h"

namespace GameMapEditor {

    //-----------------------------------------------------------------------
    void MainForm::initialize()
    {
        mCurrSceneObjectXmlFormat = NULL;
        setSceneFormLocation();
        loadAllObjectList();
        mCurrSelectCreateModelTreeNode = nullptr;

		CoreManager::getInstance().getEngineMain()->lockTreeManager();
    }
    //-----------------------------------------------------------------------
    void MainForm::clearAll()
    {
        clearSceneElementProps();
        clearSceneElementList();
    }
    //-----------------------------------------------------------------------
    void MainForm::revert()
    {
        CoreManager::getInstance().getScene()->getSceneObjectController()->setFocus( NULL );
        clearSceneElementProps();
        loadSceneElementList();
    }
    //-----------------------------------------------------------------------
    void MainForm::update()
    {
        checkSceneElementProps();
        updateCameraHint();
    }
    //-----------------------------------------------------------------------
    void MainForm::updateDebugInfo()
    {
        IDisplay* display = CoreManager::getInstance().getEngineMain()->display();
        if ( display )
        {
            lable_status_batch->Text        = "BatchCount:";
            lable_status_triCount->Text     = "TriangleCount:";
            lable_status_LastFPS->Text      = "LastFPS:";
            lable_status_aveFPS->Text       = "LastAverageFPS:";

            lable_status_batch->Text        += TypeConverter::IntToStr(display->getBatchCount());
            lable_status_triCount->Text     += TypeConverter::IntToStr(display->getTriangleCount());
            lable_status_LastFPS->Text      += TypeConverter::DoubleToStr(display->getLastFPS());
            lable_status_aveFPS->Text       += TypeConverter::DoubleToStr(display->getLastAverageFPS());
        }
    }
	//-----------------------------------------------------------------------
    void MainForm::setSceneFormLocation()
    {
        UInt margin = 5;

        Point scene_loation  = this->scene_panel->PointToScreen( this->scene_panel->Location );
        scene_loation.X  = this->DesktopLocation.X + this->scene_panel->Location.X + margin;

        FormSet::scene_form->DesktopLocation = scene_loation ;

        System::Drawing::Size  size = this->scene_panel->Size;
        size.Width  -= margin;
        size.Height -= margin;
        FormSet::scene_form->Size = size;
    }
    //-----------------------------------------------------------------------
    void MainForm::switchGameEditorOp()
    {
        OperationManager::getInstance().clearEditorOp();
        //元素Tab
        CoreManager::getInstance().getScene()->getSceneObjectController()->setEnable(false);
        if ( prop_tab_ctrl->SelectedTab == elemet_page )
        {
            CoreManager::getInstance().getScene()->getSceneObjectController()->setEnable(true);

            if ( element_tab->SelectedTab == element_create_page )
            {
                if ( SelectCreateElementTypeTab->SelectedTab == create_object_page )
                {
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_OBJECT );
                }
				else if ( SelectCreateElementTypeTab->SelectedTab == create_monster_page )
				{
					OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_MONSTER );
				}
				else if ( SelectCreateElementTypeTab->SelectedTab == create_npc_page )
				{
					OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_NPC );
				}
				else if ( SelectCreateElementTypeTab->SelectedTab == create_point_page )
				{
					OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_POINT );
				}
				else if ( SelectCreateElementTypeTab->SelectedTab == create_place_page )
				{
					OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_PLACE );
				}
				//else if ( SelectCreateElementTypeTab->SelectedTab == create_region_page )
				//{
					//OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_REGION );
				//}
				else if ( SelectCreateElementTypeTab->SelectedTab == create_building_page )
				{
					OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_BUILDING );
				}
				else if ( SelectCreateElementTypeTab->SelectedTab == create_static_page )
				{
					OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_STATIC_OBJECT );
				}
				else if ( SelectCreateElementTypeTab->SelectedTab == create_troop_page )
				{
					OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_TROOP );
				}
				else if (SelectCreateElementTypeTab->SelectedTab == create_effect_page)
				{
					OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_EFFECT );
				}
            }
        }
    }
	//-----------------------------------------------------------------------
    void MainForm::createScene()
    {
        BEGINDELEGATE(MainForm,createScene)
        ENDDELEGATE

        clearAll();

		CoreManager::getInstance().getScene()->getXmlSerializer()->createSceneContent();
    }
    //-----------------------------------------------------------------------
	void MainForm::loadScene(I32 mapID)
	{
		////////////////////////////////////////////////////
		std::map<MapIdType, MapListCsvInfo*>* mapList = MapListCsv::getInstance().getList();

		if ( !mapList )
			return;

		std::map<MapIdType, MapListCsvInfo*>::iterator iter = mapList->find((MapIdType)mapID);
		if ( iter == mapList->end() || iter->second == NULL )
			return;

		ArtMapResCsvInfo* mapInfo = ArtMapResCsv::getInstance().getArtMapResInfoById(ArtMapResIdType(iter->second->artMapResId));
		if ( !mapInfo )
			return;

		Str16 artPath = mapInfo->BaseFilePath;
		Str16 designPath = iter->second->filePath + L"\\" + iter->second->fileName;
		////////////////////////////////////////////////////


		clearAll();
		mLastFocusDir = L"";

		Str mainFilePath;
		Str subFilePath;

		MG::MGStrOp::toString( artPath.c_str(), mainFilePath );
		MG::MGStrOp::toString( designPath.c_str(), subFilePath );

		if ( CoreManager::getInstance().getScene()->getXmlSerializer()->loadContent( mainFilePath.c_str(), FormSet::main_form->isEditorMode()))
		{
			if ( CoreManager::getInstance().getScene()->getXmlSerializer()->loadSubSceneFile( subFilePath.c_str(), FormSet::main_form->isEditorMode()) )
			{
				mLastFocusDir = TypeConverter::Char8ToStr(subFilePath.c_str());

				if ( FormSet::main_form->isEditorMode() )
				{
					loadSceneElementList();
				}

				////////////////////////////////////////////////////
				switchGameEditorOp();
				////////////////////////////////////////////////////

				loadSceneEnvironmentLight();
				loadSceneGameConfig();
				resetObjectTabList(iter->second->mapType);
				restoreMapInstanceConfig((I32)iter->second->mapListId);

				////////////////////////////////////////////////////

				CoreManager::getInstance().initScene();
				updateDebugInfo();
			}

			CoreManager::getInstance().getEngineMain()->unLockTreeManager();
		}	
	}
	//-----------------------------------------------------------------------
    void MainForm::loadScene()
    {
        BEGINDELEGATE(MainForm,loadScene)
        ENDDELEGATE
        
        clearAll();
        
		folderBrowserDialog1->SelectedPath = System::Windows::Forms::Application::StartupPath;
		if ( folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
		{
			mLastFocusDir = folderBrowserDialog1->SelectedPath;
			StrToChar8 pathStr( folderBrowserDialog1->SelectedPath );
			CoreManager::getInstance().getScene()->getXmlSerializer()->loadContent( pathStr.getChar8(), FormSet::main_form->isEditorMode());

			if ( FormSet::main_form->isEditorMode() )
			{
				loadSceneElementList();
			}

			////////////////////////////////////////////////////
			switchGameEditorOp();
			////////////////////////////////////////////////////

			loadSceneEnvironmentLight();
			loadSceneGameConfig();

			////////////////////////////////////////////////////

			CoreManager::getInstance().initScene();
			updateDebugInfo();

			////////////////////////////////////////////////////

			CoreManager::getInstance().getEngineMain()->unLockTreeManager();
		}
    }
	//-----------------------------------------------------------------------
	void MainForm::saveScene()
	{
		BEGINDELEGATE(MainForm,saveScene)
			ENDDELEGATE

			if ( String::IsNullOrEmpty(mLastFocusDir) )
			{
				saveAsScene();
			}
			else
			{
				StrToChar8 pathStr( mLastFocusDir );
				//CoreManager::getInstance().getScene()->getXmlSerializer()->saveContent( pathStr.getChar8() );
				CoreManager::getInstance().getScene()->getXmlSerializer()->saveSubSceneFile(pathStr.getChar8());
			}
	}
	//-----------------------------------------------------------------------
	void MainForm::saveAsScene()
	{
		BEGINDELEGATE(MainForm,saveAsScene)
			ENDDELEGATE

			folderBrowserDialog1->SelectedPath = System::Windows::Forms::Application::StartupPath;
		if ( folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
		{
			StrToChar8 pathStr( folderBrowserDialog1->SelectedPath );
			Str fullFile = FileOp::getFullFilePath( Str(pathStr.getChar8()), Str("Scene.Xml"));

			mLastFocusDir = folderBrowserDialog1->SelectedPath;

			CoreManager::getInstance().getScene()->getXmlSerializer()->saveSubSceneFile( fullFile.c_str() );
		}
	}
	//-----------------------------------------------------------------------
	Bool MainForm::isEditorMode()
	{
		//return ToolStripMenuItem_SceneEditorMode->Checked;

		EngineMode mode = CoreManager::getInstance().getEngineMain()->getMode();
		Bool isEditorMode = true;
		if (mode != MG::EM_EDITOR)
			isEditorMode = false;
		return isEditorMode;
	}
    //-----------------------------------------------------------------------
    void MainForm::selectCtrlType()
    {
        if ( UtilType_Ctrl->SelectedTab == util_type_slg_page )
        {
            CoreManager::getInstance().getScene()->getSceneObjectController()->setControlType(ISceneObjectController::SOC_SLG);
        }else
        if ( UtilType_Ctrl->SelectedTab == util_type_move_page )
        {
            CoreManager::getInstance().getScene()->getSceneObjectController()->setControlType(ISceneObjectController::SOC_POSITION);
        }else
        if ( UtilType_Ctrl->SelectedTab == util_type_rot_page )
        {
            CoreManager::getInstance().getScene()->getSceneObjectController()->setControlType(ISceneObjectController::SOC_ROTATION);
        }else
        if ( UtilType_Ctrl->SelectedTab == util_type_scale_page )
        {
            CoreManager::getInstance().getScene()->getSceneObjectController()->setControlType(ISceneObjectController::SOC_SCALE);
        }
    }

    //-----------------------------------------------------------------------
    void MainForm::updateCameraHint()
    {
        IScene* scene = CoreManager::getInstance().getScene();
        if ( scene == NULL )
            return;

        ICamera* cam = scene->getActiveCamera();
        if ( cam == NULL )
            return;

        Vec3 pos;
        cam->getPosition(pos);

        camPosX->Text = TypeConverter::DoubleToStr(pos.x);
        camPosY->Text = TypeConverter::DoubleToStr(pos.y);
        camPosZ->Text = TypeConverter::DoubleToStr(pos.z);
    }

    //-----------------------------------------------------------------------
    void MainForm::loadAllObjectList()
    {
		loadObjectList();
		loadNpcList();
		loadMonsterList();
		loadPlaceList();
		loadPointList();
		loadTroopList();
		//loadRegionList();
		loadStaticObjectList();
		loadBuildingList();
		loadEffectDeclarationList();

		create_static_page->Enabled = false;
		create_place_page->Enabled = false;
		create_monster_page->Enabled = false;
		create_npc_page->Enabled = false;
		create_troop_page->Enabled = false;
		create_building_page->Enabled = false;
		create_object_page->Enabled = false;
		create_point_page->Enabled = false;
		create_effect_page->Enabled = false;
    }
	//-----------------------------------------------------------------------
	void MainForm::prepareCreateStaticObjectEntity()
	{
		if ( static_object_model_create_tree->SelectedNode != nullptr &&
			static_object_model_create_tree->SelectedNode->Tag != nullptr )
		{
			String^ tag = static_object_model_create_tree->SelectedNode->Tag->ToString();
			if ( !String::IsNullOrEmpty(tag) )
			{
				if ( static_object_model_create_tree->SelectedNode->Parent )
					mCurrSelectCreateModelTreeNode = static_object_model_create_tree->SelectedNode->Parent;

				U32 objectDeclID = TypeConverter::StrToInt( tag );
				OperationManager::getInstance().prepareCreateSceneObject( objectDeclID );

				ModelDeclaration* decl =  CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( objectDeclID );
				if ( decl )
				{
					char msg[256];

					sprintf_s( msg, _countof( msg ), "%s\n%s\\\\%s\n%s\\\\%s", decl->name.c_str(), decl->path.c_str(), decl->meshFileName.c_str(), 
						decl->path.c_str(), decl->materialFileName.c_str()  );

					prepare_static_model_text->Text = TypeConverter::Char8ToStr( msg );
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void MainForm::prepareCreateObjectEntity()
	{
		if ( object_model_create_tree->SelectedNode != nullptr &&
			object_model_create_tree->SelectedNode->Tag != nullptr )
		{
			String^ tag = object_model_create_tree->SelectedNode->Tag->ToString();
			if ( !String::IsNullOrEmpty(tag) )
			{
				if ( object_model_create_tree->SelectedNode->Parent )
					mCurrSelectCreateModelTreeNode = object_model_create_tree->SelectedNode->Parent;

				U32 objectDeclID = TypeConverter::StrToInt( tag );
				OperationManager::getInstance().prepareCreateSceneObject( objectDeclID );

				const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( objectDeclID );
				if ( charInfo && charInfo->CharacterType == CHARACTER_TYPE_OBJ && charInfo->isValid() )
				{
					ModelDeclaration* decl =  CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( charInfo->getCharacterArtMashId() );
					if ( decl )
					{
						char msg[256];

						sprintf_s( msg, _countof( msg ), "%s\n%s\\\\%s\n%s\\\\%s", decl->name.c_str(), decl->path.c_str(), decl->meshFileName.c_str(), 
							decl->path.c_str(), decl->materialFileName.c_str()  );

						prepare_object_model_text->Text = TypeConverter::Char8ToStr( msg );
					}
				}				
			}
		}
	}
	//-----------------------------------------------------------------------
	void MainForm::prepareCreateNpcEntity()
	{
		if ( NPC_model_create_tree->SelectedNode != nullptr &&
			NPC_model_create_tree->SelectedNode->Tag != nullptr )
		{
			String^ tag = NPC_model_create_tree->SelectedNode->Tag->ToString();
			if ( !String::IsNullOrEmpty(tag) )
			{
				if ( NPC_model_create_tree->SelectedNode->Parent )
					mCurrSelectCreateModelTreeNode = NPC_model_create_tree->SelectedNode->Parent;

				U32 objectDeclID = TypeConverter::StrToInt( tag );
				OperationManager::getInstance().prepareCreateSceneObject( objectDeclID );

				const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( objectDeclID );
				if ( charInfo && charInfo->CharacterType == CHARACTER_TYPE_NPC && charInfo->isValid() )
				{
					ModelDeclaration* decl =  CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( charInfo->getCharacterArtMashId() );
					if ( decl )
					{
						char msg[256];

						sprintf_s( msg, _countof( msg ), "%s\n%s\\\\%s\n%s\\\\%s", decl->name.c_str(), decl->path.c_str(), decl->meshFileName.c_str(), 
							decl->path.c_str(), decl->materialFileName.c_str()  );

						prepare_npc_model_text->Text = TypeConverter::Char8ToStr( msg );
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void MainForm::prepareCreatePlaceEntity()
	{
		if ( place_model_create_tree->SelectedNode != nullptr &&
			place_model_create_tree->SelectedNode->Tag != nullptr )
		{
			String^ tag = place_model_create_tree->SelectedNode->Tag->ToString();
			if ( !String::IsNullOrEmpty(tag) )
			{
				if ( place_model_create_tree->SelectedNode->Parent )
					mCurrSelectCreateModelTreeNode = place_model_create_tree->SelectedNode->Parent;

				U32 objectDeclID = TypeConverter::StrToInt( tag );
				OperationManager::getInstance().prepareCreateSceneObject( objectDeclID );

				const PlaceListCsvInfo* placeInfo = PlaceListCsv::getInstance().getPlaceListInfo( (PlaceIdType)objectDeclID );
				if ( placeInfo  )
				{
					ModelDeclaration* decl =  CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( placeInfo->artMashResId );
					if ( decl )
					{
						char msg[256];

						sprintf_s( msg, _countof( msg ), "%s\n%s\\\\%s\n%s\\\\%s", decl->name.c_str(), decl->path.c_str(), decl->meshFileName.c_str(), 
							decl->path.c_str(), decl->materialFileName.c_str()  );

						prepare_place_model_text->Text = TypeConverter::Char8ToStr( msg );
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void MainForm::prepareCreatePointEntity()
	{
		if (point_model_create_tree->SelectedNode != nullptr &&
			point_model_create_tree->SelectedNode->Tag != nullptr )
		{
			String^ tag = point_model_create_tree->SelectedNode->Tag->ToString();
			if ( !String::IsNullOrEmpty(tag) )
			{
				if ( point_model_create_tree->SelectedNode->Parent )
				mCurrSelectCreateModelTreeNode = point_model_create_tree->SelectedNode->Parent;

				U32 objectDeclID = TypeConverter::StrToInt( tag );
				OperationManager::getInstance().prepareCreateSceneObject( objectDeclID );

				const PointTempInfo* pointInfo = PointTemplate::getInstance().getPointTempInfo( objectDeclID );
				if ( pointInfo  )
				{
					ModelDeclaration* decl =  CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( pointInfo->ArtMashId );
					if ( decl )
					{
						char msg[256];

						sprintf_s( msg, _countof( msg ), "%s\n%s\\\\%s\n%s\\\\%s", decl->name.c_str(), decl->path.c_str(), decl->meshFileName.c_str(), 
							decl->path.c_str(), decl->materialFileName.c_str()  );

						prepare_point_model_text->Text = TypeConverter::Char8ToStr( msg );
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void MainForm::prepareCreateMonsterEntity()
	{
		if ( monster_model_create_tree->SelectedNode != nullptr &&
			monster_model_create_tree->SelectedNode->Tag != nullptr )
		{
			String^ tag = monster_model_create_tree->SelectedNode->Tag->ToString();
			if ( !String::IsNullOrEmpty(tag) )
			{
				if ( monster_model_create_tree->SelectedNode->Parent )
					mCurrSelectCreateModelTreeNode = monster_model_create_tree->SelectedNode->Parent;

				U32 objectDeclID = TypeConverter::StrToInt( tag );
				OperationManager::getInstance().prepareCreateSceneObject( objectDeclID );

				const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( objectDeclID );
				if ( charInfo && charInfo->CharacterType == CHARACTER_TYPE_MONSTER && charInfo->isValid() )
				{
					ModelDeclaration* decl =  CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( charInfo->getCharacterArtMashId() );
					if ( decl )
					{
						char msg[256];

						sprintf_s( msg, _countof( msg ), "%s\n%s\\\\%s\n%s\\\\%s", decl->name.c_str(), decl->path.c_str(), decl->meshFileName.c_str(), 
							decl->path.c_str(), decl->materialFileName.c_str()  );

						prepare_monster_model_text->Text = TypeConverter::Char8ToStr( msg );
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void MainForm::prepareCreateTroopEntity()
	{
		if ( troop_model_create_tree->SelectedNode != nullptr &&
			troop_model_create_tree->SelectedNode->Tag != nullptr )
		{
			String^ tag = troop_model_create_tree->SelectedNode->Tag->ToString();
			if ( !String::IsNullOrEmpty(tag) )
			{
				if ( troop_model_create_tree->SelectedNode->Parent )
					mCurrSelectCreateModelTreeNode = troop_model_create_tree->SelectedNode->Parent;

				U32 objectDeclID = TypeConverter::StrToInt( tag );
				OperationManager::getInstance().prepareCreateSceneObject( objectDeclID );

				const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( objectDeclID );
				if ( charInfo && charInfo->CharacterType == CHARACTER_TYPE_ARMY && charInfo->isValid() )
				{
					ModelDeclaration* decl =  CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( charInfo->getCharacterArtMashId() );
					if ( decl )
					{
						char msg[256];

						sprintf_s( msg, _countof( msg ), "%s\n%s\\\\%s\n%s\\\\%s", decl->name.c_str(), decl->path.c_str(), decl->meshFileName.c_str(), 
							decl->path.c_str(), decl->materialFileName.c_str()  );

						prepare_troop_model_text->Text = TypeConverter::Char8ToStr( msg );
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void MainForm::prepareCreateBuildingEntity()
	{
		if ( building_model_create_tree->SelectedNode != nullptr &&
			building_model_create_tree->SelectedNode->Tag != nullptr )
		{
			String^ tag = building_model_create_tree->SelectedNode->Tag->ToString();
			if ( !String::IsNullOrEmpty(tag) )
			{
				if ( building_model_create_tree->SelectedNode->Parent )
					mCurrSelectCreateModelTreeNode = building_model_create_tree->SelectedNode->Parent;

				U32 objectDeclID = TypeConverter::StrToInt( tag );
				OperationManager::getInstance().prepareCreateSceneObject( objectDeclID );

				const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( objectDeclID );
				if ( charInfo && charInfo->CharacterType == CHARACTER_TYPE_BUILD && charInfo->isValid() )
				{
					ModelDeclaration* decl =  CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( charInfo->getCharacterArtMashId() );
					if ( decl )
					{
						char msg[256];

						sprintf_s( msg, _countof( msg ), "%s\n%s\\\\%s\n%s\\\\%s", decl->name.c_str(), decl->path.c_str(), decl->meshFileName.c_str(), 
							decl->path.c_str(), decl->materialFileName.c_str()  );

						prepare_building_model_text->Text = TypeConverter::Char8ToStr( msg );
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void MainForm::prepareCreateRegionEntity()
	{
		/*if ( region_model_create_tree->SelectedNode != nullptr &&
			region_model_create_tree->SelectedNode->Tag != nullptr )
		{
			String^ tag = region_model_create_tree->SelectedNode->Tag->ToString();
			if ( !String::IsNullOrEmpty(tag) )
			{
				if ( region_model_create_tree->SelectedNode->Parent )
					mCurrSelectCreateModelTreeNode = region_model_create_tree->SelectedNode->Parent;

				prepare_region_model_text->Text = region_model_create_tree->SelectedNode->Text;

				Int OperationId = TypeConverter::StrToInt( tag );
				OperationManager::getInstance().prepareCreateEntity( OperationId );
			}
		}*/
	}

    //-----------------------------------------------------------------------
    void MainForm::loadSceneElementProps(ISceneObjectXmlFormat* format, Bool isChandedTab)
    {
        clearSceneElementProps();

        mCurrSceneObjectXmlFormat = format;

        if ( isChandedTab )
        {
            prop_tab_ctrl->SelectedTab = elemet_page;
            element_tab->SelectedTab = element_prop_page;
        }

        mXmlPropSet->loadXmlElement( format->getXmlElm() );
        element_prop_grids->SelectedObject = mXmlPropSet;
    }

    //-----------------------------------------------------------------------
    void MainForm::clearSceneElementProps()
    {
        mCurrSceneObjectXmlFormat = NULL;
        mXmlPropSet->clear();
        element_prop_grids->SelectedObject = mXmlPropSet;
    }    

    //-----------------------------------------------------------------------
    void MainForm::applySceneElementPropsChange()
    {
        if ( mCurrSceneObjectXmlFormat )
        {
            mCurrSceneObjectXmlFormat->apply( true );
        }
    }
    //-----------------------------------------------------------------------
    void MainForm::checkSceneElementProps()
    {
        if ( CoreManager::getInstance().getScene()->getSceneObjectController()->getChangedDirty() )
        {
			//更新Focus物件
            ISceneObject* sceneObject = CoreManager::getInstance().getScene()->getSceneObjectController()->getFocus();
            if ( sceneObject )
            {
                ISceneObjectXmlFormat* format = NULL;

				if ( !format )
					format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat(
					sceneObject->getName().c_str(), sceneObject->getType(), true);

                if ( !format )
                    format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat(
                                    sceneObject->getName().c_str(), sceneObject->getType(), false);
                if ( format )
                {
                    format->fill();
                    loadSceneElementProps( format, false );
                }
            }

			//更新其他选中的物件
			std::vector<ISceneObject*> focusObjects;
			CoreManager::getInstance().getScene()->getSceneObjectController()->getMultiFocusList( focusObjects );

			for ( U32 i = 0; i < focusObjects.size(); i++ )
			{
				ISceneObject* sceneObject = focusObjects[i];
				if ( !sceneObject )
					continue;

				ISceneObjectXmlFormat* format = NULL;

				if ( !format )
					format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat(
					sceneObject->getName().c_str(), sceneObject->getType(), true);

				if ( !format )
					format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat(
					sceneObject->getName().c_str(), sceneObject->getType(), false);

				if ( format )
				{
					format->fill();
				}
			}
        }
    }
    //-----------------------------------------------------------------------
    void MainForm::stickSelectElementToTerrain()
    {
		MG::IScene* scene = CoreManager::getInstance().getScene();
		if ( scene == NULL )
			return;

		MG::IInput* input = CoreManager::getInstance().getEngineMain()->input();
		if ( input == NULL )
			return;
		if (!input->isShiftOn())
		{
			 scene->getSceneObjectController()->stickTerrain();
		}
		else
		{
			MG::ICollisionSystem* colSystem = scene->getCollisionSystem();
			if ( colSystem == NULL )
				return;
			std::vector<ISceneObjectXmlFormat*> formatList;
			std::vector<ISceneObjectXmlFormat*>::iterator iter;
			Vec3 pos;
			scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_ENTITY, formatList,true);

			//trees
			std::vector<ISceneObjectXmlFormat*> treeFormatList;
			scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_TREE, treeFormatList,true);
			formatList.insert(formatList.end(),treeFormatList.begin(),treeFormatList.end());

			//grass
			std::vector<ISceneObjectXmlFormat*> grassFormatList;
			scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_GRASS, grassFormatList,true);
			formatList.insert(formatList.end(),grassFormatList.begin(),grassFormatList.end());

			//特效
			std::vector<ISceneObjectXmlFormat*> effectFormatList;
			scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_EFFECTENTITY, effectFormatList,true);
			formatList.insert(formatList.end(),effectFormatList.begin(),effectFormatList.end());

			for (  iter= formatList.begin(); iter!=formatList.end(); iter++ )
			{
				ISceneObjectXmlFormat* format = *iter;
				ISceneObject* obj = format->getSceneObject();
				ISceneNode* sceneNode = obj->getSceneNode();
				MG::Vec3 pos;
				sceneNode->getPosition(pos);
				//scene->getCollisionSystem()->getStickHeight(pos,pos.y);
				colSystem->getStickHeight(sceneNode,pos.y);
				sceneNode->setPosition(pos);
				format->fill();
				//sceneNode->translate(moveVec,MG::ISceneNode::TS_WORLD);
			}
		}
	}

	//-----------------------------------------------------------------------
	void MainForm::loadSceneElementList()
	{
		clearSceneElementList();

        //////////////////////////////////////////////////////////////////////////////

		std::vector<U32> groupSizeList;
        std::map<Str, std::vector<IEntity*>>  groupEntityList;
		std::vector<IEffectEntity*> effectList;
		
        ISceneObject* sceneObj = NULL;
        IEntity* entity = NULL;
        
		//////////////////////////////////////////////////////////////////////////////

		//遍历实体， 分组存放
        std::vector<ISceneObjectXmlFormat*> formatList;
        CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_ENTITY, formatList, true);
        std::vector<ISceneObjectXmlFormat*>::iterator iter = formatList.begin();
        for ( ; iter!=formatList.end(); iter++ )
        {
            sceneObj = (*iter)->getSceneObject();
            entity = (IEntity*)sceneObj;

            Str groupName = sceneObj->getGroup();

            groupEntityList[groupName].push_back( entity );
        }

		//遍历特效
		std::vector<ISceneObjectXmlFormat*> effectFormatList;
		CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_EFFECTENTITY, effectFormatList, true);
		std::vector<ISceneObjectXmlFormat*>::iterator effectIter = effectFormatList.begin();
		for ( ; effectIter!=effectFormatList.end(); effectIter++ )
		{
			IEffectEntity* effectEntity = static_cast<IEffectEntity*>((*effectIter)->getSceneObject());
			effectList.push_back( effectEntity );
		}

		//////////////////////////////////////////////////////////////////////////////

		//加入标识实体类别的组节点

		Str format = "%s （数量：%d）";
		char groupText[256];

		//静态物件
		System::String^ nodeName = TypeConverter::Char8ToStr( ( Str("DESIGN_") + SCENE_OBJECT_GROUP_STR_STATIC ).c_str() );
		TreeNode^ groupNode = gcnew TreeNode();
		sprintf_s( groupText, _countof(groupText), format.c_str(), "景观", groupEntityList[Str("DESIGN_") + SCENE_OBJECT_GROUP_STR_STATIC].size() );
		groupNode->Name = nodeName;
		groupNode->Text = TypeConverter::Char8ToStr( groupText );
		element_list->Nodes->Add( groupNode );

		//武将
		nodeName = TypeConverter::Char8ToStr( SCENE_OBJECT_GROUP_STR_GENERAL );
		groupNode = gcnew TreeNode();
		sprintf_s( groupText, _countof(groupText), format.c_str(), "武将", groupEntityList[SCENE_OBJECT_GROUP_STR_GENERAL].size() );
		groupNode->Name = nodeName;
		groupNode->Text = TypeConverter::Char8ToStr( groupText );
		element_list->Nodes->Add( groupNode );

		//军队
		nodeName = TypeConverter::Char8ToStr( SCENE_OBJECT_GROUP_STR_TROOP );
		groupNode = gcnew TreeNode();
		sprintf_s( groupText, _countof(groupText), format.c_str(), "军队", groupEntityList[SCENE_OBJECT_GROUP_STR_TROOP].size() );
		groupNode->Name = nodeName;
		groupNode->Text = TypeConverter::Char8ToStr( groupText );
		element_list->Nodes->Add( groupNode );

		//建筑
		nodeName = TypeConverter::Char8ToStr( SCENE_OBJECT_GROUP_STR_BUILDING );
		groupNode = gcnew TreeNode();
		sprintf_s( groupText, _countof(groupText), format.c_str(), "建筑", groupEntityList[SCENE_OBJECT_GROUP_STR_BUILDING].size() );
		groupNode->Name = nodeName;
		groupNode->Text = TypeConverter::Char8ToStr( groupText );
		element_list->Nodes->Add( groupNode );

		//怪物
		nodeName = TypeConverter::Char8ToStr( SCENE_OBJECT_GROUP_STR_MONSTER );
		groupNode = gcnew TreeNode();
		sprintf_s( groupText, _countof(groupText), format.c_str(), "怪物", groupEntityList[SCENE_OBJECT_GROUP_STR_MONSTER].size() );
		groupNode->Name = nodeName;
		groupNode->Text = TypeConverter::Char8ToStr( groupText );
		element_list->Nodes->Add( groupNode );

		//NPC
		nodeName = TypeConverter::Char8ToStr( SCENE_OBJECT_GROUP_STR_NPC );
		groupNode = gcnew TreeNode();
		sprintf_s( groupText, _countof(groupText), format.c_str(), "NPC", groupEntityList[SCENE_OBJECT_GROUP_STR_NPC].size() );
		groupNode->Name = nodeName;
		groupNode->Text = TypeConverter::Char8ToStr( groupText );
		element_list->Nodes->Add( groupNode );

		//物件
		nodeName = TypeConverter::Char8ToStr( SCENE_OBJECT_GROUP_STR_OBJECT );
		groupNode = gcnew TreeNode();
		sprintf_s( groupText, _countof(groupText), format.c_str(), "物件", groupEntityList[SCENE_OBJECT_GROUP_STR_OBJECT].size() );
		groupNode->Name = nodeName;
		groupNode->Text = TypeConverter::Char8ToStr( groupText );
		element_list->Nodes->Add( groupNode );

		//地点
		nodeName = TypeConverter::Char8ToStr( SCENE_OBJECT_GROUP_STR_PLACE );
		groupNode = gcnew TreeNode();
		sprintf_s( groupText, _countof(groupText), format.c_str(), "地点", groupEntityList[SCENE_OBJECT_GROUP_STR_PLACE].size() );
		groupNode->Name = nodeName;
		groupNode->Text = TypeConverter::Char8ToStr( groupText );
		element_list->Nodes->Add( groupNode );

		//坐标点
		nodeName = TypeConverter::Char8ToStr( SCENE_OBJECT_GROUP_STR_POINT );
		groupNode = gcnew TreeNode();
		sprintf_s( groupText, _countof(groupText), format.c_str(), "坐标点", groupEntityList[SCENE_OBJECT_GROUP_STR_POINT].size() );
		groupNode->Name = nodeName;
		groupNode->Text = TypeConverter::Char8ToStr( groupText );
		element_list->Nodes->Add( groupNode );

		//特效
		nodeName = TypeConverter::Char8ToStr( SCENE_OBJECT_GROUP_STR_EFFECT );
		TreeNode^ effectNode = gcnew TreeNode();
		sprintf_s( groupText, _countof(groupText), format.c_str(), "特效", effectList.size() );
		effectNode->Name = nodeName;
		effectNode->Text = TypeConverter::Char8ToStr( groupText );
		element_list->Nodes->Add( effectNode );

        //////////////////////////////////////////////////////////////////////////////

		//将所有的实体作为叶节点放入对应类型的組节点

		for ( std::map<Str, std::vector<IEntity*>>::iterator group_iter = groupEntityList.begin() ;
			group_iter != groupEntityList.end(); group_iter++ )
		{
			//////////////////////////////////////////////////////////////////////////////

			//寻找对应組节点
			Str groupName = group_iter->first;
			std::vector<IEntity*>& entityList = group_iter->second;

			TreeNode^ groupNode = nullptr;

			System::String^ groupNodeName = TypeConverter::Char8ToStr(groupName.c_str());

			for ( int node_index = 0; node_index < element_list->GetNodeCount(false); node_index++ )
			{
				TreeNode^ node = element_list->Nodes[node_index];

				if ( System::String::Compare( node->Name, groupNodeName ) == 0 )
				{
					groupNode = node;
					break;
				}
			}

			if ( groupNode == nullptr )
			{
				continue;
			}

			//////////////////////////////////////////////////////////////////////////////

			//将实体叶节点放入对应組节点, 设置实体叶节点的信息
			
			for ( U32 entity_index = 0; entity_index < entityList.size(); entity_index++ )
			{
				IEntity* entity = entityList[entity_index];
				
				System::String^ leafNodeName = TypeConverter::Char8ToStr(entity->getName().c_str());
				TreeNode^ leafNode = gcnew TreeNode(leafNodeName);
				groupNode->Nodes->Add(leafNode);
				leafNode->Tag = TypeConverter::Char8ToStr(entity->getName().c_str());

				Str treeText = entity->getName();

				if ( groupName.compare( ( Str("DESIGN_") + SCENE_OBJECT_GROUP_STR_STATIC ).c_str() ) == 0 )
				{
					IModelObject* modelObject = entity->getModelObject();
					if ( modelObject )
					{
						ModelDeclaration* decl = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( modelObject->getModelDeclarationID() );
						if ( decl )
						{
							treeText += " ";
							treeText += decl->name;
						}
					}
				}
				else if ( groupName.compare(SCENE_OBJECT_GROUP_STR_PLACE) == 0  )
				{
					Str attr = entity->getCustomAttr("PlaceID");

					U32 placeID = 0;
					MGStrOp::toU32( attr.c_str(), placeID );

					const PlaceListCsvInfo* placeInfo = PlaceListCsv::getInstance().getPlaceListInfo( (PlaceIdType)placeID );
					if ( placeInfo )
					{
						Str16 wtext = L" " + placeInfo->placeName + L" " + placeInfo->placeTitle;
						
						Str8 text;
						MGStrOp::toString(wtext.c_str(), text);

						treeText += text;
					}
				}
				else if ( groupName.compare(SCENE_OBJECT_GROUP_STR_POINT) == 0  )
				{
					Str attr = entity->getCustomAttr("PointID");

					U32 pointID = 0;
					MGStrOp::toU32( attr.c_str(), pointID );

					const PointTempInfo* pointInfo = PointTemplate::getInstance().getPointTempInfo( pointID );
					if ( pointInfo )
					{
						Str16 wtext = L" " + pointInfo->Name;

						Str8 text;
						MGStrOp::toString(wtext.c_str(), text);

						treeText += text;
					}
				}
				else if ( groupName.compare(SCENE_OBJECT_GROUP_STR_GENERAL) == 0  )
				{
					Str attr = entity->getCustomAttr("CharID");

					U32 charID = 0;
					MGStrOp::toU32( attr.c_str(), charID );

					const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( charID );

					if ( charInfo && 
						charInfo->CharacterType == CHARACTER_TYPE_GENREAL && 
						charInfo->isValid() )
					{
						Str16 wtext = L" " + charInfo->getCharacterSurName();

						Str8 text;
						MGStrOp::toString(wtext.c_str(), text);

						treeText += text;
					}
				}
				else if ( groupName.compare(SCENE_OBJECT_GROUP_STR_TROOP) == 0  )
				{
					Str attr = entity->getCustomAttr("CharID");

					U32 charID = 0;
					MGStrOp::toU32( attr.c_str(), charID );

					const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( charID );

					if ( charInfo && 
						charInfo->CharacterType == CHARACTER_TYPE_ARMY && 
						charInfo->isValid() )
					{
						Str16 wtext = L" " + charInfo->getCharacterSurName()
							+ L" " + charInfo->getCharacterTitle();

						Str8 text;
						MGStrOp::toString(wtext.c_str(), text);

						treeText += text;
					}
				}
				else if ( groupName.compare(SCENE_OBJECT_GROUP_STR_BUILDING) == 0 )
				{
					Str attr = entity->getCustomAttr("CharID");

					U32 charID = 0;
					MGStrOp::toU32( attr.c_str(), charID );

					const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( charID );

					if ( charInfo && 
						charInfo->CharacterType == CHARACTER_TYPE_BUILD && 
						charInfo->isValid() )
					{
						Str16 wtext = L" " + charInfo->getCharacterSurName();

						Str8 text;
						MGStrOp::toString(wtext.c_str(), text);

						treeText += text;
					}
				}
				else if ( groupName.compare(SCENE_OBJECT_GROUP_STR_MONSTER) == 0  )
				{
					Str attr = entity->getCustomAttr("CharID");

					U32 charID = 0;
					MGStrOp::toU32( attr.c_str(), charID );

					const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( charID );

					if ( charInfo && 
						charInfo->CharacterType == CHARACTER_TYPE_MONSTER && 
						charInfo->isValid() )
					{
						Str16 wtext = L" " + charInfo->getCharacterSurName() + charInfo->getMonsterName() + 
							/*L" （字 " + charInfo->getMonsterZhiName() + L") " + */charInfo->getCharacterTitle();

						Str8 text;
						MGStrOp::toString(wtext.c_str(), text);

						treeText += text;
					}
				}
				else if ( groupName.compare(SCENE_OBJECT_GROUP_STR_NPC) == 0  )
				{
					Str attr = entity->getCustomAttr("CharID");

					U32 charID = 0;
					MGStrOp::toU32( attr.c_str(), charID );

					const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( charID );

					if ( charInfo && 
						charInfo->CharacterType == CHARACTER_TYPE_NPC && 
						charInfo->isValid() )
					{
						Str16 wtext = L" " + charInfo->getCharacterSurName() + charInfo->getNpcName() + 
							/*L" （字 " + charInfo->getNpcZhiName() + L") " + */charInfo->getCharacterTitle();

						Str8 text;
						MGStrOp::toString(wtext.c_str(), text);

						treeText += text;
					}
				}
				else if ( groupName.compare(SCENE_OBJECT_GROUP_STR_OBJECT) == 0  )
				{
					Str attr = entity->getCustomAttr("CharID");

					U32 charID = 0;
					MGStrOp::toU32( attr.c_str(), charID );

					const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( charID );

					if ( charInfo && 
						charInfo->CharacterType == CHARACTER_TYPE_OBJ && 
						charInfo->isValid() )
					{
						Str16 wtext = L" " + charInfo->getCharacterSurName() + 
							L" " + charInfo->getCharacterTitle();

						Str8 text;
						MGStrOp::toString(wtext.c_str(), text);

						treeText += text;
					}
				}
				else
				{
					continue;
				}

				leafNode->Text = TypeConverter::Char8ToStr( treeText.c_str() );
			}
		}

		///////////////////////////////////////////////////////////////////////////
		//将所有特效加入到统计列表，并设置相应显示信息
		std::vector<IEffectEntity*>::iterator eitr = effectList.begin();
		for (; eitr!=effectList.end(); eitr++)
		{
			System::String^ leafNodeName = TypeConverter::Char8ToStr((*eitr)->getName().c_str());
			TreeNode^ leafNode = gcnew TreeNode(leafNodeName);
			effectNode->Nodes->Add(leafNode);
			leafNode->Tag = TypeConverter::Char8ToStr((*eitr)->getName().c_str());

			Str treeText = (*eitr)->getName();
			leafNode->Text = TypeConverter::Char8ToStr( treeText.c_str() );
		}
	}

	//-----------------------------------------------------------------------
	void MainForm::clearSceneElementList()
	{
		element_list->Nodes->Clear();
	}
    //-----------------------------------------------------------------------
    void MainForm::selectSceneElementFromList()
    {
		if ( element_list->SelectedNode != nullptr &&
			element_list->SelectedNode->Tag != nullptr )
		{
			System::String^ tag = element_list->SelectedNode->Tag->ToString();
			if ( !tag->Length == 0 )
			{
				StrToChar8 name( tag );
				ISceneObjectXmlFormat* format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat( name.getChar8(), SOT_ENTITY, true);
				if ( format )
				{
					loadSceneElementProps( format, false );
					CoreManager::getInstance().getScene()->getSceneObjectController()->setFocus( format->getSceneObject() );

					Vec3 pos;
					format->getSceneObject()->getSceneNode()->getPosition(pos);
					CoreManager::getInstance().getScene()->getActiveCamera()->focusPosition(pos);
				}
			}
		}
    }
    //-----------------------------------------------------------------------
    void MainForm::destroySceneElementFromList()
    {
		if ( element_list->SelectedNode != nullptr )
		{
			System::String^ tag = element_list->SelectedNode->Tag->ToString();

			if ( !tag->Length == 0 )
			{
				StrToChar8 name( tag );
				CoreManager::getInstance().getScene()->getXmlSerializer()->removeSceneObjectFormat( name.getChar8(), SOT_ENTITY, true, true);
				element_list->SelectedNode->Remove();

				revert();

				element_list->ExpandAll();
			}
		}
    }
	//-----------------------------------------------------------------------
	void MainForm::updateGameSetting()
	{
		IDisplay* display = CoreManager::getInstance().getEngineMain()->display();

		display->setTerrainColorMappingEnabled( terrain_color_check->Checked );
		display->setTerrainNormalMappingEnabled( terrain_normal_check->Checked );
		display->setTerrainSpecularMappingEnabled( terrain_spec_check->Checked );
		display->setTerrainParallaxMappingEnabled( terrain_offset_check->Checked );
		display->setTerrainLightmapEnabled( terrain_shadow_check->Checked );

		if ( rb_tex_filter_none->Checked )
		{
			display->setTerrainTextureFiltering( TFL_NONE );
		}else
			if ( rb_tex_filter_bline->Checked )
			{
				display->setTerrainTextureFiltering( TFL_BILINEAR );
			}else
				if ( rb_tex_filter_3line->Checked )
				{
					display->setTerrainTextureFiltering( TFL_TRILINEAR );
				}else
					if ( rb_tex_filter_anisotropic->Checked )
					{
						display->setTerrainTextureFiltering( TFL_ANISOTROPIC );
					}

					//----------------------------------------------------------

					Flt mipmapBias = TypeConverter::StrToDouble( txt_mipmap_bias->Text );
					display->setTerrainMipmapBias(mipmapBias);

					//----------------------------------------------------------

					if ( rb_fog_none->Checked )
					{
						display->setFogLevel(FOL_NONE);
					}else
						if ( rb_fog_line->Checked )
						{
							display->setFogLevel(FOL_LINEAR);
						}else
						{
							display->setFogLevel(FOL_EXP);
						}

						//----------------------------------------------------------

						/*if ( model_renderhigh_check->Checked )
						{
							display->setEntityRenderLevel(RDL_HIGH);
						}else
						{
							display->setEntityRenderLevel(RDL_LOW);
						}*/

						//----------------------------------------------------------

						if ( gamma_check->Checked )
						{
							display->setGammaEnabled(true);
						}else
						{
							display->setGammaEnabled(false);
						}

						//----------------------------------------------------------

						Str fsaaHint;
						U32 fsaa = TypeConverter::StrToU32( fsaa_txt->Text );
						display->setFSAA(fsaa, fsaaHint);

						//----------------------------------------------------------

						Flt scale = TypeConverter::StrToDouble( sbs_scale_txt->Text );
						Flt bias = TypeConverter::StrToDouble( sbs_bias_txt->Text );
						Flt specular = TypeConverter::StrToDouble( sbs_specular_txt->Text );
						display->setScaleBiasSpecular(Vec4(1,scale,bias,specular));

						//----------------------------------------------------------
						//if ( rb_shadow_none->Checked )
						//{
						//	display->setShadowLevel(  );
						//}else
						//	if ( rb_shadow_low->Checked )
						//	{
						//		display->setShadowLevel( SDL_LOW );
						//	}else
						//		if ( rb_shadow_medium->Checked )
						//		{
						//			display->setShadowLevel( SDL_MEDIUM );
						//		}else
						//			if ( rb_shadow_high->Checked )
						//			{
						//				display->setShadowLevel( SDL_HIGH );
						//			}
	}

	//----------------------------------------------------------------------
	void MainForm::applyGameSetting()
	{
		updateGameSetting();
		IDisplay* display = CoreManager::getInstance().getEngineMain()->display();
		display->apply();
	}
	//-----------------------------------------------------------------------
	void MainForm::loadSceneEnvironmentLight()
	{
		MG::Color ambient;
		ambient = CoreManager::getInstance().getScene()->getAmbientLight();

		light_ambient_r_edit->Text = TypeConverter::DoubleToStr(ambient.r);
		light_ambient_g_edit->Text = TypeConverter::DoubleToStr(ambient.g);
		light_ambient_b_edit->Text = TypeConverter::DoubleToStr(ambient.b);

		ILight* light = CoreManager::getInstance().getScene()->getDefaultLight();
		if (light)
		{
			MG::Color diffuse;
			diffuse = light->getDiffuseColour();
			light_diffuse_r_edit->Text = TypeConverter::DoubleToStr(diffuse.r);
			light_diffuse_g_edit->Text = TypeConverter::DoubleToStr(diffuse.g);
			light_diffuse_b_edit->Text = TypeConverter::DoubleToStr(diffuse.b);

			MG::Color spec;
			spec = light->getSpecularColour();
			light_spec_r_edit->Text = TypeConverter::DoubleToStr(spec.r);
			light_spec_g_edit->Text = TypeConverter::DoubleToStr(spec.g);
			light_spec_b_edit->Text = TypeConverter::DoubleToStr(spec.b);

		}

	}
	//-----------------------------------------------------------------------
	void MainForm::configSceneEnvironmentLight()
	{
		MG::Color ambient;

		ambient.r = TypeConverter::StrToDouble(light_ambient_r_edit->Text);
		ambient.g = TypeConverter::StrToDouble(light_ambient_g_edit->Text);
		ambient.b = TypeConverter::StrToDouble(light_ambient_b_edit->Text);      

		CoreManager::getInstance().getScene()->setAmbientLight( ambient );

		ILight* light = CoreManager::getInstance().getScene()->getDefaultLight();
		if (light)
		{
			MG::Color diffuse;
			diffuse.r = TypeConverter::StrToDouble(light_diffuse_r_edit->Text);
			diffuse.g = TypeConverter::StrToDouble(light_diffuse_g_edit->Text);
			diffuse.b = TypeConverter::StrToDouble(light_diffuse_b_edit->Text);   
			light->setDiffuseColour(diffuse);

			MG::Color spec;
			spec.r = TypeConverter::StrToDouble(light_spec_r_edit->Text);
			spec.g = TypeConverter::StrToDouble(light_spec_g_edit->Text);
			spec.b = TypeConverter::StrToDouble(light_spec_b_edit->Text);  
			light->setSpecularColour(spec);

		}
	}
	//-----------------------------------------------------------------------
	void MainForm::configSceneLightDirection()
	{
		ICamera* cam = CoreManager::getInstance().getScene()->getActiveCamera();
		ILight* light = CoreManager::getInstance().getScene()->getDefaultLight();
		if (light&&cam)
		{
			Vec3 dir;
			cam->getDirection(dir);
			light->setDirection(dir);
		}
	}
	//-----------------------------------------------------------------------
	void MainForm::loadSceneGameConfig()
	{
		ICamera* cam = CoreManager::getInstance().getScene()->getActiveCamera();
		if (cam)
		{
			Flt fov = cam->getFov();  
			fov_edit->Text = TypeConverter::DoubleToStr(fov);
		}
	}
	//-----------------------------------------------------------------------
	void MainForm::configSceneGameConfig()
	{
		IDisplay* display = CoreManager::getInstance().getEngineMain()->display();

		ICamera* cam = CoreManager::getInstance().getScene()->getActiveCamera();
		Flt fov = TypeConverter::StrToDouble(fov_edit->Text);  

		if (cam)
		{
			cam->setFov(fov);
		}

		////////////////////////////////////////////////////////////////////////////

		if ( ckb_wireframe->Checked )
		{
			display->setWireframeMode( true );
		}else
		{
			display->setWireframeMode( false );
		}

		////////////////////////////////////////////////////////////////////////////


		if ( ckb_terrain_grids_visible->Checked )
		{
			display->setTerrainGridsVisible( true );
		}else
		{
			display->setTerrainGridsVisible( false );
		}

		////////////////////////////////////////////////////////////////////////////

		display->apply();


	}
	//-----------------------------------------------------------------------
	void MainForm::restoreMapInstanceConfig(I32 iMapID)
	{
		MapListCsvInfo* mapInstanceInfo = MapListCsv::getInstance().getInfoByMapId((MapIdType)iMapID);
		if ( !mapInstanceInfo )
			return;

		ArtMapResCsvInfo* mapResInfo = ArtMapResCsv::getInstance().getArtMapResInfoById( mapInstanceInfo->artMapResId );
		if ( !mapResInfo )
			return;

		UInt cameraId = mapResInfo->slgCameraId;
		if (cameraId == 0)
			cameraId = mapResInfo->rpgCameraId;
		const GameCameraConfigInfo* config = GameCameraConfig::getInstance().getGameCameraConfigInfo( cameraId );
		if ( config )

		//设置镜头参数
		{	
			OperationManager::getInstance().setCameraDefaultPitch( config->camera_default_pitch );
			OperationManager::getInstance().setCameraPitchRange( config->camera_min_pitch, config->camera_max_pitch );
			OperationManager::getInstance().setCameraMoveBoard( config->camera_min_board, config->camera_max_board );
			OperationManager::getInstance().setCameraSpeed( config->camera_move_speed, config->camera_roll_speed );
			OperationManager::getInstance().revertCamera();
		}

		//设置其他参数
	}
	//-----------------------------------------------------------------------
	void MainForm::onEventSelectTab(Int index)
	{
		if ( index > 0 && index < 4 )
		{
			this->prop_tab_ctrl->SelectTab(index - 1);
		}
	}
	//-----------------------------------------------------------------------
	void MainForm::onEventCamspeedChanged(UInt level)
	{
		CamSpeed->Text = TypeConverter::U32ToStr(level);
	}
	//-----------------------------------------------------------------------
	void MainForm::onEventOpenLoadMapForm()
	{
		if ( FormSet::mapload_form )
			FormSet::mapload_form->openForm();
	}
	//-----------------------------------------------------------------------
	void MainForm::loadObjectList()
	{
		//初始化窗口右边Tab中的的基础模型列表。	
		////////////////////////////////////////////////////////////
		object_model_create_tree->Nodes->Clear();
		////////////////////////////////////////////////////////////

		std::map<Str16, std::vector<CharacterTempInfo*>> charTempGroups;
		std::map<U32, CharacterTempInfo*>& charTempList = CharacterTemplate::getInstance().mMapCharacterTempInfoNew;

		for ( std::map<U32, CharacterTempInfo*>::iterator iter = charTempList.begin(); 
			iter != charTempList.end(); iter++)
		{
			CharacterTempInfo* charInfo = iter->second;

			if ( charInfo && charInfo->CharacterType == CHARACTER_TYPE_OBJ && charInfo->isValid() )
			{
				charTempGroups[charInfo->getCharacterListName()].push_back( charInfo );
			}	
		}

		for ( std::map<Str16, std::vector<CharacterTempInfo*>>::iterator group_iter = charTempGroups.begin(); 
			group_iter != charTempGroups.end(); group_iter++ )
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//确定组名

			const Str16& groupName = group_iter->first;
			std::vector<CharacterTempInfo*>& group = group_iter->second;

			String^ groupNodeName = "ObjectGroupNode_" + TypeConverter::Char16ToStr(groupName.c_str());
			TreeNode^ groupNode = gcnew TreeNode(groupNodeName);
			object_model_create_tree->Nodes->Add(groupNode);

			groupNode->Text = TypeConverter::Char16ToStr(groupName.c_str());

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			for ( U32 obj_index = 0; obj_index < group.size(); obj_index++ )
			{
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//组别分割

				CharacterTempInfo* charInfo = group[obj_index];

				ModelDeclaration* decl = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( charInfo->getCharacterArtMashId() );

				if ( decl )
				{
					Str16 mesh_name;
					MG::MGStrOp::toString(decl->name.c_str(), mesh_name);

					String^ leafNodeName = "ObjectLeafNode_" + TypeConverter::IntToStr( obj_index );
					TreeNode^ leafNode = gcnew TreeNode(leafNodeName);
					groupNode->Nodes->Add( leafNode );

					Str16 text = charInfo->getCharacterSurName() + 
						L" " + charInfo->getCharacterTitle() + 
						L" " + mesh_name;

					leafNode->Text  = TypeConverter::Char16ToStr(text.c_str());
					leafNode->Tag   = TypeConverter::IntToStr(charInfo->getCharacterTempId() );
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}

		object_model_create_tree->Sort();
		//object_model_create_tree->ExpandAll();

	}
	//-----------------------------------------------------------------------
	void MainForm::clearObjectList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::selectObjectFromList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::saveObjectUpdate()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::loadNpcList()
	{
		//初始化窗口右边Tab中的的NPC列表。
		////////////////////////////////////////////////////////////
		NPC_model_create_tree->Nodes->Clear();
		////////////////////////////////////////////////////////////

		std::map<Str16, std::vector<CharacterTempInfo*>> charTempGroups;
		std::map<U32, CharacterTempInfo*>& charTempList = CharacterTemplate::getInstance().mMapCharacterTempInfoNew;

		for ( std::map<U32, CharacterTempInfo*>::iterator iter = charTempList.begin(); 
			iter != charTempList.end(); iter++)
		{
			CharacterTempInfo* charInfo = iter->second;

			if ( charInfo && charInfo->CharacterType == CHARACTER_TYPE_NPC && charInfo->isValid() )
			{
				charTempGroups[charInfo->getCharacterListName()].push_back( charInfo );
			}
		}

		for ( std::map<Str16, std::vector<CharacterTempInfo*>>::iterator group_iter = charTempGroups.begin(); 
			group_iter != charTempGroups.end(); group_iter++ )
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//确定组名

			const Str16& groupName = group_iter->first;
			std::vector<CharacterTempInfo*>& group = group_iter->second;

			String^ groupNodeName = "NpcGroupNode_" + TypeConverter::Char16ToStr(groupName.c_str());
			TreeNode^ groupNode = gcnew TreeNode(groupNodeName);
			NPC_model_create_tree->Nodes->Add(groupNode);

			groupNode->Text = TypeConverter::Char16ToStr(groupName.c_str());

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			for ( U32 npc_index = 0; npc_index < group.size(); npc_index++ )
			{
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//组别分割

				CharacterTempInfo* charInfo = group[npc_index];

				ModelDeclaration* decl = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( charInfo->getCharacterArtMashId() );

				if ( decl )
				{
					Str16 mesh_name;
					MG::MGStrOp::toString(decl->name.c_str(), mesh_name);

					String^ leafNodeName = "NpcLeafNode_" + TypeConverter::IntToStr( npc_index );
					TreeNode^ leafNode = gcnew TreeNode(leafNodeName);
					groupNode->Nodes->Add( leafNode );

					Str16 text = charInfo->getCharacterSurName() + charInfo->getNpcName() + 
						/*L" （字 " + charInfo->getNpcZhiName() + L") " + */charInfo->getCharacterTitle() + 
						L" " + mesh_name;

					leafNode->Text  = TypeConverter::Char16ToStr(text.c_str());
					leafNode->Tag   = TypeConverter::IntToStr(charInfo->getCharacterTempId() );
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}

		NPC_model_create_tree->Sort();
		//NPC_model_create_tree->ExpandAll();
	}
	//-----------------------------------------------------------------------
	void MainForm::clearNpcList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::selectNpcFromList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::saveNpcUpdate()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::loadMonsterList()
	{
		//初始化窗口右边Tab中的的Monster列表。	
		////////////////////////////////////////////////////////////
		monster_model_create_tree->Nodes->Clear();
		////////////////////////////////////////////////////////////

		std::map<Str16, std::vector<CharacterTempInfo*>> charTempGroups;
		std::map<U32, CharacterTempInfo*>& charTempList = CharacterTemplate::getInstance().mMapCharacterTempInfoNew;

		for ( std::map<U32, CharacterTempInfo*>::iterator iter = charTempList.begin(); 
			iter != charTempList.end(); iter++)
		{
			CharacterTempInfo* charInfo = iter->second;

			if ( charInfo && charInfo->CharacterType == CHARACTER_TYPE_MONSTER && charInfo->isValid() )
			{
				charTempGroups[charInfo->getCharacterListName()].push_back( charInfo );
			}			
		}

		for ( std::map<Str16, std::vector<CharacterTempInfo*>>::iterator group_iter = charTempGroups.begin(); 
			group_iter != charTempGroups.end(); group_iter++ )
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//确定组名

			const Str16& groupName = group_iter->first;
			std::vector<CharacterTempInfo*>& group = group_iter->second;

			String^ groupNodeName = "MonsterGroupNode_" + TypeConverter::Char16ToStr(groupName.c_str());
			TreeNode^ groupNode = gcnew TreeNode(groupNodeName);
			monster_model_create_tree->Nodes->Add(groupNode);

			groupNode->Text = TypeConverter::Char16ToStr(groupName.c_str());

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			for ( U32 monster_index = 0; monster_index < group.size(); monster_index++ )
			{
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//组别分割

				CharacterTempInfo* charInfo = group[monster_index];

				ModelDeclaration* decl = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( charInfo->getCharacterArtMashId() );

				if ( decl )
				{
					Str16 mesh_name;
					MG::MGStrOp::toString(decl->name.c_str(), mesh_name);

					String^ leafNodeName = "MonsterLeafNode_" + TypeConverter::IntToStr( monster_index );
					TreeNode^ leafNode = gcnew TreeNode(leafNodeName);
					groupNode->Nodes->Add( leafNode );

					Str16 text = charInfo->getCharacterSurName() + charInfo->getMonsterName() + 
						/*L" （字 " + charInfo->getMonsterZhiName() + L") " + */charInfo->getCharacterTitle() + 
						L" " + mesh_name;

					leafNode->Text  = TypeConverter::Char16ToStr(text.c_str());
					leafNode->Tag   = TypeConverter::IntToStr(charInfo->getCharacterTempId() );
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}

		monster_model_create_tree->Sort();
		//monster_model_create_tree->ExpandAll();
	}
	//-----------------------------------------------------------------------
	void MainForm::clearMonsterList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::selectMonsterFromList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::saveMonsterUpdate()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::loadPlaceList()
	{
		////////////////////////////////////////////////////////////

		//初始化窗口右边Tab中的的据点列表。

		////////////////////////////////////////////////////////////

		place_model_create_tree->Nodes->Clear();

		////////////////////////////////////////////////////////////


		std::map<Str16, std::vector<const PlaceListCsvInfo*>> placeInfoGroups;
		std::map<PlaceIdType, PlaceListCsvInfo*>* placeList = PlaceListCsv::getInstance().getList();

		if ( placeList )
		{
			std::map<PlaceIdType, PlaceListCsvInfo*>::iterator iter = placeList->begin();

			for ( ; iter != placeList->end() ; iter ++ )
			{
				PlaceListCsvInfo* placeInfo = iter->second;
				if ( placeInfo )
				{
					placeInfoGroups[placeInfo->placeListName].push_back(placeInfo);
				}
			}
		}

		for ( std::map<Str16, std::vector<const PlaceListCsvInfo*>>::iterator group_iter = placeInfoGroups.begin(); 
			group_iter != placeInfoGroups.end(); group_iter++ )
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//确定组名

			const Str16& groupName = group_iter->first;
			std::vector<const PlaceListCsvInfo*>& group = group_iter->second;

			String^ groupNodeName = "PlaceGroupNode_" + TypeConverter::Char16ToStr(groupName.c_str());
			TreeNode^ groupNode = gcnew TreeNode(groupNodeName);
			place_model_create_tree->Nodes->Add(groupNode);

			groupNode->Text = TypeConverter::Char16ToStr(groupName.c_str());

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			for ( U32 place_index = 0; place_index < group.size(); place_index++ )
			{
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//组别分割
				const PlaceListCsvInfo* placeInfo = group[place_index];

				ModelDeclaration* decl = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( placeInfo->artMashResId );

				if ( decl )
				{
					Str16 mesh_name;
					MG::MGStrOp::toString(decl->name.c_str(), mesh_name);

					String^ leafNodeName = "PlaceNode_" + TypeConverter::IntToStr(place_index);
					TreeNode ^ leafNode = gcnew TreeNode(leafNodeName);
					groupNode->Nodes->Add( leafNode );

					Str16 text = placeInfo->placeName + L" " +  placeInfo->placeTitle + L" " + placeInfo->placeText + L" " + mesh_name;
					leafNode->Text  = TypeConverter::Char16ToStr(text.c_str());
					leafNode->Tag   = TypeConverter::U32ToStr(placeInfo->placeId);
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
			//groupNode->TreeView->Sort();
		}

		//place_model_create_tree->Sort();
		//place_model_create_tree->ExpandAll();	
	}
	//-----------------------------------------------------------------------
	void MainForm::clearPlaceList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::selectPlaceFromList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::savePlaceUpdate()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::loadPointList()
	{
		//初始化窗口右边Tab中的的据点列表。
		////////////////////////////////////////////////////////////
		point_model_create_tree->Nodes->Clear();
		////////////////////////////////////////////////////////////

		std::map<Str16, std::vector<const PointTempInfo*>> pointInfoGroups;
		U32 count = PointTemplate::getInstance().getNumPointTempInfos();

		for ( U32 index = 0; index < count; index++ )
		{
			const PointTempInfo* pointInfo = PointTemplate::getInstance().getPointTempInfoByIndex( index );
			if ( pointInfo )
			{
				pointInfoGroups[pointInfo->ListName].push_back(pointInfo);
			}
		}

		for ( std::map<Str16, std::vector<const PointTempInfo*>>::iterator group_iter = pointInfoGroups.begin(); 
			group_iter != pointInfoGroups.end(); group_iter++ )
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//确定组名

			const Str16& groupName = group_iter->first;
			std::vector<const PointTempInfo*>& group = group_iter->second;

			String^ groupNodeName = "PointGroupNode_" + TypeConverter::Char16ToStr(groupName.c_str());
			TreeNode^ groupNode = gcnew TreeNode(groupNodeName);
			point_model_create_tree->Nodes->Add(groupNode);

			groupNode->Text = TypeConverter::Char16ToStr(groupName.c_str());

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			for ( U32 point_index = 0; point_index < group.size(); point_index++ )
			{
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//组别分割
				const PointTempInfo* pointInfo = group[point_index];

				ModelDeclaration* decl = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( pointInfo->ArtMashId );

				if ( decl )
				{
					Str16 mesh_name;
					MG::MGStrOp::toString(decl->name.c_str(), mesh_name);

					String^ leafNodeName = "pointNode_" + TypeConverter::IntToStr(point_index);
					TreeNode ^ leafNode = gcnew TreeNode(leafNodeName);
					groupNode->Nodes->Add( leafNode );

					Str16 text = pointInfo->Name + L" " + L" " + mesh_name;
					leafNode->Text  = TypeConverter::Char16ToStr(text.c_str());
					leafNode->Tag   = TypeConverter::U32ToStr(pointInfo->PointTemplateId);
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}

		point_model_create_tree->Sort();
		//point_model_create_tree->ExpandAll();
		
	}
	//-----------------------------------------------------------------------
	void MainForm::clearPointList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::selectPointFromList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::savePointUpdate()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::loadTroopList()
	{
		//初始化窗口右边Tab中的的军队列表。
		////////////////////////////////////////////////////////////
		troop_model_create_tree->Nodes->Clear();
		////////////////////////////////////////////////////////////

		std::map<Str16, std::vector<CharacterTempInfo*>> charTempGroups;
		std::map<U32, CharacterTempInfo*>& charTempList = CharacterTemplate::getInstance().mMapCharacterTempInfoNew;

		for ( std::map<U32, CharacterTempInfo*>::iterator iter = charTempList.begin(); 
			iter != charTempList.end(); iter++)
		{
			CharacterTempInfo* charInfo = iter->second;

			if ( charInfo && charInfo->CharacterType == CHARACTER_TYPE_ARMY && charInfo->isValid() )
			{
				charTempGroups[charInfo->getCharacterListName()].push_back( charInfo );
			}	
		}

		for ( std::map<Str16, std::vector<CharacterTempInfo*>>::iterator group_iter = charTempGroups.begin(); 
			group_iter != charTempGroups.end(); group_iter++ )
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//确定组名

			const Str16& groupName = group_iter->first;
			std::vector<CharacterTempInfo*>& group = group_iter->second;

			String^ groupNodeName = "ArmyGroupNode_" + TypeConverter::Char16ToStr(groupName.c_str());
			TreeNode^ groupNode = gcnew TreeNode(groupNodeName);
			troop_model_create_tree->Nodes->Add(groupNode);

			groupNode->Text = TypeConverter::Char16ToStr(groupName.c_str());

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			for ( U32 army_index = 0; army_index < group.size(); army_index++  )
			{
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//组别分割

				CharacterTempInfo* charInfo = group[army_index];

				ModelDeclaration* decl = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( charInfo->getCharacterArtMashId() );

				if ( decl )
				{
					Str16 mesh_name;
					MG::MGStrOp::toString(decl->name.c_str(), mesh_name);

					String^ leafNodeName = "ArmyLeafNode_" + TypeConverter::IntToStr( army_index );
					TreeNode^ leafNode = gcnew TreeNode(leafNodeName);
					groupNode->Nodes->Add( leafNode );

					Str16 text = charInfo->getCharacterSurName() + L" " + charInfo->getCharacterTitle() + L" " + mesh_name;

					leafNode->Text  = TypeConverter::Char16ToStr(text.c_str());
					leafNode->Tag   = TypeConverter::IntToStr(charInfo->getCharacterTempId() );
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}

		troop_model_create_tree->Sort();

		//troop_model_create_tree->ExpandAll();
	}
	//-----------------------------------------------------------------------
	void MainForm::clearTroopList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::selectTroopFromList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::saveTroopUpdate()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::loadBuildingList()
	{
		//初始化窗口右边Tab中的建筑列表。
		////////////////////////////////////////////////////////////
		building_model_create_tree->Nodes->Clear();
		////////////////////////////////////////////////////////////

		std::map<Str16, std::vector<CharacterTempInfo*>> charTempGroups;
		std::map<U32, CharacterTempInfo*>& charTempList = CharacterTemplate::getInstance().mMapCharacterTempInfoNew;

		for ( std::map<U32, CharacterTempInfo*>::iterator iter = charTempList.begin(); 
			iter != charTempList.end(); iter++)
		{
			CharacterTempInfo* charInfo = iter->second;

			if ( charInfo && charInfo->CharacterType == CHARACTER_TYPE_BUILD && charInfo->isValid() )
			{
				charTempGroups[charInfo->getCharacterListName()].push_back( charInfo );
			}	
		}

		for ( std::map<Str16, std::vector<CharacterTempInfo*>>::iterator group_iter = charTempGroups.begin(); 
			group_iter != charTempGroups.end(); group_iter++ )
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//确定组名

			const Str16& groupName = group_iter->first;
			std::vector<CharacterTempInfo*>& group = group_iter->second;

			String^ groupNodeName = "BuildGroupNode_" + TypeConverter::Char16ToStr(groupName.c_str());
			TreeNode^ groupNode = gcnew TreeNode(groupNodeName);
			building_model_create_tree->Nodes->Add(groupNode);

			groupNode->Text = TypeConverter::Char16ToStr(groupName.c_str());

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////

			for ( U32 build_index = 0; build_index < group.size(); build_index++  )
			{
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//组别分割

				CharacterTempInfo* charInfo = group[build_index];

				ModelDeclaration* decl = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclaration( charInfo->getCharacterArtMashId() );

				if ( decl )
				{
					Str16 mesh_name;
					MG::MGStrOp::toString(decl->name.c_str(), mesh_name);

					String^ leafNodeName = "BuildLeafNode_" + TypeConverter::IntToStr( build_index );
					TreeNode^ leafNode = gcnew TreeNode(leafNodeName);
					groupNode->Nodes->Add( leafNode );

					Str16 text = charInfo->getCharacterSurName() + L" " + mesh_name;

					leafNode->Text  = TypeConverter::Char16ToStr(text.c_str());
					leafNode->Tag   = TypeConverter::IntToStr(charInfo->getCharacterTempId() );
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}

		building_model_create_tree->Sort();
		//building_model_create_tree->ExpandAll();
	}
	//-----------------------------------------------------------------------
	void MainForm::clearBuildingList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::selectBuildingFromList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::saveBuildingUpdate()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::clearGeneralList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::selectGeneralFromList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::saveGeneralUpdate()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::loadStaticObjectList()
	{
		//初始化窗口右边Tab中的事件触发点列表。
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static_object_model_create_tree->Nodes->Clear();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::map<Str8, std::vector<ModelDeclaration*>> staticObjectGroups;

		UInt count = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclarationCount();

		for ( UInt index=0; index<count ; index++ )
		{
			ModelDeclaration* decl = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclarationByIndex(index);

			if ( decl )
			{
				staticObjectGroups[decl->group].push_back( decl );
			}
		}

		////排序
		//std::map<Str8, std::vector<ModelDeclaration*>>::iterator declIter = staticObjectGroups.begin();
		//for(declIter; declIter != staticObjectGroups.end(); declIter++)
		//{
		//	sort(declIter->second.begin(),declIter->second.end(),declLessCompare);
		//}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////

		for ( std::map<Str8, std::vector<ModelDeclaration*>>::iterator group_iter = staticObjectGroups.begin(); 
			group_iter != staticObjectGroups.end(); group_iter++ )
		{
			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			//确定组名

			const Str8& groupName = group_iter->first;
			std::vector<ModelDeclaration*>& group = group_iter->second;

			String^ groupNodeName = "StaticObjectGroupNode_" + TypeConverter::Char8ToStr(groupName.c_str());
			TreeNode^ groupNode = gcnew TreeNode(groupNodeName);
			static_object_model_create_tree->Nodes->Add(groupNode);

			groupNode->Text = TypeConverter::Char8ToStr(groupName.c_str());

			//////////////////////////////////////////////////////////////////////////////////////////////////////////

			for ( U32 static_index = 0; static_index < group.size(); static_index++  )
			{
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//组别分割

				ModelDeclaration* decl = group[static_index];

				if ( decl )
				{
					Str16 mesh_name;
					MG::MGStrOp::toString(decl->name.c_str(), mesh_name);

					String^ leafNodeName = "StaticObjectLeafNode_" + TypeConverter::IntToStr( static_index );
					TreeNode^ leafNode = gcnew TreeNode(leafNodeName);
					groupNode->Nodes->Add( leafNode );

					Str16 text = mesh_name;

					leafNode->Text  = TypeConverter::Char16ToStr(text.c_str());
					leafNode->Tag   = TypeConverter::IntToStr(decl->id );
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}

		static_object_model_create_tree->Sort();

		//static_object_model_create_tree->ExpandAll();
	}
	//-----------------------------------------------------------------------
	void MainForm::clearStaticObjectList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::selectStaticObjectFromList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::saveStaticObjectUpdate()
	{

	}

	//-----------------------------------------------------------------------
	void MainForm::loadEffectDeclarationList()
	{
		////////////////////////////////////////////////////////////
		effect_create_tree->Nodes->Clear();
		////////////////////////////////////////////////////////////

		IResourceManager* resMgr = CoreManager::getInstance().getEngineMain()->resourceMgr();

		UInt count = resMgr->getEffectResourceDeclarationCount();

		for (UInt i = 0; i < count; ++i)
		{
			////////////////////////////////////////////////////////////

			EffectResourceDeclaration* effectDecl = resMgr->getEffectResourceDeclarationByIndex(i, false);

			String^ declNodeName = "Node" + TypeConverter::IntToStr( i );
			TreeNode^ effectNode = gcnew TreeNode( declNodeName );

			Str text = effectDecl->name;// + " " + effectDecl->filePath + " " + effectDecl->fileName;

			effectNode->Text	= TypeConverter::Char8ToStr(text.c_str());
			effectNode->Tag		= TypeConverter::IntToStr(effectDecl->ResID);

			////////////////////////////////////////////////////////////

			effect_create_tree->Nodes->Add(effectNode);
		}

		effect_create_tree->Sort();
		//effect_create_tree->ExpandAll();
	}

	//-----------------------------------------------------------------------
	void MainForm::prepareCreateEffect()
	{
		if ( effect_create_tree->SelectedNode != nullptr &&
			effect_create_tree->SelectedNode->Tag != nullptr )
		{
			String^ tag = effect_create_tree->SelectedNode->Tag->ToString();
			if ( !String::IsNullOrEmpty(tag) )
			{
				if ( effect_create_tree->SelectedNode->Parent )
					mCurrSelectCreateEffectTreeNode = effect_create_tree->SelectedNode->Parent;

				U32 effectDeclID = TypeConverter::StrToInt( tag );
				EffectResourceDeclaration* decl = NULL;
				decl =  CoreManager::getInstance().getEngineMain()->resourceMgr()->getEffectResourceDeclaration( effectDeclID );
				if ( decl != NULL )
				{
					std::string msg = decl->name + "\n" +decl->filePath + "\\" + decl->fileName;
					prepare_effect_text->Text = TypeConverter::Char8ToStr( msg.c_str() );
				}

				OperationManager::getInstance().prepareCreateSceneObject( effectDeclID );
			}
		}
	}

	//-----------------------------------------------------------------------
	void MainForm::loadRegionList()
	{
		//初始化窗口右边Tab中的区域列表。
		////////////////////////////////////////////////////////////
		//region_model_create_tree->Nodes->Clear();
		////////////////////////////////////////////////////////////
	}
	//-----------------------------------------------------------------------
	void MainForm::clearRegionList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::selectRegionFromList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::saveRegionUpdate()
	{

	}

	//-----------------------------------------------------------------------
	void MainForm::resetObjectTabList(I32 mapType)
	{
		create_static_page->Enabled = false;
		create_place_page->Enabled = false;
		create_npc_page->Enabled = false;
		create_troop_page->Enabled = false;
		create_object_page->Enabled = false;
		create_monster_page->Enabled = false;
		create_building_page->Enabled = false;
		create_point_page->Enabled = false;
		create_effect_page->Enabled = false;

		if ( mapType == (I32)MT_Distribution )
		{
			create_static_page->Enabled = true;
			create_point_page->Enabled = true;
			create_npc_page->Enabled = true;
			create_place_page->Enabled = true;
			create_effect_page->Enabled = true;
		}
		else if ( mapType == (I32)MT_Place )
		{
			create_static_page->Enabled = true;
			create_npc_page->Enabled = true;
			create_troop_page->Enabled = true;
			create_object_page->Enabled = true;
			create_monster_page->Enabled = true;
			create_building_page->Enabled = true;
			create_point_page->Enabled = true;
			create_effect_page->Enabled = true;
		}
		else if ( mapType == (I32)MT_Building)
		{
			create_static_page->Enabled = true;
			create_monster_page->Enabled = true;
			create_npc_page->Enabled = true;
			create_object_page->Enabled = true;
			create_effect_page->Enabled = true;
		}
		else
		{
			create_static_page->Enabled = true;
			create_place_page->Enabled = true;
			create_npc_page->Enabled = true;
			create_troop_page->Enabled = true;
			create_object_page->Enabled = true;
			create_monster_page->Enabled = true;
			create_building_page->Enabled = true;
			create_point_page->Enabled = true;
			create_effect_page->Enabled = true;
		}
	}

	//-----------------------------------------------------------------------
	void MainForm::showCursorElement()
	{
		//OperationManager::getInstance().showCursorElement();
	}

	//-----------------------------------------------------------------------
	void MainForm::hideCursorElement()
	{
		//OperationManager::getInstance().hideCursorElement();
	}
}

