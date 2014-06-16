/******************************************************************************/
#ifndef _COREMANAGER_H_
#define _COREMANAGER_H_
/******************************************************************************/

#include "CommonGameDefine.h"
#include "PackToolPreqs.h"

/******************************************************************************/

namespace PackTool {


    /******************************************************************************/
    class CoreManager
    {
    public:
        SINGLETON_INSTANCE(CoreManager)
        CoreManager();
        ~CoreManager();

        /** 游戏初始化. */
        Bool    initialize() ;
        /** 运行游戏. */
        void    run();
        /** 游戏反初始化 */
        Bool    uninitialize() ;

        /** 停止游戏. */
        void    stop();

    public:

        /** 加载外部库 */
        Bool    loadLib();
        /** 卸载外部库. */
        Bool    unLoadLib();

        /** 加载游戏配置. */
        Bool    loadGameFile();
        /** 卸载游戏配置 */
        Bool    unLoadGameFile();

        /** 加载窗体. */
        Bool    loadForm();
        /** 卸载窗体. */
        Bool    unLoadForm();

        /** 游戏更新. */
        Bool    update( Dbl delta );


	public:

		void	test();


    private:
       

        /// 游戏更新停止标志位
        Bool mStopUpdateDirty;
        /// 上次更新帧时间
        Dbl mLastUpdateTicks;
        /// 当前更新帧时间
        Dbl mCurrUpdateTicks;
        /// 当前更新帧时间段
        Dbl mUpdateDelta;
    };

}

/******************************************************************************/
#endif

