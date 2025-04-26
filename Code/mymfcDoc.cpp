
// mymfcDoc.cpp : CmymfcDoc 클래스의 구현
//

#include "stdafx.h"
#include "slider.h"
#include "bright.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "mymfc.h"
#endif

#include "mymfcDoc.h"

#include <propkey.h>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CmymfcDoc

IMPLEMENT_DYNCREATE(CmymfcDoc, CDocument)

BEGIN_MESSAGE_MAP(CmymfcDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CmymfcDoc::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CmymfcDoc::OnFileSave)
	ON_COMMAND(ID_FILE_NEW, &CmymfcDoc::OnFileNew)
	ON_COMMAND(ID_Filter_grey, &CmymfcDoc::OnFilterGrey)
	ON_COMMAND(ID_Filter_Sobel, &CmymfcDoc::OnFilterSobel)
	ON_COMMAND(ID_Filter_Binary, &CmymfcDoc::OnFilterBinary)
	ON_COMMAND(ID_slidervalue, &CmymfcDoc::OnFiltervalue)
	ON_COMMAND(ID_Filter_Brighteness, &CmymfcDoc::OnBrightness)
	ON_COMMAND(ID_Filter_stretching, &CmymfcDoc::OnStretching)
	ON_COMMAND(ID_Filter_equalizing, &CmymfcDoc::OnEqualizing)

	ON_COMMAND(ID_RGB_R, &CmymfcDoc::Rgbhsito_r)
	ON_COMMAND(ID_RGB_G, &CmymfcDoc::Rgbhsito_g)
	ON_COMMAND(ID_RGB_B, &CmymfcDoc::Rgbhsito_b)

END_MESSAGE_MAP()


// CmymfcDoc 생성/소멸

CmymfcDoc::CmymfcDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	threshold = 128;
	flag=0;
	what_fill = 0;
}

CmymfcDoc::~CmymfcDoc()
{
}

BOOL CmymfcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CmymfcDoc serialization

void CmymfcDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CmymfcDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CmymfcDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CmymfcDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CmymfcDoc 진단

#ifdef _DEBUG
void CmymfcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CmymfcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CmymfcDoc 명령
void CmymfcDoc::OnFileOpen(){
	TCHAR szFilter[] = _T("JPG 이미지|*.jpg|PNG 이미지|*.png|Bitmap 이미지|*.bmp|Raw 이미지|*.raw|모든파일(*.*)|*.*||");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if(IDOK == fileDlg.DoModal())
	{
		CString filePath;
		filePath = fileDlg.GetPathName();
		if (!m_lmg.IsNull()) { // 필터링 이미지 있으면
			m_lmg.Destroy();
		}
		CFile file;
		switch(fileDlg.m_ofn.nFilterIndex){
		case 4:
			{
				int w, h, i, j;
				BYTE value=0;
				COLORREF pix_data;
				file.Open(filePath, CFile::modeRead, NULL);
				file.Read(&w, 4);
				file.Read(&h, 4);
				m_lmg.Create(w, h, 24);

				for(i = 0; i < h; i++){
					for(j = 0; j < w; j++){
						file.Read(&value, 1);
						pix_data = RGB(value, value, value);
						memcpy(m_lmg.GetPixelAddress(j, i), &pix_data, 3);
					}
				}
				break;
				file.Close();
			}
		default:
			m_lmg.Load(filePath);
		}
	}
	UpdateAllViews(NULL);// 뷰 갱신
}

void CmymfcDoc::OnFileSave()
{
	if(!f_Img.IsNull()){
		TCHAR szFilter[] = _T("JPG 이미지|*.jpg|PNG 이미지|*.png|Bitmap 이미지|*.bmp|Raw 이미지|*.raw|모든파일(*.*)|*.*||");
		CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

		if(fileDlg.DoModal() == IDOK){
			CString filePath;
			filePath = fileDlg.GetPathName();
			switch(fileDlg.m_ofn.nFilterIndex){
			case 1:
				filePath += _T(".jpg");
				f_Img.Save(filePath, Gdiplus::ImageFormatJPEG);
				break;
			case 2:
				filePath += _T(".png");
				f_Img.Save(filePath, Gdiplus::ImageFormatPNG);
				break;
			case 3:
				filePath += _T(".bmp");
				f_Img.Save(filePath, Gdiplus::ImageFormatBMP);
				break;
			case 4:
				filePath += _T(".raw");
				CFile file;
				int width = f_Img.GetWidth();
				int height = f_Img.GetHeight();

				file.Open(filePath, CFile::modeCreate | CFile::modeWrite, NULL);
				file.Write(&width, 4);
				file.Write(&height, 4);
				for(int i=0; i< height; i++){
					for (int j= 0 ; j< width; j++){
						COLORREF color;
						memcpy(&color, f_Img.GetPixelAddress(j,i), 3);
						file.Write(&color, 1);
					}
				}
				file.Close();
				break;
			}
		}
	}
}

void CmymfcDoc::OnFilterGrey()
{	
	what_fill = 1;
	flag=1;
	F_before();
	f_Img.Create(m_lmg.GetWidth(), m_lmg.GetHeight(), 24); // 24비트 비트맵 생성
	m_lmg.BitBlt(f_Img.GetDC(), 0, 0, m_lmg.GetWidth(), m_lmg.GetHeight(), 0, 0, SRCCOPY); // 원래 이미지를 복사함
	f_Img.ReleaseDC(); // dc 해제
	memset(histo,0,256*sizeof(int));
	int h_max = histo[0];
	make_grey();

	for (int h = 1; h < m_lmg.GetHeight() + 1; h++) {
		for (int w = 1; w < m_lmg.GetWidth() + 1; w++)
		{
			unsigned int pix_temp = grey[h][w];
			histo[pix_temp]++;
			if(histo[pix_temp] > h_max)
				h_max = histo[pix_temp];
			COLORREF pix_data = RGB(pix_temp, pix_temp, pix_temp);
			memcpy(f_Img.GetPixelAddress(w-1, h-1), &pix_data, 3);
		}
	}
	make_histogram(h_max);

	heightp_Img.Create(f_Img.GetWidth(), f_Img.GetHeight(),24);
	for(int i = 0; i < heightp_Img.GetWidth()+1; i++){
		int sum = 0;
		for(int j = 0; j< heightp_Img.GetHeight()+1; j++){
			sum += grey[j][i];
		}
		float temp = float(sum)/((255*float(f_Img.GetHeight())));
		int p_x = temp*f_Img.GetHeight();
		for(int k=0; k<p_x; k++){
			COLORREF color = RGB(255,255,255);
			memcpy(heightp_Img.GetPixelAddress(i-1, k), &color, 3);
		}
	}
	
	widthp_Img.Create(f_Img.GetWidth(), f_Img.GetHeight(), 24);

	for(int i = 0; i < f_Img.GetHeight()+1; i++){
		int sum1 = 0;
		for(int j = 0; j< f_Img.GetWidth()+1; j++){
			sum1 += grey[i][j];
		}
		float temp1 = float(sum1)/((255*float(f_Img.GetWidth())));
		int p_x = temp1*f_Img.GetWidth();
		for(int k=0; k<p_x; k++){
			COLORREF color = RGB(255,255,255);
			memcpy(widthp_Img.GetPixelAddress(k, i-1), &color, 3);
		}
	}

	UpdateAllViews(NULL); // 뷰 갱신
}
void CmymfcDoc::OnFilterSobel() // 소벨 필터
{
	what_fill = 3;
	flag = 1;
	F_before();
	make_grey();
	memset(histo,0,256*sizeof(int));
	int h_max = histo[0];

	sobel = new int*[m_lmg.GetHeight()];
	for(int i=0; i<m_lmg.GetHeight(); i++){
		sobel[i] = new int[m_lmg.GetWidth()];
		memset(sobel[i], 0, sizeof(int)*(m_lmg.GetWidth()));
	}

	f_Img.Create(m_lmg.GetWidth(), m_lmg.GetHeight(), 24);
	COLORREF data;

	int filter_x[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
	int filter_y[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
	int temp_x, temp_y;


	for(int h=0; h<m_lmg.GetHeight(); h++){
		for(int w = 0; w<m_lmg.GetWidth(); w++){
			COLORREF color;
			color = 0x00ffffff;
			memcpy(f_Img.GetPixelAddress(w,h), &color, 3);
		}
	}
	unsigned int pixel_grey;
	for(int h=0; h<m_lmg.GetHeight(); h++){
		for(int w = 0; w<m_lmg.GetWidth(); w++){
			temp_x =0;
			temp_y = 0;
			for(int i = 0; i<3; i++){
				for(int j= 0; j<3; j++){
					temp_x = temp_x+(grey[h+i][w+j]*filter_x[i][j]);
					temp_y = temp_y+ (grey[h+i][w+j]*filter_y[i][j]);
				}
			}
			if(abs(temp_x) + abs(temp_y) > threshold){
				data = 0x00000000;
				histo[0]++;
				memcpy(f_Img.GetPixelAddress(w,h), &data, 3);
				sobel[h][w] = 0;
			}
			else{
				data =0x00ffffff;
				histo[255]++;
				memcpy(f_Img.GetPixelAddress(w,h), &data, 3);
				sobel[h][w] = 255;
			}
		}
	}
	if(threshold == 255){
		histo[255] = 0;
		histo[0] = 0;
		for(int h=0; h<m_lmg.GetHeight(); h++){
			for(int w = 0; w<m_lmg.GetWidth(); w++){
				data = 0x00000000;
				memcpy(f_Img.GetPixelAddress(w,h), &data, 3);
				histo[0]++;
				sobel[h][w] = 0;
			}
		}
	}
	else if(threshold == 0){
		histo[255]=0;
		histo[0] = 0;
		for(int h=0; h<m_lmg.GetHeight(); h++){
			for(int w = 0; w<m_lmg.GetWidth(); w++){
				data = 0x00ffffff;
				memcpy(f_Img.GetPixelAddress(w,h), &data, 3);
				histo[255]++;
				sobel[h][w] = 255;
			}
		}
	}		
	if(histo[0] >= 1000000){
		histo[0] = 1000000;
	}
	if(histo[255] >= 1000000){
		histo[255] = 1000000;
	}
	h_max = max(histo[0], histo[255]);
	make_histogram(h_max);
	make_hp();
	make_wp();
	UpdateAllViews(NULL); // 뷰 갱신		
}
void CmymfcDoc::OnFilterBinary(){
	what_fill = 2;
	flag = 1;
	F_before();
	memset(histo, 0, 256 * sizeof(int));
	int h_max = histo[0];
	make_grey();

	f_Img.Create(m_lmg.GetWidth(), m_lmg.GetHeight(), 24);
	f_Img.BitBlt(f_Img.GetDC(), 0,0, m_lmg.GetWidth(), m_lmg.GetHeight(), 0,0, SRCCOPY);
	f_Img.ReleaseDC();


	sobel = new int*[m_lmg.GetHeight()];
	for(int i=0; i<m_lmg.GetHeight(); i++){
		sobel[i] = new int[m_lmg.GetWidth()];
		memset(sobel[i], 0,sizeof(int)*(m_lmg.GetWidth()));
	}
	for(int height = 0; height<m_lmg.GetHeight(); height++){
		for(int width = 0; width < m_lmg.GetWidth(); width++){
			COLORREF color;
			unsigned int temp;

			memcpy(&temp, m_lmg.GetPixelAddress(width, height), 3);
			temp = (GetRValue(temp)+GetGValue(temp)+GetBValue(temp))/3;
			if(temp>threshold){
				temp = 255;
				color = 0x00ffffff;
				memcpy(f_Img.GetPixelAddress(width, height), &color,3);
				sobel[height][width] = 255;
			}
			else{
				temp = 0;
				color = 0x00000000;
				memcpy(f_Img.GetPixelAddress(width, height), &color,3);
				sobel[height][width] =0;
			}
			histo[temp]++;
			if(histo[temp] >= h_max)
				h_max = histo[temp];
			if(h_max >= 1000000){
				histo[temp] = 1000000;
				h_max = 1000000;
			}
		}
	}
	make_histogram(h_max);
	make_wp();
	make_hp();
	UpdateAllViews(NULL);

}

void CmymfcDoc::F_before(void)
{
	if (!f_Img.IsNull()) { // 필터링 이미지 있으면
		f_Img.Destroy();
		h_Img.Destroy();
		widthp_Img.Destroy();
		heightp_Img.Destroy();
	}
	if(!RGBhistogram.IsNull()){
		RGBhistogram.Destroy();
	}
}
void CmymfcDoc::make_grey(void)
{
	grey = new int * [m_lmg.GetHeight() + 2];
	for (int i = 0; i < m_lmg.GetHeight() + 2; i++) {//높이만큼 반복해서 전체 다 할당 
		grey[i] = new int[m_lmg.GetWidth() + 2];
		memset(grey[i], 0, sizeof(int) * (m_lmg.GetWidth() + 2));
	}

	for (int h = 0; h < m_lmg.GetHeight(); h++) {
		for (int w = 0; w < m_lmg.GetWidth(); w++)
		{
			unsigned int pix_temp;
			COLORREF pix_data;
			memcpy(&pix_data, m_lmg.GetPixelAddress(w, h), 3);
			int R = GetRValue(pix_data);
			int G = GetGValue(pix_data);
			int B = GetBValue(pix_data);
			pix_temp = 0.2126 * R + 0.7152 * G + 0.0722 * B;
			grey[h + 1][w + 1] = pix_temp;
		}
	}
}

void CmymfcDoc::make_histogram(int h_max)
{
	int h;
	h_Img.Destroy();
	h_Img.Create(256, h_max, 24); // 24비트 비트맵 생성 검정임
	BYTE* byteptr = (BYTE*)h_Img.GetBits();
	int pitch = h_Img.GetPitch();
	unsigned int pix_data = 255;
	switch(what_fill){
	case 1:
		for (int w = 0; w < 256; w++) {
			for (h = 0; h < histo[w]; h++)
			{	//// 기본 색상은 검정
				*(byteptr + pitch * (h_max - h - 1) + 3 * w) = 255;
				*(byteptr + pitch * (h_max - h - 1) + 3 * w + 1) = 255;
				*(byteptr + pitch * (h_max - h - 1) + 3 * w + 2) = 255;
			}
			if(w == 254 || w == 255){
				h=0;
			}
		}
		break;
	default :
		for (int w = 250; w < 256; w++) {
			for (h = 0; h < histo[255]; h++)
			{	//// 기본 색상은 검정
				*(byteptr + pitch * (h_max - h - 1) + 3 * w) = 255;
				*(byteptr + pitch * (h_max - h - 1) + 3 * w + 1) = 255;
				*(byteptr + pitch * (h_max - h - 1) + 3 * w + 2) = 255;
			}
			if(w == 254 || w == 255){
				h=0;
			}
		}
		for (int w = 0; w < 5; w++) {
			for (h = 0; h < histo[0]; h++)
			{	//// 기본 색상은 검정
				*(byteptr + pitch * (h_max - h - 1) + 3 * w) = 255;
				*(byteptr + pitch * (h_max - h - 1) + 3 * w + 1) = 255;
				*(byteptr + pitch * (h_max - h - 1) + 3 * w + 2) = 255;
			}
			if(w == 254 || w == 255){
				h=0;
			}
		}
		break;
	}
}

void CmymfcDoc::OnFileNew()
{
	if  (!m_lmg.IsNull()){
		m_lmg.Destroy();
		threshold = 128;
		flag=0;
		what_fill = 0;
		if (!f_Img.IsNull()) { // 필터링 이미지 있으면
			f_Img.Destroy();
			h_Img.Destroy();
			widthp_Img.Destroy();
			heightp_Img.Destroy();
		}
		UpdateAllViews(NULL); // 뷰 갱신
	}
}

void CmymfcDoc::make_hp(void)
{
	heightp_Img.Create(m_lmg.GetWidth(), m_lmg.GetHeight(), 24);
	memset(load_hp,0,sizeof(int)*2000);
	for(int i=0; i<m_lmg.GetWidth(); i++){
		int sum = 0;
		for(int j=0; j<m_lmg.GetHeight(); j++){
			if(sobel[j][i] > threshold){
				sum++;
			}
			else
				load_hp[i]++;
		}
		COLORREF color1 = RGB(255,255,255);
		for(int k=0; k<sum; k++){
			memcpy(heightp_Img.GetPixelAddress(i,k),&color1,3);
		}
	}
}

void CmymfcDoc::make_wp(void){
	widthp_Img.Create(m_lmg.GetWidth(), m_lmg.GetHeight(), 24);
	memset(load_wp,0,sizeof(int)*2000);
	for(int i=0; i<m_lmg.GetHeight(); i++){
		int sum = 0;
		for(int j=0; j<m_lmg.GetWidth(); j++){
			if(sobel[i][j] > threshold){
				sum++;
			}
			else
				load_wp[i]++;
		}
		COLORREF color1 = RGB(255,255,255);
		for(int k=0; k<sum; k++){
			memcpy(widthp_Img.GetPixelAddress(k,i),&color1,3);
		}
	}
}

void CmymfcDoc::OnFiltervalue(){
	slider VC;
	VC.result = threshold;
	if(VC.DoModal() == 1){
		threshold = VC.result;

		switch(what_fill){
		case 1:
			OnFilterGrey();
			break;
		case 2:
			OnFilterBinary();
			break;
		case 3:
			OnFilterSobel();
			break;
		}
	}
}

void CmymfcDoc::OnBrightness(){
	bright TC;
	int brightness = 0;
	if(TC.DoModal() == 1 && !m_lmg.IsNull()){
		brightness = TC.result;
		for(int h=0; h<m_lmg.GetHeight(); h++){
			for(int w=0; w<m_lmg.GetWidth(); w++){
				int temp[3];
				COLORREF color;
				memcpy(&color, m_lmg.GetPixelAddress(w,h),3);
				temp[0] = GetRValue(color);
				temp[1] = GetGValue(color);
				temp[2] = GetBValue(color);
				for(int k=0; k<3; k++){
					temp[k] += brightness;
					if(temp[k] >255)
						temp[k] = 255;
					else if(temp[k] <0)
						temp[k] = 0;
				}
				color = RGB(temp[0], temp[1], temp[2]);
				memcpy(m_lmg.GetPixelAddress(w,h),&color,3);
			}
		}
		switch(what_fill){
		case 1:
			OnFilterGrey();
			break;
		case 2:
			OnFilterBinary();
			break;
		case 3:
			OnFilterSobel();
			break;
		}
		UpdateAllViews(NULL); // 뷰 갱신
	}
}
void CmymfcDoc::OnStretching(){
	flag = 1;
	int h_max = 0;
	int pixel;
	COLORREF color;
	if(what_fill == 1){
		int max = 0;
		int min = 0;
		int temp=0;
		int div;
		temp = 0;
		while(histo[temp]== 0){
			temp++;
		}
		min = temp;
		temp = 255;
		while(histo[temp] == 0){
			temp--;
		}
		max = temp;
		div = 255/(max-min);
		memset(histo,0,sizeof(histo));
		for(int h=1; h<f_Img.GetHeight(); h++){
			for(int w=1; w<f_Img.GetWidth(); w++){
				pixel = grey[h][w];
				temp = (pixel-min)*div;
				grey[h][w] = temp; 

				histo[temp]++;
				if(histo[temp]>h_max)
					h_max = histo[temp];
				if(h_max >= 1000000){
					h_max = 1000000;
					histo[temp] =1000000;
				}

				color = RGB(temp, temp, temp);
				memcpy(f_Img.GetPixelAddress(w-1,h-1), &color,3);

			}
		}
		h_Img.Destroy();
		widthp_Img.Destroy();
		heightp_Img.Destroy();
		make_histogram(h_max);
		heightp_Img.Create(f_Img.GetWidth(), f_Img.GetHeight(),24);
		for(int i = 1; i < heightp_Img.GetWidth()+1; i++){
			int sum = 0;
			for(int j = 1; j< heightp_Img.GetHeight()+1; j++){
				sum += grey[j][i];
			}
			float temp = float(sum)/((255*float(f_Img.GetHeight())));
			int p_x = temp*f_Img.GetHeight();
			for(int k=0; k<p_x; k++){
				COLORREF color = RGB(255,255,255);
				memcpy(heightp_Img.GetPixelAddress(i-1, k), &color, 3);
			}
		}

		widthp_Img.Create(f_Img.GetWidth(), f_Img.GetHeight(), 24);

		for(int i = 1; i < f_Img.GetHeight()+1; i++){
			int sum1 = 0;
			for(int j = 1; j< f_Img.GetWidth()+1; j++){
				sum1 += grey[i][j];
			}
			float temp1 = float(sum1)/((255*float(f_Img.GetWidth())));
			int p_x = temp1*f_Img.GetWidth();
			for(int k=0; k<p_x; k++){
				COLORREF color = RGB(255,255,255);
				memcpy(widthp_Img.GetPixelAddress(k, i-1), &color, 3);
			}
		}
	}
	UpdateAllViews(NULL);
}
void CmymfcDoc::OnEqualizing(){
	flag = 1;
	int h_max = 0,cur;
	if(what_fill == 1){
		unsigned long sum_histogram[256], sum, temp;
		double normal[256];
		temp = f_Img.GetWidth()*f_Img.GetHeight();
		sum = histo[0];
		sum_histogram[0] = sum;


		for(int i=0; i<256; i++){
			sum+= histo[i];
			sum_histogram[i] = sum;
		}

		for(int i =0; i<256; i++){
			normal[i] = (double)sum_histogram[i]/temp*255;
			cur = normal[i]*10;
			//반올림 계산
			if((cur/5) %2 == 0){ //버림
				cur -= cur%5;
				cur /= 10;
			}
			else{ // 올림
				cur += 5-(cur%5);
				cur /= 10;
			}
			normal[i] = cur;
		}
		memset(histo,0,sizeof(histo)); //히스토그램 초기화
		for(int i=1; i<f_Img.GetHeight(); i++){
			for(int j=1; j<f_Img.GetWidth(); j++){
				int change = normal[grey[i][j]];
				COLORREF color = RGB(change, change, change);
				grey[i][j] = change;
				histo[change]++;
				if(histo[change] > h_max)
					h_max = histo[change];
				if(h_max >= 1000000){
					h_max = 1000000;
					histo[change] = 1000000;
				}
				memcpy(f_Img.GetPixelAddress(j-1,i-1), &color, 3);
			}
		}
		h_Img.Destroy();
		widthp_Img.Destroy();
		heightp_Img.Destroy();
		make_histogram(h_max);
		heightp_Img.Create(f_Img.GetWidth(), f_Img.GetHeight(),24);
		for(int i = 0; i < heightp_Img.GetWidth()+1; i++){
			int sum1 = 0;
			for(int j = 0; j< heightp_Img.GetHeight()+1; j++){
				sum1 += grey[j][i];
			}
			float temp1 = float(sum1)/((255*float(f_Img.GetHeight())));
			int p_x = temp1*f_Img.GetHeight();
			for(int k=0; k<p_x; k++){
				COLORREF color = RGB(255,255,255);
				memcpy(heightp_Img.GetPixelAddress(i-1, k), &color, 3);
			}
		}

		widthp_Img.Create(f_Img.GetWidth(), f_Img.GetHeight(), 24);

		for(int i = 0; i < f_Img.GetHeight()+1; i++){
			int sum2 = 0;
			for(int j = 0; j< f_Img.GetWidth()+1; j++){
				sum2 += grey[i][j];
			}
			float temp2 = float(sum2)/((255*float(f_Img.GetWidth())));
			int p_x = temp2*f_Img.GetWidth();
			for(int k=0; k<p_x; k++){
				COLORREF color = RGB(255,255,255);
				memcpy(widthp_Img.GetPixelAddress(k, i-1), &color, 3);
			}
		}
		UpdateAllViews(NULL);
	}
}
void CmymfcDoc::get_rgb(){
	R_data = new int * [m_lmg.GetHeight()+2];
	for(int i=0; i<m_lmg.GetHeight()+2; i++){
		R_data[i] = new int[m_lmg.GetWidth()+2];
		memset(R_data[i],0,sizeof(int)*(m_lmg.GetWidth()+2));
	}
	for(int h=0; h<m_lmg.GetHeight(); h++){
		for(int w=0; w<m_lmg.GetWidth(); w++){
			COLORREF color;
			memcpy(&color, m_lmg.GetPixelAddress(w,h), 3);
			int r = GetRValue(color);
			R_data[h+1][w+1] = r;
		}
	}
	G_data = new int * [m_lmg.GetHeight()+2];
	for(int j=0; j<m_lmg.GetHeight()+2; j++){
		G_data[j] = new int[m_lmg.GetWidth()+2];
		memset(G_data[j],0,sizeof(int)*(m_lmg.GetWidth()+2));
	}
	for(int h1=0; h1<m_lmg.GetHeight(); h1++){
		for(int w1=0; w1<m_lmg.GetWidth(); w1++){
			COLORREF color;
			memcpy(&color, m_lmg.GetPixelAddress(w1,h1), 3);
			int g = GetGValue(color);
			G_data[h1+1][w1+1] = g;
		}
	}
	B_data = new int * [m_lmg.GetHeight()+2];
	for(int k=0; k<m_lmg.GetHeight()+2; k++){
		B_data[k] = new int[m_lmg.GetWidth()+2];
		memset(B_data[k],0,sizeof(int)*(m_lmg.GetWidth()+2));
	}
	
	for(int h2=0; h2<m_lmg.GetHeight(); h2++){
		for(int w2=0; w2<m_lmg.GetWidth(); w2++){
			COLORREF color;
			memcpy(&color, m_lmg.GetPixelAddress(w2,h2), 3);
			int b = GetBValue(color);
			B_data[h2+1][w2+1] = b;
		}
	}
}
void CmymfcDoc::Rgbhsito_r(){
	what_color = 1;
	OnHistogram(what_color);
}
void CmymfcDoc::Rgbhsito_g(){
	what_color = 2;
	OnHistogram(what_color);
}
void CmymfcDoc::Rgbhsito_b(){
	what_color = 3;
	OnHistogram(what_color);
}

void CmymfcDoc::OnHistogram(int what_color){
	flag =1;
	int h_max[3]={0,0,0};
	int max_value = 0;
	get_rgb();
	int h = 0;

	switch(what_color){
	case 1:
		RGBhistogram.Destroy();
		unsigned int temp_R;
		memset(histoR, 0, 256*sizeof(int));
		for(int h1=1; h1<m_lmg.GetHeight()+1; h1++){
			for(int w = 1; w<m_lmg.GetWidth()+1; w++){
				temp_R = 0;
			    temp_R = R_data[h1][w];
				histoR[temp_R]++;
				if(histoR[temp_R] > h_max[0])
					h_max[0] = histoR[temp_R];
				if(h_max[0]>1000000){
					h_max[0] = 1000000;
					histoR[temp_R] = 1000000;
				}
			}

		}
		RGBhistogram.Create(256, h_max[0], 24);
		
		for (int w = 0; w < 256; w++) {
			for (h = 0; h < histoR[w]; h++)
			{	//// 기본 색상은 검정
				BYTE *p = (BYTE*)RGBhistogram.GetPixelAddress(w, h);

				*p++ = 255;
				*p++ = 255;
				*p = 0;
			}
		}
		break;
	case 2:
		RGBhistogram.Destroy();
		unsigned int temp_G;
		memset(histoG, 0, 256*sizeof(int));
		for(int h1=1; h1<m_lmg.GetHeight()+1; h1++){
			for(int w = 1; w<m_lmg.GetWidth()+1; w++){
				temp_G = 0;
				temp_G = G_data[h1][w];
				histoG[temp_G]++;
				if(histoG[temp_G] > h_max[1])
					h_max[1] = histoG[temp_G];
				if(h_max[1]>1000000){
					h_max[1] = 1000000;
					histoG[temp_G] = 1000000;
				}
			}

		}
		RGBhistogram.Create(256, h_max[1], 24);
		for (int w = 0; w < 256; w++) {
			for (h = 0; h < histoG[w]; h++)
			{	//// 기본 색상은 검정
				BYTE *p = (BYTE*)RGBhistogram.GetPixelAddress(w, h);

				*p++ = 255;
				*p++ = 0;
				*p = 255;
			}
		}
		break;
	case 3:
		RGBhistogram.Destroy();
		unsigned int temp_B;
		memset(histoB, 0, 256*sizeof(int));
		for(int h1=1; h1<m_lmg.GetHeight()+1; h1++){
			for(int w = 1; w<m_lmg.GetWidth()+1; w++){
				temp_B = 0;
				temp_B = B_data[h1][w];
				histoB[temp_B]++;
				if(histoB[temp_B] > h_max[2])
					h_max[2] = histoB[temp_B];
				if(h_max[2]>1000000){
					h_max[2] = 1000000;
					histoB[temp_B] = 1000000;
				}
			}

		}
		RGBhistogram.Create(256, h_max[2], 24);
		for (int w = 0; w < 256; w++) {
			for (h = 0; h < histoB[w]; h++)
			{	//// 기본 색상은 검정
				BYTE *p = (BYTE*)RGBhistogram.GetPixelAddress(w, h);

				*p++ = 0;
				*p++ = 255;
				*p = 255;
			}
		}
		break;
	}
	UpdateAllViews(NULL);
}



