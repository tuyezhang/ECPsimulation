#include "StdAfx.h"
#include "VirtualCCDManage.h"


CVirtualCCDManage::CVirtualCCDManage( void )
{
    car_num = CAR_NUM_DEF;

    pCCD = new CvirtualCCD[car_num];
    Set_CCD_ALL_Data();


}


CVirtualCCDManage::~CVirtualCCDManage( void )
{
}

CvirtualCCD *CVirtualCCDManage::Get_CCD_pObj( int i )
{
    if ( i < car_num )
    {
        return &pCCD[i];
    }

    return NULL;
}
void CVirtualCCDManage::Set_CCD_Num( int ccd_num )
{
    CvirtualCCD *pCCDtemp = pCCD;
    car_num = ccd_num;
    CvirtualCCD *pCCD = new CvirtualCCD[car_num];
    delete []pCCDtemp;
    Set_CCD_ALL_Data();

}

int CVirtualCCDManage:: Get_CCD_Num()
{
	return car_num;
}
void CVirtualCCDManage::Set_All_CCD_Lock()
{
    for ( int i = 0; i < car_num; i++ )
    {
        pCCD[i].Set_CCD_Lock( true );
    }

}
void CVirtualCCDManage::Set_All_CCD_Unlock()
{
    for ( int i = 0; i < car_num; i++ )
    {
        pCCD[i].Set_CCD_Lock( false );
    }
}

void CVirtualCCDManage::Set_CCD_Lock( int i )
{
    if ( i < car_num )
    {
        pCCD[i].Set_CCD_Lock( true );
    }
}
void CVirtualCCDManage::Set_CCD_Unlock( int i )
{
    if ( i < car_num )
    {
        pCCD[i].Set_CCD_Lock( false );
    }
}
int CVirtualCCDManage:: Return_Match_CCD_Nid()
{
    for ( int i = 0; i < car_num; i++ )
    {
        if ( pCCD[i].Is_NID_Match( lonOP.msg_in.msg_addr.rsp.id.nid, 6 ) )
        {
            return i;
        }
    }

    return -1;
}
void CVirtualCCDManage::Set_Subnet_Node( Byte subnet , Byte node, int index )
{
    if ( index >= car_num )
    {
        return;
    }

    pCCD[index].Set_CCD_Subnet( subnet );
    pCCD[index].Set_CCD_Node( node );
}
void CVirtualCCDManage:: Send_CCD_Info( int index )
{
    if ( index >= car_num || index < 0 )
    {
        return;
    }

    pCCD[index].Send_CCD_Info();
}

void CVirtualCCDManage::Send_CCD_Info_ALL( int randomizing_interval )
{
    for( int i = 0; i < car_num; i++ )
    {
        pCCD[i].Send_CCD_Info( randomizing_interval );
    }
}

void CVirtualCCDManage::Set_CCD_Node_Information()
{
    for ( int i = 0; i < car_num; i++ )
    {
        pCCD[i].Set_CCD_Node_Information( i );
    }

}
void CVirtualCCDManage::Set_CCD_Car_Info()
{
    for ( int i = 0; i < car_num; i++ )
    {
        pCCD[i].Set_CCD_Car_Info( i );
    }
}
void CVirtualCCDManage::Set_CCD_Status()
{
    for ( int i = 0; i < car_num; i++ )
    {
        pCCD[i].Set_CCD_Status( i );
    }

}
void CVirtualCCDManage::Set_CCD_ALL_Data()
{
    Set_CCD_Node_Information();
    Set_CCD_Car_Info();
    Set_CCD_Status();
}

int CVirtualCCDManage::Return_Match_CCD_Nid( Byte * nid, Byte length ) //返回 具有给定 CCD   NID  的索引
{
    for ( int i = 0; i < car_num; i++ )
    {
        if ( pCCD[i].Is_NID_Match( nid, 6 ) )
        {
            return i;
        }
    }

    return -1;
}
int CVirtualCCDManage::Return_Match_CCD_Subnet_Node( Byte subnet, Byte node ) //返回 具有给定 CCD   NID  的索引
{
    for ( int i = 0; i < car_num; i++ )
    {
        if ( pCCD[i].Is_Subnet_Node( subnet, node ) )
        {
            return i;
        }
    }

    return -1;
}