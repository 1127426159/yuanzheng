
// yuanzhengDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "map"
using namespace::std;


// CyuanzhengDlg 对话框
class CyuanzhengDlg : public CDialogEx
{
// 构造
public:
	CyuanzhengDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_YUANZHENG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	int m_time_h;
	int m_time_m;
	int m_time_s;
	int m_skill_interval;
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	CEdit m_input1;
	CEdit m_input2;
	CEdit m_input3;
	CComboBox m_input4;
	CComboBox m_input5;
	CComboBox m_input6;
	CEdit m_input7;
	BOOL m_shutdown;
	BOOL m_close_leishen;
	CButton m_input8;
	CButton m_input9;
	CString m_skill1;
	CString m_skill2;
	CString m_skill3;
	map<char, int> m_nVirtKey;
	map<char, int> m_scanfCode;

	bool m_started;
	int m_delay;
	int m_count;
};
