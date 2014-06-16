#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "XmlPropertySet.h"

namespace GameMapEditor {

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

		// 同步ShortCut事件， Tab切换
		void	onEventSelectTab(Int index);
		// 同步ShortCut事件， camera速度切换
		void	onEventCamspeedChanged(UInt level);
		// 打开map加载
		void	onEventOpenLoadMapForm();

        //######################################################################################################
        // 工具栏
        //######################################################################################################

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

		///通过artMapRes.csv打开场景
		void	loadScene(I32 mapID);

        /*@
            【界面下方工具栏】 
        @*/

        ///选择控制方式
        void    selectCtrlType();
        ///更新摄象机提示
        void    updateCameraHint();

		Bool    isEditorMode();

        /*@
            【界面右方编辑栏】
        @*/

        //切换游戏编辑操作，当界面Tab发生变化时
        void    switchGameEditorOp();


        //######################################################################################################
        // 实体元素操作
        //######################################################################################################

        /*@
            【实体模型定义列表】 
        @*/

        ///加载模型定义列表
        void    loadAllObjectList();

        ///准备创建交互物件
        void    prepareCreateObjectEntity();
		///准备创建NPC实体
		void    prepareCreateNpcEntity();
		///准备创建据点实体
		void    prepareCreatePlaceEntity();
		///准备创建点实体
		void    prepareCreatePointEntity();
		///准备创建战斗单位实体
		void    prepareCreateMonsterEntity();
		///准备创建军队实体
		void    prepareCreateTroopEntity();
		///准备创建军队大本营
		void    prepareCreateRegionEntity();
		///准备创建景观
		void    prepareCreateStaticObjectEntity();
		///准备创建建筑
		void    prepareCreateBuildingEntity();
		///显示cursor对象
		void    showCursorElement();
		///隐藏cursor对象
		void    hideCursorElement();
		
        /*@
          【场景选中实体元素操作】 
        @*/

        ///选中元素位置贴地
        void    stickSelectElementToTerrain();

        /*@
            【场景实体元素属性列表】 
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

		// 【场景元素列表】 
		///加载场景元素列表
		void    loadSceneElementList();
		///清空场景元素列表
		void    clearSceneElementList();
		///选择场景元素列表
		void    selectSceneElementFromList();
		///删除场景元素列表
		void    destroySceneElementFromList();

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

        /*@
            【摄像机配置】
        @*/

        ///加载游戏基础参数
        void    loadSceneGameConfig();
        void    configSceneGameConfig();
		void	restoreMapInstanceConfig(I32 nMapID);


		//######################################################################################################
		// 效果操作
		//######################################################################################################

		/*@
		【灯光配置】
		@*/

		///加载场景环境灯光
		void    loadSceneEnvironmentLight();
		///培植场景环境灯光
		void    configSceneEnvironmentLight();
		///培植场景灯光方向
		void    configSceneLightDirection();

        //######################################################################################################
        // 逻辑元素操作
        //######################################################################################################

		///切换内景地图和外景地图的逻辑面板
		void	resetObjectTabList(I32 mapType);

		/*@
			Object
		@*/
		//TODO:
		void	loadObjectList();
		void    clearObjectList();
		void    selectObjectFromList();
		void    saveObjectUpdate();

        /*@
            NPC
        @*/
          //TODO:
		void    loadNpcList();
		void    clearNpcList();
		void    selectNpcFromList();
		void    saveNpcUpdate();

		/*@
			Monster
		@*/
		//TODO:
		void    loadMonsterList();
		void    clearMonsterList();
		void    selectMonsterFromList();
		void    saveMonsterUpdate();

        /*@
			Place
        @*/
        //TODO:
        void    loadPlaceList();
        void    clearPlaceList();
        void    selectPlaceFromList();
        void    savePlaceUpdate();

		/*@
			Point
		@*/
		//TODO:
		void    loadPointList();
		void    clearPointList();
		void    selectPointFromList();
		void    savePointUpdate();

		/*@
			Troop
		@*/
		//TODO:
		void    loadTroopList();
		void    clearTroopList();
		void    selectTroopFromList();
		void    saveTroopUpdate();

		/*@
			Regions
		@*/
		//TODO:
		void    loadRegionList();
		void    clearRegionList();
		void    selectRegionFromList();
		void    saveRegionUpdate();

		/*@
			General
		@*/
		//TODO:
		void    clearGeneralList();
		void    selectGeneralFromList();
		void    saveGeneralUpdate();

		/*@
			Building
		@*/
		//TODO:
		void    loadBuildingList();
		void    clearBuildingList();
		void    selectBuildingFromList();
		void    saveBuildingUpdate();

		/*@
			StaticObject
		@*/
		//TODO:
		void    loadStaticObjectList();
		void    clearStaticObjectList();
		void    selectStaticObjectFromList();
		void    saveStaticObjectUpdate();

		/*@
		【特效定义列表】 
		@*/
		///加载Effect定义列表
		void	loadEffectDeclarationList();

		///准备创建Effect
		void	prepareCreateEffect();
		
        /////////////////////////////////////////////////////////////////////////////////

	public: 

		/// Xml属性集
        XmlPropertySet^         mXmlPropSet;
        ///上次关注的场景文件目录
        String^                 mLastFocusDir;
        /// 现在的场景对象XmlFormat对象
        ISceneObjectXmlFormat*  mCurrSceneObjectXmlFormat;
private: System::Windows::Forms::TabControl^  prop_tab_ctrl;
public: 
	/// 现在选择的创建角色节点
		TreeNode ^              mCurrSelectCreateModelTreeNode;
		/// 现在选择的Effect节点
		TreeNode ^ mCurrSelectCreateEffectTreeNode;

private: System::Windows::Forms::TabPage^  elemet_page;
private: System::Windows::Forms::Panel^  panel9;







































private: System::Windows::Forms::TabPage^  setting_page;
private: System::Windows::Forms::Panel^  panel7;
private: System::Windows::Forms::TabControl^  ConfigTab;
private: System::Windows::Forms::TabPage^  Config_env_light_page;
private: System::Windows::Forms::GroupBox^  groupBox6;
private: System::Windows::Forms::Button^  button8;
private: System::Windows::Forms::GroupBox^  groupBox5;
private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::TextBox^  light_spec_b_edit;
private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::TextBox^  light_spec_g_edit;
private: System::Windows::Forms::Label^  label30;
private: System::Windows::Forms::TextBox^  light_spec_r_edit;
private: System::Windows::Forms::GroupBox^  groupBox4;
private: System::Windows::Forms::Label^  label25;
private: System::Windows::Forms::TextBox^  light_diffuse_b_edit;
private: System::Windows::Forms::Label^  label26;
private: System::Windows::Forms::TextBox^  light_diffuse_g_edit;
private: System::Windows::Forms::Label^  label27;
private: System::Windows::Forms::TextBox^  light_diffuse_r_edit;
private: System::Windows::Forms::Button^  button7;
private: System::Windows::Forms::GroupBox^  环境光;
private: System::Windows::Forms::Label^  label24;
private: System::Windows::Forms::TextBox^  light_ambient_b_edit;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::TextBox^  light_ambient_g_edit;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::TextBox^  light_ambient_r_edit;
private: System::Windows::Forms::TabPage^  config_video_page;
private: System::Windows::Forms::GroupBox^  groupBox16;
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
private: System::Windows::Forms::GroupBox^  groupBox13;
private: System::Windows::Forms::RadioButton^  rb_fog_exp;
private: System::Windows::Forms::RadioButton^  rb_fog_line;
private: System::Windows::Forms::RadioButton^  rb_fog_none;
private: System::Windows::Forms::GroupBox^  groupBox12;
private: System::Windows::Forms::RadioButton^  rb_shadow_high;
private: System::Windows::Forms::RadioButton^  rb_shadow_medium;
private: System::Windows::Forms::RadioButton^  rb_shadow_low;
private: System::Windows::Forms::RadioButton^  rb_shadow_none;
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
private: System::Windows::Forms::CheckBox^  model_renderhigh_check;
private: System::Windows::Forms::GroupBox^  groupBox8;
private: System::Windows::Forms::CheckBox^  terrain_color_check;
private: System::Windows::Forms::CheckBox^  terrain_shadow_check;
private: System::Windows::Forms::CheckBox^  terrain_offset_check;
private: System::Windows::Forms::CheckBox^  terrain_spec_check;
private: System::Windows::Forms::CheckBox^  terrain_normal_check;
private: System::Windows::Forms::TabPage^  tabPage1;
private: System::Windows::Forms::GroupBox^  groupBox18;
private: System::Windows::Forms::CheckBox^  ckb_terrain_grids_visible;
private: System::Windows::Forms::GroupBox^  groupBox17;
private: System::Windows::Forms::CheckBox^  ckb_wireframe;
private: System::Windows::Forms::Button^  button9;
private: System::Windows::Forms::GroupBox^  groupBox7;
private: System::Windows::Forms::Label^  label21;
private: System::Windows::Forms::TextBox^  fov_edit;

























private: System::Windows::Forms::Panel^  panel1;
private: System::Windows::Forms::TreeView^  treeView1;
private: System::Windows::Forms::Panel^  panel2;
private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
private: System::Windows::Forms::CheckBox^  checkBox1;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Button^  button11;
private: System::Windows::Forms::Panel^  panel3;
private: System::Windows::Forms::Button^  button12;
private: System::Windows::Forms::TextBox^  textBox2;
































































































private: System::Windows::Forms::Panel^  panel24;
private: System::Windows::Forms::NumericUpDown^  numericUpDown7;
private: System::Windows::Forms::CheckBox^  checkBox7;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Button^  button23;
private: System::Windows::Forms::TreeView^  treeView2;
private: System::Windows::Forms::Panel^  panel25;
private: System::Windows::Forms::Button^  button24;
private: System::Windows::Forms::TextBox^  textBox9;






































private: System::Windows::Forms::Panel^  panel28;
private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::Label^  label32;
private: System::Windows::Forms::Button^  button27;
private: System::Windows::Forms::TreeView^  treeView3;
private: System::Windows::Forms::Panel^  panel29;
private: System::Windows::Forms::Button^  button28;
private: System::Windows::Forms::TextBox^  textBox11;
private: System::Windows::Forms::Panel^  panel34;
private: System::Windows::Forms::Label^  label37;
private: System::Windows::Forms::Label^  label39;
private: System::Windows::Forms::Button^  button33;
private: System::Windows::Forms::TreeView^  treeView4;
private: System::Windows::Forms::Panel^  panel35;
private: System::Windows::Forms::Button^  button34;
private: System::Windows::Forms::TabControl^  element_tab;
private: System::Windows::Forms::TabPage^  element_create_page;
private: System::Windows::Forms::TabControl^  SelectCreateElementTypeTab;
private: System::Windows::Forms::TabPage^  create_static_page;
private: System::Windows::Forms::Panel^  panel26;
private: System::Windows::Forms::Label^  prepare_static_model_text;
private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Button^  button25;
private: System::Windows::Forms::TreeView^  static_object_model_create_tree;
private: System::Windows::Forms::Panel^  panel27;
private: System::Windows::Forms::Button^  button26;
private: System::Windows::Forms::TextBox^  textBox10;









private: System::Windows::Forms::TabPage^  create_troop_page;
private: System::Windows::Forms::Panel^  panel23;
private: System::Windows::Forms::Label^  prepare_troop_model_text;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Button^  button22;
private: System::Windows::Forms::TreeView^  troop_model_create_tree;
private: System::Windows::Forms::Panel^  panel22;
private: System::Windows::Forms::Button^  button21;
private: System::Windows::Forms::TextBox^  textBox8;
private: System::Windows::Forms::TabPage^  create_building_page;
private: System::Windows::Forms::Panel^  panel30;
private: System::Windows::Forms::Label^  prepare_building_model_text;
private: System::Windows::Forms::Label^  label33;
private: System::Windows::Forms::Button^  button29;
private: System::Windows::Forms::TreeView^  building_model_create_tree;
private: System::Windows::Forms::Panel^  panel31;
private: System::Windows::Forms::Button^  button30;
private: System::Windows::Forms::TextBox^  textBox12;
private: System::Windows::Forms::TabPage^  create_monster_page;
private: System::Windows::Forms::Panel^  panel21;
private: System::Windows::Forms::Label^  prepare_monster_model_text;
private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::Button^  button20;
private: System::Windows::Forms::TreeView^  monster_model_create_tree;
private: System::Windows::Forms::Panel^  panel6;
private: System::Windows::Forms::Button^  button15;
private: System::Windows::Forms::TextBox^  textBox6;
private: System::Windows::Forms::TabPage^  create_npc_page;
private: System::Windows::Forms::Panel^  panel20;
private: System::Windows::Forms::Label^  prepare_npc_model_text;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::Button^  button19;
private: System::Windows::Forms::TreeView^  NPC_model_create_tree;
private: System::Windows::Forms::Panel^  panel5;
private: System::Windows::Forms::Button^  button14;
private: System::Windows::Forms::TextBox^  textBox5;
private: System::Windows::Forms::TabPage^  create_object_page;
private: System::Windows::Forms::Panel^  panel11;
private: System::Windows::Forms::TreeView^  object_model_create_tree;
private: System::Windows::Forms::Panel^  panel14;
private: System::Windows::Forms::Label^  prepare_object_model_text;
private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::Button^  button5;
private: System::Windows::Forms::Panel^  panel10;
private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::TextBox^  textBox1;
private: System::Windows::Forms::TabPage^  create_place_page;
private: System::Windows::Forms::Panel^  panel18;
private: System::Windows::Forms::Label^  prepare_place_model_text;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Button^  button17;
private: System::Windows::Forms::TreeView^  place_model_create_tree;
private: System::Windows::Forms::Panel^  panel4;
private: System::Windows::Forms::Button^  button13;
private: System::Windows::Forms::TextBox^  textBox4;
private: System::Windows::Forms::TabPage^  create_point_page;
private: System::Windows::Forms::Panel^  panel19;
private: System::Windows::Forms::Label^  prepare_point_model_text;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::Button^  button18;
private: System::Windows::Forms::TreeView^  point_model_create_tree;
private: System::Windows::Forms::Panel^  panel17;
private: System::Windows::Forms::Button^  button16;
private: System::Windows::Forms::TextBox^  textBox7;
private: System::Windows::Forms::TabPage^  element_prop_page;
private: System::Windows::Forms::Panel^  panel13;
private: System::Windows::Forms::PropertyGrid^  element_prop_grids;
private: System::Windows::Forms::Panel^  panel12;
private: System::Windows::Forms::TabPage^  element_statistics_page;
private: System::Windows::Forms::TreeView^  element_list;
private: System::Windows::Forms::Panel^  panel15;
private: System::Windows::Forms::Button^  button4;
private: System::Windows::Forms::Button^  button6;
private: System::Windows::Forms::Panel^  panel16;
private: System::Windows::Forms::Button^  button3;
private: System::Windows::Forms::TextBox^  textBox3;
private: System::Windows::Forms::TabPage^  create_effect_page;

private: System::Windows::Forms::Panel^  panel36;
private: System::Windows::Forms::Label^  prepare_effect_text;

private: System::Windows::Forms::Label^  label42;
private: System::Windows::Forms::Button^  button35;
private: System::Windows::Forms::TreeView^  effect_create_tree;



private: System::Windows::Forms::Panel^  panel37;
private: System::Windows::Forms::Button^  button36;
private: System::Windows::Forms::TextBox^  textBox15;
private: System::Windows::Forms::Panel^  panel32;
private: System::Windows::Forms::Label^  label38;
private: System::Windows::Forms::Label^  label40;
private: System::Windows::Forms::Button^  button31;
private: System::Windows::Forms::TreeView^  treeView5;
private: System::Windows::Forms::Panel^  panel33;
private: System::Windows::Forms::Button^  button32;
private: System::Windows::Forms::TextBox^  textBox13;














private: System::Windows::Forms::TextBox^  textBox14;





































        /////////////////////////////////////////////////////////////////////////////////

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private: System::Windows::Forms::TabPage^  tabPage7;
		private: System::Windows::Forms::TrackBar^  trackBar1;
		private: System::Windows::Forms::TrackBar^  trackBar2;
		private: System::Windows::Forms::TabPage^  tabPage8;
		private: System::Windows::Forms::ToolStripStatusLabel^  lable_status_batch;
		private: System::Windows::Forms::ToolStripStatusLabel^  lable_status_LastFPS;
		private: System::Windows::Forms::ToolStripStatusLabel^  lable_status_aveFPS;
		private: System::Windows::Forms::ToolStripStatusLabel^  lable_status_triCount;
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
		private: System::Windows::Forms::ImageList^  imageList1;
		private: System::Windows::Forms::ImageList^  imageList2;
		private: System::Windows::Forms::ImageList^  terrain_texture_pic_list;
		private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
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
		private: System::Windows::Forms::Label^  CamSpeed;
		private: System::Windows::Forms::Label^  label8;
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
					 this->设置ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
					 this->ToolStripMenuItem_SceneEditorMode = (gcnew System::Windows::Forms::ToolStripMenuItem());
					 this->帮助ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
					 this->关于ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
					 this->主题ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
					 this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
					 this->lable_status_batch = (gcnew System::Windows::Forms::ToolStripStatusLabel());
					 this->lable_status_LastFPS = (gcnew System::Windows::Forms::ToolStripStatusLabel());
					 this->lable_status_aveFPS = (gcnew System::Windows::Forms::ToolStripStatusLabel());
					 this->lable_status_triCount = (gcnew System::Windows::Forms::ToolStripStatusLabel());
					 this->base_panel = (gcnew System::Windows::Forms::Panel());
					 this->splitter1 = (gcnew System::Windows::Forms::Splitter());
					 this->scene_base_panel = (gcnew System::Windows::Forms::Panel());
					 this->scene_panel = (gcnew System::Windows::Forms::Panel());
					 this->panel8 = (gcnew System::Windows::Forms::Panel());
					 this->CamSpeed = (gcnew System::Windows::Forms::Label());
					 this->label8 = (gcnew System::Windows::Forms::Label());
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
					 this->element_create_page = (gcnew System::Windows::Forms::TabPage());
					 this->SelectCreateElementTypeTab = (gcnew System::Windows::Forms::TabControl());
					 this->create_static_page = (gcnew System::Windows::Forms::TabPage());
					 this->panel26 = (gcnew System::Windows::Forms::Panel());
					 this->prepare_static_model_text = (gcnew System::Windows::Forms::Label());
					 this->label19 = (gcnew System::Windows::Forms::Label());
					 this->button25 = (gcnew System::Windows::Forms::Button());
					 this->static_object_model_create_tree = (gcnew System::Windows::Forms::TreeView());
					 this->panel27 = (gcnew System::Windows::Forms::Panel());
					 this->button26 = (gcnew System::Windows::Forms::Button());
					 this->textBox10 = (gcnew System::Windows::Forms::TextBox());
					 this->create_troop_page = (gcnew System::Windows::Forms::TabPage());
					 this->panel23 = (gcnew System::Windows::Forms::Panel());
					 this->prepare_troop_model_text = (gcnew System::Windows::Forms::Label());
					 this->label7 = (gcnew System::Windows::Forms::Label());
					 this->button22 = (gcnew System::Windows::Forms::Button());
					 this->troop_model_create_tree = (gcnew System::Windows::Forms::TreeView());
					 this->panel22 = (gcnew System::Windows::Forms::Panel());
					 this->button21 = (gcnew System::Windows::Forms::Button());
					 this->textBox8 = (gcnew System::Windows::Forms::TextBox());
					 this->create_building_page = (gcnew System::Windows::Forms::TabPage());
					 this->panel30 = (gcnew System::Windows::Forms::Panel());
					 this->prepare_building_model_text = (gcnew System::Windows::Forms::Label());
					 this->label33 = (gcnew System::Windows::Forms::Label());
					 this->button29 = (gcnew System::Windows::Forms::Button());
					 this->building_model_create_tree = (gcnew System::Windows::Forms::TreeView());
					 this->panel31 = (gcnew System::Windows::Forms::Panel());
					 this->button30 = (gcnew System::Windows::Forms::Button());
					 this->textBox12 = (gcnew System::Windows::Forms::TextBox());
					 this->create_monster_page = (gcnew System::Windows::Forms::TabPage());
					 this->panel21 = (gcnew System::Windows::Forms::Panel());
					 this->prepare_monster_model_text = (gcnew System::Windows::Forms::Label());
					 this->label17 = (gcnew System::Windows::Forms::Label());
					 this->button20 = (gcnew System::Windows::Forms::Button());
					 this->monster_model_create_tree = (gcnew System::Windows::Forms::TreeView());
					 this->panel6 = (gcnew System::Windows::Forms::Panel());
					 this->button15 = (gcnew System::Windows::Forms::Button());
					 this->textBox6 = (gcnew System::Windows::Forms::TextBox());
					 this->create_npc_page = (gcnew System::Windows::Forms::TabPage());
					 this->panel20 = (gcnew System::Windows::Forms::Panel());
					 this->prepare_npc_model_text = (gcnew System::Windows::Forms::Label());
					 this->label13 = (gcnew System::Windows::Forms::Label());
					 this->button19 = (gcnew System::Windows::Forms::Button());
					 this->NPC_model_create_tree = (gcnew System::Windows::Forms::TreeView());
					 this->panel5 = (gcnew System::Windows::Forms::Panel());
					 this->button14 = (gcnew System::Windows::Forms::Button());
					 this->textBox5 = (gcnew System::Windows::Forms::TextBox());
					 this->create_object_page = (gcnew System::Windows::Forms::TabPage());
					 this->panel11 = (gcnew System::Windows::Forms::Panel());
					 this->object_model_create_tree = (gcnew System::Windows::Forms::TreeView());
					 this->panel14 = (gcnew System::Windows::Forms::Panel());
					 this->prepare_object_model_text = (gcnew System::Windows::Forms::Label());
					 this->label23 = (gcnew System::Windows::Forms::Label());
					 this->button5 = (gcnew System::Windows::Forms::Button());
					 this->panel10 = (gcnew System::Windows::Forms::Panel());
					 this->button1 = (gcnew System::Windows::Forms::Button());
					 this->textBox1 = (gcnew System::Windows::Forms::TextBox());
					 this->create_place_page = (gcnew System::Windows::Forms::TabPage());
					 this->panel18 = (gcnew System::Windows::Forms::Panel());
					 this->prepare_place_model_text = (gcnew System::Windows::Forms::Label());
					 this->label6 = (gcnew System::Windows::Forms::Label());
					 this->button17 = (gcnew System::Windows::Forms::Button());
					 this->place_model_create_tree = (gcnew System::Windows::Forms::TreeView());
					 this->panel4 = (gcnew System::Windows::Forms::Panel());
					 this->button13 = (gcnew System::Windows::Forms::Button());
					 this->textBox4 = (gcnew System::Windows::Forms::TextBox());
					 this->create_point_page = (gcnew System::Windows::Forms::TabPage());
					 this->panel19 = (gcnew System::Windows::Forms::Panel());
					 this->prepare_point_model_text = (gcnew System::Windows::Forms::Label());
					 this->label10 = (gcnew System::Windows::Forms::Label());
					 this->button18 = (gcnew System::Windows::Forms::Button());
					 this->point_model_create_tree = (gcnew System::Windows::Forms::TreeView());
					 this->panel17 = (gcnew System::Windows::Forms::Panel());
					 this->button16 = (gcnew System::Windows::Forms::Button());
					 this->textBox7 = (gcnew System::Windows::Forms::TextBox());
					 this->create_effect_page = (gcnew System::Windows::Forms::TabPage());
					 this->panel36 = (gcnew System::Windows::Forms::Panel());
					 this->prepare_effect_text = (gcnew System::Windows::Forms::Label());
					 this->label42 = (gcnew System::Windows::Forms::Label());
					 this->button35 = (gcnew System::Windows::Forms::Button());
					 this->effect_create_tree = (gcnew System::Windows::Forms::TreeView());
					 this->panel37 = (gcnew System::Windows::Forms::Panel());
					 this->button36 = (gcnew System::Windows::Forms::Button());
					 this->textBox15 = (gcnew System::Windows::Forms::TextBox());
					 this->element_prop_page = (gcnew System::Windows::Forms::TabPage());
					 this->panel13 = (gcnew System::Windows::Forms::Panel());
					 this->element_prop_grids = (gcnew System::Windows::Forms::PropertyGrid());
					 this->panel12 = (gcnew System::Windows::Forms::Panel());
					 this->element_statistics_page = (gcnew System::Windows::Forms::TabPage());
					 this->element_list = (gcnew System::Windows::Forms::TreeView());
					 this->panel15 = (gcnew System::Windows::Forms::Panel());
					 this->button4 = (gcnew System::Windows::Forms::Button());
					 this->button6 = (gcnew System::Windows::Forms::Button());
					 this->panel16 = (gcnew System::Windows::Forms::Panel());
					 this->button3 = (gcnew System::Windows::Forms::Button());
					 this->textBox3 = (gcnew System::Windows::Forms::TextBox());
					 this->setting_page = (gcnew System::Windows::Forms::TabPage());
					 this->panel7 = (gcnew System::Windows::Forms::Panel());
					 this->ConfigTab = (gcnew System::Windows::Forms::TabControl());
					 this->Config_env_light_page = (gcnew System::Windows::Forms::TabPage());
					 this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
					 this->button8 = (gcnew System::Windows::Forms::Button());
					 this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
					 this->label28 = (gcnew System::Windows::Forms::Label());
					 this->light_spec_b_edit = (gcnew System::Windows::Forms::TextBox());
					 this->label29 = (gcnew System::Windows::Forms::Label());
					 this->light_spec_g_edit = (gcnew System::Windows::Forms::TextBox());
					 this->label30 = (gcnew System::Windows::Forms::Label());
					 this->light_spec_r_edit = (gcnew System::Windows::Forms::TextBox());
					 this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
					 this->label25 = (gcnew System::Windows::Forms::Label());
					 this->light_diffuse_b_edit = (gcnew System::Windows::Forms::TextBox());
					 this->label26 = (gcnew System::Windows::Forms::Label());
					 this->light_diffuse_g_edit = (gcnew System::Windows::Forms::TextBox());
					 this->label27 = (gcnew System::Windows::Forms::Label());
					 this->light_diffuse_r_edit = (gcnew System::Windows::Forms::TextBox());
					 this->button7 = (gcnew System::Windows::Forms::Button());
					 this->环境光 = (gcnew System::Windows::Forms::GroupBox());
					 this->label24 = (gcnew System::Windows::Forms::Label());
					 this->light_ambient_b_edit = (gcnew System::Windows::Forms::TextBox());
					 this->label11 = (gcnew System::Windows::Forms::Label());
					 this->light_ambient_g_edit = (gcnew System::Windows::Forms::TextBox());
					 this->label1 = (gcnew System::Windows::Forms::Label());
					 this->light_ambient_r_edit = (gcnew System::Windows::Forms::TextBox());
					 this->config_video_page = (gcnew System::Windows::Forms::TabPage());
					 this->groupBox16 = (gcnew System::Windows::Forms::GroupBox());
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
					 this->groupBox13 = (gcnew System::Windows::Forms::GroupBox());
					 this->rb_fog_exp = (gcnew System::Windows::Forms::RadioButton());
					 this->rb_fog_line = (gcnew System::Windows::Forms::RadioButton());
					 this->rb_fog_none = (gcnew System::Windows::Forms::RadioButton());
					 this->groupBox12 = (gcnew System::Windows::Forms::GroupBox());
					 this->rb_shadow_high = (gcnew System::Windows::Forms::RadioButton());
					 this->rb_shadow_medium = (gcnew System::Windows::Forms::RadioButton());
					 this->rb_shadow_low = (gcnew System::Windows::Forms::RadioButton());
					 this->rb_shadow_none = (gcnew System::Windows::Forms::RadioButton());
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
					 this->model_renderhigh_check = (gcnew System::Windows::Forms::CheckBox());
					 this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
					 this->terrain_color_check = (gcnew System::Windows::Forms::CheckBox());
					 this->terrain_shadow_check = (gcnew System::Windows::Forms::CheckBox());
					 this->terrain_offset_check = (gcnew System::Windows::Forms::CheckBox());
					 this->terrain_spec_check = (gcnew System::Windows::Forms::CheckBox());
					 this->terrain_normal_check = (gcnew System::Windows::Forms::CheckBox());
					 this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
					 this->groupBox18 = (gcnew System::Windows::Forms::GroupBox());
					 this->ckb_terrain_grids_visible = (gcnew System::Windows::Forms::CheckBox());
					 this->groupBox17 = (gcnew System::Windows::Forms::GroupBox());
					 this->ckb_wireframe = (gcnew System::Windows::Forms::CheckBox());
					 this->button9 = (gcnew System::Windows::Forms::Button());
					 this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
					 this->label21 = (gcnew System::Windows::Forms::Label());
					 this->fov_edit = (gcnew System::Windows::Forms::TextBox());
					 this->imageList2 = (gcnew System::Windows::Forms::ImageList(this->components));
					 this->terrain_texture_pic_list = (gcnew System::Windows::Forms::ImageList(this->components));
					 this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
					 this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
					 this->tabPage7 = (gcnew System::Windows::Forms::TabPage());
					 this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
					 this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
					 this->tabPage8 = (gcnew System::Windows::Forms::TabPage());
					 this->panel1 = (gcnew System::Windows::Forms::Panel());
					 this->treeView1 = (gcnew System::Windows::Forms::TreeView());
					 this->panel2 = (gcnew System::Windows::Forms::Panel());
					 this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
					 this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
					 this->label3 = (gcnew System::Windows::Forms::Label());
					 this->label4 = (gcnew System::Windows::Forms::Label());
					 this->button11 = (gcnew System::Windows::Forms::Button());
					 this->panel3 = (gcnew System::Windows::Forms::Panel());
					 this->button12 = (gcnew System::Windows::Forms::Button());
					 this->textBox2 = (gcnew System::Windows::Forms::TextBox());
					 this->panel24 = (gcnew System::Windows::Forms::Panel());
					 this->numericUpDown7 = (gcnew System::Windows::Forms::NumericUpDown());
					 this->checkBox7 = (gcnew System::Windows::Forms::CheckBox());
					 this->label5 = (gcnew System::Windows::Forms::Label());
					 this->label12 = (gcnew System::Windows::Forms::Label());
					 this->button23 = (gcnew System::Windows::Forms::Button());
					 this->treeView2 = (gcnew System::Windows::Forms::TreeView());
					 this->panel25 = (gcnew System::Windows::Forms::Panel());
					 this->button24 = (gcnew System::Windows::Forms::Button());
					 this->textBox9 = (gcnew System::Windows::Forms::TextBox());
					 this->panel28 = (gcnew System::Windows::Forms::Panel());
					 this->label15 = (gcnew System::Windows::Forms::Label());
					 this->label32 = (gcnew System::Windows::Forms::Label());
					 this->button27 = (gcnew System::Windows::Forms::Button());
					 this->treeView3 = (gcnew System::Windows::Forms::TreeView());
					 this->panel29 = (gcnew System::Windows::Forms::Panel());
					 this->button28 = (gcnew System::Windows::Forms::Button());
					 this->textBox11 = (gcnew System::Windows::Forms::TextBox());
					 this->panel34 = (gcnew System::Windows::Forms::Panel());
					 this->label37 = (gcnew System::Windows::Forms::Label());
					 this->label39 = (gcnew System::Windows::Forms::Label());
					 this->button33 = (gcnew System::Windows::Forms::Button());
					 this->treeView4 = (gcnew System::Windows::Forms::TreeView());
					 this->panel35 = (gcnew System::Windows::Forms::Panel());
					 this->button34 = (gcnew System::Windows::Forms::Button());
					 this->textBox14 = (gcnew System::Windows::Forms::TextBox());
					 this->panel32 = (gcnew System::Windows::Forms::Panel());
					 this->label38 = (gcnew System::Windows::Forms::Label());
					 this->label40 = (gcnew System::Windows::Forms::Label());
					 this->button31 = (gcnew System::Windows::Forms::Button());
					 this->treeView5 = (gcnew System::Windows::Forms::TreeView());
					 this->panel33 = (gcnew System::Windows::Forms::Panel());
					 this->button32 = (gcnew System::Windows::Forms::Button());
					 this->textBox13 = (gcnew System::Windows::Forms::TextBox());
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
					 this->element_create_page->SuspendLayout();
					 this->SelectCreateElementTypeTab->SuspendLayout();
					 this->create_static_page->SuspendLayout();
					 this->panel26->SuspendLayout();
					 this->panel27->SuspendLayout();
					 this->create_troop_page->SuspendLayout();
					 this->panel23->SuspendLayout();
					 this->panel22->SuspendLayout();
					 this->create_building_page->SuspendLayout();
					 this->panel30->SuspendLayout();
					 this->panel31->SuspendLayout();
					 this->create_monster_page->SuspendLayout();
					 this->panel21->SuspendLayout();
					 this->panel6->SuspendLayout();
					 this->create_npc_page->SuspendLayout();
					 this->panel20->SuspendLayout();
					 this->panel5->SuspendLayout();
					 this->create_object_page->SuspendLayout();
					 this->panel11->SuspendLayout();
					 this->panel14->SuspendLayout();
					 this->panel10->SuspendLayout();
					 this->create_place_page->SuspendLayout();
					 this->panel18->SuspendLayout();
					 this->panel4->SuspendLayout();
					 this->create_point_page->SuspendLayout();
					 this->panel19->SuspendLayout();
					 this->panel17->SuspendLayout();
					 this->create_effect_page->SuspendLayout();
					 this->panel36->SuspendLayout();
					 this->panel37->SuspendLayout();
					 this->element_prop_page->SuspendLayout();
					 this->panel13->SuspendLayout();
					 this->element_statistics_page->SuspendLayout();
					 this->panel15->SuspendLayout();
					 this->panel16->SuspendLayout();
					 this->setting_page->SuspendLayout();
					 this->panel7->SuspendLayout();
					 this->ConfigTab->SuspendLayout();
					 this->Config_env_light_page->SuspendLayout();
					 this->groupBox6->SuspendLayout();
					 this->groupBox5->SuspendLayout();
					 this->groupBox4->SuspendLayout();
					 this->环境光->SuspendLayout();
					 this->config_video_page->SuspendLayout();
					 this->groupBox16->SuspendLayout();
					 this->groupBox15->SuspendLayout();
					 this->groupBox14->SuspendLayout();
					 this->groupBox13->SuspendLayout();
					 this->groupBox12->SuspendLayout();
					 this->groupBox11->SuspendLayout();
					 this->groupBox10->SuspendLayout();
					 this->groupBox9->SuspendLayout();
					 this->groupBox8->SuspendLayout();
					 this->tabPage1->SuspendLayout();
					 this->groupBox18->SuspendLayout();
					 this->groupBox17->SuspendLayout();
					 this->groupBox7->SuspendLayout();
					 this->tabPage7->SuspendLayout();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->BeginInit();
					 this->panel1->SuspendLayout();
					 this->panel2->SuspendLayout();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
					 this->panel3->SuspendLayout();
					 this->panel24->SuspendLayout();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown7))->BeginInit();
					 this->panel25->SuspendLayout();
					 this->panel28->SuspendLayout();
					 this->panel29->SuspendLayout();
					 this->panel34->SuspendLayout();
					 this->panel35->SuspendLayout();
					 this->panel32->SuspendLayout();
					 this->panel33->SuspendLayout();
					 this->SuspendLayout();
					 // 
					 // menuStrip1
					 // 
					 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->wToolStripMenuItem, 
						 this->设置ToolStripMenuItem, this->帮助ToolStripMenuItem});
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
					 // 设置ToolStripMenuItem
					 // 
					 this->设置ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->ToolStripMenuItem_SceneEditorMode});
					 this->设置ToolStripMenuItem->Name = L"设置ToolStripMenuItem";
					 this->设置ToolStripMenuItem->Size = System::Drawing::Size(41, 20);
					 this->设置ToolStripMenuItem->Text = L"设置";
					 // 
					 // ToolStripMenuItem_SceneEditorMode
					 // 
					 this->ToolStripMenuItem_SceneEditorMode->Checked = true;
					 this->ToolStripMenuItem_SceneEditorMode->CheckState = System::Windows::Forms::CheckState::Checked;
					 this->ToolStripMenuItem_SceneEditorMode->Name = L"ToolStripMenuItem_SceneEditorMode";
					 this->ToolStripMenuItem_SceneEditorMode->Size = System::Drawing::Size(118, 22);
					 this->ToolStripMenuItem_SceneEditorMode->Text = L"编辑模式";
					 // 
					 // 帮助ToolStripMenuItem
					 // 
					 this->帮助ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->关于ToolStripMenuItem, 
						 this->主题ToolStripMenuItem});
					 this->帮助ToolStripMenuItem->Name = L"帮助ToolStripMenuItem";
					 this->帮助ToolStripMenuItem->Size = System::Drawing::Size(41, 20);
					 this->帮助ToolStripMenuItem->Text = L"帮助";
					 // 
					 // 关于ToolStripMenuItem
					 // 
					 this->关于ToolStripMenuItem->Name = L"关于ToolStripMenuItem";
					 this->关于ToolStripMenuItem->Size = System::Drawing::Size(94, 22);
					 this->关于ToolStripMenuItem->Text = L"关于";
					 // 
					 // 主题ToolStripMenuItem
					 // 
					 this->主题ToolStripMenuItem->Name = L"主题ToolStripMenuItem";
					 this->主题ToolStripMenuItem->Size = System::Drawing::Size(94, 22);
					 this->主题ToolStripMenuItem->Text = L"主题";
					 // 
					 // statusStrip1
					 // 
					 this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->lable_status_batch, 
						 this->lable_status_LastFPS, this->lable_status_aveFPS, this->lable_status_triCount});
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
					 this->scene_panel->MouseLeave += gcnew System::EventHandler(this, &MainForm::scene_panel_MouseLeave);
					 this->scene_panel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::scene_panel_MouseMove);
					 this->scene_panel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::scene_panel_MouseDown);
					 this->scene_panel->Resize += gcnew System::EventHandler(this, &MainForm::scene_panel_Resize);
					 this->scene_panel->Move += gcnew System::EventHandler(this, &MainForm::scene_panel_Move);
					 this->scene_panel->MouseEnter += gcnew System::EventHandler(this, &MainForm::scene_panel_MouseEnter);
					 // 
					 // panel8
					 // 
					 this->panel8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->panel8->Controls->Add(this->CamSpeed);
					 this->panel8->Controls->Add(this->label8);
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
					 // CamSpeed
					 // 
					 this->CamSpeed->AutoSize = true;
					 this->CamSpeed->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->CamSpeed->Location = System::Drawing::Point(560, 9);
					 this->CamSpeed->Name = L"CamSpeed";
					 this->CamSpeed->Size = System::Drawing::Size(13, 14);
					 this->CamSpeed->TabIndex = 13;
					 this->CamSpeed->Text = L"0";
					 // 
					 // label8
					 // 
					 this->label8->AutoSize = true;
					 this->label8->Location = System::Drawing::Point(471, 9);
					 this->label8->Name = L"label8";
					 this->label8->Size = System::Drawing::Size(83, 12);
					 this->label8->TabIndex = 12;
					 this->label8->Text = L"| 摄像机速度:";
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
					 this->element_tab->Controls->Add(this->element_create_page);
					 this->element_tab->Controls->Add(this->element_prop_page);
					 this->element_tab->Controls->Add(this->element_statistics_page);
					 this->element_tab->Dock = System::Windows::Forms::DockStyle::Fill;
					 this->element_tab->Location = System::Drawing::Point(0, 0);
					 this->element_tab->Name = L"element_tab";
					 this->element_tab->SelectedIndex = 0;
					 this->element_tab->Size = System::Drawing::Size(244, 685);
					 this->element_tab->TabIndex = 0;
					 this->element_tab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::element_tab_SelectedIndexChanged);
					 // 
					 // element_create_page
					 // 
					 this->element_create_page->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->element_create_page->Controls->Add(this->SelectCreateElementTypeTab);
					 this->element_create_page->Location = System::Drawing::Point(4, 24);
					 this->element_create_page->Name = L"element_create_page";
					 this->element_create_page->Padding = System::Windows::Forms::Padding(3);
					 this->element_create_page->Size = System::Drawing::Size(236, 657);
					 this->element_create_page->TabIndex = 1;
					 this->element_create_page->Text = L"新建";
					 this->element_create_page->UseVisualStyleBackColor = true;
					 // 
					 // SelectCreateElementTypeTab
					 // 
					 this->SelectCreateElementTypeTab->Appearance = System::Windows::Forms::TabAppearance::FlatButtons;
					 this->SelectCreateElementTypeTab->Controls->Add(this->create_static_page);
					 this->SelectCreateElementTypeTab->Controls->Add(this->create_troop_page);
					 this->SelectCreateElementTypeTab->Controls->Add(this->create_building_page);
					 this->SelectCreateElementTypeTab->Controls->Add(this->create_monster_page);
					 this->SelectCreateElementTypeTab->Controls->Add(this->create_npc_page);
					 this->SelectCreateElementTypeTab->Controls->Add(this->create_object_page);
					 this->SelectCreateElementTypeTab->Controls->Add(this->create_place_page);
					 this->SelectCreateElementTypeTab->Controls->Add(this->create_point_page);
					 this->SelectCreateElementTypeTab->Controls->Add(this->create_effect_page);
					 this->SelectCreateElementTypeTab->Dock = System::Windows::Forms::DockStyle::Top;
					 this->SelectCreateElementTypeTab->ItemSize = System::Drawing::Size(30, 20);
					 this->SelectCreateElementTypeTab->Location = System::Drawing::Point(3, 3);
					 this->SelectCreateElementTypeTab->Name = L"SelectCreateElementTypeTab";
					 this->SelectCreateElementTypeTab->SelectedIndex = 0;
					 this->SelectCreateElementTypeTab->Size = System::Drawing::Size(226, 647);
					 this->SelectCreateElementTypeTab->TabIndex = 0;
					 this->SelectCreateElementTypeTab->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::SelectCreateElementTypeTab_SelectedIndexChanged);
					 // 
					 // create_static_page
					 // 
					 this->create_static_page->Controls->Add(this->panel26);
					 this->create_static_page->Controls->Add(this->static_object_model_create_tree);
					 this->create_static_page->Controls->Add(this->panel27);
					 this->create_static_page->Location = System::Drawing::Point(4, 24);
					 this->create_static_page->Name = L"create_static_page";
					 this->create_static_page->Padding = System::Windows::Forms::Padding(3);
					 this->create_static_page->Size = System::Drawing::Size(218, 619);
					 this->create_static_page->TabIndex = 7;
					 this->create_static_page->Text = L"景观";
					 this->create_static_page->UseVisualStyleBackColor = true;
					 // 
					 // panel26
					 // 
					 this->panel26->Controls->Add(this->prepare_static_model_text);
					 this->panel26->Controls->Add(this->label19);
					 this->panel26->Controls->Add(this->button25);
					 this->panel26->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel26->Location = System::Drawing::Point(3, 516);
					 this->panel26->Name = L"panel26";
					 this->panel26->Size = System::Drawing::Size(212, 100);
					 this->panel26->TabIndex = 9;
					 // 
					 // prepare_static_model_text
					 // 
					 this->prepare_static_model_text->AutoEllipsis = true;
					 this->prepare_static_model_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->prepare_static_model_text->Location = System::Drawing::Point(11, 33);
					 this->prepare_static_model_text->Name = L"prepare_static_model_text";
					 this->prepare_static_model_text->Size = System::Drawing::Size(193, 57);
					 this->prepare_static_model_text->TabIndex = 3;
					 // 
					 // label19
					 // 
					 this->label19->AutoSize = true;
					 this->label19->Location = System::Drawing::Point(9, 9);
					 this->label19->Name = L"label19";
					 this->label19->Size = System::Drawing::Size(83, 12);
					 this->label19->TabIndex = 2;
					 this->label19->Text = L"当前准备模型:";
					 // 
					 // button25
					 // 
					 this->button25->Location = System::Drawing::Point(167, 4);
					 this->button25->Name = L"button25";
					 this->button25->Size = System::Drawing::Size(37, 23);
					 this->button25->TabIndex = 1;
					 this->button25->Text = L"取消";
					 this->button25->UseVisualStyleBackColor = true;
					 // 
					 // static_object_model_create_tree
					 // 
					 this->static_object_model_create_tree->AllowDrop = true;
					 this->static_object_model_create_tree->Dock = System::Windows::Forms::DockStyle::Top;
					 this->static_object_model_create_tree->Location = System::Drawing::Point(3, 38);
					 this->static_object_model_create_tree->Name = L"static_object_model_create_tree";
					 this->static_object_model_create_tree->Size = System::Drawing::Size(212, 476);
					 this->static_object_model_create_tree->TabIndex = 8;
					 this->static_object_model_create_tree->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::create_static_entity_tree_MouseDoubleClick);
					 this->static_object_model_create_tree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::static_object_model_create_tree_AfterSelect);
					 // 
					 // panel27
					 // 
					 this->panel27->Controls->Add(this->button26);
					 this->panel27->Controls->Add(this->textBox10);
					 this->panel27->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel27->Location = System::Drawing::Point(3, 3);
					 this->panel27->Name = L"panel27";
					 this->panel27->Size = System::Drawing::Size(212, 35);
					 this->panel27->TabIndex = 7;
					 // 
					 // button26
					 // 
					 this->button26->Location = System::Drawing::Point(167, 6);
					 this->button26->Name = L"button26";
					 this->button26->Size = System::Drawing::Size(44, 23);
					 this->button26->TabIndex = 2;
					 this->button26->Text = L"查询";
					 this->button26->UseVisualStyleBackColor = true;
					 // 
					 // textBox10
					 // 
					 this->textBox10->Location = System::Drawing::Point(11, 7);
					 this->textBox10->Name = L"textBox10";
					 this->textBox10->Size = System::Drawing::Size(150, 21);
					 this->textBox10->TabIndex = 1;
					 // 
					 // create_troop_page
					 // 
					 this->create_troop_page->Controls->Add(this->panel23);
					 this->create_troop_page->Controls->Add(this->troop_model_create_tree);
					 this->create_troop_page->Controls->Add(this->panel22);
					 this->create_troop_page->Location = System::Drawing::Point(4, 24);
					 this->create_troop_page->Name = L"create_troop_page";
					 this->create_troop_page->Padding = System::Windows::Forms::Padding(3);
					 this->create_troop_page->Size = System::Drawing::Size(218, 619);
					 this->create_troop_page->TabIndex = 5;
					 this->create_troop_page->Text = L"军队";
					 this->create_troop_page->UseVisualStyleBackColor = true;
					 // 
					 // panel23
					 // 
					 this->panel23->Controls->Add(this->prepare_troop_model_text);
					 this->panel23->Controls->Add(this->label7);
					 this->panel23->Controls->Add(this->button22);
					 this->panel23->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel23->Location = System::Drawing::Point(3, 512);
					 this->panel23->Name = L"panel23";
					 this->panel23->Size = System::Drawing::Size(212, 104);
					 this->panel23->TabIndex = 6;
					 // 
					 // prepare_troop_model_text
					 // 
					 this->prepare_troop_model_text->AutoEllipsis = true;
					 this->prepare_troop_model_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->prepare_troop_model_text->Location = System::Drawing::Point(11, 33);
					 this->prepare_troop_model_text->Name = L"prepare_troop_model_text";
					 this->prepare_troop_model_text->Size = System::Drawing::Size(193, 57);
					 this->prepare_troop_model_text->TabIndex = 3;
					 // 
					 // label7
					 // 
					 this->label7->AutoSize = true;
					 this->label7->Location = System::Drawing::Point(9, 9);
					 this->label7->Name = L"label7";
					 this->label7->Size = System::Drawing::Size(83, 12);
					 this->label7->TabIndex = 2;
					 this->label7->Text = L"当前准备模型:";
					 // 
					 // button22
					 // 
					 this->button22->Location = System::Drawing::Point(167, 4);
					 this->button22->Name = L"button22";
					 this->button22->Size = System::Drawing::Size(37, 23);
					 this->button22->TabIndex = 1;
					 this->button22->Text = L"取消";
					 this->button22->UseVisualStyleBackColor = true;
					 // 
					 // troop_model_create_tree
					 // 
					 this->troop_model_create_tree->AllowDrop = true;
					 this->troop_model_create_tree->Dock = System::Windows::Forms::DockStyle::Top;
					 this->troop_model_create_tree->Location = System::Drawing::Point(3, 38);
					 this->troop_model_create_tree->Name = L"troop_model_create_tree";
					 this->troop_model_create_tree->Size = System::Drawing::Size(212, 472);
					 this->troop_model_create_tree->TabIndex = 5;
					 this->troop_model_create_tree->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::create_troop_entity_tree_MouseDoubleClick);
					 this->troop_model_create_tree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::troop_model_create_tree_AfterSelect);
					 // 
					 // panel22
					 // 
					 this->panel22->Controls->Add(this->button21);
					 this->panel22->Controls->Add(this->textBox8);
					 this->panel22->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel22->Location = System::Drawing::Point(3, 3);
					 this->panel22->Name = L"panel22";
					 this->panel22->Size = System::Drawing::Size(212, 35);
					 this->panel22->TabIndex = 3;
					 // 
					 // button21
					 // 
					 this->button21->Location = System::Drawing::Point(167, 6);
					 this->button21->Name = L"button21";
					 this->button21->Size = System::Drawing::Size(44, 23);
					 this->button21->TabIndex = 2;
					 this->button21->Text = L"查询";
					 this->button21->UseVisualStyleBackColor = true;
					 // 
					 // textBox8
					 // 
					 this->textBox8->Location = System::Drawing::Point(11, 7);
					 this->textBox8->Name = L"textBox8";
					 this->textBox8->Size = System::Drawing::Size(150, 21);
					 this->textBox8->TabIndex = 1;
					 // 
					 // create_building_page
					 // 
					 this->create_building_page->Controls->Add(this->panel30);
					 this->create_building_page->Controls->Add(this->building_model_create_tree);
					 this->create_building_page->Controls->Add(this->panel31);
					 this->create_building_page->Location = System::Drawing::Point(4, 24);
					 this->create_building_page->Name = L"create_building_page";
					 this->create_building_page->Padding = System::Windows::Forms::Padding(3);
					 this->create_building_page->Size = System::Drawing::Size(218, 619);
					 this->create_building_page->TabIndex = 9;
					 this->create_building_page->Text = L"建筑";
					 this->create_building_page->UseVisualStyleBackColor = true;
					 // 
					 // panel30
					 // 
					 this->panel30->Controls->Add(this->prepare_building_model_text);
					 this->panel30->Controls->Add(this->label33);
					 this->panel30->Controls->Add(this->button29);
					 this->panel30->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel30->Location = System::Drawing::Point(3, 513);
					 this->panel30->Name = L"panel30";
					 this->panel30->Size = System::Drawing::Size(212, 103);
					 this->panel30->TabIndex = 12;
					 // 
					 // prepare_building_model_text
					 // 
					 this->prepare_building_model_text->AutoEllipsis = true;
					 this->prepare_building_model_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->prepare_building_model_text->Location = System::Drawing::Point(11, 33);
					 this->prepare_building_model_text->Name = L"prepare_building_model_text";
					 this->prepare_building_model_text->Size = System::Drawing::Size(193, 57);
					 this->prepare_building_model_text->TabIndex = 3;
					 // 
					 // label33
					 // 
					 this->label33->AutoSize = true;
					 this->label33->Location = System::Drawing::Point(9, 9);
					 this->label33->Name = L"label33";
					 this->label33->Size = System::Drawing::Size(83, 12);
					 this->label33->TabIndex = 2;
					 this->label33->Text = L"当前准备模型:";
					 // 
					 // button29
					 // 
					 this->button29->Location = System::Drawing::Point(167, 4);
					 this->button29->Name = L"button29";
					 this->button29->Size = System::Drawing::Size(37, 23);
					 this->button29->TabIndex = 1;
					 this->button29->Text = L"取消";
					 this->button29->UseVisualStyleBackColor = true;
					 // 
					 // building_model_create_tree
					 // 
					 this->building_model_create_tree->AllowDrop = true;
					 this->building_model_create_tree->Dock = System::Windows::Forms::DockStyle::Top;
					 this->building_model_create_tree->Location = System::Drawing::Point(3, 38);
					 this->building_model_create_tree->Name = L"building_model_create_tree";
					 this->building_model_create_tree->Size = System::Drawing::Size(212, 473);
					 this->building_model_create_tree->TabIndex = 11;
					 this->building_model_create_tree->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::create_building_entity_tree_MouseDoubleClick);
					 this->building_model_create_tree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::building_model_create_tree_AfterSelect);
					 // 
					 // panel31
					 // 
					 this->panel31->Controls->Add(this->button30);
					 this->panel31->Controls->Add(this->textBox12);
					 this->panel31->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel31->Location = System::Drawing::Point(3, 3);
					 this->panel31->Name = L"panel31";
					 this->panel31->Size = System::Drawing::Size(212, 35);
					 this->panel31->TabIndex = 10;
					 // 
					 // button30
					 // 
					 this->button30->Location = System::Drawing::Point(167, 6);
					 this->button30->Name = L"button30";
					 this->button30->Size = System::Drawing::Size(44, 23);
					 this->button30->TabIndex = 2;
					 this->button30->Text = L"查询";
					 this->button30->UseVisualStyleBackColor = true;
					 // 
					 // textBox12
					 // 
					 this->textBox12->Location = System::Drawing::Point(11, 7);
					 this->textBox12->Name = L"textBox12";
					 this->textBox12->Size = System::Drawing::Size(150, 21);
					 this->textBox12->TabIndex = 1;
					 // 
					 // create_monster_page
					 // 
					 this->create_monster_page->Controls->Add(this->panel21);
					 this->create_monster_page->Controls->Add(this->monster_model_create_tree);
					 this->create_monster_page->Controls->Add(this->panel6);
					 this->create_monster_page->Location = System::Drawing::Point(4, 24);
					 this->create_monster_page->Name = L"create_monster_page";
					 this->create_monster_page->Padding = System::Windows::Forms::Padding(3);
					 this->create_monster_page->Size = System::Drawing::Size(218, 619);
					 this->create_monster_page->TabIndex = 4;
					 this->create_monster_page->Text = L"怪物";
					 this->create_monster_page->UseVisualStyleBackColor = true;
					 // 
					 // panel21
					 // 
					 this->panel21->Controls->Add(this->prepare_monster_model_text);
					 this->panel21->Controls->Add(this->label17);
					 this->panel21->Controls->Add(this->button20);
					 this->panel21->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel21->Location = System::Drawing::Point(3, 513);
					 this->panel21->Name = L"panel21";
					 this->panel21->Size = System::Drawing::Size(212, 103);
					 this->panel21->TabIndex = 5;
					 // 
					 // prepare_monster_model_text
					 // 
					 this->prepare_monster_model_text->AutoEllipsis = true;
					 this->prepare_monster_model_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->prepare_monster_model_text->Location = System::Drawing::Point(11, 33);
					 this->prepare_monster_model_text->Name = L"prepare_monster_model_text";
					 this->prepare_monster_model_text->Size = System::Drawing::Size(193, 57);
					 this->prepare_monster_model_text->TabIndex = 3;
					 // 
					 // label17
					 // 
					 this->label17->AutoSize = true;
					 this->label17->Location = System::Drawing::Point(9, 9);
					 this->label17->Name = L"label17";
					 this->label17->Size = System::Drawing::Size(83, 12);
					 this->label17->TabIndex = 2;
					 this->label17->Text = L"当前准备模型:";
					 // 
					 // button20
					 // 
					 this->button20->Location = System::Drawing::Point(167, 4);
					 this->button20->Name = L"button20";
					 this->button20->Size = System::Drawing::Size(37, 23);
					 this->button20->TabIndex = 1;
					 this->button20->Text = L"取消";
					 this->button20->UseVisualStyleBackColor = true;
					 // 
					 // monster_model_create_tree
					 // 
					 this->monster_model_create_tree->AllowDrop = true;
					 this->monster_model_create_tree->Dock = System::Windows::Forms::DockStyle::Top;
					 this->monster_model_create_tree->Location = System::Drawing::Point(3, 38);
					 this->monster_model_create_tree->Name = L"monster_model_create_tree";
					 this->monster_model_create_tree->Size = System::Drawing::Size(212, 473);
					 this->monster_model_create_tree->TabIndex = 4;
					 this->monster_model_create_tree->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::create_monster_entity_tree_MouseDoubleClick);
					 this->monster_model_create_tree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::monster_model_create_tree_AfterSelect);
					 // 
					 // panel6
					 // 
					 this->panel6->Controls->Add(this->button15);
					 this->panel6->Controls->Add(this->textBox6);
					 this->panel6->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel6->Location = System::Drawing::Point(3, 3);
					 this->panel6->Name = L"panel6";
					 this->panel6->Size = System::Drawing::Size(212, 35);
					 this->panel6->TabIndex = 2;
					 // 
					 // button15
					 // 
					 this->button15->Location = System::Drawing::Point(167, 6);
					 this->button15->Name = L"button15";
					 this->button15->Size = System::Drawing::Size(44, 23);
					 this->button15->TabIndex = 2;
					 this->button15->Text = L"查询";
					 this->button15->UseVisualStyleBackColor = true;
					 // 
					 // textBox6
					 // 
					 this->textBox6->Location = System::Drawing::Point(11, 7);
					 this->textBox6->Name = L"textBox6";
					 this->textBox6->Size = System::Drawing::Size(150, 21);
					 this->textBox6->TabIndex = 1;
					 // 
					 // create_npc_page
					 // 
					 this->create_npc_page->Controls->Add(this->panel20);
					 this->create_npc_page->Controls->Add(this->NPC_model_create_tree);
					 this->create_npc_page->Controls->Add(this->panel5);
					 this->create_npc_page->Location = System::Drawing::Point(4, 24);
					 this->create_npc_page->Name = L"create_npc_page";
					 this->create_npc_page->Padding = System::Windows::Forms::Padding(3);
					 this->create_npc_page->Size = System::Drawing::Size(218, 619);
					 this->create_npc_page->TabIndex = 3;
					 this->create_npc_page->Text = L"NPC";
					 this->create_npc_page->UseVisualStyleBackColor = true;
					 // 
					 // panel20
					 // 
					 this->panel20->Controls->Add(this->prepare_npc_model_text);
					 this->panel20->Controls->Add(this->label13);
					 this->panel20->Controls->Add(this->button19);
					 this->panel20->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel20->Location = System::Drawing::Point(3, 513);
					 this->panel20->Name = L"panel20";
					 this->panel20->Size = System::Drawing::Size(212, 103);
					 this->panel20->TabIndex = 5;
					 // 
					 // prepare_npc_model_text
					 // 
					 this->prepare_npc_model_text->AutoEllipsis = true;
					 this->prepare_npc_model_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->prepare_npc_model_text->Location = System::Drawing::Point(11, 33);
					 this->prepare_npc_model_text->Name = L"prepare_npc_model_text";
					 this->prepare_npc_model_text->Size = System::Drawing::Size(193, 57);
					 this->prepare_npc_model_text->TabIndex = 3;
					 // 
					 // label13
					 // 
					 this->label13->AutoSize = true;
					 this->label13->Location = System::Drawing::Point(9, 9);
					 this->label13->Name = L"label13";
					 this->label13->Size = System::Drawing::Size(83, 12);
					 this->label13->TabIndex = 2;
					 this->label13->Text = L"当前准备模型:";
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
					 // NPC_model_create_tree
					 // 
					 this->NPC_model_create_tree->AllowDrop = true;
					 this->NPC_model_create_tree->Dock = System::Windows::Forms::DockStyle::Top;
					 this->NPC_model_create_tree->Location = System::Drawing::Point(3, 38);
					 this->NPC_model_create_tree->Name = L"NPC_model_create_tree";
					 this->NPC_model_create_tree->Size = System::Drawing::Size(212, 473);
					 this->NPC_model_create_tree->TabIndex = 4;
					 this->NPC_model_create_tree->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::create_npc_entity_tree_MouseDoubleClick);
					 this->NPC_model_create_tree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::NPC_model_create_tree_AfterSelect);
					 // 
					 // panel5
					 // 
					 this->panel5->Controls->Add(this->button14);
					 this->panel5->Controls->Add(this->textBox5);
					 this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel5->Location = System::Drawing::Point(3, 3);
					 this->panel5->Name = L"panel5";
					 this->panel5->Size = System::Drawing::Size(212, 35);
					 this->panel5->TabIndex = 2;
					 // 
					 // button14
					 // 
					 this->button14->Location = System::Drawing::Point(167, 6);
					 this->button14->Name = L"button14";
					 this->button14->Size = System::Drawing::Size(44, 23);
					 this->button14->TabIndex = 2;
					 this->button14->Text = L"查询";
					 this->button14->UseVisualStyleBackColor = true;
					 // 
					 // textBox5
					 // 
					 this->textBox5->Location = System::Drawing::Point(11, 7);
					 this->textBox5->Name = L"textBox5";
					 this->textBox5->Size = System::Drawing::Size(150, 21);
					 this->textBox5->TabIndex = 1;
					 // 
					 // create_object_page
					 // 
					 this->create_object_page->Controls->Add(this->panel11);
					 this->create_object_page->Controls->Add(this->panel10);
					 this->create_object_page->Location = System::Drawing::Point(4, 24);
					 this->create_object_page->Name = L"create_object_page";
					 this->create_object_page->Padding = System::Windows::Forms::Padding(3);
					 this->create_object_page->Size = System::Drawing::Size(218, 619);
					 this->create_object_page->TabIndex = 0;
					 this->create_object_page->Text = L"物件";
					 this->create_object_page->UseVisualStyleBackColor = true;
					 // 
					 // panel11
					 // 
					 this->panel11->Controls->Add(this->object_model_create_tree);
					 this->panel11->Controls->Add(this->panel14);
					 this->panel11->Dock = System::Windows::Forms::DockStyle::Fill;
					 this->panel11->Location = System::Drawing::Point(3, 38);
					 this->panel11->Name = L"panel11";
					 this->panel11->Size = System::Drawing::Size(212, 578);
					 this->panel11->TabIndex = 1;
					 // 
					 // object_model_create_tree
					 // 
					 this->object_model_create_tree->AllowDrop = true;
					 this->object_model_create_tree->Dock = System::Windows::Forms::DockStyle::Top;
					 this->object_model_create_tree->Location = System::Drawing::Point(0, 0);
					 this->object_model_create_tree->Name = L"object_model_create_tree";
					 this->object_model_create_tree->Size = System::Drawing::Size(212, 474);
					 this->object_model_create_tree->TabIndex = 2;
					 this->object_model_create_tree->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::create_object_entity_tree_MouseDoubleClick);
					 this->object_model_create_tree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::object_model_create_tree_AfterSelect);
					 // 
					 // panel14
					 // 
					 this->panel14->Controls->Add(this->prepare_object_model_text);
					 this->panel14->Controls->Add(this->label23);
					 this->panel14->Controls->Add(this->button5);
					 this->panel14->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel14->Location = System::Drawing::Point(0, 476);
					 this->panel14->Name = L"panel14";
					 this->panel14->Size = System::Drawing::Size(212, 102);
					 this->panel14->TabIndex = 1;
					 // 
					 // prepare_object_model_text
					 // 
					 this->prepare_object_model_text->AutoEllipsis = true;
					 this->prepare_object_model_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->prepare_object_model_text->Location = System::Drawing::Point(11, 33);
					 this->prepare_object_model_text->Name = L"prepare_object_model_text";
					 this->prepare_object_model_text->Size = System::Drawing::Size(193, 57);
					 this->prepare_object_model_text->TabIndex = 3;
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
					 // create_place_page
					 // 
					 this->create_place_page->Controls->Add(this->panel18);
					 this->create_place_page->Controls->Add(this->place_model_create_tree);
					 this->create_place_page->Controls->Add(this->panel4);
					 this->create_place_page->Location = System::Drawing::Point(4, 24);
					 this->create_place_page->Name = L"create_place_page";
					 this->create_place_page->Padding = System::Windows::Forms::Padding(3);
					 this->create_place_page->Size = System::Drawing::Size(218, 619);
					 this->create_place_page->TabIndex = 1;
					 this->create_place_page->Text = L"地点";
					 this->create_place_page->UseVisualStyleBackColor = true;
					 // 
					 // panel18
					 // 
					 this->panel18->Controls->Add(this->prepare_place_model_text);
					 this->panel18->Controls->Add(this->label6);
					 this->panel18->Controls->Add(this->button17);
					 this->panel18->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel18->Location = System::Drawing::Point(3, 514);
					 this->panel18->Name = L"panel18";
					 this->panel18->Size = System::Drawing::Size(212, 102);
					 this->panel18->TabIndex = 4;
					 // 
					 // prepare_place_model_text
					 // 
					 this->prepare_place_model_text->AutoEllipsis = true;
					 this->prepare_place_model_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->prepare_place_model_text->Location = System::Drawing::Point(11, 33);
					 this->prepare_place_model_text->Name = L"prepare_place_model_text";
					 this->prepare_place_model_text->Size = System::Drawing::Size(193, 57);
					 this->prepare_place_model_text->TabIndex = 3;
					 // 
					 // label6
					 // 
					 this->label6->AutoSize = true;
					 this->label6->Location = System::Drawing::Point(9, 9);
					 this->label6->Name = L"label6";
					 this->label6->Size = System::Drawing::Size(83, 12);
					 this->label6->TabIndex = 2;
					 this->label6->Text = L"当前准备模型:";
					 // 
					 // button17
					 // 
					 this->button17->Location = System::Drawing::Point(167, 4);
					 this->button17->Name = L"button17";
					 this->button17->Size = System::Drawing::Size(37, 23);
					 this->button17->TabIndex = 1;
					 this->button17->Text = L"取消";
					 this->button17->UseVisualStyleBackColor = true;
					 // 
					 // place_model_create_tree
					 // 
					 this->place_model_create_tree->AllowDrop = true;
					 this->place_model_create_tree->Dock = System::Windows::Forms::DockStyle::Top;
					 this->place_model_create_tree->Location = System::Drawing::Point(3, 38);
					 this->place_model_create_tree->Name = L"place_model_create_tree";
					 this->place_model_create_tree->Size = System::Drawing::Size(212, 474);
					 this->place_model_create_tree->TabIndex = 3;
					 this->place_model_create_tree->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::create_place_entity_tree_MouseDoubleClick);
					 this->place_model_create_tree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::place_model_create_tree_AfterSelect);
					 // 
					 // panel4
					 // 
					 this->panel4->Controls->Add(this->button13);
					 this->panel4->Controls->Add(this->textBox4);
					 this->panel4->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel4->Location = System::Drawing::Point(3, 3);
					 this->panel4->Name = L"panel4";
					 this->panel4->Size = System::Drawing::Size(212, 35);
					 this->panel4->TabIndex = 1;
					 // 
					 // button13
					 // 
					 this->button13->Location = System::Drawing::Point(167, 6);
					 this->button13->Name = L"button13";
					 this->button13->Size = System::Drawing::Size(44, 23);
					 this->button13->TabIndex = 2;
					 this->button13->Text = L"查询";
					 this->button13->UseVisualStyleBackColor = true;
					 // 
					 // textBox4
					 // 
					 this->textBox4->Location = System::Drawing::Point(11, 7);
					 this->textBox4->Name = L"textBox4";
					 this->textBox4->Size = System::Drawing::Size(150, 21);
					 this->textBox4->TabIndex = 1;
					 // 
					 // create_point_page
					 // 
					 this->create_point_page->Controls->Add(this->panel19);
					 this->create_point_page->Controls->Add(this->point_model_create_tree);
					 this->create_point_page->Controls->Add(this->panel17);
					 this->create_point_page->Location = System::Drawing::Point(4, 24);
					 this->create_point_page->Name = L"create_point_page";
					 this->create_point_page->Padding = System::Windows::Forms::Padding(3);
					 this->create_point_page->Size = System::Drawing::Size(218, 619);
					 this->create_point_page->TabIndex = 2;
					 this->create_point_page->Text = L"坐标点";
					 this->create_point_page->UseVisualStyleBackColor = true;
					 // 
					 // panel19
					 // 
					 this->panel19->Controls->Add(this->prepare_point_model_text);
					 this->panel19->Controls->Add(this->label10);
					 this->panel19->Controls->Add(this->button18);
					 this->panel19->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel19->Location = System::Drawing::Point(3, 515);
					 this->panel19->Name = L"panel19";
					 this->panel19->Size = System::Drawing::Size(212, 101);
					 this->panel19->TabIndex = 5;
					 // 
					 // prepare_point_model_text
					 // 
					 this->prepare_point_model_text->AutoEllipsis = true;
					 this->prepare_point_model_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->prepare_point_model_text->Location = System::Drawing::Point(11, 33);
					 this->prepare_point_model_text->Name = L"prepare_point_model_text";
					 this->prepare_point_model_text->Size = System::Drawing::Size(193, 57);
					 this->prepare_point_model_text->TabIndex = 3;
					 // 
					 // label10
					 // 
					 this->label10->AutoSize = true;
					 this->label10->Location = System::Drawing::Point(9, 9);
					 this->label10->Name = L"label10";
					 this->label10->Size = System::Drawing::Size(83, 12);
					 this->label10->TabIndex = 2;
					 this->label10->Text = L"当前准备模型:";
					 // 
					 // button18
					 // 
					 this->button18->Location = System::Drawing::Point(167, 4);
					 this->button18->Name = L"button18";
					 this->button18->Size = System::Drawing::Size(37, 23);
					 this->button18->TabIndex = 1;
					 this->button18->Text = L"取消";
					 this->button18->UseVisualStyleBackColor = true;
					 // 
					 // point_model_create_tree
					 // 
					 this->point_model_create_tree->AllowDrop = true;
					 this->point_model_create_tree->Dock = System::Windows::Forms::DockStyle::Top;
					 this->point_model_create_tree->Location = System::Drawing::Point(3, 38);
					 this->point_model_create_tree->Name = L"point_model_create_tree";
					 this->point_model_create_tree->Size = System::Drawing::Size(212, 475);
					 this->point_model_create_tree->TabIndex = 4;
					 this->point_model_create_tree->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::create_point_entity_tree_MouseDoubleClick);
					 this->point_model_create_tree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::point_model_create_tree_AfterSelect);
					 // 
					 // panel17
					 // 
					 this->panel17->Controls->Add(this->button16);
					 this->panel17->Controls->Add(this->textBox7);
					 this->panel17->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel17->Location = System::Drawing::Point(3, 3);
					 this->panel17->Name = L"panel17";
					 this->panel17->Size = System::Drawing::Size(212, 35);
					 this->panel17->TabIndex = 2;
					 // 
					 // button16
					 // 
					 this->button16->Location = System::Drawing::Point(167, 6);
					 this->button16->Name = L"button16";
					 this->button16->Size = System::Drawing::Size(44, 23);
					 this->button16->TabIndex = 2;
					 this->button16->Text = L"查询";
					 this->button16->UseVisualStyleBackColor = true;
					 // 
					 // textBox7
					 // 
					 this->textBox7->Location = System::Drawing::Point(11, 7);
					 this->textBox7->Name = L"textBox7";
					 this->textBox7->Size = System::Drawing::Size(150, 21);
					 this->textBox7->TabIndex = 1;
					 // 
					 // create_effect_page
					 // 
					 this->create_effect_page->Controls->Add(this->panel36);
					 this->create_effect_page->Controls->Add(this->effect_create_tree);
					 this->create_effect_page->Controls->Add(this->panel37);
					 this->create_effect_page->Location = System::Drawing::Point(4, 24);
					 this->create_effect_page->Name = L"create_effect_page";
					 this->create_effect_page->Padding = System::Windows::Forms::Padding(3);
					 this->create_effect_page->Size = System::Drawing::Size(218, 619);
					 this->create_effect_page->TabIndex = 10;
					 this->create_effect_page->Text = L"特效";
					 this->create_effect_page->UseVisualStyleBackColor = true;
					 // 
					 // panel36
					 // 
					 this->panel36->Controls->Add(this->prepare_effect_text);
					 this->panel36->Controls->Add(this->label42);
					 this->panel36->Controls->Add(this->button35);
					 this->panel36->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel36->Location = System::Drawing::Point(3, 515);
					 this->panel36->Name = L"panel36";
					 this->panel36->Size = System::Drawing::Size(212, 101);
					 this->panel36->TabIndex = 5;
					 // 
					 // prepare_effect_text
					 // 
					 this->prepare_effect_text->AutoEllipsis = true;
					 this->prepare_effect_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->prepare_effect_text->Location = System::Drawing::Point(11, 33);
					 this->prepare_effect_text->Name = L"prepare_effect_text";
					 this->prepare_effect_text->Size = System::Drawing::Size(193, 57);
					 this->prepare_effect_text->TabIndex = 3;
					 // 
					 // label42
					 // 
					 this->label42->AutoSize = true;
					 this->label42->Location = System::Drawing::Point(9, 9);
					 this->label42->Name = L"label42";
					 this->label42->Size = System::Drawing::Size(83, 12);
					 this->label42->TabIndex = 2;
					 this->label42->Text = L"当前准备特效:";
					 // 
					 // button35
					 // 
					 this->button35->Location = System::Drawing::Point(167, 4);
					 this->button35->Name = L"button35";
					 this->button35->Size = System::Drawing::Size(37, 23);
					 this->button35->TabIndex = 1;
					 this->button35->Text = L"取消";
					 this->button35->UseVisualStyleBackColor = true;
					 // 
					 // effect_create_tree
					 // 
					 this->effect_create_tree->AllowDrop = true;
					 this->effect_create_tree->Dock = System::Windows::Forms::DockStyle::Top;
					 this->effect_create_tree->Location = System::Drawing::Point(3, 38);
					 this->effect_create_tree->Name = L"effect_create_tree";
					 this->effect_create_tree->Size = System::Drawing::Size(212, 475);
					 this->effect_create_tree->TabIndex = 4;
					 this->effect_create_tree->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainForm::effect_create_tree_AfterSelect);
					 // 
					 // panel37
					 // 
					 this->panel37->Controls->Add(this->button36);
					 this->panel37->Controls->Add(this->textBox15);
					 this->panel37->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel37->Location = System::Drawing::Point(3, 3);
					 this->panel37->Name = L"panel37";
					 this->panel37->Size = System::Drawing::Size(212, 35);
					 this->panel37->TabIndex = 2;
					 // 
					 // button36
					 // 
					 this->button36->Location = System::Drawing::Point(167, 6);
					 this->button36->Name = L"button36";
					 this->button36->Size = System::Drawing::Size(44, 23);
					 this->button36->TabIndex = 2;
					 this->button36->Text = L"查询";
					 this->button36->UseVisualStyleBackColor = true;
					 // 
					 // textBox15
					 // 
					 this->textBox15->Location = System::Drawing::Point(11, 7);
					 this->textBox15->Name = L"textBox15";
					 this->textBox15->Size = System::Drawing::Size(150, 21);
					 this->textBox15->TabIndex = 1;
					 // 
					 // element_prop_page
					 // 
					 this->element_prop_page->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->element_prop_page->Controls->Add(this->panel13);
					 this->element_prop_page->Controls->Add(this->panel12);
					 this->element_prop_page->Location = System::Drawing::Point(4, 24);
					 this->element_prop_page->Name = L"element_prop_page";
					 this->element_prop_page->Padding = System::Windows::Forms::Padding(3);
					 this->element_prop_page->Size = System::Drawing::Size(236, 657);
					 this->element_prop_page->TabIndex = 2;
					 this->element_prop_page->Text = L"属性";
					 this->element_prop_page->UseVisualStyleBackColor = true;
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
					 // element_statistics_page
					 // 
					 this->element_statistics_page->Controls->Add(this->element_list);
					 this->element_statistics_page->Controls->Add(this->panel15);
					 this->element_statistics_page->Controls->Add(this->panel16);
					 this->element_statistics_page->Location = System::Drawing::Point(4, 24);
					 this->element_statistics_page->Name = L"element_statistics_page";
					 this->element_statistics_page->Padding = System::Windows::Forms::Padding(3);
					 this->element_statistics_page->Size = System::Drawing::Size(236, 657);
					 this->element_statistics_page->TabIndex = 3;
					 this->element_statistics_page->Text = L"统计";
					 this->element_statistics_page->UseVisualStyleBackColor = true;
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
					 this->ConfigTab->Controls->Add(this->tabPage1);
					 this->ConfigTab->Dock = System::Windows::Forms::DockStyle::Fill;
					 this->ConfigTab->Location = System::Drawing::Point(0, 0);
					 this->ConfigTab->Name = L"ConfigTab";
					 this->ConfigTab->SelectedIndex = 0;
					 this->ConfigTab->Size = System::Drawing::Size(244, 685);
					 this->ConfigTab->TabIndex = 0;
					 // 
					 // Config_env_light_page
					 // 
					 this->Config_env_light_page->Controls->Add(this->groupBox6);
					 this->Config_env_light_page->Controls->Add(this->groupBox5);
					 this->Config_env_light_page->Controls->Add(this->groupBox4);
					 this->Config_env_light_page->Controls->Add(this->button7);
					 this->Config_env_light_page->Controls->Add(this->环境光);
					 this->Config_env_light_page->Location = System::Drawing::Point(4, 24);
					 this->Config_env_light_page->Name = L"Config_env_light_page";
					 this->Config_env_light_page->Padding = System::Windows::Forms::Padding(3);
					 this->Config_env_light_page->Size = System::Drawing::Size(236, 657);
					 this->Config_env_light_page->TabIndex = 0;
					 this->Config_env_light_page->Text = L"灯光";
					 this->Config_env_light_page->UseVisualStyleBackColor = true;
					 // 
					 // groupBox6
					 // 
					 this->groupBox6->Controls->Add(this->button8);
					 this->groupBox6->Location = System::Drawing::Point(19, 249);
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
					 // groupBox5
					 // 
					 this->groupBox5->Controls->Add(this->label28);
					 this->groupBox5->Controls->Add(this->light_spec_b_edit);
					 this->groupBox5->Controls->Add(this->label29);
					 this->groupBox5->Controls->Add(this->light_spec_g_edit);
					 this->groupBox5->Controls->Add(this->label30);
					 this->groupBox5->Controls->Add(this->light_spec_r_edit);
					 this->groupBox5->Location = System::Drawing::Point(19, 174);
					 this->groupBox5->Name = L"groupBox5";
					 this->groupBox5->Size = System::Drawing::Size(200, 50);
					 this->groupBox5->TabIndex = 3;
					 this->groupBox5->TabStop = false;
					 this->groupBox5->Text = L"镜面反射";
					 // 
					 // label28
					 // 
					 this->label28->AutoSize = true;
					 this->label28->Location = System::Drawing::Point(138, 21);
					 this->label28->Name = L"label28";
					 this->label28->Size = System::Drawing::Size(17, 12);
					 this->label28->TabIndex = 5;
					 this->label28->Text = L"b:";
					 // 
					 // light_spec_b_edit
					 // 
					 this->light_spec_b_edit->Location = System::Drawing::Point(161, 18);
					 this->light_spec_b_edit->Name = L"light_spec_b_edit";
					 this->light_spec_b_edit->Size = System::Drawing::Size(33, 21);
					 this->light_spec_b_edit->TabIndex = 4;
					 this->light_spec_b_edit->Text = L"0.4";
					 // 
					 // label29
					 // 
					 this->label29->AutoSize = true;
					 this->label29->Location = System::Drawing::Point(72, 21);
					 this->label29->Name = L"label29";
					 this->label29->Size = System::Drawing::Size(17, 12);
					 this->label29->TabIndex = 3;
					 this->label29->Text = L"g:";
					 // 
					 // light_spec_g_edit
					 // 
					 this->light_spec_g_edit->Location = System::Drawing::Point(95, 18);
					 this->light_spec_g_edit->Name = L"light_spec_g_edit";
					 this->light_spec_g_edit->Size = System::Drawing::Size(33, 21);
					 this->light_spec_g_edit->TabIndex = 2;
					 this->light_spec_g_edit->Text = L"0.4";
					 // 
					 // label30
					 // 
					 this->label30->AutoSize = true;
					 this->label30->Location = System::Drawing::Point(7, 21);
					 this->label30->Name = L"label30";
					 this->label30->Size = System::Drawing::Size(17, 12);
					 this->label30->TabIndex = 1;
					 this->label30->Text = L"r:";
					 // 
					 // light_spec_r_edit
					 // 
					 this->light_spec_r_edit->Location = System::Drawing::Point(30, 18);
					 this->light_spec_r_edit->Name = L"light_spec_r_edit";
					 this->light_spec_r_edit->Size = System::Drawing::Size(33, 21);
					 this->light_spec_r_edit->TabIndex = 0;
					 this->light_spec_r_edit->Text = L"0.4";
					 // 
					 // groupBox4
					 // 
					 this->groupBox4->Controls->Add(this->label25);
					 this->groupBox4->Controls->Add(this->light_diffuse_b_edit);
					 this->groupBox4->Controls->Add(this->label26);
					 this->groupBox4->Controls->Add(this->light_diffuse_g_edit);
					 this->groupBox4->Controls->Add(this->label27);
					 this->groupBox4->Controls->Add(this->light_diffuse_r_edit);
					 this->groupBox4->Location = System::Drawing::Point(19, 95);
					 this->groupBox4->Name = L"groupBox4";
					 this->groupBox4->Size = System::Drawing::Size(200, 50);
					 this->groupBox4->TabIndex = 2;
					 this->groupBox4->TabStop = false;
					 this->groupBox4->Text = L"漫反射";
					 // 
					 // label25
					 // 
					 this->label25->AutoSize = true;
					 this->label25->Location = System::Drawing::Point(138, 21);
					 this->label25->Name = L"label25";
					 this->label25->Size = System::Drawing::Size(17, 12);
					 this->label25->TabIndex = 5;
					 this->label25->Text = L"b:";
					 // 
					 // light_diffuse_b_edit
					 // 
					 this->light_diffuse_b_edit->Location = System::Drawing::Point(161, 18);
					 this->light_diffuse_b_edit->Name = L"light_diffuse_b_edit";
					 this->light_diffuse_b_edit->Size = System::Drawing::Size(31, 21);
					 this->light_diffuse_b_edit->TabIndex = 4;
					 this->light_diffuse_b_edit->Text = L"1.0";
					 // 
					 // label26
					 // 
					 this->label26->AutoSize = true;
					 this->label26->Location = System::Drawing::Point(72, 21);
					 this->label26->Name = L"label26";
					 this->label26->Size = System::Drawing::Size(17, 12);
					 this->label26->TabIndex = 3;
					 this->label26->Text = L"g:";
					 // 
					 // light_diffuse_g_edit
					 // 
					 this->light_diffuse_g_edit->Location = System::Drawing::Point(95, 18);
					 this->light_diffuse_g_edit->Name = L"light_diffuse_g_edit";
					 this->light_diffuse_g_edit->Size = System::Drawing::Size(33, 21);
					 this->light_diffuse_g_edit->TabIndex = 2;
					 this->light_diffuse_g_edit->Text = L"1.0";
					 // 
					 // label27
					 // 
					 this->label27->AutoSize = true;
					 this->label27->Location = System::Drawing::Point(7, 21);
					 this->label27->Name = L"label27";
					 this->label27->Size = System::Drawing::Size(17, 12);
					 this->label27->TabIndex = 1;
					 this->label27->Text = L"r:";
					 // 
					 // light_diffuse_r_edit
					 // 
					 this->light_diffuse_r_edit->Location = System::Drawing::Point(30, 18);
					 this->light_diffuse_r_edit->Name = L"light_diffuse_r_edit";
					 this->light_diffuse_r_edit->Size = System::Drawing::Size(33, 21);
					 this->light_diffuse_r_edit->TabIndex = 0;
					 this->light_diffuse_r_edit->Text = L"1.0";
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
					 // 环境光
					 // 
					 this->环境光->Controls->Add(this->label24);
					 this->环境光->Controls->Add(this->light_ambient_b_edit);
					 this->环境光->Controls->Add(this->label11);
					 this->环境光->Controls->Add(this->light_ambient_g_edit);
					 this->环境光->Controls->Add(this->label1);
					 this->环境光->Controls->Add(this->light_ambient_r_edit);
					 this->环境光->Location = System::Drawing::Point(19, 18);
					 this->环境光->Name = L"环境光";
					 this->环境光->Size = System::Drawing::Size(200, 50);
					 this->环境光->TabIndex = 0;
					 this->环境光->TabStop = false;
					 this->环境光->Text = L"环境光";
					 // 
					 // label24
					 // 
					 this->label24->AutoSize = true;
					 this->label24->Location = System::Drawing::Point(138, 21);
					 this->label24->Name = L"label24";
					 this->label24->Size = System::Drawing::Size(17, 12);
					 this->label24->TabIndex = 5;
					 this->label24->Text = L"b:";
					 // 
					 // light_ambient_b_edit
					 // 
					 this->light_ambient_b_edit->Location = System::Drawing::Point(161, 18);
					 this->light_ambient_b_edit->Name = L"light_ambient_b_edit";
					 this->light_ambient_b_edit->Size = System::Drawing::Size(31, 21);
					 this->light_ambient_b_edit->TabIndex = 4;
					 this->light_ambient_b_edit->Text = L"0.5";
					 // 
					 // label11
					 // 
					 this->label11->AutoSize = true;
					 this->label11->Location = System::Drawing::Point(72, 21);
					 this->label11->Name = L"label11";
					 this->label11->Size = System::Drawing::Size(17, 12);
					 this->label11->TabIndex = 3;
					 this->label11->Text = L"g:";
					 // 
					 // light_ambient_g_edit
					 // 
					 this->light_ambient_g_edit->Location = System::Drawing::Point(95, 18);
					 this->light_ambient_g_edit->Name = L"light_ambient_g_edit";
					 this->light_ambient_g_edit->Size = System::Drawing::Size(32, 21);
					 this->light_ambient_g_edit->TabIndex = 2;
					 this->light_ambient_g_edit->Text = L"0.5";
					 // 
					 // label1
					 // 
					 this->label1->AutoSize = true;
					 this->label1->Location = System::Drawing::Point(7, 21);
					 this->label1->Name = L"label1";
					 this->label1->Size = System::Drawing::Size(17, 12);
					 this->label1->TabIndex = 1;
					 this->label1->Text = L"r:";
					 // 
					 // light_ambient_r_edit
					 // 
					 this->light_ambient_r_edit->Location = System::Drawing::Point(30, 18);
					 this->light_ambient_r_edit->Name = L"light_ambient_r_edit";
					 this->light_ambient_r_edit->Size = System::Drawing::Size(32, 21);
					 this->light_ambient_r_edit->TabIndex = 0;
					 this->light_ambient_r_edit->Text = L"0.5";
					 // 
					 // config_video_page
					 // 
					 this->config_video_page->Controls->Add(this->groupBox16);
					 this->config_video_page->Controls->Add(this->groupBox15);
					 this->config_video_page->Controls->Add(this->groupBox14);
					 this->config_video_page->Controls->Add(this->groupBox13);
					 this->config_video_page->Controls->Add(this->groupBox12);
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
					 // groupBox16
					 // 
					 this->groupBox16->Controls->Add(this->label36);
					 this->groupBox16->Controls->Add(this->sbs_specular_txt);
					 this->groupBox16->Controls->Add(this->label35);
					 this->groupBox16->Controls->Add(this->sbs_bias_txt);
					 this->groupBox16->Controls->Add(this->label34);
					 this->groupBox16->Controls->Add(this->sbs_scale_txt);
					 this->groupBox16->Location = System::Drawing::Point(17, 514);
					 this->groupBox16->Name = L"groupBox16";
					 this->groupBox16->Size = System::Drawing::Size(200, 75);
					 this->groupBox16->TabIndex = 13;
					 this->groupBox16->TabStop = false;
					 this->groupBox16->Text = L"BiasSpecular";
					 // 
					 // label36
					 // 
					 this->label36->AutoSize = true;
					 this->label36->Location = System::Drawing::Point(15, 49);
					 this->label36->Name = L"label36";
					 this->label36->Size = System::Drawing::Size(59, 12);
					 this->label36->TabIndex = 6;
					 this->label36->Text = L"Specular:";
					 // 
					 // sbs_specular_txt
					 // 
					 this->sbs_specular_txt->Location = System::Drawing::Point(76, 46);
					 this->sbs_specular_txt->Name = L"sbs_specular_txt";
					 this->sbs_specular_txt->Size = System::Drawing::Size(51, 21);
					 this->sbs_specular_txt->TabIndex = 5;
					 this->sbs_specular_txt->Text = L"32";
					 // 
					 // label35
					 // 
					 this->label35->AutoSize = true;
					 this->label35->Location = System::Drawing::Point(112, 20);
					 this->label35->Name = L"label35";
					 this->label35->Size = System::Drawing::Size(35, 12);
					 this->label35->TabIndex = 4;
					 this->label35->Text = L"Bias:";
					 // 
					 // sbs_bias_txt
					 // 
					 this->sbs_bias_txt->Location = System::Drawing::Point(148, 16);
					 this->sbs_bias_txt->Name = L"sbs_bias_txt";
					 this->sbs_bias_txt->Size = System::Drawing::Size(46, 21);
					 this->sbs_bias_txt->TabIndex = 3;
					 this->sbs_bias_txt->Text = L"-0.04";
					 // 
					 // label34
					 // 
					 this->label34->AutoSize = true;
					 this->label34->Location = System::Drawing::Point(15, 21);
					 this->label34->Name = L"label34";
					 this->label34->Size = System::Drawing::Size(41, 12);
					 this->label34->TabIndex = 2;
					 this->label34->Text = L"Scale:";
					 // 
					 // sbs_scale_txt
					 // 
					 this->sbs_scale_txt->Location = System::Drawing::Point(57, 16);
					 this->sbs_scale_txt->Name = L"sbs_scale_txt";
					 this->sbs_scale_txt->Size = System::Drawing::Size(41, 21);
					 this->sbs_scale_txt->TabIndex = 1;
					 this->sbs_scale_txt->Text = L"0.03";
					 // 
					 // groupBox15
					 // 
					 this->groupBox15->Controls->Add(this->label31);
					 this->groupBox15->Controls->Add(this->fsaa_txt);
					 this->groupBox15->Location = System::Drawing::Point(17, 466);
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
					 this->groupBox14->Location = System::Drawing::Point(17, 422);
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
					 // groupBox13
					 // 
					 this->groupBox13->Controls->Add(this->rb_fog_exp);
					 this->groupBox13->Controls->Add(this->rb_fog_line);
					 this->groupBox13->Controls->Add(this->rb_fog_none);
					 this->groupBox13->Location = System::Drawing::Point(17, 305);
					 this->groupBox13->Name = L"groupBox13";
					 this->groupBox13->Size = System::Drawing::Size(200, 69);
					 this->groupBox13->TabIndex = 10;
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
					 // groupBox12
					 // 
					 this->groupBox12->Controls->Add(this->rb_shadow_high);
					 this->groupBox12->Controls->Add(this->rb_shadow_medium);
					 this->groupBox12->Controls->Add(this->rb_shadow_low);
					 this->groupBox12->Controls->Add(this->rb_shadow_none);
					 this->groupBox12->Location = System::Drawing::Point(17, 226);
					 this->groupBox12->Name = L"groupBox12";
					 this->groupBox12->Size = System::Drawing::Size(200, 70);
					 this->groupBox12->TabIndex = 9;
					 this->groupBox12->TabStop = false;
					 this->groupBox12->Text = L"阴影质量";
					 // 
					 // rb_shadow_high
					 // 
					 this->rb_shadow_high->AutoSize = true;
					 this->rb_shadow_high->Location = System::Drawing::Point(101, 48);
					 this->rb_shadow_high->Name = L"rb_shadow_high";
					 this->rb_shadow_high->Size = System::Drawing::Size(47, 16);
					 this->rb_shadow_high->TabIndex = 3;
					 this->rb_shadow_high->Text = L"高级";
					 this->rb_shadow_high->UseVisualStyleBackColor = true;
					 // 
					 // rb_shadow_medium
					 // 
					 this->rb_shadow_medium->AutoSize = true;
					 this->rb_shadow_medium->Location = System::Drawing::Point(15, 48);
					 this->rb_shadow_medium->Name = L"rb_shadow_medium";
					 this->rb_shadow_medium->Size = System::Drawing::Size(47, 16);
					 this->rb_shadow_medium->TabIndex = 2;
					 this->rb_shadow_medium->Text = L"中等";
					 this->rb_shadow_medium->UseVisualStyleBackColor = true;
					 // 
					 // rb_shadow_low
					 // 
					 this->rb_shadow_low->AutoSize = true;
					 this->rb_shadow_low->Location = System::Drawing::Point(101, 21);
					 this->rb_shadow_low->Name = L"rb_shadow_low";
					 this->rb_shadow_low->Size = System::Drawing::Size(35, 16);
					 this->rb_shadow_low->TabIndex = 1;
					 this->rb_shadow_low->Text = L"低";
					 this->rb_shadow_low->UseVisualStyleBackColor = true;
					 // 
					 // rb_shadow_none
					 // 
					 this->rb_shadow_none->AutoSize = true;
					 this->rb_shadow_none->Checked = true;
					 this->rb_shadow_none->Location = System::Drawing::Point(15, 21);
					 this->rb_shadow_none->Name = L"rb_shadow_none";
					 this->rb_shadow_none->Size = System::Drawing::Size(59, 16);
					 this->rb_shadow_none->TabIndex = 0;
					 this->rb_shadow_none->TabStop = true;
					 this->rb_shadow_none->Text = L"无阴影";
					 this->rb_shadow_none->UseVisualStyleBackColor = true;
					 // 
					 // groupBox11
					 // 
					 this->groupBox11->Controls->Add(this->label18);
					 this->groupBox11->Controls->Add(this->txt_mipmap_bias);
					 this->groupBox11->Location = System::Drawing::Point(17, 178);
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
					 this->txt_mipmap_bias->Text = L"-2";
					 // 
					 // groupBox10
					 // 
					 this->groupBox10->Controls->Add(this->rb_tex_filter_anisotropic);
					 this->groupBox10->Controls->Add(this->rb_tex_filter_3line);
					 this->groupBox10->Controls->Add(this->rb_tex_filter_bline);
					 this->groupBox10->Controls->Add(this->rb_tex_filter_none);
					 this->groupBox10->Location = System::Drawing::Point(17, 99);
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
					 this->groupBox9->Controls->Add(this->model_renderhigh_check);
					 this->groupBox9->Location = System::Drawing::Point(17, 379);
					 this->groupBox9->Name = L"groupBox9";
					 this->groupBox9->Size = System::Drawing::Size(200, 42);
					 this->groupBox9->TabIndex = 5;
					 this->groupBox9->TabStop = false;
					 this->groupBox9->Text = L"模型";
					 // 
					 // model_renderhigh_check
					 // 
					 this->model_renderhigh_check->AutoSize = true;
					 this->model_renderhigh_check->Location = System::Drawing::Point(31, 20);
					 this->model_renderhigh_check->Name = L"model_renderhigh_check";
					 this->model_renderhigh_check->Size = System::Drawing::Size(96, 16);
					 this->model_renderhigh_check->TabIndex = 0;
					 this->model_renderhigh_check->Text = L"高级显示效果";
					 this->model_renderhigh_check->UseVisualStyleBackColor = true;
					 // 
					 // groupBox8
					 // 
					 this->groupBox8->Controls->Add(this->terrain_color_check);
					 this->groupBox8->Controls->Add(this->terrain_shadow_check);
					 this->groupBox8->Controls->Add(this->terrain_offset_check);
					 this->groupBox8->Controls->Add(this->terrain_spec_check);
					 this->groupBox8->Controls->Add(this->terrain_normal_check);
					 this->groupBox8->Location = System::Drawing::Point(17, 7);
					 this->groupBox8->Name = L"groupBox8";
					 this->groupBox8->Size = System::Drawing::Size(200, 86);
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
					 // terrain_shadow_check
					 // 
					 this->terrain_shadow_check->AutoSize = true;
					 this->terrain_shadow_check->Location = System::Drawing::Point(76, 64);
					 this->terrain_shadow_check->Name = L"terrain_shadow_check";
					 this->terrain_shadow_check->Size = System::Drawing::Size(72, 16);
					 this->terrain_shadow_check->TabIndex = 3;
					 this->terrain_shadow_check->Text = L"阴影贴图";
					 this->terrain_shadow_check->UseVisualStyleBackColor = true;
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
					 // tabPage1
					 // 
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
					 // terrain_texture_pic_list
					 // 
					 this->terrain_texture_pic_list->ColorDepth = System::Windows::Forms::ColorDepth::Depth32Bit;
					 this->terrain_texture_pic_list->ImageSize = System::Drawing::Size(30, 30);
					 this->terrain_texture_pic_list->TransparentColor = System::Drawing::Color::Transparent;
					 // 
					 // imageList1
					 // 
					 this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList1.ImageStream")));
					 this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
					 this->imageList1->Images->SetKeyName(0, L"笔刷-圆.png");
					 this->imageList1->Images->SetKeyName(1, L"笔刷-方.png");
					 this->imageList1->Images->SetKeyName(2, L"笔刷-菱.png");
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
					 // panel1
					 // 
					 this->panel1->Controls->Add(this->treeView1);
					 this->panel1->Controls->Add(this->panel2);
					 this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
					 this->panel1->Location = System::Drawing::Point(3, 38);
					 this->panel1->Name = L"panel1";
					 this->panel1->Size = System::Drawing::Size(212, 578);
					 this->panel1->TabIndex = 1;
					 // 
					 // treeView1
					 // 
					 this->treeView1->AllowDrop = true;
					 this->treeView1->Dock = System::Windows::Forms::DockStyle::Fill;
					 this->treeView1->LineColor = System::Drawing::Color::Empty;
					 this->treeView1->Location = System::Drawing::Point(0, 0);
					 this->treeView1->Name = L"treeView1";
					 this->treeView1->Size = System::Drawing::Size(212, 452);
					 this->treeView1->TabIndex = 2;
					 // 
					 // panel2
					 // 
					 this->panel2->Controls->Add(this->numericUpDown1);
					 this->panel2->Controls->Add(this->checkBox1);
					 this->panel2->Controls->Add(this->label3);
					 this->panel2->Controls->Add(this->label4);
					 this->panel2->Controls->Add(this->button11);
					 this->panel2->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel2->Location = System::Drawing::Point(0, 452);
					 this->panel2->Name = L"panel2";
					 this->panel2->Size = System::Drawing::Size(212, 126);
					 this->panel2->TabIndex = 1;
					 // 
					 // numericUpDown1
					 // 
					 this->numericUpDown1->Location = System::Drawing::Point(174, 97);
					 this->numericUpDown1->Name = L"numericUpDown1";
					 this->numericUpDown1->Size = System::Drawing::Size(30, 21);
					 this->numericUpDown1->TabIndex = 5;
					 this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {7, 0, 0, 0});
					 // 
					 // checkBox1
					 // 
					 this->checkBox1->AutoSize = true;
					 this->checkBox1->Location = System::Drawing::Point(14, 101);
					 this->checkBox1->Name = L"checkBox1";
					 this->checkBox1->Size = System::Drawing::Size(162, 16);
					 this->checkBox1->TabIndex = 4;
					 this->checkBox1->Text = L"测试批量创建 | 一边数量";
					 this->checkBox1->UseVisualStyleBackColor = true;
					 // 
					 // label3
					 // 
					 this->label3->AutoEllipsis = true;
					 this->label3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->label3->Location = System::Drawing::Point(11, 33);
					 this->label3->Name = L"label3";
					 this->label3->Size = System::Drawing::Size(193, 57);
					 this->label3->TabIndex = 3;
					 this->label3->Text = L"XXXX";
					 // 
					 // label4
					 // 
					 this->label4->AutoSize = true;
					 this->label4->Location = System::Drawing::Point(9, 9);
					 this->label4->Name = L"label4";
					 this->label4->Size = System::Drawing::Size(83, 12);
					 this->label4->TabIndex = 2;
					 this->label4->Text = L"当前准备模型:";
					 // 
					 // button11
					 // 
					 this->button11->Location = System::Drawing::Point(167, 4);
					 this->button11->Name = L"button11";
					 this->button11->Size = System::Drawing::Size(37, 23);
					 this->button11->TabIndex = 1;
					 this->button11->Text = L"取消";
					 this->button11->UseVisualStyleBackColor = true;
					 // 
					 // panel3
					 // 
					 this->panel3->Controls->Add(this->button12);
					 this->panel3->Controls->Add(this->textBox2);
					 this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel3->Location = System::Drawing::Point(3, 3);
					 this->panel3->Name = L"panel3";
					 this->panel3->Size = System::Drawing::Size(212, 35);
					 this->panel3->TabIndex = 0;
					 // 
					 // button12
					 // 
					 this->button12->Location = System::Drawing::Point(167, 6);
					 this->button12->Name = L"button12";
					 this->button12->Size = System::Drawing::Size(44, 23);
					 this->button12->TabIndex = 2;
					 this->button12->Text = L"查询";
					 this->button12->UseVisualStyleBackColor = true;
					 // 
					 // textBox2
					 // 
					 this->textBox2->Location = System::Drawing::Point(11, 7);
					 this->textBox2->Name = L"textBox2";
					 this->textBox2->Size = System::Drawing::Size(150, 21);
					 this->textBox2->TabIndex = 1;
					 // 
					 // panel24
					 // 
					 this->panel24->Controls->Add(this->numericUpDown7);
					 this->panel24->Controls->Add(this->checkBox7);
					 this->panel24->Controls->Add(this->label5);
					 this->panel24->Controls->Add(this->label12);
					 this->panel24->Controls->Add(this->button23);
					 this->panel24->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel24->Location = System::Drawing::Point(3, 490);
					 this->panel24->Name = L"panel24";
					 this->panel24->Size = System::Drawing::Size(212, 126);
					 this->panel24->TabIndex = 9;
					 // 
					 // numericUpDown7
					 // 
					 this->numericUpDown7->Location = System::Drawing::Point(174, 97);
					 this->numericUpDown7->Name = L"numericUpDown7";
					 this->numericUpDown7->Size = System::Drawing::Size(30, 21);
					 this->numericUpDown7->TabIndex = 5;
					 this->numericUpDown7->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {7, 0, 0, 0});
					 // 
					 // checkBox7
					 // 
					 this->checkBox7->AutoSize = true;
					 this->checkBox7->Location = System::Drawing::Point(14, 101);
					 this->checkBox7->Name = L"checkBox7";
					 this->checkBox7->Size = System::Drawing::Size(162, 16);
					 this->checkBox7->TabIndex = 4;
					 this->checkBox7->Text = L"测试批量创建 | 一边数量";
					 this->checkBox7->UseVisualStyleBackColor = true;
					 // 
					 // label5
					 // 
					 this->label5->AutoEllipsis = true;
					 this->label5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->label5->Location = System::Drawing::Point(11, 33);
					 this->label5->Name = L"label5";
					 this->label5->Size = System::Drawing::Size(193, 57);
					 this->label5->TabIndex = 3;
					 // 
					 // label12
					 // 
					 this->label12->AutoSize = true;
					 this->label12->Location = System::Drawing::Point(9, 9);
					 this->label12->Name = L"label12";
					 this->label12->Size = System::Drawing::Size(83, 12);
					 this->label12->TabIndex = 2;
					 this->label12->Text = L"当前准备模型:";
					 // 
					 // button23
					 // 
					 this->button23->Location = System::Drawing::Point(167, 4);
					 this->button23->Name = L"button23";
					 this->button23->Size = System::Drawing::Size(37, 23);
					 this->button23->TabIndex = 1;
					 this->button23->Text = L"取消";
					 this->button23->UseVisualStyleBackColor = true;
					 // 
					 // treeView2
					 // 
					 this->treeView2->AllowDrop = true;
					 this->treeView2->Dock = System::Windows::Forms::DockStyle::Top;
					 this->treeView2->LineColor = System::Drawing::Color::Empty;
					 this->treeView2->Location = System::Drawing::Point(3, 38);
					 this->treeView2->Name = L"treeView2";
					 this->treeView2->Size = System::Drawing::Size(212, 450);
					 this->treeView2->TabIndex = 8;
					 // 
					 // panel25
					 // 
					 this->panel25->Controls->Add(this->button24);
					 this->panel25->Controls->Add(this->textBox9);
					 this->panel25->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel25->Location = System::Drawing::Point(3, 3);
					 this->panel25->Name = L"panel25";
					 this->panel25->Size = System::Drawing::Size(212, 35);
					 this->panel25->TabIndex = 7;
					 // 
					 // button24
					 // 
					 this->button24->Location = System::Drawing::Point(167, 6);
					 this->button24->Name = L"button24";
					 this->button24->Size = System::Drawing::Size(44, 23);
					 this->button24->TabIndex = 2;
					 this->button24->Text = L"查询";
					 this->button24->UseVisualStyleBackColor = true;
					 // 
					 // textBox9
					 // 
					 this->textBox9->Location = System::Drawing::Point(11, 7);
					 this->textBox9->Name = L"textBox9";
					 this->textBox9->Size = System::Drawing::Size(150, 21);
					 this->textBox9->TabIndex = 1;
					 // 
					 // panel28
					 // 
					 this->panel28->Controls->Add(this->label15);
					 this->panel28->Controls->Add(this->label32);
					 this->panel28->Controls->Add(this->button27);
					 this->panel28->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel28->Location = System::Drawing::Point(3, 517);
					 this->panel28->Name = L"panel28";
					 this->panel28->Size = System::Drawing::Size(212, 99);
					 this->panel28->TabIndex = 12;
					 // 
					 // label15
					 // 
					 this->label15->AutoEllipsis = true;
					 this->label15->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->label15->Location = System::Drawing::Point(11, 33);
					 this->label15->Name = L"label15";
					 this->label15->Size = System::Drawing::Size(193, 57);
					 this->label15->TabIndex = 3;
					 // 
					 // label32
					 // 
					 this->label32->AutoSize = true;
					 this->label32->Location = System::Drawing::Point(9, 9);
					 this->label32->Name = L"label32";
					 this->label32->Size = System::Drawing::Size(83, 12);
					 this->label32->TabIndex = 2;
					 this->label32->Text = L"当前准备模型:";
					 // 
					 // button27
					 // 
					 this->button27->Location = System::Drawing::Point(167, 4);
					 this->button27->Name = L"button27";
					 this->button27->Size = System::Drawing::Size(37, 23);
					 this->button27->TabIndex = 1;
					 this->button27->Text = L"取消";
					 this->button27->UseVisualStyleBackColor = true;
					 // 
					 // treeView3
					 // 
					 this->treeView3->AllowDrop = true;
					 this->treeView3->Dock = System::Windows::Forms::DockStyle::Top;
					 this->treeView3->LineColor = System::Drawing::Color::Empty;
					 this->treeView3->Location = System::Drawing::Point(3, 38);
					 this->treeView3->Name = L"treeView3";
					 this->treeView3->Size = System::Drawing::Size(212, 477);
					 this->treeView3->TabIndex = 11;
					 // 
					 // panel29
					 // 
					 this->panel29->Controls->Add(this->button28);
					 this->panel29->Controls->Add(this->textBox11);
					 this->panel29->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel29->Location = System::Drawing::Point(3, 3);
					 this->panel29->Name = L"panel29";
					 this->panel29->Size = System::Drawing::Size(212, 35);
					 this->panel29->TabIndex = 10;
					 // 
					 // button28
					 // 
					 this->button28->Location = System::Drawing::Point(167, 6);
					 this->button28->Name = L"button28";
					 this->button28->Size = System::Drawing::Size(44, 23);
					 this->button28->TabIndex = 2;
					 this->button28->Text = L"查询";
					 this->button28->UseVisualStyleBackColor = true;
					 // 
					 // textBox11
					 // 
					 this->textBox11->Location = System::Drawing::Point(11, 7);
					 this->textBox11->Name = L"textBox11";
					 this->textBox11->Size = System::Drawing::Size(150, 21);
					 this->textBox11->TabIndex = 1;
					 // 
					 // panel34
					 // 
					 this->panel34->Controls->Add(this->label37);
					 this->panel34->Controls->Add(this->label39);
					 this->panel34->Controls->Add(this->button33);
					 this->panel34->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel34->Location = System::Drawing::Point(3, 517);
					 this->panel34->Name = L"panel34";
					 this->panel34->Size = System::Drawing::Size(212, 99);
					 this->panel34->TabIndex = 12;
					 // 
					 // label37
					 // 
					 this->label37->AutoEllipsis = true;
					 this->label37->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->label37->Location = System::Drawing::Point(11, 33);
					 this->label37->Name = L"label37";
					 this->label37->Size = System::Drawing::Size(193, 57);
					 this->label37->TabIndex = 3;
					 // 
					 // label39
					 // 
					 this->label39->AutoSize = true;
					 this->label39->Location = System::Drawing::Point(9, 9);
					 this->label39->Name = L"label39";
					 this->label39->Size = System::Drawing::Size(83, 12);
					 this->label39->TabIndex = 2;
					 this->label39->Text = L"当前准备模型:";
					 // 
					 // button33
					 // 
					 this->button33->Location = System::Drawing::Point(167, 4);
					 this->button33->Name = L"button33";
					 this->button33->Size = System::Drawing::Size(37, 23);
					 this->button33->TabIndex = 1;
					 this->button33->Text = L"取消";
					 this->button33->UseVisualStyleBackColor = true;
					 // 
					 // treeView4
					 // 
					 this->treeView4->AllowDrop = true;
					 this->treeView4->Dock = System::Windows::Forms::DockStyle::Top;
					 this->treeView4->LineColor = System::Drawing::Color::Empty;
					 this->treeView4->Location = System::Drawing::Point(3, 38);
					 this->treeView4->Name = L"treeView4";
					 this->treeView4->Size = System::Drawing::Size(212, 477);
					 this->treeView4->TabIndex = 11;
					 // 
					 // panel35
					 // 
					 this->panel35->Controls->Add(this->button34);
					 this->panel35->Controls->Add(this->textBox14);
					 this->panel35->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel35->Location = System::Drawing::Point(3, 3);
					 this->panel35->Name = L"panel35";
					 this->panel35->Size = System::Drawing::Size(212, 35);
					 this->panel35->TabIndex = 10;
					 // 
					 // button34
					 // 
					 this->button34->Location = System::Drawing::Point(167, 6);
					 this->button34->Name = L"button34";
					 this->button34->Size = System::Drawing::Size(44, 23);
					 this->button34->TabIndex = 2;
					 this->button34->Text = L"查询";
					 this->button34->UseVisualStyleBackColor = true;
					 // 
					 // textBox14
					 // 
					 this->textBox14->Location = System::Drawing::Point(11, 7);
					 this->textBox14->Name = L"textBox14";
					 this->textBox14->Size = System::Drawing::Size(150, 21);
					 this->textBox14->TabIndex = 1;
					 // 
					 // panel32
					 // 
					 this->panel32->Controls->Add(this->label38);
					 this->panel32->Controls->Add(this->label40);
					 this->panel32->Controls->Add(this->button31);
					 this->panel32->Dock = System::Windows::Forms::DockStyle::Bottom;
					 this->panel32->Location = System::Drawing::Point(3, 515);
					 this->panel32->Name = L"panel32";
					 this->panel32->Size = System::Drawing::Size(212, 101);
					 this->panel32->TabIndex = 5;
					 // 
					 // label38
					 // 
					 this->label38->AutoEllipsis = true;
					 this->label38->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
					 this->label38->Location = System::Drawing::Point(11, 33);
					 this->label38->Name = L"label38";
					 this->label38->Size = System::Drawing::Size(193, 57);
					 this->label38->TabIndex = 3;
					 // 
					 // label40
					 // 
					 this->label40->AutoSize = true;
					 this->label40->Location = System::Drawing::Point(9, 9);
					 this->label40->Name = L"label40";
					 this->label40->Size = System::Drawing::Size(83, 12);
					 this->label40->TabIndex = 2;
					 this->label40->Text = L"当前准备模型:";
					 // 
					 // button31
					 // 
					 this->button31->Location = System::Drawing::Point(167, 4);
					 this->button31->Name = L"button31";
					 this->button31->Size = System::Drawing::Size(37, 23);
					 this->button31->TabIndex = 1;
					 this->button31->Text = L"取消";
					 this->button31->UseVisualStyleBackColor = true;
					 // 
					 // treeView5
					 // 
					 this->treeView5->AllowDrop = true;
					 this->treeView5->Dock = System::Windows::Forms::DockStyle::Top;
					 this->treeView5->LineColor = System::Drawing::Color::Empty;
					 this->treeView5->Location = System::Drawing::Point(3, 38);
					 this->treeView5->Name = L"treeView5";
					 this->treeView5->Size = System::Drawing::Size(212, 475);
					 this->treeView5->TabIndex = 4;
					 // 
					 // panel33
					 // 
					 this->panel33->Controls->Add(this->button32);
					 this->panel33->Controls->Add(this->textBox13);
					 this->panel33->Dock = System::Windows::Forms::DockStyle::Top;
					 this->panel33->Location = System::Drawing::Point(3, 3);
					 this->panel33->Name = L"panel33";
					 this->panel33->Size = System::Drawing::Size(212, 35);
					 this->panel33->TabIndex = 2;
					 // 
					 // button32
					 // 
					 this->button32->Location = System::Drawing::Point(167, 6);
					 this->button32->Name = L"button32";
					 this->button32->Size = System::Drawing::Size(44, 23);
					 this->button32->TabIndex = 2;
					 this->button32->Text = L"查询";
					 this->button32->UseVisualStyleBackColor = true;
					 // 
					 // textBox13
					 // 
					 this->textBox13->Location = System::Drawing::Point(11, 7);
					 this->textBox13->Name = L"textBox13";
					 this->textBox13->Size = System::Drawing::Size(150, 21);
					 this->textBox13->TabIndex = 1;
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
					 this->Text = L"GameMapEditor";
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
					 this->element_create_page->ResumeLayout(false);
					 this->SelectCreateElementTypeTab->ResumeLayout(false);
					 this->create_static_page->ResumeLayout(false);
					 this->panel26->ResumeLayout(false);
					 this->panel26->PerformLayout();
					 this->panel27->ResumeLayout(false);
					 this->panel27->PerformLayout();
					 this->create_troop_page->ResumeLayout(false);
					 this->panel23->ResumeLayout(false);
					 this->panel23->PerformLayout();
					 this->panel22->ResumeLayout(false);
					 this->panel22->PerformLayout();
					 this->create_building_page->ResumeLayout(false);
					 this->panel30->ResumeLayout(false);
					 this->panel30->PerformLayout();
					 this->panel31->ResumeLayout(false);
					 this->panel31->PerformLayout();
					 this->create_monster_page->ResumeLayout(false);
					 this->panel21->ResumeLayout(false);
					 this->panel21->PerformLayout();
					 this->panel6->ResumeLayout(false);
					 this->panel6->PerformLayout();
					 this->create_npc_page->ResumeLayout(false);
					 this->panel20->ResumeLayout(false);
					 this->panel20->PerformLayout();
					 this->panel5->ResumeLayout(false);
					 this->panel5->PerformLayout();
					 this->create_object_page->ResumeLayout(false);
					 this->panel11->ResumeLayout(false);
					 this->panel14->ResumeLayout(false);
					 this->panel14->PerformLayout();
					 this->panel10->ResumeLayout(false);
					 this->panel10->PerformLayout();
					 this->create_place_page->ResumeLayout(false);
					 this->panel18->ResumeLayout(false);
					 this->panel18->PerformLayout();
					 this->panel4->ResumeLayout(false);
					 this->panel4->PerformLayout();
					 this->create_point_page->ResumeLayout(false);
					 this->panel19->ResumeLayout(false);
					 this->panel19->PerformLayout();
					 this->panel17->ResumeLayout(false);
					 this->panel17->PerformLayout();
					 this->create_effect_page->ResumeLayout(false);
					 this->panel36->ResumeLayout(false);
					 this->panel36->PerformLayout();
					 this->panel37->ResumeLayout(false);
					 this->panel37->PerformLayout();
					 this->element_prop_page->ResumeLayout(false);
					 this->panel13->ResumeLayout(false);
					 this->element_statistics_page->ResumeLayout(false);
					 this->panel15->ResumeLayout(false);
					 this->panel16->ResumeLayout(false);
					 this->panel16->PerformLayout();
					 this->setting_page->ResumeLayout(false);
					 this->panel7->ResumeLayout(false);
					 this->ConfigTab->ResumeLayout(false);
					 this->Config_env_light_page->ResumeLayout(false);
					 this->groupBox6->ResumeLayout(false);
					 this->groupBox5->ResumeLayout(false);
					 this->groupBox5->PerformLayout();
					 this->groupBox4->ResumeLayout(false);
					 this->groupBox4->PerformLayout();
					 this->环境光->ResumeLayout(false);
					 this->环境光->PerformLayout();
					 this->config_video_page->ResumeLayout(false);
					 this->groupBox16->ResumeLayout(false);
					 this->groupBox16->PerformLayout();
					 this->groupBox15->ResumeLayout(false);
					 this->groupBox15->PerformLayout();
					 this->groupBox14->ResumeLayout(false);
					 this->groupBox14->PerformLayout();
					 this->groupBox13->ResumeLayout(false);
					 this->groupBox13->PerformLayout();
					 this->groupBox12->ResumeLayout(false);
					 this->groupBox12->PerformLayout();
					 this->groupBox11->ResumeLayout(false);
					 this->groupBox11->PerformLayout();
					 this->groupBox10->ResumeLayout(false);
					 this->groupBox10->PerformLayout();
					 this->groupBox9->ResumeLayout(false);
					 this->groupBox9->PerformLayout();
					 this->groupBox8->ResumeLayout(false);
					 this->groupBox8->PerformLayout();
					 this->tabPage1->ResumeLayout(false);
					 this->groupBox18->ResumeLayout(false);
					 this->groupBox18->PerformLayout();
					 this->groupBox17->ResumeLayout(false);
					 this->groupBox17->PerformLayout();
					 this->groupBox7->ResumeLayout(false);
					 this->groupBox7->PerformLayout();
					 this->tabPage7->ResumeLayout(false);
					 this->tabPage7->PerformLayout();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->EndInit();
					 this->panel1->ResumeLayout(false);
					 this->panel2->ResumeLayout(false);
					 this->panel2->PerformLayout();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
					 this->panel3->ResumeLayout(false);
					 this->panel3->PerformLayout();
					 this->panel24->ResumeLayout(false);
					 this->panel24->PerformLayout();
					 (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown7))->EndInit();
					 this->panel25->ResumeLayout(false);
					 this->panel25->PerformLayout();
					 this->panel28->ResumeLayout(false);
					 this->panel28->PerformLayout();
					 this->panel29->ResumeLayout(false);
					 this->panel29->PerformLayout();
					 this->panel34->ResumeLayout(false);
					 this->panel34->PerformLayout();
					 this->panel35->ResumeLayout(false);
					 this->panel35->PerformLayout();
					 this->panel32->ResumeLayout(false);
					 this->panel32->PerformLayout();
					 this->panel33->ResumeLayout(false);
					 this->panel33->PerformLayout();
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
				 this->onEventOpenLoadMapForm();
			 }
	private: System::Void 保存ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->saveScene();
			 }
	private: System::Void 保存为ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->saveAsScene();
			 }
	private: System::Void 新建ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->createScene();
			 }
	private: System::Void element_prop_grids_PropertyValueChanged(System::Object^  s, System::Windows::Forms::PropertyValueChangedEventArgs^  e) {
				 this->applySceneElementPropsChange();
			 }
	private: System::Void element_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 this->selectSceneElementFromList();
			 }
	private: System::Void UtilType_Ctrl_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 this->selectCtrlType();
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->stickSelectElementToTerrain();
			 }
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {

			 }
	private: System::Void button4_Click_1(System::Object^  sender, System::EventArgs^  e) {
				 this->destroySceneElementFromList();
			 }
	//private: System::Void 打开游戏地图编辑器ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	//			 this->openGameDataEditor();
	//		 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	//private: System::Void element_create_npc_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	//			 this->prepareCreateEntity();
	//		 }
	//private: System::Void element_create_place_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	//			 this->prepareCreateEntity();
	private: System::Void create_object_entity_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 //this->prepareCreateObjectEntity();
			}
	private: System::Void create_place_entity_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 //this->prepareCreatePlaceEntity();
			}
	private: System::Void create_point_entity_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 //this->prepareCreatePointEntity();
			}
	private: System::Void create_npc_entity_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 //this->prepareCreateNpcEntity();
			}
	private: System::Void create_monster_entity_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 //this->prepareCreateMonsterEntity();
			}
	private: System::Void create_troop_entity_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 //this->prepareCreateTroopEntity();
			}
	private: System::Void create_static_entity_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 //this->prepareCreateStaticObjectEntity();
			 }
	private: System::Void create_building_entity_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 //this->prepareCreateBuildingEntity();
			 }
	private: System::Void create_region_entity_tree_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 this->prepareCreateRegionEntity();
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
	private: System::Void scene_panel_MouseEnter(System::Object^  sender, System::EventArgs^  e) {
				 this->showCursorElement();
			 }
	private: System::Void scene_panel_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
				 this->hideCursorElement();
			 }
	private: System::Void scene_panel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 }
	private: System::Void scene_panel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 }
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->loadSceneElementList();
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
	private: System::Void terrainBatchEntityTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 this->switchGameEditorOp();
			 }
	private: System::Void terrainBlockTab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 this->switchGameEditorOp();
			 }
private: System::Void terrain_brush_size_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_brush_speed_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_brush_shape_tab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_style_tab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_stytle_gun_decay_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_region_visible_ckb_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void TerrainAddRegionSelfBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void TerrainRegionSelfList_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 }
private: System::Void btn_show_block_refresh_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_foliage_noise_variable_valueChange(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_foliage_noise_rate_valueChange(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void listView_terrain_batch_entity_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 }
private: System::Void terrain_tex_blur_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_tex_mop_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_tex_remove_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_tex_add_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_texture_pic_tab_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void trackBar4_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_height_noise_range_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void terrain_height_level_range_tb_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void static_object_model_create_tree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 this->prepareCreateStaticObjectEntity();
		 }
private: System::Void troop_model_create_tree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 this->prepareCreateTroopEntity();
		 }
private: System::Void building_model_create_tree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 this->prepareCreateBuildingEntity();
		 }
private: System::Void monster_model_create_tree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 this->prepareCreateMonsterEntity();
		 }
private: System::Void NPC_model_create_tree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 this->prepareCreateNpcEntity();
		 }
private: System::Void object_model_create_tree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 this->prepareCreateObjectEntity();
		 }
private: System::Void place_model_create_tree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 this->prepareCreatePlaceEntity();
		 }
private: System::Void point_model_create_tree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 this->prepareCreatePointEntity();
		 }
private: System::Void effect_create_tree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 this->prepareCreateEffect();
		 }
};
}
