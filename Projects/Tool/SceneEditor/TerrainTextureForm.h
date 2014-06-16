#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace SceneEditor {

	/// <summary>
	/// Summary for TerrainTextureForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class TerrainTextureForm : public System::Windows::Forms::Form
	{
	public:
		TerrainTextureForm(void)
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
		~TerrainTextureForm()
		{
			if (components)
			{
				delete components;
			}
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
        void    refresh();

        /////////////////////////////////////////////////////////////////////////

        // 加载总的场景地形贴图列表
        void    loadTotalTerrainTextureList();
        // 选择当前总贴图
        void    selectTotalTerrainTextureList();

        /////////////////////////////////////////////////////////////////////////

        // 加载当前场景地形贴图列表
        void    loadCurrSceneTerrainTextureList();
        // 选择当前场景贴图
        void    selectCurrSceneTerrainTextureList();

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
        private: System::Windows::Forms::Panel^  panel1;
        private: System::Windows::Forms::Panel^  panel4;
        private: System::Windows::Forms::TreeView^  treeView_globle_terrain_tex_list;
        private: System::Windows::Forms::Panel^  panel3;
        private: System::Windows::Forms::Splitter^  splitter1;
        private: System::Windows::Forms::Panel^  panel2;
        private: System::Windows::Forms::Label^  label1;
        private: System::Windows::Forms::Panel^  panel7;
        private: System::Windows::Forms::TreeView^  treeView_scene_terrain_tex_list;
        private: System::Windows::Forms::Panel^  panel6;
        private: System::Windows::Forms::Button^  button2;
        private: System::Windows::Forms::Button^  button1;
        private: System::Windows::Forms::Panel^  panel5;
        private: System::Windows::Forms::Label^  label2;

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->panel4 = (gcnew System::Windows::Forms::Panel());
            this->treeView_globle_terrain_tex_list = (gcnew System::Windows::Forms::TreeView());
            this->panel3 = (gcnew System::Windows::Forms::Panel());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->splitter1 = (gcnew System::Windows::Forms::Splitter());
            this->panel2 = (gcnew System::Windows::Forms::Panel());
            this->panel7 = (gcnew System::Windows::Forms::Panel());
            this->treeView_scene_terrain_tex_list = (gcnew System::Windows::Forms::TreeView());
            this->panel6 = (gcnew System::Windows::Forms::Panel());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->panel5 = (gcnew System::Windows::Forms::Panel());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->panel1->SuspendLayout();
            this->panel4->SuspendLayout();
            this->panel3->SuspendLayout();
            this->panel2->SuspendLayout();
            this->panel7->SuspendLayout();
            this->panel6->SuspendLayout();
            this->panel5->SuspendLayout();
            this->SuspendLayout();
            // 
            // panel1
            // 
            this->panel1->Controls->Add(this->panel4);
            this->panel1->Controls->Add(this->panel3);
            this->panel1->Dock = System::Windows::Forms::DockStyle::Left;
            this->panel1->Location = System::Drawing::Point(0, 0);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(343, 457);
            this->panel1->TabIndex = 0;
            // 
            // panel4
            // 
            this->panel4->Controls->Add(this->treeView_globle_terrain_tex_list);
            this->panel4->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panel4->Location = System::Drawing::Point(0, 37);
            this->panel4->Name = L"panel4";
            this->panel4->Size = System::Drawing::Size(343, 420);
            this->panel4->TabIndex = 2;
            // 
            // treeView_globle_terrain_tex_list
            // 
            this->treeView_globle_terrain_tex_list->Dock = System::Windows::Forms::DockStyle::Fill;
            this->treeView_globle_terrain_tex_list->Location = System::Drawing::Point(0, 0);
            this->treeView_globle_terrain_tex_list->Name = L"treeView_globle_terrain_tex_list";
            this->treeView_globle_terrain_tex_list->Size = System::Drawing::Size(343, 420);
            this->treeView_globle_terrain_tex_list->TabIndex = 1;
            this->treeView_globle_terrain_tex_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &TerrainTextureForm::treeView_globle_terrain_tex_list_MouseDoubleClick);
            // 
            // panel3
            // 
            this->panel3->Controls->Add(this->label1);
            this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel3->Location = System::Drawing::Point(0, 0);
            this->panel3->Name = L"panel3";
            this->panel3->Size = System::Drawing::Size(343, 37);
            this->panel3->TabIndex = 1;
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(90, 12);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(125, 12);
            this->label1->TabIndex = 0;
            this->label1->Text = L"<地形贴图总资源列表>";
            // 
            // splitter1
            // 
            this->splitter1->Location = System::Drawing::Point(343, 0);
            this->splitter1->Name = L"splitter1";
            this->splitter1->Size = System::Drawing::Size(3, 457);
            this->splitter1->TabIndex = 1;
            this->splitter1->TabStop = false;
            // 
            // panel2
            // 
            this->panel2->Controls->Add(this->panel7);
            this->panel2->Controls->Add(this->panel6);
            this->panel2->Controls->Add(this->panel5);
            this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panel2->Location = System::Drawing::Point(346, 0);
            this->panel2->Name = L"panel2";
            this->panel2->Size = System::Drawing::Size(360, 457);
            this->panel2->TabIndex = 2;
            // 
            // panel7
            // 
            this->panel7->Controls->Add(this->treeView_scene_terrain_tex_list);
            this->panel7->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panel7->Location = System::Drawing::Point(0, 37);
            this->panel7->Name = L"panel7";
            this->panel7->Size = System::Drawing::Size(360, 382);
            this->panel7->TabIndex = 2;
            // 
            // treeView_scene_terrain_tex_list
            // 
            this->treeView_scene_terrain_tex_list->Dock = System::Windows::Forms::DockStyle::Fill;
            this->treeView_scene_terrain_tex_list->Location = System::Drawing::Point(0, 0);
            this->treeView_scene_terrain_tex_list->Name = L"treeView_scene_terrain_tex_list";
            this->treeView_scene_terrain_tex_list->Size = System::Drawing::Size(360, 382);
            this->treeView_scene_terrain_tex_list->TabIndex = 0;
            this->treeView_scene_terrain_tex_list->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &TerrainTextureForm::treeView_scene_terrain_tex_list_MouseDoubleClick);
            // 
            // panel6
            // 
            this->panel6->Controls->Add(this->button2);
            this->panel6->Controls->Add(this->button1);
            this->panel6->Dock = System::Windows::Forms::DockStyle::Bottom;
            this->panel6->Location = System::Drawing::Point(0, 419);
            this->panel6->Name = L"panel6";
            this->panel6->Size = System::Drawing::Size(360, 38);
            this->panel6->TabIndex = 1;
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(250, 6);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(75, 23);
            this->button2->TabIndex = 1;
            this->button2->Text = L"移除";
            this->button2->UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(169, 6);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(75, 23);
            this->button1->TabIndex = 0;
            this->button1->Text = L"获取";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &TerrainTextureForm::button1_Click);
            // 
            // panel5
            // 
            this->panel5->Controls->Add(this->label2);
            this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel5->Location = System::Drawing::Point(0, 0);
            this->panel5->Name = L"panel5";
            this->panel5->Size = System::Drawing::Size(360, 37);
            this->panel5->TabIndex = 0;
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(108, 12);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(161, 12);
            this->label2->TabIndex = 1;
            this->label2->Text = L"<当前场景地形贴图资源列表>";
            // 
            // TerrainTextureForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(706, 457);
            this->Controls->Add(this->panel2);
            this->Controls->Add(this->splitter1);
            this->Controls->Add(this->panel1);
            this->Name = L"TerrainTextureForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"TerrainTextureForm";
            this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &TerrainTextureForm::TerrainTextureForm_FormClosed);
            this->panel1->ResumeLayout(false);
            this->panel4->ResumeLayout(false);
            this->panel3->ResumeLayout(false);
            this->panel3->PerformLayout();
            this->panel2->ResumeLayout(false);
            this->panel7->ResumeLayout(false);
            this->panel6->ResumeLayout(false);
            this->panel5->ResumeLayout(false);
            this->panel5->PerformLayout();
            this->ResumeLayout(false);

        }
#pragma endregion
    private: System::Void TerrainTextureForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
                 this->closeForm();
             }
    private: System::Void treeView_scene_terrain_tex_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                 this->selectCurrSceneTerrainTextureList();
             }
    private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
                 this->selectCurrSceneTerrainTextureList();
             }
    private: System::Void treeView_globle_terrain_tex_list_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
                 this->selectTotalTerrainTextureList();
             }
};
}
