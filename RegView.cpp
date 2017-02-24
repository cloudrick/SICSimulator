// RegView.cpp : implementation file
//

#include "stdafx.h"
#include "SICSimulator.h"
#include "SICSimulatorDoc.h"
#include "SICSimulatorView.h"
#include "RegView.h"
#include "MainFrm.h"

#include "stringex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RegView

IMPLEMENT_DYNCREATE(RegView, CView)

RegView::RegView()
{
	A_back = new CBitmap  ;
	X_back = new CBitmap  ;
	L_back = new CBitmap  ;
	PC_back = new CBitmap ;
	SW_back = new CBitmap ;
	T = new CBitmap ;
	F = new CBitmap ;


	A_back->m_hObject = (HBITMAP)::LoadImage(NULL,"A_back.bmp",IMAGE_BITMAP,
						400,30,LR_LOADFROMFILE) ;
	X_back->m_hObject = (HBITMAP)::LoadImage(NULL,"X_back.bmp",IMAGE_BITMAP,
						400,30,LR_LOADFROMFILE) ;
	L_back->m_hObject = (HBITMAP)::LoadImage(NULL,"L_back.bmp",IMAGE_BITMAP,
						400,30,LR_LOADFROMFILE) ;
	PC_back->m_hObject = (HBITMAP)::LoadImage(NULL,"PC_back.bmp",IMAGE_BITMAP,
						400,30,LR_LOADFROMFILE) ;
	SW_back->m_hObject = (HBITMAP)::LoadImage(NULL,"SW_back.bmp",IMAGE_BITMAP,
						400,30,LR_LOADFROMFILE) ;
	T->m_hObject = (HBITMAP)::LoadImage(NULL,"1_reg.bmp",IMAGE_BITMAP,
						10,10,LR_LOADFROMFILE) ;
	F->m_hObject = (HBITMAP)::LoadImage(NULL,"0_reg.bmp",IMAGE_BITMAP,
						10,10,LR_LOADFROMFILE) ;

}

RegView::~RegView()
{
	delete A_back  ;
	delete X_back  ;
	delete L_back  ;
	delete PC_back ;
	delete SW_back ;
	delete T       ;
	delete F       ;
}


BEGIN_MESSAGE_MAP(RegView, CView)
	//{{AFX_MSG_MAP(RegView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RegView drawing

void RegView::OnDraw(CDC* pDC)
{
	// TODO: add draw code here

	CDC *mdc = new CDC ;
	mdc->CreateCompatibleDC(pDC) ;
	
	mdc->SelectObject(A_back) ;
	pDC->BitBlt(0,0,400,30,mdc,0,0,SRCCOPY) ;

	mdc->SelectObject(X_back) ;
	pDC->BitBlt(0,30,400,30,mdc,0,0,SRCCOPY) ;

	mdc->SelectObject(L_back) ;
	pDC->BitBlt(0,60,400,30,mdc,0,0,SRCCOPY) ;

	mdc->SelectObject(PC_back) ;
	pDC->BitBlt(0,90,400,30,mdc,0,0,SRCCOPY) ;

	mdc->SelectObject(SW_back) ;
	pDC->BitBlt(0,120,400,30,mdc,0,0,SRCCOPY) ;

	CMainFrame *MainFrame = (CMainFrame*)this->GetParent()->GetParent() ;
	CSICSimulatorView *view = (CSICSimulatorView*)MainFrame->m_wndSplitter.GetPane(0,0) ;
	CSICSimulatorDoc *pDoc = view->GetDocument() ;

	int reg[5] ;

	reg[0] = pDoc->A ;
	reg[1] = pDoc->X ;
	reg[2] = pDoc->L ;
	reg[3] = pDoc->PC;
	reg[4] = pDoc->SW;

	for( int i=0 ; i<5 ; i++)
	{
		int tmp = reg[i] ;
		for( int j=0 ; j<24; j++)
		{
			if( reg[i]%2 == 1 )
			{
				mdc->SelectObject(T) ;
			}
			else
			{
				mdc->SelectObject(F) ;
			}
			pDC->BitBlt(390-50-(j*13),i*30+15,10,10,mdc,0,0,SRCCOPY) ;
			reg[i] /= 2 ;
		}
		pDC->TextOut(410,5+i*30, ("0x" + FillChar(IntToHexString(tmp),'0',6,0)).c_str() ) ;

	}
	delete mdc ;
}

/////////////////////////////////////////////////////////////////////////////
// RegView diagnostics

#ifdef _DEBUG
void RegView::AssertValid() const
{
	CView::AssertValid();
}

void RegView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// RegView message handlers
