#pragma once
#include "resource.h"
#include "LoginPage.h"
#include "OperatePage.h"
#include "CampaignPage.h"
// CItemView 窗体视图

class CItemView : public CFormView
{
	DECLARE_DYNCREATE(CItemView)

protected:
	CItemView();           // 动态创建所使用的受保护的构造函数
	virtual ~CItemView();

public:
	enum { IDD = IDD_ITEM_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	
	bool initView();
	CPropertySheet	mSheetControl;
	CLoginPage		mLoginPage;
	COperatePage	mOperatePage;
	CCampaignPage	mCampaignPage;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

};


