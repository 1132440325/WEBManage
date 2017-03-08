
// WEBManageDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CWEBManageDlg �Ի���
class CWEBManageDlg : public CDialogEx
{
// ����
public:
	CWEBManageDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBMANAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
