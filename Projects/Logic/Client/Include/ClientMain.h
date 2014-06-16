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
	//��Ϸ�ͻ������ӿ�
	/******************************************************************************/
	class ClientMain : public IClientMain
	{
	public:
        SINGLETON_INSTANCE(ClientMain)
        ClientMain();
        virtual ~ClientMain();

        /// ��Ϸ��ʼ��
		virtual Bool        initialize() ;
        /// ������Ϸ
        virtual void        run();
        /// ��Ϸ����ʼ��
		virtual Bool        uninitialize() ;
        /// �õ��������
        Dbl				    getDelta() { return mUpdateDelta; }

        /// �Ƴ�����Ӧ�ó���
        void			    quitApplication();

	public:

		///��������GUIָ�롣
		IGui*					getGui(){assert(mMainGui);return mMainGui;}

        ///��������Pointerָ�롣
        IPointer*				getPointer(){assert(mPointer);return mPointer;}

		///��������Fontָ�롣
		IFont*					getFont(){assert(mFont);return mFont;}

		///��������GUIָ�롣
		IEngineMain*			getEngine(){assert(mEngineMain);return mEngineMain;}

        ///�������ĳ���ָ�롣
		IScene*					getScene(){ assert(mMainScene); return mMainScene;}

        ///��ýű��������
        LuaManager*				getLuaManager(){ assert(mLuaMgr); return mLuaMgr;}

		///��ô�������� 
		IMGExternalPackManager* getMGPackManager(){ return mExPackManager; };
		///��ô�������� 
		GameFilePackManager*	getPackManager(){ return mPackManager; };

        /// ���ú��ж��Ƿ�Ϊ������
        void					setConsole( Bool console );
        Bool					isConsole();

	protected:

        static LRESULT CALLBACK windowMsg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        static WinProc		mWindowProcBackup;

	private:

        /// ��������
        Bool			    loadEngine();
        /// ж������
        Bool			    unLoadEngine();

	private:

        /// ��Ϸ����
        Bool			    update( Dbl delta );

        Bool				_initialize();
        void				_run();
        Bool				_uninitialize() ;

	private:
        
		/// ��Դ����ӿ�ָ��
		GameFilePackManager*	mPackManager;
		IMGExternalPackManager* mExPackManager;

        /// ��Ϸ����ӿ�ָ��
        IEngineMain* mEngineMain;
        /// ��Ϸ����DLL������
        DllLoader mEngineDllLoader;

        /// ��Ϸ������
        IScene* mMainScene;
        /// ��Ϸ���������
        IGui* mMainGui;
        /// ��Ϸ���ָ��
        IPointer* mPointer;
		/// ��Ϸ����
		IFont* mFont;

        /// Lua������
        LuaManager* mLuaMgr;

        /// ��Ϸ����ֹͣ��־λ
        Bool mStopUpdateDirty;
        /// �ϴθ���֡ʱ��
        Dbl mLastUpdateTicks;
        /// ��ǰ����֡ʱ��
		Dbl mCurrUpdateTicks;
        /// ��ǰ����֡ʱ���
		Dbl mUpdateDelta;
		
        /// �Ƿ�Ϊ������
        Bool    mConsole;

	};
	
}

/******************************************************************************/

#endif

