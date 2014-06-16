/******************************************************************************/
#include "stdafx.h"
#include "GMClient.h"
#include "ClientNetApplyManager.h"
#include "GMManager.h"
//#include "PacketSystem.h"
//#include "ServerManager.h"
//#include "SystemManager.h"
//#include "PlayerManager.h"
//#include "MessageManager.h"
/******************************************************************************/
//#include "GMManager.h"
namespace MG
{
	/******************************************************************************/
	//class GMClient 
	/******************************************************************************/
	GMClient::GMClient()
		:mErrorMessageOut(NULL)
		,mWarningMessageOut(NULL)
	{
	}
	//-----------------------------------------------------------------------------
	GMClient::~GMClient()
	{
		uninitialize();
	}
	//-----------------------------------------------------------------------------
	Bool GMClient::initialize(const wchar_t* config)
	{
		if (!ClientNetApplyManager::getInstance().initialize())
		{
			return false;
		}
		mClientThread.create(gameRun,this);
		mIsAppRun = 1;


		/* if (NetManager::getInstance().initialize() == false)
		return FALSE;

		if (GMManager::getInstance().initialize() == false)
		return FALSE;
		if (SystemManager::getInstance().initialize(config) == false)
		return FALSE;
		if (ServerManager::getInstance().initialize() == false)
		return FALSE;
		if (PlayerManager::getInstance().initialize() == false)
		return FALSE;
		if (MessageManager::getInstance().initialize() == false)
		return FALSE;

		if (m_ClientThread==NULL)
		{
		m_ClientThread = new xnThread(clientThreadProcess, (void*)this, FALSE);
		if (m_ClientThread==NULL)
		{
		return FALSE;
		}
		m_ClientThread->Start();
		}*/

		return TRUE;
	}
	//-----------------------------------------------------------------------------
	Bool GMClient::uninitialize()
	{
		bool result = true;

		/*if (NetManager::getInstance().uninitialize() == false)
		result = FALSE;
		if (SystemManager::getInstance().uninitialize() == false)
		result = FALSE;
		if (ServerManager::getInstance().uninitialize() == false)
		result = FALSE;
		if (PlayerManager::getInstance().uninitialize() == false)
		result = FALSE;
		if (MessageManager::getInstance().uninitialize() == false)
		result = FALSE;
		if (GMManager::getInstance().uninitialize() == false)
		result = FALSE;

		{   
		if (m_ClientThread)
		m_ClientThread->Stop();
		Sleep(1000);
		_SAFE_DELETE(m_ClientThread);
		}

		xnFileShutDown();*/

		return result;
	}
	//-----------------------------------------------------------------------------
	Bool GMClient::loadData()
	{
		/* if (!SystemManager::getInstance().loadData())
		return false;
		if (!PlayerManager::getInstance().loadData())
		return false;
		if (!ServerManager::getInstance().loadData())
		return false;
		if (!MessageManager::getInstance().loadData())
		return false;
		if (!GMManager::getInstance().loadData())
		return false;*/
		return true;
	}
	//-----------------------------------------------------------------------------
	IPlayerManager* GMClient::getPlayerManager()
	{
		//return &(PlayerManager::getInstance());
		return NULL;
	}
	//-----------------------------------------------------------------------------
	IServerManager* GMClient::getServerManager()
	{
		//return &(ServerManager::getInstance());
		return NULL;
	}
	//-----------------------------------------------------------------------------
	ISystemManager* GMClient::getSystemManager()
	{
		//return &(SystemManager::getInstance());
		return NULL;
	}
	//-----------------------------------------------------------------------------
	IMessageManager* GMClient::getMessageManager()
	{
		//return &(MessageManager::getInstance());
		return NULL;
	}
	//-----------------------------------------------------------------------------
	IGMManager* GMClient::getGMManager()
	{
		return &(GMManager::getInstance());
	}
	//-----------------------------------------------------------------------------
	void GMClient::logByC(const wchar_t* group,const wchar_t* key,const wchar_t* default_value)
	{
		log( std::wstring(group), std::wstring(key), std::wstring(default_value));
	}
	//-----------------------------------------------------------------------------
	void GMClient::log(std::wstring group,std::wstring key,std::wstring default_value)
	{
		setNativeGroup(group);
		std::string& msg = getNativeValue(key,default_value);

		if (mLogOut)
			mLogOut(const_cast<char*>(msg.c_str()));
	}
	//-----------------------------------------------------------------------------
	void GMClient::showErrorMessageByC(const wchar_t* group,const wchar_t* key,const wchar_t* default_value)
	{
		showErrorMessage( std::wstring(group), std::wstring(key), std::wstring(default_value));
	}
	//-----------------------------------------------------------------------------
	void GMClient::showErrorMessage(std::wstring group,std::wstring key,std::wstring default_value)
	{
		setNativeGroup(group);
		std::string& msg  = getNativeValue(key,default_value);

		if (mErrorMessageOut)
			mErrorMessageOut(const_cast<char*>(msg.c_str()));
	}
	//-----------------------------------------------------------------------------
	void GMClient::showWarningMessageByC(const wchar_t* group,const wchar_t* key,const wchar_t* default_value)
	{
		showWarningMessage( std::wstring(group), std::wstring(key), std::wstring(default_value));
	}
	//-----------------------------------------------------------------------------
	void GMClient::showWarningMessage(std::wstring group,std::wstring key,std::wstring default_value)
	{
		setNativeGroup(group);
		std::string& msg = getNativeValue(key,default_value);

		if (mWarningMessageOut)
			mWarningMessageOut(const_cast<char*>(msg.c_str()));
	}
	//-----------------------------------------------------------------------------
	void GMClient::showHintMessageByC(const wchar_t* group,const wchar_t* key,const wchar_t* default_value)
	{
		showHintMessage( std::wstring(group), std::wstring(key), std::wstring(default_value));
	}
	//-----------------------------------------------------------------------------
	void GMClient::showHintMessage(std::wstring group,std::wstring key,std::wstring default_value)
	{
		setNativeGroup(group);
		std::string& msg = getNativeValue(key,default_value);

		if (mHintMessageOut)
			mHintMessageOut(const_cast<char*>(msg.c_str()));
	}
	//-----------------------------------------------------------------------------
	U64 GMClient::getCurrTimestamp()
	{
		return MGTimeOp::getCurrTimestamp();
	}
	//-----------------------------------------------------------------------------
	Bool GMClient::setNativeTextConfig(const wchar_t* config)
	{
		//init server 
		/* if (config==NULL)
		{
		showErrorMessage(L"NULL",L"NULL",L"no native config file");
		return FALSE;
		}

		if ( !m_NativeConfig.Create(std::wstring(config)) )
		{
		showErrorMessage(L"NULL",L"NULL",L"cant find native config file");
		return FALSE;
		}*/

		return TRUE;
	}
	//-----------------------------------------------------------------------------
	void GMClient::setNativeGroup(std::wstring name)
	{
		//m_NativeConfig.SetGroup(name);
	}
	//-----------------------------------------------------------------------------
	std::string& GMClient::getNativeValue(std::wstring name,std::wstring default_value)
	{
		/*m_native_text = m_NativeConfig.GetValue(name, default_value);
		m_native_text_string = WC2MB(m_native_text.c_str());*/
		return mNative_text_string;
	}
	//-----------------------------------------------------------------------------
	void GMClient::setNativeGroupByC(const wchar_t* name)
	{
		// m_NativeConfig.SetGroup(std::wstring(name));
	}
	//-----------------------------------------------------------------------------
	const char* GMClient::getNativeValueByC(const wchar_t* name, const wchar_t* default_value)
	{
		/*m_native_text = m_NativeConfig.GetValue(std::wstring(name), std::wstring(default_value));
		m_native_text_string = WC2MB(m_native_text.c_str());*/
		return mNative_text_string.c_str();
	}
	//-----------------------------------------------------------------------------
	void GMClient::gameRun( MG::Ptr manager )
	{
		OneThreadHandle* thd = (OneThreadHandle*)manager;
		if (!thd)
		{
			DYNAMIC_ASSERT_LOG(false,"主线程开启失败");
			return;
		}
		GMClient* client = (GMClient*)thd->getParam();
		if (!client)
		{
			DYNAMIC_ASSERT_LOG(false,"主线程开启失败");
			return;
		}
		while(client->mIsAppRun)
		{
			// 更新服务器管理
			if (ClientNetApplyManager::getInstance().update() == 0)
			{
				Sleep(1);
			}	
		}

	}
}
