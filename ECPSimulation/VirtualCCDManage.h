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
        这个函数配合 Get_CCD_Num使用 可以遍历 每个CCD指针 然后 我现在把 虚拟CCD类中结构体定义为了public 这样就可以读取相应的CCD信息
        */
        CvirtualCCD *Get_CCD_pObj( int i );//根据虚拟CCD的索引得到相应虚拟CCD的指针
        void Set_CCD_Num( int ccd_num );//设置虚拟CCD的数量
        int Get_CCD_Num();//返回ccd的数量
		/*对CCD信息的一些设定*/
        void Set_All_CCD_Lock();//设置所有CCD LOCK
        void Set_All_CCD_Unlock();//设置所有CCD UNLOCK
        void Set_CCD_Lock( int i );//设置索引为 i的CCD LOCK
        void Set_CCD_Unlock( int i );//设置索引为 i的CCD UNLOCK
        void Set_Subnet_Node( Byte subnet , Byte node, int index );//设置索引为index的 subnet 和node

		/*通过各种关系返回CCD索引*/
        int Return_Match_CCD_Nid();//根据msg_in的nid 返回CCD 的索引
        int Return_Match_CCD_Nid( Byte * nid, Byte length ); // 根据给定参数的nid 返回对应CCD   NID  的索引
        int Return_Match_CCD_Subnet_Node( Byte subnet, Byte node ); // 根据给定参数的subnet node 返回CCD   subnet node  的索引
		/*相应3号报文发送7号报文*/
        void Send_CCD_Info_ALL( int randomizing_interval ); //发送所有CCD信息根据随机间隔
        void Send_CCD_Info( int index ); //对 索引为 index 的 CCD 发送 CCD info  ~现在可以先不调用~

        /*后面这四个现在可以先不用*/
        void Set_CCD_Node_Information();//设置CCD节点信息  ~现在可以先不调用~
        void Set_CCD_Car_Info();//设置CCD信息  ~现在可以先不调用~
        void Set_CCD_Status();//设置CCD状态信息 ~现在可以先不调用~
        /*
          初始化时应该就会调用这个
        */
        void Set_CCD_ALL_Data();//设置CCD包括的所有信息 可单独调用这个,不用上面三个 也可分别调用上面三个 ~现在可以先不调用~


    private:
        int car_num;
        CvirtualCCD * pCCD;
        CLon2S4230 lonOP;

};

