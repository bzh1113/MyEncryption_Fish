#pragma once
#include "vector"
using namespace std;

class MainEncrytion
{
public:
	MainEncrytion(void);
	~MainEncrytion(void);
	//���ļ����м���
	virtual void EncytionToFile(char * szFileName) =0;
	//���ļ����н���
	virtual void DecryptToFile(char * szFileName) = 0;
	
protected:
	//��ȡ�ļ����ݴ洢���ַ�����
	virtual unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
	//���ܺ���
	virtual void EncryptionFunc(unsigned char* pBuffer,unsigned long nSize) = 0;
	//���ܺ���
	virtual void DecryptFunc(unsigned char* pBuffer,unsigned long nSize) = 0;
	//д���ļ�
	virtual void WriteToFile( const char* pszFileName, const unsigned char* pBuffer, unsigned long lSize ,bool bIsDecrypt=false);
	//�ж��Ƿ���ָ����׺��
	virtual bool IsRightFileKind(CString str, CString strfullpath="");
	//��ȡ�ļ���׺��
	virtual CString GetFileKindStr(CString strfullpath="");
	//ɾ�����ܵĺ�׺��
	virtual CString DeleteEecryptFileKindStr(const char* pszFileName,const char * pszFileKindStr);
	
};
