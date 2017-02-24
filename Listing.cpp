// Listing.cpp : implementation file
//

#include "stdafx.h"
#include "SICSimulator.h"
#include "Listing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Listing

IMPLEMENT_DYNCREATE(Listing, CFormView)

Listing::Listing()
	: CFormView(Listing::IDD)
{
	//{{AFX_DATA_INIT(Listing)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

Listing::~Listing()
{

}

void Listing::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Listing)
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Listing, CFormView)
	//{{AFX_MSG_MAP(Listing)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Listing diagnostics

#ifdef _DEBUG
void Listing::AssertValid() const
{
	CFormView::AssertValid();
}

void Listing::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Listing message handlers

void Listing::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class

	m_List.DeleteAllItems() ;
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT ) ;

	m_List.DeleteColumn(5) ;
	m_List.DeleteColumn(4) ;
	m_List.DeleteColumn(3) ;
	m_List.DeleteColumn(2) ;
	m_List.DeleteColumn(1) ;
	m_List.DeleteColumn(0) ;

	m_List.InsertColumn(0,_T("Line") ,LVCFMT_LEFT,50,0) ;
	m_List.InsertColumn(1,_T("Loc") ,LVCFMT_LEFT,50,0) ;
	m_List.InsertColumn(2,_T("Lable") ,LVCFMT_LEFT,70,0) ;
	m_List.InsertColumn(3,_T("Opcode") ,LVCFMT_LEFT,70,0) ;
	m_List.InsertColumn(4,_T("Operand") ,LVCFMT_LEFT,70,0) ;
	m_List.InsertColumn(5,_T("Object Code") ,LVCFMT_LEFT,70,0) ;
}
