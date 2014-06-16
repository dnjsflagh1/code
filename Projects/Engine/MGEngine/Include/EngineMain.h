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
	//Ogre�����ӿ�
	/******************************************************************************/
    struct OgreMainInterface
    {
        /** OgreRootָ�� */
		static Ogre::Root * root;
        /** Ogre����Ⱦ���� */
		static Ogre::RenderWindow * renderWindow;
    };
	/******************************************************************************/
	//��Ϸ�������ӿ�
	/******************************************************************************/
	class EngineMain : public IEngineMain
	{
        friend class Application;
	public:
        SINGLETON_INSTANCE(EngineMain)
        EngineMain();
        virtual ~EngineMain();

        /// �����ʼ��.
		virtual Bool                initialize( const EngineInitConfig* config ) ;
        /// ���淴��ʼ��.
		virtual Bool                uninitialize() ;

		/// ����ģʽ
		virtual void                setMode( EngineMode mode );
		/// �õ�ģʽ
		virtual EngineMode			getMode();

	public:

        /// ��������.
        virtual Bool                update( Flt delta );
        /// ��Ⱦ����
        virtual Bool                render( Flt delta );

        /// ������Ⱦ
        virtual void                lockRender();
        /// ������Ⱦ
        virtual void                unLockRender();

		/// ��ʱֹͣ����TreeSystem
		virtual	void				lockTreeManager();
		/// ���Ը���TreeSystem
		virtual void				unLockTreeManager();
		//  ��ȡTreeSystem��������	
				Bool				isTreeManagerLocked();

		//////////////////////////////////////////////////////////////////////////

        /// ���������ǰ��Ҫ��������
                void                preRendering();
        /// ��������º���Ҫ��������
                void                postRendering();

        /// Ӧ����ʾ�����޸�
                void                applyRenderConfig();
        /// ��ʾ�ֱ����޸�
                void                applyResolutionConfig(UInt nScreenX, UInt nScreenY);
	public:

        /// ��������
		virtual IScene*             createScene( CChar* sceneName, CChar* camName );
        /// ɾ�����г���
		virtual void                destroyAllScene();

        /// �õ���һ����
                Scene*              getFirstScene();

	public:

        /// �����Ϸ����ӿ�.
        virtual IApplication*       app();
        /// �����Ϸ����ӿ�
        virtual IInput*             input();
        /// �������������
        virtual ISoundManager*      soundMgr();
        /// �����Ϸ��Դ����ӿ�
        virtual IResourceManager*   resourceMgr();
        /// �����Ϸ��ʾ�ӿ�
        virtual IDisplay*           display();
        /// �����Ϸ�༭�ӿ�
        virtual IEditorSystem*      editorSystem();
		///������湤�߽ӿ�
		virtual IEngineUtil*		engineUtil();
		/// �õ����ϵͳ
		IMGExternalPackManager*		getPackManager();

	public:

		/// ��Ⱦһ֡
		virtual void				renderOneFrame( Flt delta );

    protected:

        /// ��λ������Դ�ļ�.
        void                        locateResources(CChar* filename) ; 
        /// ����������Դ�ļ�.
        void                        loadResources() ;
 
	private:

        /// ��Ϸ����ӿ�ָ��
        Application *mApp;
        /// ��Ϸ��ʾ�ӿ�ָ��
        Display *mDisplay;
        /// ����ӿ�ָ��
        InputManager *mInputMgr;
        /// ����������
        SoundALManager *mSoundMgr;
        /// ��Դ����ӿ�ָ��
        MG::ResourceManager* mResourceMgr;
        /// �����б�
        std::map<String, Scene*> mScenes;

        // ��Ⱦ����
        Bool mRenderLocker;

		// ��ϵͳ����
		bool mTreeManagerLocker;

		// ����ģʽ
		EngineMode mEngineMode;

		// ���ϵͳ
		IMGExternalPackManager*			mMGPackManager;
		IExternalOgreResourceManager*	mOgrePackManager;
	};
	
}

/******************************************************************************/

#endif

