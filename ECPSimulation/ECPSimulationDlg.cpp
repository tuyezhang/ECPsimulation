﻿
// ECPSimulationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ECPSimulation.h"
#include "ECPSimulationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CECPSimulationDlg 对话框




CECPSimulationDlg::CECPSimulationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CECPSimulationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CECPSimulationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cComboBox);
}

BEGIN_MESSAGE_MAP(CECPSimulationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CECPSimulationDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CECPSimulationDlg 消息处理程序

BOOL CECPSimulationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_cComboBox.AddString((LPCTSTR)"0号报文");
	m_cComboBox.AddString((LPCTSTR)"1号报文");
	int res=lonOP.Open("LON1");
	if(res!=-1)
		SetTimer(1,50,NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CECPSimulationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CECPSimulationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CECPSimulationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CECPSimulationDlg::OnBnClickedButton1()
{
	int messageID=m_cComboBox.GetCurSel();
	SendMessageByID(messageID);
}
void CECPSimulationDlg::SendMessageByID(int messageID)
{
	Byte msgdata[50]={0};
	
	switch(messageID)
	{
	case 0:{
		         
				Msg_sDevice_Info_Control_Query msg_send;
				msg_send.Command=(CCD<<2)|(UNLOCK);
				msg_send.Randomizing_Interval=3;
				memcpy(msgdata,&msg_send,sizeof(Msg_sDevice_Info_Control_Query));
				lonOP.setAddrBroadCast(0x01,0x03,0x01);
				lonOP.setMsgData(MSG_DEVICE_INFO_CONTROL_QUERY,0,msgdata,sizeof(Msg_sDevice_Info_Control_Query));
				lonOP.msg_put(UNACKD,NONPRIORITY);
		   }
		   break;
	case 1:{}
		   break;
	default:
		break;
	}
}


void CECPSimulationDlg::OnTimer(UINT_PTR nIDEvent)
	{
		switch(nIDEvent)
			{
				case 1:
					{
					   lonOP.Read(100);
					   Handle_Message();
					}
			}

		CDialogEx::OnTimer(nIDEvent);
	}


// 处理收到的数据
void CECPSimulationDlg::Handle_Message(void)
	{
	    switch(lonOP.getMsgInID())
			{
				case MSG_DEVICE_INFO_CONTROL_QUERY :handleOP.Handle_Message_3();
					break;
				case MSG_ASSIGN_NODE_ID: handleOP.Handle_Message_4();
					break;
				case MSG_HEU_BEACON :handleOP.Handle_Message_13();
					break;
				default:
					break; 
			}
	}
