/*
这个文件是用来建造4230协议的结构体 也包括一下
*/
#pragma pack()
#define BigEndian 1
#pragma once
#include "sunnyOpenLDVdefinitions.h"
using namespace ldv;

typedef union//尚未确定大端小端
{
	Byte a[2];
private:
	Word Value;
public:
	Word get()
	{
		WordUnion tempUnion;
		tempUnion.Value=Value;
		return tempUnion.Value;
	}
	void set(Word GetValue)
	{
		WordUnion tempUnion1;
		tempUnion1.Value=GetValue;
		Value=tempUnion1.Value;
	}
}WordUnion;
#define CAR_NUM 20 //这个后面可能去掉,在其他地方定义 xuyang

//message code 消息的枚举定义
typedef enum
{
	MSG_CAR_STATIC_INFO								= 0,
	MSG_LOCOMOTIVE_STATIC_INFO				= 1,
	MSG_QUERY_VEHICLE_STATIC_INFO			= 2,
	MSG_DEVICE_INFO_CONTROL_QUERY			= 3,
	MSG_ASSIGN_NODE_ID									= 4,
	MSG_EOT_DEVICE_INFO								= 5,
	MSG_TRAIL_HEU_DEVICE_INFO					= 6,
	MSG_CCD_DEVICE_INFO								= 7,
	MSG_PSC_DEVICE_INFO								= 8,
	MSG_TRAIN_DYNAMIC_CONFIGURATION	= 9,
	MSG_CCD_DYNAMIC_CONFIGURATION		= 10,
	MSG_PSC_DYNAMIC_CONFIGURATION			= 11,
	MSG_DEVICE_COMPATIBILITY_COMMAND	= 12,
	MSG_HEU_BEACON											= 13,
	MSG_DEVICE_STATUS_QUERY						= 14,
	MSG_CCD_STATUS_RESPONSE						= 15,
	MSG_PSC_STATUS_RESPONSE						= 16,
	MSG_TRAIL_HEU_STATUS_RESPONSE			= 17,
	MSG_EOT_BEACON											= 18,
	MSG_TRAIN_SEQUENCING_COMMAND			= 19,
	MSG_VEHICLE_SEQUENCE_COMMAND			= 20,
	MSG_VEHICLE_SEQUENCE_STATUS				= 21,
	MSG_VEHICLE_SEQUENCE_INFO_QUERY		= 22,
	MSG_VEHICLE_SEQUENCE_INFO					= 23,
	MSG_TRAIN_STATUS_DATA							= 24,
	MSG_CRITICAL_EXCEPTION							= 25,
	MSG_NORMAL_EXCEPTION							= 26,
	MSG_EXCEPTION_CLEARANCE						= 27,
	MSG_EXCEPTION_UPDATE_REQUEST			= 28,
	MSG_EXCEPTION_UPDATE								= 29,
	MSG_EXCEPTION_QUERY								= 30,
	MSG_DEVICE_ECHO_QUERY1							= 39,
	MSG_DEVICE_ECHO_QUERY2							= 40,
}s4230ID;


//message 的头帧
typedef struct  
{
	Byte id;
	Byte version;
}S4230Header;

//空重设备类型 ID0
typedef enum
{
	UNEQUIPPED,
	MACHANICAL_DEVICE,
	ELECTRONIC_DEVICE,
}EMPTY_LOAD_DEVICE_TYPE;

//排序方向 ID0
typedef enum
{
	LOAD_AT_END_B,
	LOAD_AT_END_A,
}SEQUENCE_ORIENTATION_0;

//排序方向 ID 1
typedef enum
{
	LOAD_AT_END_LONG,
	LOAD_AT_END_SHORT,
}SEQUENCE_ORIENTATION_1;

//设备类型
typedef  enum
{
	ALL							= 0,
	CCD							= 1,
	LCM							= 2,
	EOT							= 3,
	HEU							= 4,
	PSC							= 5,
	EVENT_RECORDER	= 6,
}Device_type;

//电源模型
typedef enum
{
	NORMAL_POWER_MODE	= 0,
	LOW_POWER_MODE		= 1,
}TRAIN_POWER_MODE;

//逻辑控制
typedef enum
{
	RESET_CRITICAL_FAULTS				= 1, 
	RESET_CRC_ERROR_COUNT			= 2,
	RESET_COMPATIBILITY_STATE	= 4,
}AULT_LOGIC_CONTROL;

//电源指令
typedef enum
{
	DISABLE_OUTPUT								= 0,
	ENABLE_OUTPUT_AS_PRIMARY			= 1,
	ENABLE_OUTPUT_AS_SECONDARY	= 2,
	ENABLE_LOW_VOLTAGE_OUTPUT		= 3,
	RESET_PSC_EXCEPTIONS					= 4,
}POWER_SUPPLY_COMMAND ;

//兼容指令
typedef enum
{
	CLEAR_EXCEPTION_AND_RUN	= 0,
	DEVICE_CUT_OUT						= 1,
}DEVICE_COMPATIBILITY_COMMAND;

//CCD的状态
typedef enum
{
	CCD_CUT_IN		= 0,
	CCD_CUT_OUT	= 1,
}CCD_STATUS;
//设备指令
typedef enum
{
	UNLOCK						= 0,
	LOCK							= 1,
	SEND_DEVICE_INFO	= 2,	
}Device_COMMAND;

//设备id
typedef enum
{
	NYAB			= 1,
	EMD				= 2,
	WABTEC		= 3, 
	ZEFTRON		= 4,
	GETS_GS		= 5,
	CSRW			= 6,
}MANUFACTURER_ID;

//操作模式
typedef enum
{
	RUN													= 0,
	INITIALIZATION							= 1,
	SWITCH											= 2,
	CUTOUT											= 3,
	POWER_ON										= 8,
	//POWER_OFF									= 0;
	QUIET_TRAINLINE_COMMANDED	= 0x10,
	//EMPTY_COMMAND_1         =0x00,
	LOADED_COMMAND_1          =0x20,
	//EMPTY_COMMAND_2         =0x00,
	LOADED_COMMAND_2          =0x40,		
}OPERATING_MODE;

//CCD状态
typedef enum
{
	CUT_IN                           =0,
	CUT_OUT                          =1,
	HEU_CUTOUT_COMMANDED             =2,
	ISOLATED_CRITICAL_LOSS           =4,
	CCD_FAULT_DETECTED               =8,
	CCD_INOPERATIVE                  =0x10,
	CRC_ERROR_COUNT_THRESHOLD        =0x20,
	CCD_LOW_BATTERY                  =0x40,
	CCD_LOW_RESERVOIR                =0x80,
}CCD_STATUS_ENUM;

//一般异常状态
typedef enum
{
	NORMAL_REPORT=0,
	RESPONSE_TO_QUERY=1,
}CCD_NORMAL_EXCEPTION_STATUS;

//异常标志位处理
typedef enum
{
	RESET=false,
	SET=true,
}FLAG_BIT;
//异常描述
typedef enum
{
	LOSS_OF_HEU_BEACON=1,
	LOSS_OF_BRAKE_PIPE_PRESSURE,
	CRITICAL_LOSS_RELAY,
	LOW_RESERVOIR,
	LOW_BATTERY,
	INCORRECT_BC_PRESSURE,
	CAR_ID_FAULT,
	CCD_CUTOUT,
}CCD_EXCEPTION_DESCRIPTION;

//异常请求类型
typedef enum
{
	SEND_ACTIVE_EXCEPTION_ONLY=0,
	SEND_ACTIVE_CLEAR,
	SEND_HIGHEST_PRIORITY_EXCEPTION_CLEAR,
	SEND_HIGHEST_PRIORITY_EXCEPTION,
}EXCEPTION_REQUEST_TYPE;

typedef enum
{
	ACTIVE=0,
	CLEAR,
}EXCEPTION_ACTIVE_CLEAR;



//车辆的静态信息  msg_id==0    Car Static Info(0,0,LEN=34)
typedef struct
{ 
	Byte Car_ID_Modules_Manufacturer;
	Byte Reporting_Mark[11];
	Byte Car_Type[4];
	WordUnion Car_Length;
	Byte Brakes_Controlled;
	Byte Num_Axles;
	WordUnion Empty_Weight;
	WordUnion Loaded_Weight;
	WordUnion Break_Constant;
	WordUnion Reservoir_Constant;
	Byte Net_Braking_Ratio_Default;
	Byte Min_Service_Pressure;
	Byte Empty_Load_Device_Type;
	Byte Sequencing_Orientation;
}Msg_sCar_Static_Info;



//静态信息  msg_id==1    
typedef struct  
{ 
	Byte Locomotive;
	Byte Reporting_Mark[11];
	Byte Locomotive_Type[4];
	WordUnion Locomotive_Length;
	Byte Num_Axles;
	WordUnion Empty_Weight;
	WordUnion Nominal_Weight;
	WordUnion Break_Constant;
	Byte Nominal_Wheel_Diameter;
	Byte Net_Braking_Ratio_Default;
	Byte BP_Pressure_Setpoint_Default;
	Byte Suppression_Application;
	Byte Low_Battery_Fault_Threshold;
	Byte Low_Battery_Fault_Clear_Threshold;
	Byte Sequencing_Orientation;
}Msg_slocomotive_Static_Info;

//msg id=2  没有成员数据

// msg_id=3
typedef struct  
{
	Byte Command;
	Byte Randomizing_Interval;
}Msg_sDevice_Info_Control_Query;


//msg id=4
typedef struct  
{
	Byte Subnet;
	Byte Node_ID;
}Msg_sAssign_Node_ID;


//msg id=5
typedef struct  
{
	Byte Manufacturer_ID;
	Byte EOT_Identification_Number[11];
	Byte Unique_ID[6];
	Byte Manufacturer_Revision_Level;
	Byte S_4200_Compatibility_Version;
	Byte S_4230_Compatibility_Version;
	Byte Device_Characteristics;
}Msg_sEOT_Device_Info;

//msg id=6
typedef struct  
{
	Byte Manufacturer_ID;
	Byte Reporting_Mark[11];
	Byte Unique_ID[6];
	Byte Manufacturer_Revision_Level;
	Byte S_4200_Compatibility_Version;
	Byte S_4230_Compatibility_Version;
	Byte Device_Characteristics;
	Byte Vehicle_Type[4];
	WordUnion Vehicle_Length;
	WordUnion Vehicle_Weight;
	Byte Num_Axles;
}Msg_sTrail_HEU_Device_Info;

//id7
typedef struct
{
	Byte Manufacturer_ID;
	Byte Reporting_Mark[11];
	Byte Unique_ID[6];
	Byte Manufacturer_Revision_Level;
	Byte S_4200_Compatibility_Version;
	Byte S_4230_Compatibility_Version;
	Byte Device_Characteristics;
	Byte Vehicle_Type[4];
	WordUnion Vehicle_Length;
	WordUnion Empty_Weight;
	WordUnion Loaded_Weight;
	Byte Num_Axles;
	Byte Operable_Brakes_Controlled;
	Byte Empty_Load_Device_Type;
}Msg_sCCD_Device_Info;


//msg id=8
typedef struct  
{
	Byte Manufacturer_ID;
	Byte Reporting_Mark[11];
	Byte Unique_ID[6];
	Byte Manufacturer_Revision_Level;
	Byte S_4200_Compatibility_Version;
	Byte S_4230_Compatibility_Version;
	Byte Device_Characteristics;
	Byte Vehicle_Type[4];
	WordUnion Vehicle_Length;
	WordUnion Vehicle_Weight;
	Byte Num_Axles;
}Msg_sPSC_Device_Info ;


//msg id=9
typedef struct  
{
	Byte S_4200_Rev_Compatibility[4];
	Byte S_4230_Rev_Compatibility[4];
	Byte BP_Pressure_Setpoint;
	Byte Net_Braking_Ratio;
	Byte Spare;
	Byte Train_Power_Mode;
	Byte Fault_Logic_Control;
	Byte CRC_Error_Threshold;
}Msg_sTrain_Dynamic_Configuration;

//msg id=10
typedef struct  
{
	Byte CCD_Status;
	Byte Empty_Load_Status;
}Msg_sCCD_Dynamic_Configuration;


//msg id=11
typedef struct  
{
	Byte Power_Supply_Command;
}Msg_sPSC_Dynamic_Configuration;

//msg id=12
typedef struct  
{
	Byte device_compatibility_command;
	Byte device_type;
}Msg_sDevice_Compatibility_Command;


//msg id=13
typedef struct  
{
	Byte Operating_Mode;
	Byte Train_Brake_Command;
	Byte Subnet;
	Byte Node;
	Byte Train_Speed;	
}Msg_sHEU_Beacon;

//msg id=14
typedef struct  
{
	Byte Device_Type;
}Msg_sDevice_Status_Query;

//msg id=15
typedef struct  
{
	Byte Status;
	Byte Brake_Pipe_Pressure;
	Byte Reservoir_Pressure;
	Byte Brake_Cylinder_Pressure;
	Byte Percent_Brake_Applied;
	Byte Car_Load;
	WordUnion Highest_Priority_Active_Exception;
}Msg_sCCD_Status_Response;

/*
* to do  还有    16-24 的报文结构体没有编写
*/
/*
//msg_id 16
typedef struct
{
	Byte Status;
	Byte Power_Control_Status;
	Byte Power_Supply_Availability;
	Byte CRC_Error_Count;
	Byte Low_Input_Voltage;
	Byte Error;
	Byte Trainline_Voltage;
	Byte Output_Current;
	Byte Input_Voltage;
	WordUnion Highest_Priority_Active_Exception;
}Msg_sPSC_Status_Response;


typedef struct  
{
	Byte Status;
	WordUnion Highest_Priority_Active_Exception;
}Msg_sTrail_Heu_Status_Response;

*/
//msg_25
typedef struct
{
	WordUnion Exception_Code;
	Byte Unique_ID[6];
	Byte Supporting_Data[12];
}Msg_sCritical_Exception;

//msg_26
typedef struct
{
	WordUnion Exception_Code;
	Byte Unique_ID[6];
	Byte Vehicle_Reporting_Mark[11];
	Byte Exception_Status;
	Byte Supporting_Data_Version;
	Byte Supporting_Data[12];
}Msg_sNormal_Exception;

//msg_27
typedef struct
{
	WordUnion Exception_Code;
	Byte Unique_ID[6];
	Byte Vehicle_Reporting_Mark[11];
	Byte Exception_Status;
}Msg_sException_Clear;

//msg_28
typedef struct
{
	WordUnion Exception_Code;
}Msg_sException_Update_Request;

//msg_29
typedef struct
{
	WordUnion Exception_Code;
	Byte Display_Priority;
	Byte Exception_Description;
}Msg_sException_Update;

//msg_30
typedef struct
{
	Byte Exception_Request_Type;
	WordUnion Exception_Code;
	Byte Device_Type;
}Msg_sException_Query;








//车辆的静态信息  id==0    Car Static Info(0,0,LEN=34)
typedef struct  
{ 
	Byte   car_id_modules_manufacturer;
	Byte   reporting_mark[11];
	Byte   car_type[4];
	WordUnion  car_length;
	Byte   brakes_controlled;
	Byte   num_axles;
	WordUnion    empty_weight;
	WordUnion   loaded_weight;
	WordUnion   break_constant;
	WordUnion   reservoir_constant;
	Byte   net_braking_ratio_default;
	Byte   min_service_pressure;
	Byte   empty_load_device_type;
	Byte   sequencing_orientation;
}Car_Static_Info;


//设备信息 除了设备静态信息  id==7   CCD Device Info(0,7)  37
typedef struct 
{
	Byte manufacturer_revision_level;
	Byte s_4200_compatibility_version;
	Byte s_4230_compatibility_version;
	Byte device_characteristics;
	Car_Static_Info static_info;
}CCD_Device_Info;

//节点网络信息  id==4  4  id=7  Neuron ID
typedef struct 
{
	bool isAssignedFlag;
	Byte subnet;
	Byte node_id;
	Byte neuron_id[6];
}Node_information;
//CCD  的状态信息   CCD Status Response(0,15)
typedef struct {
	Byte brake_pipe_pressure;
	Byte reservoir_pressure;
	Byte brake_cylinder_pressure;
	Byte percent_brake_applied;
	Byte car_load;
	Byte car_status;
	WordUnion highest_priority_active_exception;	
}Status;

//异常报告标志位
typedef struct
{
	bool Loss_of_HEU_Beacon;
	bool Loss_of_Brake_Pipe_Pressure;
	bool Critical_Loss_Relay;
	bool Low_Reservoir;
	bool Low_Battery;
	bool Incorrect_BC_Pressure;
	bool Car_ID_Fault;
	bool CCD_Cutout;
}Exception_Report_Flags;
//异常清除标志位
typedef struct
{
	bool Loss_of_HEU_Beacon;
	bool Loss_of_Brake_Pipe_Pressure;
	bool Critical_Loss_Relay;
	bool Low_Reservoir;
	bool Low_Battery;
	bool Incorrect_BC_Pressure;
	bool Car_ID_Fault;
	bool CCD_Cutout;
}Exception_Clear_Flags;
//CCD异常标志位
typedef struct
{
	Exception_Report_Flags Report_Flags;
	Exception_Clear_Flags Clear_Flags;
}CCD_Exception_Flags;

typedef struct
{
	int Exception_Code;
	Byte Supporting_Data_Length;
	Byte Supporting_Data[12];
}Exception_Detail;
//CCD自己存储的信息
typedef struct  
{
	Byte  lock_status;
	Status CCD_status;
	CCD_Device_Info CCD_device_info;
	Node_information node_infomation;
	CCD_Exception_Flags Exception_Flags;
	Exception_Detail CCD_Exception_Detail;
}CCD_INFO;