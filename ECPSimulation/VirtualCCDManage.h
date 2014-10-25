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
        int Return_Match_CCD_Nid();//返回 具有相应 CCD   msg_in的NID  的索引
		int Return_Match_CCD_Nid(Byte * nid, Byte length);//返回 具有给定 CCD   NID  的索引
		int Return_Match_CCD_Subnet_Node(Byte subnet, Byte node);//返回 具有给定 CCD   NID  的索引
        void Set_Subnet_Node( Byte subnet , Byte node, int index );
		void Send_CCD_Info(int index);
		void Set_CCD_Node_Information();//设置CCD节点信息
		void Set_CCD_Car_Info();//设置CCD信息
		void Set_CCD_Status();//设置CCD状态信息
		void Set_CCD_ALL_Data();//设置CCD包括的所有信息 可单独调用这个,不用上面三个 也可分别调用上面三个
		void Send_CCD_Info_ALL(int randomizing_interval);

    private:
        int car_num;
        CvirtualCCD * pCCD;
		 CLon2S4230 lonOP;
	
};

