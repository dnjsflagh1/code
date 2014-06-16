#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "XmlPropertySet.h"

namespace ModelEditor {

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
protected: 
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

        private: System::Windows::Forms::TabPage^  tabPage7;
        private: System::Windows::Forms::TrackBar^  trackBar1;
        private: System::Windows::Forms::TrackBar^  trackBar2;
        private: System::Windows::Forms::TabPage^  tabPage8;
        private: System::Windows::Forms::ListView^  listView1;
        private: System::Windows::Forms::TabControl^  tabControl1;
        private: System::Windows::Forms::TabPage^  tabPage2;
        private: System::Windows::Forms::TabPage^  tabPage3;
        private: System::Windows::Forms::TabPage^  tabPage4;
        private: System::Windows::Forms::TabPage^  tabPage5;
        private: System::Windows::Forms::TabPage^  tabPage6;
        private: System::Windows::Forms::MenuStrip^  menuStrip1;
        private: System::Windows::Forms::ToolStripMenuItem^  帮助ToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  关于ToolStripMenuItem;
        private: System::Windows::Forms::ToolStripMenuItem^  主题ToolStripMenuItem;
        private: System::Windows::Forms::StatusStrip^  statusStrip1;
        private: System::Windows::Forms::Panel^  base_panel;
        private: System::Windows::Forms::Splitter^  splitter1;
        private: System::Windows::Forms::Panel^  scene_base_panel;
        private: System::Windows::Forms::Panel^  scene_panel;
        private: System::Windows::Forms::Panel^  Prop_Panel;
        private: System::Windows::Forms::TabControl^  prop_tab_ctrl;
        private: System::Windows::Forms::TabPage^  elemet_page;
        private: System::Windows::Forms::ImageList^  imageList1;
        private: System::Windows::Forms::ImageList^  imageList2;
        private: System::Windows::Forms::ImageList^  terrain_texture_pic_list;
        private: System::Windows::Forms::Panel^  panel9;
        private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
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
            this->帮助ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->关于ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->主题ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
            this->base_panel = (gcnew System::Windows::Forms::Panel());
            this->splitter1 = (gcnew System::Windows::Forms::Splitter());
            this->scene_base_panel = (gcnew System::Windows::Forms::Panel());
            this->scene_panel = (gcnew System::Windows::Forms::Panel());
            this->Prop_Panel = (gcnew System::Windows::Forms::Panel());
            this->prop_tab_ctrl = (gcnew System::Windows::Forms::TabControl());
            this->elemet_page = (gcnew System::Windows::Forms::TabPage());
            this->panel9 = (gcnew System::Windows::Forms::Panel());
            this->imageList2 = (gcnew System::Windows::Forms::ImageList(this->components));
            this->terrain_texture_pic_list = (gcnew System::Windows::Forms::ImageList(this->components));
            this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
            this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
            this->tabPage7 = (gcnew System::Windows::Forms::TabPage());
            this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
            this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
            this->tabPage8 = (gcnew System::Windows::Forms::TabPage());
            this->menuStrip1->SuspendLayout();
            this->base_panel->SuspendLayout();
            this->scene_base_panel->SuspendLayout();
            this->Prop_Panel->SuspendLayout();
            this->prop_tab_ctrl->SuspendLayout();
            this->elemet_page->SuspendLayout();
            this->tabPage7->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->BeginInit();
            this->SuspendLayout();
            // 
            // menuStrip1
            // 
            this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->帮助ToolStripMenuItem});
            this->menuStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
            this->menuStrip1->Location = System::Drawing::Point(0, 0);
            this->menuStrip1->Name = L"menuStrip1";
            this->menuStrip1->Size = System::Drawing::Size(1192, 24);
            this->menuStrip1->TabIndex = 1;
            this->menuStrip1->Text = L"menuStrip1";
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
            this->关于ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
            this->关于ToolStripMenuItem->Text = L"关于";
            // 
            // 主题ToolStripMenuItem
            // 
            this->主题ToolStripMenuItem->Name = L"主题ToolStripMenuItem";
            this->主题ToolStripMenuItem->Size = System::Drawing::Size(152, 22);
            this->主题ToolStripMenuItem->Text = L"主题";
            // 
            // statusStrip1
            // 
            this->statusStrip1->Location = System::Drawing::Point(0, 744);
            this->statusStrip1->Name = L"statusStrip1";
            this->statusStrip1->Size = System::Drawing::Size(1192, 22);
            this->statusStrip1->TabIndex = 2;
            this->statusStrip1->Text = L"statusStrip1";
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
            this->scene_panel->Size = System::Drawing::Size(926, 716);
            this->scene_panel->TabIndex = 2;
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
            this->prop_tab_ctrl->Dock = System::Windows::Forms::DockStyle::Fill;
            this->prop_tab_ctrl->Location = System::Drawing::Point(0, 0);
            this->prop_tab_ctrl->Name = L"prop_tab_ctrl";
            this->prop_tab_ctrl->SelectedIndex = 0;
            this->prop_tab_ctrl->Size = System::Drawing::Size(258, 716);
            this->prop_tab_ctrl->TabIndex = 0;
            // 
            // elemet_page
            // 
            this->elemet_page->Controls->Add(this->panel9);
            this->elemet_page->Location = System::Drawing::Point(4, 21);
            this->elemet_page->Name = L"elemet_page";
            this->elemet_page->Padding = System::Windows::Forms::Padding(3);
            this->elemet_page->Size = System::Drawing::Size(250, 691);
            this->elemet_page->TabIndex = 3;
            this->elemet_page->Text = L"模型列表";
            this->elemet_page->UseVisualStyleBackColor = true;
            // 
            // panel9
            // 
            this->panel9->BackColor = System::Drawing::SystemColors::Control;
            this->panel9->Dock = System::Windows::Forms::DockStyle::Fill;
            this->panel9->Location = System::Drawing::Point(3, 3);
            this->panel9->Name = L"panel9";
            this->panel9->Size = System::Drawing::Size(244, 685);
            this->panel9->TabIndex = 1;
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
            this->Text = L"ModelEditor";
            this->Move += gcnew System::EventHandler(this, &MainForm::MainForm_Move);
            this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
            this->menuStrip1->ResumeLayout(false);
            this->menuStrip1->PerformLayout();
            this->base_panel->ResumeLayout(false);
            this->scene_base_panel->ResumeLayout(false);
            this->Prop_Panel->ResumeLayout(false);
            this->prop_tab_ctrl->ResumeLayout(false);
            this->elemet_page->ResumeLayout(false);
            this->tabPage7->ResumeLayout(false);
            this->tabPage7->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
        private: System::Void MainForm_Move(System::Object^  sender, System::EventArgs^  e) {
                    this->setSceneFormLocation();
                }
        private: System::Void MainForm_Resize(System::Object^  sender, System::EventArgs^  e) {
                 this->setSceneFormLocation();
                }
};
}
