
// SimpleFanyiDlg.h : ͷ�ļ�
//

#pragma once
#include "TranslateBase.h"
#include "TranslateEnglish.h"
#include "TranslateChinese.h"

// CSimpleFanyiDlg �Ի���
class CSimpleFanyiDlg : public CDialogEx
{
// ����
public:
	CSimpleFanyiDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SIMPLEFANYI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	CTranslateBase* m_pTranslateBase;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
