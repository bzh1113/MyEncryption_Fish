#pragma once
#include "vector"
using namespace std;

class MainEncrytion
{
public:
	MainEncrytion(void);
	~MainEncrytion(void);
	//对文件进行加密
	virtual void EncytionToFile(char * szFileName) =0;
	//对文件进行解密
	virtual void DecryptToFile(char * szFileName) = 0;
	
protected:
	//获取文件数据存储到字符串中
	virtual unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
	//加密函数
	virtual void EncryptionFunc(unsigned char* pBuffer,unsigned long nSize) = 0;
	//解密函数
	virtual void DecryptFunc(unsigned char* pBuffer,unsigned long nSize) = 0;
	//写入文件
	virtual void WriteToFile( const char* pszFileName, const unsigned char* pBuffer, unsigned long lSize ,bool bIsDecrypt=false);
	//判断是否是指定后缀名
	virtual bool IsRightFileKind(CString str, CString strfullpath="");
	//获取文件后缀名
	virtual CString GetFileKindStr(CString strfullpath="");
	//删除加密的后缀名
	virtual CString DeleteEecryptFileKindStr(const char* pszFileName,const char * pszFileKindStr);
	
};
