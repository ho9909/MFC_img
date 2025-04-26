// recordprogram.cpp : 구현 파일입니다.
//

#include <iostream>


#include "stdafx.h"
#include "mymfc.h"
#include "recordprogram.h"
#include "afxdialogex.h"

using namespace std;

//avcodec_register_all();
// recordprogram 대화 상자입니다.

IMPLEMENT_DYNAMIC(recordprogram, CDialogEx)

	recordprogram::recordprogram(CWnd* pParent /*=NULL*/)
	: CDialogEx(recordprogram::IDD, pParent)
{

}

recordprogram::~recordprogram()
{
}

void recordprogram::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	CWnd *pWnd = AfxGetMainWnd();
	HWND hwnd = this->m_hWnd;

	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	BYTE alpha = 50;
	COLORREF cr = GetSysColor(COLOR_BTNFACE);
	SetLayeredWindowAttributes(cr, alpha, LWA_COLORKEY);
}


BEGIN_MESSAGE_MAP(recordprogram, CDialogEx)
	ON_WM_TIMER()
	ON_COMMAND(ID_CAPTURE, &recordprogram::OnCapture)
	ON_COMMAND(ID_START, &recordprogram::OnStart)
	ON_COMMAND(ID_END, &recordprogram::OnEnd)
	ON_COMMAND(ID_ALLcap, &recordprogram::OnAllcap)
	ON_COMMAND(ID_FORCECAP, &recordprogram::OnForcecap)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// recordprogram 메시지 처리기입니다.

void recordprogram::OnTimer(UINT_PTR nIDEvent){
	if(nIDEvent == 1){
		CWnd *pWnd = AfxGetMainWnd();
		HWND hwnd = this->m_hWnd;

		HDC h_dc = ::GetWindowDC(NULL);

		TCHAR *str;

		CRect rdlg;
		::GetWindowRect(hwnd, &rdlg);
		index = 0;
		int nx = (rdlg.right-12) - (rdlg.left +8);
		int ny = (rdlg.bottom-12) - (rdlg.top +50);

		CImage record_Img;
		CWnd* pDesktopWnd = GetDesktopWindow();
		if(!pDesktopWnd){
			return;
		}
		str = (TCHAR*)malloc(10000000);
		str[index++] = (i/10000)%10000;
		str[index++] = (i/1000)%1000;
		str[index++] = (i/100)%100;
		str[index++] = (i/10)%10;
		str[index++] = (i)%10;

		CString t_char;
		t_char = _T("C:/image/");
		CString temp;
		temp.Format(_T("%d%d%d%d%d.jpg"),str[0],str[1],str[2],str[3],str[4]);
		t_char += temp;
		int color = ::GetDeviceCaps(h_dc, BITSPIXEL);
		if(!record_Img.Create(nx, ny, color)){
			return;
		}
		BitBlt(record_Img.GetDC(),0,0,nx, ny, h_dc, rdlg.left+7,rdlg.top+50,SRCCOPY);

		record_Img.Save(t_char, Gdiplus::ImageFormatJPEG);
		i++;

		record_Img.ReleaseDC();
		record_Img.Destroy();
	}
}




void recordprogram::OnCapture()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CWnd *pWnd = AfxGetMainWnd();
	HWND hwnd = this->m_hWnd;


	// 듀얼모니터 인경우 보조 모니터의 캡쳐가 되지 않음

	CRect rdlg;
	::GetWindowRect(hwnd, &rdlg);

	int nx = (rdlg.right-12) - (rdlg.left +8);
	int ny = (rdlg.bottom-12) - (rdlg.top +50);

	CImage capture_Img;
	CWnd* pDesktopWnd = GetDesktopWindow();
	if(!pDesktopWnd){
		return;
	}

	HDC h_dc = ::GetWindowDC(NULL);
	int color = ::GetDeviceCaps(h_dc, BITSPIXEL);
	if(!capture_Img.Create(nx, ny, color)){
		return;
	}
	BitBlt(capture_Img.GetDC(),0,0,nx, ny, h_dc, rdlg.left+7,rdlg.top+50,SRCCOPY);

	if(!capture_Img.IsNull()){
		TCHAR szFilter[] = _T("JPG 이미지|*.jpg|PNG 이미지|*.png|Bitmap 이미지|*.bmp|Raw 이미지|*.raw|모든파일(*.*)|*.*||");
		CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

		if(fileDlg.DoModal() == IDOK){
			CString filePath;
			filePath = fileDlg.GetPathName();
			switch(fileDlg.m_ofn.nFilterIndex){
			case 1:
				filePath += _T(".jpg");
				capture_Img.Save(filePath, Gdiplus::ImageFormatJPEG);
				break;
			case 2:
				filePath += _T(".png");
				capture_Img.Save(filePath, Gdiplus::ImageFormatPNG);
				break;
			case 3:
				filePath += _T(".bmp");
				capture_Img.Save(filePath, Gdiplus::ImageFormatBMP);
				break;
			case 4:
				filePath += _T(".raw");
				CFile file;
				int width = capture_Img.GetWidth();
				int height = capture_Img.GetHeight();

				file.Open(filePath, CFile::modeCreate | CFile::modeWrite, NULL);
				file.Write(&width, 4);
				file.Write(&height, 4);
				for(int i=0; i< height; i++){
					for (int j= 0 ; j< width; j++){
						COLORREF color;
						memcpy(&color, capture_Img.GetPixelAddress(j,i), 3);
						file.Write(&color, 1);
					}
				}
				file.Close();
				break;
			}
		}
	}

	capture_Img.ReleaseDC();
	capture_Img.Destroy();

}



void recordprogram::OnStart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	::SetWindowPos(GetSafeHwnd(),  HWND_TOPMOST , 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // 다이얼로그 최상위 포커스 고정
	i=0;
	index = 0;
	SetTimer(1,1000/24,NULL);

}

void DeleteAllFiles(CString dirName) // 디렉터리 내 모든 파일 삭제
{
	CFileFind finder;
	BOOL bWorking  = finder.FindFile((CString)dirName + "/*.*");

	while(bWorking)
	{
		bWorking  = finder.FindNextFile();
		if(finder.IsDots())
		{
			continue;
		}
		CString filePath = finder.GetFilePath();
		DeleteFile(filePath);
	}
	finder.Close();
}


void recordprogram::OnEnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	FILE *fp;

	//char output[300];
	CString dirName = _T("C:/image");
	char *command = "ffmpeg -i C:/image/%05d.jpg -vf crop=trunc(iw/2)*2:trunc(ih/2)*2 -vcodec libx264 -r 30 C:/output/output.mp4";
	fp = _popen(command,"r");
	_pclose(fp);
	KillTimer(1);
	DeleteAllFiles(dirName);
}



void recordprogram::OnAllcap()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CWnd *pWnd = AfxGetMainWnd();
	HWND hwnd = this->m_hWnd;

	HDC h_dc = ::GetWindowDC(NULL);

	CImage all_Img;

	int cx = ::GetSystemMetrics(SM_CXSCREEN);
	int cy = ::GetSystemMetrics(SM_CYSCREEN);

	int color_all = ::GetDeviceCaps(h_dc, BITSPIXEL);

	all_Img.Create(cx,cy,color_all, 0);

	::BitBlt(all_Img.GetDC(), 0,0,cx,cy, h_dc,0,0,SRCCOPY);

	if(!all_Img.IsNull()){
		TCHAR szFilter[] = _T("JPG 이미지|*.jpg|PNG 이미지|*.png|Bitmap 이미지|*.bmp|Raw 이미지|*.raw|모든파일(*.*)|*.*||");
		CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

		if(fileDlg.DoModal() == IDOK){
			CString filePath;
			filePath = fileDlg.GetPathName();
			switch(fileDlg.m_ofn.nFilterIndex){
			case 1:
				filePath += _T(".jpg");
				all_Img.Save(filePath, Gdiplus::ImageFormatJPEG);
				break;
			case 2:
				filePath += _T(".png");
				all_Img.Save(filePath, Gdiplus::ImageFormatPNG);
				break;
			case 3:
				filePath += _T(".bmp");
				all_Img.Save(filePath, Gdiplus::ImageFormatBMP);
				break;
			case 4:
				filePath += _T(".raw");
				CFile file;
				int width = all_Img.GetWidth();
				int height = all_Img.GetHeight();

				file.Open(filePath, CFile::modeCreate | CFile::modeWrite, NULL);
				file.Write(&width, 4);
				file.Write(&height, 4);
				for(int i=0; i< height; i++){
					for (int j= 0 ; j< width; j++){
						COLORREF color;
						memcpy(&color, all_Img.GetPixelAddress(j,i), 3);
						file.Write(&color, 1);
					}
				}
				file.Close();
				break;
			}
		}
	}
	::ReleaseDC(NULL, h_dc);
	all_Img.ReleaseDC();

}
BOOL recordprogram::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_hAccel = ::LoadAccelerators( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDR_MAINFRAME ) );

	return TRUE;
}

BOOL recordprogram::PreTranslateMessage(MSG *pMsg){
	if(::TranslateAccelerator(this->m_hWnd, m_hAccel, pMsg))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void recordprogram::OnForcecap()
{
	count = 1;
	
}

void recordprogram::OnKillFocus(CWnd* pNewWnd)
{
	CDialogEx::OnKillFocus(pNewWnd);

	if(count == 1){
		HWND handle;
		CPoint point;

		CWnd *pWnd = AfxGetMainWnd();
		HWND hwnd = this->m_hWnd;


		::GetCursorPos(&point);

		handle = ::WindowFromPoint(point);

		CRect rdlg;
		::GetWindowRect(handle, &rdlg);

		HDC h_dc = ::GetWindowDC(NULL);

		CImage all_Img;

		int nx = (rdlg.right) - (rdlg.left);
		int ny = (rdlg.bottom) - (rdlg.top);

		int color_all = ::GetDeviceCaps(h_dc, BITSPIXEL);

		all_Img.Create(nx,ny,color_all, 0);

		::BitBlt(all_Img.GetDC(), 0,0,nx,ny, h_dc,rdlg.left,rdlg.top,SRCCOPY);

		if(!all_Img.IsNull()){
			TCHAR szFilter[] = _T("JPG 이미지|*.jpg|PNG 이미지|*.png|Bitmap 이미지|*.bmp|Raw 이미지|*.raw|모든파일(*.*)|*.*||");
			CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

			if(fileDlg.DoModal() == IDOK){
				CString filePath;
				filePath = fileDlg.GetPathName();
				switch(fileDlg.m_ofn.nFilterIndex){
				case 1:
					filePath += _T(".jpg");
					all_Img.Save(filePath, Gdiplus::ImageFormatJPEG);
					break;
				case 2:
					filePath += _T(".png");
					all_Img.Save(filePath, Gdiplus::ImageFormatPNG);
					break;
				case 3:
					filePath += _T(".bmp");
					all_Img.Save(filePath, Gdiplus::ImageFormatBMP);
					break;
				case 4:
					filePath += _T(".raw");
					CFile file;
					int width = all_Img.GetWidth();
					int height = all_Img.GetHeight();

					file.Open(filePath, CFile::modeCreate | CFile::modeWrite, NULL);
					file.Write(&width, 4);
					file.Write(&height, 4);
					for(int i=0; i< height; i++){
						for (int j= 0 ; j< width; j++){
							COLORREF color;
							memcpy(&color, all_Img.GetPixelAddress(j,i), 3);
							file.Write(&color, 1);
						}
					}
					file.Close();
					break;
				}
			}
		}
		::ReleaseDC(NULL, h_dc);
		all_Img.ReleaseDC();
	}
	count = 0;
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
