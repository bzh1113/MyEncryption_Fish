#include <vector>
#include "afxwin.h"
// MyEncryptionDlg.h : ͷ�ļ�
//
using namespace std;
#pragma once


// CMyEncryptionDlg �Ի���
class CMyEncryptionDlg : public CDialog
{
// ����
public:
	CMyEncryptionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYENCRYPTION_DIALOG };
	enum
	{
		TAG_ENCRYPTEPNG,
		TAG_ENCRYPTEFILE,
		TAG_MAX
	};
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	

// ʵ��
protected:
	HICON m_hIcon;
	vector<CString>						m_strFilename;
	vector<CString>						m_strPngFileName;
	BYTE								m_cbEncrypteType;
	bool								m_bEnctytion;			//�Ƿ���м��ܣ������
//�Զ��庯��
	//��ȡpng�ļ�
	void	GetPngFile(CString tp);
	//�ж���ʲô���͵��ļ��ļ������Σ�.png/.txt/.plist.....��
	bool    IsRightFileKind(CString str,CFileFind *ff =NULL, CString strfullpath="");
	//��ק�ļ�����
	void	MyFileDragFinish();
	//�������͸ı䰴ť����ʾ����
	void    ChangeEncrypteType(BYTE cbEncrypteType = TAG_ENCRYPTEPNG);
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	//��ȡ�ļ����ݴ洢���ַ�����
	unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
	//����png����
	void EncryptionPngFunc(unsigned char* pBuffer,unsigned long nSize);
	//����file����
	void EncryptionFileFunc(unsigned char* pBuffer,unsigned long nSize);
	//��vector���в���
	void OperaVector(vector<CString> &filename);
	//д���ļ�
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
	//���ɲ���
	afx_msg void OnBnClickedButton2();
	
};
