#if !defined(AFX_MEMVIEW2_H__8365AE35_1488_42D2_AFE6_3162AD8FE6A3__INCLUDED_)
#define AFX_MEMVIEW2_H__8365AE35_1488_42D2_AFE6_3162AD8FE6A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MemView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MemView2 view

class MemView : public CScrollView
{
protected:
	MemView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(MemView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MemView2)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~MemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(MemView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMVIEW2_H__8365AE35_1488_42D2_AFE6_3162AD8FE6A3__INCLUDED_)
