#include "StdAfx.h"
#include "HandleMessage.h"
#include "sunnyDefine.h"

CHandleMessage::CHandleMessage( void )
{
}


CHandleMessage::~CHandleMessage( void )
{
}
void CHandleMessage:: Handle_Message_3()
{
    Msg_sDevice_Info_Control_Query msg_s;
    memcpy( &msg_s, &lonOP.msg_in.msg_data.exp.data[2], 2 );

    int com = msg_s.Command & 0x03;
    int type = ( msg_s.Command & 0x1c ) >> 2;

    if ( ( com == UNLOCK ) && ( ( type == CCD ) || ( type == ALL ) ) )
    {

        ccdManageOP.Set_All_CCD_Unlock();
    }

    if ( ( com == LOCK ) && ( ( type == CCD ) || ( type == ALL ) ) )
    {

        if ( lonOP.isBroadCastAddr() )
        {
            ccdManageOP.Set_All_CCD_Lock();

        }

        else if ( lonOP.isNidAddr() )
        {

            int i = ccdManageOP.Return_Match_CCD_Nid();

            if ( i >= 0 )
            {
                ccdManageOP.Set_CCD_Lock( i );
            }


        }



    }

    if ( ( com == SEND_DEVICE_INFO ) && ( ( type == CCD ) || ( type == ALL ) ) )
    {

        if ( lonOP.isBroadCastAddr() )
        {
            
			  ccdManageOP.Send_CCD_Info_ALL(msg_s.Randomizing_Interval);

        }
        else if ( lonOP.isNidAddr() )
        {
            int i = ccdManageOP.Return_Match_CCD_Nid();

            if ( i >= 0 )
            {
                ccdManageOP.Send_CCD_Info(i);

            }

        }


    }


}
void CHandleMessage ::Handle_Message_4()
{
    Msg_sAssign_Node_ID msg_s;

    memcpy( &msg_s, &lonOP.msg_in.msg_data.exp.data[2], 2 );
    int node = msg_s.Node_ID;
    int subnet = msg_s.Subnet;


    if ( !lonOP.isNidAddr() )
        return;

    int i = ccdManageOP.Return_Match_CCD_Nid();

    if ( i >= 0 )
    {
        
        ccdManageOP.Set_Subnet_Node( node, subnet, i );
		 ccdManageOP.Set_CCD_Lock( i );
    }




}
void CHandleMessage::Handle_Message_13()
{

}