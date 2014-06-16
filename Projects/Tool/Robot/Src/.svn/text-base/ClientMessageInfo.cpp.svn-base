#include "stdafx.h"
#include "ClientMessageInfo.h"

namespace MG
{
	//-----------------------------------------------------------------------
	const COLORREF CClientMessageInfo::mColorTable[3]=
	{
		RGB(255,255,255),
		RGB(255,255,128),
		RGB(255,125,125)
	};
	//-----------------------------------------------------------------------
	CClientMessageInfo::CClientMessageInfo(MessageType msgType,CString str)
	{
		mMessage		= str;
		mMessageType	= msgType;
		mColor			= 0;
	}
	//-----------------------------------------------------------------------
	CClientMessageInfo::~CClientMessageInfo(void)
	{
	}
	//-----------------------------------------------------------------------
	void CClientMessageInfo::SetMessageType(MessageType msgType)
	{
		mMessageType = msgType;
	}
	//-----------------------------------------------------------------------
	void CClientMessageInfo::SetMessage(CString msg)
	{
		mMessage = msg;
	}
	//-----------------------------------------------------------------------
	void CClientMessageInfo::SetMessageColor(COLORREF color)
	{
		mColor = color;
	}
	//-----------------------------------------------------------------------
	CClientMessageInfo::MessageType CClientMessageInfo::GetMessageType()
	{
		return mMessageType;
	}
	//-----------------------------------------------------------------------
	CString CClientMessageInfo::GetMessage()
	{
		return mMessage;
	}
	//-----------------------------------------------------------------------
	COLORREF CClientMessageInfo::GetMessageColor()
	{
		if (mColor > 0)
		{
			return mColor;
		}
		return mColorTable[mMessageType];
	}
	//-----------------------------------------------------------------------
}


