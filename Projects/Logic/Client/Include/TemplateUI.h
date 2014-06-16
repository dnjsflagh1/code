//*************************************************************************************
#ifndef _TemplateUI_H_584jf_
#define _TemplateUI_H_584jf_
//*************************************************************************************
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
    class  TemplateUI:public UIObject
    {
    public:
        TemplateUI();
        virtual ~TemplateUI();
        SINGLETON_INSTANCE(TemplateUI);
    public:
        virtual void setEvent();
        virtual void update();

    public:
        static void onClickButton1(void* widget);
        static void onClickButton2(void* widget);
        static void onClickButton3(void* widget);
        static void onClickButton4(void* widget);
        static void onClickWindowClose(void* widget);
        static void onSelectAcceptEvent(void* widget);
        static void onPressText(void* widget, int x, int y, MouseCode id);
        static void onReleaseImage(void* widget, int x, int y, MouseCode id);
        static void onClickTreeNode(void* widget);
        static void onClickMixlist(void* widget, int index);
        static void onClickMixListCheckBox(void* widget);
		static void onCDEvent(void* widget, int timeouttime);
		static void onImageCDEvent(void* widget, int lastFrame);
    protected:
        void insertText(std::wstring text);

    private:
        void addNode();
        void deleteNode();
        void addLeaf();
        void deleteLeaf();
        void showNodeInfo();
		void setCDEvent(int timeouttime);
		void addCDEvent();
		void openImageCD(int timeouttime);

    private:
        int     mIndex;
    };
}

#endif