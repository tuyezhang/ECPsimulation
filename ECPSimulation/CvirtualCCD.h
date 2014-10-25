#pragma once
#include "sunnyDefine.h"
#include "Util.h"
#include "Lon2S4230.h"
#include <Windows.h>
class CvirtualCCD
{
    public:
        CvirtualCCD( void );
        ~CvirtualCCD( void );
        int Send_Msg_by_ID( Byte msg_id, Byte msg_type, Byte msg_pri = NONPRIORITY, Byte msg_ver = 0 );
		unsigned int m_Elapse;
    public:
        Byte *Msg_Send_Buffer;
        CCD_Exception_Flags Exception_Flags;	//异常标志位
        CCD_Exception_Detail Exception_Detail;	//异常码，异常附加数据发送缓冲区
        Byte Send_Response;								//表示设备在需要发送报文时为主动发送还是回复，在某些时候用得到
        Byte Get_CCD_Subnet();
        Byte Get_CCD_Node();
        void  Set_CCD_Subnet( Byte subnet );
        void  Set_CCD_Node( Byte node );
        bool  Is_NID_Match( Byte * nid, Byte length );
        bool  Is_Subnet_Node( Byte sunbet, byte node );
        bool  Set_CCD_Lock( bool isLock );
        void Send_CCD_Info();
		void Send_CCD_Info(int randomizing_interval);
		void Set_CCD_Node_Information(int index);
		void Set_CCD_Car_Info(int index);
		void Set_CCD_Status(int index);
        //CCD内部信息
    private:						//所有的设备的状态和信息都是私有的，需要用响应的函数访问，修改
        Byte Lock_Status;										//开锁，锁闭状态
        Node_Information Node_Info;					//网络节点信息
        CCD_Car_Info Device_Info;						//CCD设备、车辆静态信息
        CCD_Status Dynamtic_Info;						//状态信息 动态信息
        Vehicle_Sequence Sequence;					//排序信息
        void Set_Msg_data_0( byte msg_ver, byte length ); //设置发送的0号报文数据
        void Set_Msg_data_7( byte msg_ver, byte length ); //设置发送的7号报文数据
        void Set_Msg_data_15( byte msg_ver, byte length ); //设置发送的15号报文数据
        void Set_Msg_data_21( byte msg_ver, byte length ); //设置发送的21号报文数据
        void Set_Msg_data_23( byte msg_ver, byte length ); //设置发送的23号报文数据
        void Set_Msg_data_25( byte msg_ver, byte length ); //设置发送的25号报文数据
        void Set_Msg_data_26( byte msg_ver, byte length ); //设置发送的26号报文数据
        void Set_Msg_data_27( byte msg_ver, byte length ); //设置发送的27号报文数据
		CUtil util;
		CLon2S4230 lonop;
		
		HANDLE m_hThread;
		static DWORD WINAPI ThreadFunc (LPVOID pParam);
};

