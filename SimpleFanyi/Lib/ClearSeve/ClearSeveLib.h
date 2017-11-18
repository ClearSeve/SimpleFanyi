#pragma once


//************************************
// Method:    GetPathSuffix
// FullName:  ��ȡ�ļ���׺����
// Access:    public 
// Returns:   ���غ�׺ .xxx
// Qualifier:
// Parameter: strFileName �ļ���.xxx
//************************************
CString GetPathSuffix(CString strFileName);

//************************************
// Method:    IsFilExists
// FullName:  �ж��ļ��Ƿ����
// Access:    public 
// Returns:   TRUE�ļ����� FALSE�ļ�������
// Qualifier:
// Parameter: strFilePath �ļ�·��
//************************************
BOOL IsFilExists(CString strFilePath);

//************************************
// Method:    ShowLog
// FullName:  ��������ʾ����������ַ���
// Access:    public 
// Returns:   VOID
// Qualifier:
// Parameter: strLog ��Ҫ��ʾ���ַ���
//************************************
VOID ShowLog(CString strLog);


//************************************
// Method:    WToM
// FullName:  �����ֽ��ַ���ת��Ϊ���ֽ��ַ���
// Access:    public 
// Returns:   char*
// Qualifier: ʹ�������Ҫ����free���������ͷ�
// Parameter: str ��Ҫת�����ַ���
//************************************
char* WToM(const CString& str);

// �����ֽ��ַ���ת��Ϊ���ֽ��ַ���
wchar_t* MToW(char* pstr, UINT nCodePage = CP_ACP);