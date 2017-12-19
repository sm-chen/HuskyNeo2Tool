#pragma once

#include <Windows.h>

namespace HuskyNeo2Tool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// SetAllZonesTemperatureForm 摘要
	/// </summary>
	public ref class SetAllZonesTemperatureForm : public System::Windows::Forms::Form
	{
	public:
		SetAllZonesTemperatureForm(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
			checkBoxAllZonesArray = gcnew array<System::Windows::Forms::CheckBox^, 1>(12);
			checkBoxAllZonesArray[0] = checkBox1;
			checkBoxAllZonesArray[1] = checkBox2;
			checkBoxAllZonesArray[2] = checkBox3;
			checkBoxAllZonesArray[3] = checkBox4;
			checkBoxAllZonesArray[4] = checkBox5;
			checkBoxAllZonesArray[5] = checkBox6;
			checkBoxAllZonesArray[6] = checkBox7;
			checkBoxAllZonesArray[7] = checkBox8;
			checkBoxAllZonesArray[8] = checkBox9;
			checkBoxAllZonesArray[9] = checkBox10;
			checkBoxAllZonesArray[10] = checkBox11;
			checkBoxAllZonesArray[11] = checkBox12;
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~SetAllZonesTemperatureForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public:
		array<System::Windows::Forms::CheckBox^, 1>^ checkBoxAllZonesArray;
		System::Windows::Forms::CheckBox^  checkBoxAllZones;

	private: System::Windows::Forms::Button^  button1;
	public: System::Windows::Forms::TextBox^  textBoxTemperature;
	private: 
	protected: 

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::CheckBox^  checkBox12;
	private: System::Windows::Forms::CheckBox^  checkBox11;
	private: System::Windows::Forms::CheckBox^  checkBox10;
	private: System::Windows::Forms::CheckBox^  checkBox9;
	private: System::Windows::Forms::CheckBox^  checkBox8;
	private: System::Windows::Forms::CheckBox^  checkBox7;
	private: System::Windows::Forms::CheckBox^  checkBox6;
	private: System::Windows::Forms::CheckBox^  checkBox5;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::CheckBox^  checkBox3;

	private: System::Windows::Forms::Label^  label1;
	public: 

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBoxTemperature = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBoxAllZones = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox12 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox11 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox10 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox9 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox8 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox7 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(112, 15);
			this->button1->Margin = System::Windows::Forms::Padding(4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(69, 26);
			this->button1->TabIndex = 0;
			this->button1->Text = L"确认";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SetAllZonesTemperatureForm::button1_Click);
			// 
			// textBoxTemperature
			// 
			this->textBoxTemperature->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textBoxTemperature->Location = System::Drawing::Point(7, 15);
			this->textBoxTemperature->Margin = System::Windows::Forms::Padding(4);
			this->textBoxTemperature->Name = L"textBoxTemperature";
			this->textBoxTemperature->Size = System::Drawing::Size(70, 26);
			this->textBoxTemperature->TabIndex = 1;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->textBoxTemperature);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Location = System::Drawing::Point(156, 135);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(188, 50);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			// 
			// checkBoxAllZones
			// 
			this->checkBoxAllZones->AutoSize = true;
			this->checkBoxAllZones->Location = System::Drawing::Point(18, 154);
			this->checkBoxAllZones->Name = L"checkBoxAllZones";
			this->checkBoxAllZones->Size = System::Drawing::Size(59, 20);
			this->checkBoxAllZones->TabIndex = 3;
			this->checkBoxAllZones->Text = L"全选";
			this->checkBoxAllZones->UseVisualStyleBackColor = true;
			this->checkBoxAllZones->CheckedChanged += gcnew System::EventHandler(this, &SetAllZonesTemperatureForm::checkBoxAllZones_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(77, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(24, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"℃";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(6, 15);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(75, 20);
			this->checkBox1->TabIndex = 3;
			this->checkBox1->Text = L"Zone01";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(87, 15);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(75, 20);
			this->checkBox2->TabIndex = 4;
			this->checkBox2->Text = L"Zone02";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->checkBox12);
			this->groupBox2->Controls->Add(this->checkBox11);
			this->groupBox2->Controls->Add(this->checkBox10);
			this->groupBox2->Controls->Add(this->checkBox9);
			this->groupBox2->Controls->Add(this->checkBox8);
			this->groupBox2->Controls->Add(this->checkBox7);
			this->groupBox2->Controls->Add(this->checkBox6);
			this->groupBox2->Controls->Add(this->checkBox5);
			this->groupBox2->Controls->Add(this->checkBox4);
			this->groupBox2->Controls->Add(this->checkBox3);
			this->groupBox2->Controls->Add(this->checkBox1);
			this->groupBox2->Controls->Add(this->checkBox2);
			this->groupBox2->Location = System::Drawing::Point(12, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(332, 120);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			// 
			// checkBox12
			// 
			this->checkBox12->AutoSize = true;
			this->checkBox12->Location = System::Drawing::Point(246, 90);
			this->checkBox12->Name = L"checkBox12";
			this->checkBox12->Size = System::Drawing::Size(75, 20);
			this->checkBox12->TabIndex = 14;
			this->checkBox12->Text = L"Zone12";
			this->checkBox12->UseVisualStyleBackColor = true;
			// 
			// checkBox11
			// 
			this->checkBox11->AutoSize = true;
			this->checkBox11->Location = System::Drawing::Point(165, 90);
			this->checkBox11->Name = L"checkBox11";
			this->checkBox11->Size = System::Drawing::Size(75, 20);
			this->checkBox11->TabIndex = 13;
			this->checkBox11->Text = L"Zone11";
			this->checkBox11->UseVisualStyleBackColor = true;
			// 
			// checkBox10
			// 
			this->checkBox10->AutoSize = true;
			this->checkBox10->Location = System::Drawing::Point(87, 90);
			this->checkBox10->Name = L"checkBox10";
			this->checkBox10->Size = System::Drawing::Size(75, 20);
			this->checkBox10->TabIndex = 12;
			this->checkBox10->Text = L"Zone10";
			this->checkBox10->UseVisualStyleBackColor = true;
			// 
			// checkBox9
			// 
			this->checkBox9->AutoSize = true;
			this->checkBox9->Location = System::Drawing::Point(6, 90);
			this->checkBox9->Name = L"checkBox9";
			this->checkBox9->Size = System::Drawing::Size(75, 20);
			this->checkBox9->TabIndex = 11;
			this->checkBox9->Text = L"Zone09";
			this->checkBox9->UseVisualStyleBackColor = true;
			// 
			// checkBox8
			// 
			this->checkBox8->AutoSize = true;
			this->checkBox8->Location = System::Drawing::Point(246, 53);
			this->checkBox8->Name = L"checkBox8";
			this->checkBox8->Size = System::Drawing::Size(75, 20);
			this->checkBox8->TabIndex = 10;
			this->checkBox8->Text = L"Zone08";
			this->checkBox8->UseVisualStyleBackColor = true;
			// 
			// checkBox7
			// 
			this->checkBox7->AutoSize = true;
			this->checkBox7->Location = System::Drawing::Point(165, 53);
			this->checkBox7->Name = L"checkBox7";
			this->checkBox7->Size = System::Drawing::Size(75, 20);
			this->checkBox7->TabIndex = 9;
			this->checkBox7->Text = L"Zone07";
			this->checkBox7->UseVisualStyleBackColor = true;
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->Location = System::Drawing::Point(87, 53);
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(75, 20);
			this->checkBox6->TabIndex = 8;
			this->checkBox6->Text = L"Zone06";
			this->checkBox6->UseVisualStyleBackColor = true;
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(6, 53);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(75, 20);
			this->checkBox5->TabIndex = 7;
			this->checkBox5->Text = L"Zone05";
			this->checkBox5->UseVisualStyleBackColor = true;
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(246, 15);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(75, 20);
			this->checkBox4->TabIndex = 6;
			this->checkBox4->Text = L"Zone04";
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->CheckedChanged += gcnew System::EventHandler(this, &SetAllZonesTemperatureForm::checkBox4_CheckedChanged);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(165, 15);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(75, 20);
			this->checkBox3->TabIndex = 5;
			this->checkBox3->Text = L"Zone03";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// SetAllZonesTemperatureForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(356, 197);
			this->Controls->Add(this->checkBoxAllZones);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->Name = L"SetAllZonesTemperatureForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"全区域温度设置";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	if (this->textBoxTemperature->Text == "") {
		MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		return;
	} else {
		this->DialogResult = System::Windows::Forms::DialogResult::OK;
		this->Close();
	}
}
private: System::Void checkBox4_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void checkBoxAllZones_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (this->checkBoxAllZones->Checked) {
				 for (int i = 0; i < 12; i++) {
					 checkBoxAllZonesArray[i]->Checked = TRUE;
				 }
			 } else {
				 for (int i = 0; i < 12; i++) {
					 checkBoxAllZonesArray[i]->Checked = FALSE;
				 }
			 }
}
};
}
