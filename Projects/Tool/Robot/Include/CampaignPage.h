#pragma once
#include "afxwin.h"
#include "CommonGameDefine.h"

// CCampaignPage dialog

class CCampaignPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCampaignPage)

public:
	CCampaignPage();
	virtual ~CCampaignPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_CAMPAIGN };
	virtual BOOL OnSetActive();
	enum CREATE_OPERATE
	{ 
		ONCE_CREATE_CAMPAGIN =1,CONTINUOUS_CREATE_CAMPAGIN 
	};


	void uiFlash();
	void handleCreateCampagin(CREATE_OPERATE create_operate);
	void OnlyCreateCampaginData();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCreateCampagin();
	afx_msg void OnBnClickedBtnDestoryCampagin();
	CComboBox mCombCreateCampaign;
	afx_msg void OnCbnSelchangeComb0Created();
	CComboBox mCombCanntCreateCampaign;
	std::vector<MG::RegionIdType> mCanCreateRegion;
	std::vector<MG::RegionIdType> mCanntCreateRegion;
	afx_msg void OnBnClickedBtnStratCampagin();
};
