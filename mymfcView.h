
// mymfcView.h : CmymfcView Ŭ������ �������̽�
//

#pragma once


class CmymfcView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CmymfcView();
	DECLARE_DYNCREATE(CmymfcView)

// Ư���Դϴ�.
public:
	CmymfcDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CmymfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // mymfcView.cpp�� ����� ����
inline CmymfcDoc* CmymfcView::GetDocument() const
   { return reinterpret_cast<CmymfcDoc*>(m_pDocument); }
#endif

