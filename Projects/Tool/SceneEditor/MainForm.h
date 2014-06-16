#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "XmlPropertySet.h"
#include "CreateForm.h"

namespace SceneEditor {

    enum FormOpState
    {
        MOS_NULL,
        MOS_LOAD_SCENE,

    };


	/// <summary>
	/// Summary for MainForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            mXmlPropSet  = gcnew XmlPropertySet();
            mCurrSceneObjectXmlFormat = NULL;
			mIsSceneLoaded = false;
		}

        //######################################################################################################
        // 【主方法】
        //######################################################################################################

        ///初始化
        void    initialize();
        ///设置场景窗体位置
        void    setSceneFormLocation();
        ///清空所有
        void    clearAll();
        ///还原所有
        void    revert();
        ///更新
        void    update();

        ///更新调试信息
        void    updateDebugInfo();


        //######################################################################################################
        // 【事件】
        //######################################################################################################

        // 同步ShortCuts事件, shift加上鼠标位移, 放大缩小当前笔刷尺寸
        void	onEventBrushSizeChanged(Int wheel);
        // 同步ShortCut事件， shift+ctrl+鼠标位移, 控制当前笔刷的衰减指数
        void	onEventBrushSoftenChanged(Int wheel);
        // 同步ShortCut事件， alt+ctrl+鼠标位移, 控制当前操作的幅度
        void	onEventBrushAmplitudeChanged(Int wheel);
        // 同步ShortCut事件， Tab切换
        void	onEventSelectTab(Int index);
        // 同步ShortCut事件， camera速度切换
        void	onEventCamspeedChanged(UInt level);
		// 同步按键时间， 当按下批次组定义键
		void	onEventPressDefineBatchButton();
		// 按键时间， 当按下高度定义键位
		void	onEventPressDefineWaterHeightButton();
		// 同步ShortCut事件， ctrl+Z撤销操作
		void	undo();
		// 同步ShortCut事件， ctrl+Y撤销操作
		void	redo();


        //######################################################################################################
        // 工具栏
        //######################################################################################################

        /*@
            【游戏编辑】
            【界面上方工具栏】 
			【同步在ShortCuts事件】
        @*/

        // 打开游戏数据编辑界面
        void    openGameDataEditor();
        // 打开地形贴图编辑界面
        void    openTerrainTextureEditor();
		// 打开水效果编辑界面
		void	openWaterEffectEditor();
		// 打开新建场景界面
		void openNewSceneEditor();
		// 关闭新建场景界面
		void closeNewSceneEditor();
		// 显示场景信息
		void showSceneInfo();
		//关闭场景信息界面
		void closeSceneInfo();

        /*@
            【场景文件操作】
            【界面上方工具栏】 
        @*/

        ///新建场景
        DELEGATEFUNC(createScene)();
        void    createScene();
        ///打开场景
        DELEGATEFUNC(loadScene)();
        void    loadScene();
        ///保存场景
        DELEGATEFUNC(saveScene)();
        void    saveScene();
        ///另保存为场景
        DELEGATEFUNC(saveAsScene)();
        void    saveAsScene();
		///裁剪场景
		DELEGATEFUNC(clipScene)();
		void    clipScene();
		///重排序地形贴图图层
		DELEGATEFUNC(reorderTerrainTextureLayer)();
		void    reorderTerrainTextureLayer();

        /*@
            【设置】
            【界面上方工具栏】 
        @*/

        // 响应游戏设置
        void    applyBaseSceneSetting();
        Bool    isEditorMode();


        /*@
            【场景文件操作】
            【界面上方工具栏】 
        @*/

        ///选择控制方式
        void    selectCtrlType();
        ///更新摄象机提示
        void    updateCameraHint();
		///更新鼠标提示
		void    updateMouseHint();

        /*@
            【界面右方编辑栏】
            【界面上方工具栏】 
        @*/

        //切换游戏编辑操作，当界面Tab发生变化时
        void    switchGameEditorOp();


        //######################################################################################################
        // 实体元素操作
        //######################################################################################################

        /*@
            【模型定义列表】 
        @*/

        ///加载模型定义列表
        void    loadModelDeclarationList();
        void    loadModelDeclarationList2();

        ///准备创建实体
        void    prepareCreateEntity();
        ///随机准备创建实体
        void    randonprepareCreateEntity();

        // 是否测试创建批量实体
        Bool    isTestCreateBatchEntity();
        // 测试创建批量实体数量
        UInt    getTestBatchEntityNum();


        /*@
            【植被定义列表】 
        @*/
        ///加载Tree定义列表
        void    loadTreeDeclarationList();

        ///准备创建Tree
        void    prepareCreateTree();

		/*@
			【特效定义列表】 
		@*/
		///加载Effect定义列表
		void	loadEffectDeclarationList();
		
		///准备创建Effect
		void	prepareCreateEffect();

        /*@
            【场景选中元素操作】 
        @*/

        ///选中元素位置贴地
        void    stickSelectElementToTerrain();

        /*@
            【场景元素属性列表】 
        @*/

        ///加载元素属性
        void    loadSceneElementProps(ISceneObjectXmlFormat* format, Bool isChandedTab);
        ///清空元素属性
        void    clearSceneElementProps();
        ///相应属性元素改变
        void    applySceneElementPropsChange();

        ///查询元素改变
        void    checkSceneElementProps();

        /*@
            【场景元素列表】 
        @*/

        ///加载场景实体物件列表
        void    loadSceneEntityList();
        ///清空场景实体物件列表
        void    clearSceneEntityList();
        ///选择场景实体物件列表
        void    selectSceneEntityFromList();
        ///删除场景实体物件列表
        void    destroySceneEntityFromList();

		///加载场景特效列表
		void    loadSceneEffectList();
		///清空场景特效列表
		void    clearSceneEffectList();
		///选择场景特效列表
		void    selectSceneEffectFromList();
		///删除场景特效列表
		void    destroySceneEffectFromList();

		///加载场景植被列表
		void    loadScenePlantList();
		///清空场景植被列表
		void    clearScenePlantList();
		///选择场景植被列表
		void    selectScenePlantFromList();
		///删除场景植被列表
		void    destroyScenePlantFromList();

		///加载策划场景
		void loadSubScene();
		///卸载策划场景
		void unloadSubScene();
		///显示或隐藏策划场景
		void showSubScene(bool show);

        //######################################################################################################
        // 地表操作
        //######################################################################################################
        
        /*@
            【地形相关】 
        @*/

        ///更新地形编辑参数
        void    updateTerrainEditorParameter();
        ///加载地形贴图
        void    loadTerrainTextureList();

        // 刷新地形贴图显示
        void    refreshTerrainTextureImage();

        // 得到当前活动的临时地形贴图列表索引
        Int     getCurrActiveTempTerrainTextureIndex();

        // 设置活动的地形贴图
        void    setActiveTerrainTexture( Int index );

        //######################################################################################################
        // 植被操作
        //######################################################################################################

        /*@
            【植被设置】
        @*/

		/// 加载批次树列表
		void    loadBatchTreeList();
		///从批次树列表中选择树
		void	selectBatchTreeFromList();
		/// 加载批次草列表
		void    loadBatchGrassList();
		///从批次草列表中选择草
		void	selectBatchGrassFromList();
        
        //######################################################################################################
        // 区域操作
        //######################################################################################################

        /*@
            【障碍设置】
        @*/
       
        /// 刷性地形区域可见度
        void    refreshRegionVisible();

        /// 显示障碍区域
        void    showBlockRegion();
        /*@
            【自定义区域设置】
        @*/

        /// 加载自定义区域列表
        void    loadCustomRegionList();

        /// 增加自定义区域列表
        void    addCustomRegion();

        /// 显示自定义区域
        void    showCustomRegion();


        //######################################################################################################
        // 水操作
        //######################################################################################################
        
        /// 加载水模板列表
        void    loadWaterTemplateList();
		/// 选择水模板列表
		void	selectWaterTemplate();

        /// 加载水材质组列表
        void    loadWaterGroupList();
        /// 增加水材质组
        void    addWaterGroup();
        /// 增加水材质组
        void    selectWaterGroup();
        /// 响应水材质组
        void    applyWaterGroup();

        U32             mActiveWaterGroupID; 
        FormOpState     mFormOpState;
private: System::Windows::Forms::Button^  button21;
private: System::Windows::Forms::ToolStripMenuItem^  Menu_Setting_EnableClipScene;
public: 
	U32		        mSelectWaterTemplateID;

        //######################################################################################################
        // 效果操作
        //######################################################################################################

		///更新场景设置参数
		void    updateSceneEditorParameter();

        /*@
            【灯光配置】
        @*/

        ///加载场景环境灯光
        void    loadSceneEnvironmentLight();
        ///培植场景环境灯光
        void    configSceneEnvironmentLight();
        ///培植场景灯光方向
        void    configSceneLightDirection();


		////////////////////////////////////////////////////////

		/*@
		【合成器设置】
		@*/
		// 响应设置
		void    applyCompositorSetting();

		////////////////////////////////////////////////////////

		/*@
		【雾效设置】
		@*/
		// 响应游戏设置
		void    applyFogSetting();
		// 加载游戏设置
		void    loadFogSetting();

		////////////////////////////////////////////////////////

		/*@
		【阴影设置】
		@*/
		///加载阴影基础参数
		void    loadShadowSetting();
		// 响应游戏设置
		void    applyShadowSetting();
		///生成光照贴图
		void    genarateLightingMap();

		////////////////////////////////////////////////////////

		/*@
		【植被系统设置】
		@*/
		///加载植被系统参数
		void    loadPlantSetting();
		// 
		void    applyPlantSetting();

		////////////////////////////////////////////////////////

        //######################################################################################################
        // 游戏操作
        //######################################################################################################

        /*@
            【游戏设置】
        @*/

        // 更新游戏设置
        void    updateGameSetting();
        // 响应游戏设置
        void    applyGameSetting();

        ////////////////////////////////////////////////////////

        /*@
            【摄像机配置】
        @*/

        ///加载游戏基础参数
        void    loadSceneGameConfig();
        void    configSceneGameConfig();

        ////////////////////////////////////////////////////////

        /*@
            【MiniMap设置】
        @*/
        // 生成Mini贴图
        void    genarateMiniMap();

	public: 

		///Xml属性集
        XmlPropertySet^ mXmlPropSet;
        ///上次关注的场景文件目录
        String^ mLastFocusDir;
        ///现在的场景对象XmlFormat对象
        ISceneObjectXmlFormat* mCurrSceneObjectXmlFormat;

	    /// 现在选择的创建角色节点
        TreeNode ^ mCurrSelectCreateModelTreeNode;
        /// 现在选择的创建角色节点
        TreeNode ^ mCurrSelectCreateTreeTreeNode;
		/// 现在选择的Effect节点
		TreeNode ^ mCurrSelectCreateEffectTreeNode;
		/// 是否加载了场景
		Bool mIsSceneLoaded;
		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			//
			if (components)
			{
				delete components;
			}
		}

protected: 
	
		/// <summary>
		/// Required designer variable.
		/// </summary>
        private: System::Windows::Forms::GroupBox^  groupBox39;
        private: System::Windows::Forms::CheckBox^  water_reflect_check;
        private: System::Windows::Forms::CheckBox^  water_refract_check;
        private: System::Windows::Forms::CheckBox^  water_shadow_check;
        private: System::Windows::Forms::CheckBox^  water_alpha_check;
        private: System::Windows::Forms::GroupBox^  groupBox38;
        private: System::Windows::Forms::Label^  label50;
        private: System::Windows::Forms::TextBox^  textBox_grassLod_end;
        private: System::Windows::Forms::Label^  label_grassLod_start;
        private: System::Windows::Forms::TextBox^  textBox_grassLod_start;
        private: System::Windows::Forms::Button^  button_ClipMap;
        private: System::Windows::Forms::ToolStripMenuItem^  Menu_Setting_ShowSubScene;
        private: System::Windows::Forms::ToolStripMenuItem^  Menu_Setting_SelectSubscene;
        private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusCamSpeed;
        private: System::Windows::Forms::Label^  mousePosZ;
        private: System::Windows::Forms::Label^  label80;
        private: System::Windows::Forms::Label^  mousePosY;
        private: System::Windows::Forms::Label^  label82;
        private: System::Windows::Forms::Label^  mousePosX;
        private: System::Windows::Forms::Label^  label84;
        private: System::Windows::Forms::Label^  label85;
        private: System::Windows::Forms::ToolStripMenuItem^  地图信息ToolStripMenuItem;
        private: System::Windows::Forms::GroupBox^  groupBox4;
        private: System::Windows::Forms::Label^  label11;
        private: System::Windows::Forms::Label^  label8;
        private: System::Windows::Forms::Label^  label1;
        private: System::Windows::Forms::TabPage^  plant_tree_page;
        private: System::Windows::Forms::ListView^  listView_terrain_batch_tree_list;
        private: System::Windows::Forms::ColumnHeader^  columnHeader1;
        private: System::Windows::Forms::ColumnHeader^  columnHeader2;
        private: System::Windows::Forms::ColumnHeader^  columnHeader3;
        private: System::Windows::Forms::TabPage^  plant_grass_page;
        private: System::Windows::Forms::ListView^  listView_terrain_batch_grass_list;
        private: System::Windows::Forms::ColumnHeader^  columnHeader4;
        private: System::Windows::Forms::ColumnHeader^  columnHeader5;
        private: System::Windows::Forms::ColumnHeader^  columnHeader6;
        private: System::Windows::Forms::Label^  label30;
        private: System::Windows::Forms::TextBox^  TextBox_Ambient_B;
        private: System::Windows::Forms::Label^  label83;
        private: System::Windows::Forms::TextBox^  TextBox_Ambient_G;
        private: System::Windows::Forms::Label^  label81;
        private: System::Windows::Forms::TextBox^  TextBox_Ambient_R;
        private: System::Windows::Forms::TextBox^  TextBox_Specular_B;
        private: System::Windows::Forms::Label^  label89;
        private: System::Windows::Forms::TextBox^  TextBox_Specular_G;
        private: System::Windows::Forms::Label^  label90;
        private: System::Windows::Forms::TextBox^  TextBox_Specular_R;
        private: System::Windows::Forms::Label^  label91;
        private: System::Windows::Forms::TextBox^  TextBox_Diffuse_B;
        private: System::Windows::Forms::Label^  label86;
        private: System::Windows::Forms::TextBox^  TextBox_Diffuse_G;
        private: System::Windows::Forms::Label^  label87;
        private: System::Windows::Forms::TextBox^  TextBox_Diffuse_R;
        private: System::Windows::Forms::Label^  label88;
        private: System::Windows::Forms::GroupBox^  groupBox5;
        private: System::Windows::Forms::TextBox^  TextBox_STSpecular_B;
        private: System::Windows::Forms::Label^  label24;
        private: System::Windows::Forms::TextBox^  TextBox_STSpecular_G;
        private: System::Windows::Forms::Label^  label25;
        private: System::Windows::Forms::TextBox^  TextBox_STSpecular_R;
        private: System::Windows::Forms::Label^  label26;
        private: System::Windows::Forms::TextBox^  TextBox_STDiffuse_B;
        private: System::Windows::Forms::Label^  label27;
        private: System::Windows::Forms::TextBox^  TextBox_STDiffuse_G;
        private: System::Windows::Forms::Label^  label28;
        private: System::Windows::Forms::TextBox^  TextBox_STDiffuse_R;
        private: System::Windows::Forms::Label^  label29;
        private: System::Windows::Forms::TextBox^  TextBox_STAmbient_B;
        private: System::Windows::Forms::Label^  label92;
        private: System::Windows::Forms::TextBox^  TextBox_STAmbient_G;
        private: System::Windows::Forms::Label^  label93;
        private: System::Windows::Forms::TextBox^  TextBox_STAmbient_R;
        private: System::Windows::Forms::Label^  label94;
        private: System::Windows::Forms::Label^  label95;
        private: System::Windows::Forms::Label^  label96;
        private: System::Windows::Forms::Label^  label97;
        private: System::Windows::Forms::GroupBox^  groupBox36;
        private: System::Windows::Forms::TextBox^  TextBox_SGSpecular_B;
        private: System::Windows::Forms::Label^  label98;
        private: System::Windows::Forms::TextBox^  TextBox_SGSpecular_G;
        private: System::Windows::Forms::Label^  label99;
        private: System::Windows::Forms::TextBox^  TextBox_SGSpecular_R;
        private: System::Windows::Forms::Label^  label100;
        private: System::Windows::Forms::TextBox^  TextBox_SGDiffuse_B;
        private: System::Windows::Forms::Label^  label101;
        private: System::Windows::Forms::TextBox^  TextBox_SGDiffuse_G;
        private: System::Windows::Forms::Label^  label102;
        private: System::Windows::Forms::TextBox^  TextBox_SGDiffuse_R;
        private: System::Windows::Forms::Label^  label103;
        private: System::Windows::Forms::TextBox^  TextBox_SGAmbient_B;
        private: System::Windows::Forms::Label^  label104;
        private: System::Windows::Forms::TextBox^  TextBox_SGAmbient_G;
        private: System::Windows::Forms::Label^  label105;
        private: System::Windows::Forms::TextBox^  TextBox_SGAmbient_R;
        private: System::Windows::Forms::Label^  label106;
        private: System::Windows::Forms::Label^  label107;
        private: System::Windows::Forms::Label^  label108;
        private: System::Windows::Forms::Label^  label109;
        private: System::Windows::Forms::Label^  label110;
        private: System::Windows::Forms::Label^  label112;
        private: System::Windows::Forms::Label^  label111;
        private: System::Windows::Forms::TextBox^  TextBox_Plant_MaxScale;
        private: System::Windows::Forms::TextBox^  TextBox_Plant_MinScale;
        private: System::Windows::Forms::TextBox^  textBox4;
        private: System::Windows::Forms::TextBox^  textBox5;
        private: System::Windows::Forms::CheckBox^  plant_create_align_checkbox;
        private: System::Windows::Forms::GroupBox^  groupBox37;
        private: System::Windows::Forms::RadioButton^  plant_create_ditribute_colum;
        private: System::Windows::Forms::RadioButton^  plant_create_ditribute_circle;
        private: System::Windows::Forms::CheckBox^  wind_check;
        private: System::Windows::Forms::ToolStripMenuItem^  编辑ToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  Menu_Edit_Undo;
        private: System::Windows::Forms::ToolStripMenuItem^  Menu_Edit_Redo;
        private: System::Windows::Forms::RadioButton^  rb_shadow_lispsm;
        private: System::Windows::Forms::RadioButton^  rb_shadow_plane;
        private: System::Windows::Forms::RadioButton^  rb_shadow_uniform;
        private: System::Windows::Forms::RadioButton^  rb_shadow_uniform_focused;
		private: System::Windows::Forms::TabPage^  create_effect_page;
		private: System::Windows::Forms::TreeView^  effect_create_tree;
		private: System::Windows::Forms::Panel^  panel35;
		private: System::Windows::Forms::Button^  button18;
		private: System::Windows::Forms::TextBox^  textBox2;
		private: System::Windows::Forms::Panel^  panel36;
		private: System::Windows::Forms::Label^  prepare_effect_text;
		private: System::Windows::Forms::Label^  label73;
		private: System::Windows::Forms::Button^  button19;
        private: System::Windows::Forms::Panel^  panel34;
        private: System::Windows::Forms::Label^  prepare_tree_text;
        private: System::Windows::Forms::Label^  label70;
        private: System::Windows::Forms::Button^  button17;
        private: System::Windows::Forms::Panel^  panel28;
        private: System::Windows::Forms::TreeView^  tree_create_tree;
		private: System::Windows::Forms::TabControl^  ConfigTab;
		private: System::Windows::Forms::TabPage^  Config_env_light_page;
		private: System::Windows::Forms::GroupBox^  groupBox27;
		private: System::Windows::Forms::Label^  label65;
		private: System::Windows::Forms::TextBox^  terrainLightingParameterW_txt;
		private: System::Windows::Forms::Label^  label64;
		private: System::Windows::Forms::TextBox^  terrainLightingParameterZ_txt;
		private: System::Windows::Forms::Label^  label63;
		private: System::Windows::Forms::TextBox^  terrainLightingParameterY_txt;
		private: System::Windows::Forms::Label^  label66;
		private: System::Windows::Forms::TextBox^  terrainLightingParameterX_txt;
		private: System::Windows::Forms::GroupBox^  groupBox6;
		private: System::Windows::Forms::Button^  button8;
		private: System::Windows::Forms::Button^  button7;
		private: System::Windows::Forms::TabPage^  config_video_page;
		private: System::Windows::Forms::GroupBox^  groupBox16;
		private: System::Windows::Forms::Label^  label32;
		private: System::Windows::Forms::TextBox^  sbs_normal_txt;
		private: System::Windows::Forms::Label^  label36;
		private: System::Windows::Forms::TextBox^  sbs_specular_txt;
		private: System::Windows::Forms::Label^  label35;
		private: System::Windows::Forms::TextBox^  sbs_bias_txt;
		private: System::Windows::Forms::Label^  label34;
		private: System::Windows::Forms::TextBox^  sbs_scale_txt;
		private: System::Windows::Forms::GroupBox^  groupBox15;
		private: System::Windows::Forms::Label^  label31;
		private: System::Windows::Forms::TextBox^  fsaa_txt;
		private: System::Windows::Forms::GroupBox^  groupBox14;
		private: System::Windows::Forms::CheckBox^  gamma_check;
		private: System::Windows::Forms::GroupBox^  groupBox11;
		private: System::Windows::Forms::Label^  label18;
		private: System::Windows::Forms::TextBox^  txt_mipmap_bias;
		private: System::Windows::Forms::GroupBox^  groupBox10;
		private: System::Windows::Forms::RadioButton^  rb_tex_filter_anisotropic;
		private: System::Windows::Forms::RadioButton^  rb_tex_filter_3line;
		private: System::Windows::Forms::RadioButton^  rb_tex_filter_bline;
		private: System::Windows::Forms::RadioButton^  rb_tex_filter_none;
		private: System::Windows::Forms::Button^  button10;
		private: System::Windows::Forms::GroupBox^  groupBox9;
		private: System::Windows::Forms::CheckBox^  model_sa_tex_check;
		private: System::Windows::Forms::CheckBox^  model_normal_tex_check;
		private: System::Windows::Forms::CheckBox^  model_shadow_dynamic_check;
		private: System::Windows::Forms::CheckBox^  model_shadow_tex_check;
		private: System::Windows::Forms::GroupBox^  groupBox8;
		private: System::Windows::Forms::CheckBox^  terrain_color_check;
		private: System::Windows::Forms::CheckBox^  terrain_offset_check;
		private: System::Windows::Forms::CheckBox^  terrain_spec_check;
		private: System::Windows::Forms::CheckBox^  terrain_normal_check;
		private: System::Windows::Forms::TabPage^  config_plant_page;
		private: System::Windows::Forms::GroupBox^  groupBox33;
		private: System::Windows::Forms::GroupBox^  groupBox34;
		private: System::Windows::Forms::Label^  label67;
		private: System::Windows::Forms::TextBox^  textBoxWindDirZ;
		private: System::Windows::Forms::Label^  label76;
		private: System::Windows::Forms::TextBox^  textBoxWindDirY;
		private: System::Windows::Forms::Label^  label77;
		private: System::Windows::Forms::TextBox^  textBoxWindDirX;
		private: System::Windows::Forms::TrackBar^  TrackBarWindIntensity;
		private: System::Windows::Forms::Label^  label78;
		private: System::Windows::Forms::Label^  label79;
		private: System::Windows::Forms::Button^  button20;
		private: System::Windows::Forms::TabPage^  tabPage1;
		private: System::Windows::Forms::GroupBox^  groupBox32;
		private: System::Windows::Forms::CheckBox^  ckb_water_visible;
		private: System::Windows::Forms::GroupBox^  groupBox31;
		private: System::Windows::Forms::CheckBox^  ckb_entity_visible;
		private: System::Windows::Forms::GroupBox^  groupBox18;
		private: System::Windows::Forms::CheckBox^  ckb_terrain_grids_visible;
		private: System::Windows::Forms::GroupBox^  groupBox17;
		private: System::Windows::Forms::CheckBox^  ckb_wireframe;
		private: System::Windows::Forms::Button^  button9;
		private: System::Windows::Forms::GroupBox^  groupBox7;
		private: System::Windows::Forms::Label^  label21;
		private: System::Windows::Forms::TextBox^  fov_edit;
		private: System::Windows::Forms::TabPage^  tabPage9;
		private: System::Windows::Forms::Button^  button13;
		private: System::Windows::Forms::GroupBox^  groupBox23;
		private: System::Windows::Forms::Label^  label53;
		private: System::Windows::Forms::TextBox^  txt_fog_color_b;
		private: System::Windows::Forms::Label^  label54;
		private: System::Windows::Forms::TextBox^  txt_fog_color_g;
		private: System::Windows::Forms::Label^  label55;
		private: System::Windows::Forms::TextBox^  txt_fog_color_r;
		private: System::Windows::Forms::GroupBox^  groupBox22;
		private: System::Windows::Forms::Label^  label56;
		private: System::Windows::Forms::TextBox^  txt_fog_end;
		private: System::Windows::Forms::Label^  label57;
		private: System::Windows::Forms::TextBox^  txt_fog_start;
		private: System::Windows::Forms::Label^  label58;
		private: System::Windows::Forms::TextBox^  txt_fog_exp;
		private: System::Windows::Forms::GroupBox^  groupBox13;
		private: System::Windows::Forms::RadioButton^  rb_fog_exp;
		private: System::Windows::Forms::RadioButton^  rb_fog_line;
		private: System::Windows::Forms::RadioButton^  rb_fog_none;
		private: System::Windows::Forms::TabPage^  tabPage10;
		private: System::Windows::Forms::GroupBox^  groupBox24;
		private: System::Windows::Forms::Label^  label59;
		private: System::Windows::Forms::TextBox^  shadowParameterZ_txt;
		private: System::Windows::Forms::Label^  label60;
		private: System::Windows::Forms::TextBox^  shadowParameterW_txt;
		private: System::Windows::Forms::Label^  label61;
		private: System::Windows::Forms::TextBox^  shadowParameterY_txt;
		private: System::Windows::Forms::Label^  label62;
		private: System::Windows::Forms::TextBox^  shadowParameterX_txt;
		private: System::Windows::Forms::Button^  button14;
		private: System::Windows::Forms::GroupBox^  groupBox20;
		private: System::Windows::Forms::CheckBox^  terrain_dynamic_shadow_check;
		private: System::Windows::Forms::CheckBox^  terrain_shadow_check;
		private: System::Windows::Forms::GroupBox^  groupBox12;
		private: System::Windows::Forms::RadioButton^  rb_shadow_pssm;
		private: System::Windows::Forms::RadioButton^  rb_shadow_none;
		private: System::Windows::Forms::GroupBox^  groupBox19;
		private: System::Windows::Forms::Label^  label52;
		private: System::Windows::Forms::TextBox^  txt_terrainShadowOffset;
		private: System::Windows::Forms::Button^  button11;
		private: System::Windows::Forms::TabPage^  tabPage11;
		private: System::Windows::Forms::Button^  button15;
		private: System::Windows::Forms::GroupBox^  groupBox28;
		private: System::Windows::Forms::Label^  label68;
		private: System::Windows::Forms::TextBox^  minimap_tex_size_h;
		private: System::Windows::Forms::Label^  label69;
		private: System::Windows::Forms::TextBox^  minimap_tex_size_w;
		private: System::Windows::Forms::GroupBox^  groupBox29;
		private: System::Windows::Forms::Label^  label71;
		private: System::Windows::Forms::TextBox^  minimap_size_h;
		private: System::Windows::Forms::Label^  label72;
		private: System::Windows::Forms::TextBox^  minimap_size_w;
		private: System::Windows::Forms::GroupBox^  groupBox30;
		private: System::Windows::Forms::Label^  label74;
		private: System::Windows::Forms::TextBox^  minimap_center_z;
		private: System::Windows::Forms::Label^  label75;
		private: System::Windows::Forms::TextBox^  minimap_center_x;
		private: System::Windows::Forms::TabPage^  tabPage12;
		private: System::Windows::Forms::CheckBox^  MotionBlur_ckb;
		private: System::Windows::Forms::CheckBox^  HDR_ckb;
		private: System::Windows::Forms::CheckBox^  FakeHDR_ckb;
		private: System::Windows::Forms::Button^  button16;
		private: System::Windows::Forms::CheckBox^  Bloom_ckb;
		private: System::Windows::Forms::GroupBox^  groupBox35;
		private: System::Windows::Forms::Label^  lableWindIntensity;
        private: System::Windows::Forms::Button^  water_height_confirm;
        private: System::Windows::Forms::TextBox^  water_height_text_box;
        private: System::Windows::Forms::Label^  label37;
        private: System::Windows::Forms::TabControl^  water_height_tab;
        private: System::Windows::Forms::TabPage^  water_height_level_page;
        private: System::Windows::Forms::Label^  water_height_label;
        private: System::Windows::Forms::TrackBar^  water_height_level_app;
        private: System::Windows::Forms::Label^  plant_create_GrassDis_label;
		private: System::Windows::Forms::Label^  label38;
        private: System::Windows::Forms::TabPage^  water_height_flat_page;
        private: System::Windows::Forms::Label^  label48;
        private: System::Windows::Forms::TrackBar^  trackBar5;
        private: System::Windows::Forms::Label^  label49;
		private: System::Windows::Forms::TabPage^  water_height_uniform_page;
        private: System::Windows::Forms::TrackBar^  plant_create_clumping_bar;
        private: System::Windows::Forms::Label^  plant_create_scale_offset_label;
        private: System::Windows::Forms::TrackBar^  plant_create_scale_offset_bar;
        private: System::Windows::Forms::Label^  label40;
        private: System::Windows::Forms::Label^  label39;
        private: System::Windows::Forms::Label^  label51;
        private: System::Windows::Forms::RadioButton^  region_batch_radioButton;
        private: System::Windows::Forms::RadioButton^  common_batch_radioButton;
        private: System::Windows::Forms::RadioButton^  specialize_batch_radioButton;
        private: System::Windows::Forms::TextBox^  specialize_batch_textBox;
        private: System::Windows::Forms::Button^  plant_batch_define_button;
        private: System::Windows::Forms::Label^  label19;
        private: System::Windows::Forms::ToolStripMenuItem^  打开水效果编辑器ToolStripMenuItem;
        private: System::Windows::Forms::Label^  plant_create_treeDis_label;
        private: System::Windows::Forms::TrackBar^  plant_create_treeDis_bar;
        private: System::Windows::Forms::TabControl^  plantTab;

        private: System::Windows::Forms::Panel^  panel23;
        private: System::Windows::Forms::TabControl^  waterTab;
        private: System::Windows::Forms::TabPage^  water_group_page;
        private: System::Windows::Forms::TabPage^  water_visible_page;
        private: System::Windows::Forms::Panel^  panel26;
        private: System::Windows::Forms::Panel^  panel30;
        private: System::Windows::Forms::Label^  sel_water_txt;
        private: System::Windows::Forms::Label^  label46;
        private: System::Windows::Forms::Panel^  panel31;
        private: System::Windows::Forms::TabControl^  water_mat_tab;
        private: System::Windows::Forms::TabPage^  water_template_page;
        private: System::Windows::Forms::TabPage^  tabPage15;
        private: System::Windows::Forms::Panel^  panel29;
        private: System::Windows::Forms::ListView^  water_group_list;
        private: System::Windows::Forms::ColumnHeader^  columnHeader_water_list_index;
        private: System::Windows::Forms::ColumnHeader^  columnHeader_water_list_mat_id;
        private: System::Windows::Forms::Panel^  panel32;
        private: System::Windows::Forms::Button^  button12;
        private: System::Windows::Forms::ListView^  water_mat_template_list;
        private: System::Windows::Forms::ColumnHeader^  columnHeader_water_template_list_index;
        private: System::Windows::Forms::ColumnHeader^  columnHeader_water_template_list_name;
        private: System::Windows::Forms::Panel^  panel33;
        private: System::Windows::Forms::Button^  water_group_apply_btn;
        private: System::Windows::Forms::GroupBox^  groupBox25;
        private: System::Windows::Forms::Label^  label41;
        private: System::Windows::Forms::TextBox^  water_dirZ_txt;
        private: System::Windows::Forms::Label^  label42;
        private: System::Windows::Forms::TextBox^  water_dirY_txt;
        private: System::Windows::Forms::Label^  label43;
        private: System::Windows::Forms::TextBox^  water_dirX_txt;
        private: System::Windows::Forms::GroupBox^  groupBox26;
        private: System::Windows::Forms::Label^  label44;
        private: System::Windows::Forms::TextBox^  water_posZ_txt;
        private: System::Windows::Forms::Label^  label45;
        private: System::Windows::Forms::TextBox^  water_posY_txt;
        private: System::Windows::Forms::Label^  label47;
        private: System::Windows::Forms::TextBox^  water_posX_txt;
        private: System::Windows::Forms::TabControl^  water_visible_tab;
        private: System::Windows::Forms::TabPage^  water_op_show_page;
        private: System::Windows::Forms::TabPage^  water_op_hide_page;
        private: System::Windows::Forms::TabPage^  water_height_page;
        private: System::Windows::Forms::Panel^  panel27;




        private: System::Windows::Forms::TabPage^  plant_create_page;
        private: System::Windows::Forms::Panel^  panel17;
        private: System::Windows::Forms::TabPage^  plant_set_page;
        private: System::Windows::Forms::Panel^  panel24;
        private: System::Windows::Forms::TabControl^  plantBatchEntityTab;
        private: System::Windows::Forms::TabPage^  terrain_batch_add_page;
        private: System::Windows::Forms::TabPage^  terrain_batch_remove_page;
        private: System::Windows::Forms::TabPage^  terrain_batch_noise_page;
        private: System::Windows::Forms::Panel^  panel25;
        private: System::Windows::Forms::GroupBox^  groupBox21;
        private: System::Windows::Forms::ToolStripMenuItem^  打开地形贴图编辑器ToolStripMenuItem;
        private: System::Windows::Forms::Button^  btn_show_block_refresh;
        private: System::Windows::Forms::TabPage^  terrain_region_page;
        private: System::Windows::Forms::Panel^  panel19;
        private: System::Windows::Forms::TabControl^  terrainRegionOpTab;
        private: System::Windows::Forms::TabPage^  terrain_region_add_page;
        private: System::Windows::Forms::TabPage^  terrain_region_remove_page;
        private: System::Windows::Forms::Panel^  panel20;
        private: System::Windows::Forms::CheckBox^  terrain_region_visible_ckb;
        private: System::Windows::Forms::Panel^  panel21;
        private: System::Windows::Forms::TabControl^  TerrainRegionTypeTab;
        private: System::Windows::Forms::TabPage^  TerrainRegionBlockPage;
        private: System::Windows::Forms::Button^  btn_static_block_refresh;
        private: System::Windows::Forms::TabPage^  TerrainRegionSelfPage;
        private: System::Windows::Forms::ListView^  TerrainRegionSelfList;
        private: System::Windows::Forms::ColumnHeader^  columnHeader_custom_list_index;
        private: System::Windows::Forms::ColumnHeader^  columnHeader_custom_list_name;
        private: System::Windows::Forms::Panel^  panel22;
        private: System::Windows::Forms::Button^  TerrainAddRegionSelfBtn;
        private: System::Windows::Forms::Label^  TerrainSelRegionSelfText;
        private: System::Windows::Forms::Label^  label33;
        private: System::Windows::Forms::CheckBox^  cb_is_create_batch;
        private: System::Windows::Forms::NumericUpDown^  num_create_batch;
        private: System::Windows::Forms::TabPage^  tabPage7;
        private: System::Windows::Forms::TrackBar^  trackBar1;
        private: System::Windows::Forms::TrackBar^  trackBar2;
        private: System::Windows::Forms::TabPage^  tabPage8;
        private: System::Windows::Forms::ToolStripStatusLabel^  lable_status_batch;
        private: System::Windows::Forms::ToolStripStatusLabel^  lable_status_LastFPS;
        private: System::Windows::Forms::ToolStripStatusLabel^  lable_status_aveFPS;
        private: System::Windows::Forms::ToolStripStatusLabel^  lable_status_triCount;
        private: System::Windows::Forms::Label^  lable_terrain_batch_sel;
        private: System::Windows::Forms::Label^  lable_batch_curr_sel;
        private: System::Windows::Forms::Panel^  panel18;
        private: System::Windows::Forms::ListView^  listView1;
        private: System::Windows::Forms::TabControl^  tabControl1;
        private: System::Windows::Forms::TabPage^  tabPage2;
        private: System::Windows::Forms::TabPage^  tabPage3;
        private: System::Windows::Forms::TabPage^  tabPage4;
        private: System::Windows::Forms::TabPage^  tabPage5;
        private: System::Windows::Forms::TabPage^  tabPage6;
        private: System::Windows::Forms::ToolStripMenuItem^  设置ToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem_SceneEditorMode;
        private: System::Windows::Forms::TabPage^  util_type_slg_page;
        private: System::Windows::Forms::Label^  label9;
        private: System::Windows::Forms::ToolStripMenuItem^  游戏编辑ToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  打开游戏地图编辑器ToolStripMenuItem;
        private: System::Windows::Forms::MenuStrip^  menuStrip1;
        private: System::Windows::Forms::ToolStripMenuItem^  wToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  新建ToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  加载ToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  保存ToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  保存为ToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  帮助ToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  关于ToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  主题ToolStripMenuItem;
        private: System::Windows::Forms::StatusStrip^  statusStrip1;
        private: System::Windows::Forms::Panel^  base_panel;
        private: System::Windows::Forms::Splitter^  splitter1;
        private: System::Windows::Forms::Panel^  scene_base_panel;
        private: System::Windows::Forms::Panel^  panel8;
        private: System::Windows::Forms::Panel^  scene_panel;
        private: System::Windows::Forms::Panel^  Prop_Panel;
        private: System::Windows::Forms::TabControl^  prop_tab_ctrl;
        private: System::Windows::Forms::TabPage^  setting_page;
        private: System::Windows::Forms::TabPage^  terrain_page;
        private: System::Windows::Forms::TabPage^  elemet_page;
        private: System::Windows::Forms::Panel^  panel2;
        private: System::Windows::Forms::TabControl^  terrainTab;
        private: System::Windows::Forms::TabPage^  terrain_base_page;
        private: System::Windows::Forms::TabPage^  terrain_vertex_page;
        private: System::Windows::Forms::Panel^  panel1;
        private: System::Windows::Forms::TabPage^  terrain_texture_page;
        private: System::Windows::Forms::TabPage^  terrain_plant_page;
        private: System::Windows::Forms::TabPage^  terrain_cliff_page;
        private: System::Windows::Forms::TabPage^  terrain_water_page;
        private: System::Windows::Forms::GroupBox^  groupBox1;
        private: System::Windows::Forms::Label^  terrain_brush_speed_text;
        private: System::Windows::Forms::TrackBar^  terrain_brush_speed_tb;
        private: System::Windows::Forms::Label^  label5;
        private: System::Windows::Forms::Label^  terrain_brush_size_text;
        private: System::Windows::Forms::TrackBar^  terrain_brush_size_tb;
        private: System::Windows::Forms::Label^  label3;
        private: System::Windows::Forms::GroupBox^  groupBox2;
        private: System::Windows::Forms::ImageList^  imageList1;
        private: System::Windows::Forms::GroupBox^  groupBox3;
        private: System::Windows::Forms::TabControl^  terrain_style_tab;
        private: System::Windows::Forms::TabPage^  terrain_style_gun_page;
        private: System::Windows::Forms::TabPage^  terrain_style_pen_page;
        private: System::Windows::Forms::TabPage^  terrain_style_noise_page;
        private: System::Windows::Forms::TabPage^  terrain_style_frag_page;
        private: System::Windows::Forms::Label^  terrain_stytle_gun_decay_text;
        private: System::Windows::Forms::TrackBar^  terrain_stytle_gun_decay_tb;
        private: System::Windows::Forms::Label^  label4;
        private: System::Windows::Forms::TabControl^  terrain_brush_shape_tab;
        private: System::Windows::Forms::TabPage^  terrain_shape_yuan_page;
        private: System::Windows::Forms::TabPage^  terrain_shape_fang_page;
        private: System::Windows::Forms::TabPage^  terrain_shape_lin_page;
        private: System::Windows::Forms::ImageList^  imageList2;
        private: System::Windows::Forms::Panel^  panel4;
        private: System::Windows::Forms::Panel^  panel3;
        private: System::Windows::Forms::TabControl^  terrainHeightTab;
		private: System::Windows::Forms::TabPage^  terrain_height_level_page;
        private: System::Windows::Forms::TabPage^  terrain_height_uniform_page;
        private: System::Windows::Forms::TabPage^  terrain_height_noise_page;
        private: System::Windows::Forms::TabPage^  terrain_height_flat_page;
		private: System::Windows::Forms::Label^  terrain_height_level_range_text;
		private: System::Windows::Forms::TrackBar^  terrain_height_level_range_tb;
        private: System::Windows::Forms::Label^  label6;
        private: System::Windows::Forms::Label^  terrain_height_noise_range_text;
        private: System::Windows::Forms::TrackBar^  terrain_height_noise_range_tb;
        private: System::Windows::Forms::Label^  label10;
        private: System::Windows::Forms::Label^  terrain_height_smooth_range_text;
        private: System::Windows::Forms::TrackBar^  terrain_height_smooth_range_tb;
        private: System::Windows::Forms::Label^  label12;
        private: System::Windows::Forms::Panel^  panel5;
        private: System::Windows::Forms::TabControl^  terrainTextureTab;
        private: System::Windows::Forms::TabPage^  terrain_tex_add_page;
        private: System::Windows::Forms::Label^  terrain_tex_add_text;
        private: System::Windows::Forms::TrackBar^  terrain_tex_add_tb;
        private: System::Windows::Forms::Label^  label7;
        private: System::Windows::Forms::TabPage^  terrain_tex_remove_page;
        private: System::Windows::Forms::Label^  terrain_tex_remove_text;
        private: System::Windows::Forms::TrackBar^  terrain_tex_remove_tb;
        private: System::Windows::Forms::Label^  label13;
        private: System::Windows::Forms::TabPage^  terrain_tex_uniform_page;
        private: System::Windows::Forms::TabPage^  terrain_tex_mop_page;
        private: System::Windows::Forms::Label^  terrain_tex_mop_text;
        private: System::Windows::Forms::TrackBar^  terrain_tex_mop_tb;
        private: System::Windows::Forms::Label^  label15;
        private: System::Windows::Forms::TabPage^  terrain_tex_blur_page;
        private: System::Windows::Forms::Label^  terrain_tex_blur_text;
        private: System::Windows::Forms::TrackBar^  terrain_tex_blur_tb;
        private: System::Windows::Forms::Label^  label17;
        private: System::Windows::Forms::Panel^  panel6;
        private: System::Windows::Forms::TabControl^  terrain_texture_pic_tab;
        private: System::Windows::Forms::TabPage^  terrain_tex_0;
        private: System::Windows::Forms::TabPage^  terrain_tex_1;
        private: System::Windows::Forms::TabPage^  terrain_tex_2;
        private: System::Windows::Forms::TabPage^  terrain_tex_3;
        private: System::Windows::Forms::TabPage^  terrain_tex_4;
        private: System::Windows::Forms::TabPage^  terrain_tex_5;
        private: System::Windows::Forms::TabPage^  terrain_tex_6;
        private: System::Windows::Forms::TabPage^  terrain_tex_7;
        private: System::Windows::Forms::ImageList^  terrain_texture_pic_list;
        private: System::Windows::Forms::Panel^  panel7;
        private: System::Windows::Forms::Panel^  panel9;
        private: System::Windows::Forms::TabControl^  element_tab;
        private: System::Windows::Forms::TabPage^  createElment_page;
        private: System::Windows::Forms::TabControl^  SelectCreateElementTypeTab;
        private: System::Windows::Forms::TabPage^  create_static_page;
        private: System::Windows::Forms::TabPage^  create_tree_page;
        private: System::Windows::Forms::Panel^  panel11;
        private: System::Windows::Forms::Panel^  panel10;
        private: System::Windows::Forms::Button^  button1;
        private: System::Windows::Forms::TextBox^  textBox1;
        private: System::Windows::Forms::TabPage^  elemet_prop_page;
        private: System::Windows::Forms::Panel^  panel13;
        private: System::Windows::Forms::Panel^  panel12;
        private: System::Windows::Forms::TabPage^  elemet_list_page;
        private: System::Windows::Forms::Panel^  panel16;
        private: System::Windows::Forms::Button^  button3;
        private: System::Windows::Forms::TextBox^  textBox3;
        private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
		private: System::Windows::Forms::OpenFileDialog^ openSubsceneFileDialog;
        private: System::Windows::Forms::PropertyGrid^  element_prop_grids;
        private: System::Windows::Forms::TabControl^  UtilType_Ctrl;
        private: System::Windows::Forms::TabPage^  util_type_move_page;
        private: System::Windows::Forms::TabPage^  util_type_rot_page;
        private: System::Windows::Forms::TabPage^  util_type_scale_page;
        private: System::Windows::Forms::Label^  label2;
        private: System::Windows::Forms::Label^  label14;
        private: System::Windows::Forms::Label^  label16;
        private: System::Windows::Forms::Label^  camPosZ;
        private: System::Windows::Forms::Label^  label22;
        private: System::Windows::Forms::Label^  camPosY;
        private: System::Windows::Forms::Label^  label20;
        private: System::Windows::Forms::Label^  camPosX;
        private: System::Windows::Forms::Button^  button2;
        private: System::Windows::Forms::TreeView^  model_create_tree;
        private: System::Windows::Forms::Panel^  panel14;
        private: System::Windows::Forms::Button^  button5;
        private: System::Windows::Forms::Label^  prepare_model_text;
        private: System::Windows::Forms::Label^  label23;
        private: System::Windows::Forms::TreeView^  element_list;
        private: System::Windows::Forms::Panel^  panel15;
        private: System::Windows::Forms::Button^  button4;
        private: System::Windows::Forms::Button^  button6;
        private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->wToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->新建ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->加载ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->保存ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->保存为ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->编辑ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Menu_Edit_Undo = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Menu_Edit_Redo = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->游戏编辑ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->打开游戏地图编辑器ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->打开地形贴图编辑器ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->打开水效果编辑器ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->设置ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem_SceneEditorMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Menu_Setting_ShowSubScene = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->Menu_Setting_SelectSubscene = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->帮助ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->关于ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->主题ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->地图信息ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->lable_status_batch = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lable_status_LastFPS = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lable_status_aveFPS = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lable_status_triCount = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusCamSpeed = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->base_panel = (gcnew System::Windows::Forms::Panel());
			this->splitter1 = (gcnew System::Windows::Forms::Splitter());
			this->scene_base_panel = (gcnew System::Windows::Forms::Panel());
			this->scene_panel = (gcnew System::Windows::Forms::Panel());
			this->panel8 = (gcnew System::Windows::Forms::Panel());
			this->mousePosZ = (gcnew System::Windows::Forms::Label());
			this->label80 = (gcnew System::Windows::Forms::Label());
			this->mousePosY = (gcnew System::Windows::Forms::Label());
			this->label82 = (gcnew System::Windows::Forms::Label());
			this->mousePosX = (gcnew System::Windows::Forms::Label());
			this->label84 = (gcnew System::Windows::Forms::Label());
			this->label85 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->camPosZ = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->camPosY = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->camPosX = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->UtilType_Ctrl = (gcnew System::Windows::Forms::TabControl());
			this->util_type_slg_page = (gcnew System::Windows::Forms::TabPage());
			this->util_type_move_page = (gcnew System::Windows::Forms::TabPage());
			this->util_type_rot_page = (gcnew System::Windows::Forms::TabPage());
			this->util_type_scale_page = (gcnew System::Windows::Forms::TabPage());
			this->Prop_Panel = (gcnew System::Windows::Forms::Panel());
			this->prop_tab_ctrl = (gcnew System::Windows::Forms::TabControl());
			this->elemet_page = (gcnew System::Windows::Forms::TabPage());
			this->panel9 = (gcnew System::Windows::Forms::Panel());
			this->element_tab = (gcnew System::Windows::Forms::TabControl());
			this->createElment_page = (gcnew System::Windows::Forms::TabPage());
			this->SelectCreateElementTypeTab = (gcnew System::Windows::Forms::TabControl());
			this->create_static_page = (gcnew System::Windows::Forms::TabPage());
			this->panel11 = (gcnew System::Windows::Forms::Panel());
			this->model_create_tree = (gcnew System::Windows::Forms::TreeView());
			this->panel14 = (gcnew System::Windows::Forms::Panel());
			this->num_create_batch = (gcnew System::Windows::Forms::NumericUpDown());
			this->cb_is_create_batch = (gcnew System::Windows::Forms::CheckBox());
			this->prepare_model_text = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->panel10 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->create_tree_page = (gcnew System::Windows::Forms::TabPage());
			this->panel34 = (gcnew System::Windows::Forms::Panel());
			this->prepare_tree_text = (gcnew System::Windows::Forms::Label());
			this->label70 = (gcnew System::Windows::Forms::Label());
			this->button17 = (gcnew System::Windows::Forms::Button());
			this->panel28 = (gcnew System::Windows::Forms::Panel());
			this->tree_create_tree = (gcnew System::Windows::Forms::TreeView());
			this->create_effect_page = (gcnew System::Windows::Forms::TabPage());
			this->effect_create_tree = (gcnew System::Windows::Forms::TreeView());
			this->panel35 = (gcnew System::Windows::Forms::Panel());
			this->button18 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->panel36 = (gcnew System::Windows::Forms::Panel());
			this->prepare_effect_text = (gcnew System::Windows::Forms::Label());
			this->label73 = (gcnew System::Windows::Forms::Label());
			this->button19 = (gcnew System::Windows::Forms::Button());
			this->elemet_prop_page = (gcnew System::Windows::Forms::TabPage());
			this->panel13 = (gcnew System::Windows::Forms::Panel());
			this->element_prop_grids = (gcnew System::Windows::Forms::PropertyGrid());
			this->panel12 = (gcnew System::Windows::Forms::Panel());
			this->elemet_list_page = (gcnew System::Windows::Forms::TabPage());
			this->element_list = (gcnew System::Windows::Forms::TreeView());
			this->panel15 = (gcnew System::Windows::Forms::Panel());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->panel16 = (gcnew System::Windows::Forms::Panel());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->terrain_page = (gcnew System::Windows::Forms::TabPage());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->terrainTab = (gcnew System::Windows::Forms::TabControl());
			this->terrain_base_page = (gcnew System::Windows::Forms::TabPage());
			this->button21 = (gcnew System::Windows::Forms::Button());
			this->button_ClipMap = (gcnew System::Windows::Forms::Button());
			this->terrain_vertex_page = (gcnew System::Windows::Forms::TabPage());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->terrainHeightTab = (gcnew System::Windows::Forms::TabControl());
			this->terrain_height_level_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_height_level_range_text = (gcnew System::Windows::Forms::Label());
			this->terrain_height_level_range_tb = (gcnew System::Windows::Forms::TrackBar());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->terrain_height_uniform_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_height_noise_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_height_noise_range_text = (gcnew System::Windows::Forms::Label());
			this->terrain_height_noise_range_tb = (gcnew System::Windows::Forms::TrackBar());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->terrain_height_flat_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_height_smooth_range_text = (gcnew System::Windows::Forms::Label());
			this->terrain_height_smooth_range_tb = (gcnew System::Windows::Forms::TrackBar());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->imageList2 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->terrain_texture_page = (gcnew System::Windows::Forms::TabPage());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->terrain_texture_pic_tab = (gcnew System::Windows::Forms::TabControl());
			this->terrain_tex_0 = (gcnew System::Windows::Forms::TabPage());
			this->terrain_tex_1 = (gcnew System::Windows::Forms::TabPage());
			this->terrain_tex_2 = (gcnew System::Windows::Forms::TabPage());
			this->terrain_tex_3 = (gcnew System::Windows::Forms::TabPage());
			this->terrain_tex_4 = (gcnew System::Windows::Forms::TabPage());
			this->terrain_tex_5 = (gcnew System::Windows::Forms::TabPage());
			this->terrain_tex_6 = (gcnew System::Windows::Forms::TabPage());
			this->terrain_tex_7 = (gcnew System::Windows::Forms::TabPage());
			this->terrain_texture_pic_list = (gcnew System::Windows::Forms::ImageList(this->components));
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->terrainTextureTab = (gcnew System::Windows::Forms::TabControl());
			this->terrain_tex_add_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_tex_add_text = (gcnew System::Windows::Forms::Label());
			this->terrain_tex_add_tb = (gcnew System::Windows::Forms::TrackBar());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->terrain_tex_remove_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_tex_remove_text = (gcnew System::Windows::Forms::Label());
			this->terrain_tex_remove_tb = (gcnew System::Windows::Forms::TrackBar());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->terrain_tex_uniform_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_tex_mop_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_tex_mop_text = (gcnew System::Windows::Forms::Label());
			this->terrain_tex_mop_tb = (gcnew System::Windows::Forms::TrackBar());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->terrain_tex_blur_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_tex_blur_text = (gcnew System::Windows::Forms::Label());
			this->terrain_tex_blur_tb = (gcnew System::Windows::Forms::TrackBar());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->terrain_plant_page = (gcnew System::Windows::Forms::TabPage());
			this->panel18 = (gcnew System::Windows::Forms::Panel());
			this->lable_batch_curr_sel = (gcnew System::Windows::Forms::Label());
			this->lable_terrain_batch_sel = (gcnew System::Windows::Forms::Label());
			this->plantTab = (gcnew System::Windows::Forms::TabControl());
			this->plant_tree_page = (gcnew System::Windows::Forms::TabPage());
			this->listView_terrain_batch_tree_list = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->plant_grass_page = (gcnew System::Windows::Forms::TabPage());
			this->listView_terrain_batch_grass_list = (gcnew System::Windows::Forms::ListView());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
			this->plant_create_page = (gcnew System::Windows::Forms::TabPage());
			this->panel17 = (gcnew System::Windows::Forms::Panel());
			this->panel24 = (gcnew System::Windows::Forms::Panel());
			this->plantBatchEntityTab = (gcnew System::Windows::Forms::TabControl());
			this->terrain_batch_add_page = (gcnew System::Windows::Forms::TabPage());
			this->groupBox37 = (gcnew System::Windows::Forms::GroupBox());
			this->plant_create_ditribute_colum = (gcnew System::Windows::Forms::RadioButton());
			this->plant_create_ditribute_circle = (gcnew System::Windows::Forms::RadioButton());
			this->plant_create_align_checkbox = (gcnew System::Windows::Forms::CheckBox());
			this->label112 = (gcnew System::Windows::Forms::Label());
			this->TextBox_Plant_MaxScale = (gcnew System::Windows::Forms::TextBox());
			this->label111 = (gcnew System::Windows::Forms::Label());
			this->TextBox_Plant_MinScale = (gcnew System::Windows::Forms::TextBox());
			this->label110 = (gcnew System::Windows::Forms::Label());
			this->plant_create_scale_offset_bar = (gcnew System::Windows::Forms::TrackBar());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->plant_create_scale_offset_label = (gcnew System::Windows::Forms::Label());
			this->plant_create_treeDis_label = (gcnew System::Windows::Forms::Label());
			this->plant_create_clumping_bar = (gcnew System::Windows::Forms::TrackBar());
			this->plant_create_treeDis_bar = (gcnew System::Windows::Forms::TrackBar());
			this->plant_create_GrassDis_label = (gcnew System::Windows::Forms::Label());
			this->terrain_batch_remove_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_batch_noise_page = (gcnew System::Windows::Forms::TabPage());
			this->panel25 = (gcnew System::Windows::Forms::Panel());
			this->groupBox21 = (gcnew System::Windows::Forms::GroupBox());
			this->plant_batch_define_button = (gcnew System::Windows::Forms::Button());
			this->specialize_batch_textBox = (gcnew System::Windows::Forms::TextBox());
			this->specialize_batch_radioButton = (gcnew System::Windows::Forms::RadioButton());
			this->region_batch_radioButton = (gcnew System::Windows::Forms::RadioButton());
			this->common_batch_radioButton = (gcnew System::Windows::Forms::RadioButton());
			this->plant_set_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_cliff_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_water_page = (gcnew System::Windows::Forms::TabPage());
			this->panel23 = (gcnew System::Windows::Forms::Panel());
			this->waterTab = (gcnew System::Windows::Forms::TabControl());
			this->water_group_page = (gcnew System::Windows::Forms::TabPage());
			this->panel31 = (gcnew System::Windows::Forms::Panel());
			this->water_mat_tab = (gcnew System::Windows::Forms::TabControl());
			this->water_template_page = (gcnew System::Windows::Forms::TabPage());
			this->panel32 = (gcnew System::Windows::Forms::Panel());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->water_mat_template_list = (gcnew System::Windows::Forms::ListView());
			this->columnHeader_water_template_list_index = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader_water_template_list_name = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabPage15 = (gcnew System::Windows::Forms::TabPage());
			this->panel33 = (gcnew System::Windows::Forms::Panel());
			this->water_group_apply_btn = (gcnew System::Windows::Forms::Button());
			this->groupBox25 = (gcnew System::Windows::Forms::GroupBox());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->water_dirZ_txt = (gcnew System::Windows::Forms::TextBox());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->water_dirY_txt = (gcnew System::Windows::Forms::TextBox());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->water_dirX_txt = (gcnew System::Windows::Forms::TextBox());
			this->groupBox26 = (gcnew System::Windows::Forms::GroupBox());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->water_posZ_txt = (gcnew System::Windows::Forms::TextBox());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->water_posY_txt = (gcnew System::Windows::Forms::TextBox());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->water_posX_txt = (gcnew System::Windows::Forms::TextBox());
			this->panel29 = (gcnew System::Windows::Forms::Panel());
			this->water_group_list = (gcnew System::Windows::Forms::ListView());
			this->columnHeader_water_list_index = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader_water_list_mat_id = (gcnew System::Windows::Forms::ColumnHeader());
			this->water_visible_page = (gcnew System::Windows::Forms::TabPage());
			this->panel26 = (gcnew System::Windows::Forms::Panel());
			this->water_visible_tab = (gcnew System::Windows::Forms::TabControl());
			this->water_op_show_page = (gcnew System::Windows::Forms::TabPage());
			this->water_op_hide_page = (gcnew System::Windows::Forms::TabPage());
			this->water_height_page = (gcnew System::Windows::Forms::TabPage());
			this->panel27 = (gcnew System::Windows::Forms::Panel());
			this->water_height_tab = (gcnew System::Windows::Forms::TabControl());
			this->water_height_level_page = (gcnew System::Windows::Forms::TabPage());
			this->water_height_label = (gcnew System::Windows::Forms::Label());
			this->water_height_level_app = (gcnew System::Windows::Forms::TrackBar());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->water_height_uniform_page = (gcnew System::Windows::Forms::TabPage());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->water_height_confirm = (gcnew System::Windows::Forms::Button());
			this->water_height_text_box = (gcnew System::Windows::Forms::TextBox());
			this->water_height_flat_page = (gcnew System::Windows::Forms::TabPage());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->trackBar5 = (gcnew System::Windows::Forms::TrackBar());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->panel30 = (gcnew System::Windows::Forms::Panel());
			this->sel_water_txt = (gcnew System::Windows::Forms::Label());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->terrain_region_page = (gcnew System::Windows::Forms::TabPage());
			this->panel21 = (gcnew System::Windows::Forms::Panel());
			this->TerrainRegionTypeTab = (gcnew System::Windows::Forms::TabControl());
			this->TerrainRegionBlockPage = (gcnew System::Windows::Forms::TabPage());
			this->btn_show_block_refresh = (gcnew System::Windows::Forms::Button());
			this->btn_static_block_refresh = (gcnew System::Windows::Forms::Button());
			this->TerrainRegionSelfPage = (gcnew System::Windows::Forms::TabPage());
			this->TerrainRegionSelfList = (gcnew System::Windows::Forms::ListView());
			this->columnHeader_custom_list_index = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader_custom_list_name = (gcnew System::Windows::Forms::ColumnHeader());
			this->panel22 = (gcnew System::Windows::Forms::Panel());
			this->TerrainAddRegionSelfBtn = (gcnew System::Windows::Forms::Button());
			this->TerrainSelRegionSelfText = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->panel20 = (gcnew System::Windows::Forms::Panel());
			this->terrain_region_visible_ckb = (gcnew System::Windows::Forms::CheckBox());
			this->panel19 = (gcnew System::Windows::Forms::Panel());
			this->terrainRegionOpTab = (gcnew System::Windows::Forms::TabControl());
			this->terrain_region_add_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_region_remove_page = (gcnew System::Windows::Forms::TabPage());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->terrain_style_tab = (gcnew System::Windows::Forms::TabControl());
			this->terrain_style_gun_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_stytle_gun_decay_text = (gcnew System::Windows::Forms::Label());
			this->terrain_stytle_gun_decay_tb = (gcnew System::Windows::Forms::TrackBar());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->terrain_style_pen_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_style_noise_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_style_frag_page = (gcnew System::Windows::Forms::TabPage());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->terrain_brush_shape_tab = (gcnew System::Windows::Forms::TabControl());
			this->terrain_shape_yuan_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_shape_fang_page = (gcnew System::Windows::Forms::TabPage());
			this->terrain_shape_lin_page = (gcnew System::Windows::Forms::TabPage());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->terrain_brush_speed_text = (gcnew System::Windows::Forms::Label());
			this->terrain_brush_speed_tb = (gcnew System::Windows::Forms::TrackBar());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->terrain_brush_size_text = (gcnew System::Windows::Forms::Label());
			this->terrain_brush_size_tb = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->setting_page = (gcnew System::Windows::Forms::TabPage());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->ConfigTab = (gcnew System::Windows::Forms::TabControl());
			this->Config_env_light_page = (gcnew System::Windows::Forms::TabPage());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->TextBox_STSpecular_B = (gcnew System::Windows::Forms::TextBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->TextBox_STSpecular_G = (gcnew System::Windows::Forms::TextBox());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->TextBox_STSpecular_R = (gcnew System::Windows::Forms::TextBox());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->TextBox_STDiffuse_B = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->TextBox_STDiffuse_G = (gcnew System::Windows::Forms::TextBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->TextBox_STDiffuse_R = (gcnew System::Windows::Forms::TextBox());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->TextBox_STAmbient_B = (gcnew System::Windows::Forms::TextBox());
			this->label92 = (gcnew System::Windows::Forms::Label());
			this->TextBox_STAmbient_G = (gcnew System::Windows::Forms::TextBox());
			this->label93 = (gcnew System::Windows::Forms::Label());
			this->TextBox_STAmbient_R = (gcnew System::Windows::Forms::TextBox());
			this->label94 = (gcnew System::Windows::Forms::Label());
			this->label95 = (gcnew System::Windows::Forms::Label());
			this->label96 = (gcnew System::Windows::Forms::Label());
			this->label97 = (gcnew System::Windows::Forms::Label());
			this->groupBox36 = (gcnew System::Windows::Forms::GroupBox());
			this->TextBox_SGSpecular_B = (gcnew System::Windows::Forms::TextBox());
			this->label98 = (gcnew System::Windows::Forms::Label());
			this->TextBox_SGSpecular_G = (gcnew System::Windows::Forms::TextBox());
			this->label99 = (gcnew System::Windows::Forms::Label());
			this->TextBox_SGSpecular_R = (gcnew System::Windows::Forms::TextBox());
			this->label100 = (gcnew System::Windows::Forms::Label());
			this->TextBox_SGDiffuse_B = (gcnew System::Windows::Forms::TextBox());
			this->label101 = (gcnew System::Windows::Forms::Label());
			this->TextBox_SGDiffuse_G = (gcnew System::Windows::Forms::TextBox());
			this->label102 = (gcnew System::Windows::Forms::Label());
			this->TextBox_SGDiffuse_R = (gcnew System::Windows::Forms::TextBox());
			this->label103 = (gcnew System::Windows::Forms::Label());
			this->TextBox_SGAmbient_B = (gcnew System::Windows::Forms::TextBox());
			this->label104 = (gcnew System::Windows::Forms::Label());
			this->TextBox_SGAmbient_G = (gcnew System::Windows::Forms::TextBox());
			this->label105 = (gcnew System::Windows::Forms::Label());
			this->TextBox_SGAmbient_R = (gcnew System::Windows::Forms::TextBox());
			this->label106 = (gcnew System::Windows::Forms::Label());
			this->label107 = (gcnew System::Windows::Forms::Label());
			this->label108 = (gcnew System::Windows::Forms::Label());
			this->label109 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->TextBox_Specular_B = (gcnew System::Windows::Forms::TextBox());
			this->label89 = (gcnew System::Windows::Forms::Label());
			this->TextBox_Specular_G = (gcnew System::Windows::Forms::TextBox());
			this->label90 = (gcnew System::Windows::Forms::Label());
			this->TextBox_Specular_R = (gcnew System::Windows::Forms::TextBox());
			this->label91 = (gcnew System::Windows::Forms::Label());
			this->TextBox_Diffuse_B = (gcnew System::Windows::Forms::TextBox());
			this->label86 = (gcnew System::Windows::Forms::Label());
			this->TextBox_Diffuse_G = (gcnew System::Windows::Forms::TextBox());
			this->label87 = (gcnew System::Windows::Forms::Label());
			this->TextBox_Diffuse_R = (gcnew System::Windows::Forms::TextBox());
			this->label88 = (gcnew System::Windows::Forms::Label());
			this->TextBox_Ambient_B = (gcnew System::Windows::Forms::TextBox());
			this->label83 = (gcnew System::Windows::Forms::Label());
			this->TextBox_Ambient_G = (gcnew System::Windows::Forms::TextBox());
			this->label81 = (gcnew System::Windows::Forms::Label());
			this->TextBox_Ambient_R = (gcnew System::Windows::Forms::TextBox());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox27 = (gcnew System::Windows::Forms::GroupBox());
			this->label65 = (gcnew System::Windows::Forms::Label());
			this->terrainLightingParameterW_txt = (gcnew System::Windows::Forms::TextBox());
			this->label64 = (gcnew System::Windows::Forms::Label());
			this->terrainLightingParameterZ_txt = (gcnew System::Windows::Forms::TextBox());
			this->label63 = (gcnew System::Windows::Forms::Label());
			this->terrainLightingParameterY_txt = (gcnew System::Windows::Forms::TextBox());
			this->label66 = (gcnew System::Windows::Forms::Label());
			this->terrainLightingParameterX_txt = (gcnew System::Windows::Forms::TextBox());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->config_video_page = (gcnew System::Windows::Forms::TabPage());
			this->groupBox39 = (gcnew System::Windows::Forms::GroupBox());
			this->water_reflect_check = (gcnew System::Windows::Forms::CheckBox());
			this->water_refract_check = (gcnew System::Windows::Forms::CheckBox());
			this->water_shadow_check = (gcnew System::Windows::Forms::CheckBox());
			this->water_alpha_check = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox16 = (gcnew System::Windows::Forms::GroupBox());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->sbs_normal_txt = (gcnew System::Windows::Forms::TextBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->sbs_specular_txt = (gcnew System::Windows::Forms::TextBox());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->sbs_bias_txt = (gcnew System::Windows::Forms::TextBox());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->sbs_scale_txt = (gcnew System::Windows::Forms::TextBox());
			this->groupBox15 = (gcnew System::Windows::Forms::GroupBox());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->fsaa_txt = (gcnew System::Windows::Forms::TextBox());
			this->groupBox14 = (gcnew System::Windows::Forms::GroupBox());
			this->gamma_check = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox11 = (gcnew System::Windows::Forms::GroupBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->txt_mipmap_bias = (gcnew System::Windows::Forms::TextBox());
			this->groupBox10 = (gcnew System::Windows::Forms::GroupBox());
			this->rb_tex_filter_anisotropic = (gcnew System::Windows::Forms::RadioButton());
			this->rb_tex_filter_3line = (gcnew System::Windows::Forms::RadioButton());
			this->rb_tex_filter_bline = (gcnew System::Windows::Forms::RadioButton());
			this->rb_tex_filter_none = (gcnew System::Windows::Forms::RadioButton());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->model_sa_tex_check = (gcnew System::Windows::Forms::CheckBox());
			this->model_normal_tex_check = (gcnew System::Windows::Forms::CheckBox());
			this->model_shadow_dynamic_check = (gcnew System::Windows::Forms::CheckBox());
			this->model_shadow_tex_check = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->terrain_color_check = (gcnew System::Windows::Forms::CheckBox());
			this->terrain_offset_check = (gcnew System::Windows::Forms::CheckBox());
			this->terrain_spec_check = (gcnew System::Windows::Forms::CheckBox());
			this->terrain_normal_check = (gcnew System::Windows::Forms::CheckBox());
			this->config_plant_page = (gcnew System::Windows::Forms::TabPage());
			this->groupBox38 = (gcnew System::Windows::Forms::GroupBox());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->textBox_grassLod_end = (gcnew System::Windows::Forms::TextBox());
			this->label_grassLod_start = (gcnew System::Windows::Forms::Label());
			this->textBox_grassLod_start = (gcnew System::Windows::Forms::TextBox());
			this->groupBox33 = (gcnew System::Windows::Forms::GroupBox());
			this->wind_check = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox35 = (gcnew System::Windows::Forms::GroupBox());
			this->lableWindIntensity = (gcnew System::Windows::Forms::Label());
			this->TrackBarWindIntensity = (gcnew System::Windows::Forms::TrackBar());
			this->groupBox34 = (gcnew System::Windows::Forms::GroupBox());
			this->label67 = (gcnew System::Windows::Forms::Label());
			this->textBoxWindDirZ = (gcnew System::Windows::Forms::TextBox());
			this->label76 = (gcnew System::Windows::Forms::Label());
			this->textBoxWindDirY = (gcnew System::Windows::Forms::TextBox());
			this->label77 = (gcnew System::Windows::Forms::Label());
			this->textBoxWindDirX = (gcnew System::Windows::Forms::TextBox());
			this->label78 = (gcnew System::Windows::Forms::Label());
			this->label79 = (gcnew System::Windows::Forms::Label());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox32 = (gcnew System::Windows::Forms::GroupBox());
			this->ckb_water_visible = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox31 = (gcnew System::Windows::Forms::GroupBox());
			this->ckb_entity_visible = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox18 = (gcnew System::Windows::Forms::GroupBox());
			this->ckb_terrain_grids_visible = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox17 = (gcnew System::Windows::Forms::GroupBox());
			this->ckb_wireframe = (gcnew System::Windows::Forms::CheckBox());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->fov_edit = (gcnew System::Windows::Forms::TextBox());
			this->tabPage9 = (gcnew System::Windows::Forms::TabPage());
			this->button13 = (gcnew System::Windows::Forms::Button());
			this->groupBox23 = (gcnew System::Windows::Forms::GroupBox());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->txt_fog_color_b = (gcnew System::Windows::Forms::TextBox());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->txt_fog_color_g = (gcnew System::Windows::Forms::TextBox());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->txt_fog_color_r = (gcnew System::Windows::Forms::TextBox());
			this->groupBox22 = (gcnew System::Windows::Forms::GroupBox());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->txt_fog_end = (gcnew System::Windows::Forms::TextBox());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->txt_fog_start = (gcnew System::Windows::Forms::TextBox());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->txt_fog_exp = (gcnew System::Windows::Forms::TextBox());
			this->groupBox13 = (gcnew System::Windows::Forms::GroupBox());
			this->rb_fog_exp = (gcnew System::Windows::Forms::RadioButton());
			this->rb_fog_line = (gcnew System::Windows::Forms::RadioButton());
			this->rb_fog_none = (gcnew System::Windows::Forms::RadioButton());
			this->tabPage10 = (gcnew System::Windows::Forms::TabPage());
			this->groupBox24 = (gcnew System::Windows::Forms::GroupBox());
			this->label59 = (gcnew System::Windows::Forms::Label());
			this->shadowParameterZ_txt = (gcnew System::Windows::Forms::TextBox());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->shadowParameterW_txt = (gcnew System::Windows::Forms::TextBox());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->shadowParameterY_txt = (gcnew System::Windows::Forms::TextBox());
			this->label62 = (gcnew System::Windows::Forms::Label());
			this->shadowParameterX_txt = (gcnew System::Windows::Forms::TextBox());
			this->button14 = (gcnew System::Windows::Forms::Button());
			this->groupBox20 = (gcnew System::Windows::Forms::GroupBox());
			this->terrain_dynamic_shadow_check = (gcnew System::Windows::Forms::CheckBox());
			this->terrain_shadow_check = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox12 = (gcnew System::Windows::Forms::GroupBox());
			this->rb_shadow_lispsm = (gcnew System::Windows::Forms::RadioButton());
			this->rb_shadow_plane = (gcnew System::Windows::Forms::RadioButton());
			this->rb_shadow_uniform = (gcnew System::Windows::Forms::RadioButton());
			this->rb_shadow_uniform_focused = (gcnew System::Windows::Forms::RadioButton());
			this->rb_shadow_pssm = (gcnew System::Windows::Forms::RadioButton());
			this->rb_shadow_none = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox19 = (gcnew System::Windows::Forms::GroupBox());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->txt_terrainShadowOffset = (gcnew System::Windows::Forms::TextBox());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->tabPage11 = (gcnew System::Windows::Forms::TabPage());
			this->button15 = (gcnew System::Windows::Forms::Button());
			this->groupBox28 = (gcnew System::Windows::Forms::GroupBox());
			this->label68 = (gcnew System::Windows::Forms::Label());
			this->minimap_tex_size_h = (gcnew System::Windows::Forms::TextBox());
			this->label69 = (gcnew System::Windows::Forms::Label());
			this->minimap_tex_size_w = (gcnew System::Windows::Forms::TextBox());
			this->groupBox29 = (gcnew System::Windows::Forms::GroupBox());
			this->label71 = (gcnew System::Windows::Forms::Label());
			this->minimap_size_h = (gcnew System::Windows::Forms::TextBox());
			this->label72 = (gcnew System::Windows::Forms::Label());
			this->minimap_size_w = (gcnew System::Windows::Forms::TextBox());
			this->groupBox30 = (gcnew System::Windows::Forms::GroupBox());
			this->label74 = (gcnew System::Windows::Forms::Label());
			this->minimap_center_z = (gcnew System::Windows::Forms::TextBox());
			this->label75 = (gcnew System::Windows::Forms::Label());
			this->minimap_center_x = (gcnew System::Windows::Forms::TextBox());
			this->tabPage12 = (gcnew System::Windows::Forms::TabPage());
			this->MotionBlur_ckb = (gcnew System::Windows::Forms::CheckBox());
			this->HDR_ckb = (gcnew System::Windows::Forms::CheckBox());
			this->FakeHDR_ckb = (gcnew System::Windows::Forms::CheckBox());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->Bloom_ckb = (gcnew System::Windows::Forms::CheckBox());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->openSubsceneFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tabPage7 = (gcnew System::Windows::Forms::TabPage());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->tabPage8 = (gcnew System::Windows::Forms::TabPage());
			this->Menu_Setting_EnableClipScene = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->base_panel->SuspendLayout();
			this->scene_base_panel->SuspendLayout();
			this->panel8->SuspendLayout();
			this->UtilType_Ctrl->SuspendLayout();
			this->Prop_Panel->SuspendLayout();
			this->prop_tab_ctrl->SuspendLayout();
			this->elemet_page->SuspendLayout();
			this->panel9->SuspendLayout();
			this->element_tab->SuspendLayout();
			this->createElment_page->SuspendLayout();
			this->SelectCreateElementTypeTab->SuspendLayout();
			this->create_static_page->SuspendLayout();
			this->panel11->SuspendLayout();
			this->panel14->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->num_create_batch))->BeginInit();
			this->panel10->SuspendLayout();
			this->create_tree_page->SuspendLayout();
			this->panel34->SuspendLayout();
			this->panel28->SuspendLayout();
			this->create_effect_page->SuspendLayout();
			this->panel35->SuspendLayout();
			this->panel36->SuspendLayout();
			this->elemet_prop_page->SuspendLayout();
			this->panel13->SuspendLayout();
			this->elemet_list_page->SuspendLayout();
			this->panel15->SuspendLayout();
			this->panel16->SuspendLayout();
			this->terrain_page->SuspendLayout();
			this->panel2->SuspendLayout();
			this->terrainTab->SuspendLayout();
			this->terrain_base_page->SuspendLayout();
			this->terrain_vertex_page->SuspendLayout();
			this->panel3->SuspendLayout();
			this->terrainHeightTab->SuspendLayout();
			this->terrain_height_level_page->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_height_level_range_tb))->BeginInit();
			this->terrain_height_noise_page->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_height_noise_range_tb))->BeginInit();
			this->terrain_height_flat_page->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_height_smooth_range_tb))->BeginInit();
			this->terrain_texture_page->SuspendLayout();
			this->panel6->SuspendLayout();
			this->terrain_texture_pic_tab->SuspendLayout();
			this->panel5->SuspendLayout();
			this->terrainTextureTab->SuspendLayout();
			this->terrain_tex_add_page->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_tex_add_tb))->BeginInit();
			this->terrain_tex_remove_page->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_tex_remove_tb))->BeginInit();
			this->terrain_tex_mop_page->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_tex_mop_tb))->BeginInit();
			this->terrain_tex_blur_page->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_tex_blur_tb))->BeginInit();
			this->terrain_plant_page->SuspendLayout();
			this->panel18->SuspendLayout();
			this->plantTab->SuspendLayout();
			this->plant_tree_page->SuspendLayout();
			this->plant_grass_page->SuspendLayout();
			this->plant_create_page->SuspendLayout();
			this->panel17->SuspendLayout();
			this->panel24->SuspendLayout();
			this->plantBatchEntityTab->SuspendLayout();
			this->terrain_batch_add_page->SuspendLayout();
			this->groupBox37->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->plant_create_scale_offset_bar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->plant_create_clumping_bar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->plant_create_treeDis_bar))->BeginInit();
			this->panel25->SuspendLayout();
			this->groupBox21->SuspendLayout();
			this->terrain_water_page->SuspendLayout();
			this->panel23->SuspendLayout();
			this->waterTab->SuspendLayout();
			this->water_group_page->SuspendLayout();
			this->panel31->SuspendLayout();
			this->water_mat_tab->SuspendLayout();
			this->water_template_page->SuspendLayout();
			this->panel32->SuspendLayout();
			this->tabPage15->SuspendLayout();
			this->panel33->SuspendLayout();
			this->groupBox25->SuspendLayout();
			this->groupBox26->SuspendLayout();
			this->panel29->SuspendLayout();
			this->water_visible_page->SuspendLayout();
			this->panel26->SuspendLayout();
			this->water_visible_tab->SuspendLayout();
			this->water_height_page->SuspendLayout();
			this->panel27->SuspendLayout();
			this->water_height_tab->SuspendLayout();
			this->water_height_level_page->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->water_height_level_app))->BeginInit();
			this->water_height_uniform_page->SuspendLayout();
			this->water_height_flat_page->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar5))->BeginInit();
			this->panel30->SuspendLayout();
			this->terrain_region_page->SuspendLayout();
			this->panel21->SuspendLayout();
			this->TerrainRegionTypeTab->SuspendLayout();
			this->TerrainRegionBlockPage->SuspendLayout();
			this->TerrainRegionSelfPage->SuspendLayout();
			this->panel22->SuspendLayout();
			this->panel20->SuspendLayout();
			this->panel19->SuspendLayout();
			this->terrainRegionOpTab->SuspendLayout();
			this->panel1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->terrain_style_tab->SuspendLayout();
			this->terrain_style_gun_page->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_stytle_gun_decay_tb))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->terrain_brush_shape_tab->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_brush_speed_tb))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_brush_size_tb))->BeginInit();
			this->setting_page->SuspendLayout();
			this->panel7->SuspendLayout();
			this->ConfigTab->SuspendLayout();
			this->Config_env_light_page->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox36->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox27->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->config_video_page->SuspendLayout();
			this->groupBox39->SuspendLayout();
			this->groupBox16->SuspendLayout();
			this->groupBox15->SuspendLayout();
			this->groupBox14->SuspendLayout();
			this->groupBox11->SuspendLayout();
			this->groupBox10->SuspendLayout();
			this->groupBox9->SuspendLayout();
			this->groupBox8->SuspendLayout();
			this->config_plant_page->SuspendLayout();
			this->groupBox38->SuspendLayout();
			this->groupBox33->SuspendLayout();
			this->groupBox35->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBarWindIntensity))->BeginInit();
			this->groupBox34->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox32->SuspendLayout();
			this->groupBox31->SuspendLayout();
			this->groupBox18->SuspendLayout();
			this->groupBox17->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->tabPage9->SuspendLayout();
			this->groupBox23->SuspendLayout();
			this->groupBox22->SuspendLayout();
			this->groupBox13->SuspendLayout();
			this->tabPage10->SuspendLayout();
			this->groupBox24->SuspendLayout();
			this->groupBox20->SuspendLayout();
			this->groupBox12->SuspendLayout();
			this->groupBox19->SuspendLayout();
			this->tabPage11->SuspendLayout();
			this->groupBox28->SuspendLayout();
			this->groupBox29->SuspendLayout();
			this->groupBox30->SuspendLayout();
			this->tabPage12->SuspendLayout();
			this->tabPage7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->wToolStripMenuItem, 
				this->编辑ToolStripMenuItem, this->游戏编辑ToolStripMenuItem, this->设置ToolStripMenuItem, this->帮助ToolStripMenuItem});
			this->menuStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1192, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// wToolStripMenuItem
			// 
			this->wToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->新建ToolStripMenuItem, 
				this->加载ToolStripMenuItem, this->保存ToolStripMenuItem, this->保存为ToolStripMenuItem});
			this->wToolStripMenuItem->Name = L"wToolStripMenuItem";
			this->wToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->wToolStripMenuItem->Text = L"文件";
			// 
			// 新建ToolStripMenuItem
			// 
			this->新建ToolStripMenuItem->Name = L"新建ToolStripMenuItem";
			this->新建ToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->新建ToolStripMenuItem->Text = L"新建";
			this->新建ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::新建ToolStripMenuItem_Click);
			// 
			// 加载ToolStripMenuItem
			// 
			this->加载ToolStripMenuItem->Name = L"加载ToolStripMenuItem";
			this->加载ToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->加载ToolStripMenuItem->Text = L"加载场景文件";
			this->加载ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::加载ToolStripMenuItem_Click);
			// 
			// 保存ToolStripMenuItem
			// 
			this->保存ToolStripMenuItem->Name = L"保存ToolStripMenuItem";
			this->保存ToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->保存ToolStripMenuItem->Text = L"保存";
			this->保存ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::保存ToolStripMenuItem_Click);
			// 
			// 保存为ToolStripMenuItem
			// 
			this->保存为ToolStripMenuItem->Name = L"保存为ToolStripMenuItem";
			this->保存为ToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->保存为ToolStripMenuItem->Text = L"保存为";
			this->保存为ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::保存为ToolStripMenuItem_Click);
			// 
			// 编辑ToolStripMenuItem
			// 
			this->编辑ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->Menu_Edit_Undo, 
				this->Menu_Edit_Redo});
			this->编辑ToolStripMenuItem->Name = L"编辑ToolStripMenuItem";
			this->编辑ToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->编辑ToolStripMenuItem->Text = L"编辑";
			// 
			// Menu_Edit_Undo
			// 
			this->Menu_Edit_Undo->Name = L"Menu_Edit_Undo";
			this->Menu_Edit_Undo->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Z));
			this->Menu_Edit_Undo->Size = System::Drawing::Size(135, 22);
			this->Menu_Edit_Undo->Text = L"撤销";
			this->Menu_Edit_Undo->Click += gcnew System::EventHandler(this, &MainForm::Menu_Edit_Undo_Click);
			// 
			// Menu_Edit_Redo
			// 
			this->Menu_Edit_Redo->Name = L"Menu_Edit_Redo";
			this->Menu_Edit_Redo->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Y));
			this->Menu_Edit_Redo->Size = System::Drawing::Size(135, 22);
			this->Menu_Edit_Redo->Text = L"重做";
			this->Menu_Edit_Redo->Click += gcnew System::EventHandler(this, &MainForm::Menu_Edit_Redo_Click);
			// 
			// 游戏编辑ToolStripMenuItem
			// 
			this->游戏编辑ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->打开游戏地图编辑器ToolStripMenuItem, 
				this->打开地形贴图编辑器ToolStripMenuItem, this->打开水效果编辑器ToolStripMenuItem});
			this->游戏编辑ToolStripMenuItem->Name = L"游戏编辑ToolStripMenuItem";
			this->游戏编辑ToolStripMenuItem->Size = System::Drawing::Size(77, 20);
			this->游戏编辑ToolStripMenuItem->Text = L"附属编辑器";
			// 
			// 打开游戏地图编辑器ToolStripMenuItem
			// 
			this->打开游戏地图编辑器ToolStripMenuItem->Name = L"打开游戏地图编辑器ToolStripMenuItem";
			this->打开游戏地图编辑器ToolStripMenuItem->Size = System::Drawing::Size(178, 22);
			this->打开游戏地图编辑器ToolStripMenuItem->Text = L"打开游戏地图编辑器";
			this->打开游戏地图编辑器ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::打开游戏地图编辑器ToolStripMenuItem_Click);
			// 
			// 打开地形贴图编辑器ToolStripMenuItem
			// 
			this->打开地形贴图编辑器ToolStripMenuItem->Name = L"打开地形贴图编辑器ToolStripMenuItem";
			this->打开地形贴图编辑器ToolStripMenuItem->Size = System::Drawing::Size(178, 22);
			this->打开地形贴图编辑器ToolStripMenuItem->Text = L"打开地形贴图编辑器";
			this->打开地形贴图编辑器ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::打开地形贴图编辑器ToolStripMenuItem_Click);
			// 
			// 打开水效果编辑器ToolStripMenuItem
			// 
			this->打开水效果编辑器ToolStripMenuItem->Name = L"打开水效果编辑器ToolStripMenuItem";
			this->打开水效果编辑器ToolStripMenuItem->Size = System::Drawing::Size(178, 22);
			this->打开水效果编辑器ToolStripMenuItem->Text = L"打开水效果编辑器";
			this->打开水效果编辑器ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::打开水效果编辑器ToolStripMenuItem_Click);
			// 
			// 设置ToolStripMenuItem
			// 
			this->设置ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->ToolStripMenuItem_SceneEditorMode, 
				this->Menu_Setting_ShowSubScene, this->Menu_Setting_SelectSubscene, this->Menu_Setting_EnableClipScene});
			this->设置ToolStripMenuItem->Name = L"设置ToolStripMenuItem";
			this->设置ToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->设置ToolStripMenuItem->Text = L"设置";
			// 
			// ToolStripMenuItem_SceneEditorMode
			// 
			this->ToolStripMenuItem_SceneEditorMode->Checked = true;
			this->ToolStripMenuItem_SceneEditorMode->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ToolStripMenuItem_SceneEditorMode->Name = L"ToolStripMenuItem_SceneEditorMode";
			this->ToolStripMenuItem_SceneEditorMode->Size = System::Drawing::Size(152, 22);
			this->ToolStripMenuItem_SceneEditorMode->Text = L"编辑模式";
			this->ToolStripMenuItem_SceneEditorMode->Click += gcnew System::EventHandler(this, &MainForm::ToolStripMenuItem_SceneEditorMode_Click);
			// 
			// Menu_Setting_ShowSubScene
			// 
			this->Menu_Setting_ShowSubScene->Name = L"Menu_Setting_ShowSubScene";
			this->Menu_Setting_ShowSubScene->Size = System::Drawing::Size(152, 22);
			this->Menu_Setting_ShowSubScene->Text = L"显示策划场景";
			this->Menu_Setting_ShowSubScene->Click += gcnew System::EventHandler(this, &MainForm::Menu_Setting_ShowSubScene_Click);
			// 
			// Menu_Setting_SelectSubscene
			// 
			this->Menu_Setting_SelectSubscene->Name = L"Menu_Setting_SelectSubscene";
			this->Menu_Setting_SelectSubscene->Size = System::Drawing::Size(152, 22);
			this->Menu_Setting_SelectSubscene->Text = L"选择策划场景";
			this->Menu_Setting_SelectSubscene->Click += gcnew System::EventHandler(this, &MainForm::Menu_Setting_SelectSubscene_Click);
			// 
			// 帮助ToolStripMenuItem
			// 
			this->帮助ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->关于ToolStripMenuItem, 
				this->主题ToolStripMenuItem, this->地图信息ToolStripMenuItem});
			this->帮助ToolStripMenuItem->Name = L"帮助ToolStripMenuItem";
			this->帮助ToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->帮助ToolStripMenuItem->Text = L"帮助";
			// 
			// 关于ToolStripMenuItem
			// 
			this->关于ToolStripMenuItem->Name = L"关于ToolStripMenuItem";
			this->关于ToolStripMenuItem->Size = System::Drawing::Size(118, 22);
			this->关于ToolStripMenuItem->Text = L"关于";
			// 
			// 主题ToolStripMenuItem
			// 
			this->主题ToolStripMenuItem->Name = L"主题ToolStripMenuItem";
			this->主题ToolStripMenuItem->Size = System::Drawing::Size(118, 22);
			this->主题ToolStripMenuItem->Text = L"主题";
			// 
			// 地图信息ToolStripMenuItem
			// 
			this->地图信息ToolStripMenuItem->Name = L"地图信息ToolStripMenuItem";
			this->地图信息ToolStripMenuItem->Size = System::Drawing::Size(118, 22);
			this->地图信息ToolStripMenuItem->Text = L"地图信息";
			this->地图信息ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::地图信息ToolStripMenuItem_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->lable_status_batch, 
				this->lable_status_LastFPS, this->lable_status_aveFPS, this->lable_status_triCount, this->toolStripStatusCamSpeed});
			this->statusStrip1->Location = System::Drawing::Point(0, 744);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(1192, 22);
			this->statusStrip1->TabIndex = 2;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// lable_status_batch
			// 
			this->lable_status_batch->Name = L"lable_status_batch";
			this->lable_status_batch->Size = System::Drawing::Size(77, 17);
			this->lable_status_batch->Text = L"BatchCount:0";
			// 
			// lable_status_LastFPS
			// 
			this->lable_status_LastFPS->Name = L"lable_status_LastFPS";
			this->lable_status_LastFPS->Size = System::Drawing::Size(59, 17);
			this->lable_status_LastFPS->Text = L"LastFPS:0";
			// 
			// lable_status_aveFPS
			// 
			this->lable_status_aveFPS->Name = L"lable_status_aveFPS";
			this->lable_status_aveFPS->Size = System::Drawing::Size(53, 17);
			this->lable_status_aveFPS->Text = L"aveFPS:0";
			// 
			// lable_status_triCount
			// 
			this->lable_status_triCount->Name = L"lable_status_triCount";
			this->lable_status_triCount->Size = System::Drawing::Size(65, 17);
			this->lable_status_triCount->Text = L"TriCount:0";
			// 
			// toolStripStatusCamSpeed
			// 
			this->toolStripStatusCamSpeed->Name = L"toolStripStatusCamSpeed";
			this->toolStripStatusCamSpeed->Size = System::Drawing::Size(95, 17);
			this->toolStripStatusCamSpeed->Text = L"CameraSpeed:100";
			// 
			// base_panel
			// 
			this->base_panel->Controls->Add(this->splitter1);
			this->base_panel->Controls->Add(this->scene_base_panel);
			this->base_panel->Controls->Add(this->Prop_Panel);
			this->base_panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->base_panel->Location = System::Drawing::Point(0, 24);
			this->base_panel->Name = L"base_panel";
			this->base_panel->Size = System::Drawing::Size(1192, 720);
			this->base_panel->TabIndex = 3;
			// 
			// splitter1
			// 
			this->splitter1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->splitter1->Dock = System::Windows::Forms::DockStyle::Right;
			this->splitter1->Location = System::Drawing::Point(927, 0);
			this->splitter1->Name = L"splitter1";
			this->splitter1->Size = System::Drawing::Size(3, 720);
			this->splitter1->TabIndex = 2;
			this->splitter1->TabStop = false;
			// 
			// scene_base_panel
			// 
			this->scene_base_panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->scene_base_panel->Controls->Add(this->scene_panel);
			this->scene_base_panel->Controls->Add(this->panel8);
			this->scene_base_panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->scene_base_panel->Location = System::Drawing::Point(0, 0);
			this->scene_base_panel->Name = L"scene_base_panel";
			this->scene_base_panel->Size = System::Drawing::Size(930, 720);
			this->scene_base_panel->TabIndex = 1;
			// 
			// scene_panel
			// 
			this->scene_panel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->scene_panel->Location = System::Drawing::Point(0, 0);
			this->scene_panel->Name = L"scene_panel";
			this->scene_panel->Size = System::Drawing::Size(926, 684);
			this->scene_panel->TabIndex = 2;
			this->scene_panel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::scene_panel_MouseDown);
			this->scene_panel->Resize += gcnew System::EventHandler(this, &MainForm::scene_panel_Resize);
			this->scene_panel->Move += gcnew System::EventHandler(this, &MainForm::scene_panel_Move);
			this->scene_panel->MouseEnter += gcnew System::EventHandler(this, &MainForm::scene_panel_MouseEnter);
			// 
			// panel8
			// 
			this->panel8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel8->Controls->Add(this->mousePosZ);
			this->panel8->Controls->Add(this->label80);
			this->panel8->Controls->Add(this->mousePosY);
			this->panel8->Controls->Add(this->label82);
			this->panel8->Controls->Add(this->mousePosX);
			this->panel8->Controls->Add(this->label84);
			this->panel8->Controls->Add(this->label85);
			this->panel8->Controls->Add(this->label9);
			this->panel8->Controls->Add(this->button2);
			this->panel8->Controls->Add(this->camPosZ);
			this->panel8->Controls->Add(this->label22);
			this->panel8->Controls->Add(this->camPosY);
			this->panel8->Controls->Add(this->label20);
			this->panel8->Controls->Add(this->camPosX);
			this->panel8->Controls->Add(this->label16);
			this->panel8->Controls->Add(this->label14);
			this->panel8->Controls->Add(this->label2);
			this->panel8->Controls->Add(this->UtilType_Ctrl);
			this->panel8->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel8->Location = System::Drawing::Point(0, 684);
			this->panel8->Name = L"panel8";
			this->panel8->Size = System::Drawing::Size(926, 32);
			this->panel8->TabIndex = 1;
			// 
			// mousePosZ
			// 
			this->mousePosZ->AutoSize = true;
			this->mousePosZ->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->mousePosZ->Location = System::Drawing::Point(547, 7);
			this->mousePosZ->Name = L"mousePosZ";
			this->mousePosZ->Size = System::Drawing::Size(31, 14);
			this->mousePosZ->TabIndex = 18;
			this->mousePosZ->Text = L"0.00";
			// 
			// label80
			// 
			this->label80->AutoSize = true;
			this->label80->Location = System::Drawing::Point(529, 7);
			this->label80->Name = L"label80";
			this->label80->Size = System::Drawing::Size(17, 12);
			this->label80->TabIndex = 17;
			this->label80->Text = L"Z:";
			// 
			// mousePosY
			// 
			this->mousePosY->AutoSize = true;
			this->mousePosY->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->mousePosY->Location = System::Drawing::Point(494, 7);
			this->mousePosY->Name = L"mousePosY";
			this->mousePosY->Size = System::Drawing::Size(31, 14);
			this->mousePosY->TabIndex = 16;
			this->mousePosY->Text = L"0.00";
			// 
			// label82
			// 
			this->label82->AutoSize = true;
			this->label82->Location = System::Drawing::Point(477, 8);
			this->label82->Name = L"label82";
			this->label82->Size = System::Drawing::Size(17, 12);
			this->label82->TabIndex = 15;
			this->label82->Text = L"Y:";
			// 
			// mousePosX
			// 
			this->mousePosX->AutoSize = true;
			this->mousePosX->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->mousePosX->Location = System::Drawing::Point(446, 7);
			this->mousePosX->Name = L"mousePosX";
			this->mousePosX->Size = System::Drawing::Size(31, 14);
			this->mousePosX->TabIndex = 14;
			this->mousePosX->Text = L"0.00";
			// 
			// label84
			// 
			this->label84->AutoSize = true;
			this->label84->Location = System::Drawing::Point(428, 8);
			this->label84->Name = L"label84";
			this->label84->Size = System::Drawing::Size(17, 12);
			this->label84->TabIndex = 13;
			this->label84->Text = L"X:";
			// 
			// label85
			// 
			this->label85->AutoSize = true;
			this->label85->Location = System::Drawing::Point(356, 8);
			this->label85->Name = L"label85";
			this->label85->Size = System::Drawing::Size(71, 12);
			this->label85->TabIndex = 12;
			this->label85->Text = L"| 鼠标位置:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(816, 9);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(47, 12);
			this->label9->TabIndex = 11;
			this->label9->Text = L"| 所选:";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(870, 3);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(37, 23);
			this->button2->TabIndex = 10;
			this->button2->Text = L"贴地";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// camPosZ
			// 
			this->camPosZ->AutoSize = true;
			this->camPosZ->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->camPosZ->Location = System::Drawing::Point(784, 8);
			this->camPosZ->Name = L"camPosZ";
			this->camPosZ->Size = System::Drawing::Size(31, 14);
			this->camPosZ->TabIndex = 9;
			this->camPosZ->Text = L"0.00";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(766, 8);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(17, 12);
			this->label22->TabIndex = 8;
			this->label22->Text = L"Z:";
			// 
			// camPosY
			// 
			this->camPosY->AutoSize = true;
			this->camPosY->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->camPosY->Location = System::Drawing::Point(731, 8);
			this->camPosY->Name = L"camPosY";
			this->camPosY->Size = System::Drawing::Size(31, 14);
			this->camPosY->TabIndex = 7;
			this->camPosY->Text = L"0.00";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(714, 9);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(17, 12);
			this->label20->TabIndex = 6;
			this->label20->Text = L"Y:";
			// 
			// camPosX
			// 
			this->camPosX->AutoSize = true;
			this->camPosX->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->camPosX->Location = System::Drawing::Point(683, 8);
			this->camPosX->Name = L"camPosX";
			this->camPosX->Size = System::Drawing::Size(31, 14);
			this->camPosX->TabIndex = 5;
			this->camPosX->Text = L"0.00";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(665, 9);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(17, 12);
			this->label16->TabIndex = 4;
			this->label16->Text = L"X:";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(10, 11);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(59, 12);
			this->label14->TabIndex = 3;
			this->label14->Text = L"操作方式:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(579, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(83, 12);
			this->label2->TabIndex = 1;
			this->label2->Text = L"| 摄像机位置:";
			// 
			// UtilType_Ctrl
			// 
			this->UtilType_Ctrl->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->UtilType_Ctrl->Controls->Add(this->util_type_slg_page);
			this->UtilType_Ctrl->Controls->Add(this->util_type_move_page);
			this->UtilType_Ctrl->Controls->Add(this->util_type_rot_page);
			this->UtilType_Ctrl->Controls->Add(this->util_type_scale_page);
			this->UtilType_Ctrl->Location = System::Drawing::Point(75, 5);
			this->UtilType_Ctrl->Name = L"UtilType_Ctrl";
			this->UtilType_Ctrl->SelectedIndex = 0;
			this->UtilType_Ctrl->Size = System::Drawing::Size(223, 25);
			this->UtilType_Ctrl->TabIndex = 0;
			this->UtilType_Ctrl->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::UtilType_Ctrl_SelectedIndexChanged);
			// 
			// util_type_slg_page
			// 
			this->util_type_slg_page->Location = System::Drawing::Point(4, 24);
			this->util_type_slg_page->Name = L"util_type_slg_page";
			this->util_type_slg_page->Padding = System::Windows::Forms::Padding(3);
			this->util_type_slg_page->Size = System::Drawing::Size(215, 0);
			this->util_type_slg_page->TabIndex = 4;
			this->util_type_slg_page->Text = L"SLG";
			this->util_type_slg_page->UseVisualStyleBackColor = true;
			// 
			// util_type_move_page
			// 
			this->util_type_move_page->Location = System::Drawing::Point(4, 24);
			this->util_type_move_page->Name = L"util_type_move_page";
			this->util_type_move_page->Padding = System::Windows::Forms::Padding(3);
			this->util_type_move_page->Size = System::Drawing::Size(215, 0);
			this->util_type_move_page->TabIndex = 1;
			this->util_type_move_page->Text = L"位移";
			this->util_type_move_page->UseVisualStyleBackColor = true;
			// 
			// util_type_rot_page
			// 
			this->util_type_rot_page->Location = System::Drawing::Point(4, 24);
			this->util_type_rot_page->Name = L"util_type_rot_page";
			this->util_type_rot_page->Padding = System::Windows::Forms::Padding(3);
			this->util_type_rot_page->Size = System::Drawing::Size(215, 0);
			this->util_type_rot_page->TabIndex = 2;
			this->util_type_rot_page->Text = L"旋转";
			this->util_type_rot_page->UseVisualStyleBackColor = true;
			// 
			// util_type_scale_page
			// 
			this->util_type_scale_page->Location = System::Drawing::Point(4, 24);
			this->util_type_scale_page->Name = L"util_type_scale_page";
			this->util_type_scale_page->Padding = System::Windows::Forms::Padding(3);
			this->util_type_scale_page->Size = System::Drawing::Size(215, 0);
			this->util_type_scale_page->TabIndex = 3;
			this->util_type_scale_page->Text = L"缩放";
			this->util_type_scale_page->UseVisualStyleBackColor = true;
			// 
			// Prop_Panel
			// 
			this->Prop_Panel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Prop_Panel->Controls->Add(this->prop_tab_ctrl);
			this->Prop_Panel->Dock = System::Windows::Forms::DockStyle::Right;
			this->Prop_Panel->Location = System::Drawing::Point(930, 0);
			this->Prop_Panel->Name = L"Prop_Panel";
			this->Prop_Panel->Size = System::Drawing::Size(262, 720);
			this->Prop_Panel->TabIndex = 0;
			// 
			// prop_tab_ctrl
			// 
			this->prop_tab_ctrl->Controls->Add(this->elemet_page);
			this->prop_tab_ctrl->Controls->Add(this->terrain_page);
			this->prop_tab_ctrl->Controls->Add(this->setting_page);
			this->prop_tab_ctrl->Dock = System::Windows::Forms::DockStyle::Fill;
			this->prop_tab_ctrl->Location = System::Drawing::Point(0, 0);
			this->prop_tab_ctrl->Name = L"prop_tab_ctrl";
			this->prop_tab_ctrl->SelectedIndex = 0;
			this->prop_tab_ctrl->Size = System::Drawing::Size(258, 716);
			this->prop_tab_ctrl->TabIndex = 0;
			this->prop_tab_ctrl->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::prop_tab_ctrl_SelectedIndexChanged);
			// 
			// elemet_page
			// 
			this->elemet_page->Controls->Add(this->panel9);
			this->elemet_page->Location = System::Drawing::Point(4, 21);
			this->elemet_page->Name = L"elemet_page";
			this->elemet_page->Padding = System::Windows::Forms::Padding(3);
			this->elemet_page->Size = System::Drawing::Size(250, 691);
			this->elemet_page->TabIndex = 3;
			this->elemet_page->Text = L"元素";
			this->elemet_page->UseVisualStyleBackColor = true;
			// 
			// panel9
			// 
			this->panel9->BackColor = System::Drawing::SystemColors::Control;
			this->panel9->Controls->Add(this->element_tab);
			this->panel9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel9->Location = System::Drawing::Point(3, 3);
			this->panel9->Name = L"panel9";
			this->panel9->Size = System::Drawing::Size(244, 685);
			this->panel9->TabIndex = 1;
			// 
			// element_tab
			// 
			this->element_tab->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->element_tab->Controls->Add(this->createElment_page);
			this->element_tab->Controls->Add(this->elemet_prop_page);
			this->element_tab->Controls->Add(this->elemet_list_page);
			this->element_tab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->element_tab->Location = System::Drawing::Point(0, 0);
			this->element_tab->Name = L"element_tab";
			this->element_tab->SelectedIndex = 0;
			this->element_tab->Size = System::Drawing::Size(244, 685);
			this->element_tab->TabIndex = 0;
			this->element_tab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::element_tab_SelectedIndexChanged);
			// 
			// createElment_page
			// 
			this->createElment_page->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->createElment_page->Controls->Add(this->SelectCreateElementTypeTab);
			this->createElment_page->Location = System::Drawing::Point(4, 24);
			this->createElment_page->Name = L"createElment_page";
			this->createElment_page->Padding = System::Windows::Forms::Padding(3);
			this->createElment_page->Size = System::Drawing::Size(236, 657);
			this->createElment_page->TabIndex = 1;
			this->createElment_page->Text = L"新建";
			this->createElment_page->UseVisualStyleBackColor = true;
			// 
			// SelectCreateElementTypeTab
			// 
			this->SelectCreateElementTypeTab->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->SelectCreateElementTypeTab->Controls->Add(this->create_static_page);
			this->SelectCreateElementTypeTab->Controls->Add(this->create_tree_page);
			this->SelectCreateElementTypeTab->Controls->Add(this->create_effect_page);
			this->SelectCreateElementTypeTab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->SelectCreateElementTypeTab->Location = System::Drawing::Point(3, 3);
			this->SelectCreateElementTypeTab->Name = L"SelectCreateElementTypeTab";
			this->SelectCreateElementTypeTab->SelectedIndex = 0;
			this->SelectCreateElementTypeTab->Size = System::Drawing::Size(226, 647);
			this->SelectCreateElementTypeTab->TabIndex = 0;
			this->SelectCreateElementTypeTab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::SelectCreateElementTypeTab_SelectedIndexChanged);
			// 
			// create_static_page
			// 
			this->create_static_page->Controls->Add(this->panel11);
			this->create_static_page->Controls->Add(this->panel10);
			this->create_static_page->Location = System::Drawing::Point(4, 24);
			this->create_static_page->Name = L"create_static_page";
			this->create_static_page->Padding = System::Windows::Forms::Padding(3);
			this->create_static_page->Size = System::Drawing::Size(218, 619);
			this->create_static_page->TabIndex = 0;
			this->create_static_page->Text = L"模型";
			this->create_static_page->UseVisualStyleBackColor = true;
			// 
			// panel11
			// 
			this->panel11->Controls->Add(this->model_create_tree);
			this->panel11->Controls->Add(this->panel14);
			this->panel11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel11->Location = System::Drawing::Point(3, 38);
			this->panel11->Name = L"panel11";
			this->panel11->Size = System::Drawing::Size(212, 578);
			this->panel11->TabIndex = 1;
			// 
			// model_create_tree
			// 
			this->model_create_tree->AllowDrop = true;
			this->model_create_tree->Dock = System::Windows::Forms::DockStyle::Fill;
			this->model_create_tree->Location = System::Drawing::Point(0, 0);
			this->model_create_tree->Name = L"model_create_tree";
			this->model_create_tree->Size = System::Drawing::Size(212, 452);
			this->model_create_tree->TabIndex = 2;
			this->model_create_tree->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::element_create_tree_MouseDoubleClick);
			// 
			// panel14
			// 
			this->panel14->Controls->Add(this->num_create_batch);
			this->panel14->Controls->Add(this->cb_is_create_batch);
			this->panel14->Controls->Add(this->prepare_model_text);
			this->panel14->Controls->Add(this->label23);
			this->panel14->Controls->Add(this->button5);
			this->panel14->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel14->Location = System::Drawing::Point(0, 452);
			this->panel14->Name = L"panel14";
			this->panel14->Size = System::Drawing::Size(212, 126);
			this->panel14->TabIndex = 1;
			// 
			// num_create_batch
			// 
			this->num_create_batch->Location = System::Drawing::Point(174, 97);
			this->num_create_batch->Name = L"num_create_batch";
			this->num_create_batch->Size = System::Drawing::Size(30, 21);
			this->num_create_batch->TabIndex = 5;
			this->num_create_batch->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {7, 0, 0, 0});
			// 
			// cb_is_create_batch
			// 
			this->cb_is_create_batch->AutoSize = true;
			this->cb_is_create_batch->Location = System::Drawing::Point(14, 101);
			this->cb_is_create_batch->Name = L"cb_is_create_batch";
			this->cb_is_create_batch->Size = System::Drawing::Size(162, 16);
			this->cb_is_create_batch->TabIndex = 4;
			this->cb_is_create_batch->Text = L"测试批量创建 | 一边数量";
			this->cb_is_create_batch->UseVisualStyleBackColor = true;
			// 
			// prepare_model_text
			// 
			this->prepare_model_text->AutoEllipsis = true;
			this->prepare_model_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->prepare_model_text->Location = System::Drawing::Point(11, 33);
			this->prepare_model_text->Name = L"prepare_model_text";
			this->prepare_model_text->Size = System::Drawing::Size(193, 57);
			this->prepare_model_text->TabIndex = 3;
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(9, 9);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(83, 12);
			this->label23->TabIndex = 2;
			this->label23->Text = L"当前准备模型:";
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(167, 4);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(37, 23);
			this->button5->TabIndex = 1;
			this->button5->Text = L"取消";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MainForm::button5_Click);
			// 
			// panel10
			// 
			this->panel10->Controls->Add(this->button1);
			this->panel10->Controls->Add(this->textBox1);
			this->panel10->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel10->Location = System::Drawing::Point(3, 3);
			this->panel10->Name = L"panel10";
			this->panel10->Size = System::Drawing::Size(212, 35);
			this->panel10->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(167, 6);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(44, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"查询";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(11, 7);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(150, 21);
			this->textBox1->TabIndex = 1;
			// 
			// create_tree_page
			// 
			this->create_tree_page->Controls->Add(this->panel34);
			this->create_tree_page->Controls->Add(this->panel28);
			this->create_tree_page->Location = System::Drawing::Point(4, 24);
			this->create_tree_page->Name = L"create_tree_page";
			this->create_tree_page->Padding = System::Windows::Forms::Padding(3);
			this->create_tree_page->Size = System::Drawing::Size(218, 619);
			this->create_tree_page->TabIndex = 1;
			this->create_tree_page->Text = L"植被";
			this->create_tree_page->UseVisualStyleBackColor = true;
			// 
			// panel34
			// 
			this->panel34->Controls->Add(this->prepare_tree_text);
			this->panel34->Controls->Add(this->label70);
			this->panel34->Controls->Add(this->button17);
			this->panel34->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel34->Location = System::Drawing::Point(3, 534);
			this->panel34->Name = L"panel34";
			this->panel34->Size = System::Drawing::Size(212, 82);
			this->panel34->TabIndex = 2;
			// 
			// prepare_tree_text
			// 
			this->prepare_tree_text->AutoEllipsis = true;
			this->prepare_tree_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->prepare_tree_text->Location = System::Drawing::Point(10, 33);
			this->prepare_tree_text->Name = L"prepare_tree_text";
			this->prepare_tree_text->Size = System::Drawing::Size(193, 39);
			this->prepare_tree_text->TabIndex = 3;
			// 
			// label70
			// 
			this->label70->AutoSize = true;
			this->label70->Location = System::Drawing::Point(8, 12);
			this->label70->Name = L"label70";
			this->label70->Size = System::Drawing::Size(83, 12);
			this->label70->TabIndex = 2;
			this->label70->Text = L"当前准备植被:";
			// 
			// button17
			// 
			this->button17->Location = System::Drawing::Point(166, 7);
			this->button17->Name = L"button17";
			this->button17->Size = System::Drawing::Size(37, 23);
			this->button17->TabIndex = 1;
			this->button17->Text = L"取消";
			this->button17->UseVisualStyleBackColor = true;
			// 
			// panel28
			// 
			this->panel28->Controls->Add(this->tree_create_tree);
			this->panel28->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel28->Location = System::Drawing::Point(3, 3);
			this->panel28->Name = L"panel28";
			this->panel28->Size = System::Drawing::Size(212, 613);
			this->panel28->TabIndex = 0;
			// 
			// tree_create_tree
			// 
			this->tree_create_tree->AllowDrop = true;
			this->tree_create_tree->Dock = System::Windows::Forms::DockStyle::Top;
			this->tree_create_tree->Location = System::Drawing::Point(0, 0);
			this->tree_create_tree->Name = L"tree_create_tree";
			this->tree_create_tree->Size = System::Drawing::Size(212, 532);
			this->tree_create_tree->TabIndex = 3;
			this->tree_create_tree->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::tree_create_tree_MouseDoubleClick);
			// 
			// create_effect_page
			// 
			this->create_effect_page->Controls->Add(this->effect_create_tree);
			this->create_effect_page->Controls->Add(this->panel35);
			this->create_effect_page->Controls->Add(this->panel36);
			this->create_effect_page->Location = System::Drawing::Point(4, 24);
			this->create_effect_page->Name = L"create_effect_page";
			this->create_effect_page->Padding = System::Windows::Forms::Padding(3);
			this->create_effect_page->Size = System::Drawing::Size(218, 619);
			this->create_effect_page->TabIndex = 2;
			this->create_effect_page->Text = L"特效";
			this->create_effect_page->UseVisualStyleBackColor = true;
			// 
			// effect_create_tree
			// 
			this->effect_create_tree->AllowDrop = true;
			this->effect_create_tree->Dock = System::Windows::Forms::DockStyle::Fill;
			this->effect_create_tree->Location = System::Drawing::Point(3, 38);
			this->effect_create_tree->Name = L"effect_create_tree";
			this->effect_create_tree->Size = System::Drawing::Size(212, 452);
			this->effect_create_tree->TabIndex = 5;
			this->effect_create_tree->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::effect_create_tree_MouseDoubleClick);
			// 
			// panel35
			// 
			this->panel35->Controls->Add(this->button18);
			this->panel35->Controls->Add(this->textBox2);
			this->panel35->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel35->Location = System::Drawing::Point(3, 3);
			this->panel35->Name = L"panel35";
			this->panel35->Size = System::Drawing::Size(212, 35);
			this->panel35->TabIndex = 3;
			// 
			// button18
			// 
			this->button18->Location = System::Drawing::Point(167, 6);
			this->button18->Name = L"button18";
			this->button18->Size = System::Drawing::Size(44, 23);
			this->button18->TabIndex = 2;
			this->button18->Text = L"查询";
			this->button18->UseVisualStyleBackColor = true;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(11, 7);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(150, 21);
			this->textBox2->TabIndex = 1;
			// 
			// panel36
			// 
			this->panel36->Controls->Add(this->prepare_effect_text);
			this->panel36->Controls->Add(this->label73);
			this->panel36->Controls->Add(this->button19);
			this->panel36->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel36->Location = System::Drawing::Point(3, 490);
			this->panel36->Name = L"panel36";
			this->panel36->Size = System::Drawing::Size(212, 126);
			this->panel36->TabIndex = 4;
			// 
			// prepare_effect_text
			// 
			this->prepare_effect_text->AutoEllipsis = true;
			this->prepare_effect_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->prepare_effect_text->Location = System::Drawing::Point(11, 33);
			this->prepare_effect_text->Name = L"prepare_effect_text";
			this->prepare_effect_text->Size = System::Drawing::Size(193, 84);
			this->prepare_effect_text->TabIndex = 3;
			// 
			// label73
			// 
			this->label73->AutoSize = true;
			this->label73->Location = System::Drawing::Point(9, 9);
			this->label73->Name = L"label73";
			this->label73->Size = System::Drawing::Size(83, 12);
			this->label73->TabIndex = 2;
			this->label73->Text = L"当前准备特效:";
			// 
			// button19
			// 
			this->button19->Location = System::Drawing::Point(167, 4);
			this->button19->Name = L"button19";
			this->button19->Size = System::Drawing::Size(37, 23);
			this->button19->TabIndex = 1;
			this->button19->Text = L"取消";
			this->button19->UseVisualStyleBackColor = true;
			// 
			// elemet_prop_page
			// 
			this->elemet_prop_page->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->elemet_prop_page->Controls->Add(this->panel13);
			this->elemet_prop_page->Controls->Add(this->panel12);
			this->elemet_prop_page->Location = System::Drawing::Point(4, 24);
			this->elemet_prop_page->Name = L"elemet_prop_page";
			this->elemet_prop_page->Padding = System::Windows::Forms::Padding(3);
			this->elemet_prop_page->Size = System::Drawing::Size(236, 657);
			this->elemet_prop_page->TabIndex = 2;
			this->elemet_prop_page->Text = L"属性";
			this->elemet_prop_page->UseVisualStyleBackColor = true;
			// 
			// panel13
			// 
			this->panel13->Controls->Add(this->element_prop_grids);
			this->panel13->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel13->Location = System::Drawing::Point(3, 39);
			this->panel13->Name = L"panel13";
			this->panel13->Size = System::Drawing::Size(226, 611);
			this->panel13->TabIndex = 1;
			// 
			// element_prop_grids
			// 
			this->element_prop_grids->Dock = System::Windows::Forms::DockStyle::Fill;
			this->element_prop_grids->Location = System::Drawing::Point(0, 0);
			this->element_prop_grids->Name = L"element_prop_grids";
			this->element_prop_grids->PropertySort = System::Windows::Forms::PropertySort::NoSort;
			this->element_prop_grids->Size = System::Drawing::Size(226, 611);
			this->element_prop_grids->TabIndex = 0;
			this->element_prop_grids->PropertyValueChanged += gcnew System::Windows::Forms::PropertyValueChangedEventHandler(this, &MainForm::element_prop_grids_PropertyValueChanged);
			// 
			// panel12
			// 
			this->panel12->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel12->Location = System::Drawing::Point(3, 3);
			this->panel12->Name = L"panel12";
			this->panel12->Size = System::Drawing::Size(226, 36);
			this->panel12->TabIndex = 0;
			// 
			// elemet_list_page
			// 
			this->elemet_list_page->Controls->Add(this->element_list);
			this->elemet_list_page->Controls->Add(this->panel15);
			this->elemet_list_page->Controls->Add(this->panel16);
			this->elemet_list_page->Location = System::Drawing::Point(4, 24);
			this->elemet_list_page->Name = L"elemet_list_page";
			this->elemet_list_page->Padding = System::Windows::Forms::Padding(3);
			this->elemet_list_page->Size = System::Drawing::Size(236, 657);
			this->elemet_list_page->TabIndex = 3;
			this->elemet_list_page->Text = L"列表";
			this->elemet_list_page->UseVisualStyleBackColor = true;
			// 
			// element_list
			// 
			this->element_list->Dock = System::Windows::Forms::DockStyle::Fill;
			this->element_list->FullRowSelect = true;
			this->element_list->Location = System::Drawing::Point(3, 38);
			this->element_list->Name = L"element_list";
			this->element_list->Size = System::Drawing::Size(230, 582);
			this->element_list->TabIndex = 5;
			this->element_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::element_list_MouseDoubleClick);
			// 
			// panel15
			// 
			this->panel15->Controls->Add(this->button4);
			this->panel15->Controls->Add(this->button6);
			this->panel15->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel15->Location = System::Drawing::Point(3, 620);
			this->panel15->Name = L"panel15";
			this->panel15->Size = System::Drawing::Size(230, 34);
			this->panel15->TabIndex = 4;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(151, 6);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 0;
			this->button4->Text = L"删除";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4_Click_1);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(58, 6);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(75, 23);
			this->button6->TabIndex = 1;
			this->button6->Text = L"刷新";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MainForm::button6_Click);
			// 
			// panel16
			// 
			this->panel16->Controls->Add(this->button3);
			this->panel16->Controls->Add(this->textBox3);
			this->panel16->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel16->Location = System::Drawing::Point(3, 3);
			this->panel16->Name = L"panel16";
			this->panel16->Size = System::Drawing::Size(230, 35);
			this->panel16->TabIndex = 2;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(184, 5);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(44, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"查询";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(18, 7);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(150, 21);
			this->textBox3->TabIndex = 1;
			// 
			// terrain_page
			// 
			this->terrain_page->Controls->Add(this->panel2);
			this->terrain_page->Controls->Add(this->panel1);
			this->terrain_page->Location = System::Drawing::Point(4, 21);
			this->terrain_page->Name = L"terrain_page";
			this->terrain_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_page->Size = System::Drawing::Size(250, 691);
			this->terrain_page->TabIndex = 1;
			this->terrain_page->Text = L"地形";
			this->terrain_page->UseVisualStyleBackColor = true;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->terrainTab);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel2->Location = System::Drawing::Point(3, 270);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(244, 418);
			this->panel2->TabIndex = 1;
			// 
			// terrainTab
			// 
			this->terrainTab->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->terrainTab->Controls->Add(this->terrain_base_page);
			this->terrainTab->Controls->Add(this->terrain_vertex_page);
			this->terrainTab->Controls->Add(this->terrain_texture_page);
			this->terrainTab->Controls->Add(this->terrain_plant_page);
			this->terrainTab->Controls->Add(this->terrain_cliff_page);
			this->terrainTab->Controls->Add(this->terrain_water_page);
			this->terrainTab->Controls->Add(this->terrain_region_page);
			this->terrainTab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->terrainTab->Location = System::Drawing::Point(0, 0);
			this->terrainTab->Name = L"terrainTab";
			this->terrainTab->Padding = System::Drawing::Point(0, 0);
			this->terrainTab->SelectedIndex = 0;
			this->terrainTab->Size = System::Drawing::Size(244, 418);
			this->terrainTab->TabIndex = 0;
			this->terrainTab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::terrainTab_SelectedIndexChanged);
			// 
			// terrain_base_page
			// 
			this->terrain_base_page->Controls->Add(this->button21);
			this->terrain_base_page->Controls->Add(this->button_ClipMap);
			this->terrain_base_page->Location = System::Drawing::Point(4, 24);
			this->terrain_base_page->Name = L"terrain_base_page";
			this->terrain_base_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_base_page->Size = System::Drawing::Size(236, 390);
			this->terrain_base_page->TabIndex = 0;
			this->terrain_base_page->Text = L"基础";
			this->terrain_base_page->UseVisualStyleBackColor = true;
			// 
			// button21
			// 
			this->button21->Enabled = false;
			this->button21->Location = System::Drawing::Point(22, 21);
			this->button21->Name = L"button21";
			this->button21->Size = System::Drawing::Size(75, 23);
			this->button21->TabIndex = 1;
			this->button21->Text = L"重排序贴图";
			this->button21->UseVisualStyleBackColor = true;
			this->button21->Click += gcnew System::EventHandler(this, &MainForm::button21_Click);
			// 
			// button_ClipMap
			// 
			this->button_ClipMap->Enabled = false;
			this->button_ClipMap->Location = System::Drawing::Point(144, 21);
			this->button_ClipMap->Name = L"button_ClipMap";
			this->button_ClipMap->Size = System::Drawing::Size(75, 23);
			this->button_ClipMap->TabIndex = 0;
			this->button_ClipMap->Text = L"裁剪地图";
			this->button_ClipMap->UseVisualStyleBackColor = true;
			this->button_ClipMap->Click += gcnew System::EventHandler(this, &MainForm::button_ClipMap_Click);
			// 
			// terrain_vertex_page
			// 
			this->terrain_vertex_page->Controls->Add(this->panel4);
			this->terrain_vertex_page->Controls->Add(this->panel3);
			this->terrain_vertex_page->Location = System::Drawing::Point(4, 24);
			this->terrain_vertex_page->Name = L"terrain_vertex_page";
			this->terrain_vertex_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_vertex_page->Size = System::Drawing::Size(236, 390);
			this->terrain_vertex_page->TabIndex = 1;
			this->terrain_vertex_page->Text = L"高度";
			this->terrain_vertex_page->UseVisualStyleBackColor = true;
			// 
			// panel4
			// 
			this->panel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel4->Location = System::Drawing::Point(3, 265);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(230, 122);
			this->panel4->TabIndex = 1;
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->terrainHeightTab);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel3->Location = System::Drawing::Point(3, 3);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(230, 262);
			this->panel3->TabIndex = 0;
			// 
			// terrainHeightTab
			// 
			this->terrainHeightTab->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->terrainHeightTab->Controls->Add(this->terrain_height_level_page);
			this->terrainHeightTab->Controls->Add(this->terrain_height_uniform_page);
			this->terrainHeightTab->Controls->Add(this->terrain_height_noise_page);
			this->terrainHeightTab->Controls->Add(this->terrain_height_flat_page);
			this->terrainHeightTab->ImageList = this->imageList2;
			this->terrainHeightTab->ItemSize = System::Drawing::Size(48, 36);
			this->terrainHeightTab->Location = System::Drawing::Point(11, 11);
			this->terrainHeightTab->Margin = System::Windows::Forms::Padding(0);
			this->terrainHeightTab->Multiline = true;
			this->terrainHeightTab->Name = L"terrainHeightTab";
			this->terrainHeightTab->Padding = System::Drawing::Point(1, 1);
			this->terrainHeightTab->SelectedIndex = 0;
			this->terrainHeightTab->Size = System::Drawing::Size(208, 233);
			this->terrainHeightTab->TabIndex = 1;
			this->terrainHeightTab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::terrainHeightTab_SelectedIndexChanged);
			// 
			// terrain_height_level_page
			// 
			this->terrain_height_level_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_height_level_page->Controls->Add(this->terrain_height_level_range_text);
			this->terrain_height_level_page->Controls->Add(this->terrain_height_level_range_tb);
			this->terrain_height_level_page->Controls->Add(this->label6);
			this->terrain_height_level_page->ImageIndex = 2;
			this->terrain_height_level_page->Location = System::Drawing::Point(4, 40);
			this->terrain_height_level_page->Name = L"terrain_height_level_page";
			this->terrain_height_level_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_height_level_page->Size = System::Drawing::Size(200, 189);
			this->terrain_height_level_page->TabIndex = 0;
			this->terrain_height_level_page->ToolTipText = L"升高";
			// 
			// terrain_height_level_range_text
			// 
			this->terrain_height_level_range_text->AutoSize = true;
			this->terrain_height_level_range_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->terrain_height_level_range_text->Location = System::Drawing::Point(58, 9);
			this->terrain_height_level_range_text->Name = L"terrain_height_level_range_text";
			this->terrain_height_level_range_text->Size = System::Drawing::Size(25, 14);
			this->terrain_height_level_range_text->TabIndex = 8;
			this->terrain_height_level_range_text->Text = L"1.0";
			// 
			// terrain_height_level_range_tb
			// 
			this->terrain_height_level_range_tb->Location = System::Drawing::Point(12, 26);
			this->terrain_height_level_range_tb->Maximum = 19;
			this->terrain_height_level_range_tb->Name = L"terrain_height_level_range_tb";
			this->terrain_height_level_range_tb->Size = System::Drawing::Size(161, 45);
			this->terrain_height_level_range_tb->TabIndex = 7;
			this->terrain_height_level_range_tb->Value = 1;
			this->terrain_height_level_range_tb->ValueChanged += gcnew System::EventHandler(this, &MainForm::terrain_height_level_range_tb_ValueChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(17, 9);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(35, 12);
			this->label6->TabIndex = 6;
			this->label6->Text = L"幅度:";
			// 
			// terrain_height_uniform_page
			// 
			this->terrain_height_uniform_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_height_uniform_page->ImageIndex = 3;
			this->terrain_height_uniform_page->Location = System::Drawing::Point(4, 40);
			this->terrain_height_uniform_page->Name = L"terrain_height_uniform_page";
			this->terrain_height_uniform_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_height_uniform_page->Size = System::Drawing::Size(200, 189);
			this->terrain_height_uniform_page->TabIndex = 2;
			this->terrain_height_uniform_page->ToolTipText = L"统一";
			// 
			// terrain_height_noise_page
			// 
			this->terrain_height_noise_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_height_noise_page->Controls->Add(this->terrain_height_noise_range_text);
			this->terrain_height_noise_page->Controls->Add(this->terrain_height_noise_range_tb);
			this->terrain_height_noise_page->Controls->Add(this->label10);
			this->terrain_height_noise_page->ImageIndex = 4;
			this->terrain_height_noise_page->Location = System::Drawing::Point(4, 40);
			this->terrain_height_noise_page->Name = L"terrain_height_noise_page";
			this->terrain_height_noise_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_height_noise_page->Size = System::Drawing::Size(200, 189);
			this->terrain_height_noise_page->TabIndex = 3;
			this->terrain_height_noise_page->ToolTipText = L"噪度";
			// 
			// terrain_height_noise_range_text
			// 
			this->terrain_height_noise_range_text->AutoSize = true;
			this->terrain_height_noise_range_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->terrain_height_noise_range_text->Location = System::Drawing::Point(58, 9);
			this->terrain_height_noise_range_text->Name = L"terrain_height_noise_range_text";
			this->terrain_height_noise_range_text->Size = System::Drawing::Size(25, 14);
			this->terrain_height_noise_range_text->TabIndex = 11;
			this->terrain_height_noise_range_text->Text = L"2.0";
			// 
			// terrain_height_noise_range_tb
			// 
			this->terrain_height_noise_range_tb->Location = System::Drawing::Point(13, 28);
			this->terrain_height_noise_range_tb->Maximum = 19;
			this->terrain_height_noise_range_tb->Name = L"terrain_height_noise_range_tb";
			this->terrain_height_noise_range_tb->Size = System::Drawing::Size(161, 45);
			this->terrain_height_noise_range_tb->TabIndex = 10;
			this->terrain_height_noise_range_tb->Value = 2;
			this->terrain_height_noise_range_tb->ValueChanged += gcnew System::EventHandler(this, &MainForm::terrain_height_noise_range_tb_ValueChanged);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(17, 9);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(35, 12);
			this->label10->TabIndex = 9;
			this->label10->Text = L"幅度:";
			// 
			// terrain_height_flat_page
			// 
			this->terrain_height_flat_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_height_flat_page->Controls->Add(this->terrain_height_smooth_range_text);
			this->terrain_height_flat_page->Controls->Add(this->terrain_height_smooth_range_tb);
			this->terrain_height_flat_page->Controls->Add(this->label12);
			this->terrain_height_flat_page->ImageIndex = 1;
			this->terrain_height_flat_page->Location = System::Drawing::Point(4, 40);
			this->terrain_height_flat_page->Name = L"terrain_height_flat_page";
			this->terrain_height_flat_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_height_flat_page->Size = System::Drawing::Size(200, 189);
			this->terrain_height_flat_page->TabIndex = 4;
			this->terrain_height_flat_page->ToolTipText = L"平滑";
			// 
			// terrain_height_smooth_range_text
			// 
			this->terrain_height_smooth_range_text->AutoSize = true;
			this->terrain_height_smooth_range_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->terrain_height_smooth_range_text->Location = System::Drawing::Point(58, 9);
			this->terrain_height_smooth_range_text->Name = L"terrain_height_smooth_range_text";
			this->terrain_height_smooth_range_text->Size = System::Drawing::Size(31, 14);
			this->terrain_height_smooth_range_text->TabIndex = 11;
			this->terrain_height_smooth_range_text->Text = L"0.20";
			// 
			// terrain_height_smooth_range_tb
			// 
			this->terrain_height_smooth_range_tb->Location = System::Drawing::Point(13, 28);
			this->terrain_height_smooth_range_tb->Maximum = 99;
			this->terrain_height_smooth_range_tb->Name = L"terrain_height_smooth_range_tb";
			this->terrain_height_smooth_range_tb->Size = System::Drawing::Size(161, 45);
			this->terrain_height_smooth_range_tb->TabIndex = 10;
			this->terrain_height_smooth_range_tb->Value = 19;
			this->terrain_height_smooth_range_tb->ValueChanged += gcnew System::EventHandler(this, &MainForm::trackBar4_ValueChanged);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(17, 9);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(35, 12);
			this->label12->TabIndex = 9;
			this->label12->Text = L"幅度:";
			// 
			// imageList2
			// 
			this->imageList2->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList2.ImageStream")));
			this->imageList2->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList2->Images->SetKeyName(0, L"高度-降低.png");
			this->imageList2->Images->SetKeyName(1, L"高度-平滑.png");
			this->imageList2->Images->SetKeyName(2, L"高度-升高.png");
			this->imageList2->Images->SetKeyName(3, L"高度-统一.png");
			this->imageList2->Images->SetKeyName(4, L"高度-噪音.png");
			this->imageList2->Images->SetKeyName(5, L"纹理-模糊.png");
			this->imageList2->Images->SetKeyName(6, L"纹理-抹除.png");
			this->imageList2->Images->SetKeyName(7, L"纹理-添加.png");
			this->imageList2->Images->SetKeyName(8, L"纹理-统一.png");
			this->imageList2->Images->SetKeyName(9, L"纹理-移除.png");
			// 
			// terrain_texture_page
			// 
			this->terrain_texture_page->Controls->Add(this->panel6);
			this->terrain_texture_page->Controls->Add(this->panel5);
			this->terrain_texture_page->Location = System::Drawing::Point(4, 24);
			this->terrain_texture_page->Name = L"terrain_texture_page";
			this->terrain_texture_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_texture_page->Size = System::Drawing::Size(236, 390);
			this->terrain_texture_page->TabIndex = 2;
			this->terrain_texture_page->Text = L"纹理";
			this->terrain_texture_page->UseVisualStyleBackColor = true;
			// 
			// panel6
			// 
			this->panel6->Controls->Add(this->terrain_texture_pic_tab);
			this->panel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel6->Location = System::Drawing::Point(3, 144);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(230, 243);
			this->panel6->TabIndex = 1;
			// 
			// terrain_texture_pic_tab
			// 
			this->terrain_texture_pic_tab->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->terrain_texture_pic_tab->Controls->Add(this->terrain_tex_0);
			this->terrain_texture_pic_tab->Controls->Add(this->terrain_tex_1);
			this->terrain_texture_pic_tab->Controls->Add(this->terrain_tex_2);
			this->terrain_texture_pic_tab->Controls->Add(this->terrain_tex_3);
			this->terrain_texture_pic_tab->Controls->Add(this->terrain_tex_4);
			this->terrain_texture_pic_tab->Controls->Add(this->terrain_tex_5);
			this->terrain_texture_pic_tab->Controls->Add(this->terrain_tex_6);
			this->terrain_texture_pic_tab->Controls->Add(this->terrain_tex_7);
			this->terrain_texture_pic_tab->ImageList = this->terrain_texture_pic_list;
			this->terrain_texture_pic_tab->ItemSize = System::Drawing::Size(48, 36);
			this->terrain_texture_pic_tab->Location = System::Drawing::Point(29, 4);
			this->terrain_texture_pic_tab->Margin = System::Windows::Forms::Padding(0);
			this->terrain_texture_pic_tab->Multiline = true;
			this->terrain_texture_pic_tab->Name = L"terrain_texture_pic_tab";
			this->terrain_texture_pic_tab->Padding = System::Drawing::Point(1, 1);
			this->terrain_texture_pic_tab->SelectedIndex = 0;
			this->terrain_texture_pic_tab->Size = System::Drawing::Size(173, 92);
			this->terrain_texture_pic_tab->TabIndex = 3;
			this->terrain_texture_pic_tab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::terrain_texture_pic_tab_SelectedIndexChanged);
			// 
			// terrain_tex_0
			// 
			this->terrain_tex_0->BackColor = System::Drawing::Color::Transparent;
			this->terrain_tex_0->ImageIndex = 0;
			this->terrain_tex_0->Location = System::Drawing::Point(4, 79);
			this->terrain_tex_0->Name = L"terrain_tex_0";
			this->terrain_tex_0->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_0->Size = System::Drawing::Size(165, 9);
			this->terrain_tex_0->TabIndex = 0;
			this->terrain_tex_0->UseVisualStyleBackColor = true;
			// 
			// terrain_tex_1
			// 
			this->terrain_tex_1->BackColor = System::Drawing::Color::Transparent;
			this->terrain_tex_1->ImageIndex = 1;
			this->terrain_tex_1->Location = System::Drawing::Point(4, 79);
			this->terrain_tex_1->Name = L"terrain_tex_1";
			this->terrain_tex_1->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_1->Size = System::Drawing::Size(165, 9);
			this->terrain_tex_1->TabIndex = 1;
			this->terrain_tex_1->UseVisualStyleBackColor = true;
			// 
			// terrain_tex_2
			// 
			this->terrain_tex_2->BackColor = System::Drawing::Color::Transparent;
			this->terrain_tex_2->ImageIndex = 2;
			this->terrain_tex_2->Location = System::Drawing::Point(4, 79);
			this->terrain_tex_2->Name = L"terrain_tex_2";
			this->terrain_tex_2->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_2->Size = System::Drawing::Size(165, 9);
			this->terrain_tex_2->TabIndex = 2;
			this->terrain_tex_2->UseVisualStyleBackColor = true;
			// 
			// terrain_tex_3
			// 
			this->terrain_tex_3->BackColor = System::Drawing::Color::Transparent;
			this->terrain_tex_3->ImageIndex = 3;
			this->terrain_tex_3->Location = System::Drawing::Point(4, 79);
			this->terrain_tex_3->Name = L"terrain_tex_3";
			this->terrain_tex_3->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_3->Size = System::Drawing::Size(165, 9);
			this->terrain_tex_3->TabIndex = 3;
			this->terrain_tex_3->UseVisualStyleBackColor = true;
			// 
			// terrain_tex_4
			// 
			this->terrain_tex_4->BackColor = System::Drawing::Color::Transparent;
			this->terrain_tex_4->ImageIndex = 4;
			this->terrain_tex_4->Location = System::Drawing::Point(4, 79);
			this->terrain_tex_4->Name = L"terrain_tex_4";
			this->terrain_tex_4->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_4->Size = System::Drawing::Size(165, 9);
			this->terrain_tex_4->TabIndex = 4;
			this->terrain_tex_4->UseVisualStyleBackColor = true;
			// 
			// terrain_tex_5
			// 
			this->terrain_tex_5->ImageIndex = 5;
			this->terrain_tex_5->Location = System::Drawing::Point(4, 79);
			this->terrain_tex_5->Name = L"terrain_tex_5";
			this->terrain_tex_5->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_5->Size = System::Drawing::Size(165, 9);
			this->terrain_tex_5->TabIndex = 5;
			this->terrain_tex_5->UseVisualStyleBackColor = true;
			// 
			// terrain_tex_6
			// 
			this->terrain_tex_6->ImageIndex = 6;
			this->terrain_tex_6->Location = System::Drawing::Point(4, 79);
			this->terrain_tex_6->Name = L"terrain_tex_6";
			this->terrain_tex_6->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_6->Size = System::Drawing::Size(165, 9);
			this->terrain_tex_6->TabIndex = 6;
			this->terrain_tex_6->UseVisualStyleBackColor = true;
			// 
			// terrain_tex_7
			// 
			this->terrain_tex_7->ImageIndex = 7;
			this->terrain_tex_7->Location = System::Drawing::Point(4, 79);
			this->terrain_tex_7->Name = L"terrain_tex_7";
			this->terrain_tex_7->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_7->Size = System::Drawing::Size(165, 9);
			this->terrain_tex_7->TabIndex = 7;
			this->terrain_tex_7->UseVisualStyleBackColor = true;
			// 
			// terrain_texture_pic_list
			// 
			this->terrain_texture_pic_list->ColorDepth = System::Windows::Forms::ColorDepth::Depth32Bit;
			this->terrain_texture_pic_list->ImageSize = System::Drawing::Size(30, 30);
			this->terrain_texture_pic_list->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// panel5
			// 
			this->panel5->Controls->Add(this->terrainTextureTab);
			this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel5->Location = System::Drawing::Point(3, 3);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(230, 141);
			this->panel5->TabIndex = 0;
			// 
			// terrainTextureTab
			// 
			this->terrainTextureTab->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->terrainTextureTab->Controls->Add(this->terrain_tex_add_page);
			this->terrainTextureTab->Controls->Add(this->terrain_tex_remove_page);
			this->terrainTextureTab->Controls->Add(this->terrain_tex_uniform_page);
			this->terrainTextureTab->Controls->Add(this->terrain_tex_mop_page);
			this->terrainTextureTab->Controls->Add(this->terrain_tex_blur_page);
			this->terrainTextureTab->ImageList = this->imageList2;
			this->terrainTextureTab->ItemSize = System::Drawing::Size(48, 36);
			this->terrainTextureTab->Location = System::Drawing::Point(11, 11);
			this->terrainTextureTab->Margin = System::Windows::Forms::Padding(0);
			this->terrainTextureTab->Multiline = true;
			this->terrainTextureTab->Name = L"terrainTextureTab";
			this->terrainTextureTab->Padding = System::Drawing::Point(1, 1);
			this->terrainTextureTab->SelectedIndex = 0;
			this->terrainTextureTab->Size = System::Drawing::Size(208, 119);
			this->terrainTextureTab->TabIndex = 2;
			this->terrainTextureTab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::terrainTextureTab_SelectedIndexChanged);
			// 
			// terrain_tex_add_page
			// 
			this->terrain_tex_add_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_tex_add_page->Controls->Add(this->terrain_tex_add_text);
			this->terrain_tex_add_page->Controls->Add(this->terrain_tex_add_tb);
			this->terrain_tex_add_page->Controls->Add(this->label7);
			this->terrain_tex_add_page->ImageIndex = 7;
			this->terrain_tex_add_page->Location = System::Drawing::Point(4, 40);
			this->terrain_tex_add_page->Name = L"terrain_tex_add_page";
			this->terrain_tex_add_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_add_page->Size = System::Drawing::Size(200, 75);
			this->terrain_tex_add_page->TabIndex = 0;
			this->terrain_tex_add_page->ToolTipText = L"添加纹理";
			this->terrain_tex_add_page->UseVisualStyleBackColor = true;
			// 
			// terrain_tex_add_text
			// 
			this->terrain_tex_add_text->AutoSize = true;
			this->terrain_tex_add_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->terrain_tex_add_text->Location = System::Drawing::Point(58, 9);
			this->terrain_tex_add_text->Name = L"terrain_tex_add_text";
			this->terrain_tex_add_text->Size = System::Drawing::Size(25, 14);
			this->terrain_tex_add_text->TabIndex = 8;
			this->terrain_tex_add_text->Text = L"100";
			// 
			// terrain_tex_add_tb
			// 
			this->terrain_tex_add_tb->Location = System::Drawing::Point(13, 28);
			this->terrain_tex_add_tb->Maximum = 255;
			this->terrain_tex_add_tb->Name = L"terrain_tex_add_tb";
			this->terrain_tex_add_tb->Size = System::Drawing::Size(161, 45);
			this->terrain_tex_add_tb->TabIndex = 7;
			this->terrain_tex_add_tb->Value = 100;
			this->terrain_tex_add_tb->ValueChanged += gcnew System::EventHandler(this, &MainForm::terrain_tex_add_tb_ValueChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(17, 9);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(35, 12);
			this->label7->TabIndex = 6;
			this->label7->Text = L"幅度:";
			// 
			// terrain_tex_remove_page
			// 
			this->terrain_tex_remove_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_tex_remove_page->Controls->Add(this->terrain_tex_remove_text);
			this->terrain_tex_remove_page->Controls->Add(this->terrain_tex_remove_tb);
			this->terrain_tex_remove_page->Controls->Add(this->label13);
			this->terrain_tex_remove_page->ImageIndex = 9;
			this->terrain_tex_remove_page->Location = System::Drawing::Point(4, 40);
			this->terrain_tex_remove_page->Name = L"terrain_tex_remove_page";
			this->terrain_tex_remove_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_remove_page->Size = System::Drawing::Size(200, 75);
			this->terrain_tex_remove_page->TabIndex = 1;
			this->terrain_tex_remove_page->ToolTipText = L"移除纹理";
			this->terrain_tex_remove_page->UseVisualStyleBackColor = true;
			// 
			// terrain_tex_remove_text
			// 
			this->terrain_tex_remove_text->AutoSize = true;
			this->terrain_tex_remove_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->terrain_tex_remove_text->Location = System::Drawing::Point(58, 9);
			this->terrain_tex_remove_text->Name = L"terrain_tex_remove_text";
			this->terrain_tex_remove_text->Size = System::Drawing::Size(19, 14);
			this->terrain_tex_remove_text->TabIndex = 11;
			this->terrain_tex_remove_text->Text = L"10";
			// 
			// terrain_tex_remove_tb
			// 
			this->terrain_tex_remove_tb->BackColor = System::Drawing::SystemColors::Control;
			this->terrain_tex_remove_tb->Location = System::Drawing::Point(13, 28);
			this->terrain_tex_remove_tb->Maximum = 255;
			this->terrain_tex_remove_tb->Name = L"terrain_tex_remove_tb";
			this->terrain_tex_remove_tb->Size = System::Drawing::Size(161, 45);
			this->terrain_tex_remove_tb->TabIndex = 100;
			this->terrain_tex_remove_tb->Value = 4;
			this->terrain_tex_remove_tb->ValueChanged += gcnew System::EventHandler(this, &MainForm::terrain_tex_remove_tb_ValueChanged);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(17, 9);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(35, 12);
			this->label13->TabIndex = 9;
			this->label13->Text = L"幅度:";
			// 
			// terrain_tex_uniform_page
			// 
			this->terrain_tex_uniform_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_tex_uniform_page->ImageIndex = 8;
			this->terrain_tex_uniform_page->Location = System::Drawing::Point(4, 40);
			this->terrain_tex_uniform_page->Name = L"terrain_tex_uniform_page";
			this->terrain_tex_uniform_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_uniform_page->Size = System::Drawing::Size(200, 75);
			this->terrain_tex_uniform_page->TabIndex = 2;
			this->terrain_tex_uniform_page->ToolTipText = L"统一纹理";
			this->terrain_tex_uniform_page->UseVisualStyleBackColor = true;
			// 
			// terrain_tex_mop_page
			// 
			this->terrain_tex_mop_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_tex_mop_page->Controls->Add(this->terrain_tex_mop_text);
			this->terrain_tex_mop_page->Controls->Add(this->terrain_tex_mop_tb);
			this->terrain_tex_mop_page->Controls->Add(this->label15);
			this->terrain_tex_mop_page->ImageIndex = 6;
			this->terrain_tex_mop_page->Location = System::Drawing::Point(4, 40);
			this->terrain_tex_mop_page->Name = L"terrain_tex_mop_page";
			this->terrain_tex_mop_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_mop_page->Size = System::Drawing::Size(200, 75);
			this->terrain_tex_mop_page->TabIndex = 3;
			this->terrain_tex_mop_page->ToolTipText = L"涂抹纹理";
			this->terrain_tex_mop_page->UseVisualStyleBackColor = true;
			// 
			// terrain_tex_mop_text
			// 
			this->terrain_tex_mop_text->AutoSize = true;
			this->terrain_tex_mop_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->terrain_tex_mop_text->Location = System::Drawing::Point(58, 9);
			this->terrain_tex_mop_text->Name = L"terrain_tex_mop_text";
			this->terrain_tex_mop_text->Size = System::Drawing::Size(19, 14);
			this->terrain_tex_mop_text->TabIndex = 11;
			this->terrain_tex_mop_text->Text = L"10";
			// 
			// terrain_tex_mop_tb
			// 
			this->terrain_tex_mop_tb->Location = System::Drawing::Point(13, 28);
			this->terrain_tex_mop_tb->Name = L"terrain_tex_mop_tb";
			this->terrain_tex_mop_tb->Size = System::Drawing::Size(161, 45);
			this->terrain_tex_mop_tb->TabIndex = 10;
			this->terrain_tex_mop_tb->ValueChanged += gcnew System::EventHandler(this, &MainForm::terrain_tex_mop_tb_ValueChanged);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(17, 9);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(35, 12);
			this->label15->TabIndex = 9;
			this->label15->Text = L"幅度:";
			// 
			// terrain_tex_blur_page
			// 
			this->terrain_tex_blur_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_tex_blur_page->Controls->Add(this->terrain_tex_blur_text);
			this->terrain_tex_blur_page->Controls->Add(this->terrain_tex_blur_tb);
			this->terrain_tex_blur_page->Controls->Add(this->label17);
			this->terrain_tex_blur_page->ImageIndex = 5;
			this->terrain_tex_blur_page->Location = System::Drawing::Point(4, 40);
			this->terrain_tex_blur_page->Name = L"terrain_tex_blur_page";
			this->terrain_tex_blur_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_tex_blur_page->Size = System::Drawing::Size(200, 75);
			this->terrain_tex_blur_page->TabIndex = 4;
			this->terrain_tex_blur_page->ToolTipText = L"模糊纹理";
			this->terrain_tex_blur_page->UseVisualStyleBackColor = true;
			// 
			// terrain_tex_blur_text
			// 
			this->terrain_tex_blur_text->AutoSize = true;
			this->terrain_tex_blur_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->terrain_tex_blur_text->Location = System::Drawing::Point(58, 9);
			this->terrain_tex_blur_text->Name = L"terrain_tex_blur_text";
			this->terrain_tex_blur_text->Size = System::Drawing::Size(19, 14);
			this->terrain_tex_blur_text->TabIndex = 11;
			this->terrain_tex_blur_text->Text = L"10";
			// 
			// terrain_tex_blur_tb
			// 
			this->terrain_tex_blur_tb->Location = System::Drawing::Point(13, 28);
			this->terrain_tex_blur_tb->Name = L"terrain_tex_blur_tb";
			this->terrain_tex_blur_tb->Size = System::Drawing::Size(161, 45);
			this->terrain_tex_blur_tb->TabIndex = 10;
			this->terrain_tex_blur_tb->ValueChanged += gcnew System::EventHandler(this, &MainForm::terrain_tex_blur_tb_ValueChanged);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(17, 9);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(35, 12);
			this->label17->TabIndex = 9;
			this->label17->Text = L"幅度:";
			// 
			// terrain_plant_page
			// 
			this->terrain_plant_page->Controls->Add(this->panel18);
			this->terrain_plant_page->Controls->Add(this->plantTab);
			this->terrain_plant_page->Location = System::Drawing::Point(4, 24);
			this->terrain_plant_page->Name = L"terrain_plant_page";
			this->terrain_plant_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_plant_page->Size = System::Drawing::Size(236, 390);
			this->terrain_plant_page->TabIndex = 3;
			this->terrain_plant_page->Text = L"植被";
			this->terrain_plant_page->UseVisualStyleBackColor = true;
			// 
			// panel18
			// 
			this->panel18->Controls->Add(this->lable_batch_curr_sel);
			this->panel18->Controls->Add(this->lable_terrain_batch_sel);
			this->panel18->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel18->Location = System::Drawing::Point(3, 361);
			this->panel18->Name = L"panel18";
			this->panel18->Size = System::Drawing::Size(230, 26);
			this->panel18->TabIndex = 3;
			// 
			// lable_batch_curr_sel
			// 
			this->lable_batch_curr_sel->AutoSize = true;
			this->lable_batch_curr_sel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->lable_batch_curr_sel->Location = System::Drawing::Point(61, 4);
			this->lable_batch_curr_sel->Name = L"lable_batch_curr_sel";
			this->lable_batch_curr_sel->Size = System::Drawing::Size(2, 14);
			this->lable_batch_curr_sel->TabIndex = 10;
			// 
			// lable_terrain_batch_sel
			// 
			this->lable_terrain_batch_sel->AutoSize = true;
			this->lable_terrain_batch_sel->Location = System::Drawing::Point(4, 6);
			this->lable_terrain_batch_sel->Name = L"lable_terrain_batch_sel";
			this->lable_terrain_batch_sel->Size = System::Drawing::Size(59, 12);
			this->lable_terrain_batch_sel->TabIndex = 0;
			this->lable_terrain_batch_sel->Text = L"当前选中:";
			// 
			// plantTab
			// 
			this->plantTab->Controls->Add(this->plant_tree_page);
			this->plantTab->Controls->Add(this->plant_grass_page);
			this->plantTab->Controls->Add(this->plant_create_page);
			this->plantTab->Controls->Add(this->plant_set_page);
			this->plantTab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->plantTab->Location = System::Drawing::Point(3, 3);
			this->plantTab->Name = L"plantTab";
			this->plantTab->SelectedIndex = 0;
			this->plantTab->Size = System::Drawing::Size(230, 384);
			this->plantTab->TabIndex = 5;
			// 
			// plant_tree_page
			// 
			this->plant_tree_page->BackColor = System::Drawing::SystemColors::Control;
			this->plant_tree_page->Controls->Add(this->listView_terrain_batch_tree_list);
			this->plant_tree_page->Location = System::Drawing::Point(4, 21);
			this->plant_tree_page->Name = L"plant_tree_page";
			this->plant_tree_page->Padding = System::Windows::Forms::Padding(3);
			this->plant_tree_page->Size = System::Drawing::Size(222, 359);
			this->plant_tree_page->TabIndex = 3;
			this->plant_tree_page->Text = L"树";
			// 
			// listView_terrain_batch_tree_list
			// 
			this->listView_terrain_batch_tree_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->columnHeader1, 
				this->columnHeader2, this->columnHeader3});
			this->listView_terrain_batch_tree_list->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listView_terrain_batch_tree_list->FullRowSelect = true;
			this->listView_terrain_batch_tree_list->GridLines = true;
			this->listView_terrain_batch_tree_list->Location = System::Drawing::Point(3, 3);
			this->listView_terrain_batch_tree_list->MultiSelect = false;
			this->listView_terrain_batch_tree_list->Name = L"listView_terrain_batch_tree_list";
			this->listView_terrain_batch_tree_list->Size = System::Drawing::Size(216, 353);
			this->listView_terrain_batch_tree_list->TabIndex = 5;
			this->listView_terrain_batch_tree_list->UseCompatibleStateImageBehavior = false;
			this->listView_terrain_batch_tree_list->View = System::Windows::Forms::View::Details;
			this->listView_terrain_batch_tree_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::listView_terrain_batch_tree_list_MouseDoubleClick);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"序号";
			this->columnHeader1->Width = 49;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"名字";
			this->columnHeader2->Width = 64;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"模型ID";
			this->columnHeader3->Width = 51;
			// 
			// plant_grass_page
			// 
			this->plant_grass_page->BackColor = System::Drawing::SystemColors::Control;
			this->plant_grass_page->Controls->Add(this->listView_terrain_batch_grass_list);
			this->plant_grass_page->Location = System::Drawing::Point(4, 21);
			this->plant_grass_page->Name = L"plant_grass_page";
			this->plant_grass_page->Padding = System::Windows::Forms::Padding(3);
			this->plant_grass_page->Size = System::Drawing::Size(222, 359);
			this->plant_grass_page->TabIndex = 4;
			this->plant_grass_page->Text = L"草";
			// 
			// listView_terrain_batch_grass_list
			// 
			this->listView_terrain_batch_grass_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {this->columnHeader4, 
				this->columnHeader5, this->columnHeader6});
			this->listView_terrain_batch_grass_list->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listView_terrain_batch_grass_list->FullRowSelect = true;
			this->listView_terrain_batch_grass_list->GridLines = true;
			this->listView_terrain_batch_grass_list->Location = System::Drawing::Point(3, 3);
			this->listView_terrain_batch_grass_list->MultiSelect = false;
			this->listView_terrain_batch_grass_list->Name = L"listView_terrain_batch_grass_list";
			this->listView_terrain_batch_grass_list->Size = System::Drawing::Size(216, 353);
			this->listView_terrain_batch_grass_list->TabIndex = 5;
			this->listView_terrain_batch_grass_list->UseCompatibleStateImageBehavior = false;
			this->listView_terrain_batch_grass_list->View = System::Windows::Forms::View::Details;
			this->listView_terrain_batch_grass_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::listView_terrain_batch_grass_list_MouseDoubleClick);
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"序号";
			this->columnHeader4->Width = 49;
			// 
			// columnHeader5
			// 
			this->columnHeader5->Text = L"名字";
			this->columnHeader5->Width = 64;
			// 
			// columnHeader6
			// 
			this->columnHeader6->Text = L"模型ID";
			this->columnHeader6->Width = 51;
			// 
			// plant_create_page
			// 
			this->plant_create_page->BackColor = System::Drawing::SystemColors::Control;
			this->plant_create_page->Controls->Add(this->panel17);
			this->plant_create_page->Location = System::Drawing::Point(4, 21);
			this->plant_create_page->Name = L"plant_create_page";
			this->plant_create_page->Padding = System::Windows::Forms::Padding(3);
			this->plant_create_page->Size = System::Drawing::Size(222, 359);
			this->plant_create_page->TabIndex = 1;
			this->plant_create_page->Text = L"铺设";
			// 
			// panel17
			// 
			this->panel17->Controls->Add(this->panel24);
			this->panel17->Controls->Add(this->panel25);
			this->panel17->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel17->Location = System::Drawing::Point(3, 3);
			this->panel17->Name = L"panel17";
			this->panel17->Size = System::Drawing::Size(216, 353);
			this->panel17->TabIndex = 2;
			// 
			// panel24
			// 
			this->panel24->Controls->Add(this->plantBatchEntityTab);
			this->panel24->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel24->Location = System::Drawing::Point(0, 95);
			this->panel24->Name = L"panel24";
			this->panel24->Size = System::Drawing::Size(216, 258);
			this->panel24->TabIndex = 6;
			// 
			// plantBatchEntityTab
			// 
			this->plantBatchEntityTab->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->plantBatchEntityTab->Controls->Add(this->terrain_batch_add_page);
			this->plantBatchEntityTab->Controls->Add(this->terrain_batch_remove_page);
			this->plantBatchEntityTab->Controls->Add(this->terrain_batch_noise_page);
			this->plantBatchEntityTab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->plantBatchEntityTab->ImageList = this->imageList2;
			this->plantBatchEntityTab->ItemSize = System::Drawing::Size(48, 36);
			this->plantBatchEntityTab->Location = System::Drawing::Point(0, 0);
			this->plantBatchEntityTab->Margin = System::Windows::Forms::Padding(0);
			this->plantBatchEntityTab->Multiline = true;
			this->plantBatchEntityTab->Name = L"plantBatchEntityTab";
			this->plantBatchEntityTab->Padding = System::Drawing::Point(1, 1);
			this->plantBatchEntityTab->SelectedIndex = 0;
			this->plantBatchEntityTab->Size = System::Drawing::Size(216, 258);
			this->plantBatchEntityTab->TabIndex = 4;
			this->plantBatchEntityTab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::plantBatchEntityTab_SelectIndexChanged);
			// 
			// terrain_batch_add_page
			// 
			this->terrain_batch_add_page->AutoScroll = true;
			this->terrain_batch_add_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_batch_add_page->Controls->Add(this->groupBox37);
			this->terrain_batch_add_page->Controls->Add(this->plant_create_align_checkbox);
			this->terrain_batch_add_page->Controls->Add(this->label112);
			this->terrain_batch_add_page->Controls->Add(this->TextBox_Plant_MaxScale);
			this->terrain_batch_add_page->Controls->Add(this->label111);
			this->terrain_batch_add_page->Controls->Add(this->TextBox_Plant_MinScale);
			this->terrain_batch_add_page->Controls->Add(this->label110);
			this->terrain_batch_add_page->Controls->Add(this->plant_create_scale_offset_bar);
			this->terrain_batch_add_page->Controls->Add(this->label19);
			this->terrain_batch_add_page->Controls->Add(this->label51);
			this->terrain_batch_add_page->Controls->Add(this->label40);
			this->terrain_batch_add_page->Controls->Add(this->label39);
			this->terrain_batch_add_page->Controls->Add(this->plant_create_scale_offset_label);
			this->terrain_batch_add_page->Controls->Add(this->plant_create_treeDis_label);
			this->terrain_batch_add_page->Controls->Add(this->plant_create_clumping_bar);
			this->terrain_batch_add_page->Controls->Add(this->plant_create_treeDis_bar);
			this->terrain_batch_add_page->Controls->Add(this->plant_create_GrassDis_label);
			this->terrain_batch_add_page->ImageIndex = 7;
			this->terrain_batch_add_page->Location = System::Drawing::Point(4, 40);
			this->terrain_batch_add_page->Name = L"terrain_batch_add_page";
			this->terrain_batch_add_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_batch_add_page->Size = System::Drawing::Size(208, 214);
			this->terrain_batch_add_page->TabIndex = 0;
			this->terrain_batch_add_page->ToolTipText = L"添加纹理";
			this->terrain_batch_add_page->UseVisualStyleBackColor = true;
			// 
			// groupBox37
			// 
			this->groupBox37->Controls->Add(this->plant_create_ditribute_colum);
			this->groupBox37->Controls->Add(this->plant_create_ditribute_circle);
			this->groupBox37->Location = System::Drawing::Point(6, 176);
			this->groupBox37->Name = L"groupBox37";
			this->groupBox37->Size = System::Drawing::Size(188, 55);
			this->groupBox37->TabIndex = 5;
			this->groupBox37->TabStop = false;
			this->groupBox37->Text = L"分布方式";
			// 
			// plant_create_ditribute_colum
			// 
			this->plant_create_ditribute_colum->AutoSize = true;
			this->plant_create_ditribute_colum->Checked = true;
			this->plant_create_ditribute_colum->Location = System::Drawing::Point(11, 20);
			this->plant_create_ditribute_colum->Name = L"plant_create_ditribute_colum";
			this->plant_create_ditribute_colum->Size = System::Drawing::Size(47, 16);
			this->plant_create_ditribute_colum->TabIndex = 6;
			this->plant_create_ditribute_colum->TabStop = true;
			this->plant_create_ditribute_colum->Text = L"横竖";
			this->plant_create_ditribute_colum->UseVisualStyleBackColor = true;
			this->plant_create_ditribute_colum->Click += gcnew System::EventHandler(this, &MainForm::plant_create_ditribute_colum_Click);
			// 
			// plant_create_ditribute_circle
			// 
			this->plant_create_ditribute_circle->AutoSize = true;
			this->plant_create_ditribute_circle->Location = System::Drawing::Point(71, 20);
			this->plant_create_ditribute_circle->Name = L"plant_create_ditribute_circle";
			this->plant_create_ditribute_circle->Size = System::Drawing::Size(47, 16);
			this->plant_create_ditribute_circle->TabIndex = 5;
			this->plant_create_ditribute_circle->Text = L"圆形";
			this->plant_create_ditribute_circle->UseVisualStyleBackColor = true;
			this->plant_create_ditribute_circle->Click += gcnew System::EventHandler(this, &MainForm::plant_create_ditribute_circle_Click);
			// 
			// plant_create_align_checkbox
			// 
			this->plant_create_align_checkbox->AutoSize = true;
			this->plant_create_align_checkbox->Checked = true;
			this->plant_create_align_checkbox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->plant_create_align_checkbox->Location = System::Drawing::Point(9, 84);
			this->plant_create_align_checkbox->Name = L"plant_create_align_checkbox";
			this->plant_create_align_checkbox->Size = System::Drawing::Size(48, 16);
			this->plant_create_align_checkbox->TabIndex = 28;
			this->plant_create_align_checkbox->Text = L"对齐";
			this->plant_create_align_checkbox->UseVisualStyleBackColor = true;
			this->plant_create_align_checkbox->Click += gcnew System::EventHandler(this, &MainForm::plant_create_align_checkbox_Click);
			// 
			// label112
			// 
			this->label112->AutoSize = true;
			this->label112->Location = System::Drawing::Point(7, 154);
			this->label112->Name = L"label112";
			this->label112->Size = System::Drawing::Size(53, 12);
			this->label112->TabIndex = 27;
			this->label112->Text = L"缩放倍数";
			// 
			// TextBox_Plant_MaxScale
			// 
			this->TextBox_Plant_MaxScale->Location = System::Drawing::Point(159, 150);
			this->TextBox_Plant_MaxScale->Name = L"TextBox_Plant_MaxScale";
			this->TextBox_Plant_MaxScale->Size = System::Drawing::Size(33, 21);
			this->TextBox_Plant_MaxScale->TabIndex = 26;
			this->TextBox_Plant_MaxScale->Text = L"1.5";
			this->TextBox_Plant_MaxScale->Validated += gcnew System::EventHandler(this, &MainForm::TextBox_Plant_MaxScale_Validated);
			// 
			// label111
			// 
			this->label111->AutoSize = true;
			this->label111->Location = System::Drawing::Point(134, 154);
			this->label111->Name = L"label111";
			this->label111->Size = System::Drawing::Size(23, 12);
			this->label111->TabIndex = 25;
			this->label111->Text = L"max";
			// 
			// TextBox_Plant_MinScale
			// 
			this->TextBox_Plant_MinScale->Location = System::Drawing::Point(91, 150);
			this->TextBox_Plant_MinScale->Name = L"TextBox_Plant_MinScale";
			this->TextBox_Plant_MinScale->Size = System::Drawing::Size(36, 21);
			this->TextBox_Plant_MinScale->TabIndex = 24;
			this->TextBox_Plant_MinScale->Text = L"0.5";
			this->TextBox_Plant_MinScale->Validated += gcnew System::EventHandler(this, &MainForm::TextBox_Plant_MinScale_Validated);
			// 
			// label110
			// 
			this->label110->AutoSize = true;
			this->label110->Location = System::Drawing::Point(64, 154);
			this->label110->Name = L"label110";
			this->label110->Size = System::Drawing::Size(23, 12);
			this->label110->TabIndex = 23;
			this->label110->Text = L"min";
			// 
			// plant_create_scale_offset_bar
			// 
			this->plant_create_scale_offset_bar->Enabled = false;
			this->plant_create_scale_offset_bar->Location = System::Drawing::Point(42, 99);
			this->plant_create_scale_offset_bar->Maximum = 9;
			this->plant_create_scale_offset_bar->Name = L"plant_create_scale_offset_bar";
			this->plant_create_scale_offset_bar->Size = System::Drawing::Size(160, 45);
			this->plant_create_scale_offset_bar->TabIndex = 14;
			this->plant_create_scale_offset_bar->Value = 3;
			this->plant_create_scale_offset_bar->ValueChanged += gcnew System::EventHandler(this, &MainForm::plant_property_ValueChanged);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(7, 104);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(29, 12);
			this->label19->TabIndex = 21;
			this->label19->Text = L"偏移";
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->Location = System::Drawing::Point(7, 47);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(29, 12);
			this->label51->TabIndex = 19;
			this->label51->Text = L"草距";
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(7, 8);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(29, 12);
			this->label40->TabIndex = 17;
			this->label40->Text = L"树距";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(14, 16);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(0, 12);
			this->label39->TabIndex = 16;
			// 
			// plant_create_scale_offset_label
			// 
			this->plant_create_scale_offset_label->AutoSize = true;
			this->plant_create_scale_offset_label->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->plant_create_scale_offset_label->Location = System::Drawing::Point(9, 119);
			this->plant_create_scale_offset_label->Name = L"plant_create_scale_offset_label";
			this->plant_create_scale_offset_label->Size = System::Drawing::Size(25, 14);
			this->plant_create_scale_offset_label->TabIndex = 15;
			this->plant_create_scale_offset_label->Text = L"0.3";
			// 
			// plant_create_treeDis_label
			// 
			this->plant_create_treeDis_label->AutoSize = true;
			this->plant_create_treeDis_label->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->plant_create_treeDis_label->Location = System::Drawing::Point(9, 23);
			this->plant_create_treeDis_label->Name = L"plant_create_treeDis_label";
			this->plant_create_treeDis_label->Size = System::Drawing::Size(19, 14);
			this->plant_create_treeDis_label->TabIndex = 11;
			this->plant_create_treeDis_label->Text = L"10";
			// 
			// plant_create_clumping_bar
			// 
			this->plant_create_clumping_bar->BackColor = System::Drawing::SystemColors::Control;
			this->plant_create_clumping_bar->Location = System::Drawing::Point(42, 42);
			this->plant_create_clumping_bar->Maximum = 100;
			this->plant_create_clumping_bar->Name = L"plant_create_clumping_bar";
			this->plant_create_clumping_bar->Size = System::Drawing::Size(160, 45);
			this->plant_create_clumping_bar->TabIndex = 13;
			this->plant_create_clumping_bar->Value = 10;
			this->plant_create_clumping_bar->ValueChanged += gcnew System::EventHandler(this, &MainForm::plant_property_ValueChanged);
			// 
			// plant_create_treeDis_bar
			// 
			this->plant_create_treeDis_bar->Location = System::Drawing::Point(42, 3);
			this->plant_create_treeDis_bar->Maximum = 250;
			this->plant_create_treeDis_bar->Minimum = 100;
			this->plant_create_treeDis_bar->Name = L"plant_create_treeDis_bar";
			this->plant_create_treeDis_bar->Size = System::Drawing::Size(161, 45);
			this->plant_create_treeDis_bar->SmallChange = 10;
			this->plant_create_treeDis_bar->TabIndex = 10;
			this->plant_create_treeDis_bar->TickFrequency = 10;
			this->plant_create_treeDis_bar->Value = 100;
			this->plant_create_treeDis_bar->ValueChanged += gcnew System::EventHandler(this, &MainForm::plant_property_ValueChanged);
			// 
			// plant_create_GrassDis_label
			// 
			this->plant_create_GrassDis_label->AutoSize = true;
			this->plant_create_GrassDis_label->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->plant_create_GrassDis_label->Location = System::Drawing::Point(9, 62);
			this->plant_create_GrassDis_label->Name = L"plant_create_GrassDis_label";
			this->plant_create_GrassDis_label->Size = System::Drawing::Size(25, 14);
			this->plant_create_GrassDis_label->TabIndex = 12;
			this->plant_create_GrassDis_label->Text = L"1.0";
			// 
			// terrain_batch_remove_page
			// 
			this->terrain_batch_remove_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_batch_remove_page->ImageIndex = 9;
			this->terrain_batch_remove_page->Location = System::Drawing::Point(4, 40);
			this->terrain_batch_remove_page->Name = L"terrain_batch_remove_page";
			this->terrain_batch_remove_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_batch_remove_page->Size = System::Drawing::Size(208, 214);
			this->terrain_batch_remove_page->TabIndex = 1;
			this->terrain_batch_remove_page->ToolTipText = L"移除纹理";
			this->terrain_batch_remove_page->UseVisualStyleBackColor = true;
			// 
			// terrain_batch_noise_page
			// 
			this->terrain_batch_noise_page->ImageIndex = 8;
			this->terrain_batch_noise_page->Location = System::Drawing::Point(4, 40);
			this->terrain_batch_noise_page->Name = L"terrain_batch_noise_page";
			this->terrain_batch_noise_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_batch_noise_page->Size = System::Drawing::Size(208, 214);
			this->terrain_batch_noise_page->TabIndex = 2;
			this->terrain_batch_noise_page->UseVisualStyleBackColor = true;
			// 
			// panel25
			// 
			this->panel25->Controls->Add(this->groupBox21);
			this->panel25->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel25->Location = System::Drawing::Point(0, 0);
			this->panel25->Name = L"panel25";
			this->panel25->Size = System::Drawing::Size(216, 95);
			this->panel25->TabIndex = 5;
			// 
			// groupBox21
			// 
			this->groupBox21->Controls->Add(this->plant_batch_define_button);
			this->groupBox21->Controls->Add(this->specialize_batch_textBox);
			this->groupBox21->Controls->Add(this->specialize_batch_radioButton);
			this->groupBox21->Controls->Add(this->region_batch_radioButton);
			this->groupBox21->Controls->Add(this->common_batch_radioButton);
			this->groupBox21->Location = System::Drawing::Point(4, 3);
			this->groupBox21->Name = L"groupBox21";
			this->groupBox21->Size = System::Drawing::Size(205, 86);
			this->groupBox21->TabIndex = 2;
			this->groupBox21->TabStop = false;
			this->groupBox21->Text = L"批次渲染类型";
			// 
			// plant_batch_define_button
			// 
			this->plant_batch_define_button->Location = System::Drawing::Point(147, 57);
			this->plant_batch_define_button->Name = L"plant_batch_define_button";
			this->plant_batch_define_button->Size = System::Drawing::Size(47, 23);
			this->plant_batch_define_button->TabIndex = 4;
			this->plant_batch_define_button->Text = L"锁定";
			this->plant_batch_define_button->UseVisualStyleBackColor = true;
			this->plant_batch_define_button->Click += gcnew System::EventHandler(this, &MainForm::plant_batch_define_button_MouseClick);
			// 
			// specialize_batch_textBox
			// 
			this->specialize_batch_textBox->Location = System::Drawing::Point(73, 59);
			this->specialize_batch_textBox->Name = L"specialize_batch_textBox";
			this->specialize_batch_textBox->Size = System::Drawing::Size(68, 21);
			this->specialize_batch_textBox->TabIndex = 3;
			// 
			// specialize_batch_radioButton
			// 
			this->specialize_batch_radioButton->AutoSize = true;
			this->specialize_batch_radioButton->Location = System::Drawing::Point(8, 64);
			this->specialize_batch_radioButton->Name = L"specialize_batch_radioButton";
			this->specialize_batch_radioButton->Size = System::Drawing::Size(59, 16);
			this->specialize_batch_radioButton->TabIndex = 2;
			this->specialize_batch_radioButton->TabStop = true;
			this->specialize_batch_radioButton->Text = L"自定义";
			this->specialize_batch_radioButton->UseVisualStyleBackColor = true;
			this->specialize_batch_radioButton->CheckedChanged += gcnew System::EventHandler(this, &MainForm::batch_type_radioIndexChange);
			// 
			// region_batch_radioButton
			// 
			this->region_batch_radioButton->AutoSize = true;
			this->region_batch_radioButton->Location = System::Drawing::Point(8, 42);
			this->region_batch_radioButton->Name = L"region_batch_radioButton";
			this->region_batch_radioButton->Size = System::Drawing::Size(47, 16);
			this->region_batch_radioButton->TabIndex = 1;
			this->region_batch_radioButton->TabStop = true;
			this->region_batch_radioButton->Text = L"区域";
			this->region_batch_radioButton->UseVisualStyleBackColor = true;
			this->region_batch_radioButton->CheckedChanged += gcnew System::EventHandler(this, &MainForm::batch_type_radioIndexChange);
			// 
			// common_batch_radioButton
			// 
			this->common_batch_radioButton->AutoSize = true;
			this->common_batch_radioButton->Checked = true;
			this->common_batch_radioButton->Location = System::Drawing::Point(8, 20);
			this->common_batch_radioButton->Name = L"common_batch_radioButton";
			this->common_batch_radioButton->Size = System::Drawing::Size(47, 16);
			this->common_batch_radioButton->TabIndex = 0;
			this->common_batch_radioButton->TabStop = true;
			this->common_batch_radioButton->Text = L"普通";
			this->common_batch_radioButton->UseVisualStyleBackColor = true;
			this->common_batch_radioButton->CheckedChanged += gcnew System::EventHandler(this, &MainForm::batch_type_radioIndexChange);
			// 
			// plant_set_page
			// 
			this->plant_set_page->BackColor = System::Drawing::SystemColors::Control;
			this->plant_set_page->Location = System::Drawing::Point(4, 21);
			this->plant_set_page->Name = L"plant_set_page";
			this->plant_set_page->Padding = System::Windows::Forms::Padding(3);
			this->plant_set_page->Size = System::Drawing::Size(222, 359);
			this->plant_set_page->TabIndex = 2;
			this->plant_set_page->Text = L"设置";
			// 
			// terrain_cliff_page
			// 
			this->terrain_cliff_page->Location = System::Drawing::Point(4, 24);
			this->terrain_cliff_page->Name = L"terrain_cliff_page";
			this->terrain_cliff_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_cliff_page->Size = System::Drawing::Size(236, 390);
			this->terrain_cliff_page->TabIndex = 4;
			this->terrain_cliff_page->Text = L"悬崖";
			this->terrain_cliff_page->UseVisualStyleBackColor = true;
			// 
			// terrain_water_page
			// 
			this->terrain_water_page->Controls->Add(this->panel23);
			this->terrain_water_page->Controls->Add(this->panel30);
			this->terrain_water_page->Location = System::Drawing::Point(4, 24);
			this->terrain_water_page->Name = L"terrain_water_page";
			this->terrain_water_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_water_page->Size = System::Drawing::Size(236, 390);
			this->terrain_water_page->TabIndex = 5;
			this->terrain_water_page->Text = L"水";
			this->terrain_water_page->UseVisualStyleBackColor = true;
			// 
			// panel23
			// 
			this->panel23->Controls->Add(this->waterTab);
			this->panel23->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel23->Location = System::Drawing::Point(3, 3);
			this->panel23->Name = L"panel23";
			this->panel23->Size = System::Drawing::Size(230, 339);
			this->panel23->TabIndex = 5;
			// 
			// waterTab
			// 
			this->waterTab->Controls->Add(this->water_group_page);
			this->waterTab->Controls->Add(this->water_visible_page);
			this->waterTab->Controls->Add(this->water_height_page);
			this->waterTab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->waterTab->Location = System::Drawing::Point(0, 0);
			this->waterTab->Name = L"waterTab";
			this->waterTab->SelectedIndex = 0;
			this->waterTab->Size = System::Drawing::Size(230, 339);
			this->waterTab->TabIndex = 6;
			this->waterTab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::waterTab_SelectedIndexChanged);
			// 
			// water_group_page
			// 
			this->water_group_page->BackColor = System::Drawing::SystemColors::Control;
			this->water_group_page->Controls->Add(this->panel31);
			this->water_group_page->Location = System::Drawing::Point(4, 21);
			this->water_group_page->Name = L"water_group_page";
			this->water_group_page->Padding = System::Windows::Forms::Padding(3);
			this->water_group_page->Size = System::Drawing::Size(222, 314);
			this->water_group_page->TabIndex = 0;
			this->water_group_page->Text = L"材质";
			// 
			// panel31
			// 
			this->panel31->Controls->Add(this->water_mat_tab);
			this->panel31->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel31->Location = System::Drawing::Point(3, 3);
			this->panel31->Name = L"panel31";
			this->panel31->Size = System::Drawing::Size(216, 308);
			this->panel31->TabIndex = 1;
			// 
			// water_mat_tab
			// 
			this->water_mat_tab->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->water_mat_tab->Controls->Add(this->water_template_page);
			this->water_mat_tab->Controls->Add(this->tabPage15);
			this->water_mat_tab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->water_mat_tab->Location = System::Drawing::Point(0, 0);
			this->water_mat_tab->Name = L"water_mat_tab";
			this->water_mat_tab->SelectedIndex = 0;
			this->water_mat_tab->Size = System::Drawing::Size(216, 308);
			this->water_mat_tab->TabIndex = 0;
			// 
			// water_template_page
			// 
			this->water_template_page->BackColor = System::Drawing::SystemColors::Control;
			this->water_template_page->Controls->Add(this->panel32);
			this->water_template_page->Location = System::Drawing::Point(4, 24);
			this->water_template_page->Name = L"water_template_page";
			this->water_template_page->Padding = System::Windows::Forms::Padding(3);
			this->water_template_page->Size = System::Drawing::Size(208, 280);
			this->water_template_page->TabIndex = 0;
			this->water_template_page->Text = L"模板";
			// 
			// panel32
			// 
			this->panel32->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel32->Controls->Add(this->button12);
			this->panel32->Controls->Add(this->water_mat_template_list);
			this->panel32->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel32->Location = System::Drawing::Point(3, 3);
			this->panel32->Name = L"panel32";
			this->panel32->Size = System::Drawing::Size(202, 274);
			this->panel32->TabIndex = 2;
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(11, 247);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(175, 23);
			this->button12->TabIndex = 7;
			this->button12->Text = L"增加到材质组";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &MainForm::button12_Click);
			// 
			// water_mat_template_list
			// 
			this->water_mat_template_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->columnHeader_water_template_list_index, 
				this->columnHeader_water_template_list_name});
			this->water_mat_template_list->Dock = System::Windows::Forms::DockStyle::Top;
			this->water_mat_template_list->FullRowSelect = true;
			this->water_mat_template_list->GridLines = true;
			this->water_mat_template_list->Location = System::Drawing::Point(0, 0);
			this->water_mat_template_list->MultiSelect = false;
			this->water_mat_template_list->Name = L"water_mat_template_list";
			this->water_mat_template_list->Size = System::Drawing::Size(198, 241);
			this->water_mat_template_list->TabIndex = 6;
			this->water_mat_template_list->UseCompatibleStateImageBehavior = false;
			this->water_mat_template_list->View = System::Windows::Forms::View::Details;
			this->water_mat_template_list->DoubleClick += gcnew System::EventHandler(this, &MainForm::water_mat_template_list_DoubleClick);
			// 
			// columnHeader_water_template_list_index
			// 
			this->columnHeader_water_template_list_index->Text = L"序号";
			this->columnHeader_water_template_list_index->Width = 49;
			// 
			// columnHeader_water_template_list_name
			// 
			this->columnHeader_water_template_list_name->Text = L"名字";
			this->columnHeader_water_template_list_name->Width = 80;
			// 
			// tabPage15
			// 
			this->tabPage15->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage15->Controls->Add(this->panel33);
			this->tabPage15->Controls->Add(this->panel29);
			this->tabPage15->Location = System::Drawing::Point(4, 24);
			this->tabPage15->Name = L"tabPage15";
			this->tabPage15->Padding = System::Windows::Forms::Padding(3);
			this->tabPage15->Size = System::Drawing::Size(208, 280);
			this->tabPage15->TabIndex = 1;
			this->tabPage15->Text = L"材质组";
			// 
			// panel33
			// 
			this->panel33->Controls->Add(this->water_group_apply_btn);
			this->panel33->Controls->Add(this->groupBox25);
			this->panel33->Controls->Add(this->groupBox26);
			this->panel33->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel33->Location = System::Drawing::Point(3, 90);
			this->panel33->Name = L"panel33";
			this->panel33->Size = System::Drawing::Size(202, 187);
			this->panel33->TabIndex = 2;
			// 
			// water_group_apply_btn
			// 
			this->water_group_apply_btn->Location = System::Drawing::Point(17, 158);
			this->water_group_apply_btn->Name = L"water_group_apply_btn";
			this->water_group_apply_btn->Size = System::Drawing::Size(169, 23);
			this->water_group_apply_btn->TabIndex = 5;
			this->water_group_apply_btn->Text = L"响应";
			this->water_group_apply_btn->UseVisualStyleBackColor = true;
			this->water_group_apply_btn->Click += gcnew System::EventHandler(this, &MainForm::water_group_apply_btn_Click);
			// 
			// groupBox25
			// 
			this->groupBox25->Controls->Add(this->label41);
			this->groupBox25->Controls->Add(this->water_dirZ_txt);
			this->groupBox25->Controls->Add(this->label42);
			this->groupBox25->Controls->Add(this->water_dirY_txt);
			this->groupBox25->Controls->Add(this->label43);
			this->groupBox25->Controls->Add(this->water_dirX_txt);
			this->groupBox25->Location = System::Drawing::Point(17, 68);
			this->groupBox25->Name = L"groupBox25";
			this->groupBox25->Size = System::Drawing::Size(169, 50);
			this->groupBox25->TabIndex = 4;
			this->groupBox25->TabStop = false;
			this->groupBox25->Text = L"水平面方向";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(110, 21);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(17, 12);
			this->label41->TabIndex = 5;
			this->label41->Text = L"z:";
			// 
			// water_dirZ_txt
			// 
			this->water_dirZ_txt->Location = System::Drawing::Point(130, 18);
			this->water_dirZ_txt->Name = L"water_dirZ_txt";
			this->water_dirZ_txt->Size = System::Drawing::Size(31, 21);
			this->water_dirZ_txt->TabIndex = 4;
			this->water_dirZ_txt->Text = L"0";
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Location = System::Drawing::Point(60, 21);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(17, 12);
			this->label42->TabIndex = 3;
			this->label42->Text = L"y:";
			// 
			// water_dirY_txt
			// 
			this->water_dirY_txt->Location = System::Drawing::Point(78, 18);
			this->water_dirY_txt->Name = L"water_dirY_txt";
			this->water_dirY_txt->Size = System::Drawing::Size(32, 21);
			this->water_dirY_txt->TabIndex = 2;
			this->water_dirY_txt->Text = L"1";
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Location = System::Drawing::Point(7, 21);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(17, 12);
			this->label43->TabIndex = 1;
			this->label43->Text = L"x:";
			// 
			// water_dirX_txt
			// 
			this->water_dirX_txt->Location = System::Drawing::Point(25, 18);
			this->water_dirX_txt->Name = L"water_dirX_txt";
			this->water_dirX_txt->Size = System::Drawing::Size(32, 21);
			this->water_dirX_txt->TabIndex = 0;
			this->water_dirX_txt->Text = L"0";
			// 
			// groupBox26
			// 
			this->groupBox26->Controls->Add(this->label44);
			this->groupBox26->Controls->Add(this->water_posZ_txt);
			this->groupBox26->Controls->Add(this->label45);
			this->groupBox26->Controls->Add(this->water_posY_txt);
			this->groupBox26->Controls->Add(this->label47);
			this->groupBox26->Controls->Add(this->water_posX_txt);
			this->groupBox26->Location = System::Drawing::Point(17, 6);
			this->groupBox26->Name = L"groupBox26";
			this->groupBox26->Size = System::Drawing::Size(169, 50);
			this->groupBox26->TabIndex = 3;
			this->groupBox26->TabStop = false;
			this->groupBox26->Text = L"水平面位置";
			// 
			// label44
			// 
			this->label44->AutoSize = true;
			this->label44->Location = System::Drawing::Point(110, 21);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(17, 12);
			this->label44->TabIndex = 5;
			this->label44->Text = L"z:";
			// 
			// water_posZ_txt
			// 
			this->water_posZ_txt->Location = System::Drawing::Point(130, 18);
			this->water_posZ_txt->Name = L"water_posZ_txt";
			this->water_posZ_txt->Size = System::Drawing::Size(31, 21);
			this->water_posZ_txt->TabIndex = 4;
			this->water_posZ_txt->Text = L"0";
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Location = System::Drawing::Point(60, 21);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(17, 12);
			this->label45->TabIndex = 3;
			this->label45->Text = L"y:";
			// 
			// water_posY_txt
			// 
			this->water_posY_txt->Location = System::Drawing::Point(78, 18);
			this->water_posY_txt->Name = L"water_posY_txt";
			this->water_posY_txt->Size = System::Drawing::Size(32, 21);
			this->water_posY_txt->TabIndex = 2;
			this->water_posY_txt->Text = L"0";
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->Location = System::Drawing::Point(7, 21);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(17, 12);
			this->label47->TabIndex = 1;
			this->label47->Text = L"x:";
			// 
			// water_posX_txt
			// 
			this->water_posX_txt->Location = System::Drawing::Point(25, 18);
			this->water_posX_txt->Name = L"water_posX_txt";
			this->water_posX_txt->Size = System::Drawing::Size(32, 21);
			this->water_posX_txt->TabIndex = 0;
			this->water_posX_txt->Text = L"0";
			// 
			// panel29
			// 
			this->panel29->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel29->Controls->Add(this->water_group_list);
			this->panel29->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel29->Location = System::Drawing::Point(3, 3);
			this->panel29->Name = L"panel29";
			this->panel29->Size = System::Drawing::Size(202, 87);
			this->panel29->TabIndex = 1;
			// 
			// water_group_list
			// 
			this->water_group_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->columnHeader_water_list_index, 
				this->columnHeader_water_list_mat_id});
			this->water_group_list->Dock = System::Windows::Forms::DockStyle::Fill;
			this->water_group_list->FullRowSelect = true;
			this->water_group_list->GridLines = true;
			this->water_group_list->Location = System::Drawing::Point(0, 0);
			this->water_group_list->MultiSelect = false;
			this->water_group_list->Name = L"water_group_list";
			this->water_group_list->Size = System::Drawing::Size(198, 83);
			this->water_group_list->TabIndex = 6;
			this->water_group_list->UseCompatibleStateImageBehavior = false;
			this->water_group_list->View = System::Windows::Forms::View::Details;
			this->water_group_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::water_group_list_MouseDoubleClick);
			// 
			// columnHeader_water_list_index
			// 
			this->columnHeader_water_list_index->Text = L"序号";
			this->columnHeader_water_list_index->Width = 49;
			// 
			// columnHeader_water_list_mat_id
			// 
			this->columnHeader_water_list_mat_id->Text = L"水材质模板编号";
			this->columnHeader_water_list_mat_id->Width = 120;
			// 
			// water_visible_page
			// 
			this->water_visible_page->BackColor = System::Drawing::SystemColors::Control;
			this->water_visible_page->Controls->Add(this->panel26);
			this->water_visible_page->Location = System::Drawing::Point(4, 21);
			this->water_visible_page->Name = L"water_visible_page";
			this->water_visible_page->Padding = System::Windows::Forms::Padding(3);
			this->water_visible_page->Size = System::Drawing::Size(222, 314);
			this->water_visible_page->TabIndex = 1;
			this->water_visible_page->Text = L"显示和隐藏";
			// 
			// panel26
			// 
			this->panel26->Controls->Add(this->water_visible_tab);
			this->panel26->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel26->Location = System::Drawing::Point(3, 3);
			this->panel26->Name = L"panel26";
			this->panel26->Size = System::Drawing::Size(216, 308);
			this->panel26->TabIndex = 2;
			// 
			// water_visible_tab
			// 
			this->water_visible_tab->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->water_visible_tab->Controls->Add(this->water_op_show_page);
			this->water_visible_tab->Controls->Add(this->water_op_hide_page);
			this->water_visible_tab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->water_visible_tab->ImageList = this->imageList2;
			this->water_visible_tab->ItemSize = System::Drawing::Size(48, 36);
			this->water_visible_tab->Location = System::Drawing::Point(0, 0);
			this->water_visible_tab->Margin = System::Windows::Forms::Padding(0);
			this->water_visible_tab->Multiline = true;
			this->water_visible_tab->Name = L"water_visible_tab";
			this->water_visible_tab->Padding = System::Drawing::Point(1, 1);
			this->water_visible_tab->SelectedIndex = 0;
			this->water_visible_tab->Size = System::Drawing::Size(216, 308);
			this->water_visible_tab->TabIndex = 5;
			this->water_visible_tab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::water_visible_tab_SelectedIndexChanged);
			// 
			// water_op_show_page
			// 
			this->water_op_show_page->BackColor = System::Drawing::Color::Transparent;
			this->water_op_show_page->ImageIndex = 7;
			this->water_op_show_page->Location = System::Drawing::Point(4, 40);
			this->water_op_show_page->Name = L"water_op_show_page";
			this->water_op_show_page->Padding = System::Windows::Forms::Padding(3);
			this->water_op_show_page->Size = System::Drawing::Size(208, 264);
			this->water_op_show_page->TabIndex = 0;
			this->water_op_show_page->ToolTipText = L"显示";
			this->water_op_show_page->UseVisualStyleBackColor = true;
			// 
			// water_op_hide_page
			// 
			this->water_op_hide_page->BackColor = System::Drawing::Color::Transparent;
			this->water_op_hide_page->ImageIndex = 9;
			this->water_op_hide_page->Location = System::Drawing::Point(4, 40);
			this->water_op_hide_page->Name = L"water_op_hide_page";
			this->water_op_hide_page->Padding = System::Windows::Forms::Padding(3);
			this->water_op_hide_page->Size = System::Drawing::Size(208, 264);
			this->water_op_hide_page->TabIndex = 1;
			this->water_op_hide_page->ToolTipText = L"隐藏";
			this->water_op_hide_page->UseVisualStyleBackColor = true;
			// 
			// water_height_page
			// 
			this->water_height_page->BackColor = System::Drawing::SystemColors::Control;
			this->water_height_page->Controls->Add(this->panel27);
			this->water_height_page->Location = System::Drawing::Point(4, 21);
			this->water_height_page->Name = L"water_height_page";
			this->water_height_page->Padding = System::Windows::Forms::Padding(3);
			this->water_height_page->Size = System::Drawing::Size(222, 314);
			this->water_height_page->TabIndex = 2;
			this->water_height_page->Text = L"高度";
			// 
			// panel27
			// 
			this->panel27->Controls->Add(this->water_height_tab);
			this->panel27->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel27->Location = System::Drawing::Point(3, 3);
			this->panel27->Name = L"panel27";
			this->panel27->Size = System::Drawing::Size(216, 308);
			this->panel27->TabIndex = 0;
			// 
			// water_height_tab
			// 
			this->water_height_tab->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->water_height_tab->Controls->Add(this->water_height_level_page);
			this->water_height_tab->Controls->Add(this->water_height_uniform_page);
			this->water_height_tab->Controls->Add(this->water_height_flat_page);
			this->water_height_tab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->water_height_tab->ImageList = this->imageList2;
			this->water_height_tab->ItemSize = System::Drawing::Size(48, 36);
			this->water_height_tab->Location = System::Drawing::Point(0, 0);
			this->water_height_tab->Margin = System::Windows::Forms::Padding(0);
			this->water_height_tab->Multiline = true;
			this->water_height_tab->Name = L"water_height_tab";
			this->water_height_tab->Padding = System::Drawing::Point(1, 1);
			this->water_height_tab->SelectedIndex = 0;
			this->water_height_tab->Size = System::Drawing::Size(216, 308);
			this->water_height_tab->TabIndex = 2;
			this->water_height_tab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::water_height_tab_SelectedIndexChanged);
			// 
			// water_height_level_page
			// 
			this->water_height_level_page->BackColor = System::Drawing::Color::Transparent;
			this->water_height_level_page->Controls->Add(this->water_height_label);
			this->water_height_level_page->Controls->Add(this->water_height_level_app);
			this->water_height_level_page->Controls->Add(this->label38);
			this->water_height_level_page->ImageIndex = 2;
			this->water_height_level_page->Location = System::Drawing::Point(4, 40);
			this->water_height_level_page->Name = L"water_height_level_page";
			this->water_height_level_page->Padding = System::Windows::Forms::Padding(3);
			this->water_height_level_page->Size = System::Drawing::Size(208, 264);
			this->water_height_level_page->TabIndex = 0;
			this->water_height_level_page->ToolTipText = L"升高";
			// 
			// water_height_label
			// 
			this->water_height_label->AutoSize = true;
			this->water_height_label->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->water_height_label->Location = System::Drawing::Point(58, 9);
			this->water_height_label->Name = L"water_height_label";
			this->water_height_label->Size = System::Drawing::Size(25, 14);
			this->water_height_label->TabIndex = 8;
			this->water_height_label->Text = L"1.0";
			// 
			// water_height_level_app
			// 
			this->water_height_level_app->Location = System::Drawing::Point(12, 26);
			this->water_height_level_app->Maximum = 19;
			this->water_height_level_app->Name = L"water_height_level_app";
			this->water_height_level_app->Size = System::Drawing::Size(161, 45);
			this->water_height_level_app->TabIndex = 7;
			this->water_height_level_app->Value = 1;
			this->water_height_level_app->ValueChanged += gcnew System::EventHandler(this, &MainForm::water_height_level_range_tb_ValueChanged);
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(17, 9);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(35, 12);
			this->label38->TabIndex = 6;
			this->label38->Text = L"幅度:";
			// 
			// water_height_uniform_page
			// 
			this->water_height_uniform_page->BackColor = System::Drawing::Color::Transparent;
			this->water_height_uniform_page->Controls->Add(this->label37);
			this->water_height_uniform_page->Controls->Add(this->water_height_confirm);
			this->water_height_uniform_page->Controls->Add(this->water_height_text_box);
			this->water_height_uniform_page->ImageIndex = 3;
			this->water_height_uniform_page->Location = System::Drawing::Point(4, 40);
			this->water_height_uniform_page->Name = L"water_height_uniform_page";
			this->water_height_uniform_page->Padding = System::Windows::Forms::Padding(3);
			this->water_height_uniform_page->Size = System::Drawing::Size(208, 264);
			this->water_height_uniform_page->TabIndex = 2;
			this->water_height_uniform_page->ToolTipText = L"统一";
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(28, 22);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(29, 12);
			this->label37->TabIndex = 7;
			this->label37->Text = L"高度";
			// 
			// water_height_confirm
			// 
			this->water_height_confirm->Location = System::Drawing::Point(138, 15);
			this->water_height_confirm->Name = L"water_height_confirm";
			this->water_height_confirm->Size = System::Drawing::Size(47, 23);
			this->water_height_confirm->TabIndex = 6;
			this->water_height_confirm->Text = L"锁定";
			this->water_height_confirm->UseVisualStyleBackColor = true;
			this->water_height_confirm->Click += gcnew System::EventHandler(this, &MainForm::water_height_confirm_Click);
			// 
			// water_height_text_box
			// 
			this->water_height_text_box->Location = System::Drawing::Point(63, 17);
			this->water_height_text_box->Name = L"water_height_text_box";
			this->water_height_text_box->Size = System::Drawing::Size(69, 21);
			this->water_height_text_box->TabIndex = 5;
			// 
			// water_height_flat_page
			// 
			this->water_height_flat_page->BackColor = System::Drawing::Color::Transparent;
			this->water_height_flat_page->Controls->Add(this->label48);
			this->water_height_flat_page->Controls->Add(this->trackBar5);
			this->water_height_flat_page->Controls->Add(this->label49);
			this->water_height_flat_page->ImageIndex = 1;
			this->water_height_flat_page->Location = System::Drawing::Point(4, 40);
			this->water_height_flat_page->Name = L"water_height_flat_page";
			this->water_height_flat_page->Padding = System::Windows::Forms::Padding(3);
			this->water_height_flat_page->Size = System::Drawing::Size(208, 264);
			this->water_height_flat_page->TabIndex = 4;
			this->water_height_flat_page->ToolTipText = L"平滑";
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label48->Location = System::Drawing::Point(58, 9);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(31, 14);
			this->label48->TabIndex = 11;
			this->label48->Text = L"0.20";
			// 
			// trackBar5
			// 
			this->trackBar5->Location = System::Drawing::Point(13, 28);
			this->trackBar5->Maximum = 49;
			this->trackBar5->Name = L"trackBar5";
			this->trackBar5->Size = System::Drawing::Size(161, 45);
			this->trackBar5->TabIndex = 10;
			this->trackBar5->Value = 19;
			// 
			// label49
			// 
			this->label49->AutoSize = true;
			this->label49->Location = System::Drawing::Point(17, 9);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(35, 12);
			this->label49->TabIndex = 9;
			this->label49->Text = L"幅度:";
			// 
			// panel30
			// 
			this->panel30->Controls->Add(this->sel_water_txt);
			this->panel30->Controls->Add(this->label46);
			this->panel30->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel30->Location = System::Drawing::Point(3, 342);
			this->panel30->Name = L"panel30";
			this->panel30->Size = System::Drawing::Size(230, 45);
			this->panel30->TabIndex = 4;
			// 
			// sel_water_txt
			// 
			this->sel_water_txt->AutoSize = true;
			this->sel_water_txt->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->sel_water_txt->Location = System::Drawing::Point(7, 25);
			this->sel_water_txt->Name = L"sel_water_txt";
			this->sel_water_txt->Size = System::Drawing::Size(49, 14);
			this->sel_water_txt->TabIndex = 10;
			this->sel_water_txt->Text = L"XXXXXXX";
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->Location = System::Drawing::Point(4, 6);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(83, 12);
			this->label46->TabIndex = 0;
			this->label46->Text = L"当前选中材质:";
			// 
			// terrain_region_page
			// 
			this->terrain_region_page->Controls->Add(this->panel21);
			this->terrain_region_page->Controls->Add(this->panel20);
			this->terrain_region_page->Controls->Add(this->panel19);
			this->terrain_region_page->Location = System::Drawing::Point(4, 24);
			this->terrain_region_page->Name = L"terrain_region_page";
			this->terrain_region_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_region_page->Size = System::Drawing::Size(236, 390);
			this->terrain_region_page->TabIndex = 6;
			this->terrain_region_page->Text = L"区域";
			this->terrain_region_page->UseVisualStyleBackColor = true;
			// 
			// panel21
			// 
			this->panel21->Controls->Add(this->TerrainRegionTypeTab);
			this->panel21->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel21->Location = System::Drawing::Point(3, 118);
			this->panel21->Name = L"panel21";
			this->panel21->Size = System::Drawing::Size(230, 269);
			this->panel21->TabIndex = 5;
			// 
			// TerrainRegionTypeTab
			// 
			this->TerrainRegionTypeTab->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->TerrainRegionTypeTab->Controls->Add(this->TerrainRegionBlockPage);
			this->TerrainRegionTypeTab->Controls->Add(this->TerrainRegionSelfPage);
			this->TerrainRegionTypeTab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->TerrainRegionTypeTab->ImageList = this->imageList1;
			this->TerrainRegionTypeTab->ItemSize = System::Drawing::Size(30, 20);
			this->TerrainRegionTypeTab->Location = System::Drawing::Point(0, 0);
			this->TerrainRegionTypeTab->Multiline = true;
			this->TerrainRegionTypeTab->Name = L"TerrainRegionTypeTab";
			this->TerrainRegionTypeTab->Padding = System::Drawing::Point(0, 0);
			this->TerrainRegionTypeTab->SelectedIndex = 0;
			this->TerrainRegionTypeTab->Size = System::Drawing::Size(230, 269);
			this->TerrainRegionTypeTab->TabIndex = 6;
			// 
			// TerrainRegionBlockPage
			// 
			this->TerrainRegionBlockPage->BackColor = System::Drawing::Color::Transparent;
			this->TerrainRegionBlockPage->Controls->Add(this->btn_show_block_refresh);
			this->TerrainRegionBlockPage->Controls->Add(this->btn_static_block_refresh);
			this->TerrainRegionBlockPage->Location = System::Drawing::Point(4, 24);
			this->TerrainRegionBlockPage->Name = L"TerrainRegionBlockPage";
			this->TerrainRegionBlockPage->Padding = System::Windows::Forms::Padding(3);
			this->TerrainRegionBlockPage->Size = System::Drawing::Size(222, 241);
			this->TerrainRegionBlockPage->TabIndex = 0;
			this->TerrainRegionBlockPage->Text = L"障碍";
			this->TerrainRegionBlockPage->UseVisualStyleBackColor = true;
			// 
			// btn_show_block_refresh
			// 
			this->btn_show_block_refresh->Location = System::Drawing::Point(43, 24);
			this->btn_show_block_refresh->Name = L"btn_show_block_refresh";
			this->btn_show_block_refresh->Size = System::Drawing::Size(138, 23);
			this->btn_show_block_refresh->TabIndex = 2;
			this->btn_show_block_refresh->Text = L"显示障碍";
			this->btn_show_block_refresh->UseVisualStyleBackColor = true;
			this->btn_show_block_refresh->Click += gcnew System::EventHandler(this, &MainForm::btn_show_block_refresh_Click);
			// 
			// btn_static_block_refresh
			// 
			this->btn_static_block_refresh->Location = System::Drawing::Point(43, 85);
			this->btn_static_block_refresh->Name = L"btn_static_block_refresh";
			this->btn_static_block_refresh->Size = System::Drawing::Size(138, 23);
			this->btn_static_block_refresh->TabIndex = 1;
			this->btn_static_block_refresh->Text = L"刷新物件障碍";
			this->btn_static_block_refresh->UseVisualStyleBackColor = true;
			// 
			// TerrainRegionSelfPage
			// 
			this->TerrainRegionSelfPage->BackColor = System::Drawing::Color::Transparent;
			this->TerrainRegionSelfPage->Controls->Add(this->TerrainRegionSelfList);
			this->TerrainRegionSelfPage->Controls->Add(this->panel22);
			this->TerrainRegionSelfPage->Location = System::Drawing::Point(4, 24);
			this->TerrainRegionSelfPage->Name = L"TerrainRegionSelfPage";
			this->TerrainRegionSelfPage->Padding = System::Windows::Forms::Padding(3);
			this->TerrainRegionSelfPage->Size = System::Drawing::Size(222, 241);
			this->TerrainRegionSelfPage->TabIndex = 1;
			this->TerrainRegionSelfPage->Text = L"自定义";
			this->TerrainRegionSelfPage->UseVisualStyleBackColor = true;
			// 
			// TerrainRegionSelfList
			// 
			this->TerrainRegionSelfList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->columnHeader_custom_list_index, 
				this->columnHeader_custom_list_name});
			this->TerrainRegionSelfList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->TerrainRegionSelfList->FullRowSelect = true;
			this->TerrainRegionSelfList->GridLines = true;
			this->TerrainRegionSelfList->Location = System::Drawing::Point(3, 3);
			this->TerrainRegionSelfList->MultiSelect = false;
			this->TerrainRegionSelfList->Name = L"TerrainRegionSelfList";
			this->TerrainRegionSelfList->Size = System::Drawing::Size(216, 198);
			this->TerrainRegionSelfList->TabIndex = 5;
			this->TerrainRegionSelfList->UseCompatibleStateImageBehavior = false;
			this->TerrainRegionSelfList->View = System::Windows::Forms::View::Details;
			this->TerrainRegionSelfList->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::TerrainRegionSelfList_MouseDoubleClick);
			// 
			// columnHeader_custom_list_index
			// 
			this->columnHeader_custom_list_index->Text = L"序号";
			// 
			// columnHeader_custom_list_name
			// 
			this->columnHeader_custom_list_name->Text = L"名字";
			// 
			// panel22
			// 
			this->panel22->Controls->Add(this->TerrainAddRegionSelfBtn);
			this->panel22->Controls->Add(this->TerrainSelRegionSelfText);
			this->panel22->Controls->Add(this->label33);
			this->panel22->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel22->Location = System::Drawing::Point(3, 201);
			this->panel22->Name = L"panel22";
			this->panel22->Size = System::Drawing::Size(216, 37);
			this->panel22->TabIndex = 4;
			// 
			// TerrainAddRegionSelfBtn
			// 
			this->TerrainAddRegionSelfBtn->Location = System::Drawing::Point(133, 6);
			this->TerrainAddRegionSelfBtn->Name = L"TerrainAddRegionSelfBtn";
			this->TerrainAddRegionSelfBtn->Size = System::Drawing::Size(75, 23);
			this->TerrainAddRegionSelfBtn->TabIndex = 11;
			this->TerrainAddRegionSelfBtn->Text = L"添加";
			this->TerrainAddRegionSelfBtn->UseVisualStyleBackColor = true;
			this->TerrainAddRegionSelfBtn->Click += gcnew System::EventHandler(this, &MainForm::TerrainAddRegionSelfBtn_Click);
			// 
			// TerrainSelRegionSelfText
			// 
			this->TerrainSelRegionSelfText->AutoSize = true;
			this->TerrainSelRegionSelfText->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->TerrainSelRegionSelfText->Location = System::Drawing::Point(69, 10);
			this->TerrainSelRegionSelfText->Name = L"TerrainSelRegionSelfText";
			this->TerrainSelRegionSelfText->Size = System::Drawing::Size(13, 14);
			this->TerrainSelRegionSelfText->TabIndex = 10;
			this->TerrainSelRegionSelfText->Text = L"0";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(4, 11);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(59, 12);
			this->label33->TabIndex = 0;
			this->label33->Text = L"当前选中:";
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList1->Images->SetKeyName(0, L"笔刷-圆.png");
			this->imageList1->Images->SetKeyName(1, L"笔刷-方.png");
			this->imageList1->Images->SetKeyName(2, L"笔刷-菱.png");
			// 
			// panel20
			// 
			this->panel20->Controls->Add(this->terrain_region_visible_ckb);
			this->panel20->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel20->Location = System::Drawing::Point(3, 83);
			this->panel20->Name = L"panel20";
			this->panel20->Size = System::Drawing::Size(230, 35);
			this->panel20->TabIndex = 4;
			// 
			// terrain_region_visible_ckb
			// 
			this->terrain_region_visible_ckb->AutoSize = true;
			this->terrain_region_visible_ckb->Checked = true;
			this->terrain_region_visible_ckb->CheckState = System::Windows::Forms::CheckState::Checked;
			this->terrain_region_visible_ckb->Location = System::Drawing::Point(14, 12);
			this->terrain_region_visible_ckb->Name = L"terrain_region_visible_ckb";
			this->terrain_region_visible_ckb->Size = System::Drawing::Size(96, 16);
			this->terrain_region_visible_ckb->TabIndex = 4;
			this->terrain_region_visible_ckb->Text = L"是否显示区域";
			this->terrain_region_visible_ckb->UseVisualStyleBackColor = true;
			this->terrain_region_visible_ckb->Click += gcnew System::EventHandler(this, &MainForm::terrain_region_visible_ckb_Click);
			// 
			// panel19
			// 
			this->panel19->Controls->Add(this->terrainRegionOpTab);
			this->panel19->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel19->Location = System::Drawing::Point(3, 3);
			this->panel19->Name = L"panel19";
			this->panel19->Size = System::Drawing::Size(230, 80);
			this->panel19->TabIndex = 2;
			// 
			// terrainRegionOpTab
			// 
			this->terrainRegionOpTab->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->terrainRegionOpTab->Controls->Add(this->terrain_region_add_page);
			this->terrainRegionOpTab->Controls->Add(this->terrain_region_remove_page);
			this->terrainRegionOpTab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->terrainRegionOpTab->ImageList = this->imageList2;
			this->terrainRegionOpTab->ItemSize = System::Drawing::Size(48, 36);
			this->terrainRegionOpTab->Location = System::Drawing::Point(0, 0);
			this->terrainRegionOpTab->Margin = System::Windows::Forms::Padding(0);
			this->terrainRegionOpTab->Multiline = true;
			this->terrainRegionOpTab->Name = L"terrainRegionOpTab";
			this->terrainRegionOpTab->Padding = System::Drawing::Point(1, 1);
			this->terrainRegionOpTab->SelectedIndex = 0;
			this->terrainRegionOpTab->Size = System::Drawing::Size(230, 80);
			this->terrainRegionOpTab->TabIndex = 2;
			this->terrainRegionOpTab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::terrainBlockTab_SelectedIndexChanged);
			// 
			// terrain_region_add_page
			// 
			this->terrain_region_add_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_region_add_page->ImageIndex = 7;
			this->terrain_region_add_page->Location = System::Drawing::Point(4, 40);
			this->terrain_region_add_page->Name = L"terrain_region_add_page";
			this->terrain_region_add_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_region_add_page->Size = System::Drawing::Size(222, 36);
			this->terrain_region_add_page->TabIndex = 0;
			this->terrain_region_add_page->ToolTipText = L"添加障碍";
			this->terrain_region_add_page->UseVisualStyleBackColor = true;
			// 
			// terrain_region_remove_page
			// 
			this->terrain_region_remove_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_region_remove_page->ImageIndex = 9;
			this->terrain_region_remove_page->Location = System::Drawing::Point(4, 40);
			this->terrain_region_remove_page->Name = L"terrain_region_remove_page";
			this->terrain_region_remove_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_region_remove_page->Size = System::Drawing::Size(222, 36);
			this->terrain_region_remove_page->TabIndex = 1;
			this->terrain_region_remove_page->ToolTipText = L"移除障碍";
			this->terrain_region_remove_page->UseVisualStyleBackColor = true;
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::Control;
			this->panel1->Controls->Add(this->groupBox3);
			this->panel1->Controls->Add(this->groupBox2);
			this->panel1->Controls->Add(this->groupBox1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->Location = System::Drawing::Point(3, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(244, 267);
			this->panel1->TabIndex = 0;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->terrain_style_tab);
			this->groupBox3->Location = System::Drawing::Point(10, 153);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(227, 103);
			this->groupBox3->TabIndex = 2;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"笔刷样式";
			// 
			// terrain_style_tab
			// 
			this->terrain_style_tab->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->terrain_style_tab->Controls->Add(this->terrain_style_gun_page);
			this->terrain_style_tab->Controls->Add(this->terrain_style_pen_page);
			this->terrain_style_tab->Controls->Add(this->terrain_style_noise_page);
			this->terrain_style_tab->Controls->Add(this->terrain_style_frag_page);
			this->terrain_style_tab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->terrain_style_tab->ImageList = this->imageList1;
			this->terrain_style_tab->ItemSize = System::Drawing::Size(30, 20);
			this->terrain_style_tab->Location = System::Drawing::Point(3, 17);
			this->terrain_style_tab->Multiline = true;
			this->terrain_style_tab->Name = L"terrain_style_tab";
			this->terrain_style_tab->Padding = System::Drawing::Point(0, 0);
			this->terrain_style_tab->SelectedIndex = 0;
			this->terrain_style_tab->Size = System::Drawing::Size(221, 83);
			this->terrain_style_tab->TabIndex = 0;
			this->terrain_style_tab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::terrain_style_tab_SelectedIndexChanged);
			// 
			// terrain_style_gun_page
			// 
			this->terrain_style_gun_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_style_gun_page->Controls->Add(this->terrain_stytle_gun_decay_text);
			this->terrain_style_gun_page->Controls->Add(this->terrain_stytle_gun_decay_tb);
			this->terrain_style_gun_page->Controls->Add(this->label4);
			this->terrain_style_gun_page->Location = System::Drawing::Point(4, 24);
			this->terrain_style_gun_page->Name = L"terrain_style_gun_page";
			this->terrain_style_gun_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_style_gun_page->Size = System::Drawing::Size(213, 55);
			this->terrain_style_gun_page->TabIndex = 0;
			this->terrain_style_gun_page->Text = L"喷枪";
			this->terrain_style_gun_page->UseVisualStyleBackColor = true;
			// 
			// terrain_stytle_gun_decay_text
			// 
			this->terrain_stytle_gun_decay_text->AutoSize = true;
			this->terrain_stytle_gun_decay_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->terrain_stytle_gun_decay_text->Location = System::Drawing::Point(43, 13);
			this->terrain_stytle_gun_decay_text->Name = L"terrain_stytle_gun_decay_text";
			this->terrain_stytle_gun_decay_text->Size = System::Drawing::Size(19, 14);
			this->terrain_stytle_gun_decay_text->TabIndex = 5;
			this->terrain_stytle_gun_decay_text->Text = L"50";
			// 
			// terrain_stytle_gun_decay_tb
			// 
			this->terrain_stytle_gun_decay_tb->Location = System::Drawing::Point(68, 6);
			this->terrain_stytle_gun_decay_tb->Maximum = 99;
			this->terrain_stytle_gun_decay_tb->Name = L"terrain_stytle_gun_decay_tb";
			this->terrain_stytle_gun_decay_tb->Size = System::Drawing::Size(127, 45);
			this->terrain_stytle_gun_decay_tb->TabIndex = 4;
			this->terrain_stytle_gun_decay_tb->Value = 50;
			this->terrain_stytle_gun_decay_tb->ValueChanged += gcnew System::EventHandler(this, &MainForm::terrain_stytle_gun_decay_tb_ValueChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(7, 13);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(35, 12);
			this->label4->TabIndex = 3;
			this->label4->Text = L"衰减:";
			// 
			// terrain_style_pen_page
			// 
			this->terrain_style_pen_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_style_pen_page->Location = System::Drawing::Point(4, 24);
			this->terrain_style_pen_page->Name = L"terrain_style_pen_page";
			this->terrain_style_pen_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_style_pen_page->Size = System::Drawing::Size(213, 55);
			this->terrain_style_pen_page->TabIndex = 1;
			this->terrain_style_pen_page->Text = L"画笔";
			this->terrain_style_pen_page->UseVisualStyleBackColor = true;
			// 
			// terrain_style_noise_page
			// 
			this->terrain_style_noise_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_style_noise_page->Location = System::Drawing::Point(4, 24);
			this->terrain_style_noise_page->Name = L"terrain_style_noise_page";
			this->terrain_style_noise_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_style_noise_page->Size = System::Drawing::Size(213, 55);
			this->terrain_style_noise_page->TabIndex = 2;
			this->terrain_style_noise_page->Text = L"噪度";
			this->terrain_style_noise_page->UseVisualStyleBackColor = true;
			// 
			// terrain_style_frag_page
			// 
			this->terrain_style_frag_page->BackColor = System::Drawing::Color::Transparent;
			this->terrain_style_frag_page->Location = System::Drawing::Point(4, 24);
			this->terrain_style_frag_page->Name = L"terrain_style_frag_page";
			this->terrain_style_frag_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_style_frag_page->Size = System::Drawing::Size(213, 55);
			this->terrain_style_frag_page->TabIndex = 3;
			this->terrain_style_frag_page->Text = L"碎片";
			this->terrain_style_frag_page->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->terrain_brush_shape_tab);
			this->groupBox2->Location = System::Drawing::Point(9, 95);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(228, 54);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"笔刷形状";
			// 
			// terrain_brush_shape_tab
			// 
			this->terrain_brush_shape_tab->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->terrain_brush_shape_tab->Controls->Add(this->terrain_shape_yuan_page);
			this->terrain_brush_shape_tab->Controls->Add(this->terrain_shape_fang_page);
			this->terrain_brush_shape_tab->Controls->Add(this->terrain_shape_lin_page);
			this->terrain_brush_shape_tab->ImageList = this->imageList1;
			this->terrain_brush_shape_tab->Location = System::Drawing::Point(13, 21);
			this->terrain_brush_shape_tab->Multiline = true;
			this->terrain_brush_shape_tab->Name = L"terrain_brush_shape_tab";
			this->terrain_brush_shape_tab->Padding = System::Drawing::Point(0, 0);
			this->terrain_brush_shape_tab->SelectedIndex = 0;
			this->terrain_brush_shape_tab->Size = System::Drawing::Size(173, 28);
			this->terrain_brush_shape_tab->TabIndex = 0;
			this->terrain_brush_shape_tab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::terrain_brush_shape_tab_SelectedIndexChanged);
			// 
			// terrain_shape_yuan_page
			// 
			this->terrain_shape_yuan_page->ImageIndex = 0;
			this->terrain_shape_yuan_page->Location = System::Drawing::Point(4, 26);
			this->terrain_shape_yuan_page->Name = L"terrain_shape_yuan_page";
			this->terrain_shape_yuan_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_shape_yuan_page->Size = System::Drawing::Size(165, 0);
			this->terrain_shape_yuan_page->TabIndex = 0;
			this->terrain_shape_yuan_page->Text = L"圆";
			this->terrain_shape_yuan_page->UseVisualStyleBackColor = true;
			// 
			// terrain_shape_fang_page
			// 
			this->terrain_shape_fang_page->ImageIndex = 1;
			this->terrain_shape_fang_page->Location = System::Drawing::Point(4, 26);
			this->terrain_shape_fang_page->Name = L"terrain_shape_fang_page";
			this->terrain_shape_fang_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_shape_fang_page->Size = System::Drawing::Size(165, 0);
			this->terrain_shape_fang_page->TabIndex = 1;
			this->terrain_shape_fang_page->Text = L"方";
			this->terrain_shape_fang_page->UseVisualStyleBackColor = true;
			// 
			// terrain_shape_lin_page
			// 
			this->terrain_shape_lin_page->ImageIndex = 2;
			this->terrain_shape_lin_page->Location = System::Drawing::Point(4, 26);
			this->terrain_shape_lin_page->Name = L"terrain_shape_lin_page";
			this->terrain_shape_lin_page->Padding = System::Windows::Forms::Padding(3);
			this->terrain_shape_lin_page->Size = System::Drawing::Size(165, 0);
			this->terrain_shape_lin_page->TabIndex = 2;
			this->terrain_shape_lin_page->Text = L"菱";
			this->terrain_shape_lin_page->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->terrain_brush_speed_text);
			this->groupBox1->Controls->Add(this->terrain_brush_speed_tb);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->terrain_brush_size_text);
			this->groupBox1->Controls->Add(this->terrain_brush_size_tb);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Location = System::Drawing::Point(7, 9);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(231, 81);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"笔刷设置";
			// 
			// terrain_brush_speed_text
			// 
			this->terrain_brush_speed_text->AutoSize = true;
			this->terrain_brush_speed_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->terrain_brush_speed_text->Location = System::Drawing::Point(43, 58);
			this->terrain_brush_speed_text->Name = L"terrain_brush_speed_text";
			this->terrain_brush_speed_text->Size = System::Drawing::Size(31, 14);
			this->terrain_brush_speed_text->TabIndex = 8;
			this->terrain_brush_speed_text->Text = L"2.00";
			// 
			// terrain_brush_speed_tb
			// 
			this->terrain_brush_speed_tb->Location = System::Drawing::Point(80, 47);
			this->terrain_brush_speed_tb->Maximum = 4;
			this->terrain_brush_speed_tb->Name = L"terrain_brush_speed_tb";
			this->terrain_brush_speed_tb->Size = System::Drawing::Size(136, 45);
			this->terrain_brush_speed_tb->TabIndex = 7;
			this->terrain_brush_speed_tb->Value = 1;
			this->terrain_brush_speed_tb->ValueChanged += gcnew System::EventHandler(this, &MainForm::terrain_brush_speed_tb_ValueChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(7, 58);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(35, 12);
			this->label5->TabIndex = 6;
			this->label5->Text = L"速度:";
			// 
			// terrain_brush_size_text
			// 
			this->terrain_brush_size_text->AutoSize = true;
			this->terrain_brush_size_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->terrain_brush_size_text->Location = System::Drawing::Point(43, 22);
			this->terrain_brush_size_text->Name = L"terrain_brush_size_text";
			this->terrain_brush_size_text->Size = System::Drawing::Size(25, 14);
			this->terrain_brush_size_text->TabIndex = 5;
			this->terrain_brush_size_text->Text = L"1.0";
			// 
			// terrain_brush_size_tb
			// 
			this->terrain_brush_size_tb->Location = System::Drawing::Point(78, 9);
			this->terrain_brush_size_tb->Maximum = 50;
			this->terrain_brush_size_tb->Name = L"terrain_brush_size_tb";
			this->terrain_brush_size_tb->Size = System::Drawing::Size(136, 45);
			this->terrain_brush_size_tb->TabIndex = 4;
			this->terrain_brush_size_tb->Value = 2;
			this->terrain_brush_size_tb->ValueChanged += gcnew System::EventHandler(this, &MainForm::terrain_brush_size_tb_ValueChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 23);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 12);
			this->label3->TabIndex = 3;
			this->label3->Text = L"尺寸:";
			// 
			// setting_page
			// 
			this->setting_page->Controls->Add(this->panel7);
			this->setting_page->Location = System::Drawing::Point(4, 21);
			this->setting_page->Name = L"setting_page";
			this->setting_page->Padding = System::Windows::Forms::Padding(3);
			this->setting_page->Size = System::Drawing::Size(250, 691);
			this->setting_page->TabIndex = 0;
			this->setting_page->Text = L"设置";
			this->setting_page->UseVisualStyleBackColor = true;
			// 
			// panel7
			// 
			this->panel7->BackColor = System::Drawing::SystemColors::Control;
			this->panel7->Controls->Add(this->ConfigTab);
			this->panel7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel7->Location = System::Drawing::Point(3, 3);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(244, 685);
			this->panel7->TabIndex = 0;
			// 
			// ConfigTab
			// 
			this->ConfigTab->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
			this->ConfigTab->Controls->Add(this->Config_env_light_page);
			this->ConfigTab->Controls->Add(this->config_video_page);
			this->ConfigTab->Controls->Add(this->config_plant_page);
			this->ConfigTab->Controls->Add(this->tabPage1);
			this->ConfigTab->Controls->Add(this->tabPage9);
			this->ConfigTab->Controls->Add(this->tabPage10);
			this->ConfigTab->Controls->Add(this->tabPage11);
			this->ConfigTab->Controls->Add(this->tabPage12);
			this->ConfigTab->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ConfigTab->Location = System::Drawing::Point(0, 0);
			this->ConfigTab->Name = L"ConfigTab";
			this->ConfigTab->SelectedIndex = 0;
			this->ConfigTab->Size = System::Drawing::Size(244, 685);
			this->ConfigTab->TabIndex = 0;
			// 
			// Config_env_light_page
			// 
			this->Config_env_light_page->Controls->Add(this->groupBox5);
			this->Config_env_light_page->Controls->Add(this->groupBox36);
			this->Config_env_light_page->Controls->Add(this->groupBox4);
			this->Config_env_light_page->Controls->Add(this->groupBox27);
			this->Config_env_light_page->Controls->Add(this->groupBox6);
			this->Config_env_light_page->Controls->Add(this->button7);
			this->Config_env_light_page->Location = System::Drawing::Point(4, 24);
			this->Config_env_light_page->Name = L"Config_env_light_page";
			this->Config_env_light_page->Padding = System::Windows::Forms::Padding(3);
			this->Config_env_light_page->Size = System::Drawing::Size(236, 657);
			this->Config_env_light_page->TabIndex = 0;
			this->Config_env_light_page->Text = L"灯光";
			this->Config_env_light_page->UseVisualStyleBackColor = true;
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->TextBox_STSpecular_B);
			this->groupBox5->Controls->Add(this->label24);
			this->groupBox5->Controls->Add(this->TextBox_STSpecular_G);
			this->groupBox5->Controls->Add(this->label25);
			this->groupBox5->Controls->Add(this->TextBox_STSpecular_R);
			this->groupBox5->Controls->Add(this->label26);
			this->groupBox5->Controls->Add(this->TextBox_STDiffuse_B);
			this->groupBox5->Controls->Add(this->label27);
			this->groupBox5->Controls->Add(this->TextBox_STDiffuse_G);
			this->groupBox5->Controls->Add(this->label28);
			this->groupBox5->Controls->Add(this->TextBox_STDiffuse_R);
			this->groupBox5->Controls->Add(this->label29);
			this->groupBox5->Controls->Add(this->TextBox_STAmbient_B);
			this->groupBox5->Controls->Add(this->label92);
			this->groupBox5->Controls->Add(this->TextBox_STAmbient_G);
			this->groupBox5->Controls->Add(this->label93);
			this->groupBox5->Controls->Add(this->TextBox_STAmbient_R);
			this->groupBox5->Controls->Add(this->label94);
			this->groupBox5->Controls->Add(this->label95);
			this->groupBox5->Controls->Add(this->label96);
			this->groupBox5->Controls->Add(this->label97);
			this->groupBox5->Location = System::Drawing::Point(19, 107);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(211, 86);
			this->groupBox5->TabIndex = 24;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"树灯光";
			// 
			// TextBox_STSpecular_B
			// 
			this->TextBox_STSpecular_B->Location = System::Drawing::Point(178, 63);
			this->TextBox_STSpecular_B->Name = L"TextBox_STSpecular_B";
			this->TextBox_STSpecular_B->Size = System::Drawing::Size(27, 21);
			this->TextBox_STSpecular_B->TabIndex = 23;
			this->TextBox_STSpecular_B->Text = L"1.0";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(166, 67);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(17, 12);
			this->label24->TabIndex = 22;
			this->label24->Text = L"b:";
			// 
			// TextBox_STSpecular_G
			// 
			this->TextBox_STSpecular_G->Location = System::Drawing::Point(131, 63);
			this->TextBox_STSpecular_G->Name = L"TextBox_STSpecular_G";
			this->TextBox_STSpecular_G->Size = System::Drawing::Size(27, 21);
			this->TextBox_STSpecular_G->TabIndex = 21;
			this->TextBox_STSpecular_G->Text = L"1.0";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(119, 67);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(17, 12);
			this->label25->TabIndex = 20;
			this->label25->Text = L"g:";
			// 
			// TextBox_STSpecular_R
			// 
			this->TextBox_STSpecular_R->Location = System::Drawing::Point(84, 63);
			this->TextBox_STSpecular_R->Name = L"TextBox_STSpecular_R";
			this->TextBox_STSpecular_R->Size = System::Drawing::Size(27, 21);
			this->TextBox_STSpecular_R->TabIndex = 19;
			this->TextBox_STSpecular_R->Text = L"1.0";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(72, 67);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(17, 12);
			this->label26->TabIndex = 18;
			this->label26->Text = L"r:";
			// 
			// TextBox_STDiffuse_B
			// 
			this->TextBox_STDiffuse_B->Location = System::Drawing::Point(178, 38);
			this->TextBox_STDiffuse_B->Name = L"TextBox_STDiffuse_B";
			this->TextBox_STDiffuse_B->Size = System::Drawing::Size(27, 21);
			this->TextBox_STDiffuse_B->TabIndex = 17;
			this->TextBox_STDiffuse_B->Text = L"1.0";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(166, 42);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(17, 12);
			this->label27->TabIndex = 16;
			this->label27->Text = L"b:";
			// 
			// TextBox_STDiffuse_G
			// 
			this->TextBox_STDiffuse_G->Location = System::Drawing::Point(131, 38);
			this->TextBox_STDiffuse_G->Name = L"TextBox_STDiffuse_G";
			this->TextBox_STDiffuse_G->Size = System::Drawing::Size(27, 21);
			this->TextBox_STDiffuse_G->TabIndex = 15;
			this->TextBox_STDiffuse_G->Text = L"1.0";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(119, 42);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(17, 12);
			this->label28->TabIndex = 14;
			this->label28->Text = L"g:";
			// 
			// TextBox_STDiffuse_R
			// 
			this->TextBox_STDiffuse_R->Location = System::Drawing::Point(84, 38);
			this->TextBox_STDiffuse_R->Name = L"TextBox_STDiffuse_R";
			this->TextBox_STDiffuse_R->Size = System::Drawing::Size(27, 21);
			this->TextBox_STDiffuse_R->TabIndex = 13;
			this->TextBox_STDiffuse_R->Text = L"1.0";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(72, 42);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(17, 12);
			this->label29->TabIndex = 12;
			this->label29->Text = L"r:";
			// 
			// TextBox_STAmbient_B
			// 
			this->TextBox_STAmbient_B->Location = System::Drawing::Point(177, 13);
			this->TextBox_STAmbient_B->Name = L"TextBox_STAmbient_B";
			this->TextBox_STAmbient_B->Size = System::Drawing::Size(27, 21);
			this->TextBox_STAmbient_B->TabIndex = 11;
			this->TextBox_STAmbient_B->Text = L"1.0";
			// 
			// label92
			// 
			this->label92->AutoSize = true;
			this->label92->Location = System::Drawing::Point(165, 17);
			this->label92->Name = L"label92";
			this->label92->Size = System::Drawing::Size(17, 12);
			this->label92->TabIndex = 10;
			this->label92->Text = L"b:";
			// 
			// TextBox_STAmbient_G
			// 
			this->TextBox_STAmbient_G->Location = System::Drawing::Point(130, 13);
			this->TextBox_STAmbient_G->Name = L"TextBox_STAmbient_G";
			this->TextBox_STAmbient_G->Size = System::Drawing::Size(27, 21);
			this->TextBox_STAmbient_G->TabIndex = 9;
			this->TextBox_STAmbient_G->Text = L"1.0";
			// 
			// label93
			// 
			this->label93->AutoSize = true;
			this->label93->Location = System::Drawing::Point(118, 17);
			this->label93->Name = L"label93";
			this->label93->Size = System::Drawing::Size(17, 12);
			this->label93->TabIndex = 8;
			this->label93->Text = L"g:";
			// 
			// TextBox_STAmbient_R
			// 
			this->TextBox_STAmbient_R->Location = System::Drawing::Point(83, 13);
			this->TextBox_STAmbient_R->Name = L"TextBox_STAmbient_R";
			this->TextBox_STAmbient_R->Size = System::Drawing::Size(27, 21);
			this->TextBox_STAmbient_R->TabIndex = 7;
			this->TextBox_STAmbient_R->Text = L"1.0";
			// 
			// label94
			// 
			this->label94->AutoSize = true;
			this->label94->Location = System::Drawing::Point(71, 17);
			this->label94->Name = L"label94";
			this->label94->Size = System::Drawing::Size(17, 12);
			this->label94->TabIndex = 6;
			this->label94->Text = L"r:";
			// 
			// label95
			// 
			this->label95->AutoSize = true;
			this->label95->Location = System::Drawing::Point(4, 67);
			this->label95->Name = L"label95";
			this->label95->Size = System::Drawing::Size(65, 12);
			this->label95->TabIndex = 4;
			this->label95->Text = L"镜面反射光";
			// 
			// label96
			// 
			this->label96->AutoSize = true;
			this->label96->Location = System::Drawing::Point(3, 43);
			this->label96->Name = L"label96";
			this->label96->Size = System::Drawing::Size(53, 12);
			this->label96->TabIndex = 2;
			this->label96->Text = L"漫反射光";
			// 
			// label97
			// 
			this->label97->AutoSize = true;
			this->label97->Location = System::Drawing::Point(2, 18);
			this->label97->Name = L"label97";
			this->label97->Size = System::Drawing::Size(41, 12);
			this->label97->TabIndex = 0;
			this->label97->Text = L"环境光";
			// 
			// groupBox36
			// 
			this->groupBox36->Controls->Add(this->TextBox_SGSpecular_B);
			this->groupBox36->Controls->Add(this->label98);
			this->groupBox36->Controls->Add(this->TextBox_SGSpecular_G);
			this->groupBox36->Controls->Add(this->label99);
			this->groupBox36->Controls->Add(this->TextBox_SGSpecular_R);
			this->groupBox36->Controls->Add(this->label100);
			this->groupBox36->Controls->Add(this->TextBox_SGDiffuse_B);
			this->groupBox36->Controls->Add(this->label101);
			this->groupBox36->Controls->Add(this->TextBox_SGDiffuse_G);
			this->groupBox36->Controls->Add(this->label102);
			this->groupBox36->Controls->Add(this->TextBox_SGDiffuse_R);
			this->groupBox36->Controls->Add(this->label103);
			this->groupBox36->Controls->Add(this->TextBox_SGAmbient_B);
			this->groupBox36->Controls->Add(this->label104);
			this->groupBox36->Controls->Add(this->TextBox_SGAmbient_G);
			this->groupBox36->Controls->Add(this->label105);
			this->groupBox36->Controls->Add(this->TextBox_SGAmbient_R);
			this->groupBox36->Controls->Add(this->label106);
			this->groupBox36->Controls->Add(this->label107);
			this->groupBox36->Controls->Add(this->label108);
			this->groupBox36->Controls->Add(this->label109);
			this->groupBox36->Location = System::Drawing::Point(19, 209);
			this->groupBox36->Name = L"groupBox36";
			this->groupBox36->Size = System::Drawing::Size(211, 86);
			this->groupBox36->TabIndex = 24;
			this->groupBox36->TabStop = false;
			this->groupBox36->Text = L"草灯光";
			// 
			// TextBox_SGSpecular_B
			// 
			this->TextBox_SGSpecular_B->Location = System::Drawing::Point(178, 63);
			this->TextBox_SGSpecular_B->Name = L"TextBox_SGSpecular_B";
			this->TextBox_SGSpecular_B->Size = System::Drawing::Size(27, 21);
			this->TextBox_SGSpecular_B->TabIndex = 23;
			this->TextBox_SGSpecular_B->Text = L"1.0";
			// 
			// label98
			// 
			this->label98->AutoSize = true;
			this->label98->Location = System::Drawing::Point(166, 67);
			this->label98->Name = L"label98";
			this->label98->Size = System::Drawing::Size(17, 12);
			this->label98->TabIndex = 22;
			this->label98->Text = L"b:";
			// 
			// TextBox_SGSpecular_G
			// 
			this->TextBox_SGSpecular_G->Location = System::Drawing::Point(131, 63);
			this->TextBox_SGSpecular_G->Name = L"TextBox_SGSpecular_G";
			this->TextBox_SGSpecular_G->Size = System::Drawing::Size(27, 21);
			this->TextBox_SGSpecular_G->TabIndex = 21;
			this->TextBox_SGSpecular_G->Text = L"1.0";
			// 
			// label99
			// 
			this->label99->AutoSize = true;
			this->label99->Location = System::Drawing::Point(119, 67);
			this->label99->Name = L"label99";
			this->label99->Size = System::Drawing::Size(17, 12);
			this->label99->TabIndex = 20;
			this->label99->Text = L"g:";
			// 
			// TextBox_SGSpecular_R
			// 
			this->TextBox_SGSpecular_R->Location = System::Drawing::Point(84, 63);
			this->TextBox_SGSpecular_R->Name = L"TextBox_SGSpecular_R";
			this->TextBox_SGSpecular_R->Size = System::Drawing::Size(27, 21);
			this->TextBox_SGSpecular_R->TabIndex = 19;
			this->TextBox_SGSpecular_R->Text = L"1.0";
			// 
			// label100
			// 
			this->label100->AutoSize = true;
			this->label100->Location = System::Drawing::Point(72, 67);
			this->label100->Name = L"label100";
			this->label100->Size = System::Drawing::Size(17, 12);
			this->label100->TabIndex = 18;
			this->label100->Text = L"r:";
			// 
			// TextBox_SGDiffuse_B
			// 
			this->TextBox_SGDiffuse_B->Location = System::Drawing::Point(178, 38);
			this->TextBox_SGDiffuse_B->Name = L"TextBox_SGDiffuse_B";
			this->TextBox_SGDiffuse_B->Size = System::Drawing::Size(27, 21);
			this->TextBox_SGDiffuse_B->TabIndex = 17;
			this->TextBox_SGDiffuse_B->Text = L"1.0";
			// 
			// label101
			// 
			this->label101->AutoSize = true;
			this->label101->Location = System::Drawing::Point(166, 42);
			this->label101->Name = L"label101";
			this->label101->Size = System::Drawing::Size(17, 12);
			this->label101->TabIndex = 16;
			this->label101->Text = L"b:";
			// 
			// TextBox_SGDiffuse_G
			// 
			this->TextBox_SGDiffuse_G->Location = System::Drawing::Point(131, 38);
			this->TextBox_SGDiffuse_G->Name = L"TextBox_SGDiffuse_G";
			this->TextBox_SGDiffuse_G->Size = System::Drawing::Size(27, 21);
			this->TextBox_SGDiffuse_G->TabIndex = 15;
			this->TextBox_SGDiffuse_G->Text = L"1.0";
			// 
			// label102
			// 
			this->label102->AutoSize = true;
			this->label102->Location = System::Drawing::Point(119, 42);
			this->label102->Name = L"label102";
			this->label102->Size = System::Drawing::Size(17, 12);
			this->label102->TabIndex = 14;
			this->label102->Text = L"g:";
			// 
			// TextBox_SGDiffuse_R
			// 
			this->TextBox_SGDiffuse_R->Location = System::Drawing::Point(84, 38);
			this->TextBox_SGDiffuse_R->Name = L"TextBox_SGDiffuse_R";
			this->TextBox_SGDiffuse_R->Size = System::Drawing::Size(27, 21);
			this->TextBox_SGDiffuse_R->TabIndex = 13;
			this->TextBox_SGDiffuse_R->Text = L"1.0";
			// 
			// label103
			// 
			this->label103->AutoSize = true;
			this->label103->Location = System::Drawing::Point(72, 42);
			this->label103->Name = L"label103";
			this->label103->Size = System::Drawing::Size(17, 12);
			this->label103->TabIndex = 12;
			this->label103->Text = L"r:";
			// 
			// TextBox_SGAmbient_B
			// 
			this->TextBox_SGAmbient_B->Location = System::Drawing::Point(177, 13);
			this->TextBox_SGAmbient_B->Name = L"TextBox_SGAmbient_B";
			this->TextBox_SGAmbient_B->Size = System::Drawing::Size(27, 21);
			this->TextBox_SGAmbient_B->TabIndex = 11;
			this->TextBox_SGAmbient_B->Text = L"1.0";
			// 
			// label104
			// 
			this->label104->AutoSize = true;
			this->label104->Location = System::Drawing::Point(165, 17);
			this->label104->Name = L"label104";
			this->label104->Size = System::Drawing::Size(17, 12);
			this->label104->TabIndex = 10;
			this->label104->Text = L"b:";
			// 
			// TextBox_SGAmbient_G
			// 
			this->TextBox_SGAmbient_G->Location = System::Drawing::Point(130, 13);
			this->TextBox_SGAmbient_G->Name = L"TextBox_SGAmbient_G";
			this->TextBox_SGAmbient_G->Size = System::Drawing::Size(27, 21);
			this->TextBox_SGAmbient_G->TabIndex = 9;
			this->TextBox_SGAmbient_G->Text = L"1.0";
			// 
			// label105
			// 
			this->label105->AutoSize = true;
			this->label105->Location = System::Drawing::Point(118, 17);
			this->label105->Name = L"label105";
			this->label105->Size = System::Drawing::Size(17, 12);
			this->label105->TabIndex = 8;
			this->label105->Text = L"g:";
			// 
			// TextBox_SGAmbient_R
			// 
			this->TextBox_SGAmbient_R->Location = System::Drawing::Point(83, 13);
			this->TextBox_SGAmbient_R->Name = L"TextBox_SGAmbient_R";
			this->TextBox_SGAmbient_R->Size = System::Drawing::Size(27, 21);
			this->TextBox_SGAmbient_R->TabIndex = 7;
			this->TextBox_SGAmbient_R->Text = L"1.0";
			// 
			// label106
			// 
			this->label106->AutoSize = true;
			this->label106->Location = System::Drawing::Point(71, 17);
			this->label106->Name = L"label106";
			this->label106->Size = System::Drawing::Size(17, 12);
			this->label106->TabIndex = 6;
			this->label106->Text = L"r:";
			// 
			// label107
			// 
			this->label107->AutoSize = true;
			this->label107->Location = System::Drawing::Point(4, 67);
			this->label107->Name = L"label107";
			this->label107->Size = System::Drawing::Size(65, 12);
			this->label107->TabIndex = 4;
			this->label107->Text = L"镜面反射光";
			// 
			// label108
			// 
			this->label108->AutoSize = true;
			this->label108->Location = System::Drawing::Point(3, 43);
			this->label108->Name = L"label108";
			this->label108->Size = System::Drawing::Size(53, 12);
			this->label108->TabIndex = 2;
			this->label108->Text = L"漫反射光";
			// 
			// label109
			// 
			this->label109->AutoSize = true;
			this->label109->Location = System::Drawing::Point(2, 18);
			this->label109->Name = L"label109";
			this->label109->Size = System::Drawing::Size(41, 12);
			this->label109->TabIndex = 0;
			this->label109->Text = L"环境光";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->TextBox_Specular_B);
			this->groupBox4->Controls->Add(this->label89);
			this->groupBox4->Controls->Add(this->TextBox_Specular_G);
			this->groupBox4->Controls->Add(this->label90);
			this->groupBox4->Controls->Add(this->TextBox_Specular_R);
			this->groupBox4->Controls->Add(this->label91);
			this->groupBox4->Controls->Add(this->TextBox_Diffuse_B);
			this->groupBox4->Controls->Add(this->label86);
			this->groupBox4->Controls->Add(this->TextBox_Diffuse_G);
			this->groupBox4->Controls->Add(this->label87);
			this->groupBox4->Controls->Add(this->TextBox_Diffuse_R);
			this->groupBox4->Controls->Add(this->label88);
			this->groupBox4->Controls->Add(this->TextBox_Ambient_B);
			this->groupBox4->Controls->Add(this->label83);
			this->groupBox4->Controls->Add(this->TextBox_Ambient_G);
			this->groupBox4->Controls->Add(this->label81);
			this->groupBox4->Controls->Add(this->TextBox_Ambient_R);
			this->groupBox4->Controls->Add(this->label30);
			this->groupBox4->Controls->Add(this->label11);
			this->groupBox4->Controls->Add(this->label8);
			this->groupBox4->Controls->Add(this->label1);
			this->groupBox4->Location = System::Drawing::Point(19, 15);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(211, 86);
			this->groupBox4->TabIndex = 16;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"场景灯光";
			// 
			// TextBox_Specular_B
			// 
			this->TextBox_Specular_B->Location = System::Drawing::Point(178, 63);
			this->TextBox_Specular_B->Name = L"TextBox_Specular_B";
			this->TextBox_Specular_B->Size = System::Drawing::Size(27, 21);
			this->TextBox_Specular_B->TabIndex = 23;
			this->TextBox_Specular_B->Text = L"1.0";
			// 
			// label89
			// 
			this->label89->AutoSize = true;
			this->label89->Location = System::Drawing::Point(166, 67);
			this->label89->Name = L"label89";
			this->label89->Size = System::Drawing::Size(17, 12);
			this->label89->TabIndex = 22;
			this->label89->Text = L"b:";
			// 
			// TextBox_Specular_G
			// 
			this->TextBox_Specular_G->Location = System::Drawing::Point(131, 63);
			this->TextBox_Specular_G->Name = L"TextBox_Specular_G";
			this->TextBox_Specular_G->Size = System::Drawing::Size(27, 21);
			this->TextBox_Specular_G->TabIndex = 21;
			this->TextBox_Specular_G->Text = L"1.0";
			// 
			// label90
			// 
			this->label90->AutoSize = true;
			this->label90->Location = System::Drawing::Point(119, 67);
			this->label90->Name = L"label90";
			this->label90->Size = System::Drawing::Size(17, 12);
			this->label90->TabIndex = 20;
			this->label90->Text = L"g:";
			// 
			// TextBox_Specular_R
			// 
			this->TextBox_Specular_R->Location = System::Drawing::Point(84, 63);
			this->TextBox_Specular_R->Name = L"TextBox_Specular_R";
			this->TextBox_Specular_R->Size = System::Drawing::Size(27, 21);
			this->TextBox_Specular_R->TabIndex = 19;
			this->TextBox_Specular_R->Text = L"1.0";
			// 
			// label91
			// 
			this->label91->AutoSize = true;
			this->label91->Location = System::Drawing::Point(72, 67);
			this->label91->Name = L"label91";
			this->label91->Size = System::Drawing::Size(17, 12);
			this->label91->TabIndex = 18;
			this->label91->Text = L"r:";
			// 
			// TextBox_Diffuse_B
			// 
			this->TextBox_Diffuse_B->Location = System::Drawing::Point(178, 38);
			this->TextBox_Diffuse_B->Name = L"TextBox_Diffuse_B";
			this->TextBox_Diffuse_B->Size = System::Drawing::Size(27, 21);
			this->TextBox_Diffuse_B->TabIndex = 17;
			this->TextBox_Diffuse_B->Text = L"1.0";
			// 
			// label86
			// 
			this->label86->AutoSize = true;
			this->label86->Location = System::Drawing::Point(166, 42);
			this->label86->Name = L"label86";
			this->label86->Size = System::Drawing::Size(17, 12);
			this->label86->TabIndex = 16;
			this->label86->Text = L"b:";
			// 
			// TextBox_Diffuse_G
			// 
			this->TextBox_Diffuse_G->Location = System::Drawing::Point(131, 38);
			this->TextBox_Diffuse_G->Name = L"TextBox_Diffuse_G";
			this->TextBox_Diffuse_G->Size = System::Drawing::Size(27, 21);
			this->TextBox_Diffuse_G->TabIndex = 15;
			this->TextBox_Diffuse_G->Text = L"1.0";
			// 
			// label87
			// 
			this->label87->AutoSize = true;
			this->label87->Location = System::Drawing::Point(119, 42);
			this->label87->Name = L"label87";
			this->label87->Size = System::Drawing::Size(17, 12);
			this->label87->TabIndex = 14;
			this->label87->Text = L"g:";
			// 
			// TextBox_Diffuse_R
			// 
			this->TextBox_Diffuse_R->Location = System::Drawing::Point(84, 38);
			this->TextBox_Diffuse_R->Name = L"TextBox_Diffuse_R";
			this->TextBox_Diffuse_R->Size = System::Drawing::Size(27, 21);
			this->TextBox_Diffuse_R->TabIndex = 13;
			this->TextBox_Diffuse_R->Text = L"1.0";
			// 
			// label88
			// 
			this->label88->AutoSize = true;
			this->label88->Location = System::Drawing::Point(72, 42);
			this->label88->Name = L"label88";
			this->label88->Size = System::Drawing::Size(17, 12);
			this->label88->TabIndex = 12;
			this->label88->Text = L"r:";
			// 
			// TextBox_Ambient_B
			// 
			this->TextBox_Ambient_B->Location = System::Drawing::Point(177, 13);
			this->TextBox_Ambient_B->Name = L"TextBox_Ambient_B";
			this->TextBox_Ambient_B->Size = System::Drawing::Size(27, 21);
			this->TextBox_Ambient_B->TabIndex = 11;
			this->TextBox_Ambient_B->Text = L"1.0";
			// 
			// label83
			// 
			this->label83->AutoSize = true;
			this->label83->Location = System::Drawing::Point(165, 17);
			this->label83->Name = L"label83";
			this->label83->Size = System::Drawing::Size(17, 12);
			this->label83->TabIndex = 10;
			this->label83->Text = L"b:";
			// 
			// TextBox_Ambient_G
			// 
			this->TextBox_Ambient_G->Location = System::Drawing::Point(130, 13);
			this->TextBox_Ambient_G->Name = L"TextBox_Ambient_G";
			this->TextBox_Ambient_G->Size = System::Drawing::Size(27, 21);
			this->TextBox_Ambient_G->TabIndex = 9;
			this->TextBox_Ambient_G->Text = L"1.0";
			// 
			// label81
			// 
			this->label81->AutoSize = true;
			this->label81->Location = System::Drawing::Point(118, 17);
			this->label81->Name = L"label81";
			this->label81->Size = System::Drawing::Size(17, 12);
			this->label81->TabIndex = 8;
			this->label81->Text = L"g:";
			// 
			// TextBox_Ambient_R
			// 
			this->TextBox_Ambient_R->Location = System::Drawing::Point(83, 13);
			this->TextBox_Ambient_R->Name = L"TextBox_Ambient_R";
			this->TextBox_Ambient_R->Size = System::Drawing::Size(29, 21);
			this->TextBox_Ambient_R->TabIndex = 7;
			this->TextBox_Ambient_R->Text = L"1.0";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(71, 17);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(17, 12);
			this->label30->TabIndex = 6;
			this->label30->Text = L"r:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(4, 67);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(65, 12);
			this->label11->TabIndex = 4;
			this->label11->Text = L"镜面反射光";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(3, 43);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(53, 12);
			this->label8->TabIndex = 2;
			this->label8->Text = L"漫反射光";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(2, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"环境光";
			// 
			// groupBox27
			// 
			this->groupBox27->Controls->Add(this->label65);
			this->groupBox27->Controls->Add(this->terrainLightingParameterW_txt);
			this->groupBox27->Controls->Add(this->label64);
			this->groupBox27->Controls->Add(this->terrainLightingParameterZ_txt);
			this->groupBox27->Controls->Add(this->label63);
			this->groupBox27->Controls->Add(this->terrainLightingParameterY_txt);
			this->groupBox27->Controls->Add(this->label66);
			this->groupBox27->Controls->Add(this->terrainLightingParameterX_txt);
			this->groupBox27->Location = System::Drawing::Point(19, 357);
			this->groupBox27->Name = L"groupBox27";
			this->groupBox27->Size = System::Drawing::Size(200, 127);
			this->groupBox27->TabIndex = 15;
			this->groupBox27->TabStop = false;
			this->groupBox27->Text = L"地形光照参数";
			// 
			// label65
			// 
			this->label65->AutoSize = true;
			this->label65->Location = System::Drawing::Point(12, 104);
			this->label65->Name = L"label65";
			this->label65->Size = System::Drawing::Size(41, 12);
			this->label65->TabIndex = 8;
			this->label65->Text = L"参数4:";
			// 
			// terrainLightingParameterW_txt
			// 
			this->terrainLightingParameterW_txt->Location = System::Drawing::Point(158, 100);
			this->terrainLightingParameterW_txt->Name = L"terrainLightingParameterW_txt";
			this->terrainLightingParameterW_txt->Size = System::Drawing::Size(34, 21);
			this->terrainLightingParameterW_txt->TabIndex = 7;
			this->terrainLightingParameterW_txt->Text = L"0";
			// 
			// label64
			// 
			this->label64->AutoSize = true;
			this->label64->Location = System::Drawing::Point(11, 76);
			this->label64->Name = L"label64";
			this->label64->Size = System::Drawing::Size(41, 12);
			this->label64->TabIndex = 6;
			this->label64->Text = L"参数3:";
			// 
			// terrainLightingParameterZ_txt
			// 
			this->terrainLightingParameterZ_txt->Location = System::Drawing::Point(157, 72);
			this->terrainLightingParameterZ_txt->Name = L"terrainLightingParameterZ_txt";
			this->terrainLightingParameterZ_txt->Size = System::Drawing::Size(34, 21);
			this->terrainLightingParameterZ_txt->TabIndex = 5;
			this->terrainLightingParameterZ_txt->Text = L"0";
			// 
			// label63
			// 
			this->label63->AutoSize = true;
			this->label63->Location = System::Drawing::Point(10, 47);
			this->label63->Name = L"label63";
			this->label63->Size = System::Drawing::Size(137, 12);
			this->label63->TabIndex = 4;
			this->label63->Text = L"满反射光法线基数(0-1):";
			// 
			// terrainLightingParameterY_txt
			// 
			this->terrainLightingParameterY_txt->Location = System::Drawing::Point(157, 44);
			this->terrainLightingParameterY_txt->Name = L"terrainLightingParameterY_txt";
			this->terrainLightingParameterY_txt->Size = System::Drawing::Size(34, 21);
			this->terrainLightingParameterY_txt->TabIndex = 3;
			this->terrainLightingParameterY_txt->Text = L"0";
			// 
			// label66
			// 
			this->label66->AutoSize = true;
			this->label66->Location = System::Drawing::Point(10, 21);
			this->label66->Name = L"label66";
			this->label66->Size = System::Drawing::Size(125, 12);
			this->label66->TabIndex = 2;
			this->label66->Text = L"环境光法线基数(0-1):";
			// 
			// terrainLightingParameterX_txt
			// 
			this->terrainLightingParameterX_txt->Location = System::Drawing::Point(157, 16);
			this->terrainLightingParameterX_txt->Name = L"terrainLightingParameterX_txt";
			this->terrainLightingParameterX_txt->Size = System::Drawing::Size(34, 21);
			this->terrainLightingParameterX_txt->TabIndex = 1;
			this->terrainLightingParameterX_txt->Text = L"0.5";
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->button8);
			this->groupBox6->Location = System::Drawing::Point(19, 301);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(200, 50);
			this->groupBox6->TabIndex = 4;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"光照方向";
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(112, 21);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(75, 23);
			this->button8->TabIndex = 2;
			this->button8->Text = L"取值";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MainForm::button8_Click_1);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(155, 628);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(75, 23);
			this->button7->TabIndex = 1;
			this->button7->Text = L"响应";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MainForm::button7_Click);
			// 
			// config_video_page
			// 
			this->config_video_page->Controls->Add(this->groupBox39);
			this->config_video_page->Controls->Add(this->groupBox16);
			this->config_video_page->Controls->Add(this->groupBox15);
			this->config_video_page->Controls->Add(this->groupBox14);
			this->config_video_page->Controls->Add(this->groupBox11);
			this->config_video_page->Controls->Add(this->groupBox10);
			this->config_video_page->Controls->Add(this->button10);
			this->config_video_page->Controls->Add(this->groupBox9);
			this->config_video_page->Controls->Add(this->groupBox8);
			this->config_video_page->Location = System::Drawing::Point(4, 24);
			this->config_video_page->Name = L"config_video_page";
			this->config_video_page->Padding = System::Windows::Forms::Padding(3);
			this->config_video_page->Size = System::Drawing::Size(236, 657);
			this->config_video_page->TabIndex = 1;
			this->config_video_page->Text = L"渲染效果";
			this->config_video_page->UseVisualStyleBackColor = true;
			// 
			// groupBox39
			// 
			this->groupBox39->Controls->Add(this->water_reflect_check);
			this->groupBox39->Controls->Add(this->water_refract_check);
			this->groupBox39->Controls->Add(this->water_shadow_check);
			this->groupBox39->Controls->Add(this->water_alpha_check);
			this->groupBox39->Location = System::Drawing::Point(17, 77);
			this->groupBox39->Name = L"groupBox39";
			this->groupBox39->Size = System::Drawing::Size(200, 65);
			this->groupBox39->TabIndex = 14;
			this->groupBox39->TabStop = false;
			this->groupBox39->Text = L"水";
			// 
			// water_reflect_check
			// 
			this->water_reflect_check->AutoSize = true;
			this->water_reflect_check->Checked = true;
			this->water_reflect_check->CheckState = System::Windows::Forms::CheckState::Checked;
			this->water_reflect_check->Location = System::Drawing::Point(26, 20);
			this->water_reflect_check->Name = L"water_reflect_check";
			this->water_reflect_check->Size = System::Drawing::Size(48, 16);
			this->water_reflect_check->TabIndex = 4;
			this->water_reflect_check->Text = L"反射";
			this->water_reflect_check->UseVisualStyleBackColor = true;
			// 
			// water_refract_check
			// 
			this->water_refract_check->AutoSize = true;
			this->water_refract_check->Location = System::Drawing::Point(122, 42);
			this->water_refract_check->Name = L"water_refract_check";
			this->water_refract_check->Size = System::Drawing::Size(48, 16);
			this->water_refract_check->TabIndex = 2;
			this->water_refract_check->Text = L"折射";
			this->water_refract_check->UseVisualStyleBackColor = true;
			// 
			// water_shadow_check
			// 
			this->water_shadow_check->AutoSize = true;
			this->water_shadow_check->Location = System::Drawing::Point(122, 20);
			this->water_shadow_check->Name = L"water_shadow_check";
			this->water_shadow_check->Size = System::Drawing::Size(48, 16);
			this->water_shadow_check->TabIndex = 1;
			this->water_shadow_check->Text = L"阴影";
			this->water_shadow_check->UseVisualStyleBackColor = true;
			// 
			// water_alpha_check
			// 
			this->water_alpha_check->AutoSize = true;
			this->water_alpha_check->Location = System::Drawing::Point(26, 42);
			this->water_alpha_check->Name = L"water_alpha_check";
			this->water_alpha_check->Size = System::Drawing::Size(48, 16);
			this->water_alpha_check->TabIndex = 0;
			this->water_alpha_check->Text = L"透视";
			this->water_alpha_check->UseVisualStyleBackColor = true;
			// 
			// groupBox16
			// 
			this->groupBox16->Controls->Add(this->label32);
			this->groupBox16->Controls->Add(this->sbs_normal_txt);
			this->groupBox16->Controls->Add(this->label36);
			this->groupBox16->Controls->Add(this->sbs_specular_txt);
			this->groupBox16->Controls->Add(this->label35);
			this->groupBox16->Controls->Add(this->sbs_bias_txt);
			this->groupBox16->Controls->Add(this->label34);
			this->groupBox16->Controls->Add(this->sbs_scale_txt);
			this->groupBox16->Location = System::Drawing::Point(17, 452);
			this->groupBox16->Name = L"groupBox16";
			this->groupBox16->Size = System::Drawing::Size(200, 75);
			this->groupBox16->TabIndex = 13;
			this->groupBox16->TabStop = false;
			this->groupBox16->Text = L"BiasSpecular";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(107, 49);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(35, 12);
			this->label32->TabIndex = 8;
			this->label32->Text = L"Bump:";
			// 
			// sbs_normal_txt
			// 
			this->sbs_normal_txt->Location = System::Drawing::Point(143, 45);
			this->sbs_normal_txt->Name = L"sbs_normal_txt";
			this->sbs_normal_txt->Size = System::Drawing::Size(46, 21);
			this->sbs_normal_txt->TabIndex = 7;
			this->sbs_normal_txt->Text = L"1";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(10, 49);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(35, 12);
			this->label36->TabIndex = 6;
			this->label36->Text = L"Spec:";
			// 
			// sbs_specular_txt
			// 
			this->sbs_specular_txt->Location = System::Drawing::Point(53, 46);
			this->sbs_specular_txt->Name = L"sbs_specular_txt";
			this->sbs_specular_txt->Size = System::Drawing::Size(40, 21);
			this->sbs_specular_txt->TabIndex = 5;
			this->sbs_specular_txt->Text = L"32";
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(107, 20);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(35, 12);
			this->label35->TabIndex = 4;
			this->label35->Text = L"Bias:";
			// 
			// sbs_bias_txt
			// 
			this->sbs_bias_txt->Location = System::Drawing::Point(143, 16);
			this->sbs_bias_txt->Name = L"sbs_bias_txt";
			this->sbs_bias_txt->Size = System::Drawing::Size(46, 21);
			this->sbs_bias_txt->TabIndex = 3;
			this->sbs_bias_txt->Text = L"-0.04";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(10, 21);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(41, 12);
			this->label34->TabIndex = 2;
			this->label34->Text = L"Scale:";
			// 
			// sbs_scale_txt
			// 
			this->sbs_scale_txt->Location = System::Drawing::Point(52, 16);
			this->sbs_scale_txt->Name = L"sbs_scale_txt";
			this->sbs_scale_txt->Size = System::Drawing::Size(41, 21);
			this->sbs_scale_txt->TabIndex = 1;
			this->sbs_scale_txt->Text = L"0.03";
			// 
			// groupBox15
			// 
			this->groupBox15->Controls->Add(this->label31);
			this->groupBox15->Controls->Add(this->fsaa_txt);
			this->groupBox15->Location = System::Drawing::Point(17, 404);
			this->groupBox15->Name = L"groupBox15";
			this->groupBox15->Size = System::Drawing::Size(200, 42);
			this->groupBox15->TabIndex = 12;
			this->groupBox15->TabStop = false;
			this->groupBox15->Text = L"FSAA";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(27, 18);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(35, 12);
			this->label31->TabIndex = 2;
			this->label31->Text = L"FSAA:";
			// 
			// fsaa_txt
			// 
			this->fsaa_txt->Location = System::Drawing::Point(101, 15);
			this->fsaa_txt->Name = L"fsaa_txt";
			this->fsaa_txt->Size = System::Drawing::Size(71, 21);
			this->fsaa_txt->TabIndex = 1;
			this->fsaa_txt->Text = L"0";
			// 
			// groupBox14
			// 
			this->groupBox14->Controls->Add(this->gamma_check);
			this->groupBox14->Location = System::Drawing::Point(17, 356);
			this->groupBox14->Name = L"groupBox14";
			this->groupBox14->Size = System::Drawing::Size(200, 42);
			this->groupBox14->TabIndex = 11;
			this->groupBox14->TabStop = false;
			this->groupBox14->Text = L"Gamma";
			// 
			// gamma_check
			// 
			this->gamma_check->AutoSize = true;
			this->gamma_check->Location = System::Drawing::Point(31, 20);
			this->gamma_check->Name = L"gamma_check";
			this->gamma_check->Size = System::Drawing::Size(96, 16);
			this->gamma_check->TabIndex = 0;
			this->gamma_check->Text = L"是否伽玛矫正";
			this->gamma_check->UseVisualStyleBackColor = true;
			// 
			// groupBox11
			// 
			this->groupBox11->Controls->Add(this->label18);
			this->groupBox11->Controls->Add(this->txt_mipmap_bias);
			this->groupBox11->Location = System::Drawing::Point(17, 224);
			this->groupBox11->Name = L"groupBox11";
			this->groupBox11->Size = System::Drawing::Size(200, 44);
			this->groupBox11->TabIndex = 8;
			this->groupBox11->TabStop = false;
			this->groupBox11->Text = L"Mipmap";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(15, 20);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(47, 12);
			this->label18->TabIndex = 1;
			this->label18->Text = L"偏移量:";
			// 
			// txt_mipmap_bias
			// 
			this->txt_mipmap_bias->Location = System::Drawing::Point(110, 16);
			this->txt_mipmap_bias->Name = L"txt_mipmap_bias";
			this->txt_mipmap_bias->Size = System::Drawing::Size(71, 21);
			this->txt_mipmap_bias->TabIndex = 0;
			this->txt_mipmap_bias->Text = L"-1";
			// 
			// groupBox10
			// 
			this->groupBox10->Controls->Add(this->rb_tex_filter_anisotropic);
			this->groupBox10->Controls->Add(this->rb_tex_filter_3line);
			this->groupBox10->Controls->Add(this->rb_tex_filter_bline);
			this->groupBox10->Controls->Add(this->rb_tex_filter_none);
			this->groupBox10->Location = System::Drawing::Point(17, 148);
			this->groupBox10->Name = L"groupBox10";
			this->groupBox10->Size = System::Drawing::Size(200, 70);
			this->groupBox10->TabIndex = 7;
			this->groupBox10->TabStop = false;
			this->groupBox10->Text = L"纹理质量";
			// 
			// rb_tex_filter_anisotropic
			// 
			this->rb_tex_filter_anisotropic->AutoSize = true;
			this->rb_tex_filter_anisotropic->Location = System::Drawing::Point(101, 48);
			this->rb_tex_filter_anisotropic->Name = L"rb_tex_filter_anisotropic";
			this->rb_tex_filter_anisotropic->Size = System::Drawing::Size(95, 16);
			this->rb_tex_filter_anisotropic->TabIndex = 3;
			this->rb_tex_filter_anisotropic->Text = L"各向异性插值";
			this->rb_tex_filter_anisotropic->UseVisualStyleBackColor = true;
			// 
			// rb_tex_filter_3line
			// 
			this->rb_tex_filter_3line->AutoSize = true;
			this->rb_tex_filter_3line->Location = System::Drawing::Point(15, 48);
			this->rb_tex_filter_3line->Name = L"rb_tex_filter_3line";
			this->rb_tex_filter_3line->Size = System::Drawing::Size(83, 16);
			this->rb_tex_filter_3line->TabIndex = 2;
			this->rb_tex_filter_3line->Text = L"三线性插值";
			this->rb_tex_filter_3line->UseVisualStyleBackColor = true;
			// 
			// rb_tex_filter_bline
			// 
			this->rb_tex_filter_bline->AutoSize = true;
			this->rb_tex_filter_bline->Checked = true;
			this->rb_tex_filter_bline->Location = System::Drawing::Point(101, 21);
			this->rb_tex_filter_bline->Name = L"rb_tex_filter_bline";
			this->rb_tex_filter_bline->Size = System::Drawing::Size(83, 16);
			this->rb_tex_filter_bline->TabIndex = 1;
			this->rb_tex_filter_bline->TabStop = true;
			this->rb_tex_filter_bline->Text = L"双线性插值";
			this->rb_tex_filter_bline->UseVisualStyleBackColor = true;
			// 
			// rb_tex_filter_none
			// 
			this->rb_tex_filter_none->AutoSize = true;
			this->rb_tex_filter_none->Location = System::Drawing::Point(15, 21);
			this->rb_tex_filter_none->Name = L"rb_tex_filter_none";
			this->rb_tex_filter_none->Size = System::Drawing::Size(59, 16);
			this->rb_tex_filter_none->TabIndex = 0;
			this->rb_tex_filter_none->Text = L"无插值";
			this->rb_tex_filter_none->UseVisualStyleBackColor = true;
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(142, 613);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(75, 23);
			this->button10->TabIndex = 6;
			this->button10->Text = L"响应操作";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MainForm::button10_Click);
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->model_sa_tex_check);
			this->groupBox9->Controls->Add(this->model_normal_tex_check);
			this->groupBox9->Controls->Add(this->model_shadow_dynamic_check);
			this->groupBox9->Controls->Add(this->model_shadow_tex_check);
			this->groupBox9->Location = System::Drawing::Point(17, 282);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(200, 68);
			this->groupBox9->TabIndex = 5;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"模型";
			// 
			// model_sa_tex_check
			// 
			this->model_sa_tex_check->AutoSize = true;
			this->model_sa_tex_check->Location = System::Drawing::Point(101, 44);
			this->model_sa_tex_check->Name = L"model_sa_tex_check";
			this->model_sa_tex_check->Size = System::Drawing::Size(96, 16);
			this->model_sa_tex_check->TabIndex = 4;
			this->model_sa_tex_check->Text = L"高光和AO贴图";
			this->model_sa_tex_check->UseVisualStyleBackColor = true;
			// 
			// model_normal_tex_check
			// 
			this->model_normal_tex_check->AutoSize = true;
			this->model_normal_tex_check->Location = System::Drawing::Point(17, 44);
			this->model_normal_tex_check->Name = L"model_normal_tex_check";
			this->model_normal_tex_check->Size = System::Drawing::Size(72, 16);
			this->model_normal_tex_check->TabIndex = 3;
			this->model_normal_tex_check->Text = L"法线贴图";
			this->model_normal_tex_check->UseVisualStyleBackColor = true;
			// 
			// model_shadow_dynamic_check
			// 
			this->model_shadow_dynamic_check->AutoSize = true;
			this->model_shadow_dynamic_check->Location = System::Drawing::Point(101, 20);
			this->model_shadow_dynamic_check->Name = L"model_shadow_dynamic_check";
			this->model_shadow_dynamic_check->Size = System::Drawing::Size(72, 16);
			this->model_shadow_dynamic_check->TabIndex = 2;
			this->model_shadow_dynamic_check->Text = L"动态阴影";
			this->model_shadow_dynamic_check->UseVisualStyleBackColor = true;
			// 
			// model_shadow_tex_check
			// 
			this->model_shadow_tex_check->AutoSize = true;
			this->model_shadow_tex_check->Location = System::Drawing::Point(17, 20);
			this->model_shadow_tex_check->Name = L"model_shadow_tex_check";
			this->model_shadow_tex_check->Size = System::Drawing::Size(72, 16);
			this->model_shadow_tex_check->TabIndex = 1;
			this->model_shadow_tex_check->Text = L"阴影贴图";
			this->model_shadow_tex_check->UseVisualStyleBackColor = true;
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->terrain_color_check);
			this->groupBox8->Controls->Add(this->terrain_offset_check);
			this->groupBox8->Controls->Add(this->terrain_spec_check);
			this->groupBox8->Controls->Add(this->terrain_normal_check);
			this->groupBox8->Location = System::Drawing::Point(17, 7);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(200, 65);
			this->groupBox8->TabIndex = 4;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"地形";
			// 
			// terrain_color_check
			// 
			this->terrain_color_check->AutoSize = true;
			this->terrain_color_check->Checked = true;
			this->terrain_color_check->CheckState = System::Windows::Forms::CheckState::Checked;
			this->terrain_color_check->Location = System::Drawing::Point(26, 20);
			this->terrain_color_check->Name = L"terrain_color_check";
			this->terrain_color_check->Size = System::Drawing::Size(72, 16);
			this->terrain_color_check->TabIndex = 4;
			this->terrain_color_check->Text = L"颜色贴图";
			this->terrain_color_check->UseVisualStyleBackColor = true;
			// 
			// terrain_offset_check
			// 
			this->terrain_offset_check->AutoSize = true;
			this->terrain_offset_check->Location = System::Drawing::Point(122, 42);
			this->terrain_offset_check->Name = L"terrain_offset_check";
			this->terrain_offset_check->Size = System::Drawing::Size(72, 16);
			this->terrain_offset_check->TabIndex = 2;
			this->terrain_offset_check->Text = L"视差贴图";
			this->terrain_offset_check->UseVisualStyleBackColor = true;
			// 
			// terrain_spec_check
			// 
			this->terrain_spec_check->AutoSize = true;
			this->terrain_spec_check->Location = System::Drawing::Point(122, 20);
			this->terrain_spec_check->Name = L"terrain_spec_check";
			this->terrain_spec_check->Size = System::Drawing::Size(72, 16);
			this->terrain_spec_check->TabIndex = 1;
			this->terrain_spec_check->Text = L"高光贴图";
			this->terrain_spec_check->UseVisualStyleBackColor = true;
			// 
			// terrain_normal_check
			// 
			this->terrain_normal_check->AutoSize = true;
			this->terrain_normal_check->Location = System::Drawing::Point(26, 42);
			this->terrain_normal_check->Name = L"terrain_normal_check";
			this->terrain_normal_check->Size = System::Drawing::Size(72, 16);
			this->terrain_normal_check->TabIndex = 0;
			this->terrain_normal_check->Text = L"法线贴图";
			this->terrain_normal_check->UseVisualStyleBackColor = true;
			// 
			// config_plant_page
			// 
			this->config_plant_page->Controls->Add(this->groupBox38);
			this->config_plant_page->Controls->Add(this->groupBox33);
			this->config_plant_page->Controls->Add(this->button20);
			this->config_plant_page->Location = System::Drawing::Point(4, 24);
			this->config_plant_page->Name = L"config_plant_page";
			this->config_plant_page->Padding = System::Windows::Forms::Padding(3);
			this->config_plant_page->Size = System::Drawing::Size(236, 657);
			this->config_plant_page->TabIndex = 7;
			this->config_plant_page->Text = L"植被";
			this->config_plant_page->UseVisualStyleBackColor = true;
			// 
			// groupBox38
			// 
			this->groupBox38->Controls->Add(this->label50);
			this->groupBox38->Controls->Add(this->textBox_grassLod_end);
			this->groupBox38->Controls->Add(this->label_grassLod_start);
			this->groupBox38->Controls->Add(this->textBox_grassLod_start);
			this->groupBox38->Location = System::Drawing::Point(6, 205);
			this->groupBox38->Name = L"groupBox38";
			this->groupBox38->Size = System::Drawing::Size(212, 54);
			this->groupBox38->TabIndex = 12;
			this->groupBox38->TabStop = false;
			this->groupBox38->Text = L"草Lod";
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->Location = System::Drawing::Point(109, 23);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(29, 12);
			this->label50->TabIndex = 11;
			this->label50->Text = L"end:";
			// 
			// textBox_grassLod_end
			// 
			this->textBox_grassLod_end->Location = System::Drawing::Point(144, 20);
			this->textBox_grassLod_end->Name = L"textBox_grassLod_end";
			this->textBox_grassLod_end->Size = System::Drawing::Size(33, 21);
			this->textBox_grassLod_end->TabIndex = 10;
			this->textBox_grassLod_end->Text = L"200";
			// 
			// label_grassLod_start
			// 
			this->label_grassLod_start->AutoSize = true;
			this->label_grassLod_start->Location = System::Drawing::Point(11, 23);
			this->label_grassLod_start->Name = L"label_grassLod_start";
			this->label_grassLod_start->Size = System::Drawing::Size(41, 12);
			this->label_grassLod_start->TabIndex = 7;
			this->label_grassLod_start->Text = L"start:";
			// 
			// textBox_grassLod_start
			// 
			this->textBox_grassLod_start->Location = System::Drawing::Point(58, 20);
			this->textBox_grassLod_start->Name = L"textBox_grassLod_start";
			this->textBox_grassLod_start->Size = System::Drawing::Size(33, 21);
			this->textBox_grassLod_start->TabIndex = 6;
			this->textBox_grassLod_start->Text = L"100";
			// 
			// groupBox33
			// 
			this->groupBox33->Controls->Add(this->wind_check);
			this->groupBox33->Controls->Add(this->groupBox35);
			this->groupBox33->Controls->Add(this->groupBox34);
			this->groupBox33->Controls->Add(this->label78);
			this->groupBox33->Controls->Add(this->label79);
			this->groupBox33->Location = System::Drawing::Point(6, 14);
			this->groupBox33->Name = L"groupBox33";
			this->groupBox33->Size = System::Drawing::Size(224, 173);
			this->groupBox33->TabIndex = 4;
			this->groupBox33->TabStop = false;
			this->groupBox33->Text = L"风参数";
			// 
			// wind_check
			// 
			this->wind_check->AutoSize = true;
			this->wind_check->Location = System::Drawing::Point(7, 18);
			this->wind_check->Name = L"wind_check";
			this->wind_check->Size = System::Drawing::Size(60, 16);
			this->wind_check->TabIndex = 11;
			this->wind_check->Text = L"启用风";
			this->wind_check->UseVisualStyleBackColor = true;
			this->wind_check->CheckedChanged += gcnew System::EventHandler(this, &MainForm::wind_check_CheckedChanged);
			// 
			// groupBox35
			// 
			this->groupBox35->Controls->Add(this->lableWindIntensity);
			this->groupBox35->Controls->Add(this->TrackBarWindIntensity);
			this->groupBox35->Location = System::Drawing::Point(6, 100);
			this->groupBox35->Name = L"groupBox35";
			this->groupBox35->Size = System::Drawing::Size(212, 64);
			this->groupBox35->TabIndex = 10;
			this->groupBox35->TabStop = false;
			this->groupBox35->Text = L"强度";
			// 
			// lableWindIntensity
			// 
			this->lableWindIntensity->AutoSize = true;
			this->lableWindIntensity->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->lableWindIntensity->Location = System::Drawing::Point(13, 26);
			this->lableWindIntensity->Name = L"lableWindIntensity";
			this->lableWindIntensity->Size = System::Drawing::Size(31, 14);
			this->lableWindIntensity->TabIndex = 8;
			this->lableWindIntensity->Text = L"0.10";
			// 
			// TrackBarWindIntensity
			// 
			this->TrackBarWindIntensity->Location = System::Drawing::Point(60, 15);
			this->TrackBarWindIntensity->Name = L"TrackBarWindIntensity";
			this->TrackBarWindIntensity->Size = System::Drawing::Size(146, 45);
			this->TrackBarWindIntensity->TabIndex = 7;
			this->TrackBarWindIntensity->TickStyle = System::Windows::Forms::TickStyle::TopLeft;
			this->TrackBarWindIntensity->Value = 1;
			this->TrackBarWindIntensity->ValueChanged += gcnew System::EventHandler(this, &MainForm::TrackBarWindIntensity_ValueChanged);
			// 
			// groupBox34
			// 
			this->groupBox34->Controls->Add(this->label67);
			this->groupBox34->Controls->Add(this->textBoxWindDirZ);
			this->groupBox34->Controls->Add(this->label76);
			this->groupBox34->Controls->Add(this->textBoxWindDirY);
			this->groupBox34->Controls->Add(this->label77);
			this->groupBox34->Controls->Add(this->textBoxWindDirX);
			this->groupBox34->Location = System::Drawing::Point(6, 41);
			this->groupBox34->Name = L"groupBox34";
			this->groupBox34->Size = System::Drawing::Size(212, 54);
			this->groupBox34->TabIndex = 9;
			this->groupBox34->TabStop = false;
			this->groupBox34->Text = L"方向";
			// 
			// label67
			// 
			this->label67->AutoSize = true;
			this->label67->Location = System::Drawing::Point(142, 23);
			this->label67->Name = L"label67";
			this->label67->Size = System::Drawing::Size(17, 12);
			this->label67->TabIndex = 11;
			this->label67->Text = L"z:";
			// 
			// textBoxWindDirZ
			// 
			this->textBoxWindDirZ->Location = System::Drawing::Point(165, 20);
			this->textBoxWindDirZ->Name = L"textBoxWindDirZ";
			this->textBoxWindDirZ->Size = System::Drawing::Size(33, 21);
			this->textBoxWindDirZ->TabIndex = 10;
			this->textBoxWindDirZ->Text = L"-1.0";
			// 
			// label76
			// 
			this->label76->AutoSize = true;
			this->label76->Location = System::Drawing::Point(76, 23);
			this->label76->Name = L"label76";
			this->label76->Size = System::Drawing::Size(17, 12);
			this->label76->TabIndex = 9;
			this->label76->Text = L"y:";
			// 
			// textBoxWindDirY
			// 
			this->textBoxWindDirY->Location = System::Drawing::Point(99, 20);
			this->textBoxWindDirY->Name = L"textBoxWindDirY";
			this->textBoxWindDirY->Size = System::Drawing::Size(33, 21);
			this->textBoxWindDirY->TabIndex = 8;
			this->textBoxWindDirY->Text = L"0.0";
			// 
			// label77
			// 
			this->label77->AutoSize = true;
			this->label77->Location = System::Drawing::Point(11, 23);
			this->label77->Name = L"label77";
			this->label77->Size = System::Drawing::Size(17, 12);
			this->label77->TabIndex = 7;
			this->label77->Text = L"x:";
			// 
			// textBoxWindDirX
			// 
			this->textBoxWindDirX->Location = System::Drawing::Point(34, 20);
			this->textBoxWindDirX->Name = L"textBoxWindDirX";
			this->textBoxWindDirX->Size = System::Drawing::Size(33, 21);
			this->textBoxWindDirX->TabIndex = 6;
			this->textBoxWindDirX->Text = L"0.0";
			// 
			// label78
			// 
			this->label78->AutoSize = true;
			this->label78->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label78->Location = System::Drawing::Point(48, 55);
			this->label78->Name = L"label78";
			this->label78->Size = System::Drawing::Size(31, 14);
			this->label78->TabIndex = 8;
			this->label78->Text = L"2.00";
			// 
			// label79
			// 
			this->label79->AutoSize = true;
			this->label79->Location = System::Drawing::Point(7, 55);
			this->label79->Name = L"label79";
			this->label79->Size = System::Drawing::Size(35, 12);
			this->label79->TabIndex = 6;
			this->label79->Text = L"速度:";
			// 
			// button20
			// 
			this->button20->Location = System::Drawing::Point(37, 610);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(165, 23);
			this->button20->TabIndex = 2;
			this->button20->Text = L"响应";
			this->button20->UseVisualStyleBackColor = true;
			this->button20->Click += gcnew System::EventHandler(this, &MainForm::button20_Click);
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->groupBox32);
			this->tabPage1->Controls->Add(this->groupBox31);
			this->tabPage1->Controls->Add(this->groupBox18);
			this->tabPage1->Controls->Add(this->groupBox17);
			this->tabPage1->Controls->Add(this->button9);
			this->tabPage1->Controls->Add(this->groupBox7);
			this->tabPage1->Location = System::Drawing::Point(4, 24);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(236, 657);
			this->tabPage1->TabIndex = 2;
			this->tabPage1->Text = L"基础";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// groupBox32
			// 
			this->groupBox32->Controls->Add(this->ckb_water_visible);
			this->groupBox32->Location = System::Drawing::Point(15, 247);
			this->groupBox32->Name = L"groupBox32";
			this->groupBox32->Size = System::Drawing::Size(200, 50);
			this->groupBox32->TabIndex = 6;
			this->groupBox32->TabStop = false;
			this->groupBox32->Text = L"水";
			// 
			// ckb_water_visible
			// 
			this->ckb_water_visible->AutoSize = true;
			this->ckb_water_visible->Checked = true;
			this->ckb_water_visible->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ckb_water_visible->Location = System::Drawing::Point(18, 20);
			this->ckb_water_visible->Name = L"ckb_water_visible";
			this->ckb_water_visible->Size = System::Drawing::Size(72, 16);
			this->ckb_water_visible->TabIndex = 5;
			this->ckb_water_visible->Text = L"水面显示";
			this->ckb_water_visible->UseVisualStyleBackColor = true;
			// 
			// groupBox31
			// 
			this->groupBox31->Controls->Add(this->ckb_entity_visible);
			this->groupBox31->Location = System::Drawing::Point(15, 326);
			this->groupBox31->Name = L"groupBox31";
			this->groupBox31->Size = System::Drawing::Size(200, 50);
			this->groupBox31->TabIndex = 5;
			this->groupBox31->TabStop = false;
			this->groupBox31->Text = L"物件";
			// 
			// ckb_entity_visible
			// 
			this->ckb_entity_visible->AutoSize = true;
			this->ckb_entity_visible->Checked = true;
			this->ckb_entity_visible->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ckb_entity_visible->Location = System::Drawing::Point(18, 20);
			this->ckb_entity_visible->Name = L"ckb_entity_visible";
			this->ckb_entity_visible->Size = System::Drawing::Size(72, 16);
			this->ckb_entity_visible->TabIndex = 5;
			this->ckb_entity_visible->Text = L"物件显示";
			this->ckb_entity_visible->UseVisualStyleBackColor = true;
			// 
			// groupBox18
			// 
			this->groupBox18->Controls->Add(this->ckb_terrain_grids_visible);
			this->groupBox18->Location = System::Drawing::Point(15, 175);
			this->groupBox18->Name = L"groupBox18";
			this->groupBox18->Size = System::Drawing::Size(200, 50);
			this->groupBox18->TabIndex = 4;
			this->groupBox18->TabStop = false;
			this->groupBox18->Text = L"地形";
			// 
			// ckb_terrain_grids_visible
			// 
			this->ckb_terrain_grids_visible->AutoSize = true;
			this->ckb_terrain_grids_visible->Location = System::Drawing::Point(18, 20);
			this->ckb_terrain_grids_visible->Name = L"ckb_terrain_grids_visible";
			this->ckb_terrain_grids_visible->Size = System::Drawing::Size(96, 16);
			this->ckb_terrain_grids_visible->TabIndex = 5;
			this->ckb_terrain_grids_visible->Text = L"地形网格显示";
			this->ckb_terrain_grids_visible->UseVisualStyleBackColor = true;
			// 
			// groupBox17
			// 
			this->groupBox17->Controls->Add(this->ckb_wireframe);
			this->groupBox17->Location = System::Drawing::Point(15, 100);
			this->groupBox17->Name = L"groupBox17";
			this->groupBox17->Size = System::Drawing::Size(200, 50);
			this->groupBox17->TabIndex = 3;
			this->groupBox17->TabStop = false;
			this->groupBox17->Text = L"模式";
			// 
			// ckb_wireframe
			// 
			this->ckb_wireframe->AutoSize = true;
			this->ckb_wireframe->Location = System::Drawing::Point(18, 20);
			this->ckb_wireframe->Name = L"ckb_wireframe";
			this->ckb_wireframe->Size = System::Drawing::Size(72, 16);
			this->ckb_wireframe->TabIndex = 5;
			this->ckb_wireframe->Text = L"线框模式";
			this->ckb_wireframe->UseVisualStyleBackColor = true;
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(155, 613);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(75, 23);
			this->button9->TabIndex = 2;
			this->button9->Text = L"响应";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MainForm::button9_Click_1);
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->label21);
			this->groupBox7->Controls->Add(this->fov_edit);
			this->groupBox7->Location = System::Drawing::Point(15, 26);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(200, 50);
			this->groupBox7->TabIndex = 1;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"摄像机";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(7, 21);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(29, 12);
			this->label21->TabIndex = 1;
			this->label21->Text = L"FOV:";
			// 
			// fov_edit
			// 
			this->fov_edit->Location = System::Drawing::Point(42, 18);
			this->fov_edit->Name = L"fov_edit";
			this->fov_edit->Size = System::Drawing::Size(58, 21);
			this->fov_edit->TabIndex = 0;
			this->fov_edit->Text = L"0.5";
			// 
			// tabPage9
			// 
			this->tabPage9->Controls->Add(this->button13);
			this->tabPage9->Controls->Add(this->groupBox23);
			this->tabPage9->Controls->Add(this->groupBox22);
			this->tabPage9->Controls->Add(this->groupBox13);
			this->tabPage9->Location = System::Drawing::Point(4, 24);
			this->tabPage9->Name = L"tabPage9";
			this->tabPage9->Padding = System::Windows::Forms::Padding(3);
			this->tabPage9->Size = System::Drawing::Size(236, 657);
			this->tabPage9->TabIndex = 3;
			this->tabPage9->Text = L"雾效果";
			this->tabPage9->UseVisualStyleBackColor = true;
			// 
			// button13
			// 
			this->button13->Location = System::Drawing::Point(145, 613);
			this->button13->Name = L"button13";
			this->button13->Size = System::Drawing::Size(75, 23);
			this->button13->TabIndex = 14;
			this->button13->Text = L"响应";
			this->button13->UseVisualStyleBackColor = true;
			this->button13->Click += gcnew System::EventHandler(this, &MainForm::button13_Click);
			// 
			// groupBox23
			// 
			this->groupBox23->Controls->Add(this->label53);
			this->groupBox23->Controls->Add(this->txt_fog_color_b);
			this->groupBox23->Controls->Add(this->label54);
			this->groupBox23->Controls->Add(this->txt_fog_color_g);
			this->groupBox23->Controls->Add(this->label55);
			this->groupBox23->Controls->Add(this->txt_fog_color_r);
			this->groupBox23->Location = System::Drawing::Point(20, 98);
			this->groupBox23->Name = L"groupBox23";
			this->groupBox23->Size = System::Drawing::Size(200, 50);
			this->groupBox23->TabIndex = 13;
			this->groupBox23->TabStop = false;
			this->groupBox23->Text = L"颜色";
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->Location = System::Drawing::Point(138, 21);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(17, 12);
			this->label53->TabIndex = 5;
			this->label53->Text = L"b:";
			// 
			// txt_fog_color_b
			// 
			this->txt_fog_color_b->Location = System::Drawing::Point(161, 18);
			this->txt_fog_color_b->Name = L"txt_fog_color_b";
			this->txt_fog_color_b->Size = System::Drawing::Size(31, 21);
			this->txt_fog_color_b->TabIndex = 4;
			this->txt_fog_color_b->Text = L"1";
			// 
			// label54
			// 
			this->label54->AutoSize = true;
			this->label54->Location = System::Drawing::Point(72, 21);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(17, 12);
			this->label54->TabIndex = 3;
			this->label54->Text = L"g:";
			// 
			// txt_fog_color_g
			// 
			this->txt_fog_color_g->Location = System::Drawing::Point(95, 18);
			this->txt_fog_color_g->Name = L"txt_fog_color_g";
			this->txt_fog_color_g->Size = System::Drawing::Size(32, 21);
			this->txt_fog_color_g->TabIndex = 2;
			this->txt_fog_color_g->Text = L"1";
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->Location = System::Drawing::Point(7, 21);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(17, 12);
			this->label55->TabIndex = 1;
			this->label55->Text = L"r:";
			// 
			// txt_fog_color_r
			// 
			this->txt_fog_color_r->Location = System::Drawing::Point(30, 18);
			this->txt_fog_color_r->Name = L"txt_fog_color_r";
			this->txt_fog_color_r->Size = System::Drawing::Size(32, 21);
			this->txt_fog_color_r->TabIndex = 0;
			this->txt_fog_color_r->Text = L"1";
			// 
			// groupBox22
			// 
			this->groupBox22->Controls->Add(this->label56);
			this->groupBox22->Controls->Add(this->txt_fog_end);
			this->groupBox22->Controls->Add(this->label57);
			this->groupBox22->Controls->Add(this->txt_fog_start);
			this->groupBox22->Controls->Add(this->label58);
			this->groupBox22->Controls->Add(this->txt_fog_exp);
			this->groupBox22->Location = System::Drawing::Point(20, 154);
			this->groupBox22->Name = L"groupBox22";
			this->groupBox22->Size = System::Drawing::Size(200, 159);
			this->groupBox22->TabIndex = 12;
			this->groupBox22->TabStop = false;
			this->groupBox22->Text = L"参数";
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->Location = System::Drawing::Point(8, 130);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(59, 12);
			this->label56->TabIndex = 11;
			this->label56->Text = L"结束距离:";
			// 
			// txt_fog_end
			// 
			this->txt_fog_end->Location = System::Drawing::Point(74, 124);
			this->txt_fog_end->Name = L"txt_fog_end";
			this->txt_fog_end->Size = System::Drawing::Size(88, 21);
			this->txt_fog_end->TabIndex = 10;
			this->txt_fog_end->Text = L"1000";
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->Location = System::Drawing::Point(8, 78);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(59, 12);
			this->label57->TabIndex = 9;
			this->label57->Text = L"开始距离:";
			// 
			// txt_fog_start
			// 
			this->txt_fog_start->Location = System::Drawing::Point(74, 75);
			this->txt_fog_start->Name = L"txt_fog_start";
			this->txt_fog_start->Size = System::Drawing::Size(88, 21);
			this->txt_fog_start->TabIndex = 8;
			this->txt_fog_start->Text = L"0";
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->Location = System::Drawing::Point(8, 27);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(59, 12);
			this->label58->TabIndex = 7;
			this->label58->Text = L"指数强度:";
			// 
			// txt_fog_exp
			// 
			this->txt_fog_exp->Location = System::Drawing::Point(73, 24);
			this->txt_fog_exp->Name = L"txt_fog_exp";
			this->txt_fog_exp->Size = System::Drawing::Size(89, 21);
			this->txt_fog_exp->TabIndex = 6;
			this->txt_fog_exp->Text = L"0.002";
			// 
			// groupBox13
			// 
			this->groupBox13->Controls->Add(this->rb_fog_exp);
			this->groupBox13->Controls->Add(this->rb_fog_line);
			this->groupBox13->Controls->Add(this->rb_fog_none);
			this->groupBox13->Location = System::Drawing::Point(20, 23);
			this->groupBox13->Name = L"groupBox13";
			this->groupBox13->Size = System::Drawing::Size(200, 69);
			this->groupBox13->TabIndex = 11;
			this->groupBox13->TabStop = false;
			this->groupBox13->Text = L"雾";
			// 
			// rb_fog_exp
			// 
			this->rb_fog_exp->AutoSize = true;
			this->rb_fog_exp->Location = System::Drawing::Point(17, 47);
			this->rb_fog_exp->Name = L"rb_fog_exp";
			this->rb_fog_exp->Size = System::Drawing::Size(59, 16);
			this->rb_fog_exp->TabIndex = 5;
			this->rb_fog_exp->Text = L"指数雾";
			this->rb_fog_exp->UseVisualStyleBackColor = true;
			// 
			// rb_fog_line
			// 
			this->rb_fog_line->AutoSize = true;
			this->rb_fog_line->Location = System::Drawing::Point(103, 20);
			this->rb_fog_line->Name = L"rb_fog_line";
			this->rb_fog_line->Size = System::Drawing::Size(59, 16);
			this->rb_fog_line->TabIndex = 4;
			this->rb_fog_line->Text = L"线性雾";
			this->rb_fog_line->UseVisualStyleBackColor = true;
			// 
			// rb_fog_none
			// 
			this->rb_fog_none->AutoSize = true;
			this->rb_fog_none->Checked = true;
			this->rb_fog_none->Location = System::Drawing::Point(17, 20);
			this->rb_fog_none->Name = L"rb_fog_none";
			this->rb_fog_none->Size = System::Drawing::Size(47, 16);
			this->rb_fog_none->TabIndex = 3;
			this->rb_fog_none->TabStop = true;
			this->rb_fog_none->Text = L"无雾";
			this->rb_fog_none->UseVisualStyleBackColor = true;
			// 
			// tabPage10
			// 
			this->tabPage10->Controls->Add(this->groupBox24);
			this->tabPage10->Controls->Add(this->button14);
			this->tabPage10->Controls->Add(this->groupBox20);
			this->tabPage10->Controls->Add(this->groupBox12);
			this->tabPage10->Controls->Add(this->groupBox19);
			this->tabPage10->Location = System::Drawing::Point(4, 24);
			this->tabPage10->Name = L"tabPage10";
			this->tabPage10->Padding = System::Windows::Forms::Padding(3);
			this->tabPage10->Size = System::Drawing::Size(236, 657);
			this->tabPage10->TabIndex = 4;
			this->tabPage10->Text = L"阴影";
			this->tabPage10->UseVisualStyleBackColor = true;
			// 
			// groupBox24
			// 
			this->groupBox24->Controls->Add(this->label59);
			this->groupBox24->Controls->Add(this->shadowParameterZ_txt);
			this->groupBox24->Controls->Add(this->label60);
			this->groupBox24->Controls->Add(this->shadowParameterW_txt);
			this->groupBox24->Controls->Add(this->label61);
			this->groupBox24->Controls->Add(this->shadowParameterY_txt);
			this->groupBox24->Controls->Add(this->label62);
			this->groupBox24->Controls->Add(this->shadowParameterX_txt);
			this->groupBox24->Location = System::Drawing::Point(18, 175);
			this->groupBox24->Name = L"groupBox24";
			this->groupBox24->Size = System::Drawing::Size(200, 127);
			this->groupBox24->TabIndex = 14;
			this->groupBox24->TabStop = false;
			this->groupBox24->Text = L"Parameter";
			// 
			// label59
			// 
			this->label59->AutoSize = true;
			this->label59->Location = System::Drawing::Point(10, 74);
			this->label59->Name = L"label59";
			this->label59->Size = System::Drawing::Size(65, 12);
			this->label59->TabIndex = 8;
			this->label59->Text = L"阴影参数3:";
			// 
			// shadowParameterZ_txt
			// 
			this->shadowParameterZ_txt->Location = System::Drawing::Point(112, 71);
			this->shadowParameterZ_txt->Name = L"shadowParameterZ_txt";
			this->shadowParameterZ_txt->Size = System::Drawing::Size(58, 21);
			this->shadowParameterZ_txt->TabIndex = 7;
			this->shadowParameterZ_txt->Text = L"0";
			// 
			// label60
			// 
			this->label60->AutoSize = true;
			this->label60->Location = System::Drawing::Point(10, 102);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(65, 12);
			this->label60->TabIndex = 6;
			this->label60->Text = L"阴影参数4:";
			// 
			// shadowParameterW_txt
			// 
			this->shadowParameterW_txt->Location = System::Drawing::Point(112, 99);
			this->shadowParameterW_txt->Name = L"shadowParameterW_txt";
			this->shadowParameterW_txt->Size = System::Drawing::Size(58, 21);
			this->shadowParameterW_txt->TabIndex = 5;
			this->shadowParameterW_txt->Text = L"0";
			// 
			// label61
			// 
			this->label61->AutoSize = true;
			this->label61->Location = System::Drawing::Point(10, 47);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(65, 12);
			this->label61->TabIndex = 4;
			this->label61->Text = L"阴影参数2:";
			// 
			// shadowParameterY_txt
			// 
			this->shadowParameterY_txt->Location = System::Drawing::Point(112, 44);
			this->shadowParameterY_txt->Name = L"shadowParameterY_txt";
			this->shadowParameterY_txt->Size = System::Drawing::Size(58, 21);
			this->shadowParameterY_txt->TabIndex = 3;
			this->shadowParameterY_txt->Text = L"0";
			// 
			// label62
			// 
			this->label62->AutoSize = true;
			this->label62->Location = System::Drawing::Point(10, 21);
			this->label62->Name = L"label62";
			this->label62->Size = System::Drawing::Size(89, 12);
			this->label62->TabIndex = 2;
			this->label62->Text = L"阴影基数(0-1):";
			// 
			// shadowParameterX_txt
			// 
			this->shadowParameterX_txt->Location = System::Drawing::Point(112, 18);
			this->shadowParameterX_txt->Name = L"shadowParameterX_txt";
			this->shadowParameterX_txt->Size = System::Drawing::Size(58, 21);
			this->shadowParameterX_txt->TabIndex = 1;
			this->shadowParameterX_txt->Text = L"0";
			// 
			// button14
			// 
			this->button14->Location = System::Drawing::Point(143, 613);
			this->button14->Name = L"button14";
			this->button14->Size = System::Drawing::Size(75, 23);
			this->button14->TabIndex = 12;
			this->button14->Text = L"响应";
			this->button14->UseVisualStyleBackColor = true;
			this->button14->Click += gcnew System::EventHandler(this, &MainForm::button14_Click);
			// 
			// groupBox20
			// 
			this->groupBox20->Controls->Add(this->terrain_dynamic_shadow_check);
			this->groupBox20->Controls->Add(this->terrain_shadow_check);
			this->groupBox20->Location = System::Drawing::Point(18, 19);
			this->groupBox20->Name = L"groupBox20";
			this->groupBox20->Size = System::Drawing::Size(200, 46);
			this->groupBox20->TabIndex = 11;
			this->groupBox20->TabStop = false;
			this->groupBox20->Text = L"地形";
			// 
			// terrain_dynamic_shadow_check
			// 
			this->terrain_dynamic_shadow_check->AutoSize = true;
			this->terrain_dynamic_shadow_check->Location = System::Drawing::Point(112, 15);
			this->terrain_dynamic_shadow_check->Name = L"terrain_dynamic_shadow_check";
			this->terrain_dynamic_shadow_check->Size = System::Drawing::Size(72, 16);
			this->terrain_dynamic_shadow_check->TabIndex = 7;
			this->terrain_dynamic_shadow_check->Text = L"动态阴影";
			this->terrain_dynamic_shadow_check->UseVisualStyleBackColor = true;
			// 
			// terrain_shadow_check
			// 
			this->terrain_shadow_check->AutoSize = true;
			this->terrain_shadow_check->Location = System::Drawing::Point(16, 15);
			this->terrain_shadow_check->Name = L"terrain_shadow_check";
			this->terrain_shadow_check->Size = System::Drawing::Size(72, 16);
			this->terrain_shadow_check->TabIndex = 6;
			this->terrain_shadow_check->Text = L"阴影贴图";
			this->terrain_shadow_check->UseVisualStyleBackColor = true;
			// 
			// groupBox12
			// 
			this->groupBox12->Controls->Add(this->rb_shadow_lispsm);
			this->groupBox12->Controls->Add(this->rb_shadow_plane);
			this->groupBox12->Controls->Add(this->rb_shadow_uniform);
			this->groupBox12->Controls->Add(this->rb_shadow_uniform_focused);
			this->groupBox12->Controls->Add(this->rb_shadow_pssm);
			this->groupBox12->Controls->Add(this->rb_shadow_none);
			this->groupBox12->Location = System::Drawing::Point(18, 78);
			this->groupBox12->Name = L"groupBox12";
			this->groupBox12->Size = System::Drawing::Size(200, 91);
			this->groupBox12->TabIndex = 10;
			this->groupBox12->TabStop = false;
			this->groupBox12->Text = L"阴影质量";
			// 
			// rb_shadow_lispsm
			// 
			this->rb_shadow_lispsm->AutoSize = true;
			this->rb_shadow_lispsm->Location = System::Drawing::Point(7, 65);
			this->rb_shadow_lispsm->Name = L"rb_shadow_lispsm";
			this->rb_shadow_lispsm->Size = System::Drawing::Size(59, 16);
			this->rb_shadow_lispsm->TabIndex = 6;
			this->rb_shadow_lispsm->Text = L"LISPSM";
			this->rb_shadow_lispsm->UseVisualStyleBackColor = true;
			// 
			// rb_shadow_plane
			// 
			this->rb_shadow_plane->AutoSize = true;
			this->rb_shadow_plane->Location = System::Drawing::Point(66, 65);
			this->rb_shadow_plane->Name = L"rb_shadow_plane";
			this->rb_shadow_plane->Size = System::Drawing::Size(131, 16);
			this->rb_shadow_plane->TabIndex = 5;
			this->rb_shadow_plane->Text = L"PLANE_OPTIMALDEPTH";
			this->rb_shadow_plane->UseVisualStyleBackColor = true;
			// 
			// rb_shadow_uniform
			// 
			this->rb_shadow_uniform->AutoSize = true;
			this->rb_shadow_uniform->Location = System::Drawing::Point(7, 43);
			this->rb_shadow_uniform->Name = L"rb_shadow_uniform";
			this->rb_shadow_uniform->Size = System::Drawing::Size(65, 16);
			this->rb_shadow_uniform->TabIndex = 4;
			this->rb_shadow_uniform->Text = L"UNIFORM";
			this->rb_shadow_uniform->UseVisualStyleBackColor = true;
			// 
			// rb_shadow_uniform_focused
			// 
			this->rb_shadow_uniform_focused->AutoSize = true;
			this->rb_shadow_uniform_focused->Location = System::Drawing::Point(75, 43);
			this->rb_shadow_uniform_focused->Name = L"rb_shadow_uniform_focused";
			this->rb_shadow_uniform_focused->Size = System::Drawing::Size(113, 16);
			this->rb_shadow_uniform_focused->TabIndex = 3;
			this->rb_shadow_uniform_focused->Text = L"UNIFORM_FOCUSED";
			this->rb_shadow_uniform_focused->UseVisualStyleBackColor = true;
			// 
			// rb_shadow_pssm
			// 
			this->rb_shadow_pssm->AutoSize = true;
			this->rb_shadow_pssm->Location = System::Drawing::Point(75, 20);
			this->rb_shadow_pssm->Name = L"rb_shadow_pssm";
			this->rb_shadow_pssm->Size = System::Drawing::Size(47, 16);
			this->rb_shadow_pssm->TabIndex = 1;
			this->rb_shadow_pssm->Text = L"PSSM";
			this->rb_shadow_pssm->UseVisualStyleBackColor = true;
			// 
			// rb_shadow_none
			// 
			this->rb_shadow_none->AutoSize = true;
			this->rb_shadow_none->Checked = true;
			this->rb_shadow_none->Location = System::Drawing::Point(7, 21);
			this->rb_shadow_none->Name = L"rb_shadow_none";
			this->rb_shadow_none->Size = System::Drawing::Size(59, 16);
			this->rb_shadow_none->TabIndex = 0;
			this->rb_shadow_none->TabStop = true;
			this->rb_shadow_none->Text = L"无阴影";
			this->rb_shadow_none->UseVisualStyleBackColor = true;
			// 
			// groupBox19
			// 
			this->groupBox19->Controls->Add(this->label52);
			this->groupBox19->Controls->Add(this->txt_terrainShadowOffset);
			this->groupBox19->Controls->Add(this->button11);
			this->groupBox19->Location = System::Drawing::Point(18, 308);
			this->groupBox19->Name = L"groupBox19";
			this->groupBox19->Size = System::Drawing::Size(200, 151);
			this->groupBox19->TabIndex = 6;
			this->groupBox19->TabStop = false;
			this->groupBox19->Text = L"生成全局光照贴图";
			// 
			// label52
			// 
			this->label52->AutoSize = true;
			this->label52->Location = System::Drawing::Point(14, 23);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(113, 12);
			this->label52->TabIndex = 4;
			this->label52->Text = L"地形阴影偏移(1-0):";
			// 
			// txt_terrainShadowOffset
			// 
			this->txt_terrainShadowOffset->Location = System::Drawing::Point(137, 20);
			this->txt_terrainShadowOffset->Name = L"txt_terrainShadowOffset";
			this->txt_terrainShadowOffset->Size = System::Drawing::Size(33, 21);
			this->txt_terrainShadowOffset->TabIndex = 3;
			this->txt_terrainShadowOffset->Text = L"1";
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(16, 113);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(177, 23);
			this->button11->TabIndex = 2;
			this->button11->Text = L"生成(需要等待一会)";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &MainForm::button11_Click_1);
			// 
			// tabPage11
			// 
			this->tabPage11->Controls->Add(this->button15);
			this->tabPage11->Controls->Add(this->groupBox28);
			this->tabPage11->Controls->Add(this->groupBox29);
			this->tabPage11->Controls->Add(this->groupBox30);
			this->tabPage11->Location = System::Drawing::Point(4, 24);
			this->tabPage11->Name = L"tabPage11";
			this->tabPage11->Padding = System::Windows::Forms::Padding(3);
			this->tabPage11->Size = System::Drawing::Size(236, 657);
			this->tabPage11->TabIndex = 5;
			this->tabPage11->Text = L"MiniMap";
			this->tabPage11->UseVisualStyleBackColor = true;
			// 
			// button15
			// 
			this->button15->Location = System::Drawing::Point(17, 245);
			this->button15->Name = L"button15";
			this->button15->Size = System::Drawing::Size(200, 23);
			this->button15->TabIndex = 7;
			this->button15->Text = L"生成MiniMap";
			this->button15->UseVisualStyleBackColor = true;
			this->button15->Click += gcnew System::EventHandler(this, &MainForm::button15_Click);
			// 
			// groupBox28
			// 
			this->groupBox28->Controls->Add(this->label68);
			this->groupBox28->Controls->Add(this->minimap_tex_size_h);
			this->groupBox28->Controls->Add(this->label69);
			this->groupBox28->Controls->Add(this->minimap_tex_size_w);
			this->groupBox28->Location = System::Drawing::Point(17, 177);
			this->groupBox28->Name = L"groupBox28";
			this->groupBox28->Size = System::Drawing::Size(200, 50);
			this->groupBox28->TabIndex = 6;
			this->groupBox28->TabStop = false;
			this->groupBox28->Text = L"保存贴图像素大小";
			// 
			// label68
			// 
			this->label68->AutoSize = true;
			this->label68->Location = System::Drawing::Point(72, 21);
			this->label68->Name = L"label68";
			this->label68->Size = System::Drawing::Size(17, 12);
			this->label68->TabIndex = 3;
			this->label68->Text = L"h:";
			// 
			// minimap_tex_size_h
			// 
			this->minimap_tex_size_h->Location = System::Drawing::Point(95, 18);
			this->minimap_tex_size_h->Name = L"minimap_tex_size_h";
			this->minimap_tex_size_h->Size = System::Drawing::Size(33, 21);
			this->minimap_tex_size_h->TabIndex = 2;
			this->minimap_tex_size_h->Text = L"1024";
			// 
			// label69
			// 
			this->label69->AutoSize = true;
			this->label69->Location = System::Drawing::Point(7, 21);
			this->label69->Name = L"label69";
			this->label69->Size = System::Drawing::Size(17, 12);
			this->label69->TabIndex = 1;
			this->label69->Text = L"w:";
			// 
			// minimap_tex_size_w
			// 
			this->minimap_tex_size_w->Location = System::Drawing::Point(30, 18);
			this->minimap_tex_size_w->Name = L"minimap_tex_size_w";
			this->minimap_tex_size_w->Size = System::Drawing::Size(33, 21);
			this->minimap_tex_size_w->TabIndex = 0;
			this->minimap_tex_size_w->Text = L"1024";
			// 
			// groupBox29
			// 
			this->groupBox29->Controls->Add(this->label71);
			this->groupBox29->Controls->Add(this->minimap_size_h);
			this->groupBox29->Controls->Add(this->label72);
			this->groupBox29->Controls->Add(this->minimap_size_w);
			this->groupBox29->Location = System::Drawing::Point(17, 98);
			this->groupBox29->Name = L"groupBox29";
			this->groupBox29->Size = System::Drawing::Size(200, 50);
			this->groupBox29->TabIndex = 5;
			this->groupBox29->TabStop = false;
			this->groupBox29->Text = L"世界大小";
			// 
			// label71
			// 
			this->label71->AutoSize = true;
			this->label71->Location = System::Drawing::Point(72, 21);
			this->label71->Name = L"label71";
			this->label71->Size = System::Drawing::Size(17, 12);
			this->label71->TabIndex = 3;
			this->label71->Text = L"h:";
			// 
			// minimap_size_h
			// 
			this->minimap_size_h->Location = System::Drawing::Point(95, 18);
			this->minimap_size_h->Name = L"minimap_size_h";
			this->minimap_size_h->Size = System::Drawing::Size(33, 21);
			this->minimap_size_h->TabIndex = 2;
			this->minimap_size_h->Text = L"1024";
			// 
			// label72
			// 
			this->label72->AutoSize = true;
			this->label72->Location = System::Drawing::Point(7, 21);
			this->label72->Name = L"label72";
			this->label72->Size = System::Drawing::Size(17, 12);
			this->label72->TabIndex = 1;
			this->label72->Text = L"w:";
			// 
			// minimap_size_w
			// 
			this->minimap_size_w->Location = System::Drawing::Point(30, 18);
			this->minimap_size_w->Name = L"minimap_size_w";
			this->minimap_size_w->Size = System::Drawing::Size(33, 21);
			this->minimap_size_w->TabIndex = 0;
			this->minimap_size_w->Text = L"1024";
			// 
			// groupBox30
			// 
			this->groupBox30->Controls->Add(this->label74);
			this->groupBox30->Controls->Add(this->minimap_center_z);
			this->groupBox30->Controls->Add(this->label75);
			this->groupBox30->Controls->Add(this->minimap_center_x);
			this->groupBox30->Location = System::Drawing::Point(17, 21);
			this->groupBox30->Name = L"groupBox30";
			this->groupBox30->Size = System::Drawing::Size(200, 50);
			this->groupBox30->TabIndex = 4;
			this->groupBox30->TabStop = false;
			this->groupBox30->Text = L"世界中心点";
			// 
			// label74
			// 
			this->label74->AutoSize = true;
			this->label74->Location = System::Drawing::Point(72, 21);
			this->label74->Name = L"label74";
			this->label74->Size = System::Drawing::Size(17, 12);
			this->label74->TabIndex = 3;
			this->label74->Text = L"z:";
			// 
			// minimap_center_z
			// 
			this->minimap_center_z->Location = System::Drawing::Point(95, 18);
			this->minimap_center_z->Name = L"minimap_center_z";
			this->minimap_center_z->Size = System::Drawing::Size(32, 21);
			this->minimap_center_z->TabIndex = 2;
			this->minimap_center_z->Text = L"-512";
			// 
			// label75
			// 
			this->label75->AutoSize = true;
			this->label75->Location = System::Drawing::Point(7, 21);
			this->label75->Name = L"label75";
			this->label75->Size = System::Drawing::Size(17, 12);
			this->label75->TabIndex = 1;
			this->label75->Text = L"x:";
			// 
			// minimap_center_x
			// 
			this->minimap_center_x->Location = System::Drawing::Point(30, 18);
			this->minimap_center_x->Name = L"minimap_center_x";
			this->minimap_center_x->Size = System::Drawing::Size(32, 21);
			this->minimap_center_x->TabIndex = 0;
			this->minimap_center_x->Text = L"512";
			// 
			// tabPage12
			// 
			this->tabPage12->Controls->Add(this->MotionBlur_ckb);
			this->tabPage12->Controls->Add(this->HDR_ckb);
			this->tabPage12->Controls->Add(this->FakeHDR_ckb);
			this->tabPage12->Controls->Add(this->button16);
			this->tabPage12->Controls->Add(this->Bloom_ckb);
			this->tabPage12->Location = System::Drawing::Point(4, 24);
			this->tabPage12->Name = L"tabPage12";
			this->tabPage12->Padding = System::Windows::Forms::Padding(3);
			this->tabPage12->Size = System::Drawing::Size(236, 657);
			this->tabPage12->TabIndex = 6;
			this->tabPage12->Text = L"合成器";
			this->tabPage12->UseVisualStyleBackColor = true;
			// 
			// MotionBlur_ckb
			// 
			this->MotionBlur_ckb->AutoSize = true;
			this->MotionBlur_ckb->Location = System::Drawing::Point(36, 127);
			this->MotionBlur_ckb->Name = L"MotionBlur_ckb";
			this->MotionBlur_ckb->Size = System::Drawing::Size(84, 16);
			this->MotionBlur_ckb->TabIndex = 11;
			this->MotionBlur_ckb->Text = L"MotionBlur";
			this->MotionBlur_ckb->UseVisualStyleBackColor = true;
			// 
			// HDR_ckb
			// 
			this->HDR_ckb->AutoSize = true;
			this->HDR_ckb->Location = System::Drawing::Point(36, 90);
			this->HDR_ckb->Name = L"HDR_ckb";
			this->HDR_ckb->Size = System::Drawing::Size(42, 16);
			this->HDR_ckb->TabIndex = 10;
			this->HDR_ckb->Text = L"HDR";
			this->HDR_ckb->UseVisualStyleBackColor = true;
			// 
			// FakeHDR_ckb
			// 
			this->FakeHDR_ckb->AutoSize = true;
			this->FakeHDR_ckb->Location = System::Drawing::Point(36, 55);
			this->FakeHDR_ckb->Name = L"FakeHDR_ckb";
			this->FakeHDR_ckb->Size = System::Drawing::Size(66, 16);
			this->FakeHDR_ckb->TabIndex = 9;
			this->FakeHDR_ckb->Text = L"FakeHDR";
			this->FakeHDR_ckb->UseVisualStyleBackColor = true;
			// 
			// button16
			// 
			this->button16->Location = System::Drawing::Point(25, 190);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(177, 23);
			this->button16->TabIndex = 8;
			this->button16->Text = L"启用";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &MainForm::button16_Click);
			// 
			// Bloom_ckb
			// 
			this->Bloom_ckb->AutoSize = true;
			this->Bloom_ckb->Location = System::Drawing::Point(36, 23);
			this->Bloom_ckb->Name = L"Bloom_ckb";
			this->Bloom_ckb->Size = System::Drawing::Size(54, 16);
			this->Bloom_ckb->TabIndex = 7;
			this->Bloom_ckb->Text = L"Bloom";
			this->Bloom_ckb->UseVisualStyleBackColor = true;
			// 
			// tabPage7
			// 
			this->tabPage7->BackColor = System::Drawing::Color::Transparent;
			this->tabPage7->Controls->Add(this->trackBar1);
			this->tabPage7->Controls->Add(this->trackBar2);
			this->tabPage7->ImageIndex = 7;
			this->tabPage7->Location = System::Drawing::Point(4, 40);
			this->tabPage7->Name = L"tabPage7";
			this->tabPage7->Padding = System::Windows::Forms::Padding(3);
			this->tabPage7->Size = System::Drawing::Size(218, 89);
			this->tabPage7->TabIndex = 0;
			this->tabPage7->ToolTipText = L"添加纹理";
			this->tabPage7->UseVisualStyleBackColor = true;
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(66, 40);
			this->trackBar1->Maximum = 20;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(149, 45);
			this->trackBar1->TabIndex = 6;
			this->trackBar1->Value = 5;
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(66, 3);
			this->trackBar2->Maximum = 20;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(150, 45);
			this->trackBar2->TabIndex = 5;
			this->trackBar2->Value = 5;
			// 
			// tabPage8
			// 
			this->tabPage8->BackColor = System::Drawing::Color::Transparent;
			this->tabPage8->ImageIndex = 9;
			this->tabPage8->Location = System::Drawing::Point(4, 40);
			this->tabPage8->Name = L"tabPage8";
			this->tabPage8->Padding = System::Windows::Forms::Padding(3);
			this->tabPage8->Size = System::Drawing::Size(218, 89);
			this->tabPage8->TabIndex = 1;
			this->tabPage8->ToolTipText = L"移除纹理";
			this->tabPage8->UseVisualStyleBackColor = true;
			// 
			// Menu_Setting_EnableClipScene
			// 
			this->Menu_Setting_EnableClipScene->Name = L"Menu_Setting_EnableClipScene";
			this->Menu_Setting_EnableClipScene->Size = System::Drawing::Size(152, 22);
			this->Menu_Setting_EnableClipScene->Text = L"启用裁剪地图";
			this->Menu_Setting_EnableClipScene->Click += gcnew System::EventHandler(this, &MainForm::Menu_Setting_EnableClipScene_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1192, 766);
			this->Controls->Add(this->base_panel);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SceneEditor";
			this->Move += gcnew System::EventHandler(this, &MainForm::MainForm_Move);
			this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->base_panel->ResumeLayout(false);
			this->scene_base_panel->ResumeLayout(false);
			this->panel8->ResumeLayout(false);
			this->panel8->PerformLayout();
			this->UtilType_Ctrl->ResumeLayout(false);
			this->Prop_Panel->ResumeLayout(false);
			this->prop_tab_ctrl->ResumeLayout(false);
			this->elemet_page->ResumeLayout(false);
			this->panel9->ResumeLayout(false);
			this->element_tab->ResumeLayout(false);
			this->createElment_page->ResumeLayout(false);
			this->SelectCreateElementTypeTab->ResumeLayout(false);
			this->create_static_page->ResumeLayout(false);
			this->panel11->ResumeLayout(false);
			this->panel14->ResumeLayout(false);
			this->panel14->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->num_create_batch))->EndInit();
			this->panel10->ResumeLayout(false);
			this->panel10->PerformLayout();
			this->create_tree_page->ResumeLayout(false);
			this->panel34->ResumeLayout(false);
			this->panel34->PerformLayout();
			this->panel28->ResumeLayout(false);
			this->create_effect_page->ResumeLayout(false);
			this->panel35->ResumeLayout(false);
			this->panel35->PerformLayout();
			this->panel36->ResumeLayout(false);
			this->panel36->PerformLayout();
			this->elemet_prop_page->ResumeLayout(false);
			this->panel13->ResumeLayout(false);
			this->elemet_list_page->ResumeLayout(false);
			this->panel15->ResumeLayout(false);
			this->panel16->ResumeLayout(false);
			this->panel16->PerformLayout();
			this->terrain_page->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->terrainTab->ResumeLayout(false);
			this->terrain_base_page->ResumeLayout(false);
			this->terrain_vertex_page->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->terrainHeightTab->ResumeLayout(false);
			this->terrain_height_level_page->ResumeLayout(false);
			this->terrain_height_level_page->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_height_level_range_tb))->EndInit();
			this->terrain_height_noise_page->ResumeLayout(false);
			this->terrain_height_noise_page->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_height_noise_range_tb))->EndInit();
			this->terrain_height_flat_page->ResumeLayout(false);
			this->terrain_height_flat_page->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_height_smooth_range_tb))->EndInit();
			this->terrain_texture_page->ResumeLayout(false);
			this->panel6->ResumeLayout(false);
			this->terrain_texture_pic_tab->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->terrainTextureTab->ResumeLayout(false);
			this->terrain_tex_add_page->ResumeLayout(false);
			this->terrain_tex_add_page->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_tex_add_tb))->EndInit();
			this->terrain_tex_remove_page->ResumeLayout(false);
			this->terrain_tex_remove_page->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_tex_remove_tb))->EndInit();
			this->terrain_tex_mop_page->ResumeLayout(false);
			this->terrain_tex_mop_page->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_tex_mop_tb))->EndInit();
			this->terrain_tex_blur_page->ResumeLayout(false);
			this->terrain_tex_blur_page->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_tex_blur_tb))->EndInit();
			this->terrain_plant_page->ResumeLayout(false);
			this->panel18->ResumeLayout(false);
			this->panel18->PerformLayout();
			this->plantTab->ResumeLayout(false);
			this->plant_tree_page->ResumeLayout(false);
			this->plant_grass_page->ResumeLayout(false);
			this->plant_create_page->ResumeLayout(false);
			this->panel17->ResumeLayout(false);
			this->panel24->ResumeLayout(false);
			this->plantBatchEntityTab->ResumeLayout(false);
			this->terrain_batch_add_page->ResumeLayout(false);
			this->terrain_batch_add_page->PerformLayout();
			this->groupBox37->ResumeLayout(false);
			this->groupBox37->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->plant_create_scale_offset_bar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->plant_create_clumping_bar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->plant_create_treeDis_bar))->EndInit();
			this->panel25->ResumeLayout(false);
			this->groupBox21->ResumeLayout(false);
			this->groupBox21->PerformLayout();
			this->terrain_water_page->ResumeLayout(false);
			this->panel23->ResumeLayout(false);
			this->waterTab->ResumeLayout(false);
			this->water_group_page->ResumeLayout(false);
			this->panel31->ResumeLayout(false);
			this->water_mat_tab->ResumeLayout(false);
			this->water_template_page->ResumeLayout(false);
			this->panel32->ResumeLayout(false);
			this->tabPage15->ResumeLayout(false);
			this->panel33->ResumeLayout(false);
			this->groupBox25->ResumeLayout(false);
			this->groupBox25->PerformLayout();
			this->groupBox26->ResumeLayout(false);
			this->groupBox26->PerformLayout();
			this->panel29->ResumeLayout(false);
			this->water_visible_page->ResumeLayout(false);
			this->panel26->ResumeLayout(false);
			this->water_visible_tab->ResumeLayout(false);
			this->water_height_page->ResumeLayout(false);
			this->panel27->ResumeLayout(false);
			this->water_height_tab->ResumeLayout(false);
			this->water_height_level_page->ResumeLayout(false);
			this->water_height_level_page->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->water_height_level_app))->EndInit();
			this->water_height_uniform_page->ResumeLayout(false);
			this->water_height_uniform_page->PerformLayout();
			this->water_height_flat_page->ResumeLayout(false);
			this->water_height_flat_page->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar5))->EndInit();
			this->panel30->ResumeLayout(false);
			this->panel30->PerformLayout();
			this->terrain_region_page->ResumeLayout(false);
			this->panel21->ResumeLayout(false);
			this->TerrainRegionTypeTab->ResumeLayout(false);
			this->TerrainRegionBlockPage->ResumeLayout(false);
			this->TerrainRegionSelfPage->ResumeLayout(false);
			this->panel22->ResumeLayout(false);
			this->panel22->PerformLayout();
			this->panel20->ResumeLayout(false);
			this->panel20->PerformLayout();
			this->panel19->ResumeLayout(false);
			this->terrainRegionOpTab->ResumeLayout(false);
			this->panel1->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->terrain_style_tab->ResumeLayout(false);
			this->terrain_style_gun_page->ResumeLayout(false);
			this->terrain_style_gun_page->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_stytle_gun_decay_tb))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->terrain_brush_shape_tab->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_brush_speed_tb))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->terrain_brush_size_tb))->EndInit();
			this->setting_page->ResumeLayout(false);
			this->panel7->ResumeLayout(false);
			this->ConfigTab->ResumeLayout(false);
			this->Config_env_light_page->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->groupBox36->ResumeLayout(false);
			this->groupBox36->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox27->ResumeLayout(false);
			this->groupBox27->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->config_video_page->ResumeLayout(false);
			this->groupBox39->ResumeLayout(false);
			this->groupBox39->PerformLayout();
			this->groupBox16->ResumeLayout(false);
			this->groupBox16->PerformLayout();
			this->groupBox15->ResumeLayout(false);
			this->groupBox15->PerformLayout();
			this->groupBox14->ResumeLayout(false);
			this->groupBox14->PerformLayout();
			this->groupBox11->ResumeLayout(false);
			this->groupBox11->PerformLayout();
			this->groupBox10->ResumeLayout(false);
			this->groupBox10->PerformLayout();
			this->groupBox9->ResumeLayout(false);
			this->groupBox9->PerformLayout();
			this->groupBox8->ResumeLayout(false);
			this->groupBox8->PerformLayout();
			this->config_plant_page->ResumeLayout(false);
			this->groupBox38->ResumeLayout(false);
			this->groupBox38->PerformLayout();
			this->groupBox33->ResumeLayout(false);
			this->groupBox33->PerformLayout();
			this->groupBox35->ResumeLayout(false);
			this->groupBox35->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TrackBarWindIntensity))->EndInit();
			this->groupBox34->ResumeLayout(false);
			this->groupBox34->PerformLayout();
			this->tabPage1->ResumeLayout(false);
			this->groupBox32->ResumeLayout(false);
			this->groupBox32->PerformLayout();
			this->groupBox31->ResumeLayout(false);
			this->groupBox31->PerformLayout();
			this->groupBox18->ResumeLayout(false);
			this->groupBox18->PerformLayout();
			this->groupBox17->ResumeLayout(false);
			this->groupBox17->PerformLayout();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			this->tabPage9->ResumeLayout(false);
			this->groupBox23->ResumeLayout(false);
			this->groupBox23->PerformLayout();
			this->groupBox22->ResumeLayout(false);
			this->groupBox22->PerformLayout();
			this->groupBox13->ResumeLayout(false);
			this->groupBox13->PerformLayout();
			this->tabPage10->ResumeLayout(false);
			this->groupBox24->ResumeLayout(false);
			this->groupBox24->PerformLayout();
			this->groupBox20->ResumeLayout(false);
			this->groupBox20->PerformLayout();
			this->groupBox12->ResumeLayout(false);
			this->groupBox12->PerformLayout();
			this->groupBox19->ResumeLayout(false);
			this->groupBox19->PerformLayout();
			this->tabPage11->ResumeLayout(false);
			this->groupBox28->ResumeLayout(false);
			this->groupBox28->PerformLayout();
			this->groupBox29->ResumeLayout(false);
			this->groupBox29->PerformLayout();
			this->groupBox30->ResumeLayout(false);
			this->groupBox30->PerformLayout();
			this->tabPage12->ResumeLayout(false);
			this->tabPage12->PerformLayout();
			this->tabPage7->ResumeLayout(false);
			this->tabPage7->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
    private: System::Void scene_panel_Move(System::Object^  sender, System::EventArgs^  e) {
                 this->setSceneFormLocation();
             }
    private: System::Void scene_panel_Resize(System::Object^  sender, System::EventArgs^  e) {
                 this->setSceneFormLocation();
            }
    private: System::Void MainForm_Move(System::Object^  sender, System::EventArgs^  e) {
                 this->setSceneFormLocation();
            }
    private: System::Void MainForm_Resize(System::Object^  sender, System::EventArgs^  e) {
                 this->setSceneFormLocation();
            }
    private: System::Void 加载ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->loadScene();
                 //mFormOpState = MOS_LOAD_SCENE;
             }
    private: System::Void 保存ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->saveScene();
             }
    private: System::Void 保存为ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->saveAsScene();
             }
    private: System::Void element_create_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                this->prepareCreateEntity();
                }
    private: System::Void 新建ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->openNewSceneEditor();
                 //this->createScene();
             }
    private: System::Void element_prop_grids_PropertyValueChanged(System::Object^  s, System::Windows::Forms::PropertyValueChangedEventArgs^  e) {
                this->applySceneElementPropsChange();
             }
    private: System::Void element_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                this->selectSceneEntityFromList();
             }
    private: System::Void UtilType_Ctrl_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->selectCtrlType();
             }
    private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->stickSelectElementToTerrain();
             }
    private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->prepareCreateEntity();
             }
    private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
                 
             }
    private: System::Void button4_Click_1(System::Object^  sender, System::EventArgs^  e) {
                 this->destroySceneEntityFromList();
             }
    private: System::Void 打开游戏地图编辑器ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->openGameDataEditor();
             }
    private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		     }
    private: System::Void element_create_npc_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                this->prepareCreateEntity();
		     }
    private: System::Void element_create_place_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                this->prepareCreateEntity();
		     }
	private: System::Void tree_create_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				this->prepareCreateTree();
			 }
	private: System::Void effect_create_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				this->prepareCreateEffect();
			 }
    private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
	
		     }
    private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {

		     }
    private: System::Void prop_tab_ctrl_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->switchGameEditorOp();
             }
    private: System::Void element_tab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->switchGameEditorOp();
             }
    private: System::Void SelectCreateElementTypeTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->switchGameEditorOp();
             }
    private: System::Void terrainTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->switchGameEditorOp();
             }
    private: System::Void terrainHeightTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->switchGameEditorOp();
             }
    private: System::Void terrainTextureTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->switchGameEditorOp();
             }
	private: System::Void plant_property_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 this->updateTerrainEditorParameter();
			 }
	private: System::Void terrain_foliage_noise_variable_valueChange(System::Object^  sender, System::EventArgs^  e) {
				 this->updateTerrainEditorParameter();
			 }
	private: System::Void terrain_foliage_noise_rate_valueChange(System::Object^  sender, System::EventArgs^  e) {
				 this->updateTerrainEditorParameter();
		     }
    private: System::Void terrain_brush_size_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->updateTerrainEditorParameter();   
             }
    private: System::Void terrain_brush_speed_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                this->updateTerrainEditorParameter();   
             }
    private: System::Void terrain_brush_shape_tab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->updateTerrainEditorParameter();   
             }
    private: System::Void terrain_style_tab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->updateTerrainEditorParameter();   
             }
    private: System::Void terrain_stytle_gun_decay_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->updateTerrainEditorParameter();   
             }
    private: System::Void terrain_height_noise_range_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->updateTerrainEditorParameter();   
             }
    private: System::Void terrain_height_level_range_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->updateTerrainEditorParameter();   
             }
    private: System::Void terrain_height_down_range_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->updateTerrainEditorParameter();   
             }
    private: System::Void trackBar4_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->updateTerrainEditorParameter();   
             }
    private: System::Void terrain_tex_add_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->updateTerrainEditorParameter();   
             }
    private: System::Void terrain_tex_remove_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->updateTerrainEditorParameter();   
             }
    private: System::Void terrain_tex_mop_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->updateTerrainEditorParameter();   
             }
    private: System::Void terrain_tex_blur_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 this->updateTerrainEditorParameter();   
			 }
	private: System::Void terrain_texture_pic_tab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 this->updateTerrainEditorParameter();   
			 }
	private: System::Void plant_create_align_checkbox_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->updateTerrainEditorParameter();
			 }
	private: System::Void TextBox_Plant_MinScale_Validated(System::Object^  sender, System::EventArgs^  e) {
				 this->updateTerrainEditorParameter();
			 }
	private: System::Void TextBox_Plant_MaxScale_Validated(System::Object^  sender, System::EventArgs^  e) {
				 this->updateTerrainEditorParameter();
			 }
	private: System::Void plant_create_ditribute_colum_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->updateTerrainEditorParameter();
			 }
	private: System::Void plant_create_ditribute_circle_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->updateTerrainEditorParameter();
			 }
	private: System::Void TrackBarWindIntensity_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				 this->updateSceneEditorParameter();
			 }
    private: System::Void scene_panel_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
             }
    private: System::Void scene_panel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
             }
    private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
                this->loadSceneEntityList();
				this->loadSceneEffectList();
             }
    private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->configSceneEnvironmentLight();
             }
    private: System::Void button8_Click_1(System::Object^  sender, System::EventArgs^  e) {
                 this->configSceneLightDirection();
             }
    private: System::Void button9_Click_1(System::Object^  sender, System::EventArgs^  e) {
                 this->configSceneGameConfig();
             }
    private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->applyGameSetting();
             }
    private: System::Void ToolStripMenuItem_SceneEditorMode_Click(System::Object^  sender, System::EventArgs^  e) {
                 ToolStripMenuItem_SceneEditorMode->Checked = !ToolStripMenuItem_SceneEditorMode->Checked;
                 this->applyBaseSceneSetting();
             }
    private: System::Void terrainBatchEntityTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->switchGameEditorOp();
             }
    private: System::Void terrain_block_visible_ckb_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->refreshRegionVisible();
             }
    private: System::Void terrainBlockTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->switchGameEditorOp();
             }
    private: System::Void btn_show_block_refresh_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->showBlockRegion();
             }
    private: System::Void TerrainRegionSelfList_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                this->showCustomRegion();
             }
    private: System::Void TerrainAddRegionSelfBtn_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->addCustomRegion();
             }
    private: System::Void terrain_region_visible_ckb_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->refreshRegionVisible();
             }
    private: System::Void 打开地形贴图编辑器ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->openTerrainTextureEditor();
             }
	private: System::Void 打开水效果编辑器ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->openWaterEffectEditor();
			 }
    private: System::Void waterTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->switchGameEditorOp();
             }
    private: System::Void water_visible_tab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->switchGameEditorOp();
             }
    private: System::Void water_height_tab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                 this->switchGameEditorOp();
             }
    private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->addWaterGroup();
             }
    private: System::Void water_group_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                 this->selectWaterGroup();
             }
    private: System::Void water_group_apply_btn_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->applyWaterGroup();
             }
	private: System::Void plantBatchEntityTab_SelectIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 this->switchGameEditorOp();
			}
	private: System::Void plant_batch_define_button_MouseClick(System::Object^  sender, System::EventArgs^  e) {
				 this->onEventPressDefineBatchButton();
			}
	private: System::Void batch_type_radioIndexChange(System::Object^  sender, System::EventArgs^  e) {
				 this->updateTerrainEditorParameter();
			}
    private: System::Void water_mat_template_list_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
				     this->selectWaterTemplate();
			    }
    private: System::Void water_height_level_range_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
				     this->updateTerrainEditorParameter();
			    }
    private: System::Void water_height_confirm_Click(System::Object^  sender, System::EventArgs^  e) {
				     this->onEventPressDefineWaterHeightButton();
			    }
    private: System::Void button11_Click(System::Object^  sender, System::EventArgs^  e) {
                    this->genarateLightingMap();
             }
    private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
                    this->applyFogSetting();
             }
    private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) {
                    this->applyShadowSetting();
             }
	private: System::Void button11_Click_1(System::Object^  sender, System::EventArgs^  e) {
					this->genarateLightingMap();
			 }
    private: System::Void button15_Click(System::Object^  sender, System::EventArgs^  e) {
                    this->genarateMiniMap();
             }
    private: System::Void button16_Click(System::Object^  sender, System::EventArgs^  e) {
                    this->applyCompositorSetting();
             }
	private: System::Void button20_Click(System::Object^  sender, System::EventArgs^  e) {
					this->applyPlantSetting();
					
			 }
private: System::Void wind_check_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Menu_Edit_Undo_Click(System::Object^  sender, System::EventArgs^  e) {
			 undo();
		 }
private: System::Void Menu_Edit_Redo_Click(System::Object^  sender, System::EventArgs^  e) {
			 redo();
		 }
private: System::Void Menu_Setting_ShowSubScene_Click(System::Object^  sender, System::EventArgs^  e) {
			 Menu_Setting_ShowSubScene->Checked = !Menu_Setting_ShowSubScene->Checked;
			 showSubScene(Menu_Setting_ShowSubScene->Checked);
		 }
private: System::Void Menu_Setting_SelectSubscene_Click(System::Object^  sender, System::EventArgs^  e) {
			 loadSubScene();
		 }
private: System::Void 地图信息ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 showSceneInfo();
		 }
private: System::Void listView_terrain_batch_tree_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->selectBatchTreeFromList();
		 }
private: System::Void listView_terrain_batch_grass_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->selectBatchGrassFromList();
		 }
private: System::Void button_ClipMap_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->clipScene();
		 }
private: System::Void button21_Click(System::Object^  sender, System::EventArgs^  e) {
			 reorderTerrainTextureLayer();
		 }
private: System::Void Menu_Setting_EnableClipScene_Click(System::Object^  sender, System::EventArgs^  e) {
			 button21->Enabled = !button21->Enabled;
			 button_ClipMap->Enabled = !button_ClipMap->Enabled;
			 Menu_Setting_EnableClipScene->Checked = button_ClipMap->Enabled;
		 }
};
}
