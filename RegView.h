#if !defined(AFX_REGVIEW_H__0A2DBE30_AD43_45A7_A361_5F2BE9F36FE6__INCLUDED_)
#define AFX_REGVIEW_H__0A2DBE30_AD43_45A7_A361_5F2BE9F36FE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RegView view

class RegView : public CView
{
protected:
	RegView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(RegView)

// Attributes
public:
	CBitmap *A_back  ;
	CBitmap *X_back  ;
	CBitmap *L_back  ;
	CBitmap *PC_back ;
	CBitmap *SW_back ;
	CBitmap *T       ;
	CBitmap *F       ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RegView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~RegView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(RegView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGVIEW_H__0A2DBE30_AD43_45A7_A361_5F2BE9F36FE6__INCLUDED_)
