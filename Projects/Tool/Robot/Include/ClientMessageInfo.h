#ifndef _CLIENTMESSAGEINFO_H_
#define _CLIENTMESSAGEINFO_H_

namespace MG
{
	class CClientMessageInfo
	{
	public:
		//输出信息的类型
		enum MessageType
		{	
			MessageType_Normal	= 0,			//普通级别
			MessageType_System	= 1,			//系统级别
			MessageType_Error	= 2,			//调试级别
		};

		CClientMessageInfo(MessageType msgType,CString str);
		~CClientMessageInfo(void);

		void		SetMessageType(MessageType eMsgType);
		void		SetMessage(CString strMsg);
		void		SetMessageColor(COLORREF color);

		MessageType GetMessageType();
		CString		GetMessage();
		COLORREF	GetMessageColor();

	private:
		const static COLORREF	mColorTable[3];
		MessageType				mMessageType;
		CString					mMessage;
		COLORREF				mColor;
	};
}

#endif //_CLIENTMESSAGEINFO_H_