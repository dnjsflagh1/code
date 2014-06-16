//*************************************************************************************
#ifndef _UIMESSAGEBOX_H_578439hjk_
#define _UIMESSAGEBOX_H_578439hjk_
//*************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
    class  UIMessageBox : public UIObject
    {
    public:
                UIMessageBox();
        virtual ~UIMessageBox();
                SINGLETON_INSTANCE(UIMessageBox);

    public:
        virtual void    setEvent();

    public:    //打开消息框，并设置消息框内容
        void    showHint(
                            std::wstring msgTtSec, std::wstring msgTtKey, std::wstring defaultTt, 
                            std::wstring msgConSec, std::wstring msgConKey, std::wstring defaultCon,
                            void* userConfirm = NULL, PVOID_CALLBACK funcConfirm = NULL
                         );

		void    showHint(std::wstring msg );

    public:    //按下确定按钮触发的事件
        static  void    onclickConfirm(void* widget);
        //static  void    onclickCansel(void* widget);

    protected: //调用回调函数
                void    callConfirm();
                //void    callCansel();

    protected:
        PVOID_CALLBACK      mpFuncConfirm;
        void*               mpUserConfirm; 
        //PVOID_CALLBACK      pFuncCansel;
        //void*               pUserCansel;
	private:
		Int                 getEditBoxWidth();
		Int                 getEditBoxHeight();

    };
}

#endif