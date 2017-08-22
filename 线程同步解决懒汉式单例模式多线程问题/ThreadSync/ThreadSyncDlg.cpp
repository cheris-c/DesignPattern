
// ThreadSyncDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ThreadSync.h"
#include "ThreadSyncDlg.h"
#include "afxdialogex.h"

#include <iostream>
using namespace std;

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


// CThreadSyncDlg 对话框



CThreadSyncDlg::CThreadSyncDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CThreadSyncDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadSyncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CThreadSyncDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CThreadSyncDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CThreadSyncDlg 消息处理程序

BOOL CThreadSyncDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CThreadSyncDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CThreadSyncDlg::OnPaint()
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
HCURSOR CThreadSyncDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////////
// Singleton.cpp : 定义控制台应用程序的入口点。
//

/*懒汉式单例模式多线程问题*/
/*利用临界区保证单例模式的正确性*/

//懒汉式单例

static CCriticalSection cs;

class Singleton
{
private:
	Singleton()
	{
		cout << "Singleton constructor called!" << endl;
	}
	~Singleton()
	{
		cout << "Singleton deconstructor called!" << endl;
	}

public:
	static Singleton* getInstance()		//获取实例
	{
		if (m_psl == NULL)
		{
			cs.Lock();		   //只有当m_psl为空时才开始加锁机制	 二次检查
			if (m_psl == NULL)
				m_psl = new Singleton();

			cs.Unlock();
		}
		return m_psl;
	}

	static void freeInstance()		//释放实例
	{
		if (m_psl != NULL)
		{
			delete m_psl;
			m_psl = NULL;
		}
	}

	void print()
	{
		cout << "Singleton test!" << endl;
	}

private:
	static Singleton *m_psl;
};

Singleton* Singleton::m_psl = NULL;

//////////////////////////////////////////////////////////////////////////////
void threadProc(void *)
{
	Singleton::getInstance()->print();
}

void CThreadSyncDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码

	//main1();
	HANDLE thread[10];

	for (int i = 0; i < 3; i++)
	{
		thread[i] = (HANDLE)_beginthread(threadProc, 0, NULL);
		if (thread[i] == NULL)
		{
			cout << "线程" << i << "创建失败" << endl;
			break;
		}
	}

	//挂起主线程,让出cpu,等待所有的子线程都执行完毕后再继续执行
	for (int i = 0; i < 3; i++)
	{
		WaitForSingleObject(thread[i], INFINITE);  //第二个参数为等待时间
	}
}
