// TrackingDlg.h : header file
//

#if !defined(AFX_TRACKINGDLG_H__8466897F_7717_4BDB_9BF0_301437AC603E__INCLUDED_)
#define AFX_TRACKINGDLG_H__8466897F_7717_4BDB_9BF0_301437AC603E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "size.h"
#include "pf2d.h"

/////////////////////////////////////////////////////////////////////////////
// CTrackingDlg dialog

class CTrackingDlg : public CDialog
{
// Construction
public:
	CTrackingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTrackingDlg)
	enum { IDD = IDD_TRACKING_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTrackingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACKINGDLG_H__8466897F_7717_4BDB_9BF0_301437AC603E__INCLUDED_)
