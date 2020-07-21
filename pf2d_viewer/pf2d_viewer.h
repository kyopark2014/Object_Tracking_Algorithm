// pf2d_viewer.h : main header file for the PF2D_VIEWER application
//

#if !defined(AFX_PF2D_VIEWER_H__B1C9EE28_B03E_4369_9697_D16B0F6CE4D2__INCLUDED_)
#define AFX_PF2D_VIEWER_H__B1C9EE28_B03E_4369_9697_D16B0F6CE4D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "pf2d.h"

/////////////////////////////////////////////////////////////////////////////
// CPf2d_viewerApp:
// See pf2d_viewer.cpp for the implementation of this class
//

class CPf2d_viewerApp : public CWinApp
{
public:
	CPf2d_viewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPf2d_viewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPf2d_viewerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PF2D_VIEWER_H__B1C9EE28_B03E_4369_9697_D16B0F6CE4D2__INCLUDED_)
