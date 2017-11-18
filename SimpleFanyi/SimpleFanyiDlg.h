
// SimpleFanyiDlg.h : 头文件
//

#pragma once
#include "TranslateBase.h"
#include "TranslateEnglish.h"
#include "TranslateChinese.h"

// CSimpleFanyiDlg 对话框
class CSimpleFanyiDlg : public CDialogEx
{
// 构造
public:
	CSimpleFanyiDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SIMPLEFANYI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CTranslateBase* m_pTranslateBase;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
