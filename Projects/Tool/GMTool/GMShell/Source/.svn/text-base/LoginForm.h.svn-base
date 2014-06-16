#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace MG {

	/// <summary>
	/// Summary for LoginForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		LoginForm(void)
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
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}

		DELEGATEFUNC(startLogin)();
		void startLogin();

		DELEGATEFUNC(quitLogin)(DWORD reason);
		void quitLogin(DWORD reason);

		//@
		//@  loadGameTextConfig
		//@
		DELEGATEFUNC(loadGameTextConfig)();
		void loadGameTextConfig();

	private: System::Windows::Forms::Label^		lbl_title;
	private: System::Windows::Forms::Button^	btn_login;
	private: System::Windows::Forms::Button^	btn_exit;
	private: System::Windows::Forms::GroupBox^  gbo_input;
	private: System::Windows::Forms::TextBox^	edt_username;
	private: System::Windows::Forms::Label^		lbl_password;
	private: System::Windows::Forms::Label^		lbl_username;
	private: System::Windows::Forms::TextBox^	edt_password;

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
			this->lbl_title = (gcnew System::Windows::Forms::Label());
			this->btn_login = (gcnew System::Windows::Forms::Button());
			this->btn_exit = (gcnew System::Windows::Forms::Button());
			this->gbo_input = (gcnew System::Windows::Forms::GroupBox());
			this->edt_password = (gcnew System::Windows::Forms::TextBox());
			this->edt_username = (gcnew System::Windows::Forms::TextBox());
			this->lbl_password = (gcnew System::Windows::Forms::Label());
			this->lbl_username = (gcnew System::Windows::Forms::Label());
			this->gbo_input->SuspendLayout();
			this->SuspendLayout();
			// 
			// lbl_title
			// 
			this->lbl_title->AutoSize = true;
			this->lbl_title->Font = (gcnew System::Drawing::Font(L"SimSun", 16, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
			this->lbl_title->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->lbl_title->Location = System::Drawing::Point(89, 5);
			this->lbl_title->Name = L"lbl_title";
			this->lbl_title->Size = System::Drawing::Size(130, 22);
			this->lbl_title->TabIndex = 0;
			this->lbl_title->Text = L"YXZ-GMTooL";
			// 
			// btn_login
			// 
			this->btn_login->Location = System::Drawing::Point(58, 136);
			this->btn_login->Name = L"btn_login";
			this->btn_login->Size = System::Drawing::Size(75, 23);
			this->btn_login->TabIndex = 1;
			this->btn_login->Text = L"Login";
			this->btn_login->UseVisualStyleBackColor = true;
			this->btn_login->Click += gcnew System::EventHandler(this, &LoginForm::btn_login_Click);
			// 
			// btn_exit
			// 
			this->btn_exit->Location = System::Drawing::Point(168, 136);
			this->btn_exit->Name = L"btn_exit";
			this->btn_exit->Size = System::Drawing::Size(75, 23);
			this->btn_exit->TabIndex = 6;
			this->btn_exit->Text = L"Exit";
			this->btn_exit->UseVisualStyleBackColor = true;
			this->btn_exit->Click += gcnew System::EventHandler(this, &LoginForm::btn_exit_Click);
			// 
			// gbo_input
			// 
			this->gbo_input->Controls->Add(this->edt_password);
			this->gbo_input->Controls->Add(this->edt_username);
			this->gbo_input->Controls->Add(this->lbl_password);
			this->gbo_input->Controls->Add(this->lbl_username);
			this->gbo_input->Location = System::Drawing::Point(33, 37);
			this->gbo_input->Name = L"gbo_input";
			this->gbo_input->Size = System::Drawing::Size(237, 90);
			this->gbo_input->TabIndex = 9;
			this->gbo_input->TabStop = false;
			this->gbo_input->Text = L"Login";
			// 
			// edt_password
			// 
			this->edt_password->Location = System::Drawing::Point(100, 58);
			this->edt_password->Name = L"edt_password";
			this->edt_password->PasswordChar = '*';
			this->edt_password->Size = System::Drawing::Size(100, 21);
			this->edt_password->TabIndex = 15;
			// 
			// edt_username
			// 
			this->edt_username->Location = System::Drawing::Point(100, 27);
			this->edt_username->Name = L"edt_username";
			this->edt_username->Size = System::Drawing::Size(100, 21);
			this->edt_username->TabIndex = 14;
			// 
			// lbl_password
			// 
			this->lbl_password->AutoSize = true;
			this->lbl_password->Location = System::Drawing::Point(22, 61);
			this->lbl_password->Name = L"lbl_password";
			this->lbl_password->Size = System::Drawing::Size(53, 12);
			this->lbl_password->TabIndex = 10;
			this->lbl_password->Text = L"Password";
			// 
			// lbl_username
			// 
			this->lbl_username->AutoSize = true;
			this->lbl_username->Location = System::Drawing::Point(22, 31);
			this->lbl_username->Name = L"lbl_username";
			this->lbl_username->Size = System::Drawing::Size(53, 12);
			this->lbl_username->TabIndex = 9;
			this->lbl_username->Text = L"UserName";
			// 
			// LoginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(300, 166);
			this->Controls->Add(this->gbo_input);
			this->Controls->Add(this->btn_exit);
			this->Controls->Add(this->btn_login);
			this->Controls->Add(this->lbl_title);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MaximizeBox = false;
			this->Name = L"LoginForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"LoginForm";
			this->gbo_input->ResumeLayout(false);
			this->gbo_input->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void btn_exit_Click(System::Object^  sender, System::EventArgs^  e);
		private: System::Void btn_login_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
