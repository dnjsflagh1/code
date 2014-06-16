// MainFrm.h : CMainFrame 类的接口
//


#pragma once

#include "FixedSplitter.h"
class COnceOpPage;
class CRepeatetlyRandomOpPage;
class CRepeatedlyOrderOpPage;
class CItemView;
class CMainView;
class CLoginPage;
class CCampaignPage;
class CNewMainView;
class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame);
public:
	CItemView*			GetItemView();
	CMainView*			GetMainView();
	CLoginPage*			GetLoginPage();
	CCampaignPage*		GetCampaignPage();
	
	CNewMainView*				GetNewView();
	COnceOpPage*				GetOnceOpPage();
	CRepeatetlyRandomOpPage*	GetRepeatetlyRandomOpPage();
	CRepeatedlyOrderOpPage*		GetRepeatedlyOrderOpPage();

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	
protected:  
	// 控件条嵌入成员
	CFixedSplitter		mWndSplitter;
	CItemView*			mItemView;
	CNewMainView*		mNewMainView;

protected:
	// 生成的消息映射函数
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnSetFocus(CWnd *pOldWnd);
	afx_msg void		OnGetMinMaxInfo( MINMAXINFO  *info); 
	afx_msg void		OnClose();
	afx_msg LRESULT		OnNcHitTest(CPoint point);
	afx_msg void		OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
};


