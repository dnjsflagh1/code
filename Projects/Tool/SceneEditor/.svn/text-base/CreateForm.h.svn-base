#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace SceneEditor {

	enum 
	{
		SMALLBATCH, //小批次
		BIGBATCH    //大批次
	};

	enum 
	{
		SLG,        //SLG地图
		RPG,        //RPG地图
		INTEGRATED  //综合地图
	};

	/// <summary>
	/// Summary for CreateForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CreateForm : public System::Windows::Forms::Form
	{
	public:
		CreateForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	public:
		///初始化
		void initialize();
		///反初始化
		void unInitialize();
		///关闭
		void closeForm();
		///验证参数合法性
		void validateForm();

	public:

		///重置部分窗口
		void refreshForm();

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CreateForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TextBox^  TextBox_MapNameEN;


	protected: 

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  TextBox_MapNameCN;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ComboBox^  ComboBox_MapSize;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  ComboBox_UnitLength;


	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::ComboBox^  ComboBox_ChunkNum;



	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::ComboBox^  ComboBox_MaxHeight;

	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::ComboBox^  ComboBox_MinHeight;


	private: System::Windows::Forms::Label^  label8;


	private: System::Windows::Forms::Button^  cancel;

	private: System::Windows::Forms::Button^  confirm;


	private: System::Windows::Forms::RadioButton^  RadioButton_IntegratedMap;

	private: System::Windows::Forms::RadioButton^  RadioButton_RPGMap;

	private: System::Windows::Forms::RadioButton^  RadioButton_SLGMap;


	private: System::Windows::Forms::RadioButton^  RadioButton_SmallBatch;

	private: System::Windows::Forms::RadioButton^  RadioButton_BigBatch;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Panel^  panel2;



	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::ComboBox^  ComboBox_TileSize;

	private: System::Windows::Forms::Label^  label16;









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
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->ComboBox_TileSize = (gcnew System::Windows::Forms::ComboBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->ComboBox_MapSize = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->ComboBox_UnitLength = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->ComboBox_ChunkNum = (gcnew System::Windows::Forms::ComboBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->ComboBox_MinHeight = (gcnew System::Windows::Forms::ComboBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->ComboBox_MaxHeight = (gcnew System::Windows::Forms::ComboBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->RadioButton_IntegratedMap = (gcnew System::Windows::Forms::RadioButton());
			this->RadioButton_SLGMap = (gcnew System::Windows::Forms::RadioButton());
			this->RadioButton_RPGMap = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->RadioButton_SmallBatch = (gcnew System::Windows::Forms::RadioButton());
			this->RadioButton_BigBatch = (gcnew System::Windows::Forms::RadioButton());
			this->cancel = (gcnew System::Windows::Forms::Button());
			this->confirm = (gcnew System::Windows::Forms::Button());
			this->TextBox_MapNameCN = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->TextBox_MapNameEN = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->panel2);
			this->panel1->Controls->Add(this->groupBox2);
			this->panel1->Controls->Add(this->groupBox1);
			this->panel1->Controls->Add(this->cancel);
			this->panel1->Controls->Add(this->confirm);
			this->panel1->Controls->Add(this->TextBox_MapNameCN);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->TextBox_MapNameEN);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(330, 343);
			this->panel1->TabIndex = 0;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->label15);
			this->panel2->Controls->Add(this->ComboBox_TileSize);
			this->panel2->Controls->Add(this->label16);
			this->panel2->Controls->Add(this->ComboBox_MapSize);
			this->panel2->Controls->Add(this->label3);
			this->panel2->Controls->Add(this->ComboBox_UnitLength);
			this->panel2->Controls->Add(this->label4);
			this->panel2->Controls->Add(this->label6);
			this->panel2->Controls->Add(this->label11);
			this->panel2->Controls->Add(this->label5);
			this->panel2->Controls->Add(this->ComboBox_ChunkNum);
			this->panel2->Controls->Add(this->label8);
			this->panel2->Controls->Add(this->label12);
			this->panel2->Controls->Add(this->ComboBox_MinHeight);
			this->panel2->Controls->Add(this->label9);
			this->panel2->Controls->Add(this->label7);
			this->panel2->Controls->Add(this->ComboBox_MaxHeight);
			this->panel2->Controls->Add(this->label10);
			this->panel2->Location = System::Drawing::Point(2, 65);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(306, 117);
			this->panel2->TabIndex = 25;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(284, 90);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(17, 12);
			this->label15->TabIndex = 24;
			this->label15->Text = L"格";
			// 
			// ComboBox_TileSize
			// 
			this->ComboBox_TileSize->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComboBox_TileSize->Enabled = false;
			this->ComboBox_TileSize->FormattingEnabled = true;
			this->ComboBox_TileSize->Location = System::Drawing::Point(219, 87);
			this->ComboBox_TileSize->Name = L"ComboBox_TileSize";
			this->ComboBox_TileSize->Size = System::Drawing::Size(59, 20);
			this->ComboBox_TileSize->TabIndex = 22;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(160, 90);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(53, 12);
			this->label16->TabIndex = 23;
			this->label16->Text = L"Tile大小";
			// 
			// ComboBox_MapSize
			// 
			this->ComboBox_MapSize->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComboBox_MapSize->FormattingEnabled = true;
			this->ComboBox_MapSize->Location = System::Drawing::Point(70, 9);
			this->ComboBox_MapSize->Name = L"ComboBox_MapSize";
			this->ComboBox_MapSize->Size = System::Drawing::Size(59, 20);
			this->ComboBox_MapSize->TabIndex = 3;
			this->ComboBox_MapSize->SelectedIndexChanged += gcnew System::EventHandler(this, &CreateForm::ComboBox_MapSize_SelectedIndexChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(160, 12);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 12);
			this->label3->TabIndex = 4;
			this->label3->Text = L"每格边长";
			// 
			// ComboBox_UnitLength
			// 
			this->ComboBox_UnitLength->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComboBox_UnitLength->FormattingEnabled = true;
			this->ComboBox_UnitLength->Location = System::Drawing::Point(219, 9);
			this->ComboBox_UnitLength->Name = L"ComboBox_UnitLength";
			this->ComboBox_UnitLength->Size = System::Drawing::Size(59, 20);
			this->ComboBox_UnitLength->TabIndex = 2;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(284, 12);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(17, 12);
			this->label4->TabIndex = 6;
			this->label4->Text = L"米";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(11, 12);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(53, 12);
			this->label6->TabIndex = 7;
			this->label6->Text = L"地图大小";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(135, 90);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(17, 12);
			this->label11->TabIndex = 18;
			this->label11->Text = L"块";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(135, 12);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(17, 12);
			this->label5->TabIndex = 9;
			this->label5->Text = L"格";
			// 
			// ComboBox_ChunkNum
			// 
			this->ComboBox_ChunkNum->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComboBox_ChunkNum->Enabled = false;
			this->ComboBox_ChunkNum->FormattingEnabled = true;
			this->ComboBox_ChunkNum->Location = System::Drawing::Point(70, 87);
			this->ComboBox_ChunkNum->Name = L"ComboBox_ChunkNum";
			this->ComboBox_ChunkNum->Size = System::Drawing::Size(59, 20);
			this->ComboBox_ChunkNum->TabIndex = 6;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(11, 38);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(53, 12);
			this->label8->TabIndex = 10;
			this->label8->Text = L"最低海拔";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(11, 90);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(59, 12);
			this->label12->TabIndex = 16;
			this->label12->Text = L"chunk数量";
			// 
			// ComboBox_MinHeight
			// 
			this->ComboBox_MinHeight->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComboBox_MinHeight->FormattingEnabled = true;
			this->ComboBox_MinHeight->Location = System::Drawing::Point(70, 35);
			this->ComboBox_MinHeight->Name = L"ComboBox_MinHeight";
			this->ComboBox_MinHeight->Size = System::Drawing::Size(59, 20);
			this->ComboBox_MinHeight->TabIndex = 4;
			this->ComboBox_MinHeight->SelectedIndexChanged += gcnew System::EventHandler(this, &CreateForm::ComboBox_MinHeight_SelectedIndexChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(135, 64);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(17, 12);
			this->label9->TabIndex = 15;
			this->label9->Text = L"米";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(135, 38);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(17, 12);
			this->label7->TabIndex = 12;
			this->label7->Text = L"米";
			// 
			// ComboBox_MaxHeight
			// 
			this->ComboBox_MaxHeight->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ComboBox_MaxHeight->Enabled = false;
			this->ComboBox_MaxHeight->FormattingEnabled = true;
			this->ComboBox_MaxHeight->Location = System::Drawing::Point(70, 61);
			this->ComboBox_MaxHeight->Name = L"ComboBox_MaxHeight";
			this->ComboBox_MaxHeight->Size = System::Drawing::Size(59, 20);
			this->ComboBox_MaxHeight->TabIndex = 5;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(11, 64);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(53, 12);
			this->label10->TabIndex = 13;
			this->label10->Text = L"最高海拔";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->RadioButton_IntegratedMap);
			this->groupBox2->Controls->Add(this->RadioButton_SLGMap);
			this->groupBox2->Controls->Add(this->RadioButton_RPGMap);
			this->groupBox2->Location = System::Drawing::Point(186, 188);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(84, 91);
			this->groupBox2->TabIndex = 24;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"地图类型";
			// 
			// RadioButton_IntegratedMap
			// 
			this->RadioButton_IntegratedMap->AutoSize = true;
			this->RadioButton_IntegratedMap->Location = System::Drawing::Point(6, 67);
			this->RadioButton_IntegratedMap->Name = L"RadioButton_IntegratedMap";
			this->RadioButton_IntegratedMap->Size = System::Drawing::Size(71, 16);
			this->RadioButton_IntegratedMap->TabIndex = 11;
			this->RadioButton_IntegratedMap->TabStop = true;
			this->RadioButton_IntegratedMap->Text = L"综合地图";
			this->RadioButton_IntegratedMap->UseVisualStyleBackColor = true;
			// 
			// RadioButton_SLGMap
			// 
			this->RadioButton_SLGMap->AutoSize = true;
			this->RadioButton_SLGMap->Location = System::Drawing::Point(6, 24);
			this->RadioButton_SLGMap->Name = L"RadioButton_SLGMap";
			this->RadioButton_SLGMap->Size = System::Drawing::Size(65, 16);
			this->RadioButton_SLGMap->TabIndex = 9;
			this->RadioButton_SLGMap->TabStop = true;
			this->RadioButton_SLGMap->Text = L"SLG地图";
			this->RadioButton_SLGMap->UseVisualStyleBackColor = true;
			// 
			// RadioButton_RPGMap
			// 
			this->RadioButton_RPGMap->AutoSize = true;
			this->RadioButton_RPGMap->Location = System::Drawing::Point(6, 46);
			this->RadioButton_RPGMap->Name = L"RadioButton_RPGMap";
			this->RadioButton_RPGMap->Size = System::Drawing::Size(65, 16);
			this->RadioButton_RPGMap->TabIndex = 10;
			this->RadioButton_RPGMap->TabStop = true;
			this->RadioButton_RPGMap->Text = L"RPG地图";
			this->RadioButton_RPGMap->UseVisualStyleBackColor = true;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->RadioButton_SmallBatch);
			this->groupBox1->Controls->Add(this->RadioButton_BigBatch);
			this->groupBox1->Location = System::Drawing::Point(27, 188);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(84, 65);
			this->groupBox1->TabIndex = 23;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"批处理";
			// 
			// RadioButton_SmallBatch
			// 
			this->RadioButton_SmallBatch->AutoSize = true;
			this->RadioButton_SmallBatch->Location = System::Drawing::Point(6, 42);
			this->RadioButton_SmallBatch->Name = L"RadioButton_SmallBatch";
			this->RadioButton_SmallBatch->Size = System::Drawing::Size(71, 16);
			this->RadioButton_SmallBatch->TabIndex = 8;
			this->RadioButton_SmallBatch->TabStop = true;
			this->RadioButton_SmallBatch->Text = L"小批次组";
			this->RadioButton_SmallBatch->UseVisualStyleBackColor = true;
			// 
			// RadioButton_BigBatch
			// 
			this->RadioButton_BigBatch->AutoSize = true;
			this->RadioButton_BigBatch->Location = System::Drawing::Point(6, 20);
			this->RadioButton_BigBatch->Name = L"RadioButton_BigBatch";
			this->RadioButton_BigBatch->Size = System::Drawing::Size(71, 16);
			this->RadioButton_BigBatch->TabIndex = 7;
			this->RadioButton_BigBatch->TabStop = true;
			this->RadioButton_BigBatch->Text = L"大批次组";
			this->RadioButton_BigBatch->UseVisualStyleBackColor = true;
			// 
			// cancel
			// 
			this->cancel->Location = System::Drawing::Point(179, 302);
			this->cancel->Name = L"cancel";
			this->cancel->Size = System::Drawing::Size(75, 23);
			this->cancel->TabIndex = 13;
			this->cancel->Text = L"取消";
			this->cancel->UseVisualStyleBackColor = true;
			this->cancel->Click += gcnew System::EventHandler(this, &CreateForm::cancel_Click);
			// 
			// confirm
			// 
			this->confirm->Location = System::Drawing::Point(36, 302);
			this->confirm->Name = L"confirm";
			this->confirm->Size = System::Drawing::Size(75, 23);
			this->confirm->TabIndex = 12;
			this->confirm->Text = L"确定";
			this->confirm->UseVisualStyleBackColor = true;
			this->confirm->Click += gcnew System::EventHandler(this, &CreateForm::confirm_Click);
			// 
			// TextBox_MapNameCN
			// 
			this->TextBox_MapNameCN->Location = System::Drawing::Point(82, 37);
			this->TextBox_MapNameCN->Name = L"TextBox_MapNameCN";
			this->TextBox_MapNameCN->Size = System::Drawing::Size(183, 21);
			this->TextBox_MapNameCN->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 41);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(65, 12);
			this->label2->TabIndex = 2;
			this->label2->Text = L"地图中文名";
			// 
			// TextBox_MapNameEN
			// 
			this->TextBox_MapNameEN->Location = System::Drawing::Point(82, 10);
			this->TextBox_MapNameEN->Name = L"TextBox_MapNameEN";
			this->TextBox_MapNameEN->Size = System::Drawing::Size(183, 21);
			this->TextBox_MapNameEN->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(65, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"地图英文名";
			// 
			// CreateForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(330, 343);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"CreateForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"新地图";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &CreateForm::CreateForm_FormClosed);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void confirm_Click(System::Object^  sender, System::EventArgs^  e) {
				 validateForm();
			 }
private: System::Void cancel_Click(System::Object^  sender, System::EventArgs^  e) {
			 Close();
			 closeForm();
		 }
private: System::Void CreateForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 closeForm();
		 }
private: System::Void ComboBox_MapSize_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 //获取地图宽度(高度)
			 int mapSize = System::Int32::Parse(ComboBox_MapSize->SelectedItem->ToString());
			 if (ComboBox_TileSize->Items->Count <= 0)
				 return;

			 if (mapSize == 1024)
			 {
				 ComboBox_TileSize->SelectedIndex = 1;
				 ComboBox_ChunkNum->SelectedIndex = 1;
			 }
			 else if (mapSize == 512)
			 {
				 ComboBox_TileSize->SelectedIndex = 1;
				 ComboBox_ChunkNum->SelectedIndex = 0;
			 }
			 else if (mapSize == 256)
			 {
				 ComboBox_TileSize->SelectedIndex = 1;
				 ComboBox_ChunkNum->SelectedIndex = 0;
			 } 
			 else if (mapSize == 128)
			 {
				 ComboBox_TileSize->SelectedIndex = 0;
				 ComboBox_ChunkNum->SelectedIndex = 0;
			 } 
		 }
private: System::Void ComboBox_MinHeight_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (ComboBox_MaxHeight->Items->Count <= 0)
				 return;
			 //获取地图宽度(高度)
			 System::Int32 minHeight = System::Int32::Parse(ComboBox_MinHeight->SelectedItem->ToString());
			 System::Int32 maxHeight = -minHeight;
			 ComboBox_MaxHeight->Items->Clear();
			 ComboBox_MaxHeight->Items->Add(maxHeight);
			 ComboBox_MaxHeight->SelectedIndex = 0;
		 }
};
}
