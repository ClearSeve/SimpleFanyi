
// SimpleFanyiDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimpleFanyi.h"
#include "SimpleFanyiDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimpleFanyiDlg �Ի���



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


// CSimpleFanyiDlg ��Ϣ�������

BOOL CSimpleFanyiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSimpleFanyiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);


		

	}
	else
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		// ��������
		CFont* pOldFont = dc.SelectObject(CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT)));
		// �������ֱ���
		dc.SetBkMode(TRANSPARENT);
		
		if (m_pTranslateBase != NULL)
			m_pTranslateBase->Draw(&dc);

		// �ָ�����
		dc.SelectObject(pOldFont);
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSimpleFanyiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSimpleFanyiDlg::OnOK()
{// ��ѯ
	// ��ȡҪ��ѯ���ַ���
	CString strContent;
	GetDlgItemText(IDC_CONTENT, strContent);

	// �ж��Ƿ�Ϊ��
	if (strContent.IsEmpty())
		return; // Ϊ��ֱ�ӷ���

	// ����ɵĲ�ѯ����
	if (m_pTranslateBase != NULL)
	{
		delete m_pTranslateBase;
		m_pTranslateBase = NULL;
	}
		

	// �жϵ�һ���ַ��Ƿ�Ϊ��ĸ
	if ((strContent[0] >= _T('A') && strContent[0] <= _T('Z')) || (strContent[0] >= _T('a') && strContent[0] <= _T('z')))
	{ // ����
		m_pTranslateBase = new CTranslateEnglish(strContent.MakeLower());
	}
	else
	{ // ����
		m_pTranslateBase = new CTranslateChinese(strContent);
	}
}


BOOL CSimpleFanyiDlg::PreTranslateMessage(MSG* pMsg)
{
	// ����Esc ������������
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		// �������
		SetDlgItemText(IDC_CONTENT, _T(""));
		// �������뽹��
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
