#pragma once

namespace HuskyNeo2Tool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// AlarmStatusWindow 摘要
	/// </summary>
	public ref class AlarmStatusWindow : public System::Windows::Forms::Form
	{
	public:
		AlarmStatusWindow(void)
		{
			InitializeComponent();
			
			labelZoneAlarmMsgArray = gcnew array<System::Windows::Forms::Label^, 1>(12);
			labelZoneAlarmMsgArray[0] = labelZone01AlarmMsg;
			labelZoneAlarmMsgArray[1] = labelZone02AlarmMsg;
			labelZoneAlarmMsgArray[2] = labelZone03AlarmMsg;
			labelZoneAlarmMsgArray[3] = labelZone04AlarmMsg;
			labelZoneAlarmMsgArray[4] = labelZone05AlarmMsg;
			labelZoneAlarmMsgArray[5] = labelZone06AlarmMsg;
			labelZoneAlarmMsgArray[6] = labelZone07AlarmMsg;
			labelZoneAlarmMsgArray[7] = labelZone08AlarmMsg;
			labelZoneAlarmMsgArray[8] = labelZone09AlarmMsg;
			labelZoneAlarmMsgArray[9] = labelZone10AlarmMsg;
			labelZoneAlarmMsgArray[10] = labelZone11AlarmMsg;
			labelZoneAlarmMsgArray[11] = labelZone12AlarmMsg;
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~AlarmStatusWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	public: array<System::Windows::Forms::Label^, 1>^ labelZoneAlarmMsgArray;

	private: System::Windows::Forms::Button^  buttonControlerReset;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  labelZone01AlarmMsg;
	private: System::Windows::Forms::Label^  labelZone02AlarmMsg;
	private: System::Windows::Forms::Label^  labelZone12AlarmMsg;
	private: System::Windows::Forms::Label^  labelZone11AlarmMsg;
	private: System::Windows::Forms::Label^  labelZone10AlarmMsg;
	private: System::Windows::Forms::Label^  labelZone09AlarmMsg;
	private: System::Windows::Forms::Label^  labelZone08AlarmMsg;
	private: System::Windows::Forms::Label^  labelZone07AlarmMsg;
	private: System::Windows::Forms::Label^  labelZone06AlarmMsg;
	private: System::Windows::Forms::Label^  labelZone05AlarmMsg;
	private: System::Windows::Forms::Label^  labelZone04AlarmMsg;
	private: System::Windows::Forms::Label^  labelZone03AlarmMsg;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
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
			this->labelZone01AlarmMsg = (gcnew System::Windows::Forms::Label());
			this->buttonControlerReset = (gcnew System::Windows::Forms::Button());
			this->labelZone02AlarmMsg = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->labelZone12AlarmMsg = (gcnew System::Windows::Forms::Label());
			this->labelZone11AlarmMsg = (gcnew System::Windows::Forms::Label());
			this->labelZone10AlarmMsg = (gcnew System::Windows::Forms::Label());
			this->labelZone09AlarmMsg = (gcnew System::Windows::Forms::Label());
			this->labelZone08AlarmMsg = (gcnew System::Windows::Forms::Label());
			this->labelZone07AlarmMsg = (gcnew System::Windows::Forms::Label());
			this->labelZone06AlarmMsg = (gcnew System::Windows::Forms::Label());
			this->labelZone05AlarmMsg = (gcnew System::Windows::Forms::Label());
			this->labelZone04AlarmMsg = (gcnew System::Windows::Forms::Label());
			this->labelZone03AlarmMsg = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// labelZone01AlarmMsg
			// 
			this->labelZone01AlarmMsg->AutoSize = true;
			this->labelZone01AlarmMsg->BackColor = System::Drawing::Color::White;
			this->labelZone01AlarmMsg->ForeColor = System::Drawing::Color::Red;
			this->labelZone01AlarmMsg->Location = System::Drawing::Point(78, 13);
			this->labelZone01AlarmMsg->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone01AlarmMsg->Name = L"labelZone01AlarmMsg";
			this->labelZone01AlarmMsg->Size = System::Drawing::Size(152, 16);
			this->labelZone01AlarmMsg->TabIndex = 0;
			this->labelZone01AlarmMsg->Text = L"低于设定点温度警报";
			// 
			// buttonControlerReset
			// 
			this->buttonControlerReset->Location = System::Drawing::Point(431, 172);
			this->buttonControlerReset->Margin = System::Windows::Forms::Padding(4);
			this->buttonControlerReset->Name = L"buttonControlerReset";
			this->buttonControlerReset->Size = System::Drawing::Size(100, 31);
			this->buttonControlerReset->TabIndex = 1;
			this->buttonControlerReset->Text = L"清除警报";
			this->buttonControlerReset->UseVisualStyleBackColor = true;
			this->buttonControlerReset->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::buttonControlerReset_Click);
			// 
			// labelZone02AlarmMsg
			// 
			this->labelZone02AlarmMsg->AutoSize = true;
			this->labelZone02AlarmMsg->ForeColor = System::Drawing::Color::Red;
			this->labelZone02AlarmMsg->Location = System::Drawing::Point(78, 35);
			this->labelZone02AlarmMsg->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone02AlarmMsg->Name = L"labelZone02AlarmMsg";
			this->labelZone02AlarmMsg->Size = System::Drawing::Size(152, 16);
			this->labelZone02AlarmMsg->TabIndex = 2;
			this->labelZone02AlarmMsg->Text = L"低于设定点温度警报";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->labelZone12AlarmMsg);
			this->groupBox1->Controls->Add(this->labelZone11AlarmMsg);
			this->groupBox1->Controls->Add(this->labelZone10AlarmMsg);
			this->groupBox1->Controls->Add(this->labelZone09AlarmMsg);
			this->groupBox1->Controls->Add(this->labelZone08AlarmMsg);
			this->groupBox1->Controls->Add(this->labelZone07AlarmMsg);
			this->groupBox1->Controls->Add(this->labelZone06AlarmMsg);
			this->groupBox1->Controls->Add(this->labelZone05AlarmMsg);
			this->groupBox1->Controls->Add(this->labelZone04AlarmMsg);
			this->groupBox1->Controls->Add(this->labelZone03AlarmMsg);
			this->groupBox1->Controls->Add(this->labelZone01AlarmMsg);
			this->groupBox1->Controls->Add(this->labelZone02AlarmMsg);
			this->groupBox1->Location = System::Drawing::Point(16, 16);
			this->groupBox1->Margin = System::Windows::Forms::Padding(4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(4);
			this->groupBox1->Size = System::Drawing::Size(532, 150);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(292, 121);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(64, 16);
			this->label12->TabIndex = 13;
			this->label12->Text = L"Zone12:";
			this->label12->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::label1_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(7, 121);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(64, 16);
			this->label6->TabIndex = 13;
			this->label6->Text = L"Zone06:";
			this->label6->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::label1_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(292, 99);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(64, 16);
			this->label11->TabIndex = 13;
			this->label11->Text = L"Zone11:";
			this->label11->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::label1_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(7, 99);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(64, 16);
			this->label5->TabIndex = 13;
			this->label5->Text = L"Zone05:";
			this->label5->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::label1_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(292, 78);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(64, 16);
			this->label10->TabIndex = 13;
			this->label10->Text = L"Zone10:";
			this->label10->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::label1_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(7, 78);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(64, 16);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Zone04:";
			this->label4->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::label1_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(292, 57);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(64, 16);
			this->label9->TabIndex = 13;
			this->label9->Text = L"Zone09:";
			this->label9->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::label1_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 57);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(64, 16);
			this->label3->TabIndex = 13;
			this->label3->Text = L"Zone03:";
			this->label3->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::label1_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(292, 35);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(64, 16);
			this->label8->TabIndex = 13;
			this->label8->Text = L"Zone08:";
			this->label8->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::label1_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(292, 13);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(64, 16);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Zone07:";
			this->label7->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 35);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(64, 16);
			this->label2->TabIndex = 13;
			this->label2->Text = L"Zone02:";
			this->label2->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::label1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(64, 16);
			this->label1->TabIndex = 13;
			this->label1->Text = L"Zone01:";
			this->label1->Click += gcnew System::EventHandler(this, &AlarmStatusWindow::label1_Click);
			// 
			// labelZone12AlarmMsg
			// 
			this->labelZone12AlarmMsg->AutoSize = true;
			this->labelZone12AlarmMsg->ForeColor = System::Drawing::Color::Red;
			this->labelZone12AlarmMsg->Location = System::Drawing::Point(363, 121);
			this->labelZone12AlarmMsg->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone12AlarmMsg->Name = L"labelZone12AlarmMsg";
			this->labelZone12AlarmMsg->Size = System::Drawing::Size(152, 16);
			this->labelZone12AlarmMsg->TabIndex = 12;
			this->labelZone12AlarmMsg->Text = L"低于设定点温度警报";
			// 
			// labelZone11AlarmMsg
			// 
			this->labelZone11AlarmMsg->AutoSize = true;
			this->labelZone11AlarmMsg->ForeColor = System::Drawing::Color::Red;
			this->labelZone11AlarmMsg->Location = System::Drawing::Point(363, 99);
			this->labelZone11AlarmMsg->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone11AlarmMsg->Name = L"labelZone11AlarmMsg";
			this->labelZone11AlarmMsg->Size = System::Drawing::Size(152, 16);
			this->labelZone11AlarmMsg->TabIndex = 11;
			this->labelZone11AlarmMsg->Text = L"低于设定点温度警报";
			// 
			// labelZone10AlarmMsg
			// 
			this->labelZone10AlarmMsg->AutoSize = true;
			this->labelZone10AlarmMsg->ForeColor = System::Drawing::Color::Red;
			this->labelZone10AlarmMsg->Location = System::Drawing::Point(363, 78);
			this->labelZone10AlarmMsg->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone10AlarmMsg->Name = L"labelZone10AlarmMsg";
			this->labelZone10AlarmMsg->Size = System::Drawing::Size(152, 16);
			this->labelZone10AlarmMsg->TabIndex = 10;
			this->labelZone10AlarmMsg->Text = L"低于设定点温度警报";
			// 
			// labelZone09AlarmMsg
			// 
			this->labelZone09AlarmMsg->AutoSize = true;
			this->labelZone09AlarmMsg->ForeColor = System::Drawing::Color::Red;
			this->labelZone09AlarmMsg->Location = System::Drawing::Point(363, 57);
			this->labelZone09AlarmMsg->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone09AlarmMsg->Name = L"labelZone09AlarmMsg";
			this->labelZone09AlarmMsg->Size = System::Drawing::Size(152, 16);
			this->labelZone09AlarmMsg->TabIndex = 9;
			this->labelZone09AlarmMsg->Text = L"低于设定点温度警报";
			// 
			// labelZone08AlarmMsg
			// 
			this->labelZone08AlarmMsg->AutoSize = true;
			this->labelZone08AlarmMsg->ForeColor = System::Drawing::Color::Red;
			this->labelZone08AlarmMsg->Location = System::Drawing::Point(363, 35);
			this->labelZone08AlarmMsg->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone08AlarmMsg->Name = L"labelZone08AlarmMsg";
			this->labelZone08AlarmMsg->Size = System::Drawing::Size(152, 16);
			this->labelZone08AlarmMsg->TabIndex = 8;
			this->labelZone08AlarmMsg->Text = L"低于设定点温度警报";
			// 
			// labelZone07AlarmMsg
			// 
			this->labelZone07AlarmMsg->AutoSize = true;
			this->labelZone07AlarmMsg->ForeColor = System::Drawing::Color::Red;
			this->labelZone07AlarmMsg->Location = System::Drawing::Point(363, 13);
			this->labelZone07AlarmMsg->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone07AlarmMsg->Name = L"labelZone07AlarmMsg";
			this->labelZone07AlarmMsg->Size = System::Drawing::Size(152, 16);
			this->labelZone07AlarmMsg->TabIndex = 7;
			this->labelZone07AlarmMsg->Text = L"低于设定点温度警报";
			// 
			// labelZone06AlarmMsg
			// 
			this->labelZone06AlarmMsg->AutoSize = true;
			this->labelZone06AlarmMsg->ForeColor = System::Drawing::Color::Red;
			this->labelZone06AlarmMsg->Location = System::Drawing::Point(78, 121);
			this->labelZone06AlarmMsg->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone06AlarmMsg->Name = L"labelZone06AlarmMsg";
			this->labelZone06AlarmMsg->Size = System::Drawing::Size(152, 16);
			this->labelZone06AlarmMsg->TabIndex = 6;
			this->labelZone06AlarmMsg->Text = L"低于设定点温度警报";
			// 
			// labelZone05AlarmMsg
			// 
			this->labelZone05AlarmMsg->AutoSize = true;
			this->labelZone05AlarmMsg->ForeColor = System::Drawing::Color::Red;
			this->labelZone05AlarmMsg->Location = System::Drawing::Point(78, 99);
			this->labelZone05AlarmMsg->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone05AlarmMsg->Name = L"labelZone05AlarmMsg";
			this->labelZone05AlarmMsg->Size = System::Drawing::Size(152, 16);
			this->labelZone05AlarmMsg->TabIndex = 5;
			this->labelZone05AlarmMsg->Text = L"低于设定点温度警报";
			// 
			// labelZone04AlarmMsg
			// 
			this->labelZone04AlarmMsg->AutoSize = true;
			this->labelZone04AlarmMsg->ForeColor = System::Drawing::Color::Red;
			this->labelZone04AlarmMsg->Location = System::Drawing::Point(78, 78);
			this->labelZone04AlarmMsg->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone04AlarmMsg->Name = L"labelZone04AlarmMsg";
			this->labelZone04AlarmMsg->Size = System::Drawing::Size(152, 16);
			this->labelZone04AlarmMsg->TabIndex = 4;
			this->labelZone04AlarmMsg->Text = L"低于设定点温度警报";
			// 
			// labelZone03AlarmMsg
			// 
			this->labelZone03AlarmMsg->AutoSize = true;
			this->labelZone03AlarmMsg->ForeColor = System::Drawing::Color::Red;
			this->labelZone03AlarmMsg->Location = System::Drawing::Point(78, 57);
			this->labelZone03AlarmMsg->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone03AlarmMsg->Name = L"labelZone03AlarmMsg";
			this->labelZone03AlarmMsg->Size = System::Drawing::Size(152, 16);
			this->labelZone03AlarmMsg->TabIndex = 3;
			this->labelZone03AlarmMsg->Text = L"低于设定点温度警报";
			// 
			// AlarmStatusWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(563, 216);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->buttonControlerReset);
			this->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->Name = L"AlarmStatusWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"警报";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void buttonControlerReset_Click(System::Object^  sender, System::EventArgs^  e) {
			this->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Close();
		}
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
		}
};
}
