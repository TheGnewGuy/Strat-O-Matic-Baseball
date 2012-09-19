// FormA.h: interface for the FormA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMA_H__137DAC21_895E_11D2_B0EE_444553540000__INCLUDED_)
#define AFX_FORMA_H__137DAC21_895E_11D2_B0EE_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class FormA  
{
protected:

public:
	FormA();
	void OnDraw(CDC* pDC, CBaseballDoc* pDoc);
	virtual ~FormA();

protected:
	CPalette hPalette;
	HANDLE hRes;
	LPBITMAPINFO lpBitmapInfo;
	int nColorData;

};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMA_H__137DAC21_895E_11D2_B0EE_444553540000__INCLUDED_)
