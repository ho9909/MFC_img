
// mymfcDoc.h : CmymfcDoc 클래스의 인터페이스
//


#pragma once


class CmymfcDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CmymfcDoc();
	DECLARE_DYNCREATE(CmymfcDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CmymfcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileOpen(); // 파일 오픈
	afx_msg void OnFileSave(); // 파일 저장
	afx_msg void OnFilterBinary(); // 바이너리 필터
	afx_msg void OnFilterGrey(); // 그레이 필터
	afx_msg void OnFilterSobel(); // 소벨 필터
	afx_msg void OnFiltervalue(); // 임계값 다이얼로그
	afx_msg void OnFileNew();


	void make_hp(void);
	void make_wp(void);
	void make_grey(void);
	void load_grey(void);
	void get_rgb(void);
	void make_histogram(int max);
	void OnHistogram(int);

	CImage m_lmg; // 불러온 이미지
	CImage f_Img; // 필터거친 이미지
	CImage h_Img; // 히스토그램 이미지
	CImage widthp_Img; // 가로 프로젝션 이미지
	CImage heightp_Img; // 세로 프로젝션 이미지
	CImage RGBhistogram; //rgb 히스토그램 이미지

	int what_color;
	bool flag; // 필터 플래그
	int histo[256]; // 히스토그램 배열
	int histoR[256];
	int histoG[256];
	int histoB[256];

	int load_wp[2000];
	int load_hp[2000];

	int** grey;
	int** R_data;
	int** G_data;
	int** B_data;
	int** sobel;
	int** binary;
	unsigned int threshold;
	void F_before(void);
	int what_fill;
	afx_msg void OnBrightness();
	afx_msg void OnStretching();
	afx_msg void OnEqualizing();
	afx_msg void Rgbhsito_r();
	afx_msg void Rgbhsito_g();
	afx_msg void Rgbhsito_b();
	void make_gwp(void);
	void make_ghp(void);
};
