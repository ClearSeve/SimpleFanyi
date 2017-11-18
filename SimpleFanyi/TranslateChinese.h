#pragma once
#include "TranslateBase.h"
class CTranslateChinese : public CTranslateBase
{
public:
	CTranslateChinese(const CString& strContent);
	~CTranslateChinese();
public:
	// 解析
	virtual VOID Json(const CString& strJson);
	// 绘制
	virtual VOID Draw(CPaintDC* pDc);
	virtual VOID MouseMove(const CPoint& point);
	virtual VOID Click(const CPoint& point);
private:
	void AddItemTip(const CString& strText,BOOL bSpace=FALSE);
	void AddItemClick(const CString& strText);
private:
	vector<DRAWTEXTSTRUCT> m_strExchange;

	// 增加Item的位置
	int m_nY;
	int m_nX;
};

