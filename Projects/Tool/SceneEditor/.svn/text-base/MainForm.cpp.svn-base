#include "StdAfx.h"
#include "MainForm.h"
#include "GlobalOptions.h"
#include "CoreManager.h"
#include "Utility.h"
#include "XmlHelper.h"
#include "OperationManager.h"
#include "AppDataConfig.h"
#include "ICollisionSystem.h"

namespace SceneEditor {

	//------------------------------------------------------------------------
	//此函数仅用于排序模型列表
	bool declLessCompare(ModelDeclaration* decl1,ModelDeclaration* decl2)
	{
		Str name1 = decl1->name;
		Str name2 = decl2->name;
		std::vector<Str> name1Parts,name2Parts;
		size_t pos;
		int n1=0;
		while ((pos = name1.find_first_of('-')) != std::string::npos)
		{
			Str part = name1.substr(0,pos);
			name1Parts.push_back(part);
			name1 = name1.substr(pos+1);
		}
		if (n1 > 0)
		{
			pos = name1.find_last_not_of('_');
			Str lastPart = name1.substr(pos+1);
			name1Parts.push_back(lastPart);
		}

		int n2 = 0;
		while ((pos = name2.find_first_of('-')) != std::string::npos)
		{
			Str part = name2.substr(0,pos);
			name2Parts.push_back(part);
			name2 = name2.substr(pos+1);
		}
		if (n2 > 0)
		{
			pos = name2.find_last_not_of('_');
			Str lastPart = name2.substr(pos+1);
			name2Parts.push_back(lastPart);
		}

		int minSize = min(name1Parts.size(),name2Parts.size());

		if (minSize == 0)
			return decl1->name < decl2->name;
		else
		{
			for (int i=0; i<minSize; i++)
			{
				if (name1Parts[i] != name2Parts[i])
				{
					return name1Parts[i] < name2Parts[i];
				}
			}

			return decl1->name < decl2->name;
		}
	}

	//------------------------------------------------------------------------
	//此函数仅用于排序特效列表
	bool effectDeclLessCompare(EffectResourceDeclaration* decl1,EffectResourceDeclaration* decl2)
	{
		return decl1->name < decl2->name;
	}

	//------------------------------------------------------------------------
	//此函数仅用于排序树资源列表
	bool treeDeclLessCompare(TreeDeclaration* decl1,TreeDeclaration* decl2)
	{
		return decl1->strName < decl2->strName;
	}

	//------------------------------------------------------------------------
	//此函数仅用于排序草资源列表
	bool grassDeclLessCompare(GrassDeclaration* decl1,GrassDeclaration* decl2)
	{
		return decl1->strName < decl2->strName;
	}

    //-----------------------------------------------------------------------
    void MainForm::initialize()
    {
        mFormOpState              = MOS_NULL;
        mCurrSceneObjectXmlFormat = NULL;
        setSceneFormLocation();
        loadModelDeclarationList();
        loadTreeDeclarationList();
		loadEffectDeclarationList();
        loadWaterTemplateList();
		loadBatchTreeList();
		loadBatchGrassList();
        mCurrSelectCreateModelTreeNode = nullptr;

		CoreManager::getInstance().getEngineMain()->lockTreeManager();
    }
    //-----------------------------------------------------------------------
    void MainForm::clearAll()
    {
		unloadSubScene();
        clearSceneElementProps();
        clearSceneEntityList();
		clearSceneEffectList();
		clearScenePlantList();

		mIsSceneLoaded = false;
    }
    //-----------------------------------------------------------------------
    void MainForm::revert()
    {
        CoreManager::getInstance().getScene()->getSceneObjectController()->setFocus( NULL );
        clearSceneElementProps();
        loadSceneEntityList();
		loadSceneEffectList();
    }
    //-----------------------------------------------------------------------
    void MainForm::update()
    {
        checkSceneElementProps();
        updateCameraHint();
		updateMouseHint();
        mFormOpState = MOS_NULL;
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
    void MainForm::openGameDataEditor()
    {
        if ( FormSet::gameData_form == nullptr)
        {
            FormSet::gameData_form  = gcnew GameDataEditorForm();
            FormSet::gameData_form->CreateControl();
            FormSet::gameData_form->initialize();
            FormSet::gameData_form->Show();
        }
    }
    //-----------------------------------------------------------------------
    void MainForm::openTerrainTextureEditor()
    {
        if ( FormSet::terrainTexture_form == nullptr)
        {
            FormSet::terrainTexture_form  = gcnew TerrainTextureForm();
            FormSet::terrainTexture_form->CreateControl();
            FormSet::terrainTexture_form->initialize();
            FormSet::terrainTexture_form->Show();
        }
    }
	//-----------------------------------------------------------------------
	void MainForm::openWaterEffectEditor()
	{
		if ( FormSet::waterEditor_form == nullptr)
		{
			FormSet::waterEditor_form  = gcnew WaterEditor();
			FormSet::waterEditor_form->CreateControl();
			FormSet::waterEditor_form->initialize();
			FormSet::waterEditor_form->Show();
		}
	}
	//-----------------------------------------------------------------------
	//功能：打开新建场景界面
	//作者：Costa
	void MainForm::openNewSceneEditor()
	{
		if ( FormSet::create_form == nullptr)
		{
			FormSet::create_form  = gcnew CreateForm();
			FormSet::create_form->CreateControl();
			FormSet::create_form->initialize();
			FormSet::create_form->Show();
		}
	}
	//-----------------------------------------------------------------------
	//功能：关闭新建场景界面
	//作者：Costa
	void MainForm::closeNewSceneEditor()
	{
		FormSet::create_form = nullptr;
	}
	//-----------------------------------------------------------------------
	//功能：显示场景信息
	//作者：Costa
	void MainForm::showSceneInfo()
	{
		if ( FormSet::SceneInfo_form == nullptr)
		{
			FormSet::SceneInfo_form  = gcnew SceneInfo();
			FormSet::SceneInfo_form->CreateControl();
			FormSet::SceneInfo_form->initialize();
			FormSet::SceneInfo_form->Show();
		}
	}	
	//-----------------------------------------------------------------------
	//功能：关闭场景信息界面
	//作者：Costa
	void MainForm::closeSceneInfo()
	{
		FormSet::SceneInfo_form = nullptr;
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

            if ( element_tab->SelectedTab == createElment_page )
            {
                if ( SelectCreateElementTypeTab->SelectedTab == create_static_page )
                {
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_ENTITY );
                }else
                if ( SelectCreateElementTypeTab->SelectedTab == create_tree_page )
                {
					OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_TREE );
                }
				else if ( SelectCreateElementTypeTab->SelectedTab == create_effect_page )
				{
					OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_CREATE_EFFECTENTITY );
				}
            }
        }else
        //地形Tab
        if ( prop_tab_ctrl->SelectedTab == terrain_page )
        {
			//地形Tab--高度
            if ( terrainTab->SelectedTab == terrain_vertex_page )
            {
                if ( terrainHeightTab->SelectedTab == terrain_height_level_page )
                { 
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_HEIGHT_LEVEL );
                }else
                if ( terrainHeightTab->SelectedTab == terrain_height_uniform_page )
                {
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_HEIGHT_UNIFORM );
                }else
                if ( terrainHeightTab->SelectedTab == terrain_height_noise_page )
                {
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_HEIGHT_NOISE );
                }else
                if ( terrainHeightTab->SelectedTab == terrain_height_flat_page )
                {
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_HEIGHT_FLAT );
                }
            }else
			//地形Tab--纹理
            if ( terrainTab->SelectedTab == terrain_texture_page )
            {
                if ( terrainTextureTab->SelectedTab == terrain_tex_add_page )
                { 
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_TEXTURE_ADD );
                }else
                if ( terrainTextureTab->SelectedTab == terrain_tex_remove_page )
                {
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_TEXTURE_REMOVE );
                }else
                if ( terrainTextureTab->SelectedTab == terrain_tex_uniform_page )
                {
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_TEXTURE_UNIFORM );
                }else
                if ( terrainTextureTab->SelectedTab == terrain_tex_mop_page )
                {
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_TEXTURE_MOP );
                }else
                if ( terrainTextureTab->SelectedTab == terrain_tex_blur_page )
                {
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_TEXTURE_BLUR );
                }
            }else
			//地形Tab--植被
            if ( terrainTab->SelectedTab == terrain_plant_page )
            {
                if ( plantBatchEntityTab->SelectedTab == terrain_batch_add_page )
                { 
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_BATCH_ADD );
                }
				else 
                if ( plantBatchEntityTab->SelectedTab == terrain_batch_remove_page )
                {
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_BATCH_REMOVE );
                }
				else
                if ( plantBatchEntityTab->SelectedTab == terrain_batch_noise_page )
				{
					OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_BATCH_DEFINE );						
				}
            }else
			//地形Tab--悬崖
            if ( terrainTab->SelectedTab == terrain_region_page )
            {
                if ( terrainRegionOpTab->SelectedTab == terrain_region_add_page )
                { 
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_REGION_ADD );
                }
                else 
                if ( terrainRegionOpTab->SelectedTab == terrain_region_remove_page )
                {
                    OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_REGION_REMOVE );
                }
            }else
			//地形Tab--水
            if ( terrainTab->SelectedTab == terrain_water_page )
            {
                if ( waterTab->SelectedTab == water_visible_page )
                { 
                    if ( water_visible_tab->SelectedTab == water_op_show_page )
                    { 
                        OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_WATER_SHOW );
                    }else
                    if ( water_visible_tab->SelectedTab == water_op_hide_page )
                    {
                        OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_WATER_HIDE );
                    }
                }
                else 
                if ( waterTab->SelectedTab == water_height_page )
                {
                    if ( water_height_tab->SelectedTab == water_height_level_page )
                    { 
                        OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_WATER_HEIGHT_LEVEL );
                    }else
                    if ( water_height_tab->SelectedTab == water_height_uniform_page )
                    {
                        OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_WATER_HEIGHT_UNIFORM );
                    }else
                    if ( water_height_tab->SelectedTab == water_height_flat_page )
                    {
                        OperationManager::getInstance().setActiveEditorOp( OperationManager::OT_TERRAIN_WATER_HEIGHT_FLAT );
                    }
                }
            }
        }else
        //配置Tab
        if ( prop_tab_ctrl->SelectedTab == setting_page )
        {
            
        }
    }
	//-----------------------------------------------------------------------
	void MainForm::updateSceneEditorParameter()
	{
		/*
			speedTree植被系统的控件更新, 和原有的植被系统是两个系统
		*/

		Double windIntensity = (TrackBarWindIntensity->Value) * 0.1f;
		lableWindIntensity->Text = TypeConverter::DoubleToStr( windIntensity );
	}

    //-----------------------------------------------------------------------
    void MainForm::updateTerrainEditorParameter()
    {
        IEditorSystem* editorSys    = CoreManager::getInstance().getEngineMain()->editorSystem();

         
		//###########################################################
		// 笔刷当前贴图索引
		
        Int tempIndex = getCurrActiveTempTerrainTextureIndex();
		if ( tempIndex < CoreManager::getInstance().mPreparedTerrainTextureList.size() )
		{
			Int texIndex = CoreManager::getInstance().mPreparedTerrainTextureList[tempIndex];
			editorSys->getBrushSystem()->setActiveTextureLayerIndex( texIndex );
		}
        //###########################################################
        // 笔刷形状参数
        IBrushShape* brushShape = editorSys->getBrushSystem()->getBrushCircleShape();
        if ( terrain_brush_shape_tab->SelectedTab == terrain_shape_yuan_page )
        { 
            brushShape = editorSys->getBrushSystem()->getBrushCircleShape();
        }else
        if ( terrain_brush_shape_tab->SelectedTab == terrain_shape_fang_page )
        {
            brushShape = editorSys->getBrushSystem()->getBrushRectShape();
        }else
        if ( terrain_brush_shape_tab->SelectedTab == terrain_shape_lin_page )
        {
            brushShape = editorSys->getBrushSystem()->getBrushRhombusShape();
        }
        editorSys->getBrushSystem()->setActiveShape( brushShape );

		//###########################################################
		// 笔刷基础参数
		Flt brush_size = (terrain_brush_size_tb->Value + 1) * 0.5f;
		this->terrain_brush_size_text->Text = TypeConverter::DoubleToStr( brush_size );
		editorSys->getBrushSystem()->setSize( brush_size );

		Flt brush_speed = (terrain_brush_speed_tb->Value + 1) * 1.0f; 
		this->terrain_brush_speed_text->Text = TypeConverter::DoubleToStr( brush_speed );
		editorSys->getBrushSystem()->setSpeed( brush_speed );

        //###########################################################
        // 笔刷类型参数
        IBrushStyle* brushStyle = editorSys->getBrushSystem()->getBrushAirStyle();
        if ( terrain_style_tab->SelectedTab == terrain_style_gun_page )
        { 
            brushStyle = editorSys->getBrushSystem()->getBrushAirStyle();

			Double attenuation = terrain_stytle_gun_decay_tb->Value + 1;
			terrain_stytle_gun_decay_text->Text = TypeConverter::DoubleToStr( attenuation );
			(dynamic_cast<IBrushAirStyle*>(brushStyle))->setAttenuation( (Flt)attenuation );

        }else
        if ( terrain_style_tab->SelectedTab == terrain_style_pen_page )
        {
            brushStyle = editorSys->getBrushSystem()->getBrushPaintStyle();
        }else
        if ( terrain_style_tab->SelectedTab == terrain_style_noise_page )
        {
            brushStyle = editorSys->getBrushSystem()->getBrushNoiseStyle();
        }else
        if ( terrain_style_tab->SelectedTab == terrain_style_frag_page )
        {
            brushStyle = editorSys->getBrushSystem()->getBrushFractalStyle();
        }
        editorSys->getBrushSystem()->setActiveStyle( brushStyle );

        //###########################################################
        //地图高度参数
        Double amplitude = (terrain_height_level_range_tb->Value + 1) * 1.0f;
		terrain_height_level_range_text->Text = TypeConverter::DoubleToStr( amplitude );
        editorSys->getTerrainRaiseHeightOperationManager()->setAmplitude( (Flt)amplitude );
		editorSys->getTerrainLowerHeightOperationManager()->setAmplitude( (Flt)amplitude );

		amplitude = (terrain_height_noise_range_tb->Value + 1) * 1.0f;
		terrain_height_noise_range_text->Text = TypeConverter::DoubleToStr( amplitude );
		editorSys->getTerrainNoiseHeightOperationManager()->setAmplitude( (Flt)amplitude );
        
        amplitude = (terrain_height_smooth_range_tb->Value + 1) * 0.01f;
		terrain_height_smooth_range_text->Text = TypeConverter::DoubleToStr( amplitude );
        editorSys->getTerrainSmoothHeightOperationManager()->setAmplitude( (Flt)amplitude );

		

        //###########################################################
        //地图贴图参数
        amplitude = terrain_tex_add_tb->Value * 0.00390625f;
		terrain_tex_add_text->Text = TypeConverter::IntToStr( terrain_tex_add_tb->Value );
		editorSys->getTerrainAddTextureOperationManager()->setAmplitude( (Flt)amplitude );
        //editorSys->getTerrainAddTextureOperationManager()->setAmplitude( amplitude );

        amplitude = terrain_tex_remove_tb->Value * 0.00390625f;
		terrain_tex_remove_text->Text = TypeConverter::IntToStr( terrain_tex_remove_tb->Value );
		editorSys->getTerrainRemoveTextureOperationManager()->setAmplitude( (Flt)amplitude );
        //###########################################################

		//###########################################################
		//植被参数
		double grassDistance = (plant_create_clumping_bar->Value + 1) * 0.1f;
		plant_create_GrassDis_label->Text = TypeConverter::DoubleToStr( grassDistance );
		//editorSys->getTerrainAddBatchEntityOperationManager()->setClumping( (Flt)amplitude );
		editorSys->getTerrainAddTreeOperationManager()->setGrassDistance((Flt)grassDistance);

		amplitude = (plant_create_treeDis_bar->Value + 1) * 0.1f;
		plant_create_treeDis_label->Text = TypeConverter::DoubleToStr( amplitude );
		//editorSys->getTerrainAddBatchEntityOperationManager()->setDensity( amplitude );
		//editorSys->getTerrainAddTreeOperationManager()->setDensity( amplitude );
		editorSys->getTerrainAddTreeOperationManager()->setTreeDistance((Flt)amplitude);

		bool align = plant_create_align_checkbox->Checked;
		editorSys->getTerrainAddTreeOperationManager()->setAlign(align);

		plant_create_scale_offset_bar->Enabled = !plant_create_align_checkbox->Checked;
		amplitude = (plant_create_scale_offset_bar->Value + 1) * 0.1f;
		plant_create_scale_offset_label->Text = TypeConverter::DoubleToStr( amplitude );
		editorSys->getTerrainAddTreeOperationManager()->setPositionOffset((Flt)amplitude);

		if (plant_create_ditribute_colum->Checked)
		{
			editorSys->getTerrainAddTreeOperationManager()->setDistribute(1);
		}
		else if (plant_create_ditribute_circle->Checked)
		{
			editorSys->getTerrainAddTreeOperationManager()->setDistribute(2);
		}

		Flt minScale = TypeConverter::StrToDouble(TextBox_Plant_MinScale->Text);
		Flt maxScale = TypeConverter::StrToDouble(TextBox_Plant_MaxScale->Text);
		editorSys->getTerrainAddTreeOperationManager()->setMinScale( minScale );
		editorSys->getTerrainAddTreeOperationManager()->setMaxScale( maxScale );

		if ( common_batch_radioButton->Checked )
		{
			//editorSys->getTerrainDefineBatchEntityOperationManager()->setMode( ITerrainDefineBatchEntityOperationManager::DEFINE_BATCH_MODE_COMMON );
			editorSys->getTerrainDefineTreeOperationManager()->setMode( ITerrainDefineTreeOperationManager::DEFINE_BATCH_MODE_COMMON );
			specialize_batch_textBox->Enabled = false;
			plant_batch_define_button->Enabled = false;
		}
		else if ( region_batch_radioButton->Checked )
		{
			//editorSys->getTerrainDefineBatchEntityOperationManager()->setMode( ITerrainDefineBatchEntityOperationManager::DEFINE_BATCH_MODE_REGION );	
			editorSys->getTerrainDefineTreeOperationManager()->setMode( ITerrainDefineTreeOperationManager::DEFINE_BATCH_MODE_REGION );	
			specialize_batch_textBox->Enabled = false;
			plant_batch_define_button->Enabled = false;
		}
		else if ( specialize_batch_radioButton->Checked )
		{
			//editorSys->getTerrainDefineBatchEntityOperationManager()->setMode( ITerrainDefineBatchEntityOperationManager::DEFINE_BATCH_MODE_SPECIALIZE );
			editorSys->getTerrainDefineTreeOperationManager()->setMode( ITerrainDefineTreeOperationManager::DEFINE_BATCH_MODE_SPECIALIZE );

			plant_batch_define_button->Enabled = true;
			//specialize_batch_textBox->Enabled = !editorSys->getTerrainDefineBatchEntityOperationManager()->isLocked();
			specialize_batch_textBox->Enabled = !editorSys->getTerrainDefineTreeOperationManager()->isLocked();
			
		}

		//###########################################################
		//水参数
		//高度参数
		amplitude = (water_height_level_app->Value + 1) * 1.0f;
		water_height_label->Text = TypeConverter::DoubleToStr( amplitude );
		editorSys->getTerrainRaiseHeightOperationManager()->setWaterAmplitude( (Flt)amplitude );
		editorSys->getTerrainLowerHeightOperationManager()->setWaterAmplitude( (Flt)amplitude );
    }

	//-----------------------------------------------------------------------
	void MainForm::loadTerrainTextureList()
	{
        CoreManager::getInstance().mPreparedTerrainTextureList.clear();
        for ( Int i=0; i<8 ; i++ )
        {
            CoreManager::getInstance().mPreparedTerrainTextureList.push_back( i );
        }
        
        if ( FormSet::terrainTexture_form != nullptr)
        {
            FormSet::terrainTexture_form->refresh();    
        }

        refreshTerrainTextureImage();
	}

    //-----------------------------------------------------------------------
    void MainForm::refreshTerrainTextureImage()
    {
        terrain_texture_pic_list->Images->Clear();

        ITerrainSurfaceManager* surfaceMgr    = CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainSurfaceManager();
        if ( surfaceMgr )
        {

            for ( Int i=0; i<CoreManager::getInstance().mPreparedTerrainTextureList.size() ; i++ )
            {
                Int index = CoreManager::getInstance().mPreparedTerrainTextureList[i];
                
                TerrainTextureLayerDeclaration* decl = surfaceMgr->getGlobleTextureLayer( index );

                if ( decl )
                {
                    Str cStr = "Media\\TerrainTexture\\thumbnails\\" + decl->thumbnailsFileName;

                    String^ filename = TypeConverter::Char8ToStr(cStr.c_str());
                    terrain_texture_pic_list->Images->Add(Image::FromFile(filename));
                }
            }
        }

        terrain_texture_pic_tab->ImageList = terrain_texture_pic_list;
        terrain_texture_pic_tab->Refresh();

    }

    //-----------------------------------------------------------------------
    void MainForm::setActiveTerrainTexture( Int index )
    {
        IEditorSystem* editorSys    = CoreManager::getInstance().getEngineMain()->editorSystem();

        Int tempIndex = getCurrActiveTempTerrainTextureIndex();
        CoreManager::getInstance().mPreparedTerrainTextureList[tempIndex] = index ;
        refreshTerrainTextureImage();

        editorSys->getBrushSystem()->setActiveTextureLayerIndex( index );
    }

    //-----------------------------------------------------------------------
    Int MainForm::getCurrActiveTempTerrainTextureIndex()
    {
        if ( terrain_texture_pic_tab->SelectedTab == terrain_tex_0 )
        { 
            return 0;
        }else
        if ( terrain_texture_pic_tab->SelectedTab == terrain_tex_1 )
        {
            return 1;
        }else
        if ( terrain_texture_pic_tab->SelectedTab == terrain_tex_2 )
        {
            return 2;
        }else
        if ( terrain_texture_pic_tab->SelectedTab == terrain_tex_3 )
        { 
            return 3;
        }else
        if ( terrain_texture_pic_tab->SelectedTab == terrain_tex_4 )
        {
            return 4;
        }else
        if ( terrain_texture_pic_tab->SelectedTab == terrain_tex_5 )
        {
            return 5;
        }else
        if ( terrain_texture_pic_tab->SelectedTab == terrain_tex_6 )
        { 
            return 6;
        }else
        if ( terrain_texture_pic_tab->SelectedTab == terrain_tex_7 )
        {
            return 7;
        }

        return 0;
    }

	//-----------------------------------------------------------------------
	// 加载批次树列表
	void MainForm::loadBatchTreeList()
	{
		////////////////////////////////////////////////////////////
		listView_terrain_batch_tree_list->Items->Clear();
		lable_batch_curr_sel->Text;
		////////////////////////////////////////////////////////////

		IScene* pScene = NULL;
		pScene = CoreManager::getInstance().getScene();
		if (pScene == NULL)
			return;

		ITreeManager* pTreeMgr = pScene->getTreeManager();
		//UInt treeNr = pTreeMgr->getTreeDeclarationCount();
		const std::map<MG::UInt, TreeDeclaration>& treeDeclMap = pTreeMgr->getTreeDeclMap();
		//将树资源添加到列表便于排序
		std::vector<TreeDeclaration*> treeDeclList;
		for (std::map<MG::UInt, TreeDeclaration>::const_iterator it = treeDeclMap.begin(); it != treeDeclMap.end(); ++it)
		{
			TreeDeclaration* pTreeDecl = pTreeMgr->getTreeDeclarationByIndex((*it).second.uId);
			treeDeclList.push_back(pTreeDecl);
		}

		//列表排序
		sort(treeDeclList.begin(),treeDeclList.end(),treeDeclLessCompare);

		//将树资源添加到界面显示出来
		std::vector<TreeDeclaration*>::iterator treeDeclIter = treeDeclList.begin();
		for (int i=0; treeDeclIter!=treeDeclList.end(); ++treeDeclIter,++i)
		{
			String ^ index  = TypeConverter::IntToStr(i);
			String ^ name   = TypeConverter::Char8ToStr((*treeDeclIter)->strName.c_str());
			String ^ id		= TypeConverter::IntToStr((*treeDeclIter)->uId);

			ListViewItem ^ item = gcnew ListViewItem;

			item->SubItems->default[0]->Text            = index;
			item->SubItems->default[0]->Name            = "columnHeader_batch_list_index";

			ListViewItem::ListViewSubItem ^subItem = item->SubItems->Add(name);
			subItem->Text = name;
			subItem->Name = "columnHeader_batch_list_name";

			subItem = item->SubItems->Add(id);
			subItem->Text = id;
			subItem->Name = "columnHeader_batch_list_model_id";

			listView_terrain_batch_tree_list->Items->Add(item);
		}
	}

	//-----------------------------------------------------------------------
	// 加载批次草列表
	void MainForm::loadBatchGrassList()
	{
		////////////////////////////////////////////////////////////
		listView_terrain_batch_grass_list->Items->Clear();
		lable_batch_curr_sel->Text;
		////////////////////////////////////////////////////////////

		IScene* pScene = NULL;
		pScene = CoreManager::getInstance().getScene();
		if (pScene == NULL)
			return;

		ITreeManager* pTreeMgr = pScene->getTreeManager();
		const std::map<MG::UInt, GrassDeclaration>& grassDeclMap = pTreeMgr->getGrassDeclMap();
		//将草资源添加到列表便于排序
		std::vector<GrassDeclaration*> grassDeclList;
		for (std::map<MG::UInt, GrassDeclaration>::const_iterator it = grassDeclMap.begin(); it != grassDeclMap.end(); ++it)
		{
			GrassDeclaration* pGrassDecl = pTreeMgr->getGrassDeclarationByIndex(it->first);
			if (pGrassDecl != NULL)
			{
				grassDeclList.push_back(pGrassDecl);
			}
		}

		//列表排序
		sort(grassDeclList.begin(),grassDeclList.end(),grassDeclLessCompare);

		//将草资源添加到界面显示出来
		std::vector<GrassDeclaration*>::iterator grassDeclIter = grassDeclList.begin();
		for (int i=0; grassDeclIter!=grassDeclList.end(); ++grassDeclIter,++i)
		{
			String ^ index  = TypeConverter::IntToStr(i);
			String ^ name   = TypeConverter::Char8ToStr((*grassDeclIter)->strName.c_str());
			String ^ id		= TypeConverter::IntToStr((*grassDeclIter)->uId);

			ListViewItem ^ item = gcnew ListViewItem;

			item->SubItems->default[0]->Text            = index;
			item->SubItems->default[0]->Name            = "columnHeader_batch_list_index";

			ListViewItem::ListViewSubItem ^subItem = item->SubItems->Add(name);
			subItem->Text = name;
			subItem->Name = "columnHeader_batch_list_name";

			subItem = item->SubItems->Add(id);
			subItem->Text = id;
			subItem->Name = "columnHeader_batch_list_model_id";

			listView_terrain_batch_grass_list->Items->Add(item);
		}
	}

	//-----------------------------------------------------------------------
	//从批次树列表中选择树
	void MainForm::selectBatchTreeFromList()
	{
		if ( listView_terrain_batch_tree_list->SelectedItems->Count <= 0 )
			return;

		ListViewItem^ item = listView_terrain_batch_tree_list->SelectedItems[0];

		String ^ strID = item->SubItems["columnHeader_batch_list_model_id"]->Text;
		String ^ strName = item->SubItems["columnHeader_batch_list_name"]->Text;

		lable_batch_curr_sel->Text = strName;

		U32 modelID = TypeConverter::StrToInt(strID);

		IEditorSystem* editorSys    = CoreManager::getInstance().getEngineMain()->editorSystem();
		editorSys->getTerrainTreeOperationManager()->setOpModel( modelID );
		editorSys->getTerrainTreeOperationManager()->setTreeType(0);
	}

	//-----------------------------------------------------------------------
	//从批次草列表中选择草
	void MainForm::selectBatchGrassFromList()
	{
		if ( listView_terrain_batch_grass_list->SelectedItems->Count <= 0 )
			return;

		ListViewItem^ item = listView_terrain_batch_grass_list->SelectedItems[0];

		String ^ strID = item->SubItems["columnHeader_batch_list_model_id"]->Text;
		String ^ strName = item->SubItems["columnHeader_batch_list_name"]->Text;

		lable_batch_curr_sel->Text = strName;

		U32 modelID = TypeConverter::StrToInt(strID);

		IEditorSystem* editorSys    = CoreManager::getInstance().getEngineMain()->editorSystem();
		editorSys->getTerrainTreeOperationManager()->setOpModel( modelID );
		editorSys->getTerrainTreeOperationManager()->setTreeType(1);
	}

    //-----------------------------------------------------------------------
    void MainForm::refreshRegionVisible()
    {
        Bool isDisplayed = CoreManager::getInstance().getEngineMain()->display()->getTerrainRegionDisplayEnabled();
        if ( terrain_region_visible_ckb->Checked != isDisplayed )
        {
            CoreManager::getInstance().getEngineMain()->display()->setTerrainRegionDisplayEnabled( !isDisplayed );
            CoreManager::getInstance().getEngineMain()->display()->apply();
        }
    }

    //-----------------------------------------------------------------------
    void MainForm::showBlockRegion()
    {
        CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainRegionManager()->setBlockRegionVisible( true );
        CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainRegionManager()->applyRegionVisible();
    }

    //-----------------------------------------------------------------------
    void MainForm::loadCustomRegionList()
    {
        TerrainRegionSelfList->Items->Clear();
        TerrainSelRegionSelfText->Text = "";

        Int count = CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainRegionManager()->getCustomRegionCount();
        for ( Int i=0; i<=count; i++ )
        {
            CustomRegionDeclaration* layer = CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainRegionManager()->getCustomRegionDeclaration( i );
            if (layer)
            {
                String ^ index      = TypeConverter::IntToStr(i);
                String ^ name       = "";

                ListViewItem ^ item = gcnew ListViewItem;
                item->SubItems->default[0]->Text            = index;
                item->SubItems->default[0]->Name            = "columnHeader_custom_list_index";
                item->SubItems->Add(name)->Name             = "columnHeader_custom_list_name";

                TerrainRegionSelfList->Items->Add(item);
            }
        }
    }

    //-----------------------------------------------------------------------
    void MainForm::addCustomRegion()
    {
        CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainRegionManager()->addCustomRegion();
        loadCustomRegionList();
    }

    //-----------------------------------------------------------------------
    void MainForm::showCustomRegion()
    {
        if (TerrainRegionSelfList->SelectedItems->Count <=0)
            return;
        ListViewItem^ item = TerrainRegionSelfList->SelectedItems[0];  

        String ^ strIndex = item->SubItems["columnHeader_custom_list_index"]->Text;
        String ^ strName = item->SubItems["columnHeader_custom_list_name"]->Text;

        TerrainSelRegionSelfText->Text = strIndex;

        Int index = TypeConverter::StrToInt(strIndex);

        ///////////////////////////////////////////////////////////////////
        
        Int count = CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainRegionManager()->getCustomRegionCount();
        for ( Int i=0; i<count; i++ )
        {
            CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainRegionManager()->setCustomRegionVisible( i, false );
        }

        CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainRegionManager()->setCustomRegionVisible( index, true );
        CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainRegionManager()->setBlockRegionVisible( false );

        CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainRegionManager()->applyRegionVisible();
    }

	//-----------------------------------------------------------------------
    void MainForm::createScene()
    {
        BEGINDELEGATE(MainForm,createScene)
        ENDDELEGATE

        clearAll();

        CoreManager::getInstance().getScene()->clear();
        CoreManager::getInstance().getEngineMain()->resourceMgr()->unLoadAllResource();

        CoreManager::getInstance().getScene()->getXmlSerializer()->createSceneContent();
    }
    //-----------------------------------------------------------------------
    void MainForm::loadScene()
    {
        BEGINDELEGATE(MainForm,loadScene)
        ENDDELEGATE
        
        clearAll();
        
        //folderBrowserDialog1->SelectedPath = System::Windows::Forms::Application::StartupPath;
		if (String::IsNullOrEmpty(mLastFocusDir))
			folderBrowserDialog1->SelectedPath = System::Windows::Forms::Application::StartupPath + "\\Media\\Scene";
		else
			folderBrowserDialog1->SelectedPath = mLastFocusDir;
        if ( folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
        {
            mLastFocusDir = folderBrowserDialog1->SelectedPath;
            StrToChar8 pathStr( folderBrowserDialog1->SelectedPath );

			//保存最后打开文件目录到config文件
			AppDataManager::getInstance()->setMapFilePath(pathStr.getChar8());


            CoreManager::getInstance().getScene()->clear();
            CoreManager::getInstance().getEngineMain()->resourceMgr()->unLoadAllResource();

            CoreManager::getInstance().getScene()->getXmlSerializer()->loadContent( pathStr.getChar8(), FormSet::main_form->isEditorMode() );
            
            if ( FormSet::main_form->isEditorMode() )
            {
                loadSceneEntityList();
				loadScenePlantList();
				loadSceneEffectList();
            }

			////////////////////////////////////////////////////

            loadTerrainTextureList();
            updateTerrainEditorParameter();

            ////////////////////////////////////////////////////

            loadCustomRegionList();

            ////////////////////////////////////////////////////
           
            loadWaterGroupList();

            ////////////////////////////////////////////////////

            switchGameEditorOp();

            ////////////////////////////////////////////////////

            loadSceneEnvironmentLight();
            loadSceneGameConfig();
            loadFogSetting();
            loadShadowSetting();
			loadPlantSetting();

            ////////////////////////////////////////////////////

            CoreManager::getInstance().initScene();
            updateDebugInfo();

			////////////////////////////////////////////////////

			applyCompositorSetting();

			////////////////////////////////////////////////////

			// 解锁treemanager

			CoreManager::getInstance().getEngineMain()->unLockTreeManager();

			mIsSceneLoaded = true;
        }
		
    }
    //-----------------------------------------------------------------------
    void MainForm::saveScene()
    {
        BEGINDELEGATE(MainForm,saveScene)
        ENDDELEGATE

		if ( !isEditorMode() || !mIsSceneLoaded)
			return;

        if ( String::IsNullOrEmpty(mLastFocusDir) )
        {
            saveAsScene();
        }
        else
        {
            StrToChar8 pathStr( mLastFocusDir );
            CoreManager::getInstance().getScene()->getXmlSerializer()->saveContent( pathStr.getChar8() );
        }
    }
    //-----------------------------------------------------------------------
    void MainForm::saveAsScene()
    {
        BEGINDELEGATE(MainForm,saveAsScene)
        ENDDELEGATE

		if ( !isEditorMode() || !mIsSceneLoaded)
			return;
        
        folderBrowserDialog1->SelectedPath = System::Windows::Forms::Application::StartupPath;
        if ( folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
        {
            mLastFocusDir = folderBrowserDialog1->SelectedPath;
            StrToChar8 pathStr( folderBrowserDialog1->SelectedPath );

            CoreManager::getInstance().getScene()->getXmlSerializer()->saveContent( pathStr.getChar8() );
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

        display->setWaterReflectionEnabled( water_reflect_check->Checked );
        display->setWaterDepthCheckEnabled( water_alpha_check->Checked );
        display->setWaterRefractionEnabled( water_refract_check->Checked );

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

        display->setEntityLightingMapEnable( model_shadow_tex_check->Checked );

        display->setEntityNormalMapEnable( model_normal_tex_check->Checked );
        
        display->setEntitySaMapEnable( model_sa_tex_check->Checked );
        
        display->setEntityReceiveDynamicShadowsEnabled( model_shadow_dynamic_check->Checked );
        
        //----------------------------------------------------------

        if ( gamma_check->Checked )
        {
            display->setGammaEnabled(true);
        }else
        {
            display->setGammaEnabled(false);
        }

        //----------------------------------------------------------

		Str str;
        U32 fsaa = TypeConverter::StrToU32( fsaa_txt->Text );
        display->setFSAA(fsaa, str);

        //----------------------------------------------------------

        Flt scale = TypeConverter::StrToDouble( sbs_scale_txt->Text );
        Flt bias = TypeConverter::StrToDouble( sbs_bias_txt->Text );
        Flt specular = TypeConverter::StrToDouble( sbs_specular_txt->Text );
		Flt bump = TypeConverter::StrToDouble( sbs_normal_txt->Text );
        display->setScaleBiasSpecular(Vec4(bump,scale,bias,specular));
      
    }

    //----------------------------------------------------------------------
    void MainForm::applyGameSetting()
    {
        updateGameSetting();
        IDisplay* display = CoreManager::getInstance().getEngineMain()->display();
        display->apply();
    }
    //-----------------------------------------------------------------------
    void MainForm::applyBaseSceneSetting()
    {
		//if ( ToolStripMenuItem_SceneEditorMode->Checked )
		//{
		//	CoreManager::getInstance().getEngineMain()->setMode(EM_EDITOR);
		//}else
		//{
		//	CoreManager::getInstance().getEngineMain()->setMode(EM_NORMAL);
		//}
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
	void MainForm::updateMouseHint()
	{
		Vec3 pos;
		CoreManager::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos,true);

		mousePosX->Text = TypeConverter::DoubleToStr(pos.x);
		mousePosY->Text = TypeConverter::DoubleToStr(pos.y);
		mousePosZ->Text = TypeConverter::DoubleToStr(pos.z);
	}


    //-----------------------------------------------------------------------
    void MainForm::loadModelDeclarationList()
    {
        ////////////////////////////////////////////////////////////

        model_create_tree->Nodes->Clear();

        ////////////////////////////////////////////////////////////

        std::map<Str, std::vector<ModelDeclaration*>>  groupDeclList;

        ////////////////////////////////////////////////////////////

        UInt count = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclarationCount();
        for ( UInt index=0; index<count ; index++ )
        {
            ModelDeclaration* decl = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclarationByIndex(index);

            groupDeclList[decl->group].push_back( decl );
        }

		//排序
		std::map<Str, std::vector<ModelDeclaration*>>::iterator declIter = groupDeclList.begin();
		for(declIter; declIter != groupDeclList.end(); declIter++)
		{
			sort(declIter->second.begin(),declIter->second.end(),declLessCompare);
		}

        ////////////////////////////////////////////////////////////


        {
            std::map<Str, std::vector<ModelDeclaration*>>::iterator iter = groupDeclList.begin();
            for ( ; iter!=groupDeclList.end(); iter++)
            {
                Str declName = iter->first;

                ////////////////////////////////////////////////////////////

				String^ declNodeName    = TypeConverter::Char8ToStr( declName.c_str() );
				System::String^ declCount = "(" + TypeConverter::IntToStr(iter->second.size()) + ")";
				declNodeName += declCount;

                TreeNode ^ typeTreeNode = gcnew TreeNode(declNodeName);
                typeTreeNode->Tag = "";

                model_create_tree->Nodes->Add( typeTreeNode );

                ////////////////////////////////////////////////////////////

                UInt count = iter->second.size();
                for ( UInt i=0; i<count; i++ )
                {
                    ModelDeclaration* decl = iter->second[i];

                    ////////////////////////////////////////////////////////////

                    String^ declNodeName = "Node" + TypeConverter::IntToStr( i );
                    TreeNode ^ declTreeNode = gcnew TreeNode( declNodeName );

                    Str text = decl->name + " " + decl->path + " " + decl->meshFileName;
                    declTreeNode->Text  = TypeConverter::Char8ToStr(text.c_str());
                    declTreeNode->Tag   = TypeConverter::IntToStr(decl->id);

                    typeTreeNode->Nodes->Add( declTreeNode );

                    ////////////////////////////////////////////////////////////
                }
            }
            //model_create_tree->ExpandAll();
        }
       
    }

    //-----------------------------------------------------------------------
    void MainForm::loadModelDeclarationList2()
    {
        //////////////////////////////////////////////////////////////////////////////

        model_create_tree->Nodes->Clear();
        
        //////////////////////////////////////////////////////////////////////////////
        tinyxml2::XMLDocument xmlDoc;
        xmlDoc.LoadFile("Config\\Engine\\ModelDeclarationList.xml");
        //const XMLDocument* xmlDoc = CoreManager::getInstance().getEngineMain()->resourceMgr()->getModelDeclXmlDoc();
        //if ( xmlDoc )
        {
            const XMLElement* rootElm = xmlDoc.RootElement();
            if (rootElm)
            {
                //create component
                {
                    //初始化Xml节点
                    const XMLNode* parentNode       = rootElm;
                    const XMLNode* currNode         = parentNode->FirstChild();
                    const XMLNode* firstSiblingNode = currNode;
                    const XMLNode* nextNode         = NULL;
                    const XMLElement* element       = NULL;

                    if (!currNode)
                        return;

                    //初始化控件节点
                    TreeNode ^ parentTreeNode = gcnew TreeNode("Root");
                    parentTreeNode->ExpandAll();

                    Int nodeNum = 0;
                    String^ treeNodeName = "Node" + TypeConverter::IntToStr(nodeNum);
                    TreeNode ^ currTreeNode = gcnew TreeNode(treeNodeName);
                    //currTreeNode->ExpandAll();

                    parentTreeNode->Nodes->Add( currTreeNode );
                    model_create_tree->Nodes->Add( parentTreeNode );

                    //声明属性参数
                    Str8 name;
                    Str8 path;
                    Str8 modelFileName;
                    Str8 thumbnailsFileName;
                    Str8 describe;
                    Flt width;
                    Flt height;

                    //开始遍历
                    while( currNode )
                    {
                        nodeNum++;
                        treeNodeName = "Node" + TypeConverter::IntToStr(nodeNum);

                        //TODO:
                        Str formatType = XML_GET_VALUE(currNode);
                        element = currNode->ToElement();
                        if (formatType == "Model")
                        {
                            XmlHelper::getAttribute( element, name, "name");
                            XmlHelper::getAttribute( element, path, "path");
                            XmlHelper::getAttribute( element, modelFileName, "modelFileName");
                            XmlHelper::getAttribute( element, thumbnailsFileName, "thumbnailsFileName");
                            XmlHelper::getAttribute( element, describe, "describe");
                            XmlHelper::getAttribute( element, width, "width");
                            XmlHelper::getAttribute( element, height, "height");
                            
                            Str text = name + " " + describe + " " + path + " " + modelFileName;
                            currTreeNode->Text = TypeConverter::Char8ToStr(text.c_str());
                            currTreeNode->Tag = TypeConverter::Char8ToStr(name.c_str());
                        }else
                        if (formatType == "Content")
                        {
                            XmlHelper::getAttribute( element, name, "name");
                            Str text = name;
                            currTreeNode->Text = TypeConverter::Char8ToStr(text.c_str());
                        }

                        //@ tree
                        //往下遍历
                        nextNode = currNode->FirstChild();
                        if ( nextNode )
                            parentTreeNode = currTreeNode;

                        //兄弟遍历
                        if (!nextNode)
                        {
                            firstSiblingNode = currNode->Parent()->FirstChild();
                            nextNode         = currNode->NextSibling();
                            if (nextNode&&nextNode==firstSiblingNode)
                                nextNode = NULL;
                        }
                        
                        //往上遍历
                        if (!nextNode)
                        {
                            nextNode = currNode->Parent();
                            if (nextNode == parentNode)
                                break;

                            firstSiblingNode = nextNode->Parent()->FirstChild();

                            if ( currTreeNode->Parent != nullptr )
                                parentTreeNode = currTreeNode->Parent->Parent;

                            nextNode         = nextNode->NextSibling();
                            if (nextNode&&nextNode==firstSiblingNode)
                                nextNode = NULL;
                        }
                        currNode = nextNode;

                        //增加控件节点
                        if ( currNode )
                        {
                            currTreeNode = gcnew TreeNode(treeNodeName);
                            if ( parentTreeNode != nullptr )
                            {
                                parentTreeNode->Nodes->Add( currTreeNode );
                                //parentTreeNode->ExpandAll();
                            }
                        }

                    }
                }
            }
        }
    }
    
    //-----------------------------------------------------------------------
    void MainForm::prepareCreateEntity()
    {
        if ( model_create_tree->SelectedNode != nullptr &&
			model_create_tree->SelectedNode->Tag != nullptr )
        {
            String^ tag = model_create_tree->SelectedNode->Tag->ToString();
            if ( !String::IsNullOrEmpty(tag) )
            {
                if ( model_create_tree->SelectedNode->Parent )
                    mCurrSelectCreateModelTreeNode = model_create_tree->SelectedNode->Parent;

                prepare_model_text->Text = model_create_tree->SelectedNode->Text;

                Int modelDeclId = TypeConverter::StrToInt( tag );

                OperationManager::getInstance().prepareCreateObject( modelDeclId );
            }
        }
    }

    //-----------------------------------------------------------------------
    void MainForm::randonprepareCreateEntity()
    {
        if ( mCurrSelectCreateModelTreeNode != nullptr )
        {
            Int count = mCurrSelectCreateModelTreeNode->Nodes->Count;
            Int index = MGRandom::getInstance().rand_ab_One(0,count);
            if ( (count>0) && (index < count))
            {
                TreeNode ^ currTreeNode = mCurrSelectCreateModelTreeNode->Nodes[index];
                String^ tag = currTreeNode->Tag->ToString();

                if ( !String::IsNullOrEmpty(tag) )
                {
                    prepare_model_text->Text = currTreeNode->Text;;

                    Int modelDeclId = TypeConverter::StrToInt( tag );

                    OperationManager::getInstance().prepareCreateObject( modelDeclId );
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    Bool MainForm::isTestCreateBatchEntity()
    {
        return cb_is_create_batch->Checked;
    }

    //-----------------------------------------------------------------------
    UInt MainForm::getTestBatchEntityNum()
    {
        return Convert::ToInt32(num_create_batch->Value);
    }

    //-----------------------------------------------------------------------
	void MainForm::loadEffectDeclarationList()
	{
		////////////////////////////////////////////////////////////
		effect_create_tree->Nodes->Clear();
		////////////////////////////////////////////////////////////

		IResourceManager* resMgr = CoreManager::getInstance().getEngineMain()->resourceMgr();

		UInt count = resMgr->getEffectResourceDeclarationCount();

		//将所有资源保存到一个列表便于排序
		std::vector<EffectResourceDeclaration*> effectDeclList;
		for (int i=0; i< count; ++i)
		{
			EffectResourceDeclaration* effectDecl = resMgr->getEffectResourceDeclarationByIndex(i, false);
			effectDeclList.push_back(effectDecl);
		}
		//对资源进行排序
		sort(effectDeclList.begin(),effectDeclList.end(),effectDeclLessCompare);

		//将资源添加到界面显示出来
		std::vector<EffectResourceDeclaration*>::iterator effectDeclIter = effectDeclList.begin();
		for (int i=0; effectDeclIter != effectDeclList.end(); ++effectDeclIter,++i)
		{
			////////////////////////////////////////////////////////////

			String^ declNodeName = "Node" + TypeConverter::IntToStr( i );
			TreeNode^ effectNode = gcnew TreeNode( declNodeName );

			Str text = (*effectDeclIter)->name + " " + (*effectDeclIter)->filePath + " " + (*effectDeclIter)->fileName;

			effectNode->Text	= TypeConverter::Char8ToStr(text.c_str());
			effectNode->Tag		= TypeConverter::IntToStr((*effectDeclIter)->ResID);

			////////////////////////////////////////////////////////////

			effect_create_tree->Nodes->Add(effectNode);
		}

		effect_create_tree->ExpandAll();
	}


	//-----------------------------------------------------------------------
    void MainForm::loadTreeDeclarationList()
    {
		////////////////////////////////////////////////////////////

		tree_create_tree->Nodes->Clear();

		////////////////////////////////////////////////////////////

		String^ declNodeName = "Node" + TypeConverter::IntToStr( 0 );
		TreeNode^ declTreeNode = gcnew TreeNode( "TreeRoot" );

		Str text = "Tree";
		declTreeNode->Text  = "Tree";
		declTreeNode->Tag   = TypeConverter::IntToStr(0);
		
		IScene* pScene = CoreManager::getInstance().getScene();
		if (pScene == NULL)
		{
			return;
		}

		ITreeManager* pTreeMgr = pScene->getTreeManager();
		//UInt treeNr = pTreeMgr->getTreeDeclarationCount();
		const std::map<MG::UInt, TreeDeclaration>& treeDeclMap = pTreeMgr->getTreeDeclMap();
		//将树资源添加到列表便于排序
		std::vector<TreeDeclaration*> treeDeclList;
		for (std::map<MG::UInt, TreeDeclaration>::const_iterator it = treeDeclMap.begin(); it != treeDeclMap.end(); ++it)
		{
			TreeDeclaration* pTreeDecl = pTreeMgr->getTreeDeclarationByIndex((*it).second.uId);
			treeDeclList.push_back(pTreeDecl);
		}

		//列表排序
		sort(treeDeclList.begin(),treeDeclList.end(),treeDeclLessCompare);

		//显示树数量
		System::String^ treeDeclCount = "(" + TypeConverter::IntToStr(treeDeclList.size()) + ")";
		declTreeNode->Text += treeDeclCount;

		//将树资源添加到界面显示出来
		std::vector<TreeDeclaration*>::iterator treeDeclIter = treeDeclList.begin();
		for (int i=0; treeDeclIter!=treeDeclList.end(); ++treeDeclIter,++i)
		{
			String^ declNodeName = "Node" + TypeConverter::IntToStr( i );
			TreeNode^ treesNode = gcnew TreeNode( declNodeName );

			treesNode->Text		= TypeConverter::Char8ToStr((*treeDeclIter)->strName.c_str());
			treesNode->Tag		= TypeConverter::IntToStr((*treeDeclIter)->uId);

			declTreeNode->Nodes->Add(treesNode);
		}

		tree_create_tree->Nodes->Add( declTreeNode );

		//grass
		String^ declNodeGrassName = "Node" + TypeConverter::IntToStr( 1 );
		TreeNode^ declGrassNode = gcnew TreeNode( "GrassRoot" );

		
		declGrassNode->Text  = "Grass";
		declGrassNode->Tag   = TypeConverter::IntToStr(1);

		const std::map<MG::UInt, GrassDeclaration>& grassDeclMap = pTreeMgr->getGrassDeclMap();

		//将草资源添加到列表便于排序
		std::vector<GrassDeclaration*> grassDeclList;
		for (std::map<MG::UInt, GrassDeclaration>::const_iterator it = grassDeclMap.begin(); it != grassDeclMap.end(); ++it)
		{
			GrassDeclaration* pGrassDecl = pTreeMgr->getGrassDeclarationByIndex(it->first);
			if (pGrassDecl != NULL)
			{
				grassDeclList.push_back(pGrassDecl);
			}
		}

		//列表排序
		sort(grassDeclList.begin(),grassDeclList.end(),grassDeclLessCompare);

		//显示草数量
		System::String^ grassDeclCount = "(" + TypeConverter::IntToStr(grassDeclList.size()) + ")";
		declGrassNode->Text += grassDeclCount;

		//将草资源添加到界面显示出来
		std::vector<GrassDeclaration*>::iterator grassDeclIter = grassDeclList.begin();
		for (int i=0; grassDeclIter != grassDeclList.end(); ++grassDeclIter,++i)
		{
			String^ declNodeName = "Node" + TypeConverter::IntToStr( i );
			TreeNode^ grassNode = gcnew TreeNode( declNodeName );

			grassNode->Text		= TypeConverter::Char8ToStr((*grassDeclIter)->strName.c_str());
			grassNode->Tag		= TypeConverter::IntToStr((*grassDeclIter)->uId);

			declGrassNode->Nodes->Add(grassNode);
		}
		tree_create_tree->Nodes->Add( declGrassNode );
/*
		UInt treeNr = pTreeMgr->getTreeDeclarationCount();
		for (UInt i = 0; i < treeNr; ++i)
		{
			TreeDeclaration* pTreeDecl = pTreeMgr->getTreeDeclarationByIndex(i);

			String^ declNodeName = "Node" + TypeConverter::IntToStr( i );
			TreeNode^ treesNode = gcnew TreeNode( declNodeName );

			treesNode->Text		= TypeConverter::Char8ToStr(pTreeDecl->strName.c_str());
			treesNode->Tag		= TypeConverter::IntToStr(i);

			declTreeNode->Nodes->Add(treesNode);
		}*/

		tree_create_tree->ExpandAll();
    }

    //-----------------------------------------------------------------------
    void MainForm::prepareCreateTree()
    {
        if ( tree_create_tree->SelectedNode != nullptr &&
            tree_create_tree->SelectedNode->Tag != nullptr )
        {
            String^ tag = tree_create_tree->SelectedNode->Tag->ToString();
            if ( !String::IsNullOrEmpty(tag) )
            {
				TreeNode^ pParentNode = tree_create_tree->SelectedNode->Parent;
				if (pParentNode == nullptr)
				{
					return;
				}
                if (  pParentNode->Tag->ToString() == "0" )
				{
					OperationManager::getInstance().setTreeType(0);
				}
				else if (pParentNode->Tag->ToString() == "1")
				{
					OperationManager::getInstance().setTreeType(1);
				}
				
				mCurrSelectCreateTreeTreeNode = pParentNode;
                prepare_tree_text->Text = tree_create_tree->SelectedNode->Text;

                Int modelDeclId = TypeConverter::StrToInt( tag );

                OperationManager::getInstance().prepareCreateObject( modelDeclId );
            }
        }
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

				prepare_effect_text->Text = effect_create_tree->SelectedNode->Text;

				Int effectDeclID = TypeConverter::StrToInt( tag );

				OperationManager::getInstance().prepareCreateObject( effectDeclID );
			}
		}
	}

    //-----------------------------------------------------------------------
    void MainForm::loadSceneElementProps(ISceneObjectXmlFormat* format, Bool isChandedTab)
    {
        clearSceneElementProps();

        mCurrSceneObjectXmlFormat = format;

        if ( isChandedTab )
        {
            prop_tab_ctrl->SelectedTab = elemet_page;
            element_tab->SelectedTab = elemet_prop_page;
        }

        mXmlPropSet->loadXmlElement( format->getXmlElm() );

		{
			mXmlPropSet->addSubGroupProperty("TrackAnimation", "Name", "");

			mXmlPropSet->addSubGroupProperty("TextureAnimation", "u_start", "0.0");
			mXmlPropSet->addSubGroupProperty("TextureAnimation", "v_start", "0.0");
			mXmlPropSet->addSubGroupProperty("TextureAnimation", "u_speed", "0.0");
			mXmlPropSet->addSubGroupProperty("TextureAnimation", "v_speed", "0.0");
		}
		
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

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// apply custom attributes

			ISceneObject* sceneObject = CoreManager::getInstance().getScene()->getSceneObjectController()->getFocus();
			if ( sceneObject )
			{

				// 节点动画
				{
					std::string nodeAnimation = mXmlPropSet->getSubGroupProperty( "TrackAnimation", "Name" );
					sceneObject->getSceneNode()->playNodeAnimation( nodeAnimation, true, false );
				}

				// 材质贴图动画
				{
					IEntity* entity = dynamic_cast<IEntity*>(sceneObject);
					if ( entity )
					{
						Vec2 uv_start, uv_speed;

						std::string res = mXmlPropSet->getSubGroupProperty( "TextureAnimation", "u_start" );
						MGStrOp::toFlt( res.c_str(), uv_start.x );
						res = mXmlPropSet->getSubGroupProperty( "TextureAnimation", "v_start" );
						MGStrOp::toFlt( res.c_str(), uv_start.y );
						res = mXmlPropSet->getSubGroupProperty( "TextureAnimation", "u_speed" );
						MGStrOp::toFlt( res.c_str(), uv_speed.x );
						res = mXmlPropSet->getSubGroupProperty( "TextureAnimation", "v_speed" );
						MGStrOp::toFlt( res.c_str(), uv_speed.y );

						IEngineUtil* engineUtil = CoreManager::getInstance().getEngineMain()->engineUtil();
						engineUtil->setTextureAnimation( entity, uv_start, uv_speed );
					}	
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
				//在统计列表中选中物件
				System::String^ text = TypeConverter::Char8ToStr(sceneObject->getName().c_str());
				if (element_list->Nodes->Find(text,true)->Length > 0)
				{
					element_list->SelectedNode = element_list->Nodes->Find(text,true)[0];
					element_list->SelectedNode->Checked = true;
				}

                ISceneObjectXmlFormat* format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat(\
					sceneObject->getName().c_str(), sceneObject->getType());
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

				ISceneObjectXmlFormat* format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat(sceneObject->getName().c_str(), sceneObject->getType());
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
			scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_ENTITY, formatList);

			//trees
			std::vector<ISceneObjectXmlFormat*> treeFormatList;
			scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_TREE, treeFormatList);
			formatList.insert(formatList.end(),treeFormatList.begin(),treeFormatList.end());

			//grass
			std::vector<ISceneObjectXmlFormat*> grassFormatList;
			scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_GRASS, grassFormatList);
			formatList.insert(formatList.end(),grassFormatList.begin(),grassFormatList.end());

			//特效
			std::vector<ISceneObjectXmlFormat*> effectFormatList;
			scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_EFFECTENTITY, effectFormatList);
			formatList.insert(formatList.end(),effectFormatList.begin(),effectFormatList.end());

			for (  iter= formatList.begin(); iter!=formatList.end(); iter++ )
			{
				ISceneObjectXmlFormat* format = *iter;
				ISceneObject* obj = format->getSceneObject();
				ISceneNode* sceneNode = obj->getSceneNode();
				MG::Vec3 pos;
				sceneNode->getPosition(pos);
				colSystem->getStickHeight(pos,pos.y);
				sceneNode->setPosition(pos);
				format->fill();
				//sceneNode->translate(moveVec,MG::ISceneNode::TS_WORLD);
			}
		}
    }

    //-----------------------------------------------------------------------
    void MainForm::loadSceneEntityList()
    {
        clearSceneEntityList();

		/*
			场景中已经存在的entity列表的初始化
		*/
		
        {
            //////////////////////////////////////////////////////////////////////////////

			ISceneObject* sceneObj = NULL;
			IEntity* entity = NULL;
            std::map<U32, std::map<Str, std::vector<IEntity*>>>  groupEntityList;

            //////////////////////////////////////////////////////////////////////////////

            {
                std::vector<ISceneObjectXmlFormat*> formatList;

                CoreManager::getInstance().getScene()->getXmlSerializer()->
					getSceneObjectXmlFormatList(SOT_ENTITY, formatList);

                for (  std::vector<ISceneObjectXmlFormat*>::iterator iter = formatList.begin(); iter!=formatList.end(); iter++ )
                {
                    sceneObj = (*iter)->getSceneObject();
                    entity = (IEntity*)sceneObj;

                    U32 declID = entity->getModelObject()->getModelDeclarationID();
                    Str groupName = entity->getDeclaration().batchGroup;

                    groupEntityList[declID][groupName].push_back( entity );
                }
            }

			//trees
			std::map<U32, std::vector<ITree*>>  groupTreeList;
			{
				std::vector<ISceneObjectXmlFormat*> formatListTree;

				CoreManager::getInstance().getScene()->getXmlSerializer()->
					getSceneObjectXmlFormatList(SOT_TREE, formatListTree);

				for (  std::vector<ISceneObjectXmlFormat*>::iterator iter = formatListTree.begin(); iter!=formatListTree.end(); iter++ )
				{
					ISceneObject* sceneTreeObj = NULL;
					ITree* tree = NULL;
					sceneTreeObj = (*iter)->getSceneObject();
					tree = (ITree*)sceneTreeObj;

					UInt declID = tree->getBaseTreeId();
					//Str groupName = entity->getDeclaration().batchGroup;

					groupTreeList[declID].push_back( tree );
				}
			}
			//grasses
			std::map<U32, std::vector<IGrass*>>	groupGrassList;
			{
				std::vector<ISceneObjectXmlFormat*> formatListGrass;

				CoreManager::getInstance().getScene()->getXmlSerializer()->
					getSceneObjectXmlFormatList(SOT_GRASS, formatListGrass);

				for (  std::vector<ISceneObjectXmlFormat*>::iterator iter = formatListGrass.begin(); iter!=formatListGrass.end(); iter++ )
				{
					ISceneObject* sceneGrassObj = NULL;
					IGrass* grass = NULL;
					sceneGrassObj = (*iter)->getSceneObject();
					grass = (IGrass*)sceneGrassObj;

					UInt declID = grass->getBaseGrassId();
					//Str groupName = entity->getDeclaration().batchGroup;

					groupGrassList[declID].push_back( grass );
				}
			}
            //////////////////////////////////////////////////////////////////////////////

            {
                TreeNode ^ rootTreeNode = gcnew TreeNode("模型元素");
                element_list->Nodes->Add( rootTreeNode );
                
                for ( std::map<U32, std::map<Str, std::vector<IEntity*>>>::iterator iter = groupEntityList.begin()
					; iter!=groupEntityList.end(); iter++)
                {
                    U32 declID = iter->first;

                    ////////////////////////////////////////////////////////////

                    ModelDeclaration* decl		= CoreManager::getInstance().getEngineMain()->
						resourceMgr()->getModelDeclaration(declID);

                    String^ declName			= TypeConverter::Char8ToStr( decl->name.c_str() ) ;
                    TreeNode ^ typeTreeNode		= gcnew TreeNode(declName);

                    typeTreeNode->Tag = "";

                    rootTreeNode->Nodes->Add( typeTreeNode );

                    ////////////////////////////////////////////////////////////

                    for ( std::map<Str, std::vector<IEntity*>>::iterator jter = iter->second.begin(); jter!=iter->second.end(); jter++ )
                    {
                        Str groupName = jter->first;

                        groupName = Str("批次组:") + groupName;

                        ////////////////////////////////////////////////////////////

                        String^ batchNodeName    = TypeConverter::Char8ToStr( groupName.c_str() ) ;

                        TreeNode ^ batchTreeNode = gcnew TreeNode(batchNodeName);
                        batchTreeNode->Tag = "";

                        typeTreeNode->Nodes->Add( batchTreeNode );

                        ////////////////////////////////////////////////////////////

                        UInt count = jter->second.size();

                        for ( UInt i=0; i<count; i++ )
                        {
                            entity = jter->second[i];

                            Str entityName = entity->getName();

                            ////////////////////////////////////////////////////////////

                            String^ entityNodeName		= TypeConverter::Char8ToStr( entityName.c_str() ) ;

                            TreeNode^ entityTreeNode	= gcnew TreeNode(entityNodeName);
                            entityTreeNode->Tag			= "Entity";
                            entityTreeNode->Name		= entityNodeName;

                            batchTreeNode->Nodes->Add( entityTreeNode );

                            ////////////////////////////////////////////////////////////
                        }
                    }
                }

				for (std::map<U32, std::vector<ITree*>>::iterator it = groupTreeList.begin(); it != groupTreeList.end(); ++it)
				{
					U32 declID = it->first;

					IScene* scene = CoreManager::getInstance().getScene();
					if (scene != NULL)
					{
						ITreeManager* pTreeMgr = scene->getTreeManager();
						TreeDeclaration* pTreeDecl = pTreeMgr->getTreeDeclarationByIndex(declID);
						if (pTreeDecl != NULL)
						{
							String^ declName = TypeConverter::Char8ToStr( pTreeDecl->strName.c_str() ) ;
							TreeNode ^ typeTreeNode = gcnew TreeNode(declName);
							typeTreeNode->Tag = "";
							rootTreeNode->Nodes->Add( typeTreeNode );

							std::vector<ITree*>& vecTrees = it->second;
							for (size_t i = 0; i < vecTrees.size(); ++i)
							{
								String^ treeNodeName		= TypeConverter::Char8ToStr( vecTrees[i]->getName().c_str() ) ;

								TreeNode^ entityTreeNode	= gcnew TreeNode(treeNodeName);
								entityTreeNode->Tag			= "Tree";
								entityTreeNode->Name		= treeNodeName;

								typeTreeNode->Nodes->Add( entityTreeNode );
							}
						}
					}
				}

				for (std::map<U32, std::vector<IGrass*>>::iterator it = groupGrassList.begin(); it != groupGrassList.end(); ++it)
				{
					U32 declID = it->first;

					IScene* scene = CoreManager::getInstance().getScene();
					if (scene != NULL)
					{
						ITreeManager* pTreeMgr = scene->getTreeManager();
						GrassDeclaration* pGrassDecl = pTreeMgr->getGrassDeclarationByIndex(declID);
						if (pGrassDecl != NULL)
						{
							String^ declName = TypeConverter::Char8ToStr( pGrassDecl->strName.c_str() ) ;
							TreeNode ^ typeGrassNode = gcnew TreeNode(declName);
							typeGrassNode->Tag = "";
							rootTreeNode->Nodes->Add( typeGrassNode );

							std::vector<IGrass*>& vecGrasses = it->second;
							for (size_t i = 0; i < vecGrasses.size(); ++i)
							{
								String^ grassNodeName		= TypeConverter::Char8ToStr( vecGrasses[i]->getName().c_str() ) ;

								TreeNode^ entityTreeNode	= gcnew TreeNode(grassNodeName);
								entityTreeNode->Tag			= "Grass";
								entityTreeNode->Name		= grassNodeName;

								typeGrassNode->Nodes->Add( entityTreeNode );
							}
						}
					}
				}
                //rootTreeNode->ExpandAll();
            }
            
        }
    }
    //-----------------------------------------------------------------------
    void MainForm::clearSceneEntityList()
    {
        element_list->Nodes->Clear();
    }
    //-----------------------------------------------------------------------
    void MainForm::selectSceneEntityFromList()
    {
        if ( element_list->SelectedNode != nullptr &&
			element_list->SelectedNode->Tag != nullptr )
        {
            String^ tag = element_list->SelectedNode->Tag->ToString();
            if ( System::String::Compare( tag, "Entity" ) == 0  )
            {
                StrToChar8 name( element_list->SelectedNode->Text );
                ISceneObjectXmlFormat* format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat( name.getChar8(), SOT_ENTITY);
                if ( format )
                {
                    loadSceneElementProps( format, false );
                    CoreManager::getInstance().getScene()->getSceneObjectController()->setFocus( format->getSceneObject() );

                    Vec3 pos;
                    format->getSceneObject()->getSceneNode()->getPosition(pos);
                    CoreManager::getInstance().getScene()->getActiveCamera()->focusPosition(pos);
                }
            }
			else if ( System::String::Compare( tag, "Tree" ) == 0 )
			{
				StrToChar8 name( element_list->SelectedNode->Text );
				ISceneObjectXmlFormat* format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat( name.getChar8(), SOT_TREE);
				if ( format )
				{
					loadSceneElementProps( format, false );
					CoreManager::getInstance().getScene()->getSceneObjectController()->setFocus( format->getSceneObject() );

					Vec3 pos;
					format->getSceneObject()->getSceneNode()->getPosition(pos);
					CoreManager::getInstance().getScene()->getActiveCamera()->focusPosition(pos);
				}
			}
			else if ( System::String::Compare( tag, "Grass" ) == 0 )
			{
				StrToChar8 name( element_list->SelectedNode->Text );
				ISceneObjectXmlFormat* format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat( name.getChar8(), SOT_GRASS);
				if ( format )
				{
					loadSceneElementProps( format, false );
					CoreManager::getInstance().getScene()->getSceneObjectController()->setFocus( format->getSceneObject() );

					Vec3 pos;
					format->getSceneObject()->getSceneNode()->getPosition(pos);
					CoreManager::getInstance().getScene()->getActiveCamera()->focusPosition(pos);
				}
			}
			else
			{

			}
        }
    }
    //-----------------------------------------------------------------------
    void MainForm::destroySceneEntityFromList()
    {
        if ( element_list->SelectedNode != nullptr )
        {
            String^ tag = element_list->SelectedNode->Tag->ToString();
            if ( System::String::Compare( tag, "Entity" ) == 0  ) //单个Entity
            {
				CoreManager::getInstance().getScene()->getSceneObjectController()->setFocus(NULL);
                StrToChar8 name( element_list->SelectedNode->Text );
                CoreManager::getInstance().getScene()->getXmlSerializer()->removeSceneObjectFormat( name.getChar8(), SOT_ENTITY, true);
                element_list->SelectedNode->Remove();

                revert();
            }else if (System::String::Compare( tag, "" ) == 0) //一组Entity
            {
				CoreManager::getInstance().getScene()->getSceneObjectController()->setFocus(NULL);
				int count = element_list->SelectedNode->Nodes->Count;
				for (int i=0; i<count; ++i)
				{
					tag = element_list->SelectedNode->Nodes[i]->Tag->ToString();
					if ( System::String::Compare( tag, "Entity" ) == 0  )
					{
						StrToChar8 name( element_list->SelectedNode->Nodes[i]->Text);
						CoreManager::getInstance().getScene()->getXmlSerializer()->removeSceneObjectFormat( name.getChar8(), SOT_ENTITY, true);
					}
				}
				element_list->SelectedNode->Remove();
				revert();
            }
        }
    }
	//-----------------------------------------------------------------------
	void MainForm::loadSceneEffectList()
	{
		//先清除列表
		clearSceneEffectList();

		std::vector<IEffectEntity*> effectList;

		//遍历特效
		std::vector<ISceneObjectXmlFormat*> effectFormatList;
		CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_EFFECTENTITY, effectFormatList, true);
		std::vector<ISceneObjectXmlFormat*>::iterator effectIter = effectFormatList.begin();
		for ( ; effectIter!=effectFormatList.end(); effectIter++ )
		{
			IEffectEntity* effectEntity = static_cast<IEffectEntity*>((*effectIter)->getSceneObject());
			effectList.push_back( effectEntity );
		}

		//特效
		System::String^ nodeName = TypeConverter::Char8ToStr( SCENE_OBJECT_GROUP_STR_EFFECT );
		System::Int32 count = effectList.size();
		System::String^ groupText = "特效" + "(数量：" + count.ToString() + ")";
		TreeNode^ effectNode = gcnew TreeNode();
		effectNode->Name = nodeName;
		effectNode->Text = groupText;
		element_list->Nodes->Add( effectNode );

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
	void MainForm::clearSceneEffectList()
	{
	}
	//-----------------------------------------------------------------------
	void MainForm::selectSceneEffectFromList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::destroySceneEffectFromList()
	{
	}
	//-----------------------------------------------------------------------
	void MainForm::loadScenePlantList()
	{

	}
	//-----------------------------------------------------------------------
	void MainForm::clearScenePlantList()
	{
	}
	//-----------------------------------------------------------------------
	void MainForm::selectScenePlantFromList()
	{
	}
	//-----------------------------------------------------------------------
	void MainForm::destroyScenePlantFromList()
	{
	}

	//-----------------------------------------------------------------------
	void MainForm::loadSubScene()
	{
		openSubsceneFileDialog->InitialDirectory = System::Windows::Forms::Application::StartupPath+L"\\Config\\Scene";
		openSubsceneFileDialog->Filter = "XML files (*.xml)|*.xml|All Files (*.*)|*.*";
		openSubsceneFileDialog->FilterIndex = 1;
		openSubsceneFileDialog->Title = "选择策划场景文件";
		openSubsceneFileDialog->RestoreDirectory = true;
		if (openSubsceneFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			System::String^ fileName = openSubsceneFileDialog->FileName;
			StrToChar8 strFileName(fileName);
			unloadSubScene();
			IScene* scene = CoreManager::getInstance().getScene();
			scene->getXmlSerializer()->loadSubSceneFile(strFileName.getChar8(),FormSet::main_form->isEditorMode());

			//成功加载场景后显示场景
			Menu_Setting_ShowSubScene->Checked = true;
			showSubScene(true);
		}
	}

	//-----------------------------------------------------------------------
	void MainForm::unloadSubScene()
	{
		IScene* scene = CoreManager::getInstance().getScene();
		scene->getXmlSerializer()->unloadSubScene();

		//卸载场景后隐藏场景
		Menu_Setting_ShowSubScene->Checked = false;
	}
	//-----------------------------------------------------------------------
	void MainForm::showSubScene(bool show)
	{
		IScene* scene = CoreManager::getInstance().getScene();
		scene->getXmlSerializer()->showSubscene(show);
	}
    //-----------------------------------------------------------------------
    void MainForm::loadSceneEnvironmentLight()
    {
        MG::Color ambient;
        ambient = CoreManager::getInstance().getScene()->getAmbientLight();
        
		TextBox_Ambient_R->Text = TypeConverter::DoubleToStr(ambient.r);
		TextBox_Ambient_G->Text = TypeConverter::DoubleToStr(ambient.g);
		TextBox_Ambient_B->Text = TypeConverter::DoubleToStr(ambient.b);

        ILight* light = CoreManager::getInstance().getScene()->getDefaultLight();
        if (light)
        {
            MG::Color diffuse;
            diffuse = light->getDiffuseColour();
			TextBox_Diffuse_R->Text = TypeConverter::DoubleToStr(diffuse.r);
			TextBox_Diffuse_G->Text = TypeConverter::DoubleToStr(diffuse.g);
			TextBox_Diffuse_B->Text = TypeConverter::DoubleToStr(diffuse.b);

            MG::Color spec;
            spec = light->getSpecularColour();
			TextBox_Specular_R->Text = TypeConverter::DoubleToStr(spec.r);
			TextBox_Specular_G->Text = TypeConverter::DoubleToStr(spec.g);
			TextBox_Specular_B->Text = TypeConverter::DoubleToStr(spec.b);
        }


		WorldEnvironment env = CoreManager::getInstance().getScene()->getTreeManager()->getWorldEnv();
		MG::Color STAmbient = env.cLightAmbient;
		MG::Color STDiffuse = env.cLightDiffuse;
		MG::Color STSpecular = env.cLightSpecular;
		TextBox_STAmbient_R->Text = TypeConverter::DoubleToStr(STAmbient.r);
		TextBox_STAmbient_G->Text = TypeConverter::DoubleToStr(STAmbient.g);
		TextBox_STAmbient_B->Text = TypeConverter::DoubleToStr(STAmbient.b);
		TextBox_STDiffuse_R->Text = TypeConverter::DoubleToStr(STDiffuse.r);
		TextBox_STDiffuse_G->Text = TypeConverter::DoubleToStr(STDiffuse.g);
		TextBox_STDiffuse_B->Text = TypeConverter::DoubleToStr(STDiffuse.b);
		TextBox_STSpecular_R->Text = TypeConverter::DoubleToStr(STSpecular.r);
		TextBox_STSpecular_G->Text = TypeConverter::DoubleToStr(STSpecular.g);
		TextBox_STSpecular_B->Text = TypeConverter::DoubleToStr(STSpecular.b);

		MG::Color SGAmbient = env.cGrassLightAmbient;
		MG::Color SGDiffuse = env.cGrassLightDiffuse;
		MG::Color SGSpecular = env.cGrassLightSpecular;
		TextBox_SGAmbient_R->Text = TypeConverter::DoubleToStr(SGAmbient.r);
		TextBox_SGAmbient_G->Text = TypeConverter::DoubleToStr(SGAmbient.g);
		TextBox_SGAmbient_B->Text = TypeConverter::DoubleToStr(SGAmbient.b);
		TextBox_SGDiffuse_R->Text = TypeConverter::DoubleToStr(SGDiffuse.r);
		TextBox_SGDiffuse_G->Text = TypeConverter::DoubleToStr(SGDiffuse.g);
		TextBox_SGDiffuse_B->Text = TypeConverter::DoubleToStr(SGDiffuse.b);
		TextBox_SGSpecular_R->Text = TypeConverter::DoubleToStr(SGSpecular.r);
		TextBox_SGSpecular_G->Text = TypeConverter::DoubleToStr(SGSpecular.g);
		TextBox_SGSpecular_B->Text = TypeConverter::DoubleToStr(SGSpecular.b);

        IDisplay* display = CoreManager::getInstance().getEngineMain()->display();

        Vec4 tp = display->getTerrainLightingParameter();
        terrainLightingParameterX_txt->Text = TypeConverter::DoubleToStr(tp.x);
        terrainLightingParameterY_txt->Text = TypeConverter::DoubleToStr(tp.y);
        terrainLightingParameterZ_txt->Text = TypeConverter::DoubleToStr(tp.z);
        terrainLightingParameterW_txt->Text = TypeConverter::DoubleToStr(tp.w);

    }
    //-----------------------------------------------------------------------
    void MainForm::configSceneEnvironmentLight()
    {
        MG::Color ambient;

		ambient.r = TypeConverter::StrToDouble(TextBox_Ambient_R->Text);
        ambient.g = TypeConverter::StrToDouble(TextBox_Ambient_G->Text);
        ambient.b = TypeConverter::StrToDouble(TextBox_Ambient_B->Text);

        CoreManager::getInstance().getScene()->setAmbientLight( ambient );

        ILight* light = CoreManager::getInstance().getScene()->getDefaultLight();
        if (light)
        {
            MG::Color diffuse;
			diffuse.r = TypeConverter::StrToDouble(TextBox_Diffuse_R->Text);
			diffuse.g = TypeConverter::StrToDouble(TextBox_Diffuse_G->Text);
			diffuse.b = TypeConverter::StrToDouble(TextBox_Diffuse_B->Text);
            light->setDiffuseColour(diffuse);

            MG::Color spec;
			spec.r = TypeConverter::StrToDouble(TextBox_Specular_R->Text);
			spec.g = TypeConverter::StrToDouble(TextBox_Specular_G->Text);
			spec.b = TypeConverter::StrToDouble(TextBox_Specular_B->Text);
            light->setSpecularColour(spec);

        }

        {
            IDisplay* display = CoreManager::getInstance().getEngineMain()->display();

            Vec4 tp;
            tp.x = TypeConverter::StrToDouble(terrainLightingParameterX_txt->Text);
            tp.y = TypeConverter::StrToDouble(terrainLightingParameterY_txt->Text);
            tp.z = TypeConverter::StrToDouble(terrainLightingParameterZ_txt->Text);   
            tp.w = TypeConverter::StrToDouble(terrainLightingParameterZ_txt->Text);   
            display->setTerrainLightingParameter( tp );

            display->apply();
        }

		//SpeedTree光照环境
		{
			MG::Color STAmbient,STDiffuse,STSpecular;
			STAmbient.r = TypeConverter::StrToDouble(TextBox_STAmbient_R->Text);
			STAmbient.g = TypeConverter::StrToDouble(TextBox_STAmbient_G->Text);
			STAmbient.b = TypeConverter::StrToDouble(TextBox_STAmbient_B->Text);

			STDiffuse.r = TypeConverter::StrToDouble(TextBox_STDiffuse_R->Text);
			STDiffuse.g = TypeConverter::StrToDouble(TextBox_STDiffuse_G->Text);
			STDiffuse.b = TypeConverter::StrToDouble(TextBox_STDiffuse_B->Text);

			STSpecular.r = TypeConverter::StrToDouble(TextBox_STSpecular_R->Text);
			STSpecular.g = TypeConverter::StrToDouble(TextBox_STSpecular_G->Text);
			STSpecular.b = TypeConverter::StrToDouble(TextBox_STSpecular_B->Text);

			MG::Color SGAmbient,SGDiffuse,SGSpecular;
			SGAmbient.r = TypeConverter::StrToDouble(TextBox_SGAmbient_R->Text);
			SGAmbient.g = TypeConverter::StrToDouble(TextBox_SGAmbient_G->Text);
			SGAmbient.b = TypeConverter::StrToDouble(TextBox_SGAmbient_B->Text);

			SGDiffuse.r = TypeConverter::StrToDouble(TextBox_SGDiffuse_R->Text);
			SGDiffuse.g = TypeConverter::StrToDouble(TextBox_SGDiffuse_G->Text);
			SGDiffuse.b = TypeConverter::StrToDouble(TextBox_SGDiffuse_B->Text);

			SGSpecular.r = TypeConverter::StrToDouble(TextBox_SGSpecular_R->Text);
			SGSpecular.g = TypeConverter::StrToDouble(TextBox_SGSpecular_G->Text);
			SGSpecular.b = TypeConverter::StrToDouble(TextBox_SGSpecular_B->Text);

			ITreeManager* pTreeMgr = CoreManager::getInstance().getScene()->getTreeManager();
			WorldEnvironment env = pTreeMgr->getWorldEnv();
			env.cLightAmbient = STAmbient;
			env.cLightDiffuse = STDiffuse;
			env.cLightSpecular = STSpecular;
			env.cGrassLightAmbient = SGAmbient;
			env.cGrassLightDiffuse = SGDiffuse;
			env.cGrassLightSpecular = SGSpecular;
			pTreeMgr->setWorldEnv(env);
		}
    }
    //-----------------------------------------------------------------------
    void MainForm::configSceneLightDirection()
    {
        ICamera* cam = CoreManager::getInstance().getScene()->getActiveCamera();
        ILight* light = CoreManager::getInstance().getScene()->getDefaultLight();
        if (light&&cam)
        {
            Vec3 pos;
            Vec3 dir;
            cam->getDirection(dir);
            cam->getPosition(pos);

            light->setDirection(dir);
            light->setPosition(pos);
        }
    }

    //-----------------------------------------------------------------------
    void MainForm::genarateLightingMap()
    {
        Flt offset = (Flt)TypeConverter::StrToDouble(txt_terrainShadowOffset->Text);
        CoreManager::getInstance().getScene()->getShadowManager()->setTerrainShadowOffset( offset );
        CoreManager::getInstance().getScene()->getShadowManager()->genarateLightingMap();
    }

    //-----------------------------------------------------------------------
    void MainForm::genarateMiniMap()
    {
        Flt centerX = (Flt)TypeConverter::StrToDouble(minimap_center_x->Text);
        Flt centerZ = (Flt)TypeConverter::StrToDouble(minimap_center_z->Text);

        Flt sizeW = (Flt)TypeConverter::StrToDouble(minimap_size_w->Text);
        Flt sizeH = (Flt)TypeConverter::StrToDouble(minimap_size_h->Text);

        Flt texSizeW = (Flt)TypeConverter::StrToDouble(minimap_tex_size_w->Text);
        Flt texSizeH = (Flt)TypeConverter::StrToDouble(minimap_tex_size_h->Text);

        IMiniMapManager* mgr = CoreManager::getInstance().getScene()->getMiniMapManager();

        if ( mgr )
        {
            folderBrowserDialog1->SelectedPath = System::Windows::Forms::Application::StartupPath;
            if ( folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
            {
                mLastFocusDir = folderBrowserDialog1->SelectedPath;
                StrToChar8 pathStr( folderBrowserDialog1->SelectedPath );
                Str savePath = pathStr.getChar8();
                
                mgr->genarateMiniMap( Vec2(centerX,centerZ), Vec2(sizeW,sizeH), savePath, Vec2(texSizeW,texSizeH) );
            }
        }
    }

    //-----------------------------------------------------------------------
    void MainForm::applyCompositorSetting()
    {
        IScene* scene    = CoreManager::getInstance().getScene();
        if ( scene )
        {
            //scene->getCompositorManager()->addCompositor( "MG_FAKE_HDR", 0 );

            scene->getCompositorManager()->setCompositorEnable( "MG_POST_BLOOM", Bloom_ckb->Checked );

            //scene->getCompositorManager()->setCompositorEnable( "MG_TEST", Bloom_ckb->Checked );
            //scene->getCompositorManager()->setCompositorEnable( "MG_FAKE_HDR", FakeHDR_ckb->Checked );
            //scene->getCompositorManager()->setCompositorEnable( "MGHDR", HDR_ckb->Checked );
            //scene->getCompositorManager()->setCompositorEnable( "MGMotionBlur", MotionBlur_ckb->Checked );
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

		////////////////////////////////////////////////////////////////////////////


		if ( ckb_water_visible->Checked )
		{
			display->setTerrainWaterVisible( true );
		}else
		{
			display->setTerrainWaterVisible( false );
		}

		////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////


		if ( ckb_entity_visible->Checked )
		{
			display->setEntityVisible( true );
		}else
		{
			display->setEntityVisible( false );
		}

		////////////////////////////////////////////////////////////////////////////

        display->apply();

  
    }
	//-----------------------------------------------------------------------
	void MainForm::onEventPressDefineWaterHeightButton()
	{
		IEditorSystem* editorSys    = CoreManager::getInstance().getEngineMain()->editorSystem();
		if ( !editorSys )
			return;

		bool islocked = !editorSys->getTerrainUniformHeightOperationManager()->isLocked();
		editorSys->getTerrainUniformHeightOperationManager()->lock(islocked);

		if ( islocked )
		{
			double waterHeight = 0;

			if ( !System::String::IsNullOrEmpty( water_height_text_box->Text) )
			{
				waterHeight = (Flt)TypeConverter::StrToDouble(water_height_text_box->Text);
				editorSys->getTerrainUniformHeightOperationManager()->setWaterHeight((Flt)waterHeight);	
			}

			waterHeight = editorSys->getTerrainUniformHeightOperationManager()->getWaterHeight();
			water_height_text_box->Text = TypeConverter::DoubleToStr(waterHeight);
			water_height_text_box->Enabled = false;

			Str Lock = "更改";
			water_height_confirm->Text = TypeConverter::Char8ToStr(Lock.c_str());
		}
		else
		{
			water_height_text_box->Enabled = true;

			Str unLock = "锁定";
			water_height_confirm->Text = TypeConverter::Char8ToStr(unLock.c_str());
		}
	}

    //-----------------------------------------------------------------------
    void MainForm::loadShadowSetting()
    {
        IDisplay* display = CoreManager::getInstance().getEngineMain()->display();

		bool receiveShadow = display->getTerrainReceiveDynamicShadowsEnabled();
		bool enableLightMap = display->getTerrainLightmapEnabled();
		terrain_dynamic_shadow_check->Checked = receiveShadow;
		terrain_shadow_check->Checked = enableLightMap;

		MG::ShadowType type = display->getShadowType();
		switch (type)
		{
		case SCL_NONE:
			rb_shadow_none->Checked = true;
			break;

		case SCL_PSSM_DIFFUSE_TEXTURE:
		case SCL_PSSM_DEPTH_TEXTURE:
			rb_shadow_pssm->Checked = true;
			break;

        case SCL_UNIFORM_DEPTH_TEXTURE:
            rb_shadow_uniform->Checked = true;
            break;
        case SCL_UNIFORM_FOCUSED_DEPTH_TEXTURE:
            rb_shadow_uniform_focused->Checked = true;
            break;
        case SCL_LISPSM_DEPTH_TEXTURE:
            rb_shadow_lispsm->Checked = true;
            break;
        case SCL_PLANE_OPTIMALDEPTH_TEXTURE:
            rb_shadow_plane->Checked = true;
            break;
		}

        Vec4 sp = display->getShadowParameter();
        shadowParameterX_txt->Text = TypeConverter::DoubleToStr(sp.x);
        shadowParameterY_txt->Text = TypeConverter::DoubleToStr(sp.y);
        shadowParameterZ_txt->Text = TypeConverter::DoubleToStr(sp.z);
        shadowParameterW_txt->Text = TypeConverter::DoubleToStr(sp.w);
    }

    //-----------------------------------------------------------------------
    void MainForm::applyShadowSetting()
    {
        IDisplay* display = CoreManager::getInstance().getEngineMain()->display();


        //----------------------------------------------------------

        display->setTerrainLightmapEnabled( terrain_shadow_check->Checked );
		AppDataManager::getInstance()->setLightMapEnable(terrain_shadow_check->Checked);

        display->setTerrainReceiveDynamicShadowsEnabled( terrain_dynamic_shadow_check->Checked );

		AppDataManager::getInstance()->setReceiveShadow(terrain_dynamic_shadow_check->Checked);


        //----------------------------------------------------------

        if ( rb_shadow_none->Checked )
        {
            display->setShadowType( SCL_NONE );
			AppDataManager::getInstance()->setShadowType(SCL_NONE);
        }else
        if ( rb_shadow_pssm->Checked )
        {
            display->setShadowType( SCL_PSSM_DEPTH_TEXTURE );
			AppDataManager::getInstance()->setShadowType(SCL_PSSM_DEPTH_TEXTURE);
        }
        else
        if ( rb_shadow_uniform->Checked )
        {
            display->setShadowType( SCL_UNIFORM_DEPTH_TEXTURE );
            AppDataManager::getInstance()->setShadowType(SCL_UNIFORM_DEPTH_TEXTURE);
        }
        else
        if ( rb_shadow_uniform_focused->Checked )
        {
            display->setShadowType( SCL_UNIFORM_FOCUSED_DEPTH_TEXTURE );
            AppDataManager::getInstance()->setShadowType(SCL_UNIFORM_FOCUSED_DEPTH_TEXTURE);
        }
        else
        if ( rb_shadow_lispsm->Checked )
        {
            display->setShadowType( SCL_LISPSM_DEPTH_TEXTURE );
            AppDataManager::getInstance()->setShadowType(SCL_LISPSM_DEPTH_TEXTURE);
        }
        else
        if ( rb_shadow_plane->Checked )
        {
            display->setShadowType( SCL_PLANE_OPTIMALDEPTH_TEXTURE );
            AppDataManager::getInstance()->setShadowType(SCL_PLANE_OPTIMALDEPTH_TEXTURE);
        }

        //----------------------------------------------------------

        {
            Vec4 sp;
            sp.x = TypeConverter::StrToDouble(shadowParameterX_txt->Text);
            sp.y = TypeConverter::StrToDouble(shadowParameterY_txt->Text);
            sp.z = TypeConverter::StrToDouble(shadowParameterZ_txt->Text);   
            sp.w = TypeConverter::StrToDouble(shadowParameterW_txt->Text);   
            display->setShadowParameter( sp );
        }


        display->apply();
    }

    //-----------------------------------------------------------------------
    void MainForm::applyFogSetting()
    {
        IDisplay* display = CoreManager::getInstance().getEngineMain()->display();
        //----------------------------------------------------------

        MG::Color color ;

        color.r = TypeConverter::StrToDouble(txt_fog_color_r->Text);
        color.g = TypeConverter::StrToDouble(txt_fog_color_g->Text);
        color.b = TypeConverter::StrToDouble(txt_fog_color_b->Text);  

        Flt expDensity  = TypeConverter::StrToDouble(txt_fog_exp->Text);
        Flt fogStart    = TypeConverter::StrToDouble(txt_fog_start->Text);
        Flt fogEnd      = TypeConverter::StrToDouble(txt_fog_end->Text);


        if ( rb_fog_none->Checked )
        {
            display->setFogLevel(FOL_NONE,color,expDensity,fogStart,fogEnd);
			AppDataManager::getInstance()->setFogLevel(FOL_NONE);
        }else
        if ( rb_fog_line->Checked )
        {
            display->setFogLevel(FOL_LINEAR,color,expDensity,fogStart,fogEnd);
			AppDataManager::getInstance()->setFogLevel(FOL_LINEAR);
        }else
        {
            display->setFogLevel(FOL_EXP,color,expDensity,fogStart,fogEnd);
			AppDataManager::getInstance()->setFogLevel(FOL_EXP);
        }

        //----------------------------------------------------------
		ITreeManager* manager = NULL;
		IScene* scene = CoreManager::getInstance().getScene();
		if ( scene )
			manager = scene->getTreeManager();

		if ( manager )
		{
			manager->setFog(color, fogStart, fogEnd);
		}
        display->apply();
    }

    //-----------------------------------------------------------------------
    void MainForm::loadFogSetting()
    {

        IDisplay* display = CoreManager::getInstance().getEngineMain()->display();

        //----------------------------------------------------------

        MG::Color color  = display->getFogColor();

        txt_fog_color_r->Text = TypeConverter::DoubleToStr(color.r);
        txt_fog_color_g->Text = TypeConverter::DoubleToStr(color.g);
        txt_fog_color_b->Text = TypeConverter::DoubleToStr(color.b);

        //----------------------------------------------------------

		FogLevel fogLevel = display->getFogLevel();
		switch (fogLevel)
		{
		case FOL_NONE:
			rb_fog_none->Checked = true;
			break;
		case FOL_LINEAR:
			rb_fog_line->Checked = true;
			break;
		case FOL_EXP:
		case FOL_EXP2:
			rb_fog_exp->Checked = true;
			break;
		}

        txt_fog_exp->Text = TypeConverter::DoubleToStr( display->getFogExpDensity() );

        txt_fog_start->Text = TypeConverter::DoubleToStr( display->getFogLinearStart() );

        txt_fog_end->Text = TypeConverter::DoubleToStr( display->getFogLinearEnd() );

        //----------------------------------------------------------
    }

	//-----------------------------------------------------------------------
	void MainForm::applyPlantSetting()
	{
		ITreeManager* manager = NULL;

		IScene* scene = CoreManager::getInstance().getScene();
		if ( scene )
			manager = scene->getTreeManager();

		if ( manager )
		{
			//----------------------------------------------------------
			
			//从UI获取speedtree参数
			
			Vec3 direction;

			direction.x = (Flt)TypeConverter::StrToDouble(textBoxWindDirX->Text);
			direction.y = (Flt)TypeConverter::StrToDouble(textBoxWindDirY->Text);
			direction.z = (Flt)TypeConverter::StrToDouble(textBoxWindDirZ->Text);

			Flt	intensity = (Flt)TypeConverter::StrToDouble(lableWindIntensity->Text);

			Flt grassLodStart = (Flt)TypeConverter::StrToDouble(textBox_grassLod_start->Text);
			Flt grassLodEnd = (Flt)TypeConverter::StrToDouble(textBox_grassLod_end->Text);

			//----------------------------------------------------------

			//设置到系统

			manager->setWindEnable(wind_check->Checked);
			manager->setGlobalWindDirection(direction);
			manager->setGlobalWindStrength(intensity);

			manager->setGrassLod(grassLodStart,grassLodEnd);

			//----------------------------------------------------------
		}

	}
	//-----------------------------------------------------------------------
	void MainForm::loadPlantSetting()
	{
		ITreeManager* manager = NULL;

		IScene* scene = CoreManager::getInstance().getScene();
		if ( scene )
			manager = scene->getTreeManager();

		if ( manager )
		{
			//----------------------------------------------------------

			//从系统获取speedtree参数

			Vec3 direction = manager->getGlobalWindDirection();

			Flt intensity = manager->getGlobalWindStrength();

			Vec2 grassLod;
			manager->getGrassLod(grassLod.x, grassLod.y);

			//----------------------------------------------------------

			//设置到UI上
			textBoxWindDirX->Text = TypeConverter::DoubleToStr((Double)direction.x);
			textBoxWindDirY->Text = TypeConverter::DoubleToStr((Double)direction.y);
			textBoxWindDirZ->Text = TypeConverter::DoubleToStr((Double)direction.z);

			lableWindIntensity->Text = TypeConverter::DoubleToStr((Double)intensity);

			textBox_grassLod_start->Text = TypeConverter::DoubleToStr((Double)grassLod.x);
			textBox_grassLod_end->Text = TypeConverter::DoubleToStr((Double)grassLod.y);

			Bool bWindEnable = manager->isWindEnabled();
			if (bWindEnable)
			{
				wind_check->CheckState = System::Windows::Forms::CheckState::Checked;
			}
			else
			{
				wind_check->CheckState = System::Windows::Forms::CheckState::Unchecked;
			}


			//----------------------------------------------------------
		}
	}

	//-----------------------------------------------------------------------
	void MainForm::onEventPressDefineBatchButton()
	{
		IEditorSystem* editorSys    = CoreManager::getInstance().getEngineMain()->editorSystem();
		if ( !editorSys )
			return;

		bool islocked = !editorSys->getTerrainDefineTreeOperationManager()->isLocked();
		editorSys->getTerrainDefineTreeOperationManager()->lock(islocked);

		if ( islocked )
		{
			StrToChar8 strToChar8 = StrToChar8(specialize_batch_textBox->Text);
			Str groupname = strToChar8.getChar8();
			if ( !groupname.empty() )
			{
				//editorSys->getTerrainDefineBatchEntityOperationManager()->setGroupName(groupname);
				editorSys->getTerrainDefineTreeOperationManager()->setGroupName(groupname);
			}
			groupname = editorSys->getTerrainDefineTreeOperationManager()->getGroupName();
			specialize_batch_textBox->Text = TypeConverter::Char8ToStr(groupname.c_str());
			specialize_batch_textBox->Enabled = false;

			Str Lock = "更改";
			plant_batch_define_button->Text = TypeConverter::Char8ToStr(Lock.c_str());
		}
		else
		{
			specialize_batch_textBox->Enabled = true;

			Str unLock = "锁定";
			plant_batch_define_button->Text = TypeConverter::Char8ToStr(unLock.c_str());
		}
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
		toolStripStatusCamSpeed->Text = "CameraSpeed:"+TypeConverter::U32ToStr(level);
	}
	//-----------------------------------------------------------------------
	void MainForm::onEventBrushSizeChanged(Int wheel)
	{
		IEditorSystem* editorSys    = CoreManager::getInstance().getEngineMain()->editorSystem();
		if ( !editorSys )
			return;

		if ( prop_tab_ctrl->SelectedTab != terrain_page )
			return;

		//同步当前的画笔尺寸
		if ( wheel > 0 )
		{
			if ( this->terrain_brush_size_tb->Value < this->terrain_brush_size_tb->Maximum )
				this->terrain_brush_size_tb->Value = this->terrain_brush_size_tb->Value + 1;
		}
		else if ( wheel < 0 )
		{
			if ( this->terrain_brush_size_tb->Value > this->terrain_brush_size_tb->Minimum )
				this->terrain_brush_size_tb->Value = this->terrain_brush_size_tb->Value - 1;
		}

		Flt brush_size = (terrain_brush_size_tb->Value + 1) * 0.5f;
		this->terrain_brush_size_text->Text = TypeConverter::DoubleToStr( brush_size );
		editorSys->getBrushSystem()->setSize( brush_size );
	}
	//-----------------------------------------------------------------------
	void MainForm::onEventBrushSoftenChanged(Int wheel)
	{
		IEditorSystem* editorSys    = CoreManager::getInstance().getEngineMain()->editorSystem();
		if ( !editorSys )
			return;

		if ( prop_tab_ctrl->SelectedTab != terrain_page ||
			terrain_style_tab->SelectedTab != terrain_style_gun_page  )
			return;

		//同步当前的画笔衰减
		//同步当前的画笔尺寸
		if ( wheel > 0 )
		{
			if ( this->terrain_stytle_gun_decay_tb->Value < this->terrain_stytle_gun_decay_tb->Maximum )
				this->terrain_stytle_gun_decay_tb->Value = this->terrain_stytle_gun_decay_tb->Value + 1;
		}
		else if ( wheel < 0 )
		{
			if ( this->terrain_stytle_gun_decay_tb->Value > this->terrain_stytle_gun_decay_tb->Minimum )
				this->terrain_stytle_gun_decay_tb->Value = this->terrain_stytle_gun_decay_tb->Value - 1;
		}

		IBrushAirStyle* brushStyle = editorSys->getBrushSystem()->getBrushAirStyle();

		Double attenuation = terrain_stytle_gun_decay_tb->Value + 1;
		terrain_stytle_gun_decay_text->Text = TypeConverter::DoubleToStr( attenuation );
		(dynamic_cast<IBrushAirStyle*>(brushStyle))->setAttenuation( (Flt)attenuation );
	}
	//-----------------------------------------------------------------------
	void MainForm::onEventBrushAmplitudeChanged(Int wheel)
	{
		IEditorSystem* editorSys    = CoreManager::getInstance().getEngineMain()->editorSystem();
		if ( !editorSys )
			return;

		if ( prop_tab_ctrl->SelectedTab != terrain_page )
			return;

		System::Windows::Forms::TrackBar^ operationTab = nullptr;

		if ( terrainTab->SelectedTab == terrain_vertex_page )
		{
			if ( terrainHeightTab->SelectedTab == terrain_height_level_page )
				operationTab = terrain_height_level_range_tb;				
			else if ( terrainHeightTab->SelectedTab == terrain_height_noise_page )
				operationTab = terrain_height_noise_range_tb;
			else if ( terrainHeightTab->SelectedTab == terrain_height_flat_page )
				operationTab = terrain_height_smooth_range_tb;
		}
		else if ( terrainTab->SelectedTab == terrain_texture_page )
		{
			if ( terrainTextureTab->SelectedTab == terrain_tex_add_page )
				operationTab = terrain_tex_add_tb;
			else if ( terrainTextureTab->SelectedTab == terrain_tex_remove_page )
				operationTab = terrain_tex_remove_tb;
			else if ( terrainTextureTab->SelectedTab == terrain_tex_mop_page )
				operationTab = terrain_tex_mop_tb;
			else if ( terrainTextureTab->SelectedTab == terrain_tex_blur_page )
				operationTab = terrain_tex_blur_tb;
		}

		if ( operationTab == nullptr )
			return;

		if ( wheel > 0 )
		{
			if ( operationTab->Value < operationTab->Maximum )
				operationTab->Value = operationTab->Value + 1;
		}
		else if ( wheel < 0 )
		{
			if ( operationTab->Value > operationTab->Minimum )
				operationTab->Value = operationTab->Value - 1;
		}

		//###########################################################
		//地图高度参数
		Double amplitude = (terrain_height_level_range_tb->Value + 1) * 1.0f;
		terrain_height_level_range_text->Text = TypeConverter::DoubleToStr( amplitude );
		editorSys->getTerrainRaiseHeightOperationManager()->setAmplitude( (Flt)amplitude );
		editorSys->getTerrainLowerHeightOperationManager()->setAmplitude( (Flt)amplitude );

		amplitude = (terrain_height_noise_range_tb->Value + 1) * 1.0f;
		terrain_height_noise_range_text->Text = TypeConverter::DoubleToStr( amplitude );
		editorSys->getTerrainNoiseHeightOperationManager()->setAmplitude( (Flt)amplitude );

		amplitude = (terrain_height_smooth_range_tb->Value + 1) * 0.01f;
		terrain_height_smooth_range_text->Text = TypeConverter::DoubleToStr( amplitude );
		editorSys->getTerrainSmoothHeightOperationManager()->setAmplitude( (Flt)amplitude );

		//###########################################################
		//地图贴图参数
		amplitude = terrain_tex_add_tb->Value * 0.00390625f;
		terrain_tex_add_text->Text = TypeConverter::IntToStr( terrain_tex_add_tb->Value );
		editorSys->getTerrainAddTextureOperationManager()->setAmplitude( (Flt)amplitude );
		//editorSys->getTerrainAddTextureOperationManager()->setAmplitude( amplitude );

		amplitude = terrain_tex_remove_tb->Value * 0.00390625f;
		terrain_tex_remove_text->Text = TypeConverter::IntToStr( terrain_tex_remove_tb->Value );
		editorSys->getTerrainRemoveTextureOperationManager()->setAmplitude( (Flt)amplitude );
		//###########################################################
	}


    //-----------------------------------------------------------------------
    void MainForm::loadWaterTemplateList()
    {
		mSelectWaterTemplateID = 0;
        //TODO:
		////////////////////////////////////////////////////////////
		water_mat_template_list->Items->Clear();
		sel_water_txt->Text = nullptr;
		////////////////////////////////////////////////////////////

		IResourceManager* resourceMgr = CoreManager::getInstance().getEngineMain()->resourceMgr();

		if ( resourceMgr )
		{
			UInt count = resourceMgr->getNumWaterEffectResourceDeclaration();

			for ( UInt i=0; i<count; i++ )
			{
				WaterEffectResourceDeclaration* decl = resourceMgr->getWaterEffectResourceDeclarationByIndex(i);

				if ( decl )
				{
					String ^ name   = TypeConverter::Char8ToStr(decl->waterEffectDesc.c_str());
					String ^ id		= TypeConverter::U32ToStr(decl->waterEffectID);

					ListViewItem ^ item = gcnew ListViewItem;

					item->SubItems->default[0]->Text            = id;
					item->SubItems->default[0]->Name            = "columnHeader_water_template_list_index";

					ListViewItem::ListViewSubItem ^subItem = item->SubItems->Add(name);
					subItem->Text = name;
					subItem->Name = "columnHeader_water_template_list_name";

					water_mat_template_list->Items->Add(item);
				}
			}
		}

    }

	//-----------------------------------------------------------------------
	void MainForm::selectWaterTemplate()
	{
		if ( water_mat_template_list->SelectedItems->Count <= 0 )
			return;

		sel_water_txt->Text = nullptr;

		ListViewItem^ item = water_mat_template_list->SelectedItems[0];
		if ( item != nullptr )
		{
			String ^ strID = item->SubItems["columnHeader_water_template_list_index"]->Text;
			String ^ strName = item->SubItems["columnHeader_water_template_list_name"]->Text;

			sel_water_txt->Text = strName;
			U32 effectID = TypeConverter::StrToInt(strID);

			mSelectWaterTemplateID = effectID;
		}
	}

    //-----------------------------------------------------------------------
    void MainForm::loadWaterGroupList()
    {
        mActiveWaterGroupID = 0;

		ITerrainSurfaceManager* surfaceMgr    = CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainSurfaceManager();

		
        //surfaceMgr->getGlobleWaterGroupMaxCount();
        //surfaceMgr->getGlobleWaterGroupByIndex();

		////////////////////////////////////////////////////////////
		water_group_list->Items->Clear();
		//sel_water_txt->Text = nullptr;
		////////////////////////////////////////////////////////////

		if ( surfaceMgr )
		{
			UInt count = surfaceMgr->getGlobleWaterGroupMaxCount();

			for ( UInt i=0; i<count; i++ )
			{
				TerrainWaterGroupDeclaration* decl = surfaceMgr->getGlobleWaterGroupByIndex(i);

				if ( decl )
				{
					String ^ id   = TypeConverter::U32ToStr(decl->groupID);
					String ^ matID	= TypeConverter::U32ToStr(decl->wMatID);

					ListViewItem ^ item = gcnew ListViewItem;

					item->SubItems->default[0]->Text            = id;
					item->SubItems->default[0]->Name            = "columnHeader_water_list_index";

					ListViewItem::ListViewSubItem ^subItem = item->SubItems->Add(matID);
					subItem->Text = matID;
					subItem->Name = "columnHeader_water_list_mat_id";

					water_group_list->Items->Add(item);
				}
			}
		}
    }

    //-----------------------------------------------------------------------
    void MainForm::addWaterGroup()
	{
		U32 wMatID = mSelectWaterTemplateID;

		/*ListViewItem^ item = water_mat_template_list->SelectedItems[0];
		if ( item != nullptr )
		{
			String ^ strID = item->SubItems["columnHeader_water_template_list_index"]->Text;
			wMatID = TypeConverter::StrToInt(strID);
		}*/
        // TODO： 需要从模板列表中得到
        ///////////////////////////////////////////////////////////

        ITerrainSurfaceManager* surfaceMgr    = CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainSurfaceManager();

        UInt count = surfaceMgr->getGlobleWaterGroupMaxCount();
        TerrainWaterGroupDeclaration* decl = surfaceMgr->addGlobleWaterGroup( count );

		if ( decl )
		{
			decl->wMatID = wMatID;
			loadWaterGroupList();
		}
        ///////////////////////////////////////////////////////////
        
    }

    //-----------------------------------------------------------------------
    void MainForm::selectWaterGroup()
    {
        mActiveWaterGroupID = 0;
		sel_water_txt->Text = nullptr;

		if ( water_group_list->SelectedItems->Count <= 0 )
			return;

		ListViewItem^ item = water_group_list->SelectedItems[0];
		if ( item != nullptr )
		{
			String ^ strID = item->SubItems["columnHeader_water_list_index"]->Text;
			String ^ strMatID = item->SubItems["columnHeader_water_list_mat_id"]->Text;

			mActiveWaterGroupID = TypeConverter::StrToInt(strID);
		}
		
        // TODO:
		// 设置watergroup
		 IEditorSystem* editorSys = CoreManager::getInstance().getEngineMain()->editorSystem();
		 if ( editorSys )
		 {
			 ITerrainWaterShowOperationManager* waterMgr = editorSys->getTerrainWaterShowOperationManager();
			 if ( waterMgr )
				 waterMgr->setWaterGroupID(mActiveWaterGroupID);
		 }

        // 从材质实例表中得到
		 ITerrainSurfaceManager* surfaceMgr = CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainSurfaceManager();
		 TerrainWaterGroupDeclaration* decl = NULL;
		 if ( surfaceMgr )
		 {
			 decl = surfaceMgr->getGlobleWaterGroup( mActiveWaterGroupID );
		 }

		 //在界面上显示相关属性
		 if ( decl )
		 {
			 water_dirX_txt->Text = TypeConverter::DoubleToStr(decl->reflectDirection.x);
			 water_dirY_txt->Text = TypeConverter::DoubleToStr(decl->reflectDirection.y);
			 water_dirZ_txt->Text = TypeConverter::DoubleToStr(decl->reflectDirection.z);

			 water_posX_txt->Text = TypeConverter::DoubleToStr(decl->reflectPostion.x);
			 water_posY_txt->Text = TypeConverter::DoubleToStr(decl->reflectPostion.y);
			 water_posZ_txt->Text = TypeConverter::DoubleToStr(decl->reflectPostion.z);

			 String^ group_text = TypeConverter::U32ToStr(decl->groupID);
			 group_text += "号材质";

			 sel_water_txt->Text = group_text;
		 }
    }

    //-----------------------------------------------------------------------
    void MainForm::applyWaterGroup()
    {
        ITerrainSurfaceManager* surfaceMgr    = CoreManager::getInstance().getScene()->getTerrainManager()->getTerrainSurfaceManager();

        TerrainWaterGroupDeclaration* decl = surfaceMgr->getGlobleWaterGroup( mActiveWaterGroupID );

        //TODO:
        if ( decl )
        {
            //TODO:
            //decl->reflectDirection = ?;
            //decl->reflectPosition = ?;
			decl->reflectDirection.x = TypeConverter::StrToDouble(water_dirX_txt->Text);
			decl->reflectDirection.y = TypeConverter::StrToDouble(water_dirY_txt->Text);
			decl->reflectDirection.z = TypeConverter::StrToDouble(water_dirZ_txt->Text);

			decl->reflectPostion.x = TypeConverter::StrToDouble(water_posX_txt->Text);
			decl->reflectPostion.y = TypeConverter::StrToDouble(water_posY_txt->Text);
			decl->reflectPostion.z = TypeConverter::StrToDouble(water_posZ_txt->Text);
        }
    }

	//-----------------------------------------------------------------------
	void MainForm::undo()
	{
		OperationManager::getInstance().undoOp();
	}

	void MainForm::redo()
	{
		OperationManager::getInstance().redoOp();
	}

	//-----------------------------------------------------------------------------------------------------------------
	//功能：裁剪场景
	void MainForm::clipScene()
	{
		////获取保存新场景的路径
		//folderBrowserDialog1->SelectedPath = System::Windows::Forms::Application::StartupPath;
		//if ( folderBrowserDialog1->ShowDialog() != System::Windows::Forms::DialogResult::OK )
		//	return;
		//StrToChar8 pathStr( folderBrowserDialog1->SelectedPath );
		StrToChar8 pathStr( mLastFocusDir );

		//查找场景Entity列表，找出裁剪定位Entity(四个标尺物件(ID为：200001))
		IScene* scene = CoreManager::getInstance().getScene();

		std::vector<Vec3> flagPositions;

		scene->getSceneObjectController()->setFocus(NULL);
		std::vector<MG::ISceneObjectXmlFormat*> formatList;
		scene->getXmlSerializer()->getSceneObjectXmlFormatList(MG::SOT_ENTITY,formatList);

		size_t flagCount = formatList.size();
		for (size_t i=0; i<flagCount; ++i)
		{
			MG::IEntity* entity = static_cast<MG::IEntity*>(formatList[i]->getSceneObject());
			int modelID = entity->getModelObject()->getModelDeclarationID();
			if (modelID == 200001)
			{
				Vec3 pos;
				entity->getSceneNode()->getPosition(pos);
				flagPositions.push_back(pos);
				scene->getXmlSerializer()->removeSceneObjectFormat(formatList[i],true);
			}
		}


		//没找到裁剪定位Entity则返回
		//if (topEnity == NULL || bottomEntity == NULL)
		if (flagPositions.size() < 4)
		{
			System::Windows::Forms::MessageBox::Show("请在地图上放置四个标尺物件，标尺物件包围的区域为裁剪区域!");
			return;
		}

		//裁剪完成前禁用裁剪按钮
		button_ClipMap->Enabled = false;

		//找到裁剪定位Entity则计算出裁剪区域
		MG::Vec3 topPos,bottomPos;
		topPos.x = min(flagPositions[0].x, min(flagPositions[1].x, min(flagPositions[2].x, flagPositions[3].x)));
		topPos.z = min(flagPositions[0].z, min(flagPositions[1].z, min(flagPositions[2].z, flagPositions[3].z)));
		bottomPos.x = max(flagPositions[0].x, max(flagPositions[1].x, max(flagPositions[2].x, flagPositions[3].x)));
		bottomPos.z = max(flagPositions[0].z, max(flagPositions[1].z, max(flagPositions[2].z, flagPositions[3].z)));

		MG::Dlb clipWidth,clipHeight;
		clipWidth = fabs(topPos.x - bottomPos.x); //取求出两个定位点之间的宽度
		clipHeight = fabs(topPos.z - bottomPos.z); //取求出两个定位点之间的高度
		MG::Dlb clipSize = max(clipWidth,clipHeight); //取两者中最大者作为新地图边长(新地图必须是方形的)
		MG::U32 newMapSize = MG::U32(ceil(clipSize)) + MG::U32(ceil(clipSize))%2; //保证新地图边长为偶数
		//保证裁剪大小为128的倍数
		div_t clipDiv = div(newMapSize,128); 
		MG::U32 realMapSize = (clipDiv.quot + clipDiv.rem/64)*128;
		MG::Dbl delta = int(realMapSize - newMapSize)*0.5;
		//计算出裁剪区域(正方形)
		MG::RectF clipRect;
		clipRect.left = topPos.x + delta;
		clipRect.top = topPos.z + delta;
		clipRect.right = clipRect.left + realMapSize;
		clipRect.bottom = clipRect.top + realMapSize;

		//裁剪场景
		//--------------------------------------------------------------------
		//裁剪方法：根据裁剪区域并合并chunk贴图到一个大的贴图，
		//然后根据裁剪大小从大贴图中裁剪出需要的数据放置到一个新的贴图.
		//最后根据新地图chunk数量将新贴图切割成几部分重新存到文件
		scene->getXmlSerializer()->clipContent(pathStr.getChar8(), clipRect);

		//return;

		//卸载当前场景
		clearAll();


		//加载裁剪过的场景
		scene->getXmlSerializer()->loadContent(pathStr.getChar8());

		if ( FormSet::main_form->isEditorMode() )
		{
			loadSceneEntityList();
			loadScenePlantList();
			loadSceneEffectList();
		}

		////////////////////////////////////////////////////

		loadTerrainTextureList();
		updateTerrainEditorParameter();

		////////////////////////////////////////////////////

		loadCustomRegionList();

		////////////////////////////////////////////////////

		loadWaterGroupList();

		////////////////////////////////////////////////////

		switchGameEditorOp();

		////////////////////////////////////////////////////

		loadSceneEnvironmentLight();
		loadSceneGameConfig();
		loadFogSetting();
		loadShadowSetting();
		loadPlantSetting();

		////////////////////////////////////////////////////

		CoreManager::getInstance().initScene();
		updateDebugInfo();

		////////////////////////////////////////////////////

		applyCompositorSetting();

		////////////////////////////////////////////////////

		// 解锁treemanager

		CoreManager::getInstance().getEngineMain()->unLockTreeManager();

		System::Windows::Forms::MessageBox::Show("成功裁剪地图！");

		//裁剪完成后启用裁剪按钮
		button_ClipMap->Enabled = true;
	}

	//-----------------------------------------------------------------------------------------------------------------
	void MainForm::reorderTerrainTextureLayer()
	{
		button21->Enabled = false;
		StrToChar8 pathStr( mLastFocusDir );

		MG::Str path = pathStr.getChar8();

		ITerrainManager* pTerrainMgr = CoreManager::getInstance().getScene()->getTerrainManager();
		pTerrainMgr->_reorderTextureLayer(path);

		System::Windows::Forms::MessageBox::Show("成功重排序贴图，请重新加载地图，或直接裁剪地图！");

		button21->Enabled = true;
	}
}

