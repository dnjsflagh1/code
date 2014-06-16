//***************************************************************************************************
#ifndef _H_UIRPGMINIMAP_
#define _H_UIRPGMINIMAP_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
#include "GameMiniMapManager.h"
//***************************************************************************************************
namespace MG
{
    class UIRPGMiniMap  : public UIObject, public GameMiniMapListener
    {
    public:
        UIRPGMiniMap();
        ~UIRPGMiniMap();
        SINGLETON_INSTANCE(UIRPGMiniMap);

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