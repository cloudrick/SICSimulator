#if !defined(AFX_ONTROL_H__0FF792BE_B1E7_4665_9934_493570B587A7__INCLUDED_)
#define AFX_ONTROL_H__0FF792BE_B1E7_4665_9934_493570B587A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ontrol.h : header file
//

#include <string>

using namespace std ;
/////////////////////////////////////////////////////////////////////////////
// Control form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif


struct MISSLABLE
{
	int Addr ;
	int line ;
	string Name ;
	bool indexed ;
} ;

class Control : public CFormView
{
protected:
	Control();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(Control)

// Form Data
public:
	//{{AFX_DATA(Control)
	enum { IDD = IDD_ONTROL_FORM };
	CButton	m_b5;
	CButton	m_b4;
	CButton	m_b2;
	CButton	m_b1;
	float	m_step;
	float	m_runstep;
	CString	m_in;
	CString	m_out;
	//}}AFX_DATA

// Attributes
public:

	int pass_step ;
	int run_step ;
	unsigned long int loc  ;
	bool started  ;
	bool run_started ;

	MISSLABLE misslable[100] ;
	int ml_length ;


	bool JEQ ;
	bool JGT ;
	bool JLT ;

	int rsub_line ;
	int rsub_pc   ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Control)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~Control();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(Control)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStop();
	afx_msg void OnGo();
	afx_msg void OnStepGo();
	afx_msg void OnRun();
	afx_msg void OnRunStop();
	afx_msg void OnStepRun();
	afx_msg void OnClearMemory();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONTROL_H__0FF792BE_B1E7_4665_9934_493570B587A7__INCLUDED_)
