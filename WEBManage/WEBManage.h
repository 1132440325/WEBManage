
// WEBManage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWEBManageApp: 
// �йش����ʵ�֣������ WEBManage.cpp
//

class CWEBManageApp : public CWinApp
{
public:
	CWEBManageApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWEBManageApp theApp;