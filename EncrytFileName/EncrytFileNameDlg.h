
// EncrytFileNameDlg.h : ͷ�ļ�
//

#pragma once
#include "vector"
#include "afxwin.h"
using namespace std;

// CEncrytFileNameDlg �Ի���
class CEncrytFileNameDlg : public CDialog
{
// ����
public:
	CEncrytFileNameDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ENCRYTFILENAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//��ȡpng�ļ�
	void	GetFileName(CString tp);


	vector<CString>						m_strFilename;
	bool								m_bEnctytion;			//�Ƿ���м��ܣ������
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButton1();
	CButton m_cbEncrypteType;
};
