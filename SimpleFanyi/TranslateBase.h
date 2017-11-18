#pragma once

#include "Lib/cJSON/cJSON.h"
#include "Lib/ClearSeve/ClearSeveLib.h"
#include "resource.h"

#include <vector>
using namespace std;

// #import "c:\\windows\system32\\winhttp.dll" no_namespace 
#import "c:\\windows\system32\\winhttpcom.dll" no_namespace 

typedef struct  _DRAWTEXTSTRUCT
{
	CString strText1;
	CString strText2;
	CRect rectDraw1;
	CRect rectDraw2;
	BOOL bHighlight;


}DRAWTEXTSTRUCT, *LPDRAWTEXTSTRUCT;

class CTranslateBase
{
public:
	CTranslateBase();
	~CTranslateBase();
public:
	// ��ȡ����
	CString QueryData(const CString& strContent);
	// ����
	virtual VOID Json(const CString& strJson) = 0;
	// ����
	virtual VOID Draw(CPaintDC* pDc) = 0;
	virtual VOID MouseMove(const CPoint& point) = 0;
	virtual VOID Click(const CPoint& point) = 0;
private:
	IWinHttpRequestPtr m_pHttpReq;
};

