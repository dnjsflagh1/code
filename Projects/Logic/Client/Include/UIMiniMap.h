//***************************************************************************************************
#ifndef _H_UIMINIMAP_
#define _H_UIMINIMAP_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
#include "GameMiniMapManager.h"
//***************************************************************************************************
namespace MG
{
    class UIMiniMap  : public UIObject, public GameMiniMapListener
    {
    public:
        UIMiniMap();
        ~UIMiniMap();
        SINGLETON_INSTANCE(UIMiniMap);

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