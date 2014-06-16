#pragma once
#include "TabPageSSL.h"
#include "afxcmn.h"
#include "afxwin.h"

/// NetStatesTab dialog

class NetStatesTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(NetStatesTab)

public:
	NetStatesTab(CWnd* pParent = NULL);   // standard constructor
	virtual ~NetStatesTab();

	// Dialog Data
	enum { IDD = IDD_LUANCHER_NET_STATES_DLG };
public:
	void updateDate(LuanchUpdateInfo *updateInfo,MG::I32 count);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int			mSelfID;

	CString		mServerSendSpeedBytes;
	CString		mServerSendBytes;
	CString		mServerSendSpeedPackets;
	CString		mServerSendPackets;

	CString		mServerRecvSpeedBytes;
	CString		mServerRecvBytes;
	CString		mServerRecvSpeedPackets;
	CString		mServerRecvPackets;

	CString		mServerCount;

	CString		mClientSendSpeedBytes;
	CString		mClientSendBytes;
	CString		mClientSendSpeedPackets;
	CString		mClientSendPackets;

	CString		mClientRecvSpeedBytes;
	CString		mClientRecvBytes;
	CString		mClientRecvSpeedPackets;
	CString		mClientRecvPackets;

	CString		mClientCount;


};