#pragma once


// CInfoSetting dialog

class CInfoSetting : public CDialog
{
	DECLARE_DYNAMIC(CInfoSetting)

public:
	CInfoSetting(CWnd* pParent = NULL, 
		unsigned int=50, unsigned int=50, unsigned int=15,
		unsigned int=0, unsigned int=0, double=0.0, unsigned int=0, unsigned int=0, unsigned int=0);   // standard constructor
	virtual ~CInfoSetting();

// Dialog Data
	enum { IDD = IDD_INFOSETTINGS };

	unsigned int Rows;
	unsigned int Cols;
	unsigned int AntNum;

	//settings for Evolution
	unsigned int PopCount;
	unsigned int SelectionSize;
	double MutRate;
	unsigned int MaxDepth;
	unsigned int TimeClicks;
	unsigned int CrossDepth;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CEdit* RowEdit;
	CEdit* ColEdit;
	CEdit* AntNumEdit;
	CEdit* PopCountEdit;
	CEdit* SelectionSizeEdit;
	CEdit* MutRateEdit;
	CEdit* MaxdepthEdit;
	CEdit* TimeClickEdit;
	CEdit*  CrossDepthClickEdit;

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEdit1();
};
