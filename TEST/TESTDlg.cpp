
// TESTDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TEST.h"
#include "TESTDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTESTDlg 对话框



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


// CTESTDlg 消息处理程序

BOOL CTESTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	int DeskCount = 0;
	DWORD DeskInfo = GetLogicalDrives();
	while (DeskInfo)//通过循环操作查看每一位数据是否为1，如果为1则磁盘为真,如果为0则磁盘不存在。
	{
		if (DeskInfo & 1)//通过位运算的逻辑与操作，判断是否为1
		{
			++DeskCount;
		}
		DeskInfo = DeskInfo >> 1;//通过位运算的右移操作保证每循环一次所检查的位置向右移动一位。
	}
	DWORD DSLength = GetLogicalDriveStrings(0, NULL);
	LPTSTR lpDriveStrings = (LPTSTR)HeapAlloc(GetProcessHeap(), 0, DSLength * sizeof(TCHAR));
	//通过GetLogicalDriveStrings()函数获取所有驱动器字符串信息长度。
	GetLogicalDriveStrings(DSLength, lpDriveStrings);
	WCHAR temp_dir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,temp_dir);
	m_edit.SetWindowTextW(temp_dir);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, L"磁盘名",0,75);
	m_list.InsertColumn(1, L"磁盘类型", 0, 100);
	m_list.InsertColumn(2, L"总空间", 0, 100);
	m_list.InsertColumn(3, L"剩余空间", 0, 100);
	m_list.InsertColumn(4, L"使用空间",0, 100);
	m_dir.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_dir.InsertColumn(0, L"文件名", 0, 150);
	m_dir.InsertColumn(1, L"文件类型", 0, 100);
	//通过GetLogicalDriveStrings将字符串信息复制到堆区数组中,其中保存了所有驱动器的信息。
	int DType;
	int si = 0;
	BOOL fResult;
	unsigned _int64 i64FreeBytesToCaller;
	unsigned _int64 i64TotalBytes;
	unsigned _int64 i64FreeBytes;
	for (DWORD i = 0; i < (DSLength / 4); ++i)
		//为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
	{

		char  dir2[3] = { lpDriveStrings[si], ':', '\0' };//盘符ABCD等
		TCHAR dir[3] = { lpDriveStrings[si], ':', '\0' };
		DType = GetDriveType(lpDriveStrings + i * 4);//磁盘类型，光盘，磁盘，硬盘等
		fResult = GetDiskFreeSpaceEx(
			dir,
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);
		//GetDiskFreeSpaceEx函数，可以获取驱动器磁盘的空间状态,使用或未用空间大小，函数返回的是个BOOL类型数据
		if (fResult == TRUE)//通过返回的BOOL数据判断驱动器是否在工作状态
		{
			//输出空间大小，注意此处单位b，
			int index = m_list.InsertItem(m_list.GetItemCount(), dir);
			CString Driver_Type = L"";
			switch (DType)
			{
			case DRIVE_REMOVABLE:
				Driver_Type = L"软盘驱动器";
				break;
			case DRIVE_FIXED:
				Driver_Type = L"硬盘";
				break;
			case DRIVE_REMOTE:
				Driver_Type = L"网络驱动器";
				break;
			case DRIVE_CDROM:
				Driver_Type = L"CD-ROM驱动器";
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTESTDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CTESTDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//
//	*pResult = 0;
//}


void CTESTDlg::OnLvnItemActivateList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	WCHAR dir[4] = { 0 };
	m_list.GetItemText((int)m_list.GetFirstSelectedItemPosition()-1,0,dir,3);
	wcscat_s(dir, 4, L"\\");
	m_edit.SetWindowTextW(dir);
	*pResult = 0;
}
void CTESTDlg::GetFileList(CString sFolderPath)
{
	//遍历文件夹里面的文件  
	m_dir.DeleteAllItems();
	WIN32_FIND_DATA FindData;
	HANDLE hError;
	sFolderPath += L"\\*.*";
	hError = FindFirstFile(sFolderPath, &FindData);
	if (hError == INVALID_HANDLE_VALUE)
	{
		MessageBox(L"查找失败!");
		return;
	}
	while (::FindNextFile(hError, &FindData))
	{
		int index = m_dir.InsertItem(m_dir.GetItemCount(),FindData.cFileName);
		if (FindData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			//目录
			m_dir.SetItemText(index, 1, L"目录");
		}else{
			m_dir.SetItemText(index, 1, L"文件");
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
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int pos = (int)m_dir.GetFirstSelectedItemPosition()-1;
	if (m_dir.GetItemText(pos, 1) == L"目录") {
		//为目录
		CString ori_content;
		m_edit.GetWindowTextW(ori_content);
		ori_content += L"\\"+ m_dir.GetItemText(pos, 0);
		m_edit.SetWindowTextW(ori_content);
		OnBnClickedButton1();
	}
}
