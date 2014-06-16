//***************************************************************************************************
#ifndef _H_UIPROCESS_
#define _H_UIPROCESS_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    class UIProgress: public UIObject
    {
    public:
        UIProgress();
        ~UIProgress();
        SINGLETON_INSTANCE(UIProgress);

    public:
        virtual	void	setEvent();
		void			setPosition(Int val);
		void			setText(Char16* str);
		void			update();

    protected:
    private:
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************