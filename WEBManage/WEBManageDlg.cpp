
// WEBManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WEBManage.h"
#include "WEBManageDlg.h"
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


// CWEBManageDlg 对话框



CWEBManageDlg::CWEBManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WEBMANAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWEBManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PRINT, m_print_edit);
	DDX_Control(pDX, IDC_EDIT2, m_edit_password);
}

BEGIN_MESSAGE_MAP(CWEBManageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CWEBManageDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CWEBManageDlg 消息处理程序

BOOL CWEBManageDlg::OnInitDialog()
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
	SetDlgItemText(IDC_EDIT1,L"9000");
	SetDlgItemText(IDC_EDIT2, L"admin");
	PrintInfo(L"欢迎使用WEB远程协助软件1.0，请勿用于非法用途！");

	
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWEBManageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWEBManageDlg::OnPaint()
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
HCURSOR CWEBManageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWEBManageDlg::PrintInfo(CString content)
{
	if (content == "") {
		return;
	}
	m_print_edit.SetSel(-1);
	m_print_edit.ReplaceSel((content + L"\r\n"));
}


void CWEBManageDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}


void CWEBManageDlg::OnBnClickedButton1()
{
	AfxBeginThread((AFX_THREADPROC)Proc_Listen, this);
	
}

void Proc_Listen(LPVOID app)
{
	CWEBManageDlg *App = (CWEBManageDlg *)app;
	App->GetDlgItem(IDC_BUTTON1)->SetWindowTextW(L"关闭");
	SOCKET serversoc;
	SOCKET clientsoc;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN clientaddr;
	int len;
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 0), &wsa);
	if ((serversoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		App->PrintInfo(L"套接字socket创建失败!\n");
	}

	//命名协议，IP，端口
	serveraddr.sin_family = AF_INET;
	CString port;
	App->GetDlgItemTextW(IDC_EDIT1, port);	
	serveraddr.sin_port = htons(_ttoi(port));
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//绑定套接字
	if (bind(serversoc, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		App->PrintInfo(L"套接字绑定失败!\n");
	}

	App->PrintInfo(L"开始监听...\n");
	//监听请求
	if (listen(serversoc, 1) != 0)
	{
		App->PrintInfo(L"监听失败!\n");
	}

	len = sizeof(SOCKADDR_IN);
	CString CheckedIP;
	while (TRUE)
	{
		if ((clientsoc = accept(serversoc, (SOCKADDR *)&clientaddr, &len)) <= 0)
		{
			App->PrintInfo(L"接受连接失败!\n");
		}
		else {
			App->PrintInfo(L"[+]收到一个连接！\n");
			while (TRUE)
			{
				char buf[1024] = { 0 };
				if (recv(clientsoc, buf, 1024, 0) <= 0 ) {
					//连接已经出错
					App->PrintInfo(L"[-]一个客户已退出！\n");
					break;
				}
				else {
					//连接正常继续处理
					App->PrintInfo(L"[+]接收到一个请求\n");
					CString sBuf(buf);
					char* ipAddr = inet_ntoa(clientaddr.sin_addr);
					CString sIpAddr(ipAddr);
					App->PrintInfo(L"[+]来自客户端："+ sIpAddr +" 请求地址:" + GetRequestAddr(sBuf));
					if (sIpAddr != CheckedIP) {
						//未通过身份认证
						if (GetRequestAddr(sBuf).Find(L"/?password=") != -1) {
							CString password;
							App->GetDlgItemTextW(IDC_EDIT2, password);
							if (GetRequestAddr(sBuf) == L"/?password=" + password);
							{
								//认证密码通过
								CheckedIP = sIpAddr;
								App->PrintInfo(L"[+]IP地址：" + sIpAddr + L"通过认证");
								SendHtmlDataByFile(clientsoc, L"Index.html");
								continue;
							}
						}
						SendHtmlDataByFile(clientsoc, L"Login.html");
						continue;
					}
					if (GetRequestAddr(sBuf).Find(L"?x") != -1 && GetRequestAddr(sBuf).Find(L"&y") != -1) {
						//请求点击
						int x = _ttoi(GetMidStrByLAndR(GetRequestAddr(sBuf), L"?x=", L"&y"));
						int y = _ttoi(GetMidStrByLAndR(GetRequestAddr(sBuf)+L"|", L"&y=", L"|"));
						SetCursorPos(x, y);
						mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						SendHtmlDataByText(clientsoc,L"1");
					}
					if (GetRequestAddr(sBuf).Find(L"ScreenShot.bmp")!=-1) {
						//请求屏幕截图
						SendScreenShot(clientsoc);
						continue;
					}
					if (GetRequestAddr(sBuf) == L"/"){
						//请求首页
						SendHtmlDataByFile(clientsoc, L"Index.html");
						continue;
					}
					if (GetRequestAddr(sBuf).Find(L"password") != -1) {
						SendHtmlDataByFile(clientsoc, L"Index.html");
						continue;
					}
					else {
						SendHtmlDataByImg(clientsoc, GetRequestAddr(sBuf));
						continue;
					}
				}
			}
		}
		Sleep(1000);
	}
}

bool My_Send(SOCKET m_SOCKET, char* buf, int iSize) {
	int iSended = send(m_SOCKET, buf, iSize, 0);
	while (iSended < iSize)
	{
		if (iSended <= 0) {
			return false;
		}
		iSended = send(m_SOCKET, &buf[iSended], iSize - iSended, 0);
	}
	return TRUE;
}
CString GetMidStrByLAndR(CString& strSrc, CString strLeft, CString strRight)
{
	CString strRet;
	int eIdxBegin = strSrc.Find(strLeft);
	if (eIdxBegin != -1)
	{
		eIdxBegin += strLeft.GetLength();
		int eIdxEnd = strSrc.Find(strRight, eIdxBegin);
		if (eIdxEnd != -1)
		{
			strRet = strSrc.Mid(eIdxBegin, eIdxEnd - eIdxBegin);
			return strRet;
		}
	}

	return strRet;
}
CString GetRequestAddr(CString content) 
{
	return GetMidStrByLAndR(content, L"GET ", L" HTTP");
}
BOOL SendHtmlDataByFile(SOCKET m_socket,CString filename)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; //删除文件名，只获得路径
	CString str_url = szFilePath;    //str_url 中保存的是当前目录
	CFile file;
	CString c_filename;
	c_filename = str_url + L"\Src\\" + filename;
	if (!file.Open(c_filename, CFile::modeRead))
	{
		return FALSE;
	}
	ULONGLONG iFilelenth = file.GetLength();
	char* tempbuf = (char *)malloc(iFilelenth * sizeof(char));
	if (tempbuf == NULL) {
		MessageBoxA(0, "为文件申请内存失败！","",MB_OK);
		return FALSE;
	}
	file.Read(tempbuf, iFilelenth);
	char headerbuf[1024];
	sprintf_s(headerbuf, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n", (INT)iFilelenth);
	
	char* databuf = (char *)malloc((1024 + iFilelenth) * sizeof(char));
	strcpy(databuf, headerbuf);
	strcat_s(databuf, (1024 + iFilelenth) * sizeof(char), tempbuf);
	free(tempbuf);
	My_Send(m_socket, databuf, (1024 + iFilelenth) * sizeof(char));
	return TRUE;
}
BOOL SendHtmlDataByImg(SOCKET m_socket, CString filename)
{
	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; //删除文件名，只获得路径
	CString str_url = szFilePath;    //str_url 中保存的是当前目录
	CFile file;
	CString c_filename;
	c_filename = str_url + L"\Src\\" + filename;
	if (!file.Open(c_filename, CFile::modeRead))
	{
		return FALSE;
	}
	ULONGLONG iFilelenth = file.GetLength();
	char* tempbuf = (char *)malloc(iFilelenth * sizeof(char));
	file.Read(tempbuf, iFilelenth);
	char headerbuf[1024];
	sprintf_s(headerbuf, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n", (INT)iFilelenth);
	char* databuf = (char *)malloc(1024 + iFilelenth);
	My_Send(m_socket, headerbuf, strlen(headerbuf) * sizeof(char));
	My_Send(m_socket, tempbuf, iFilelenth);
	free(tempbuf);
	return TRUE;
}
BOOL SendHtmlDataByText(SOCKET m_socket, CString text)
{
	CString ResponseHeader;
	ResponseHeader.Format(L"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n", text.GetLength());
	ResponseHeader += text;
	USES_CONVERSION;
	My_Send(m_socket, T2A((LPCTSTR)ResponseHeader), ResponseHeader.GetLength());
	return TRUE;
}

BOOL SendScreenShot(SOCKET m_socket) 
{
	// TODO: 在此添加额外的初始化代码
	CWnd *pDesktop = CWEBManageDlg::GetDesktopWindow();
	CDC *pdeskdc = pDesktop->GetDC();
	CRect re;
	pDesktop->GetClientRect(&re);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pdeskdc, re.Width(), re.Height());
	CDC memorydc;
	memorydc.CreateCompatibleDC(pdeskdc);
	CBitmap *pold = memorydc.SelectObject(&bmp);
	memorydc.BitBlt(0, 0, re.Width(), re.Height(), pdeskdc, 0, 0, SRCCOPY);
	CPoint po;
	GetCursorPos(&po);
	HICON hicon = (HICON)GetCursor();
	memorydc.DrawIcon(po.x - 10, po.y - 10, hicon);
	memorydc.SelectObject(pold);
	BITMAP bit;
	bmp.GetBitmap(&bit);
	DWORD size = bit.bmWidthBytes * bit.bmHeight;
	LPSTR lpdata = (LPSTR)GlobalAlloc(GPTR, size);
	BITMAPINFOHEADER pbitinfo;
	pbitinfo.biBitCount = 24;
	pbitinfo.biClrImportant = 0;
	pbitinfo.biCompression = BI_RGB;
	pbitinfo.biHeight = bit.bmHeight;
	pbitinfo.biPlanes = 1;
	pbitinfo.biSize = sizeof(BITMAPINFOHEADER);
	pbitinfo.biSizeImage = size;
	pbitinfo.biWidth = bit.bmWidth;
	pbitinfo.biXPelsPerMeter = 0;
	pbitinfo.biYPelsPerMeter = 0;
	GetDIBits(pdeskdc->m_hDC, bmp, 0, pbitinfo.biHeight, lpdata, (BITMAPINFO*)&pbitinfo, DIB_RGB_COLORS);
	BITMAPFILEHEADER bfh;
	bfh.bfReserved1 = bfh.bfReserved2 = 0;
	bfh.bfType = ((WORD)('M' << 8) | 'B');
	bfh.bfSize = size + 54;
	bfh.bfOffBits = 54;
	//写入文件  
	CFile file;
	CString strFileName(GetModuleDir());
	strFileName += _T("\\Src\\");
	CreateDirectory((LPCTSTR)strFileName, NULL);
	CTime t = CTime::GetCurrentTime();
	CString tt = t.Format("%Y-%m-%d_%H-%M-%S");
	strFileName += tt;
	strFileName += _T(".bmp");
	if (file.Open((LPCTSTR)strFileName, CFile::modeCreate | CFile::modeWrite))
	{
		file.Write(&bfh, sizeof(BITMAPFILEHEADER));
		file.Write(&pbitinfo, sizeof(BITMAPINFOHEADER));
		file.Write(lpdata, size);
		file.Close();
	}
	GlobalFree(lpdata);
	SendHtmlDataByImg(m_socket, tt + L".bmp");
	DeleteFile(strFileName);
	return TRUE;  
}
CString GetModuleDir()
{
	HMODULE module = GetModuleHandle(0);
	WCHAR pFileName[MAX_PATH];
	GetModuleFileName(module, pFileName, MAX_PATH);

	CString csFullPath(pFileName);
	int nPos = csFullPath.ReverseFind(_T('\\'));
	if (nPos < 0)
		return CString("");
	else
		return csFullPath.Left(nPos);
}