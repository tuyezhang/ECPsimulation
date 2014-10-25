#pragma once
#include "CvirtualCCD.h"
#include "Lon2S4230.h"

#define  CAR_NUM_DEF 20
class CVirtualCCDManage
{
    public:
        CVirtualCCDManage( void );
        ~CVirtualCCDManage( void );
        /*
        ���������� Get_CCD_Numʹ�� ���Ա��� ÿ��CCDָ�� Ȼ�� �����ڰ� ����CCD���нṹ�嶨��Ϊ��public �����Ϳ��Զ�ȡ��Ӧ��CCD��Ϣ
        */
        CvirtualCCD *Get_CCD_pObj( int i );//��������CCD�������õ���Ӧ����CCD��ָ��
        void Set_CCD_Num( int ccd_num );//��������CCD������
        int Get_CCD_Num();//����ccd������
		/*��CCD��Ϣ��һЩ�趨*/
        void Set_All_CCD_Lock();//��������CCD LOCK
        void Set_All_CCD_Unlock();//��������CCD UNLOCK
        void Set_CCD_Lock( int i );//��������Ϊ i��CCD LOCK
        void Set_CCD_Unlock( int i );//��������Ϊ i��CCD UNLOCK
        void Set_Subnet_Node( Byte subnet , Byte node, int index );//��������Ϊindex�� subnet ��node

		/*ͨ�����ֹ�ϵ����CCD����*/
        int Return_Match_CCD_Nid();//����msg_in��nid ����CCD ������
        int Return_Match_CCD_Nid( Byte * nid, Byte length ); // ���ݸ���������nid ���ض�ӦCCD   NID  ������
        int Return_Match_CCD_Subnet_Node( Byte subnet, Byte node ); // ���ݸ���������subnet node ����CCD   subnet node  ������
		/*��Ӧ3�ű��ķ���7�ű���*/
        void Send_CCD_Info_ALL( int randomizing_interval ); //��������CCD��Ϣ����������
        void Send_CCD_Info( int index ); //�� ����Ϊ index �� CCD ���� CCD info  ~���ڿ����Ȳ�����~

        /*�������ĸ����ڿ����Ȳ���*/
        void Set_CCD_Node_Information();//����CCD�ڵ���Ϣ  ~���ڿ����Ȳ�����~
        void Set_CCD_Car_Info();//����CCD��Ϣ  ~���ڿ����Ȳ�����~
        void Set_CCD_Status();//����CCD״̬��Ϣ ~���ڿ����Ȳ�����~
        /*
          ��ʼ��ʱӦ�þͻ�������
        */
        void Set_CCD_ALL_Data();//����CCD������������Ϣ �ɵ����������,������������ Ҳ�ɷֱ������������ ~���ڿ����Ȳ�����~


    private:
        int car_num;
        CvirtualCCD * pCCD;
        CLon2S4230 lonOP;

};

