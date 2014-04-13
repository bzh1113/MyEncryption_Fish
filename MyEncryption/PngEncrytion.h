#pragma once
#include "MainEncrytion.h"
#include "vector"
using namespace std;

const char szEncrypStr[16] = {'b','e','c','a','u','s','e','i','s','p','n','g',13,14,15,16};

class PngEncrytion : public MainEncrytion
{
public:
	PngEncrytion(void);

	~PngEncrytion(void);

	virtual void EncytionToFile( char * szFileName );

	virtual void DecryptToFile( char * szFileName );

protected:

	virtual unsigned char* getFileData( const char* pszFileName, const char* pszMode, unsigned long * pSize );

	virtual void EncryptionFunc( unsigned char* pBuffer,unsigned long nSize );

	virtual void WriteToFile(const char* pszFileName, const unsigned char* pBuffer, unsigned long lSize ,bool bIsDecrypt=false);

	virtual void DecryptFunc( unsigned char* pBuffer,unsigned long nSize );

	std::string						m_strChangeName;
};
