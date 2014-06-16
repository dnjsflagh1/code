\/******************************************************************************/
#include "stdafx.h"
#include "InputManager.h"
#include "LogSystem.h"
#include "Display.h"
#include <Ime.h>
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    SINGLETON_DEFINE( InputManager )
    //-----------------------------------------------------------------------
	InputManager::InputManager( void )
        :mMouse( 0 )
	    ,mKeyboard( 0 )
	    ,mInputSystem( 0 )
		,mCurrRespondDelta( 0 )
	    ,mIgnoreRespondInterval( 0.1f )
		,mIsIgnoreRespond( true )
        ,mBisIMEHold(false)
		,mFocusLastFrame(true)
		,mHwnd(NULL)
	{
	}

	//-----------------------------------------------------------------------
	InputManager::~InputManager( void ) {
		if( mInputSystem ) {
			if( mMouse ) {
				mInputSystem->destroyInputObject( mMouse );
				mMouse = 0;
			}

			if( mKeyboard ) {
				mInputSystem->destroyInputObject( mKeyboard );
				mKeyboard = 0;
			}

			if( mJoysticks.size() > 0 ) {
				itJoystick    = mJoysticks.begin();
				itJoystickEnd = mJoysticks.end();
				for(; itJoystick != itJoystickEnd; ++itJoystick ) {
					mInputSystem->destroyInputObject( *itJoystick );
				}

				mJoysticks.clear();
			}

			// If you use OIS1.0RC1 or above, uncomment this line
			// and comment the line below it
			mInputSystem->destroyInputSystem( mInputSystem );
			//mInputSystem->destroyInputSystem();
			mInputSystem = 0;

			// Clear Listeners
			mKeyListeners.clear();
			mMouseListeners.clear();
			mJoystickListeners.clear();
		}
	}

	//-----------------------------------------------------------------------
	void InputManager::initialise( Ogre::RenderWindow *renderWindow, HWND inputhandle, bool subWin) {
		if( !mInputSystem ) {
			// Setup basic variables
			OIS::ParamList paramList;    
			size_t windowHnd = 0;
			std::ostringstream windowHndStr;

			// Get window handle
			renderWindow->getCustomAttribute( "WINDOW", &windowHnd );
			if (inputhandle != 0)
				mHwnd = (HWND)inputhandle;
			else
				mHwnd = (HWND)windowHnd;
            
            //注册监听IME的回调函数。
            mPoldProc = (WNDPROC)(LONG64) SetWindowLong(HWND(mHwnd), GWL_WNDPROC, (LONG)(LONG64)winFunc);

			// Fill parameter list
			windowHndStr << (unsigned int) mHwnd;
			paramList.insert( std::make_pair( std::string( "WINDOW" ), windowHndStr.str() ) );
			if(subWin == false)
			{
				paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
				paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
			}
			else
			{
				paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_BACKGROUND" )));
				paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_BACKGROUND")));
			}
			
			paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
			paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
			// Create inputsystem
			mInputSystem = OIS::InputManager::createInputSystem( paramList );

			// If possible create a buffered keyboard
			if( mInputSystem->getNumberOfDevices( OIS::OISKeyboard ) > 0 ) {
				mKeyboard = static_cast<OIS::Keyboard*>( mInputSystem->createInputObject( OIS::OISKeyboard, true ) );
				mKeyboard->setEventCallback( this );
			}

			// If possible create a buffered mouse
			if( mInputSystem->getNumberOfDevices( OIS::OISMouse ) > 0 ) {
				mMouse = static_cast<OIS::Mouse*>( mInputSystem->createInputObject( OIS::OISMouse, true ) );
				mMouse->setEventCallback( this );

				// Get window size
				unsigned int width, height, depth;
				int left, top;
				renderWindow->getMetrics( width, height, depth, left, top );

				// Set mouse region
				this->setWindowExtents( width, height );
			}

			// If possible create all joysticks in buffered mode
			if( mInputSystem->getNumberOfDevices( OIS::OISJoyStick ) > 0 ) {

				mJoysticks.resize( mInputSystem->getNumberOfDevices( OIS::OISJoyStick ) );

				itJoystick    = mJoysticks.begin();
				itJoystickEnd = mJoysticks.end();
				for(; itJoystick != itJoystickEnd; ++itJoystick ) {
					(*itJoystick) = static_cast<OIS::JoyStick*>( mInputSystem->createInputObject( OIS::OISJoyStick, true ) );
					(*itJoystick)->setEventCallback( this );
				}
			}
		}
	}

	//-----------------------------------------------------------------------
	void InputManager::capture( void ) 
    {
		// Need to capture / update each device every frame
		bool isAppFocus = ( mHwnd == GetFocus() );

        bool isReFocus = false;
		if ( isAppFocus != mFocusLastFrame )
		{
			if ( !mFocusLastFrame )
            {
                isReFocus = true;
            }
		}
        mFocusLastFrame = isAppFocus;

        if ( isAppFocus == false )
            return;

        {
            if( mMouse ) 
            {
                mMouse->capture();
            }

            if( mKeyboard ) 
            {
                mKeyboard->capture();
            }

            if( mJoysticks.size() > 0 ) 
            {
                itJoystick    = mJoysticks.begin();
                itJoystickEnd = mJoysticks.end();
                for(; itJoystick != itJoystickEnd; ++itJoystick ) 
                {
                    (*itJoystick)->capture();
                }
            }
        }

        if ( isReFocus )
        {
            const_cast<OIS::MouseState&>(mMouse->getMouseState()).clear();
            clearMouseState();
            clearKeyState();
        }
	}

	//-----------------------------------------------------------------------
	void InputManager::update( float delta )
	{
		mCurrRespondDelta += delta;
		if ( mCurrRespondDelta > mIgnoreRespondInterval )
		{
			mCurrRespondDelta = 0;
			mIsIgnoreRespond = false;
		}else
		{
			mIsIgnoreRespond = true;
		}

		//暂时每帧都检测，需要做效率检测后决定
		//if ( mIsIgnoreRespond == false )
		{
			clearMouseState();
			clearKeyState();

			capture();
		}
			
	}
	//-----------------------------------------------------------------------
	void InputManager::clearMouseState()
	{
		std::map<MouseCode,OpState>::iterator iter =  mMouseStates.begin();
		std::map<MouseCode,OpState>::iterator iter_end =  mMouseStates.end();
		for( ;iter!=iter_end; iter++ )
		{
			iter->second = OS_NULL;
		}
	}
	//-----------------------------------------------------------------------
	void InputManager::clearKeyState()
	{
		std::map<KeyCode,OpState>::iterator iter =  mKeyStates.begin();
		std::map<KeyCode,OpState>::iterator iter_end =  mKeyStates.end();
		for( ;iter!=iter_end; iter++ )
		{
			iter->second = OS_NULL;
		}
	}
	//-----------------------------------------------------------------------
	void InputManager::setMouseState( MouseCode code, InputManager::OpState state )
	{
		mMouseStates[code] = state;
	}
	//-----------------------------------------------------------------------
	void InputManager::setKeyState( KeyCode code, InputManager::OpState state )
	{
		mKeyStates[code] = state;
	}
	//-----------------------------------------------------------------------
	InputManager::OpState InputManager::getMouseState( MouseCode code )
	{
		std::map<MouseCode,OpState>::iterator iter_end =  mMouseStates.end();
		std::map<MouseCode,OpState>::iterator iter_find =  mMouseStates.find(code);
		if ( iter_find != iter_end )
		{	
			return iter_find->second;
		}
		return OS_NULL;
	}
	//-----------------------------------------------------------------------
	InputManager::OpState InputManager::getKeyState( KeyCode code )
	{
		std::map<KeyCode,OpState>::iterator iter_end =  mKeyStates.end();
		std::map<KeyCode,OpState>::iterator iter_find =  mKeyStates.find(code);
		if ( iter_find != iter_end )
		{	
			return iter_find->second;
		}
		return OS_NULL;
	}
    //-----------------------------------------------------------------------
    Bool InputManager::isKeyHolded (KeyCode key)
    {
		if ( mKeyboard )
		{
			return mKeyboard->isKeyDown( (OIS::KeyCode)key );
		}
        return false;
    }
    //-----------------------------------------------------------------------
    Bool InputManager::isKeyPressed(KeyCode key)
    {
		if ( getKeyState(key) == OS_PRESSED )
		{
			return true;
		}
        return false;
    }
    //-----------------------------------------------------------------------
    Bool InputManager::isKeyReleased(KeyCode key)
    {
		if ( getKeyState(key) == OS_RELEASEED )
		{
			return true;
		}
        return false;
    }
    //-----------------------------------------------------------------------
    Bool InputManager::isCtrlOn ()
    {
        if ( mKeyboard )
        {
            return ( mKeyboard->isKeyDown( OIS::KC_LCONTROL ) || mKeyboard->isKeyDown( OIS::KC_RCONTROL ) );
        }
        return false;
    }
    //-----------------------------------------------------------------------
    Bool InputManager::isShiftOn()
    {
        if ( mKeyboard )
        {
            return ( mKeyboard->isKeyDown( OIS::KC_LSHIFT ) || mKeyboard->isKeyDown( OIS::KC_RSHIFT ) );
        }
        return false;
    }
    //-----------------------------------------------------------------------
    Bool InputManager::isAltOn  ()
    {
        if ( mKeyboard )
        {
            return ( mKeyboard->isKeyDown( OIS::KC_LMENU ) || mKeyboard->isKeyDown( OIS::KC_RMENU ) );
        }
        return false;
    }
    //-----------------------------------------------------------------------
    Vec2 InputManager::getMousePos()
    {
		if ( mMouse )
		{
			return Vec2(mMouse->getMouseState().X.abs, mMouse->getMouseState().Y.abs);
		}
		
        return Vec2(0.5,0.5);
    }
	//-----------------------------------------------------------------------
	Vec2 InputManager::getMouseScreenPos()
	{
		Vec2 pos = getMousePos();

		pos.x = pos.x / mMouse->getMouseState().width ;
		pos.y = pos.y / mMouse->getMouseState().height ;

		return pos;
	}
    //-----------------------------------------------------------------------
    Vec2 InputManager::getMouseMoveDelta()
    {
		if ( mMouse )
		{
			return Vec2(mMouse->getMouseState().X.rel*0.001, mMouse->getMouseState().Y.rel*0.001);
		}

        return Vec2(0,0);
    }
    //-----------------------------------------------------------------------
    Flt InputManager::getMouseSpeed() 
    {
        return 1;
    }
    //-----------------------------------------------------------------------
    void InputManager::setMouseSpeed(Flt speed)
    {

        
    }
    //-----------------------------------------------------------------------
    Int InputManager::getMouseWheel() 
    {
		if ( mMouse )
		{
			return mMouse->getMouseState().Z.rel;
		} 
		
        return 0;
    }
    //-----------------------------------------------------------------------
    Bool InputManager::isMouseHolded (MouseCode mouse) 
    {
		if ( mMouse )
		{
			return mMouse->getMouseState().buttonDown( (OIS::MouseButtonID)mouse );
		}
        return false;
    }
    //-----------------------------------------------------------------------
    Bool InputManager::isMousePressed(MouseCode mouse) 
    {
		if ( getMouseState(mouse) == OS_PRESSED )
		{
			return true;
		}
        return false;
    }
    //-----------------------------------------------------------------------
    Bool InputManager::isMouseReleased(MouseCode mouse)
    {
		if ( getMouseState(mouse) == OS_RELEASEED  )
		{
			return true;
		}
        return false;
    }
    //-----------------------------------------------------------------------
    Bool InputManager::isMouseDoubleClicked(MouseCode mouse)
    {
        

        return false;
    }
    //-----------------------------------------------------------------------
    bool InputManager::IMEkeyPressed( const OIS::KeyEvent &e )
    {
        //LogSystem::getInstance().log(out_sys, "IME: imekey = %d,    imetext = %d\n", e.key, e.text);
        itKeyListener = mKeyListeners.begin();
        itKeyListenerEnd = mKeyListeners.end();
        for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) 
        {
            if( itKeyListener->second->keyPressed( e ) )
                break;
        }
        return true;
    }
	//-----------------------------------------------------------------------
	bool InputManager::keyPressed( const OIS::KeyEvent &e ) 
	{
		setKeyState( (MG::KeyCode)e.key, OS_PRESSED );
        if (mBisIMEHold == false)
        {
            //LogSystem::getInstance().log(out_error, "EG:    egkey = %d,     egtext = %d\n", e.key, e.text);
            itKeyListener    = mKeyListeners.begin();
            itKeyListenerEnd = mKeyListeners.end();
            for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
                if( itKeyListener->second->keyPressed( e ) )
                    break;
            }
        }
		

		//Notice:
		//if ( CEGUI::System::getSingletonPtr() )
		//{
		//	CEGUI::System::getSingletonPtr()->injectKeyDown(e.key);
		//	CEGUI::System::getSingletonPtr()->injectChar(e.text);
		//}

		return true;
	}

	//-----------------------------------------------------------------------
	bool InputManager::keyReleased( const OIS::KeyEvent &e )
	{
		setKeyState( (MG::KeyCode)e.key, OS_RELEASEED );

		itKeyListener    = mKeyListeners.begin();
		itKeyListenerEnd = mKeyListeners.end();
		for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
			if( itKeyListener->second->keyReleased( e ) )
				break;
		}

		//Notice:
		//if ( CEGUI::System::getSingletonPtr() )
		//{
		//	CEGUI::System::getSingletonPtr()->injectKeyUp(e.key);
		//}
		
		return true;
	}

	//-----------------------------------------------------------------------
	bool InputManager::mouseMoved( const OIS::MouseEvent &e )
	{
		itMouseListener    = mMouseListeners.begin();
		itMouseListenerEnd = mMouseListeners.end();
		for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
			if( itMouseListener->second->mouseMoved( e ) )
				break;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	bool InputManager::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
	{
		setMouseState( (MG::MouseCode)id, OS_PRESSED );

		itMouseListener    = mMouseListeners.begin();
		itMouseListenerEnd = mMouseListeners.end();
		for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
			if( itMouseListener->second->mousePressed( e, id ) )
				break;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	bool InputManager::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) 
	{
		setMouseState( (MG::MouseCode)id, OS_RELEASEED );

		itMouseListener    = mMouseListeners.begin();
		itMouseListenerEnd = mMouseListeners.end();
		for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
			if( itMouseListener->second->mouseReleased( e, id ) )
				break;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	bool InputManager::povMoved( const OIS::JoyStickEvent &e, int pov )
	{
		itJoystickListener    = mJoystickListeners.begin();
		itJoystickListenerEnd = mJoystickListeners.end();
		for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
			if(!itJoystickListener->second->povMoved( e, pov ))
				break;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	bool InputManager::axisMoved( const OIS::JoyStickEvent &e, int axis ) {
		itJoystickListener    = mJoystickListeners.begin();
		itJoystickListenerEnd = mJoystickListeners.end();
		for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
			if(!itJoystickListener->second->axisMoved( e, axis ))
				break;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	bool InputManager::sliderMoved( const OIS::JoyStickEvent &e, int sliderID ) {
		itJoystickListener    = mJoystickListeners.begin();
		itJoystickListenerEnd = mJoystickListeners.end();
		for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
			if(!itJoystickListener->second->sliderMoved( e, sliderID ))
				break;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	bool InputManager::buttonPressed( const OIS::JoyStickEvent &e, int button ) {
		itJoystickListener    = mJoystickListeners.begin();
		itJoystickListenerEnd = mJoystickListeners.end();
		for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
			if(!itJoystickListener->second->buttonPressed( e, button ))
				break;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	bool InputManager::buttonReleased( const OIS::JoyStickEvent &e, int button ) {
		itJoystickListener    = mJoystickListeners.begin();
		itJoystickListenerEnd = mJoystickListeners.end();
		for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
			if(!itJoystickListener->second->buttonReleased( e, button ))
				break;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	void InputManager::addKeyListener( OIS::KeyListener *keyListener, const std::string& instanceName ) {
		if( mKeyboard ) {
			// Check for duplicate items
			itKeyListener = mKeyListeners.find( instanceName );
			if( itKeyListener == mKeyListeners.end() ) {
				mKeyListeners[ instanceName ] = keyListener;
			}
			else {
				// Duplicate Item
			}
		}
	}

	//-----------------------------------------------------------------------
	void InputManager::addMouseListener( OIS::MouseListener *mouseListener, const std::string& instanceName ) {
		if( mMouse ) {
			// Check for duplicate items
			itMouseListener = mMouseListeners.find( instanceName );
			if( itMouseListener == mMouseListeners.end() ) {
				mMouseListeners[ instanceName ] = mouseListener;
			}
			else {
				// Duplicate Item
			}
		}
	}

	//-----------------------------------------------------------------------
	void InputManager::addJoystickListener( OIS::JoyStickListener *joystickListener, const std::string& instanceName ) {
		if( mJoysticks.size() > 0 ) {
			// Check for duplicate items
			itJoystickListener = mJoystickListeners.find( instanceName );
			if( itJoystickListener == mJoystickListeners.end() ) {
				mJoystickListeners[ instanceName ] = joystickListener;
			}
			else {
				// Duplicate Item
			}
		}
	}

	//-----------------------------------------------------------------------
	void InputManager::removeKeyListener( const std::string& instanceName ) {
		// Check if item exists
		itKeyListener = mKeyListeners.find( instanceName );
		if( itKeyListener != mKeyListeners.end() ) {
			mKeyListeners.erase( itKeyListener );
		}
		else {
			// Doesn't Exist
		}
	}

	//-----------------------------------------------------------------------
	void InputManager::removeMouseListener( const std::string& instanceName ) {
		// Check if item exists
		itMouseListener = mMouseListeners.find( instanceName );
		if( itMouseListener != mMouseListeners.end() ) {
			mMouseListeners.erase( itMouseListener );
		}
		else {
			// Doesn't Exist
		}
	}

	//-----------------------------------------------------------------------
	void InputManager::removeJoystickListener( const std::string& instanceName ) {
		// Check if item exists
		itJoystickListener = mJoystickListeners.find( instanceName );
		if( itJoystickListener != mJoystickListeners.end() ) {
			mJoystickListeners.erase( itJoystickListener );
		}
		else {
			// Doesn't Exist
		}
	}

	//-----------------------------------------------------------------------
	void InputManager::removeKeyListener( OIS::KeyListener *keyListener ) {
		itKeyListener    = mKeyListeners.begin();
		itKeyListenerEnd = mKeyListeners.end();
		for(; itKeyListener != itKeyListenerEnd; ++itKeyListener ) {
			if( itKeyListener->second == keyListener ) {
				mKeyListeners.erase( itKeyListener );
				break;
			}
		}
	}

	//-----------------------------------------------------------------------
	void InputManager::removeMouseListener( OIS::MouseListener *mouseListener ) {
		itMouseListener    = mMouseListeners.begin();
		itMouseListenerEnd = mMouseListeners.end();
		for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
			if( itMouseListener->second == mouseListener ) {
				mMouseListeners.erase( itMouseListener );
				break;
			}
		}
	}

	//-----------------------------------------------------------------------
	void InputManager::removeJoystickListener( OIS::JoyStickListener *joystickListener ) {
		itJoystickListener    = mJoystickListeners.begin();
		itJoystickListenerEnd = mJoystickListeners.end();
		for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
			if( itJoystickListener->second == joystickListener ) {
				mJoystickListeners.erase( itJoystickListener );
				break;
			}
		}
	}

	//-----------------------------------------------------------------------
	void InputManager::removeAllListeners( void ) {
		mKeyListeners.clear();
		mMouseListeners.clear();
		mJoystickListeners.clear();
	}

	//-----------------------------------------------------------------------
	void InputManager::removeAllKeyListeners( void ) {
		mKeyListeners.clear();
	}

	//-----------------------------------------------------------------------
	void InputManager::removeAllMouseListeners( void ) {
		mMouseListeners.clear();
	}

	//-----------------------------------------------------------------------
	void InputManager::removeAllJoystickListeners( void ) {
		mJoystickListeners.clear();
	}

	//-----------------------------------------------------------------------
	void InputManager::setWindowExtents( int width, int height ) {
		// Set mouse region (if window resizes, we should alter this to reflect as well)
		const OIS::MouseState &mouseState = mMouse->getMouseState();
		mouseState.width  = width;
		mouseState.height = height;
	}

	//-----------------------------------------------------------------------
	OIS::Mouse* InputManager::getMouse( void ) {
		return mMouse;
	}

	//-----------------------------------------------------------------------
	OIS::Keyboard* InputManager::getKeyboard( void ) {
		return mKeyboard;
	}

	//-----------------------------------------------------------------------
	OIS::JoyStick* InputManager::getJoystick( unsigned int index ) {
		// Make sure it's a valid index
		if( index < mJoysticks.size() ) {
			return mJoysticks[ index ];
		}

		return 0;
	}

	//-----------------------------------------------------------------------
	int InputManager::getNumOfJoysticks( void ) {
		// Cast to keep compiler happy ^^
		return (int) mJoysticks.size();
	}
    //-----------------------------------------------------------------------
    LRESULT CALLBACK InputManager::winFunc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
    {
        InputManager* pInstance = InputManager::getSingletonPtr();
        if ( !pInstance )
            return DefWindowProc( hwnd, message, wParam, lParam );

        switch (message)
        {
            //通过输入法获取字符
        case WM_IME_COMPOSITION:
            {
                if ( pInstance->deal_IME_COMPOSITION( hwnd, lParam) )
                    return true;
            }
            break;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
            {
                if ( pInstance->IsIMEHold() )
                {
                    switch (wParam)
                    {
                    case VK_LEFT:
                    case VK_RIGHT:
                    case VK_BACK:
                    case VK_DELETE:
                    case VK_HOME:
                    case VK_END:
                    case VK_UP:
                    case VK_DOWN:
                    case VK_INSERT:
                    case VK_CONTROL:
                    case VK_SHIFT:
                    case VK_RETURN:
                    case VK_F1:
                    case VK_F2:
                    case VK_F3:
                    case VK_F4:
                    case VK_F5:
                    case VK_F6:
                    case VK_F7:
                    case VK_F8:
                    case VK_F9:
                    case VK_F10:
                    case VK_F11:
                    case VK_F12:
                    case VK_ESCAPE:
                        {
                            pInstance->IsIMEHold( false );
                        }
                        break;
                    }
                }              
            }
            break;
        case WM_CHAR:
            {
                if ( pInstance->IsIMEHold() )
                {
                    pInstance->IsIMEHold( false );
                }
            }
            break;
        }
        return CallWindowProc( pInstance->getOldProc(), hwnd, message, wParam, lParam );
    }
    //-----------------------------------------------------------------------
    bool InputManager::deal_IME_COMPOSITION( HWND hWnd, LPARAM lParam )
    {
        HIMC hIMC;
        DWORD dwSize;
        IsIMEHold( true );
        if (lParam & GCS_RESULTSTR)
        {
            hIMC = ImmGetContext( hWnd );
            dwSize = ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, NULL, 0);     
            dwSize += sizeof(WCHAR); 
            int dwCount=dwSize/2; 
            WCHAR *lpWideStr=new WCHAR[dwCount];  
            memset(lpWideStr, 0,dwSize); 
            ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, lpWideStr, dwSize);  
            
            for (int i = 0; i <dwCount ;i++)        
            { 
                IMEkeyPressed( OIS::KeyEvent( NULL, OIS::KeyCode(0), (unsigned int)lpWideStr[i] ) ); 
            }

            ImmReleaseContext( hWnd, hIMC );
        }
        return true;
    }
}

