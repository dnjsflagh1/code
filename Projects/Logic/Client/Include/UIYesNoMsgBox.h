//*************************************************************************************
#ifndef _UIYESNOMSGBOX_H_
#define _UIYESNOMSGBOX_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
	class  UIYesNoMsgBox : public UIObject
	{
	public:
		UIYesNoMsgBox();
		virtual ~UIYesNoMsgBox(){;}
		SINGLETON_INSTANCE(UIYesNoMsgBox);

	public:
		virtual void    setEvent();

	public:    //打开消息框，并设置消息框内容
		void    showHint(
			std::wstring msgTtSec, std::wstring msgTtKey, std::wstring defaultTt, 
			std::wstring msgConSec, std::wstring msgConKey, std::wstring defaultCon,
			void* userConfirm = NULL, PVOID_CALLBACK funcConfirm = NULL,
			void* userCansel = NULL, PVOID_CALLBACK funcCansel = NULL
			);
		void    showHint(
			Str16 title,Str16 content,
			void* userConfirm = NULL, PVOID_CALLBACK funcConfirm = NULL,
			void* userCansel = NULL, PVOID_CALLBACK funcCansel = NULL
			);

	public:    //按下确定按钮触发的事件
		static  void    onclickConfirm(void* widget);
		static  void    onclickCansel(void* widget);

	protected: //调用回调函数
		void    callConfirm();
		void    callCansel();

	protected:
		PVOID_CALLBACK      mpFuncConfirm;
		void*               mpUserConfirm; 
		PVOID_CALLBACK      mpFuncCansel;
		void*               mpUserCansel;
	private:
		Int                 getEditBoxWidth();
		Int                 getEditBoxHeight();

	};
}

#endif