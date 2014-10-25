#include "StdAfx.h"
#include "CvirtualCCD.h"
#include <vector>
using namespace std;


CvirtualCCD::CvirtualCCD( void )
{
}


CvirtualCCD::~CvirtualCCD( void )
{
}

//报文组包函数
int CvirtualCCD::Send_Msg_by_ID( Byte msg_id, Byte msg_type, Byte msg_pri, Byte msg_ver )
{
    Byte length = util.get_Msg_length( msg_id );

    switch( msg_id )
    {
        case MSG_CAR_STATIC_INFO://0
        {

            Set_Msg_data_0( msg_ver, length );
        }
        break;

        case MSG_CCD_DEVICE_INFO:
        {

            Set_Msg_data_7( msg_ver, length );
        }
        break;

        case MSG_CCD_STATUS_RESPONSE:
        {

            Set_Msg_data_15( msg_ver, length );

        }
        break;

        case  MSG_VEHICLE_SEQUENCE_STATUS:
        {

            Set_Msg_data_21( msg_ver, length );

        }
        break;

        case MSG_VEHICLE_SEQUENCE_INFO:
        {

            Set_Msg_data_23( msg_ver, length );
        }
        break;

        case MSG_CRITICAL_EXCEPTION:
        {

            Set_Msg_data_25( msg_ver, length + Exception_Detail.Supporting_Data_Length );
        }
        break;

        case MSG_NORMAL_EXCEPTION:
        {

            Set_Msg_data_26( msg_ver, length + Exception_Detail.Supporting_Data_Length );
        }
        break;

        case MSG_EXCEPTION_CLEARANCE:
        {

            Set_Msg_data_27( msg_ver, length );
        }
        break;

        case MSG_EXCEPTION_UPDATE:
        {
            /*暂不处理*/
        }
        break;

        default:
            return -1;
    }

    lonop.setAddrSubNetNode( Node_Info.Subnet, Node_Info.Node, 1, 2 ); //这个还要改为具体的 subnet node
    lonop.msg_put( msg_type, msg_pri );
    return 0;

}

void CvirtualCCD:: Set_Msg_data_0( byte msg_ver, byte length )
{
    Msg_sCar_Static_Info msg_send;
    memcpy( &msg_send, &Device_Info, length );
    lonop.setMsgData( 0, msg_ver, ( void * )&msg_send, length - 2 );
}
void CvirtualCCD:: Set_Msg_data_7( byte msg_ver, byte length )
{
    Msg_sCCD_Device_Info msg_send;
    msg_send.Manufacturer_ID = Device_Info.Car_ID_Modules_Manufacturer;
    memcpy( msg_send.Reporting_Mark, Device_Info.Reporting_Mark, 11 );
    memcpy( msg_send.Unique_ID, Device_Info.Unique_ID, 6 );
    msg_send.Manufacturer_Revision_Level = Device_Info.Manufacturer_Revision_Level;
    msg_send.S_4200_Compatibility_Version = Device_Info.S_4200_Compatibility_Version;
    msg_send.S_4230_Compatibility_Version = Device_Info.S_4230_Compatibility_Version;
    msg_send.Device_Characteristics = Device_Info.Device_Characteristics;
    memcpy( msg_send.Vehicle_Type, Device_Info.Car_Type, 4 );
    msg_send.Vehicle_Length.set( Device_Info.Car_Length.get() );
    msg_send.Empty_Weight.set( Device_Info.Empty_Weight.get() );
    msg_send.Loaded_Weight.set( Device_Info.Loaded_Weight.get() );
    msg_send.Num_Axles = Device_Info.Num_Axles;
    msg_send.Operable_Brakes_Controlled = Device_Info.Operable_Brakes_Controlled;
    msg_send.Empty_Load_Device_Type = Device_Info.Empty_Load_Device_Type;
    lonop.setMsgData( 7, msg_ver, ( void * )&msg_send, length - 2 );
}
void CvirtualCCD:: Set_Msg_data_15( byte msg_ver, byte length )
{
    Msg_sCCD_Status_Response msg_send;
    memcpy( &msg_send, &Dynamtic_Info, length );
    lonop.setMsgData( 15, msg_ver, ( void * )&msg_send, length - 2 );
}

void CvirtualCCD:: Set_Msg_data_21( byte msg_ver, byte length )
{
    Msg_sVehicle_Sequence_Status msg_send;
    msg_send.Sequence_Status = Sequence.Status;
    lonop.setMsgData( 21, msg_ver, ( void * )&msg_send, length - 2 );
}
void CvirtualCCD:: Set_Msg_data_23( byte msg_ver, byte length )
{
    Msg_sVehicle_Sequence_Info msg_send;
    msg_send.Vehicle_Sequence_State = Sequence.Count_State;
    msg_send.Sequencing_Flags = Sequence.Sequencing_Flag;
    msg_send.Vehicle_Orientation = Device_Info.Sequencing_Orientation;
    msg_send.Pulse_Count.set( Sequence.Pulse_Count.get() );
    msg_send.Vehicle_Position.set( Sequence.Position.get() );
    lonop.setMsgData( 23, msg_ver, ( void * )&msg_send, length - 2 );
}
void CvirtualCCD:: Set_Msg_data_25( byte msg_ver, byte length )
{
    Msg_sCritical_Exception msg_send;
    msg_send.Exception_Code.set( Exception_Detail.Exception_Code.get() );
    memcpy( msg_send.Unique_ID, Device_Info.Unique_ID, 6 );
    memcpy( msg_send.Supporting_Data, Exception_Detail.Supporting_Data, Exception_Detail.Supporting_Data_Length );
    lonop.setMsgData( 25, msg_ver, ( void * )&msg_send, length - 2 );
}
void CvirtualCCD:: Set_Msg_data_26( byte msg_ver, byte length )
{
    Msg_sNormal_Exception msg_send;
    msg_send.Exception_Code.set( Exception_Detail.Exception_Code.get() );
    memcpy( msg_send.Unique_ID, Device_Info.Unique_ID, 6 );
    memcpy( msg_send.Vehicle_Reporting_Mark, Device_Info.Reporting_Mark, 11 );
    msg_send.Exception_Status = Send_Response;
    msg_send.Supporting_Data_Version = Exception_Detail.Supporting_Data_Version;
    memcpy( msg_send.Supporting_Data, Exception_Detail.Supporting_Data, Exception_Detail.Supporting_Data_Length );
    lonop.setMsgData( 26, msg_ver, ( void * )&msg_send, length - 2 );

}
void CvirtualCCD:: Set_Msg_data_27( byte msg_ver, byte length )
{
    Msg_sException_Clear msg_send;
    msg_send.Exception_Code.set( Exception_Detail.Exception_Code.get() );
    memcpy( msg_send.Unique_ID, Device_Info.Unique_ID, 6 );
    memcpy( msg_send.Vehicle_Reporting_Mark, Device_Info.Reporting_Mark, 11 );
    msg_send.Exception_Status = Send_Response;
    lonop.setMsgData( 27, msg_ver, ( void * )&msg_send, length - 2 );
}

//CCD 信息的设置与获取
Byte CvirtualCCD:: Get_CCD_Subnet()
{
    return Node_Info.Subnet;
}
Byte  CvirtualCCD:: Get_CCD_Node()
{
    return Node_Info.Node;
}
void   CvirtualCCD:: Set_CCD_Subnet( Byte subnet )
{
    Node_Info.Subnet = subnet;
}

void   CvirtualCCD:: Set_CCD_Node( Byte node )
{
    Node_Info.Node = node;
}

bool  CvirtualCCD::Is_NID_Match( Byte * nid, Byte length )
{
    if ( length != 6 || nid == NULL )
    {
        return false;
    }

    for ( int i = 0; i < 6; i++ )
    {
        if ( nid[i] != Node_Info.Neuron_ID[i] )
        {
            return false;
        }
    }

    return true;
}

bool CvirtualCCD::Is_Subnet_Node( Byte subnet, byte node )
{
    if ( subnet == Get_CCD_Subnet() && node == Get_CCD_Node() )
    {
        return true;
    }

    return false;
}

bool  CvirtualCCD::Set_CCD_Lock( bool isLock )
{
    Lock_Status = isLock;
    return isLock;
}
void CvirtualCCD::Send_CCD_Info()
{
    Send_Msg_by_ID( MSG_CCD_DEVICE_INFO, UNACKD );
}

void CvirtualCCD::Send_CCD_Info( int randomizing_interval )
{
    srand( ( unsigned )time( 0 ) );
    int ran_num = rand() % randomizing_interval;
    m_Elapse = ran_num;
    m_hThread = CreateThread( NULL, 0, ( LPTHREAD_START_ROUTINE )ThreadFunc, ( LPVOID )this, 0, NULL );
}
DWORD WINAPI CvirtualCCD::ThreadFunc ( LPVOID pParam )
{
    time_t t1, t2;
    double  Diff = 0;
    CvirtualCCD* pCCD = ( ( CvirtualCCD * )pParam );
    /*获取系统当前时间*/
    t1 = time( NULL );
    int flag = true;

    while( flag )
    {
        /*以秒为单位获取系统当前时间*/
        t2 = time( NULL );
        /*比较第二次获取的时间与第一次的时间是不是间隔了两秒*/
        Diff = difftime( t2, t1 );

        /*间隔两秒打印Diff和i*/
        if( ( int )Diff == pCCD->m_Elapse )
        {
            //cout<<"Time out!"<<endl;
            pCCD->Send_CCD_Info();
            t1 = t2;
            flag = false;
        }
    }

    return 0;
}

void CvirtualCCD::Set_CCD_Node_Information( int index )
{
    //设备节点信息初始化	 nid设定  最前面一位是01---到carnum
    srand( ( unsigned )time( 0 ) );
    int ran_num = rand() % 7 + 3;
    int ran_num2 = rand() % 127 + 1;
    int ran_nid2, ran_nid3, ran_nid4, ran_nid5, ran_nid6;
    ran_nid2 = rand() % 0xff + 1;
    ran_nid3 = rand() % 0xff + 1;
    ran_nid4 = rand() % 0xff + 1;
    ran_nid5 = rand() % 0xff + 1;
    ran_nid6 = rand() % 0xff + 1;
    Node_Info.Subnet = ran_num;
    Node_Info.Node = ran_num2;
    Node_Info.Neuron_ID[5] = ran_nid6;
    Node_Info.Neuron_ID[4] = ran_nid5;
    Node_Info.Neuron_ID[3] = ran_nid4;
    Node_Info.Neuron_ID[2] = ran_nid3;
    Node_Info.Neuron_ID[1] = ran_nid2;
    Node_Info.Neuron_ID[0] = index;
}
void CvirtualCCD::Set_CCD_Car_Info( int index )
{
    srand( ( unsigned )time( 0 ) );
    Device_Info.Manufacturer_Revision_Level = 0;
    Device_Info.S_4200_Compatibility_Version = 2;
    Device_Info.S_4230_Compatibility_Version = 2;
    Device_Info.Device_Characteristics = 0;
    Device_Info.Car_ID_Modules_Manufacturer = 1;
    //下面是car type  最后要达到的目的是 CAR00000xxx
    string s = "CAR00000000";
    memcpy( Device_Info.Reporting_Mark, s.c_str(), 11 );
    int ran_car = rand() % ( 200 ) + 1;
    Device_Info.Reporting_Mark[10] += ran_car % 10;
    Device_Info.Reporting_Mark[9] += ( ran_car / 10 ) % 10;
    Device_Info.Reporting_Mark[8] += ran_car / 100;
    //其他数据默认设定
    Device_Info.Car_Length.set( 800 );
    Device_Info.Num_Axles = 4;
    Device_Info.Brakes_Controlled = 40;
    Device_Info.Empty_Weight.set( 500 );
    Device_Info.Loaded_Weight.set( 2860 );
    Device_Info.Break_Constant.set( 572 );
    Device_Info.Reservoir_Constant.set( 711 );
    Device_Info.Net_Braking_Ratio_Default = 64;
    Device_Info.Min_Service_Pressure = 7;
    Device_Info.Empty_Load_Device_Type = 0;
    Device_Info.Sequencing_Orientation = 0;
    //cat_type 设置成csrw
    string s1 = "CSRW";
    memcpy( Device_Info.Car_Type, s1.c_str(), 4 );
}
void CvirtualCCD::Set_CCD_Status( int index )
{
    //设备状态信息
    Dynamtic_Info.Brake_Pipe_Pressure = 50;
    Dynamtic_Info.Reservoir_Pressure = 70;
    Dynamtic_Info.Brake_Cylinder_Pressure = 90;
    Dynamtic_Info.Percent_Brake_Applied = index;
    Dynamtic_Info.Car_Load = 5;
    Dynamtic_Info.Highest_Priority_Active_Exception.set( 65535 );
    Dynamtic_Info.Car_Status = 3;
    Lock_Status = LOCK;
}