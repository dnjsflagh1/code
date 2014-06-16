//***************************************************************************************************
#ifndef _H_UIMAINFUNCTION_
#define _H_UIMAINFUNCTION_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    class UIMainFunciton : public UIObject
    {
    public:
        UIMainFunciton();
        ~UIMainFunciton();
        SINGLETON_INSTANCE(UIMainFunciton);

    public:
        virtual void setEvent();

	private:
		/*

		*/
		static void OnClickClanInfo(void* widget);
        static void OnClickCampaign(void* widget);
		static void OnClickTaskInfo(void* widget);
		static void OnClickForce(void* widget);
		static void OnClickFriendsInfo(void* widget);
		static void OnClickSystemInfo(void* widget);


    protected:
    private:
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************