#pragma once
#include "resource.h"
#include "SettingPage.h"
#include "OnceOpPage.h"
#include "RepeatetlyRandomOpPage.h"
#include "RepeatedlyOrderOpPage.h"
#include "CampaignOpPage.h"
// CNewMainView form view

class CNewMainView : public CFormView
{
	DECLARE_DYNCREATE(CNewMainView)

protected:
	CNewMainView();           // protected constructor used by dynamic creation
	virtual ~CNewMainView();

public:
	enum { IDD = IDD_NEW_MAIN_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	bool initView();
public:
	CPropertySheet				mSheetControl;
	CSettingPage				mSettingPage;
	COnceOpPage					mOnceOpPage;
	CRepeatetlyRandomOpPage		mRandomOpPage;
	CRepeatedlyOrderOpPage		mOrderOpPage;
	CCampaignOpPage				mCampaignOpPage;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

};


