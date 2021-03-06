
// EncrytFileNameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EncrytFileName.h"
#include "EncrytFileNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CEncrytFileNameDlg 对话框




CEncrytFileNameDlg::CEncrytFileNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEncrytFileNameDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEncrytFileNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_cbEncrypteType);
}

BEGIN_MESSAGE_MAP(CEncrytFileNameDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CEncrytFileNameDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CEncrytFileNameDlg 消息处理程序

BOOL CEncrytFileNameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	m_bEnctytion = true;


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEncrytFileNameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEncrytFileNameDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEncrytFileNameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEncrytFileNameDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	m_strFilename.clear();
	UINT uFileNum=::DragQueryFile(hDropInfo,0xffffffff,NULL,0); 
	if (m_bEnctytion)//加密状态
	{
		WCHAR strFileName[MAX_PATH]; 
		for (int i=0;i<uFileNum;i++) 
		{ 
			ZeroMemory(&strFileName, sizeof(strFileName));
			::DragQueryFileW(hDropInfo,i,strFileName,MAX_PATH); 
			CString strTempFilename(strFileName); 
			//如果不是文件目录
			if  (GetFileAttributesW(strFileName) != FILE_ATTRIBUTE_DIRECTORY) 
			{
				m_strFilename.push_back(strTempFilename );
			}
			else
			{
				GetFileName(strTempFilename);
			}
		} 
	}
	else		//解密状态
	{
		WCHAR strFileName[MAX_PATH]; 
		for (int i=0;i<uFileNum;i++) 
		{ 
			ZeroMemory(&strFileName, sizeof(strFileName));
			::DragQueryFileW(hDropInfo,i,strFileName,MAX_PATH); 
			CString strTempFilename(strFileName); 
			//如果不是文件目录
			if  (GetFileAttributesW(strFileName) != FILE_ATTRIBUTE_DIRECTORY) 
			{
				m_strFilename.push_back(strTempFilename );
			}
			else
			{
				GetFileName(strTempFilename);
			}
		} 
	}



	::DragFinish(hDropInfo); 

	CDialog::OnDropFiles(hDropInfo);
}

void CEncrytFileNameDlg::GetFileName( CString tp )
{
	CFileFind fileFinder;
	CString filePath = tp + _T("\\*.*");
	BOOL bFinished = fileFinder.FindFile(filePath);
	while(bFinished)  //每次循环对应一个类别目录
	{
		bFinished = fileFinder.FindNextFile();
		if(fileFinder.IsDirectory() && !fileFinder.IsDots())  //若是目录则递归调用此方法
		{
			GetFileName(fileFinder.GetFilePath());
		}
		else  //再判断文件
		{
			CString fullfilename = fileFinder.GetFilePath();
			m_strFilename.push_back(fullfilename);
		}
	}
	fileFinder.Close();
}

void CEncrytFileNameDlg::OnBnClickedButton1()
{
	m_bEnctytion = !m_bEnctytion;
	if (m_bEnctytion)
	{
		m_cbEncrypteType.SetWindowText("加密");
	}
	else
	{
		m_cbEncrypteType.SetWindowText("解密");
	}
}
