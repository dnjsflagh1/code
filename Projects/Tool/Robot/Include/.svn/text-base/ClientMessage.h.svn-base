#ifndef _CLIENTMESSAGE_H_
#define _CLIENTMESSAGE_H_
#include "ClientMessageInfo.h"

namespace MG
{
	class CClientMessage
	{
	public:
		CClientMessage(CClient* client);
		~CClientMessage();

		Int									GetMessageCount();
		Int									GetNewMessageCount();
		CString								GetCurMsg();
		COLORREF							GetCurMsgColor();
		CClientMessageInfo::MessageType		GetCurMsgType();
		Bool								GetSystemMessageFilter();
		Bool								GetDebugMessageFilter();
		Bool								GetFilterBeforeAdd();
		static Bool							GetOnlyAddMainPlayerMessage();

		void								ClearAll();
		Bool								MoveToNext();						// 不带参数过滤检查的索引移动,返回 : true代表有消息 false代表没消息
		Bool								MoveToBegin();						// 不带参数过滤检查的索引移动,返回 : true代表有消息 false代表没消息
		Bool								MoveToNextAvailable();				// 带参数过滤检查的索引移动,返回 : true代表有消息 false代表没消息且指针会移动到最后
		Bool								MoveToFirstAvailable();				// 带参数过滤检查的索引移动,返回 : true代表有消息 false代表没消息且指针会移动到最后
		void								SetSystemMessageFilter(Bool filter);
		void								SetDebugMessageFilter(Bool filter);
		void								SetFilterBeforeAdd(Bool yes);			// 在添加信息前判断是否过滤消息
		static void							SetOnlyAddMainPlayerMessage(Bool yes);	// 仅添加当前用户的信息

		Bool								AddMsg(CString str,...);				// 添加一般信息,可能失败(返回false)
		Bool								AddSystemMsg(CString str,...);			// 添加系统消息,受m_bFilterBeforeAdd和m_bSystemFilter影响,可能失败(返回false)
		Bool								AddErrorMsg(CString str,...);			// 添加调试消息,受m_bFilterBeforeAdd和m_bDebugFilter影响,可能失败(返回false)
		Bool								AddCustomMsg(CClientMessageInfo::MessageType type,COLORREF color,CString str,...);	//添加定制消息,受输入参数type和内部参数m_bFilterBeforeAdd,m_bSystemFilter和m_bDebugFilter影响,可能失败(返回false)
		void								AddToMessageArray(CClientMessageInfo* msg);// 把消息加入到数组

	private:
		inline void							IndexBoundCorrect(Int &index);	//修正超出范围的索引值,使其数值回绕(环形数组)

	private:
		static Bool volatile mOnlyAddMainPlayerMessage;
		CClient*		mClient;
		CPtrArray		mMsgObject;
		Int				mMsgStartIndex;		//指向数组的开始,可能有效,也可能无效(m_nMsgStartIndex==m_nMsgEndIndex时无效)
		Int				mMsgCurrentIndex;		//指向当前索引值,范围在m_nMsgStartIndex和m_nMsgEndIndex之间,当m_nMsgCurrentIndex==m_nMsgEndIndex时,此值无效
		Int				mMsgEndIndex;			//永远指向一个不存在数值的新的数组索引
		Bool			mSystemFilter;
		Bool			mDebugFilter;
		Bool			mFilterBeforeAdd;
		UInt			mTotalMessageCounts;
	};
}


#endif // _CLIENTMESSAGE_H_

