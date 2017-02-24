#if !defined(AFX_SYMTAB_H__825CD842_A941_4EEF_8756_07D17C9D1A32__INCLUDED_)
#define AFX_SYMTAB_H__825CD842_A941_4EEF_8756_07D17C9D1A32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Symtab.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Symtab form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class Symtab : public CFormView
{
protected:
	Symtab();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(Symtab)

// Form Data
public:
	//{{AFX_DATA(Symtab)
	enum { IDD = IDD_SYMTAB_FORM };
	CListCtrl	m_symtab;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Symtab)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~Symtab();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(Symtab)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYMTAB_H__825CD842_A941_4EEF_8756_07D17C9D1A32__INCLUDED_)
