// Symtab.cpp : implementation file
//

#include "stdafx.h"
#include "SICSimulator.h"
#include "Symtab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Symtab

IMPLEMENT_DYNCREATE(Symtab, CFormView)

Symtab::Symtab()
	: CFormView(Symtab::IDD)
{
	//{{AFX_DATA_INIT(Symtab)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

Symtab::~Symtab()
{
}

void Symtab::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Symtab)
	DDX_Control(pDX, IDC_LIST1, m_symtab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Symtab, CFormView)
	//{{AFX_MSG_MAP(Symtab)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Symtab diagnostics

#ifdef _DEBUG
void Symtab::AssertValid() const
{
	CFormView::AssertValid();
}

void Symtab::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Symtab message handlers

void Symtab::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	m_symtab.DeleteAllItems() ;

	m_symtab.DeleteColumn(1) ;
	m_symtab.DeleteColumn(0) ;

	m_symtab.InsertColumn(0,"LABLE Name" , LVCFMT_LEFT , 100 , 0 ) ;
	m_symtab.InsertColumn(1,"LABLE Address" , LVCFMT_LEFT , 120 , 0 ) ;

}
