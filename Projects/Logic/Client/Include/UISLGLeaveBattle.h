//***************************************************************************************************
#ifndef _H_UISLLEAVEBATTLE_
#define _H_UISLLEAVEBATTLE_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    class UISLGLeaveBattle  : public UIObject
    {
    public:
        UISLGLeaveBattle();
        ~UISLGLeaveBattle();
        SINGLETON_INSTANCE(UISLGLeaveBattle);

    public:


		void			init();
		//virtual void	update();
        
	

	public:

		////////////////////////////////////////////////////////////////////////
		virtual void	setEvent();
		static  void    onEventLeave(void* widget);
		

    protected:
    private:
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************