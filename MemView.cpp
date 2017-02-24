// MemView.cpp : implementation file
//

#include "stdafx.h"
#include "SICSimulator.h"
#include "MainFrm.h"
#include "SICSimulatorDoc.h"
#include "SICSimulatorView.h"
#include "MemView.h"

#include "StringEx.h"

#include<string>

using namespace std ;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MemView

IMPLEMENT_DYNCREATE(MemView, CScrollView)

MemView::MemView()
{
}

MemView::~MemView()
{
}


BEGIN_MESSAGE_MAP(MemView, CScrollView)
	//{{AFX_MSG_MAP(MemView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MemView drawing

void MemView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 900  ;
	sizeTotal.cy = 15420 ;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void MemView::OnDraw(CDC* pDC)
{
	CMainFrame *MainFrame = (CMainFrame*)this->GetParent()->GetParent() ;
	CSICSimulatorView *view = (CSICSimulatorView*)MainFrame->m_wndSplitter.GetPane(0,0) ;
	CSICSimulatorDoc *pDoc = view->GetDocument() ;

	pDC->SetTextColor(0x000000) ;

	pDC->TextOut(10,10,"Memory") ;
	pDC->TextOut(10,30,"Address") ;
	pDC->TextOut(200,30,"Contents") ;
	pDC->TextOut(600,30,"Contents") ;


	pDC->MoveTo(10,50) ;
	pDC->LineTo(800,50) ;

	pDC->MoveTo(70,10) ;
	pDC->LineTo(70,15420) ;

	pDC->MoveTo(410,10) ;
	pDC->LineTo(410,15420) ;

	pDC->MoveTo(470,10) ;
	pDC->LineTo(470,15420) ;

	int i,j ;
	string tmp ;

	for( i=0 ; i<1024 ; i++ )
	{
		tmp = FillChar(IntToHexString(i*16),'0',4,false) ;
		pDC->TextOut(30,60+(i*15),CString(tmp.c_str())) ;

		for( j=0 ; j<16 ; j++)
		{
			if(pDoc->Memory[i*16+j]>=0)
				tmp = FillChar(IntToHexString(pDoc->Memory[i*16+j]),'0',2,false) ;
			else if(pDoc->Memory[i*16+j]==-1)
				tmp = "- -" ;
			else
				tmp = "xx" ;
			pDC->TextOut(80+(j*20),60+(i*15),CString(tmp.c_str())) ;
		}
	}

	for( i=1024 ; i<2048 ; i++ )
	{
		tmp = FillChar(IntToHexString(i*16),'0',4,false) ;
		pDC->TextOut(430,60+((i-1024)*15),CString(tmp.c_str())) ;

		for( j=0 ; j<16 ; j++)
		{
			if( pDoc->Memory[i*16+j] >= 0 )
				tmp = FillChar(IntToHexString(pDoc->Memory[i*16+j]),'0',2,false) ;
			else if(pDoc->Memory[i*16+j]==-1)
				tmp = "- -" ;
			else
				tmp = "x x" ;
			pDC->TextOut(480+(j*20),60+(((i-1024)*15)),CString(tmp.c_str())) ;
		}
	}

}

/////////////////////////////////////////////////////////////////////////////
// MemView diagnostics

#ifdef _DEBUG
void MemView::AssertValid() const
{
	CScrollView::AssertValid();
}

void MemView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MemView message handlers
