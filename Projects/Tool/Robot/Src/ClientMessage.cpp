#include "stdafx.h"
#include "ClientManager.h"
#include "MGRobot.h"
#include "MainFrm.h"
#include "MainView.h"
#include "ClientMessage.h"


namespace MG
{
	//-----------------------------------------------------------------------
	Bool volatile CClientMessage::mOnlyAddMainPlayerMessage = false;
	//-----------------------------------------------------------------------
	CClientMessage::CClientMessage(CClient* client)
	{
		mClient = client;
		mMsgObject.SetSize(MESSAGE_INFORMATION_MAXNUM);
		mSystemFilter = mDebugFilter = mFilterBeforeAdd = false;
		mTotalMessageCounts = mMsgStartIndex = mMsgEndIndex = 0;
		mMsgCurrentIndex = -1;
	}
	//-----------------------------------------------------------------------
	CClientMessage::~CClientMessage()
	{
		ClearAll();
	}
	//-----------------------------------------------------------------------
	void CClientMessage::IndexBoundCorrect(Int &index)
	{
		if (index >= MESSAGE_INFORMATION_MAXNUM)
		{
			index %= MESSAGE_INFORMATION_MAXNUM;
		}
	}
	//-----------------------------------------------------------------------
	Int CClientMessage::GetMessageCount()
	{
		if (mMsgStartIndex<=mMsgEndIndex)
		{
			return mMsgEndIndex-mMsgStartIndex;
		}
		else
		{
			return mMsgEndIndex+MESSAGE_INFORMATION_MAXNUM-mMsgStartIndex;
		}
	}
	//-----------------------------------------------------------------------
	Int CClientMessage::GetNewMessageCount()
	{
		if (mMsgCurrentIndex == -1)
		{
			return GetMessageCount();
		}
		else if (mMsgCurrentIndex < mMsgEndIndex)
		{
			return mMsgEndIndex - mMsgCurrentIndex - 1;
		}
		else
		{
			return mMsgEndIndex + MESSAGE_INFORMATION_MAXNUM - mMsgCurrentIndex - 1;
		}
	}
	//-----------------------------------------------------------------------
	CString CClientMessage::GetCurMsg()
	{
		if (mMsgStartIndex == mMsgEndIndex 
			|| mMsgCurrentIndex == -1)
		{
			return "";
		}
		CClientMessageInfo* msgInfo = reinterpret_cast<CClientMessageInfo*>(mMsgObject.GetAt(mMsgCurrentIndex));
		return msgInfo->GetMessage();
	}
	//-----------------------------------------------------------------------
	COLORREF CClientMessage::GetCurMsgColor()
	{
		if (mMsgStartIndex == mMsgEndIndex 
			|| mMsgCurrentIndex == -1)
		{
			return RGB(255,255,255);
		}
		CClientMessageInfo* msgInfo = reinterpret_cast<CClientMessageInfo*>(mMsgObject.GetAt(mMsgCurrentIndex));
		return msgInfo->GetMessageColor();
	}
	//-----------------------------------------------------------------------
	CClientMessageInfo::MessageType CClientMessage::GetCurMsgType()
	{
		if (mMsgStartIndex == mMsgEndIndex 
			|| mMsgCurrentIndex == -1)
		{
			return CClientMessageInfo::MessageType_Normal;
		}
		CClientMessageInfo* msgInfo = reinterpret_cast<CClientMessageInfo*>(mMsgObject.GetAt(mMsgCurrentIndex));
		return msgInfo->GetMessageType();
	}
	//-----------------------------------------------------------------------
	void CClientMessage::ClearAll()
	{
		int nCount=GetMessageCount();
		for (int i = 0; i < nCount; i++,mMsgStartIndex++)
		{
			IndexBoundCorrect(mMsgStartIndex);
			CClientMessageInfo* msgInfo = reinterpret_cast<CClientMessageInfo*>(mMsgObject.GetAt(mMsgStartIndex));
			MG_SAFE_DELETE(msgInfo);
		}
		mMsgStartIndex = mMsgEndIndex = 0;
		mMsgCurrentIndex = -1;
	}
	//-----------------------------------------------------------------------
	Bool CClientMessage::MoveToNext()
	{
		if (mMsgStartIndex == mMsgEndIndex)
		{
			return false;
		}
		else if (mMsgCurrentIndex == -1)
		{
			mMsgCurrentIndex = mMsgStartIndex;
			return true;
		}
		int nNextIndex = mMsgCurrentIndex + 1;
		IndexBoundCorrect(nNextIndex);
		if (nNextIndex == mMsgEndIndex)
		{
			return false;
		}
		mMsgCurrentIndex = nNextIndex;
		return true;
	}
	//-----------------------------------------------------------------------
	Bool CClientMessage::MoveToBegin()
	{
		if (mMsgCurrentIndex == -1 
			&& mMsgStartIndex == mMsgEndIndex)
		{
			return false;
		}
		mMsgCurrentIndex = mMsgStartIndex;
		return (mMsgStartIndex == mMsgEndIndex) ? false : true;
	}
	//-----------------------------------------------------------------------
	Bool CClientMessage::MoveToNextAvailable()
	{
		while (MoveToNext())
		{
			CClientMessageInfo::MessageType mssageType=GetCurMsgType();
			if ( (mSystemFilter && mssageType==CClientMessageInfo::MessageType_System) 
				|| (mDebugFilter && mssageType==CClientMessageInfo::MessageType_Error))
			{
				continue;
			}
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------------------
	Bool CClientMessage::MoveToFirstAvailable()
	{
		if (!MoveToBegin())
		{
			return false;
		}
		CClientMessageInfo::MessageType tpye=GetCurMsgType();
		if ( (mSystemFilter && tpye==CClientMessageInfo::MessageType_System) 
			|| (mDebugFilter && tpye==CClientMessageInfo::MessageType_Error) )
		{
			return MoveToNextAvailable();
		}
		return true;
	}
	//-----------------------------------------------------------------------
	void CClientMessage::SetSystemMessageFilter(Bool filter)
	{
		mSystemFilter = filter;
	}
	//-----------------------------------------------------------------------
	void CClientMessage::SetDebugMessageFilter(Bool filter)
	{
		mDebugFilter = filter;
	}
	//-----------------------------------------------------------------------
	void CClientMessage::SetFilterBeforeAdd(Bool yes)
	{
		mFilterBeforeAdd = yes;
	}
	//-----------------------------------------------------------------------
	Bool CClientMessage::GetSystemMessageFilter()
	{
		return mSystemFilter;
	}
	//-----------------------------------------------------------------------
	Bool CClientMessage::GetDebugMessageFilter()
	{
		return mDebugFilter;
	}
	//-----------------------------------------------------------------------
	Bool CClientMessage::GetFilterBeforeAdd()
	{
		return mFilterBeforeAdd;
	}
	//-----------------------------------------------------------------------
	void CClientMessage::SetOnlyAddMainPlayerMessage(Bool yes)	//静态函数,设置:仅添加当前用户的信息
	{
		mOnlyAddMainPlayerMessage = yes;
	}
	//-----------------------------------------------------------------------
	Bool CClientMessage::GetOnlyAddMainPlayerMessage()
	{
		return mOnlyAddMainPlayerMessage;
	}
	//-----------------------------------------------------------------------
	Bool CClientMessage::AddMsg(CString str,...)
	{
		mTotalMessageCounts++;
		CString strInfo;
		CString strTemp;
		va_list argList;
		va_start( argList, str );
		strTemp.FormatV(str,argList);
		va_end( argList );
		Str8 temp;
		MG::MGStrOp::toString(mClient->getPlayerName(),temp);
		
		strInfo.Format("账号名 %s,消息总数 %d,内容 %s",temp.c_str(),mTotalMessageCounts,strTemp);
		strInfo=CTime::GetCurrentTime().Format("<%H:%M:%S>")+strInfo;
		strInfo += '\n';
		MG_LOG(out_info,strInfo.GetBuffer());


		/*CClientMessageInfo *pPlayerMessage = MG_NEW CClientMessageInfo(CClientMessageInfo::MessageType_Normal,strInfo);
		CMainView* mainView = ((CMainFrame*)theApp.m_pMainWnd)->GetMainView();
		while (mainView && !mainView->PostMessage(THREAD_MSG_ADD_SYSTEM_MESSAGE,(WPARAM)(LPVOID)mClient,(LPARAM)pPlayerMessage))
		{
			Sleep(10);
			mainView = ((CMainFrame*)theApp.m_pMainWnd)->GetMainView();
		};*/
		return true;
	}
	//-----------------------------------------------------------------------
	Bool CClientMessage::AddSystemMsg(CString str,...)
	{
		mTotalMessageCounts++;
		CString strInfo;
		CString strTemp;
		va_list argList;
		va_start( argList, str );
		strTemp.FormatV(str,argList);
		Str8 temp;
		MG::MGStrOp::toString(mClient->getPlayerName(),temp);
		va_end( argList );
		strInfo.Format("账号名 %s,消息总数 %d,内容 %s",temp.c_str(),mTotalMessageCounts,strTemp);
		strInfo = CTime::GetCurrentTime().Format("<%H:%M:%S>") + strInfo;
		strInfo += '\n';
		MG_LOG(out_info,strInfo.GetBuffer());
		
		/*mTotalMessageCounts++;
		CString strInfo;
		Str8 temp;
		MG::MGStrOp::toString(mClient->getPlayerName(),temp);
		strInfo.Format("账号名 %s,消息总数 %d\n",temp.c_str(),mTotalMessageCounts);
		MG_LOG(out_debug,strInfo.GetBuffer());*/

		/*CClientMessageInfo *pPlayerMessage = MG_NEW CClientMessageInfo(CClientMessageInfo::MessageType_System,strInfo);
		CMainView* mainView = ((CMainFrame*)theApp.m_pMainWnd)->GetMainView();
		while (mainView && !mainView->PostMessage(THREAD_MSG_ADD_SYSTEM_MESSAGE,(WPARAM)(LPVOID)mClient,(LPARAM)pPlayerMessage))
		{
			Sleep(10);
			mainView = ((CMainFrame*)theApp.m_pMainWnd)->GetMainView();
		};*/
		return true;
	}
	//-----------------------------------------------------------------------
	Bool CClientMessage::AddErrorMsg(CString str,...)
	{
		mTotalMessageCounts++;
		CString strInfo;
		CString strTemp;
		va_list argList;
		va_start( argList, str );
		strTemp.FormatV(str,argList);
		Str8 temp;
		MG::MGStrOp::toString(mClient->getPlayerName(),temp);
		va_end( argList );
		strInfo.Format("账号名 %s,消息总数 %d,内容 %s",temp.c_str(),mTotalMessageCounts,strTemp);
		strInfo = CTime::GetCurrentTime().Format("<%H:%M:%S>") + strInfo;
		strInfo += '\n';
		MG_LOG(out_error,strInfo.GetBuffer());

		/*mTotalMessageCounts++;
		CString strInfo;
		Str8 temp;
		MG::MGStrOp::toString(mClient->getPlayerName(),temp);
		strInfo.Format("账号名 %s,消息总数 %d\n",temp.c_str(),mTotalMessageCounts);
		MG_LOG(out_debug,strInfo.GetBuffer());*/

		/*CClientMessageInfo *pPlayerMessage = MG_NEW CClientMessageInfo(CClientMessageInfo::MessageType_Error,strInfo);
		CMainView* mainView = ((CMainFrame*)theApp.m_pMainWnd)->GetMainView();
		while (mainView && !mainView->PostMessage(THREAD_MSG_ADD_SYSTEM_MESSAGE,(WPARAM)(LPVOID)mClient,(LPARAM)pPlayerMessage))
		{
			Sleep(10);
			mainView = ((CMainFrame*)theApp.m_pMainWnd)->GetMainView();
		};*/
		return true;
	}
	//-----------------------------------------------------------------------
	Bool CClientMessage::AddCustomMsg(CClientMessageInfo::MessageType type,COLORREF color,CString str,...)
	{
		mTotalMessageCounts++;
		CString strInfo;
		CString strTemp;
		va_list argList;
		va_start( argList, str );
		strTemp.FormatV(str,argList);
		Str8 temp;
		MG::MGStrOp::toString(mClient->getPlayerName(),temp);
		va_end( argList );
		strInfo.Format("账号名 %s,消息总数 %d,内容 %s\n。",temp.c_str(),mTotalMessageCounts,strTemp);
		strInfo = CTime::GetCurrentTime().Format("<%H:%M:%S>") + strInfo;
		MG_LOG(out_debug,strInfo.GetBuffer());
		/*CClientMessageInfo *pPlayerMessage = MG_NEW CClientMessageInfo(type,strInfo);
		pPlayerMessage->SetMessageColor(color);
		CMainView* mainView = ((CMainFrame*)theApp.m_pMainWnd)->GetMainView();
		while (mainView && !mainView->PostMessage(THREAD_MSG_ADD_SYSTEM_MESSAGE,(WPARAM)(LPVOID)mClient,(LPARAM)pPlayerMessage))
		{
			Sleep(1);
		};*/
		return true;
	}
	//-----------------------------------------------------------------------
	void CClientMessage::AddToMessageArray(CClientMessageInfo* msg)
	{
		mMsgObject.SetAt(mMsgEndIndex,msg);
		IndexBoundCorrect(++mMsgEndIndex);
		if (mMsgEndIndex == mMsgStartIndex)
		{
			if (mMsgCurrentIndex == mMsgStartIndex)
			{
				IndexBoundCorrect(++mMsgCurrentIndex);
			}
			CClientMessageInfo* clientMessage = reinterpret_cast<CClientMessageInfo*>(mMsgObject.GetAt(mMsgStartIndex));
			MG_SAFE_DELETE(clientMessage);
			IndexBoundCorrect(++mMsgStartIndex);
		}
	}
	//-----------------------------------------------------------------------

}

