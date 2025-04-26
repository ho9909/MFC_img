#pragma once

#include <atlimage.h>
#include "afxwin.h"
#include "afxcmn.h"
#include "mymfc.h"

// bright 대화 상자입니다.

class bright : public CDialogEx
{
	DECLARE_DYNAMIC(bright)

public:
	bright(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~bright();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BRIGHTNESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl slider1;
	afx_msg void OnEnChangeEditTest();
	CEdit edit1;
	virtual BOOL OnInitDialog();

	class CmymfcDOC *pDoc;
	afx_msg void OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult);
	int result;
};
