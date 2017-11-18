
// SimpleFanyiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SimpleFanyi.h"
#include "SimpleFanyiDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimpleFanyiDlg 对话框



CSimpleFanyiDlg::CSimpleFanyiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimpleFanyiDlg::IDD, pParent), m_pTranslateBase(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleFanyiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSimpleFanyiDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CSimpleFanyiDlg 消息处理程序

BOOL CSimpleFanyiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSimpleFanyiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);


		

	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		// 设置字体
		CFont* pOldFont = dc.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
		// 设置文字背景
		dc.SetBkMode(TRANSPARENT);
		
		if (m_pTranslateBase != NULL)
			m_pTranslateBase->Draw(&dc);

		// 恢复字体
		dc.SelectObject(pOldFont);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSimpleFanyiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSimpleFanyiDlg::OnOK()
{// 查询
	// 获取要查询的字符串
	CString strContent;
	GetDlgItemText(IDC_CONTENT, strContent);

	// 判断是否为空
	if (strContent.IsEmpty())
		return; // 为空直接返回

	// 清除旧的查询数据
	if (m_pTranslateBase != NULL)
	{
		delete m_pTranslateBase;
		m_pTranslateBase = NULL;
	}
		

	// 判断第一个字符是否为字母
	if ((strContent[0] >= _T('A') && strContent[0] <= _T('Z')) || (strContent[0] >= _T('a') && strContent[0] <= _T('z')))
	{ // 单词
		m_pTranslateBase = new CTranslateEnglish(strContent.MakeLower());
	}
	else
	{ // 汉字
		m_pTranslateBase = new CTranslateChinese(strContent);
	}
}


BOOL CSimpleFanyiDlg::PreTranslateMessage(MSG* pMsg)
{
	// 按下Esc 清除输入的内容
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		// 清除内容
		SetDlgItemText(IDC_CONTENT, _T(""));
		// 设置输入焦点
		GetDlgItem(IDC_CONTENT)->SetFocus();
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CSimpleFanyiDlg::DestroyWindow()
{
	if (m_pTranslateBase!=NULL)
	{
		delete m_pTranslateBase;
	}

	return CDialogEx::DestroyWindow();
}


void CSimpleFanyiDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	
	if (m_pTranslateBase != NULL)
	{
		m_pTranslateBase->MouseMove(point);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CSimpleFanyiDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	if (m_pTranslateBase != NULL)
	{
		m_pTranslateBase->Click(point);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}
