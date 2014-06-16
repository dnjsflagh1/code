// NetStatesTab.cpp : implementation file
//

#include "stdafx.h"
#include "ServerLauncher.h"
#include "NetStatesTab.h"
#include "ServerLauncherDlg.h"

extern char g_szWorkPath[MAX_PATH];
// NetStatesTab dialog

IMPLEMENT_DYNAMIC(NetStatesTab, CDialog)

NetStatesTab::NetStatesTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(NetStatesTab::IDD, pParent)
{
	mSelfID = 0;
}

NetStatesTab::~NetStatesTab()
{
}

void NetStatesTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);

	//CString		mServerSendSpeedBytes;
	//CString		mServerSendBytes;
	//CString		mServerSendSpeedPackets;
	//CString		mServerSendPackets;
	//CString		mServerCount;

	//CString		mClientSendSpeedBytes;
	//CString		mClientSendBytes;
	//CString		mClientSendSpeedPackets;
	//CString		mClientSendPackets;
	//CString		mClientCount;

	DDX_Text(pDX, IDC_ET_SERVER_SEND_SPEED_BYTES, mServerSendSpeedBytes);
	DDX_Text(pDX, IDC_ET_SERVER_SEND_BYTES, mServerSendBytes);
	DDX_Text(pDX, IDC_ET_SERVER_SEND_SPEED_PACKETS, mServerSendSpeedPackets);
	DDX_Text(pDX, IDC_ET_SERVER_SEND_PACKETS, mServerSendPackets);
	DDX_Text(pDX, IDC_ET_SERVER_RECV_SPEED_BYTES, mServerRecvSpeedBytes);
	DDX_Text(pDX, IDC_ET_SERVER_RECV_BYTES, mServerRecvBytes);
	DDX_Text(pDX, IDC_ET_SERVER_RECV_SPEED_PACKETS, mServerRecvSpeedPackets);
	DDX_Text(pDX, IDC_ET_SERVER_RECV_PACKETS, mServerRecvPackets);

	DDX_Text(pDX, IDC_ET_SERVER_COUNT, mServerCount);
	
	DDX_Text(pDX, IDC_ET_CLIENT_SEND_SPEED_BYTES, mClientSendSpeedBytes);
	DDX_Text(pDX, IDC_ET_CLIENT_SEND_BYTES, mClientSendBytes);
	DDX_Text(pDX, IDC_ET_CLIENT_SEND_SPEED_PACKETS, mClientSendSpeedPackets);
	DDX_Text(pDX, IDC_ET_CLIENT_SEND_PACKETS, mClientSendPackets);
	DDX_Text(pDX, IDC_ET_CLIENT_RECV_SPEED_BYTES, mClientRecvSpeedBytes);
	DDX_Text(pDX, IDC_ET_CLIENT_RECV_BYTES, mClientRecvBytes);
	DDX_Text(pDX, IDC_ET_CLIENT_RECV_SPEED_PACKETS, mClientRecvSpeedPackets);
	DDX_Text(pDX, IDC_ET_CLIENT_RECV_PACKETS, mClientRecvPackets);

	DDX_Text(pDX, IDC_ET_CLIENT_COUNT, mClientCount);

}


BEGIN_MESSAGE_MAP(NetStatesTab, CTabPageSSL)
END_MESSAGE_MAP()


// NetStatesTab message handlers
BOOL NetStatesTab::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	return TRUE;
}

void NetStatesTab::updateDate(LuanchUpdateInfo *updateInfo,MG::I32 count)
{
	if (count == 2)
	{
		mServerSendSpeedBytes.Format(	L"%f",updateInfo[0].sendSpeedBytes);
		mServerSendBytes.Format(		L"%d",updateInfo[0].sendBytes);
		mServerSendSpeedPackets.Format(	L"%f",updateInfo[0].sendSpeedPackets);
		mServerSendPackets.Format(		L"%d",updateInfo[0].sendPackets);

		mServerRecvSpeedBytes.Format(	L"%f",updateInfo[0].recvSpeedBytes);
		mServerRecvBytes.Format(		L"%d",updateInfo[0].recvBytes);
		mServerRecvSpeedPackets.Format(	L"%f",updateInfo[0].recvSpeedPackets);
		mServerRecvPackets.Format(		L"%d",updateInfo[0].recvPackets);
		mServerCount.Format(			L"%d",updateInfo[0].currConnectionCount);

		mClientSendSpeedBytes.Format(	L"%f",updateInfo[1].sendSpeedBytes);
		mClientSendBytes.Format(		L"%d",updateInfo[1].sendBytes);
		mClientSendSpeedPackets.Format(	L"%f",updateInfo[1].sendSpeedPackets);
		mClientSendPackets.Format(		L"%d",updateInfo[1].sendPackets);

		mClientRecvSpeedBytes.Format(	L"%f",updateInfo[1].recvSpeedBytes);
		mClientRecvBytes.Format(		L"%d",updateInfo[1].recvBytes);
		mClientRecvSpeedPackets.Format(	L"%f",updateInfo[1].recvSpeedPackets);
		mClientRecvPackets.Format(		L"%d",updateInfo[1].recvPackets);
		mClientCount.Format(			L"%d",updateInfo[1].currConnectionCount);
	}else if(count == 1)
	{
		mServerSendSpeedBytes.Format(	L"%f",updateInfo[0].sendSpeedBytes);
		mServerSendBytes.Format(		L"%d",updateInfo[0].sendBytes);
		mServerSendSpeedPackets.Format(	L"%f",updateInfo[0].sendSpeedPackets);
		mServerSendPackets.Format(		L"%d",updateInfo[0].sendPackets);

		mServerRecvSpeedBytes.Format(	L"%f",updateInfo[0].recvSpeedBytes);
		mServerRecvBytes.Format(		L"%d",updateInfo[0].recvBytes);
		mServerRecvSpeedPackets.Format(	L"%f",updateInfo[0].recvSpeedPackets);
		mServerRecvPackets.Format(		L"%d",updateInfo[0].recvPackets);
		mServerCount.Format(			L"%d",updateInfo[0].currConnectionCount);
	}

	UpdateData(FALSE);
}

