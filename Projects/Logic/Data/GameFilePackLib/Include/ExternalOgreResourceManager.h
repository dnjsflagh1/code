#ifndef __EX_OGRE_RESOURCE_MANAGER__
#define __EX_OGRE_RESOURCE_MANAGER__

#include "OgreExternalInterface.h"

class GameFilePackManager;
namespace MG
{
	// 外部的资源管理器
	class ExOgreResourceManager : public Ogre::IExternalOgreResourceManager
	{
	public:
		ExOgreResourceManager(GameFilePackManager* packManager);
		virtual ~ExOgreResourceManager();

	public:
		// 得到完整路径名(这个就是以前的findExistFile函数)
		virtual std::string		getWholeFilePath( const std::string& fileName, const std::string& type );

		// 文件是否存在
		virtual bool			isFileExist(const std::string& filename);

		// 文件名是完整路径
		virtual bool			extractPackFile( const std::string& pathfilename, MG::MGExtractedPackFile& file );

		// 返回压缩包目录下的文件列表
		virtual MG::StringMap	findZip(const std::string& path, const std::string& pattern);

		// 返回压缩包目录下文件信息列表
		virtual MG::FileInfoVec findZipFileInfo(const std::string& path, const std::string& pattern);

		// 压缩包里是否有资源文件
		virtual bool			isPackResEmpty();
	private:
		GameFilePackManager* mPackManager;
	};

} 
#endif