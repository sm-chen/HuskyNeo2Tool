#pragma once

#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#include "Husky.h"
#include "IpConfigure.h"
#include "AllZonesTemperatureSetting.h"

#define HUSKY_DEV_NUM 12

namespace HuskyNeo2Tool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 摘要
	///
	/// 警告: 如果更改此类的名称，则需要更改
	///          与此类所依赖的所有 .resx 文件关联的托管资源编译器工具的
	///          “资源文件名”属性。否则，
	///          设计器将不能与此窗体的关联
	///          本地化资源正确交互。
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();

			ipConfig = gcnew IpConfigure();
			huskys = gcnew array<Husky *, 1>(HUSKY_DEV_NUM);
			//for (int i = 0; i < HUSKY_DEV_NUM; i++) {
			//	huskys[i] = new Husky();
			//}

			textBoxIpConfigs = gcnew array<System::Windows::Forms::TextBox^, 1>(HUSKY_DEV_NUM);
			textBoxIpConfigs[0] = ipConfig->textBox1;
			textBoxIpConfigs[1] = ipConfig->textBox2;
			textBoxIpConfigs[2] = ipConfig->textBox3;
			textBoxIpConfigs[3] = ipConfig->textBox4;
			textBoxIpConfigs[4] = ipConfig->textBox5;
			textBoxIpConfigs[5] = ipConfig->textBox6;
			textBoxIpConfigs[6] = ipConfig->textBox7;
			textBoxIpConfigs[7] = ipConfig->textBox8;
			textBoxIpConfigs[8] = ipConfig->textBox9;
			textBoxIpConfigs[9] = ipConfig->textBox10;
			textBoxIpConfigs[10] = ipConfig->textBox11;
			textBoxIpConfigs[11] = ipConfig->textBox12;

			char ipconfigPathBuf[MAX_PATH];
			_getcwd(ipconfigPathBuf, MAX_PATH ); //get current work dir
			int len = strlen(ipconfigPathBuf);
			strcpy(ipconfigPathBuf + len, "\\ipconfig");
			FILE *fp = fopen(ipconfigPathBuf, "rt+"); // if file not exist will return NULL!
			if (fp == NULL) {
				printf("Open Failed.\n");
				for (int i = 0; i < HUSKY_DEV_NUM; i++) {
					huskys[i] = new Husky();
				}
			} else {
				for (int i = 0; i < HUSKY_DEV_NUM; i++) {
					char ipAddressBuf[LINE_LEN_MAX];
					ipAddressBuf[0] = '\0'; // clear buffer
					fgets(ipAddressBuf, LINE_LEN_MAX, fp); //read a line
					int len = strlen(ipAddressBuf);
					if (len < IP_ADDRESS_STRING_LEN && ipAddressBuf[len - 1] == '\n') {
						ipAddressBuf[len - 1] = '\0'; // delete '\n'
					} else {
						ipAddressBuf[IP_ADDRESS_STRING_LEN - 1] = '\0';
					}
					textBoxIpConfigs[i]->Text = gcnew String(ipAddressBuf);
					huskys[i] = new Husky(ipAddressBuf);
				}

				fclose(fp);
			}

			currentHusky = NULL;
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
				delete components;


			for (int i = 0; i < HUSKY_DEV_NUM; i++) {
				if (huskys[i])
					delete huskys[i];
			}
		}
	private:
		IpConfigure ^ipConfig;
		//Husky *huskys[HUSKY_DEV_NUM];
		array<Husky *,1>^ huskys;
		array<System::Windows::Forms::TextBox^, 1>^ textBoxIpConfigs;
		Husky *currentHusky;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	protected: 

	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  labelIpAddr;

	private: System::Windows::Forms::Button^  buttonConnect;
	private: System::Windows::Forms::GroupBox^  groupBoxZones;

	private: System::Windows::Forms::GroupBox^  groupBoxZone01;

	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  buttonZone01TempSet;

	private: System::Windows::Forms::Button^  buttonZone01TempGet;

	private: System::Windows::Forms::TextBox^  textBoxZone01Setpoint;

	private: System::Windows::Forms::Label^  labelZone01RealTemp;


private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::Label^  label27;
private: System::Windows::Forms::GroupBox^  groupBoxZone12;

private: System::Windows::Forms::Label^  label57;
private: System::Windows::Forms::Label^  label58;
private: System::Windows::Forms::Label^  labelZone12RealTemp;
private: System::Windows::Forms::TextBox^  textBoxZone12Setpoint;
private: System::Windows::Forms::Button^  buttonZone12TempSet;

private: System::Windows::Forms::Button^  buttonZone12TempGet;

private: System::Windows::Forms::Label^  label60;
private: System::Windows::Forms::Label^  label61;
private: System::Windows::Forms::GroupBox^  groupBoxZone08;

private: System::Windows::Forms::Label^  label37;
private: System::Windows::Forms::Label^  label38;
private: System::Windows::Forms::Label^  labelZone08RealTemp;
private: System::Windows::Forms::TextBox^  textBoxZone08Setpoint;
private: System::Windows::Forms::Button^  buttonZone08TempSet;

private: System::Windows::Forms::Button^  buttonZone08TempGet;

private: System::Windows::Forms::Label^  label40;
private: System::Windows::Forms::Label^  label41;
private: System::Windows::Forms::GroupBox^  groupBoxZone04;


private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::Label^  labelZone04RealTemp;
private: System::Windows::Forms::TextBox^  textBoxZone04Setpoint;
private: System::Windows::Forms::Button^  buttonZone04TempSet;

private: System::Windows::Forms::Button^  buttonZone04TempGet;

private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::Label^  label18;
private: System::Windows::Forms::GroupBox^  groupBoxZone11;

private: System::Windows::Forms::Label^  label52;
private: System::Windows::Forms::Label^  label53;
private: System::Windows::Forms::Label^  labelZone11RealTemp;
private: System::Windows::Forms::TextBox^  textBoxZone11Setpoint;
private: System::Windows::Forms::Button^  buttonZone11TempSet;

private: System::Windows::Forms::Button^  buttonZone11TempGet;

private: System::Windows::Forms::Label^  label55;
private: System::Windows::Forms::Label^  label56;
private: System::Windows::Forms::GroupBox^  groupBoxZone07;

private: System::Windows::Forms::Label^  label32;
private: System::Windows::Forms::Label^  label33;
private: System::Windows::Forms::Label^  labelZone07RealTemp;
private: System::Windows::Forms::TextBox^  textBoxZone07Setpoint;
private: System::Windows::Forms::Button^  buttonZone07TempSet;

private: System::Windows::Forms::Button^  buttonZone07TempGet;

private: System::Windows::Forms::Label^  label35;
private: System::Windows::Forms::Label^  label36;
private: System::Windows::Forms::GroupBox^  groupBoxZone03;

private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::Label^  labelZone03RealTemp;
private: System::Windows::Forms::TextBox^  textBoxZone03Setpoint;
private: System::Windows::Forms::Button^  buttonZone03TempSet;

private: System::Windows::Forms::Button^  buttonZone03TempGet;

private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::GroupBox^  groupBoxZone10;

private: System::Windows::Forms::Label^  label47;
private: System::Windows::Forms::Label^  label48;
private: System::Windows::Forms::Label^  labelZone10RealTemp;
private: System::Windows::Forms::TextBox^  textBoxZone10Setpoint;
private: System::Windows::Forms::Button^  buttonZone10TempSet;

private: System::Windows::Forms::Button^  buttonZone10TempGet;

private: System::Windows::Forms::Label^  label50;
private: System::Windows::Forms::Label^  label51;
private: System::Windows::Forms::GroupBox^  groupBoxZone09;

private: System::Windows::Forms::Label^  label42;
private: System::Windows::Forms::Label^  label43;
private: System::Windows::Forms::Label^  labelZone09RealTemp;
private: System::Windows::Forms::TextBox^  textBoxZone09Setpoint;
private: System::Windows::Forms::Button^  buttonZone09TempSet;

private: System::Windows::Forms::Button^  buttonZone09TempGet;

private: System::Windows::Forms::Label^  label45;
private: System::Windows::Forms::Label^  label46;
private: System::Windows::Forms::GroupBox^  groupBoxZone06;

private: System::Windows::Forms::Label^  label24;
private: System::Windows::Forms::Label^  label25;
private: System::Windows::Forms::Label^  labelZone06RealTemp;
private: System::Windows::Forms::TextBox^  textBoxZone06Setpoint;
private: System::Windows::Forms::Button^  buttonZone06TempSet;

private: System::Windows::Forms::Button^  buttonZone06TempGet;

private: System::Windows::Forms::Label^  label30;
private: System::Windows::Forms::Label^  label31;
private: System::Windows::Forms::GroupBox^  groupBoxZone05;

private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::Label^  labelZone05RealTemp;
private: System::Windows::Forms::TextBox^  textBoxZone05Setpoint;
private: System::Windows::Forms::Button^  buttonZone05TempSet;

private: System::Windows::Forms::Button^  buttonZone05TempGet;

private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::GroupBox^  groupBoxZone02;

private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Label^  labelZone02RealTemp;
private: System::Windows::Forms::TextBox^  textBoxZone02Setpoint;
private: System::Windows::Forms::Button^  buttonZone02TempSet;

private: System::Windows::Forms::Button^  buttonZone02TempGet;

private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::Button^  button28;
private: System::Windows::Forms::Button^  button27;
private: System::Windows::Forms::Button^  buttonIpConfig;

	private:
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::TextBox^  textBoxAllZonesSetpoint;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxAllZonesSetpoint = (gcnew System::Windows::Forms::TextBox());
			this->button28 = (gcnew System::Windows::Forms::Button());
			this->button27 = (gcnew System::Windows::Forms::Button());
			this->buttonIpConfig = (gcnew System::Windows::Forms::Button());
			this->buttonConnect = (gcnew System::Windows::Forms::Button());
			this->labelIpAddr = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBoxZones = (gcnew System::Windows::Forms::GroupBox());
			this->groupBoxZone12 = (gcnew System::Windows::Forms::GroupBox());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->labelZone12RealTemp = (gcnew System::Windows::Forms::Label());
			this->textBoxZone12Setpoint = (gcnew System::Windows::Forms::TextBox());
			this->buttonZone12TempSet = (gcnew System::Windows::Forms::Button());
			this->buttonZone12TempGet = (gcnew System::Windows::Forms::Button());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone08 = (gcnew System::Windows::Forms::GroupBox());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->labelZone08RealTemp = (gcnew System::Windows::Forms::Label());
			this->textBoxZone08Setpoint = (gcnew System::Windows::Forms::TextBox());
			this->buttonZone08TempSet = (gcnew System::Windows::Forms::Button());
			this->buttonZone08TempGet = (gcnew System::Windows::Forms::Button());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone04 = (gcnew System::Windows::Forms::GroupBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->labelZone04RealTemp = (gcnew System::Windows::Forms::Label());
			this->textBoxZone04Setpoint = (gcnew System::Windows::Forms::TextBox());
			this->buttonZone04TempSet = (gcnew System::Windows::Forms::Button());
			this->buttonZone04TempGet = (gcnew System::Windows::Forms::Button());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone11 = (gcnew System::Windows::Forms::GroupBox());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->labelZone11RealTemp = (gcnew System::Windows::Forms::Label());
			this->textBoxZone11Setpoint = (gcnew System::Windows::Forms::TextBox());
			this->buttonZone11TempSet = (gcnew System::Windows::Forms::Button());
			this->buttonZone11TempGet = (gcnew System::Windows::Forms::Button());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone07 = (gcnew System::Windows::Forms::GroupBox());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->labelZone07RealTemp = (gcnew System::Windows::Forms::Label());
			this->textBoxZone07Setpoint = (gcnew System::Windows::Forms::TextBox());
			this->buttonZone07TempSet = (gcnew System::Windows::Forms::Button());
			this->buttonZone07TempGet = (gcnew System::Windows::Forms::Button());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone03 = (gcnew System::Windows::Forms::GroupBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->labelZone03RealTemp = (gcnew System::Windows::Forms::Label());
			this->textBoxZone03Setpoint = (gcnew System::Windows::Forms::TextBox());
			this->buttonZone03TempSet = (gcnew System::Windows::Forms::Button());
			this->buttonZone03TempGet = (gcnew System::Windows::Forms::Button());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone10 = (gcnew System::Windows::Forms::GroupBox());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->labelZone10RealTemp = (gcnew System::Windows::Forms::Label());
			this->textBoxZone10Setpoint = (gcnew System::Windows::Forms::TextBox());
			this->buttonZone10TempSet = (gcnew System::Windows::Forms::Button());
			this->buttonZone10TempGet = (gcnew System::Windows::Forms::Button());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone09 = (gcnew System::Windows::Forms::GroupBox());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->labelZone09RealTemp = (gcnew System::Windows::Forms::Label());
			this->textBoxZone09Setpoint = (gcnew System::Windows::Forms::TextBox());
			this->buttonZone09TempSet = (gcnew System::Windows::Forms::Button());
			this->buttonZone09TempGet = (gcnew System::Windows::Forms::Button());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone06 = (gcnew System::Windows::Forms::GroupBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->labelZone06RealTemp = (gcnew System::Windows::Forms::Label());
			this->textBoxZone06Setpoint = (gcnew System::Windows::Forms::TextBox());
			this->buttonZone06TempSet = (gcnew System::Windows::Forms::Button());
			this->buttonZone06TempGet = (gcnew System::Windows::Forms::Button());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone05 = (gcnew System::Windows::Forms::GroupBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->labelZone05RealTemp = (gcnew System::Windows::Forms::Label());
			this->textBoxZone05Setpoint = (gcnew System::Windows::Forms::TextBox());
			this->buttonZone05TempSet = (gcnew System::Windows::Forms::Button());
			this->buttonZone05TempGet = (gcnew System::Windows::Forms::Button());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone02 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->labelZone02RealTemp = (gcnew System::Windows::Forms::Label());
			this->textBoxZone02Setpoint = (gcnew System::Windows::Forms::TextBox());
			this->buttonZone02TempSet = (gcnew System::Windows::Forms::Button());
			this->buttonZone02TempGet = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone01 = (gcnew System::Windows::Forms::GroupBox());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->labelZone01RealTemp = (gcnew System::Windows::Forms::Label());
			this->textBoxZone01Setpoint = (gcnew System::Windows::Forms::TextBox());
			this->buttonZone01TempSet = (gcnew System::Windows::Forms::Button());
			this->buttonZone01TempGet = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBoxZones->SuspendLayout();
			this->groupBoxZone12->SuspendLayout();
			this->groupBoxZone08->SuspendLayout();
			this->groupBoxZone04->SuspendLayout();
			this->groupBoxZone11->SuspendLayout();
			this->groupBoxZone07->SuspendLayout();
			this->groupBoxZone03->SuspendLayout();
			this->groupBoxZone10->SuspendLayout();
			this->groupBoxZone09->SuspendLayout();
			this->groupBoxZone06->SuspendLayout();
			this->groupBoxZone05->SuspendLayout();
			this->groupBoxZone02->SuspendLayout();
			this->groupBoxZone01->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->AutoSize = true;
			this->groupBox1->BackColor = System::Drawing::SystemColors::Window;
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->textBoxAllZonesSetpoint);
			this->groupBox1->Controls->Add(this->button28);
			this->groupBox1->Controls->Add(this->button27);
			this->groupBox1->Controls->Add(this->buttonIpConfig);
			this->groupBox1->Controls->Add(this->buttonConnect);
			this->groupBox1->Controls->Add(this->labelIpAddr);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(733, 60);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(602, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(17, 12);
			this->label1->TabIndex = 12;
			this->label1->Text = L"℃";
			// 
			// textBoxAllZonesSetpoint
			// 
			this->textBoxAllZonesSetpoint->Location = System::Drawing::Point(559, 18);
			this->textBoxAllZonesSetpoint->Name = L"textBoxAllZonesSetpoint";
			this->textBoxAllZonesSetpoint->Size = System::Drawing::Size(42, 21);
			this->textBoxAllZonesSetpoint->TabIndex = 11;
			// 
			// button28
			// 
			this->button28->Location = System::Drawing::Point(619, 17);
			this->button28->Name = L"button28";
			this->button28->Size = System::Drawing::Size(108, 23);
			this->button28->TabIndex = 10;
			this->button28->Text = L"全区域温度设置";
			this->button28->UseVisualStyleBackColor = true;
			this->button28->Click += gcnew System::EventHandler(this, &Form1::button28_Click);
			// 
			// button27
			// 
			this->button27->Location = System::Drawing::Point(434, 17);
			this->button27->Name = L"button27";
			this->button27->Size = System::Drawing::Size(107, 23);
			this->button27->TabIndex = 9;
			this->button27->Text = L"全区域温度读取";
			this->button27->UseVisualStyleBackColor = true;
			this->button27->Click += gcnew System::EventHandler(this, &Form1::button27_Click);
			// 
			// buttonIpConfig
			// 
			this->buttonIpConfig->Location = System::Drawing::Point(289, 17);
			this->buttonIpConfig->Name = L"buttonIpConfig";
			this->buttonIpConfig->Size = System::Drawing::Size(75, 23);
			this->buttonIpConfig->TabIndex = 8;
			this->buttonIpConfig->Text = L"IP配置";
			this->buttonIpConfig->UseVisualStyleBackColor = true;
			this->buttonIpConfig->Click += gcnew System::EventHandler(this, &Form1::buttonIpConfig_Click);
			// 
			// buttonConnect
			// 
			this->buttonConnect->Location = System::Drawing::Point(204, 17);
			this->buttonConnect->Name = L"buttonConnect";
			this->buttonConnect->Size = System::Drawing::Size(75, 23);
			this->buttonConnect->TabIndex = 7;
			this->buttonConnect->Text = L"连接";
			this->buttonConnect->UseVisualStyleBackColor = true;
			this->buttonConnect->Click += gcnew System::EventHandler(this, &Form1::buttonConnect_Click);
			// 
			// labelIpAddr
			// 
			this->labelIpAddr->AutoSize = true;
			this->labelIpAddr->Location = System::Drawing::Point(89, 23);
			this->labelIpAddr->Name = L"labelIpAddr";
			this->labelIpAddr->Size = System::Drawing::Size(29, 12);
			this->labelIpAddr->TabIndex = 6;
			this->labelIpAddr->Text = L"IP: ";
			// 
			// comboBox1
			// 
			this->comboBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(12) {L"机台01", L"机台02", L"机台03", L"机台04", L"机台05", L"机台06", 
				L"机台07", L"机台08", L"机台09", L"机台10", L"机台11", L"机台12"});
			this->comboBox1->Location = System::Drawing::Point(9, 20);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(74, 20);
			this->comboBox1->TabIndex = 5;
			this->comboBox1->Text = L"选择机台";
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox1_SelectedIndexChanged);
			// 
			// groupBoxZones
			// 
			this->groupBoxZones->Controls->Add(this->groupBoxZone12);
			this->groupBoxZones->Controls->Add(this->groupBoxZone08);
			this->groupBoxZones->Controls->Add(this->groupBoxZone04);
			this->groupBoxZones->Controls->Add(this->groupBoxZone11);
			this->groupBoxZones->Controls->Add(this->groupBoxZone07);
			this->groupBoxZones->Controls->Add(this->groupBoxZone03);
			this->groupBoxZones->Controls->Add(this->groupBoxZone10);
			this->groupBoxZones->Controls->Add(this->groupBoxZone09);
			this->groupBoxZones->Controls->Add(this->groupBoxZone06);
			this->groupBoxZones->Controls->Add(this->groupBoxZone05);
			this->groupBoxZones->Controls->Add(this->groupBoxZone02);
			this->groupBoxZones->Controls->Add(this->groupBoxZone01);
			this->groupBoxZones->Location = System::Drawing::Point(12, 69);
			this->groupBoxZones->Name = L"groupBoxZones";
			this->groupBoxZones->Size = System::Drawing::Size(733, 381);
			this->groupBoxZones->TabIndex = 1;
			this->groupBoxZones->TabStop = false;
			// 
			// groupBoxZone12
			// 
			this->groupBoxZone12->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone12->Controls->Add(this->label57);
			this->groupBoxZone12->Controls->Add(this->label58);
			this->groupBoxZone12->Controls->Add(this->labelZone12RealTemp);
			this->groupBoxZone12->Controls->Add(this->textBoxZone12Setpoint);
			this->groupBoxZone12->Controls->Add(this->buttonZone12TempSet);
			this->groupBoxZone12->Controls->Add(this->buttonZone12TempGet);
			this->groupBoxZone12->Controls->Add(this->label60);
			this->groupBoxZone12->Controls->Add(this->label61);
			this->groupBoxZone12->Location = System::Drawing::Point(552, 258);
			this->groupBoxZone12->Name = L"groupBoxZone12";
			this->groupBoxZone12->Size = System::Drawing::Size(175, 113);
			this->groupBoxZone12->TabIndex = 0;
			this->groupBoxZone12->TabStop = false;
			this->groupBoxZone12->Text = L"Zone12";
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->Location = System::Drawing::Point(135, 49);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(17, 12);
			this->label57->TabIndex = 6;
			this->label57->Text = L"℃";
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->Location = System::Drawing::Point(135, 24);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(17, 12);
			this->label58->TabIndex = 6;
			this->label58->Text = L"℃";
			// 
			// labelZone12RealTemp
			// 
			this->labelZone12RealTemp->AutoSize = true;
			this->labelZone12RealTemp->Location = System::Drawing::Point(82, 23);
			this->labelZone12RealTemp->Name = L"labelZone12RealTemp";
			this->labelZone12RealTemp->Size = System::Drawing::Size(23, 12);
			this->labelZone12RealTemp->TabIndex = 5;
			this->labelZone12RealTemp->Text = L"0.0";
			// 
			// textBoxZone12Setpoint
			// 
			this->textBoxZone12Setpoint->Location = System::Drawing::Point(81, 43);
			this->textBoxZone12Setpoint->Name = L"textBoxZone12Setpoint";
			this->textBoxZone12Setpoint->Size = System::Drawing::Size(45, 21);
			this->textBoxZone12Setpoint->TabIndex = 4;
			this->textBoxZone12Setpoint->Text = L"0.0";
			// 
			// buttonZone12TempSet
			// 
			this->buttonZone12TempSet->Location = System::Drawing::Point(87, 78);
			this->buttonZone12TempSet->Name = L"buttonZone12TempSet";
			this->buttonZone12TempSet->Size = System::Drawing::Size(66, 23);
			this->buttonZone12TempSet->TabIndex = 3;
			this->buttonZone12TempSet->Text = L"设置温度";
			this->buttonZone12TempSet->UseVisualStyleBackColor = true;
			this->buttonZone12TempSet->Click += gcnew System::EventHandler(this, &Form1::buttonZone12TempSet_Click);
			// 
			// buttonZone12TempGet
			// 
			this->buttonZone12TempGet->Location = System::Drawing::Point(15, 78);
			this->buttonZone12TempGet->Name = L"buttonZone12TempGet";
			this->buttonZone12TempGet->Size = System::Drawing::Size(66, 23);
			this->buttonZone12TempGet->TabIndex = 2;
			this->buttonZone12TempGet->Text = L"读取温度";
			this->buttonZone12TempGet->UseVisualStyleBackColor = true;
			this->buttonZone12TempGet->Click += gcnew System::EventHandler(this, &Form1::buttonZone12TempGet_Click);
			// 
			// label60
			// 
			this->label60->AutoSize = true;
			this->label60->Location = System::Drawing::Point(13, 49);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(65, 12);
			this->label60->TabIndex = 1;
			this->label60->Text = L"设定温度: ";
			// 
			// label61
			// 
			this->label61->AutoSize = true;
			this->label61->Location = System::Drawing::Point(13, 23);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(65, 12);
			this->label61->TabIndex = 0;
			this->label61->Text = L"实时温度: ";
			// 
			// groupBoxZone08
			// 
			this->groupBoxZone08->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone08->Controls->Add(this->label37);
			this->groupBoxZone08->Controls->Add(this->label38);
			this->groupBoxZone08->Controls->Add(this->labelZone08RealTemp);
			this->groupBoxZone08->Controls->Add(this->textBoxZone08Setpoint);
			this->groupBoxZone08->Controls->Add(this->buttonZone08TempSet);
			this->groupBoxZone08->Controls->Add(this->buttonZone08TempGet);
			this->groupBoxZone08->Controls->Add(this->label40);
			this->groupBoxZone08->Controls->Add(this->label41);
			this->groupBoxZone08->Location = System::Drawing::Point(552, 139);
			this->groupBoxZone08->Name = L"groupBoxZone08";
			this->groupBoxZone08->Size = System::Drawing::Size(175, 113);
			this->groupBoxZone08->TabIndex = 0;
			this->groupBoxZone08->TabStop = false;
			this->groupBoxZone08->Text = L"Zone08";
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(135, 49);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(17, 12);
			this->label37->TabIndex = 6;
			this->label37->Text = L"℃";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(135, 24);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(17, 12);
			this->label38->TabIndex = 6;
			this->label38->Text = L"℃";
			// 
			// labelZone08RealTemp
			// 
			this->labelZone08RealTemp->AutoSize = true;
			this->labelZone08RealTemp->Location = System::Drawing::Point(82, 23);
			this->labelZone08RealTemp->Name = L"labelZone08RealTemp";
			this->labelZone08RealTemp->Size = System::Drawing::Size(23, 12);
			this->labelZone08RealTemp->TabIndex = 5;
			this->labelZone08RealTemp->Text = L"0.0";
			// 
			// textBoxZone08Setpoint
			// 
			this->textBoxZone08Setpoint->Location = System::Drawing::Point(81, 43);
			this->textBoxZone08Setpoint->Name = L"textBoxZone08Setpoint";
			this->textBoxZone08Setpoint->Size = System::Drawing::Size(45, 21);
			this->textBoxZone08Setpoint->TabIndex = 4;
			this->textBoxZone08Setpoint->Text = L"0.0";
			// 
			// buttonZone08TempSet
			// 
			this->buttonZone08TempSet->Location = System::Drawing::Point(87, 78);
			this->buttonZone08TempSet->Name = L"buttonZone08TempSet";
			this->buttonZone08TempSet->Size = System::Drawing::Size(66, 23);
			this->buttonZone08TempSet->TabIndex = 3;
			this->buttonZone08TempSet->Text = L"设置温度";
			this->buttonZone08TempSet->UseVisualStyleBackColor = true;
			this->buttonZone08TempSet->Click += gcnew System::EventHandler(this, &Form1::buttonZone08TempSet_Click);
			// 
			// buttonZone08TempGet
			// 
			this->buttonZone08TempGet->Location = System::Drawing::Point(15, 78);
			this->buttonZone08TempGet->Name = L"buttonZone08TempGet";
			this->buttonZone08TempGet->Size = System::Drawing::Size(66, 23);
			this->buttonZone08TempGet->TabIndex = 2;
			this->buttonZone08TempGet->Text = L"读取温度";
			this->buttonZone08TempGet->UseVisualStyleBackColor = true;
			this->buttonZone08TempGet->Click += gcnew System::EventHandler(this, &Form1::buttonZone08TempGet_Click);
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(13, 49);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(65, 12);
			this->label40->TabIndex = 1;
			this->label40->Text = L"设定温度: ";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(13, 23);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(65, 12);
			this->label41->TabIndex = 0;
			this->label41->Text = L"实时温度: ";
			// 
			// groupBoxZone04
			// 
			this->groupBoxZone04->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone04->Controls->Add(this->label14);
			this->groupBoxZone04->Controls->Add(this->label15);
			this->groupBoxZone04->Controls->Add(this->labelZone04RealTemp);
			this->groupBoxZone04->Controls->Add(this->textBoxZone04Setpoint);
			this->groupBoxZone04->Controls->Add(this->buttonZone04TempSet);
			this->groupBoxZone04->Controls->Add(this->buttonZone04TempGet);
			this->groupBoxZone04->Controls->Add(this->label17);
			this->groupBoxZone04->Controls->Add(this->label18);
			this->groupBoxZone04->Location = System::Drawing::Point(552, 20);
			this->groupBoxZone04->Name = L"groupBoxZone04";
			this->groupBoxZone04->Size = System::Drawing::Size(175, 113);
			this->groupBoxZone04->TabIndex = 0;
			this->groupBoxZone04->TabStop = false;
			this->groupBoxZone04->Text = L"Zone04";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(135, 49);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(17, 12);
			this->label14->TabIndex = 6;
			this->label14->Text = L"℃";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(135, 24);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(17, 12);
			this->label15->TabIndex = 6;
			this->label15->Text = L"℃";
			// 
			// labelZone04RealTemp
			// 
			this->labelZone04RealTemp->AutoSize = true;
			this->labelZone04RealTemp->Location = System::Drawing::Point(82, 23);
			this->labelZone04RealTemp->Name = L"labelZone04RealTemp";
			this->labelZone04RealTemp->Size = System::Drawing::Size(23, 12);
			this->labelZone04RealTemp->TabIndex = 5;
			this->labelZone04RealTemp->Text = L"0.0";
			// 
			// textBoxZone04Setpoint
			// 
			this->textBoxZone04Setpoint->Location = System::Drawing::Point(82, 43);
			this->textBoxZone04Setpoint->Name = L"textBoxZone04Setpoint";
			this->textBoxZone04Setpoint->Size = System::Drawing::Size(45, 21);
			this->textBoxZone04Setpoint->TabIndex = 4;
			this->textBoxZone04Setpoint->Text = L"0.0";
			// 
			// buttonZone04TempSet
			// 
			this->buttonZone04TempSet->Location = System::Drawing::Point(87, 78);
			this->buttonZone04TempSet->Name = L"buttonZone04TempSet";
			this->buttonZone04TempSet->Size = System::Drawing::Size(66, 23);
			this->buttonZone04TempSet->TabIndex = 3;
			this->buttonZone04TempSet->Text = L"设置温度";
			this->buttonZone04TempSet->UseVisualStyleBackColor = true;
			this->buttonZone04TempSet->Click += gcnew System::EventHandler(this, &Form1::buttonZone04TempSet_Click);
			// 
			// buttonZone04TempGet
			// 
			this->buttonZone04TempGet->Location = System::Drawing::Point(15, 78);
			this->buttonZone04TempGet->Name = L"buttonZone04TempGet";
			this->buttonZone04TempGet->Size = System::Drawing::Size(66, 23);
			this->buttonZone04TempGet->TabIndex = 2;
			this->buttonZone04TempGet->Text = L"读取温度";
			this->buttonZone04TempGet->UseVisualStyleBackColor = true;
			this->buttonZone04TempGet->Click += gcnew System::EventHandler(this, &Form1::buttonZone04TempGet_Click);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(13, 49);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(65, 12);
			this->label17->TabIndex = 1;
			this->label17->Text = L"设定温度: ";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(13, 23);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(65, 12);
			this->label18->TabIndex = 0;
			this->label18->Text = L"实时温度: ";
			// 
			// groupBoxZone11
			// 
			this->groupBoxZone11->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone11->Controls->Add(this->label52);
			this->groupBoxZone11->Controls->Add(this->label53);
			this->groupBoxZone11->Controls->Add(this->labelZone11RealTemp);
			this->groupBoxZone11->Controls->Add(this->textBoxZone11Setpoint);
			this->groupBoxZone11->Controls->Add(this->buttonZone11TempSet);
			this->groupBoxZone11->Controls->Add(this->buttonZone11TempGet);
			this->groupBoxZone11->Controls->Add(this->label55);
			this->groupBoxZone11->Controls->Add(this->label56);
			this->groupBoxZone11->Location = System::Drawing::Point(369, 258);
			this->groupBoxZone11->Name = L"groupBoxZone11";
			this->groupBoxZone11->Size = System::Drawing::Size(175, 113);
			this->groupBoxZone11->TabIndex = 0;
			this->groupBoxZone11->TabStop = false;
			this->groupBoxZone11->Text = L"Zone11";
			// 
			// label52
			// 
			this->label52->AutoSize = true;
			this->label52->Location = System::Drawing::Point(135, 49);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(17, 12);
			this->label52->TabIndex = 6;
			this->label52->Text = L"℃";
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->Location = System::Drawing::Point(135, 24);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(17, 12);
			this->label53->TabIndex = 6;
			this->label53->Text = L"℃";
			// 
			// labelZone11RealTemp
			// 
			this->labelZone11RealTemp->AutoSize = true;
			this->labelZone11RealTemp->Location = System::Drawing::Point(82, 23);
			this->labelZone11RealTemp->Name = L"labelZone11RealTemp";
			this->labelZone11RealTemp->Size = System::Drawing::Size(23, 12);
			this->labelZone11RealTemp->TabIndex = 5;
			this->labelZone11RealTemp->Text = L"0.0";
			// 
			// textBoxZone11Setpoint
			// 
			this->textBoxZone11Setpoint->Location = System::Drawing::Point(81, 43);
			this->textBoxZone11Setpoint->Name = L"textBoxZone11Setpoint";
			this->textBoxZone11Setpoint->Size = System::Drawing::Size(45, 21);
			this->textBoxZone11Setpoint->TabIndex = 4;
			this->textBoxZone11Setpoint->Text = L"0.0";
			// 
			// buttonZone11TempSet
			// 
			this->buttonZone11TempSet->Location = System::Drawing::Point(87, 78);
			this->buttonZone11TempSet->Name = L"buttonZone11TempSet";
			this->buttonZone11TempSet->Size = System::Drawing::Size(66, 23);
			this->buttonZone11TempSet->TabIndex = 3;
			this->buttonZone11TempSet->Text = L"设置温度";
			this->buttonZone11TempSet->UseVisualStyleBackColor = true;
			this->buttonZone11TempSet->Click += gcnew System::EventHandler(this, &Form1::buttonZone11TempSet_Click);
			// 
			// buttonZone11TempGet
			// 
			this->buttonZone11TempGet->Location = System::Drawing::Point(15, 78);
			this->buttonZone11TempGet->Name = L"buttonZone11TempGet";
			this->buttonZone11TempGet->Size = System::Drawing::Size(66, 23);
			this->buttonZone11TempGet->TabIndex = 2;
			this->buttonZone11TempGet->Text = L"读取温度";
			this->buttonZone11TempGet->UseVisualStyleBackColor = true;
			this->buttonZone11TempGet->Click += gcnew System::EventHandler(this, &Form1::buttonZone11TempGet_Click);
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->Location = System::Drawing::Point(13, 49);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(65, 12);
			this->label55->TabIndex = 1;
			this->label55->Text = L"设定温度: ";
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->Location = System::Drawing::Point(13, 23);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(65, 12);
			this->label56->TabIndex = 0;
			this->label56->Text = L"实时温度: ";
			// 
			// groupBoxZone07
			// 
			this->groupBoxZone07->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone07->Controls->Add(this->label32);
			this->groupBoxZone07->Controls->Add(this->label33);
			this->groupBoxZone07->Controls->Add(this->labelZone07RealTemp);
			this->groupBoxZone07->Controls->Add(this->textBoxZone07Setpoint);
			this->groupBoxZone07->Controls->Add(this->buttonZone07TempSet);
			this->groupBoxZone07->Controls->Add(this->buttonZone07TempGet);
			this->groupBoxZone07->Controls->Add(this->label35);
			this->groupBoxZone07->Controls->Add(this->label36);
			this->groupBoxZone07->Location = System::Drawing::Point(369, 139);
			this->groupBoxZone07->Name = L"groupBoxZone07";
			this->groupBoxZone07->Size = System::Drawing::Size(175, 113);
			this->groupBoxZone07->TabIndex = 0;
			this->groupBoxZone07->TabStop = false;
			this->groupBoxZone07->Text = L"Zone07";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(135, 49);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(17, 12);
			this->label32->TabIndex = 6;
			this->label32->Text = L"℃";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(135, 24);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(17, 12);
			this->label33->TabIndex = 6;
			this->label33->Text = L"℃";
			// 
			// labelZone07RealTemp
			// 
			this->labelZone07RealTemp->AutoSize = true;
			this->labelZone07RealTemp->Location = System::Drawing::Point(82, 23);
			this->labelZone07RealTemp->Name = L"labelZone07RealTemp";
			this->labelZone07RealTemp->Size = System::Drawing::Size(23, 12);
			this->labelZone07RealTemp->TabIndex = 5;
			this->labelZone07RealTemp->Text = L"0.0";
			// 
			// textBoxZone07Setpoint
			// 
			this->textBoxZone07Setpoint->Location = System::Drawing::Point(81, 43);
			this->textBoxZone07Setpoint->Name = L"textBoxZone07Setpoint";
			this->textBoxZone07Setpoint->Size = System::Drawing::Size(45, 21);
			this->textBoxZone07Setpoint->TabIndex = 4;
			this->textBoxZone07Setpoint->Text = L"0.0";
			// 
			// buttonZone07TempSet
			// 
			this->buttonZone07TempSet->Location = System::Drawing::Point(87, 78);
			this->buttonZone07TempSet->Name = L"buttonZone07TempSet";
			this->buttonZone07TempSet->Size = System::Drawing::Size(66, 23);
			this->buttonZone07TempSet->TabIndex = 3;
			this->buttonZone07TempSet->Text = L"设置温度";
			this->buttonZone07TempSet->UseVisualStyleBackColor = true;
			this->buttonZone07TempSet->Click += gcnew System::EventHandler(this, &Form1::buttonZone07TempSet_Click);
			// 
			// buttonZone07TempGet
			// 
			this->buttonZone07TempGet->Location = System::Drawing::Point(15, 78);
			this->buttonZone07TempGet->Name = L"buttonZone07TempGet";
			this->buttonZone07TempGet->Size = System::Drawing::Size(66, 23);
			this->buttonZone07TempGet->TabIndex = 2;
			this->buttonZone07TempGet->Text = L"读取温度";
			this->buttonZone07TempGet->UseVisualStyleBackColor = true;
			this->buttonZone07TempGet->Click += gcnew System::EventHandler(this, &Form1::buttonZone07TempGet_Click);
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(13, 49);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(65, 12);
			this->label35->TabIndex = 1;
			this->label35->Text = L"设定温度: ";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(13, 23);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(65, 12);
			this->label36->TabIndex = 0;
			this->label36->Text = L"实时温度: ";
			// 
			// groupBoxZone03
			// 
			this->groupBoxZone03->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone03->Controls->Add(this->label9);
			this->groupBoxZone03->Controls->Add(this->label10);
			this->groupBoxZone03->Controls->Add(this->labelZone03RealTemp);
			this->groupBoxZone03->Controls->Add(this->textBoxZone03Setpoint);
			this->groupBoxZone03->Controls->Add(this->buttonZone03TempSet);
			this->groupBoxZone03->Controls->Add(this->buttonZone03TempGet);
			this->groupBoxZone03->Controls->Add(this->label12);
			this->groupBoxZone03->Controls->Add(this->label13);
			this->groupBoxZone03->Location = System::Drawing::Point(369, 20);
			this->groupBoxZone03->Name = L"groupBoxZone03";
			this->groupBoxZone03->Size = System::Drawing::Size(175, 113);
			this->groupBoxZone03->TabIndex = 0;
			this->groupBoxZone03->TabStop = false;
			this->groupBoxZone03->Text = L"Zone03";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(135, 49);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(17, 12);
			this->label9->TabIndex = 6;
			this->label9->Text = L"℃";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(135, 24);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(17, 12);
			this->label10->TabIndex = 6;
			this->label10->Text = L"℃";
			// 
			// labelZone03RealTemp
			// 
			this->labelZone03RealTemp->AutoSize = true;
			this->labelZone03RealTemp->Location = System::Drawing::Point(82, 23);
			this->labelZone03RealTemp->Name = L"labelZone03RealTemp";
			this->labelZone03RealTemp->Size = System::Drawing::Size(23, 12);
			this->labelZone03RealTemp->TabIndex = 5;
			this->labelZone03RealTemp->Text = L"0.0";
			// 
			// textBoxZone03Setpoint
			// 
			this->textBoxZone03Setpoint->Location = System::Drawing::Point(82, 43);
			this->textBoxZone03Setpoint->Name = L"textBoxZone03Setpoint";
			this->textBoxZone03Setpoint->Size = System::Drawing::Size(45, 21);
			this->textBoxZone03Setpoint->TabIndex = 4;
			this->textBoxZone03Setpoint->Text = L"0.0";
			// 
			// buttonZone03TempSet
			// 
			this->buttonZone03TempSet->Location = System::Drawing::Point(87, 78);
			this->buttonZone03TempSet->Name = L"buttonZone03TempSet";
			this->buttonZone03TempSet->Size = System::Drawing::Size(66, 23);
			this->buttonZone03TempSet->TabIndex = 3;
			this->buttonZone03TempSet->Text = L"设置温度";
			this->buttonZone03TempSet->UseVisualStyleBackColor = true;
			this->buttonZone03TempSet->Click += gcnew System::EventHandler(this, &Form1::buttonZone03TempSet_Click);
			// 
			// buttonZone03TempGet
			// 
			this->buttonZone03TempGet->Location = System::Drawing::Point(15, 78);
			this->buttonZone03TempGet->Name = L"buttonZone03TempGet";
			this->buttonZone03TempGet->Size = System::Drawing::Size(66, 23);
			this->buttonZone03TempGet->TabIndex = 2;
			this->buttonZone03TempGet->Text = L"读取温度";
			this->buttonZone03TempGet->UseVisualStyleBackColor = true;
			this->buttonZone03TempGet->Click += gcnew System::EventHandler(this, &Form1::buttonZone03TempGet_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(13, 49);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(65, 12);
			this->label12->TabIndex = 1;
			this->label12->Text = L"设定温度: ";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(13, 23);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(65, 12);
			this->label13->TabIndex = 0;
			this->label13->Text = L"实时温度: ";
			// 
			// groupBoxZone10
			// 
			this->groupBoxZone10->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone10->Controls->Add(this->label47);
			this->groupBoxZone10->Controls->Add(this->label48);
			this->groupBoxZone10->Controls->Add(this->labelZone10RealTemp);
			this->groupBoxZone10->Controls->Add(this->textBoxZone10Setpoint);
			this->groupBoxZone10->Controls->Add(this->buttonZone10TempSet);
			this->groupBoxZone10->Controls->Add(this->buttonZone10TempGet);
			this->groupBoxZone10->Controls->Add(this->label50);
			this->groupBoxZone10->Controls->Add(this->label51);
			this->groupBoxZone10->Location = System::Drawing::Point(188, 258);
			this->groupBoxZone10->Name = L"groupBoxZone10";
			this->groupBoxZone10->Size = System::Drawing::Size(175, 113);
			this->groupBoxZone10->TabIndex = 0;
			this->groupBoxZone10->TabStop = false;
			this->groupBoxZone10->Text = L"Zone10";
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->Location = System::Drawing::Point(135, 49);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(17, 12);
			this->label47->TabIndex = 6;
			this->label47->Text = L"℃";
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->Location = System::Drawing::Point(135, 24);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(17, 12);
			this->label48->TabIndex = 6;
			this->label48->Text = L"℃";
			// 
			// labelZone10RealTemp
			// 
			this->labelZone10RealTemp->AutoSize = true;
			this->labelZone10RealTemp->Location = System::Drawing::Point(82, 23);
			this->labelZone10RealTemp->Name = L"labelZone10RealTemp";
			this->labelZone10RealTemp->Size = System::Drawing::Size(23, 12);
			this->labelZone10RealTemp->TabIndex = 5;
			this->labelZone10RealTemp->Text = L"0.0";
			// 
			// textBoxZone10Setpoint
			// 
			this->textBoxZone10Setpoint->Location = System::Drawing::Point(81, 43);
			this->textBoxZone10Setpoint->Name = L"textBoxZone10Setpoint";
			this->textBoxZone10Setpoint->Size = System::Drawing::Size(45, 21);
			this->textBoxZone10Setpoint->TabIndex = 4;
			this->textBoxZone10Setpoint->Text = L"0.0";
			// 
			// buttonZone10TempSet
			// 
			this->buttonZone10TempSet->Location = System::Drawing::Point(87, 78);
			this->buttonZone10TempSet->Name = L"buttonZone10TempSet";
			this->buttonZone10TempSet->Size = System::Drawing::Size(66, 23);
			this->buttonZone10TempSet->TabIndex = 3;
			this->buttonZone10TempSet->Text = L"设置温度";
			this->buttonZone10TempSet->UseVisualStyleBackColor = true;
			this->buttonZone10TempSet->Click += gcnew System::EventHandler(this, &Form1::buttonZone10TempSet_Click);
			// 
			// buttonZone10TempGet
			// 
			this->buttonZone10TempGet->Location = System::Drawing::Point(15, 78);
			this->buttonZone10TempGet->Name = L"buttonZone10TempGet";
			this->buttonZone10TempGet->Size = System::Drawing::Size(66, 23);
			this->buttonZone10TempGet->TabIndex = 2;
			this->buttonZone10TempGet->Text = L"读取温度";
			this->buttonZone10TempGet->UseVisualStyleBackColor = true;
			this->buttonZone10TempGet->Click += gcnew System::EventHandler(this, &Form1::buttonZone10TempGet_Click);
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->Location = System::Drawing::Point(13, 49);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(65, 12);
			this->label50->TabIndex = 1;
			this->label50->Text = L"设定温度: ";
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->Location = System::Drawing::Point(13, 23);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(65, 12);
			this->label51->TabIndex = 0;
			this->label51->Text = L"实时温度: ";
			// 
			// groupBoxZone09
			// 
			this->groupBoxZone09->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone09->Controls->Add(this->label42);
			this->groupBoxZone09->Controls->Add(this->label43);
			this->groupBoxZone09->Controls->Add(this->labelZone09RealTemp);
			this->groupBoxZone09->Controls->Add(this->textBoxZone09Setpoint);
			this->groupBoxZone09->Controls->Add(this->buttonZone09TempSet);
			this->groupBoxZone09->Controls->Add(this->buttonZone09TempGet);
			this->groupBoxZone09->Controls->Add(this->label45);
			this->groupBoxZone09->Controls->Add(this->label46);
			this->groupBoxZone09->Location = System::Drawing::Point(7, 258);
			this->groupBoxZone09->Name = L"groupBoxZone09";
			this->groupBoxZone09->Size = System::Drawing::Size(175, 113);
			this->groupBoxZone09->TabIndex = 0;
			this->groupBoxZone09->TabStop = false;
			this->groupBoxZone09->Text = L"Zone09";
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Location = System::Drawing::Point(135, 49);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(17, 12);
			this->label42->TabIndex = 6;
			this->label42->Text = L"℃";
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Location = System::Drawing::Point(135, 24);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(17, 12);
			this->label43->TabIndex = 6;
			this->label43->Text = L"℃";
			// 
			// labelZone09RealTemp
			// 
			this->labelZone09RealTemp->AutoSize = true;
			this->labelZone09RealTemp->Location = System::Drawing::Point(82, 23);
			this->labelZone09RealTemp->Name = L"labelZone09RealTemp";
			this->labelZone09RealTemp->Size = System::Drawing::Size(23, 12);
			this->labelZone09RealTemp->TabIndex = 5;
			this->labelZone09RealTemp->Text = L"0.0";
			// 
			// textBoxZone09Setpoint
			// 
			this->textBoxZone09Setpoint->Location = System::Drawing::Point(81, 43);
			this->textBoxZone09Setpoint->Name = L"textBoxZone09Setpoint";
			this->textBoxZone09Setpoint->Size = System::Drawing::Size(45, 21);
			this->textBoxZone09Setpoint->TabIndex = 4;
			this->textBoxZone09Setpoint->Text = L"0.0";
			// 
			// buttonZone09TempSet
			// 
			this->buttonZone09TempSet->Location = System::Drawing::Point(87, 78);
			this->buttonZone09TempSet->Name = L"buttonZone09TempSet";
			this->buttonZone09TempSet->Size = System::Drawing::Size(66, 23);
			this->buttonZone09TempSet->TabIndex = 3;
			this->buttonZone09TempSet->Text = L"设置温度";
			this->buttonZone09TempSet->UseVisualStyleBackColor = true;
			this->buttonZone09TempSet->Click += gcnew System::EventHandler(this, &Form1::buttonZone09TempSet_Click);
			// 
			// buttonZone09TempGet
			// 
			this->buttonZone09TempGet->Location = System::Drawing::Point(15, 78);
			this->buttonZone09TempGet->Name = L"buttonZone09TempGet";
			this->buttonZone09TempGet->Size = System::Drawing::Size(66, 23);
			this->buttonZone09TempGet->TabIndex = 2;
			this->buttonZone09TempGet->Text = L"读取温度";
			this->buttonZone09TempGet->UseVisualStyleBackColor = true;
			this->buttonZone09TempGet->Click += gcnew System::EventHandler(this, &Form1::buttonZone09TempGet_Click);
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Location = System::Drawing::Point(13, 49);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(65, 12);
			this->label45->TabIndex = 1;
			this->label45->Text = L"设定温度: ";
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->Location = System::Drawing::Point(13, 23);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(65, 12);
			this->label46->TabIndex = 0;
			this->label46->Text = L"实时温度: ";
			// 
			// groupBoxZone06
			// 
			this->groupBoxZone06->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone06->Controls->Add(this->label24);
			this->groupBoxZone06->Controls->Add(this->label25);
			this->groupBoxZone06->Controls->Add(this->labelZone06RealTemp);
			this->groupBoxZone06->Controls->Add(this->textBoxZone06Setpoint);
			this->groupBoxZone06->Controls->Add(this->buttonZone06TempSet);
			this->groupBoxZone06->Controls->Add(this->buttonZone06TempGet);
			this->groupBoxZone06->Controls->Add(this->label30);
			this->groupBoxZone06->Controls->Add(this->label31);
			this->groupBoxZone06->Location = System::Drawing::Point(188, 139);
			this->groupBoxZone06->Name = L"groupBoxZone06";
			this->groupBoxZone06->Size = System::Drawing::Size(175, 113);
			this->groupBoxZone06->TabIndex = 0;
			this->groupBoxZone06->TabStop = false;
			this->groupBoxZone06->Text = L"Zone06";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(135, 49);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(17, 12);
			this->label24->TabIndex = 6;
			this->label24->Text = L"℃";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(135, 24);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(17, 12);
			this->label25->TabIndex = 6;
			this->label25->Text = L"℃";
			// 
			// labelZone06RealTemp
			// 
			this->labelZone06RealTemp->AutoSize = true;
			this->labelZone06RealTemp->Location = System::Drawing::Point(82, 23);
			this->labelZone06RealTemp->Name = L"labelZone06RealTemp";
			this->labelZone06RealTemp->Size = System::Drawing::Size(23, 12);
			this->labelZone06RealTemp->TabIndex = 5;
			this->labelZone06RealTemp->Text = L"0.0";
			// 
			// textBoxZone06Setpoint
			// 
			this->textBoxZone06Setpoint->Location = System::Drawing::Point(81, 43);
			this->textBoxZone06Setpoint->Name = L"textBoxZone06Setpoint";
			this->textBoxZone06Setpoint->Size = System::Drawing::Size(45, 21);
			this->textBoxZone06Setpoint->TabIndex = 4;
			this->textBoxZone06Setpoint->Text = L"0.0";
			// 
			// buttonZone06TempSet
			// 
			this->buttonZone06TempSet->Location = System::Drawing::Point(87, 78);
			this->buttonZone06TempSet->Name = L"buttonZone06TempSet";
			this->buttonZone06TempSet->Size = System::Drawing::Size(66, 23);
			this->buttonZone06TempSet->TabIndex = 3;
			this->buttonZone06TempSet->Text = L"设置温度";
			this->buttonZone06TempSet->UseVisualStyleBackColor = true;
			this->buttonZone06TempSet->Click += gcnew System::EventHandler(this, &Form1::buttonZone06TempSet_Click);
			// 
			// buttonZone06TempGet
			// 
			this->buttonZone06TempGet->Location = System::Drawing::Point(15, 78);
			this->buttonZone06TempGet->Name = L"buttonZone06TempGet";
			this->buttonZone06TempGet->Size = System::Drawing::Size(66, 23);
			this->buttonZone06TempGet->TabIndex = 2;
			this->buttonZone06TempGet->Text = L"读取温度";
			this->buttonZone06TempGet->UseVisualStyleBackColor = true;
			this->buttonZone06TempGet->Click += gcnew System::EventHandler(this, &Form1::buttonZone06TempGet_Click);
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(13, 49);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(65, 12);
			this->label30->TabIndex = 1;
			this->label30->Text = L"设定温度: ";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(13, 23);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(65, 12);
			this->label31->TabIndex = 0;
			this->label31->Text = L"实时温度: ";
			// 
			// groupBoxZone05
			// 
			this->groupBoxZone05->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone05->Controls->Add(this->label19);
			this->groupBoxZone05->Controls->Add(this->label20);
			this->groupBoxZone05->Controls->Add(this->labelZone05RealTemp);
			this->groupBoxZone05->Controls->Add(this->textBoxZone05Setpoint);
			this->groupBoxZone05->Controls->Add(this->buttonZone05TempSet);
			this->groupBoxZone05->Controls->Add(this->buttonZone05TempGet);
			this->groupBoxZone05->Controls->Add(this->label22);
			this->groupBoxZone05->Controls->Add(this->label23);
			this->groupBoxZone05->Location = System::Drawing::Point(7, 139);
			this->groupBoxZone05->Name = L"groupBoxZone05";
			this->groupBoxZone05->Size = System::Drawing::Size(175, 113);
			this->groupBoxZone05->TabIndex = 0;
			this->groupBoxZone05->TabStop = false;
			this->groupBoxZone05->Text = L"Zone05";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(135, 49);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(17, 12);
			this->label19->TabIndex = 6;
			this->label19->Text = L"℃";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(135, 24);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(17, 12);
			this->label20->TabIndex = 6;
			this->label20->Text = L"℃";
			// 
			// labelZone05RealTemp
			// 
			this->labelZone05RealTemp->AutoSize = true;
			this->labelZone05RealTemp->Location = System::Drawing::Point(82, 23);
			this->labelZone05RealTemp->Name = L"labelZone05RealTemp";
			this->labelZone05RealTemp->Size = System::Drawing::Size(23, 12);
			this->labelZone05RealTemp->TabIndex = 5;
			this->labelZone05RealTemp->Text = L"0.0";
			// 
			// textBoxZone05Setpoint
			// 
			this->textBoxZone05Setpoint->Location = System::Drawing::Point(81, 43);
			this->textBoxZone05Setpoint->Name = L"textBoxZone05Setpoint";
			this->textBoxZone05Setpoint->Size = System::Drawing::Size(45, 21);
			this->textBoxZone05Setpoint->TabIndex = 4;
			this->textBoxZone05Setpoint->Text = L"0.0";
			// 
			// buttonZone05TempSet
			// 
			this->buttonZone05TempSet->Location = System::Drawing::Point(87, 78);
			this->buttonZone05TempSet->Name = L"buttonZone05TempSet";
			this->buttonZone05TempSet->Size = System::Drawing::Size(66, 23);
			this->buttonZone05TempSet->TabIndex = 3;
			this->buttonZone05TempSet->Text = L"设置温度";
			this->buttonZone05TempSet->UseVisualStyleBackColor = true;
			this->buttonZone05TempSet->Click += gcnew System::EventHandler(this, &Form1::buttonZone05TempSet_Click);
			// 
			// buttonZone05TempGet
			// 
			this->buttonZone05TempGet->Location = System::Drawing::Point(15, 78);
			this->buttonZone05TempGet->Name = L"buttonZone05TempGet";
			this->buttonZone05TempGet->Size = System::Drawing::Size(66, 23);
			this->buttonZone05TempGet->TabIndex = 2;
			this->buttonZone05TempGet->Text = L"读取温度";
			this->buttonZone05TempGet->UseVisualStyleBackColor = true;
			this->buttonZone05TempGet->Click += gcnew System::EventHandler(this, &Form1::buttonZone05TempGet_Click);
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(13, 49);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(65, 12);
			this->label22->TabIndex = 1;
			this->label22->Text = L"设定温度: ";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(13, 23);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(65, 12);
			this->label23->TabIndex = 0;
			this->label23->Text = L"实时温度: ";
			// 
			// groupBoxZone02
			// 
			this->groupBoxZone02->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone02->Controls->Add(this->label4);
			this->groupBoxZone02->Controls->Add(this->label5);
			this->groupBoxZone02->Controls->Add(this->labelZone02RealTemp);
			this->groupBoxZone02->Controls->Add(this->textBoxZone02Setpoint);
			this->groupBoxZone02->Controls->Add(this->buttonZone02TempSet);
			this->groupBoxZone02->Controls->Add(this->buttonZone02TempGet);
			this->groupBoxZone02->Controls->Add(this->label7);
			this->groupBoxZone02->Controls->Add(this->label8);
			this->groupBoxZone02->Location = System::Drawing::Point(188, 20);
			this->groupBoxZone02->Name = L"groupBoxZone02";
			this->groupBoxZone02->Size = System::Drawing::Size(175, 113);
			this->groupBoxZone02->TabIndex = 0;
			this->groupBoxZone02->TabStop = false;
			this->groupBoxZone02->Text = L"Zone02";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(135, 49);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(17, 12);
			this->label4->TabIndex = 6;
			this->label4->Text = L"℃";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(135, 24);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(17, 12);
			this->label5->TabIndex = 6;
			this->label5->Text = L"℃";
			// 
			// labelZone02RealTemp
			// 
			this->labelZone02RealTemp->AutoSize = true;
			this->labelZone02RealTemp->Location = System::Drawing::Point(82, 23);
			this->labelZone02RealTemp->Name = L"labelZone02RealTemp";
			this->labelZone02RealTemp->Size = System::Drawing::Size(23, 12);
			this->labelZone02RealTemp->TabIndex = 5;
			this->labelZone02RealTemp->Text = L"0.0";
			// 
			// textBoxZone02Setpoint
			// 
			this->textBoxZone02Setpoint->Location = System::Drawing::Point(82, 43);
			this->textBoxZone02Setpoint->Name = L"textBoxZone02Setpoint";
			this->textBoxZone02Setpoint->Size = System::Drawing::Size(45, 21);
			this->textBoxZone02Setpoint->TabIndex = 4;
			this->textBoxZone02Setpoint->Text = L"0.0";
			// 
			// buttonZone02TempSet
			// 
			this->buttonZone02TempSet->Location = System::Drawing::Point(87, 78);
			this->buttonZone02TempSet->Name = L"buttonZone02TempSet";
			this->buttonZone02TempSet->Size = System::Drawing::Size(66, 23);
			this->buttonZone02TempSet->TabIndex = 3;
			this->buttonZone02TempSet->Text = L"设置温度";
			this->buttonZone02TempSet->UseVisualStyleBackColor = true;
			this->buttonZone02TempSet->Click += gcnew System::EventHandler(this, &Form1::buttonZone02TempSet_Click);
			// 
			// buttonZone02TempGet
			// 
			this->buttonZone02TempGet->Location = System::Drawing::Point(15, 78);
			this->buttonZone02TempGet->Name = L"buttonZone02TempGet";
			this->buttonZone02TempGet->Size = System::Drawing::Size(66, 23);
			this->buttonZone02TempGet->TabIndex = 2;
			this->buttonZone02TempGet->Text = L"读取温度";
			this->buttonZone02TempGet->UseVisualStyleBackColor = true;
			this->buttonZone02TempGet->Click += gcnew System::EventHandler(this, &Form1::buttonZone02TempGet_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(13, 49);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(65, 12);
			this->label7->TabIndex = 1;
			this->label7->Text = L"设定温度: ";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(13, 23);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(65, 12);
			this->label8->TabIndex = 0;
			this->label8->Text = L"实时温度: ";
			// 
			// groupBoxZone01
			// 
			this->groupBoxZone01->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone01->Controls->Add(this->label28);
			this->groupBoxZone01->Controls->Add(this->label27);
			this->groupBoxZone01->Controls->Add(this->labelZone01RealTemp);
			this->groupBoxZone01->Controls->Add(this->textBoxZone01Setpoint);
			this->groupBoxZone01->Controls->Add(this->buttonZone01TempSet);
			this->groupBoxZone01->Controls->Add(this->buttonZone01TempGet);
			this->groupBoxZone01->Controls->Add(this->label3);
			this->groupBoxZone01->Controls->Add(this->label2);
			this->groupBoxZone01->Location = System::Drawing::Point(7, 20);
			this->groupBoxZone01->Name = L"groupBoxZone01";
			this->groupBoxZone01->Size = System::Drawing::Size(175, 113);
			this->groupBoxZone01->TabIndex = 0;
			this->groupBoxZone01->TabStop = false;
			this->groupBoxZone01->Text = L"Zone01";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(135, 49);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(17, 12);
			this->label28->TabIndex = 6;
			this->label28->Text = L"℃";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(135, 24);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(17, 12);
			this->label27->TabIndex = 6;
			this->label27->Text = L"℃";
			// 
			// labelZone01RealTemp
			// 
			this->labelZone01RealTemp->AutoSize = true;
			this->labelZone01RealTemp->Location = System::Drawing::Point(82, 23);
			this->labelZone01RealTemp->Name = L"labelZone01RealTemp";
			this->labelZone01RealTemp->Size = System::Drawing::Size(23, 12);
			this->labelZone01RealTemp->TabIndex = 5;
			this->labelZone01RealTemp->Text = L"0.0";
			// 
			// textBoxZone01Setpoint
			// 
			this->textBoxZone01Setpoint->Location = System::Drawing::Point(82, 43);
			this->textBoxZone01Setpoint->Name = L"textBoxZone01Setpoint";
			this->textBoxZone01Setpoint->Size = System::Drawing::Size(45, 21);
			this->textBoxZone01Setpoint->TabIndex = 4;
			this->textBoxZone01Setpoint->Text = L"0.0";
			// 
			// buttonZone01TempSet
			// 
			this->buttonZone01TempSet->Location = System::Drawing::Point(87, 78);
			this->buttonZone01TempSet->Name = L"buttonZone01TempSet";
			this->buttonZone01TempSet->Size = System::Drawing::Size(66, 23);
			this->buttonZone01TempSet->TabIndex = 3;
			this->buttonZone01TempSet->Text = L"设置温度";
			this->buttonZone01TempSet->UseVisualStyleBackColor = true;
			this->buttonZone01TempSet->Click += gcnew System::EventHandler(this, &Form1::buttonZone01TempSet_Click);
			// 
			// buttonZone01TempGet
			// 
			this->buttonZone01TempGet->Location = System::Drawing::Point(15, 78);
			this->buttonZone01TempGet->Name = L"buttonZone01TempGet";
			this->buttonZone01TempGet->Size = System::Drawing::Size(66, 23);
			this->buttonZone01TempGet->TabIndex = 2;
			this->buttonZone01TempGet->Text = L"读取温度";
			this->buttonZone01TempGet->UseVisualStyleBackColor = true;
			this->buttonZone01TempGet->Click += gcnew System::EventHandler(this, &Form1::buttonZone01TempGet_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(13, 49);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(65, 12);
			this->label3->TabIndex = 1;
			this->label3->Text = L"设定温度: ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 23);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(65, 12);
			this->label2->TabIndex = 0;
			this->label2->Text = L"实时温度: ";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(760, 468);
			this->Controls->Add(this->groupBoxZones);
			this->Controls->Add(this->groupBox1);
			this->KeyPreview = true;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"HuskyNeo2Tool";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBoxZones->ResumeLayout(false);
			this->groupBoxZone12->ResumeLayout(false);
			this->groupBoxZone12->PerformLayout();
			this->groupBoxZone08->ResumeLayout(false);
			this->groupBoxZone08->PerformLayout();
			this->groupBoxZone04->ResumeLayout(false);
			this->groupBoxZone04->PerformLayout();
			this->groupBoxZone11->ResumeLayout(false);
			this->groupBoxZone11->PerformLayout();
			this->groupBoxZone07->ResumeLayout(false);
			this->groupBoxZone07->PerformLayout();
			this->groupBoxZone03->ResumeLayout(false);
			this->groupBoxZone03->PerformLayout();
			this->groupBoxZone10->ResumeLayout(false);
			this->groupBoxZone10->PerformLayout();
			this->groupBoxZone09->ResumeLayout(false);
			this->groupBoxZone09->PerformLayout();
			this->groupBoxZone06->ResumeLayout(false);
			this->groupBoxZone06->PerformLayout();
			this->groupBoxZone05->ResumeLayout(false);
			this->groupBoxZone05->PerformLayout();
			this->groupBoxZone02->ResumeLayout(false);
			this->groupBoxZone02->PerformLayout();
			this->groupBoxZone01->ResumeLayout(false);
			this->groupBoxZone01->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {

			 }

private: System::Void buttonZone01TempGet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = currentHusky->getTemperature(1);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone01Setpoint->Text = temperature.ToString();

		float realtimeTemperature = currentHusky->getRealtimeTemperature(1);
		realtimeTemperature = (realtimeTemperature - 32) / 1.8;
		tmp = realtimeTemperature * 10 + 0.5;
		realtimeTemperature = (float)tmp / 10;
		this->labelZone01RealTemp->Text = realtimeTemperature.ToString();
	}
private: System::Void buttonZone02TempGet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = currentHusky->getTemperature(2);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone02Setpoint->Text = temperature.ToString();

		float realtimeTemperature = currentHusky->getRealtimeTemperature(2);
		realtimeTemperature = (realtimeTemperature - 32) / 1.8;
		tmp = realtimeTemperature * 10 + 0.5;
		realtimeTemperature = (float)tmp / 10;
		this->labelZone02RealTemp->Text = realtimeTemperature.ToString();
	}
private: System::Void buttonZone03TempGet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = currentHusky->getTemperature(3);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone03Setpoint->Text = temperature.ToString();

		float realtimeTemperature = currentHusky->getRealtimeTemperature(3);
		realtimeTemperature = (realtimeTemperature - 32) / 1.8;
		tmp = realtimeTemperature * 10 + 0.5;
		realtimeTemperature = (float)tmp / 10;
		this->labelZone03RealTemp->Text = realtimeTemperature.ToString();
	}
private: System::Void buttonZone04TempGet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = currentHusky->getTemperature(4);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone04Setpoint->Text = temperature.ToString();

		float realtimeTemperature = currentHusky->getRealtimeTemperature(4);
		realtimeTemperature = (realtimeTemperature - 32) / 1.8;
		tmp = realtimeTemperature * 10 + 0.5;
		realtimeTemperature = (float)tmp / 10;
		this->labelZone04RealTemp->Text = realtimeTemperature.ToString();
	}
private: System::Void buttonZone05TempGet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = currentHusky->getTemperature(5);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone05Setpoint->Text = temperature.ToString();

		float realtimeTemperature = currentHusky->getRealtimeTemperature(5);
		realtimeTemperature = (realtimeTemperature - 32) / 1.8;
		tmp = realtimeTemperature * 10 + 0.5;
		realtimeTemperature = (float)tmp / 10;
		this->labelZone05RealTemp->Text = realtimeTemperature.ToString();
	}
private: System::Void buttonZone06TempGet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = currentHusky->getTemperature(6);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone06Setpoint->Text = temperature.ToString();

		float realtimeTemperature = currentHusky->getRealtimeTemperature(6);
		realtimeTemperature = (realtimeTemperature - 32) / 1.8;
		tmp = realtimeTemperature * 10 + 0.5;
		realtimeTemperature = (float)tmp / 10;
		this->labelZone06RealTemp->Text = realtimeTemperature.ToString();
	}
private: System::Void buttonZone07TempGet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = currentHusky->getTemperature(7);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone07Setpoint->Text = temperature.ToString();

		float realtimeTemperature = currentHusky->getRealtimeTemperature(7);
		realtimeTemperature = (realtimeTemperature - 32) / 1.8;
		tmp = realtimeTemperature * 10 + 0.5;
		realtimeTemperature = (float)tmp / 10;
		this->labelZone07RealTemp->Text = realtimeTemperature.ToString();
	}
private: System::Void buttonZone08TempGet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = currentHusky->getTemperature(8);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone08Setpoint->Text = temperature.ToString();

		float realtimeTemperature = currentHusky->getRealtimeTemperature(8);
		realtimeTemperature = (realtimeTemperature - 32) / 1.8;
		tmp = realtimeTemperature * 10 + 0.5;
		realtimeTemperature = (float)tmp / 10;
		this->labelZone08RealTemp->Text = realtimeTemperature.ToString();
	}
private: System::Void buttonZone09TempGet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = currentHusky->getTemperature(9);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone09Setpoint->Text = temperature.ToString();

		float realtimeTemperature = currentHusky->getRealtimeTemperature(9);
		realtimeTemperature = (realtimeTemperature - 32) / 1.8;
		tmp = realtimeTemperature * 10 + 0.5;
		realtimeTemperature = (float)tmp / 10;
		this->labelZone09RealTemp->Text = realtimeTemperature.ToString();
	}
private: System::Void buttonZone10TempGet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = currentHusky->getTemperature(10);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone10Setpoint->Text = temperature.ToString();

		float realtimeTemperature = currentHusky->getRealtimeTemperature(10);
		realtimeTemperature = (realtimeTemperature - 32) / 1.8;
		tmp = realtimeTemperature * 10 + 0.5;
		realtimeTemperature = (float)tmp / 10;
		this->labelZone10RealTemp->Text = realtimeTemperature.ToString();
	}
private: System::Void buttonZone11TempGet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = currentHusky->getTemperature(11);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone11Setpoint->Text = temperature.ToString();

		float realtimeTemperature = currentHusky->getRealtimeTemperature(11);
		realtimeTemperature = (realtimeTemperature - 32) / 1.8;
		tmp = realtimeTemperature * 10 + 0.5;
		realtimeTemperature = (float)tmp / 10;
		this->labelZone11RealTemp->Text = realtimeTemperature.ToString();
	}
private: System::Void buttonZone12TempGet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = currentHusky->getTemperature(12);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone12Setpoint->Text = temperature.ToString();

		float realtimeTemperature = currentHusky->getRealtimeTemperature(12);
		realtimeTemperature = (realtimeTemperature - 32) / 1.8;
		tmp = realtimeTemperature * 10 + 0.5;
		realtimeTemperature = (float)tmp / 10;
		this->labelZone12RealTemp->Text = realtimeTemperature.ToString();
	}

private: System::Void buttonZone01TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (this->textBoxZone01Setpoint->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxZone01Setpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setTemperature(temperature, 1) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
private: System::Void buttonZone02TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (this->textBoxZone02Setpoint->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxZone02Setpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setTemperature(temperature, 2) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
private: System::Void buttonZone03TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (this->textBoxZone03Setpoint->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxZone03Setpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setTemperature(temperature, 3) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
private: System::Void buttonZone04TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (this->textBoxZone04Setpoint->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxZone04Setpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setTemperature(temperature, 4) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
private: System::Void buttonZone05TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (this->textBoxZone05Setpoint->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxZone05Setpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setTemperature(temperature, 5) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
private: System::Void buttonZone06TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (this->textBoxZone06Setpoint->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxZone06Setpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setTemperature(temperature, 6) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
private: System::Void buttonZone07TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (this->textBoxZone07Setpoint->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxZone07Setpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setTemperature(temperature, 7) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
private: System::Void buttonZone08TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (this->textBoxZone08Setpoint->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxZone08Setpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setTemperature(temperature, 8) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
private: System::Void buttonZone09TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (this->textBoxZone09Setpoint->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxZone09Setpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setTemperature(temperature, 9) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
private: System::Void buttonZone10TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (this->textBoxZone10Setpoint->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxZone10Setpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setTemperature(temperature, 10) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
private: System::Void buttonZone11TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (this->textBoxZone11Setpoint->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxZone11Setpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setTemperature(temperature, 11) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
private: System::Void buttonZone12TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (this->textBoxZone12Setpoint->Text == "") {
			MessageBox::Show("请输入温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxZone12Setpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setTemperature(temperature, 12) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}


private: System::Void buttonConnect_Click(System::Object^  sender, System::EventArgs^  e) {
	if (currentHusky == NULL) {
		MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		return;
	}

	if (!currentHusky->isConnected()) {
		if (currentHusky->connect())
			this->buttonConnect->Text = L"断开";
		else
			MessageBox::Show("连接失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	} else {
		currentHusky->disconnect();
		this->buttonConnect->Text = L"连接";
	}
}
private: System::Void buttonIpConfig_Click(System::Object^  sender, System::EventArgs^  e) {
		System::Windows::Forms::DialogResult result;
		if (ipConfig)
			result = ipConfig->ShowDialog();

		if (result == ::DialogResult::OK) {
			for (int i = 0; i < HUSKY_DEV_NUM; i++) {
				huskys[i]->setIpAddr((char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(textBoxIpConfigs[i]->Text));
			}

			if (currentHusky) {
				char currentHuskyIp[IP_ADDRESS_STRING_LEN];
				currentHusky->getIpAddr(currentHuskyIp);
				this->labelIpAddr->Text = gcnew String("IP: ") + gcnew String(currentHuskyIp);
			}
        }

		return;
	}
private: System::Void button27_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}

		float temperature = currentHusky->getTemperature(1);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		int tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone01Setpoint->Text = temperature.ToString();

		temperature = currentHusky->getTemperature(2);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone02Setpoint->Text = temperature.ToString();

		temperature = currentHusky->getTemperature(3);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone03Setpoint->Text = temperature.ToString();

		temperature = currentHusky->getTemperature(4);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone04Setpoint->Text = temperature.ToString();

		temperature = currentHusky->getTemperature(5);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone05Setpoint->Text = temperature.ToString();

		temperature = currentHusky->getTemperature(6);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone06Setpoint->Text = temperature.ToString();

		temperature = currentHusky->getTemperature(7);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone07Setpoint->Text = temperature.ToString();

		temperature = currentHusky->getTemperature(8);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone08Setpoint->Text = temperature.ToString();

		temperature = currentHusky->getTemperature(9);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone09Setpoint->Text = temperature.ToString();

		temperature = currentHusky->getTemperature(10);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone10Setpoint->Text = temperature.ToString();

		temperature = currentHusky->getTemperature(11);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone11Setpoint->Text = temperature.ToString();

		temperature = currentHusky->getTemperature(12);
		// C = (F - 32) / 1.8
		temperature = (temperature - 32) / 1.8;
		tmp = temperature * 10 + 0.5;
		temperature = (float)tmp / 10;
		this->textBoxZone12Setpoint->Text = temperature.ToString();
	}
private: System::Void button28_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		//(gcnew AllZonesTemperatureSetting())->Show();
		if (this->textBoxAllZonesSetpoint->Text == "") {
			MessageBox::Show("请输入全区域温度！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		float temperature = Convert::ToDouble(this->textBoxAllZonesSetpoint->Text);
		// F = 32 + C * 1.8;
		temperature = 32 + temperature * 1.8;
		if (currentHusky->setAllZonesTemperature(temperature) == FALSE)
			MessageBox::Show("设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 currentHusky = huskys[this->comboBox1->SelectedIndex];
			 char currentHuskyIp[IP_ADDRESS_STRING_LEN];
			 currentHusky->getIpAddr(currentHuskyIp);
			 this->labelIpAddr->Text = gcnew String("IP: ") + gcnew String(currentHuskyIp);
	}
};
}

