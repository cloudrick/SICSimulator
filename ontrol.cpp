// ontrol.cpp : implementation file
//

#include "stdafx.h"
#include "SICSimulator.h"
#include "SICSimulatorDoc.h"
#include "SICSimulatorView.h"
#include "ontrol.h"
#include "Listing.h"
#include "MemView.h"
#include "MainFrm.h"
#include "Symtab.h"

#include "stringex.h"

#include <string>

using namespace std ;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Control

IMPLEMENT_DYNCREATE(Control, CFormView)

Control::Control()
	: CFormView(Control::IDD)
{
	//{{AFX_DATA_INIT(Control)
	m_step = 0.0f;
	m_runstep = 0.0f;
	m_in = _T("");
	m_out = _T("");
	//}}AFX_DATA_INIT
	pass_step = 0 ;
	started = false ;
	run_started = false ;
	run_step = 0 ;

	JEQ = false ;
	JGT = false ;
	JLT = false ;

	rsub_line = 0 ;
	rsub_pc = 0 ;
}

Control::~Control()
{
}

void Control::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Control)
	DDX_Control(pDX, IDC_BUTTON5, m_b5);
	DDX_Control(pDX, IDC_BUTTON4, m_b4);
	DDX_Control(pDX, IDC_BUTTON2, m_b2);
	DDX_Control(pDX, IDC_BUTTON1, m_b1);
	DDX_Text(pDX, IDC_EDIT1, m_step);
	DDX_Text(pDX, IDC_EDIT2, m_runstep);
	DDX_Text(pDX, IDC_EDIT3, m_in);
	DDX_Text(pDX, IDC_EDIT4, m_out);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Control, CFormView)
	//{{AFX_MSG_MAP(Control)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, OnStop)
	ON_BN_CLICKED(IDC_BUTTON1, OnGo)
	ON_BN_CLICKED(IDC_BUTTON2, OnStepGo)
	ON_BN_CLICKED(IDC_BUTTON4, OnRun)
	ON_BN_CLICKED(IDC_BUTTON6, OnRunStop)
	ON_BN_CLICKED(IDC_BUTTON5, OnStepRun)
	ON_BN_CLICKED(IDC_BUTTON7, OnClearMemory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Control diagnostics

#ifdef _DEBUG
void Control::AssertValid() const
{
	CFormView::AssertValid();
}

void Control::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void SourceCodeParse(string str,string& lable,string& op,string& addr)
{
	char *p1,*p2,*p3 ;

	string tmp = string(str.begin(),str.end()) ;

	p1 = strtok((char *)str.data()," \t") ;
	p2    = strtok(NULL," \t") ;
	p3  = strtok(NULL," \t") ;

	if( p3 == NULL )
	{
		lable = "" ;
		if( p2 == NULL )
			addr = "" ;
		else
			addr = p2 ;
		if( p1 == NULL )
			op = "" ;
		else
			op = p1 ;
	}
	else
	{
		lable = p1 ;
		op = p2 ;
		addr = p3 ;
	}
	ToUP(op) ;
	str = tmp ;
}

void Control::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if( nIDEvent == 1 )
		OnStepGo() ;
	if( nIDEvent == 2 )
		OnStepRun() ;
	CFormView::OnTimer(nIDEvent);
}

void Control::OnStop() 
{
	// TODO: Add your control notification handler code here
	m_b1.EnableWindow(true) ;
	m_b2.EnableWindow(true) ;
	pass_step = 0 ;
	started = false ;
	KillTimer(1) ;
}

void Control::OnGo() 
{
	// TODO: Add your control notification handler code here
	m_b2.EnableWindow(false) ;
	UpdateData(true) ;
	if( m_step < 0.2 )
		m_step = (float)0.2 ;
	UpdateData(false) ;
	SetTimer(1,m_step*1000,NULL) ;
}

void Control::OnStepGo() 
{
	// TODO: Add your control notification handler code here
	m_b1.EnableWindow(false) ;

	CSICSimulatorDoc *pDoc = (CSICSimulatorDoc*)GetDocument() ;

	string lable,opcode,operand ;

	CMainFrame *main = (CMainFrame*)this->GetParent()->GetParent();

	Listing *listing = (Listing*)main->m_wndSplitter.GetPane(0,1) ;
	Symtab *sym = (Symtab*)main->m_wndSplitter.GetPane(1,0) ;

	CListCtrl *symtab = &(sym->m_symtab) ;
	CListCtrl *list = &(listing->m_List) ;

	pDoc->SaveModified() ;

	if( !started )
	{
		list->DeleteAllItems() ;
		symtab->DeleteAllItems() ;
		loc = 0 ;
		ml_length = 0 ;
		pDoc->START_ADDRESS = loc ;
		for( int i=0 ; i<pDoc->source_length ; i++)
		{
			pDoc->LOC[i] = 0 ;
		}
		for( int j=0 ; j<32768 ; j++)
			pDoc->Memory[j] = 0 ;

		pDoc->SYMTAB_LENGTH = 0 ;
	}

	if( pass_step >= pDoc->source_length )
	{
		OnStop() ;
		AfxMessageBox("Pass Done1") ;
		return ;
	}

	SourceCodeParse( pDoc->source[pass_step],lable,opcode,operand) ;

	list->InsertItem(pass_step, IntToDecString(pass_step+1).c_str() ) ;

	if( lable=="" && opcode=="" && operand=="" )
	{
		pass_step++ ;
		return ;
	}

	if( lable[0]=='.' || opcode[0]=='.' || operand[0]=='.' )
	{
		pass_step++ ;
		return ;
	}

	if( opcode == "START")
	{
		HexStringToInt(operand,(unsigned long)loc) ;
		pDoc->START_ADDRESS = loc ;
		pDoc->LOC[pass_step]= loc ;
		started = true ;

		list->SetItemText(pass_step,1, FillChar(IntToHexString(pDoc->LOC[pass_step]),'0',4,0).c_str()) ;
		list->SetItemText(pass_step,2, lable.c_str()) ;
		list->SetItemText(pass_step,3, opcode.c_str()) ;
		list->SetItemText(pass_step,4, operand.c_str()) ;
		list->SendMessage(WM_VSCROLL,SB_LINEDOWN) ;
		pass_step++ ;
		return ;
	}

	if( !started )
	{
		loc = 0 ;
		pDoc->START_ADDRESS = 0 ;
		pDoc->LOC[pass_step]= 0 ;
		started = true ;
	}

	pDoc->LOC[pass_step] = loc ;

	list->SetItemText(pass_step,1, FillChar(IntToHexString(loc),'0',4,0).c_str() ) ;
	list->SetItemState(pass_step , LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED ) ;
	list->EnsureVisible(pass_step,false) ;
	list->SetFocus() ;

	list->SetItemText(pass_step,2, lable.c_str()) ;
	list->SetItemText(pass_step,3, opcode.c_str()) ;
	list->SetItemText(pass_step,4, operand.c_str()) ;
	list->SendMessage(WM_VSCROLL,SB_LINEDOWN) ;

	if( lable != "" )
	{
		if( pDoc->SearchFromSymTab(lable) < 0 )
		{
			pDoc->InsertToSymTab(lable,loc) ;

			pDoc->symtab[pDoc->SYMTAB_LENGTH-1].line = pass_step ;
			
			symtab->InsertItem( pDoc->SYMTAB_LENGTH-1 , lable.c_str() ) ;
			symtab->SetItemText(pDoc->SYMTAB_LENGTH-1 , 1 , 
				FillChar(IntToHexString(loc),'0',4,0).c_str() ) ;

			for( int j=0 ; j< ml_length ; j++)
			{
				if( misslable[j].Name == lable )
				{
					if(misslable[j].indexed)
					{
						pDoc->WriteToMemory(misslable[j].Addr,2,loc+32768) ;
						pDoc->OBJCodeALL[misslable[j].line] += FillChar(IntToHexString(loc+32768),'0',4,0) ;
					}
					else
					{
						pDoc->WriteToMemory(misslable[j].Addr,2,loc) ;
						pDoc->OBJCodeALL[misslable[j].line] += FillChar(IntToHexString(loc),'0',4,0) ;
					}
					pDoc->UpdateAllViews(this) ;
				}
			}

		}
		else
		{
			string error = "Redefine LABLE " + lable ;
			AfxMessageBox(error.c_str()) ;
			OnStop() ;
		}
	}

	int iFromISA = pDoc->SearchFromISA( opcode ) ;

	if( iFromISA >= 0 )
	{
		bool indexed = false ;

		if( operand.find(",X") != string::npos )
		{
			indexed = true ;
			operand = string( operand.begin() , operand.end()-2 ) ;
		}

		int iFromSymtab = pDoc->SearchFromSymTab(operand) ;
		
		pDoc->WriteToMemory(loc,1,pDoc->ISA[iFromISA].Opcode) ;
		pDoc->OBJCodeALL[pass_step] = FillChar(IntToHexString(pDoc->ISA[iFromISA].Opcode),'0',2,0) ;

		if( iFromSymtab >= 0 )
		{
			if( indexed )
			{
				pDoc->WriteToMemory(loc+1,2,pDoc->symtab[iFromSymtab].data+32768) ;
				pDoc->OBJCodeALL[pass_step] += FillChar(IntToHexString(pDoc->symtab[iFromSymtab].data+32768),'0',4,0) ;

			}
			else
			{
				pDoc->WriteToMemory(loc+1,2,pDoc->symtab[iFromSymtab].data) ;
				pDoc->OBJCodeALL[pass_step] += FillChar(IntToHexString(pDoc->symtab[iFromSymtab].data),'0',4,0) ;

			}
			pDoc->UpdateAllViews(this) ;
		}
		else
		{
			misslable[ml_length].Addr = loc+1 ;
			misslable[ml_length].line = pass_step ;
			misslable[ml_length].Name = operand ;
			misslable[ml_length++].indexed = indexed ;

			if( operand == "" )
			{
				pDoc->WriteToMemory(loc+1,2,0) ;
				pDoc->OBJCodeALL[pass_step] += "0000" ;
			}
			else
			{
				pDoc->WriteToMemory(loc+1,1,-1) ;
				pDoc->WriteToMemory(loc+2,1,-1) ;
			}
			pDoc->UpdateAllViews(this) ;
		}

		loc += 3 ;
	}
	else if( opcode == "WORD" )
	{
		long int v ;
		DecStringToInt(operand,v) ;
		pDoc->WriteToMemory(loc,3,v) ;
		pDoc->OBJCodeALL[pass_step] = FillChar(IntToHexString(v),'0',6,0) ;
		loc += 3 ;
	}
	else if( opcode == "RESW" )
	{
		long int tmp ;
		DecStringToInt(operand,tmp) ;
		for( int i=0 ; i<3*tmp ; i++)
			pDoc->WriteToMemory(loc+i,1,-2) ;

		loc += 3*tmp ;
	}
	else if( opcode == "RESB" )
	{
		long int tmp ;
		DecStringToInt(operand,tmp) ;
		for( int i=0 ; i<tmp ; i++)
			pDoc->WriteToMemory(loc+i,1,-2) ;
		loc += tmp ;
	}
	else if( opcode == "BYTE" )
	{
		string tmp = pDoc->GetConstString(operand) ;

		for( int i=0 ; i<tmp.length() ; i+=2)
		{
			if(i+1<tmp.length())
			{
				pDoc->WriteToMemory(loc+(i/2),1,
				 (GetHexValue(tmp[i])*16)+ GetHexValue(tmp[i+1])) ;
			}
			else
			{
				pDoc->WriteToMemory(loc+(i/2),1,
				 (GetHexValue(tmp[i])*16)) ;
			}
		}
		pDoc->OBJCodeALL[pass_step] = tmp ;
		loc += pDoc->GetTotalBytes(operand) ;
	}
	else if( opcode == "END" )
	{
		list->SetItemText(pass_step,2, lable.c_str()) ;
		list->SetItemText(pass_step,3, opcode.c_str()) ;
		list->SetItemText(pass_step,4, operand.c_str()) ;
		list->SendMessage(WM_VSCROLL,SB_LINEDOWN) ;

		for( int i=0 ; i<pDoc->source_length ; i++)
		{
			list->SetItemText(i,5,pDoc->OBJCodeALL[i].c_str()) ;
		}

		OnStop() ;
		AfxMessageBox("Pass Done") ;
		return ;
	}
	else
	{
		string error = "Error OPCODE " + opcode ;
		AfxMessageBox(error.c_str()) ;
		OnStop() ;
	}
	pDoc->UpdateAllViews(this) ;
	pass_step++ ;
}

void Control::OnRun() 
{
	UpdateData(true) ;
	if( m_runstep < 1 )
		m_runstep = (float)1 ;
	UpdateData(false) ;
	SetTimer(2,m_runstep*1000,NULL) ;
}

void Control::OnRunStop() 
{
	// TODO: Add your control notification handler code here
	m_b1.EnableWindow(true) ;
	m_b2.EnableWindow(true) ;
	m_b4.EnableWindow(true) ;
	m_b5.EnableWindow(true) ;
	run_started = false ;
	JEQ = false ;
	JGT = false ;
	JLT = false ;
	KillTimer(2) ;
}

void Control::OnStepRun() 
{
	// TODO: Add your control notification handler code here
	CSICSimulatorDoc *pDoc = (CSICSimulatorDoc*)GetDocument() ;

	CMainFrame *main = (CMainFrame*)this->GetParent()->GetParent();

	Listing *listing = (Listing*)main->m_wndSplitter.GetPane(0,1) ;
	CListCtrl *list = &(listing->m_List) ;

	pDoc->SaveModified() ;

	m_b4.EnableWindow(false) ;

	if( !run_started )
	{

		for ( int i=0 ; i<(pDoc->source_length) ; i++ )
		{
			OnStepGo() ;
		}
		pDoc->A = 0 ;
		pDoc->X = 0 ;
		pDoc->L = 0 ;
		pDoc->PC = pDoc->START_ADDRESS ;
		pDoc->SW = 0 ;
		m_b1.EnableWindow(false) ;
		m_b2.EnableWindow(false) ;
		run_step = 0 ;
		run_started = true ;
	}

	if( run_step >= pDoc->source_length )
	{
		OnRunStop() ;
		AfxMessageBox("Run Done") ;
		return ;
	}

	string lable,opcode,operand ;
	SourceCodeParse( pDoc->source[run_step],lable,opcode,operand) ;

	list->SetItemState(run_step , LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED ) ;
	list->EnsureVisible(run_step,false) ;
	list->SetFocus() ;

	bool indexed = false ;

	if( operand.find(",X") != string::npos )
	{
		indexed = true ;
		operand = string( operand.begin() , operand.end()-2 ) ;
	}

	pDoc->PC = pDoc->LOC[run_step] ;
	pDoc->UpdateAllViews(this) ;

	if( opcode == "START")
	{
		unsigned long int v ;
		HexStringToInt(operand,v) ;
		pDoc->PC = v ;
	}
	else if( opcode == "ADD" )
	{
		int j = pDoc->SearchFromSymTab(operand) ;
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int v = pDoc->Memory[pDoc->symtab[j].data+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+1+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+2+m] ;
		pDoc->A += v ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "AND" )
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		int v = pDoc->Memory[pDoc->symtab[j].data+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+1+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+2+m] ;
		pDoc->A &= v ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "COMP")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		int v = pDoc->Memory[pDoc->symtab[j].data+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+1+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+2+m] ;

		if( pDoc->A == v )
		{
			JEQ = true ;
			JGT = false ;
			JLT = false ;
		}
		else if(pDoc->A >= v)
		{
			JEQ = false ;
			JGT = true ;
			JLT = false ;
		}
		else
		{
			JEQ = false ;
			JGT = false ;
			JLT = true ;
		}
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "DIV")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		int v = pDoc->Memory[pDoc->symtab[j].data+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+1+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+2+m] ;
		pDoc->A /= v ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "J")
	{
		int j = pDoc->SearchFromSymTab(operand) ;
		run_step = pDoc->symtab[j].line	;
		return ;
	}
	else if( opcode == "JEQ")
	{
		if( JEQ )
		{
			int j = pDoc->SearchFromSymTab(operand) ;
			run_step = pDoc->symtab[j].line	;
			return ;
		}
	}
	else if( opcode == "JGT")
	{
		if( JGT )
		{		
			int j = pDoc->SearchFromSymTab(operand) ;
			run_step = pDoc->symtab[j].line	;
			return ;
		}
	}
	else if( opcode == "JLT")
	{
		if( JLT )
		{
			int j = pDoc->SearchFromSymTab(operand) ;
			run_step = pDoc->symtab[j].line	;
			return ;
		}
	}
	else if( opcode == "JSUB")
	{
		rsub_line = run_step  ;
		pDoc->L = pDoc->PC ;
		rsub_pc = pDoc->PC+3 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		run_step = pDoc->symtab[j].line	;
		return ;
	}
	else if( opcode == "LDA")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		int v = pDoc->Memory[pDoc->symtab[j].data+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+1+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+2+m] ;
		pDoc->A = v ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "LDCH")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		int v = pDoc->Memory[pDoc->symtab[j].data+m] ;
		pDoc->L &= 0xffffff00 ;
		pDoc->L += v ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "LDL")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		int v = pDoc->Memory[pDoc->symtab[j].data+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+1+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+2+m] ;
		pDoc->L = v ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "LDX")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		int v = pDoc->Memory[pDoc->symtab[j].data+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+1+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+2+m] ;
		pDoc->X = v ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "MUL")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		int v = pDoc->Memory[pDoc->symtab[j].data+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+1+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+2+m] ;
		pDoc->A *= v ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "OR")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		int v = pDoc->Memory[pDoc->symtab[j].data+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+1+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+2+m] ;
		pDoc->A |= v ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "RD")
	{
		UpdateData(true) ;
		int c = m_in.GetAt(0) ;

		pDoc->A = c ;

		CString tmp ;

		for( int i=1 ; i<m_in.GetLength() ; i++)
			tmp += m_in.GetAt(i) ;

		m_in = tmp ;
		UpdateData(false) ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "RSUB")
	{
		run_step = rsub_line;
	}
	else if( opcode == "STA")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		pDoc->WriteToMemory(pDoc->symtab[j].data+m,3,pDoc->A) ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "STCH")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		pDoc->WriteToMemory(pDoc->symtab[j].data+m,1,pDoc->A) ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "STL")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		pDoc->WriteToMemory(pDoc->symtab[j].data+m,3,pDoc->L) ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "STSW")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		pDoc->WriteToMemory(pDoc->symtab[j].data+m,3,pDoc->SW) ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "STX")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		pDoc->WriteToMemory(pDoc->symtab[j].data+m,3,pDoc->X) ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "SUB")
	{
		int m ;
		if( indexed )
			m = pDoc->X ;
		else
			m = 0 ;
		int j = pDoc->SearchFromSymTab(operand) ;
		int v = pDoc->Memory[pDoc->symtab[j].data+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+1+m] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+2+m] ;
		pDoc->A -= v ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "TD")
	{
		UpdateData(true) ;
		if( m_in == "" )
			JEQ = true ;
		else
			JEQ = false ;
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "TIX")
	{
		pDoc->X += 1 ;

		int j = pDoc->SearchFromSymTab(operand) ;
		int v = pDoc->Memory[pDoc->symtab[j].data] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+1] ;
		v <<= 8 ;
		v += pDoc->Memory[pDoc->symtab[j].data+2] ;

		if( pDoc->X == v )
		{
			JEQ = true ;
			JGT = false ;
			JLT = false ;
		}
		else if(pDoc->X >= v)
		{
			JEQ = false ;
			JGT = true ;
			JLT = false ;
		}
		else
		{
			JEQ = false ;
			JGT = false ;
			JLT = true ;
		}
		pDoc->UpdateAllViews(this) ;
	}
	else if( opcode == "WD")
	{
		m_out += (char)(pDoc->A) ;
		UpdateData(false) ;
		pDoc->UpdateAllViews(this) ;
	}

	pDoc->UpdateAllViews(this) ;
	run_step++ ;
}

void Control::OnClearMemory() 
{
	// TODO: Add your control notification handler code here

	CSICSimulatorDoc *pDoc = (CSICSimulatorDoc*)GetDocument() ;

	for( int i=0 ; i<32768 ; i++)
		pDoc->Memory[i] = 0 ;

	pDoc->UpdateAllViews(this) ;
}
