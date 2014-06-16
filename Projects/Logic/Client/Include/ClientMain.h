/******************************************************************************/
#ifndef _CLIENTMAIN_H_
#define _CLIENTMAIN_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "MGClientInterface.h"
#include "GameObjectOpCtrl.h"
#include "GameFilePackManager.h"
#include "MGExternalPackManager.h"
#include "ExternalOgreResourceManager.h"

/******************************************************************************/
namespace MG
{

	typedef LRESULT (__stdcall *WinProc)(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	/******************************************************************************/
	//游戏客户端主接口
	/******************************************************************************/
	class ClientMain : public IClientMain
	{
	public:
        SINGLETON_INSTANCE(ClientMain)
        ClientMain();
        virtual ~ClientMain();

        /// 游戏初始化
		virtual Bool        initialize() ;
        /// 运行游戏
        virtual void        run();
        /// 游戏反初始化
		virtual Bool        uninitialize() ;
        /// 得到心跳间隔
        Dbl				    getDelta() { return mUpdateDelta; }

        /// 推出整个应用程序
        void			    quitApplication();

	public:

		///获得引擎的GUI指针。
		IGui*					getGui(){assert(mMainGui);return mMainGui;}

        ///获得引擎的Pointer指针。
        IPointer*				getPointer(){assert(mPointer);return mPointer;}

		///获得引擎的Font指针。
		IFont*					getFont(){assert(mFont);return mFont;}

		///获得引擎的GUI指针。
		IEngineMain*			getEngine(){assert(mEngineMain);return mEngineMain;}

        ///获得引擎的场景指针。
		IScene*					getScene(){ assert(mMainScene); return mMainScene;}

        ///获得脚本管理对象
        LuaManager*				getLuaManager(){ assert(mLuaMgr); return mLuaMgr;}

		///获得打包管理器 
		IMGExternalPackManager* getMGPackManager(){ return mExPackManager; };
		///获得打包管理器 
		GameFilePackManager*	getPackManager(){ return mPackManager; };

        /// 设置和判断是否为单机版
        void					setConsole( Bool console );
        Bool					isConsole();

	protected:

        static LRESULT CALLBACK windowMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        static WinProc		mWindowProcBackup;

	private:

        /// 加载引擎
        Bool			    loadEngine();
        /// 卸载引擎
        Bool			    unLoadEngine();

	private:

        /// 游戏更新
        Bool			    update( Dbl delta );

        Bool				_initialize();
        void				_run();
        Bool				_uninitialize() ;

	private:
        
		/// 资源打包接口指针
		GameFilePackManager*	mPackManager;
		IMGExternalPackManager* mExPackManager;

        /// 游戏引擎接口指针
        IEngineMain* mEngineMain;
        /// 游戏引擎DLL加载器
        DllLoader mEngineDllLoader;

        /// 游戏主场景
        IScene* mMainScene;
        /// 游戏主界面对象
        IGui* mMainGui;
        /// 游戏鼠标指针
        IPointer* mPointer;
		/// 游戏字体
		IFont* mFont;

        /// Lua管理器
        LuaManager* mLuaMgr;

        /// 游戏更新停止标志位
        Bool mStopUpdateDirty;
        /// 上次更新帧时间
        Dbl mLastUpdateTicks;
        /// 当前更新帧时间
		Dbl mCurrUpdateTicks;
        /// 当前更新帧时间段
		Dbl mUpdateDelta;
		
        /// 是否为单机版
        Bool    mConsole;

	};
	
}

/******************************************************************************/

#endif

