/******************************************************************************/
#ifndef _LOGOSCREEN_H_
#define _LOGOSCREEN_H_
/******************************************************************************/

#include "ClientPreqs.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    // 游戏标题界面相关功能
    /******************************************************************************/
    class LogoScreen : public IScreen
    {
    public:

        SINGLETON_INSTANCE(LogoScreen)
        LogoScreen();
        virtual ~LogoScreen();

        enum
        {
            INTRO_STEP0,
            INTRO_STEP1,
            INTRO_STEP2,
            INTRO_STEP3,
            INTRO_STEP_MOVIE,
            INTRO_STEP_END,

            INTRO_NR,
        };

        virtual void    update( Flt delta );
        virtual Bool    isFinished();
        virtual void    onEnter();
        virtual void    onLeave();

        virtual void    onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        virtual void    onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        virtual void    onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );

    protected:

        void		loadVideo();
        void		deleteVideo();

        static Str  STATE_NAME;

    };

}

/******************************************************************************/

#endif

