#pragma once

#include <atlimage.h>
#include "afxwin.h"
#include "afxcmn.h"
#include "mymfc.h"

// slider 대화 상자입니다.

class slider : public CDialog
{
	DECLARE_DYNAMIC(slider)

public:
	slider(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~slider();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SLIDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sliderTest;
	afx_msg void OnEnChangeEditTest();
	CEdit m_editest;
	virtual BOOL OnInitDialog();

	class CmymfcDOC *pDoc;
	afx_msg void OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult);
	int result;
};
