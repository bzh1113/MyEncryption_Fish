
// EncrytFileName.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEncrytFileNameApp:
// �йش����ʵ�֣������ EncrytFileName.cpp
//

class CEncrytFileNameApp : public CWinAppEx
{
public:
	CEncrytFileNameApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEncrytFileNameApp theApp;