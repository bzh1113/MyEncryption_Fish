#include "StdAfx.h"
#include "FileEncrytion.h"
#include "CommonString.h"

FileEncrytion::FileEncrytion(void)
{

}

FileEncrytion::~FileEncrytion(void)
{
}

void FileEncrytion::EncryptionFunc( unsigned char* pBuffer,unsigned long nSize )
{
	if (pBuffer && nSize>0)
	{
		for (int i=0; i<nSize; i++)
		{
			((unsigned char*)pBuffer)[i] ^= szFileEncrypStr[i%32];
		}
	}
}

void FileEncrytion::EncytionToFile( char * szFileName )
{
	unsigned long nSize = 0;
	unsigned char *pBuffer = getFileData(szFileName, "rb", &nSize);
	EncryptionFunc(pBuffer,nSize);
	WriteToFile(szFileName,pBuffer,nSize);
}

void FileEncrytion::DecryptFunc( unsigned char* pBuffer,unsigned long nSize )
{
	if (pBuffer && nSize>0)
	{
		for (int i=0; i<nSize; i++)
		{
			((unsigned char*)pBuffer)[i] ^= szFileEncrypStr[i%32];
		}
	}
}

void FileEncrytion::DecryptToFile( char * szFileName )
{
	unsigned long nSize = 0;
	unsigned char *pBuffer = getFileData(szFileName, "rb", &nSize);
	EncryptionFunc(pBuffer,nSize);
	WriteToFile(szFileName,pBuffer,nSize,true);
}

