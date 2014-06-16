/******************************************************************************/

/******************************************************************************/
#ifndef __MG_PACK_TOOL_MANAGER__
#define __MG_PACK_TOOL_MANAGER__


class GameFilePackManager;
namespace MG
{
	// 外部的资源管理器
	class MGPackUpdateManager
	{
	public:
		MGPackUpdateManager();
		virtual ~MGPackUpdateManager();

	public:
		// 更新合并资源包
		bool				resUpdate( const std::string& zipname, const std::string& unzipfolder,
								const std::string& gamefolder, const std::string& tempGamefolder);
		// 删除文件夹和里面的文件(包括子目录,递归)
		bool				deleteTempFolder(LPCSTR lpszPath);

	protected:
		////////////////////////////////////////////////////////////////////////////////////
		// 更新包内部使用接口
		// 把压缩包解压到一个临时目录下.
		bool				unZip(const std::string& zipname, const std::string& unzipfolder);

		// 搜索目录下的资源,并拷贝到临时文件夹
		bool				findCopyPackFile(LPCSTR Path, LPCSTR gamefolder, LPCSTR tempGamefolder);
		// 遍历解压出来的文件夹,保存名字列表,然后把客户端里相同的资源拷贝到另外一个临时目录
		bool				copyClientRes(LPCSTR filename, LPCSTR gamefolder,LPCSTR tempClienResfolder);

		// 合并压缩包
		bool				injectPack(const std::string& unzipfolder, const std::string& tempClienResfolder, 
								StringMap &filemap);


		// 把资源合并后的资源拷贝回客户端
		bool				copyinjectResToGame(LPCSTR filename, LPCSTR gamefolder, LPCSTR tempClienResfolder);

		// 遍历合并后的资源文件夹, 然后把资源拷贝到客户端
		bool				traverseResAndCopy(LPCSTR tempGamefolder, LPCSTR gamefolder);

		
		// 删除文件夹内的文件(包括子目录,递归)
		bool				deleteFiles(LPCSTR lpszPath);
		//

	private:
		// pack管理对象
		MGPackManager *mPackManager;

		// 需要拷贝的.cn文件列表
		StringMap	mPackFileMap;

		// 保存查找文件时候最外层路径, 一个用于做路径对比
		// (因为用的递归,每次这个值都会改,不能用局部变量).
		std::string mfindtempPath;

		//
		std::string mDeleteDirectory;
	};

} 
#endif
