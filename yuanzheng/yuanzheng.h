
// yuanzheng.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CyuanzhengApp: 
// �йش����ʵ�֣������ yuanzheng.cpp
//

class CyuanzhengApp : public CWinApp
{
public:
	CyuanzhengApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CyuanzhengApp theApp;