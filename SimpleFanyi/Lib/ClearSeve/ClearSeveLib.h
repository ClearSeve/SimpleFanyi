#pragma once


//************************************
// Method:    GetPathSuffix
// FullName:  获取文件后缀名称
// Access:    public 
// Returns:   返回后缀 .xxx
// Qualifier:
// Parameter: strFileName 文件名.xxx
//************************************
CString GetPathSuffix(CString strFileName);

//************************************
// Method:    IsFilExists
// FullName:  判断文件是否存在
// Access:    public 
// Returns:   TRUE文件存在 FALSE文件不存在
// Qualifier:
// Parameter: strFilePath 文件路径
//************************************
BOOL IsFilExists(CString strFilePath);

//************************************
// Method:    ShowLog
// FullName:  向命令提示符窗口输出字符串
// Access:    public 
// Returns:   VOID
// Qualifier:
// Parameter: strLog 需要显示的字符串
//************************************
VOID ShowLog(CString strLog);


//************************************
// Method:    WToM
// FullName:  将宽字节字符集转换为多字节字符集
// Access:    public 
// Returns:   char*
// Qualifier: 使用完后需要调用free函数进行释放
// Parameter: str 需要转换的字符串
//************************************
char* WToM(const CString& str);

// 将多字节字符集转换为宽字节字符集
wchar_t* MToW(char* pstr, UINT nCodePage = CP_ACP);