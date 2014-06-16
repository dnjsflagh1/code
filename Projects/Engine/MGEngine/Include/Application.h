/******************************************************************************/
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IApplication.h"
#include "Singleton.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//游戏程序处理
	/******************************************************************************/
	class Application : public IApplication, public MGSingleton<Application>
	{
	public:
        SINGLETON_DECLARE( Application )
        Application();
        virtual ~Application();

        /// 创建Ogre的渲染窗口
        virtual void    createWindow( CChar* name, Int width, Int height, Bool fullScreen = false, HWND handle = 0 );
		/// 获得主窗口句柄
		virtual U32		getWindowHandle();
    private:

		/// 窗口名称
        String mWindowName;
	};
	
}

/******************************************************************************/

#endif
