#pragma once

#include <Windows.h>
#include <string.h>
#include <direct.h>
#include <stdio.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace HuskyNeo2Tool {

	/// <summary>
	/// IpConfigure 摘要
	///
	/// 警告: 如果更改此类的名称，则需要更改
	///          与此类所依赖的所有 .resx 文件关联的托管资源编译器工具的
	///          “资源文件名”属性。否则，
	///          设计器将不能与此窗体的关联
	///          本地化资源正确交互。
	/// </summary>
	public ref class IpConfigure : public System::Windows::Forms::Form
	{
	public:
		IpConfigure(void)
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
		~IpConfigure()
		{
			if (components)
			{
				delete components;
			}
		}
	char **huskyIps;
	
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;

	public: System::Windows::Forms::TextBox^  textBox1;
	public: System::Windows::Forms::TextBox^  textBox2;
	public: System::Windows::Forms::TextBox^  textBox3;
	public: System::Windows::Forms::TextBox^  textBox4;
	public: System::Windows::Forms::TextBox^  textBox5;
	public: System::Windows::Forms::TextBox^  textBox6;
	public: System::Windows::Forms::TextBox^  textBox7;
	public: System::Windows::Forms::TextBox^  textBox8;
	public: System::Windows::Forms::TextBox^  textBox9;
	public: System::Windows::Forms::TextBox^  textBox10;
	public: System::Windows::Forms::TextBox^  textBox11;
	public: System::Windows::Forms::TextBox^  textBox12;


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
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(99, 19);
			this->textBox1->Margin = System::Windows::Forms::Padding(4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(153, 26);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"192.168.1.1";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(489, 232);
			this->button1->Margin = System::Windows::Forms::Padding(4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 31);
			this->button1->TabIndex = 1;
			this->button1->Text = L"确定";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &IpConfigure::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(344, 232);
			this->button2->Margin = System::Windows::Forms::Padding(4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 31);
			this->button2->TabIndex = 2;
			this->button2->Text = L"取消";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &IpConfigure::button2_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->textBox12);
			this->groupBox1->Controls->Add(this->textBox6);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->textBox11);
			this->groupBox1->Controls->Add(this->textBox5);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->textBox10);
			this->groupBox1->Controls->Add(this->textBox4);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->textBox9);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->textBox3);
			this->groupBox1->Controls->Add(this->textBox8);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->textBox7);
			this->groupBox1->Controls->Add(this->textBox2);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Location = System::Drawing::Point(16, 16);
			this->groupBox1->Margin = System::Windows::Forms::Padding(4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(4);
			this->groupBox1->Size = System::Drawing::Size(573, 208);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(325, 163);
			this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(88, 16);
			this->label12->TabIndex = 1;
			this->label12->Text = L"机台12 IP:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(8, 163);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(88, 16);
			this->label6->TabIndex = 1;
			this->label6->Text = L"机台06 IP:";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(325, 135);
			this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(88, 16);
			this->label11->TabIndex = 1;
			this->label11->Text = L"机台11 IP:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(8, 135);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(88, 16);
			this->label5->TabIndex = 1;
			this->label5->Text = L"机台05 IP:";
			// 
			// textBox12
			// 
			this->textBox12->Location = System::Drawing::Point(416, 159);
			this->textBox12->Margin = System::Windows::Forms::Padding(4);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(153, 26);
			this->textBox12->TabIndex = 0;
			this->textBox12->Text = L"192.168.1.12";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(99, 159);
			this->textBox6->Margin = System::Windows::Forms::Padding(4);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(153, 26);
			this->textBox6->TabIndex = 0;
			this->textBox6->Text = L"192.168.1.6";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(325, 107);
			this->label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(88, 16);
			this->label10->TabIndex = 1;
			this->label10->Text = L"机台10 IP:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(8, 107);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(88, 16);
			this->label4->TabIndex = 1;
			this->label4->Text = L"机台04 IP:";
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(416, 131);
			this->textBox11->Margin = System::Windows::Forms::Padding(4);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(153, 26);
			this->textBox11->TabIndex = 0;
			this->textBox11->Text = L"192.168.1.11";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(99, 131);
			this->textBox5->Margin = System::Windows::Forms::Padding(4);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(153, 26);
			this->textBox5->TabIndex = 0;
			this->textBox5->Text = L"192.168.1.5";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(325, 79);
			this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(88, 16);
			this->label9->TabIndex = 1;
			this->label9->Text = L"机台09 IP:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(8, 79);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(88, 16);
			this->label3->TabIndex = 1;
			this->label3->Text = L"机台03 IP:";
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(416, 103);
			this->textBox10->Margin = System::Windows::Forms::Padding(4);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(153, 26);
			this->textBox10->TabIndex = 0;
			this->textBox10->Text = L"192.168.1.10";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(99, 103);
			this->textBox4->Margin = System::Windows::Forms::Padding(4);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(153, 26);
			this->textBox4->TabIndex = 0;
			this->textBox4->Text = L"192.168.1.4";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(325, 51);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(88, 16);
			this->label8->TabIndex = 1;
			this->label8->Text = L"机台08 IP:";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(416, 75);
			this->textBox9->Margin = System::Windows::Forms::Padding(4);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(153, 26);
			this->textBox9->TabIndex = 0;
			this->textBox9->Text = L"192.168.1.9";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(8, 51);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(88, 16);
			this->label2->TabIndex = 1;
			this->label2->Text = L"机台02 IP:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(325, 23);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(88, 16);
			this->label7->TabIndex = 1;
			this->label7->Text = L"机台07 IP:";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(99, 75);
			this->textBox3->Margin = System::Windows::Forms::Padding(4);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(153, 26);
			this->textBox3->TabIndex = 0;
			this->textBox3->Text = L"192.168.1.3";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(416, 47);
			this->textBox8->Margin = System::Windows::Forms::Padding(4);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(153, 26);
			this->textBox8->TabIndex = 0;
			this->textBox8->Text = L"192.168.1.8";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(8, 23);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(88, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"机台01 IP:";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(416, 19);
			this->textBox7->Margin = System::Windows::Forms::Padding(4);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(153, 26);
			this->textBox7->TabIndex = 0;
			this->textBox7->Text = L"192.168.1.7";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(99, 47);
			this->textBox2->Margin = System::Windows::Forms::Padding(4);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(153, 26);
			this->textBox2->TabIndex = 0;
			this->textBox2->Text = L"192.168.1.2";
			// 
			// IpConfigure
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(612, 271);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->Name = L"IpConfigure";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"机台IP配置";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		char pBuf[MAX_PATH];
		_getcwd(pBuf, MAX_PATH ); //get current work dir
		int len = strlen(pBuf);
		strcpy(pBuf + len, "\\ipconfig");
		FILE *fp;
		fp = fopen(pBuf, "wt+");
		if (fp == NULL) {
			printf("Open Failed.\n"); 
			MessageBox::Show("IP地址配置信息保存失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		} else {
			fprintf(fp,"%s\n",(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox1->Text)); //write a line
			fprintf(fp,"%s\n",(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox2->Text));
			fprintf(fp,"%s\n",(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox3->Text));
			fprintf(fp,"%s\n",(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox4->Text));
			fprintf(fp,"%s\n",(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox5->Text));
			fprintf(fp,"%s\n",(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox6->Text));
			fprintf(fp,"%s\n",(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox7->Text));
			fprintf(fp,"%s\n",(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox8->Text));
			fprintf(fp,"%s\n",(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox9->Text));
			fprintf(fp,"%s\n",(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox10->Text));
			fprintf(fp,"%s\n",(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox11->Text));
			fprintf(fp,"%s\n",(char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->textBox12->Text));

			fclose(fp);
		}

		this->DialogResult = ::DialogResult::OK;
		this->Close();
	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
};
}
