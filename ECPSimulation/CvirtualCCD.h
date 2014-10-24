#pragma once
#include "sunnyDefine.h"

class CvirtualCCD
{
public:
	CvirtualCCD(void);
	~CvirtualCCD(void);
	void Send_Msg_by_ID(Byte msg_id,Byte msg_type,Byte msg_pri=NONPRIORITY, Byte msg_ver=0);

public:
	Byte *Msg_Send_Buffer;
	CCD_Exception_Flags Exception_Flags;	//�쳣��־λ
	CCD_Exception_Detail Exception_Detail;	//�쳣�룬�쳣�������ݷ��ͻ�����
	Byte Send_Response;								//��ʾ�豸����Ҫ���ͱ���ʱΪ�������ͻ��ǻظ�����ĳЩʱ���õõ�

	//CCD�ڲ���Ϣ
private:						//���е��豸��״̬����Ϣ����˽�еģ���Ҫ����Ӧ�ĺ������ʣ��޸�
	Byte Lock_Status;										//����������״̬
	Node_Information Node_Info;					//����ڵ���Ϣ
	CCD_Car_Info Device_Info;						//CCD�豸��������̬��Ϣ
	CCD_Status Dynamtic_Info;						//״̬��Ϣ ��̬��Ϣ
	Vehicle_Sequence Sequence;					//������Ϣ
};

