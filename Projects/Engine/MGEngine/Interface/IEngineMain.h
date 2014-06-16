/******************************************************************************/
#ifndef _IENGINEMAIN_H_
#define _IENGINEMAIN_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "IScene.h"
#include "GameFilePackManager.h"

namespace MG
{
	/******************************************************************************/
	//游戏引擎基础配置
	/******************************************************************************/
	enum EngineMode
	{
		EM_NORMAL = 0,
		EM_EDITOR,
		EM_DEBUG,
	};

	struct EngineInitConfig
	{
		CChar*  pluginFileName;
		CChar*  configFileName;
		CChar*  logFileName;
		CChar*  resFileName;
		CChar*  modelDeclFileName;
		CChar*	treeDeclFileName;
		CChar*	accessoryDeclFileName;
		CChar*	materialDeclFileName;
		CChar*	materialParamDeclFileName;
		CChar*	effectDeclFileName;
		CChar*	effectComponentDeclFileName;
		CChar*	waterEffectDeclFileName;
		CChar*	grassEffectDeclFileName;
		CChar*  terrainTextureDeclFileName;
        CChar*  treeResourceFileName;
        CChar*  grassResourceFileName;

		HWND    windowsHandle;
		HWND	inputHandle;
		CChar*  windowName;
		U32     screenWidth;
		U32     screenHeight;

		Bool    isFullScreen;
		Bool	isVsync;

		U32		fsaa;
		Str		fsaaHint;

		GameFilePackManager* packManager;

		EngineInitConfig()
		{
			pluginFileName				= 0;
			configFileName				= 0;
			logFileName					= 0;
			resFileName					= 0;
			modelDeclFileName			= 0;
			terrainTextureDeclFileName  = 0;
			packManager					= NULL;
			inputHandle					= 0;
		}
	};
	/******************************************************************************/
	//游戏引擎主接口
	/******************************************************************************/
	class IEngineMain
	{
	public:

		/// 引擎初始化.
		virtual Bool                initialize( const EngineInitConfig* config ) = 0;
		/// 引擎反初始化.
		virtual Bool                uninitialize() = 0;
		/// 更新引擎
		virtual Bool                update( Flt delta ) = 0;
        /// 渲染引擎
        virtual Bool                render( Flt delta ) = 0;

		/// 设置模式
		virtual void                setMode( EngineMode mode ) = 0;
		/// 得到模式
		virtual EngineMode			getMode() = 0;

	public:

		/// 暂时停止更新TreeSystem
		virtual	void				lockTreeManager() = 0;
		/// 可以更新TreeSystem
		virtual void				unLockTreeManager() = 0;

	public:

		/// 创建场景
		virtual IScene*             createScene( CChar* sceneName, CChar* camName ) = 0;
		/// 删除所有场景
		virtual void                destroyAllScene() = 0;

	public:

		/// 获得游戏程序接口.
		virtual IApplication*       app() = 0;
		/// 获得游戏输入接口
		virtual IInput*             input() = 0;
		/// 获得声音管理器
		virtual ISoundManager*      soundMgr() = 0;
		/// 获得游戏资源接口
		virtual IResourceManager*   resourceMgr() = 0;
		/// 获得游戏显示接口
		virtual IDisplay*           display() = 0;
		/// 获得游戏编辑接口
		virtual IEditorSystem*      editorSystem() = 0;
		///获得引擎工具接口
		virtual IEngineUtil*		engineUtil() = 0;

	public:

		/// 渲染单帧
		virtual void				renderOneFrame( Flt delta ) = 0;

	};

}

/******************************************************************************/
#endif

