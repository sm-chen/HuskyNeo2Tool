#pragma once

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
	public ref class AllZonesTemperatureSetting : public System::Windows::Forms::Form
	{
	public:
		AllZonesTemperatureSetting(void)
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
		~AllZonesTemperatureSetting()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(140, 72);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"确定";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &AllZonesTemperatureSetting::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(59, 72);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"取消";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &AllZonesTemperatureSetting::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(35, 33);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 12);
			this->label1->TabIndex = 2;
			this->label1->Text = L"全局温度:";
			this->label1->Click += gcnew System::EventHandler(this, &AllZonesTemperatureSetting::label1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(100, 30);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(45, 21);
			this->textBox1->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(151, 33);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(17, 12);
			this->label2->TabIndex = 4;
			this->label2->Text = L"℃";
			// 
			// AllZonesTemperatureSetting
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(220, 107);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"AllZonesTemperatureSetting";
			this->Text = L"AllZonesTemperatureSetting";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
};
}
