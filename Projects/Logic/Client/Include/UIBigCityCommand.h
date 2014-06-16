//***************************************************************************************************
#ifndef _H_UIBIGCITYCOMMAND_
#define _H_UIBIGCITYCOMMAND_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    class UIBigCityCommand  : public UIObject
    {
    public:
        UIBigCityCommand();
        ~UIBigCityCommand();
        SINGLETON_INSTANCE(UIBigCityCommand);

    public:


		void			init();
		//virtual void	update();
        
	

	public:

		////////////////////////////////////////////////////////////////////////
		virtual void	setEvent();
		

    protected:
    private:
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************