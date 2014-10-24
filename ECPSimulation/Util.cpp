#include "StdAfx.h"
#include "Util.h"


CUtil::CUtil(void)
{
}


CUtil::~CUtil(void)
{
}

Byte CUtil::get_Msg_length(Byte msg_id)
{
	switch(msg_id)
	{
	case MSG_CAR_STATIC_INFO:				return 34;
		break;
	case MSG_LOCOMOTIVE_STATIC_INFO:		return 30;
		break;
	case MSG_QUERY_VEHICLE_STATIC_INFO:	return 2;
		break;
	case MSG_DEVICE_INFO_CONTROL_QUERY:	return 4;
		break;
	case MSG_ASSIGN_NODE_ID:				return 4;
		break;
	case MSG_EOT_DEVICE_INFO:				return 24;
		break;
	case MSG_TRAIL_HEU_DEVICE_INFO:		return 33;
		break;
	case MSG_CCD_DEVICE_INFO:				return 37;
		break;
	case MSG_PSC_DEVICE_INFO:				return 33;
		break;
	case MSG_TRAIN_DYNAMIC_CONFIGURATION:	return 16;
		break;
	case MSG_CCD_DYNAMIC_CONFIGURATION:	return 4;
		break;
	case MSG_PSC_DYNAMIC_CONFIGURATION:	return 3;
		break;
	case MSG_DEVICE_COMPATIBILITY_COMMAND:return 4;
		break;
	case MSG_HEU_BEACON:					return 7;
		break;
	case MSG_DEVICE_STATUS_QUERY:			return 3;
		break;
	case MSG_CCD_STATUS_RESPONSE:			return 10;
		break;
	case MSG_PSC_STATUS_RESPONSE:			return 8;
		break;
	case MSG_TRAIL_HEU_STATUS_RESPONSE:	return 5;
		break;
	case MSG_EOT_BEACON:					return 7;
		break;
	case MSG_TRAIN_SEQUENCING_COMMAND:	return 4;
		break;
	case MSG_VEHICLE_SEQUENCE_COMMAND:	return 5;
		break;
	case MSG_VEHICLE_SEQUENCE_STATUS:		return 3;
		break;
	case MSG_VEHICLE_SEQUENCE_INFO_QUERY:	return 5;
		break;
	case MSG_VEHICLE_SEQUENCE_INFO:		return 9;
		break;
	case MSG_TRAIN_STATUS_DATA:			return 7;
		break;
	case MSG_CRITICAL_EXCEPTION:			return 10;//不包括附加数据
		break;
	case MSG_NORMAL_EXCEPTION:			return 23;//不包括附加数据
		break;
	case MSG_EXCEPTION_CLEARANCE:			return 22;
		break;
	case MSG_EXCEPTION_UPDATE_REQUEST:	return 4;
		break;
	case MSG_EXCEPTION_QUERY:				return 6;
		break;
	default:
		{
			return 0;
			break;
		}
		
	}
}
