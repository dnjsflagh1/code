//*************************************************************************************************//
#ifndef _PRINT_WINDOWS_CFG_H_
#define _PRINT_WINDOWS_CFG_H_
//*************************************************************************************************//

	
//*************************************************************************************************//
namespace MG
{

	struct PrintWindowsCfgInfo
	{
		Int		printMap;					//打印 地图信息  0. 不打印  1. 打印
		Int		printPlayer;				//打印 玩家信息  0. 不打印  1. 打印
		Int		printPlayerCharacter;		//打印 角色信息  0. 不打印  1. 打印
	
		PrintWindowsCfgInfo()
			:printMap(0)
			,printPlayer(0)
			,printPlayerCharacter(0)
		{
		}
	};

	//*************************************************************************************************//
	class PrintWindowsCfg
	{
	public:
	public:
		PrintWindowsCfg();
		~PrintWindowsCfg();
		SINGLETON_INSTANCE(PrintWindowsCfg);

	public:
		// MG_CN_MODIFY
		Bool					loadFile(std::wstring fileName, IMGExternalPackManager* packManager = NULL);
		
		Int						getPrintMap();
		Int						getPrintPlayer();
		Int						getPrintPlayerCharacter();

	protected:
		void                unloadFile();
	
	private:
		PrintWindowsCfgInfo*	getConfig();
	private:
		std::vector<PrintWindowsCfgInfo>        mPrintWindowConfigList;
	};
}

#endif	//_PRINT_WINDOWS_CFG_H_