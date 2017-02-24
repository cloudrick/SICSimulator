// SICSimulator.h : main header file for the SICSIMULATOR application
//

#if !defined(AFX_SICSIMULATOR_H__BB36E726_2AB7_4D24_8194_84B3674AF193__INCLUDED_)
#define AFX_SICSIMULATOR_H__BB36E726_2AB7_4D24_8194_84B3674AF193__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSICSimulatorApp:
// See SICSimulator.cpp for the implementation of this class
//

class CSICSimulatorApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CSICSimulatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSICSimulatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSICSimulatorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SICSIMULATOR_H__BB36E726_2AB7_4D24_8194_84B3674AF193__INCLUDED_)
