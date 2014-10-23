#pragma once
#include "ldv32.h"					// native OpenLDV interface (ldv_* API)
#include "sunnyDefine.h"
#include "sunnyOpenLDVdefinitions.h"
class CLon2S4230
{
	//�ײ㺯��
public:
	CLon2S4230(void);
	~CLon2S4230(void);
	static ExpApp msg_out,msg_in;	
	// Open() wraps ldv_open. Override to implement tracing or alternative behavior
	static LDVCode  Open(LPCSTR pIdentifier);	
	static LDVCode  Close();	
	static LDVCode  Read(short uLen);	 

private:
	static LDVCode  Write(void* pMsg, short uLen);
	static LDVCode  Close(LPCSTR pIdentifier);


	//˽�к���
private:
	static short m_OpenLdvHandle;	// handle used for ldv_* calls. -1 (minus 1) if not valid.
	static  void setMsgIn(Byte *buf);
	static void msg_init();
	static void setPrior();/*�������ȼ���*/
	static void setNonPrior();/*�������ȼ���*/
	static void setType(Byte TPDUType);/*����TPDUtype*/
	static S4230Header s4230header;//�� msg_out ��
	static void setTPDU();/*����ģʽΪTPDU*/
	static void setAPDU();/* ����ģʽΪAPDU*/
	static void setMsgCode(Byte msgcode);
	static void setS4230Header(Byte id,Byte version);

	//�û�����
public:
	static void msg_put(Byte TPDUtype,Byte Priority);
	static void setAddrBroadCast(Byte srcSubnet,Byte srcNode,Byte DstSubnet);/*����ģʽΪ�㲥 �����Լ���subnet �Լ�node �Լ� Ŀ���subnet*/
	static void setAddrSubNetNode(Byte srcSubnet,Byte srcNode,Byte DstSubnet,Byte DstNode);/*����ģʽΪsubnetnode  �����Լ���subnet �Լ�node �Լ� Ŀ���subnet��node*/
	static void setAddrNeuronID(Byte srcSubnet,Byte srcNode,Byte DstSubnet,Byte nid[ NEURON_ID_LEN ]);/*����ģʽΪid �����Լ���subnet �Լ�node �Լ� Ŀ���subnet��id*/
	static void setMsgData(Byte id,Byte version,void *data,Byte Length);	
	//���ܻ���һЩ get id����������
};

short CLon2S4230::m_OpenLdvHandle=-1;
ExpApp CLon2S4230::msg_in;
ExpApp CLon2S4230::msg_out;
S4230Header CLon2S4230::s4230header;




