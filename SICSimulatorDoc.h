// SICSimulatorDoc.h : interface of the CSICSimulatorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SICSIMULATORDOC_H__9015ADBC_6088_4521_9762_D94FD01A4FCC__INCLUDED_)
#define AFX_SICSIMULATORDOC_H__9015ADBC_6088_4521_9762_D94FD01A4FCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

using namespace std ;

class SIC_IS
{
public:
	SIC_IS( string m_M             ,
		      unsigned long int m_Op ,
			  string m_N)
			 : Mnemonic(m_M),Opcode(m_Op),Note(m_N)  {}

	SIC_IS(){}
	string Mnemonic          ;
	unsigned long int Opcode ;
	string Note		         ;
} ;

struct SIC_SYMTAB
{
	string SymName ;
	int line ;
	unsigned long int data ;
} ;


class CSICSimulatorDoc : public CDocument
{
protected: // create from serialization only
	CSICSimulatorDoc();
	DECLARE_DYNCREATE(CSICSimulatorDoc)

// Attributes
public:

	int  MAX_LINE_OF_FILE ; 
	SIC_IS ISA[26] ;

	SIC_SYMTAB symtab[100] ;
	int SYMTAB_LENGTH   ;

	unsigned long int START_ADDRESS         ;
	unsigned long int PROGRAM_LENGH         ;
	unsigned long int *LOC                  ;
	string            *OBJCodeALL			;

	int A  ;
	int X  ;
	int L  ;
	unsigned long int PC ;
	int SW ;

	int Memory[32768] ;

	string *source    ;
	int source_length ;

// Operations
public:

	int GetTotalBytes(string str) ;

	int SearchFromSymTab(string lab) ;
	bool InsertToSymTab(string lab,unsigned long int loc) ;
	int SearchFromISA(string op) ;

	string GetConstString(string str) ;

	void WriteToMemory(int,int,long int) ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSICSimulatorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSICSimulatorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSICSimulatorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SICSIMULATORDOC_H__9015ADBC_6088_4521_9762_D94FD01A4FCC__INCLUDED_)
