#ifndef __MRTMATERIALLISTENER_H__
#define __MRTMATERIALLISTENER_H__

#include <Ogre.h>
#include <OgreMaterialManager.h>

class MrtMaterialListener : public Ogre::MaterialManager::Listener
{
protected:

public:
	MrtMaterialListener()
	{

	}

	Ogre::Technique *handleSchemeNotFound(unsigned short, const Ogre::String& schemeName, Ogre::Material*mat, unsigned short, const Ogre::Renderable*)
	{
		if (schemeName == "MRT0")
		{
			int i = 0;
			i++;
			//LogManager::getSingleton().logMessage(">> adding glow to material: "+mat->getName());
			//return mBlackMat->getTechnique(0);
		}
		return NULL;
	}
};


#endif