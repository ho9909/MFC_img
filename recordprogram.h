

#pragma once

#include <atlimage.h>
#include "afxwin.h"
#include "afxcmn.h"
#include "mymfc.h"

// recordprogram ��ȭ �����Դϴ�.

class recordprogram : public CDialogEx
{
	DECLARE_DYNAMIC(recordprogram)

public:
	recordprogram(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual ~recordprogram();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	HACCEL m_hAccel;
	CImage all_Img1;
	virtual BOOL OnInitDialog();
	int index;
	int i;
	int count;
	HDC h_dc1;
	afx_msg void OnCapture();
	afx_msg void OnStart();
	afx_msg void OnEnd();
	afx_msg void OnAllcap();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnForcecap();//HWND handle, CPoint point
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};
