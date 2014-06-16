#pragma once


// CCampaignOpPage dialog

class CCampaignOpPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCampaignOpPage)

public:
	CCampaignOpPage();
	virtual ~CCampaignOpPage();

// Dialog Data
	enum { IDD = IDD_CAMPAIGN_OP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCampSetting();
};
