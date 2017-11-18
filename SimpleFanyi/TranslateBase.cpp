#include "stdafx.h"
#include "TranslateBase.h"


CTranslateBase::CTranslateBase() :m_pHttpReq(NULL)
{
	HRESULT hRef = m_pHttpReq.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hRef))
	{
		AfxMessageBox(_T("信息交互接口创建失败!"));
	}
}


CTranslateBase::~CTranslateBase()
{
}

CString CTranslateBase::QueryData(const CString& strContent)
{
	
	CString strURL;
	strURL.Format(_T("http://dict-co.iciba.com/api/dictionary.php?key=500B8563E8140310C58EBD2B29831041&type=json&w=%s"), strContent);
	HRESULT hRef = m_pHttpReq->Open(_T("GET"), strURL.AllocSysString());
	if (FAILED(hRef))
		return _T("");

	hRef = m_pHttpReq->Send();
	if (FAILED(hRef))
		return _T("");

	// 拷贝字符串
	CString strRef = m_pHttpReq->ResponseText;
	
	return strRef;
}
