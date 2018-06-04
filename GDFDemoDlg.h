// GDFDemoDlg.h : header file
//

#if !defined(AFX_GDFDEMODLG_H__24AB99BB_F7E4_427B_8E3C_EC393FC97A19__INCLUDED_)
#define AFX_GDFDEMODLG_H__24AB99BB_F7E4_427B_8E3C_EC393FC97A19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGDFDemoDlg dialog

class CGDFDemoDlg : public CDialog
{
// Construction
public:
	CGDFDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGDFDemoDlg)
	enum { IDD = IDD_GDFDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGDFDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGDFDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBdraw();
	afx_msg void OnBstars();
	afx_msg void OnBfigures();
	afx_msg void OnBgo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GDFDEMODLG_H__24AB99BB_F7E4_427B_8E3C_EC393FC97A19__INCLUDED_)
