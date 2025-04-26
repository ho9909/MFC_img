
// mymfcView.h : CmymfcView 클래스의 인터페이스
//

#pragma once


class CmymfcView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CmymfcView();
	DECLARE_DYNCREATE(CmymfcView)

// 특성입니다.
public:
	CmymfcDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CmymfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	CPoint start;
	CPoint end;
	int count;
	int cur_flag;
	CImage c_Img;
	CImage result_Img;
	CImage win_Img;
	int x_count, y_count;
	//BOOL WindowCapture(HWND hTargetWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDiscrimination();
	afx_msg void captureall();
	afx_msg void captureArea();
};

#ifndef _DEBUG  // mymfcView.cpp의 디버그 버전
inline CmymfcDoc* CmymfcView::GetDocument() const
   { return reinterpret_cast<CmymfcDoc*>(m_pDocument); }
#endif

