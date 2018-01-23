#pragma once

#include "NumberKeyboard.h"

namespace HuskyNeo2Tool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// AllZonesTemperatureSetting 摘要
	/// </summary>
	public ref class SetOneZoneTemperatureForm : public System::Windows::Forms::Form
	{
	public:
		SetOneZoneTemperatureForm(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~SetOneZoneTemperatureForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  buttonOK;
	protected: 

	protected: 
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;
	public: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label2;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// buttonOK
			// 
			this->buttonOK->Location = System::Drawing::Point(163, 64);
			this->buttonOK->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(76, 34);
			this->buttonOK->TabIndex = 0;
			this->buttonOK->Text = L"确定";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &SetOneZoneTemperatureForm::buttonOK_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(75, 64);
			this->button2->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(77, 34);
			this->button2->TabIndex = 1;
			this->button2->Text = L"取消";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &SetOneZoneTemperatureForm::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 18);
			this->label1->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(109, 22);
			this->label1->TabIndex = 2;
			this->label1->Text = L"输入温度:";
			this->label1->Click += gcnew System::EventHandler(this, &SetOneZoneTemperatureForm::label1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(127, 14);
			this->textBox1->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(79, 32);
			this->textBox1->TabIndex = 3;
			this->textBox1->Click += gcnew System::EventHandler(this, &SetOneZoneTemperatureForm::textBox1_Click);
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &SetOneZoneTemperatureForm::textBox1_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(207, 18);
			this->label2->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(32, 22);
			this->label2->TabIndex = 4;
			this->label2->Text = L"℃";
			// 
			// SetOneZoneTemperatureForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 21);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(262, 109);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->buttonOK);
			this->Font = (gcnew System::Drawing::Font(L"宋体", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->MaximizeBox = false;
			this->Name = L"SetOneZoneTemperatureForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"温度设置";
			this->Load += gcnew System::EventHandler(this, &SetOneZoneTemperatureForm::AllZonesTemperatureSetting_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->textBox1->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}else if (Convert::ToDouble(this->textBox1->Text) < 0 || Convert::ToDouble(this->textBox1->Text) > 500) {
			MessageBox::Show("温控器温度设置范围为 0~500 ℃！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
private: System::Void AllZonesTemperatureSetting_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			NumberKeyboard^ nb = gcnew NumberKeyboard();
			nb->parentTextBox = textBox1;
			Point p;
			p.X = this->Location.X;
			p.Y = this->Location.Y + this->Height;

			nb->Location = p;

			System::Windows::Forms::DialogResult result = nb->ShowDialog();
			if (result == ::DialogResult::OK) {
				InvokeOnClick(this->buttonOK, e);
			}
		 }
};
}
