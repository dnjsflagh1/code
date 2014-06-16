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
	//游戏输入处理
	/******************************************************************************/
	class InputManager : public MGSingleton<InputManager>, public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener, public IInput
	{
	public:
        SINGLETON_DECLARE( InputManager )
        InputManager();
        virtual ~InputManager();

        void initialise( Ogre::RenderWindow *renderWindow, HWND inputhandle = 0, bool subWin = false);
        void update( float delta );

        /// 是否键盘被按住
        virtual Bool isKeyHolded (KeyCode key);
        /// 是否键盘按下
        virtual Bool isKeyPressed(KeyCode key); 
        /// 是否键盘弹起
        virtual Bool isKeyReleased(KeyCode key);

        /// 是否左或右Ctrl键被按下
        virtual Bool isCtrlOn () ;
        /// 是否左或右Shift键被按下
        virtual Bool isShiftOn() ;
        /// 是否左或右Alt键被按下
        virtual Bool isAltOn  () ;

    public:

        /// 得到鼠标屏幕中坐标
        virtual Vec2 getMousePos() ;
		/// 得到鼠标屏幕中坐标
		virtual Vec2 getMouseScreenPos() ;
        /// 得到鼠标移动间隔距离
        virtual Vec2 getMouseMoveDelta();

        /// 得到鼠标速度
        virtual Flt getMouseSpeed() ;
        /// 设置鼠标速度
        virtual void setMouseSpeed(Flt speed) ;

        /// 得到滚轮数据
        virtual Int getMouseWheel() ;
        /// 是否鼠标被按住
        virtual Bool isMouseHolded (MouseCode mouse) ;
        /// 是否鼠标按下
        virtual Bool isMousePressed(MouseCode mouse) ; 
        /// 是否鼠标弹起
        virtual Bool isMouseReleased(MouseCode mouse) ;
        /// 是否鼠标双击
        virtual Bool isMouseDoubleClicked(MouseCode mouse) ;
    
    public:
        //IME监听中文输入，处理完后重新发给Gui。
        static LRESULT CALLBACK winFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        //获得主窗口默认的回调函数
        WNDPROC	getOldProc(){return mPoldProc;}
        //设置是否IME控制。
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
        //设置鼠标的活动范围
        void setWindowExtents( int width, int height );

		//窗口是否失去焦点
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

        //处理IME消息(中文输入)
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

        //记录主窗口的回调函数。
        WNDPROC	mPoldProc;
        Bool mBisIMEHold;

		//记录主窗口
		HWND mHwnd;

		//记录上一帧是否获得焦点
		Bool mFocusLastFrame;
	};
}

/******************************************************************************/

#endif
