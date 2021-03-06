//***************************************************************************************************
#ifndef _H_UIBIGCITYMINIMAP_
#define _H_UIBIGCITYMINIMAP_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
#include "GameMiniMapManager.h"
//***************************************************************************************************
namespace MG
{
    class UIBigCityMiniMap  : public UIObject, public GameMiniMapListener
    {
    public:
        UIBigCityMiniMap();
        ~UIBigCityMiniMap();
        SINGLETON_INSTANCE(UIBigCityMiniMap);

    public:


		void			init();
		virtual void	update(Flt delta);
        
		//���ڵ�ͼ����
		void            setMapName(Str16 mapName);

		////////////////////////////////////////////////////////////////////////
		void			onMiniMapLoaded(GameMiniMap* miniMap);
		void			onMiniMapUnLoad(GameMiniMap* miniMap);
		////////////////////////////////////////////////////////////////////////

	public:

		////////////////////////////////////////////////////////////////////////
		virtual void	setEvent();
		static	void	onClickSetFlag(void* widget);
		static	void	onClickPathSearch(void* widget);
		static	void	onClickMap(void* widget);
		
		static	void	onClickMiniMap(void* widget);
		static  void	onDragMiniMap(void* widget, Int left, Int top);
		////////////////////////////////////////////////////////////////////////


    protected:
    private:
    };
}
//***************************************************************************************************
#endif
//***************************************************************************************************