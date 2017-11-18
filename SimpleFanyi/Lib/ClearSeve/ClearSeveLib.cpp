#include "stdafx.h"
#include "ClearSeveLib.h"

//************************************
// Method:    GetPathSuffix
// FullName:  获取文件后缀名称
// Access:    public 
// Returns:   返回后缀 .xxx
// Qualifier:
// Parameter: strFileName 文件名.xxx
//************************************
CString GetPathSuffix(CString strFileName)
{
	int pos = strFileName.Find(_T(".")); //获取. 的位置
	if (pos == -1){ //如果没有找到，直接返回该字符串
		return strFileName;
	}
	else{
		return GetPathSuffix(strFileName.Mid(pos + 1)); //找到了的话，往深层遍历，直到最底层
	}
}

//************************************
// Method:    IsFilExists
// FullName:  判断文件是否存在
// Access:    public 
// Returns:   TRUE文件存在 FALSE文件不存在
// Qualifier:
// Parameter: strFilePath 文件路径
//************************************
BOOL IsFilExists(CString strFilePath)
{
	// 构造文件查询结构体
	WIN32_FIND_DATA Find_Data = { 0 };
	// 查找文件
	FindFirstFile(strFilePath, &Find_Data);
	// 判断文件名
	if (wcscmp(Find_Data.cFileName, _T("")) != 0)
	{
		return TRUE;
	}
	return FALSE;
}

//************************************
// Method:    ShowLog
// FullName:  向命令提示符窗口输出字符串
// Access:    public 
// Returns:   VOID
// Qualifier:
// Parameter: strLog 需要显示的字符串
//************************************
VOID ShowLog(CString strLog)
{
	// AllocConsole(); // 显示命令提示符窗口
	HANDLE hAndle = GetStdHandle(STD_OUTPUT_HANDLE);// 获取句柄
	WriteConsole(hAndle, strLog, strLog.GetLength(), NULL, NULL); // 输出内容
}
//************************************
// Method:    WToM
// FullName:  将宽字节字符集转换为多字节字符集
// Access:    public 
// Returns:   char*
// Qualifier: 使用完后需要调用free函数进行释放
// Parameter: str 需要转换的字符串
//************************************
char* WToM(const CString& str)
{
	// 转换后所需要的内存大小
	int nstrLen = WideCharToMultiByte(CP_ACP, 0, str, wcslen(str), NULL, 0, NULL, NULL);
	// 申请内存空间
	char* pmstr = (char*)malloc(sizeof(char)*(nstrLen + 1));
	// 清空内存
	ZeroMemory(pmstr, sizeof(char)*(nstrLen + 1));
	// 转换字符串
	nstrLen = WideCharToMultiByte(CP_ACP, 0, str, wcslen(str), pmstr, nstrLen, NULL, NULL);
	// 添加结尾
	pmstr[nstrLen] = 0;
	return pmstr;
}

wchar_t* MToW(char* pstr)
{
	// 获取转换后所需要的内存大小
	int nstrLen = MultiByteToWideChar(CP_ACP, 0, pstr, strlen(pstr), NULL, 0);
	// 申请内存
	wchar_t* pwszstr = (wchar_t*)malloc(sizeof(wchar_t)*(nstrLen + 1));
	// 清空内存
	ZeroMemory(pwszstr, sizeof(wchar_t)*(nstrLen + 1));
	// 进行转换
	nstrLen = MultiByteToWideChar(CP_ACP, 0, pstr, strlen(pstr), pwszstr, nstrLen);
	// 字符串结尾
	pwszstr[nstrLen] = 0;
	return pwszstr;
}

wchar_t* MToW(char* pstr, UINT nCodePage/*=CP_ACP*/)
{
	// 获取转换后所需要的内存大小
	int nstrLen = MultiByteToWideChar(nCodePage, 0, pstr, strlen(pstr), NULL, 0);
	// 申请内存
	wchar_t* pwszstr = (wchar_t*)malloc(sizeof(wchar_t)*(nstrLen + 1));
	// 清空内存
	ZeroMemory(pwszstr, sizeof(wchar_t)*(nstrLen + 1));
	// 进行转换
	nstrLen = MultiByteToWideChar(nCodePage, 0, pstr, strlen(pstr), pwszstr, nstrLen);
	// 字符串结尾
	pwszstr[nstrLen] = 0;
	return pwszstr;
}