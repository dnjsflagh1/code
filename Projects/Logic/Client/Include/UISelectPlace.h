//*************************************************************************************
#ifndef _UISELECTPLACE_H_
#define _UISELECTPLACE_H_
//*************************************************************************************
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
	/******************************************************************************/
	//据点点选界面
	/******************************************************************************/
    class  UISelectPlace:public UIObject
    {
	public:
		UISelectPlace():mCurrPlaceObjId(0),mCharacterId(0)
		{;}
		virtual ~UISelectPlace(){;}
		SINGLETON_INSTANCE(UISelectPlace);
	public:
		virtual void	setEvent();
		virtual Bool	openGui();
        virtual Bool    closeGui();
		
			void            openPlaceDialog(PlaceIdType placeId,PlayerCharacterIdType characterId); 
		//设置据点名称
		void			setTitle(CChar16* title);
		//设置据点描述
		void			setDesc(CChar16* desc);

		void			setCurrPlaceObj(PlaceIdType placeObjId);
		PlaceIdType		getCurrPlaceObjId();

		void			                setCurrCharacterId(PlayerCharacterIdType characterId);
		PlayerCharacterIdType			getCurrCharacterId();

		static	void	onClickCloseBtn(void* widget);
		static	void	onEnterPlace(void* widget);
		static	void	onReturnMap(void* widget);

	private:
		PlaceIdType	           mCurrPlaceObjId;
		PlayerCharacterIdType  mCharacterId;


	};
	
}
#endif