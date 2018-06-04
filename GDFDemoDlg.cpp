// =======================================================================
// GDFDemoDlg.cpp : implementation file
// =======================================================================
#include "stdafx.h"
#include "GDFDemo.h"
#include "GDFDemoDlg.h"
// -----------------------------------------------------------------------
#include <math.h>
#include "GDF.h"
// -----------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// =======================================================================
int pBullet[]=
	{
	GDF_POLYFL, 6, -10, -4, 4, -4, 15, 0,
		           4, 4, -10, 4, -10, -4, 0, 4,
				   0
	};
// =======================================================================
int pTank[]=
	{
	// korpus
	GDF_RECTFL, -60, 40, 60,-40,		0,	2,
		GDF_LN, -60, 25, 60, 25,		0,
		GDF_LN, -60,-25, 60,-25,		0,
	GDF_RECTFL, -50, 20,-35,  5,		0,	2,
	GDF_RECTFL, -50,-20,-35, -5,		0,	2,
	// gusenitsi
	GDF_RECTFL, -58, 42, 58, 40,		0,	2,
	GDF_RECTFL, -58,-42, 58,-40,		0,	2,
	// bashnya
	GDF_POLYFL, 9,	-15, 8, -2, 20, 20, 20, 28, 8,
					28, -8, 20,-20, -2,-20,-15,-8,-15, 8, 0, 2,
	GDF_RECTFL, 15, -17, 20, -3,		0,	2,
	GDF_CIRCFL,  9, 9, 9,			0,	2,	
	GDF_RECTFL, 17, 6, 19, 12,		0,  2,
	GDF_RECTFL, 28, -3, 110, 3,		0,  2,
	GDF_RECTFL, 110, -4, 120, 4,		0,  2,
	0
	};
// =======================================================================
int pTankBrown[]=
	{
	// korpus
	GDF_RECTFL, -60, 40, 60,-40,		0,	6,
		GDF_LN, -60, 25, 60, 25,		0,
		GDF_LN, -60,-25, 60,-25,		0,
	GDF_RECTFL, -50, 20,-35,  5,		0,	6,
	GDF_RECTFL, -50,-20,-35, -5,		0,	6,
	// gusenitsi
	GDF_RECTFL, -58, 42, 58, 40,		0,	6,
	GDF_RECTFL, -58,-42, 58,-40,		0,	6,
	// bashnya
	GDF_POLYFL, 9,	-15, 8, -2, 20, 20, 20, 28, 8,
					28, -8, 20,-20, -2,-20,-15,-8,-15, 8, 0, 6,
	GDF_RECTFL, 15, -17, 20, -3,		0,	6,
	GDF_CIRCFL,  9, 9, 9,				0,	6,	
	GDF_RECTFL, 17, 6, 19, 12,			0,  6,
	GDF_RECTFL, 28, -3, 110, 3,			0,  6,
	GDF_RECTFL, 110, -4, 120, 4,		0,  6,
	0
	};
// =======================================================================
int pPlane[]=
	{
	// body
	GDF_RECTFL, -45, 10, 45, -10, 8, 7,
	// rockets - left
	GDF_RECTFL, -5,-60,22,-57,8,7, GDF_TRIFL, 22,-60,25,-58,22,-57,12,4,
	GDF_RECTFL, -5,-50,22,-47,8,7, GDF_TRIFL, 22,-50,25,-48,22,-47,12,4,
	GDF_RECTFL, -5,-40,22,-37,8,7, GDF_TRIFL, 22,-40,25,-38,22,-37,12,4,
	// rockets - right
	GDF_RECTFL, -5,60,22,57,8,7, GDF_TRIFL, 22,60,25,58,22,57,12,4,
	GDF_RECTFL, -5,50,22,47,8,7, GDF_TRIFL, 22,50,25,48,22,47,12,4,
	GDF_RECTFL, -5,40,22,37,8,7, GDF_TRIFL, 22,40,25,38,22,37,12,4,
	// forward
	GDF_POLYFL, 5, 45, -10, 67, -5, 67, 5, 45, 10, 45, -10, 8, 7,
	GDF_TRIFL, 67, -3, 75, 0, 67, 3, 8, 7,
	// wings
	GDF_POLYFL, 4, 0, -10, 0, -70, 15, -70, 25, -10, 8, 7,
	GDF_POLYFL, 4, 0, 10, 0, 70, 15, 70, 25, 10, 8, 7,
	// rul'
	GDF_RECT, 0,-55,5,-15,8,
	GDF_RECT, 0,55,5,15,8,
	// stabiliser
	GDF_POLYFL, 6, -2,-70, -2,-75, 15,-75, 19,-72, 15,-70, -2,-70, 8, 7,
	GDF_POLYFL, 6, -2,70, -2,75, 15,75, 19,72, 15,70, -2,70, 8, 7,
	// zakryliky
	GDF_POLYFL, 4, -45,-10, -45,-30, -35,-30, -30,-10, 8, 7,
	GDF_POLYFL, 4, -45,10, -45,30, -35,30, -30,10, 8, 7,
	// rul' 2
	GDF_RECT, -45,-25,-43,-12,8,
	GDF_RECT, -45,25,-43,12,8,
	// sopla
	GDF_RECTFL, -45,-2,-47,-8,8,7,
	GDF_RECTFL, -45,2,-47,8,8,7,
	// back wing
	GDF_TRI, -40,-2,-20,0,-40, 2, 8,
	GDF_LN, -40,0,-20,0,8,
	// baki
	GDF_RECT, 20,-7,35,-10,8,
	GDF_RECT, 20,7,35,10,8,
	// kabina (fonar')
	GDF_RECT, 20,-3,35,3, 8,
	GDF_TRI, 35,-3,37,0,35, 3, 8,
	GDF_TRI, 20,-3,18,0,20, 3, 8,
	// onboard number
	GDF_POLY, 3, 10,-40, 15,-37, 10,-35, 8,
	GDF_LN, 12,-39,12,-36,8,
	GDF_LN, 12,-33,12,-31,8,
	GDF_POLY, 3, 13,-29, 15,-27, 10,-27, 8,
	GDF_RECT, 10,-25,15,-22,8,
	// onboard name
	GDF_POLY, 4,10,22,10,20,15,20,15,22,8,
	GDF_POLY, 4,10,27,10,25,15,25,15,27,8,
	GDF_POLY, 4,10,32,10,30,15,30,15,32,8,
	GDF_LN, 10,35,15,35,8,
	GDF_RECT, 15,35,12,37,8,
	0};
// =======================================================================
int pPAL16[]=
	{
	// body
	GDF_RECTFL, -80, 20, -70, -20, 14, 0,
	GDF_RECTFL, -70, 20, -60, -20, 14, 1,
	GDF_RECTFL, -60, 20, -50, -20, 14, 2,
	GDF_RECTFL, -50, 20, -40, -20, 14, 3,
	GDF_RECTFL, -40, 20, -30, -20, 14, 4,
	GDF_RECTFL, -30, 20, -20, -20, 14, 5,
	GDF_RECTFL, -20, 20, -10, -20, 14, 6,
	GDF_RECTFL, -10, 20,   0, -20, 14, 7,
	GDF_RECTFL,   0, 20,  10, -20, 14, 8,
	GDF_RECTFL,  10, 20,  20, -20, 14, 9,
	GDF_RECTFL,  20, 20,  30, -20, 14, 10,
	GDF_RECTFL,  30, 20,  40, -20, 14, 11,
	GDF_RECTFL,  40, 20,  50, -20, 14, 12,
	GDF_RECTFL,  50, 20,  60, -20, 14, 13,
	GDF_RECTFL,  60, 20,  70, -20, 14, 14,
	GDF_RECTFL,  70, 20,  80, -20, 14, 15,
	0};
// =======================================================================
int pFIGS[]=
	{			
	GDF_PIX,	25, 10, 0,	
	GDF_LN,		5,	5, 25, 25, 2,
	GDF_LNC,	25,	25,	45,	5,	35, 20, 35, 10,	1,
	GDF_RECT,	50,	10, 60,	25,	4,
	GDF_RECTFL,	65, 10, 75, 25, 4, 12,
	GDF_POLYB,	13,	50,	30, 
					52, 33, 58, 28, 60,	30, 
					62, 35, 58, 40, 60,	45,	
					58, 43, 52, 47, 50,	45,	
					48, 49, 52, 34, 50,	30, 1,	
	GDF_POLYBFL,13,	65,	30, 
					67, 33, 73, 28, 75,	30, 
					77, 35, 73, 40, 75,	45,	
					73, 43, 67, 47, 65,	45,	
					63, 49, 67, 34, 65,	30, 1, 9,
	GDF_TRI,	5,	45,	12, 30, 20, 45, 2,
	GDF_TRIFL,	25,	45,	32, 30, 40, 45, 2, 10,
	GDF_CIRC,	12, 57, 7, 1,
	GDF_CIRCFL,	32, 57, 7, 1, 9,
	GDF_ELL,	50, 50, 60, 65, 6,
	GDF_ELLFL,	65, 50, 75, 65, 6, 14,
	// brush styles
	GDF_CC,		GDF_CBRST,	HS_BDIAGONAL,
	GDF_RECTFL,	80, 10, 90, 25, 1, 9,
	GDF_CC,		GDF_CBRST,	HS_CROSS,
	GDF_RECTFL,	95, 10,105, 25, 2, 10,
	GDF_CC,		GDF_CBRST,	HS_DIAGCROSS,
	GDF_RECTFL,	110,10,120, 25, 3, 11,
	GDF_CC,		GDF_CBRST,	HS_FDIAGONAL,
	GDF_RECTFL,	80, 30, 90, 45, 4, 12,
	GDF_CC,		GDF_CBRST,	HS_HORIZONTAL,
	GDF_RECTFL,	95, 30,105, 45, 5, 13,
	GDF_CC,		GDF_CBRST,	HS_VERTICAL,
	GDF_RECTFL,	110,30,120, 45, 6, 14,
	GDF_CC,		GDF_CBRST,	HS_SOLID,
	// pen styles
	GDF_CC,		GDF_CPST,	PS_DASH,
	GDF_TRIFL,	80,	50,	85, 65, 90, 50, 11, 11,
	GDF_CC,		GDF_CPST,	PS_DOT,
	GDF_TRIFL,	90,	65, 95, 50,100, 65, 9, 9,
	GDF_CC,		GDF_CPST,	PS_DASHDOT,
	GDF_TRIFL, 100,	50,105, 65,110, 50, 13, 13,
	GDF_CC,		GDF_CPST,	PS_DASHDOTDOT,
	GDF_TRIFL, 110,	65,115, 50,120, 65, 12, 12,
	GDF_CC,		GDF_CPST,	PS_SOLID,
	// pen sizes	
	GDF_CC,		GDF_CPSZ,	2,
	GDF_RECTFL,125, 10,135, 25, 1, 9,
	GDF_CC,		GDF_CPSZ,	3,
	GDF_RECTFL,125, 30,135, 45, 2, 10,
	GDF_CC,		GDF_CPSZ,	5,
	GDF_RECTFL,125, 50,135, 65, 4, 12,
	0};
// =======================================================================
// CAboutDlg dialog used for App About
// =======================================================================
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
// =======================================================================
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}
// =======================================================================
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}
// =======================================================================
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
// =======================================================================
// CGDFDemoDlg dialog
// =======================================================================
CGDFDemoDlg::CGDFDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGDFDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGDFDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
// =======================================================================
void CGDFDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGDFDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
// =======================================================================
BEGIN_MESSAGE_MAP(CGDFDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CGDFDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BDRAW, OnBdraw)
	ON_BN_CLICKED(IDC_BSTARS, OnBstars)
	ON_BN_CLICKED(IDC_BFIGURES, OnBfigures)
	ON_BN_CLICKED(IDC_BGO, OnBgo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
// =======================================================================
// CGDFDemoDlg message handlers
// =======================================================================
BOOL CGDFDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
// =======================================================================
void CGDFDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}
// =======================================================================
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
// =======================================================================
void CGDFDemoDlg::OnPaint() 
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
// =======================================================================
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGDFDemoDlg::OnQueryDragIcon()
{
return (HCURSOR) m_hIcon;
}
// =======================================================================
void CGDFDemoDlg::OnBfigures() 
{
CRect r;
CDC* pDC=GetDC();
CGDF tGDF;
tGDF.SetDC(pDC);
GetWindowRect(&r);
tGDF.Put(100, 100, 3, 4, pFIGS);
GetWindowRect(&r);
//tGDF.Put(r.Width()/2, r.Height()/2, 45, 3, pPlane);
pDC->SetROP2(R2_NOTXORPEN);
//int *pPtr=pPlane;
int *pPtr=pFIGS;
for (int i=45; i<=45+2*360; i++)
//for (double i=45; i<=45+2*360; i+=.05)
	{
	tGDF.Put(r.Width()/2, r.Height()/2, i, 3, pPtr);
	tGDF.Put(r.Width()/2, r.Height()/2, i, 3, pPtr);	
	}
pDC->SetROP2(R2_COPYPEN); 
ReleaseDC(pDC);
}
// =======================================================================
void CGDFDemoDlg::OnBdraw() 
{
CDC* pDC=GetDC();
CGDF tGDF;
tGDF.SetDC(pDC);
tGDF.Put(200, 150, 90, 1, pPlane);
tGDF.Put(400, 150, 90, 1, pTank);
tGDF.Put(500, 150, 90, 1, pBullet);
tGDF.Put(300, 300, -45, 0.5, pTankBrown);
tGDF.Put(200, 300, -45, 0.5, pPlane);
ReleaseDC(pDC);
}
// =======================================================================
void CGDFDemoDlg::OnBstars() 
{
CRect r;
CDC* pDC=GetDC();
CGDF tGDF;
tGDF.SetDC(pDC);
GetWindowRect(&r);
tGDF.DrawStars(0, 0, r.Width(), r.Height(), 1000);
pDC->SetROP2(R2_XORPEN);
for (int i=0; i<=2*360; i++)
	{
	tGDF.Put(r.Width()/2, r.Height()/2, i, 3, pPAL16);
	tGDF.Put(r.Width()/2, r.Height()/2, i, 3, pPAL16);	
	}
pDC->SetROP2(R2_COPYPEN); tGDF.Put(300, 300, 0, 2, pPAL16);
ReleaseDC(pDC);
}
// =======================================================================
void CGDFDemoDlg::OnBgo() 
{
// -----------------------------------------------------------------------
CDC* pDC=GetDC();
CGDF tGDF;
tGDF.SetDC(pDC);
// -----------------------------------------------------------------------
int i=0;
int dx[2], dy[2];
POINT pBullets[4];
POINT pTanks[2];
int pBAngles[4], pTAngles[2], pTSpd[2];
pTanks[0].x=10; pTanks[0].y=10;		pTAngles[0]=-45; pTSpd[0]=2;
pTanks[1].x=600; pTanks[1].y=600;	pTAngles[1]=160; pTSpd[1]=2;
// -----------------------------------------------------------------------
pDC->SetROP2(R2_XORPEN);
// -----------------------------------------------------------------------
#define M_PIM	(3.1415926535)
#define DEGtoRAD(_nA_)	(M_PIM*(_nA_)/180)
//#define DEGtoRAD, sn=sin(M_PI*nAngle/180);
while (i++<1000)
	{
	// -------------------------------------------------------------------
	dx[0]=pTanks[0].x-pTanks[1].x;
	dy[0]=pTanks[0].y-pTanks[1].y;
	// -------------------------------------------------------------------
	dx[1]=pTanks[1].x-pTanks[0].x;
	dy[1]=pTanks[1].y-pTanks[0].y;
	// -------------------------------------------------------------------
		{
		/*if (dx[0]>50) dx[0]--;
		if (dy[0]>50) dy[0]--;
		if (dx[0]<20) dx[0]++;
		if (dy[0]<20) dy[0]++;*/
		}
	// -------------------------------------------------------------------
 	dx[0]=pTSpd[0]*cos(DEGtoRAD(-pTAngles[0]));
	dy[0]=pTSpd[0]*sin(DEGtoRAD(-pTAngles[0]));
	pTanks[0].x+=dx[0];
	pTanks[0].y+=dy[0];
	// -------------------------------------------------------------------
	dx[1]=pTSpd[1]*cos(DEGtoRAD(-pTAngles[1]));
	dy[1]=pTSpd[1]*sin(DEGtoRAD(-pTAngles[1]));
	pTanks[1].x+=dx[1];
	pTanks[1].y+=dy[1];
	// -------------------------------------------------------------------
	tGDF.Put(pTanks[0].x, pTanks[0].y, pTAngles[0], .5, pTank);
	tGDF.Put(pTanks[1].x, pTanks[1].y, pTAngles[1], .5, pTankBrown);
	// -------------------------------------------------------------------
	tGDF.Put(pTanks[0].x, pTanks[0].y, pTAngles[0], .5, pTank);
	tGDF.Put(pTanks[1].x, pTanks[1].y, pTAngles[1], .5, pTankBrown);
	}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
}
