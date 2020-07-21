// TrackingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tracking.h"
#include "TrackingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrackingDlg dialog

CTrackingDlg::CTrackingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrackingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrackingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrackingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrackingDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTrackingDlg, CDialog)
	//{{AFX_MSG_MAP(CTrackingDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrackingDlg message handlers

BOOL CTrackingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	pf2d pf;
	int i;

	// get the angle of an object
	pf.get_yn();

	FILE *fp;
	fp = fopen("yn.txt","w"); 
	for(i=0;i<Nt;i++) 
		fprintf(fp,"%f\n",pf.yn[i]*180/pi);
	fclose(fp);

	// trace the object
	pf.estimate_pariticle_2d(); 

	int Width=600;
	int Height=600;

	SetWindowPos(NULL,0,0,Width,Height+20,SWP_NOMOVE|SWP_SHOWWINDOW);

	double max=0;
	int t;
	for(t=0;t<Nt;t++) {
		if(fabs(pf.target[0][t])>max)
			max = fabs(pf.target[0][t]);
		if(fabs(pf.target[1][t])>max)
			max = fabs(pf.target[1][t]);
		if(fabs(pf.estimate[0][t])>max)
			max = fabs(pf.estimate[0][t]);
		if(fabs(pf.estimate[1][t])>max)
			max = fabs(pf.estimate[1][t]);
	}

	CClientDC dc(this);	
	int x,y;
	int origin_x,origin_y;
	int rad=5;

	CBrush brush_t,brush_e,*pOldBrush;
	brush_t.CreateSolidBrush(RGB(0,0,255)); // target
	brush_e.CreateSolidBrush(RGB(255,0,0)); // estimate
	
	origin_x=Width/2,origin_y=Height/2+20;
	CPen pen_a,pen_t,pen_e,*pOldPen;
	pen_a.CreatePen(PS_DOT,1,RGB(0,0,0)); // axis
	pen_t.CreatePen(PS_SOLID,1,RGB(0,0,255)); // target
	pen_e.CreatePen(PS_SOLID,1,RGB(255,0,0)); // estimate

	// set pen for axis
	pOldPen = dc.SelectObject(&pen_a);
	// x axis
	dc.MoveTo(0,    origin_y);
	dc.LineTo(Width,origin_y);
	// y axis
	dc.MoveTo(origin_x,0);
	dc.LineTo(origin_x,Height);
	
	// select brush1
	dc.SelectObject(&pen_t);
	pOldBrush = (CBrush *)dc.SelectObject(&brush_t);

	// show target	
	bool l=false;
	for(t=0;t<Nt;t++) {
		x=origin_x + (int)(pf.target[0][t]/max*(Width/2+10));
		y=origin_y + (int)(pf.target[1][t]/max*(Height/2+10));
		
		if(l==false) {
			l=true;
			dc.MoveTo(x,y);
		}
		else {
			l=false;
			dc.LineTo(x,y);		
		}

		dc.Ellipse(x-rad,y-rad,x+rad,y+rad);
	}

	// set brush and pen for estimation
	dc.SelectObject(&brush_e);
	dc.SelectObject(&pen_e);
	l = false;
	// show tracking value
	for(t=0;t<Nt;t++) {
		x=origin_x + (int)(pf.estimate[0][t]/max*(Width/2+10));
		y=origin_y + (int)(pf.estimate[1][t]/max*(Height/2+10));

		if(l==false) {
			l=true;
			dc.MoveTo(x,y);
		}
		else {
			l=false;
			dc.LineTo(x,y);		
		}

		dc.Ellipse(x-rad,y-rad,x+rad,y+rad);
	}

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrackingDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrackingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
