/******************************************************************************/
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "Singleton.h"
#include "IInput.h"
#include <OIS\OISMouse.h>
#include <OIS\OISKeyboard.h>
#include <OIS\OISJoyStick.h>
#include <OIS\OISInputManager.h>

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//��Ϸ���봦��
	/******************************************************************************/
	class InputManager : public MGSingleton<InputManager>, public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener, public IInput
	{
	public:
        SINGLETON_DECLARE( InputManager )
        InputManager();
        virtual ~InputManager();

        void initialise( Ogre::RenderWindow *renderWindow, HWND inputhandle = 0, bool subWin = false);
        void update( float delta );

        /// �Ƿ���̱���ס
        virtual Bool isKeyHolded (KeyCode key);
        /// �Ƿ���̰���
        virtual Bool isKeyPressed(KeyCode key); 
        /// �Ƿ���̵���
        virtual Bool isKeyReleased(KeyCode key);

        /// �Ƿ������Ctrl��������
        virtual Bool isCtrlOn () ;
        /// �Ƿ������Shift��������
        virtual Bool isShiftOn() ;
        /// �Ƿ������Alt��������
        virtual Bool isAltOn  () ;

    public:

        /// �õ������Ļ������
        virtual Vec2 getMousePos() ;
		/// �õ������Ļ������
		virtual Vec2 getMouseScreenPos() ;
        /// �õ�����ƶ��������
        virtual Vec2 getMouseMoveDelta();

        /// �õ�����ٶ�
        virtual Flt getMouseSpeed() ;
        /// ��������ٶ�
        virtual void setMouseSpeed(Flt speed) ;

        /// �õ���������
        virtual Int getMouseWheel() ;
        /// �Ƿ���걻��ס
        virtual Bool isMouseHolded (MouseCode mouse) ;
        /// �Ƿ���갴��
        virtual Bool isMousePressed(MouseCode mouse) ; 
        /// �Ƿ���굯��
        virtual Bool isMouseReleased(MouseCode mouse) ;
        /// �Ƿ����˫��
        virtual Bool isMouseDoubleClicked(MouseCode mouse) ;
    
    public:
        //IME�����������룬����������·���Gui��
        static LRESULT CALLBACK winFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        //���������Ĭ�ϵĻص�����
        WNDPROC	getOldProc(){return mPoldProc;}
        //�����Ƿ�IME���ơ�
        void IsIMEHold(Bool isIMEHold){mBisIMEHold = isIMEHold;}
        Bool IsIMEHold(){return mBisIMEHold;}

		void addKeyListener( OIS::KeyListener *keyListener, const std::string& instanceName );
		void addMouseListener( OIS::MouseListener *mouseListener, const std::string& instanceName );
		void addJoystickListener( OIS::JoyStickListener *joystickListener, const std::string& instanceName );

		void removeKeyListener( const std::string& instanceName );
		void removeMouseListener( const std::string& instanceName );
		void removeJoystickListener( const std::string& instanceName );

		void removeKeyListener( OIS::KeyListener *keyListener );
		void removeMouseListener( OIS::MouseListener *mouseListener );
		void removeJoystickListener( OIS::JoyStickListener *joystickListener );

		void removeAllListeners( void );
		void removeAllKeyListeners( void );
		void removeAllMouseListeners( void );
		void removeAllJoystickListeners( void );
        //�������Ļ��Χ
        void setWindowExtents( int width, int height );

		//�����Ƿ�ʧȥ����
		Bool isFocusLastFrame() { return mFocusLastFrame; }

    protected:

		OIS::Mouse*    getMouse( void );
		OIS::Keyboard* getKeyboard( void );
		OIS::JoyStick* getJoystick( unsigned int index );

		int getNumOfJoysticks( void );

	private:
    
        void capture( void );

		bool keyPressed( const OIS::KeyEvent &e );
        bool IMEkeyPressed( const OIS::KeyEvent &e );
		bool keyReleased( const OIS::KeyEvent &e );

		bool mouseMoved( const OIS::MouseEvent &e );
		bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
		bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

		bool povMoved( const OIS::JoyStickEvent &e, int pov );
		bool axisMoved( const OIS::JoyStickEvent &e, int axis );
		bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID );
		bool buttonPressed( const OIS::JoyStickEvent &e, int button );
		bool buttonReleased( const OIS::JoyStickEvent &e, int button );

        //����IME��Ϣ(��������)
        bool deal_IME_COMPOSITION(HWND hWnd, LPARAM lParam);

		OIS::InputManager *mInputSystem;
		OIS::Mouse        *mMouse;
		OIS::Keyboard     *mKeyboard;

		std::vector<OIS::JoyStick*> mJoysticks;
		std::vector<OIS::JoyStick*>::iterator itJoystick;
		std::vector<OIS::JoyStick*>::iterator itJoystickEnd;

		std::map<std::string, OIS::KeyListener*> mKeyListeners;
		std::map<std::string, OIS::MouseListener*> mMouseListeners;
		std::map<std::string, OIS::JoyStickListener*> mJoystickListeners;

		std::map<std::string, OIS::KeyListener*>::iterator itKeyListener;
		std::map<std::string, OIS::MouseListener*>::iterator itMouseListener;
		std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListener;

		std::map<std::string, OIS::KeyListener*>::iterator itKeyListenerEnd;
		std::map<std::string, OIS::MouseListener*>::iterator itMouseListenerEnd;
		std::map<std::string, OIS::JoyStickListener*>::iterator itJoystickListenerEnd;

	private:


		enum OpState
		{
			OS_NULL = 0,
			OS_PRESSED = 1,
			OS_RELEASEED = 2
		};

		void	clearMouseState();
		void	clearKeyState();

		void	setMouseState( MouseCode code, OpState state );
		void	setKeyState( KeyCode code, OpState state );
		OpState	getMouseState( MouseCode code );
		OpState	getKeyState( KeyCode code );

		Vec2 mMouseLastPos;
		std::map<MouseCode,OpState> mMouseStates;
		std::map<KeyCode,OpState> mKeyStates;
		float mCurrRespondDelta;
		float mIgnoreRespondInterval;
		Bool mIsIgnoreRespond;

        //��¼�����ڵĻص�������
        WNDPROC	mPoldProc;
        Bool mBisIMEHold;

		//��¼������
		HWND mHwnd;

		//��¼��һ֡�Ƿ��ý���
		Bool mFocusLastFrame;
	};
}

/******************************************************************************/

#endif
