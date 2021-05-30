
// yuanzhengDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "yuanzheng.h"
#include "yuanzhengDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	CyuanzhengDlg* that = (CyuanzhengDlg*)lpParameter;
	// ������ʾ��
	::Beep(500, 200);
	// �ӳ�����
	int delay_second = that->m_delay * 60;
	for (int i = 0; i < delay_second; i++) {
		::Sleep(1000);
		that->UpdateData(0);
	}
	// Ѱ����֮�ȴ���
	HWND game = ::FindWindow(_TEXT("MapleStoryClass"), NULL);
	// �z����Ϸ�����Ƿ����
	if (game == NULL) {
		that->MessageBox(_TEXT("δ�z�y���Α򴰿�"));
		exit(0);
	}
	// �ȴ�1��
	Sleep(1000);

	long next_time = time(0);
	// �������ʱ��
	long end_time = time(0) + that->m_time_h*3600+that->m_time_m*60+that->m_time_s;
	// �����ǰʱ��δ����ֹͣѭ��
	long now;
	while (end_time > (now=time(0))) {
		// ÿ�����Сʱ�ͷż���
		if (now > next_time) {
			//�����´��ͷż��ܵ�ʱ��
			next_time = now + 25 * 60+5;
			// ������Ϸ����Ϊǰ�ô���
			HWND top = ::GetForegroundWindow();
			if (top != game) {
				::SetForegroundWindow(game);
			}
			Sleep(2000);
			for (int i = 0; i < that->m_count; i++) {
				//ʹ�ü���1
				if (that->m_skill1 != "") {
					::PostMessage(game, WM_KEYDOWN, that->m_nVirtKey[that->m_skill1[0]], 1 | that->m_scanfCode[that->m_skill1[0]] << 16 | 0 << 24);
					::Sleep(50);
					::PostMessage(game, WM_KEYUP, that->m_nVirtKey[that->m_skill1[0]], 1 | 1 << 30 | 1 << 31 | that->m_scanfCode[that->m_skill1[0]] << 16 | 0 << 24);
					::Sleep(1000);
				}

				//ʹ�ü���2
				if (that->m_skill2 != "") {
					::PostMessage(game, WM_KEYDOWN, that->m_nVirtKey[that->m_skill2[0]], 1 | that->m_scanfCode[that->m_skill2[0]] << 16 | 0 << 24);
					::Sleep(50);
					::PostMessage(game, WM_KEYUP, that->m_nVirtKey[that->m_skill2[0]], 1 | 1 << 30 | 1 << 31 | that->m_scanfCode[that->m_skill2[0]] << 16 | 0 << 24);
					::Sleep(1000);
				}

				//ʹ�ü���3
				if (that->m_skill3 != "") {
					::PostMessage(game, WM_KEYDOWN, that->m_nVirtKey[that->m_skill3[0]], 1 | that->m_scanfCode[that->m_skill3[0]] << 16 | 0 << 24);
					::Sleep(50);
					::PostMessage(game, WM_KEYUP, that->m_nVirtKey[that->m_skill3[0]], 1 | 1 << 30 | 1 << 31 | that->m_scanfCode[that->m_skill3[0]] << 16 | 0 << 24);
					::Sleep(1000);
				}
				//�ȴ�����ʩ�ż�����ٴ�ʩ��
				Sleep(that->m_skill_interval*1000);
			}
		}
		::Sleep(1000);
		//ˢ��ʣ��ʱ��
		long last_time = end_time - time(0);
		that->m_time_h = last_time / 60 / 60;
		that->m_time_m = last_time / 60 % 60;
		that->m_time_s = last_time % 60;
		that->UpdateData(0);
	}

	// �ر����������
	if (that->m_close_leishen) {
		// Ѱ���������������
		HWND leishen = ::FindWindow(NULL, _TEXT("���������"));
		if (leishen != NULL) {
			// ֹͣ����
			::PostMessage(leishen, WM_LBUTTONDOWN, MK_LBUTTON, 1008 | 457 << 16);
			Sleep(50);
			::PostMessage(leishen, WM_LBUTTONUP, 0, 1008 | 457 << 16);
			::Sleep(5000);
			HWND prompt = ::FindWindow(NULL, _TEXT("uiErrorPrompt"));
			::PostMessage(prompt, WM_LBUTTONDOWN, MK_LBUTTON, 315 | 262 << 16);
			Sleep(50);
			::PostMessage(prompt, WM_LBUTTONUP, 0, 315 | 262 << 16);
			Sleep(2000);
		}
	}
	if (that->m_shutdown) {
		// �����ػ��ƻ�����60���ػ��������ڼ������������ʾ��������"shutdown -a"ȡ���ػ��ƻ�
		system("shutdown -s -t 60");
	}
	return 0;
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CyuanzhengDlg �Ի���



CyuanzhengDlg::CyuanzhengDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_YUANZHENG_DIALOG, pParent)
	, m_time_h(5)
	, m_time_m(0)
	, m_time_s(0)
	, m_skill_interval(20)
	, m_shutdown(TRUE)
	, m_close_leishen(TRUE)
	, m_skill1(_T("E"))
	, m_skill2(_T("D"))
	, m_skill3(_T(""))
	, m_started(0)
	, m_delay(0)
	, m_count(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nVirtKey['0'] = 0x30;
	m_nVirtKey['1'] = 0x31;
	m_nVirtKey['2'] = 0x32;
	m_nVirtKey['3'] = 0x33;
	m_nVirtKey['4'] = 0x34;
	m_nVirtKey['5'] = 0x35;
	m_nVirtKey['6'] = 0x36;
	m_nVirtKey['7'] = 0x37;
	m_nVirtKey['8'] = 0x38;
	m_nVirtKey['9'] = 0x39;
	m_nVirtKey['A'] = 0x41;
	m_nVirtKey['B'] = 0x42;
	m_nVirtKey['C'] = 0x43;
	m_nVirtKey['D'] = 0x44;
	m_nVirtKey['E'] = 0x45;
	m_nVirtKey['F'] = 0x46;
	m_nVirtKey['G'] = 0x46;
	m_nVirtKey['H'] = 0x47;
	m_nVirtKey['I'] = 0x48;
	m_nVirtKey['J'] = 0x4a;
	m_nVirtKey['K'] = 0x4b;
	m_nVirtKey['L'] = 0x4c;
	m_nVirtKey['M'] = 0x4d;
	m_nVirtKey['N'] = 0x4e;
	m_nVirtKey['O'] = 0x4f;
	m_nVirtKey['P'] = 0x50;
	m_nVirtKey['Q'] = 0x51;
	m_nVirtKey['R'] = 0x52;
	m_nVirtKey['S'] = 0x53;
	m_nVirtKey['T'] = 0x54;
	m_nVirtKey['U'] = 0x55;
	m_nVirtKey['V'] = 0x56;
	m_nVirtKey['W'] = 0x57;
	m_nVirtKey['X'] = 0x58;
	m_nVirtKey['Y'] = 0x59;
	m_nVirtKey['Z'] = 0x5a;

	m_scanfCode['1'] = 0x02;
	m_scanfCode['2'] = 0x03;
	m_scanfCode['3'] = 0x04;
	m_scanfCode['4'] = 0x05;
	m_scanfCode['5'] = 0x06;
	m_scanfCode['6'] = 0x07;
	m_scanfCode['7'] = 0x08;
	m_scanfCode['8'] = 0x09;
	m_scanfCode['9'] = 0x0a;
	m_scanfCode['0'] = 0x0b;
	m_scanfCode['A'] = 0x1e;
	m_scanfCode['B'] = 0x30;
	m_scanfCode['C'] = 0x2e;
	m_scanfCode['D'] = 0x20;
	m_scanfCode['E'] = 0x12;
	m_scanfCode['F'] = 0x21;
	m_scanfCode['G'] = 0x22;
	m_scanfCode['H'] = 0x23;
	m_scanfCode['I'] = 0x17;
	m_scanfCode['J'] = 0x24;
	m_scanfCode['K'] = 0x25;
	m_scanfCode['L'] = 0x26;
	m_scanfCode['M'] = 0x32;
	m_scanfCode['N'] = 0x31;
	m_scanfCode['O'] = 0x18;
	m_scanfCode['P'] = 0x19;
	m_scanfCode['Q'] = 0x10;
	m_scanfCode['R'] = 0x13;
	m_scanfCode['S'] = 0x1f;
	m_scanfCode['T'] = 0x14;
	m_scanfCode['U'] = 0x16;
	m_scanfCode['V'] = 0x2f;
	m_scanfCode['W'] = 0x11;
	m_scanfCode['X'] = 0x2d;
	m_scanfCode['Y'] = 0x15;
	m_scanfCode['Z'] = 0x2c;
}

void CyuanzhengDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_time_h);
	DDV_MinMaxInt(pDX, m_time_h, 0, 12);
	DDX_Text(pDX, IDC_EDIT2, m_time_m);
	DDV_MinMaxInt(pDX, m_time_m, 0, 60);
	DDX_Text(pDX, IDC_EDIT3, m_time_s);
	DDV_MinMaxInt(pDX, m_time_s, 0, 60);
	DDX_Text(pDX, IDC_EDIT4, m_skill_interval);
	DDV_MinMaxInt(pDX, m_skill_interval, 0, 60);
	DDX_Control(pDX, IDC_EDIT1, m_input1);
	DDX_Control(pDX, IDC_EDIT2, m_input2);
	DDX_Control(pDX, IDC_EDIT3, m_input3);
	DDX_Control(pDX, IDC_COMBO2, m_input4);
	DDX_Control(pDX, IDC_COMBO3, m_input5);
	DDX_Control(pDX, IDC_COMBO4, m_input6);
	DDX_Control(pDX, IDC_EDIT4, m_input7);
	DDX_Check(pDX, IDC_CHECK2, m_shutdown);
	DDX_Check(pDX, IDC_CHECK1, m_close_leishen);
	DDX_Control(pDX, IDC_CHECK1, m_input8);
	DDX_Control(pDX, IDC_CHECK2, m_input9);
	DDX_CBString(pDX, IDC_COMBO2, m_skill1);
	DDX_CBString(pDX, IDC_COMBO3, m_skill2);
	DDX_CBString(pDX, IDC_COMBO4, m_skill3);
	DDX_Text(pDX, IDC_EDIT5, m_delay);
	DDV_MinMaxInt(pDX, m_delay, 0, 25);
	DDX_Text(pDX, IDC_EDIT6, m_count);
	DDV_MinMaxInt(pDX, m_count, 1, 10);
	DDX_Control(pDX, IDC_EDIT5, m_input10);
	DDX_Control(pDX, IDC_EDIT6, m_input11);
}

BEGIN_MESSAGE_MAP(CyuanzhengDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CyuanzhengDlg ��Ϣ�������

BOOL CyuanzhengDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	for (char i = '0'; i <= '9'; i++) {
		m_input4.AddString(CString(i));
		m_input5.AddString(CString(i));
		m_input6.AddString(CString(i));
	}
	for (char i = 'A'; i <= 'Z'; i++) {
		m_input4.AddString(CString(i));
		m_input5.AddString(CString(i));
		m_input6.AddString(CString(i));
	}

	::RegisterHotKey(m_hWnd, 1001, MOD_CONTROL, VK_F1);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CyuanzhengDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CyuanzhengDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CyuanzhengDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CyuanzhengDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	// CDialogEx::OnOK();
}


void CyuanzhengDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!this->UpdateData()) {
		return;
	}
	if (this->m_started) {
		return;
	}
	this->m_started = TRUE;
	m_input1.EnableWindow(0);
	m_input2.EnableWindow(0);
	m_input3.EnableWindow(0);
	m_input4.EnableWindow(0);
	m_input5.EnableWindow(0);
	m_input6.EnableWindow(0);
	m_input7.EnableWindow(0);
	m_input8.EnableWindow(0);
	m_input9.EnableWindow(0);
	m_input10.EnableWindow(0);
	m_input11.EnableWindow(0);
	if (nHotKeyId == 1001) {
		CreateThread(NULL, 0, ThreadProc, (LPVOID)this, 0, NULL);
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}
