
// mymfcDoc.h : CmymfcDoc Ŭ������ �������̽�
//


#pragma once


class CmymfcDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CmymfcDoc();
	DECLARE_DYNCREATE(CmymfcDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CmymfcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileOpen(); // ���� ����
	afx_msg void OnFileSave(); // ���� ����
	afx_msg void OnFilterBinary(); // ���̳ʸ� ����
	afx_msg void OnFilterGrey(); // �׷��� ����
	afx_msg void OnFilterSobel(); // �Һ� ����
	afx_msg void OnFiltervalue(); // �Ӱ谪 ���̾�α�
	afx_msg void OnFileNew();


	void make_hp(void);
	void make_wp(void);
	void make_grey(void);
	void load_grey(void);
	void get_rgb(void);
	void make_histogram(int max);
	void OnHistogram(int);

	CImage m_lmg; // �ҷ��� �̹���
	CImage f_Img; // ���Ͱ�ģ �̹���
	CImage h_Img; // ������׷� �̹���
	CImage widthp_Img; // ���� �������� �̹���
	CImage heightp_Img; // ���� �������� �̹���
	CImage RGBhistogram; //rgb ������׷� �̹���

	int what_color;
	bool flag; // ���� �÷���
	int histo[256]; // ������׷� �迭
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
