#pragma once


namespace PackTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

    //######################################################################################################
    // 【主方法】
    //######################################################################################################

    /// 选择源目录
    DELEGATEFUNC(selectSrcFolder)();
    void    selectSrcFolder();
    /// 选择目标目录
    DELEGATEFUNC(selectDestFolder)();
    void    selectDestFolder();

    /// 开始打包
    DELEGATEFUNC(startPack)();
    void    startPack();

    ///上次关注的场景文件目录
    String^ mSrcDir;
    String^ mDestDir;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::Panel^  panel1;
    private: System::Windows::Forms::Panel^  panel2;
    private: System::Windows::Forms::Button^  button5;
    private: System::Windows::Forms::Label^  src_folder;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Button^  button1;
    private: System::Windows::Forms::Label^  dest_folder;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::Panel^  panel3;
    private: System::Windows::Forms::TreeView^  src_list;
    private: System::Windows::Forms::Panel^  panel4;
    private: System::Windows::Forms::TreeView^  des_list;
    private: System::Windows::Forms::Button^  button2;
    private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;

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
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->panel3 = (gcnew System::Windows::Forms::Panel());
            this->src_list = (gcnew System::Windows::Forms::TreeView());
            this->button5 = (gcnew System::Windows::Forms::Button());
            this->src_folder = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->panel2 = (gcnew System::Windows::Forms::Panel());
            this->panel4 = (gcnew System::Windows::Forms::Panel());
            this->des_list = (gcnew System::Windows::Forms::TreeView());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->dest_folder = (gcnew System::Windows::Forms::Label());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
            this->panel1->SuspendLayout();
            this->panel3->SuspendLayout();
            this->panel2->SuspendLayout();
            this->panel4->SuspendLayout();
            this->SuspendLayout();
            // 
            // panel1
            // 
            this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panel1->Controls->Add(this->panel3);
            this->panel1->Controls->Add(this->button5);
            this->panel1->Controls->Add(this->src_folder);
            this->panel1->Controls->Add(this->label2);
            this->panel1->Location = System::Drawing::Point(12, 12);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(191, 370);
            this->panel1->TabIndex = 0;
            // 
            // panel3
            // 
            this->panel3->Controls->Add(this->src_list);
            this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel3->Location = System::Drawing::Point(0, 0);
            this->panel3->Name = L"panel3";
            this->panel3->Size = System::Drawing::Size(189, 243);
            this->panel3->TabIndex = 13;
            // 
            // src_list
            // 
            this->src_list->AllowDrop = true;
            this->src_list->Dock = System::Windows::Forms::DockStyle::Fill;
            this->src_list->Location = System::Drawing::Point(0, 0);
            this->src_list->Name = L"src_list";
            this->src_list->Size = System::Drawing::Size(189, 243);
            this->src_list->TabIndex = 3;
            // 
            // button5
            // 
            this->button5->Location = System::Drawing::Point(7, 333);
            this->button5->Name = L"button5";
            this->button5->Size = System::Drawing::Size(175, 23);
            this->button5->TabIndex = 12;
            this->button5->Text = L"选择源散包目录";
            this->button5->UseVisualStyleBackColor = true;
            this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
            // 
            // src_folder
            // 
            this->src_folder->AutoEllipsis = true;
            this->src_folder->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->src_folder->Location = System::Drawing::Point(7, 285);
            this->src_folder->Name = L"src_folder";
            this->src_folder->Size = System::Drawing::Size(175, 37);
            this->src_folder->TabIndex = 11;
            this->src_folder->Text = L"XXXX";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(3, 259);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(71, 12);
            this->label2->TabIndex = 10;
            this->label2->Text = L"源散包目录:";
            // 
            // panel2
            // 
            this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panel2->Controls->Add(this->panel4);
            this->panel2->Controls->Add(this->button1);
            this->panel2->Controls->Add(this->dest_folder);
            this->panel2->Controls->Add(this->label1);
            this->panel2->Location = System::Drawing::Point(221, 12);
            this->panel2->Name = L"panel2";
            this->panel2->Size = System::Drawing::Size(191, 370);
            this->panel2->TabIndex = 1;
            // 
            // panel4
            // 
            this->panel4->Controls->Add(this->des_list);
            this->panel4->Dock = System::Windows::Forms::DockStyle::Top;
            this->panel4->Location = System::Drawing::Point(0, 0);
            this->panel4->Name = L"panel4";
            this->panel4->Size = System::Drawing::Size(189, 243);
            this->panel4->TabIndex = 16;
            // 
            // des_list
            // 
            this->des_list->AllowDrop = true;
            this->des_list->Dock = System::Windows::Forms::DockStyle::Fill;
            this->des_list->Location = System::Drawing::Point(0, 0);
            this->des_list->Name = L"des_list";
            this->des_list->Size = System::Drawing::Size(189, 243);
            this->des_list->TabIndex = 3;
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(6, 334);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(175, 23);
            this->button1->TabIndex = 15;
            this->button1->Text = L"选择压缩包存放目录";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
            // 
            // dest_folder
            // 
            this->dest_folder->AutoEllipsis = true;
            this->dest_folder->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->dest_folder->Location = System::Drawing::Point(6, 285);
            this->dest_folder->Name = L"dest_folder";
            this->dest_folder->Size = System::Drawing::Size(175, 37);
            this->dest_folder->TabIndex = 14;
            this->dest_folder->Text = L"XXXX";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(3, 260);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(95, 12);
            this->label1->TabIndex = 13;
            this->label1->Text = L"压缩包存放目录:";
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(12, 388);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(399, 51);
            this->button2->TabIndex = 16;
            this->button2->Text = L"开始压缩";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
            // 
            // Form1
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(428, 450);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->panel2);
            this->Controls->Add(this->panel1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
            this->Name = L"Form1";
            this->Text = L"PackTool";
            this->panel1->ResumeLayout(false);
            this->panel1->PerformLayout();
            this->panel3->ResumeLayout(false);
            this->panel2->ResumeLayout(false);
            this->panel2->PerformLayout();
            this->panel4->ResumeLayout(false);
            this->ResumeLayout(false);

        }
#pragma endregion
    private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
                this->selectSrcFolder();
             }
    private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
                this->selectDestFolder();            
             }
    private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
                this->startPack();    
             }
};
}

