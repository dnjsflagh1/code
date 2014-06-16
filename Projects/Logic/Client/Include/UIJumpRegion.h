//***************************************************************************************************
#ifndef _UIJUMPREGION_H_
#define _UIJUMPREGION_H_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{
    class UIJumpRegion : public UIObject
    {
    public:
        UIJumpRegion();
        ~UIJumpRegion();
        SINGLETON_INSTANCE(UIJumpRegion);

    public:
        virtual void	setEvent();
				void	addRegion( CRegionObject* region );
		virtual	Bool	openGui();

		static	void	onEnterRegion(void* widget);
		static	void	onSelectRegion(void* widget, Int index );
		static	void	onClickCloseBtn(void* widget);

		CRegionObject*	getCurrSelectRegion();
				void	setCurrRegionIndex(U32 index);
				void	setCurrCharacter(IdType characterId);
				IdType	getCurrCharacterId();
    private:
		void			_clear();
					

		std::map<U32,CRegionObject*> mRegionMap;
		U32							mCurrSelectRegion;
		IdType						mCurrCharacterId;
    };
}
//***************************************************************************************************
#endif
//******