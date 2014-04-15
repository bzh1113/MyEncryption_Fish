#pragma once
#include "MainEncrytion.h"
#include "vector"
using namespace std;

const char szFileEncrypStr[32] = {'b','e','c','a','u','s','e','i','s','F','I','L',13,14,15,16,
'F','I','L','i','s','s','o','b','e','a','u','t','i','f','u','l'};

class FileEncrytion:public MainEncrytion
{
public:
	FileEncrytion(void);
	~FileEncrytion(void);

	virtual void EncryptionFunc( unsigned char* pBuffer,unsigned long nSize );

	virtual void EncytionToFile( char * szFileName );

	virtual void DecryptFunc( unsigned char* pBuffer,unsigned long nSize );

	virtual void DecryptToFile( char * szFileName );

protected:
	std::string						m_strChangeName;
};
