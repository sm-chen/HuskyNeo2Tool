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
	/// AllZonesTemperatureSetting ժҪ
	/// </summary>
	public ref class SetOneZoneTemperatureForm : public System::Windows::Forms::Form
	{
	public:
		SetOneZoneTemperatureForm(void)
		{
			InitializeComponent();
			//
			//TODO: �ڴ˴���ӹ��캯������
			//
		}

	protected:
		/// <summary>
		/// ������������ʹ�õ���Դ��
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
		/// ����������������
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����֧������ķ��� - ��Ҫ
		/// ʹ�ô���༭���޸Ĵ˷��������ݡ�
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
			this->buttonOK->Text = L"ȷ��";
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
			this->button2->Text = L"ȡ��";
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
			this->label1->Text = L"�����¶�:";
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
			this->label2->Text = L"��";
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
			this->Font = (gcnew System::Drawing::Font(L"����", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->MaximizeBox = false;
			this->Name = L"SetOneZoneTemperatureForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"�¶�����";
			this->Load += gcnew System::EventHandler(this, &SetOneZoneTemperatureForm::AllZonesTemperatureSetting_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->textBox1->Text == "") {
			MessageBox::Show("�������¶ȣ�", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}else if (Convert::ToDouble(this->textBox1->Text) < 0 || Convert::ToDouble(this->textBox1->Text) > 500) {
			MessageBox::Show("�¿����¶����÷�ΧΪ 0~500 �棡", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
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
