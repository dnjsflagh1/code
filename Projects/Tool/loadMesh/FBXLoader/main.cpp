
#include "FBXLoader.hpp"
#include <Ogre.h>
#include <OgreDefaultHardwareBufferManager.h>

#pragma comment(lib, "OgreMainStatic_d.lib")

int main(int argc, char** argv)
{	
	static Ogre::String s_strDefault = "";
	Ogre::Root* lpRoot = new Ogre::Root(s_strDefault, s_strDefault, s_strDefault);

	CFBXLoader loader;
	if (argc > 1)
	{
		Ogre::DefaultHardwareBufferManager* lpBufferManager = new Ogre::DefaultHardwareBufferManager(); // needed because we don't have a rendersystem
		Ogre::MeshPtr lpMesh = Ogre::MeshManager::getSingleton().createManual("conversion", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		loader.convertFbxToMesh(argv[1], lpMesh.get());
		Ogre::MeshSerializer nSerializer;
		nSerializer.exportMesh(lpMesh.get(), "test.mesh", Ogre::MESH_VERSION_1_8);

		delete lpBufferManager;
	}

	delete lpRoot;
	return 0;
}
