#pragma once

#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#include "Husky.h"
#include "IpConfigure.h"
#include "AllZonesTemperatureSetting.h"
#include "SetAllZonesTemperatureForm.h"
#include "AlarmStatusWindow.h"

#define HUSKY_DEV_NUM 12

namespace HuskyNeo2Tool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

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
			huskys = gcnew array<Husky*, 1>(HUSKY_DEV_NUM);


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

			labelZonesRealTemp = gcnew array<System::Windows::Forms::Label^, 1>(12);
			labelZonesRealTemp[0] = labelZone01RealTemp;
			labelZonesRealTemp[1] = labelZone02RealTemp;
			labelZonesRealTemp[2] = labelZone03RealTemp;
			labelZonesRealTemp[3] = labelZone04RealTemp;
			labelZonesRealTemp[4] = labelZone05RealTemp;
			labelZonesRealTemp[5] = labelZone06RealTemp;
			labelZonesRealTemp[6] = labelZone07RealTemp;
			labelZonesRealTemp[7] = labelZone08RealTemp;
			labelZonesRealTemp[8] = labelZone09RealTemp;
			labelZonesRealTemp[9] = labelZone10RealTemp;
			labelZonesRealTemp[10] = labelZone11RealTemp;
			labelZonesRealTemp[11] = labelZone12RealTemp;

			labelZonesSetpoint = gcnew array<System::Windows::Forms::Label^, 1>(12);
			labelZonesSetpoint[0] = labelZone01Setpoint;
			labelZonesSetpoint[1] = labelZone02Setpoint;
			labelZonesSetpoint[2] = labelZone03Setpoint;
			labelZonesSetpoint[3] = labelZone04Setpoint;
			labelZonesSetpoint[4] = labelZone05Setpoint;
			labelZonesSetpoint[5] = labelZone06Setpoint;
			labelZonesSetpoint[6] = labelZone07Setpoint;
			labelZonesSetpoint[7] = labelZone08Setpoint;
			labelZonesSetpoint[8] = labelZone09Setpoint;
			labelZonesSetpoint[9] = labelZone10Setpoint;
			labelZonesSetpoint[10] = labelZone11Setpoint;
			labelZonesSetpoint[11] = labelZone12Setpoint;

			buttonZonesSwitchArray = gcnew array<System::Windows::Forms::Button^, 1>(12);
			buttonZonesSwitchArray[0] = buttonZone01Switch;
			buttonZonesSwitchArray[1] = buttonZone02Switch;
			buttonZonesSwitchArray[2] = buttonZone03Switch;
			buttonZonesSwitchArray[3] = buttonZone04Switch;
			buttonZonesSwitchArray[4] = buttonZone05Switch;
			buttonZonesSwitchArray[5] = buttonZone06Switch;
			buttonZonesSwitchArray[6] = buttonZone07Switch;
			buttonZonesSwitchArray[7] = buttonZone08Switch;
			buttonZonesSwitchArray[8] = buttonZone09Switch;
			buttonZonesSwitchArray[9] = buttonZone10Switch;
			buttonZonesSwitchArray[10] = buttonZone11Switch;
			buttonZonesSwitchArray[11] = buttonZone12Switch;

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

			//currentHusky = huskys[0];
			currentHusky = new Husky();
			alarmStatusWindow = gcnew AlarmStatusWindow();

			realtimeTemperatureUiUpdate = gcnew UiUpdate(this, &HuskyNeo2Tool::Form1::realtimeTemperatureUiUpdateMethod);
			setpointUiUpdate = gcnew UiUpdate(this, &HuskyNeo2Tool::Form1::setpointUiUpdateMethod);
			zoneSwitchUiUpdate = gcnew UiUpdate(this, &HuskyNeo2Tool::Form1::zoneSwitchUiUpdateMethod);
			myShowAlarmMsg = gcnew showAlarmMsg(this, &HuskyNeo2Tool::Form1::showAlarmMsgMethod);
			
			Thread ^t1 = gcnew Thread(gcnew ThreadStart(this, &HuskyNeo2Tool::Form1::UiUpdateThread));
			t1->IsBackground = true;
			t1->Start();

			Thread ^t2 = gcnew Thread(gcnew ThreadStart(this, &HuskyNeo2Tool::Form1::alarmStatusCheckingThread));
			t2->IsBackground = true;
			t2->Start();
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
		array<Husky *,1>^ huskys;
		array<System::Windows::Forms::TextBox^, 1>^ textBoxIpConfigs;
		array<System::Windows::Forms::Label^, 1>^ labelZonesRealTemp;
		array<System::Windows::Forms::Label^, 1>^ labelZonesSetpoint;
		array<System::Windows::Forms::Button^, 1>^ buttonZonesSwitchArray;
		Husky *currentHusky;
		AlarmStatusWindow^ alarmStatusWindow;

	private: // UI Update
		delegate void UiUpdate(int i, float value);
		UiUpdate^ realtimeTemperatureUiUpdate;
		UiUpdate^ setpointUiUpdate;
		UiUpdate^ zoneSwitchUiUpdate;
	
		void realtimeTemperatureUiUpdateMethod(int i, float value)
		{
			this->labelZonesRealTemp[i]->Text = value.ToString();
		}
		void setpointUiUpdateMethod(int i, float value)
		{
			this->labelZonesSetpoint[i]->Text = value.ToString();
		}
		// value:  1 -> "打开"    0 -> "关闭"
		void zoneSwitchUiUpdateMethod(int i, float value)
		{
			if (value > 0)
				this->buttonZonesSwitchArray[i]->Text = L"打开";
			else
				this->buttonZonesSwitchArray[i]->Text = L"关闭";
		}

		void UiUpdateThread()
		{
			int tmp = 0;
			do {
				if (currentHusky == NULL || !currentHusky->isConnected()) {
					Sleep(5000);
					continue;
				}

				if (tmp % 5 == 0) { // update UI every 3 * 5 = 15S
					tmp = 0;
					for (int i = 0; i < 12; i++) {
						float temperature = currentHusky->getTemperature(i + 1);
						// C = (F - 32) / 1.8
						temperature = (temperature - 32) / 1.8;
						int tmp = temperature * 10 + 0.5;
						temperature = (float)tmp / 10;
						this->Invoke(this->setpointUiUpdate, i, temperature);
						Sleep(100);
					}

					for (int i = 0; i < 12; i++) {
						if (currentHusky->getZoneOnOff(i + 1)) {
							this->Invoke(this->zoneSwitchUiUpdate, i, 0);
						} else {
							this->Invoke(this->zoneSwitchUiUpdate, i, 1);
						}
						//Sleep(100);
					}
				} else
					tmp++;

				for (int i = 0; i < 12; i++) {
					float realtimeTemperature = currentHusky->getRealtimeTemperature(i + 1);
					realtimeTemperature = (realtimeTemperature - 32) / 1.8;
					int tmp = realtimeTemperature * 10 + 0.5;
					realtimeTemperature = (float)tmp / 10;
					this->Invoke(this->realtimeTemperatureUiUpdate, i, realtimeTemperature);
					Sleep(100); // 1s?
				}
				Sleep(3000); // 3s?
			} while (1);
		}

	private: // ALARM
		delegate void showAlarmMsg();
		showAlarmMsg^ myShowAlarmMsg;

		void showAlarmMsgMethod()
		{
			System::Windows::Forms::DialogResult result = this->alarmStatusWindow->ShowDialog();
			if (result == ::DialogResult::OK) {
				currentHusky->controlerReset();
			}
		}

		void alarmStatusCheckingThread()
		{
			/*
			while (1) {
				alarmStatusWindow->labelZoneAlarmMsgArray[1]->ForeColor = System::Drawing::Color::Black;
				this->Invoke(this->myShowAlarmMsg);
			}
			*/
			while (1) {
				if (currentHusky == NULL || !currentHusky->isConnected()) {
					Sleep(3000);
					continue;
				}
				for (int i = 0; i < 12; i++) {
					uint16_t status = currentHusky->getControlerStatus(i + 1);
					char *msg = currentHusky->getControlerStatusString(status);
					if (msg) {
						for (int j = 0; j < 12; j++) {
							if (currentHusky->getZoneOnOff(j + 1)) {
								uint16_t status = currentHusky->getControlerStatus(j + 1);
								char *msg = currentHusky->getControlerStatusString(status);
								alarmStatusWindow->labelZoneAlarmMsgArray[j]->Text = gcnew String(msg);
							} else {
								alarmStatusWindow->labelZoneAlarmMsgArray[j]->Text = L"确定";
								alarmStatusWindow->labelZoneAlarmMsgArray[j]->ForeColor = System::Drawing::Color::Black;
							}
						}
						this->Invoke(this->myShowAlarmMsg);
						break;
					}
				}
				Sleep(1000);
			}
		}

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  labelZone12Setpoint;
	private: System::Windows::Forms::Label^  labelZone08Setpoint;
	private: System::Windows::Forms::Label^  labelZone04Setpoint;
	private: System::Windows::Forms::Label^  labelZone11Setpoint;
	private: System::Windows::Forms::Label^  labelZone07Setpoint;
	private: System::Windows::Forms::Label^  labelZone03Setpoint;
	private: System::Windows::Forms::Label^  labelZone10Setpoint;
	private: System::Windows::Forms::Label^  labelZone09Setpoint;
	private: System::Windows::Forms::Label^  labelZone06Setpoint;
	private: System::Windows::Forms::Label^  labelZone05Setpoint;
	private: System::Windows::Forms::Label^  labelZone02Setpoint;
	private: System::Windows::Forms::Label^  labelZone01Setpoint;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Button^  buttonConnect;
	private: System::Windows::Forms::GroupBox^  groupBoxZones;
	private: System::Windows::Forms::GroupBox^  groupBoxZone01;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  buttonZone01Switch;
	private: System::Windows::Forms::Label^  labelZone01RealTemp;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::GroupBox^  groupBoxZone12;
	private: System::Windows::Forms::Label^  label57;
	private: System::Windows::Forms::Label^  label58;
	private: System::Windows::Forms::Label^  labelZone12RealTemp;
	private: System::Windows::Forms::Button^  buttonZone12Switch;
	private: System::Windows::Forms::Label^  label60;
	private: System::Windows::Forms::Label^  label61;
	private: System::Windows::Forms::GroupBox^  groupBoxZone08;
	private: System::Windows::Forms::Label^  label37;
	private: System::Windows::Forms::Label^  label38;
	private: System::Windows::Forms::Label^  labelZone08RealTemp;
	private: System::Windows::Forms::Button^  buttonZone08Switch;
	private: System::Windows::Forms::Label^  label40;
	private: System::Windows::Forms::Label^  label41;
	private: System::Windows::Forms::GroupBox^  groupBoxZone04;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  labelZone04RealTemp;
	private: System::Windows::Forms::Button^  buttonZone04Switch;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::GroupBox^  groupBoxZone11;
	private: System::Windows::Forms::Label^  label52;
	private: System::Windows::Forms::Label^  label53;
	private: System::Windows::Forms::Label^  labelZone11RealTemp;
	private: System::Windows::Forms::Button^  buttonZone11Switch;
	private: System::Windows::Forms::Label^  label55;
	private: System::Windows::Forms::Label^  label56;
	private: System::Windows::Forms::GroupBox^  groupBoxZone07;
	private: System::Windows::Forms::Label^  label32;
	private: System::Windows::Forms::Label^  label33;
	private: System::Windows::Forms::Label^  labelZone07RealTemp;
	private: System::Windows::Forms::Button^  buttonZone07Switch;

	private: System::Windows::Forms::Label^  label35;
	private: System::Windows::Forms::Label^  label36;
	private: System::Windows::Forms::GroupBox^  groupBoxZone03;

	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  labelZone03RealTemp;
	private: System::Windows::Forms::Button^  buttonZone03Switch;

	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::GroupBox^  groupBoxZone10;

	private: System::Windows::Forms::Label^  label47;
	private: System::Windows::Forms::Label^  label48;
	private: System::Windows::Forms::Label^  labelZone10RealTemp;
	private: System::Windows::Forms::Button^  buttonZone10Switch;

	private: System::Windows::Forms::Label^  label50;
	private: System::Windows::Forms::Label^  label51;
	private: System::Windows::Forms::GroupBox^  groupBoxZone09;

	private: System::Windows::Forms::Label^  label42;
	private: System::Windows::Forms::Label^  label43;
	private: System::Windows::Forms::Label^  labelZone09RealTemp;
	private: System::Windows::Forms::Button^  buttonZone09Switch;

	private: System::Windows::Forms::Label^  label45;
	private: System::Windows::Forms::Label^  label46;
	private: System::Windows::Forms::GroupBox^  groupBoxZone06;

	private: System::Windows::Forms::Label^  label24;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  labelZone06RealTemp;
	private: System::Windows::Forms::Button^  buttonZone06Switch;

	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::GroupBox^  groupBoxZone05;

	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  labelZone05RealTemp;
	private: System::Windows::Forms::Button^  buttonZone05Switch;

	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label23;
	private: System::Windows::Forms::GroupBox^  groupBoxZone02;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  labelZone02RealTemp;
	private: System::Windows::Forms::Button^  buttonZone02Switch;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Button^  button28;
	private: System::Windows::Forms::Button^  button27;


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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button28 = (gcnew System::Windows::Forms::Button());
			this->button27 = (gcnew System::Windows::Forms::Button());
			this->buttonConnect = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBoxZones = (gcnew System::Windows::Forms::GroupBox());
			this->groupBoxZone12 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone12Setpoint = (gcnew System::Windows::Forms::Label());
			this->label57 = (gcnew System::Windows::Forms::Label());
			this->label58 = (gcnew System::Windows::Forms::Label());
			this->labelZone12RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone12Switch = (gcnew System::Windows::Forms::Button());
			this->label60 = (gcnew System::Windows::Forms::Label());
			this->label61 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone08 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone08Setpoint = (gcnew System::Windows::Forms::Label());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->labelZone08RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone08Switch = (gcnew System::Windows::Forms::Button());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone04 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone04Setpoint = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->labelZone04RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone04Switch = (gcnew System::Windows::Forms::Button());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone11 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone11Setpoint = (gcnew System::Windows::Forms::Label());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->labelZone11RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone11Switch = (gcnew System::Windows::Forms::Button());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->label56 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone07 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone07Setpoint = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->labelZone07RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone07Switch = (gcnew System::Windows::Forms::Button());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone03 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone03Setpoint = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->labelZone03RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone03Switch = (gcnew System::Windows::Forms::Button());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone10 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone10Setpoint = (gcnew System::Windows::Forms::Label());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->labelZone10RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone10Switch = (gcnew System::Windows::Forms::Button());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone09 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone09Setpoint = (gcnew System::Windows::Forms::Label());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->labelZone09RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone09Switch = (gcnew System::Windows::Forms::Button());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone06 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone06Setpoint = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->labelZone06RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone06Switch = (gcnew System::Windows::Forms::Button());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone05 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone05Setpoint = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->labelZone05RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone05Switch = (gcnew System::Windows::Forms::Button());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone02 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone02Setpoint = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->labelZone02RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone02Switch = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone01 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone01Setpoint = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->labelZone01RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone01Switch = (gcnew System::Windows::Forms::Button());
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
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->button28);
			this->groupBox1->Controls->Add(this->button27);
			this->groupBox1->Controls->Add(this->buttonConnect);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Location = System::Drawing::Point(16, 16);
			this->groupBox1->Margin = System::Windows::Forms::Padding(4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(4);
			this->groupBox1->Size = System::Drawing::Size(730, 86);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(3, 35);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(96, 16);
			this->label6->TabIndex = 13;
			this->label6->Text = L"机台号端口:";
			// 
			// button28
			// 
			this->button28->Location = System::Drawing::Point(627, 28);
			this->button28->Margin = System::Windows::Forms::Padding(4);
			this->button28->Name = L"button28";
			this->button28->Size = System::Drawing::Size(95, 31);
			this->button28->TabIndex = 10;
			this->button28->Text = L"温度设置";
			this->button28->UseVisualStyleBackColor = true;
			this->button28->Click += gcnew System::EventHandler(this, &Form1::button28_Click);
			// 
			// button27
			// 
			this->button27->Location = System::Drawing::Point(511, 28);
			this->button27->Margin = System::Windows::Forms::Padding(4);
			this->button27->Name = L"button27";
			this->button27->Size = System::Drawing::Size(95, 31);
			this->button27->TabIndex = 9;
			this->button27->Text = L"温度读取";
			this->button27->UseVisualStyleBackColor = true;
			this->button27->Click += gcnew System::EventHandler(this, &Form1::button27_Click);
			// 
			// buttonConnect
			// 
			this->buttonConnect->Location = System::Drawing::Point(187, 28);
			this->buttonConnect->Margin = System::Windows::Forms::Padding(4);
			this->buttonConnect->Name = L"buttonConnect";
			this->buttonConnect->Size = System::Drawing::Size(82, 31);
			this->buttonConnect->TabIndex = 7;
			this->buttonConnect->Text = L"连接";
			this->buttonConnect->UseVisualStyleBackColor = true;
			this->buttonConnect->Click += gcnew System::EventHandler(this, &Form1::buttonConnect_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(9) {L"COM1", L"COM2", L"COM3", L"COM4", L"COM5", L"COM6", 
				L"COM7", L"COM8", L"COM9"});
			this->comboBox1->Location = System::Drawing::Point(97, 31);
			this->comboBox1->Margin = System::Windows::Forms::Padding(4);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(61, 24);
			this->comboBox1->TabIndex = 5;
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
			this->groupBoxZones->Location = System::Drawing::Point(16, 104);
			this->groupBoxZones->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZones->Name = L"groupBoxZones";
			this->groupBoxZones->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZones->Size = System::Drawing::Size(730, 447);
			this->groupBoxZones->TabIndex = 1;
			this->groupBoxZones->TabStop = false;
			// 
			// groupBoxZone12
			// 
			this->groupBoxZone12->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone12->Controls->Add(this->labelZone12Setpoint);
			this->groupBoxZone12->Controls->Add(this->label57);
			this->groupBoxZone12->Controls->Add(this->label58);
			this->groupBoxZone12->Controls->Add(this->labelZone12RealTemp);
			this->groupBoxZone12->Controls->Add(this->buttonZone12Switch);
			this->groupBoxZone12->Controls->Add(this->label60);
			this->groupBoxZone12->Controls->Add(this->label61);
			this->groupBoxZone12->Location = System::Drawing::Point(545, 303);
			this->groupBoxZone12->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZone12->Name = L"groupBoxZone12";
			this->groupBoxZone12->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZone12->Size = System::Drawing::Size(175, 135);
			this->groupBoxZone12->TabIndex = 0;
			this->groupBoxZone12->TabStop = false;
			this->groupBoxZone12->Text = L"Zone12";
			// 
			// labelZone12Setpoint
			// 
			this->labelZone12Setpoint->AutoSize = true;
			this->labelZone12Setpoint->Location = System::Drawing::Point(95, 65);
			this->labelZone12Setpoint->Name = L"labelZone12Setpoint";
			this->labelZone12Setpoint->Size = System::Drawing::Size(32, 16);
			this->labelZone12Setpoint->TabIndex = 7;
			this->labelZone12Setpoint->Text = L"0.0";
			// 
			// label57
			// 
			this->label57->AutoSize = true;
			this->label57->Location = System::Drawing::Point(144, 65);
			this->label57->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label57->Name = L"label57";
			this->label57->Size = System::Drawing::Size(24, 16);
			this->label57->TabIndex = 6;
			this->label57->Text = L"℃";
			// 
			// label58
			// 
			this->label58->AutoSize = true;
			this->label58->Location = System::Drawing::Point(144, 32);
			this->label58->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label58->Name = L"label58";
			this->label58->Size = System::Drawing::Size(24, 16);
			this->label58->TabIndex = 6;
			this->label58->Text = L"℃";
			// 
			// labelZone12RealTemp
			// 
			this->labelZone12RealTemp->AutoSize = true;
			this->labelZone12RealTemp->Location = System::Drawing::Point(95, 31);
			this->labelZone12RealTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone12RealTemp->Name = L"labelZone12RealTemp";
			this->labelZone12RealTemp->Size = System::Drawing::Size(32, 16);
			this->labelZone12RealTemp->TabIndex = 5;
			this->labelZone12RealTemp->Text = L"0.0";
			// 
			// buttonZone12Switch
			// 
			this->buttonZone12Switch->Location = System::Drawing::Point(20, 96);
			this->buttonZone12Switch->Margin = System::Windows::Forms::Padding(4);
			this->buttonZone12Switch->Name = L"buttonZone12Switch";
			this->buttonZone12Switch->Size = System::Drawing::Size(88, 31);
			this->buttonZone12Switch->TabIndex = 3;
			this->buttonZone12Switch->Text = L"打开";
			this->buttonZone12Switch->UseVisualStyleBackColor = true;
			this->buttonZone12Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone12TempSet_Click);
			// 
			// label60
			// 
			this->label60->AutoSize = true;
			this->label60->Location = System::Drawing::Point(17, 65);
			this->label60->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label60->Name = L"label60";
			this->label60->Size = System::Drawing::Size(88, 16);
			this->label60->TabIndex = 1;
			this->label60->Text = L"设定温度: ";
			// 
			// label61
			// 
			this->label61->AutoSize = true;
			this->label61->Location = System::Drawing::Point(17, 31);
			this->label61->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label61->Name = L"label61";
			this->label61->Size = System::Drawing::Size(88, 16);
			this->label61->TabIndex = 0;
			this->label61->Text = L"实时温度: ";
			// 
			// groupBoxZone08
			// 
			this->groupBoxZone08->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone08->Controls->Add(this->labelZone08Setpoint);
			this->groupBoxZone08->Controls->Add(this->label37);
			this->groupBoxZone08->Controls->Add(this->label38);
			this->groupBoxZone08->Controls->Add(this->labelZone08RealTemp);
			this->groupBoxZone08->Controls->Add(this->buttonZone08Switch);
			this->groupBoxZone08->Controls->Add(this->label40);
			this->groupBoxZone08->Controls->Add(this->label41);
			this->groupBoxZone08->Location = System::Drawing::Point(545, 160);
			this->groupBoxZone08->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZone08->Name = L"groupBoxZone08";
			this->groupBoxZone08->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZone08->Size = System::Drawing::Size(175, 135);
			this->groupBoxZone08->TabIndex = 0;
			this->groupBoxZone08->TabStop = false;
			this->groupBoxZone08->Text = L"Zone08";
			// 
			// labelZone08Setpoint
			// 
			this->labelZone08Setpoint->AutoSize = true;
			this->labelZone08Setpoint->Location = System::Drawing::Point(95, 65);
			this->labelZone08Setpoint->Name = L"labelZone08Setpoint";
			this->labelZone08Setpoint->Size = System::Drawing::Size(32, 16);
			this->labelZone08Setpoint->TabIndex = 7;
			this->labelZone08Setpoint->Text = L"0.0";
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(144, 65);
			this->label37->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(24, 16);
			this->label37->TabIndex = 6;
			this->label37->Text = L"℃";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(144, 32);
			this->label38->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(24, 16);
			this->label38->TabIndex = 6;
			this->label38->Text = L"℃";
			// 
			// labelZone08RealTemp
			// 
			this->labelZone08RealTemp->AutoSize = true;
			this->labelZone08RealTemp->Location = System::Drawing::Point(95, 31);
			this->labelZone08RealTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone08RealTemp->Name = L"labelZone08RealTemp";
			this->labelZone08RealTemp->Size = System::Drawing::Size(32, 16);
			this->labelZone08RealTemp->TabIndex = 5;
			this->labelZone08RealTemp->Text = L"0.0";
			// 
			// buttonZone08Switch
			// 
			this->buttonZone08Switch->Location = System::Drawing::Point(17, 95);
			this->buttonZone08Switch->Margin = System::Windows::Forms::Padding(4);
			this->buttonZone08Switch->Name = L"buttonZone08Switch";
			this->buttonZone08Switch->Size = System::Drawing::Size(88, 31);
			this->buttonZone08Switch->TabIndex = 3;
			this->buttonZone08Switch->Text = L"打开";
			this->buttonZone08Switch->UseVisualStyleBackColor = true;
			this->buttonZone08Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone08TempSet_Click);
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(17, 65);
			this->label40->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(88, 16);
			this->label40->TabIndex = 1;
			this->label40->Text = L"设定温度: ";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(17, 31);
			this->label41->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(88, 16);
			this->label41->TabIndex = 0;
			this->label41->Text = L"实时温度: ";
			// 
			// groupBoxZone04
			// 
			this->groupBoxZone04->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone04->Controls->Add(this->labelZone04Setpoint);
			this->groupBoxZone04->Controls->Add(this->label14);
			this->groupBoxZone04->Controls->Add(this->label15);
			this->groupBoxZone04->Controls->Add(this->labelZone04RealTemp);
			this->groupBoxZone04->Controls->Add(this->buttonZone04Switch);
			this->groupBoxZone04->Controls->Add(this->label17);
			this->groupBoxZone04->Controls->Add(this->label18);
			this->groupBoxZone04->Location = System::Drawing::Point(545, 17);
			this->groupBoxZone04->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZone04->Name = L"groupBoxZone04";
			this->groupBoxZone04->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZone04->Size = System::Drawing::Size(175, 135);
			this->groupBoxZone04->TabIndex = 0;
			this->groupBoxZone04->TabStop = false;
			this->groupBoxZone04->Text = L"Zone04";
			// 
			// labelZone04Setpoint
			// 
			this->labelZone04Setpoint->AutoSize = true;
			this->labelZone04Setpoint->Location = System::Drawing::Point(95, 65);
			this->labelZone04Setpoint->Name = L"labelZone04Setpoint";
			this->labelZone04Setpoint->Size = System::Drawing::Size(32, 16);
			this->labelZone04Setpoint->TabIndex = 7;
			this->labelZone04Setpoint->Text = L"0.0";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(144, 65);
			this->label14->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(24, 16);
			this->label14->TabIndex = 6;
			this->label14->Text = L"℃";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(144, 32);
			this->label15->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(24, 16);
			this->label15->TabIndex = 6;
			this->label15->Text = L"℃";
			// 
			// labelZone04RealTemp
			// 
			this->labelZone04RealTemp->AutoSize = true;
			this->labelZone04RealTemp->Location = System::Drawing::Point(95, 31);
			this->labelZone04RealTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone04RealTemp->Name = L"labelZone04RealTemp";
			this->labelZone04RealTemp->Size = System::Drawing::Size(32, 16);
			this->labelZone04RealTemp->TabIndex = 5;
			this->labelZone04RealTemp->Text = L"0.0";
			// 
			// buttonZone04Switch
			// 
			this->buttonZone04Switch->Location = System::Drawing::Point(17, 94);
			this->buttonZone04Switch->Margin = System::Windows::Forms::Padding(4);
			this->buttonZone04Switch->Name = L"buttonZone04Switch";
			this->buttonZone04Switch->Size = System::Drawing::Size(88, 31);
			this->buttonZone04Switch->TabIndex = 3;
			this->buttonZone04Switch->Text = L"打开";
			this->buttonZone04Switch->UseVisualStyleBackColor = true;
			this->buttonZone04Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone04TempSet_Click);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(17, 65);
			this->label17->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(88, 16);
			this->label17->TabIndex = 1;
			this->label17->Text = L"设定温度: ";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(17, 31);
			this->label18->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(88, 16);
			this->label18->TabIndex = 0;
			this->label18->Text = L"实时温度: ";
			// 
			// groupBoxZone11
			// 
			this->groupBoxZone11->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone11->Controls->Add(this->labelZone11Setpoint);
			this->groupBoxZone11->Controls->Add(this->label52);
			this->groupBoxZone11->Controls->Add(this->label53);
			this->groupBoxZone11->Controls->Add(this->labelZone11RealTemp);
			this->groupBoxZone11->Controls->Add(this->buttonZone11Switch);
			this->groupBoxZone11->Controls->Add(this->label55);
			this->groupBoxZone11->Controls->Add(this->label56);
			this->groupBoxZone11->Location = System::Drawing::Point(366, 303);
			this->groupBoxZone11->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZone11->Name = L"groupBoxZone11";
			this->groupBoxZone11->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZone11->Size = System::Drawing::Size(175, 135);
			this->groupBoxZone11->TabIndex = 0;
			this->groupBoxZone11->TabStop = false;
			this->groupBoxZone11->Text = L"Zone11";
			// 
			// labelZone11Setpoint
			// 
			this->labelZone11Setpoint->AutoSize = true;
			this->labelZone11Setpoint->Location = System::Drawing::Point(93, 66);
			this->labelZone11Setpoint->Name = L"labelZone11Setpoint";
			this->labelZone11Setpoint->Size = System::Drawing::Size(32, 16);
			this->labelZone11Setpoint->TabIndex = 7;
			this->labelZone11Setpoint->Text = L"0.0";
			// 
			// label52
			// 
			this->label52->AutoSize = true;
			this->label52->Location = System::Drawing::Point(144, 66);
			this->label52->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(24, 16);
			this->label52->TabIndex = 6;
			this->label52->Text = L"℃";
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->Location = System::Drawing::Point(144, 33);
			this->label53->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(24, 16);
			this->label53->TabIndex = 6;
			this->label53->Text = L"℃";
			// 
			// labelZone11RealTemp
			// 
			this->labelZone11RealTemp->AutoSize = true;
			this->labelZone11RealTemp->Location = System::Drawing::Point(93, 32);
			this->labelZone11RealTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone11RealTemp->Name = L"labelZone11RealTemp";
			this->labelZone11RealTemp->Size = System::Drawing::Size(32, 16);
			this->labelZone11RealTemp->TabIndex = 5;
			this->labelZone11RealTemp->Text = L"0.0";
			// 
			// buttonZone11Switch
			// 
			this->buttonZone11Switch->Location = System::Drawing::Point(19, 96);
			this->buttonZone11Switch->Margin = System::Windows::Forms::Padding(4);
			this->buttonZone11Switch->Name = L"buttonZone11Switch";
			this->buttonZone11Switch->Size = System::Drawing::Size(88, 31);
			this->buttonZone11Switch->TabIndex = 3;
			this->buttonZone11Switch->Text = L"打开";
			this->buttonZone11Switch->UseVisualStyleBackColor = true;
			this->buttonZone11Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone11TempSet_Click);
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->Location = System::Drawing::Point(17, 65);
			this->label55->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(88, 16);
			this->label55->TabIndex = 1;
			this->label55->Text = L"设定温度: ";
			// 
			// label56
			// 
			this->label56->AutoSize = true;
			this->label56->Location = System::Drawing::Point(17, 31);
			this->label56->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label56->Name = L"label56";
			this->label56->Size = System::Drawing::Size(88, 16);
			this->label56->TabIndex = 0;
			this->label56->Text = L"实时温度: ";
			// 
			// groupBoxZone07
			// 
			this->groupBoxZone07->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone07->Controls->Add(this->labelZone07Setpoint);
			this->groupBoxZone07->Controls->Add(this->label32);
			this->groupBoxZone07->Controls->Add(this->label33);
			this->groupBoxZone07->Controls->Add(this->labelZone07RealTemp);
			this->groupBoxZone07->Controls->Add(this->buttonZone07Switch);
			this->groupBoxZone07->Controls->Add(this->label35);
			this->groupBoxZone07->Controls->Add(this->label36);
			this->groupBoxZone07->Location = System::Drawing::Point(366, 160);
			this->groupBoxZone07->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZone07->Name = L"groupBoxZone07";
			this->groupBoxZone07->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZone07->Size = System::Drawing::Size(175, 135);
			this->groupBoxZone07->TabIndex = 0;
			this->groupBoxZone07->TabStop = false;
			this->groupBoxZone07->Text = L"Zone07";
			// 
			// labelZone07Setpoint
			// 
			this->labelZone07Setpoint->AutoSize = true;
			this->labelZone07Setpoint->Location = System::Drawing::Point(93, 65);
			this->labelZone07Setpoint->Name = L"labelZone07Setpoint";
			this->labelZone07Setpoint->Size = System::Drawing::Size(32, 16);
			this->labelZone07Setpoint->TabIndex = 7;
			this->labelZone07Setpoint->Text = L"0.0";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(142, 65);
			this->label32->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(24, 16);
			this->label32->TabIndex = 6;
			this->label32->Text = L"℃";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(142, 32);
			this->label33->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(24, 16);
			this->label33->TabIndex = 6;
			this->label33->Text = L"℃";
			// 
			// labelZone07RealTemp
			// 
			this->labelZone07RealTemp->AutoSize = true;
			this->labelZone07RealTemp->Location = System::Drawing::Point(93, 31);
			this->labelZone07RealTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone07RealTemp->Name = L"labelZone07RealTemp";
			this->labelZone07RealTemp->Size = System::Drawing::Size(32, 16);
			this->labelZone07RealTemp->TabIndex = 5;
			this->labelZone07RealTemp->Text = L"0.0";
			// 
			// buttonZone07Switch
			// 
			this->buttonZone07Switch->Location = System::Drawing::Point(19, 95);
			this->buttonZone07Switch->Margin = System::Windows::Forms::Padding(4);
			this->buttonZone07Switch->Name = L"buttonZone07Switch";
			this->buttonZone07Switch->Size = System::Drawing::Size(88, 31);
			this->buttonZone07Switch->TabIndex = 3;
			this->buttonZone07Switch->Text = L"打开";
			this->buttonZone07Switch->UseVisualStyleBackColor = true;
			this->buttonZone07Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone07TempSet_Click);
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(17, 65);
			this->label35->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(88, 16);
			this->label35->TabIndex = 1;
			this->label35->Text = L"设定温度: ";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(17, 31);
			this->label36->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(88, 16);
			this->label36->TabIndex = 0;
			this->label36->Text = L"实时温度: ";
			// 
			// groupBoxZone03
			// 
			this->groupBoxZone03->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone03->Controls->Add(this->labelZone03Setpoint);
			this->groupBoxZone03->Controls->Add(this->label9);
			this->groupBoxZone03->Controls->Add(this->label10);
			this->groupBoxZone03->Controls->Add(this->labelZone03RealTemp);
			this->groupBoxZone03->Controls->Add(this->buttonZone03Switch);
			this->groupBoxZone03->Controls->Add(this->label12);
			this->groupBoxZone03->Controls->Add(this->label13);
			this->groupBoxZone03->Location = System::Drawing::Point(366, 17);
			this->groupBoxZone03->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZone03->Name = L"groupBoxZone03";
			this->groupBoxZone03->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZone03->Size = System::Drawing::Size(175, 135);
			this->groupBoxZone03->TabIndex = 0;
			this->groupBoxZone03->TabStop = false;
			this->groupBoxZone03->Text = L"Zone03";
			// 
			// labelZone03Setpoint
			// 
			this->labelZone03Setpoint->AutoSize = true;
			this->labelZone03Setpoint->Location = System::Drawing::Point(93, 65);
			this->labelZone03Setpoint->Name = L"labelZone03Setpoint";
			this->labelZone03Setpoint->Size = System::Drawing::Size(32, 16);
			this->labelZone03Setpoint->TabIndex = 7;
			this->labelZone03Setpoint->Text = L"0.0";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(142, 65);
			this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(24, 16);
			this->label9->TabIndex = 6;
			this->label9->Text = L"℃";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(142, 32);
			this->label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(24, 16);
			this->label10->TabIndex = 6;
			this->label10->Text = L"℃";
			// 
			// labelZone03RealTemp
			// 
			this->labelZone03RealTemp->AutoSize = true;
			this->labelZone03RealTemp->Location = System::Drawing::Point(93, 31);
			this->labelZone03RealTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone03RealTemp->Name = L"labelZone03RealTemp";
			this->labelZone03RealTemp->Size = System::Drawing::Size(32, 16);
			this->labelZone03RealTemp->TabIndex = 5;
			this->labelZone03RealTemp->Text = L"0.0";
			// 
			// buttonZone03Switch
			// 
			this->buttonZone03Switch->Location = System::Drawing::Point(20, 94);
			this->buttonZone03Switch->Margin = System::Windows::Forms::Padding(4);
			this->buttonZone03Switch->Name = L"buttonZone03Switch";
			this->buttonZone03Switch->Size = System::Drawing::Size(88, 31);
			this->buttonZone03Switch->TabIndex = 3;
			this->buttonZone03Switch->Text = L"打开";
			this->buttonZone03Switch->UseVisualStyleBackColor = true;
			this->buttonZone03Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone03TempSet_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(17, 65);
			this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(88, 16);
			this->label12->TabIndex = 1;
			this->label12->Text = L"设定温度: ";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(17, 31);
			this->label13->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(88, 16);
			this->label13->TabIndex = 0;
			this->label13->Text = L"实时温度: ";
			// 
			// groupBoxZone10
			// 
			this->groupBoxZone10->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone10->Controls->Add(this->labelZone10Setpoint);
			this->groupBoxZone10->Controls->Add(this->label47);
			this->groupBoxZone10->Controls->Add(this->label48);
			this->groupBoxZone10->Controls->Add(this->labelZone10RealTemp);
			this->groupBoxZone10->Controls->Add(this->buttonZone10Switch);
			this->groupBoxZone10->Controls->Add(this->label50);
			this->groupBoxZone10->Controls->Add(this->label51);
			this->groupBoxZone10->Location = System::Drawing::Point(188, 303);
			this->groupBoxZone10->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZone10->Name = L"groupBoxZone10";
			this->groupBoxZone10->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZone10->Size = System::Drawing::Size(175, 135);
			this->groupBoxZone10->TabIndex = 0;
			this->groupBoxZone10->TabStop = false;
			this->groupBoxZone10->Text = L"Zone10";
			// 
			// labelZone10Setpoint
			// 
			this->labelZone10Setpoint->AutoSize = true;
			this->labelZone10Setpoint->Location = System::Drawing::Point(93, 65);
			this->labelZone10Setpoint->Name = L"labelZone10Setpoint";
			this->labelZone10Setpoint->Size = System::Drawing::Size(32, 16);
			this->labelZone10Setpoint->TabIndex = 7;
			this->labelZone10Setpoint->Text = L"0.0";
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->Location = System::Drawing::Point(142, 65);
			this->label47->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(24, 16);
			this->label47->TabIndex = 6;
			this->label47->Text = L"℃";
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->Location = System::Drawing::Point(142, 32);
			this->label48->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(24, 16);
			this->label48->TabIndex = 6;
			this->label48->Text = L"℃";
			// 
			// labelZone10RealTemp
			// 
			this->labelZone10RealTemp->AutoSize = true;
			this->labelZone10RealTemp->Location = System::Drawing::Point(93, 31);
			this->labelZone10RealTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone10RealTemp->Name = L"labelZone10RealTemp";
			this->labelZone10RealTemp->Size = System::Drawing::Size(32, 16);
			this->labelZone10RealTemp->TabIndex = 5;
			this->labelZone10RealTemp->Text = L"0.0";
			// 
			// buttonZone10Switch
			// 
			this->buttonZone10Switch->Location = System::Drawing::Point(20, 96);
			this->buttonZone10Switch->Margin = System::Windows::Forms::Padding(4);
			this->buttonZone10Switch->Name = L"buttonZone10Switch";
			this->buttonZone10Switch->Size = System::Drawing::Size(88, 31);
			this->buttonZone10Switch->TabIndex = 3;
			this->buttonZone10Switch->Text = L"打开";
			this->buttonZone10Switch->UseVisualStyleBackColor = true;
			this->buttonZone10Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone10TempSet_Click);
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->Location = System::Drawing::Point(17, 65);
			this->label50->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(88, 16);
			this->label50->TabIndex = 1;
			this->label50->Text = L"设定温度: ";
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->Location = System::Drawing::Point(17, 31);
			this->label51->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(88, 16);
			this->label51->TabIndex = 0;
			this->label51->Text = L"实时温度: ";
			// 
			// groupBoxZone09
			// 
			this->groupBoxZone09->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone09->Controls->Add(this->labelZone09Setpoint);
			this->groupBoxZone09->Controls->Add(this->label42);
			this->groupBoxZone09->Controls->Add(this->label43);
			this->groupBoxZone09->Controls->Add(this->labelZone09RealTemp);
			this->groupBoxZone09->Controls->Add(this->buttonZone09Switch);
			this->groupBoxZone09->Controls->Add(this->label45);
			this->groupBoxZone09->Controls->Add(this->label46);
			this->groupBoxZone09->Location = System::Drawing::Point(10, 303);
			this->groupBoxZone09->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZone09->Name = L"groupBoxZone09";
			this->groupBoxZone09->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZone09->Size = System::Drawing::Size(175, 135);
			this->groupBoxZone09->TabIndex = 0;
			this->groupBoxZone09->TabStop = false;
			this->groupBoxZone09->Text = L"Zone09";
			// 
			// labelZone09Setpoint
			// 
			this->labelZone09Setpoint->AutoSize = true;
			this->labelZone09Setpoint->Location = System::Drawing::Point(94, 65);
			this->labelZone09Setpoint->Name = L"labelZone09Setpoint";
			this->labelZone09Setpoint->Size = System::Drawing::Size(32, 16);
			this->labelZone09Setpoint->TabIndex = 7;
			this->labelZone09Setpoint->Text = L"0.0";
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Location = System::Drawing::Point(143, 65);
			this->label42->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(24, 16);
			this->label42->TabIndex = 6;
			this->label42->Text = L"℃";
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Location = System::Drawing::Point(143, 32);
			this->label43->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(24, 16);
			this->label43->TabIndex = 6;
			this->label43->Text = L"℃";
			// 
			// labelZone09RealTemp
			// 
			this->labelZone09RealTemp->AutoSize = true;
			this->labelZone09RealTemp->Location = System::Drawing::Point(94, 31);
			this->labelZone09RealTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone09RealTemp->Name = L"labelZone09RealTemp";
			this->labelZone09RealTemp->Size = System::Drawing::Size(32, 16);
			this->labelZone09RealTemp->TabIndex = 5;
			this->labelZone09RealTemp->Text = L"0.0";
			// 
			// buttonZone09Switch
			// 
			this->buttonZone09Switch->Location = System::Drawing::Point(20, 96);
			this->buttonZone09Switch->Margin = System::Windows::Forms::Padding(4);
			this->buttonZone09Switch->Name = L"buttonZone09Switch";
			this->buttonZone09Switch->Size = System::Drawing::Size(88, 31);
			this->buttonZone09Switch->TabIndex = 3;
			this->buttonZone09Switch->Text = L"打开";
			this->buttonZone09Switch->UseVisualStyleBackColor = true;
			this->buttonZone09Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone09TempSet_Click);
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Location = System::Drawing::Point(17, 65);
			this->label45->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(88, 16);
			this->label45->TabIndex = 1;
			this->label45->Text = L"设定温度: ";
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->Location = System::Drawing::Point(17, 31);
			this->label46->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(88, 16);
			this->label46->TabIndex = 0;
			this->label46->Text = L"实时温度: ";
			// 
			// groupBoxZone06
			// 
			this->groupBoxZone06->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone06->Controls->Add(this->labelZone06Setpoint);
			this->groupBoxZone06->Controls->Add(this->label24);
			this->groupBoxZone06->Controls->Add(this->label25);
			this->groupBoxZone06->Controls->Add(this->labelZone06RealTemp);
			this->groupBoxZone06->Controls->Add(this->buttonZone06Switch);
			this->groupBoxZone06->Controls->Add(this->label30);
			this->groupBoxZone06->Controls->Add(this->label31);
			this->groupBoxZone06->Location = System::Drawing::Point(188, 160);
			this->groupBoxZone06->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZone06->Name = L"groupBoxZone06";
			this->groupBoxZone06->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZone06->Size = System::Drawing::Size(175, 135);
			this->groupBoxZone06->TabIndex = 0;
			this->groupBoxZone06->TabStop = false;
			this->groupBoxZone06->Text = L"Zone06";
			// 
			// labelZone06Setpoint
			// 
			this->labelZone06Setpoint->AutoSize = true;
			this->labelZone06Setpoint->Location = System::Drawing::Point(93, 65);
			this->labelZone06Setpoint->Name = L"labelZone06Setpoint";
			this->labelZone06Setpoint->Size = System::Drawing::Size(32, 16);
			this->labelZone06Setpoint->TabIndex = 7;
			this->labelZone06Setpoint->Text = L"0.0";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(142, 65);
			this->label24->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(24, 16);
			this->label24->TabIndex = 6;
			this->label24->Text = L"℃";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(142, 32);
			this->label25->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(24, 16);
			this->label25->TabIndex = 6;
			this->label25->Text = L"℃";
			// 
			// labelZone06RealTemp
			// 
			this->labelZone06RealTemp->AutoSize = true;
			this->labelZone06RealTemp->Location = System::Drawing::Point(93, 31);
			this->labelZone06RealTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone06RealTemp->Name = L"labelZone06RealTemp";
			this->labelZone06RealTemp->Size = System::Drawing::Size(32, 16);
			this->labelZone06RealTemp->TabIndex = 5;
			this->labelZone06RealTemp->Text = L"0.0";
			// 
			// buttonZone06Switch
			// 
			this->buttonZone06Switch->Location = System::Drawing::Point(17, 95);
			this->buttonZone06Switch->Margin = System::Windows::Forms::Padding(4);
			this->buttonZone06Switch->Name = L"buttonZone06Switch";
			this->buttonZone06Switch->Size = System::Drawing::Size(88, 31);
			this->buttonZone06Switch->TabIndex = 3;
			this->buttonZone06Switch->Text = L"打开";
			this->buttonZone06Switch->UseVisualStyleBackColor = true;
			this->buttonZone06Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone06TempSet_Click);
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(17, 65);
			this->label30->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(88, 16);
			this->label30->TabIndex = 1;
			this->label30->Text = L"设定温度: ";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(17, 31);
			this->label31->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(88, 16);
			this->label31->TabIndex = 0;
			this->label31->Text = L"实时温度: ";
			// 
			// groupBoxZone05
			// 
			this->groupBoxZone05->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone05->Controls->Add(this->labelZone05Setpoint);
			this->groupBoxZone05->Controls->Add(this->label19);
			this->groupBoxZone05->Controls->Add(this->label20);
			this->groupBoxZone05->Controls->Add(this->labelZone05RealTemp);
			this->groupBoxZone05->Controls->Add(this->buttonZone05Switch);
			this->groupBoxZone05->Controls->Add(this->label22);
			this->groupBoxZone05->Controls->Add(this->label23);
			this->groupBoxZone05->Location = System::Drawing::Point(10, 160);
			this->groupBoxZone05->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZone05->Name = L"groupBoxZone05";
			this->groupBoxZone05->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZone05->Size = System::Drawing::Size(175, 135);
			this->groupBoxZone05->TabIndex = 0;
			this->groupBoxZone05->TabStop = false;
			this->groupBoxZone05->Text = L"Zone05";
			// 
			// labelZone05Setpoint
			// 
			this->labelZone05Setpoint->AutoSize = true;
			this->labelZone05Setpoint->Location = System::Drawing::Point(94, 65);
			this->labelZone05Setpoint->Name = L"labelZone05Setpoint";
			this->labelZone05Setpoint->Size = System::Drawing::Size(32, 16);
			this->labelZone05Setpoint->TabIndex = 7;
			this->labelZone05Setpoint->Text = L"0.0";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(143, 65);
			this->label19->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(24, 16);
			this->label19->TabIndex = 6;
			this->label19->Text = L"℃";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(143, 32);
			this->label20->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(24, 16);
			this->label20->TabIndex = 6;
			this->label20->Text = L"℃";
			// 
			// labelZone05RealTemp
			// 
			this->labelZone05RealTemp->AutoSize = true;
			this->labelZone05RealTemp->Location = System::Drawing::Point(94, 31);
			this->labelZone05RealTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone05RealTemp->Name = L"labelZone05RealTemp";
			this->labelZone05RealTemp->Size = System::Drawing::Size(32, 16);
			this->labelZone05RealTemp->TabIndex = 5;
			this->labelZone05RealTemp->Text = L"0.0";
			// 
			// buttonZone05Switch
			// 
			this->buttonZone05Switch->Location = System::Drawing::Point(20, 95);
			this->buttonZone05Switch->Margin = System::Windows::Forms::Padding(4);
			this->buttonZone05Switch->Name = L"buttonZone05Switch";
			this->buttonZone05Switch->Size = System::Drawing::Size(88, 31);
			this->buttonZone05Switch->TabIndex = 3;
			this->buttonZone05Switch->Text = L"打开";
			this->buttonZone05Switch->UseVisualStyleBackColor = true;
			this->buttonZone05Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone05TempSet_Click);
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(17, 65);
			this->label22->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(88, 16);
			this->label22->TabIndex = 1;
			this->label22->Text = L"设定温度: ";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(17, 31);
			this->label23->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(88, 16);
			this->label23->TabIndex = 0;
			this->label23->Text = L"实时温度: ";
			// 
			// groupBoxZone02
			// 
			this->groupBoxZone02->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone02->Controls->Add(this->labelZone02Setpoint);
			this->groupBoxZone02->Controls->Add(this->label4);
			this->groupBoxZone02->Controls->Add(this->label5);
			this->groupBoxZone02->Controls->Add(this->labelZone02RealTemp);
			this->groupBoxZone02->Controls->Add(this->buttonZone02Switch);
			this->groupBoxZone02->Controls->Add(this->label7);
			this->groupBoxZone02->Controls->Add(this->label8);
			this->groupBoxZone02->Location = System::Drawing::Point(188, 17);
			this->groupBoxZone02->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZone02->Name = L"groupBoxZone02";
			this->groupBoxZone02->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZone02->Size = System::Drawing::Size(175, 135);
			this->groupBoxZone02->TabIndex = 0;
			this->groupBoxZone02->TabStop = false;
			this->groupBoxZone02->Text = L"Zone02";
			// 
			// labelZone02Setpoint
			// 
			this->labelZone02Setpoint->AutoSize = true;
			this->labelZone02Setpoint->Location = System::Drawing::Point(93, 65);
			this->labelZone02Setpoint->Name = L"labelZone02Setpoint";
			this->labelZone02Setpoint->Size = System::Drawing::Size(32, 16);
			this->labelZone02Setpoint->TabIndex = 7;
			this->labelZone02Setpoint->Text = L"0.0";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(142, 65);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(24, 16);
			this->label4->TabIndex = 6;
			this->label4->Text = L"℃";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(142, 32);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(24, 16);
			this->label5->TabIndex = 6;
			this->label5->Text = L"℃";
			// 
			// labelZone02RealTemp
			// 
			this->labelZone02RealTemp->AutoSize = true;
			this->labelZone02RealTemp->Location = System::Drawing::Point(93, 31);
			this->labelZone02RealTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone02RealTemp->Name = L"labelZone02RealTemp";
			this->labelZone02RealTemp->Size = System::Drawing::Size(32, 16);
			this->labelZone02RealTemp->TabIndex = 5;
			this->labelZone02RealTemp->Text = L"0.0";
			// 
			// buttonZone02Switch
			// 
			this->buttonZone02Switch->Location = System::Drawing::Point(20, 94);
			this->buttonZone02Switch->Margin = System::Windows::Forms::Padding(4);
			this->buttonZone02Switch->Name = L"buttonZone02Switch";
			this->buttonZone02Switch->Size = System::Drawing::Size(88, 31);
			this->buttonZone02Switch->TabIndex = 3;
			this->buttonZone02Switch->Text = L"打开";
			this->buttonZone02Switch->UseVisualStyleBackColor = true;
			this->buttonZone02Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone02TempSet_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(17, 65);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(88, 16);
			this->label7->TabIndex = 1;
			this->label7->Text = L"设定温度: ";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(17, 31);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(88, 16);
			this->label8->TabIndex = 0;
			this->label8->Text = L"实时温度: ";
			// 
			// groupBoxZone01
			// 
			this->groupBoxZone01->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone01->Controls->Add(this->labelZone01Setpoint);
			this->groupBoxZone01->Controls->Add(this->label28);
			this->groupBoxZone01->Controls->Add(this->label27);
			this->groupBoxZone01->Controls->Add(this->labelZone01RealTemp);
			this->groupBoxZone01->Controls->Add(this->buttonZone01Switch);
			this->groupBoxZone01->Controls->Add(this->label3);
			this->groupBoxZone01->Controls->Add(this->label2);
			this->groupBoxZone01->Location = System::Drawing::Point(10, 17);
			this->groupBoxZone01->Margin = System::Windows::Forms::Padding(4);
			this->groupBoxZone01->Name = L"groupBoxZone01";
			this->groupBoxZone01->Padding = System::Windows::Forms::Padding(4);
			this->groupBoxZone01->Size = System::Drawing::Size(175, 135);
			this->groupBoxZone01->TabIndex = 0;
			this->groupBoxZone01->TabStop = false;
			this->groupBoxZone01->Text = L"Zone01";
			// 
			// labelZone01Setpoint
			// 
			this->labelZone01Setpoint->AutoSize = true;
			this->labelZone01Setpoint->Location = System::Drawing::Point(94, 65);
			this->labelZone01Setpoint->Name = L"labelZone01Setpoint";
			this->labelZone01Setpoint->Size = System::Drawing::Size(32, 16);
			this->labelZone01Setpoint->TabIndex = 7;
			this->labelZone01Setpoint->Text = L"0.0";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(142, 65);
			this->label28->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(24, 16);
			this->label28->TabIndex = 6;
			this->label28->Text = L"℃";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(142, 32);
			this->label27->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(24, 16);
			this->label27->TabIndex = 6;
			this->label27->Text = L"℃";
			// 
			// labelZone01RealTemp
			// 
			this->labelZone01RealTemp->AutoSize = true;
			this->labelZone01RealTemp->Location = System::Drawing::Point(93, 31);
			this->labelZone01RealTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone01RealTemp->Name = L"labelZone01RealTemp";
			this->labelZone01RealTemp->Size = System::Drawing::Size(32, 16);
			this->labelZone01RealTemp->TabIndex = 5;
			this->labelZone01RealTemp->Text = L"0.0";
			// 
			// buttonZone01Switch
			// 
			this->buttonZone01Switch->Location = System::Drawing::Point(17, 94);
			this->buttonZone01Switch->Margin = System::Windows::Forms::Padding(4);
			this->buttonZone01Switch->Name = L"buttonZone01Switch";
			this->buttonZone01Switch->Size = System::Drawing::Size(88, 31);
			this->buttonZone01Switch->TabIndex = 3;
			this->buttonZone01Switch->Text = L"打开";
			this->buttonZone01Switch->UseVisualStyleBackColor = true;
			this->buttonZone01Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone01TempSet_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(17, 65);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(88, 16);
			this->label3->TabIndex = 1;
			this->label3->Text = L"设定温度: ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(17, 31);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(88, 16);
			this->label2->TabIndex = 0;
			this->label2->Text = L"实时温度: ";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(764, 560);
			this->Controls->Add(this->groupBoxZones);
			this->Controls->Add(this->groupBox1);
			this->Font = (gcnew System::Drawing::Font(L"宋体", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->KeyPreview = true;
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
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

private: System::Void buttonZone01TempSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		
		if (currentHusky->getZoneOnOff(1)) {
			currentHusky->setZoneOnOff(1, FALSE);
			this->buttonZone01Switch->Text = L"打开";
		} else {
			currentHusky->setZoneOnOff(1, TRUE);
			this->buttonZone01Switch->Text = L"关闭";
		}
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
		
		if (currentHusky->getZoneOnOff(2)) {
			currentHusky->setZoneOnOff(2, FALSE);
			this->buttonZone02Switch->Text = L"打开";
		} else {
			currentHusky->setZoneOnOff(2, TRUE);
			this->buttonZone02Switch->Text = L"关闭";
		}
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
		if (currentHusky->getZoneOnOff(3)) {
			currentHusky->setZoneOnOff(3, FALSE);
			this->buttonZone03Switch->Text = L"打开";
		} else {
			currentHusky->setZoneOnOff(3, TRUE);
			this->buttonZone03Switch->Text = L"关闭";
		}
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
		if (currentHusky->getZoneOnOff(4)) {
			currentHusky->setZoneOnOff(4, FALSE);
			this->buttonZone04Switch->Text = L"打开";
		} else {
			currentHusky->setZoneOnOff(4, TRUE);
			this->buttonZone04Switch->Text = L"关闭";
		}
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
		if (currentHusky->getZoneOnOff(5)) {
			currentHusky->setZoneOnOff(5, FALSE);
			this->buttonZone05Switch->Text = L"打开";
		} else {
			currentHusky->setZoneOnOff(5, TRUE);
			this->buttonZone05Switch->Text = L"关闭";
		}
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
		if (currentHusky->getZoneOnOff(6)) {
			currentHusky->setZoneOnOff(6, FALSE);
			this->buttonZone06Switch->Text = L"打开";
		} else {
			currentHusky->setZoneOnOff(6, TRUE);
			this->buttonZone06Switch->Text = L"关闭";
		}
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
		if (currentHusky->getZoneOnOff(7)) {
			currentHusky->setZoneOnOff(7, FALSE);
			this->buttonZone07Switch->Text = L"打开";
		} else {
			currentHusky->setZoneOnOff(7, TRUE);
			this->buttonZone07Switch->Text = L"关闭";
		}
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
		if (currentHusky->getZoneOnOff(8)) {
			currentHusky->setZoneOnOff(8, FALSE);
			this->buttonZone08Switch->Text = L"打开";
		} else {
			currentHusky->setZoneOnOff(8, TRUE);
			this->buttonZone08Switch->Text = L"关闭";
		}
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
		if (currentHusky->getZoneOnOff(9)) {
			currentHusky->setZoneOnOff(9, FALSE);
			this->buttonZone09Switch->Text = L"打开";
		} else {
			currentHusky->setZoneOnOff(9, TRUE);
			this->buttonZone09Switch->Text = L"关闭";
		}
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
		if (currentHusky->getZoneOnOff(10)) {
			currentHusky->setZoneOnOff(10, FALSE);
			this->buttonZone10Switch->Text = L"打开";
		} else {
			currentHusky->setZoneOnOff(10, TRUE);
			this->buttonZone10Switch->Text = L"关闭";
		}
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
		if (currentHusky->getZoneOnOff(11)) {
			currentHusky->setZoneOnOff(11, FALSE);
			this->buttonZone11Switch->Text = L"打开";
		} else {
			currentHusky->setZoneOnOff(11, TRUE);
			this->buttonZone11Switch->Text = L"关闭";
		}
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
		if (currentHusky->getZoneOnOff(12)) {
			currentHusky->setZoneOnOff(12, FALSE);
			this->buttonZone12Switch->Text = L"打开";
		} else {
			currentHusky->setZoneOnOff(12, TRUE);
			this->buttonZone12Switch->Text = L"关闭";
		}
	}


private: System::Void buttonConnect_Click(System::Object^  sender, System::EventArgs^  e) {
	if (currentHusky == NULL) {
		MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		return;
	}

	if (currentHusky->isConnected()) {
		currentHusky->disconnect();
		this->buttonConnect->Text = L"连接";
	} else {
		if (currentHusky->connect())
			this->buttonConnect->Text = L"断开";
		else
			MessageBox::Show("连接失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
}
/*
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
*/
private: System::Void button27_Click(System::Object^  sender, System::EventArgs^  e) {
		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}

		for (int i = 0; i < 12; i++) {
			float temperature = currentHusky->getTemperature(i + 1);
			// C = (F - 32) / 1.8
			temperature = (temperature - 32) / 1.8;
			int tmp = temperature * 10 + 0.5;
			temperature = (float)tmp / 10;
			this->labelZonesSetpoint[i]->Text = temperature.ToString();
		}
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

		SetAllZonesTemperatureForm^ setAllZonesTemperatureForm = gcnew SetAllZonesTemperatureForm();
		System::Windows::Forms::DialogResult result = setAllZonesTemperatureForm->ShowDialog();
		if (result == ::DialogResult::OK) {
			for (int i = 0; i < 12; i++) {
				if (setAllZonesTemperatureForm->checkBoxAllZonesArray[i]->Checked) {
					float temperature = Convert::ToDouble(setAllZonesTemperatureForm->textBoxTemperature->Text);
					// F = 32 + C * 1.8;
					temperature = 32 + temperature * 1.8;
					if (currentHusky->setTemperature(temperature, i + 1) == FALSE)
						MessageBox::Show("Zone" + (i+1) + " 设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
					else
						this->labelZonesSetpoint[i]->Text = setAllZonesTemperatureForm->textBoxTemperature->Text; // update setpoint
				}
			}
		}
	}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
/*
		currentHusky = huskys[this->comboBox1->SelectedIndex];
		char currentHuskyIp[IP_ADDRESS_STRING_LEN];
		currentHusky->getIpAddr(currentHuskyIp);
		this->labelIpAddr->Text = gcnew String("IP: ") + gcnew String(currentHuskyIp);
*/
		currentHusky->setSerialPortNum(this->comboBox1->SelectedIndex + 1);
	}
};
}

