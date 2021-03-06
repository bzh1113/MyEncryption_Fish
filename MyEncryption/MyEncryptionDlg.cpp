#include "stdafx.h"
#include "MyEncryption.h"
#include "MyEncryptionDlg.h"
#include <io.h>
#include <fstream>
#include <iostream>
#include "PngEncrytion.h"
#include "FileEncrytion.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define CC_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = 0; } } while(0)
CString strType[2] = {"当前为PNG加密", "当前为FILE加密"};

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


// CMyEncryptionDlg 对话框




CMyEncryptionDlg::CMyEncryptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyEncryptionDlg::IDD, pParent)
	, m_lPngCount(0)
	, m_lFlieCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyEncryptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PNG_COUNT, m_lPngCount);
	DDX_Text(pDX, IDC_FILE_COUNT, m_lFlieCount);
	DDX_Control(pDX, ID_BTNTYPE, m_btnEnctyType);
	DDX_Control(pDX, ID_ISENCRY, m_btnIsEncry);
	//DDX_Control(pDX, IDC_CHECK1, m_CheckDelete);
}

BEGIN_MESSAGE_MAP(CMyEncryptionDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
	ON_BN_CLICKED(ID_BTNTYPE, &CMyEncryptionDlg::OnBnClickedBtntype)
	ON_BN_CLICKED(IDC_ISENCRY, &CMyEncryptionDlg::OnBnClickedIsencry)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyEncryptionDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMyEncryptionDlg 消息处理程序

BOOL CMyEncryptionDlg::OnInitDialog()
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
	m_strFilename.clear();
	m_strPngFileName.clear();
	ChangeEncrypteType(TAG_ENCRYPTEPNG);
	m_bEnctytion = false;
	OnBnClickedIsencry();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyEncryptionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyEncryptionDlg::OnPaint()
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
HCURSOR CMyEncryptionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMyEncryptionDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	m_strFilename.clear();
	m_strPngFileName.clear();
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
				if (m_cbEncrypteType == TAG_ENCRYPTEFILE)//加密文件
				{
					m_strFilename.push_back(strTempFilename );
				}
				else if (IsRightFileKind(".png", NULL, strTempFilename))
				{
					m_strPngFileName.push_back(strTempFilename );
				}
			}
			else
			{
				GetPngFile(strTempFilename);
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
				if (m_cbEncrypteType == TAG_ENCRYPTEFILE)
				{
					m_strFilename.push_back(strTempFilename );
				}
				else if (IsRightFileKind(".zhb", NULL, strTempFilename))
				{
					m_strPngFileName.push_back(strTempFilename );
				}
			}
			else
			{
				GetPngFile(strTempFilename);
			}
		} 
	}

	

	::DragFinish(hDropInfo); 
	MyFileDragFinish();
	
	CDialog::OnDropFiles(hDropInfo);
}

void CMyEncryptionDlg::GetPngFile( CString tp )
{
	CFileFind fileFinder;
	CString filePath = tp + _T("\\*.*");
   BOOL bFinished = fileFinder.FindFile(filePath);
   while(bFinished)  //每次循环对应一个类别目录
   {
      bFinished = fileFinder.FindNextFile();
      if(fileFinder.IsDirectory() && !fileFinder.IsDots())  //若是目录则递归调用此方法
      {
             GetPngFile(fileFinder.GetFilePath());
      }
      else  //再判断文件
      {
		  if (m_cbEncrypteType == TAG_ENCRYPTEFILE)
		  {
			  CString fullfilename = fileFinder.GetFilePath();
			  m_strFilename.push_back(fullfilename);
		  } 
		  else if(IsRightFileKind(".png", &fileFinder)) //判断是否是想要的文件类型文件类型
		  {
			  CString fullfilename = fileFinder.GetFilePath();
			  m_strPngFileName.push_back(fullfilename);
		  }
      }
   }
   fileFinder.Close();
}

bool CMyEncryptionDlg::IsRightFileKind( CString str, CFileFind *ff, CString strfullpath )
{
	//获取文件类型
	if (ff)
	{
		CString fileName = ff->GetFileName();
		int dotPos=fileName.ReverseFind('.');
		CString fileExt=fileName.Right(fileName.GetLength()-dotPos);
		if(fileExt == str) 
		{
			return true;
		}
	}
	else
	{
		int dotPos=strfullpath.ReverseFind('.');
		CString fileExt=strfullpath.Right(strfullpath.GetLength()-dotPos);
		if(fileExt == str)  
		{
			return true;
		}
	}
	return false;

}

void CMyEncryptionDlg::MyFileDragFinish()
{
	m_lPngCount = m_strPngFileName.size();
	m_lFlieCount = m_strFilename.size();
	UpdateData(FALSE);
}

void CMyEncryptionDlg::ChangeEncrypteType(BYTE cbEncrypteType)
{
	m_cbEncrypteType = cbEncrypteType;
	if (m_cbEncrypteType == TAG_ENCRYPTEPNG)
	{
		m_btnEnctyType.SetWindowText(strType[TAG_ENCRYPTEPNG]);
	}
	else if(m_cbEncrypteType == TAG_ENCRYPTEFILE)
	{
		m_btnEnctyType.SetWindowText(strType[TAG_ENCRYPTEFILE]);
	}
}



void CMyEncryptionDlg::OnBnClickedBtntype()
{
	ASSERT(m_cbEncrypteType<TAG_MAX);
	m_cbEncrypteType++;
	if (m_cbEncrypteType>=TAG_MAX)
	{
		m_cbEncrypteType = TAG_ENCRYPTEPNG;
	}
	ChangeEncrypteType(m_cbEncrypteType);
}


void CMyEncryptionDlg::OnBnClickedIsencry()
{
	m_bEnctytion = !m_bEnctytion;
	if(m_bEnctytion)
	{
		m_btnIsEncry.SetWindowText("加密");
	}
	else
	{
		m_btnIsEncry.SetWindowText("解密");
	}
}

void CMyEncryptionDlg::OnBnClickedButton2()
{
	if (m_strPngFileName.size()>0)
	{
		PngEncrytion enctyt;
		for(int i=0; i<m_strPngFileName.size(); i++)
		{
// 			unsigned long nSize = 0;
// 			unsigned char *pBuffer = getFileData(m_strPngFileName[i].GetBuffer(), "rb", &nSize);
// 			EncryptionPngFunc(pBuffer, nSize);
			if (m_bEnctytion)
			{
				enctyt.EncytionToFile(m_strPngFileName[i].GetBuffer());
			}
			else
			{
				enctyt.DecryptToFile(m_strPngFileName[i].GetBuffer());
			}
			if (IsDlgButtonChecked(IDC_CHECKDEL))
			{
				CFile TempFile; 
				TempFile.Remove(m_strPngFileName[i]);
			}
		}

	}
	else if(m_strFilename.size()>0)			//文件加密
	{
		FileEncrytion enctyt;
		for(int i=0; i<m_strFilename.size(); i++)
		{
			// 			unsigned long nSize = 0;
			// 			unsigned char *pBuffer = getFileData(m_strPngFileName[i].GetBuffer(), "rb", &nSize);
			// 			EncryptionPngFunc(pBuffer, nSize);
			if (m_bEnctytion)
			{
				enctyt.EncytionToFile(m_strFilename[i].GetBuffer());
			}
			else
			{
				enctyt.DecryptToFile(m_strFilename[i].GetBuffer());
			}
			if (IsDlgButtonChecked(IDC_CHECKDEL))
			{
				CFile TempFile; 
				TempFile.Remove(m_strFilename[i]);
			}
		}
	}
	m_lPngCount = 0;
	m_lFlieCount = 0;
	UpdateData(FALSE);
}

unsigned char* CMyEncryptionDlg::getFileData( const char* pszFileName, const char* pszMode, unsigned long * pSize )
{
	unsigned char * pBuffer = NULL;
	ASSERT(pszFileName != NULL && pSize != NULL && pszMode != NULL);
	*pSize = 0;
	do
	{
		// read the file from hardware
		std::string fullPath(pszFileName);
		FILE *fp = fopen(fullPath.c_str(), pszMode);
		ASSERT(fp);

		fseek(fp,0,SEEK_END);
		*pSize = ftell(fp);
		fseek(fp,0,SEEK_SET);
		pBuffer = new unsigned char[*pSize];
		*pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
		fclose(fp);
	} while (0);

	if (! pBuffer)
	{
		std::string msg = "Get data from file(";
		msg.append(pszFileName).append(") failed!");

	}
	return pBuffer;
}

void CMyEncryptionDlg::EncryptionPngFunc( unsigned char* pBuffer ,unsigned long nSize)
{
	if (pBuffer && nSize>0)
	{
		char szTable[16] = {1,2,3,4,5,6,7,8,9,10,11,1,13,14,15,16};
		for (int i=0; i<nSize; i++)
		{
			((unsigned char*)pBuffer)[i] ^= szTable[i%16];
		}
	}
}

void CMyEncryptionDlg::OperaVector( vector<CString> &filename )
{
	for (int i=0; i<filename.size(); i++)
	{

	}
}

void CMyEncryptionDlg::EncryptionFileFunc( unsigned char* pBuffer,unsigned long nSize )
{
	
}

void CMyEncryptionDlg::WriteToFile( const char* pszFileName, const unsigned char* pBuffer, unsigned long lSize )
{
	std::string NewPath(pszFileName);
	NewPath += ".zhb";
	FILE *fp = fopen(NewPath.c_str(), "rb+");
	ASSERT(fp);
	fseek(fp,0,SEEK_SET);
	fwrite(pBuffer, lSize,1, fp);
	fclose(fp);
}


