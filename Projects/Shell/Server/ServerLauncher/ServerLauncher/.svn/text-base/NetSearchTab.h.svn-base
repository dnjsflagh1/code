#pragma once
#include "TabPageSSL.h"
#include "afxcmn.h"
#include "afxwin.h"

/// NetSearchTab dialog

class NetSearchTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(NetSearchTab)

public:
	NetSearchTab(CWnd* pParent = NULL);   // standard constructor
	virtual ~NetSearchTab();

	// Dialog Data
	enum { IDD = IDD_LUANCHER_SEARCH_DLG };
public:


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int			mSelfID;
	CListCtrl	mList;
};