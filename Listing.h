#if !defined(AFX_LISTING_H__966C71E7_B5ED_402A_B045_1776E04BA324__INCLUDED_)
#define AFX_LISTING_H__966C71E7_B5ED_402A_B045_1776E04BA324__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Listing.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Listing form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class Listing : public CFormView
{
protected:
	Listing();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(Listing)

// Form Data
public:
	//{{AFX_DATA(Listing)
	enum { IDD = IDD_LISTING_FORM };
	CListCtrl	m_List;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Listing)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~Listing();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(Listing)

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTING_H__966C71E7_B5ED_402A_B045_1776E04BA324__INCLUDED_)
