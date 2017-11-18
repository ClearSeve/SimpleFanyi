#pragma once
#include "TranslateBase.h"




class CTranslateEnglish : public CTranslateBase
{
public:
	CTranslateEnglish(const CString& strContent);
	~CTranslateEnglish();
public:
	// 解析
	virtual VOID Json(const CString& strJson);
	// 绘制
	virtual VOID Draw(CPaintDC* pDc);
	virtual VOID MouseMove(const CPoint& point);
	virtual VOID Click(const CPoint& point);
private:
	void AddItem(CString strName, CString strValue);
private:
	// 音标 英国音标,  美国音标
	CString m_strPHEN, m_strPHAM;
	
	vector<CString> m_strList;
	
	vector<DRAWTEXTSTRUCT> m_strExchange;

	// 增加Item的位置
	int m_nY;
	int m_nX;
};

