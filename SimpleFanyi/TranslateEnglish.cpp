#include "stdafx.h"
#include "TranslateEnglish.h"



CTranslateEnglish::CTranslateEnglish(const CString& strContent)
{
	CString strJson = QueryData(strContent);
	if (!strJson.IsEmpty())
	{ // 得到json数据
		Json(strJson);
	}
}


CTranslateEnglish::~CTranslateEnglish()
{
}

VOID CTranslateEnglish::Json(const CString& strJson)
{
	// 解析json, 转换为宽字符
	char* pstrJson = WToM(strJson);
	cJSON* pJson = cJSON_Parse(pstrJson);
	if (pJson!=NULL)
	{
		cJSON* pSymbols = cJSON_GetObjectItem(pJson, "symbols");
		if (pSymbols!=NULL)
		{
			
			cJSON* pPH_EN = cJSON_GetObjectItem(pSymbols->child, "ph_en");
			if (pPH_EN!=NULL)
			{
				wchar_t* pwstrPHEN = MToW(pPH_EN->valuestring,CP_UTF8);
				m_strPHEN.Format(_T("英:[%s]"), pwstrPHEN);
				free(pwstrPHEN);
			}
			cJSON* pPH_AM = cJSON_GetObjectItem(pSymbols->child, "ph_am");
			if (pPH_AM != NULL)
			{
				wchar_t* pwstrPHAM = MToW(pPH_AM->valuestring, CP_UTF8);
				m_strPHAM.Format(_T("美:[%s]"), pwstrPHAM);
				free(pwstrPHAM);
			}
			cJSON* pParts = cJSON_GetObjectItem(pSymbols->child, "parts");
			if (pParts != NULL)
			{
				int nPartsSize = cJSON_GetArraySize(pParts);
				for (int nParts = 0; nParts < nPartsSize; nParts++)
				{
					cJSON * pPartsSub = cJSON_GetArrayItem(pParts, nParts);
					if (pPartsSub != NULL)
					{
						cJSON* pPart = cJSON_GetObjectItem(pPartsSub, "part");
						cJSON* pMeans = cJSON_GetObjectItem(pPartsSub, "means");
						wchar_t* pwstrPart = MToW(pPart->valuestring);
						CString strItem = pwstrPart;
						free(pwstrPart);
						strItem += _T(" ");
						int nMeansSize = cJSON_GetArraySize(pMeans);
						for (int nMeans = 0; nMeans < nMeansSize; nMeans++)
						{
							cJSON * pPartsSub = cJSON_GetArrayItem(pMeans, nMeans);
							wchar_t* pwstrParts = MToW(pPartsSub->valuestring, CP_UTF8);
							strItem += pwstrParts;
							free(pwstrParts);
							strItem += _T(";  ");
						}
						m_strList.push_back(strItem);
					}
				}
			}

			cJSON* pExchange = cJSON_GetObjectItem(pJson, "exchange");
			if (pExchange != NULL)
			{
				
				m_nY = 110 + m_strList.size() * 20;
				m_nX = 20;

				int nExchangeSize = cJSON_GetArraySize(pExchange);
				for (int nExchange = 0; nExchange < nExchangeSize; nExchange++)
				{
					cJSON * pExchangeSub = cJSON_GetArrayItem(pExchange, nExchange);
					if (pExchangeSub != NULL && pExchangeSub->child != NULL )
					{
						wchar_t* pwstrName = MToW(pExchangeSub->string);
						wchar_t* pwstrValue = MToW(pExchangeSub->child->valuestring);

						if (StrCmp(pwstrName,_T("word_pl")) == 0)
						{
							AddItem(_T("复数"), pwstrValue);
						}
						else if (StrCmp(pwstrName, _T("word_third")) == 0)
						{
							AddItem(_T("第三人称单数"), pwstrValue);
						}
						else if (StrCmp(pwstrName, _T("word_past")) == 0)
						{
							AddItem(_T("过去式"), pwstrValue);
						}
						else if (StrCmp(pwstrName, _T("word_done")) == 0)
						{
							AddItem(_T("过去分词"), pwstrValue);
						}
						else if (StrCmp(pwstrName, _T("word_ing")) == 0)
						{
							AddItem(_T("现在分词"), pwstrValue);
						}
						else if (StrCmp(pwstrName, _T("word_er")) == 0)
						{
							AddItem(_T("比较级"), pwstrValue);
						}
						else if (StrCmp(pwstrName, _T("word_est")) == 0)
						{
							AddItem(_T("最高级"), pwstrValue);
						}
						else
						{
							AddItem(pwstrName, pwstrValue);
						}
						
						free(pwstrName);
						free(pwstrValue);
						
					}
				}
			}
		}
		cJSON_Delete(pJson);
	}
	
	// 刷新界面
	AfxGetApp()->GetMainWnd()->Invalidate();
	free(pstrJson);
}

VOID CTranslateEnglish::Draw(CPaintDC* pDc)
{
	pDc->TextOut(20, 48, m_strPHEN);
	pDc->TextOut(20, 70, m_strPHAM);

	int nY = 100;
	if (m_strList.size() != 0)
	{
		vector<CString>::iterator ListIterator = m_strList.begin();
		while (ListIterator != m_strList.end())
		{
			pDc->TextOut(20, nY, *ListIterator);
			++ListIterator;
			nY += 20;
		}
	}
	if (m_strExchange.size()!=0)
	{
		vector<DRAWTEXTSTRUCT>::iterator ExchangeIterator = m_strExchange.begin();
		while (ExchangeIterator != m_strExchange.end())
		{
			pDc->TextOut(ExchangeIterator->rectDraw1.left, ExchangeIterator->rectDraw1.top, ExchangeIterator->strText1);
			pDc->TextOut(ExchangeIterator->rectDraw2.left, ExchangeIterator->rectDraw2.top, ExchangeIterator->strText2);
			++ExchangeIterator;
		}
	}
	
	
}

VOID CTranslateEnglish::MouseMove(const CPoint& point)
{
	if (m_strExchange.size() != 0)
	{	
		vector<DRAWTEXTSTRUCT>::iterator ExchangeIterator = m_strExchange.begin();
		while (ExchangeIterator != m_strExchange.end())
		{
			
			if (ExchangeIterator->rectDraw2.PtInRect(point) && ExchangeIterator->bHighlight == FALSE)
			{ // 在里面
				CClientDC dc(AfxGetApp()->GetMainWnd());
				// 设置字体
				CFont* pOldFont = dc.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
				// 设置文字背景
				dc.SetBkMode(TRANSPARENT);
				// 设置颜色
				dc.SetTextColor(RGB(87,0xCE,0xFF));
				// 绘制文字
				dc.TextOut(ExchangeIterator->rectDraw2.left, ExchangeIterator->rectDraw2.top, ExchangeIterator->strText2);
				// 恢复字体
				dc.SelectObject(pOldFont);
				// 设置高亮
				ExchangeIterator->bHighlight = TRUE;
			}
			else if (!ExchangeIterator->rectDraw2.PtInRect(point) && ExchangeIterator->bHighlight == TRUE)
			{
				CClientDC dc(AfxGetApp()->GetMainWnd());
				// 设置字体
				CFont* pOldFont = dc.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
				// 设置文字背景
				dc.SetBkMode(TRANSPARENT);
				// 绘制文字
				dc.TextOut(ExchangeIterator->rectDraw2.left, ExchangeIterator->rectDraw2.top, ExchangeIterator->strText2);
				// 恢复字体
				dc.SelectObject(pOldFont);
				// 设置高亮
				ExchangeIterator->bHighlight = FALSE;
			}
			++ExchangeIterator;
		}
	}
}

VOID CTranslateEnglish::Click(const CPoint& point)
{
	if (m_strExchange.size() != 0)
	{
		vector<DRAWTEXTSTRUCT>::iterator ExchangeIterator = m_strExchange.begin();
		while (ExchangeIterator != m_strExchange.end())
		{

			if (ExchangeIterator->rectDraw2.PtInRect(point) && ExchangeIterator->bHighlight == TRUE)
			{
				// 设置内容
				CString strContent;
				strContent = ExchangeIterator->strText2.Left(ExchangeIterator->strText2.GetLength() - 3);
				AfxGetApp()->GetMainWnd()->SetDlgItemText(IDC_CONTENT, strContent);
				// 移动插入符
				static_cast<CEdit*>(AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_CONTENT))->SetSel(-1);
				// 设置焦点
				static_cast<CEdit*>(AfxGetApp()->GetMainWnd()->GetDlgItem(IDC_CONTENT))->SetFocus();
				// 发送点击命令
				AfxGetApp()->GetMainWnd()->PostMessage(WM_COMMAND,IDOK);
				
			}
			++ExchangeIterator;
		}
	}
}

void CTranslateEnglish::AddItem(CString strName, CString strValue)
{
	strName += _T(": ");
	strValue += _T(";  ");
	CClientDC dc(AfxGetApp()->GetMainWnd());
	

	DRAWTEXTSTRUCT text = { 0 };
	text.strText1 = strName;
	text.strText2 = strValue;
	// 设置字体
	CFont* pOldFont = dc.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
	CSize size1 = dc.GetTextExtent(text.strText1);
	CSize size2 = dc.GetTextExtent(text.strText2);
	// 恢复字体
	dc.SelectObject(pOldFont);

	if (m_nX+size1.cx+size2.cx>=400)
	{
		m_nX = 20;
		m_nY += 20;
	}
	text.rectDraw1 = CRect(m_nX, m_nY, m_nX + size1.cx, m_nY + size1.cy);
	m_nX += size1.cx;
	text.rectDraw2 = CRect(m_nX, m_nY, m_nX + size2.cx, m_nY + size1.cy);
	m_nX += size2.cx;

	m_strExchange.push_back(text);
}
