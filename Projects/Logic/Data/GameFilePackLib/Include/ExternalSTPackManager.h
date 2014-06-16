/******************************************************************************/
// SpeedTree文件打包加载系统
/******************************************************************************/
#ifndef __SPEEDTREE_EXTERNAL_PACK_MANAGER__
#define __SPEEDTREE_EXTERNAL_PACK_MANAGER__

#include "IExternalSTPackManager.h"

class GameFilePackManager;
namespace MG
{
	// SpeedTree资源管理器
	class ExternalSTPackManager : public SpeedTree::IExternalSTPackManager
	{
	public:
		ExternalSTPackManager(GameFilePackManager* packManager);
		virtual ~ExternalSTPackManager();

	public:
		// 解压缩文件到内存
		// 文件名是完整路径
		virtual bool		extractPackFile( const char* pathfilename, char*& buf, int& size );

		// 解压缩文件到内存
		// 文件名是完整路径
		virtual bool		extractPackFile( const char* pathfilename, wchar_t*& buf);

	private:
		GameFilePackManager* mPackManager;
	};

} 
#endif
