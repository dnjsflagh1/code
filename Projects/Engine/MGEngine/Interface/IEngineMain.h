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
	//��Ϸ�����������
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
	//��Ϸ�������ӿ�
	/******************************************************************************/
	class IEngineMain
	{
	public:

		/// �����ʼ��.
		virtual Bool                initialize( const EngineInitConfig* config ) = 0;
		/// ���淴��ʼ��.
		virtual Bool                uninitialize() = 0;
		/// ��������
		virtual Bool                update( Flt delta ) = 0;
        /// ��Ⱦ����
        virtual Bool                render( Flt delta ) = 0;

		/// ����ģʽ
		virtual void                setMode( EngineMode mode ) = 0;
		/// �õ�ģʽ
		virtual EngineMode			getMode() = 0;

	public:

		/// ��ʱֹͣ����TreeSystem
		virtual	void				lockTreeManager() = 0;
		/// ���Ը���TreeSystem
		virtual void				unLockTreeManager() = 0;

	public:

		/// ��������
		virtual IScene*             createScene( CChar* sceneName, CChar* camName ) = 0;
		/// ɾ�����г���
		virtual void                destroyAllScene() = 0;

	public:

		/// �����Ϸ����ӿ�.
		virtual IApplication*       app() = 0;
		/// �����Ϸ����ӿ�
		virtual IInput*             input() = 0;
		/// �������������
		virtual ISoundManager*      soundMgr() = 0;
		/// �����Ϸ��Դ�ӿ�
		virtual IResourceManager*   resourceMgr() = 0;
		/// �����Ϸ��ʾ�ӿ�
		virtual IDisplay*           display() = 0;
		/// �����Ϸ�༭�ӿ�
		virtual IEditorSystem*      editorSystem() = 0;
		///������湤�߽ӿ�
		virtual IEngineUtil*		engineUtil() = 0;

	public:

		/// ��Ⱦ��֡
		virtual void				renderOneFrame( Flt delta ) = 0;

	};

}

/******************************************************************************/
#endif

