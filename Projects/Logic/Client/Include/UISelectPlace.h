//*************************************************************************************
#ifndef _UISELECTPLACE_H_
#define _UISELECTPLACE_H_
//*************************************************************************************
#include "UIObject.h"
//*************************************************************************************
namespace MG
{
	/******************************************************************************/
	//�ݵ��ѡ����
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
		//���þݵ�����
		void			setTitle(CChar16* title);
		//���þݵ�����
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