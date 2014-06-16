#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace MG {

	/// <summary>
	/// Summary for LoadingForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class LoadingForm : public System::Windows::Forms::Form
	{
	public:
		LoadingForm(void)
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
		~LoadingForm()
		{
			if (components)
			{
				delete components;
			}
		}

	public:
		DELEGATEFUNC(showMessage)(String^ msg);
		void showMessage(String^msg);

		//@
		//@  loadGameTextConfig
		//@
		DELEGATEFUNC(loadGameTextConfig)();
		void loadGameTextConfig();


	private: System::Windows::Forms::Panel^  pnl_main;
	private: System::Windows::Forms::Label^  lbl_show_msg;


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
			this->pnl_main = (gcnew System::Windows::Forms::Panel());
			this->lbl_show_msg = (gcnew System::Windows::Forms::Label());
			this->pnl_main->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnl_main
			// 
			this->pnl_main->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pnl_main->Controls->Add(this->lbl_show_msg);
			this->pnl_main->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnl_main->ForeColor = System::Drawing::SystemColors::ControlText;
			this->pnl_main->Location = System::Drawing::Point(0, 0);
			this->pnl_main->Name = L"pnl_main";
			this->pnl_main->Size = System::Drawing::Size(256, 66);
			this->pnl_main->TabIndex = 1;
			// 
			// lbl_show_msg
			// 
			this->lbl_show_msg->Font = (gcnew System::Drawing::Font(L"SimSun", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->lbl_show_msg->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->lbl_show_msg->Location = System::Drawing::Point(11, 21);
			this->lbl_show_msg->Name = L"lbl_show_msg";
			this->lbl_show_msg->Size = System::Drawing::Size(232, 23);
			this->lbl_show_msg->TabIndex = 1;
			this->lbl_show_msg->Text = L"Please Wait Moment...";
			this->lbl_show_msg->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// LoadingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(256, 66);
			this->Controls->Add(this->pnl_main);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->Name = L"LoadingForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"LoadingForm";
			this->pnl_main->ResumeLayout(false);
			this->ResumeLayout(false);
        }
#pragma endregion
	};
}
