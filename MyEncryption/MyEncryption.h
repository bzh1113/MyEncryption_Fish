
// MyEncryption.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyEncryptionApp:
// �йش����ʵ�֣������ MyEncryption.cpp
//

class CMyEncryptionApp : public CWinAppEx
{
public:
	CMyEncryptionApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyEncryptionApp theApp;