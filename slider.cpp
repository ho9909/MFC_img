// slider.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "mymfc.h"
#include "slider.h"
#include "afxdialogex.h"


// slider ��ȭ �����Դϴ�.

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


// slider �޽��� ó�����Դϴ�.


BOOL slider::OnInitDialog(){
	//�ʱ� ����

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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString temp;
	m_editest.GetWindowText(temp);
	result = _ttoi(temp);
	m_sliderTest.SetPos(result);

}

void slider::OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); // ������ Ÿ�� ��ȯ
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iPos = m_sliderTest.GetPos(); //��ǥ�� �ޱ�
	CString sPos;
	sPos.Format(_T("%d"), iPos); //���氪 ����
	m_editest.SetWindowText(sPos); // ���氪 ���
	*pResult = 0;
}
