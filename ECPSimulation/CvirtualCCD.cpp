#include "StdAfx.h"
#include "CvirtualCCD.h"
#include "Util.h"
CUtil util;

CvirtualCCD::CvirtualCCD(void)
{
}


CvirtualCCD::~CvirtualCCD(void)
{
}

//报文组包函数
void CvirtualCCD::Send_Msg_by_ID(Byte msg_id,Byte msg_type,Byte msg_pri, Byte msg_ver)
{
	Byte length=util.get_Msg_length(msg_id);
	if (msg_id==MSG_CRITICAL_EXCEPTION||msg_id==MSG_NORMAL_EXCEPTION)
		length+=Exception_Detail.Supporting_Data_Length;
	Msg_Send_Buffer=new Byte[length];
	Byte *Addr;
	switch(msg_id)
	{
	case MSG_CAR_STATIC_INFO://0
		{
			Msg_sCar_Static_Info msg_send;
			memcpy(&msg_send,&Device_Info,length);
			Addr=(Byte*)&msg_send;
		}
		 break;
	case MSG_CCD_DEVICE_INFO:
		{
			Msg_sCCD_Device_Info msg_send;
			msg_send.Manufacturer_ID=Device_Info.Car_ID_Modules_Manufacturer;
			memcpy(msg_send.Reporting_Mark,Device_Info.Reporting_Mark,11);
			memcpy(msg_send.Unique_ID,Device_Info.Unique_ID,6);
			msg_send.Manufacturer_Revision_Level=Device_Info.Manufacturer_Revision_Level;
			msg_send.S_4200_Compatibility_Version=Device_Info.S_4200_Compatibility_Version;
			msg_send.S_4230_Compatibility_Version=Device_Info.S_4230_Compatibility_Version;
			msg_send.Device_Characteristics=Device_Info.Device_Characteristics;
			memcpy(msg_send.Vehicle_Type,Device_Info.Car_Type,4);
			msg_send.Vehicle_Length.set(Device_Info.Car_Length.get());
			msg_send.Empty_Weight.set(Device_Info.Empty_Weight.get());
			msg_send.Loaded_Weight.set(Device_Info.Loaded_Weight.get());
			msg_send.Num_Axles=Device_Info.Num_Axles;
			msg_send.Operable_Brakes_Controlled=Device_Info.Operable_Brakes_Controlled;
			msg_send.Empty_Load_Device_Type=Device_Info.Empty_Load_Device_Type;
			Addr=(Byte*)&msg_send;
		}
		break;
	case MSG_CCD_STATUS_RESPONSE:
		{
			Msg_sCCD_Status_Response msg_send;
			memcpy(&msg_send,&Dynamtic_Info,length);
			Addr=(Byte*)&msg_send;
		}
		break;
	case  MSG_VEHICLE_SEQUENCE_STATUS:
		{
			Msg_sVehicle_Sequence_Status msg_send;
			msg_send.Sequence_Status=Sequence.Status;
			Addr=(Byte*)&msg_send;
		}
		break;
	case MSG_VEHICLE_SEQUENCE_INFO:
		{
			Msg_sVehicle_Sequence_Info msg_send;
			msg_send.Vehicle_Sequence_State=Sequence.Count_State;
			msg_send.Sequencing_Flags=Sequence.Sequencing_Flag;
			msg_send.Vehicle_Orientation=Device_Info.Sequencing_Orientation;
			msg_send.Pulse_Count.set(Sequence.Pulse_Count.get());
			msg_send.Vehicle_Position.set(Sequence.Position.get());
			Addr=(Byte*)&msg_send;
		}
		break;
	case MSG_CRITICAL_EXCEPTION:
		{
			Msg_sCritical_Exception msg_send;
			msg_send.Exception_Code.set(Exception_Detail.Exception_Code.get());
			memcpy(msg_send.Unique_ID,Device_Info.Unique_ID,6);
			memcpy(msg_send.Supporting_Data,Exception_Detail.Supporting_Data,Exception_Detail.Supporting_Data_Length);
			Addr=(Byte*)&msg_send;
		}
		break;
	case MSG_NORMAL_EXCEPTION:
		{
			Msg_sNormal_Exception msg_send;
			msg_send.Exception_Code.set(Exception_Detail.Exception_Code.get());
			memcpy(msg_send.Unique_ID,Device_Info.Unique_ID,6);
			memcpy(msg_send.Vehicle_Reporting_Mark,Device_Info.Reporting_Mark,11);
			msg_send.Exception_Status=Send_Response;
			msg_send.Supporting_Data_Version=Exception_Detail.Supporting_Data_Version;
			memcpy(msg_send.Supporting_Data,Exception_Detail.Supporting_Data,Exception_Detail.Supporting_Data_Length);
			Addr=(Byte*)&msg_send;
		}
		break;
	case MSG_EXCEPTION_CLEARANCE:
		{
			Msg_sException_Clear msg_send;
			msg_send.Exception_Code.set(Exception_Detail.Exception_Code.get());
			memcpy(msg_send.Unique_ID,Device_Info.Unique_ID,6);
			memcpy(msg_send.Vehicle_Reporting_Mark,Device_Info.Reporting_Mark,11);
			msg_send.Exception_Status=Send_Response;
			Addr=(Byte*)&msg_send;
		}
		break;
	case MSG_EXCEPTION_UPDATE:
		{
			/*暂不处理*/
		}
		break;
	default:
		return;
	}
	memcpy(Msg_Send_Buffer,Addr,length);
}