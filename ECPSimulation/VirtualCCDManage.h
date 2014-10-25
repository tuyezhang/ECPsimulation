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
        int Return_Match_CCD_Nid();//���� ������Ӧ CCD   msg_in��NID  ������
		int Return_Match_CCD_Nid(Byte * nid, Byte length);//���� ���и��� CCD   NID  ������
		int Return_Match_CCD_Subnet_Node(Byte subnet, Byte node);//���� ���и��� CCD   NID  ������
        void Set_Subnet_Node( Byte subnet , Byte node, int index );
		void Send_CCD_Info(int index);
		void Set_CCD_Node_Information();//����CCD�ڵ���Ϣ
		void Set_CCD_Car_Info();//����CCD��Ϣ
		void Set_CCD_Status();//����CCD״̬��Ϣ
		void Set_CCD_ALL_Data();//����CCD������������Ϣ �ɵ����������,������������ Ҳ�ɷֱ������������
		void Send_CCD_Info_ALL(int randomizing_interval);

    private:
        int car_num;
        CvirtualCCD * pCCD;
		 CLon2S4230 lonOP;
	
};

