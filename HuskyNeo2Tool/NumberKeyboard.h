#pragma once

namespace HuskyNeo2Tool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// NumberKeyboard 摘要
	/// </summary>
	public ref class NumberKeyboard : public System::Windows::Forms::Form
	{
	public:
		NumberKeyboard(void)
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
		~NumberKeyboard()
		{
			if (components)
			{
				delete components;
			}
		}
	public: TextBox^ parentTextBox;
	private: System::Windows::Forms::Button^  buttonNum1;
	private: System::Windows::Forms::Button^  buttonNum2;
	private: System::Windows::Forms::Button^  buttonNum3;
	private: System::Windows::Forms::Button^  buttonNum4;
	private: System::Windows::Forms::Button^  buttonNum5;
	private: System::Windows::Forms::Button^  buttonNum6;
	private: System::Windows::Forms::Button^  buttonNum7;
	private: System::Windows::Forms::Button^  buttonNum8;
	private: System::Windows::Forms::Button^  buttonNum9;
	private: System::Windows::Forms::Button^  buttonNum0;

	private: System::Windows::Forms::Button^  buttonDelete;
	private: System::Windows::Forms::Button^  buttonEnter;

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
			this->buttonNum1 = (gcnew System::Windows::Forms::Button());
			this->buttonNum2 = (gcnew System::Windows::Forms::Button());
			this->buttonNum3 = (gcnew System::Windows::Forms::Button());
			this->buttonNum4 = (gcnew System::Windows::Forms::Button());
			this->buttonNum5 = (gcnew System::Windows::Forms::Button());
			this->buttonNum6 = (gcnew System::Windows::Forms::Button());
			this->buttonNum7 = (gcnew System::Windows::Forms::Button());
			this->buttonNum8 = (gcnew System::Windows::Forms::Button());
			this->buttonNum9 = (gcnew System::Windows::Forms::Button());
			this->buttonNum0 = (gcnew System::Windows::Forms::Button());
			this->buttonDelete = (gcnew System::Windows::Forms::Button());
			this->buttonEnter = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// buttonNum1
			// 
			this->buttonNum1->Location = System::Drawing::Point(20, 120);
			this->buttonNum1->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonNum1->Name = L"buttonNum1";
			this->buttonNum1->Size = System::Drawing::Size(59, 40);
			this->buttonNum1->TabIndex = 0;
			this->buttonNum1->Text = L"1";
			this->buttonNum1->UseVisualStyleBackColor = true;
			this->buttonNum1->Click += gcnew System::EventHandler(this, &NumberKeyboard::buttonNum1_Click);
			// 
			// buttonNum2
			// 
			this->buttonNum2->Location = System::Drawing::Point(90, 120);
			this->buttonNum2->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonNum2->Name = L"buttonNum2";
			this->buttonNum2->Size = System::Drawing::Size(64, 40);
			this->buttonNum2->TabIndex = 1;
			this->buttonNum2->Text = L"2";
			this->buttonNum2->UseVisualStyleBackColor = true;
			this->buttonNum2->Click += gcnew System::EventHandler(this, &NumberKeyboard::buttonNum2_Click);
			// 
			// buttonNum3
			// 
			this->buttonNum3->Location = System::Drawing::Point(165, 120);
			this->buttonNum3->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonNum3->Name = L"buttonNum3";
			this->buttonNum3->Size = System::Drawing::Size(61, 40);
			this->buttonNum3->TabIndex = 2;
			this->buttonNum3->Text = L"3";
			this->buttonNum3->UseVisualStyleBackColor = true;
			this->buttonNum3->Click += gcnew System::EventHandler(this, &NumberKeyboard::buttonNum3_Click);
			// 
			// buttonNum4
			// 
			this->buttonNum4->Location = System::Drawing::Point(20, 69);
			this->buttonNum4->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonNum4->Name = L"buttonNum4";
			this->buttonNum4->Size = System::Drawing::Size(59, 40);
			this->buttonNum4->TabIndex = 3;
			this->buttonNum4->Text = L"4";
			this->buttonNum4->UseVisualStyleBackColor = true;
			this->buttonNum4->Click += gcnew System::EventHandler(this, &NumberKeyboard::buttonNum4_Click);
			// 
			// buttonNum5
			// 
			this->buttonNum5->Location = System::Drawing::Point(90, 69);
			this->buttonNum5->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonNum5->Name = L"buttonNum5";
			this->buttonNum5->Size = System::Drawing::Size(64, 40);
			this->buttonNum5->TabIndex = 4;
			this->buttonNum5->Text = L"5";
			this->buttonNum5->UseVisualStyleBackColor = true;
			this->buttonNum5->Click += gcnew System::EventHandler(this, &NumberKeyboard::buttonNum5_Click);
			// 
			// buttonNum6
			// 
			this->buttonNum6->Location = System::Drawing::Point(166, 67);
			this->buttonNum6->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonNum6->Name = L"buttonNum6";
			this->buttonNum6->Size = System::Drawing::Size(59, 40);
			this->buttonNum6->TabIndex = 5;
			this->buttonNum6->Text = L"6";
			this->buttonNum6->UseVisualStyleBackColor = true;
			this->buttonNum6->Click += gcnew System::EventHandler(this, &NumberKeyboard::buttonNum6_Click);
			// 
			// buttonNum7
			// 
			this->buttonNum7->Location = System::Drawing::Point(20, 14);
			this->buttonNum7->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonNum7->Name = L"buttonNum7";
			this->buttonNum7->Size = System::Drawing::Size(60, 40);
			this->buttonNum7->TabIndex = 6;
			this->buttonNum7->Text = L"7";
			this->buttonNum7->UseVisualStyleBackColor = true;
			this->buttonNum7->Click += gcnew System::EventHandler(this, &NumberKeyboard::buttonNum7_Click);
			// 
			// buttonNum8
			// 
			this->buttonNum8->Location = System::Drawing::Point(90, 14);
			this->buttonNum8->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonNum8->Name = L"buttonNum8";
			this->buttonNum8->Size = System::Drawing::Size(64, 40);
			this->buttonNum8->TabIndex = 7;
			this->buttonNum8->Text = L"8";
			this->buttonNum8->UseVisualStyleBackColor = true;
			this->buttonNum8->Click += gcnew System::EventHandler(this, &NumberKeyboard::buttonNum8_Click);
			// 
			// buttonNum9
			// 
			this->buttonNum9->Location = System::Drawing::Point(165, 14);
			this->buttonNum9->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonNum9->Name = L"buttonNum9";
			this->buttonNum9->Size = System::Drawing::Size(61, 40);
			this->buttonNum9->TabIndex = 8;
			this->buttonNum9->Text = L"9";
			this->buttonNum9->UseVisualStyleBackColor = true;
			this->buttonNum9->Click += gcnew System::EventHandler(this, &NumberKeyboard::buttonNum9_Click);
			// 
			// buttonNum0
			// 
			this->buttonNum0->Location = System::Drawing::Point(90, 172);
			this->buttonNum0->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonNum0->Name = L"buttonNum0";
			this->buttonNum0->Size = System::Drawing::Size(64, 40);
			this->buttonNum0->TabIndex = 9;
			this->buttonNum0->Text = L"0";
			this->buttonNum0->UseVisualStyleBackColor = true;
			this->buttonNum0->Click += gcnew System::EventHandler(this, &NumberKeyboard::buttonNum0_Click);
			// 
			// buttonDelete
			// 
			this->buttonDelete->Location = System::Drawing::Point(20, 172);
			this->buttonDelete->Name = L"buttonDelete";
			this->buttonDelete->Size = System::Drawing::Size(60, 40);
			this->buttonDelete->TabIndex = 10;
			this->buttonDelete->Text = L"←";
			this->buttonDelete->UseVisualStyleBackColor = true;
			this->buttonDelete->Click += gcnew System::EventHandler(this, &NumberKeyboard::buttonDelete_Click);
			// 
			// buttonEnter
			// 
			this->buttonEnter->Location = System::Drawing::Point(166, 172);
			this->buttonEnter->Name = L"buttonEnter";
			this->buttonEnter->Size = System::Drawing::Size(60, 40);
			this->buttonEnter->TabIndex = 11;
			this->buttonEnter->Text = L"↩";
			this->buttonEnter->UseVisualStyleBackColor = true;
			this->buttonEnter->Click += gcnew System::EventHandler(this, &NumberKeyboard::buttonEnter_Click);
			// 
			// NumberKeyboard
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 21);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(246, 224);
			this->Controls->Add(this->buttonEnter);
			this->Controls->Add(this->buttonDelete);
			this->Controls->Add(this->buttonNum0);
			this->Controls->Add(this->buttonNum9);
			this->Controls->Add(this->buttonNum8);
			this->Controls->Add(this->buttonNum7);
			this->Controls->Add(this->buttonNum6);
			this->Controls->Add(this->buttonNum5);
			this->Controls->Add(this->buttonNum4);
			this->Controls->Add(this->buttonNum3);
			this->Controls->Add(this->buttonNum2);
			this->Controls->Add(this->buttonNum1);
			this->Font = (gcnew System::Drawing::Font(L"宋体", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->MaximizeBox = false;
			this->Name = L"NumberKeyboard";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"数字键盘";
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void buttonNum0_Click(System::Object^  sender, System::EventArgs^  e) {
			 parentTextBox->Text += "0";
		 }
private: System::Void buttonEnter_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->DialogResult = System::Windows::Forms::DialogResult::OK;
			 this->Close();
		 }
private: System::Void buttonDelete_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (parentTextBox->Text->Length > 0)
				parentTextBox->Text = parentTextBox->Text->Substring(0, parentTextBox->Text->Length - 1);
		 }
private: System::Void buttonNum1_Click(System::Object^  sender, System::EventArgs^  e) {
			 parentTextBox->Text += "1";
		 }
private: System::Void buttonNum2_Click(System::Object^  sender, System::EventArgs^  e) {
			 parentTextBox->Text += "2";
		 }
private: System::Void buttonNum3_Click(System::Object^  sender, System::EventArgs^  e) {
			 parentTextBox->Text += "3";
		 }
private: System::Void buttonNum4_Click(System::Object^  sender, System::EventArgs^  e) {
			 parentTextBox->Text += "4";
		 }
private: System::Void buttonNum5_Click(System::Object^  sender, System::EventArgs^  e) {
			 parentTextBox->Text += "5";
		 }
private: System::Void buttonNum6_Click(System::Object^  sender, System::EventArgs^  e) {
			 parentTextBox->Text += "6";
		 }
private: System::Void buttonNum7_Click(System::Object^  sender, System::EventArgs^  e) {
			 parentTextBox->Text += "7";
		 }
private: System::Void buttonNum8_Click(System::Object^  sender, System::EventArgs^  e) {
			 parentTextBox->Text += "8";
		 }
private: System::Void buttonNum9_Click(System::Object^  sender, System::EventArgs^  e) {
			 parentTextBox->Text += "9";
		 }
};
}
