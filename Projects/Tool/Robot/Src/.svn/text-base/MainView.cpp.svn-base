// F:\work\xh\MGProgram\Trunk\Projects\Robot\Src\MainView.cpp : 实现文件
//

#include "stdafx.h"
#include "MGRobot.h"
#include "MainView.h"
#include "ClientManager.h"
#include "ClientMessageInfo.h"
// CMainView
IMPLEMENT_DYNCREATE(CMainView, CFormView)

CMainView::CMainView()
	: CFormView(CMainView::IDD)
{

}

CMainView::~CMainView()
{
}

void CMainView::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_RICHEDIT21, mRichEditInformation);
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainView, CFormView)
	ON_WM_TIMER()
	ON_MESSAGE(THREAD_MSG_ADD_SYSTEM_MESSAGE, onRefreshMessage)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_MESSAGE, &CMainView::OnBnClickedButtonClearMessage)
END_MESSAGE_MAP()


// CMainView 诊断

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMainView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}



#endif
#endif //_DEBUG

bool CMainView::initView()
{
	/*mLastRefreshTick = 0;
	mRichEditInformation.SetBackgroundColor(FALSE, RGB(0,0, 0));
	mRichEditInformation.ShowScrollBar(SB_BOTH,true);
	UpdateData(FALSE);
	SetTimer(1,500,NULL);*/
	return true;
}
void CMainView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*if (nIDEvent == 1)
	{
		refreshMessage();
		MSG msg;
		while (PeekMessage(&msg,this->m_hWnd,WM_TIMER,WM_TIMER,PM_REMOVE));
	}*/
	CFormView::OnTimer(nIDEvent);
}

LRESULT CMainView::onRefreshMessage( WPARAM wParam,LPARAM lParam )
{
	//--------------------------------------------------------
	/*MG::CClient *client = reinterpret_cast<MG::CClient*>(wParam);
	if (!client)
	{
		return NULL;
	}
	MG::CClientMessageInfo *clientMessageInfo = reinterpret_cast<MG::CClientMessageInfo*>(lParam);
	if(!clientMessageInfo)
	{
		return NULL;
	}
	client->getClientMessage()->AddToMessageArray(clientMessageInfo);*/

	//--------------------------------------------------------
	MG::CClient *client = reinterpret_cast<MG::CClient*>(wParam);
	if (!client)
	{
		return NULL;
	}
	MG::CClientMessageInfo *clientMessageInfo = reinterpret_cast<MG::CClientMessageInfo*>(lParam);
	if(!clientMessageInfo)
	{
		return NULL;
	}
	CHARFORMAT cf;
	cf.cbSize=sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR;
	cf.crTextColor = clientMessageInfo->GetMessageColor();
	cf.dwEffects = 0;
	mRichEditInformation.SetSel(-1,-1);
	mRichEditInformation.SetWordCharFormat(cf);
	mRichEditInformation.ReplaceSel(clientMessageInfo->GetMessage()+"\n");
	MG_DELETE(clientMessageInfo);
	if (mRichEditInformation.GetLineCount() > 1000)
	{
		mRichEditInformation.SetWindowText("");
	}
	return NULL;
}

void CMainView::refreshMessage()
{
	/*if (m_ScrollLock.GetCheck()==BST_CHECKED)
	{
		return;
	}
	CPlayer *pPlayer=CPlayerMgr::GetMainPlayer();
	if (!pPlayer)
	{
		return;
	}*/
	
	MG::CClient* client = NULL;
	int i = 1;
	//获取client
	std::map<MG::I32,MG::CClient*>* dataSet = MG::ClientManager::getInstance().getDataSet();
	if (!dataSet || dataSet->empty())
	{
		return;
	}

	//各种模式 显示
	//a
	std::map<MG::I32,MG::CClient*>::iterator it = dataSet->begin();
	for (; it != dataSet->end(); it++)
	{
		client = it->second;
		if (client)
		{
			MG::CClientMessage *clientMessage = client->getClientMessage();
			if (!clientMessage)
			{
				return;
			}
			int nCount= clientMessage->GetNewMessageCount();
			if (nCount <= 0)
				return;

				mRichEditInformation.SetSel(-1,-1);
				while(clientMessage->MoveToNextAvailable())
				{
					if (mRichEditInformation.GetLineCount() > MESSAGE_VISIBLE_MAXNUM)
					{
						int nCharCount=0;
						for (int i = 0; i < nCount + 20; i++)
						{
							nCharCount += mRichEditInformation.LineLength(i)+1;
						}
						//m_RichEditInformation.LockWindowUpdate();
						mRichEditInformation.SetSel(0,nCharCount);
						mRichEditInformation.ReplaceSel(NULL);
						mRichEditInformation.SetSel(-1,-1);
						//m_RichEditInformation.UnlockWindowUpdate();
					}
					CHARFORMAT cf;
					cf.cbSize=sizeof(CHARFORMAT);
					cf.dwMask = CFM_COLOR;
					cf.crTextColor = clientMessage->GetCurMsgColor();
					cf.dwEffects=0;
					mRichEditInformation.SetWordCharFormat(cf);
					mRichEditInformation.ReplaceSel(clientMessage->GetCurMsg()+"\n");
				}
			}
		}
	
	//b

}

void CMainView::refreshAllMessages()
{

}

void CMainView::OnBnClickedButtonClearMessage()
{
	// TODO: 在此添加控件通知处理程序代码
	mRichEditInformation.SetWindowText("\n");
}
