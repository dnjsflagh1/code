//***************************************************************************************************
#ifndef _UICHARACTERJUMPREGION_H_
#define _UICHARACTERJUMPREGION_H_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    class UICharacterJumpRegion: public UIObject
    {
    public:
        UICharacterJumpRegion();
        ~UICharacterJumpRegion();
        SINGLETON_INSTANCE(UICharacterJumpRegion);

    public:
        virtual void		setEvent();
		virtual	Bool		openGui();

		static	void		onEnterRegion(void* widget);
		static	void		onClickCloseBtn(void* widget);

				void		setCurrRegion( CRegionObject* region );
		CRegionObject*		getCurrSelectRegion();
				void		setCurrCharacter(CPlayerCharacter* character);
		CPlayerCharacter*	getCurrCharacter();
    private:
		CRegionObject*				mCurrSelectRegion;
		CPlayerCharacter*			mCurrCharacter;
    };
}
//***************************************************************************************************
#endif
//******