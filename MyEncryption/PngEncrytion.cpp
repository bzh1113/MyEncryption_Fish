#include "StdAfx.h"
#include "PngEncrytion.h"
#include "CommonString.h"



PngEncrytion::PngEncrytion(void)
{
	m_strChangeName = ".wuji";
}

PngEncrytion::~PngEncrytion(void)
{
}

unsigned char* PngEncrytion::getFileData( const char* pszFileName, const char* pszMode, unsigned long * pSize )
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

void PngEncrytion::EncytionToFile( char * szFileName )
{
	unsigned long nSize = 0;
	unsigned char *pBuffer = getFileData(szFileName, "rb", &nSize);
	EncryptionFunc(pBuffer,nSize);
	WriteToFile(szFileName,pBuffer,nSize);
}

void PngEncrytion::EncryptionFunc( unsigned char* pBuffer,unsigned long nSize )
{
	if (pBuffer && nSize>0)
	{
		for (int i=0; i<nSize; i++)
		{
			((unsigned char*)pBuffer)[i] ^= szPngEncrypStr[i%32];
		}
	}
}

void PngEncrytion::WriteToFile( const char* pszFileName, const unsigned char* pBuffer, unsigned long lSize ,bool bIsDecrypt )
{
	std::string NewPath(pszFileName);
	if (bIsDecrypt)//½âÃÜ
	{
		CString temp = DeleteEecryptFileKindStr(pszFileName,CHANGE_FILENAME_STR);
		std::string tempNewPath(temp.GetBuffer());
		NewPath=tempNewPath;
	}
	else	//¼ÓÃÜ
	{
		NewPath += CHANGE_FILENAME_STR;
	}
	FILE *fp = fopen(NewPath.c_str(), "wb");
	ASSERT(fp);
	fseek(fp,0,SEEK_SET);
	fwrite(pBuffer, lSize,1, fp);
	fclose(fp);
}

void PngEncrytion::DecryptToFile( char * szFileName )
{
	unsigned long nSize = 0;
	unsigned char *pBuffer = getFileData(szFileName, "rb", &nSize);
	DecryptFunc(pBuffer,nSize);
	WriteToFile(szFileName,pBuffer,nSize,true);
}

void PngEncrytion::DecryptFunc( unsigned char* pBuffer,unsigned long nSize )
{
	if (pBuffer && nSize>0)
	{
		for (int i=0; i<nSize; i++)
		{
			((unsigned char*)pBuffer)[i] ^= szPngEncrypStr[i%32];
		}
	}
}


