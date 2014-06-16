// MainFrm.h : CMainFrame ��Ľӿ�
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

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	
protected:  
	// �ؼ���Ƕ���Ա
	CFixedSplitter		mWndSplitter;
	CItemView*			mItemView;
	CNewMainView*		mNewMainView;

protected:
	// ���ɵ���Ϣӳ�亯��
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnSetFocus(CWnd *pOldWnd);
	afx_msg void		OnGetMinMaxInfo( MINMAXINFO  *info); 
	afx_msg void		OnClose();
	afx_msg LRESULT		OnNcHitTest(CPoint point);
	afx_msg void		OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
};


