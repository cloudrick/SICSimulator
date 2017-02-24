// SICSimulatorDoc.cpp : implementation of the CSICSimulatorDoc class
//

#include "stdafx.h"
#include "SICSimulator.h"
#include "SICSimulatorDoc.h"

#include "stringex.h"

#include <fstream>
#include <string>

using namespace std ;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSICSimulatorDoc

IMPLEMENT_DYNCREATE(CSICSimulatorDoc, CDocument)

BEGIN_MESSAGE_MAP(CSICSimulatorDoc, CDocument)
	//{{AFX_MSG_MAP(CSICSimulatorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSICSimulatorDoc construction/destruction

CSICSimulatorDoc::CSICSimulatorDoc()
{
	// TODO: add one-time construction code here

	MAX_LINE_OF_FILE = 100 ; 

	LOC = new unsigned long int [MAX_LINE_OF_FILE] ;
	OBJCodeALL = new string[MAX_LINE_OF_FILE]	   ;

	
	ISA[0] = SIC_IS( "ADD"    , 0x18 , ""    ) ;
	ISA[1] = SIC_IS( "AND"    , 0x40 , ""    ) ;
	ISA[2] = SIC_IS( "COMP"   , 0x28 , "C"   ) ;
	ISA[3] = SIC_IS( "DIV"    , 0x24 , ""    ) ;
	ISA[4] = SIC_IS( "J"      , 0x3C , ""    ) ;
	ISA[5] = SIC_IS( "JEQ"    , 0x30 , ""    ) ;
	ISA[6] = SIC_IS( "JGT"    , 0x34 , ""    ) ;
	ISA[7] = SIC_IS( "JLT"    , 0x38 , ""    ) ;
	ISA[8] = SIC_IS( "JSUB"   , 0x48 , ""    ) ;
	ISA[9] = SIC_IS( "LDA"    , 0x00 , ""    ) ;
	ISA[10] = SIC_IS( "LDCH"   , 0x50 , ""    ) ;
	ISA[11] = SIC_IS( "LDL"    , 0x08 , ""    ) ;
	ISA[12] = SIC_IS( "LDX"    , 0x04 , ""    ) ;
	ISA[13] = SIC_IS( "MUL"    , 0x20 , ""    ) ;
	ISA[14] = SIC_IS( "OR"     , 0x44 , ""    ) ;
	ISA[15] = SIC_IS( "RD"     , 0xD8 , "P"   ) ;
	ISA[16] = SIC_IS( "RSUB"   , 0x4C , ""    ) ;
	ISA[17] = SIC_IS( "STA"    , 0x0C , ""    ) ;
	ISA[18] = SIC_IS( "STCH"   , 0x54 , ""    ) ;
	ISA[19] = SIC_IS( "STL"    , 0x14 , ""    ) ;
	ISA[20] = SIC_IS( "STSW"   , 0xE8 , "P"   ) ;
	ISA[21] = SIC_IS( "STX"    , 0x10 , ""    ) ;
	ISA[22] = SIC_IS( "SUB"    , 0x1C , ""    ) ;
	ISA[23] = SIC_IS( "TD"     , 0xE0 , "PC"  ) ;
	ISA[24] = SIC_IS( "TIX"    , 0x2C , "C"   ) ;
	ISA[25] = SIC_IS( "WD"     , 0xDC , "P"   ) ; 

	A = X = L = PC = SW = 0x00000000 ;
	SYMTAB_LENGTH = 0 ;

	for( int i=0 ; i<32767 ; i++)
		Memory[i] = 0 ;

	source_length = 0 ;
	source = new string[MAX_LINE_OF_FILE] ;

}

CSICSimulatorDoc::~CSICSimulatorDoc()
{
	delete [] LOC ;
	delete [] OBJCodeALL ;
	delete [] source ;
}

BOOL CSICSimulatorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	SYMTAB_LENGTH = 0 ;
	source_length = 0 ;

	for( int i=0 ; i<32767 ; i++)
		Memory[i] = 0 ;


	return TRUE;
}

BOOL CSICSimulatorDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here

	fstream in ;
	in.open( lpszPathName , ios::in ) ;

	SYMTAB_LENGTH = 0 ;
	source_length = 0 ;

	while( true )
	{
		if( in.eof() )
			break ;
		char tmp[100] ;
		in.getline(tmp,100) ;
		source[source_length++] = tmp ;
	}
	in.close() ;
	return TRUE;
}

BOOL CSICSimulatorDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (!CDocument::OnSaveDocument(lpszPathName))
		return FALSE;

	fstream in ;
	in.open( lpszPathName , ios::in ) ;

	SYMTAB_LENGTH = 0 ;
	source_length = 0 ;

	while( true )
	{
		if( in.eof() )
			break ;
		char tmp[100] ;
		in.getline(tmp,100) ;
		source[source_length++] = tmp ;
	}
	in.close() ;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSICSimulatorDoc serialization

void CSICSimulatorDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CSICSimulatorDoc diagnostics

#ifdef _DEBUG
void CSICSimulatorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSICSimulatorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSICSimulatorDoc commands

int CSICSimulatorDoc::GetTotalBytes(string str)
{
	int tmp = 0 ;
	if( str[0] == 'X' )
	{
		tmp = str.length() - 3 ;
		if( tmp%2 == 1)
			tmp = (tmp + 1)/2 ;
		else
			tmp /= 2 ;
		return tmp ;
	}
	else if( str[0] == 'C' )
	{
		return str.length() - 3 ;
	}

	return -1 ;
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

int CSICSimulatorDoc::SearchFromSymTab(string lab)
{
	for( int i=0 ; i<SYMTAB_LENGTH ; i++)
	{
		if( symtab[i].SymName == lab )
			return i ;
	}
	return -1 ;
}

bool CSICSimulatorDoc::InsertToSymTab(string lab,unsigned long int loc)
{
	if( SearchFromSymTab(lab)>=0 )
		return false ;

	symtab[SYMTAB_LENGTH].SymName = lab ;
	symtab[SYMTAB_LENGTH].data    = loc ;
	SYMTAB_LENGTH++ ;

	return true ;
}

int CSICSimulatorDoc::SearchFromISA(string op)
{
	for( int i=0 ; i<26 ; i++)
	{
		if( ISA[i].Mnemonic == op )
			return i ;
	}
	return -1 ;
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

string CSICSimulatorDoc::GetConstString(string str)
{
	string r ;
	long int v ;

	if( str[0] == 'C' )
	{
		str = string(str.begin()+2,str.end()-1) ;
		
		for( int i=0 ; i<str.length() ; i++)
		{
			r = r + IntToHexString(str[i]) ;
		}
	}
	else if( str[0] == 'X' )
	{
		str = string(str.begin()+2,str.end()-1) ;
		r = str ;
	}
	else if( DecStringToInt(str,v) == true )
	{
		r = IntToHexString(v) ;
	}

	return r ;
}

void CSICSimulatorDoc::WriteToMemory(int start,int length,long int data)
{
	while( length )
	{
		if( start+length-1 < 32768 )
		{
			Memory[start+length-1] = data%256 ;
			data /= 256 ;
		}
		length-- ;
	}
}


