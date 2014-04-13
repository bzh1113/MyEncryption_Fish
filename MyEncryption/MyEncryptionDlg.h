#include <vector>
#include "afxwin.h"
// MyEncryptionDlg.h : 头文件
//
using namespace std;
#pragma once


// CMyEncryptionDlg 对话框
class CMyEncryptionDlg : public CDialog
{
// 构造
public:
	CMyEncryptionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYENCRYPTION_DIALOG };
	enum
	{
		TAG_ENCRYPTEPNG,
		TAG_ENCRYPTEFILE,
		TAG_MAX
	};
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	

// 实现
protected:
	HICON m_hIcon;
	vector<CString>						m_strFilename;
	vector<CString>						m_strPngFileName;
	BYTE								m_cbEncrypteType;
	bool								m_bEnctytion;			//是否进行加密，否解密
//自定义函数
	//获取png文件
	void	GetPngFile(CString tp);
	//判断是什么类型的文件文件（传参：.png/.txt/.plist.....）
	bool    IsRightFileKind(CString str,CFileFind *ff =NULL, CString strfullpath="");
	//拖拽文件结束
	void	MyFileDragFinish();
	//根据类型改变按钮上显示的字
	void    ChangeEncrypteType(BYTE cbEncrypteType = TAG_ENCRYPTEPNG);
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	//获取文件数据存储到字符串中
	unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
	//加密png函数
	void EncryptionPngFunc(unsigned char* pBuffer,unsigned long nSize);
	//加密file函数
	void EncryptionFileFunc(unsigned char* pBuffer,unsigned long nSize);
	//对vector进行操作
	void OperaVector(vector<CString> &filename);
	//写入文件
	void WriteToFile(const char* pszFileName, const unsigned char* pBuffer, unsigned long lSize);


	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	long m_lPngCount;
	long m_lFlieCount;
	CButton m_btnEnctyType;
	afx_msg void OnBnClickedBtntype();
	CButton m_btnIsEncry;
	afx_msg void OnBnClickedIsencry();
	//生成操作
	afx_msg void OnBnClickedButton2();
	
};
