// bright.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "mymfc.h"
#include "bright.h"
#include "afxdialogex.h"


// bright ��ȭ �����Դϴ�.

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


// bright �޽��� ó�����Դϴ�.
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
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString temp;
	edit1.GetWindowText(temp);
	result = _ttoi(temp);
	slider1.SetPos(result);
}

void bright::OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); // ������ Ÿ�� ��ȯ
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int iPos = slider1.GetPos(); //�̵��ϴ� ��ǥ�� �ޱ�
	CString sPos;
	sPos.Format(_T("%d"), iPos); //���氪 ����
	edit1.SetWindowText(sPos); // ���氪 ���
	*pResult = 0;

}