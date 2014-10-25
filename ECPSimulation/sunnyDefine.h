/*
这个文件是用来建造4230协议的结构体 也包括一下
*/
#pragma pack()
#define BigEndian 1
#define CAR_NUM 20 //这个后面可能去掉,在其他地方定义 xuyang
#pragma once
#include "sunnyOpenLDVdefinitions.h"
using namespace ldv;

//16位数据存储方式尚未确定大端小端
typedef union
{
    Byte a[2];
private:
    Word Value;
public:
    Word get()
    {
        WordUnion tempUnion;
        tempUnion.Value = Value;
        return tempUnion.Value;
    }
    void set( Word GetValue )
    {
        WordUnion tempUnion1;
        tempUnion1.Value = GetValue;
        Value = tempUnion1.Value;
    }
} WordUnion;

//message code 消息的枚举定义，消息长度（除去报文ID号以及版本号，异常报文除去附加信息）
typedef enum
{
    MSG_CAR_STATIC_INFO								= 0,		length_CAR_STATIC_INFO								= 32,
    MSG_LOCOMOTIVE_STATIC_INFO				= 1,		length_LOCOMOTIVE_STATIC_INFO				= 28,
    MSG_QUERY_VEHICLE_STATIC_INFO			= 2,		length_QUERY_VEHICLE_STATIC_INFO		= 0,
    MSG_DEVICE_INFO_CONTROL_QUERY			= 3,		length_DEVICE_INFO_CONTROL_QUERY		= 2,
    MSG_ASSIGN_NODE_ID									= 4,		length_ASSIGN_NODE_ID								= 2,
    MSG_EOT_DEVICE_INFO								= 5,		length_EOT_DEVICE_INFO								= 22,
    MSG_TRAIL_HEU_DEVICE_INFO					= 6,		length_TRAIL_HEU_DEVICE_INFO					= 31,
    MSG_CCD_DEVICE_INFO								= 7,		length_CCD_DEVICE_INFO								= 35,
    MSG_PSC_DEVICE_INFO								= 8,		length_PSC_DEVICE_INFO								= 31,
    MSG_TRAIN_DYNAMIC_CONFIGURATION	= 9,		length_TRAIN_DYNAMIC_CONFIGURATION	= 14,
    MSG_CCD_DYNAMIC_CONFIGURATION		= 10,		length_CCD_DYNAMIC_CONFIGURATION		= 2,
    MSG_PSC_DYNAMIC_CONFIGURATION			= 11,		length_PSC_DYNAMIC_CONFIGURATION		= 1,
    MSG_DEVICE_COMPATIBILITY_COMMAND	= 12,		length_DEVICE_COMPATIBILITY_COMMAND	= 2,
    MSG_HEU_BEACON											= 13,		length_HEU_BEACON										= 5,
    MSG_DEVICE_STATUS_QUERY						= 14,		length_DEVICE_STATUS_QUERY					= 1,
    MSG_CCD_STATUS_RESPONSE						= 15,		length_CCD_STATUS_RESPONSE					= 8,
    MSG_PSC_STATUS_RESPONSE						= 16,		length_PSC_STATUS_RESPONSE					= 6,
    MSG_TRAIL_HEU_STATUS_RESPONSE			= 17,		length_TRAIL_HEU_STATUS_RESPONSE		= 3,
    MSG_EOT_BEACON											= 18,		length_EOT_BEACON										= 5,
    MSG_TRAIN_SEQUENCING_COMMAND			= 19,		length_TRAIN_SEQUENCING_COMMAND		= 2,
    MSG_VEHICLE_SEQUENCE_COMMAND			= 20,		length_VEHICLE_SEQUENCE_COMMAND		= 3,
    MSG_VEHICLE_SEQUENCE_STATUS				= 21,		length_VEHICLE_SEQUENCE_STATUS			= 1,
    MSG_VEHICLE_SEQUENCE_INFO_QUERY		= 22,		length_VEHICLE_SEQUENCE_INFO_QUERY	= 3,
    MSG_VEHICLE_SEQUENCE_INFO					= 23,		length_VEHICLE_SEQUENCE_INFO				= 7,
    MSG_TRAIN_STATUS_DATA							= 24,		length_TRAIN_STATUS_DATA						= 5,
    MSG_CRITICAL_EXCEPTION							= 25,		length_CRITICAL_EXCEPTION						= 8,
    MSG_NORMAL_EXCEPTION							= 26,		length_NORMAL_EXCEPTION							= 21,
    MSG_EXCEPTION_CLEARANCE						= 27,		length_EXCEPTION_CLEARANCE						= 20,
    MSG_EXCEPTION_UPDATE_REQUEST			= 28,		length_EXCEPTION_UPDATE_REQUEST			= 2,
    MSG_EXCEPTION_UPDATE								= 29,		length_EXCEPTION_UPDATE							= 8,//没有异常描述
    MSG_EXCEPTION_QUERY								= 30,		length_EXCEPTION_QUERY								= 4,
    MSG_DEVICE_ECHO_QUERY1							= 39,		length_DEVICE_ECHO_QUERY1						= 0,
    MSG_DEVICE_ECHO_QUERY2							= 40,		length_DEVICE_ECHO_QUERY2						= 0,
} s4230MSG_ID_length;



//message 的头帧，ID号与报文版本号
typedef struct
{
    Byte id;
    Byte version;
} S4230Header;

//空重设备类型 ID0
typedef enum
{
    UNEQUIPPED,
    MACHANICAL_DEVICE,
    ELECTRONIC_DEVICE,
} EMPTY_LOAD_DEVICE_TYPE;

//车辆排序方向 ID0
typedef enum
{
    LOAD_AT_END_B,
    LOAD_AT_END_A,
} SEQUENCE_ORIENTATION_0;

//机车排序方向 ID 1
typedef enum
{
    LOAD_AT_END_LONG,
    LOAD_AT_END_SHORT,
} SEQUENCE_ORIENTATION_1;

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
} DEVICE_TYPE;

//电源模式
typedef enum
{
    NORMAL_POWER_MODE	= 0,
    LOW_POWER_MODE		= 1,
} TRAIN_POWER_MODE;

//逻辑控制
typedef enum
{
    RESET_CRITICAL_FAULTS				= 1,
    RESET_CRC_ERROR_COUNT			= 2,
    RESET_COMPATIBILITY_STATE	= 4,
} AULT_LOGIC_CONTROL;

//电源指令
typedef enum
{
    DISABLE_OUTPUT								= 0,
    ENABLE_OUTPUT_AS_PRIMARY			= 1,
    ENABLE_OUTPUT_AS_SECONDARY	= 2,
    ENABLE_LOW_VOLTAGE_OUTPUT		= 3,
    RESET_PSC_EXCEPTIONS					= 4,
} POWER_SUPPLY_COMMAND ;

//兼容指令
typedef enum
{
    CLEAR_EXCEPTION_AND_RUN	= 0,
    DEVICE_CUT_OUT						= 1,
} DEVICE_COMPATIBILITY_COMMAND;

//CCD的状态
typedef enum
{
    CCD_CUT_IN		= 0,
    CCD_CUT_OUT	= 1,
} CCD_STATUS;

//设备指令
typedef enum
{
    UNLOCK						= 0,
    LOCK							= 1,
    SEND_DEVICE_INFO	= 2,
} DEVICE_COMMAND;

//设备ID
typedef enum
{
    NYAB			= 1,
    EMD				= 2,
    WABTEC		= 3,
    ZEFTRON		= 4,
    GETS_GS		= 5,
    CSRW			= 6,
} MANUFACTURER_ID;

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
    //EMPTY_COMMAND_1					= 0x00,
    LOADED_COMMAND_1						= 0x20,
    //EMPTY_COMMAND_2					= 0x00,
    LOADED_COMMAND_2					= 0x40,
} OPERATING_MODE;

//CCD状态
typedef enum
{
    CUT_IN											= 0,
    CUT_OUT										= 1,
    HEU_CUTOUT_COMMANDED			= 2,
    ISOLATED_CRITICAL_LOSS			= 4,
    CCD_FAULT_DETECTED					= 8,
    CCD_INOPERATIVE							= 0x10,
    CRC_ERROR_COUNT_THRESHOLD	= 0x20,
    CCD_LOW_BATTERY						= 0x40,
    CCD_LOW_RESERVOIR					= 0x80,
} CCD_STATUS_ENUM;

//一般异常状态
typedef enum
{
    NORMAL_REPORT			= 0,
    RESPONSE_TO_QUERY	= 1,
} CCD_NORMAL_EXCEPTION_STATUS;

//异常描述
typedef enum
{
    CODE_LOSS_OF_HEU_BEACON					= 10000,	length_LOSS_OF_HEU_BEACON					= 0,
    CODE_LOSS_OF_BRAKE_PIPE_PRESSURE	= 10001,	length_LOSS_OF_BRAKE_PIPE_PRESSURE	= 2,
    CODE_CRITICAL_LOSS_RELAY					= 10002,	length_CRITICAL_LOSS_RELAY					= 12,
    CODE_LOW_BRAKE_PIPE_PRESSURE			= 10010,	length_LOW_BRAKE_PIPE_PRESSURE			= 2,
    CODE_LOW_RESERVOIR								= 10011,	length_LOW_RESERVOIR								= 3,
    CODE_LOW_TRAINLINE_VOLTAGE			= 10012,	length_LOW_TRAINLINE_VOLTAGE			= 1,
    CODE_HIGH_TRAINLINE_VOLTAGE			= 10013,	length_HIGH_TRAINLINE_VOLTAGE			= 1,
    CODE_TRAINLINE_SHORT_CIRCUIT			= 10014,	length_TRAINLINE_SHORT_CIRCUIT			= 2,
    CODE_LOW_INPUT_VOLTAGE					= 10015,	length_LOW_INPUT_VOLTAGE					= 3,
    CODE_LOW_BATTERY									= 10016,	length_LOW_BATTERY									= 1,
    CODE_INCORRECT_BC_PRESSURE				= 10017,	length_INCORRECT_BC_PRESSURE				= 5,
    CODE_CAR_ID_FAULT									= 10018,	length_CAR_ID_FAULT								= 1,
    CODE_LOVOMOTIVE_ID_FAULT					= 10019,	length_LOVOMOTIVE_ID_FAULT				= 1,
    CODE_CCD_CUTOUT									= 10020,	length_CCD_CUTOUT									= 1,
    CODE_COMPATIBILITY_ERROR					= 10021,	length_COMPATIBILITY_ERROR					= 4,
    CODE_MULTIPLE_LEAD_HEUs					= 10022,	length_MULTIPLE_LEAD_HEUs					= 0,
    CODE_PSC_ENABLE_FAULT						= 10023,	length_PSC_ENABLE_FAULT						= 2,
    HIGHEST_LEVEL_EXCEPTION					= 65535,
} EXCEPTION_CODE_length;

typedef enum
{
    LOSS_OF_HEU_BEACON = 1 << 0,
    LOSS_OF_BRAKE_PIPE_PRESSURE = 1 << 1,
    CRITICAL_LOSS_RELAY = 1 << 2,
    LOW_RESERVOIR = 1 << 3,
    LOW_BATTERY = 1 << 4,
    INCORRECT_BC_PRESSURE = 1 << 5,
    CAR_ID_FAULT = 1 << 6,
    CCD_CUTOUT = 1 << 7,
    CCD_COMPATIBILITY_ERROR = 1 << 8,
} CCD_EXCEPTION_FLAGS;

//异常请求类型
typedef enum
{
    SEND_ACTIVE_EXCEPTION_ONLY = 0,
    SEND_ACTIVE_CLEAR,
    SEND_HIGHEST_PRIORITY_EXCEPTION_CLEAR,
    SEND_HIGHEST_PRIORITY_EXCEPTION,
} EXCEPTION_REQUEST_TYPE;

/*车辆静态信息 msg_id==0, LEN==34*/
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
} Msg_sCar_Static_Info;

/*机车静态信息 msg_id==1, LEN==30*/
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
} Msg_sLocomotive_Static_Info;

/*查询车辆静态信息 msg_id==2, LEN==2*/
//没有数据

/*设备信息控制/查询 msg_id==3, LEN==4*/
typedef struct
{
    Byte Command;
    Byte Randomizing_Interval;
} Msg_sDevice_Info_Control_Query;

/*分配节点ID msg_id==4, LEN==4*/
typedef struct
{
    Byte Subnet;
    Byte Node_ID;
} Msg_sAssign_Node_ID;

/*设备信息（EOT） msg_id==5, LEN==24*/
typedef struct
{
    Byte Manufacturer_ID;
    Byte EOT_Identification_Number[11];
    Byte Unique_ID[6];
    Byte Manufacturer_Revision_Level;
    Byte S_4200_Compatibility_Version;
    Byte S_4230_Compatibility_Version;
    Byte Device_Characteristics;
} Msg_sEOT_Device_Info;

/*设备信息（HEU） msg_id==6, LEN==33*/
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
} Msg_sTrail_HEU_Device_Info;

/*设备信息（CCD） msg_id==7, LEN==37*/
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
} Msg_sCCD_Device_Info;

/*设备信息（PSC） msg_id==8, LEN==33*/
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
} Msg_sPSC_Device_Info ;

/*列车动态配置 msg_id==9, LEN==16*/
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
} Msg_sTrain_Dynamic_Configuration;

/*CCD动态配置 msg_id==10, LEN==4*/
typedef struct
{
    Byte CCD_Status;
    Byte Empty_Load_Status;
} Msg_sCCD_Dynamic_Configuration;

/*PSC动态配置 msg_id==11, LEN==3*/
typedef struct
{
    Byte Power_Supply_Command;
} Msg_sPSC_Dynamic_Configuration;

/*设备兼容性命令 msg_id==12, LEN==4*/
typedef struct
{
    Byte Device_Compatibility_Command;
    Byte Device_Type;
} Msg_sDevice_Compatibility_Command;

/*HEU信标 msg_id==13, LEN==7*/
typedef struct
{
    Byte Operating_Mode;
    Byte Train_Brake_Command;
    Byte Subnet;
    Byte Node;
    Byte Train_Speed;
} Msg_sHEU_Beacon;

/*设备状态查询 msg_id==14, LEN==3*/
typedef struct
{
    Byte Device_Type;
} Msg_sDevice_Status_Query;

/*CCD状态响应 msg_id==15, LEN==10*/
typedef struct
{
    Byte Status;
    Byte Brake_Pipe_Pressure;
    Byte Reservoir_Pressure;
    Byte Brake_Cylinder_Pressure;
    Byte Percent_Brake_Applied;
    Byte Car_Load;
    WordUnion Highest_Priority_Active_Exception;
} Msg_sCCD_Status_Response;

/*PSC状态响应 msg_id==16, LEN==8*/
typedef struct
{
    Byte Status;
    Byte Trainline_Voltage;
    Byte Output_Current;
    Byte Input_Voltage;
    WordUnion Highest_Priority_Active_Exception;
} Msg_sPSC_Status_Response;

/*辅机HEU状态响应 msg_id==17, LEN==5*/
typedef struct
{
    Byte Status;
    WordUnion Highest_Priority_Active_Exception;
} Msg_sHEU_Trail_Status_Response;

/*EOT信标 msg_id==18, LEN==7*/
typedef struct
{
    Byte Status;
    Byte Brake_Pipe_Pressure;
    Byte Battery_Voltage;
    Byte Trainline_Voltage;
    Byte Aux_Status;
} Msg_sEOT_Beacon;

/*列车排序命令 msg_id==19, LEN==4*/
typedef struct
{
    Byte Sequencing_Command;
    Byte Sequencing_Status;
} Msg_sTrain_Sequencing_Command;

/*车辆排序命令 msg_id==20, LEN==5*/
typedef struct
{
    Byte Sequence_Command;
    WordUnion Vehicle_Position;
} Msg_sVehicle_Sequence_Command;

/*车辆排序状态 msg_id==21, LEN==3*/
typedef struct
{
    Byte Sequence_Status;
} Msg_sVehicle_Sequence_Status;

/*车辆排序状态查询 msg_id==22, LEN==5*/
typedef struct
{
    Byte Query_Command;
    WordUnion Number_Of_Vehicles;
} Msg_sVehicle_Sequence_Info_Query;

/*车辆排序信息 msg_id==23, LEN==9*/
typedef struct
{
    Byte Vehicle_Sequence_State;
    Byte Sequencing_Flags;
    Byte Vehicle_Orientation;
    WordUnion Pulse_Count;
    WordUnion Vehicle_Position;
} Msg_sVehicle_Sequence_Info;

/*列车状态数据 msg_id==24, LEN==7*/
typedef struct
{
    Byte Train_Brake_Command_Source;
    Byte HEU_Operational_State;
    Byte Percent_Of_Operable_Brakes;
    WordUnion Total_Potentially_Operative_Brakes;
} Msg_sTrain_Status_Data;

/*紧急异常 msg_id==25, LEN==10 to 22*/
typedef struct
{
    WordUnion Exception_Code;
    Byte Unique_ID[6];
    Byte Supporting_Data[12];
} Msg_sCritical_Exception;

/*一般异常 msg_id==26, LEN==23 to 35*/
typedef struct
{
    WordUnion Exception_Code;
    Byte Unique_ID[6];
    Byte Vehicle_Reporting_Mark[11];
    Byte Exception_Status;
    Byte Supporting_Data_Version;
    Byte Supporting_Data[12];
} Msg_sNormal_Exception;

/*异常清除 msg_id==27, LEN==22*/
typedef struct
{
    WordUnion Exception_Code;
    Byte Unique_ID[6];
    Byte Vehicle_Reporting_Mark[11];
    Byte Exception_Status;
} Msg_sException_Clear;

/*异常修改请求 msg_id==28, LEN==4*/
typedef struct
{
    WordUnion Exception_Code;
} Msg_sException_Update_Request;

/*异常修改 msg_id==29, LEN==10 to 33*/
typedef struct
{
    WordUnion Exception_Code;
    Byte Display_Priority;
    Byte Exception_Description;
} Msg_sException_Update;

/*异常查询 msg_id==30, LEN==6*/
typedef struct
{
    Byte Exception_Request_Type;
    WordUnion Exception_Code;
    Byte Device_Type;
} Msg_sException_Query;

//车辆的静态信息  id==0    Car Static Info(0,0,LEN=34)
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
} Car_Static_Info;

// 包括车辆静态信息，CCD设备信息
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
    Byte Unique_ID[6];
    Byte Manufacturer_Revision_Level;
    Byte S_4200_Compatibility_Version;
    Byte S_4230_Compatibility_Version;
    Byte Device_Characteristics;
    Byte Operable_Brakes_Controlled;
} CCD_Car_Info;

//节点网络信息  id==4  4  id=7  Neuron ID
typedef struct
{
    bool isAssignedFlag;
    Byte Subnet;
    Byte Node;
    Byte Neuron_ID[6];
} Node_Information;

//CCD  的状态信息   CCD Status Response(0,15)
typedef struct
{
    Byte Car_Status;
    Byte Brake_Pipe_Pressure;
    Byte Reservoir_Pressure;
    Byte Brake_Cylinder_Pressure;
    Byte Percent_Brake_Applied;
    Byte Car_Load;
    WordUnion Highest_Priority_Active_Exception;
} CCD_Status;

//CCD异常标志位
typedef struct
{
    int Report_Flags;
    int Clear_Flags;
} CCD_Exception_Flags;

//异常附加信息、异常码
typedef struct
{
    WordUnion Exception_Code;
    Byte Supporting_Data_Version;
    Byte Supporting_Data_Length;
    Byte Supporting_Data[12];
} CCD_Exception_Detail;

//排序信息
typedef struct
{
    Byte Status;
    Byte Count_State;
    Byte Sequencing_Flag;
    WordUnion Pulse_Count;
    WordUnion Position;
} Vehicle_Sequence;

////CCD自己存储的信息
//typedef struct
//{
//	Byte  Lock_Status;
//	CCD_Status Status;
//	CCD_Car_Info Device_Info;
//	Node_Information Node_Info;
//	CCD_Exception_Flags Exception_Flags;
//	CCD_Exception_Detail Exception_Detail;
//}CCD_Info;