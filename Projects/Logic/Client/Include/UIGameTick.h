//***************************************************************************************************
#ifndef _H_UIGAMETICK_
#define _H_UIGAMETICK_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
	struct TickData
	{
		Str16	str;
		Bool	isEmpty;
		Flt		alpha;
		TickData()
		{
			alpha	= 1.0f;
			str		= L"";
			isEmpty = false;
		}
	};
	//***************************************************************************************************
	//UIGameTick ”Œœ∑∑¥¿°UI
	//***************************************************************************************************
    class UIGameTick : public UIObject
    {
    public:
        UIGameTick();
        ~UIGameTick();
        SINGLETON_INSTANCE(UIGameTick);
		enum {tick_count = 4};
    public:
        virtual void	setEvent();
		virtual void	update();
		void			addStr(Char16* str);
		void			setAlphaReduce(Flt alpha);

    protected:
    private:
		TickData		mData[tick_count];
		Flt				mAlphaReduce;
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************