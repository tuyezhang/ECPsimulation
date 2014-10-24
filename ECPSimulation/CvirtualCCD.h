#pragma once
#include "sunnyDefine.h"

class CvirtualCCD
{
public:
	CvirtualCCD(void);
	~CvirtualCCD(void);
	void Send_Msg_by_ID(Byte msg_id,Byte msg_type,Byte msg_pri=NONPRIORITY, Byte msg_ver=0);

public:
	Byte *Msg_Send_Buffer;
	CCD_Exception_Flags Exception_Flags;	//异常标志位
	CCD_Exception_Detail Exception_Detail;	//异常码，异常附加数据发送缓冲区
	Byte Send_Response;								//表示设备在需要发送报文时为主动发送还是回复，在某些时候用得到

	//CCD内部信息
private:						//所有的设备的状态和信息都是私有的，需要用响应的函数访问，修改
	Byte Lock_Status;										//开锁，锁闭状态
	Node_Information Node_Info;					//网络节点信息
	CCD_Car_Info Device_Info;						//CCD设备、车辆静态信息
	CCD_Status Dynamtic_Info;						//状态信息 动态信息
	Vehicle_Sequence Sequence;					//排序信息
};

