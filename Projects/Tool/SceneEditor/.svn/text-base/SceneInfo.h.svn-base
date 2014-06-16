#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace SceneEditor {

	/// <summary>
	/// Summary for SceneInfo
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class SceneInfo : public System::Windows::Forms::Form
	{
	public:
		SceneInfo(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void initialize();
		void closeForm();

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SceneInfo()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  richTextBox1;

	protected: 

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
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->Location = System::Drawing::Point(12, 12);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(268, 242);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->Text = L"";
			// 
			// SceneInfo
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 266);
			this->Controls->Add(this->richTextBox1);
			this->Name = L"SceneInfo";
			this->Text = L"³¡¾°ÐÅÏ¢";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &SceneInfo::SceneInfo_FormClosed);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void SceneInfo_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				 closeForm();
			 }
	};
}
