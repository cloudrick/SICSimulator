// SICSimulatorView.h : interface of the CSICSimulatorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SICSIMULATORVIEW_H__4C11CD22_D422_42CE_B1CD_39F849F67178__INCLUDED_)
#define AFX_SICSIMULATORVIEW_H__4C11CD22_D422_42CE_B1CD_39F849F67178__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSICSimulatorView : public CEditView
{
protected: // create from serialization only
	CSICSimulatorView();
	DECLARE_DYNCREATE(CSICSimulatorView)

// Attributes
public:
	CSICSimulatorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSICSimulatorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSICSimulatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSICSimulatorView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SICSimulatorView.cpp
inline CSICSimulatorDoc* CSICSimulatorView::GetDocument()
   { return (CSICSimulatorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SICSIMULATORVIEW_H__4C11CD22_D422_42CE_B1CD_39F849F67178__INCLUDED_)
