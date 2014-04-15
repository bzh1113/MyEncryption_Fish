#include "StdAfx.h"
#include "MainEncrytion.h"
#include "CommonString.h"

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

void MainEncrytion::WriteToFile( const char* pszFileName, const unsigned char* pBuffer, unsigned long lSize ,bool bIsDecrypt/*=false*/ )
{
	std::string NewPath(pszFileName);
	if (bIsDecrypt)//Ω‚√‹
	{
		CString temp = DeleteEecryptFileKindStr(pszFileName,CHANGE_FILENAME_STR);
		std::string tempNewPath(temp.GetBuffer());
		NewPath=tempNewPath;
	}
	else	//º”√‹
	{
		NewPath += CHANGE_FILENAME_STR;
	}
	FILE *fp = fopen(NewPath.c_str(), "wb");
	ASSERT(fp);
	fseek(fp,0,SEEK_SET);
	fwrite(pBuffer, lSize,1, fp);
	fclose(fp);
}

unsigned char* MainEncrytion::getFileData( const char* pszFileName, const char* pszMode, unsigned long * pSize )
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
		ASSERT(FALSE);
		std::string msg = "Get data from file(";
		msg.append(pszFileName).append(") failed!");
	}
	return pBuffer;
}

