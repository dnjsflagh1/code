//*************************************************************************************
#ifndef _UIEDITYESNOMSGBOX_H_
#define _UIEDITYESNOMSGBOX_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
	class  UIEditYesNoMsgBox : public UIObject
	{
	public:
		UIEditYesNoMsgBox();
		virtual ~UIEditYesNoMsgBox(){;}
		SINGLETON_INSTANCE(UIEditYesNoMsgBox);

	public:
		virtual void    setEvent();

	public:    //打开消息框，并设置消息框内容
		void    showHint(
			std::wstring msgTtSec, std::wstring msgTtKey, std::wstring defaultTt, 
			std::wstring msgConSec, std::wstring msgConKey, std::wstring defaultCon,Int maxCount,
			void* userConfirm = NULL, PVOIDINTINT_CALLBACK funcConfirm = NULL,
			void* userCancel = NULL, PVOID_CALLBACK funcCancel = NULL
			);
		void    showHint(
			Str16 title,Str16 content,Int maxCount,
			void* userConfirm = NULL, PVOIDINTINT_CALLBACK funcConfirm = NULL,
			void* userCancel = NULL, PVOID_CALLBACK funcCancel = NULL
			);

	public:    //按下确定按钮触发的事件
		static  void    onclickConfirm(void* widget);
		static  void    onclickCancel(void* widget);

	protected: //调用回调函数
		void    callConfirm();
		void    callCancel();

	protected:
		PVOIDINTINT_CALLBACK      mpFuncConfirm;
		void*               mpUserConfirm; 
		PVOID_CALLBACK      mpFuncCancel;
		void*               mpUserCancel;
		Int					mInputCount;
		Int					mMaxCount;

	};
}

#endif