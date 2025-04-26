
// mymfcView.cpp : CmymfcView 클래스의 구현
//

#include "stdafx.h"
#include "recordprogram.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "mymfc.h"
#endif

#include "mymfcDoc.h"
#include "mymfcView.h"


#include <atlimage.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmymfcView

IMPLEMENT_DYNCREATE(CmymfcView, CScrollView)

BEGIN_MESSAGE_MAP(CmymfcView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CmymfcView::OnFilePrintPreview)
	ON_COMMAND(ID_discrimination, &CmymfcView::OnDiscrimination)
	ON_COMMAND(ID_CAPTUREArea, &CmymfcView::captureArea)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CmymfcView 생성/소멸

CmymfcView::CmymfcView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CmymfcView::~CmymfcView()
{
}

BOOL CmymfcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CmymfcView 그리기

void CmymfcView::OnDraw(CDC* pDC)
{
	CmymfcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	pDC = GetDC(); // dc 가져옴
	pDC -> Rectangle(10, 30, 400, 450);		// 1 원본 사진
	pDC -> Rectangle(410, 30, 800, 450);	// 2 필터 적용 사진
	pDC -> Rectangle(810, 30, 1200, 450);	// 3 세로 프로젝션
	pDC -> Rectangle(10, 460, 400, 880);	// 4 히스토그램
	pDC -> Rectangle(410, 460, 800, 880);	// 5 가로 프로젝션
	pDC -> Rectangle(810, 460, 1200, 880);	// 6 RGB히스토그램

	CPen pen,  *oldpen;
	POINT x;
	for(int i=0; i<256; i++){
		x.x = 1.3*i;
		x.y = 900;
		pen.CreatePen(PS_SOLID,1,RGB(i,i,i));
		oldpen = pDC->SelectObject(&pen);
		pDC->MoveTo(20+x.x, 900);
		pDC->LineTo(20+x.x,915);
		pen.DeleteObject();
	}

	if (!pDoc->m_lmg.IsNull()){ // 원본 이미지 출력
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		pDoc->m_lmg.StretchBlt(pDC->m_hDC, 11, 31, 388, 418);
		if (!c_Img.IsNull())
			c_Img.Destroy();
	}
	if (!pDoc->f_Img.IsNull() && pDoc->flag == 1){ // 필터링 이미지 출력
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		pDoc->f_Img.StretchBlt(pDC->m_hDC, 411, 31, 388, 418);
	}
	if (!pDoc->h_Img.IsNull() && pDoc->flag == 1) { // 히스토그램 이미지 출력
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		pDoc->h_Img.StretchBlt(pDC->m_hDC, 11, 461, 388, 418,NOTSRCCOPY);
	}

	pDC->TextOutW(5, 890, _T("0"));
	pDC->TextOutW(385, 890, _T("255"));

	if (!pDoc->widthp_Img.IsNull() && pDoc->flag == 1) { // 가로 프로젝션
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		pDoc->widthp_Img.StretchBlt(pDC->m_hDC, 811, 31, 388, 418);
	}
	if (!pDoc->heightp_Img.IsNull() && pDoc->flag == 1) { // 세로 프로젝션
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		pDoc->heightp_Img.StretchBlt(pDC->m_hDC, 411, 461, 388, 418);
	}
	if (!pDoc->RGBhistogram.IsNull() && pDoc->flag == 1) { // rgb 히스토그램
		pDoc->RGBhistogram.StretchBlt(pDC->m_hDC,811, 461, 388, 418, NOTSRCCOPY);
	}
	pDoc -> flag = 0;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CmymfcView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CmymfcView 인쇄


void CmymfcView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CmymfcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CmymfcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CmymfcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CmymfcView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CmymfcView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CmymfcView 진단

#ifdef _DEBUG
void CmymfcView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CmymfcView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CmymfcDoc* CmymfcView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmymfcDoc)));
	return (CmymfcDoc*)m_pDocument;
}
#endif //_DEBUG


// CmymfcView 메시지 처리기

void CmymfcView::OnMouseMove(UINT nFlags, CPoint point)
{		
	CDC* pDC;
	CmymfcDoc* pDoc = GetDocument();
	if(count !=0&&!pDoc->m_lmg.IsNull()){
		pDC = GetDC();

		CClientDC dc(this);
		CView::OnMouseMove(nFlags,point);
		CBrush brush;
		CPoint cur;

		brush.CreateStockObject(NULL_BRUSH); 
		CBrush *pOldBrush = dc.SelectObject(&brush);

		switch(count){
		case 1:
			SetStretchBltMode(pDC->m_hDC, HALFTONE);
			pDoc->m_lmg.StretchBlt(pDC->m_hDC, 11,31, 388, 418);
			if((point.x >10 && point.x <400) && (point.y > 30 && point.y < 450)){}
			else if( point.x <11)
				point.x =11;
			else if(point.x > 399)
				point.x = 399;
			else if(point.y <31)
				point.y = 31;
			else if(point.y > 449)
				point.y = 449;
			break;
		case 2:
			SetStretchBltMode(pDC->m_hDC, HALFTONE);
			pDoc->f_Img.StretchBlt(pDC->m_hDC, 411, 31, 388, 418);
			if((point.x > 410 && point.x < 800)&&(point.y<450 && point.y >30)){}
			else if(point.x < 410)
				point.x = 410;
			else if(point.x > 799)
				point.x = 799;
			else if(point.y < 31)
				point.x = 31;
			else if(point.y > 449)
				point.y = 449;
			break;
		}
		dc.Rectangle(start.x, start.y, point.x, point.y);
		dc.SelectObject(pOldBrush);
		DeleteObject(brush);
	}
}

void CmymfcView::OnLButtonUp(UINT nFlags, CPoint point){
	CView::OnLButtonDown(nFlags,point);
	end = point;
	if(end.x == 0 && end.y == 0){
		count = 0;
	}
	switch(count){
	case 1:
		if((end.x > 10 && end.x <400)&&(end.y<450 && end.y>30)){
		}
		else if(end.x <11)
			end.x = 11;
		else if(end.x>399)
			end.x = 399;
		else if(end.y>449)
			end.y = 449;
		else if(end.y<31)
			end.y = 31;
		start.x -= 11, start.y -= 31;
		end.x -= 11, end.y -= 31;
		break;
	case 2:
		if((end.x > 410 && end.x < 800)&&(end.y<450 && end.y >30)){}
		else if(end.x<411)
			end.x =411;
		else if(end.x >799)
			end.x = 799;
		else if(end.y <31)
			end.y = 31;
		else if(end.y >449)
			end.y = 449;
		start.x -= 410, start.y -= 31;
		end.x -= 410, end.y -= 31;
	}
	if(count !=0){
		CDC* pDC;
		pDC = GetDC();
		CmymfcDoc* pDoc = GetDocument();

		if(start.x >end.x){
			int temp;
			temp = start.x;
			start.x = end.x;
			end.x = temp;
		}
		if(start.y >end.y){
			int temp;
			temp = start.y;
			start.y = end.y;
			end.y = temp;
		}
		double width = double(pDoc->m_lmg.GetWidth())/388;
		double height = double(pDoc->m_lmg.GetHeight())/418;

		start.x  = double(start.x)*width;
		start.y = double(start.y)*height;
		end.x = double(end.x)*width;
		end.y = double(end.y)*height; 

		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		if (!c_Img.IsNull()){
			c_Img.Destroy();
		}
		switch(count){
		case 1:
			c_Img.Create(end.x -start.x, end.y-start.y, 24);
			pDoc->m_lmg.BitBlt(c_Img.GetDC(),0,0,c_Img.GetWidth(), c_Img.GetHeight(),start.x,start.y,SRCCOPY);
			c_Img.ReleaseDC();

			SetStretchBltMode(pDC->m_hDC, HALFTONE);
			c_Img.StretchBlt(pDC->m_hDC, 811, 461, 388, 418);
			break;
		case 2:
			c_Img.Create(end.x -start.x, end.y-start.y, 24);
			pDoc->f_Img.BitBlt(c_Img.GetDC(),0,0,c_Img.GetWidth(), c_Img.GetHeight(),start.x,start.y,SRCCOPY);
			c_Img.ReleaseDC();

			SetStretchBltMode(pDC->m_hDC, HALFTONE);
			c_Img.StretchBlt(pDC->m_hDC, 811, 461, 388, 418);
			break;
		}
	}
	count =0;

}

void CmymfcView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CView::OnLButtonDown(nFlags, point);
	if((point.x >10 && point.x < 400) && (point.y < 450 && point.y >30)){
		start = point;
		CmymfcDoc* pDoc = GetDocument();
		if(!pDoc->m_lmg.IsNull())
			count = 1;
	}
	if((point.x > 410 && point.x < 800)&&(point.y<450 && point.y >30)){
		start = point;
		CmymfcDoc* pDoc = GetDocument();
		if(!pDoc->f_Img.IsNull())
			count =2;
	}
}
void CmymfcView::OnDiscrimination(){

		// 이미지 이미 있으면 삭제
	if (!c_Img.IsNull()){
		result_Img.Destroy();
	}

	CDC* pDC;
	pDC = GetDC();
	CmymfcDoc* pDoc = GetDocument();
	int i=0,k = 0;
	int hp_sum=0;
	int wp_sum=0;
	int temp=0;
	int p_max=0;
	int cur = 0;

	for(int j = 0; j<2000; j++){
		hp_sum += pDoc->load_hp[j];
		wp_sum += pDoc->load_wp[j];
	}
	hp_sum  = hp_sum/pDoc->m_lmg.GetWidth();
	wp_sum = wp_sum/pDoc->m_lmg.GetHeight();


	// 시작 지점 찾기
	//i = pDoc->m_lmg.GetHeight()-1;
	//while(pDoc->load_wp[i] == 0){
	//	if(pDoc->load_wp[i] != 0)
	//		break;
	//	i--;
	//}
	for(i = pDoc->m_lmg.GetHeight()-1; i>=0; i--){
		if(p_max < pDoc->load_wp[i]){
			p_max = pDoc->load_wp[i];
			cur = i;
		}
	}
	// 가로 시작점
	//while(pDoc->load_hp[temp] == 0){
	//	if(pDoc->load_hp[temp] != 0)
	//		break;
	//	temp++;
	//}
	for(k=0; k<pDoc->m_lmg.GetWidth(); k++){
		if(pDoc->load_hp[k] < hp_sum && pDoc->load_hp[k] != 0)
			break;
	}
	i = cur+100;
	y_count  = cur-100;
	//// 여유값 두기
	//i = i-30;
	//if(i > pDoc->m_lmg.GetHeight()-1){
	//	i = pDoc->m_lmg.GetHeight()-1;
	//}


	//k = temp;
	// 끝지점 찾기
	//y_count = i-200;
	//x_count = k+300;

	//세로 끝점 (평균값으로 하기에는 한계가....)
	//for(y_count=pDoc->m_lmg.GetHeight()-1; y_count>=0; y_count--){
	//	if(pDoc->load_wp[y_count] > wp_sum-40 && pDoc->load_wp[y_count] != 0 &&y_count != i)
	//		break;
	//}
	// 가로 끝점
	for(x_count=0; x_count<pDoc->m_lmg.GetWidth(); x_count++){
		if(pDoc->load_hp[x_count] > hp_sum && pDoc->load_hp[x_count] != 0 && x_count != k && x_count > k)
			break;
	}
	k = temp-10;
	if(k <0){
		k = 0;
	}
	x_count = x_count +30;

	// 원본 이미지 값을 넘길 경우
	if(x_count > pDoc->m_lmg.GetWidth())
		x_count = pDoc->m_lmg.GetWidth();

	// 추출한 이미지 출력
	result_Img.Create(abs(x_count-k),abs(i-y_count),24);
	pDoc->m_lmg.BitBlt(result_Img.GetDC(),0,0,result_Img.GetWidth(),result_Img.GetHeight(),k,y_count,SRCCOPY);
	result_Img.ReleaseDC();
	SetStretchBltMode(pDC->m_hDC, HALFTONE);
	result_Img.StretchBlt(pDC->m_hDC, 811, 461, 388, 418);

}


void CmymfcView::captureArea(){
	recordprogram RC;
	if(RC.DoModal() == 1){
		int temp = 1;
	}
}
	