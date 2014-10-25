#pragma once
#include "CvirtualCCD.h"
#include "Lon2S4230.h"

#define  CAR_NUM_DEF 20
class CVirtualCCDManage
{
    public:
        CVirtualCCDManage( void );
        ~CVirtualCCDManage( void );
        CvirtualCCD *Get_CCD_pObj( int i );
        void Set_CCD_Num( int ccd_num );
        void Set_All_CCD_Lock();
        void Set_All_CCD_Unlock();
        void Set_CCD_Lock( int i );
        void Set_CCD_Unlock( int i );
        int Return_Match_CCD_Nid();
        void Set_Subnet_Node( Byte subnet , Byte node, int index );
		void Send_CCD_Info(int index);

    private:
        int car_num;
        CvirtualCCD * pCCD;
		 CLon2S4230 lonOP;
};

