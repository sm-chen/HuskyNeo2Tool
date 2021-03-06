
#pragma once


#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#include "SerialPort.h"


typedef unsigned short u16;
typedef u16 uint16_t;
typedef unsigned char  u8;
typedef u8 uint8_t;

typedef unsigned long  u32;
typedef  u32 uint32_t;
typedef uint32_t binfloat ;


#define BUF_SIZE 100
#define LINE_LEN_MAX 1000
#define IP_ADDRESS_STRING_LEN 20

#define UDP_RECVFROM_TIMEOUT_TIMES 60 // 60 * 20 = 1200ms/1.2s
#define UDP_RECVFROM_TIMEOUT_TIME  20 // ms
#define TRY_TIMES 3 //

#define DEVID 0x26 //DEVICE ID
#define ADD   0X20 //ADDRESS
//Control Characters
#define SOH 0x01 //START OF HEADING
#define STX 0x02 //START OF TEXT
#define ETX 0x03 //END OF TEXT
#define EOT 0x04 //END OF TRANSMISSION
#define ENQ 0x05 //ENQUIRY
//#define ACK 0x06 //ACKNOWLEDGE
#define DLE 0x10 //DATALINK ESCAPE
#define NAK 0x15 //NEGATIVE ACKNOWLEDGE
#define SYN 0x16 //SYNCHRONOUS IDLE
#define ETB 0x17 //END OF TRANSMISSION BLOCK
#define RES 0x20 //Reserved

#define ACK0 0x30
#define ACK1 0x31

#define AUTOMATIC_REGULATION_MODE 0x0001 //Closed-Loop
#define MANUAL_REGULATION_MODE 0x0000 //Open-Loop

/** Controller Status
 *	bit definition
 *	0   加热器功率非零
 *	1   启用软启动
 *	2   手动调节（非 Auto[ 自动]或 View[ 查看] 调节模式）
 *	3   低于设定点温度时警报
 *	4   高于设定点温度时警报
 *	5   低于设定点温度时终止
 *	6   高于设定点温度时终止
 *	7   未找到热电偶
 *	8   热电偶接反
 *	9   不支持
 *	10  保险丝熔断
 *	11  不支持
 *	12  不支持
 *	13  不支持
 *	14  不支持
 *	15  不支持
 *******************************/
#define POWER_TO_HEATER_NOT_ZERO (1 << 0)
#define MANUAL_REGULATION        (1 << 2)
#define ALARM_UNDER_TEMPERATURE  (1 << 3)
#define ALARM_OVER_TEMPERATURE   (1 << 4)
#define ABORT_UNDER_TEMPERATURE  (1 << 5)
#define ABORT_OVER_TEMPERATURE   (1 << 6)
#define LOST_THERMOCOUPLE        (1 << 7)
#define REVERSED_THERMOCOUPLE    (1 << 8)
#define FUSE_BLOWN               (1 << 10)

const uint16_t controllerStatusBits[] = {POWER_TO_HEATER_NOT_ZERO,
										 MANUAL_REGULATION,
										 ALARM_UNDER_TEMPERATURE,
										 ALARM_OVER_TEMPERATURE,
										 ABORT_UNDER_TEMPERATURE,
										 ABORT_OVER_TEMPERATURE,
										 LOST_THERMOCOUPLE,
										 REVERSED_THERMOCOUPLE,
										 FUSE_BLOWN};
// corresponding to controllerStatusBits
const char controllerStatusString[][30] = { {"加热器功率非零"},
											{"确定"},
											{"低于设定点温度警报"},
											{"高于设定点温度警报"},
											{"低于设定点温度终止"},
											{"高于设定点温度终止"},
											{"未找到热电偶"},
											{"热电偶接反"},
											{"保险丝熔断"},};

const uint16_t a_crctable[] =
      {0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
       0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
       0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
       0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
       0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
       0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
       0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
       0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
       0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
       0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
       0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
       0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
       0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
       0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
       0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
       0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
       0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
       0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
       0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
       0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
       0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
       0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
       0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
       0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
       0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
       0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
       0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
       0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
       0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
       0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
       0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
       0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040}; 

class Husky
{
public:
	Husky(void);
	Husky(char *ipAddr);
	~Husky(void);
	uint16_t modbus_crc16(unsigned char *data, int length);
	BOOLEAN checkCrc(unsigned char *data, int len);
	uint16_t generateCrc(unsigned char *data, int len);
	int deleteDLE(unsigned char *data, int len);
	BOOLEAN connect();
	void disconnect();
	int sendData(char *data, int len);
	int receivData(char *data);
	float getTemperature(int zone);
	BOOLEAN setTemperature(float temperature, int zone);
	BOOLEAN isConnected();
	void setConnected();
	void setDisconnected();
	float getRealtimeTemperature(int zone);
	BOOLEAN setAllZonesTemperature(float temperature);

	BOOLEAN checkHuskyVersion();

	void setIpAddr(char *ipAddr);
	void getIpAddr(char *ipAddr);

	float getManualPercentOutput(int zone);
	BOOLEAN setManualPercentOutput(int zone, float percent);

	/** 0x0001: Closed-Loop(Automatic)
	 *  0x0000: Open-Loop(Manual)
	 */
	uint16_t getRegulationMode(int zone);
	BOOLEAN setRegulationMode(int zone, uint16_t mode);
	
	/** Zone off: Manual Percent output is 0% and Regulation Mode is Manual(Open-Loop)
	 *  Zone on : Regulation Mode is Automatic(Closed-Loop) and percent output is 50%?
	 */
	BOOLEAN getZoneOnOff(int zone); // On: return true; Off: return false;
	BOOLEAN setZoneOnOff(int zone, BOOLEAN on);

	uint16_t getControlerStatus(int zone);
	BOOLEAN controlerReset();
	char *getControlerStatusString(uint16_t status);

	void setSerialPortNum(int num);
	int getSerialPortNum();

	int readBytes(unsigned char *receivDataBuf, int bytes);

	BOOLEAN isCommunicationErr();
	void restoreCommunicationErr();
private:
	BOOLEAN mIsConnected;

	SOCKET sock;
	char mServIpAddr[IP_ADDRESS_STRING_LEN];
	int mServPort;
	sockaddr_in servAddr;
	sockaddr_in localAddr;

	HANDLE mMutex;

	int mSerialPortNum;

	BOOLEAN mCommunicationErr;
public:
	CSerialPort serialPort;
};

