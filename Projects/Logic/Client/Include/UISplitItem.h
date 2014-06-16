//*************************************************************************************
#ifndef _UISplitItem_H_
#define _UISplitItem_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
	class  UISplitItem : public UIObject
	{
	public:
		UISplitItem();
		virtual ~UISplitItem(){;}
		SINGLETON_INSTANCE(UISplitItem);

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
		static  void    onClickBtnLeft(void* widget);
		static  void    onClickBtnRight(void* widget);
		static  void    onInputSplitTextChange(void* widget);

	protected: //调用回调函数
		void    callConfirm();
		void    callCancel();

	protected:
		PVOIDINTINT_CALLBACK      mpFuncConfirm;
		void*               mpUserConfirm; 
		PVOID_CALLBACK      mpFuncCancel;
		void*               mpUserCancel;
		Int					mInputSplitCount;
		Int					mMaxCount;
	private:
		void init();
		void setAutoNumberEnabled(U32 index, bool enable);
		void setEditCountValue();  //系统修正输入框的值

	};
}

#endif