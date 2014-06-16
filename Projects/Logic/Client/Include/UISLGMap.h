//***************************************************************************************************
#ifndef _H_UISLGMAP_
#define _H_UISLGMAP_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
#include "GameMiniMapManager.h"
//***************************************************************************************************
namespace MG
{
    class UISLGMap  : public UIObject, public GameMiniMapListener
    {
    public:
        UISLGMap();
        ~UISLGMap();
        SINGLETON_INSTANCE(UISLGMap);

    public:


		void			init();
		virtual void	update(Flt delta);
        
		//所在地图名称
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