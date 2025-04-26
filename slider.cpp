// slider.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "mymfc.h"
#include "slider.h"
#include "afxdialogex.h"


// slider 대화 상자입니다.

IMPLEMENT_DYNAMIC(slider, CDialog)

slider::slider(CWnd* pParent /*=NULL*/)
	: CDialog(slider::IDD, pParent)
{

}

slider::~slider()
{
}

void slider::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_TEST, m_sliderTest);
	DDX_Control(pDX, IDC_EDIT_TEST, m_editest);
}


BEGIN_MESSAGE_MAP(slider, CDialog)
	ON_EN_CHANGE(IDC_EDIT_TEST, &slider::OnEnChangeEditTest)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_TEST, &slider::OnNMCustomdrawSlider)
END_MESSAGE_MAP()


// slider 메시지 처리기입니다.


BOOL slider::OnInitDialog(){
	//초기 설정

	CDialog::OnInitDialog();
	m_sliderTest.SetRange(0,255);
	m_sliderTest.SetRangeMax(255);
	m_sliderTest.SetRangeMin(0);
	m_sliderTest.SetPos(result);
	
	int xpos = m_sliderTest.GetPos();
	CString ipos;
	ipos.Format(_T("%d"), xpos);
	m_editest.SetWindowText(ipos);

	return TRUE;
}

void slider::OnEnChangeEditTest()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString temp;
	m_editest.GetWindowText(temp);
	result = _ttoi(temp);
	m_sliderTest.SetPos(result);

}

void slider::OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); // 포인터 타입 변환
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iPos = m_sliderTest.GetPos(); //좌표값 받기
	CString sPos;
	sPos.Format(_T("%d"), iPos); //변경값 저장
	m_editest.SetWindowText(sPos); // 변경값 출력
	*pResult = 0;
}
