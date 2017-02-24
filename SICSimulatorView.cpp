// SICSimulatorView.cpp : implementation of the CSICSimulatorView class
//

#include "stdafx.h"
#include "SICSimulator.h"
#include "SICSimulatorDoc.h"
#include "SICSimulatorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSICSimulatorView

IMPLEMENT_DYNCREATE(CSICSimulatorView, CEditView)

BEGIN_MESSAGE_MAP(CSICSimulatorView, CEditView)
	//{{AFX_MSG_MAP(CSICSimulatorView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSICSimulatorView construction/destruction

CSICSimulatorView::CSICSimulatorView()
{
	// TODO: add construction code here

}

CSICSimulatorView::~CSICSimulatorView()
{
}

BOOL CSICSimulatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CSICSimulatorView drawing

void CSICSimulatorView::OnDraw(CDC* pDC)
{
	CSICSimulatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSICSimulatorView printing

BOOL CSICSimulatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CSICSimulatorView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CSICSimulatorView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CSICSimulatorView diagnostics

#ifdef _DEBUG
void CSICSimulatorView::AssertValid() const
{
	CEditView::AssertValid();
}

void CSICSimulatorView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CSICSimulatorDoc* CSICSimulatorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSICSimulatorDoc)));
	return (CSICSimulatorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSICSimulatorView message handlers
