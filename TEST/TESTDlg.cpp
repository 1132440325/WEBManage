
// TESTDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TEST.h"
#include "TESTDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CTESTDlg �Ի���



CTESTDlg::CTESTDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_LIST3, m_dir);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(CTESTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CTESTDlg::OnLvnColumnclickList1)
ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST1, &CTESTDlg::OnLvnItemActivateList1)
ON_BN_CLICKED(IDC_BUTTON1, &CTESTDlg::OnBnClickedButton1)
ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST3, &CTESTDlg::OnLvnItemActivateList3)
END_MESSAGE_MAP()


// CTESTDlg ��Ϣ�������

BOOL CTESTDlg::OnInitDialog()
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
	int DeskCount = 0;
	DWORD DeskInfo = GetLogicalDrives();
	while (DeskInfo)//ͨ��ѭ�������鿴ÿһλ�����Ƿ�Ϊ1�����Ϊ1�����Ϊ��,���Ϊ0����̲����ڡ�
	{
		if (DeskInfo & 1)//ͨ��λ������߼���������ж��Ƿ�Ϊ1
		{
			++DeskCount;
		}
		DeskInfo = DeskInfo >> 1;//ͨ��λ��������Ʋ�����֤ÿѭ��һ��������λ�������ƶ�һλ��
	}
	DWORD DSLength = GetLogicalDriveStrings(0, NULL);
	LPTSTR lpDriveStrings = (LPTSTR)HeapAlloc(GetProcessHeap(), 0, DSLength * sizeof(TCHAR));
	//ͨ��GetLogicalDriveStrings()������ȡ�����������ַ�����Ϣ���ȡ�
	GetLogicalDriveStrings(DSLength, lpDriveStrings);
	WCHAR temp_dir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,temp_dir);
	m_edit.SetWindowTextW(temp_dir);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, L"������",0,75);
	m_list.InsertColumn(1, L"��������", 0, 100);
	m_list.InsertColumn(2, L"�ܿռ�", 0, 100);
	m_list.InsertColumn(3, L"ʣ��ռ�", 0, 100);
	m_list.InsertColumn(4, L"ʹ�ÿռ�",0, 100);
	m_dir.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_dir.InsertColumn(0, L"�ļ���", 0, 150);
	m_dir.InsertColumn(1, L"�ļ�����", 0, 100);
	//ͨ��GetLogicalDriveStrings���ַ�����Ϣ���Ƶ�����������,���б�������������������Ϣ��
	int DType;
	int si = 0;
	BOOL fResult;
	unsigned _int64 i64FreeBytesToCaller;
	unsigned _int64 i64TotalBytes;
	unsigned _int64 i64FreeBytes;
	for (DWORD i = 0; i < (DSLength / 4); ++i)
		//Ϊ����ʾÿ����������״̬����ͨ��ѭ�����ʵ�֣�����DStr�ڲ������������A:\NULLB:\NULLC:\NULL����������Ϣ������DSLength/4���Ի�þ����ѭ����Χ
	{

		char  dir2[3] = { lpDriveStrings[si], ':', '\0' };//�̷�ABCD��
		TCHAR dir[3] = { lpDriveStrings[si], ':', '\0' };
		DType = GetDriveType(lpDriveStrings + i * 4);//�������ͣ����̣����̣�Ӳ�̵�
		fResult = GetDiskFreeSpaceEx(
			dir,
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);
		//GetDiskFreeSpaceEx���������Ի�ȡ���������̵Ŀռ�״̬,ʹ�û�δ�ÿռ��С���������ص��Ǹ�BOOL��������
		if (fResult == TRUE)//ͨ�����ص�BOOL�����ж��������Ƿ��ڹ���״̬
		{
			//����ռ��С��ע��˴���λb��
			int index = m_list.InsertItem(m_list.GetItemCount(), dir);
			CString Driver_Type = L"";
			switch (DType)
			{
			case DRIVE_REMOVABLE:
				Driver_Type = L"����������";
				break;
			case DRIVE_FIXED:
				Driver_Type = L"Ӳ��";
				break;
			case DRIVE_REMOTE:
				Driver_Type = L"����������";
				break;
			case DRIVE_CDROM:
				Driver_Type = L"CD-ROM������";
				break;
			default:
				break;
			}
			m_list.SetItemText(index, 1, Driver_Type);
			WCHAR TotalBytes[65];
			_ui64tow_s(i64TotalBytes/1024/1024/1024,TotalBytes,65,10);
			wcscat_s(TotalBytes,65, L" GB");
			m_list.SetItemText(index, 2, TotalBytes);

			WCHAR FreeBytes[65];
			_ui64tow_s(i64FreeBytes / 1024 / 1024 / 1024, FreeBytes, 65, 10);
			wcscat_s(FreeBytes, 65, L" GB");
			m_list.SetItemText(index, 3, FreeBytes);

			WCHAR FreeBytesToCaller[65];
			_ui64tow_s((i64TotalBytes - i64FreeBytes) / 1024 / 1024 / 1024, FreeBytesToCaller, 65, 10);
			wcscat_s(FreeBytesToCaller, 65, L" GB");
			m_list.SetItemText(index, 4, FreeBytesToCaller);
		}
		else
		{

		}
		si += 4;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTESTDlg::OnPaint()
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
HCURSOR CTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CTESTDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//
//	*pResult = 0;
//}


void CTESTDlg::OnLvnItemActivateList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WCHAR dir[4] = { 0 };
	m_list.GetItemText((int)m_list.GetFirstSelectedItemPosition()-1,0,dir,3);
	wcscat_s(dir, 4, L"\\");
	m_edit.SetWindowTextW(dir);
	*pResult = 0;
}
void CTESTDlg::GetFileList(CString sFolderPath)
{
	//�����ļ���������ļ�  
	m_dir.DeleteAllItems();
	WIN32_FIND_DATA FindData;
	HANDLE hError;
	sFolderPath += L"\\*.*";
	hError = FindFirstFile(sFolderPath, &FindData);
	if (hError == INVALID_HANDLE_VALUE)
	{
		MessageBox(L"����ʧ��!");
		return;
	}
	while (::FindNextFile(hError, &FindData))
	{
		int index = m_dir.InsertItem(m_dir.GetItemCount(),FindData.cFileName);
		if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			//Ŀ¼
			m_dir.SetItemText(index, 1, L"Ŀ¼");
		}else{
			m_dir.SetItemText(index, 1, L"�ļ�");
		}
		
	}
}


void CTESTDlg::OnBnClickedButton1()
{
	// TODO: 
	CString temp_dir;
	m_edit.GetWindowTextW(temp_dir);
	GetFileList(temp_dir);
}


void CTESTDlg::OnLvnItemActivateList3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	int pos = (int)m_dir.GetFirstSelectedItemPosition()-1;
	if (m_dir.GetItemText(pos, 1) == L"Ŀ¼") {
		//ΪĿ¼
		CString ori_content;
		m_edit.GetWindowTextW(ori_content);
		ori_content += L"\\"+ m_dir.GetItemText(pos, 0);
		m_edit.SetWindowTextW(ori_content);
		OnBnClickedButton1();
	}
}
