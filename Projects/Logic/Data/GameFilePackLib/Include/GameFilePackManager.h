/******************************************************************************/
#ifndef _GAMEFILEPACKMANAGER_H
#define _GAMEFILEPACKMANAGER_H
/******************************************************************************/

#include "Singleton.h"
#include "GameFilePackPreqs.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    // 文件打包加载系统
    /******************************************************************************/
	class GameFilePackManager
    {
    public:

        SINGLETON_INSTANCE(GameFilePackManager);
        GameFilePackManager();
        virtual ~GameFilePackManager();

	public:

		/** 
			# 加载所有打包文件
			@ 打包文件遍历Config和Media下所有的CN文件并加载
		*/
		void		load();
		// 卸载所有打包文件
		void		unload();

		// 得到完整路径名(这个就是以前的findExistFile函数)
		std::string	getWholeFilePath( const std::string& fileName, const std::string& type );

		// 解压缩文件到内存
		// 文件名是完整路径
		bool		extractPackFile( const std::string& pathfilename, MGExtractedPackFile& file );

		// 解压缩文件到内存
		// 文件名是完整路径
		bool		extractPackFile( const std::string& pathfilename, char*& buf, Int& size );

		// 解压缩文件到内存
		// 文件名是完整路径
		bool		extractPackFile( const std::string& pathfilename, wchar_t*& buf );

		// 文件是否存在
		bool		isFileExist(const std::string& filename);

		// Ogre使用
		// 返回压缩包目录下的文件列表
		StringMap	findZip(const std::string& path, const std::string& pattern);

		// 返回压缩包目录下文件信息列表
		FileInfoVec findZipFileInfo(const std::string& path, const std::string& pattern);

		// 压缩包里是否有资源文件
		bool		isPackResEmpty();

	protected:

		////////////////////////////////////////////////////////////////////////////////////
		// 得到打包文件集，通过完整路径名
		IMGPackFileSet*		getPackFileSetFromPath( const std::string& filePath );

		// 得到打包文件集，通过类型
		IMGPackFileSet*		getPackFileSetFromType( const std::string& type );

		////////////////////////////////////////////////////////////////////////////////////
		/**
			查找当前目录下的config和media文件夹,并加载压缩文件(.cn文件可以读取,已加密测试过)
			找路径下的文件(.cn)并加载.
		*/
		void				findAndLoadPackFile(LPCSTR Path, LPCSTR filter);
		/** 
			# 读取资源包的结构
			# 并保存资源包目录结构
		*/
		void				loadPackFile( const std::string& filename, const char* password );
		// 卸载资源包
		void				unloadAllPackFile();

	private:

		/////////////////////////////////////////////////////////////////////////
		// 所有打包文件对象映射列表
		ZIP_ARC_MAP	mPackSet;

		/////////////////////////////////////////////////////////////////////////
		// 所有压缩包的路径映射
		// 完整路径(包括Config/Base..这类外部字符串)做key值, 压缩包类型value.
		// 用于传路径进来得到压缩包类型(getPackFileSetFromPath返回IMGPackFileSet*)
		StringMap mPathPackType;

		/////////////////////////////////////////////////////////////////////////
		// OGRE 使用的中间目录结构
		// 把文件路径相同的文件归类.路径为key值,value值为路径相同的文件.
		ResClassifyPathMap	mClassifyPathMap;

		// 同一路径下同一文件类型的列表归类.
		ResClassifyPathTypeMap	mClassifyPathTypeMap;
		//////////////////////////////////////////////////////////////////////////

		// pack管理对象
		MGPackManager *mPackManager;
    };

}


#endif	
