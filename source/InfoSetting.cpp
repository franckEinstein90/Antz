// InfoSetting.cpp : implementation file
//

#include "stdafx.h"
#include "Assignment2.h"
#include "InfoSetting.h"
#include ".\infosetting.h"


// CInfoSetting dialog

IMPLEMENT_DYNAMIC(CInfoSetting, CDialog)
CInfoSetting::CInfoSetting(CWnd* pParent /*=NULL*/, 
			   unsigned int rows, unsigned  int cols, unsigned int antNum,
			   unsigned int popCount, unsigned int selsize, double mutrate, unsigned int MDepth, unsigned int timeClicks, unsigned int  crossDepth):
CDialog(CInfoSetting::IDD, pParent), 
Rows(rows), Cols(cols), AntNum(antNum),
PopCount(popCount), SelectionSize(selsize),MutRate(mutrate), MaxDepth(MDepth), TimeClicks(timeClicks), CrossDepth(crossDepth)
{
	
}

CInfoSetting::~CInfoSetting()
{
}

void CInfoSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInfoSetting, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CInfoSetting message handlers

void CInfoSetting::OnBnClickedOk()
{
	
	CString t;
	RowEdit->GetWindowText(t);
	stringstream trad1;
	trad1<<(LPCTSTR) t;
	trad1>>Rows;

	trad1.clear();
	ColEdit->GetWindowText(t);
	trad1<<(LPCTSTR) t;
	trad1>>Cols;
	
	trad1.clear();
	AntNumEdit->GetWindowText(t);
	trad1<<(LPCTSTR) t;
	trad1>>AntNum;


	trad1.clear();
	PopCountEdit->GetWindowText(t);
	trad1<<(LPCTSTR) t;
	trad1>>PopCount;

	
	trad1.clear();
	MutRateEdit->GetWindowText(t);
	trad1<<(LPCTSTR) t;
	trad1>>MutRate;

	
	trad1.clear();
	MaxdepthEdit->GetWindowText(t);
	trad1<<(LPCTSTR) t;
	trad1>>MaxDepth;

	trad1.clear();
	SelectionSizeEdit->GetWindowText(t);
	trad1<<(LPCTSTR) t;
	trad1>>SelectionSize;
	
	trad1.clear();
	TimeClickEdit->GetWindowText(t);
	trad1<<(LPCTSTR) t;
	trad1>>TimeClicks;
	OnOK();


	trad1.clear();
	CrossDepthClickEdit->GetWindowText(t);
	trad1<<(LPCTSTR) t;
	trad1>>CrossDepth;
}

BOOL CInfoSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	RowEdit	= (CEdit*) GetDlgItem(IDC_ROWS);
	ColEdit	= (CEdit*) GetDlgItem(IDC_COLS);
	AntNumEdit = (CEdit*) GetDlgItem(IDC_ANTNUM);

	PopCountEdit = (CEdit*) GetDlgItem(IDC_POPCOUNT);
	MutRateEdit  = (CEdit*) GetDlgItem(ID_MUTRATE);
	MaxdepthEdit  = (CEdit*) GetDlgItem(IDC_MAXDEPTH);
	TimeClickEdit = (CEdit*) GetDlgItem(IDC_TICLICKS);
	CrossDepthClickEdit = (CEdit*) GetDlgItem(IDC_CROSSDEPTH);
	SelectionSizeEdit = (CEdit*)GetDlgItem(IDC_SELECT);	

	CString temp;
	temp.Format(_T("%d"), Rows);
	RowEdit->SetWindowText(temp);
	temp.Format(_T("%d"), Cols);
	ColEdit->SetWindowText(temp);
	temp.Format(_T("%d"), AntNum);
	AntNumEdit->SetWindowText(temp);

	temp.Format(_T("%d"), PopCount);
	PopCountEdit->SetWindowText(temp);
	temp.Format(_T("%f "), MutRate);
	MutRateEdit->SetWindowText(temp);
	temp.Format(_T("%d"), MaxDepth);
	MaxdepthEdit->SetWindowText(temp);
	temp.Format(_T("%d"), TimeClicks);
	TimeClickEdit->SetWindowText(temp);
	temp.Format(_T("%d"), CrossDepth);
	CrossDepthClickEdit->SetWindowText(temp);
	temp.Format(_T("%d"), SelectionSize);
	SelectionSizeEdit->SetWindowText(temp);





	return TRUE;  
	
	
	// return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}













