#include "stdafx.h"
#include "ClearSeveLib.h"

//************************************
// Method:    GetPathSuffix
// FullName:  ��ȡ�ļ���׺����
// Access:    public 
// Returns:   ���غ�׺ .xxx
// Qualifier:
// Parameter: strFileName �ļ���.xxx
//************************************
CString GetPathSuffix(CString strFileName)
{
	int pos = strFileName.Find(_T(".")); //��ȡ. ��λ��
	if (pos == -1){ //���û���ҵ���ֱ�ӷ��ظ��ַ���
		return strFileName;
	}
	else{
		return GetPathSuffix(strFileName.Mid(pos + 1)); //�ҵ��˵Ļ�������������ֱ����ײ�
	}
}

//************************************
// Method:    IsFilExists
// FullName:  �ж��ļ��Ƿ����
// Access:    public 
// Returns:   TRUE�ļ����� FALSE�ļ�������
// Qualifier:
// Parameter: strFilePath �ļ�·��
//************************************
BOOL IsFilExists(CString strFilePath)
{
	// �����ļ���ѯ�ṹ��
	WIN32_FIND_DATA Find_Data = { 0 };
	// �����ļ�
	FindFirstFile(strFilePath, &Find_Data);
	// �ж��ļ���
	if (wcscmp(Find_Data.cFileName, _T("")) != 0)
	{
		return TRUE;
	}
	return FALSE;
}

//************************************
// Method:    ShowLog
// FullName:  ��������ʾ����������ַ���
// Access:    public 
// Returns:   VOID
// Qualifier:
// Parameter: strLog ��Ҫ��ʾ���ַ���
//************************************
VOID ShowLog(CString strLog)
{
	// AllocConsole(); // ��ʾ������ʾ������
	HANDLE hAndle = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ���
	WriteConsole(hAndle, strLog, strLog.GetLength(), NULL, NULL); // �������
}
//************************************
// Method:    WToM
// FullName:  �����ֽ��ַ���ת��Ϊ���ֽ��ַ���
// Access:    public 
// Returns:   char*
// Qualifier: ʹ�������Ҫ����free���������ͷ�
// Parameter: str ��Ҫת�����ַ���
//************************************
char* WToM(const CString& str)
{
	// ת��������Ҫ���ڴ��С
	int nstrLen = WideCharToMultiByte(CP_ACP, 0, str, wcslen(str), NULL, 0, NULL, NULL);
	// �����ڴ�ռ�
	char* pmstr = (char*)malloc(sizeof(char)*(nstrLen + 1));
	// ����ڴ�
	ZeroMemory(pmstr, sizeof(char)*(nstrLen + 1));
	// ת���ַ���
	nstrLen = WideCharToMultiByte(CP_ACP, 0, str, wcslen(str), pmstr, nstrLen, NULL, NULL);
	// ��ӽ�β
	pmstr[nstrLen] = 0;
	return pmstr;
}

wchar_t* MToW(char* pstr)
{
	// ��ȡת��������Ҫ���ڴ��С
	int nstrLen = MultiByteToWideChar(CP_ACP, 0, pstr, strlen(pstr), NULL, 0);
	// �����ڴ�
	wchar_t* pwszstr = (wchar_t*)malloc(sizeof(wchar_t)*(nstrLen + 1));
	// ����ڴ�
	ZeroMemory(pwszstr, sizeof(wchar_t)*(nstrLen + 1));
	// ����ת��
	nstrLen = MultiByteToWideChar(CP_ACP, 0, pstr, strlen(pstr), pwszstr, nstrLen);
	// �ַ�����β
	pwszstr[nstrLen] = 0;
	return pwszstr;
}

wchar_t* MToW(char* pstr, UINT nCodePage/*=CP_ACP*/)
{
	// ��ȡת��������Ҫ���ڴ��С
	int nstrLen = MultiByteToWideChar(nCodePage, 0, pstr, strlen(pstr), NULL, 0);
	// �����ڴ�
	wchar_t* pwszstr = (wchar_t*)malloc(sizeof(wchar_t)*(nstrLen + 1));
	// ����ڴ�
	ZeroMemory(pwszstr, sizeof(wchar_t)*(nstrLen + 1));
	// ����ת��
	nstrLen = MultiByteToWideChar(nCodePage, 0, pstr, strlen(pstr), pwszstr, nstrLen);
	// �ַ�����β
	pwszstr[nstrLen] = 0;
	return pwszstr;
}