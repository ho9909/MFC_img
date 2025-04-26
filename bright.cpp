// bright.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "mymfc.h"
#include "bright.h"
#include "afxdialogex.h"


// bright 대화 상자입니다.

IMPLEMENT_DYNAMIC(bright, CDialogEx)

bright::bright(CWnd* pParent /*=NULL*/)
	: CDialogEx(bright::IDD, pParent)
{
	result = 5;
}

bright::~bright()
{
}

void bright::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, slider1);
	DDX_Control(pDX, IDC_EDIT2, edit1);
}


BEGIN_MESSAGE_MAP(bright, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT2, &bright::OnEnChangeEditTest)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &bright::OnNMCustomdrawSlider)
END_MESSAGE_MAP()


// bright 메시지 처리기입니다.
BOOL bright::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	slider1.SetRange(-255,255);
	slider1.SetRangeMax(255);
	slider1.SetRangeMin(-255);
	slider1.SetPos(result);

	int xpos = slider1.GetPos();
	CString ipos;
	ipos.Format(_T("%d"), xpos);
	edit1.SetWindowText(ipos);

	return TRUE;
}

void bright::OnEnChangeEditTest()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString temp;
	edit1.GetWindowText(temp);
	result = _ttoi(temp);
	slider1.SetPos(result);
}

void bright::OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); // 포인터 타입 변환
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iPos = slider1.GetPos(); //이동하는 좌표값 받기
	CString sPos;
	sPos.Format(_T("%d"), iPos); //변경값 저장
	edit1.SetWindowText(sPos); // 변경값 출력
	*pResult = 0;

}