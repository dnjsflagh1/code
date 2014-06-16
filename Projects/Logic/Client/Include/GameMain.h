/******************************************************************************/
#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_
/******************************************************************************/

#include "ClientPreqs.h"

/******************************************************************************/
namespace MG
{
    
    /******************************************************************************/
    //游戏功能主接口
    /******************************************************************************/
    class GameMain
    {
    public:

        SINGLETON_INSTANCE(GameMain)
        GameMain();
        virtual ~GameMain();

        /// 游戏初始化
        Bool        initialize(IMGExternalPackManager* packManager) ;
        /// 运行游戏
        void        run();
        /// 游戏反初始化
        Bool        uninitialize() ;
        /// 更新
        Bool        update( Dbl delta );

        /// 停止游戏并且重新还原游戏各个动态模块内存数据
        /// 游戏界面回到最初登入
        void        stopAndRestore();

        // 进入标题界面
        void        enterLogoScreen();
        // 进入登入界面
        void        enterLoginScreen();
        // 进入游戏界面
        void        enterGameScreen();

        /// 清空所有操作控制器
        void        clearOperatorCtrls() ;
        /// 还原所有操作控制器
        void        revertOperatorCtrls();
        /// 增加操作控制器
        void        addOperatorCtrls(IOpCtrl* ctrl) ;
        /// 移除操作控制器
        void        removeOperatorCtrls(IOpCtrl* ctrl) ;

    public:

        // 当开始加载场景
        void        onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        // 当结束加载场景
        void        onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );
        /// 当卸载场景
        void        onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType );

    protected:

        /// 加载游戏文件
        Bool        loadGameFile(IMGExternalPackManager* packManager);

        /// 加载脚本文件
        Bool        loadGameScript();

    private:

        // 主流程状态管理器
        LinedStateManager   mScreenLinedStateManager;
        IScreen* mActiveScreen;

        /// 操作控制集合
        std::vector<IOpCtrl*> mOpCtrls;


    };

}

/******************************************************************************/

#endif

