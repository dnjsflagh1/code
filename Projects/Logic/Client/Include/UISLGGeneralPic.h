//***************************************************************************************************
#ifndef _H_UISLGGENERALPIC_
#define _H_UISLGGENERALPIC_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    class UISLGGeneralPic  : public UIObject
    {
    public:
        UISLGGeneralPic();
        ~UISLGGeneralPic();
        SINGLETON_INSTANCE(UISLGGeneralPic);

    public:
        virtual void	setEvent();
		//virtual	bool	openGui();
		//virtual void update();

		void	setCharacterId(IdType id);
		IdType	getCharacterId(){return mCharacterId;};

		static	void onClickGenrealHead( void* widget );

    protected:
    private:
		IdType mCharacterId;
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************