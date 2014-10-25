#pragma once
#include "sunnyDefine.h"
#include "Util.h"
#include "Lon2S4230.h"
#include <Windows.h>
class CvirtualCCD
{
    public:
        CvirtualCCD( void );
        ~CvirtualCCD( void );
		/*������ӦID�ı���*/
        int Send_Msg_by_ID( Byte msg_id, Byte msg_type, Byte msg_pri = NONPRIORITY, Byte msg_ver = 0 );
		unsigned int m_Elapse;//�����ʱ��ʱ���3�ű�����
    public:
        Byte *Msg_Send_Buffer;
        CCD_Exception_Flags Exception_Flags;	//�쳣��־λ
        CCD_Exception_Detail Exception_Detail;	//�쳣�룬�쳣�������ݷ��ͻ�����
        Byte Send_Response;								//��ʾ�豸����Ҫ���ͱ���ʱΪ�������ͻ��ǻظ�����ĳЩʱ���õõ�
        Byte Get_CCD_Subnet();//�õ�CCD��subnet
        Byte Get_CCD_Node();//�õ�CCD��node
        void  Set_CCD_Subnet( Byte subnet );//����CCD��subnet
        void  Set_CCD_Node( Byte node );//����CCD��node
        bool  Is_NID_Match( Byte * nid, Byte length );//�Ƿ����������nidƥ��
        bool  Is_Subnet_Node( Byte sunbet, byte node );//�Ƿ������ subnet node ƥ��
        bool  Set_CCD_Lock( bool isLock );//����CCD������  true :���� false:����
        void Send_CCD_Info();//��������CCD��Ϣ7�ű���
		void Send_CCD_Info(int randomizing_interval);//�������������ͱ�����Ϣ
		void Set_CCD_Node_Information(int index);//���� CCD �ڵ���Ϣ index ��ʾ���ǵڼ��� �� manager���
		void Set_CCD_Car_Info(int index);//���� CCD ��̬��������Ϣ index ��ʾ���ǵڼ��� �� manager���
		void Set_CCD_Status(int index);//���� CCD ״̬��Ϣ index ��ʾ���ǵڼ��� �� manager���
        //CCD�ڲ���Ϣ
    public:						//���е��豸��״̬����Ϣ����˽�еģ���Ҫ����Ӧ�ĺ������ʣ��޸�
        Byte Lock_Status;										//����������״̬
        Node_Information Node_Info;					//����ڵ���Ϣ
        CCD_Car_Info Device_Info;						//CCD�豸��������̬��Ϣ
        CCD_Status Dynamtic_Info;						//״̬��Ϣ ��̬��Ϣ
        Vehicle_Sequence Sequence;					//������Ϣ
	private:		
        void Set_Msg_data_0( byte msg_ver, byte length ); //���÷��͵�0�ű�������
        void Set_Msg_data_7( byte msg_ver, byte length ); //���÷��͵�7�ű�������
        void Set_Msg_data_15( byte msg_ver, byte length ); //���÷��͵�15�ű�������
        void Set_Msg_data_21( byte msg_ver, byte length ); //���÷��͵�21�ű�������
        void Set_Msg_data_23( byte msg_ver, byte length ); //���÷��͵�23�ű�������
        void Set_Msg_data_25( byte msg_ver, byte length ); //���÷��͵�25�ű�������
        void Set_Msg_data_26( byte msg_ver, byte length ); //���÷��͵�26�ű�������
        void Set_Msg_data_27( byte msg_ver, byte length ); //���÷��͵�27�ű�������
		CUtil util;
		CLon2S4230 lonop;	
		HANDLE m_hThread;
		static DWORD WINAPI ThreadFunc (LPVOID pParam);
};

