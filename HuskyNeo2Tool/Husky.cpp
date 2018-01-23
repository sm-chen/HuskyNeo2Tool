
#include <Windows.h>

#include "StdAfx.h"

#include "Husky.h"


Husky::Husky(void)
{
	mIsConnected = FALSE;
	mServPort = 4002;
	mServIpAddr[0] = '\0';
	mMutex = CreateMutex(NULL, FALSE, NULL);
	mCommunicationErr = FALSE;

}

Husky::Husky(char *ipAddr)
{
	Husky();
	strncpy(mServIpAddr, ipAddr, IP_ADDRESS_STRING_LEN - 1);
	mServIpAddr[IP_ADDRESS_STRING_LEN - 1] = '\0';
}

Husky::~Husky(void)
{
}
uint16_t Husky::modbus_crc16(unsigned char *data, int length) {
	uint16_t crc_reg = 0x0;
	uint16_t *p_crc_reg = &crc_reg;
	unsigned char * p_crc_reg_l = (unsigned char *)p_crc_reg;
	unsigned char * p_crc_reg_h = (unsigned char *)p_crc_reg + 1;
	if (length <= 0)
		return crc_reg;

	while (length--) {
		*p_crc_reg = *(a_crctable + ((*p_crc_reg_l)^*data++))^*(p_crc_reg_h);
	}
	return *p_crc_reg;
}
int Husky::deleteDLE(unsigned char *data, int len)
{
	for (int i = 0; i < len; i++) {
		if (data[i] != DLE) {
			continue;
		} else {
			if (data[i + 1] == DLE)
				i++;
			for (int j = i; j < len - 1; j++) {
				data[j] = data[j + 1];
			}
			len--;
		}
	}
	return len;
}
BOOLEAN Husky::checkCrc(unsigned char *data, int len)
{
	uint16_t recievCrcValue = (data[len - 2] << 8) | data[len - 1];
	len = len - 2;

	if (data[0] == DLE && (data[1] == SOH || data[1] == STX)) {
		unsigned char *crcDataStart = data + 2;
		len = len - 2;
		len = deleteDLE(crcDataStart, len);
		uint16_t calcCrcValue = modbus_crc16(crcDataStart, len);
		
		if (recievCrcValue == calcCrcValue)
			return TRUE;
		else
			return FALSE;
	} else {
		return FALSE;
	}
}
uint16_t Husky::generateCrc(unsigned char *data, int len)
{
	unsigned char *crcDataStart = data;
	if (data[0] == DLE && (data[1] == SOH || data[1] == STX)) {
		crcDataStart = data + 2;
		len = len - 2;
	}
	len = deleteDLE(crcDataStart, len);
	return modbus_crc16(crcDataStart, len);
}

BOOLEAN Husky::connect()
{
/*
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建套接字
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	//服务器地址信息

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(mServIpAddr);
	servAddr.sin_port = htons(mServPort);

	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(mServPort);
	localAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(sock, (SOCKADDR*)&localAddr, sizeof(SOCKADDR)) < 0)
		return FALSE;

	int mode = 1; // 0: block mode   1: none block mode
	ioctlsocket(sock, FIONBIO, (unsigned long *)&mode); // none block mode

	if (checkHuskyVersion()) {
		mIsConnected = TRUE;
		return TRUE;
	} else {
		closesocket(sock);
		WSACleanup();
		return FALSE;
	}
*/
	BOOLEAN ret = FALSE;
	WaitForSingleObject(mMutex, INFINITE);
	if (this->serialPort.InitPort(getSerialPortNum())) {
		if (checkHuskyVersion()) {
			mIsConnected = TRUE;
			ret = TRUE;
		} else {
			this->serialPort.ClosePort();
			mIsConnected = FALSE;
			ret = FALSE;
		}
	} else {
		ret = FALSE;
	}

	ReleaseMutex(mMutex);
	return ret;
}

void Husky::disconnect()
{
/*
	closesocket(sock);
	WSACleanup();
	mIsConnected = FALSE;
*/
	WaitForSingleObject(mMutex, INFINITE);
	this->serialPort.ClosePort();
	mIsConnected = FALSE;
	ReleaseMutex(mMutex);
}

int Husky::sendData(char *data, int len)
{
	return sendto(sock, data, len, 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
}
int Husky::receivData(char *data)
{
	sockaddr fromAddr;
	int addrLen = sizeof(fromAddr);

	return recvfrom(sock, data, BUF_SIZE, 0, &fromAddr, &addrLen);
}


float bytetof(unsigned char *p_data)
{
	union cvnlesscast {
		binfloat mirror ;
		float value ;
	} cvnlesscast;

	cvnlesscast.mirror = (*p_data << 24 | *(p_data + 1) << 16 | *(p_data + 2) << 8 | *(p_data + 3));

	return cvnlesscast.value ;
}
unsigned char *ftobyte(float value, unsigned char *p_data)
{
	union cvnlesscast {
		binfloat mirror;
		float value ;
	} cvnlesscast;

	cvnlesscast.value = value ;
	*p_data = (cvnlesscast.mirror & 0xFF000000 ) >> 24;
	*(p_data + 1) = (cvnlesscast.mirror & 0x00FF0000) >> 16;
	*(p_data + 2) = (cvnlesscast.mirror & 0x0000FF00) >> 8;
	*(p_data + 3) = (cvnlesscast.mirror & 0x000000FF);

	return p_data ;
}

/* read n bytes from husky:
 * bytes: the bytes receive from husky until timeout. 1 will return immediately when receive any bytes until timeout.
 * receivDataBuf: reveived data buffer.
 */
int Husky::readBytes(unsigned char* receivData, int bytes)
{
	int len = 0;
	int times = 0;
	len = serialPort.ReadData(receivData);
	while (len < bytes && times < UDP_RECVFROM_TIMEOUT_TIMES) {
		len = len + serialPort.ReadData(receivData + len);
		Sleep(UDP_RECVFROM_TIMEOUT_TIME);
		times++;
	}
	return len;
}

float Husky::getTemperature(int zone)
{
	if (zone <= 0 || zone > 12)
		return 0;
	int tryTimes = TRY_TIMES;
	WaitForSingleObject(mMutex, INFINITE);

tryagain:
	float temperature;
	unsigned char CMD1 = 0x30 | zone;
	unsigned char CMD2 = 0x20;
	unsigned char data[] = {EOT, DEVID, ADD, CMD1, CMD2, RES, ENQ};
	unsigned char AckMsg[] = {DLE, ACK1};
	unsigned char receivData[BUF_SIZE];
	int len = 0;
	//this->receivData((char *)receivData); // clear current udp buffer!
	this->serialPort.ReadData(receivData); // ??? need to clear buffer???
	//this->sendData((char *)data, sizeof(data));
	this->serialPort.WriteData(data, sizeof(data));

	len = readBytes(receivData, 18);

	unsigned char temperData[4] = {receivData[10], receivData[11], receivData[12], receivData[13]};
	
	if (len <= 0 || !checkCrc(receivData, len)) {
		printf("CRC Check failed!");
/************************************************************************************/
		len = readBytes(receivData, 1);

		if (len <= 0) {
			Sleep(1000); // ???
		} else if (len > 0 && receivData[0] == ENQ) {
			this->serialPort.WriteData(AckMsg, sizeof(AckMsg));
			Sleep(100);
		} else if (len > 0 && receivData[0] == EOT) {
			;
		}
/*************************************************************************************/
		temperature = 32; // 0℃

		if (--tryTimes)
			goto tryagain;
		goto error;
		mCommunicationErr = TRUE;
	}

	//this->sendData((char *)AckMsg, sizeof(AckMsg));
	this->serialPort.WriteData(AckMsg, sizeof(AckMsg));

	len = readBytes(receivData, 1); // EOT

	temperature = bytetof(temperData);

error:
	ReleaseMutex(mMutex);
	return temperature;
}


BOOLEAN Husky::setTemperature(float temperature, int zone)
{
	if (zone <= 0 || zone > 12)
		return FALSE;
	int tryTimes = TRY_TIMES;
	WaitForSingleObject(mMutex, INFINITE);

tryagain:
	unsigned char CMD1 = 0x30 | zone;
	unsigned char CMD2 = 0x21;
	unsigned char data[] = {EOT, DEVID, ADD, CMD1, CMD2, RES, ENQ};
	unsigned char receivData[BUF_SIZE];

	//this->receivData((char *)receivData); // clear current udp buffer!
	this->serialPort.ReadData(receivData);
	//this->sendData((char *)data, sizeof(data));
	this->serialPort.WriteData(data, sizeof(data));

	// Controller allow to set Temperature data from husky is 7 bytes
	int len = readBytes(receivData, 7);

	// Controller allow to do
	if (receivData[2] == CMD1 && receivData[3] == CMD2 && receivData[5] == DLE && receivData[6] == ACK0) {
		unsigned char temperData[4];
		ftobyte(temperature, temperData);

		unsigned char data[] = {DLE, STX, temperData[0] ,temperData[1], temperData[2], temperData[3], DLE, ETX};
		unsigned char crcData[sizeof(data) + 2];
		for (int i = 0; i < sizeof(data); i++) {
			crcData[i] = data[i];
		}
		uint16_t crcValue = generateCrc(data, sizeof(data));
		crcData[sizeof(crcData) - 1] = *(unsigned char *)(&crcValue);
		crcData[sizeof(crcData) - 2] = *((unsigned char *)(&crcValue) + 1);
		//this->sendData((char *)crcData, sizeof(crcData));
		serialPort.WriteData(crcData, sizeof(crcData));

		// read 2 bytes ACK MSG
		len = readBytes(receivData, 2);
		if (len == 2 && receivData[0] == DLE && receivData[1] == ACK1) {
			unsigned char endTrans[] = {EOT};
			//this->sendData((char *)endTrans, sizeof(endTrans));
			serialPort.WriteData(endTrans, sizeof(endTrans));
			goto ok;
		} else
			goto error;
	} else {
		goto error;
	}
ok:
	ReleaseMutex(mMutex);
	return TRUE;
error:
/************************************************************************************/
	len = readBytes(receivData, 1);
	if (len > 0 && receivData[0] == ENQ) {
		unsigned char AckMsg[] = {DLE, ACK1};
		this->serialPort.WriteData(AckMsg, sizeof(AckMsg));
		Sleep(100);
	} else if (len > 0 && receivData[0] == EOT) {
		;
	} else {
		Sleep(1000);
	}
/*************************************************************************************/
	if (--tryTimes)
		goto tryagain;
	ReleaseMutex(mMutex);
	mCommunicationErr = TRUE;
	return FALSE;
}

BOOLEAN Husky::isConnected()
{
	return mIsConnected;
}

void Husky::setConnected()
{
	mIsConnected = TRUE;
}
void Husky::setDisconnected()
{
	mIsConnected = FALSE;
}

float Husky::getRealtimeTemperature(int zone)
{
	if (zone <= 0 || zone > 12)
		return 0;
	int tryTimes = TRY_TIMES;
	WaitForSingleObject(mMutex, INFINITE);

tryagain:
	float temperature;
	unsigned char CMD1 = 0x30 | zone;
	unsigned char CMD2 = 0x22;
	unsigned char data[] = {EOT, DEVID, ADD, CMD1, CMD2, RES, ENQ};
	unsigned char AckMsg[] = {DLE, ACK1};
	unsigned char receivData[BUF_SIZE];
	int len = 0;
	//this->receivData((char *)receivData); // clear current udp buffer!
	this->serialPort.ReadData(receivData);
	//this->sendData((char *)data, sizeof(data));
	this->serialPort.WriteData(data, sizeof(data));

	// read temperature data from husky is 18 bytes
	len = readBytes(receivData, 18);
	unsigned char temperData[4] = {receivData[10], receivData[11], receivData[12], receivData[13]};
	
	if (len <= 0 || !checkCrc(receivData, len)) {
		printf("CRC Check failed!");
/************************************************************************************/
		len = readBytes(receivData, 1);

		if (len <= 0) {
			Sleep(1000); // ???
		} else if (len > 0 && receivData[0] == ENQ) {
			this->serialPort.WriteData(AckMsg, sizeof(AckMsg));
			Sleep(100);
		} else if (len > 0 && receivData[0] == EOT) {
			;
		}
/*************************************************************************************/
		temperature = 32; // 0℃
		if (--tryTimes)
			goto tryagain;
		mCommunicationErr = TRUE;
		goto error;
	}

	this->serialPort.WriteData(AckMsg, sizeof(AckMsg));

	len = readBytes(receivData, 1); // EOT

	temperature = bytetof(temperData);

error:
	ReleaseMutex(mMutex);
	return temperature;
}

BOOLEAN Husky::setAllZonesTemperature(float temperature)
{
	for(int i = 1; i <= 12; i++) {
		setTemperature(temperature, i);
	}
	return TRUE;
}

BOOLEAN Husky::checkHuskyVersion()
{
	WaitForSingleObject(mMutex, INFINITE);

	unsigned char CMD1 = 0x20;
	unsigned char CMD2 = 0x22;
	unsigned char data[] = {EOT, DEVID, ADD, CMD1, CMD2, RES, ENQ};
	unsigned char AckMsg[] = {DLE, ACK1};
	unsigned char receivData[BUF_SIZE];
	int len = 0;
	//this->receivData((char *)receivData); // clear current udp buffer!
	this->serialPort.ReadData(receivData);
	//this->sendData((char *)data, sizeof(data));
	this->serialPort.WriteData(data, sizeof(data));

	len = readBytes(receivData, 18);
	// current Husky Neo2 Version
	unsigned char versionData[4] = {receivData[10], receivData[11], receivData[12], receivData[13]};

	if (len <= 0 || !checkCrc(receivData, len) ||
		!(versionData[0] == 0x32 && versionData[1] == 0x36 && versionData[2] == 0x30 && versionData[3] == 0x31)) {
		printf("CRC Check failed!");
/************************************************************************************/
		len = readBytes(receivData, 1);

		if (len <= 0) {
			Sleep(1000); // ???
		} else if (len > 0 && receivData[0] == ENQ) {
			this->serialPort.WriteData(AckMsg, sizeof(AckMsg));
			Sleep(100);
		} else if (len > 0 && receivData[0] == EOT) {
			;
		}
/*************************************************************************************/
		goto error;
	}

	//this->sendData((char *)AckMsg, sizeof(AckMsg));
	this->serialPort.WriteData(AckMsg, sizeof(AckMsg));

	len = readBytes(receivData, 1);
	
	ReleaseMutex(mMutex);
	return TRUE;
error:
	ReleaseMutex(mMutex);
	return FALSE;
}

void Husky::setIpAddr(char *ipAddr)
{
	strncpy(mServIpAddr, ipAddr, IP_ADDRESS_STRING_LEN - 1);
	mServIpAddr[IP_ADDRESS_STRING_LEN - 1] = '\0';
}

void Husky::getIpAddr(char *ipAddr)
{
	strncpy(ipAddr, mServIpAddr, IP_ADDRESS_STRING_LEN - 1);
	ipAddr[IP_ADDRESS_STRING_LEN - 1] = '\0';
}

float Husky::getManualPercentOutput(int zone)
{
	if (zone <= 0 || zone > 12)
		return 0;
	int tryTimes = TRY_TIMES;
	WaitForSingleObject(mMutex, INFINITE);

tryagain:
	float percent;
	unsigned char CMD1 = 0x30 | zone;
	unsigned char CMD2 = 0x6A;
	unsigned char data[] = {EOT, DEVID, ADD, CMD1, CMD2, RES, ENQ};
	unsigned char AckMsg[] = {DLE, ACK1};
	unsigned char receivData[BUF_SIZE];
	int len = 0;
	//this->receivData((char *)receivData); // clear current udp buffer!
	this->serialPort.ReadData(receivData);
	//this->sendData((char *)data, sizeof(data));
	this->serialPort.WriteData(data, sizeof(data));

	// read percent data from husky is 18 bytes
	len = readBytes(receivData, 18);
	unsigned char percentData[4] = {receivData[10], receivData[11], receivData[12], receivData[13]};
	
	if (len <= 0 || !checkCrc(receivData, len)) {
		printf("CRC Check failed!");
/************************************************************************************/
		len = readBytes(receivData, 1);

		if (len <= 0) {
			Sleep(1000); // ???
		} else if (len > 0 && receivData[0] == ENQ) {
			this->serialPort.WriteData(AckMsg, sizeof(AckMsg));
			Sleep(100);
		} else if (len > 0 && receivData[0] == EOT) {
			;
		}
/*************************************************************************************/
		percent = -1;
		if (--tryTimes)
			goto tryagain;
		mCommunicationErr = TRUE;
		goto error;
	}
	
	//this->sendData((char *)AckMsg, sizeof(AckMsg));
	this->serialPort.WriteData(AckMsg, sizeof(AckMsg));

	len = readBytes(receivData, 1); // EOT

	percent = bytetof(percentData);

error:
	ReleaseMutex(mMutex);
	return percent;
}
BOOLEAN Husky::setManualPercentOutput(int zone, float percent)
{
	if (zone <= 0 || zone > 12)
		return FALSE;
	int tryTimes = TRY_TIMES;
	WaitForSingleObject(mMutex, INFINITE);
tryagain:
	unsigned char CMD1 = 0x30 | zone;
	unsigned char CMD2 = 0x6b;
	unsigned char data[] = {EOT, DEVID, ADD, CMD1, CMD2, RES, ENQ};
	unsigned char receivData[BUF_SIZE];

	//this->receivData((char *)receivData); // clear current udp buffer!
	this->serialPort.ReadData(receivData);
	//this->sendData((char *)data, sizeof(data));
	this->serialPort.WriteData(data, sizeof(data));

	// Controller allow to set PercentOutput data from husky is 7 bytes
	int len = readBytes(receivData, 7);

	// Controller allow to do
	if (receivData[2] == CMD1 && receivData[3] == CMD2 && receivData[5] == DLE && receivData[6] == ACK0) {
		unsigned char percentData[4];
		ftobyte(percent, percentData);

		unsigned char data[] = {DLE, STX, percentData[0] ,percentData[1], percentData[2], percentData[3], DLE, ETX};
		unsigned char crcData[sizeof(data) + 2];
		for (int i = 0; i < sizeof(data); i++) {
			crcData[i] = data[i];
		}
		uint16_t crcValue = generateCrc(data, sizeof(data));
		crcData[sizeof(crcData) - 1] = *(unsigned char *)(&crcValue);
		crcData[sizeof(crcData) - 2] = *((unsigned char *)(&crcValue) + 1);
		//this->sendData((char *)crcData, sizeof(crcData));
		this->serialPort.WriteData(crcData, sizeof(crcData));

		// read 2 bytes ACK MSG
		len = readBytes(receivData, 2);
		if (len == 2 && receivData[0] == DLE && receivData[1] == ACK1) {
			unsigned char endTrans[] = {EOT};
			//this->sendData((char *)endTrans, sizeof(endTrans));
			this->serialPort.WriteData(endTrans, sizeof(endTrans));
			goto ok;
		} else
			goto error;
	} else {
		goto error;
	}
ok:
	ReleaseMutex(mMutex);
	return TRUE;
error:
/************************************************************************************/
	len = readBytes(receivData, 1);
	if (len > 0 && receivData[0] == ENQ) {
		unsigned char AckMsg[] = {DLE, ACK1};
		this->serialPort.WriteData(AckMsg, sizeof(AckMsg));
		Sleep(100);
	} else if (len > 0 && receivData[0] == EOT) {
		;
	} else {
		Sleep(1000);
	}
/*************************************************************************************/
	if (--tryTimes)
		goto tryagain;
	mCommunicationErr = TRUE;
	ReleaseMutex(mMutex);
	return FALSE;
}

uint16_t Husky::getRegulationMode(int zone)
{
	if (zone <= 0 || zone > 12)
		return 0;
	int tryTimes = TRY_TIMES;
	WaitForSingleObject(mMutex, INFINITE);
tryagain:
	unsigned char CMD1 = 0x30 | zone;
	unsigned char CMD2 = 0x8E;
	unsigned char data[] = {EOT, DEVID, ADD, CMD1, CMD2, RES, ENQ};
	unsigned char AckMsg[] = {DLE, ACK1};
	unsigned char receivData[BUF_SIZE];
	int len = 0;
	//this->receivData((char *)receivData); // clear current udp buffer!
	this->serialPort.ReadData(receivData);
	//this->sendData((char *)data, sizeof(data));
	this->serialPort.WriteData(data, sizeof(data));

	// read RegulationMode data from husky is 18 bytes
	len = readBytes(receivData, 16);
	//unsigned char temperData[2] = {receivData[10], receivData[11]};
	uint16_t mode = (receivData[10] << 8) | receivData[11];
	
	if (len <= 0 || !checkCrc(receivData, len)) {
		printf("CRC Check failed!");
/************************************************************************************/
		len = readBytes(receivData, 1);

		if (len <= 0) {
			Sleep(1000); // ???
		} else if (len > 0 && receivData[0] == ENQ) {
			this->serialPort.WriteData(AckMsg, sizeof(AckMsg));
			Sleep(100);
		} else if (len > 0 && receivData[0] == EOT) {
			;
		}
/*************************************************************************************/
		mode = -1;
		if (--tryTimes)
			goto tryagain;
		mCommunicationErr = TRUE;
		goto error;
	}

	//this->sendData((char *)AckMsg, sizeof(AckMsg));
	this->serialPort.WriteData(AckMsg, sizeof(AckMsg));

	len = readBytes(receivData, 1); // EOT

	//temperature = bytetof(temperData);

error:
	ReleaseMutex(mMutex);
	return mode;
}
BOOLEAN Husky::setRegulationMode(int zone, uint16_t mode)
{
	if (zone <= 0 || zone > 12)
		return FALSE;
	int tryTimes = TRY_TIMES;
	WaitForSingleObject(mMutex, INFINITE);
tryagain:
	unsigned char CMD1 = 0x30 | zone;
	unsigned char CMD2 = 0x8f;
	unsigned char data[] = {EOT, DEVID, ADD, CMD1, CMD2, RES, ENQ};
	unsigned char receivData[BUF_SIZE];

	//this->receivData((char *)receivData); // clear current udp buffer!
	this->serialPort.ReadData(receivData);
	//this->sendData((char *)data, sizeof(data));
	this->serialPort.WriteData(data, sizeof(data));

	// Controller allow to set Regulation Mode data from husky is 7 bytes
	int len = readBytes(receivData, 7);

	// Controller allow to do
	if (receivData[2] == CMD1 && receivData[3] == CMD2 && receivData[5] == DLE && receivData[6] == ACK0) {
		//unsigned char temperData[4];
		//ftobyte(temperature, temperData);
		unsigned char data1 = mode > 8;
		unsigned char data2 = (unsigned char)mode;
		unsigned char data[] = {DLE, STX, data1, data2, DLE, ETX};
		unsigned char crcData[sizeof(data) + 2];
		for (int i = 0; i < sizeof(data); i++) {
			crcData[i] = data[i];
		}
		uint16_t crcValue = generateCrc(data, sizeof(data));
		crcData[sizeof(crcData) - 1] = *(unsigned char *)(&crcValue);
		crcData[sizeof(crcData) - 2] = *((unsigned char *)(&crcValue) + 1);
		this->serialPort.WriteData(crcData, sizeof(crcData));

		// read 2 bytes ACK MSG
		len = readBytes(receivData, 2);
		if (len == 2 && receivData[0] == DLE && receivData[1] == ACK1) {
			unsigned char endTrans[] = {EOT};
			//this->sendData((char *)endTrans, sizeof(endTrans));
			this->serialPort.WriteData(endTrans, sizeof(endTrans));
			goto ok;
		} else
			goto error;
	} else {
		goto error;
	}
ok:
	ReleaseMutex(mMutex);
	return TRUE;
error:
/************************************************************************************/
	len = readBytes(receivData, 1);
	if (len > 0 && receivData[0] == ENQ) {
		unsigned char AckMsg[] = {DLE, ACK1};
		this->serialPort.WriteData(AckMsg, sizeof(AckMsg));
		Sleep(100);
	} else if (len > 0 && receivData[0] == EOT) {
		;
	} else {
		Sleep(1000);
	}
/*************************************************************************************/
	if (--tryTimes)
		goto tryagain;
	mCommunicationErr = TRUE;
	ReleaseMutex(mMutex);
	return FALSE;
}

BOOLEAN Husky::getZoneOnOff(int zone)
{
	uint16_t mode;
	float manualPercentOutput;

	mode = getRegulationMode(zone);
	//manualPercentOutput = getManualPercentOutput(zone);

	if (mode == MANUAL_REGULATION_MODE /*&& manualPercentOutput == 0*/)
		return FALSE;
	else
		return TRUE;
		
}
BOOLEAN Husky::setZoneOnOff(int zone, BOOLEAN on)
{
	if (on) {
		setRegulationMode(zone, AUTOMATIC_REGULATION_MODE);
		setManualPercentOutput(zone, 50); // 50%???
	} else {
		setRegulationMode(zone, MANUAL_REGULATION_MODE);
		setManualPercentOutput(zone, 0);
	}

	return TRUE;
}

uint16_t Husky::getControlerStatus(int zone)
{
	if (zone <= 0 || zone > 12)
		return 0;
	int tryTimes = TRY_TIMES;
	WaitForSingleObject(mMutex, INFINITE);
tryagain:
	unsigned char CMD1 = 0x30 | zone;
	unsigned char CMD2 = 0x44; // 0x44: controler status;  0x2E: Alarm Active Status
	unsigned char data[] = {EOT, DEVID, ADD, CMD1, CMD2, RES, ENQ};
	unsigned char AckMsg[] = {DLE, ACK1};
	unsigned char receivData[BUF_SIZE];
	int len = 0;
	//this->receivData((char *)receivData); // clear current udp buffer!
	this->serialPort.ReadData(receivData);
	//this->sendData((char *)data, sizeof(data));
	this->serialPort.WriteData(data, sizeof(data));

	// Alarm Active Status data from husky is 16 bytes
	len = readBytes(receivData, 16);
	//unsigned char temperData[2] = {receivData[10], receivData[11]};
	uint16_t alarmStatus = (receivData[10] << 8) | receivData[11];
	
	if (len <= 0 || !checkCrc(receivData, len)) {
		printf("CRC Check failed!");
/************************************************************************************/
		len = readBytes(receivData, 1);

		if (len <= 0) {
			Sleep(1000); // ???
		} else if (len > 0 && receivData[0] == ENQ) {
			this->serialPort.WriteData(AckMsg, sizeof(AckMsg));
			Sleep(100);
		} else if (len > 0 && receivData[0] == EOT) {
			;
		}
/*************************************************************************************/
		alarmStatus = 0;
		if (--tryTimes)
			goto tryagain;
		mCommunicationErr = TRUE;
		goto error;
	}

	//this->sendData((char *)AckMsg, sizeof(AckMsg));
	this->serialPort.WriteData(AckMsg, sizeof(AckMsg));

	len = readBytes(receivData, 1); // EOT

error:
	ReleaseMutex(mMutex);
	return alarmStatus;
}
BOOLEAN Husky::controlerReset()
{
	int tryTimes = TRY_TIMES;
	WaitForSingleObject(mMutex, INFINITE);
tryagain:
	unsigned char CMD1 = 0x31;
	unsigned char CMD2 = 0x35;
	unsigned char data[] = {EOT, DEVID, ADD, CMD1, CMD2, RES, ENQ};
	unsigned char receivData[BUF_SIZE];

	//this->receivData((char *)receivData); // clear current udp buffer!
	this->serialPort.ReadData(receivData);
	//this->sendData((char *)data, sizeof(data));
	this->serialPort.WriteData(data, sizeof(data));

	// Controller allow to reset data from husky is 7 bytes
	int len = readBytes(receivData, 7);

	// Controller allow to do
	if (receivData[2] == CMD1 && receivData[3] == CMD2 && receivData[5] == DLE && receivData[6] == ACK0) {
		//unsigned char temperData[4];
		//ftobyte(temperature, temperData);
		unsigned char data1 = 0x00;
		unsigned char data2 = 0x01;
		unsigned char data[] = {DLE, STX, data1, data2, DLE, ETX};
		unsigned char crcData[sizeof(data) + 2];
		for (int i = 0; i < sizeof(data); i++) {
			crcData[i] = data[i];
		}
		uint16_t crcValue = generateCrc(data, sizeof(data));
		crcData[sizeof(crcData) - 1] = *(unsigned char *)(&crcValue);
		crcData[sizeof(crcData) - 2] = *((unsigned char *)(&crcValue) + 1);
		this->serialPort.WriteData(crcData, sizeof(crcData));

		// read 2 bytes ACK MSG
		len = readBytes(receivData, 2);
		if (len == 2 && receivData[0] == DLE && receivData[1] == ACK1) {
			unsigned char endTrans[] = {EOT};
			//this->sendData((char *)endTrans, sizeof(endTrans));
			this->serialPort.WriteData(endTrans, sizeof(endTrans));
			goto ok;
		} else
			goto error;
	} else {
		goto error;
	}
ok:
	ReleaseMutex(mMutex);
	return TRUE;
error:
/************************************************************************************/
	len = readBytes(receivData, 1);
	if (len > 0 && receivData[0] == ENQ) {
		unsigned char AckMsg[] = {DLE, ACK1};
		this->serialPort.WriteData(AckMsg, sizeof(AckMsg));
		Sleep(100);
	} else if (len > 0 && receivData[0] == EOT) {
		;
	} else {
		Sleep(1000);
	}
/*************************************************************************************/
	if (--tryTimes)
		goto tryagain;
	mCommunicationErr = TRUE;
	ReleaseMutex(mMutex);
	return FALSE;
}

char *Husky::getControlerStatusString(uint16_t status)
{
	for (int i = 0; i < sizeof(controllerStatusBits); i++) {
		if (status & controllerStatusBits[i])
			return (char *)controllerStatusString[i];
	}
	return NULL;
}

void Husky::setSerialPortNum(int num)
{
	mSerialPortNum = num;
}
int Husky::getSerialPortNum()
{
	return mSerialPortNum;
}

BOOLEAN Husky::isCommunicationErr()
{
	return mCommunicationErr;
}
void Husky::restoreCommunicationErr()
{
	mCommunicationErr = FALSE;
}