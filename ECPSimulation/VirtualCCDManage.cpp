#include "StdAfx.h"
#include "VirtualCCDManage.h"
#include "Lon2S4230.h"
extern CLon2S4230 lonOP;

CVirtualCCDManage::CVirtualCCDManage(void)
	{
	car_num=CAR_NUM_DEF;
	  
	      pCCD=new CvirtualCCD[car_num];
	
	}


CVirtualCCDManage::~CVirtualCCDManage(void)
	{
	}

CvirtualCCD *CVirtualCCDManage::Get_CCD_pObj(int i)
	{
	     if (i<car_num)
	     {
			 return &pCCD[i];
	     }
		 return NULL;
	}
void CVirtualCCDManage::Set_CCD_Num(int ccd_num)
	{
	   CvirtualCCD *pCCDtemp=pCCD;
	   CvirtualCCD *pCCD=new CvirtualCCD[car_num];
	   delete []pCCDtemp;

	}
void CVirtualCCDManage::Set_All_CCD_Lock()
	{
		for (int i=0;i<car_num;i++)
		{
			 pCCD[i].Set_CCD_Lock(true);
		}
		 
	}
void CVirtualCCDManage::Set_All_CCD_Unlock()
	{
		for (int i=0;i<car_num;i++)
		{
			pCCD[i].Set_CCD_Lock(false);
		}
	}

void CVirtualCCDManage::Set_CCD_Lock(int i)
	{
	   if (i<car_num)
	   {
			pCCD[i].Set_CCD_Lock(true);
	   }
	}
void CVirtualCCDManage::Set_CCD_Unlock(int i)
	{
	if (i<car_num)
		{
			pCCD[i].Set_CCD_Lock(false);
		}
	}
int CVirtualCCDManage:: Return_Match_CCD_Nid()
	{
	   for (int i=0;i<car_num;i++)
	   {
		   if (pCCD[i].Is_NID_Match(lonOP.msg_in.msg_addr.rsp.id.nid,6))
		   {
				return i;
		   }
	   }
	   return -1;
	}
