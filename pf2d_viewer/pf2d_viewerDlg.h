// pf2d_viewerDlg.h : header file
//

#if !defined(AFX_PF2D_VIEWERDLG_H__4F55DC57_AFEA_47E4_BB59_3B470D8BC3A6__INCLUDED_)
#define AFX_PF2D_VIEWERDLG_H__4F55DC57_AFEA_47E4_BB59_3B470D8BC3A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPf2d_viewerDlg dialog
#include "pf2d.h"
#include "size.h"

class CPf2d_viewerDlg : public CDialog
{
// Construction
public:
	CPf2d_viewerDlg(CWnd* pParent = NULL);	// standard constructor
	pf2d pf;

// Dialog Data
	//{{AFX_DATA(CPf2d_viewerDlg)
	enum { IDD = IDD_PF2D_VIEWER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPf2d_viewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPf2d_viewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PF2D_VIEWERDLG_H__4F55DC57_AFEA_47E4_BB59_3B470D8BC3A6__INCLUDED_)
