#include "stdafx.h"
#include "TranslateChinese.h"


CTranslateChinese::CTranslateChinese(const CString& strContent)
{
	m_nY = 70;
	m_nX = 20;

	CString strJson = QueryData(strContent);
	if (!strJson.IsEmpty())
	{ // �õ�json����
		Json(strJson);
	}
}


CTranslateChinese::~CTranslateChinese()
{
}

VOID CTranslateChinese::Json(const CString& strJson)
{
	
	// ����json, ת��Ϊ���ַ�
	char* pstrJson = WToM(strJson);
	cJSON* pJson = cJSON_Parse(pstrJson);
	if (pJson != NULL)
	{
		cJSON* pSymbols = cJSON_GetObjectItem(pJson, "symbols");
		if (pSymbols != NULL)
		{
			int nSymbolsSize = cJSON_GetArraySize(pSymbols);
			for (int nSymbols = 0; nSymbols < nSymbolsSize; nSymbols++)
			{
				cJSON * pSymbolsSub = cJSON_GetArrayItem(pSymbols, nSymbols);
				if (pSymbolsSub != NULL)
				{
					cJSON* pParts = cJSON_GetObjectItem(pSymbolsSub, "parts");
					if (pParts != NULL && pParts->child != NULL)
					{
						cJSON* pPart_name = cJSON_GetObjectItem(pParts->child, "part_name");
						if (pPart_name!=NULL)
						{
							wchar_t* pwstrPart_name = MToW(pPart_name->valuestring, CP_UTF8);
							AddItemTip(pwstrPart_name,TRUE);
							free(pwstrPart_name);
						}
						
						cJSON* pMeans = cJSON_GetObjectItem(pParts->child, "means");
						if (pMeans != NULL)
						{
							int nMeansSize = cJSON_GetArraySize(pMeans);
							for (int nParts = 0; nParts < nMeansSize; nParts++)
							{
								cJSON * pSymbolsSub = cJSON_GetArrayItem(pMeans, nParts);
								if (pSymbolsSub != NULL && pSymbolsSub->child!=NULL)
								{
									cJSON * pWord_mean = cJSON_GetObjectItem(pSymbolsSub, "word_mean");
									if (pWord_mean)
									{
										wchar_t* pwstrWord_mean = MToW(pWord_mean->valuestring, CP_UTF8);
										AddItemClick(pwstrWord_mean);
										free(pwstrWord_mean);
									}
								}
							}
						}

						m_nY += 20;
						m_nX = 20;
					}
				}
			}
		}

		cJSON_Delete(pJson);
	}
	// ˢ�½���
	AfxGetApp()->GetMainWnd()->Invalidate();
	free(pstrJson);
}

VOID CTranslateChinese::Draw(CPaintDC* pDc)
{
	if (m_strExchange.size() != 0)
	{
		vector<DRAWTEXTSTRUCT>::iterator ExchangeIterator = m_strExchange.begin();
		while (ExchangeIterator != m_strExchange.end())
		{

			if (ExchangeIterator->strText1.IsEmpty())
			{
				pDc->TextOut(ExchangeIterator->rectDraw2.left, ExchangeIterator->rectDraw2.top, ExchangeIterator->strText2);
			}
			else
			{
				pDc->TextOut(ExchangeIterator->rectDraw1.left, ExchangeIterator->rectDraw1.top, ExchangeIterator->strText1);
			}
			++ExchangeIterator;
		}
		
	}

}

VOID CTranslateChinese::MouseMove(const CPoint& point)
{
	if (m_strExchange.size() != 0)
	{
		vector<DRAWTEXTSTRUCT>::iterator ExchangeIterator = m_strExchange.begin();
		while (ExchangeIterator != m_strExchange.end())
		{

			if (ExchangeIterator->rectDraw2.PtInRect(point) && ExchangeIterator->bHighlight == FALSE)
			{ // ������
				CClientDC dc(AfxGetApp()->GetMainWnd());
				// ��������
				CFont* pOldFont = dc.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
				// �������ֱ���
				dc.SetBkMode(TRANSPARENT);
				// ������ɫ
				dc.SetTextColor(RGB(87, 0xCE, 0xFF));
				// ��������
				dc.TextOut(ExchangeIterator->rectDraw2.left, ExchangeIterator->rectDraw2.top, ExchangeIterator->strText2);
				// �ָ�����
				dc.SelectObject(pOldFont);
				// ���ø���
				ExchangeIterator->bHighlight = TRUE;
			}
			else if (!ExchangeIterator->rectDraw2.PtInRect(point) && ExchangeIterator->bHighlight == TRUE)
			{
				CClientDC dc(AfxGetApp()->GetMainWnd());
				// ��������
				CFont* pOldFont = dc.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
				// �������ֱ���
				dc.SetBkMode(TRANSPARENT);
				// ��������
				dc.TextOut(ExchangeIterator->rectDraw2.left, ExchangeIterator->rectDraw2.top, ExchangeIterator->strText2);
				// �ָ�����
				dc.SelectObject(pOldFont);
				// ���ø���
				ExchangeIterator->bHighlight = FALSE;
			}
			++ExchangeIterator;
		}
	}
}

VOID CTranslateChinese::Click(const CPoint& point)
{
	if (m_strExchange.size() != 0)
	{
		vector<DRAWTEXTSTRUCT>::iterator ExchangeIterator = m_strExchange.begin();
		while (ExchangeIterator != m_strExchange.end())
		{

			if (ExchangeIterator->rectDraw2.PtInRect(point) && ExchangeIterator->bHighlight == TRUE)
			{
				// ��������
				CString strContent;
				strContent = ExchangeIterator->strText2.Left(ExchangeIterator->strText2.GetLength() - 2);
				AfxGetApp()->GetMainWnd()->SetDlgItemText(IDC_CONTENT, strContent);
				// �ƶ������
				static_cast<CEdit*>(AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_CONTENT))->SetSel(-1);
				// ���ý���
				static_cast<CEdit*>(AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_CONTENT))->SetFocus();
				// ���͵������
				AfxGetApp()->GetMainWnd()->PostMessage(WM_COMMAND, IDOK);

			}
			++ExchangeIterator;
		}
	}
}

void CTranslateChinese::AddItemTip(const CString& strText, BOOL bSpace)
{
	CClientDC dc(AfxGetApp()->GetMainWnd());

	DRAWTEXTSTRUCT text = { 0 };
	if (bSpace == TRUE)
		text.strText1 = strText + _T(" ");
	else
		text.strText1 = strText;

	// ��������
	CFont* pOldFont = dc.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	CSize size1 = dc.GetTextExtent(text.strText1);
	// �ָ�����
	dc.SelectObject(pOldFont);
	
	text.rectDraw1 = CRect(m_nX, m_nY, m_nX + size1.cx, m_nY + size1.cy);
	m_nX += size1.cx;

	m_strExchange.push_back(text);
}

void CTranslateChinese::AddItemClick(const CString& strText)
{
	CClientDC dc(AfxGetApp()->GetMainWnd());
	CString strNewText; 
	// �ж���ĸ��ʼ��λ��
	if ((strText[0] >= _T('A') && strText[0] <= _T('Z')) || (strText[0] >= _T('a') && strText[0]<=_T('z')))
	{ // ���ж���Ӣ��, ���ý�ȡ
		strNewText = strText;
	}
	else
	{ // ������Ӣ��
		// ��������ĸ�Ŀ�ʼλ��
		int i;
		for (i = 1; i < strText.GetLength(); ++i)
		{
			if ((strText[i] >= _T('A') && strText[i] <= _T('Z')) || (strText[i] >= _T('a') && strText[i] <= _T('z')))
				break;
		}
		CString strTipText = strText.Left(i);
		AddItemTip(strTipText);
		strNewText = strText.Right(strText.GetLength() - i);
	}	
	
	DRAWTEXTSTRUCT text = { 0 };
	text.strText2 = strNewText + _T("; ");
	// ��������
	CFont* pOldFont = dc.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	CSize size2 = dc.GetTextExtent(text.strText2);
	// �ָ�����
	dc.SelectObject(pOldFont);

	text.rectDraw2 = CRect(m_nX, m_nY, m_nX + size2.cx, m_nY + size2.cy);
	m_nX += size2.cx;

	m_strExchange.push_back(text);

}
