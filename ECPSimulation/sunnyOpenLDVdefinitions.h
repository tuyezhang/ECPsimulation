//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	OpenLDV Developer Example
/// <OpenLDV-Example Revision="1"/>
//	Copyright (c) 2004 Echelon Corporation. All rights reserved.
//
//	This file is defined as Example Software in, and use governed by, the
//	OpenLDV Software License Agreement.
//
//	ECHELON MAKES NO REPRESENTATION, WARRANTY, OR CONDITION OF
//	ANY KIND, EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE OR IN
//	ANY COMMUNICATION WITH YOU, INCLUDING, BUT NOT LIMITED TO,
//	ANY IMPLIED WARRANTIES OF MERCHANTABILITY, SATISFACTORY
//	QUALITY, FITNESS FOR ANY PARTICULAR PURPOSE,
//	NONINFRINGEMENT, AND THEIR EQUIVALENTS.
//
//	OpenLDVdefinitions.h: header file containing commonly used type 
//	definitions, enumerations and constants useful to access and use
//	the OpenLDV API.
//                                                                                  
//	++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#ifndef _NI_COMM_H
#define _NI_COMM_H

//
//	Note the types and structures defined here must match the ANSI/EIA/CEA 709.1
//	protocol specification. Data types defined there (or in the related literature)
//	typically assume a data packing of 1 (one) byte, a padding of 0 (zero), and 
//	big-endian ordering for both aggregated types and bitfields. 
//	When adding more definitions, when using this header file with a compiler 
//	other than Microsoft Visual Studio .NET 2003, or when porting these definitions
//	to a programming language other than ANSI-C or ANSI-C++, care must be taken to 
//	model these types such that the host compiler produces the layout and alignment
//	required by protocol.
//	
#pragma pack(push,1)

#ifdef __cplusplus
extern "C"
{            /* Assume C declarations for C++ */
	namespace ldv
	{
#endif  /* __cplusplus */

#define niDEFAULT_WAIT_TIME 10			/* Seconds */
#define	NEURON_ID_LEN		6			/* 6 bytes per Neuron ID */
#define	PROGRAM_ID_LEN		8			/* 8 bytes per program ID */
#define DOMAIN_ID_LEN		6			// maximum domain ID length (possible values: 0, 1, 3, 6)
#define	AUTH_KEY_LEN		6			// authentication key size per domain table index

		typedef unsigned char	Byte;
		typedef unsigned short	Word;
		typedef Byte			Bits;
		typedef Byte			Bool;

		/*
		****************************************************************************
		* Application buffer structures for sending and receiving messages to and
		* from a network interface.  The 'ExpAppBuffer' and 'ImpAppBuffer'
		* structures define the application buffer structures with and without
		* explicit addressing.  These structures have up to four parts:
		*
		*   Network Interface Command (NI_Hdr)                        (2 Bytes)
		*   Message Header (MsgHdr)                                   (3 Bytes)
		*   Network Address (ExplicitAddr)                            (11 Bytes)
		*   Data (MsgData)                                            (varies)
		*
		* Network Interface Command (NI_Hdr):
		*
		*   The network interface command is always present.  It contains the
		*   network interface command and queue specifier.  This is the only
		*   field required for local network interface commands such as niRESET.
		*
		* Message Header (MsgHdr: union of NetVarHdr and ExpMsgHdr):
		*
		*   This field is present if the buffer is a data transfer or a completion
		*   event.  The message header describes the type of LONTALK message
		*   contained in the data field.
		*
		*   NetVarHdr is used if the message is a network variable message and
		*   network interface selection is enabled.
		*
		*   ExpMsgHdr is used if the message is an explicit message, or a network
		*   variable message and host selection is enabled (this is the default
		*   for the SLTA).
		*
		* Network Address (ExplicitAddr:  SendAddrDtl, RcvAddrDtl, or RespAddrDtl)
		*
		*   This field is present if the message is a data transfer or completion
		*   event, and explicit addressing is enabled.  The network address
		*   specifies the destination address for downlink application buffers,
		*   or the source address for uplink application buffers.  Explicit
		*   addressing is the default for the SLTA.
		*
		*   SendAddrDtl is used for outgoing messages or NV updates.
		*
		*   RcvAddrDtl is used  for incoming messages or unsolicited NV updates.
		*
		*   RespAddrDtl is used for incoming responses or NV updates solicited
		*   by a poll.
		*
		* Data (MsgData: union of UnprocessedNV, ProcessedNV, and ExplicitMsg)
		*
		*   This field is present if the message is a data transfer or completion
		*   event.
		*
		*   If the message is a completion event, then the first two Bytes of the
		*   data are included.  This provides the NV index, the NV selector, or the
		*   message code as appropriate.
		*
		*   UnprocessedNV is used if the message is a network variable update, and
		*   host selection is enabled. It consists of a two-Byte header followed by
		*   the NV data.
		*
		*   ProcessedNV is used if the message is a network variable update, and
		*   network interface selection is enabled. It consists of a two-Byte header
		*   followed by the NV data.
		*
		*   ExplicitMsg is used if the message is an explicit message.  It consists
		*   of a one-Byte code field followed by the message data.
		*
		* Note - the fields defined here are for a little-endian (Intel-style)
		* host processor, such as the 80x86 processors used in PC compatibles.
		* Bit fields are allocated right-to-left within a Byte.
		* For a big-endian (Motorola-style) host, bit fields are typically
		* allocated left-to-right.  For this type of processor, reverse
		* the bit fields within each Byte.  Compare the NEURON C include files
		* ADDRDEFS.H and MSG_ADDR.H, which are defined for the big-endian NEURON
		* CHIP.
		****************************************************************************
		*/


		/*
		****************************************************************************
		* Network Interface Command data structure.  This is the application-layer
		* header used for all messages to and from a LONWORKS network interface.
		****************************************************************************
		*/

	   
   

	 
	   

		/*
		* MAX_NETMSG_DATA specifies the maximum size of the data portion of an
		* application buffer.  MAX_NETVAR_DATA specifies the maximum size of the
		* data portion of a network variable update.  The values specified here
		* are the absolute maximums,based on the LONTALK protocol. Actual limits
		* are based on the buffer sizes defined on the attached NEURON CHIP.
		*/

#define MAX_NETMSG_DATA		228	// max payload for application message
#define MAX_NETVAR_DATA		31	// max payload for network variable
#define	MAX_OPENLDV_DATA	257	// max transfer unit size to/from OpenLDV driver

		/*
		* Header for network interface messages.  The header is a union of
		* two command formats: the 'q' format is used for the niCOMM and
		* niNETMGMT commands that require a queue specification; the 'noq'
		* format is used for all other network interface commands.
		* Both formats have a length specification where:
		*
		*      length = header (3) + address field (11 if present) + data field
		*
		* WARNING:  The fields shown in this structure do NOT reflect the actual
		* structure required by the network interface.  Depending on the network
		* interface, the network driver may change the order of the data and add
		* additional fields to change the application-layer header to a link-layer
		* header.  See the description of the link-layer header in Chapter 2 of the
		* Host Application Programmer's Guide.
		*/

	   


		/*
		****************************************************************************
		* Message Header structure for sending and receiving explicit
		* messages and network variables which are not processed by the
		* network interface (host selection enabled).
		****************************************************************************
		*/

		/* Literals for 'st' fields of ExpMsgHdr and NetVarHdr. */

		typedef enum
		{
				ACKD            = 0,
				UNACKD_RPT      = 1,
				UNACKD          = 2,
		} TPDUTYPE;

		typedef enum{
			      NONPRIORITY     =0,
				  PRIORITY        =1,

		}Priority;

		typedef enum
		{
				TPDU            = 0,
				APDU            = 3,
		} PDUFMT;
		
		 typedef enum
		{
				BROADCAST         =0,
				SUBNET_NODE       = 2,
				NEURON_ID         = 3,
		} ADDRFMT;

		  typedef enum
		{
				a				 =0,
				b                =1,
				c				 =2,
				d				 =3,
				e                =4,
				f				 =5,
		} MSGCODE;


	  
		/* Explicit message and Unprocessed NV Application Buffer. */

		typedef struct {   
			Bits   Priority  :1;        /* 1 => Priority message                */
			Bits   AddrFmt   :2;
			Bits   TPDUtype  :3;
			Bits   PDUFmt    :2;
			Byte   Length;     
		} ExpMsgHdr;

	   
	   

		/*
		****************************************************************************
		* Network Address structures for sending messages with explicit addressing
		* enabled.
		****************************************************************************
		*/

		/* Literals for 'type' field of destination addresses for outgoing messages. */

		

		/* Subnet/node ID address.  Use for a unicast destination address. */
		typedef struct {
			Bits   inode      :7;        /* my Node number                          */
			Bits   isubnet    :8;        /* my Subnet ID                            */
			Bits   node      :7;        /* Node number                          */
			Bits   subnet    :8;        /* Subnet ID                            */
		} SendSnode;

		/* 48-bit NEURON ID destination address. */
		typedef struct {
			Bits   inode      :7;        /* my Node number                          */
			Bits   isubnet    :8;        /* my Subnet ID                            */
			Bits   subnet     :8;       /* Subnet ID, 0 => pass all routers     */
			Byte   nid[ NEURON_ID_LEN ];  /* NEURON ID                          */
		} SendNrnid;

		/* Broadcast destination address. */
		typedef struct {
			Bits   inode      :7;        /* my Node number                          */
			Bits   isubnet    :8;        /* my Subnet ID                            */
			Bits   subnet      :8;      /* Subnet ID, 0 => domain-wide          */
		} SendBcast;

	   

	   

		/* Union of all destination addresses. */
		typedef union
		{            
			SendSnode      sn;
			SendBcast      bc;
			SendNrnid      id;
		} AddrDtl;


	 
		/*
		****************************************************************************
		* Data field structures for explicit messages and network variables.
		****************************************************************************
		*/

	  
		/* Data field for explicit messages. */

		typedef struct {
			Byte       code;                  /* Message code                     */
			Byte       data[MAX_NETMSG_DATA]; /* Message data                     */
		} ExplicitMsg;

		/* Data field for any driver-specific data. This field also denotes the maximum		*
		* size of the transfer unit to and from the OpenLDV driver, which is 257 byte.		*
		* Although that maximum transfer unit is not typically used, defining the			*
		* ExpAppBuffer structure (below) such that is covers that entire maximum transfer	*
		* unit size allows for all clients of all possible OpenLDV interfaces to declare	*
		* a sufficiently large data storage.												*/

		
		typedef union
		{
			ExpMsgHdr  exp;
			
		} MsgHdr;


		typedef union
		{
			ExplicitMsg   exp;
			
		} MsgData;
	   
		typedef union
		{
			
			AddrDtl rsp;
		} ExplicitAddr;

		/*
		****************************************************************************
		* Message buffer types.
		****************************************************************************
		*/

		/* Application buffer when using explicit addressing. */
		typedef struct {
			MsgHdr       msg_hdr;           /* Message header */
			ExplicitAddr msg_addr;              /* Network address */
			MsgData      msg_data;              /* Message data */
		} ExpApp;
  

#ifdef __cplusplus
	}	// namespace
}	// extern
#endif  /* __cplusplus */

#pragma pack(pop)

#endif
