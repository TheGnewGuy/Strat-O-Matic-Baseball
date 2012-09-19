// BaseballView.h : interface of the CBaseballView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASEBALLVIEW_H__20B48471_70F7_11D2_B0EE_444553540000__INCLUDED_)
#define AFX_BASEBALLVIEW_H__20B48471_70F7_11D2_B0EE_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CBaseballView : public CScrollView
{
protected: // create from serialization only
	CBaseballView();
	DECLARE_DYNCREATE(CBaseballView)

// Attributes
public:
	CBaseballDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseballView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
//	FormA m_FormA;
	virtual ~CBaseballView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CPalette hPalette;
	HANDLE hRes;
	LPBITMAPINFO lpBitmapInfo;
	int nColorData;

// Generated message map functions
protected:
	//{{AFX_MSG(CBaseballView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LPVOID MyAllocMem(DWORD cb);
	LPDEVMODE ChangeDevMode(HWND hWnd, char *pDevice);
};

#ifndef _DEBUG  // debug version in BaseballView.cpp
inline CBaseballDoc* CBaseballView::GetDocument()
   { return (CBaseballDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEBALLVIEW_H__20B48471_70F7_11D2_B0EE_444553540000__INCLUDED_)
