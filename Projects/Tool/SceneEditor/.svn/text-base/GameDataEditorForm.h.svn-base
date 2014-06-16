#pragma once

#include "CommonGameDefine.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace SceneEditor {

	/// <summary>
	/// Summary for GameDataEditorForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class GameDataEditorForm : public System::Windows::Forms::Form
	{
	public:
		GameDataEditorForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GameDataEditorForm()
		{
			if (components)
			{
				delete components;
			}
		}
    public:

        ///初始化
        void initialize();
        ///反初始化
        void unInitialize();
        ///关闭
        void closeForm();

        ///加载
        void load();
        ///清空所有数据和控件内容
        void clearAll();
        ///刷新
        void refresh();
        
        //@{ 美术资源操作       
            ///加载美术资源表    
            void loadArtResList();        
            
            
        //@}


        //@{ 地图界面操作

            ///加载地图对象表   
            void loadMapObjectList();

			void loadDistObjList();

			void searchDistObjList();

            ///查询地图对象表   
            void searchMapObjectList(); 

            ///选择一个地图对象   
            void selMapObjectFromList(); 

            ///保存地图对象表   
            void saveSelMapObject();  

            ///清空地图对象界面数据
            void clearMapUI();   
            
        //@}

        //@{ 地点界面操作

            ///加载地图对象表   
            void loadPlaceObjectList();   

            ///查询地图对象表   
            void searchPlaceObjectList(); 

            ///选择一个地点对象   
            void selPlaceObjectFromList(); 

            ///保存地图对象表   
            void saveSelPlaceObject();  

            ///打开地点所属地图场景   
            void loadPlaceScene();  

            ///清空地点对象界面数据
            void clearPlaceUI();   

        //@}

        //@{ 区域界面操作


            
        //@}

        //@{ 建筑界面操作



        //@}

	private:
		IdType	m_SelCityArtID; 
		/// <summary>
		/// Required designer variable.
		/// </summary>
    private: System::Windows::Forms::MenuStrip^  menuStrip2;
    private: System::Windows::Forms::ToolStripMenuItem^  文件ToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  保存ToolStripMenuItem1;
    private: System::Windows::Forms::ToolStripMenuItem^  帮助ToolStripMenuItem1;
    private: System::Windows::Forms::Panel^  panel1;
    private: System::Windows::Forms::Panel^  panel2;
    private: System::Windows::Forms::TabControl^  tabControl1;
    private: System::Windows::Forms::TabPage^  tabPage3;
    private: System::Windows::Forms::Panel^  panel3;
    private: System::Windows::Forms::TabControl^  tabControl6;
    private: System::Windows::Forms::TabPage^  tabPage10;
    private: System::Windows::Forms::TabPage^  tabPage11;
    private: System::Windows::Forms::TabPage^  tabPage1;
    private: System::Windows::Forms::TabPage^  tabPage2;
    private: System::Windows::Forms::ListView^  Art_Res_list;
    private: System::Windows::Forms::ColumnHeader^  ArtResCol_ID;
    private: System::Windows::Forms::ColumnHeader^  ArtResCol_Path;
    private: System::Windows::Forms::Panel^  panel4;
    private: System::Windows::Forms::Panel^  panel18;
    private: System::Windows::Forms::ListView^  map_load_list;
    private: System::Windows::Forms::ColumnHeader^  MapCol_ID;
    private: System::Windows::Forms::ColumnHeader^  MapCol_Name;
    private: System::Windows::Forms::ColumnHeader^  MapCol_DistrictID;
    private: System::Windows::Forms::ColumnHeader^  MapCol_Type;
    private: System::Windows::Forms::Panel^  panel17;
    private: System::Windows::Forms::ComboBox^  Map_find_type_edit;
    private: System::Windows::Forms::Label^  label30;
    private: System::Windows::Forms::Label^  label24;
    private: System::Windows::Forms::Button^  button6;
    private: System::Windows::Forms::TextBox^  Map_find_district_id_edit;
    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::Label^  Map_ID_Edit;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::Button^  button1;
    private: System::Windows::Forms::ComboBox^  Map_Distrct_ID_Edit;
    private: System::Windows::Forms::ComboBox^  Map_ArtRes_Edit;
    private: System::Windows::Forms::TextBox^  Map_Note_edit;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::TextBox^  Map_Test_Edit;
    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::TextBox^  Map_Name_Edit;
    private: System::Windows::Forms::TabPage^  tabPage4;
    private: System::Windows::Forms::Panel^  panel5;
    private: System::Windows::Forms::ComboBox^  comboBox3;
    private: System::Windows::Forms::Label^  label8;
    private: System::Windows::Forms::Button^  button2;
    private: System::Windows::Forms::ListView^  Map_District_List;
    private: System::Windows::Forms::ColumnHeader^  MapDistrictCol_ID;
    private: System::Windows::Forms::Panel^  panel7;
    private: System::Windows::Forms::ListView^  Map_place_list;
    private: System::Windows::Forms::ColumnHeader^  MapPlaceCol_ID;
    private: System::Windows::Forms::ColumnHeader^  MapPlaceCol_Name;
    private: System::Windows::Forms::ColumnHeader^  MapPlaceCol_DistrictID;
    private: System::Windows::Forms::Panel^  panel8;
    private: System::Windows::Forms::Label^  label9;
    private: System::Windows::Forms::Button^  button3;
    private: System::Windows::Forms::TextBox^  textBox1;
    private: System::Windows::Forms::Panel^  panel6;
    private: System::Windows::Forms::ColumnHeader^  MapPlaceCol_SceneObjectName;
    private: System::Windows::Forms::Button^  button4;
    private: System::Windows::Forms::GroupBox^  groupBox2;
    private: System::Windows::Forms::ComboBox^  MapPlace_District_Id_Edit;
    private: System::Windows::Forms::ComboBox^  MapPlace_Template_Edit;
    private: System::Windows::Forms::TextBox^  MapPlace_Note_Edit;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::Label^  label10;
    private: System::Windows::Forms::TextBox^  MapPlace_Text_Edit;
    private: System::Windows::Forms::Label^  label11;
    private: System::Windows::Forms::TextBox^  MapPlace_Name_Edit;
    private: System::Windows::Forms::Label^  label12;
    private: System::Windows::Forms::Label^  MapPlace_ID_Text;
    private: System::Windows::Forms::Label^  label14;
    private: System::Windows::Forms::Label^  label15;
    private: System::Windows::Forms::ComboBox^  MapPlace_MapID_Edit;
    private: System::Windows::Forms::Label^  label17;
    private: System::Windows::Forms::Button^  button5;
    private: System::Windows::Forms::ComboBox^  MapPlace_SceneObjectName_edit;
    private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::ColumnHeader^  MapDistrictCol_Name;
private: System::Windows::Forms::Button^  button7;

	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip2 = (gcnew System::Windows::Forms::MenuStrip());
			this->文件ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->保存ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->帮助ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->tabControl6 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage10 = (gcnew System::Windows::Forms::TabPage());
			this->panel18 = (gcnew System::Windows::Forms::Panel());
			this->map_load_list = (gcnew System::Windows::Forms::ListView());
			this->MapCol_ID = (gcnew System::Windows::Forms::ColumnHeader());
			this->MapCol_Name = (gcnew System::Windows::Forms::ColumnHeader());
			this->MapCol_DistrictID = (gcnew System::Windows::Forms::ColumnHeader());
			this->MapCol_Type = (gcnew System::Windows::Forms::ColumnHeader());
			this->panel17 = (gcnew System::Windows::Forms::Panel());
			this->Map_find_type_edit = (gcnew System::Windows::Forms::ComboBox());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->Map_find_district_id_edit = (gcnew System::Windows::Forms::TextBox());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->Map_Distrct_ID_Edit = (gcnew System::Windows::Forms::ComboBox());
			this->Map_ArtRes_Edit = (gcnew System::Windows::Forms::ComboBox());
			this->Map_Note_edit = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->Map_Test_Edit = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->Map_Name_Edit = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->Map_ID_Edit = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabPage11 = (gcnew System::Windows::Forms::TabPage());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->Map_place_list = (gcnew System::Windows::Forms::ListView());
			this->MapPlaceCol_ID = (gcnew System::Windows::Forms::ColumnHeader());
			this->MapPlaceCol_Name = (gcnew System::Windows::Forms::ColumnHeader());
			this->MapPlaceCol_SceneObjectName = (gcnew System::Windows::Forms::ColumnHeader());
			this->MapPlaceCol_DistrictID = (gcnew System::Windows::Forms::ColumnHeader());
			this->panel8 = (gcnew System::Windows::Forms::Panel());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->MapPlace_MapID_Edit = (gcnew System::Windows::Forms::ComboBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->MapPlace_SceneObjectName_edit = (gcnew System::Windows::Forms::ComboBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->MapPlace_District_Id_Edit = (gcnew System::Windows::Forms::ComboBox());
			this->MapPlace_Template_Edit = (gcnew System::Windows::Forms::ComboBox());
			this->MapPlace_Note_Edit = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->MapPlace_Text_Edit = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->MapPlace_Name_Edit = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->MapPlace_ID_Text = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->Art_Res_list = (gcnew System::Windows::Forms::ListView());
			this->ArtResCol_ID = (gcnew System::Windows::Forms::ColumnHeader());
			this->ArtResCol_Path = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->Map_District_List = (gcnew System::Windows::Forms::ListView());
			this->MapDistrictCol_ID = (gcnew System::Windows::Forms::ColumnHeader());
			this->MapDistrictCol_Name = (gcnew System::Windows::Forms::ColumnHeader());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->menuStrip2->SuspendLayout();
			this->panel1->SuspendLayout();
			this->panel3->SuspendLayout();
			this->tabControl6->SuspendLayout();
			this->tabPage10->SuspendLayout();
			this->panel18->SuspendLayout();
			this->panel17->SuspendLayout();
			this->panel4->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tabPage11->SuspendLayout();
			this->panel7->SuspendLayout();
			this->panel8->SuspendLayout();
			this->panel6->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->panel2->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->panel5->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip2
			// 
			this->menuStrip2->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->文件ToolStripMenuItem, 
				this->帮助ToolStripMenuItem1});
			this->menuStrip2->Location = System::Drawing::Point(0, 0);
			this->menuStrip2->Name = L"menuStrip2";
			this->menuStrip2->Size = System::Drawing::Size(792, 24);
			this->menuStrip2->TabIndex = 2;
			this->menuStrip2->Text = L"menuStrip2";
			// 
			// 文件ToolStripMenuItem
			// 
			this->文件ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->保存ToolStripMenuItem1});
			this->文件ToolStripMenuItem->Name = L"文件ToolStripMenuItem";
			this->文件ToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->文件ToolStripMenuItem->Text = L"文件";
			// 
			// 保存ToolStripMenuItem1
			// 
			this->保存ToolStripMenuItem1->Name = L"保存ToolStripMenuItem1";
			this->保存ToolStripMenuItem1->Size = System::Drawing::Size(142, 22);
			this->保存ToolStripMenuItem1->Text = L"加载地图信息";
			this->保存ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &GameDataEditorForm::保存ToolStripMenuItem1_Click);
			// 
			// 帮助ToolStripMenuItem1
			// 
			this->帮助ToolStripMenuItem1->Name = L"帮助ToolStripMenuItem1";
			this->帮助ToolStripMenuItem1->Size = System::Drawing::Size(41, 20);
			this->帮助ToolStripMenuItem1->Text = L"帮助";
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->panel3);
			this->panel1->Controls->Add(this->panel2);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 24);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(792, 542);
			this->panel1->TabIndex = 5;
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->tabControl6);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel3->Location = System::Drawing::Point(0, 0);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(634, 542);
			this->panel3->TabIndex = 7;
			// 
			// tabControl6
			// 
			this->tabControl6->Controls->Add(this->tabPage10);
			this->tabControl6->Controls->Add(this->tabPage11);
			this->tabControl6->Controls->Add(this->tabPage1);
			this->tabControl6->Controls->Add(this->tabPage2);
			this->tabControl6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl6->Location = System::Drawing::Point(0, 0);
			this->tabControl6->Name = L"tabControl6";
			this->tabControl6->SelectedIndex = 0;
			this->tabControl6->Size = System::Drawing::Size(634, 542);
			this->tabControl6->TabIndex = 6;
			// 
			// tabPage10
			// 
			this->tabPage10->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage10->Controls->Add(this->panel18);
			this->tabPage10->Controls->Add(this->panel4);
			this->tabPage10->Location = System::Drawing::Point(4, 21);
			this->tabPage10->Name = L"tabPage10";
			this->tabPage10->Padding = System::Windows::Forms::Padding(3);
			this->tabPage10->Size = System::Drawing::Size(626, 517);
			this->tabPage10->TabIndex = 0;
			this->tabPage10->Text = L"分块地图编辑";
			// 
			// panel18
			// 
			this->panel18->Controls->Add(this->map_load_list);
			this->panel18->Controls->Add(this->panel17);
			this->panel18->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel18->Location = System::Drawing::Point(3, 3);
			this->panel18->Name = L"panel18";
			this->panel18->Size = System::Drawing::Size(237, 511);
			this->panel18->TabIndex = 11;
			// 
			// map_load_list
			// 
			this->map_load_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->MapCol_ID, this->MapCol_Name, 
				this->MapCol_DistrictID, this->MapCol_Type});
			this->map_load_list->Dock = System::Windows::Forms::DockStyle::Fill;
			this->map_load_list->FullRowSelect = true;
			this->map_load_list->GridLines = true;
			this->map_load_list->Location = System::Drawing::Point(0, 65);
			this->map_load_list->Name = L"map_load_list";
			this->map_load_list->Size = System::Drawing::Size(237, 446);
			this->map_load_list->TabIndex = 10;
			this->map_load_list->UseCompatibleStateImageBehavior = false;
			this->map_load_list->View = System::Windows::Forms::View::Details;
			this->map_load_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &GameDataEditorForm::map_load_list_MouseDoubleClick);
			// 
			// MapCol_ID
			// 
			this->MapCol_ID->Text = L"地图编号";
			this->MapCol_ID->Width = 48;
			// 
			// MapCol_Name
			// 
			this->MapCol_Name->Text = L"名字";
			// 
			// MapCol_DistrictID
			// 
			this->MapCol_DistrictID->Text = L"政区编号";
			this->MapCol_DistrictID->Width = 74;
			// 
			// MapCol_Type
			// 
			this->MapCol_Type->Text = L"类型";
			// 
			// panel17
			// 
			this->panel17->Controls->Add(this->Map_find_type_edit);
			this->panel17->Controls->Add(this->label30);
			this->panel17->Controls->Add(this->label24);
			this->panel17->Controls->Add(this->button6);
			this->panel17->Controls->Add(this->Map_find_district_id_edit);
			this->panel17->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel17->Location = System::Drawing::Point(0, 0);
			this->panel17->Name = L"panel17";
			this->panel17->Size = System::Drawing::Size(237, 65);
			this->panel17->TabIndex = 4;
			// 
			// Map_find_type_edit
			// 
			this->Map_find_type_edit->FormattingEnabled = true;
			this->Map_find_type_edit->Location = System::Drawing::Point(66, 35);
			this->Map_find_type_edit->Name = L"Map_find_type_edit";
			this->Map_find_type_edit->Size = System::Drawing::Size(96, 20);
			this->Map_find_type_edit->TabIndex = 6;
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(5, 40);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(35, 12);
			this->label30->TabIndex = 5;
			this->label30->Text = L"类型:";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(5, 10);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(59, 12);
			this->label24->TabIndex = 3;
			this->label24->Text = L"政区编号:";
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(171, 35);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(44, 23);
			this->button6->TabIndex = 2;
			this->button6->Text = L"查询";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &GameDataEditorForm::button6_Click);
			// 
			// Map_find_district_id_edit
			// 
			this->Map_find_district_id_edit->Location = System::Drawing::Point(66, 7);
			this->Map_find_district_id_edit->Name = L"Map_find_district_id_edit";
			this->Map_find_district_id_edit->Size = System::Drawing::Size(96, 21);
			this->Map_find_district_id_edit->TabIndex = 1;
			// 
			// panel4
			// 
			this->panel4->Controls->Add(this->button7);
			this->panel4->Controls->Add(this->button1);
			this->panel4->Controls->Add(this->groupBox1);
			this->panel4->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel4->Location = System::Drawing::Point(240, 3);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(383, 511);
			this->panel4->TabIndex = 10;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(279, 479);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"保存";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &GameDataEditorForm::button1_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->Map_Distrct_ID_Edit);
			this->groupBox1->Controls->Add(this->Map_ArtRes_Edit);
			this->groupBox1->Controls->Add(this->Map_Note_edit);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->Map_Test_Edit);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->Map_Name_Edit);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->Map_ID_Edit);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(22, 10);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(345, 458);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"当前选择的分块地图";
			// 
			// Map_Distrct_ID_Edit
			// 
			this->Map_Distrct_ID_Edit->FormattingEnabled = true;
			this->Map_Distrct_ID_Edit->Location = System::Drawing::Point(103, 52);
			this->Map_Distrct_ID_Edit->Name = L"Map_Distrct_ID_Edit";
			this->Map_Distrct_ID_Edit->Size = System::Drawing::Size(96, 20);
			this->Map_Distrct_ID_Edit->TabIndex = 18;
			// 
			// Map_ArtRes_Edit
			// 
			this->Map_ArtRes_Edit->FormattingEnabled = true;
			this->Map_ArtRes_Edit->Location = System::Drawing::Point(139, 84);
			this->Map_ArtRes_Edit->Name = L"Map_ArtRes_Edit";
			this->Map_ArtRes_Edit->Size = System::Drawing::Size(96, 20);
			this->Map_ArtRes_Edit->TabIndex = 17;
			// 
			// Map_Note_edit
			// 
			this->Map_Note_edit->Location = System::Drawing::Point(103, 347);
			this->Map_Note_edit->Multiline = true;
			this->Map_Note_edit->Name = L"Map_Note_edit";
			this->Map_Note_edit->Size = System::Drawing::Size(229, 96);
			this->Map_Note_edit->TabIndex = 16;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(26, 87);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(107, 12);
			this->label7->TabIndex = 15;
			this->label7->Text = L"美术场景资源编号:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(26, 155);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(35, 12);
			this->label6->TabIndex = 13;
			this->label6->Text = L"说明:";
			// 
			// Map_Test_Edit
			// 
			this->Map_Test_Edit->Location = System::Drawing::Point(103, 152);
			this->Map_Test_Edit->Multiline = true;
			this->Map_Test_Edit->Name = L"Map_Test_Edit";
			this->Map_Test_Edit->Size = System::Drawing::Size(229, 165);
			this->Map_Test_Edit->TabIndex = 12;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(26, 117);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(35, 12);
			this->label5->TabIndex = 11;
			this->label5->Text = L"名字:";
			// 
			// Map_Name_Edit
			// 
			this->Map_Name_Edit->Location = System::Drawing::Point(103, 117);
			this->Map_Name_Edit->Name = L"Map_Name_Edit";
			this->Map_Name_Edit->Size = System::Drawing::Size(96, 21);
			this->Map_Name_Edit->TabIndex = 10;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(26, 333);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(59, 12);
			this->label4->TabIndex = 9;
			this->label4->Text = L"策划备注:";
			// 
			// Map_ID_Edit
			// 
			this->Map_ID_Edit->AutoSize = true;
			this->Map_ID_Edit->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Map_ID_Edit->Location = System::Drawing::Point(103, 28);
			this->Map_ID_Edit->Name = L"Map_ID_Edit";
			this->Map_ID_Edit->Size = System::Drawing::Size(25, 14);
			this->Map_ID_Edit->TabIndex = 7;
			this->Map_ID_Edit->Text = L"XXX";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(26, 28);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(59, 12);
			this->label2->TabIndex = 6;
			this->label2->Text = L"地图编号:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(26, 55);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 12);
			this->label1->TabIndex = 5;
			this->label1->Text = L"政区编号:";
			// 
			// tabPage11
			// 
			this->tabPage11->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage11->Controls->Add(this->panel7);
			this->tabPage11->Controls->Add(this->panel6);
			this->tabPage11->Location = System::Drawing::Point(4, 21);
			this->tabPage11->Name = L"tabPage11";
			this->tabPage11->Padding = System::Windows::Forms::Padding(3);
			this->tabPage11->Size = System::Drawing::Size(626, 517);
			this->tabPage11->TabIndex = 1;
			this->tabPage11->Text = L"地点编辑";
			// 
			// panel7
			// 
			this->panel7->Controls->Add(this->Map_place_list);
			this->panel7->Controls->Add(this->panel8);
			this->panel7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel7->Location = System::Drawing::Point(3, 3);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(223, 511);
			this->panel7->TabIndex = 1;
			// 
			// Map_place_list
			// 
			this->Map_place_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->MapPlaceCol_ID, 
				this->MapPlaceCol_Name, this->MapPlaceCol_SceneObjectName, this->MapPlaceCol_DistrictID});
			this->Map_place_list->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Map_place_list->FullRowSelect = true;
			this->Map_place_list->GridLines = true;
			this->Map_place_list->Location = System::Drawing::Point(0, 39);
			this->Map_place_list->Name = L"Map_place_list";
			this->Map_place_list->Size = System::Drawing::Size(223, 472);
			this->Map_place_list->TabIndex = 11;
			this->Map_place_list->UseCompatibleStateImageBehavior = false;
			this->Map_place_list->View = System::Windows::Forms::View::Details;
			this->Map_place_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &GameDataEditorForm::Map_place_list_MouseDoubleClick);
			// 
			// MapPlaceCol_ID
			// 
			this->MapPlaceCol_ID->Text = L"编号";
			this->MapPlaceCol_ID->Width = 48;
			// 
			// MapPlaceCol_Name
			// 
			this->MapPlaceCol_Name->Text = L"名字";
			// 
			// MapPlaceCol_SceneObjectName
			// 
			this->MapPlaceCol_SceneObjectName->Text = L"场景对象名字";
			this->MapPlaceCol_SceneObjectName->Width = 88;
			// 
			// MapPlaceCol_DistrictID
			// 
			this->MapPlaceCol_DistrictID->Text = L"政区编号";
			this->MapPlaceCol_DistrictID->Width = 86;
			// 
			// panel8
			// 
			this->panel8->Controls->Add(this->label9);
			this->panel8->Controls->Add(this->button3);
			this->panel8->Controls->Add(this->textBox1);
			this->panel8->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel8->Location = System::Drawing::Point(0, 0);
			this->panel8->Name = L"panel8";
			this->panel8->Size = System::Drawing::Size(223, 39);
			this->panel8->TabIndex = 5;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(5, 10);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(83, 12);
			this->label9->TabIndex = 3;
			this->label9->Text = L"所属地图编号:";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(176, 7);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(44, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"查询";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &GameDataEditorForm::button3_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(94, 7);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(76, 21);
			this->textBox1->TabIndex = 1;
			// 
			// panel6
			// 
			this->panel6->Controls->Add(this->button4);
			this->panel6->Controls->Add(this->groupBox2);
			this->panel6->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel6->Location = System::Drawing::Point(226, 3);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(397, 511);
			this->panel6->TabIndex = 0;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(302, 477);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 1;
			this->button4->Text = L"保存";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &GameDataEditorForm::button4_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->MapPlace_MapID_Edit);
			this->groupBox2->Controls->Add(this->label17);
			this->groupBox2->Controls->Add(this->button5);
			this->groupBox2->Controls->Add(this->MapPlace_SceneObjectName_edit);
			this->groupBox2->Controls->Add(this->label16);
			this->groupBox2->Controls->Add(this->MapPlace_District_Id_Edit);
			this->groupBox2->Controls->Add(this->MapPlace_Template_Edit);
			this->groupBox2->Controls->Add(this->MapPlace_Note_Edit);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->MapPlace_Text_Edit);
			this->groupBox2->Controls->Add(this->label11);
			this->groupBox2->Controls->Add(this->MapPlace_Name_Edit);
			this->groupBox2->Controls->Add(this->label12);
			this->groupBox2->Controls->Add(this->MapPlace_ID_Text);
			this->groupBox2->Controls->Add(this->label14);
			this->groupBox2->Controls->Add(this->label15);
			this->groupBox2->Location = System::Drawing::Point(28, 11);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(347, 460);
			this->groupBox2->TabIndex = 0;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"当前选择的地点";
			// 
			// MapPlace_MapID_Edit
			// 
			this->MapPlace_MapID_Edit->FormattingEnabled = true;
			this->MapPlace_MapID_Edit->Location = System::Drawing::Point(274, 49);
			this->MapPlace_MapID_Edit->Name = L"MapPlace_MapID_Edit";
			this->MapPlace_MapID_Edit->Size = System::Drawing::Size(62, 20);
			this->MapPlace_MapID_Edit->TabIndex = 35;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(162, 52);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(107, 12);
			this->label17->TabIndex = 34;
			this->label17->Text = L"所属分块地图编号:";
			// 
			// button5
			// 
			this->button5->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->button5->Location = System::Drawing::Point(212, 119);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(114, 23);
			this->button5->TabIndex = 33;
			this->button5->Text = L"加载所属城市场景";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &GameDataEditorForm::button5_Click);
			// 
			// MapPlace_SceneObjectName_edit
			// 
			this->MapPlace_SceneObjectName_edit->FormattingEnabled = true;
			this->MapPlace_SceneObjectName_edit->Location = System::Drawing::Point(109, 121);
			this->MapPlace_SceneObjectName_edit->Name = L"MapPlace_SceneObjectName_edit";
			this->MapPlace_SceneObjectName_edit->Size = System::Drawing::Size(84, 20);
			this->MapPlace_SceneObjectName_edit->TabIndex = 32;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->label16->Location = System::Drawing::Point(20, 124);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(83, 12);
			this->label16->TabIndex = 31;
			this->label16->Text = L"场景对象名字:";
			// 
			// MapPlace_District_Id_Edit
			// 
			this->MapPlace_District_Id_Edit->FormattingEnabled = true;
			this->MapPlace_District_Id_Edit->Location = System::Drawing::Point(97, 49);
			this->MapPlace_District_Id_Edit->Name = L"MapPlace_District_Id_Edit";
			this->MapPlace_District_Id_Edit->Size = System::Drawing::Size(62, 20);
			this->MapPlace_District_Id_Edit->TabIndex = 30;
			// 
			// MapPlace_Template_Edit
			// 
			this->MapPlace_Template_Edit->FormattingEnabled = true;
			this->MapPlace_Template_Edit->Location = System::Drawing::Point(109, 85);
			this->MapPlace_Template_Edit->Name = L"MapPlace_Template_Edit";
			this->MapPlace_Template_Edit->Size = System::Drawing::Size(84, 20);
			this->MapPlace_Template_Edit->TabIndex = 29;
			// 
			// MapPlace_Note_Edit
			// 
			this->MapPlace_Note_Edit->Location = System::Drawing::Point(97, 344);
			this->MapPlace_Note_Edit->Multiline = true;
			this->MapPlace_Note_Edit->Name = L"MapPlace_Note_Edit";
			this->MapPlace_Note_Edit->Size = System::Drawing::Size(229, 96);
			this->MapPlace_Note_Edit->TabIndex = 28;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(20, 88);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(83, 12);
			this->label3->TabIndex = 27;
			this->label3->Text = L"地点模板编号:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(20, 205);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(35, 12);
			this->label10->TabIndex = 26;
			this->label10->Text = L"说明:";
			// 
			// MapPlace_Text_Edit
			// 
			this->MapPlace_Text_Edit->Location = System::Drawing::Point(97, 202);
			this->MapPlace_Text_Edit->Multiline = true;
			this->MapPlace_Text_Edit->Name = L"MapPlace_Text_Edit";
			this->MapPlace_Text_Edit->Size = System::Drawing::Size(229, 120);
			this->MapPlace_Text_Edit->TabIndex = 25;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(20, 162);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(35, 12);
			this->label11->TabIndex = 24;
			this->label11->Text = L"名字:";
			// 
			// MapPlace_Name_Edit
			// 
			this->MapPlace_Name_Edit->Location = System::Drawing::Point(97, 162);
			this->MapPlace_Name_Edit->Name = L"MapPlace_Name_Edit";
			this->MapPlace_Name_Edit->Size = System::Drawing::Size(96, 21);
			this->MapPlace_Name_Edit->TabIndex = 23;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(20, 330);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(59, 12);
			this->label12->TabIndex = 22;
			this->label12->Text = L"策划备注:";
			// 
			// MapPlace_ID_Text
			// 
			this->MapPlace_ID_Text->AutoSize = true;
			this->MapPlace_ID_Text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->MapPlace_ID_Text->Location = System::Drawing::Point(97, 25);
			this->MapPlace_ID_Text->Name = L"MapPlace_ID_Text";
			this->MapPlace_ID_Text->Size = System::Drawing::Size(25, 14);
			this->MapPlace_ID_Text->TabIndex = 21;
			this->MapPlace_ID_Text->Text = L"XXX";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(20, 25);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(59, 12);
			this->label14->TabIndex = 20;
			this->label14->Text = L"地点编号:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(20, 52);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(59, 12);
			this->label15->TabIndex = 19;
			this->label15->Text = L"政区编号:";
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage1->Location = System::Drawing::Point(4, 21);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(626, 517);
			this->tabPage1->TabIndex = 2;
			this->tabPage1->Text = L"区域编辑";
			// 
			// tabPage2
			// 
			this->tabPage2->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage2->Location = System::Drawing::Point(4, 21);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(626, 517);
			this->tabPage2->TabIndex = 3;
			this->tabPage2->Text = L"建筑编辑";
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->tabControl1);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel2->Location = System::Drawing::Point(634, 0);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(158, 542);
			this->panel2->TabIndex = 6;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(158, 542);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage3
			// 
			this->tabPage3->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage3->Controls->Add(this->Art_Res_list);
			this->tabPage3->Location = System::Drawing::Point(4, 21);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(150, 517);
			this->tabPage3->TabIndex = 0;
			this->tabPage3->Text = L"美术场景表";
			// 
			// Art_Res_list
			// 
			this->Art_Res_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->ArtResCol_ID, 
				this->ArtResCol_Path});
			this->Art_Res_list->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Art_Res_list->FullRowSelect = true;
			this->Art_Res_list->GridLines = true;
			this->Art_Res_list->Location = System::Drawing::Point(3, 3);
			this->Art_Res_list->Name = L"Art_Res_list";
			this->Art_Res_list->Size = System::Drawing::Size(144, 511);
			this->Art_Res_list->TabIndex = 9;
			this->Art_Res_list->UseCompatibleStateImageBehavior = false;
			this->Art_Res_list->View = System::Windows::Forms::View::Details;
			// 
			// ArtResCol_ID
			// 
			this->ArtResCol_ID->Text = L"编号";
			this->ArtResCol_ID->Width = 48;
			// 
			// ArtResCol_Path
			// 
			this->ArtResCol_Path->Text = L"路径";
			this->ArtResCol_Path->Width = 84;
			// 
			// tabPage4
			// 
			this->tabPage4->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage4->Controls->Add(this->Map_District_List);
			this->tabPage4->Controls->Add(this->panel5);
			this->tabPage4->Location = System::Drawing::Point(4, 21);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(150, 517);
			this->tabPage4->TabIndex = 1;
			this->tabPage4->Text = L"政区";
			// 
			// Map_District_List
			// 
			this->Map_District_List->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->MapDistrictCol_ID, 
				this->MapDistrictCol_Name});
			this->Map_District_List->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Map_District_List->FullRowSelect = true;
			this->Map_District_List->GridLines = true;
			this->Map_District_List->Location = System::Drawing::Point(3, 65);
			this->Map_District_List->Name = L"Map_District_List";
			this->Map_District_List->Size = System::Drawing::Size(144, 449);
			this->Map_District_List->TabIndex = 12;
			this->Map_District_List->UseCompatibleStateImageBehavior = false;
			this->Map_District_List->View = System::Windows::Forms::View::Details;
			// 
			// MapDistrictCol_ID
			// 
			this->MapDistrictCol_ID->Text = L"编号";
			this->MapDistrictCol_ID->Width = 48;
			// 
			// MapDistrictCol_Name
			// 
			this->MapDistrictCol_Name->Text = L"名字";
			this->MapDistrictCol_Name->Width = 81;
			// 
			// panel5
			// 
			this->panel5->Controls->Add(this->comboBox3);
			this->panel5->Controls->Add(this->label8);
			this->panel5->Controls->Add(this->button2);
			this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel5->Location = System::Drawing::Point(3, 3);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(144, 62);
			this->panel5->TabIndex = 11;
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Location = System::Drawing::Point(42, 7);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(96, 20);
			this->comboBox3->TabIndex = 6;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(3, 10);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(35, 12);
			this->label8->TabIndex = 5;
			this->label8->Text = L"类型:";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(92, 33);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(44, 23);
			this->button2->TabIndex = 2;
			this->button2->Text = L"查询";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &GameDataEditorForm::button2_Click);
			// 
			// button7
			// 
			this->button7->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->button7->Location = System::Drawing::Point(50, 479);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(114, 23);
			this->button7->TabIndex = 34;
			this->button7->Text = L"加载所属城市场景";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &GameDataEditorForm::button7_Click);
			// 
			// GameDataEditorForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(792, 566);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->menuStrip2);
			this->Name = L"GameDataEditorForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"GameDataEditorForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &GameDataEditorForm::GameDataEditorForm_FormClosed);
			this->menuStrip2->ResumeLayout(false);
			this->menuStrip2->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->tabControl6->ResumeLayout(false);
			this->tabPage10->ResumeLayout(false);
			this->panel18->ResumeLayout(false);
			this->panel17->ResumeLayout(false);
			this->panel17->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tabPage11->ResumeLayout(false);
			this->panel7->ResumeLayout(false);
			this->panel8->ResumeLayout(false);
			this->panel8->PerformLayout();
			this->panel6->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage4->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
    private: System::Void 保存ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
                this->load();
             }
    private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
                this->searchMapObjectList();
             }
    private: System::Void map_load_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                this->selMapObjectFromList();
             }
    private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->saveSelMapObject();
             }
    private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->searchPlaceObjectList();
             }
    private: System::Void Map_place_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                 this->selPlaceObjectFromList();
             }
    private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->loadPlaceScene();
             }
    private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->saveSelPlaceObject();
             }
    private: System::Void GameDataEditorForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
                 this->closeForm();
             }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				this->searchDistObjList();
		 }
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
				this->loadPlaceScene();
		 }
};
}
