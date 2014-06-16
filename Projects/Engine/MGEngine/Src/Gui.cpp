/******************************************************************************/
#include "stdafx.h"
#include "Gui.h"
#include "EngineMain.h"
#include "Scene.h"
#include "GuiDelegateElementPool.h"
#include "GuiElempoolEx.h"
#include "MyGUI_LayerManager.h"
#include "MyGUI_InputManager.h"
#include "MGPointer.h"
#include "newFuction.h"
#include "DEFont.h"

// MG_CN_MODIFY
#include "MyGUI_OgreDataStream.h"
/******************************************************************************/

namespace MG
{
#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32

    MyGUI::Char translateWin32Text(MyGUI::KeyCode kc)
    {
        static WCHAR deadKey = 0;

        BYTE keyState[256];
        HKL  layout = GetKeyboardLayout(0);
        if ( GetKeyboardState(keyState) == 0 )
            return 0;

        int code = *((int*)&kc);
        unsigned int vk = MapVirtualKeyEx((UINT)code, 3, layout);
        if ( vk == 0 )
            return 0;

        WCHAR buff[3] = { 0, 0, 0 };
        int ascii = ToUnicodeEx(vk, (UINT)code, keyState, buff, 3, 0, layout);
        if (ascii == 1 && deadKey != '\0' )
        {
            // A dead key is stored and we have just converted a character key
            // Combine the two into a single character
            WCHAR wcBuff[3] = { buff[0], deadKey, '\0' };
            WCHAR out[3];

            deadKey = '\0';
            if(FoldStringW(MAP_PRECOMPOSED, (LPWSTR)wcBuff, 3, (LPWSTR)out, 3))
                return out[0];
        }
        else if (ascii == 1)
        {
            // We have a single character
            deadKey = '\0';
            return buff[0];
        }
        else if(ascii == 2)
        {
            // Convert a non-combining diacritical mark into a combining diacritical mark
            // Combining versions range from 0x300 to 0x36F; only 5 (for French) have been mapped below
            // http://www.fileformat.info/info/unicode/block/combining_diacritical_marks/images.htm
            switch(buff[0])	{
            case 0x5E: // Circumflex accent: ?
                deadKey = 0x302; break;
            case 0x60: // Grave accent: ?
                deadKey = 0x300; break;
            case 0xA8: // Diaeresis: ?
                deadKey = 0x308; break;
            case 0xB4: // Acute accent: ?
                deadKey = 0x301; break;
            case 0xB8: // Cedilla: ?
                deadKey = 0x327; break;
            default:
                deadKey = buff[0]; break;
            }
        }

        return 0;
    }

#endif
    //-----------------------------------------------------------------------
    Gui::Gui(CChar* resourceFileName, CChar* coreFileName, Scene* scene)
        :mMyGUI(NULL)
        ,mPlatform(NULL)                       
        ,mScene(scene)
    {
        setupResources( resourceFileName );

        mPlatform = MG_NEW MyGUI::OgrePlatform();
        mPlatform->initialise(OgreMainInterface::renderWindow, mScene->mOgreSceneManager);

		mMyGUI = MG_NEW MyGUI::Gui();
		mMyGUI->initialise(coreFileName);
        
    }
    //-----------------------------------------------------------------------
    Gui::~Gui()
    {
        //MG_SAFE_DELETE( mInfo );
        //MG_SAFE_DELETE( mFocusInfo );

		//反初始化控件池
		GuiDgElmPoolEx::getInstance().unInitialize();

		//清空界面
		clear();

		//清空所以引擎对象
        if (mMyGUI)
		{
			mMyGUI->shutdown();
            MG_SAFE_DELETE( mMyGUI );
		}

		//清空平台对象
		if (mPlatform)
		{
			mPlatform->shutdown();
            MG_SAFE_DELETE( mPlatform );
		}
        
    }
	//-----------------------------------------------------------------------
	Bool Gui::setupResources(const Str fileName)
	{
		MyGUI::xml::Document doc;

		// MG_CN_MODIFY
		if (!doc.open(fileName))
		{
			Ogre::DataStreamPtr stream = 
				Ogre::ResourceGroupManager::getSingleton().openResource(fileName, "");
			MyGUI::OgreDataStream* data = new MyGUI::OgreDataStream(stream);
			if(!doc.open(data))
				doc.getLastError();
		}

		MyGUI::xml::ElementPtr root = doc.getRoot();
		if (root == nullptr || root->getName() != "Paths")
			return false;

		MyGUI::xml::ElementEnumerator node = root->getElementEnumerator();
		while (node.next())
		{
			if (node->getName() == "Path")
			{
				bool rootAttr = false;
				if (node->findAttribute("root") != "")
				{
					rootAttr = MyGUI::utility::parseBool(node->findAttribute("root"));
					if (rootAttr) mRootMedia = node->getContent();
				}

				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(node->getContent(), 
					"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, false);
			}
		}

        return true;
	}

	//-----------------------------------------------------------------------
	Layout* Gui::loadLayOut( const Str8 _fileName )
	{
	    assert(_fileName.length() > 1);
        //创建新的layout。
        Layout* tempLayout = MG_NEW Layout(_fileName);
        assert(tempLayout);
        //将layout加入map
        mLayouts[_fileName] = tempLayout;     

		return tempLayout;
	}
    //-----------------------------------------------------------------------
    Layout* Gui::getLayOut(const Str8 fileName)
    {
       assert(fileName.length() > 1);
       //查找
       std::map<Str , Layout*>::iterator pos = mLayouts.find(fileName);
       if( pos != mLayouts.end() )
           return pos->second;

       //如果没有找到，加载一次。
       return loadLayOut( fileName ); 
    }
    //-----------------------------------------------------------------------
    void Gui::clear()
    {
        std::map<Str , Layout*>::iterator pos = mLayouts.begin();
        while ( pos != mLayouts.end() )
        {
            MG_DELETE pos->second;
            ++pos;
        }
        mLayouts.clear();
    }
    //-----------------------------------------------------------------------
    bool Gui::keyPressed( const OIS::KeyEvent &e )
    {
        if (!mMyGUI)
            return false;

        MyGUI::Char text = (MyGUI::Char)e.text;
        MyGUI::KeyCode key = MyGUI::KeyCode::Enum(e.key);

        if ( text <= 0xFF )
        {
            int scan_code = key.toValue();

            if (scan_code > 70 && scan_code < 84)
            {
                static MyGUI::Char nums[13] = { 55, 56, 57, 45, 52, 53, 54, 43, 49, 50, 51, 48, 46 };
                text = nums[scan_code-71];
            }
            else if (key == MyGUI::KeyCode::Divide)
            {
                text = '/';
            }
            else
            {
#if MYGUI_PLATFORM == MYGUI_PLATFORM_WIN32
                text = translateWin32Text(key);
#endif
            }   
        }

        return mMyGUI->injectKeyPress( key, text );
    }
    //-----------------------------------------------------------------------
    bool Gui::keyReleased( const OIS::KeyEvent &e )
    {
        if (!mMyGUI)
            return false;
        return mMyGUI->injectKeyRelease( MyGUI::KeyCode::Enum(e.key) );
    }
    //-----------------------------------------------------------------------
    bool Gui::mouseMoved( const OIS::MouseEvent &e )
    {
        if (!mMyGUI)
            return false;
        return mMyGUI->injectMouseMove(e.state.X.abs, e.state.Y.abs, e.state.Z.abs);
    }
    //-----------------------------------------------------------------------
    bool Gui::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
    {
        if (!mMyGUI)
            return false;
        return mMyGUI->injectMousePress(e.state.X.abs, e.state.Y.abs, (MyGUI::MouseButton::Enum)id);
    }
    //-----------------------------------------------------------------------
    bool Gui::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
    {
        if (!mMyGUI)
            return false;
        return mMyGUI->injectMouseRelease(e.state.X.abs, e.state.Y.abs, (MyGUI::MouseButton::Enum)id);
    }
    //-----------------------------------------------------------------------
    void Gui::SeeInfo(Flt delta)
    {
        //if (mInfo)
        //{
        //    static float time = 0.f;
        //    time += delta;
        //    if (time > 1)
        //    {
        //        time -= 1;
        //        try
        //        {
        //            const Ogre::RenderTarget::FrameStats& stats = OgreMainInterface::renderWindow->getStatistics();
        //            mInfo->change("FPS", (int)stats.lastFPS);
        //            mInfo->change("triangle", stats.triangleCount);
        //            mInfo->change("batch", stats.batchCount);
        //            //mInfo->change("batch gui", MyGUI::RenderManager::getInstance().getBatch());
        //            mInfo->update();
        //        }
        //        catch (...)
        //        {
        //        }
        //    }
        //}
    }
    //-----------------------------------------------------------------------
    IText* Gui::getText( const MGTextDs* pTds, CoordI coord, std::wstring caption, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getText(pTds, coord, caption, isTop);
    }
    //-----------------------------------------------------------------------
    IText* Gui::getText( const MGTextDs* pTds, VecI2 pos, VecI2 size, std::wstring caption, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getText(pTds, CoordI(pos.x, pos.y, size.x, size.y), caption, isTop);
    }
    //-----------------------------------------------------------------------
    IText* Gui::getText( const MGTextDs* pTds, Int left, Int top, Int width, Int height, std::wstring caption, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getText(pTds, CoordI(left, top, width, height), caption, isTop);
    }
    //-----------------------------------------------------------------------
    IImage* Gui::getImage( CoordI coord, std::string imagename, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getImage(coord, imagename, isTop);
    }
    //-----------------------------------------------------------------------
    IImage* Gui::getImage( VecI2 pos, VecI2 size, std::string imagename, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getImage(CoordI(pos.x, pos.y, size.x, size.y), imagename, isTop);
    }
    //-----------------------------------------------------------------------
    IImage* Gui::getImage( Int left, Int top, Int width, Int height, std::string imagename, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getImage(CoordI(left, top, width, height), imagename, isTop);
    }
    //-----------------------------------------------------------------------
    IImage* Gui::getImage( CoordI coord, std::string imagenrecouse, std::string group, std::string item, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getImage(coord, imagenrecouse, group, item, isTop);
    }
    //-----------------------------------------------------------------------
    IImage* Gui::getImage( VecI2 pos, VecI2 size, std::string imagenrecouse, std::string group, std::string item, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getImage(CoordI(pos.x, pos.y, size.x, size.y), imagenrecouse, group, item, isTop);
    }
    //-----------------------------------------------------------------------
    IImage* Gui::getImage( Int left, Int top, Int width, Int height, std::string imagenrecouse, std::string group, std::string item, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getImage(CoordI(left, top, width, height), imagenrecouse, group, item, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGText( const MGTextDs*& pTds, CoordI coord, std::wstring caption, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGText(pTds, coord, caption, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGText( const MGTextDs*& pTds, VecI2 pos, VecI2 size, std::wstring caption, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGText(pTds, CoordI(pos.x, pos.y, size.x, size.y), caption, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGText( const MGTextDs*& pTds, Int left, Int top, Int width, Int height, std::wstring caption, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGText(pTds, CoordI(left, top, width, height), caption, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGImage( CoordI coord, std::string imagename, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGImage(coord, imagename, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGImage( VecI2 pos, VecI2 size, std::string imagename, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGImage(CoordI(pos.x, pos.y, size.x, size.y), imagename, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGImage( Int left, Int top, Int width, Int height, std::string imagename, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGImage(CoordI(left, top, width, height), imagename, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGImage( CoordI coord, std::string imagenrecouse, std::string group, std::string item, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGImage(coord, imagenrecouse, group, item, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGImage( VecI2 pos, VecI2 size, std::string imagenrecouse, std::string group, std::string item, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGImage(CoordI(pos.x, pos.y, size.x, size.y), imagenrecouse, group, item, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGImage( Int left, Int top, Int width, Int height, std::string imagenrecouse, std::string group, std::string item, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGImage(CoordI(left, top, width, height), imagenrecouse, group, item, isTop);
    }
    //-----------------------------------------------------------------------
    IEdit* Gui::getEdit( const MGTextDs* pTds, CoordI coord, std::wstring caption, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getEdit(pTds, coord, caption, isTop);
    }
    //-----------------------------------------------------------------------
    IEdit* Gui::getEdit( const MGTextDs* pTds, VecI2 pos, VecI2 size, std::wstring caption, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getEdit(pTds, CoordI(pos.x, pos.y, size.x, size.y), caption, isTop);
    }
    //-----------------------------------------------------------------------
    IEdit* Gui::getEdit( const MGTextDs* pTds, Int left, Int top, Int width, Int height, std::wstring caption, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getEdit(pTds, CoordI(left, top, width, height), caption, isTop);
    }
    //-----------------------------------------------------------------------
    IProgress* Gui::getProgress( CoordI coord, U32 range, U32 position, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getProgress(coord, range, position, isTop);
    }
    //-----------------------------------------------------------------------
    IProgress* Gui::getProgress( VecI2 pos, VecI2 size, U32 range, U32 position, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getProgress(CoordI(pos.x, pos.y, size.x, size.y), range, position, isTop);
    }
    //-----------------------------------------------------------------------
    IProgress* Gui::getProgress( Int left, Int top, Int width, Int height, U32 range, U32 position, Bool isTop )
    {
        return GuiDgElmPoolEx::getInstance().getProgress(CoordI(left, top, width, height), range, position, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGEdit( const MGTextDs* pTds, CoordI coord, std::wstring caption, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGEdit(pTds, coord, caption, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGEdit( const MGTextDs* pTds, VecI2 pos, VecI2 size, std::wstring caption, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGEdit(pTds, CoordI(pos.x, pos.y, size.x, size.y), caption, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGEdit( const MGTextDs* pTds, Int left, Int top, Int width, Int height, std::wstring caption, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGEdit(pTds, CoordI(left, top, width, height), caption, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGProgress( CoordI coord, U32 range, U32 position, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGProgress(coord, range, position, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGProgress( VecI2 pos, VecI2 size, U32 range, U32 position, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGProgress(CoordI(pos.x, pos.y, size.x, size.y), range, position, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::MGProgress( Int left, Int top, Int width, Int height, U32 range, U32 position, Bool isTop )
    {
        GuiDgElmPoolEx::getInstance().MGProgress(CoordI(left, top, width, height), range, position, isTop);
    }
    //-----------------------------------------------------------------------
    void Gui::destroyEdit( IEdit*& pEdit )
    {
		if ( pEdit == NULL )
			return;
        DEEdit* ptemp = dynamic_cast<DEEdit*>(pEdit);
        GuiDgElmPoolEx::getInstance().removeEdit(ptemp);
        pEdit = ptemp;
    }
    //-----------------------------------------------------------------------
    void Gui::destroyProgress( IProgress*& pProgress )
    {
		if ( pProgress == NULL )
			return;
        DEProgress* ptemp = dynamic_cast<DEProgress*>(pProgress);
        GuiDgElmPoolEx::getInstance().removeProgress(ptemp);
        pProgress = ptemp;
    }
    //-----------------------------------------------------------------------
    void Gui::preUpdate()
    {
        GuiDgElmPoolEx::getInstance().preUpdateClear();
    }
	void Gui::update(Flt delta)
	{
		GuiFuction::getInstance().update(delta);
	}
    //-----------------------------------------------------------------------
    void Gui::destroyImage( IImage*& pImage )
    {
		if ( pImage == NULL )
			return;
        DEImage* ptemp = dynamic_cast<DEImage*>(pImage); 
        GuiDgElmPoolEx::getInstance().removeImage( ptemp );
        pImage = ptemp;
    }
    //-----------------------------------------------------------------------
    void Gui::destroyText( IText*& pText )
    {
		if ( pText == NULL )
			return;
        DEText* ptemp = dynamic_cast<DEText*>(pText);
        GuiDgElmPoolEx::getInstance().removeText( ptemp );
        pText = ptemp;
    }
    //-----------------------------------------------------------------------
    MG::U32 Gui::getLengthStr( Str16 src, Str8 fontName /*= ""*/ )
    {
        MyGUI::FontManager* pFontManager = MyGUI::FontManager::getInstancePtr();
        assert(pFontManager);
        if ( fontName == "" )
        {
            fontName = pFontManager->getDefaultFont();
        }
        MyGUI::IFont* pFont = pFontManager->getByName(fontName);

        U32 length = 0;
        U32 nCount = src.length();
        for (U32 i=0; i<nCount; i++)
        {
            length += pFont->getGlyphInfo( src[i] )->width;
        }
        
        return length;
    }
    //-----------------------------------------------------------------------
    MG::U32 Gui::getLengthStr( Str8 src, Str8 fontName /*= ""*/ )
    {
        Str16 wsrc;
        MGStrOp::toString(src.c_str(), wsrc);

        return getLengthStr(wsrc, fontName);
    }
    //-----------------------------------------------------------------------
    MG::U32 Gui::getHeightStr( Str16 src, Int width, Str8 fontName/* = ""*/ )
    {
        Int length = getLengthStr(src, fontName);
        Int height = getHeightChar(fontName);

        Int row = length/width;
        if ( length%width == 0 )
            return row * height;
        else
            return (row +1) * height;

    }
    //-----------------------------------------------------------------------
    MG::U32 Gui::getHeightStr( Str8 src, Int width, Str8 fontName /*= ""*/ )
    {
        Int length = getLengthStr(src, fontName);
        Int height = getHeightChar(fontName);

        Int row = length/width;
        if ( length%width == 0 )
            return row * height;
        else
            return (row +1) * height;
    }
    //-----------------------------------------------------------------------
    U32 Gui::getHeightStrAddBreak(Str16& src, Int width, Str8 fontName)
    {
        MyGUI::FontManager* pFontManager = MyGUI::FontManager::getInstancePtr();
        assert(pFontManager);
        if ( fontName == "" )
        {
            fontName = pFontManager->getDefaultFont();
        }
        MyGUI::IFont* pFont = pFontManager->getByName(fontName);

        U32 row = 1;
        U32 length = 0;
        U32 lastLineBreak = 0;
        U32 nCount = src.length();
        Str16 tempStr;
		Str16 tempSrc;
        for (U32 i=0; i<nCount; i++)
        {
            if ( length + pFont->getGlyphInfo( src[i] )->width > UInt(width) )
            {
                //重新设置字符串
                tempStr = src.substr(lastLineBreak, i-lastLineBreak);
                tempStr += L'\n';
                tempSrc += tempStr;
                //数据重置
                lastLineBreak = i;
                length = 0;
                ++row;
            }
            else
                length += pFont->getGlyphInfo( src[i] )->width;
        }
		//设置字符串
		tempSrc += src.substr(lastLineBreak, nCount-lastLineBreak);
		src = tempSrc;

        return row * pFont->getDefaultHeight();
    }
    //-----------------------------------------------------------------------
    U32 Gui::getHeightStrAddBreak(Str8& src, Int width, Str8 fontName)
    {
        Str16 wsrc;
        MGStrOp::toString(src.c_str(), wsrc);

        U32 height = getHeightStrAddBreak(wsrc, width, fontName);
        
        MGStrOp::toString(wsrc.c_str(), src);

        return height;
    }
    //-----------------------------------------------------------------------
    MG::U32 Gui::getHeightChar( Str8 fontName /*= ""*/ )
    {
        MyGUI::FontManager* pFontManager = MyGUI::FontManager::getInstancePtr();
        assert(pFontManager);
        if ( fontName == "" )
        {
            fontName = pFontManager->getDefaultFont();
        }
        MyGUI::IFont* pFont = pFontManager->getByName(fontName);

        return pFont->getDefaultHeight();
    }
    //-----------------------------------------------------------------------
    MG::VecI2 Gui::getImageSize( Str8 textureName )
    {
        const MyGUI::IntSize tempsize = MyGUI::texture_utility::getTextureSize(textureName);
        return VecI2(tempsize.width, tempsize.height);
    }
    //-----------------------------------------------------------------------
    MG::VecI2 Gui::getImageSize( Str8 imageRecouse, Str8 group, Str8 item )
    {
        MyGUI::IResourcePtr resource = MyGUI::ResourceManager::getInstance().getByName(imageRecouse, false);
        assert(resource);
        if (resource)
        {    
            MyGUI::ResourceImageSetPtr _resource = resource->castType<MyGUI::ResourceImageSet>();
            assert(_resource);
            if ( _resource )
            {
                MyGUI::ImageIndexInfo imageindexinfo = _resource->getIndexInfo(group, item);
                return VecI2(imageindexinfo.size.width, imageindexinfo.size.height);
            }
        }
        return VecI2(0, 0);
    }
    //-----------------------------------------------------------------------
    MG::U32 Gui::getIndexByWidth( Str16 src, U32 width, Str8 fontName /*= ""*/ )
    {
        MyGUI::FontManager* pFontManager = MyGUI::FontManager::getInstancePtr();
        assert(pFontManager);
        if ( fontName == "" )
        {
            fontName = pFontManager->getDefaultFont();
        }
        MyGUI::IFont* pFont = pFontManager->getByName(fontName);

        U32 length = 0;
        U32 nCount = src.length();
        for (U32 i=0; i<nCount; i++)
        {
            length += pFont->getGlyphInfo( src[i] )->width;
            if ( length > width )
                return i;
        }

        return nCount;
    }
    //-----------------------------------------------------------------------
    MG::U32 Gui::getIndexByWidth( Str8 src, U32 width, Str8 fontName /*= ""*/ )
    {
        Str16 wsrc;
        MGStrOp::toString(src.c_str(), wsrc);

        return getIndexByWidth(wsrc, width, fontName);
    }
    //-----------------------------------------------------------------------
	void Gui::resizeWindow( Ogre::RenderWindow* window )
    {
        //MyGUI::IntSize tempSize(nScreenX, nScreenY);
		//MyGUI::LayerManager::getInstance().resizeView(tempSize);
		MyGUI::OgreRenderManager::getInstance().windowResized( window );
    }
	//-----------------------------------------------------------------------
	void Gui::resizeWindow()
	{
		MyGUI::OgreRenderManager::getInstance().windowResized( OgreMainInterface::renderWindow );
	}
	//-----------------------------------------------------------------------
	MG::Bool Gui::isMouseCanHoldUI()
	{
		return MyGUI::InputManager::getInstance().isFocusMouse();
	}
	//-----------------------------------------------------------------------
	MG::Bool Gui::isKeyCanHoldUI()
	{
		return MyGUI::InputManager::getInstance().isFocusKey();
	}
	//-----------------------------------------------------------------------
	void Gui::init( Str8 fontName, IPointer*& pIPointer, IFont*& pIFont )
	{
		MyGUI::FontManager::getInstance().setTrueFontName(fontName, true);

		pIPointer = &MGPointer::getInstance();

		pIFont = &DEFont::getInstance();

		//初始化最早的两个界面
		GuiDgElmPoolEx::getInstance().Initialize();

	}
	//*****************************************************************************************************
    #define MAIN_WIDGET "_Main"
    //*****************************************************************************************************
    //class layout
    Layout::Layout(Str8 fileName)
		:mMainWidget(NULL)
    {
        //获取控件指针容器。
        mElements = MyGUI::LayoutManager::getInstance().load(fileName);
        assert(mElements.size() > 0);
        //获得父控件指针。
        for (MyGUI::VectorWidgetPtr::iterator iter=mElements.begin(); iter!=mElements.end(); ++iter)
        {
            if ((*iter)->getName() == MAIN_WIDGET)
            {
                mMainWidget = (*iter);
                break;
            }
        }
        assert( mMainWidget != nullptr );
    }
    //------------------------------------------------------------------------------
    Layout::~Layout()
    {
       //shunDown();  
    }
    //------------------------------------------------------------------------------
    Bool Layout::isVisible()
    {
        assert( mMainWidget != nullptr );
        return mMainWidget->isVisible();
    }
    //------------------------------------------------------------------------------
    void Layout::setVisible(Bool bVisible)
    {
        assert( mMainWidget != nullptr );
        mMainWidget->setVisible(bVisible);
        if ( bVisible == true )
            MyGUI::LayerManager::getInstance().upLayerItem(mMainWidget);
    }
    //------------------------------------------------------------------------------
    void Layout::shunDown()
    {
        MyGUI::LayoutManager::getInstance().unloadLayout(mElements);
        mElements.clear();
    }
    //------------------------------------------------------------------------------
    IButton* Layout::getButton( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEButton(p);
    }
    //------------------------------------------------------------------------------
    IEdit* Layout::getEdit( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEEdit(p);
    }
    //------------------------------------------------------------------------------
    IForm* Layout::getForm( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEForm(p);
    }
    //------------------------------------------------------------------------------
    IImage* Layout::getImage( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEImage(p);
    }
    //------------------------------------------------------------------------------
    IProgress* Layout::getProgress( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEProgress(p);
    }
    //------------------------------------------------------------------------------
    IText* Layout::getText( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEText(p);
    }
    //------------------------------------------------------------------------------
    IViewScroll* Layout::getViewScroll( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEViewScroll(p);
    }
    //------------------------------------------------------------------------------
    IWidget* Layout::getWidget( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEWidget(p);
    }
    //------------------------------------------------------------------------------
    IList* Layout::getList( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEList(p);
    }
    //------------------------------------------------------------------------------
    ITab* Layout::getTab( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDETab(p);
    }
    //------------------------------------------------------------------------------
    ITabItem* Layout::getTabItem( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDETabItem(p);
    }
    //------------------------------------------------------------------------------
    IComboBox* Layout::getComboBox( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEComboBox(p);
    }
    //------------------------------------------------------------------------------
    IMixTree* Layout::getMixTree( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEMixTree(p);
    }
    //------------------------------------------------------------------------------
    IRollingText* Layout::getRollingText( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDERollingText(p);
    }
    //------------------------------------------------------------------------------
    IMixList* Layout::getMixList( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEMixList(p);
    }
    //------------------------------------------------------------------------------
    IMixListRow* Layout::getMixListRow( const Str8 name )
    {
        MyGUI::Widget* p = mElements.at(0)->findWidget(name);
        assert( p != nullptr );

        return GuiDgElmPool::getInstance().getDEMixListRow(p);
    }
    //------------------------------------------------------------------------------
    MG::Bool Layout::isMouseInUI()
    {
        if ( mMainWidget->isVisible() == false )
            return false;

        //根据鼠标位置找到当前的控件
        const MyGUI::IntPoint& curPos = MyGUI::InputManager::getInstance().getMousePosition(); 
        MyGUI::Widget* p = MyGUI::LayerManager::getInstance().getWidgetFromPoint(curPos.left, curPos.top);

        //如果不等于主控件，说明不再此UI中。
        while (p != mMainWidget)
        {
            if ( p == NULL )
                return false;

            p = p->getParent();
        }

        return true;
    }
	//------------------------------------------------------------------------------
	IHScroll* Layout::getHScroll( const Str8 name )
	{
		MyGUI::Widget* p = mElements.at(0)->findWidget(name);
		assert( p != nullptr );

		return GuiDgElmPool::getInstance().geDEHScroll(p);
	}
	//------------------------------------------------------------------------------
	IVScroll* Layout::getVScroll( const Str8 name )
	{
		MyGUI::Widget* p = mElements.at(0)->findWidget(name);
		assert( p != nullptr );

		return GuiDgElmPool::getInstance().geDEVScroll(p);
	}
	//------------------------------------------------------------------------------
	ITimeText* Layout::getTimeText( const Str8 name )
	{
		MyGUI::Widget* p = mElements.at(0)->findWidget(name);
		assert( p != nullptr );

		return GuiDgElmPool::getInstance().getDETimeText(p);
	}
}

