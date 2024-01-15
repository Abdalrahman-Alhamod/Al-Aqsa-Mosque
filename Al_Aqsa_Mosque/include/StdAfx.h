// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#if !defined(AFX_STDAFX_H__D7629C63_B0FF_11D4_A3B0_0050DA731472__INCLUDED_)
#define AFX_STDAFX_H__D7629C63_B0FF_11D4_A3B0_0050DA731472__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

//#include <afxwin.h>        // MFC core and standard components
//#include <afxext.h>        // MFC extensions
//#include <afxtempl.h>		// MFC collection classes 
//
//#ifndef _AFX_NO_AFXCMN_SUPPORT
//#include <afxcmn.h>			// MFC support for Windows Common Controls
//#endif // _AFX_NO_AFXCMN_SUPPORT


//// Include OpenGL header files
//#include <gl\gl.h>			// opengl32.lib 
#include <gl\glaux.h>		// glaux.lib 
#include <gl\glu.h>			// glu32.lib 
#include <mmsystem.h>		// winmm.lib (used for timeGetTime function)


// Generate auto linkage for OpenGL libraries
#pragma comment(lib, "OPENGL32.LIB")
#pragma comment(lib, "GLAUX.LIB")
#pragma comment(lib, "GLU32.LIB")

// Generate auto linkage for Direct Sound libraries
#pragma comment(lib, "DSOUND.LIB")

#pragma comment(lib, "WINMM.LIB")
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__D7629C63_B0FF_11D4_A3B0_0050DA731472__INCLUDED_)
