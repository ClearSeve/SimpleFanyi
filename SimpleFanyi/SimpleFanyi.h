
// SimpleFanyi.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSimpleFanyiApp: 
// �йش����ʵ�֣������ SimpleFanyi.cpp
//

class CSimpleFanyiApp : public CWinApp
{
public:
	CSimpleFanyiApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSimpleFanyiApp theApp;