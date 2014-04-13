#include "StdAfx.h"
#include "MainEncrytion.h"

MainEncrytion::MainEncrytion(void)
{
}

MainEncrytion::~MainEncrytion(void)
{
}

bool MainEncrytion::IsRightFileKind( CString str, CString strfullpath/*=""*/ )
{
	int dotPos=strfullpath.ReverseFind('.');
	CString fileExt=strfullpath.Right(strfullpath.GetLength()-dotPos);
	if(fileExt == str)  
	{
		return true;
	}
	return false;
}

CString MainEncrytion::GetFileKindStr( CString strfullpath/*=""*/ )
{
	int dotPos=strfullpath.ReverseFind('.');
	CString fileExt=strfullpath.Right(strfullpath.GetLength()-dotPos);
	return fileExt;
}

CString MainEncrytion::DeleteEecryptFileKindStr( const char* pszFileName,const char * pszFileKindStr )
{
	CString strFileName = pszFileName;
	CString strFileKindStr = pszFileKindStr;
	strFileName.Delete(strFileName.GetLength()- strFileKindStr.GetLength(), strFileKindStr.GetLength());
	return strFileName;
} 

