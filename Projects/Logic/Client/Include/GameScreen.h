/******************************************************************************/
#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_
/******************************************************************************/

#include "ClientPreqs.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    // ��Ϸ������ع���
    /******************************************************************************/
	class GameScreen : public IScreen, public ResourceLoadListener
    {
    public:

        SINGLETON_INSTANCE(GameScreen)
        GameScreen();
        virtual ~GameScreen();

        virtual void    update( Flt delta );
        virtual Bool    isFinished();
        virtual void    onEnter();
        virtual void    onLeave();

        virtual void    onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        virtual void    onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        virtual void    onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );

		// �䶯��ȡ��Դ������
		virtual void	onInitResourceLoadListener();
		virtual void	onClearResourceLoadListener();

		virtual void	preLoadTerrainChunk( UInt index, UInt total );
		virtual void	postLoadTerrainChunk( UInt index, UInt total );
		virtual void	preloadObject( UInt index, UInt total );
		virtual void	postloadObject( ISceneObject* entity, UInt index, UInt total );

    protected:

        static Str  STATE_NAME;

    };

}

/******************************************************************************/

#endif

