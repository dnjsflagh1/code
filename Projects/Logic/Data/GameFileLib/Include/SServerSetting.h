//*************************************************************************************************//
#ifndef _H_SSERVERSETTING_
#define _H_SSERVERSETTING_
//*************************************************************************************************//

#include "NetAddress.h"
#include "NetDefine.h"

namespace MG
{

	struct CoreInfo
	{
		std::wstring	name;
		I32				id;
		I32				type;
		std::wstring	dllName;
		I32				updateTick;			///毫秒
		I32				closeTime;			///秒
		Bool			isWriteCoreLog;		///Dlg日志
		Bool			isWriteDbLog;		///Dlg日志
		Bool			isWriteShellLog;		///Dlg日志
		Bool			isAutoStart;
		I32				logLevel;			///.txt日志
		Bool			isOpenConsole;

	};

	//数据库链接信息
	struct DbConnectInfo
	{
		std::wstring	ip;
		std::wstring	name;
		std::wstring	account;
		std::wstring	password;
		I32				port;
		Bool			isCreate;
	};
	
	//链接的远程信息 
	struct ConnectRemoteInfo
	{
		std::wstring	name;
		I32				type;
		NetAddress		addr;
	};
	//监听的远程信息 
	/*struct ListenRemoteInfo
	{
		std::wstring	name;
		I32				type;
		std::wstring	ip;
	};*/
	struct ListenInfoSendToClient
	{
		NetAddress		addr;
	};
	//监听客户端的本地信息
	struct ClientListenInfo 
	{
		I32				maxConnects;
		Bool			isSaveShellLog;
		Bool			isEncrypted;
		NetAddress		addr;
	};
	//监听服务器的本地信息
	struct ServerListenInfo 
	{
		I32				maxConnects;
		Bool			isSaveShellLog;
		Bool			isEncrypted;
		NetAddress		addr;
	};

	//允许的远程（服务器）链接IP列表
	struct AllowedServerIpCollection
	{
		Bool isValid;
		std::vector<Str16> allowedIps;

	};

	//需要链接的远程服务器列表
	struct ConnectServerCollection
	{
		I32 maxConnects;
		std::map<U64, ConnectRemoteInfo*> connectServers;
	};

	class SServerSetting 
	{
	public:
		SServerSetting();
		~SServerSetting();
		SINGLETON_INSTANCE(SServerSetting);

	public:
		// MG_CN_MODIFY
		Bool	loadFile(std::wstring fileName, IMGExternalPackManager* packManager = NULL);
		Bool	isClientLisiten();
		Bool	isServerLisiten();
	protected:
		void	unloadFile();

	public:
		typedef std::map<U64, ConnectRemoteInfo*>::iterator ConnectionIt;

	public:
		CoreInfo*					getCoreInfo() const;
		DbConnectInfo*				getDbConnectInfo() const;
		ClientListenInfo*			getClientListenInfo() const;
		ServerListenInfo*			getServerListenInfo() const;
		ConnectServerCollection*	getConnectServers() const;
		AllowedServerIpCollection*	getAllowedServerIpCollection() const;
		ListenInfoSendToClient*		getListenInfoSendToClient()const;


	private:
		CoreInfo*					mCore;
		DbConnectInfo*				mDb;

		ClientListenInfo*			mClientListen;
		ServerListenInfo*			mServerListen;

		ConnectServerCollection*	mConnectServers;
		AllowedServerIpCollection*	mAllowedServerIps;
		ListenInfoSendToClient*		mLinstenSendToClient;
	};
	
}
//*************************************************************************************************//
#endif
//*************************************************************************************************//