#pragma once

#include <atlimage.h>
#include "afxwin.h"
#include "afxcmn.h"
#include "mymfc.h"

// slider ��ȭ �����Դϴ�.

class slider : public CDialog
{
	DECLARE_DYNAMIC(slider)

public:
	slider(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~slider();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SLIDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
