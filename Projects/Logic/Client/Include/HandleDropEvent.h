//********************************************************************************************************************
#ifndef _H_HANDLE_DROP_EVENT_
#define _H_HANDLE_DROP_EVENT_
//********************************************************************************************************************
#include "ClientPreqs.h"
#include "UICommon.h"
//********************************************************************************************************************
namespace MG
{
    class HandleDropEvent
    {
    public:
        HandleDropEvent(){ ;}
        ~HandleDropEvent(){;}


		SINGLETON_INSTANCE(HandleDropEvent);

    public:
        void        setEvent();

    protected:
    private:
        static void     handleDropEvent(void* pointer);
		static void		onDropItem(void* arg = NULL);
		static void		onCancelDropItem(void* arg = NULL);
		IconInfo		mDropItemInfo;

    };
}
//********************************************************************************************************************
#endif
//********************************************************************************************************************