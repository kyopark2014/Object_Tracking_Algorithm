// Tracking.h : main header file for the TRACKING application
//

#if !defined(AFX_TRACKING_H__C6EE4B0E_B8F9_4562_8168_5BA80BA3EA33__INCLUDED_)
#define AFX_TRACKING_H__C6EE4B0E_B8F9_4562_8168_5BA80BA3EA33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTrackingApp:
// See Tracking.cpp for the implementation of this class
//

class CTrackingApp : public CWinApp
{
public:
	CTrackingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrackingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTrackingApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACKING_H__C6EE4B0E_B8F9_4562_8168_5BA80BA3EA33__INCLUDED_)
