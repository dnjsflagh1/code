//***************************************************************************************************
#ifndef _H_UISLGTIMELEFT_
#define _H_UISLGTIMELEFT_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    class UISLGTimeLeft  : public UIObject
    {
		public:
			UISLGTimeLeft();
			~UISLGTimeLeft();
			SINGLETON_INSTANCE(UISLGTimeLeft);

		public:
			void			setCountDownTime(Int seconds);
			virtual	bool	openGui();
		public:
			static void		eventTimeFinish(void* widget, Int i);
	
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************