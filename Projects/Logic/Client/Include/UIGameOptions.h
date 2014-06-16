//*****************************************************************************************************************
#ifndef _H_UIGAMEOPTIONS_
#define _H_UIGAMEOPTIONS_
//*****************************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*****************************************************************************************************************
namespace MG
{
    

    class UIGameOptions : public UIObject
    {
    public:
        UIGameOptions(){;}
        ~UIGameOptions(){;}
        SINGLETON_INSTANCE(UIGameOptions);

    public:
        virtual void setEvent();

    protected:
    private:
        static void onClickExit(void* widget);
		static void onClickRlogin(void* widget);
		static void onClickReturn(void* widget);
		static void onClickFuncSet(void* widget);
		static void onClickVideoSet(void* widget);
		static void onClickAudioSet(void* widget);
		static void onClickNetworkSet(void* widget);
		static void	exitGame(void* arg);
		static void reLogin(void* arg);

    };
}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************