/******************************************************************************/
// 文件打包加载系统
/******************************************************************************/
#ifndef __MG_EXTERNAL_PACK_MANAGER__
#define __MG_EXTERNAL_PACK_MANAGER__

#include "IMGPackExterInterface.h"

class GameFilePackManager;
namespace MG
{
	// 外部的资源管理器
	class MGExternalPackManager : public IMGExternalPackManager
	{
	public:
		MGExternalPackManager(GameFilePackManager* packManager);
		virtual ~MGExternalPackManager();

	public:
		// 文件名是完整路径
		virtual bool		extractPackFile( const std::string& pathfilename, MG::MGExtractedPackFile& file );
		// 解压缩文件到内存
		// 文件名是完整路径
		virtual bool		extractPackFile( const std::string& pathfilename, char*& buf, int& size );

		// 解压缩文件到内存
		// 文件名是完整路径
		virtual bool		extractPackFile( const std::string& pathfilename, wchar_t*& buf );
		
		// 压缩包里是否有资源文件
		virtual bool		isPackResEmpty();
	private:
		GameFilePackManager* mPackManager;
	};

} 
#endif
