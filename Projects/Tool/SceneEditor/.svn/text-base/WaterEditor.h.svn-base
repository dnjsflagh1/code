#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace SceneEditor {

	/// <summary>
	/// Summary for WaterEditor
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class WaterEditor : public System::Windows::Forms::Form
	{
	public:
		WaterEditor(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

			mSelectEffectID = 0;
		}

	public:

		/////////////////////////////////////////////////////////////////////////

		///初始化
		void    initialize();
		///反初始化
		void    unInitialize();
		///关闭
		void    closeForm();

		/////////////////////////////////////////////////////////////////////////
		// 刷新
		void    clearEditPanel();
		/////////////////////////////////////////////////////////////////////////
		// 加载总的水特效列表
		void    loadTotalWaterEffectList();
		// 选择当前总贴图
		void    selectWaterEffectList(U32 id);
		// 当前资源的配置
		void	applyWaterEffectList(U32 id, bool isSave);
		/////////////////////////////////////////////////////////////////////////

	protected:

		/////////////////////////////////////////////////////////////////////////
		//事件
		/////////////////////////////////////////////////////////////////////////

		//当选中一个listView的项目
		void	onEventPressListView();

		//当确定按钮摁下
		void	onEventPressOK();

		//摁下存储按钮
		void    onEventPressSave();

		//摁下重载入按钮
		void	onEventPressReload();

	protected:

		//当选中的effectID
		U32		mSelectEffectID;


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~WaterEditor()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::TextBox^  edit_waterBumpTexAnimW;
    private: System::Windows::Forms::Label^  label36;
    private: System::Windows::Forms::Label^  label37;
    private: System::Windows::Forms::TextBox^  edit_waterBumpTexAnimZ;
    private: System::Windows::Forms::TextBox^  edit_waterBumpTexAnimY;
    private: System::Windows::Forms::Label^  label38;
    private: System::Windows::Forms::Label^  label39;
    private: System::Windows::Forms::TextBox^  edit_waterBumpTexAnimX;
    private: System::Windows::Forms::TextBox^  edit_waterReflectScalsesX;
    private: System::Windows::Forms::Label^  label35;
    private: System::Windows::Forms::Label^  label32;
    private: System::Windows::Forms::TextBox^  edit_waterReflectScalsesW;
    private: System::Windows::Forms::Label^  label33;
    private: System::Windows::Forms::TextBox^  edit_waterReflectScalsesZ;
    private: System::Windows::Forms::Label^  label34;
    private: System::Windows::Forms::TextBox^  edit_waterReflectScalsesY;
    private: System::Windows::Forms::Button^  WaterEditor_Save;
    private: System::Windows::Forms::Button^  WaterEditor_Reload;
    private: System::Windows::Forms::GroupBox^  groupBox9;
    private: System::Windows::Forms::Label^  label22;
    private: System::Windows::Forms::TextBox^  edit_waterSpecularColorZ;
    private: System::Windows::Forms::Label^  label24;
    private: System::Windows::Forms::TextBox^  edit_waterSpecularColorY;
    private: System::Windows::Forms::Label^  label25;
    private: System::Windows::Forms::TextBox^  edit_waterSpecularColorX;
    private: System::Windows::Forms::GroupBox^  groupBox6;
    private: System::Windows::Forms::Label^  label16;
    private: System::Windows::Forms::TextBox^  edit_waterReflectColorZ;
    private: System::Windows::Forms::Label^  label20;
    private: System::Windows::Forms::TextBox^  edit_waterReflectColorY;
    private: System::Windows::Forms::Label^  label21;
    private: System::Windows::Forms::TextBox^  edit_waterReflectColorX;
    private: System::Windows::Forms::GroupBox^  groupBox5;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::TextBox^  textBox1;
    private: System::Windows::Forms::Label^  label4;
    private: System::Windows::Forms::TextBox^  textBox2;
    private: System::Windows::Forms::Label^  label7;
    private: System::Windows::Forms::TextBox^  textBox3;
    private: System::Windows::Forms::TextBox^  edit_waterReflectColorW;
    private: System::Windows::Forms::Label^  label11;
    private: System::Windows::Forms::Label^  label8;
    private: System::Windows::Forms::Label^  label26;
    private: System::Windows::Forms::TextBox^  edit_waterRefractScalsesW;
    private: System::Windows::Forms::Label^  label12;
    private: System::Windows::Forms::TextBox^  edit_waterRefractScalsesZ;
    private: System::Windows::Forms::Label^  label27;
    private: System::Windows::Forms::Label^  label28;
    private: System::Windows::Forms::TextBox^  edit_waterSpecularScalsesW;
    private: System::Windows::Forms::Label^  label29;
    private: System::Windows::Forms::TextBox^  edit_waterSpecularScalsesZ;
    private: System::Windows::Forms::Label^  label30;
    private: System::Windows::Forms::TextBox^  edit_waterSpecularScalsesX;
    private: System::Windows::Forms::Label^  label31;
    private: System::Windows::Forms::TextBox^  edit_waterSpecularScalsesY;
    private: System::Windows::Forms::GroupBox^  groupBox3;
    private: System::Windows::Forms::Label^  label15;
    private: System::Windows::Forms::TextBox^  edit_waterSkyCubeTexName;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::TextBox^  edit_waterBumpTexName1;
    private: System::Windows::Forms::Label^  label14;
    private: System::Windows::Forms::TextBox^  edit_waterBumpTexName3;
    private: System::Windows::Forms::Label^  label13;
    private: System::Windows::Forms::TextBox^  edit_waterBumpTexName2;
    private: System::Windows::Forms::Panel^  panel1;
    private: System::Windows::Forms::ListView^  listView_WaterEffect_list;
    private: System::Windows::Forms::ColumnHeader^  columnHeader_water_effect_index;
    private: System::Windows::Forms::ColumnHeader^  columnHeader_water_effect_name;
    private: System::Windows::Forms::Panel^  panel18;
    private: System::Windows::Forms::Label^  cur_water_effect_label;
    private: System::Windows::Forms::Label^  lable_terrain_batch_sel;
    private: System::Windows::Forms::Panel^  panel2;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::TextBox^  edit_waterBumpTexParamsZ;
    private: System::Windows::Forms::GroupBox^  groupBox1;
    private: System::Windows::Forms::Label^  label5;
    private: System::Windows::Forms::TextBox^  edit_waterBumpTexParamsY;
    private: System::Windows::Forms::Label^  label6;
    private: System::Windows::Forms::TextBox^  edit_waterBumpTexParamsX;
    private: System::Windows::Forms::GroupBox^  groupBox4;
    private: System::Windows::Forms::Label^  label17;
    private: System::Windows::Forms::TextBox^  edit_waterDeepColorZ;
    private: System::Windows::Forms::Label^  label18;
    private: System::Windows::Forms::TextBox^  edit_waterDeepColorY;
    private: System::Windows::Forms::Label^  label19;
    private: System::Windows::Forms::TextBox^  edit_waterDeepColorX;
    private: System::Windows::Forms::GroupBox^  groupBox2;
    private: System::Windows::Forms::Label^  label9;
    private: System::Windows::Forms::TextBox^  edit_waterRefractScalsesX;
    private: System::Windows::Forms::Label^  label10;
    private: System::Windows::Forms::TextBox^  edit_waterRefractScalsesY;
    private: System::Windows::Forms::Label^  label23;
    private: System::Windows::Forms::TextBox^  edit_waterBumpTexParamsW;
    private: System::Windows::Forms::Button^  WaterEditor_Confirm;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->listView_WaterEffect_list = (gcnew System::Windows::Forms::ListView());
            this->columnHeader_water_effect_index = (gcnew System::Windows::Forms::ColumnHeader());
            this->columnHeader_water_effect_name = (gcnew System::Windows::Forms::ColumnHeader());
            this->panel18 = (gcnew System::Windows::Forms::Panel());
            this->cur_water_effect_label = (gcnew System::Windows::Forms::Label());
            this->lable_terrain_batch_sel = (gcnew System::Windows::Forms::Label());
            this->panel2 = (gcnew System::Windows::Forms::Panel());
            this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
            this->edit_waterBumpTexAnimW = (gcnew System::Windows::Forms::TextBox());
            this->label36 = (gcnew System::Windows::Forms::Label());
            this->label37 = (gcnew System::Windows::Forms::Label());
            this->edit_waterBumpTexAnimZ = (gcnew System::Windows::Forms::TextBox());
            this->edit_waterBumpTexAnimY = (gcnew System::Windows::Forms::TextBox());
            this->label38 = (gcnew System::Windows::Forms::Label());
            this->label39 = (gcnew System::Windows::Forms::Label());
            this->edit_waterBumpTexAnimX = (gcnew System::Windows::Forms::TextBox());
            this->label14 = (gcnew System::Windows::Forms::Label());
            this->edit_waterBumpTexName3 = (gcnew System::Windows::Forms::TextBox());
            this->label13 = (gcnew System::Windows::Forms::Label());
            this->edit_waterBumpTexName2 = (gcnew System::Windows::Forms::TextBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->edit_waterBumpTexName1 = (gcnew System::Windows::Forms::TextBox());
            this->label15 = (gcnew System::Windows::Forms::Label());
            this->edit_waterSkyCubeTexName = (gcnew System::Windows::Forms::TextBox());
            this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
            this->label28 = (gcnew System::Windows::Forms::Label());
            this->edit_waterSpecularScalsesW = (gcnew System::Windows::Forms::TextBox());
            this->label29 = (gcnew System::Windows::Forms::Label());
            this->edit_waterSpecularScalsesZ = (gcnew System::Windows::Forms::TextBox());
            this->label30 = (gcnew System::Windows::Forms::Label());
            this->edit_waterSpecularScalsesX = (gcnew System::Windows::Forms::TextBox());
            this->label31 = (gcnew System::Windows::Forms::Label());
            this->edit_waterSpecularScalsesY = (gcnew System::Windows::Forms::TextBox());
            this->label27 = (gcnew System::Windows::Forms::Label());
            this->label22 = (gcnew System::Windows::Forms::Label());
            this->edit_waterSpecularColorZ = (gcnew System::Windows::Forms::TextBox());
            this->label24 = (gcnew System::Windows::Forms::Label());
            this->edit_waterSpecularColorY = (gcnew System::Windows::Forms::TextBox());
            this->label25 = (gcnew System::Windows::Forms::Label());
            this->edit_waterSpecularColorX = (gcnew System::Windows::Forms::TextBox());
            this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
            this->edit_waterReflectScalsesX = (gcnew System::Windows::Forms::TextBox());
            this->label35 = (gcnew System::Windows::Forms::Label());
            this->label32 = (gcnew System::Windows::Forms::Label());
            this->edit_waterReflectScalsesW = (gcnew System::Windows::Forms::TextBox());
            this->label33 = (gcnew System::Windows::Forms::Label());
            this->edit_waterReflectScalsesZ = (gcnew System::Windows::Forms::TextBox());
            this->label34 = (gcnew System::Windows::Forms::Label());
            this->edit_waterReflectScalsesY = (gcnew System::Windows::Forms::TextBox());
            this->edit_waterReflectColorW = (gcnew System::Windows::Forms::TextBox());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label16 = (gcnew System::Windows::Forms::Label());
            this->edit_waterReflectColorZ = (gcnew System::Windows::Forms::TextBox());
            this->label20 = (gcnew System::Windows::Forms::Label());
            this->edit_waterReflectColorY = (gcnew System::Windows::Forms::TextBox());
            this->label21 = (gcnew System::Windows::Forms::Label());
            this->edit_waterReflectColorX = (gcnew System::Windows::Forms::TextBox());
            this->WaterEditor_Reload = (gcnew System::Windows::Forms::Button());
            this->WaterEditor_Save = (gcnew System::Windows::Forms::Button());
            this->WaterEditor_Confirm = (gcnew System::Windows::Forms::Button());
            this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
            this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->textBox2 = (gcnew System::Windows::Forms::TextBox());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->textBox3 = (gcnew System::Windows::Forms::TextBox());
            this->label17 = (gcnew System::Windows::Forms::Label());
            this->edit_waterDeepColorZ = (gcnew System::Windows::Forms::TextBox());
            this->label18 = (gcnew System::Windows::Forms::Label());
            this->edit_waterDeepColorY = (gcnew System::Windows::Forms::TextBox());
            this->label19 = (gcnew System::Windows::Forms::Label());
            this->edit_waterDeepColorX = (gcnew System::Windows::Forms::TextBox());
            this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
            this->edit_waterBumpTexParamsW = (gcnew System::Windows::Forms::TextBox());
            this->label23 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->edit_waterBumpTexParamsY = (gcnew System::Windows::Forms::TextBox());
            this->edit_waterBumpTexParamsZ = (gcnew System::Windows::Forms::TextBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->edit_waterBumpTexParamsX = (gcnew System::Windows::Forms::TextBox());
            this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
            this->label26 = (gcnew System::Windows::Forms::Label());
            this->edit_waterRefractScalsesW = (gcnew System::Windows::Forms::TextBox());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->edit_waterRefractScalsesZ = (gcnew System::Windows::Forms::TextBox());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->edit_waterRefractScalsesX = (gcnew System::Windows::Forms::TextBox());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->edit_waterRefractScalsesY = (gcnew System::Windows::Forms::TextBox());
            this->panel1->SuspendLayout();
            this->panel18->SuspendLayout();
            this->panel2->SuspendLayout();
            this->groupBox3->SuspendLayout();
            this->groupBox9->SuspendLayout();
            this->groupBox6->SuspendLayout();
            this->groupBox4->SuspendLayout();
            this->groupBox5->SuspendLayout();
            this->groupBox1->SuspendLayout();
            this->groupBox2->SuspendLayout();
            this->SuspendLayout();
            // 
            // panel1
            // 
            this->panel1->Controls->Add(this->listView_WaterEffect_list);
            this->panel1->Controls->Add(this->panel18);
            this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panel1->Location = System::Drawing::Point(0, 0);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(798, 524);
            this->panel1->TabIndex = 0;
            // 
            // listView_WaterEffect_list
            // 
            this->listView_WaterEffect_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->columnHeader_water_effect_index, 
                this->columnHeader_water_effect_name});
            this->listView_WaterEffect_list->Dock = System::Windows::Forms::DockStyle::Fill;
            this->listView_WaterEffect_list->FullRowSelect = true;
            this->listView_WaterEffect_list->GridLines = true;
            this->listView_WaterEffect_list->Location = System::Drawing::Point(0, 0);
            this->listView_WaterEffect_list->MultiSelect = false;
            this->listView_WaterEffect_list->Name = L"listView_WaterEffect_list";
            this->listView_WaterEffect_list->Size = System::Drawing::Size(798, 453);
            this->listView_WaterEffect_list->TabIndex = 6;
            this->listView_WaterEffect_list->UseCompatibleStateImageBehavior = false;
            this->listView_WaterEffect_list->View = System::Windows::Forms::View::Details;
            this->listView_WaterEffect_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &WaterEditor::listView_WaterEffect_list_MouseDoubleClick);
            // 
            // columnHeader_water_effect_index
            // 
            this->columnHeader_water_effect_index->Text = L"序号";
            this->columnHeader_water_effect_index->Width = 67;
            // 
            // columnHeader_water_effect_name
            // 
            this->columnHeader_water_effect_name->Text = L"名字";
            this->columnHeader_water_effect_name->Width = 143;
            // 
            // panel18
            // 
            this->panel18->Controls->Add(this->cur_water_effect_label);
            this->panel18->Controls->Add(this->lable_terrain_batch_sel);
            this->panel18->Dock = System::Windows::Forms::DockStyle::Bottom;
            this->panel18->Location = System::Drawing::Point(0, 453);
            this->panel18->Name = L"panel18";
            this->panel18->Size = System::Drawing::Size(798, 71);
            this->panel18->TabIndex = 7;
            // 
            // cur_water_effect_label
            // 
            this->cur_water_effect_label->AutoSize = true;
            this->cur_water_effect_label->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->cur_water_effect_label->Location = System::Drawing::Point(7, 25);
            this->cur_water_effect_label->Name = L"cur_water_effect_label";
            this->cur_water_effect_label->Size = System::Drawing::Size(2, 14);
            this->cur_water_effect_label->TabIndex = 10;
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
            // panel2
            // 
            this->panel2->Controls->Add(this->groupBox3);
            this->panel2->Controls->Add(this->groupBox9);
            this->panel2->Controls->Add(this->groupBox6);
            this->panel2->Controls->Add(this->WaterEditor_Reload);
            this->panel2->Controls->Add(this->WaterEditor_Save);
            this->panel2->Controls->Add(this->WaterEditor_Confirm);
            this->panel2->Controls->Add(this->groupBox4);
            this->panel2->Controls->Add(this->groupBox1);
            this->panel2->Controls->Add(this->groupBox2);
            this->panel2->Dock = System::Windows::Forms::DockStyle::Right;
            this->panel2->Location = System::Drawing::Point(231, 0);
            this->panel2->Name = L"panel2";
            this->panel2->Size = System::Drawing::Size(567, 524);
            this->panel2->TabIndex = 1;
            // 
            // groupBox3
            // 
            this->groupBox3->Controls->Add(this->edit_waterBumpTexAnimW);
            this->groupBox3->Controls->Add(this->label36);
            this->groupBox3->Controls->Add(this->label37);
            this->groupBox3->Controls->Add(this->edit_waterBumpTexAnimZ);
            this->groupBox3->Controls->Add(this->edit_waterBumpTexAnimY);
            this->groupBox3->Controls->Add(this->label38);
            this->groupBox3->Controls->Add(this->label39);
            this->groupBox3->Controls->Add(this->edit_waterBumpTexAnimX);
            this->groupBox3->Controls->Add(this->label14);
            this->groupBox3->Controls->Add(this->edit_waterBumpTexName3);
            this->groupBox3->Controls->Add(this->label13);
            this->groupBox3->Controls->Add(this->edit_waterBumpTexName2);
            this->groupBox3->Controls->Add(this->label2);
            this->groupBox3->Controls->Add(this->edit_waterBumpTexName1);
            this->groupBox3->Controls->Add(this->label15);
            this->groupBox3->Controls->Add(this->edit_waterSkyCubeTexName);
            this->groupBox3->Location = System::Drawing::Point(289, 85);
            this->groupBox3->Name = L"groupBox3";
            this->groupBox3->Size = System::Drawing::Size(262, 183);
            this->groupBox3->TabIndex = 11;
            this->groupBox3->TabStop = false;
            this->groupBox3->Text = L"贴图材质";
            // 
            // edit_waterBumpTexAnimW
            // 
            this->edit_waterBumpTexAnimW->Location = System::Drawing::Point(215, 153);
            this->edit_waterBumpTexAnimW->Name = L"edit_waterBumpTexAnimW";
            this->edit_waterBumpTexAnimW->Size = System::Drawing::Size(32, 21);
            this->edit_waterBumpTexAnimW->TabIndex = 10;
            this->edit_waterBumpTexAnimW->Text = L"0.5";
            // 
            // label36
            // 
            this->label36->AutoSize = true;
            this->label36->Location = System::Drawing::Point(156, 158);
            this->label36->Name = L"label36";
            this->label36->Size = System::Drawing::Size(47, 12);
            this->label36->TabIndex = 13;
            this->label36->Text = L"未开放:";
            // 
            // label37
            // 
            this->label37->AutoSize = true;
            this->label37->Location = System::Drawing::Point(14, 156);
            this->label37->Name = L"label37";
            this->label37->Size = System::Drawing::Size(83, 12);
            this->label37->TabIndex = 15;
            this->label37->Text = L"贴图置换速度:";
            // 
            // edit_waterBumpTexAnimZ
            // 
            this->edit_waterBumpTexAnimZ->Location = System::Drawing::Point(215, 126);
            this->edit_waterBumpTexAnimZ->Name = L"edit_waterBumpTexAnimZ";
            this->edit_waterBumpTexAnimZ->Size = System::Drawing::Size(32, 21);
            this->edit_waterBumpTexAnimZ->TabIndex = 14;
            this->edit_waterBumpTexAnimZ->Text = L"0.5";
            // 
            // edit_waterBumpTexAnimY
            // 
            this->edit_waterBumpTexAnimY->Location = System::Drawing::Point(104, 153);
            this->edit_waterBumpTexAnimY->Name = L"edit_waterBumpTexAnimY";
            this->edit_waterBumpTexAnimY->Size = System::Drawing::Size(32, 21);
            this->edit_waterBumpTexAnimY->TabIndex = 9;
            this->edit_waterBumpTexAnimY->Text = L"0.5";
            // 
            // label38
            // 
            this->label38->AutoSize = true;
            this->label38->Location = System::Drawing::Point(156, 129);
            this->label38->Name = L"label38";
            this->label38->Size = System::Drawing::Size(47, 12);
            this->label38->TabIndex = 11;
            this->label38->Text = L"未开放:";
            // 
            // label39
            // 
            this->label39->AutoSize = true;
            this->label39->Location = System::Drawing::Point(14, 130);
            this->label39->Name = L"label39";
            this->label39->Size = System::Drawing::Size(83, 12);
            this->label39->TabIndex = 12;
            this->label39->Text = L"贴图动画数量:";
            // 
            // edit_waterBumpTexAnimX
            // 
            this->edit_waterBumpTexAnimX->Location = System::Drawing::Point(104, 125);
            this->edit_waterBumpTexAnimX->Name = L"edit_waterBumpTexAnimX";
            this->edit_waterBumpTexAnimX->Size = System::Drawing::Size(32, 21);
            this->edit_waterBumpTexAnimX->TabIndex = 8;
            this->edit_waterBumpTexAnimX->Text = L"0.5";
            // 
            // label14
            // 
            this->label14->AutoSize = true;
            this->label14->Location = System::Drawing::Point(14, 103);
            this->label14->Name = L"label14";
            this->label14->Size = System::Drawing::Size(65, 12);
            this->label14->TabIndex = 7;
            this->label14->Text = L"水波贴图3:";
            // 
            // edit_waterBumpTexName3
            // 
            this->edit_waterBumpTexName3->Location = System::Drawing::Point(84, 99);
            this->edit_waterBumpTexName3->Name = L"edit_waterBumpTexName3";
            this->edit_waterBumpTexName3->Size = System::Drawing::Size(157, 21);
            this->edit_waterBumpTexName3->TabIndex = 6;
            // 
            // label13
            // 
            this->label13->AutoSize = true;
            this->label13->Location = System::Drawing::Point(14, 75);
            this->label13->Name = L"label13";
            this->label13->Size = System::Drawing::Size(65, 12);
            this->label13->TabIndex = 5;
            this->label13->Text = L"水波贴图2:";
            // 
            // edit_waterBumpTexName2
            // 
            this->edit_waterBumpTexName2->Location = System::Drawing::Point(84, 71);
            this->edit_waterBumpTexName2->Name = L"edit_waterBumpTexName2";
            this->edit_waterBumpTexName2->Size = System::Drawing::Size(157, 21);
            this->edit_waterBumpTexName2->TabIndex = 4;
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(14, 48);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(65, 12);
            this->label2->TabIndex = 3;
            this->label2->Text = L"水波贴图1:";
            // 
            // edit_waterBumpTexName1
            // 
            this->edit_waterBumpTexName1->Location = System::Drawing::Point(84, 43);
            this->edit_waterBumpTexName1->Name = L"edit_waterBumpTexName1";
            this->edit_waterBumpTexName1->Size = System::Drawing::Size(157, 21);
            this->edit_waterBumpTexName1->TabIndex = 2;
            // 
            // label15
            // 
            this->label15->AutoSize = true;
            this->label15->Location = System::Drawing::Point(10, 19);
            this->label15->Name = L"label15";
            this->label15->Size = System::Drawing::Size(71, 12);
            this->label15->TabIndex = 1;
            this->label15->Text = L"天空盒贴图:";
            // 
            // edit_waterSkyCubeTexName
            // 
            this->edit_waterSkyCubeTexName->Location = System::Drawing::Point(85, 14);
            this->edit_waterSkyCubeTexName->Name = L"edit_waterSkyCubeTexName";
            this->edit_waterSkyCubeTexName->Size = System::Drawing::Size(156, 21);
            this->edit_waterSkyCubeTexName->TabIndex = 0;
            // 
            // groupBox9
            // 
            this->groupBox9->Controls->Add(this->label28);
            this->groupBox9->Controls->Add(this->edit_waterSpecularScalsesW);
            this->groupBox9->Controls->Add(this->label29);
            this->groupBox9->Controls->Add(this->edit_waterSpecularScalsesZ);
            this->groupBox9->Controls->Add(this->label30);
            this->groupBox9->Controls->Add(this->edit_waterSpecularScalsesX);
            this->groupBox9->Controls->Add(this->label31);
            this->groupBox9->Controls->Add(this->edit_waterSpecularScalsesY);
            this->groupBox9->Controls->Add(this->label27);
            this->groupBox9->Controls->Add(this->label22);
            this->groupBox9->Controls->Add(this->edit_waterSpecularColorZ);
            this->groupBox9->Controls->Add(this->label24);
            this->groupBox9->Controls->Add(this->edit_waterSpecularColorY);
            this->groupBox9->Controls->Add(this->label25);
            this->groupBox9->Controls->Add(this->edit_waterSpecularColorX);
            this->groupBox9->Location = System::Drawing::Point(15, 361);
            this->groupBox9->Name = L"groupBox9";
            this->groupBox9->Size = System::Drawing::Size(261, 154);
            this->groupBox9->TabIndex = 10;
            this->groupBox9->TabStop = false;
            this->groupBox9->Text = L"镜面高光";
            // 
            // label28
            // 
            this->label28->AutoSize = true;
            this->label28->Location = System::Drawing::Point(10, 126);
            this->label28->Name = L"label28";
            this->label28->Size = System::Drawing::Size(47, 12);
            this->label28->TabIndex = 15;
            this->label28->Text = L"未开放:";
            // 
            // edit_waterSpecularScalsesW
            // 
            this->edit_waterSpecularScalsesW->Location = System::Drawing::Point(220, 124);
            this->edit_waterSpecularScalsesW->Name = L"edit_waterSpecularScalsesW";
            this->edit_waterSpecularScalsesW->Size = System::Drawing::Size(32, 21);
            this->edit_waterSpecularScalsesW->TabIndex = 14;
            this->edit_waterSpecularScalsesW->Text = L"0.5";
            // 
            // label29
            // 
            this->label29->AutoSize = true;
            this->label29->Location = System::Drawing::Point(10, 101);
            this->label29->Name = L"label29";
            this->label29->Size = System::Drawing::Size(83, 12);
            this->label29->TabIndex = 13;
            this->label29->Text = L"镜面高光密度:";
            // 
            // edit_waterSpecularScalsesZ
            // 
            this->edit_waterSpecularScalsesZ->Location = System::Drawing::Point(220, 98);
            this->edit_waterSpecularScalsesZ->Name = L"edit_waterSpecularScalsesZ";
            this->edit_waterSpecularScalsesZ->Size = System::Drawing::Size(32, 21);
            this->edit_waterSpecularScalsesZ->TabIndex = 12;
            this->edit_waterSpecularScalsesZ->Text = L"0.5";
            // 
            // label30
            // 
            this->label30->AutoSize = true;
            this->label30->Location = System::Drawing::Point(10, 75);
            this->label30->Name = L"label30";
            this->label30->Size = System::Drawing::Size(83, 12);
            this->label30->TabIndex = 11;
            this->label30->Text = L"镜面高光强弱:";
            // 
            // edit_waterSpecularScalsesX
            // 
            this->edit_waterSpecularScalsesX->Location = System::Drawing::Point(220, 47);
            this->edit_waterSpecularScalsesX->Name = L"edit_waterSpecularScalsesX";
            this->edit_waterSpecularScalsesX->Size = System::Drawing::Size(32, 21);
            this->edit_waterSpecularScalsesX->TabIndex = 10;
            this->edit_waterSpecularScalsesX->Text = L"0.5";
            // 
            // label31
            // 
            this->label31->AutoSize = true;
            this->label31->Location = System::Drawing::Point(10, 50);
            this->label31->Name = L"label31";
            this->label31->Size = System::Drawing::Size(83, 12);
            this->label31->TabIndex = 9;
            this->label31->Text = L"镜面高光范围:";
            // 
            // edit_waterSpecularScalsesY
            // 
            this->edit_waterSpecularScalsesY->Location = System::Drawing::Point(220, 72);
            this->edit_waterSpecularScalsesY->Name = L"edit_waterSpecularScalsesY";
            this->edit_waterSpecularScalsesY->Size = System::Drawing::Size(32, 21);
            this->edit_waterSpecularScalsesY->TabIndex = 8;
            this->edit_waterSpecularScalsesY->Text = L"0.5";
            // 
            // label27
            // 
            this->label27->AutoSize = true;
            this->label27->Location = System::Drawing::Point(10, 24);
            this->label27->Name = L"label27";
            this->label27->Size = System::Drawing::Size(59, 12);
            this->label27->TabIndex = 6;
            this->label27->Text = L"高光颜色:";
            // 
            // label22
            // 
            this->label22->AutoSize = true;
            this->label22->Location = System::Drawing::Point(201, 23);
            this->label22->Name = L"label22";
            this->label22->Size = System::Drawing::Size(17, 12);
            this->label22->TabIndex = 5;
            this->label22->Text = L"b:";
            // 
            // edit_waterSpecularColorZ
            // 
            this->edit_waterSpecularColorZ->Location = System::Drawing::Point(220, 20);
            this->edit_waterSpecularColorZ->Name = L"edit_waterSpecularColorZ";
            this->edit_waterSpecularColorZ->Size = System::Drawing::Size(31, 21);
            this->edit_waterSpecularColorZ->TabIndex = 4;
            this->edit_waterSpecularColorZ->Text = L"0.5";
            // 
            // label24
            // 
            this->label24->AutoSize = true;
            this->label24->Location = System::Drawing::Point(142, 23);
            this->label24->Name = L"label24";
            this->label24->Size = System::Drawing::Size(17, 12);
            this->label24->TabIndex = 3;
            this->label24->Text = L"g:";
            // 
            // edit_waterSpecularColorY
            // 
            this->edit_waterSpecularColorY->Location = System::Drawing::Point(163, 20);
            this->edit_waterSpecularColorY->Name = L"edit_waterSpecularColorY";
            this->edit_waterSpecularColorY->Size = System::Drawing::Size(32, 21);
            this->edit_waterSpecularColorY->TabIndex = 2;
            this->edit_waterSpecularColorY->Text = L"0.5";
            // 
            // label25
            // 
            this->label25->AutoSize = true;
            this->label25->Location = System::Drawing::Point(82, 23);
            this->label25->Name = L"label25";
            this->label25->Size = System::Drawing::Size(17, 12);
            this->label25->TabIndex = 1;
            this->label25->Text = L"r:";
            // 
            // edit_waterSpecularColorX
            // 
            this->edit_waterSpecularColorX->Location = System::Drawing::Point(104, 20);
            this->edit_waterSpecularColorX->Name = L"edit_waterSpecularColorX";
            this->edit_waterSpecularColorX->Size = System::Drawing::Size(32, 21);
            this->edit_waterSpecularColorX->TabIndex = 0;
            this->edit_waterSpecularColorX->Text = L"0.5";
            // 
            // groupBox6
            // 
            this->groupBox6->Controls->Add(this->edit_waterReflectScalsesX);
            this->groupBox6->Controls->Add(this->label35);
            this->groupBox6->Controls->Add(this->label32);
            this->groupBox6->Controls->Add(this->edit_waterReflectScalsesW);
            this->groupBox6->Controls->Add(this->label33);
            this->groupBox6->Controls->Add(this->edit_waterReflectScalsesZ);
            this->groupBox6->Controls->Add(this->label34);
            this->groupBox6->Controls->Add(this->edit_waterReflectScalsesY);
            this->groupBox6->Controls->Add(this->edit_waterReflectColorW);
            this->groupBox6->Controls->Add(this->label11);
            this->groupBox6->Controls->Add(this->label8);
            this->groupBox6->Controls->Add(this->label16);
            this->groupBox6->Controls->Add(this->edit_waterReflectColorZ);
            this->groupBox6->Controls->Add(this->label20);
            this->groupBox6->Controls->Add(this->edit_waterReflectColorY);
            this->groupBox6->Controls->Add(this->label21);
            this->groupBox6->Controls->Add(this->edit_waterReflectColorX);
            this->groupBox6->Location = System::Drawing::Point(13, 55);
            this->groupBox6->Name = L"groupBox6";
            this->groupBox6->Size = System::Drawing::Size(262, 176);
            this->groupBox6->TabIndex = 10;
            this->groupBox6->TabStop = false;
            this->groupBox6->Text = L"场景反射";
            // 
            // edit_waterReflectScalsesX
            // 
            this->edit_waterReflectScalsesX->Location = System::Drawing::Point(222, 71);
            this->edit_waterReflectScalsesX->Name = L"edit_waterReflectScalsesX";
            this->edit_waterReflectScalsesX->Size = System::Drawing::Size(32, 21);
            this->edit_waterReflectScalsesX->TabIndex = 16;
            this->edit_waterReflectScalsesX->Text = L"0.5";
            // 
            // label35
            // 
            this->label35->AutoSize = true;
            this->label35->Location = System::Drawing::Point(12, 47);
            this->label35->Name = L"label35";
            this->label35->Size = System::Drawing::Size(107, 12);
            this->label35->TabIndex = 15;
            this->label35->Text = L"场景物件反射强弱:";
            // 
            // label32
            // 
            this->label32->AutoSize = true;
            this->label32->Location = System::Drawing::Point(12, 152);
            this->label32->Name = L"label32";
            this->label32->Size = System::Drawing::Size(47, 12);
            this->label32->TabIndex = 14;
            this->label32->Text = L"未开放:";
            // 
            // edit_waterReflectScalsesW
            // 
            this->edit_waterReflectScalsesW->Location = System::Drawing::Point(222, 149);
            this->edit_waterReflectScalsesW->Name = L"edit_waterReflectScalsesW";
            this->edit_waterReflectScalsesW->Size = System::Drawing::Size(32, 21);
            this->edit_waterReflectScalsesW->TabIndex = 13;
            this->edit_waterReflectScalsesW->Text = L"0.5";
            // 
            // label33
            // 
            this->label33->AutoSize = true;
            this->label33->Location = System::Drawing::Point(12, 127);
            this->label33->Name = L"label33";
            this->label33->Size = System::Drawing::Size(47, 12);
            this->label33->TabIndex = 12;
            this->label33->Text = L"未开放:";
            // 
            // edit_waterReflectScalsesZ
            // 
            this->edit_waterReflectScalsesZ->Location = System::Drawing::Point(222, 123);
            this->edit_waterReflectScalsesZ->Name = L"edit_waterReflectScalsesZ";
            this->edit_waterReflectScalsesZ->Size = System::Drawing::Size(32, 21);
            this->edit_waterReflectScalsesZ->TabIndex = 11;
            this->edit_waterReflectScalsesZ->Text = L"0.5";
            // 
            // label34
            // 
            this->label34->AutoSize = true;
            this->label34->Location = System::Drawing::Point(12, 101);
            this->label34->Name = L"label34";
            this->label34->Size = System::Drawing::Size(47, 12);
            this->label34->TabIndex = 10;
            this->label34->Text = L"未开放:";
            // 
            // edit_waterReflectScalsesY
            // 
            this->edit_waterReflectScalsesY->Location = System::Drawing::Point(222, 97);
            this->edit_waterReflectScalsesY->Name = L"edit_waterReflectScalsesY";
            this->edit_waterReflectScalsesY->Size = System::Drawing::Size(32, 21);
            this->edit_waterReflectScalsesY->TabIndex = 9;
            this->edit_waterReflectScalsesY->Text = L"0.5";
            // 
            // edit_waterReflectColorW
            // 
            this->edit_waterReflectColorW->Location = System::Drawing::Point(222, 44);
            this->edit_waterReflectColorW->Name = L"edit_waterReflectColorW";
            this->edit_waterReflectColorW->Size = System::Drawing::Size(32, 21);
            this->edit_waterReflectColorW->TabIndex = 8;
            this->edit_waterReflectColorW->Text = L"0.5";
            // 
            // label11
            // 
            this->label11->AutoSize = true;
            this->label11->Location = System::Drawing::Point(12, 74);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(119, 12);
            this->label11->TabIndex = 7;
            this->label11->Text = L"场景物件反射扭曲度:";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Location = System::Drawing::Point(11, 22);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(83, 12);
            this->label8->TabIndex = 6;
            this->label8->Text = L"天空反射颜色:";
            // 
            // label16
            // 
            this->label16->AutoSize = true;
            this->label16->Location = System::Drawing::Point(204, 22);
            this->label16->Name = L"label16";
            this->label16->Size = System::Drawing::Size(17, 12);
            this->label16->TabIndex = 5;
            this->label16->Text = L"b:";
            // 
            // edit_waterReflectColorZ
            // 
            this->edit_waterReflectColorZ->Location = System::Drawing::Point(222, 17);
            this->edit_waterReflectColorZ->Name = L"edit_waterReflectColorZ";
            this->edit_waterReflectColorZ->Size = System::Drawing::Size(31, 21);
            this->edit_waterReflectColorZ->TabIndex = 4;
            this->edit_waterReflectColorZ->Text = L"0.5";
            // 
            // label20
            // 
            this->label20->AutoSize = true;
            this->label20->Location = System::Drawing::Point(149, 21);
            this->label20->Name = L"label20";
            this->label20->Size = System::Drawing::Size(17, 12);
            this->label20->TabIndex = 3;
            this->label20->Text = L"g:";
            // 
            // edit_waterReflectColorY
            // 
            this->edit_waterReflectColorY->Location = System::Drawing::Point(168, 17);
            this->edit_waterReflectColorY->Name = L"edit_waterReflectColorY";
            this->edit_waterReflectColorY->Size = System::Drawing::Size(32, 21);
            this->edit_waterReflectColorY->TabIndex = 2;
            this->edit_waterReflectColorY->Text = L"0.5";
            // 
            // label21
            // 
            this->label21->AutoSize = true;
            this->label21->Location = System::Drawing::Point(95, 21);
            this->label21->Name = L"label21";
            this->label21->Size = System::Drawing::Size(17, 12);
            this->label21->TabIndex = 1;
            this->label21->Text = L"r:";
            // 
            // edit_waterReflectColorX
            // 
            this->edit_waterReflectColorX->Location = System::Drawing::Point(114, 17);
            this->edit_waterReflectColorX->Name = L"edit_waterReflectColorX";
            this->edit_waterReflectColorX->Size = System::Drawing::Size(32, 21);
            this->edit_waterReflectColorX->TabIndex = 0;
            this->edit_waterReflectColorX->Text = L"0.5";
            // 
            // WaterEditor_Reload
            // 
            this->WaterEditor_Reload->Location = System::Drawing::Point(476, 448);
            this->WaterEditor_Reload->Name = L"WaterEditor_Reload";
            this->WaterEditor_Reload->Size = System::Drawing::Size(74, 23);
            this->WaterEditor_Reload->TabIndex = 9;
            this->WaterEditor_Reload->Text = L"恢复";
            this->WaterEditor_Reload->UseVisualStyleBackColor = true;
            this->WaterEditor_Reload->Click += gcnew System::EventHandler(this, &WaterEditor::WaterEditor_Reload_Click);
            // 
            // WaterEditor_Save
            // 
            this->WaterEditor_Save->Location = System::Drawing::Point(476, 482);
            this->WaterEditor_Save->Name = L"WaterEditor_Save";
            this->WaterEditor_Save->Size = System::Drawing::Size(75, 23);
            this->WaterEditor_Save->TabIndex = 8;
            this->WaterEditor_Save->Text = L"响应&&保存";
            this->WaterEditor_Save->UseVisualStyleBackColor = true;
            this->WaterEditor_Save->Click += gcnew System::EventHandler(this, &WaterEditor::WaterEditor_Save_Click);
            // 
            // WaterEditor_Confirm
            // 
            this->WaterEditor_Confirm->Location = System::Drawing::Point(476, 411);
            this->WaterEditor_Confirm->Name = L"WaterEditor_Confirm";
            this->WaterEditor_Confirm->Size = System::Drawing::Size(75, 23);
            this->WaterEditor_Confirm->TabIndex = 7;
            this->WaterEditor_Confirm->Text = L"响应";
            this->WaterEditor_Confirm->UseVisualStyleBackColor = true;
            this->WaterEditor_Confirm->Click += gcnew System::EventHandler(this, &WaterEditor::WaterEditor_Confirm_Click);
            // 
            // groupBox4
            // 
            this->groupBox4->Controls->Add(this->groupBox5);
            this->groupBox4->Controls->Add(this->label17);
            this->groupBox4->Controls->Add(this->edit_waterDeepColorZ);
            this->groupBox4->Controls->Add(this->label18);
            this->groupBox4->Controls->Add(this->edit_waterDeepColorY);
            this->groupBox4->Controls->Add(this->label19);
            this->groupBox4->Controls->Add(this->edit_waterDeepColorX);
            this->groupBox4->Location = System::Drawing::Point(15, 6);
            this->groupBox4->Name = L"groupBox4";
            this->groupBox4->Size = System::Drawing::Size(259, 44);
            this->groupBox4->TabIndex = 5;
            this->groupBox4->TabStop = false;
            this->groupBox4->Text = L"水质颜色";
            // 
            // groupBox5
            // 
            this->groupBox5->Controls->Add(this->label3);
            this->groupBox5->Controls->Add(this->textBox1);
            this->groupBox5->Controls->Add(this->label4);
            this->groupBox5->Controls->Add(this->textBox2);
            this->groupBox5->Controls->Add(this->label7);
            this->groupBox5->Controls->Add(this->textBox3);
            this->groupBox5->Location = System::Drawing::Point(0, 51);
            this->groupBox5->Name = L"groupBox5";
            this->groupBox5->Size = System::Drawing::Size(207, 50);
            this->groupBox5->TabIndex = 10;
            this->groupBox5->TabStop = false;
            this->groupBox5->Text = L"水质颜色";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(140, 21);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(17, 12);
            this->label3->TabIndex = 5;
            this->label3->Text = L"b:";
            // 
            // textBox1
            // 
            this->textBox1->Location = System::Drawing::Point(161, 18);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(31, 21);
            this->textBox1->TabIndex = 4;
            this->textBox1->Text = L"0.5";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Location = System::Drawing::Point(74, 21);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(17, 12);
            this->label4->TabIndex = 3;
            this->label4->Text = L"g:";
            // 
            // textBox2
            // 
            this->textBox2->Location = System::Drawing::Point(95, 18);
            this->textBox2->Name = L"textBox2";
            this->textBox2->Size = System::Drawing::Size(32, 21);
            this->textBox2->TabIndex = 2;
            this->textBox2->Text = L"0.5";
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Location = System::Drawing::Point(9, 21);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(17, 12);
            this->label7->TabIndex = 1;
            this->label7->Text = L"r:";
            // 
            // textBox3
            // 
            this->textBox3->Location = System::Drawing::Point(30, 18);
            this->textBox3->Name = L"textBox3";
            this->textBox3->Size = System::Drawing::Size(32, 21);
            this->textBox3->TabIndex = 0;
            this->textBox3->Text = L"0.5";
            // 
            // label17
            // 
            this->label17->AutoSize = true;
            this->label17->Location = System::Drawing::Point(140, 21);
            this->label17->Name = L"label17";
            this->label17->Size = System::Drawing::Size(17, 12);
            this->label17->TabIndex = 5;
            this->label17->Text = L"b:";
            // 
            // edit_waterDeepColorZ
            // 
            this->edit_waterDeepColorZ->Location = System::Drawing::Point(161, 18);
            this->edit_waterDeepColorZ->Name = L"edit_waterDeepColorZ";
            this->edit_waterDeepColorZ->Size = System::Drawing::Size(31, 21);
            this->edit_waterDeepColorZ->TabIndex = 4;
            this->edit_waterDeepColorZ->Text = L"0.5";
            // 
            // label18
            // 
            this->label18->AutoSize = true;
            this->label18->Location = System::Drawing::Point(74, 21);
            this->label18->Name = L"label18";
            this->label18->Size = System::Drawing::Size(17, 12);
            this->label18->TabIndex = 3;
            this->label18->Text = L"g:";
            // 
            // edit_waterDeepColorY
            // 
            this->edit_waterDeepColorY->Location = System::Drawing::Point(95, 18);
            this->edit_waterDeepColorY->Name = L"edit_waterDeepColorY";
            this->edit_waterDeepColorY->Size = System::Drawing::Size(32, 21);
            this->edit_waterDeepColorY->TabIndex = 2;
            this->edit_waterDeepColorY->Text = L"0.5";
            // 
            // label19
            // 
            this->label19->AutoSize = true;
            this->label19->Location = System::Drawing::Point(9, 21);
            this->label19->Name = L"label19";
            this->label19->Size = System::Drawing::Size(17, 12);
            this->label19->TabIndex = 1;
            this->label19->Text = L"r:";
            // 
            // edit_waterDeepColorX
            // 
            this->edit_waterDeepColorX->Location = System::Drawing::Point(30, 18);
            this->edit_waterDeepColorX->Name = L"edit_waterDeepColorX";
            this->edit_waterDeepColorX->Size = System::Drawing::Size(32, 21);
            this->edit_waterDeepColorX->TabIndex = 0;
            this->edit_waterDeepColorX->Text = L"0.5";
            // 
            // groupBox1
            // 
            this->groupBox1->Controls->Add(this->edit_waterBumpTexParamsW);
            this->groupBox1->Controls->Add(this->label23);
            this->groupBox1->Controls->Add(this->label5);
            this->groupBox1->Controls->Add(this->edit_waterBumpTexParamsY);
            this->groupBox1->Controls->Add(this->edit_waterBumpTexParamsZ);
            this->groupBox1->Controls->Add(this->label1);
            this->groupBox1->Controls->Add(this->label6);
            this->groupBox1->Controls->Add(this->edit_waterBumpTexParamsX);
            this->groupBox1->Location = System::Drawing::Point(289, 7);
            this->groupBox1->Name = L"groupBox1";
            this->groupBox1->Size = System::Drawing::Size(262, 71);
            this->groupBox1->TabIndex = 2;
            this->groupBox1->TabStop = false;
            this->groupBox1->Text = L"水波贴图参数";
            // 
            // edit_waterBumpTexParamsW
            // 
            this->edit_waterBumpTexParamsW->Location = System::Drawing::Point(211, 44);
            this->edit_waterBumpTexParamsW->Name = L"edit_waterBumpTexParamsW";
            this->edit_waterBumpTexParamsW->Size = System::Drawing::Size(32, 21);
            this->edit_waterBumpTexParamsW->TabIndex = 0;
            this->edit_waterBumpTexParamsW->Text = L"0.5";
            // 
            // label23
            // 
            this->label23->AutoSize = true;
            this->label23->Location = System::Drawing::Point(164, 47);
            this->label23->Name = L"label23";
            this->label23->Size = System::Drawing::Size(35, 12);
            this->label23->TabIndex = 1;
            this->label23->Text = L"尺寸:";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(158, 22);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(41, 12);
            this->label5->TabIndex = 3;
            this->label5->Text = L"y偏移:";
            // 
            // edit_waterBumpTexParamsY
            // 
            this->edit_waterBumpTexParamsY->Location = System::Drawing::Point(211, 17);
            this->edit_waterBumpTexParamsY->Name = L"edit_waterBumpTexParamsY";
            this->edit_waterBumpTexParamsY->Size = System::Drawing::Size(32, 21);
            this->edit_waterBumpTexParamsY->TabIndex = 2;
            this->edit_waterBumpTexParamsY->Text = L"0.5";
            // 
            // edit_waterBumpTexParamsZ
            // 
            this->edit_waterBumpTexParamsZ->Location = System::Drawing::Point(88, 45);
            this->edit_waterBumpTexParamsZ->Name = L"edit_waterBumpTexParamsZ";
            this->edit_waterBumpTexParamsZ->Size = System::Drawing::Size(32, 21);
            this->edit_waterBumpTexParamsZ->TabIndex = 0;
            this->edit_waterBumpTexParamsZ->Text = L"0.5";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(15, 49);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(35, 12);
            this->label1->TabIndex = 1;
            this->label1->Text = L"强弱:";
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(10, 23);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(41, 12);
            this->label6->TabIndex = 1;
            this->label6->Text = L"x偏移:";
            // 
            // edit_waterBumpTexParamsX
            // 
            this->edit_waterBumpTexParamsX->Location = System::Drawing::Point(88, 18);
            this->edit_waterBumpTexParamsX->Name = L"edit_waterBumpTexParamsX";
            this->edit_waterBumpTexParamsX->Size = System::Drawing::Size(32, 21);
            this->edit_waterBumpTexParamsX->TabIndex = 0;
            this->edit_waterBumpTexParamsX->Text = L"0.5";
            // 
            // groupBox2
            // 
            this->groupBox2->Controls->Add(this->label26);
            this->groupBox2->Controls->Add(this->edit_waterRefractScalsesW);
            this->groupBox2->Controls->Add(this->label12);
            this->groupBox2->Controls->Add(this->edit_waterRefractScalsesZ);
            this->groupBox2->Controls->Add(this->label9);
            this->groupBox2->Controls->Add(this->edit_waterRefractScalsesX);
            this->groupBox2->Controls->Add(this->label10);
            this->groupBox2->Controls->Add(this->edit_waterRefractScalsesY);
            this->groupBox2->Location = System::Drawing::Point(13, 237);
            this->groupBox2->Name = L"groupBox2";
            this->groupBox2->Size = System::Drawing::Size(262, 118);
            this->groupBox2->TabIndex = 3;
            this->groupBox2->TabStop = false;
            this->groupBox2->Text = L"折射";
            // 
            // label26
            // 
            this->label26->AutoSize = true;
            this->label26->Location = System::Drawing::Point(9, 95);
            this->label26->Name = L"label26";
            this->label26->Size = System::Drawing::Size(47, 12);
            this->label26->TabIndex = 7;
            this->label26->Text = L"未开放:";
            // 
            // edit_waterRefractScalsesW
            // 
            this->edit_waterRefractScalsesW->Location = System::Drawing::Point(219, 93);
            this->edit_waterRefractScalsesW->Name = L"edit_waterRefractScalsesW";
            this->edit_waterRefractScalsesW->Size = System::Drawing::Size(32, 21);
            this->edit_waterRefractScalsesW->TabIndex = 6;
            this->edit_waterRefractScalsesW->Text = L"0.5";
            // 
            // label12
            // 
            this->label12->AutoSize = true;
            this->label12->Location = System::Drawing::Point(9, 70);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(47, 12);
            this->label12->TabIndex = 5;
            this->label12->Text = L"未开放:";
            // 
            // edit_waterRefractScalsesZ
            // 
            this->edit_waterRefractScalsesZ->Location = System::Drawing::Point(219, 67);
            this->edit_waterRefractScalsesZ->Name = L"edit_waterRefractScalsesZ";
            this->edit_waterRefractScalsesZ->Size = System::Drawing::Size(32, 21);
            this->edit_waterRefractScalsesZ->TabIndex = 4;
            this->edit_waterRefractScalsesZ->Text = L"0.5";
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Location = System::Drawing::Point(9, 44);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(191, 12);
            this->label9->TabIndex = 3;
            this->label9->Text = L"水质色和反射色比例折射附加强弱:";
            // 
            // edit_waterRefractScalsesX
            // 
            this->edit_waterRefractScalsesX->Location = System::Drawing::Point(219, 16);
            this->edit_waterRefractScalsesX->Name = L"edit_waterRefractScalsesX";
            this->edit_waterRefractScalsesX->Size = System::Drawing::Size(32, 21);
            this->edit_waterRefractScalsesX->TabIndex = 2;
            this->edit_waterRefractScalsesX->Text = L"0.5";
            // 
            // label10
            // 
            this->label10->AutoSize = true;
            this->label10->Location = System::Drawing::Point(9, 19);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(155, 12);
            this->label10->TabIndex = 1;
            this->label10->Text = L"水质色和反射色比例基础值:";
            // 
            // edit_waterRefractScalsesY
            // 
            this->edit_waterRefractScalsesY->Location = System::Drawing::Point(219, 41);
            this->edit_waterRefractScalsesY->Name = L"edit_waterRefractScalsesY";
            this->edit_waterRefractScalsesY->Size = System::Drawing::Size(32, 21);
            this->edit_waterRefractScalsesY->TabIndex = 0;
            this->edit_waterRefractScalsesY->Text = L"0.5";
            // 
            // WaterEditor
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(798, 524);
            this->Controls->Add(this->panel2);
            this->Controls->Add(this->panel1);
            this->Name = L"WaterEditor";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"WaterEditor";
            this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &WaterEditor::WaterEditor_FormClosed);
            this->panel1->ResumeLayout(false);
            this->panel18->ResumeLayout(false);
            this->panel18->PerformLayout();
            this->panel2->ResumeLayout(false);
            this->groupBox3->ResumeLayout(false);
            this->groupBox3->PerformLayout();
            this->groupBox9->ResumeLayout(false);
            this->groupBox9->PerformLayout();
            this->groupBox6->ResumeLayout(false);
            this->groupBox6->PerformLayout();
            this->groupBox4->ResumeLayout(false);
            this->groupBox4->PerformLayout();
            this->groupBox5->ResumeLayout(false);
            this->groupBox5->PerformLayout();
            this->groupBox1->ResumeLayout(false);
            this->groupBox1->PerformLayout();
            this->groupBox2->ResumeLayout(false);
            this->groupBox2->PerformLayout();
            this->ResumeLayout(false);

        }
#pragma endregion
	private: System::Void WaterEditor_Confirm_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->onEventPressOK();
			 }
private: System::Void listView_WaterEffect_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 this->onEventPressListView();
			 }
private: System::Void WaterEditor_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				 this->closeForm();
			 }
private: System::Void WaterEditor_Save_Click(System::Object^  sender, System::EventArgs^  e) {
				this->onEventPressSave();
			}
private: System::Void WaterEditor_Reload_Click(System::Object^  sender, System::EventArgs^  e) {
				this->onEventPressReload();
			}
};
}
