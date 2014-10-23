#pragma once
#include "ldv32.h"					// native OpenLDV interface (ldv_* API)
#include "sunnyDefine.h"
#include "sunnyOpenLDVdefinitions.h"
class CLon2S4230
{
	//底层函数
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


	//私有函数
private:
	static short m_OpenLdvHandle;	// handle used for ldv_* calls. -1 (minus 1) if not valid.
	static  void setMsgIn(Byte *buf);
	static void msg_init();
	static void setPrior();/*设置优先级高*/
	static void setNonPrior();/*设置优先级低*/
	static void setType(Byte TPDUType);/*设置TPDUtype*/
	static S4230Header s4230header;//给 msg_out 用
	static void setTPDU();/*设置模式为TPDU*/
	static void setAPDU();/* 设置模式为APDU*/
	static void setMsgCode(Byte msgcode);
	static void setS4230Header(Byte id,Byte version);

	//用户函数
public:
	static void msg_put(Byte TPDUtype,Byte Priority);
	static void setAddrBroadCast(Byte srcSubnet,Byte srcNode,Byte DstSubnet);/*设置模式为广播 设置自己的subnet 以及node 以及 目标的subnet*/
	static void setAddrSubNetNode(Byte srcSubnet,Byte srcNode,Byte DstSubnet,Byte DstNode);/*设置模式为subnetnode  设置自己的subnet 以及node 以及 目标的subnet和node*/
	static void setAddrNeuronID(Byte srcSubnet,Byte srcNode,Byte DstSubnet,Byte nid[ NEURON_ID_LEN ]);/*设置模式为id 设置自己的subnet 以及node 以及 目标的subnet和id*/
	static void setMsgData(Byte id,Byte version,void *data,Byte Length);	
	//可能还有一些 get id或者其他的
};

short CLon2S4230::m_OpenLdvHandle=-1;
ExpApp CLon2S4230::msg_in;
ExpApp CLon2S4230::msg_out;
S4230Header CLon2S4230::s4230header;




