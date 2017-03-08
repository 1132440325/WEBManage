
// WEBManageDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CWEBManageDlg 对话框
class CWEBManageDlg : public CDialogEx
{
// 构造
public:
	CWEBManageDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBMANAGE_DIALOG };
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
public:
	CEdit m_print_edit;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton1();
	void PrintInfo(CString content);
	CEdit m_edit_password;
};

void Proc_Listen(LPVOID app);

bool My_Send(SOCKET m_SOCKET, char * buf, int iSize);

CString GetMidStrByLAndR(CString & strSrc, CString strLeft, CString strRight);

CString GetRequestAddr(CString content);

BOOL SendHtmlDataByFile(SOCKET m_socket, CString filename);

BOOL SendHtmlDataByImg(SOCKET m_socket, CString filename);

BOOL SendHtmlDataByText(SOCKET m_socket, CString text);

BOOL SendScreenShot(SOCKET m_socket);

CString GetModuleDir();
