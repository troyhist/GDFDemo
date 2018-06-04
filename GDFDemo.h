// GDFDemo.h : main header file for the GDFDEMO application
//

#if !defined(AFX_GDFDEMO_H__177E1D98_3B0F_4123_BAD4_D1B29EF96209__INCLUDED_)
#define AFX_GDFDEMO_H__177E1D98_3B0F_4123_BAD4_D1B29EF96209__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGDFDemoApp:
// See GDFDemo.cpp for the implementation of this class
//

class CGDFDemoApp : public CWinApp
{
public:
	CGDFDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGDFDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGDFDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GDFDEMO_H__177E1D98_3B0F_4123_BAD4_D1B29EF96209__INCLUDED_)
