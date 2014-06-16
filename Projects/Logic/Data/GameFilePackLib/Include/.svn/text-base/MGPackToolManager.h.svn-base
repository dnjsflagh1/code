/******************************************************************************/

/******************************************************************************/
#ifndef __MG_PACK_TOOL_MANAGER__
#define __MG_PACK_TOOL_MANAGER__


class GameFilePackManager;
namespace MG
{
	// 外部的资源管理器
	class MGPackToolManager
	{
	public:

		MGPackToolManager();
		virtual ~MGPackToolManager();

	public:

		// 打包游戏散包资源为多个CN格式文件
		bool		packGameRes(const std::string& src, const std::string& des);

		// 对比部分用到的
		// 读取新资源目录,保存文件名
		void		loadNewResFolder(LPCSTR newResPath);
		// 对比和拷贝
		bool		compareAndCopy(LPCSTR lastResPath, LPCSTR newResPath, LPCSTR packFolder);
		// 对比MD5码
		bool		compareMD5(FILE* lastResFile,FILE* newResFile);

	private:
		// pack管理对象
		MGPackManager *mPackManager;

		// 新资源目录下的文件列表
		std::list<std::string>	mNewResFileList;

		// 记录新资源最外层的路径
		std::string				mNewResPath;
	};

} 
#endif
