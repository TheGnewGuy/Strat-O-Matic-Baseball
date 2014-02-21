// FormA.cpp: implementation of the FormA class.
//
//////////////////////////////////////////////////////////////////////
//
// 8/7/99 Added HR to pitcher data and SB/CS to Stats
//

#include "stdafx.h"
#include "Baseball.h"
#include "dialogs.h"
#include "BaseballDoc.h"
#include "FormA.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FormA::FormA()
{
	HANDLE hPal;
	LPLOGPALETTE lpLogPalette;
	int i;

	// TODO: add construction code here

	hRes = LoadResource(AfxGetResourceHandle(),
		FindResource(AfxGetResourceHandle(),
		MAKEINTRESOURCE(IDB_FieldLineGray),RT_BITMAP));
	lpBitmapInfo = (LPBITMAPINFO) LockResource(hRes);
	// Calculate the number of color data entries in DIB
	if (lpBitmapInfo->bmiHeader.biClrUsed != 0)
		nColorData = lpBitmapInfo->bmiHeader.biClrUsed;
	else
	{
		switch (lpBitmapInfo->bmiHeader.biBitCount)
		{
			case 1:
				nColorData = 2;		// Monochrome
				break;
			case 4:
				nColorData = 16;	// typical VGA
				break;
			case 8:
				nColorData = 256;	// 256 colors
				break;
			case 24:
				nColorData = 0;		// RGB encoded for every pixel in bitmap
				break;
		}
	}
	// Allocate memory to hold palette
	hPal = GlobalAlloc(GMEM_MOVEABLE, sizeof(LOGPALETTE) +
		(nColorData * sizeof(PALETTEENTRY)));
	lpLogPalette = (LPLOGPALETTE) GlobalLock(hPal);
	// Create the logical palette
	lpLogPalette->palVersion = 0x300;	// Windows 3.0
	lpLogPalette->palNumEntries = nColorData;
	// Load each color into the palette fields
	for (i=0; i<nColorData; i++)
	{
		lpLogPalette->palPalEntry[i].peRed =
			lpBitmapInfo->bmiColors[i].rgbRed;
		lpLogPalette->palPalEntry[i].peGreen =
			lpBitmapInfo->bmiColors[i].rgbGreen;
		lpLogPalette->palPalEntry[i].peBlue =
			lpBitmapInfo->bmiColors[i].rgbBlue;
	}
	// Create the palette
	hPalette.CreatePalette(lpLogPalette);
	GlobalUnlock(hRes);
	GlobalUnlock(hPal);
	GlobalFree(hPal);
}

FormA::~FormA()
{

}

void FormA::OnDraw(CDC * pDC, CBaseballDoc* pDoc)
{
	#define xStart		2000
	#define yStartForm	250
	#define yStart		500
	#define xIncInning	437
	#define yIncInning	437
	#define xIncStats	250
	#define yIncStats	437

	int ix, iy;
	int ibx, iby;
	int i;
	LPSTR lpBits;
	CFont* origFont;
	CFont myFont;
	LOGFONT lf;
	char szFontName[LF_FACESIZE] = "Times New Roman";

	CSize l_bitmapsize;
	CWnd* pmyCWnd;

	// TODO: add draw code for native data here
	pmyCWnd = AfxGetMainWnd();

	memset(&lf, 0, sizeof(LOGFONT));
	lstrcpy(lf.lfFaceName, szFontName);
	lf.lfHeight = -100;
	VERIFY(myFont.CreateFontIndirect(&lf));
	origFont = pDC->SelectObject(&myFont);

	// Based on 8000 x 10,500 = .001
	// Size for drawing is 437,0 x 10490,-7990
	// 7/16 = 43.75
	// 1/16 = 6.25

	int xStopInning, xStopStats, yStopInnings;
	xStopInning = (12*xIncInning)+xStart;
	yStopInnings = (12*yIncInning)+yStart;
	for (ix=xStart; ix<=xStopInning; ix+=xIncInning)
	{
		pDC->MoveTo(ix,-yStartForm);		// Fld Rating
		pDC->LineTo(ix,-yStopInnings);
	}

	xStopStats = (11*xIncStats)+ix;
	for (ix; ix<=xStopStats; ix+=xIncStats)
	{
		pDC->MoveTo(ix,-yStartForm);		// AB
		pDC->LineTo(ix,-yStopInnings);
	}
	ix-=xIncStats;

	for (iy=yStart; iy<=yStopInnings; iy+=437)
	{
		pDC->MoveTo(437,-iy);		// Players
		pDC->LineTo(xStopStats,-iy);
	}

	iy-=437;
	pDC->MoveTo(437,-yStartForm);
	pDC->LineTo(437,-yStopInnings);
	pDC->LineTo(xStopStats,-yStopInnings);
	pDC->LineTo(xStopStats,-yStartForm);
	pDC->LineTo(437,-yStartForm);
	pDC->TextOut(xStart+49,-(yStartForm+45),"FLDG",4);
	if (pDoc->GetScoresheetFormXtra())
	{
		pDC->TextOut(xStart+150+(1*xIncInning),-(yStartForm+45),"13",2);
		pDC->TextOut(xStart+150+(2*xIncInning),-(yStartForm+45),"14",2);
		pDC->TextOut(xStart+150+(3*xIncInning),-(yStartForm+45),"15",2);
		pDC->TextOut(xStart+150+(4*xIncInning),-(yStartForm+45),"16",2);
		pDC->TextOut(xStart+150+(5*xIncInning),-(yStartForm+45),"17",2);
		pDC->TextOut(xStart+150+(6*xIncInning),-(yStartForm+45),"18",2);
		pDC->TextOut(xStart+150+(7*xIncInning),-(yStartForm+45),"19",2);
		pDC->TextOut(xStart+150+(8*xIncInning),-(yStartForm+45),"20",2);
		pDC->TextOut(xStart+150+(9*xIncInning),-(yStartForm+45),"21",2);
		pDC->TextOut(xStart+113+(10*xIncInning),-(yStartForm+45),"22",2);
		pDC->TextOut(xStart+113+(11*xIncInning),-(yStartForm+45),"23",2);
		pDC->TextOut(xStart+113+(12*xIncInning),-(yStartForm+45),"24",2);
	}
	else
	{
		pDC->TextOut(xStart+150+(1*xIncInning),-(yStartForm+45),"1",1);
		pDC->TextOut(xStart+150+(2*xIncInning),-(yStartForm+45),"2",1);
		pDC->TextOut(xStart+150+(3*xIncInning),-(yStartForm+45),"3",1);
		pDC->TextOut(xStart+150+(4*xIncInning),-(yStartForm+45),"4",1);
		pDC->TextOut(xStart+150+(5*xIncInning),-(yStartForm+45),"5",1);
		pDC->TextOut(xStart+150+(6*xIncInning),-(yStartForm+45),"6",1);
		pDC->TextOut(xStart+150+(7*xIncInning),-(yStartForm+45),"7",1);
		pDC->TextOut(xStart+150+(8*xIncInning),-(yStartForm+45),"8",1);
		pDC->TextOut(xStart+150+(9*xIncInning),-(yStartForm+45),"9",1);
		pDC->TextOut(xStart+113+(10*xIncInning),-(yStartForm+45),"10",2);
		pDC->TextOut(xStart+113+(11*xIncInning),-(yStartForm+45),"11",2);
		pDC->TextOut(xStart+113+(12*xIncInning),-(yStartForm+45),"12",2);
	}
	pDC->TextOut(xStart+33+(13*xIncInning),-(yStartForm+45),"AB",2);
	pDC->TextOut(xStart+88+(13*xIncInning)+(1*xIncStats),-(yStartForm+45),"R",1);
	pDC->TextOut(xStart+88+(13*xIncInning)+(2*xIncStats),-(yStartForm+45),"H",1);
	pDC->TextOut(xStart+25+(13*xIncInning)+(3*xIncStats),-(yStartForm+45),"RBI",3);
	pDC->TextOut(xStart+33+(13*xIncInning)+(4*xIncStats),-(yStartForm+45),"2B",2);
	pDC->TextOut(xStart+33+(13*xIncInning)+(5*xIncStats),-(yStartForm+45),"3B",2);
	pDC->TextOut(xStart+33+(13*xIncInning)+(6*xIncStats),-(yStartForm+45),"HR",2);
	pDC->TextOut(xStart+88+(13*xIncInning)+(7*xIncStats),-(yStartForm+45),"W",1);
	pDC->TextOut(xStart+88+(13*xIncInning)+(8*xIncStats),-(yStartForm+45),"K",1);
	pDC->TextOut(xStart+33+(13*xIncInning)+(9*xIncStats),-(yStartForm+45),"RE",2);
	pDC->TextOut(xStart+25+(13*xIncInning)+(10*xIncStats),-(yStartForm+45-30),"SB",2);
	pDC->TextOut(xStart+75+(13*xIncInning)+(10*xIncStats),-(yStartForm+45+70),"CS",2);

	// Boxes for Inning Scores
	pDC->MoveTo(437,-7000);
	pDC->LineTo(7062,-7000);
	pDC->MoveTo(437,-7500);
	pDC->LineTo(7062,-7500);
	pDC->MoveTo(437,-6750);
	pDC->LineTo(7062,-6750);
	pDC->LineTo(7062,-7990);
	pDC->LineTo(437,-7990);
	pDC->LineTo(437,-6750);
	for (i=1437; i<7062; i+=375)
	{
		pDC->MoveTo(i,-6750);
		pDC->LineTo(i,-7990);
	}
	pDC->TextOut(712,-6800,"TEAMS",5);
	if (pDoc->GetScoresheetFormXtra())
	{
		pDC->TextOut(1437+150,-6800,"13",2);
		pDC->TextOut(1437+150+(1*375),-6800,"14",2);
		pDC->TextOut(1437+150+(2*375),-6800,"15",2);
		pDC->TextOut(1437+150+(3*375),-6800,"16",2);
		pDC->TextOut(1437+150+(4*375),-6800,"17",2);
		pDC->TextOut(1437+150+(5*375),-6800,"18",2);
		pDC->TextOut(1437+150+(6*375),-6800,"19",2);
		pDC->TextOut(1437+150+(7*375),-6800,"20",2);
		pDC->TextOut(1437+150+(8*375),-6800,"21",2);
		pDC->TextOut(1437+113+(9*375),-6800,"22",2);
		pDC->TextOut(1437+113+(10*375),-6800,"23",2);
		pDC->TextOut(1437+113+(11*375),-6800,"24",2);
	}
	else
	{
		pDC->TextOut(1437+150,-6800,"1",1);
		pDC->TextOut(1437+150+(1*375),-6800,"2",1);
		pDC->TextOut(1437+150+(2*375),-6800,"3",1);
		pDC->TextOut(1437+150+(3*375),-6800,"4",1);
		pDC->TextOut(1437+150+(4*375),-6800,"5",1);
		pDC->TextOut(1437+150+(5*375),-6800,"6",1);
		pDC->TextOut(1437+150+(6*375),-6800,"7",1);
		pDC->TextOut(1437+150+(7*375),-6800,"8",1);
		pDC->TextOut(1437+150+(8*375),-6800,"9",1);
		pDC->TextOut(1437+113+(9*375),-6800,"10",2);
		pDC->TextOut(1437+113+(10*375),-6800,"11",2);
		pDC->TextOut(1437+113+(11*375),-6800,"12",2);
	}
		pDC->TextOut(1437+150+(12*375),-6800,"R",1);
		pDC->TextOut(1437+150+(13*375),-6800,"H",1);
		pDC->TextOut(1437+150+(14*375),-6800,"E",1);

	// Pitcher Stats
	pDC->MoveTo(xStopStats,-yStopInnings-125);
	pDC->LineTo(xStopStats,-yStopInnings-125-(5*250));
	pDC->LineTo(xStopStats-1000-(6*375),-yStopInnings-125-(5*250));
	pDC->LineTo(xStopStats-1000-(6*375),-yStopInnings-125);
	pDC->LineTo(xStopStats,-yStopInnings-125);
	for (i=xStopStats-(6*375);i<=xStopStats;i+=375)
	{
		pDC->MoveTo(i,-yStopInnings-125);
		pDC->LineTo(i,-yStopInnings-125-(5*250));
	}
	for (i=yStopInnings+125+250; i<=yStopInnings+125+(5*250); i+=250)
	{
		pDC->MoveTo(xStopStats-1000-(6*375),-i);
		pDC->LineTo(xStopStats,-i);
	}
	pDC->TextOut(xStopStats-1000-(6*375)+192,-yStopInnings-125-50,"PITCHER",7);
	pDC->TextOut(xStopStats-(6*375)+113,-yStopInnings-125-50,"IP",2);
	pDC->TextOut(xStopStats-(6*375)+150+(1*375),-yStopInnings-125-50,"H",1);
	pDC->TextOut(xStopStats-(6*375)+150+(2*375),-yStopInnings-125-50,"W",1);
	pDC->TextOut(xStopStats-(6*375)+150+(3*375),-yStopInnings-125-50,"K",1);
	pDC->TextOut(xStopStats-(6*375)+113+(4*375),-yStopInnings-125-50,"HR",2);
	pDC->TextOut(xStopStats-(6*375)+113+(5*375),-yStopInnings-125-50,"ER",2);

	// Game Number
	pDC->MoveTo(xStopStats,-7990);
	pDC->LineTo(xStopStats,-7250);
	pDC->LineTo(xStopStats-1000,-7250);
	pDC->LineTo(xStopStats-1000,-7990);
	pDC->LineTo(xStopStats,-7990);
	pDC->MoveTo(xStopStats-1000,-7500);
	pDC->LineTo(xStopStats,-7500);
	pDC->TextOut(xStopStats-1000+50,-7250-50,"GAME NUMBER",11);

	// Load the Bitmap
	pDC->SelectPalette(&hPalette, FALSE);
	pDC->RealizePalette();		// Put the palette into action
	hRes = LoadResource(AfxGetResourceHandle(),
		FindResource(AfxGetResourceHandle(),
			MAKEINTRESOURCE(IDB_FieldLineGray),RT_BITMAP));
	lpBitmapInfo = (LPBITMAPINFO) LockResource (hRes);
	// Find the address of the bitmap data
	lpBits = (LPSTR) lpBitmapInfo;
	lpBits += (WORD)lpBitmapInfo->bmiHeader.biSize +
		(WORD) (nColorData * sizeof(RGBQUAD));
	
	// Display the bitmap on the windows client area
	for (ibx=xStart+20+xIncInning; ibx<=xStopInning+20; ibx+=xIncInning)
	{
		for (iby=yStart+20; iby<=yStopInnings; iby+=yIncInning)
		{
			StretchDIBits(pDC->m_hDC, ibx, -iby,
				392,
				-392,
				0, 0,
				(WORD) lpBitmapInfo->bmiHeader.biWidth, 
				(WORD) lpBitmapInfo->bmiHeader.biHeight,
				lpBits, lpBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
		}
	}

	GlobalUnlock(hRes);
	DeleteObject(hPalette);
	FreeResource(hRes);

//		pmyCWnd->MessageBox( "Create CompatibleDC Failed", 
//			"Information", 
//			MB_ICONINFORMATION );
	pDC->SelectObject(origFont);

}
