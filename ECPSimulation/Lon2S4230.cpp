#include "StdAfx.h"
#include "Lon2S4230.h"
#include <vector> 
using namespace std;
/*
 lon2S4230 主要使用 基本方法主要是static的
 发送信息
open("LON1");
setMsgData();
setAddrXXX();
msg_put();UNACK/ ACKD;
接收数据
定时
read();


*/
short CLon2S4230::m_OpenLdvHandle=-1;
ExpApp CLon2S4230::msg_in;
ExpApp CLon2S4230::msg_out;
S4230Header CLon2S4230::s4230header;
CLon2S4230::CLon2S4230(void)
{
	msg_init();
}


CLon2S4230::~CLon2S4230(void)
{
}

//用第二层打开设备
LDVCode CLon2S4230::Open(LPCSTR pIdentifier)
{
	if (m_OpenLdvHandle!=-1)
	{
		return 0;
	}
	//LDVCode eResult = ldv_open_cap(pIdentifier, &m_OpenLdvHandle, LDV_DEVCAP_L2, m_hWnd, m_lParam);
	LDVCode eResult = ldv_open_cap(pIdentifier, &m_OpenLdvHandle, LDV_DEVCAP_L2, 0, 0);

	if (eResult != LDV_OK) {
		m_OpenLdvHandle = -1;
		return -1;
	}

	return eResult;
}


//关闭lon设备
LDVCode CLon2S4230::Close(LPCSTR pIdentifier)
{
	if (m_OpenLdvHandle==-1)
	{
		return 0;
	}
	LDVCode eResult = ldv_close(m_OpenLdvHandle);

	if (eResult != LDV_OK) {
		m_OpenLdvHandle = -1;
		return -1;
	}
	return eResult;
}
//关闭lon设备
LDVCode CLon2S4230::Close()
{
	 if (m_OpenLdvHandle==-1)
	 {
		 return 0;
	 }
	LDVCode eResult = ldv_close(m_OpenLdvHandle);

	if (eResult != LDV_OK) {
		m_OpenLdvHandle = -1;
		return -1;
	}
	return eResult;
}


// Write provides synchronized access to ldv_write()  
LDVCode CLon2S4230::Write(void* pMsg, short uLen)
{

	LDVCode eResult = ldv_write(m_OpenLdvHandle, pMsg, uLen);
	return eResult;

}
//读数据 设置结构体 调用readtolist
LDVCode CLon2S4230::Read( short uLen)
{
	Byte buf[100]={0};
	LDVCode ldvCode = ldv_read(m_OpenLdvHandle, buf, uLen);
	if (ldvCode != LDV_NO_MSG_AVAIL)
	{
		if((buf[3]&0x01)==1||(buf[0]&0xf0)!=0x10)
		{
			return -1;
		}		
			setMsgIn(buf);
	}


	return ldvCode;

}



/************************************************************************/
/* 这一块是底层的一些协议                                                                     */
/************************************************************************/


//把读到的消息入结构体 这个长度有点问题
void CLon2S4230::setMsgIn(Byte *buf)
{
	int pos=0;
	pos++;
	pos++;//2
	msg_in.msg_hdr.exp.Priority=(buf[pos++]&0x80)>>7;
	msg_in.msg_hdr.exp.AddrFmt=(buf[pos]&0x0C)>>2;
	msg_in.msg_hdr.exp.PDUFmt=(buf[pos]&0x30)>>4;
	pos++;//4
	int prefix=(msg_in.msg_hdr.exp.PDUFmt==APDU);

	switch(msg_in.msg_hdr.exp.AddrFmt)
	{
	case BROADCAST:
		{			
			msg_in.msg_addr.rsp.bc.isubnet=buf[pos++];
			msg_in.msg_addr.rsp.bc.inode=buf[pos++]&0x7f;
			msg_in.msg_addr.rsp.bc.subnet=buf[pos++];
			if (buf[1]>(9-prefix))
			{
				msg_in.msg_hdr.exp.Length=buf[1]-9+prefix;
			}
			else
				msg_in.msg_hdr.exp.Length=0;
		};
		break;
	case SUBNET_NODE:
		{

			msg_in.msg_addr.rsp.sn.isubnet=buf[pos++];
			msg_in.msg_addr.rsp.sn.inode=buf[pos++]&0x7f;
			msg_in.msg_addr.rsp.sn.subnet=buf[pos++];
			msg_in.msg_addr.rsp.sn.node=buf[pos++]&0x7f;


			if (buf[1]>(10-prefix))
			{
				msg_in.msg_hdr.exp.Length=buf[1]-10+prefix;
			}
			else
				msg_in.msg_hdr.exp.Length=0;

		};
		break;
	case NEURON_ID:
		{



			msg_in.msg_addr.rsp.id.isubnet=buf[pos++];
			msg_in.msg_addr.rsp.id.inode=buf[pos++]&0x7f;
			msg_in.msg_addr.rsp.id.subnet=buf[pos++];
			msg_in.msg_addr.rsp.id.nid[0]=buf[pos++];
			msg_in.msg_addr.rsp.id.nid[1]=buf[pos++];
			msg_in.msg_addr.rsp.id.nid[2]=buf[pos++];
			msg_in.msg_addr.rsp.id.nid[3]=buf[pos++];
			msg_in.msg_addr.rsp.id.nid[4]=buf[pos++];
			msg_in.msg_addr.rsp.id.nid[5]=buf[pos++];


			if (buf[1]>(15-prefix))
			{
				msg_in.msg_hdr.exp.Length=buf[1]-15+prefix;
			}
			else
				msg_in.msg_hdr.exp.Length=0;
		};
		break;

	}

	if (msg_in.msg_hdr.exp.PDUFmt==APDU)
	{
		msg_in.msg_hdr.exp.TPDUtype=UNACKD;  
	}
	else
	{
		msg_in.msg_hdr.exp.TPDUtype=(buf[pos++]&0x30)>>4;

	}


	if (msg_in.msg_hdr.exp.Length>0)
	{
		msg_in.msg_data.exp.code=buf[pos++];
	}
	else{
		msg_in.msg_data.exp.code=0;
	}


	for (int i=0;i<msg_in.msg_hdr.exp.Length;i++)
	{
		if (msg_in.msg_hdr.exp.Length>0)
		{
			msg_in.msg_data.exp.data[i]=buf[pos+i];

		}


	}
	if (msg_in.msg_hdr.exp.Length>0)
	{
		s4230header.id=msg_in.msg_data.exp.data[0];
		s4230header.version=msg_in.msg_data.exp.data[1];
	}


}




/*
设置模式为TPDU
*/
void CLon2S4230::setTPDU(){
	msg_out.msg_hdr.exp.PDUFmt=TPDU;
}
/*
设置模式为APDU
*/
void CLon2S4230::setAPDU(){
	msg_out.msg_hdr.exp.PDUFmt=APDU;
}
/*
设置模式为广播 设置自己的subnet 以及node 以及 目标的subnet
*/
void CLon2S4230::setAddrBroadCast(Byte srcSubnet,Byte srcNode,Byte DstSubnet){
	msg_out.msg_hdr.exp.AddrFmt=BROADCAST;
	msg_out.msg_addr.rsp.bc.inode=srcNode;
	msg_out.msg_addr.rsp.bc.isubnet=srcSubnet;
	msg_out.msg_addr.rsp.bc.subnet=DstSubnet;
}
void CLon2S4230::setAddrSubNetNode(Byte srcSubnet,Byte srcNode,Byte DstSubnet,Byte DstNode){
	msg_out.msg_hdr.exp.AddrFmt=SUBNET_NODE;
	msg_out.msg_addr.rsp.sn.inode=srcNode;
	msg_out.msg_addr.rsp.sn.isubnet=srcSubnet;
	msg_out.msg_addr.rsp.sn.subnet=DstSubnet;
	msg_out.msg_addr.rsp.sn.node=DstNode;
}
void CLon2S4230::setAddrNeuronID(Byte srcSubnet,Byte srcNode,Byte DstSubnet,Byte nid[ NEURON_ID_LEN ]){
	msg_out.msg_hdr.exp.AddrFmt=NEURON_ID;
	msg_out.msg_addr.rsp.id.inode=srcNode;
	msg_out.msg_addr.rsp.id.isubnet=srcSubnet;
	msg_out.msg_addr.rsp.id.subnet=DstSubnet;
	msg_out.msg_addr.rsp.id.nid[0]=nid[0];
	msg_out.msg_addr.rsp.id.nid[1]=nid[1];
	msg_out.msg_addr.rsp.id.nid[2]=nid[2];
	msg_out.msg_addr.rsp.id.nid[3]=nid[3];
	msg_out.msg_addr.rsp.id.nid[4]=nid[4];
	msg_out.msg_addr.rsp.id.nid[5]=nid[5];
}
/*
设置优先级高
*/
void CLon2S4230::setPrior(){
	msg_out.msg_hdr.exp.Priority=1;
}

/*
设置优先级低
*/
void CLon2S4230::setNonPrior(){
	msg_out.msg_hdr.exp.Priority=0;
}
void CLon2S4230::setMsgCode(Byte msgcode){
	msg_out.msg_data.exp.code=msgcode;
}
/*
设置TPDUtype
*/
void CLon2S4230::setType(Byte TPDUType)
{
	if (TPDUType==UNACKD)
	{
		setAPDU();
		msg_out.msg_hdr.exp.TPDUtype=UNACKD;
	}
	else
	{
		msg_out.msg_hdr.exp.TPDUtype= TPDUType;
		setTPDU();
	}

}

//设置信息data 把id 和version独立出来
void CLon2S4230::setMsgData(Byte id,Byte version, void *data,Byte Length)
{
	Byte *msgData=(Byte *)data;
	setS4230Header(id,version);
	msg_out.msg_data.exp.data[0]=id;
	msg_out.msg_data.exp.data[1]=version;
	for (int i=0;i<Length;i++)
	{
		msg_out.msg_data.exp.data[i+2]=msgData[i];
	}
	//2=id + version 
	msg_out.msg_hdr.exp.Length=Length+2;
}

//设置4230协议的 id 和version
void CLon2S4230::setS4230Header(Byte id,Byte version)
{
	s4230header.id=id;
	s4230header.version=version;
}



/*
报文的初始化主要是一些标志位的设置
*/
void CLon2S4230::msg_init()
{
	msg_out.msg_hdr.exp.AddrFmt=BROADCAST;
	msg_out.msg_hdr.exp.PDUFmt=TPDU;
	msg_out.msg_hdr.exp.Priority=1;
	msg_out.msg_hdr.exp.TPDUtype=ACKD;
	msg_out.msg_hdr.exp.Length=0;
	msg_in.msg_hdr.exp.Length=0;
	setMsgCode(0);
}
/*
报文的发出，主要是一些标志位的识别然后发出报文
*/

void CLon2S4230::msg_put(Byte TPDUtype,Byte Priority)
{
	setType(TPDUtype);
	if (Priority==PRIORITY)
	{
		setPrior();
	} 
	else
	{
		setNonPrior();
	}
	Byte head[]={0x13,0x00,0x00,0x00};
	Byte address[9];
	Byte msgdata[MAX_NETMSG_DATA];
	Byte tpdu[]={0x00};
	Byte msgcode[]={msg_out.msg_data.exp.code};
	Byte crc[]={0x00,0x00};
	int sizeAddress;
	for (int i=0;i<msg_out.msg_hdr.exp.Length;i++)
	{
		msgdata[i]=msg_out.msg_data.exp.data[i];
	}
	if (msg_out.msg_hdr.exp.AddrFmt==BROADCAST)
	{ 
		 sizeAddress=3;
		 address[0]=msg_out.msg_addr.rsp.bc.isubnet;
		 address[1]=0x80+msg_out.msg_addr.rsp.bc.inode;
		 address[2]=msg_out.msg_addr.rsp.bc.subnet;	
	}
	if (msg_out.msg_hdr.exp.AddrFmt==SUBNET_NODE)
	{
		 sizeAddress=4;
		 address[0]=msg_out.msg_addr.rsp.sn.isubnet;
		 address[1]=0x80+msg_out.msg_addr.rsp.bc.inode;
		 address[2]=msg_out.msg_addr.rsp.sn.subnet;	
		 address[3]=msg_out.msg_addr.rsp.sn.node+0x80;	
	}
	if (msg_out.msg_hdr.exp.AddrFmt==NEURON_ID)
	{
		 sizeAddress=9;
		 address[0]=msg_out.msg_addr.rsp.id.isubnet;
		 address[1]=0x80+msg_out.msg_addr.rsp.id.inode;
		 address[2]=msg_out.msg_addr.rsp.id.subnet;	
		 address[3]=msg_out.msg_addr.rsp.id.nid[0];
		 address[4]=msg_out.msg_addr.rsp.id.nid[1];	
		 address[5]=msg_out.msg_addr.rsp.id.nid[2];	
		 address[6]=msg_out.msg_addr.rsp.id.nid[3];	
		 address[7]=msg_out.msg_addr.rsp.id.nid[4];
		 address[8]=msg_out.msg_addr.rsp.id.nid[5];
	}
	
	head[2]+=msg_out.msg_hdr.exp.Priority<<7;
	head[3]+=msg_out.msg_hdr.exp.PDUFmt<<4;
	head[3]+=msg_out.msg_hdr.exp.AddrFmt<<2;
	
	vector<Byte> vInts;
	/*
	 加入报文头
	*/
	for (int i=0;i<sizeof(head)/sizeof(head[0]);i++)
	{
		vInts.push_back(head[i]);
	}
	/*
	 加入报文地址
	*/
	for (Byte i=0;i<sizeAddress/sizeof(address[0]);i++)
	{
		vInts.push_back(address[i]);
	}

	/*
	 加入报文PDUFMT
	*/
	if (msg_out.msg_hdr.exp.PDUFmt==TPDU)
	{
		tpdu[0]=msg_out.msg_hdr.exp.TPDUtype<<4;
		vInts.push_back(tpdu[0]);
	}
	
	/*
	 加入报文code
	*/
	vInts.push_back(msgcode[0]);
	

	/*
	 加入报文data
	*/
	for (Byte i=0;i<msg_out.msg_hdr.exp.Length/sizeof(msgdata[0]);i++)
	{
		vInts.push_back(msgdata[i]);
	}
	/*
	 加入报文crc 0x00 0x00
	*/
	for (int i=0;i<sizeof(crc)/sizeof(crc[0]);i++)
	{
		vInts.push_back(crc[i]);
	}
	/*
	 组成报文
	*/
	Byte *data=new Byte[vInts.size()];
	for (Byte i=0;i<vInts.size();i++)
	{
		data[i]=vInts[i];
	}
	/*
	 组成报文长度
	*/
	data[1]=vInts.size()-4;
	/*
	判断是不是rpt
	*/
	if (msg_out.msg_hdr.exp.TPDUtype==UNACKD_RPT)
	{
		//Write(data,(short)vInts.size());
		//Write(data,(short)vInts.size());
	}
	Write(data,(short)vInts.size());
}




