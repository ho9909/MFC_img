#pragma once

#include <atlimage.h>
#include "afxwin.h"
#include "afxcmn.h"
#include "mymfc.h"

// bright ��ȭ �����Դϴ�.

class bright : public CDialogEx
{
	DECLARE_DYNAMIC(bright)

public:
	bright(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~bright();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BRIGHTNESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
