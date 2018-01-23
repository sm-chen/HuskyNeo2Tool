#pragma once

#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#include "Husky.h"
#include "IpConfigure.h"
#include "SetOneZoneTemperatureForm.h"
#include "SetAllZonesTemperatureForm.h"
#include "AlarmStatusWindow.h"
#include "SetTempInProgressForm.h"

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
			//alarmStatusWindow = gcnew AlarmStatusWindow();

			setAllZonesTemperatureForm = gcnew SetAllZonesTemperatureForm();
			setTempInProgressForm = gcnew SetTempInProgressForm();

			realtimeTemperatureUiUpdate = gcnew UiUpdate(this, &HuskyNeo2Tool::Form1::realtimeTemperatureUiUpdateMethod);
			setpointUiUpdate = gcnew UiUpdate(this, &HuskyNeo2Tool::Form1::setpointUiUpdateMethod);
			zoneSwitchUiUpdate = gcnew UiUpdate(this, &HuskyNeo2Tool::Form1::zoneSwitchUiUpdateMethod);
			myShowAlarmMsg = gcnew showAlarmMsg(this, &HuskyNeo2Tool::Form1::showAlarmMsgMethod);
			setTempProgressUiUpdate = gcnew UiUpdate(this, &HuskyNeo2Tool::Form1::setTempProgressUiUpdateMethod);
			showCommunicationErrUiUpdate = gcnew UiUpdate(this, &HuskyNeo2Tool::Form1::showCommunicationErrUiUpdateMethod);
			opLock = FALSE;

			t2 = gcnew Thread(gcnew ThreadStart(this, &HuskyNeo2Tool::Form1::alarmStatusCheckingThread));
			t2->IsBackground = true;
			t2->Start();

			t1 = gcnew Thread(gcnew ThreadStart(this, &HuskyNeo2Tool::Form1::UiUpdateThread));
			t1->IsBackground = true;
			t1->Start();

			this->comboBox1->SelectedIndex = 0;
			if (currentHusky->connect())
				this->buttonConnect->Text = L"断开";

			communicationErrDetectThreadHandle = gcnew Thread(gcnew ThreadStart(this, &HuskyNeo2Tool::Form1::communicationErrDetectThread));
			communicationErrDetectThreadHandle->IsBackground = true;
			communicationErrDetectThreadHandle->Start();
		}

	protected:
		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (currentHusky && currentHusky->isConnected())
				currentHusky->disconnect();
			if (t2 && t2->IsAlive)
				t2->Abort();
			if (t1 &&t1->IsAlive)
				t1->Abort();
			if (readTemperatureButtonThread && readTemperatureButtonThread->IsAlive)
				readTemperatureButtonThread->Abort();

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
		BOOLEAN opLock;

		SetAllZonesTemperatureForm^ setAllZonesTemperatureForm;
		SetTempInProgressForm^ setTempInProgressForm;
		String^ failedZones;
		Thread ^setTemperatureButtonThread;

		Thread ^readTemperatureButtonThread;
		Thread ^t2;
		Thread ^t1;
		Thread ^communicationErrDetectThreadHandle;

	private: // UI Update
		delegate void UiUpdate(int i, float value);
		UiUpdate^ realtimeTemperatureUiUpdate;
		UiUpdate^ setpointUiUpdate;
		UiUpdate^ zoneSwitchUiUpdate;
		UiUpdate^ setTempProgressUiUpdate;
private: System::Windows::Forms::Button^  buttonLock;













		 UiUpdate^ showCommunicationErrUiUpdate;
	
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
		// value: 0 -> close Progress window;
		void setTempProgressUiUpdateMethod(int i, float value)
		{
			if (value == 0) {
				setTempInProgressForm->Close();
			} else {
				MessageBox::Show("Zones: " + failedZones + " 温度设置失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			}
		}
		void showCommunicationErrUiUpdateMethod(int i, float value)
		{
			MessageBox::Show("通讯故障！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			//currentHusky->restoreCommunicationErr();
		}

		void UiUpdateThread()
		{
			int tmp = 0;
			do {
				if (currentHusky == NULL || !currentHusky->isConnected()) {
					Sleep(5000);
					continue;
				}

				if (tmp % 5 == 0) { // update UI every 2 * 5 = 10S
					tmp = 1;
					for (int i = 0; i < 12; i++) {
						if (currentHusky == NULL || !currentHusky->isConnected()) {
							break;
						}
						float temperature = currentHusky->getTemperature(i + 1);
						// C = (F - 32) / 1.8
						temperature = (temperature - 32) / (float)1.8;
						//int tmp = temperature * 10 + 0.5;
						//temperature = (float)tmp / 10;
						int tmp = (int)(temperature + 0.5);
						this->Invoke(this->setpointUiUpdate, i, tmp);
						Sleep(50);
					}

					for (int i = 0; i < 12; i++) {
						if (currentHusky == NULL || !currentHusky->isConnected()) {
							break;
						}
						if (currentHusky->getZoneOnOff(i + 1)) {
							this->Invoke(this->zoneSwitchUiUpdate, i, (float)0);
						} else {
							this->Invoke(this->zoneSwitchUiUpdate, i, 1);
						}
						Sleep(50);
					}
				} else
					tmp++;

				for (int i = 0; i < 12; i++) {
					if (currentHusky == NULL || !currentHusky->isConnected()) {
						break;
					}
					float realtimeTemperature = currentHusky->getRealtimeTemperature(i + 1);
					if (realtimeTemperature == 0) {
						this->Invoke(this->realtimeTemperatureUiUpdate, i, (float)0);
					} else {
						realtimeTemperature = (realtimeTemperature - 32) / (float)1.8;
						//int tmp = realtimeTemperature * 10 + 0.5;
						//realtimeTemperature = (float)tmp / 10;
						int tmp = (int)(realtimeTemperature + 0.5);
						this->Invoke(this->realtimeTemperatureUiUpdate, i, tmp);
					}
					Sleep(50);
				} 
				Sleep(2000);
			} while (1);
		}

		void ReadTemperatureButtonThread()
		{
			if (currentHusky == NULL || !currentHusky->isConnected()) {
				return;
			}
			for (int i = 0; i < 12; i++) {
				if (currentHusky == NULL || !currentHusky->isConnected()) {
					break;
				}
				float temperature = currentHusky->getTemperature(i + 1);
				// C = (F - 32) / 1.8
				temperature = (temperature - 32) / (float)1.8;
				//int tmp = temperature * 10 + 0.5;
				//temperature = (float)tmp / 10;
				int tmp = (int)(temperature + 0.5);
				//this->labelZonesSetpoint[i]->Text = temperature.ToString();
				this->Invoke(this->setpointUiUpdate, i, tmp);
			}
		}
		void SetTemperatureButtonThread()
		{
			if (currentHusky == NULL || !currentHusky->isConnected()) {
				return;
			}

			failedZones = "";
			for (int i = 0; i < 12; i++) {
				if (setAllZonesTemperatureForm->checkBoxAllZonesArray[i]->Checked) {
					float temperature = (float)Convert::ToDouble(setAllZonesTemperatureForm->textBoxTemperature->Text);
					// F -> C: F = 32 + C * 1.8;
					float Fahrenheit = 32 + temperature * (float)1.8;
					if (currentHusky->setTemperature(Fahrenheit, i + 1) == FALSE)
						failedZones = failedZones + (i + 1) + " ";
						//MessageBox::Show("Zone" + (i+1) + " 设置温度失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
					//else
						//this->Invoke(this->setpointUiUpdate, i, temperature);
						//this->labelZonesSetpoint[i]->Text = setAllZonesTemperatureForm->textBoxTemperature->Text; // update setpoint
				}
			}
			ReadTemperatureButtonThread(); // update set point.
			if (failedZones != "")
				this->Invoke(this->setTempProgressUiUpdate, 0, 1);

			this->Invoke(this->setTempProgressUiUpdate, 0, 0);
		}

		void communicationErrDetectThread()
		{
			Sleep(5000);
			while (1) {
				if (currentHusky != NULL && currentHusky->isConnected() && currentHusky->isCommunicationErr()) {
					this->Invoke(this->showCommunicationErrUiUpdate, 0, 0);
					currentHusky->restoreCommunicationErr();
				}
				Sleep(1000);
			}
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
			/* // test
			while (1) {
				Sleep(3000);
				alarmStatusWindow->labelZoneAlarmMsgArray[1]->ForeColor = System::Drawing::Color::Black;
				this->Invoke(this->myShowAlarmMsg);
			}
			*/
			while (1) {
				if (currentHusky == NULL || !currentHusky->isConnected()) {
					Sleep(1000);
					continue;
				}
				for (int i = 0; i < 12; i++) {
					if (currentHusky == NULL || !currentHusky->isConnected()) {
						break;
					}
					uint16_t status = currentHusky->getControlerStatus(i + 1);
					if (status && status != MANUAL_REGULATION) {
						if (currentHusky == NULL || !currentHusky->isConnected())
							break;

						uint16_t status1 = currentHusky->getControlerStatus(1);
						uint16_t status2 = currentHusky->getControlerStatus(2);
						uint16_t status3 = currentHusky->getControlerStatus(3);
						uint16_t status4 = currentHusky->getControlerStatus(4);
						uint16_t status5 = currentHusky->getControlerStatus(5);
						uint16_t status6 = currentHusky->getControlerStatus(6);
						uint16_t status7 = currentHusky->getControlerStatus(7);
						uint16_t status8 = currentHusky->getControlerStatus(8);
						uint16_t status9 = currentHusky->getControlerStatus(9);
						uint16_t status10 = currentHusky->getControlerStatus(10);
						uint16_t status11 = currentHusky->getControlerStatus(11);
						uint16_t status12 = currentHusky->getControlerStatus(12);

						char *msg1 = currentHusky->getControlerStatusString(status1);
						char *msg2 = currentHusky->getControlerStatusString(status2);
						char *msg3 = currentHusky->getControlerStatusString(status3);
						char *msg4 = currentHusky->getControlerStatusString(status4);
						char *msg5 = currentHusky->getControlerStatusString(status5);
						char *msg6 = currentHusky->getControlerStatusString(status6);
						char *msg7 = currentHusky->getControlerStatusString(status7);
						char *msg8 = currentHusky->getControlerStatusString(status8);
						char *msg9 = currentHusky->getControlerStatusString(status9);
						char *msg10 = currentHusky->getControlerStatusString(status10);
						char *msg11 = currentHusky->getControlerStatusString(status11);
						char *msg12 = currentHusky->getControlerStatusString(status12);

						alarmStatusWindow = gcnew AlarmStatusWindow();

						alarmStatusWindow->labelZoneAlarmMsgArray[0]->Text = gcnew String(msg1);
						alarmStatusWindow->labelZoneAlarmMsgArray[1]->Text = gcnew String(msg2);
						alarmStatusWindow->labelZoneAlarmMsgArray[2]->Text = gcnew String(msg3);
						alarmStatusWindow->labelZoneAlarmMsgArray[3]->Text = gcnew String(msg4);
						alarmStatusWindow->labelZoneAlarmMsgArray[4]->Text = gcnew String(msg5);
						alarmStatusWindow->labelZoneAlarmMsgArray[5]->Text = gcnew String(msg6);
						alarmStatusWindow->labelZoneAlarmMsgArray[6]->Text = gcnew String(msg7);
						alarmStatusWindow->labelZoneAlarmMsgArray[7]->Text = gcnew String(msg8);
						alarmStatusWindow->labelZoneAlarmMsgArray[8]->Text = gcnew String(msg9);
						alarmStatusWindow->labelZoneAlarmMsgArray[9]->Text = gcnew String(msg10);
						alarmStatusWindow->labelZoneAlarmMsgArray[10]->Text = gcnew String(msg11);
						alarmStatusWindow->labelZoneAlarmMsgArray[11]->Text = gcnew String(msg12);

						this->Invoke(this->myShowAlarmMsg);
						Sleep(2000);
						break;
					}
					Sleep(1000);
				}
				Sleep(1000);
			}
		}
private: System::Windows::Forms::Label^  labelComNumPrompt;



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
private: System::Windows::Forms::Label^  labelRealTempPrompt01;
private: System::Windows::Forms::Label^  labelSetpointPrompt01;


	private: System::Windows::Forms::Button^  buttonZone01Switch;
	private: System::Windows::Forms::Label^  labelZone01RealTemp;
private: System::Windows::Forms::Label^  labelSetpointUnits01;

private: System::Windows::Forms::Label^  labelRealTempUnits01;

	private: System::Windows::Forms::GroupBox^  groupBoxZone12;
private: System::Windows::Forms::Label^  labelSetpointUnits12;

private: System::Windows::Forms::Label^  labelRealTempUnits12;

	private: System::Windows::Forms::Label^  labelZone12RealTemp;
	private: System::Windows::Forms::Button^  buttonZone12Switch;
private: System::Windows::Forms::Label^  labelSetpointPrompt12;

private: System::Windows::Forms::Label^  labelRealTempPrompt12;

	private: System::Windows::Forms::GroupBox^  groupBoxZone08;
private: System::Windows::Forms::Label^  labelSetpointUnits08;

private: System::Windows::Forms::Label^  labelRealTempUnits08;

	private: System::Windows::Forms::Label^  labelZone08RealTemp;
	private: System::Windows::Forms::Button^  buttonZone08Switch;
private: System::Windows::Forms::Label^  labelSetpointPrompt08;

private: System::Windows::Forms::Label^  labelRealTempPrompt08;

	private: System::Windows::Forms::GroupBox^  groupBoxZone04;
private: System::Windows::Forms::Label^  labelSetpointUnits04;

private: System::Windows::Forms::Label^  labelRealTempUnits04;

	private: System::Windows::Forms::Label^  labelZone04RealTemp;
	private: System::Windows::Forms::Button^  buttonZone04Switch;
private: System::Windows::Forms::Label^  labelSetpointPrompt04;

private: System::Windows::Forms::Label^  labelRealTempPrompt04;

	private: System::Windows::Forms::GroupBox^  groupBoxZone11;
private: System::Windows::Forms::Label^  labelSetpointUnits11;

private: System::Windows::Forms::Label^  labelRealTempUnits11;

	private: System::Windows::Forms::Label^  labelZone11RealTemp;
	private: System::Windows::Forms::Button^  buttonZone11Switch;
private: System::Windows::Forms::Label^  labelSetpointPrompt11;

private: System::Windows::Forms::Label^  labelRealTempPrompt11;

	private: System::Windows::Forms::GroupBox^  groupBoxZone07;
private: System::Windows::Forms::Label^  labelSetpointUnits07;

private: System::Windows::Forms::Label^  labelRealTempUnits07;

	private: System::Windows::Forms::Label^  labelZone07RealTemp;
	private: System::Windows::Forms::Button^  buttonZone07Switch;
private: System::Windows::Forms::Label^  labelSetpointPrompt07;


private: System::Windows::Forms::Label^  labelRealTempPrompt07;

	private: System::Windows::Forms::GroupBox^  groupBoxZone03;
private: System::Windows::Forms::Label^  labelSetpointUnits03;


private: System::Windows::Forms::Label^  labelRealTempUnits03;

	private: System::Windows::Forms::Label^  labelZone03RealTemp;
	private: System::Windows::Forms::Button^  buttonZone03Switch;
private: System::Windows::Forms::Label^  labelSetpointPrompt03;


private: System::Windows::Forms::Label^  labelRealTempPrompt03;

	private: System::Windows::Forms::GroupBox^  groupBoxZone10;
private: System::Windows::Forms::Label^  labelSetpointUnits10;


private: System::Windows::Forms::Label^  labelRealTempUnits10;

	private: System::Windows::Forms::Label^  labelZone10RealTemp;
	private: System::Windows::Forms::Button^  buttonZone10Switch;
private: System::Windows::Forms::Label^  labelSetpointPrompt10;


private: System::Windows::Forms::Label^  labelRealTempPrompt10;

	private: System::Windows::Forms::GroupBox^  groupBoxZone09;
private: System::Windows::Forms::Label^  labelSetpointUnits09;


private: System::Windows::Forms::Label^  labelRealTempUnits09;

	private: System::Windows::Forms::Label^  labelZone09RealTemp;
	private: System::Windows::Forms::Button^  buttonZone09Switch;
private: System::Windows::Forms::Label^  labelSetpointPrompt09;


private: System::Windows::Forms::Label^  labelRealTempPrompt09;

	private: System::Windows::Forms::GroupBox^  groupBoxZone06;
private: System::Windows::Forms::Label^  labelSetpointUnits06;


private: System::Windows::Forms::Label^  labelRealTempUnits06;

	private: System::Windows::Forms::Label^  labelZone06RealTemp;
	private: System::Windows::Forms::Button^  buttonZone06Switch;
private: System::Windows::Forms::Label^  labelSetpointPrompt06;


private: System::Windows::Forms::Label^  labelRealTempPrompt06;

	private: System::Windows::Forms::GroupBox^  groupBoxZone05;
private: System::Windows::Forms::Label^  labelSetpointUnits05;


private: System::Windows::Forms::Label^  labelRealTempUnits05;

	private: System::Windows::Forms::Label^  labelZone05RealTemp;
	private: System::Windows::Forms::Button^  buttonZone05Switch;
private: System::Windows::Forms::Label^  labelSetpointPrompt05;
private: System::Windows::Forms::Label^  labelRealTempPrompt05;



	private: System::Windows::Forms::GroupBox^  groupBoxZone02;
private: System::Windows::Forms::Label^  labelSetpointUnits02;


private: System::Windows::Forms::Label^  labelRealTempUnits02;

	private: System::Windows::Forms::Label^  labelZone02RealTemp;
	private: System::Windows::Forms::Button^  buttonZone02Switch;
private: System::Windows::Forms::Label^  labelSetpointPrompt02;


private: System::Windows::Forms::Label^  labelRealTempPrompt02;

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
			this->buttonLock = (gcnew System::Windows::Forms::Button());
			this->labelComNumPrompt = (gcnew System::Windows::Forms::Label());
			this->button28 = (gcnew System::Windows::Forms::Button());
			this->button27 = (gcnew System::Windows::Forms::Button());
			this->buttonConnect = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBoxZones = (gcnew System::Windows::Forms::GroupBox());
			this->groupBoxZone12 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone12Setpoint = (gcnew System::Windows::Forms::Label());
			this->labelSetpointUnits12 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempUnits12 = (gcnew System::Windows::Forms::Label());
			this->labelZone12RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone12Switch = (gcnew System::Windows::Forms::Button());
			this->labelSetpointPrompt12 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempPrompt12 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone08 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone08Setpoint = (gcnew System::Windows::Forms::Label());
			this->labelSetpointUnits08 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempUnits08 = (gcnew System::Windows::Forms::Label());
			this->labelZone08RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone08Switch = (gcnew System::Windows::Forms::Button());
			this->labelSetpointPrompt08 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempPrompt08 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone04 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone04Setpoint = (gcnew System::Windows::Forms::Label());
			this->labelSetpointUnits04 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempUnits04 = (gcnew System::Windows::Forms::Label());
			this->labelZone04RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone04Switch = (gcnew System::Windows::Forms::Button());
			this->labelSetpointPrompt04 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempPrompt04 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone11 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone11Setpoint = (gcnew System::Windows::Forms::Label());
			this->labelSetpointUnits11 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempUnits11 = (gcnew System::Windows::Forms::Label());
			this->labelZone11RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone11Switch = (gcnew System::Windows::Forms::Button());
			this->labelSetpointPrompt11 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempPrompt11 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone07 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone07Setpoint = (gcnew System::Windows::Forms::Label());
			this->labelSetpointUnits07 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempUnits07 = (gcnew System::Windows::Forms::Label());
			this->labelZone07RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone07Switch = (gcnew System::Windows::Forms::Button());
			this->labelSetpointPrompt07 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempPrompt07 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone03 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone03Setpoint = (gcnew System::Windows::Forms::Label());
			this->labelSetpointUnits03 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempUnits03 = (gcnew System::Windows::Forms::Label());
			this->labelZone03RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone03Switch = (gcnew System::Windows::Forms::Button());
			this->labelSetpointPrompt03 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempPrompt03 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone10 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone10Setpoint = (gcnew System::Windows::Forms::Label());
			this->labelSetpointUnits10 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempUnits10 = (gcnew System::Windows::Forms::Label());
			this->labelZone10RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone10Switch = (gcnew System::Windows::Forms::Button());
			this->labelSetpointPrompt10 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempPrompt10 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone09 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone09Setpoint = (gcnew System::Windows::Forms::Label());
			this->labelSetpointUnits09 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempUnits09 = (gcnew System::Windows::Forms::Label());
			this->labelZone09RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone09Switch = (gcnew System::Windows::Forms::Button());
			this->labelSetpointPrompt09 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempPrompt09 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone06 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone06Setpoint = (gcnew System::Windows::Forms::Label());
			this->labelSetpointUnits06 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempUnits06 = (gcnew System::Windows::Forms::Label());
			this->labelZone06RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone06Switch = (gcnew System::Windows::Forms::Button());
			this->labelSetpointPrompt06 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempPrompt06 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone05 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone05Setpoint = (gcnew System::Windows::Forms::Label());
			this->labelSetpointUnits05 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempUnits05 = (gcnew System::Windows::Forms::Label());
			this->labelZone05RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone05Switch = (gcnew System::Windows::Forms::Button());
			this->labelSetpointPrompt05 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempPrompt05 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone02 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone02Setpoint = (gcnew System::Windows::Forms::Label());
			this->labelSetpointUnits02 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempUnits02 = (gcnew System::Windows::Forms::Label());
			this->labelZone02RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone02Switch = (gcnew System::Windows::Forms::Button());
			this->labelSetpointPrompt02 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempPrompt02 = (gcnew System::Windows::Forms::Label());
			this->groupBoxZone01 = (gcnew System::Windows::Forms::GroupBox());
			this->labelZone01Setpoint = (gcnew System::Windows::Forms::Label());
			this->labelSetpointUnits01 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempUnits01 = (gcnew System::Windows::Forms::Label());
			this->labelZone01RealTemp = (gcnew System::Windows::Forms::Label());
			this->buttonZone01Switch = (gcnew System::Windows::Forms::Button());
			this->labelSetpointPrompt01 = (gcnew System::Windows::Forms::Label());
			this->labelRealTempPrompt01 = (gcnew System::Windows::Forms::Label());
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
			this->groupBox1->Controls->Add(this->buttonLock);
			this->groupBox1->Controls->Add(this->labelComNumPrompt);
			this->groupBox1->Controls->Add(this->button28);
			this->groupBox1->Controls->Add(this->button27);
			this->groupBox1->Controls->Add(this->buttonConnect);
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Location = System::Drawing::Point(10, 6);
			this->groupBox1->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBox1->Size = System::Drawing::Size(1005, 113);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// buttonLock
			// 
			this->buttonLock->Location = System::Drawing::Point(402, 37);
			this->buttonLock->Name = L"buttonLock";
			this->buttonLock->Size = System::Drawing::Size(112, 41);
			this->buttonLock->TabIndex = 14;
			this->buttonLock->Text = L"锁定";
			this->buttonLock->UseVisualStyleBackColor = true;
			this->buttonLock->Click += gcnew System::EventHandler(this, &Form1::buttonLock_Click);
			// 
			// labelComNumPrompt
			// 
			this->labelComNumPrompt->AutoSize = true;
			this->labelComNumPrompt->Location = System::Drawing::Point(4, 46);
			this->labelComNumPrompt->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelComNumPrompt->Name = L"labelComNumPrompt";
			this->labelComNumPrompt->Size = System::Drawing::Size(131, 22);
			this->labelComNumPrompt->TabIndex = 13;
			this->labelComNumPrompt->Text = L"机台端口号:";
			// 
			// button28
			// 
			this->button28->Location = System::Drawing::Point(857, 37);
			this->button28->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->button28->Name = L"button28";
			this->button28->Size = System::Drawing::Size(131, 41);
			this->button28->TabIndex = 10;
			this->button28->Text = L"温度设置";
			this->button28->UseVisualStyleBackColor = true;
			this->button28->Click += gcnew System::EventHandler(this, &Form1::button28_Click);
			// 
			// button27
			// 
			this->button27->Location = System::Drawing::Point(696, 37);
			this->button27->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->button27->Name = L"button27";
			this->button27->Size = System::Drawing::Size(131, 41);
			this->button27->TabIndex = 9;
			this->button27->Text = L"温度读取";
			this->button27->UseVisualStyleBackColor = true;
			this->button27->Click += gcnew System::EventHandler(this, &Form1::button27_Click);
			// 
			// buttonConnect
			// 
			this->buttonConnect->Location = System::Drawing::Point(257, 37);
			this->buttonConnect->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonConnect->Name = L"buttonConnect";
			this->buttonConnect->Size = System::Drawing::Size(112, 41);
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
			this->comboBox1->Location = System::Drawing::Point(133, 42);
			this->comboBox1->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(82, 29);
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
			this->groupBoxZones->Location = System::Drawing::Point(10, 122);
			this->groupBoxZones->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZones->Name = L"groupBoxZones";
			this->groupBoxZones->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZones->Size = System::Drawing::Size(1003, 587);
			this->groupBoxZones->TabIndex = 1;
			this->groupBoxZones->TabStop = false;
			// 
			// groupBoxZone12
			// 
			this->groupBoxZone12->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone12->Controls->Add(this->labelZone12Setpoint);
			this->groupBoxZone12->Controls->Add(this->labelSetpointUnits12);
			this->groupBoxZone12->Controls->Add(this->labelRealTempUnits12);
			this->groupBoxZone12->Controls->Add(this->labelZone12RealTemp);
			this->groupBoxZone12->Controls->Add(this->buttonZone12Switch);
			this->groupBoxZone12->Controls->Add(this->labelSetpointPrompt12);
			this->groupBoxZone12->Controls->Add(this->labelRealTempPrompt12);
			this->groupBoxZone12->Location = System::Drawing::Point(749, 398);
			this->groupBoxZone12->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone12->Name = L"groupBoxZone12";
			this->groupBoxZone12->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone12->Size = System::Drawing::Size(241, 176);
			this->groupBoxZone12->TabIndex = 0;
			this->groupBoxZone12->TabStop = false;
			this->groupBoxZone12->Text = L"Zone12";
			this->groupBoxZone12->Click += gcnew System::EventHandler(this, &Form1::groupBoxZone12_Click);
			// 
			// labelZone12Setpoint
			// 
			this->labelZone12Setpoint->AutoSize = true;
			this->labelZone12Setpoint->Location = System::Drawing::Point(131, 82);
			this->labelZone12Setpoint->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone12Setpoint->Name = L"labelZone12Setpoint";
			this->labelZone12Setpoint->Size = System::Drawing::Size(21, 22);
			this->labelZone12Setpoint->TabIndex = 7;
			this->labelZone12Setpoint->Text = L"0";
			this->labelZone12Setpoint->Click += gcnew System::EventHandler(this, &Form1::labelZone12Setpoint_Click);
			// 
			// labelSetpointUnits12
			// 
			this->labelSetpointUnits12->AutoSize = true;
			this->labelSetpointUnits12->Location = System::Drawing::Point(190, 82);
			this->labelSetpointUnits12->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointUnits12->Name = L"labelSetpointUnits12";
			this->labelSetpointUnits12->Size = System::Drawing::Size(32, 22);
			this->labelSetpointUnits12->TabIndex = 6;
			this->labelSetpointUnits12->Text = L"℃";
			this->labelSetpointUnits12->Click += gcnew System::EventHandler(this, &Form1::labelSetpointUnits12_Click);
			// 
			// labelRealTempUnits12
			// 
			this->labelRealTempUnits12->AutoSize = true;
			this->labelRealTempUnits12->Location = System::Drawing::Point(190, 42);
			this->labelRealTempUnits12->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempUnits12->Name = L"labelRealTempUnits12";
			this->labelRealTempUnits12->Size = System::Drawing::Size(32, 22);
			this->labelRealTempUnits12->TabIndex = 6;
			this->labelRealTempUnits12->Text = L"℃";
			this->labelRealTempUnits12->Click += gcnew System::EventHandler(this, &Form1::labelRealTempUnits12_Click);
			// 
			// labelZone12RealTemp
			// 
			this->labelZone12RealTemp->AutoSize = true;
			this->labelZone12RealTemp->Location = System::Drawing::Point(131, 41);
			this->labelZone12RealTemp->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelZone12RealTemp->Name = L"labelZone12RealTemp";
			this->labelZone12RealTemp->Size = System::Drawing::Size(21, 22);
			this->labelZone12RealTemp->TabIndex = 5;
			this->labelZone12RealTemp->Text = L"0";
			this->labelZone12RealTemp->Click += gcnew System::EventHandler(this, &Form1::labelZone12RealTemp_Click);
			// 
			// buttonZone12Switch
			// 
			this->buttonZone12Switch->Location = System::Drawing::Point(28, 123);
			this->buttonZone12Switch->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonZone12Switch->Name = L"buttonZone12Switch";
			this->buttonZone12Switch->Size = System::Drawing::Size(185, 41);
			this->buttonZone12Switch->TabIndex = 3;
			this->buttonZone12Switch->Text = L"打开";
			this->buttonZone12Switch->UseVisualStyleBackColor = true;
			this->buttonZone12Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone12TempSet_Click);
			// 
			// labelSetpointPrompt12
			// 
			this->labelSetpointPrompt12->AutoSize = true;
			this->labelSetpointPrompt12->Location = System::Drawing::Point(23, 82);
			this->labelSetpointPrompt12->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointPrompt12->Name = L"labelSetpointPrompt12";
			this->labelSetpointPrompt12->Size = System::Drawing::Size(120, 22);
			this->labelSetpointPrompt12->TabIndex = 1;
			this->labelSetpointPrompt12->Text = L"设定温度: ";
			this->labelSetpointPrompt12->Click += gcnew System::EventHandler(this, &Form1::labelSetpointPrompt12_Click);
			// 
			// labelRealTempPrompt12
			// 
			this->labelRealTempPrompt12->AutoSize = true;
			this->labelRealTempPrompt12->Location = System::Drawing::Point(23, 41);
			this->labelRealTempPrompt12->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempPrompt12->Name = L"labelRealTempPrompt12";
			this->labelRealTempPrompt12->Size = System::Drawing::Size(120, 22);
			this->labelRealTempPrompt12->TabIndex = 0;
			this->labelRealTempPrompt12->Text = L"实时温度: ";
			this->labelRealTempPrompt12->Click += gcnew System::EventHandler(this, &Form1::labelRealTempPrompt12_Click);
			// 
			// groupBoxZone08
			// 
			this->groupBoxZone08->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone08->Controls->Add(this->labelZone08Setpoint);
			this->groupBoxZone08->Controls->Add(this->labelSetpointUnits08);
			this->groupBoxZone08->Controls->Add(this->labelRealTempUnits08);
			this->groupBoxZone08->Controls->Add(this->labelZone08RealTemp);
			this->groupBoxZone08->Controls->Add(this->buttonZone08Switch);
			this->groupBoxZone08->Controls->Add(this->labelSetpointPrompt08);
			this->groupBoxZone08->Controls->Add(this->labelRealTempPrompt08);
			this->groupBoxZone08->Location = System::Drawing::Point(749, 210);
			this->groupBoxZone08->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone08->Name = L"groupBoxZone08";
			this->groupBoxZone08->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone08->Size = System::Drawing::Size(241, 176);
			this->groupBoxZone08->TabIndex = 0;
			this->groupBoxZone08->TabStop = false;
			this->groupBoxZone08->Text = L"Zone08";
			this->groupBoxZone08->Click += gcnew System::EventHandler(this, &Form1::groupBoxZone08_Click);
			// 
			// labelZone08Setpoint
			// 
			this->labelZone08Setpoint->AutoSize = true;
			this->labelZone08Setpoint->Location = System::Drawing::Point(131, 82);
			this->labelZone08Setpoint->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone08Setpoint->Name = L"labelZone08Setpoint";
			this->labelZone08Setpoint->Size = System::Drawing::Size(21, 22);
			this->labelZone08Setpoint->TabIndex = 7;
			this->labelZone08Setpoint->Text = L"0";
			this->labelZone08Setpoint->Click += gcnew System::EventHandler(this, &Form1::labelZone08Setpoint_Click);
			// 
			// labelSetpointUnits08
			// 
			this->labelSetpointUnits08->AutoSize = true;
			this->labelSetpointUnits08->Location = System::Drawing::Point(190, 82);
			this->labelSetpointUnits08->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointUnits08->Name = L"labelSetpointUnits08";
			this->labelSetpointUnits08->Size = System::Drawing::Size(32, 22);
			this->labelSetpointUnits08->TabIndex = 6;
			this->labelSetpointUnits08->Text = L"℃";
			this->labelSetpointUnits08->Click += gcnew System::EventHandler(this, &Form1::labelSetpointUnits08_Click);
			// 
			// labelRealTempUnits08
			// 
			this->labelRealTempUnits08->AutoSize = true;
			this->labelRealTempUnits08->Location = System::Drawing::Point(190, 42);
			this->labelRealTempUnits08->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempUnits08->Name = L"labelRealTempUnits08";
			this->labelRealTempUnits08->Size = System::Drawing::Size(32, 22);
			this->labelRealTempUnits08->TabIndex = 6;
			this->labelRealTempUnits08->Text = L"℃";
			this->labelRealTempUnits08->Click += gcnew System::EventHandler(this, &Form1::labelRealTempUnits08_Click);
			// 
			// labelZone08RealTemp
			// 
			this->labelZone08RealTemp->AutoSize = true;
			this->labelZone08RealTemp->Location = System::Drawing::Point(131, 41);
			this->labelZone08RealTemp->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelZone08RealTemp->Name = L"labelZone08RealTemp";
			this->labelZone08RealTemp->Size = System::Drawing::Size(21, 22);
			this->labelZone08RealTemp->TabIndex = 5;
			this->labelZone08RealTemp->Text = L"0";
			this->labelZone08RealTemp->Click += gcnew System::EventHandler(this, &Form1::labelZone08RealTemp_Click);
			// 
			// buttonZone08Switch
			// 
			this->buttonZone08Switch->Location = System::Drawing::Point(28, 123);
			this->buttonZone08Switch->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonZone08Switch->Name = L"buttonZone08Switch";
			this->buttonZone08Switch->Size = System::Drawing::Size(185, 41);
			this->buttonZone08Switch->TabIndex = 3;
			this->buttonZone08Switch->Text = L"打开";
			this->buttonZone08Switch->UseVisualStyleBackColor = true;
			this->buttonZone08Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone08TempSet_Click);
			// 
			// labelSetpointPrompt08
			// 
			this->labelSetpointPrompt08->AutoSize = true;
			this->labelSetpointPrompt08->Location = System::Drawing::Point(23, 82);
			this->labelSetpointPrompt08->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointPrompt08->Name = L"labelSetpointPrompt08";
			this->labelSetpointPrompt08->Size = System::Drawing::Size(120, 22);
			this->labelSetpointPrompt08->TabIndex = 1;
			this->labelSetpointPrompt08->Text = L"设定温度: ";
			this->labelSetpointPrompt08->Click += gcnew System::EventHandler(this, &Form1::labelSetpointPrompt08_Click);
			// 
			// labelRealTempPrompt08
			// 
			this->labelRealTempPrompt08->AutoSize = true;
			this->labelRealTempPrompt08->Location = System::Drawing::Point(23, 41);
			this->labelRealTempPrompt08->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempPrompt08->Name = L"labelRealTempPrompt08";
			this->labelRealTempPrompt08->Size = System::Drawing::Size(120, 22);
			this->labelRealTempPrompt08->TabIndex = 0;
			this->labelRealTempPrompt08->Text = L"实时温度: ";
			this->labelRealTempPrompt08->Click += gcnew System::EventHandler(this, &Form1::labelRealTempPrompt08_Click);
			// 
			// groupBoxZone04
			// 
			this->groupBoxZone04->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone04->Controls->Add(this->labelZone04Setpoint);
			this->groupBoxZone04->Controls->Add(this->labelSetpointUnits04);
			this->groupBoxZone04->Controls->Add(this->labelRealTempUnits04);
			this->groupBoxZone04->Controls->Add(this->labelZone04RealTemp);
			this->groupBoxZone04->Controls->Add(this->buttonZone04Switch);
			this->groupBoxZone04->Controls->Add(this->labelSetpointPrompt04);
			this->groupBoxZone04->Controls->Add(this->labelRealTempPrompt04);
			this->groupBoxZone04->Location = System::Drawing::Point(749, 22);
			this->groupBoxZone04->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone04->Name = L"groupBoxZone04";
			this->groupBoxZone04->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone04->Size = System::Drawing::Size(241, 176);
			this->groupBoxZone04->TabIndex = 0;
			this->groupBoxZone04->TabStop = false;
			this->groupBoxZone04->Text = L"Zone04";
			this->groupBoxZone04->Click += gcnew System::EventHandler(this, &Form1::groupBoxZone04_Click);
			// 
			// labelZone04Setpoint
			// 
			this->labelZone04Setpoint->AutoSize = true;
			this->labelZone04Setpoint->Location = System::Drawing::Point(131, 82);
			this->labelZone04Setpoint->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone04Setpoint->Name = L"labelZone04Setpoint";
			this->labelZone04Setpoint->Size = System::Drawing::Size(21, 22);
			this->labelZone04Setpoint->TabIndex = 7;
			this->labelZone04Setpoint->Text = L"0";
			this->labelZone04Setpoint->Click += gcnew System::EventHandler(this, &Form1::labelZone04Setpoint_Click);
			// 
			// labelSetpointUnits04
			// 
			this->labelSetpointUnits04->AutoSize = true;
			this->labelSetpointUnits04->Location = System::Drawing::Point(190, 82);
			this->labelSetpointUnits04->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointUnits04->Name = L"labelSetpointUnits04";
			this->labelSetpointUnits04->Size = System::Drawing::Size(32, 22);
			this->labelSetpointUnits04->TabIndex = 6;
			this->labelSetpointUnits04->Text = L"℃";
			this->labelSetpointUnits04->Click += gcnew System::EventHandler(this, &Form1::labelSetpointUnits04_Click);
			// 
			// labelRealTempUnits04
			// 
			this->labelRealTempUnits04->AutoSize = true;
			this->labelRealTempUnits04->Location = System::Drawing::Point(190, 42);
			this->labelRealTempUnits04->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempUnits04->Name = L"labelRealTempUnits04";
			this->labelRealTempUnits04->Size = System::Drawing::Size(32, 22);
			this->labelRealTempUnits04->TabIndex = 6;
			this->labelRealTempUnits04->Text = L"℃";
			this->labelRealTempUnits04->Click += gcnew System::EventHandler(this, &Form1::labelRealTempUnits04_Click);
			// 
			// labelZone04RealTemp
			// 
			this->labelZone04RealTemp->AutoSize = true;
			this->labelZone04RealTemp->Location = System::Drawing::Point(131, 41);
			this->labelZone04RealTemp->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelZone04RealTemp->Name = L"labelZone04RealTemp";
			this->labelZone04RealTemp->Size = System::Drawing::Size(21, 22);
			this->labelZone04RealTemp->TabIndex = 5;
			this->labelZone04RealTemp->Text = L"0";
			this->labelZone04RealTemp->Click += gcnew System::EventHandler(this, &Form1::labelZone04RealTemp_Click);
			// 
			// buttonZone04Switch
			// 
			this->buttonZone04Switch->Location = System::Drawing::Point(28, 122);
			this->buttonZone04Switch->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonZone04Switch->Name = L"buttonZone04Switch";
			this->buttonZone04Switch->Size = System::Drawing::Size(185, 41);
			this->buttonZone04Switch->TabIndex = 3;
			this->buttonZone04Switch->Text = L"打开";
			this->buttonZone04Switch->UseVisualStyleBackColor = true;
			this->buttonZone04Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone04TempSet_Click);
			// 
			// labelSetpointPrompt04
			// 
			this->labelSetpointPrompt04->AutoSize = true;
			this->labelSetpointPrompt04->Location = System::Drawing::Point(23, 82);
			this->labelSetpointPrompt04->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointPrompt04->Name = L"labelSetpointPrompt04";
			this->labelSetpointPrompt04->Size = System::Drawing::Size(120, 22);
			this->labelSetpointPrompt04->TabIndex = 1;
			this->labelSetpointPrompt04->Text = L"设定温度: ";
			this->labelSetpointPrompt04->Click += gcnew System::EventHandler(this, &Form1::labelSetpointPrompt04_Click);
			// 
			// labelRealTempPrompt04
			// 
			this->labelRealTempPrompt04->AutoSize = true;
			this->labelRealTempPrompt04->Location = System::Drawing::Point(23, 41);
			this->labelRealTempPrompt04->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempPrompt04->Name = L"labelRealTempPrompt04";
			this->labelRealTempPrompt04->Size = System::Drawing::Size(120, 22);
			this->labelRealTempPrompt04->TabIndex = 0;
			this->labelRealTempPrompt04->Text = L"实时温度: ";
			this->labelRealTempPrompt04->Click += gcnew System::EventHandler(this, &Form1::labelRealTempPrompt04_Click);
			// 
			// groupBoxZone11
			// 
			this->groupBoxZone11->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone11->Controls->Add(this->labelZone11Setpoint);
			this->groupBoxZone11->Controls->Add(this->labelSetpointUnits11);
			this->groupBoxZone11->Controls->Add(this->labelRealTempUnits11);
			this->groupBoxZone11->Controls->Add(this->labelZone11RealTemp);
			this->groupBoxZone11->Controls->Add(this->buttonZone11Switch);
			this->groupBoxZone11->Controls->Add(this->labelSetpointPrompt11);
			this->groupBoxZone11->Controls->Add(this->labelRealTempPrompt11);
			this->groupBoxZone11->Location = System::Drawing::Point(504, 398);
			this->groupBoxZone11->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone11->Name = L"groupBoxZone11";
			this->groupBoxZone11->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone11->Size = System::Drawing::Size(241, 176);
			this->groupBoxZone11->TabIndex = 0;
			this->groupBoxZone11->TabStop = false;
			this->groupBoxZone11->Text = L"Zone11";
			this->groupBoxZone11->Click += gcnew System::EventHandler(this, &Form1::groupBoxZone11_Click);
			// 
			// labelZone11Setpoint
			// 
			this->labelZone11Setpoint->AutoSize = true;
			this->labelZone11Setpoint->Location = System::Drawing::Point(128, 83);
			this->labelZone11Setpoint->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone11Setpoint->Name = L"labelZone11Setpoint";
			this->labelZone11Setpoint->Size = System::Drawing::Size(21, 22);
			this->labelZone11Setpoint->TabIndex = 7;
			this->labelZone11Setpoint->Text = L"0";
			this->labelZone11Setpoint->Click += gcnew System::EventHandler(this, &Form1::labelZone11Setpoint_Click);
			// 
			// labelSetpointUnits11
			// 
			this->labelSetpointUnits11->AutoSize = true;
			this->labelSetpointUnits11->Location = System::Drawing::Point(190, 83);
			this->labelSetpointUnits11->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointUnits11->Name = L"labelSetpointUnits11";
			this->labelSetpointUnits11->Size = System::Drawing::Size(32, 22);
			this->labelSetpointUnits11->TabIndex = 6;
			this->labelSetpointUnits11->Text = L"℃";
			this->labelSetpointUnits11->Click += gcnew System::EventHandler(this, &Form1::labelSetpointUnits11_Click);
			// 
			// labelRealTempUnits11
			// 
			this->labelRealTempUnits11->AutoSize = true;
			this->labelRealTempUnits11->Location = System::Drawing::Point(190, 43);
			this->labelRealTempUnits11->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempUnits11->Name = L"labelRealTempUnits11";
			this->labelRealTempUnits11->Size = System::Drawing::Size(32, 22);
			this->labelRealTempUnits11->TabIndex = 6;
			this->labelRealTempUnits11->Text = L"℃";
			this->labelRealTempUnits11->Click += gcnew System::EventHandler(this, &Form1::labelRealTempUnits11_Click);
			// 
			// labelZone11RealTemp
			// 
			this->labelZone11RealTemp->AutoSize = true;
			this->labelZone11RealTemp->Location = System::Drawing::Point(128, 42);
			this->labelZone11RealTemp->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelZone11RealTemp->Name = L"labelZone11RealTemp";
			this->labelZone11RealTemp->Size = System::Drawing::Size(21, 22);
			this->labelZone11RealTemp->TabIndex = 5;
			this->labelZone11RealTemp->Text = L"0";
			this->labelZone11RealTemp->Click += gcnew System::EventHandler(this, &Form1::labelZone11RealTemp_Click);
			// 
			// buttonZone11Switch
			// 
			this->buttonZone11Switch->Location = System::Drawing::Point(28, 123);
			this->buttonZone11Switch->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonZone11Switch->Name = L"buttonZone11Switch";
			this->buttonZone11Switch->Size = System::Drawing::Size(185, 41);
			this->buttonZone11Switch->TabIndex = 3;
			this->buttonZone11Switch->Text = L"打开";
			this->buttonZone11Switch->UseVisualStyleBackColor = true;
			this->buttonZone11Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone11TempSet_Click);
			// 
			// labelSetpointPrompt11
			// 
			this->labelSetpointPrompt11->AutoSize = true;
			this->labelSetpointPrompt11->Location = System::Drawing::Point(23, 82);
			this->labelSetpointPrompt11->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointPrompt11->Name = L"labelSetpointPrompt11";
			this->labelSetpointPrompt11->Size = System::Drawing::Size(120, 22);
			this->labelSetpointPrompt11->TabIndex = 1;
			this->labelSetpointPrompt11->Text = L"设定温度: ";
			this->labelSetpointPrompt11->Click += gcnew System::EventHandler(this, &Form1::labelSetpointPrompt11_Click);
			// 
			// labelRealTempPrompt11
			// 
			this->labelRealTempPrompt11->AutoSize = true;
			this->labelRealTempPrompt11->Location = System::Drawing::Point(23, 41);
			this->labelRealTempPrompt11->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempPrompt11->Name = L"labelRealTempPrompt11";
			this->labelRealTempPrompt11->Size = System::Drawing::Size(120, 22);
			this->labelRealTempPrompt11->TabIndex = 0;
			this->labelRealTempPrompt11->Text = L"实时温度: ";
			this->labelRealTempPrompt11->Click += gcnew System::EventHandler(this, &Form1::labelRealTempPrompt11_Click);
			// 
			// groupBoxZone07
			// 
			this->groupBoxZone07->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone07->Controls->Add(this->labelZone07Setpoint);
			this->groupBoxZone07->Controls->Add(this->labelSetpointUnits07);
			this->groupBoxZone07->Controls->Add(this->labelRealTempUnits07);
			this->groupBoxZone07->Controls->Add(this->labelZone07RealTemp);
			this->groupBoxZone07->Controls->Add(this->buttonZone07Switch);
			this->groupBoxZone07->Controls->Add(this->labelSetpointPrompt07);
			this->groupBoxZone07->Controls->Add(this->labelRealTempPrompt07);
			this->groupBoxZone07->Location = System::Drawing::Point(504, 210);
			this->groupBoxZone07->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone07->Name = L"groupBoxZone07";
			this->groupBoxZone07->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone07->Size = System::Drawing::Size(241, 176);
			this->groupBoxZone07->TabIndex = 0;
			this->groupBoxZone07->TabStop = false;
			this->groupBoxZone07->Text = L"Zone07";
			this->groupBoxZone07->Click += gcnew System::EventHandler(this, &Form1::groupBoxZone07_Click);
			// 
			// labelZone07Setpoint
			// 
			this->labelZone07Setpoint->AutoSize = true;
			this->labelZone07Setpoint->Location = System::Drawing::Point(128, 82);
			this->labelZone07Setpoint->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone07Setpoint->Name = L"labelZone07Setpoint";
			this->labelZone07Setpoint->Size = System::Drawing::Size(21, 22);
			this->labelZone07Setpoint->TabIndex = 7;
			this->labelZone07Setpoint->Text = L"0";
			this->labelZone07Setpoint->Click += gcnew System::EventHandler(this, &Form1::labelZone07Setpoint_Click);
			// 
			// labelSetpointUnits07
			// 
			this->labelSetpointUnits07->AutoSize = true;
			this->labelSetpointUnits07->Location = System::Drawing::Point(188, 82);
			this->labelSetpointUnits07->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointUnits07->Name = L"labelSetpointUnits07";
			this->labelSetpointUnits07->Size = System::Drawing::Size(32, 22);
			this->labelSetpointUnits07->TabIndex = 6;
			this->labelSetpointUnits07->Text = L"℃";
			this->labelSetpointUnits07->Click += gcnew System::EventHandler(this, &Form1::labelSetpointUnits07_Click);
			// 
			// labelRealTempUnits07
			// 
			this->labelRealTempUnits07->AutoSize = true;
			this->labelRealTempUnits07->Location = System::Drawing::Point(188, 42);
			this->labelRealTempUnits07->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempUnits07->Name = L"labelRealTempUnits07";
			this->labelRealTempUnits07->Size = System::Drawing::Size(32, 22);
			this->labelRealTempUnits07->TabIndex = 6;
			this->labelRealTempUnits07->Text = L"℃";
			this->labelRealTempUnits07->Click += gcnew System::EventHandler(this, &Form1::labelRealTempUnits07_Click);
			// 
			// labelZone07RealTemp
			// 
			this->labelZone07RealTemp->AutoSize = true;
			this->labelZone07RealTemp->Location = System::Drawing::Point(128, 41);
			this->labelZone07RealTemp->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelZone07RealTemp->Name = L"labelZone07RealTemp";
			this->labelZone07RealTemp->Size = System::Drawing::Size(21, 22);
			this->labelZone07RealTemp->TabIndex = 5;
			this->labelZone07RealTemp->Text = L"0";
			this->labelZone07RealTemp->Click += gcnew System::EventHandler(this, &Form1::labelZone07RealTemp_Click);
			// 
			// buttonZone07Switch
			// 
			this->buttonZone07Switch->Location = System::Drawing::Point(28, 123);
			this->buttonZone07Switch->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonZone07Switch->Name = L"buttonZone07Switch";
			this->buttonZone07Switch->Size = System::Drawing::Size(185, 41);
			this->buttonZone07Switch->TabIndex = 3;
			this->buttonZone07Switch->Text = L"打开";
			this->buttonZone07Switch->UseVisualStyleBackColor = true;
			this->buttonZone07Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone07TempSet_Click);
			// 
			// labelSetpointPrompt07
			// 
			this->labelSetpointPrompt07->AutoSize = true;
			this->labelSetpointPrompt07->Location = System::Drawing::Point(23, 82);
			this->labelSetpointPrompt07->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointPrompt07->Name = L"labelSetpointPrompt07";
			this->labelSetpointPrompt07->Size = System::Drawing::Size(120, 22);
			this->labelSetpointPrompt07->TabIndex = 1;
			this->labelSetpointPrompt07->Text = L"设定温度: ";
			this->labelSetpointPrompt07->Click += gcnew System::EventHandler(this, &Form1::labelSetpointPrompt07_Click);
			// 
			// labelRealTempPrompt07
			// 
			this->labelRealTempPrompt07->AutoSize = true;
			this->labelRealTempPrompt07->Location = System::Drawing::Point(23, 41);
			this->labelRealTempPrompt07->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempPrompt07->Name = L"labelRealTempPrompt07";
			this->labelRealTempPrompt07->Size = System::Drawing::Size(120, 22);
			this->labelRealTempPrompt07->TabIndex = 0;
			this->labelRealTempPrompt07->Text = L"实时温度: ";
			this->labelRealTempPrompt07->Click += gcnew System::EventHandler(this, &Form1::labelRealTempPrompt07_Click);
			// 
			// groupBoxZone03
			// 
			this->groupBoxZone03->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone03->Controls->Add(this->labelZone03Setpoint);
			this->groupBoxZone03->Controls->Add(this->labelSetpointUnits03);
			this->groupBoxZone03->Controls->Add(this->labelRealTempUnits03);
			this->groupBoxZone03->Controls->Add(this->labelZone03RealTemp);
			this->groupBoxZone03->Controls->Add(this->buttonZone03Switch);
			this->groupBoxZone03->Controls->Add(this->labelSetpointPrompt03);
			this->groupBoxZone03->Controls->Add(this->labelRealTempPrompt03);
			this->groupBoxZone03->Location = System::Drawing::Point(504, 22);
			this->groupBoxZone03->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone03->Name = L"groupBoxZone03";
			this->groupBoxZone03->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone03->Size = System::Drawing::Size(241, 176);
			this->groupBoxZone03->TabIndex = 0;
			this->groupBoxZone03->TabStop = false;
			this->groupBoxZone03->Text = L"Zone03";
			this->groupBoxZone03->Click += gcnew System::EventHandler(this, &Form1::groupBoxZone03_Click);
			// 
			// labelZone03Setpoint
			// 
			this->labelZone03Setpoint->AutoSize = true;
			this->labelZone03Setpoint->Location = System::Drawing::Point(128, 82);
			this->labelZone03Setpoint->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone03Setpoint->Name = L"labelZone03Setpoint";
			this->labelZone03Setpoint->Size = System::Drawing::Size(21, 22);
			this->labelZone03Setpoint->TabIndex = 7;
			this->labelZone03Setpoint->Text = L"0";
			this->labelZone03Setpoint->Click += gcnew System::EventHandler(this, &Form1::labelZone03Setpoint_Click);
			// 
			// labelSetpointUnits03
			// 
			this->labelSetpointUnits03->AutoSize = true;
			this->labelSetpointUnits03->Location = System::Drawing::Point(188, 82);
			this->labelSetpointUnits03->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointUnits03->Name = L"labelSetpointUnits03";
			this->labelSetpointUnits03->Size = System::Drawing::Size(32, 22);
			this->labelSetpointUnits03->TabIndex = 6;
			this->labelSetpointUnits03->Text = L"℃";
			this->labelSetpointUnits03->Click += gcnew System::EventHandler(this, &Form1::labelSetpointUnits03_Click);
			// 
			// labelRealTempUnits03
			// 
			this->labelRealTempUnits03->AutoSize = true;
			this->labelRealTempUnits03->Location = System::Drawing::Point(188, 42);
			this->labelRealTempUnits03->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempUnits03->Name = L"labelRealTempUnits03";
			this->labelRealTempUnits03->Size = System::Drawing::Size(32, 22);
			this->labelRealTempUnits03->TabIndex = 6;
			this->labelRealTempUnits03->Text = L"℃";
			this->labelRealTempUnits03->Click += gcnew System::EventHandler(this, &Form1::labelRealTempUnits03_Click);
			// 
			// labelZone03RealTemp
			// 
			this->labelZone03RealTemp->AutoSize = true;
			this->labelZone03RealTemp->Location = System::Drawing::Point(128, 41);
			this->labelZone03RealTemp->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelZone03RealTemp->Name = L"labelZone03RealTemp";
			this->labelZone03RealTemp->Size = System::Drawing::Size(21, 22);
			this->labelZone03RealTemp->TabIndex = 5;
			this->labelZone03RealTemp->Text = L"0";
			this->labelZone03RealTemp->Click += gcnew System::EventHandler(this, &Form1::labelZone03RealTemp_Click);
			// 
			// buttonZone03Switch
			// 
			this->buttonZone03Switch->Location = System::Drawing::Point(28, 122);
			this->buttonZone03Switch->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonZone03Switch->Name = L"buttonZone03Switch";
			this->buttonZone03Switch->Size = System::Drawing::Size(185, 41);
			this->buttonZone03Switch->TabIndex = 3;
			this->buttonZone03Switch->Text = L"打开";
			this->buttonZone03Switch->UseVisualStyleBackColor = true;
			this->buttonZone03Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone03TempSet_Click);
			// 
			// labelSetpointPrompt03
			// 
			this->labelSetpointPrompt03->AutoSize = true;
			this->labelSetpointPrompt03->Location = System::Drawing::Point(23, 82);
			this->labelSetpointPrompt03->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointPrompt03->Name = L"labelSetpointPrompt03";
			this->labelSetpointPrompt03->Size = System::Drawing::Size(120, 22);
			this->labelSetpointPrompt03->TabIndex = 1;
			this->labelSetpointPrompt03->Text = L"设定温度: ";
			this->labelSetpointPrompt03->Click += gcnew System::EventHandler(this, &Form1::labelSetpointPrompt03_Click);
			// 
			// labelRealTempPrompt03
			// 
			this->labelRealTempPrompt03->AutoSize = true;
			this->labelRealTempPrompt03->Location = System::Drawing::Point(23, 41);
			this->labelRealTempPrompt03->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempPrompt03->Name = L"labelRealTempPrompt03";
			this->labelRealTempPrompt03->Size = System::Drawing::Size(120, 22);
			this->labelRealTempPrompt03->TabIndex = 0;
			this->labelRealTempPrompt03->Text = L"实时温度: ";
			this->labelRealTempPrompt03->Click += gcnew System::EventHandler(this, &Form1::labelRealTempPrompt03_Click);
			// 
			// groupBoxZone10
			// 
			this->groupBoxZone10->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone10->Controls->Add(this->labelZone10Setpoint);
			this->groupBoxZone10->Controls->Add(this->labelSetpointUnits10);
			this->groupBoxZone10->Controls->Add(this->labelRealTempUnits10);
			this->groupBoxZone10->Controls->Add(this->labelZone10RealTemp);
			this->groupBoxZone10->Controls->Add(this->buttonZone10Switch);
			this->groupBoxZone10->Controls->Add(this->labelSetpointPrompt10);
			this->groupBoxZone10->Controls->Add(this->labelRealTempPrompt10);
			this->groupBoxZone10->Location = System::Drawing::Point(259, 398);
			this->groupBoxZone10->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone10->Name = L"groupBoxZone10";
			this->groupBoxZone10->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone10->Size = System::Drawing::Size(241, 176);
			this->groupBoxZone10->TabIndex = 0;
			this->groupBoxZone10->TabStop = false;
			this->groupBoxZone10->Text = L"Zone10";
			this->groupBoxZone10->Click += gcnew System::EventHandler(this, &Form1::groupBoxZone10_Click);
			// 
			// labelZone10Setpoint
			// 
			this->labelZone10Setpoint->AutoSize = true;
			this->labelZone10Setpoint->Location = System::Drawing::Point(128, 82);
			this->labelZone10Setpoint->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone10Setpoint->Name = L"labelZone10Setpoint";
			this->labelZone10Setpoint->Size = System::Drawing::Size(21, 22);
			this->labelZone10Setpoint->TabIndex = 7;
			this->labelZone10Setpoint->Text = L"0";
			this->labelZone10Setpoint->Click += gcnew System::EventHandler(this, &Form1::labelZone10Setpoint_Click);
			// 
			// labelSetpointUnits10
			// 
			this->labelSetpointUnits10->AutoSize = true;
			this->labelSetpointUnits10->Location = System::Drawing::Point(188, 82);
			this->labelSetpointUnits10->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointUnits10->Name = L"labelSetpointUnits10";
			this->labelSetpointUnits10->Size = System::Drawing::Size(32, 22);
			this->labelSetpointUnits10->TabIndex = 6;
			this->labelSetpointUnits10->Text = L"℃";
			this->labelSetpointUnits10->Click += gcnew System::EventHandler(this, &Form1::labelSetpointUnits10_Click);
			// 
			// labelRealTempUnits10
			// 
			this->labelRealTempUnits10->AutoSize = true;
			this->labelRealTempUnits10->Location = System::Drawing::Point(188, 42);
			this->labelRealTempUnits10->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempUnits10->Name = L"labelRealTempUnits10";
			this->labelRealTempUnits10->Size = System::Drawing::Size(32, 22);
			this->labelRealTempUnits10->TabIndex = 6;
			this->labelRealTempUnits10->Text = L"℃";
			this->labelRealTempUnits10->Click += gcnew System::EventHandler(this, &Form1::labelRealTempUnits10_Click);
			// 
			// labelZone10RealTemp
			// 
			this->labelZone10RealTemp->AutoSize = true;
			this->labelZone10RealTemp->Location = System::Drawing::Point(128, 41);
			this->labelZone10RealTemp->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelZone10RealTemp->Name = L"labelZone10RealTemp";
			this->labelZone10RealTemp->Size = System::Drawing::Size(21, 22);
			this->labelZone10RealTemp->TabIndex = 5;
			this->labelZone10RealTemp->Text = L"0";
			this->labelZone10RealTemp->Click += gcnew System::EventHandler(this, &Form1::labelZone10RealTemp_Click);
			// 
			// buttonZone10Switch
			// 
			this->buttonZone10Switch->Location = System::Drawing::Point(28, 124);
			this->buttonZone10Switch->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonZone10Switch->Name = L"buttonZone10Switch";
			this->buttonZone10Switch->Size = System::Drawing::Size(185, 41);
			this->buttonZone10Switch->TabIndex = 3;
			this->buttonZone10Switch->Text = L"打开";
			this->buttonZone10Switch->UseVisualStyleBackColor = true;
			this->buttonZone10Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone10TempSet_Click);
			// 
			// labelSetpointPrompt10
			// 
			this->labelSetpointPrompt10->AutoSize = true;
			this->labelSetpointPrompt10->Location = System::Drawing::Point(23, 82);
			this->labelSetpointPrompt10->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointPrompt10->Name = L"labelSetpointPrompt10";
			this->labelSetpointPrompt10->Size = System::Drawing::Size(120, 22);
			this->labelSetpointPrompt10->TabIndex = 1;
			this->labelSetpointPrompt10->Text = L"设定温度: ";
			this->labelSetpointPrompt10->Click += gcnew System::EventHandler(this, &Form1::labelSetpointPrompt10_Click);
			// 
			// labelRealTempPrompt10
			// 
			this->labelRealTempPrompt10->AutoSize = true;
			this->labelRealTempPrompt10->Location = System::Drawing::Point(23, 41);
			this->labelRealTempPrompt10->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempPrompt10->Name = L"labelRealTempPrompt10";
			this->labelRealTempPrompt10->Size = System::Drawing::Size(120, 22);
			this->labelRealTempPrompt10->TabIndex = 0;
			this->labelRealTempPrompt10->Text = L"实时温度: ";
			this->labelRealTempPrompt10->Click += gcnew System::EventHandler(this, &Form1::labelRealTempPrompt10_Click);
			// 
			// groupBoxZone09
			// 
			this->groupBoxZone09->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone09->Controls->Add(this->labelZone09Setpoint);
			this->groupBoxZone09->Controls->Add(this->labelSetpointUnits09);
			this->groupBoxZone09->Controls->Add(this->labelRealTempUnits09);
			this->groupBoxZone09->Controls->Add(this->labelZone09RealTemp);
			this->groupBoxZone09->Controls->Add(this->buttonZone09Switch);
			this->groupBoxZone09->Controls->Add(this->labelSetpointPrompt09);
			this->groupBoxZone09->Controls->Add(this->labelRealTempPrompt09);
			this->groupBoxZone09->Location = System::Drawing::Point(13, 398);
			this->groupBoxZone09->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone09->Name = L"groupBoxZone09";
			this->groupBoxZone09->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone09->Size = System::Drawing::Size(241, 176);
			this->groupBoxZone09->TabIndex = 0;
			this->groupBoxZone09->TabStop = false;
			this->groupBoxZone09->Text = L"Zone09";
			this->groupBoxZone09->Click += gcnew System::EventHandler(this, &Form1::groupBoxZone09_Click);
			// 
			// labelZone09Setpoint
			// 
			this->labelZone09Setpoint->AutoSize = true;
			this->labelZone09Setpoint->Location = System::Drawing::Point(130, 82);
			this->labelZone09Setpoint->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone09Setpoint->Name = L"labelZone09Setpoint";
			this->labelZone09Setpoint->Size = System::Drawing::Size(21, 22);
			this->labelZone09Setpoint->TabIndex = 7;
			this->labelZone09Setpoint->Text = L"0";
			this->labelZone09Setpoint->Click += gcnew System::EventHandler(this, &Form1::labelZone09Setpoint_Click);
			// 
			// labelSetpointUnits09
			// 
			this->labelSetpointUnits09->AutoSize = true;
			this->labelSetpointUnits09->Location = System::Drawing::Point(189, 82);
			this->labelSetpointUnits09->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointUnits09->Name = L"labelSetpointUnits09";
			this->labelSetpointUnits09->Size = System::Drawing::Size(32, 22);
			this->labelSetpointUnits09->TabIndex = 6;
			this->labelSetpointUnits09->Text = L"℃";
			this->labelSetpointUnits09->Click += gcnew System::EventHandler(this, &Form1::labelSetpointUnits09_Click);
			// 
			// labelRealTempUnits09
			// 
			this->labelRealTempUnits09->AutoSize = true;
			this->labelRealTempUnits09->Location = System::Drawing::Point(189, 42);
			this->labelRealTempUnits09->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempUnits09->Name = L"labelRealTempUnits09";
			this->labelRealTempUnits09->Size = System::Drawing::Size(32, 22);
			this->labelRealTempUnits09->TabIndex = 6;
			this->labelRealTempUnits09->Text = L"℃";
			this->labelRealTempUnits09->Click += gcnew System::EventHandler(this, &Form1::labelRealTempUnits09_Click);
			// 
			// labelZone09RealTemp
			// 
			this->labelZone09RealTemp->AutoSize = true;
			this->labelZone09RealTemp->Location = System::Drawing::Point(130, 41);
			this->labelZone09RealTemp->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelZone09RealTemp->Name = L"labelZone09RealTemp";
			this->labelZone09RealTemp->Size = System::Drawing::Size(21, 22);
			this->labelZone09RealTemp->TabIndex = 5;
			this->labelZone09RealTemp->Text = L"0";
			this->labelZone09RealTemp->Click += gcnew System::EventHandler(this, &Form1::labelZone09RealTemp_Click);
			// 
			// buttonZone09Switch
			// 
			this->buttonZone09Switch->Location = System::Drawing::Point(28, 123);
			this->buttonZone09Switch->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonZone09Switch->Name = L"buttonZone09Switch";
			this->buttonZone09Switch->Size = System::Drawing::Size(185, 41);
			this->buttonZone09Switch->TabIndex = 3;
			this->buttonZone09Switch->Text = L"打开";
			this->buttonZone09Switch->UseVisualStyleBackColor = true;
			this->buttonZone09Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone09TempSet_Click);
			// 
			// labelSetpointPrompt09
			// 
			this->labelSetpointPrompt09->AutoSize = true;
			this->labelSetpointPrompt09->Location = System::Drawing::Point(23, 82);
			this->labelSetpointPrompt09->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointPrompt09->Name = L"labelSetpointPrompt09";
			this->labelSetpointPrompt09->Size = System::Drawing::Size(120, 22);
			this->labelSetpointPrompt09->TabIndex = 1;
			this->labelSetpointPrompt09->Text = L"设定温度: ";
			this->labelSetpointPrompt09->Click += gcnew System::EventHandler(this, &Form1::labelSetpointPrompt09_Click);
			// 
			// labelRealTempPrompt09
			// 
			this->labelRealTempPrompt09->AutoSize = true;
			this->labelRealTempPrompt09->Location = System::Drawing::Point(23, 41);
			this->labelRealTempPrompt09->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempPrompt09->Name = L"labelRealTempPrompt09";
			this->labelRealTempPrompt09->Size = System::Drawing::Size(120, 22);
			this->labelRealTempPrompt09->TabIndex = 0;
			this->labelRealTempPrompt09->Text = L"实时温度: ";
			this->labelRealTempPrompt09->Click += gcnew System::EventHandler(this, &Form1::labelRealTempPrompt09_Click);
			// 
			// groupBoxZone06
			// 
			this->groupBoxZone06->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone06->Controls->Add(this->labelZone06Setpoint);
			this->groupBoxZone06->Controls->Add(this->labelSetpointUnits06);
			this->groupBoxZone06->Controls->Add(this->labelRealTempUnits06);
			this->groupBoxZone06->Controls->Add(this->labelZone06RealTemp);
			this->groupBoxZone06->Controls->Add(this->buttonZone06Switch);
			this->groupBoxZone06->Controls->Add(this->labelSetpointPrompt06);
			this->groupBoxZone06->Controls->Add(this->labelRealTempPrompt06);
			this->groupBoxZone06->Location = System::Drawing::Point(259, 210);
			this->groupBoxZone06->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone06->Name = L"groupBoxZone06";
			this->groupBoxZone06->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone06->Size = System::Drawing::Size(241, 176);
			this->groupBoxZone06->TabIndex = 0;
			this->groupBoxZone06->TabStop = false;
			this->groupBoxZone06->Text = L"Zone06";
			this->groupBoxZone06->Click += gcnew System::EventHandler(this, &Form1::groupBoxZone06_Click);
			// 
			// labelZone06Setpoint
			// 
			this->labelZone06Setpoint->AutoSize = true;
			this->labelZone06Setpoint->Location = System::Drawing::Point(128, 82);
			this->labelZone06Setpoint->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone06Setpoint->Name = L"labelZone06Setpoint";
			this->labelZone06Setpoint->Size = System::Drawing::Size(21, 22);
			this->labelZone06Setpoint->TabIndex = 7;
			this->labelZone06Setpoint->Text = L"0";
			this->labelZone06Setpoint->Click += gcnew System::EventHandler(this, &Form1::labelZone06Setpoint_Click);
			// 
			// labelSetpointUnits06
			// 
			this->labelSetpointUnits06->AutoSize = true;
			this->labelSetpointUnits06->Location = System::Drawing::Point(188, 82);
			this->labelSetpointUnits06->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointUnits06->Name = L"labelSetpointUnits06";
			this->labelSetpointUnits06->Size = System::Drawing::Size(32, 22);
			this->labelSetpointUnits06->TabIndex = 6;
			this->labelSetpointUnits06->Text = L"℃";
			this->labelSetpointUnits06->Click += gcnew System::EventHandler(this, &Form1::labelSetpointUnits06_Click);
			// 
			// labelRealTempUnits06
			// 
			this->labelRealTempUnits06->AutoSize = true;
			this->labelRealTempUnits06->Location = System::Drawing::Point(188, 42);
			this->labelRealTempUnits06->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempUnits06->Name = L"labelRealTempUnits06";
			this->labelRealTempUnits06->Size = System::Drawing::Size(32, 22);
			this->labelRealTempUnits06->TabIndex = 6;
			this->labelRealTempUnits06->Text = L"℃";
			this->labelRealTempUnits06->Click += gcnew System::EventHandler(this, &Form1::labelRealTempUnits06_Click);
			// 
			// labelZone06RealTemp
			// 
			this->labelZone06RealTemp->AutoSize = true;
			this->labelZone06RealTemp->Location = System::Drawing::Point(128, 41);
			this->labelZone06RealTemp->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelZone06RealTemp->Name = L"labelZone06RealTemp";
			this->labelZone06RealTemp->Size = System::Drawing::Size(21, 22);
			this->labelZone06RealTemp->TabIndex = 5;
			this->labelZone06RealTemp->Text = L"0";
			this->labelZone06RealTemp->Click += gcnew System::EventHandler(this, &Form1::labelZone06RealTemp_Click);
			// 
			// buttonZone06Switch
			// 
			this->buttonZone06Switch->Location = System::Drawing::Point(28, 123);
			this->buttonZone06Switch->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonZone06Switch->Name = L"buttonZone06Switch";
			this->buttonZone06Switch->Size = System::Drawing::Size(185, 41);
			this->buttonZone06Switch->TabIndex = 3;
			this->buttonZone06Switch->Text = L"打开";
			this->buttonZone06Switch->UseVisualStyleBackColor = true;
			this->buttonZone06Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone06TempSet_Click);
			// 
			// labelSetpointPrompt06
			// 
			this->labelSetpointPrompt06->AutoSize = true;
			this->labelSetpointPrompt06->Location = System::Drawing::Point(23, 82);
			this->labelSetpointPrompt06->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointPrompt06->Name = L"labelSetpointPrompt06";
			this->labelSetpointPrompt06->Size = System::Drawing::Size(120, 22);
			this->labelSetpointPrompt06->TabIndex = 1;
			this->labelSetpointPrompt06->Text = L"设定温度: ";
			this->labelSetpointPrompt06->Click += gcnew System::EventHandler(this, &Form1::labelSetpointPrompt06_Click);
			// 
			// labelRealTempPrompt06
			// 
			this->labelRealTempPrompt06->AutoSize = true;
			this->labelRealTempPrompt06->Location = System::Drawing::Point(23, 41);
			this->labelRealTempPrompt06->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempPrompt06->Name = L"labelRealTempPrompt06";
			this->labelRealTempPrompt06->Size = System::Drawing::Size(120, 22);
			this->labelRealTempPrompt06->TabIndex = 0;
			this->labelRealTempPrompt06->Text = L"实时温度: ";
			this->labelRealTempPrompt06->Click += gcnew System::EventHandler(this, &Form1::labelRealTempPrompt06_Click);
			// 
			// groupBoxZone05
			// 
			this->groupBoxZone05->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone05->Controls->Add(this->labelZone05Setpoint);
			this->groupBoxZone05->Controls->Add(this->labelSetpointUnits05);
			this->groupBoxZone05->Controls->Add(this->labelRealTempUnits05);
			this->groupBoxZone05->Controls->Add(this->labelZone05RealTemp);
			this->groupBoxZone05->Controls->Add(this->buttonZone05Switch);
			this->groupBoxZone05->Controls->Add(this->labelSetpointPrompt05);
			this->groupBoxZone05->Controls->Add(this->labelRealTempPrompt05);
			this->groupBoxZone05->Location = System::Drawing::Point(13, 210);
			this->groupBoxZone05->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone05->Name = L"groupBoxZone05";
			this->groupBoxZone05->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone05->Size = System::Drawing::Size(241, 176);
			this->groupBoxZone05->TabIndex = 0;
			this->groupBoxZone05->TabStop = false;
			this->groupBoxZone05->Text = L"Zone05";
			this->groupBoxZone05->Click += gcnew System::EventHandler(this, &Form1::groupBoxZone05_Click);
			// 
			// labelZone05Setpoint
			// 
			this->labelZone05Setpoint->AutoSize = true;
			this->labelZone05Setpoint->Location = System::Drawing::Point(130, 82);
			this->labelZone05Setpoint->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone05Setpoint->Name = L"labelZone05Setpoint";
			this->labelZone05Setpoint->Size = System::Drawing::Size(21, 22);
			this->labelZone05Setpoint->TabIndex = 7;
			this->labelZone05Setpoint->Text = L"0";
			this->labelZone05Setpoint->Click += gcnew System::EventHandler(this, &Form1::labelZone05Setpoint_Click);
			// 
			// labelSetpointUnits05
			// 
			this->labelSetpointUnits05->AutoSize = true;
			this->labelSetpointUnits05->Location = System::Drawing::Point(197, 82);
			this->labelSetpointUnits05->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointUnits05->Name = L"labelSetpointUnits05";
			this->labelSetpointUnits05->Size = System::Drawing::Size(32, 22);
			this->labelSetpointUnits05->TabIndex = 6;
			this->labelSetpointUnits05->Text = L"℃";
			this->labelSetpointUnits05->Click += gcnew System::EventHandler(this, &Form1::labelSetpointUnits05_Click);
			// 
			// labelRealTempUnits05
			// 
			this->labelRealTempUnits05->AutoSize = true;
			this->labelRealTempUnits05->Location = System::Drawing::Point(197, 42);
			this->labelRealTempUnits05->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempUnits05->Name = L"labelRealTempUnits05";
			this->labelRealTempUnits05->Size = System::Drawing::Size(32, 22);
			this->labelRealTempUnits05->TabIndex = 6;
			this->labelRealTempUnits05->Text = L"℃";
			this->labelRealTempUnits05->Click += gcnew System::EventHandler(this, &Form1::labelRealTempUnits05_Click);
			// 
			// labelZone05RealTemp
			// 
			this->labelZone05RealTemp->AutoSize = true;
			this->labelZone05RealTemp->Location = System::Drawing::Point(130, 41);
			this->labelZone05RealTemp->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelZone05RealTemp->Name = L"labelZone05RealTemp";
			this->labelZone05RealTemp->Size = System::Drawing::Size(21, 22);
			this->labelZone05RealTemp->TabIndex = 5;
			this->labelZone05RealTemp->Text = L"0";
			this->labelZone05RealTemp->Click += gcnew System::EventHandler(this, &Form1::labelZone05RealTemp_Click);
			// 
			// buttonZone05Switch
			// 
			this->buttonZone05Switch->Location = System::Drawing::Point(28, 123);
			this->buttonZone05Switch->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonZone05Switch->Name = L"buttonZone05Switch";
			this->buttonZone05Switch->Size = System::Drawing::Size(185, 41);
			this->buttonZone05Switch->TabIndex = 3;
			this->buttonZone05Switch->Text = L"打开";
			this->buttonZone05Switch->UseVisualStyleBackColor = true;
			this->buttonZone05Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone05TempSet_Click);
			// 
			// labelSetpointPrompt05
			// 
			this->labelSetpointPrompt05->AutoSize = true;
			this->labelSetpointPrompt05->Location = System::Drawing::Point(23, 82);
			this->labelSetpointPrompt05->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointPrompt05->Name = L"labelSetpointPrompt05";
			this->labelSetpointPrompt05->Size = System::Drawing::Size(120, 22);
			this->labelSetpointPrompt05->TabIndex = 1;
			this->labelSetpointPrompt05->Text = L"设定温度: ";
			this->labelSetpointPrompt05->Click += gcnew System::EventHandler(this, &Form1::labelSetpointPrompt05_Click);
			// 
			// labelRealTempPrompt05
			// 
			this->labelRealTempPrompt05->AutoSize = true;
			this->labelRealTempPrompt05->Location = System::Drawing::Point(23, 41);
			this->labelRealTempPrompt05->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempPrompt05->Name = L"labelRealTempPrompt05";
			this->labelRealTempPrompt05->Size = System::Drawing::Size(120, 22);
			this->labelRealTempPrompt05->TabIndex = 0;
			this->labelRealTempPrompt05->Text = L"实时温度: ";
			this->labelRealTempPrompt05->Click += gcnew System::EventHandler(this, &Form1::labelRealTempPrompt05_Click);
			// 
			// groupBoxZone02
			// 
			this->groupBoxZone02->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone02->Controls->Add(this->labelZone02Setpoint);
			this->groupBoxZone02->Controls->Add(this->labelSetpointUnits02);
			this->groupBoxZone02->Controls->Add(this->labelRealTempUnits02);
			this->groupBoxZone02->Controls->Add(this->labelZone02RealTemp);
			this->groupBoxZone02->Controls->Add(this->buttonZone02Switch);
			this->groupBoxZone02->Controls->Add(this->labelSetpointPrompt02);
			this->groupBoxZone02->Controls->Add(this->labelRealTempPrompt02);
			this->groupBoxZone02->Location = System::Drawing::Point(259, 22);
			this->groupBoxZone02->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone02->Name = L"groupBoxZone02";
			this->groupBoxZone02->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone02->Size = System::Drawing::Size(241, 176);
			this->groupBoxZone02->TabIndex = 0;
			this->groupBoxZone02->TabStop = false;
			this->groupBoxZone02->Text = L"Zone02";
			this->groupBoxZone02->Click += gcnew System::EventHandler(this, &Form1::groupBoxZone02_Click);
			// 
			// labelZone02Setpoint
			// 
			this->labelZone02Setpoint->AutoSize = true;
			this->labelZone02Setpoint->Location = System::Drawing::Point(128, 82);
			this->labelZone02Setpoint->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone02Setpoint->Name = L"labelZone02Setpoint";
			this->labelZone02Setpoint->Size = System::Drawing::Size(21, 22);
			this->labelZone02Setpoint->TabIndex = 7;
			this->labelZone02Setpoint->Text = L"0";
			this->labelZone02Setpoint->Click += gcnew System::EventHandler(this, &Form1::labelZone02Setpoint_Click);
			// 
			// labelSetpointUnits02
			// 
			this->labelSetpointUnits02->AutoSize = true;
			this->labelSetpointUnits02->Location = System::Drawing::Point(188, 82);
			this->labelSetpointUnits02->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointUnits02->Name = L"labelSetpointUnits02";
			this->labelSetpointUnits02->Size = System::Drawing::Size(32, 22);
			this->labelSetpointUnits02->TabIndex = 6;
			this->labelSetpointUnits02->Text = L"℃";
			this->labelSetpointUnits02->Click += gcnew System::EventHandler(this, &Form1::labelSetpointUnits02_Click);
			// 
			// labelRealTempUnits02
			// 
			this->labelRealTempUnits02->AutoSize = true;
			this->labelRealTempUnits02->Location = System::Drawing::Point(188, 42);
			this->labelRealTempUnits02->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempUnits02->Name = L"labelRealTempUnits02";
			this->labelRealTempUnits02->Size = System::Drawing::Size(32, 22);
			this->labelRealTempUnits02->TabIndex = 6;
			this->labelRealTempUnits02->Text = L"℃";
			this->labelRealTempUnits02->Click += gcnew System::EventHandler(this, &Form1::labelRealTempUnits02_Click);
			// 
			// labelZone02RealTemp
			// 
			this->labelZone02RealTemp->AutoSize = true;
			this->labelZone02RealTemp->Location = System::Drawing::Point(128, 41);
			this->labelZone02RealTemp->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelZone02RealTemp->Name = L"labelZone02RealTemp";
			this->labelZone02RealTemp->Size = System::Drawing::Size(21, 22);
			this->labelZone02RealTemp->TabIndex = 5;
			this->labelZone02RealTemp->Text = L"0";
			this->labelZone02RealTemp->Click += gcnew System::EventHandler(this, &Form1::labelZone02RealTemp_Click);
			// 
			// buttonZone02Switch
			// 
			this->buttonZone02Switch->Location = System::Drawing::Point(28, 122);
			this->buttonZone02Switch->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonZone02Switch->Name = L"buttonZone02Switch";
			this->buttonZone02Switch->Size = System::Drawing::Size(185, 41);
			this->buttonZone02Switch->TabIndex = 3;
			this->buttonZone02Switch->Text = L"打开";
			this->buttonZone02Switch->UseVisualStyleBackColor = true;
			this->buttonZone02Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone02TempSet_Click);
			// 
			// labelSetpointPrompt02
			// 
			this->labelSetpointPrompt02->AutoSize = true;
			this->labelSetpointPrompt02->Location = System::Drawing::Point(23, 82);
			this->labelSetpointPrompt02->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointPrompt02->Name = L"labelSetpointPrompt02";
			this->labelSetpointPrompt02->Size = System::Drawing::Size(120, 22);
			this->labelSetpointPrompt02->TabIndex = 1;
			this->labelSetpointPrompt02->Text = L"设定温度: ";
			this->labelSetpointPrompt02->Click += gcnew System::EventHandler(this, &Form1::labelSetpointPrompt02_Click);
			// 
			// labelRealTempPrompt02
			// 
			this->labelRealTempPrompt02->AutoSize = true;
			this->labelRealTempPrompt02->Location = System::Drawing::Point(23, 41);
			this->labelRealTempPrompt02->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempPrompt02->Name = L"labelRealTempPrompt02";
			this->labelRealTempPrompt02->Size = System::Drawing::Size(120, 22);
			this->labelRealTempPrompt02->TabIndex = 0;
			this->labelRealTempPrompt02->Text = L"实时温度: ";
			this->labelRealTempPrompt02->Click += gcnew System::EventHandler(this, &Form1::labelRealTempPrompt02_Click);
			// 
			// groupBoxZone01
			// 
			this->groupBoxZone01->BackColor = System::Drawing::SystemColors::Window;
			this->groupBoxZone01->Controls->Add(this->labelZone01Setpoint);
			this->groupBoxZone01->Controls->Add(this->labelSetpointUnits01);
			this->groupBoxZone01->Controls->Add(this->labelRealTempUnits01);
			this->groupBoxZone01->Controls->Add(this->labelZone01RealTemp);
			this->groupBoxZone01->Controls->Add(this->buttonZone01Switch);
			this->groupBoxZone01->Controls->Add(this->labelSetpointPrompt01);
			this->groupBoxZone01->Controls->Add(this->labelRealTempPrompt01);
			this->groupBoxZone01->Location = System::Drawing::Point(13, 22);
			this->groupBoxZone01->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone01->Name = L"groupBoxZone01";
			this->groupBoxZone01->Padding = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->groupBoxZone01->Size = System::Drawing::Size(241, 176);
			this->groupBoxZone01->TabIndex = 0;
			this->groupBoxZone01->TabStop = false;
			this->groupBoxZone01->Text = L"Zone01";
			this->groupBoxZone01->Click += gcnew System::EventHandler(this, &Form1::groupBoxZone01_Click);
			// 
			// labelZone01Setpoint
			// 
			this->labelZone01Setpoint->AutoSize = true;
			this->labelZone01Setpoint->Location = System::Drawing::Point(128, 82);
			this->labelZone01Setpoint->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labelZone01Setpoint->Name = L"labelZone01Setpoint";
			this->labelZone01Setpoint->Size = System::Drawing::Size(21, 22);
			this->labelZone01Setpoint->TabIndex = 7;
			this->labelZone01Setpoint->Text = L"0";
			this->labelZone01Setpoint->Click += gcnew System::EventHandler(this, &Form1::labelZone01Setpoint_Click);
			// 
			// labelSetpointUnits01
			// 
			this->labelSetpointUnits01->AutoSize = true;
			this->labelSetpointUnits01->Location = System::Drawing::Point(188, 82);
			this->labelSetpointUnits01->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointUnits01->Name = L"labelSetpointUnits01";
			this->labelSetpointUnits01->Size = System::Drawing::Size(32, 22);
			this->labelSetpointUnits01->TabIndex = 6;
			this->labelSetpointUnits01->Text = L"℃";
			this->labelSetpointUnits01->Click += gcnew System::EventHandler(this, &Form1::labelSetpointUnits01_Click);
			// 
			// labelRealTempUnits01
			// 
			this->labelRealTempUnits01->AutoSize = true;
			this->labelRealTempUnits01->Location = System::Drawing::Point(188, 42);
			this->labelRealTempUnits01->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempUnits01->Name = L"labelRealTempUnits01";
			this->labelRealTempUnits01->Size = System::Drawing::Size(32, 22);
			this->labelRealTempUnits01->TabIndex = 6;
			this->labelRealTempUnits01->Text = L"℃";
			this->labelRealTempUnits01->Click += gcnew System::EventHandler(this, &Form1::labelRealTempUnits01_Click);
			// 
			// labelZone01RealTemp
			// 
			this->labelZone01RealTemp->AutoSize = true;
			this->labelZone01RealTemp->Location = System::Drawing::Point(128, 41);
			this->labelZone01RealTemp->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelZone01RealTemp->Name = L"labelZone01RealTemp";
			this->labelZone01RealTemp->Size = System::Drawing::Size(21, 22);
			this->labelZone01RealTemp->TabIndex = 5;
			this->labelZone01RealTemp->Text = L"0";
			this->labelZone01RealTemp->Click += gcnew System::EventHandler(this, &Form1::labelZone01RealTemp_Click);
			// 
			// buttonZone01Switch
			// 
			this->buttonZone01Switch->Location = System::Drawing::Point(28, 122);
			this->buttonZone01Switch->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
			this->buttonZone01Switch->Name = L"buttonZone01Switch";
			this->buttonZone01Switch->Size = System::Drawing::Size(185, 41);
			this->buttonZone01Switch->TabIndex = 3;
			this->buttonZone01Switch->Text = L"打开";
			this->buttonZone01Switch->UseVisualStyleBackColor = true;
			this->buttonZone01Switch->Click += gcnew System::EventHandler(this, &Form1::buttonZone01TempSet_Click);
			// 
			// labelSetpointPrompt01
			// 
			this->labelSetpointPrompt01->AutoSize = true;
			this->labelSetpointPrompt01->Location = System::Drawing::Point(23, 82);
			this->labelSetpointPrompt01->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelSetpointPrompt01->Name = L"labelSetpointPrompt01";
			this->labelSetpointPrompt01->Size = System::Drawing::Size(120, 22);
			this->labelSetpointPrompt01->TabIndex = 1;
			this->labelSetpointPrompt01->Text = L"设定温度: ";
			this->labelSetpointPrompt01->Click += gcnew System::EventHandler(this, &Form1::labelSetpointPrompt01_Click);
			// 
			// labelRealTempPrompt01
			// 
			this->labelRealTempPrompt01->AutoSize = true;
			this->labelRealTempPrompt01->Location = System::Drawing::Point(23, 41);
			this->labelRealTempPrompt01->Margin = System::Windows::Forms::Padding(6, 0, 6, 0);
			this->labelRealTempPrompt01->Name = L"labelRealTempPrompt01";
			this->labelRealTempPrompt01->Size = System::Drawing::Size(120, 22);
			this->labelRealTempPrompt01->TabIndex = 0;
			this->labelRealTempPrompt01->Text = L"实时温度: ";
			this->labelRealTempPrompt01->Click += gcnew System::EventHandler(this, &Form1::labelRealTempPrompt01_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 21);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1024, 715);
			this->Controls->Add(this->groupBoxZones);
			this->Controls->Add(this->groupBox1);
			this->Font = (gcnew System::Drawing::Font(L"宋体", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->KeyPreview = true;
			this->Margin = System::Windows::Forms::Padding(6, 5, 6, 5);
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

	//labelZone01Setpoint->Text = L"666";
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
		if (!readTemperatureButtonThread || !readTemperatureButtonThread->IsAlive) {
			readTemperatureButtonThread = gcnew Thread(gcnew ThreadStart(this, &HuskyNeo2Tool::Form1::ReadTemperatureButtonThread));
			readTemperatureButtonThread->IsBackground = true;
			readTemperatureButtonThread->Start();
		}
/*
		for (int i = 0; i < 12; i++) {
			float temperature = currentHusky->getTemperature(i + 1);
			// C = (F - 32) / 1.8
			temperature = (temperature - 32) / 1.8;
			int tmp = temperature * 10 + 0.5;
			temperature = (float)tmp / 10;
			this->labelZonesSetpoint[i]->Text = temperature.ToString();
		}
*/
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

		System::Windows::Forms::DialogResult result = setAllZonesTemperatureForm->ShowDialog();
		if (result == ::DialogResult::OK) {
			if (setTemperatureButtonThread && setTemperatureButtonThread->IsAlive) {
				setTemperatureButtonThread->Abort();
				//setTemperatureButtonThread = (Thread ^)NULL;
			}
			setTemperatureButtonThread = gcnew Thread(gcnew ThreadStart(this, &HuskyNeo2Tool::Form1::SetTemperatureButtonThread));
			setTemperatureButtonThread->IsBackground = true;
			setTemperatureButtonThread->Start();
			setTempInProgressForm->ShowDialog();
		}
/*
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
*/
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
private: System::Void buttonLock_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (opLock) {
				buttonConnect->Enabled = true;
				comboBox1->Enabled = true;
				button27->Enabled = true;
				button28->Enabled = true;
				labelComNumPrompt->Enabled = true;
				groupBoxZones->Enabled = true;
				this->buttonLock->Text = L"锁定";
				opLock = FALSE;
				
			 } else {
				
				buttonConnect->Enabled = false;
				comboBox1->Enabled = false;
				button27->Enabled = false;
				button28->Enabled = false;
				labelComNumPrompt->Enabled = false;

				groupBoxZones->Enabled = false;
				this->buttonLock->Text = L"解锁";
				opLock = TRUE;
			 }
		 }
private:
	void zoneSetpoint_Click(int zoneNum) {
		//fix me: check zoneNum.

		if (currentHusky == NULL) {
			MessageBox::Show("请选择机台号！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}
		if (!currentHusky->isConnected()) {
			MessageBox::Show("当前设备未连接！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			return;
		}

		SetOneZoneTemperatureForm ^temperatureSetting = gcnew SetOneZoneTemperatureForm();
		if (zoneNum < 10)
			temperatureSetting->Text = "Zone0" + zoneNum + " 温度设置";
		else
			temperatureSetting->Text = "Zone" + zoneNum + " 温度设置";
		System::Windows::Forms::DialogResult result = temperatureSetting->ShowDialog();
		if (result == ::DialogResult::OK && temperatureSetting->textBox1->Text != "") {
			float temperature = (float)Convert::ToDouble(temperatureSetting->textBox1->Text);
			// F -> C: F = 32 + C * 1.8;
			float Fahrenheit = 32 + temperature * (float)1.8;
			if (currentHusky->setTemperature(Fahrenheit, zoneNum) == FALSE) //*
				MessageBox::Show("Zone" + zoneNum + "温度设置失败！", "Error", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);//*
			else
				this->labelZonesSetpoint[zoneNum - 1]->Text = temperatureSetting->textBox1->Text; //*
		}
	}

/******************************* label Zone Setpoint Click Event ********************************/
private: System::Void labelZone01Setpoint_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(1);
	}
private: System::Void labelZone02Setpoint_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(2);
	}
private: System::Void labelZone03Setpoint_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(3);
	}
private: System::Void labelZone04Setpoint_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(4);
	}
private: System::Void labelZone05Setpoint_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(5);
	}
private: System::Void labelZone06Setpoint_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(6);
	}
private: System::Void labelZone07Setpoint_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(7);
	}
private: System::Void labelZone08Setpoint_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(8);
	}
private: System::Void labelZone09Setpoint_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(9);
	}
private: System::Void labelZone10Setpoint_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(10);
	}
private: System::Void labelZone11Setpoint_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(11);
	}
private: System::Void labelZone12Setpoint_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(12);
	}

/******************************* GroupBox Click Event *****************************************/
private: System::Void groupBoxZone01_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(1);
	}
private: System::Void groupBoxZone02_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(2);
	}
private: System::Void groupBoxZone03_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(3);
	}
private: System::Void groupBoxZone04_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(4);
	}
private: System::Void groupBoxZone05_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(5);
	}
private: System::Void groupBoxZone06_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(6);
	}
private: System::Void groupBoxZone07_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(7);
	}
private: System::Void groupBoxZone08_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(8);
	}
private: System::Void groupBoxZone09_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(9);
	}
private: System::Void groupBoxZone10_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(10);
	}
private: System::Void groupBoxZone11_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(11);
	}
private: System::Void groupBoxZone12_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(12);
	}

/******************************* labelRealTempPrompt Click Event ***********************************/
private: System::Void labelRealTempPrompt01_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(1);
	}
private: System::Void labelRealTempPrompt02_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(2);
	}
private: System::Void labelRealTempPrompt03_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(3);
	}
private: System::Void labelRealTempPrompt04_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(4);
	}
private: System::Void labelRealTempPrompt05_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(5);
	}
private: System::Void labelRealTempPrompt06_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(6);
	}
private: System::Void labelRealTempPrompt07_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(7);
	}
private: System::Void labelRealTempPrompt08_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(8);
	}
private: System::Void labelRealTempPrompt09_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(9);
	}
private: System::Void labelRealTempPrompt10_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(10);
	}
private: System::Void labelRealTempPrompt11_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(11);
	}
private: System::Void labelRealTempPrompt12_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(12);
	}
/******************************* labelSetpointPrompt Click Event ***********************************/
private: System::Void labelSetpointPrompt01_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(1);
	}
private: System::Void labelSetpointPrompt02_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(2);
	}
private: System::Void labelSetpointPrompt03_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(3);
	}
private: System::Void labelSetpointPrompt04_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(4);
	}
private: System::Void labelSetpointPrompt05_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(5);
	}
private: System::Void labelSetpointPrompt06_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(6);
	}
private: System::Void labelSetpointPrompt07_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(7);
	}
private: System::Void labelSetpointPrompt08_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(8);
	}
private: System::Void labelSetpointPrompt09_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(9);
	}
private: System::Void labelSetpointPrompt10_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(10);
	}
private: System::Void labelSetpointPrompt11_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(11);
	}
private: System::Void labelSetpointPrompt12_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(12);
	}

/******************************* labelSetpointPrompt Click Event ***********************************/
private: System::Void labelZone01RealTemp_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(1);
	}
private: System::Void labelZone02RealTemp_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(2);
	}
private: System::Void labelZone03RealTemp_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(3);
	}
private: System::Void labelZone04RealTemp_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(4);
	}
private: System::Void labelZone05RealTemp_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(5);
	}
private: System::Void labelZone06RealTemp_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(6);
	}
private: System::Void labelZone07RealTemp_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(7);
	}
private: System::Void labelZone08RealTemp_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(8);
	}
private: System::Void labelZone09RealTemp_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(9);
	}
private: System::Void labelZone10RealTemp_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(10);
	}
private: System::Void labelZone11RealTemp_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(11);
	}
private: System::Void labelZone12RealTemp_Click(System::Object^  sender, System::EventArgs^  e) {
		zoneSetpoint_Click(12);
	}
/******************************* labelRealTempUnits Click Event ***********************************/
private: System::Void labelRealTempUnits01_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(1);
		 }
private: System::Void labelRealTempUnits02_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(2);
		 }
private: System::Void labelRealTempUnits03_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(3);
		 }
private: System::Void labelRealTempUnits04_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(4);
		 }
private: System::Void labelRealTempUnits05_Click(System::Object^  sender, System::EventArgs^  e) {
			zoneSetpoint_Click(5);
		 }
private: System::Void labelRealTempUnits06_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(6);
		 }
private: System::Void labelRealTempUnits07_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(7);
		 }
private: System::Void labelRealTempUnits08_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(8);
		 }
private: System::Void labelRealTempUnits09_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(9);
		 }
private: System::Void labelRealTempUnits10_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(10);
		 }
private: System::Void labelRealTempUnits11_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(11);
		 }
private: System::Void labelRealTempUnits12_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(12);
		 }
/******************************* labelSetpointUnits Click Event ***********************************/
private: System::Void labelSetpointUnits01_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(1);
		 }
private: System::Void labelSetpointUnits02_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(2);
		 }
private: System::Void labelSetpointUnits03_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(3);
		 }
private: System::Void labelSetpointUnits04_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(4);
		 }
private: System::Void labelSetpointUnits05_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(5);
		 }
private: System::Void labelSetpointUnits06_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(6);
		 }
private: System::Void labelSetpointUnits07_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(6);
		 }
private: System::Void labelSetpointUnits08_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(8);
		 }
private: System::Void labelSetpointUnits09_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(9);
		 }
private: System::Void labelSetpointUnits10_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(10);
		 }
private: System::Void labelSetpointUnits11_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(11);
		 }
private: System::Void labelSetpointUnits12_Click(System::Object^  sender, System::EventArgs^  e) {
			 zoneSetpoint_Click(12);
		 }
};
}

