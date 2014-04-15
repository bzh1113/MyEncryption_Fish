
// EncrytFileNameDlg.h : 头文件
//

#pragma once
#include "vector"
#include "afxwin.h"
using namespace std;

// CEncrytFileNameDlg 对话框
class CEncrytFileNameDlg : public CDialog
{
// 构造
public:
	CEncrytFileNameDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ENCRYTFILENAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//获取png文件
	void	GetFileName(CString tp);


	vector<CString>						m_strFilename;
	bool								m_bEnctytion;			//是否进行加密，否解密
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButton1();
	CButton m_cbEncrypteType;
};
