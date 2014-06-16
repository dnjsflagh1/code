/******************************************************************************/
#ifndef _ENGINEMAIN_H_
#define _ENGINEMAIN_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IEngineMain.h"
#include "ResourceManager.h"

// MG_CN_MODIFY
#include "IMGPackExterInterface.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//Ogre基础接口
	/******************************************************************************/
    struct OgreMainInterface
    {
        /** OgreRoot指针 */
		static Ogre::Root * root;
        /** Ogre的渲染窗口 */
		static Ogre::RenderWindow * renderWindow;
    };
	/******************************************************************************/
	//游戏引擎主接口
	/******************************************************************************/
	class EngineMain : public IEngineMain
	{
        friend class Application;
	public:
        SINGLETON_INSTANCE(EngineMain)
        EngineMain();
        virtual ~EngineMain();

        /// 引擎初始化.
		virtual Bool                initialize( const EngineInitConfig* config ) ;
        /// 引擎反初始化.
		virtual Bool                uninitialize() ;

		/// 设置模式
		virtual void                setMode( EngineMode mode );
		/// 得到模式
		virtual EngineMode			getMode();

	public:

        /// 更新引擎.
        virtual Bool                update( Flt delta );
        /// 渲染引擎
        virtual Bool                render( Flt delta );

        /// 锁定渲染
        virtual void                lockRender();
        /// 解锁渲染
        virtual void                unLockRender();

		/// 暂时停止更新TreeSystem
		virtual	void				lockTreeManager();
		/// 可以更新TreeSystem
		virtual void				unLockTreeManager();
		//  获取TreeSystem锁定开关	
				Bool				isTreeManagerLocked();

		//////////////////////////////////////////////////////////////////////////

        /// 在引擎更新前需要做的事情
                void                preRendering();
        /// 在引擎更新后需要做的事情
                void                postRendering();

        /// 应用显示参数修改
                void                applyRenderConfig();
        /// 显示分辨率修改
                void                applyResolutionConfig(UInt nScreenX, UInt nScreenY);
	public:

        /// 创建场景
		virtual IScene*             createScene( CChar* sceneName, CChar* camName );
        /// 删除所有场景
		virtual void                destroyAllScene();

        /// 得到第一场景
                Scene*              getFirstScene();

	public:

        /// 获得游戏程序接口.
        virtual IApplication*       app();
        /// 获得游戏输入接口
        virtual IInput*             input();
        /// 获得声音管理器
        virtual ISoundManager*      soundMgr();
        /// 获得游戏资源管理接口
        virtual IResourceManager*   resourceMgr();
        /// 获得游戏显示接口
        virtual IDisplay*           display();
        /// 获得游戏编辑接口
        virtual IEditorSystem*      editorSystem();
		///获得引擎工具接口
		virtual IEngineUtil*		engineUtil();
		/// 得到打包系统
		IMGExternalPackManager*		getPackManager();

	public:

		/// 渲染一帧
		virtual void				renderOneFrame( Flt delta );

    protected:

        /// 定位引擎资源文件.
        void                        locateResources(CChar* filename) ; 
        /// 加载引擎资源文件.
        void                        loadResources() ;
 
	private:

        /// 游戏程序接口指针
        Application *mApp;
        /// 游戏显示接口指针
        Display *mDisplay;
        /// 输入接口指针
        InputManager *mInputMgr;
        /// 声音管理器
        SoundALManager *mSoundMgr;
        /// 资源管理接口指针
        MG::ResourceManager* mResourceMgr;
        /// 场景列表
        std::map<String, Scene*> mScenes;

        // 渲染锁定
        Bool mRenderLocker;

		// 树系统锁定
		bool mTreeManagerLocker;

		// 引擎模式
		EngineMode mEngineMode;

		// 打包系统
		IMGExternalPackManager*			mMGPackManager;
		IExternalOgreResourceManager*	mOgrePackManager;
	};
	
}

/******************************************************************************/

#endif

