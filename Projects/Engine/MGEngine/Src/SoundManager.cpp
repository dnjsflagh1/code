/******************************************************************************/
#include "stdafx.h"
#include "SoundManager.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //SoundManager
    /******************************************************************************/
    SINGLETON_DEFINE( SoundALManager )
    //-----------------------------------------------------------------------
    SoundALManager::SoundALManager()
        :mSoundManager(NULL)
    {
        createOgreAL();
    }
    //-----------------------------------------------------------------------
    SoundALManager::~SoundALManager()
    {
        destroyAllSound();
        destroyOgreAL();
    }
    //-----------------------------------------------------------------------
    ISound* SoundALManager::createOrRetriveSound(CChar* name, CChar* fileName, CChar* filePath, Bool isLoop)
    {
        SoundAL* result = NULL;
        std::map<Str,SoundAL*>::iterator iter = mSounds.find(name);
        if ( iter != mSounds.end() )
        {
            result = iter->second;
        }
        if (!result)
        {
			if ( Ogre::ResourceGroupManager::getSingleton().resourceGroupExists(Str(filePath)) == false )
			{
				Ogre::ResourceGroupManager::getSingleton().createResourceGroup(Str(filePath),false);
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Str(filePath), "FileSystem", Str(filePath), false);
				Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(Str(filePath));
			}

			//Str SoundFullPath = name;

			OgreAL::Sound* sound = NULL;
			if ( mSoundManager )
			{
				sound = mSoundManager->createSound(name, fileName, isLoop, false);
				DYNAMIC_ASSERT( sound );
			}

			result = MG_NEW SoundAL(sound);
			mSounds[name] = result;
        }
        return result;
    }
	//-----------------------------------------------------------------------
	void SoundALManager::stopAll(void)
	{
		std::map<Str,SoundAL*>::iterator iter = mSounds.begin();
		for ( ;iter!=mSounds.end();iter++)
		{
			iter->second->stop();
		}
	}
    //-----------------------------------------------------------------------
    void SoundALManager::destroyAllSound()
    {
        std::map<Str,SoundAL*>::iterator iter = mSounds.begin();
        for ( ;iter!=mSounds.end();iter++)
        {
            MG_SAFE_DELETE(iter->second);
        }
        mSounds.clear();
    }
    //-----------------------------------------------------------------------
    void SoundALManager::createOgreAL()
    {
        try {
            Ogre::StringVector deviceList = OgreAL::SoundManager::getDeviceList();
            
            if ( deviceList.size() > 0 )
            {
                mSoundManager = MG_NEW OgreAL::SoundManager(deviceList[0]);
            }
        } catch( Ogre::Exception ex ) {
            String msg = "Sound System init failed because ";
            Ogre::LogManager::getSingletonPtr()->logMessage( msg + ex.getFullDescription(), Ogre::LML_CRITICAL );
            mSoundManager = 0;
        }
    }
    //-----------------------------------------------------------------------
    void SoundALManager::destroyOgreAL()
    {
        MG_SAFE_DELETE(mSoundManager);
    }
    //-----------------------------------------------------------------------
	ISound* SoundALManager::retrieveSound( CChar* name )
	{
		SoundAL* result = NULL;
		std::map<Str,SoundAL*>::iterator iter = mSounds.find(name);
		if ( iter != mSounds.end() )
		{
			result = iter->second;
		}

		return result;
	}
	//-----------------------------------------------------------------------
	MG::Bool SoundALManager::createNewAndSave(CChar* name, CChar* fileName, CChar* filePath, Bool isLoop)
	{

		SoundAL* result = NULL;
		if ( Ogre::ResourceGroupManager::getSingleton().resourceGroupExists(Str(filePath)) == false )
		{
			Ogre::ResourceGroupManager::getSingleton().createResourceGroup(Str(filePath),false);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Str(filePath), "FileSystem", Str(filePath), false);
			Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(Str(filePath));
		}

		//Str SoundFullPath = name;

		OgreAL::Sound* sound = NULL;
		if ( mSoundManager )
		{
			sound = mSoundManager->createSound(name, fileName, isLoop, false);
			DYNAMIC_ASSERT( sound );
		}

		result = MG_NEW SoundAL(sound);
		mSounds[name] = result;

		return true;
	}
	/******************************************************************************/
    //SoundAL
    /******************************************************************************/

    SoundAL::SoundAL(OgreAL::Sound* sound)
        :mSoundAL(sound)
    {

    }
    //-----------------------------------------------------------------------
    SoundAL::~SoundAL()
    {

    }
    //-----------------------------------------------------------------------
    void SoundAL::play()
    {
		if (mSoundAL)
			mSoundAL->play();
    }
    //-----------------------------------------------------------------------
    Bool  SoundAL::isPlaying()
    {
		if (mSoundAL)
			return mSoundAL->isPlaying();
		return false;
    }
    //-----------------------------------------------------------------------
    void SoundAL::stop()
    {
		if (mSoundAL)
			mSoundAL->stop();
    }
    //-----------------------------------------------------------------------
    Bool  SoundAL::isStopped()
    {
		if (mSoundAL)
			return mSoundAL->isStopped();
		return true;
    }
    //-----------------------------------------------------------------------
    void  SoundAL::pause()
    {
		if (mSoundAL)
			mSoundAL->pause();
    }
    //-----------------------------------------------------------------------
    Bool  SoundAL::isPaused()
    {
		if (mSoundAL)
			return mSoundAL->isPaused();
		return true;
    }
    //-----------------------------------------------------------------------
    void  SoundAL::fadeIn( Flt fadeTime )
    {
		if (mSoundAL)
			mSoundAL->fadeIn( fadeTime );
    }
    //-----------------------------------------------------------------------
    void  SoundAL::fadeOut( Flt fadeTime )
    {
		if (mSoundAL)
			mSoundAL->fadeOut( fadeTime );
    }
    //-----------------------------------------------------------------------
    void  SoundAL::setLoop(Bool isLoop)
    {
		if (mSoundAL)
			mSoundAL->setLoop( isLoop );
    }
    //-----------------------------------------------------------------------
    Bool  SoundAL::isLooping()
    {
		if (mSoundAL)
			return  mSoundAL->isLooping();
		return false;
    }
    //-----------------------------------------------------------------------
    void  SoundAL::setPriority(SoundPriority priority)
    {
		if (mSoundAL)
			mSoundAL->setPriority( OgreAL::Sound::Priority(priority) );
    }


}