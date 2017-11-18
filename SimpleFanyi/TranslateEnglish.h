#pragma once
#include "TranslateBase.h"




class CTranslateEnglish : public CTranslateBase
{
public:
	CTranslateEnglish(const CString& strContent);
	~CTranslateEnglish();
public:
	// ����
	virtual VOID Json(const CString& strJson);
	// ����
	virtual VOID Draw(CPaintDC* pDc);
	virtual VOID MouseMove(const CPoint& point);
	virtual VOID Click(const CPoint& point);
private:
	void AddItem(CString strName, CString strValue);
private:
	// ���� Ӣ������,  ��������
	CString m_strPHEN, m_strPHAM;
	
	vector<CString> m_strList;
	
	vector<DRAWTEXTSTRUCT> m_strExchange;

	// ����Item��λ��
	int m_nY;
	int m_nX;
};

