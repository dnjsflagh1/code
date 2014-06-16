//**********************************************************************************************************
#include "stdafx.h"
#include "DEImage.h"
//**********************************************************************************************************
//**********************************************************************************************************
namespace MG
{ 
	std::map<MyGUI::ImageBox*, PVOIDINT_CALLBACK> DEImage::mMapFrameChangeEvent;
	//-----------------------------------------------------------------------------
    DEImage::DEImage()
        :mpEGImage(nullptr)
    {

    }
    //-----------------------------------------------------------------------------
    DEImage::~DEImage()
    {

    }
    //-----------------------------------------------------------------------------
    Bool DEImage::setEGImage( MyGUI::Widget* p )
    {
        assert( p );
        mpEGImage = p->castType<MyGUI::ImageBox>();
        assert( mpEGImage );
        setEGWidget(p);
        return true;
    }
    //-----------------------------------------------------------------------------
    IWidget* DEImage::getWidget()
    {
        setEGWidget(mpEGImage);
        return this;
    }
    //-----------------------------------------------------------------------------
    void DEImage::setTexture( const Str& name )
    {
        assert(mpEGImage);
        mpEGImage->setImageTexture(name);
    }
    //-----------------------------------------------------------------------------
    void DEImage::setTexture( const std::string& _name, const std::string& _group, const std::string& _item )
    {
        assert(mpEGImage);
		mpEGImage->setItemResource("");
        mpEGImage->setItemResource(_name);
        mpEGImage->setItemGroup(_group);
        mpEGImage->setItemName(_item);
    }
    //-----------------------------------------------------------------------------
    bool DEImage::setItemResource( const std::string& _name )
    {
        assert(mpEGImage);
        return mpEGImage->setItemResource(_name);
    }
    //-----------------------------------------------------------------------------
    void DEImage::setItemGroup( const std::string& _value )
    {
        assert(mpEGImage);
        mpEGImage->setItemGroup(_value);
    }
    //-----------------------------------------------------------------------------
    void DEImage::setItemName( const std::string& _value )
    {
        assert(mpEGImage);
        mpEGImage->setItemName(_value);
    }
	//-----------------------------------------------------------------------------
	void DEImage::setImageBroadcast( MGIMAGE_BROADCAST_TYPE type, U32 broadcastTime, U32 totalTime )
	{
		assert(mpEGImage);
		mpEGImage->setImageBroadcast( (MyGUI::IMAGE_BROADCAST_TYPE)( (Int)type ) );
		if ( broadcastTime > 0  &&  totalTime > 0 )
			mpEGImage->setBroadcastTime(broadcastTime, totalTime);
		else
			mpEGImage->setVisible(false);
	}
	//-----------------------------------------------------------------------------
	MG::MGIMAGE_BROADCAST_TYPE DEImage::getImageBroadcast()
	{
		assert(mpEGImage);
		return (MGIMAGE_BROADCAST_TYPE)( (Int)( mpEGImage->getImageBroadcast() ) );
	}
	//-----------------------------------------------------------------------------
	void DEImage::setAngle(Flt angle)
	{
		assert(mpEGImage);
		MyGUI::RotatingSkin* subRotatingSkin = mpEGImage->getSubWidgetMain()->castType<MyGUI::RotatingSkin>();
		if ( subRotatingSkin )
		{
			subRotatingSkin->setAngle(angle);
		}
	}
	//-----------------------------------------------------------------------------
	void DEImage::setUVCoord(Flt left, Flt bottom, Flt width, Flt height)
	{
		assert(mpEGImage);
		MyGUI::ISubWidgetRect* subWidgetRect = mpEGImage->getSubWidgetMain();
		if ( subWidgetRect )
		{
			MyGUI::FloatRect rect = MyGUI::FloatRect(left, bottom, width, height);
			subWidgetRect->_setUVSet(rect);
		}
	}
	//-----------------------------------------------------------------------------
	void DEImage::setRenderTexture( const std::string& name, const std::string& group )
	{
		//////////////////////////////////////////////////////////////////////////////////
		mpEGImage->setRenderItemTexture(NULL);

		//////////////////////////////////////////////////////////////////////////////////
		if ( !Ogre::ResourceGroupManager::getSingleton().resourceGroupExists( group ) )
		{
			return;
		}
		
		//通过OgreMain.dll中的TextureManager来创建一个贴图。
		Ogre::TexturePtr ogreTexture = Ogre::TextureManager::getSingleton().getByName( name, group );

		if ( !ogreTexture.isNull() )
		{
			//////////////////////////////////////////////////////////////////////////////////

			//通过MyGui的渲染管理器创建或者获取一个MyGui的贴图接口。
			string texName = group + "\\" + name;

			MyGUI::ITexture* texture = MyGUI::OgreRenderManager::getInstance().getTexture( texName );
			MyGUI::OgreTexture* _texture = dynamic_cast<MyGUI::OgreTexture*>(texture);

			if ( _texture )
			{
				//MyGui的贴图接口销毁时会把自己关联的Ogre贴图也一并销毁， 所以需要首先把该贴图置空.
				_texture->setOgreTexture(Ogre::TexturePtr());

				MyGUI::OgreRenderManager::getInstance().destroyTexture( texture );
			}

			texture = MyGUI::OgreRenderManager::getInstance().createTexture( texName );

			//////////////////////////////////////////////////////////////////////////////////
			
			//将MyGui的贴图接口和TextureManager创建的贴图关联起来。
			_texture = dynamic_cast<MyGUI::OgreTexture*>(texture);

			if ( _texture )
			{
				_texture->setOgreTexture(ogreTexture);

				mpEGImage->setRenderItemTexture(texture);
			}

			//////////////////////////////////////////////////////////////////////////////////
		}
		return;
	}
	//-----------------------------------------------------------------------------
	void DEImage::setFrameChangeEvent( PVOIDINT_CALLBACK func )
	{
		assert(mpEGImage);
		mMapFrameChangeEvent[mpEGImage] = func;
		mpEGImage->mEventChangeFrame = MyGUI::newDelegate(this, &DEImage::notifyFrameChangeEvent);
	}
	//-----------------------------------------------------------------------------
	void DEImage::notifyFrameChangeEvent( MyGUI::ImageBox* p, Int lastFrame )
	{
		assert(p);
		mpEGImage = p;

		(*mMapFrameChangeEvent[mpEGImage])(mpEGImage, lastFrame);
	}
}