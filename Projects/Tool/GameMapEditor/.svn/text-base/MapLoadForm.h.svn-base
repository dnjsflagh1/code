#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace GameMapEditor {

	/// <summary>
	/// Summary for MapLoadForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class MapLoadForm : public System::Windows::Forms::Form
	{
	public:
		MapLoadForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	public:

		///初始化
		void    initialize();
		///反初始化
		void    unInitialize();
		///开始加载地图
		void	loadMap();

	public:

		///打开窗口
		DELEGATEFUNC(openForm)();
		void	openForm();
		///关闭窗口
		DELEGATEFUNC(closeForm)();
		void    closeForm();

	private:

		//加载ArtMapRes中的所有文件
		DELEGATEFUNC(loadMapList)();
		void loadMapList();

		//准备加载地图
		DELEGATEFUNC(prepareLoadingMap)();
		void prepareLoadingMap();

	private:

		I32 mCurrMapID;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MapLoadForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TreeView^  map_info_tree_view;
	private: System::Windows::Forms::Panel^  panel14;
	private: System::Windows::Forms::Label^  prepare_load_map_text;

	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::Button^  button_ok;

	protected: 

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
			this->map_info_tree_view = (gcnew System::Windows::Forms::TreeView());
			this->panel14 = (gcnew System::Windows::Forms::Panel());
			this->prepare_load_map_text = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->button_ok = (gcnew System::Windows::Forms::Button());
			this->panel14->SuspendLayout();
			this->SuspendLayout();
			// 
			// map_info_tree_view
			// 
			this->map_info_tree_view->Dock = System::Windows::Forms::DockStyle::Top;
			this->map_info_tree_view->Location = System::Drawing::Point(0, 0);
			this->map_info_tree_view->Name = L"map_info_tree_view";
			this->map_info_tree_view->Size = System::Drawing::Size(305, 308);
			this->map_info_tree_view->TabIndex = 2;
			this->map_info_tree_view->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MapLoadForm::map_list_tree_view_DoubleClicked);
			this->map_info_tree_view->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MapLoadForm::map_info_tree_view_AfterSelect);
			// 
			// panel14
			// 
			this->panel14->Controls->Add(this->prepare_load_map_text);
			this->panel14->Controls->Add(this->label23);
			this->panel14->Controls->Add(this->button_ok);
			this->panel14->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel14->Location = System::Drawing::Point(0, 310);
			this->panel14->Name = L"panel14";
			this->panel14->Size = System::Drawing::Size(305, 119);
			this->panel14->TabIndex = 3;
			// 
			// prepare_load_map_text
			// 
			this->prepare_load_map_text->AutoEllipsis = true;
			this->prepare_load_map_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->prepare_load_map_text->Location = System::Drawing::Point(11, 30);
			this->prepare_load_map_text->Name = L"prepare_load_map_text";
			this->prepare_load_map_text->Size = System::Drawing::Size(281, 80);
			this->prepare_load_map_text->TabIndex = 3;
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(9, 9);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(113, 12);
			this->label23->TabIndex = 2;
			this->label23->Text = L"当前选择的地图信息";
			// 
			// button_ok
			// 
			this->button_ok->Location = System::Drawing::Point(231, 4);
			this->button_ok->Name = L"button_ok";
			this->button_ok->Size = System::Drawing::Size(61, 23);
			this->button_ok->TabIndex = 1;
			this->button_ok->Text = L"确定";
			this->button_ok->UseVisualStyleBackColor = true;
			this->button_ok->Click += gcnew System::EventHandler(this, &MapLoadForm::button_confirm_clicked);
			// 
			// MapLoadForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(305, 429);
			this->Controls->Add(this->panel14);
			this->Controls->Add(this->map_info_tree_view);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MapLoadForm";
			this->Text = L"MapLoadForm";
			this->panel14->ResumeLayout(false);
			this->panel14->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

		//////////////////////////////////////////////////////////////////////////
		//Event
		//////////////////////////////////////////////////////////////////////////
	private: System::Void button_confirm_clicked(System::Object^  sender, System::EventArgs^  e) {
				 this->loadMap();
		 }
	private: System::Void map_list_tree_view_DoubleClicked(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if ( map_info_tree_view->SelectedNode != nullptr &&
					 map_info_tree_view->SelectedNode->Tag != nullptr )
				 {
					this->loadMap();
				 }
		 }

private: System::Void map_info_tree_view_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) {
			 this->prepareLoadingMap();
		 }
};
}
