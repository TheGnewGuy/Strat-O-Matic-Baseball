// FormB.cpp: implementation of the FormB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Baseball.h"
#include "dialogs.h"
#include "BaseballDoc.h"
#include "FormB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FormB::FormB()
{

}

FormB::~FormB()
{

}

void FormB::OnDraw(CDC * pDC, CBaseballDoc * pDoc)
{
	// Based on 8000 x 10,500 = .001
	// Size for drawing is 437,0 x 10490,-7990
	// 7/16 = 43.75
	// 1/16 = 6.25
	// 3/8  = 3.75
	#define xStart		350
	#define yStart		750
//	#define xEnd		7500
	#define yEnd		10490
	#define xInc		350
	#define yInc		250
	#define cols		17
	#define rows		38

	int i,j,xEnd;
	CFont* origFont;
	CFont myFont;
	LOGFONT lf;
	//char  szFontName[LF_FACESIZE] = _T("Times New Roman");
	
	memset(&lf, 0, sizeof(LOGFONT));
//	lstrcpy((LPWSTR)&lf.lfFaceName, _T("Times New Roman"));
	lstrcpy(lf.lfFaceName, _T("Times New Roman"));
	lf.lfHeight = -100;
	VERIFY(myFont.CreateFontIndirect(&lf));
	origFont = pDC->SelectObject(&myFont);
//
//	pDC->TextOut(100,-100,"FormB",5);

	xEnd = xStart+1500+(cols*xInc);
	i = yStart;
	for (j=0; j<rows; j++)
	{
		i+=yInc;
		pDC->MoveTo(xStart,-i);
		pDC->LineTo(xEnd,-i);
	}
	for (j=xStart+1500; j<xEnd; j+=xInc)
	{
		pDC->MoveTo(j,-yStart);
		pDC->LineTo(j,-i);
	}
	pDC->TextOut(xStart + 1500 + 100, -(yStart + 55), _T("AB"), 2);
	pDC->TextOut(xStart + 1500 + 150 + (1 * xInc), -(yStart + 55), _T("R"), 1);
	pDC->TextOut(xStart + 1500 + 150 + (2 * xInc), -(yStart + 55), _T("H"), 1);
	pDC->TextOut(xStart + 1500 + 90 + (3 * xInc), -(yStart + 55), _T("RBI"), 3);
	pDC->TextOut(xStart + 1500 + 125 + (4 * xInc), -(yStart + 55), _T("2B"), 2);
	pDC->TextOut(xStart + 1500 + 125 + (5 * xInc), -(yStart + 55), _T("3B"), 2);
	pDC->TextOut(xStart + 1500 + 125 + (6 * xInc), -(yStart + 55), _T("HR"), 2);
	pDC->TextOut(xStart + 1500 + 150 + (7 * xInc), -(yStart + 55), _T("W"), 1);
	pDC->TextOut(xStart + 1500 + 150 + (8 * xInc), -(yStart + 55), _T("K"), 1);
	pDC->TextOut(xStart + 1500 + 125 + (9 * xInc), -(yStart + 55), _T("RE"), 2);
	pDC->TextOut(xStart + 1500 + 125 + (10 * xInc), -(yStart + 55), _T("SB"), 2);
	pDC->TextOut(xStart + 1500 + 125 + (11 * xInc), -(yStart + 55), _T("SF"), 2);
	pDC->TextOut(xStart + 1500 + 90 + (12 * xInc), -(yStart + 55), _T("AVG"), 3);
	pDC->TextOut(xStart + 1500 + 90 + (13 * xInc), -(yStart + 55), _T("SLG"), 3);
	pDC->TextOut(xStart + 1500 + 90 + (14 * xInc), -(yStart + 55), _T("OB%"), 3);

	pDC->MoveTo(xStart,-yStart);
	pDC->LineTo(xEnd,-yStart);
	pDC->LineTo(xEnd,-i);
	pDC->MoveTo(xStart,-i);
	pDC->LineTo(xStart,-yStart);

	pDC->SelectObject(origFont);
}
