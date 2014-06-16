//*************************************************************************************************//
#ifndef _H_CSELECTSERVERCONFIG_
#define _H_CSELECTSERVERCONFIG_
//*************************************************************************************************//
namespace MG
{
    //*************************************************************************************************//
    class CSelectServerConfig 
    {
    public:
        struct ServerConfig
        {
            std::wstring mServerName;            //服务器名称
            std::wstring mServerIP;              //服务器IP
            Int mPort;                          //服务器端口
        };
    public:
        CSelectServerConfig();
        ~CSelectServerConfig();
        SINGLETON_INSTANCE(CSelectServerConfig);
    public:
		// MG_CN_MODIFY
        Bool                loadFile(std::wstring fileName, IMGExternalPackManager* packManager = NULL);
        Int                 getServerConfigNum();
        ServerConfig*       getServerConfigByIndex(Int index);
        ServerConfig*       getServerConfigByName( std::wstring name );
    protected:
        void                unloadFile();
    private:
        std::vector<ServerConfig*>*         mpServerConfigList;
    };
    //*************************************************************************************************//
}
//*************************************************************************************************//
#endif
//*************************************************************************************************//