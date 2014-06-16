/******************************************************************************/
#include "stdafx.h"
#include "GMManager.h"
#include "GMCommonData.h"
#include "VersionSwitch.h"
#include "GMAccountOpNetPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "ThreadStatusEventManager.h"
/******************************************************************************/

/******************************************************************************/
namespace MG
{
	//-------------------------------------------------------------------------
	GMManager::GMManager()
	{
		mLoginData = MG_NEW GMClientInfo;
	}
	//-------------------------------------------------------------------------
	GMManager::~GMManager()
	{
		MG_SAFE_DELETE(mLoginData);
	}
	//-------------------------------------------------------------------------
	std::map<U32,GMClientInfo*>* GMManager::getGMDataSet()
	{
		
		return &mGMDataSet;
	}
	//-------------------------------------------------------------------------
	std::map<Int,std::string>& GMManager::getAuthorityList()
	{
		return mAuthorityList;
	}
	//-------------------------------------------------------------------------
	Int GMManager::getAuthorityID( CChar8* name )
	{
		Int result = 0;
		std::string strName = name;
		std::map<Int,std::string>::iterator iter = mAuthorityList.begin();
		for (;iter!=mAuthorityList.end();iter++)
		{
			if (iter->second == strName)
			{
				result = iter->first;
				break;
			}
		}
		return result;
	}
	//-------------------------------------------------------------------------
	CChar8* GMManager::getAuthorityName( Int auId )
	{
		std::map<Int,std::string>::iterator iter = mAuthorityList.find(auId);

		if (iter!=mAuthorityList.end())
		{
			return iter->second.c_str();
		}
		return NULL;
	}
	//-------------------------------------------------------------------------
	void GMManager::setUpdateAllGMCallback( IGMCLIENT_CALLBACK callback )
	{
		mUpdateAllGmcallback = callback;
	}
	//-------------------------------------------------------------------------
	void GMManager::setUpdateGMCallback( IGMCLIENT_CALLBACK_ULONGLONG callback )
	{
		mUpdateGmcallback = callback;
	}
	//-------------------------------------------------------------------------
	gm_account_operate_result GMManager::login( CChar8* username, CChar8* password )
	{
		Str16 name,psw;
		mLoginResult = gaor_timeout;
		MGStrOp::toString(username,name);
		MGStrOp::toString(password,psw);

		WStrnCpyS(mLoginData->name,name.c_str(),MAX_ACCOUNT_LONGIN_NAME_LEN - 1);
		WStrnCpyS(mLoginData->password,psw.c_str(),MAX_ACCOUNT_LONGIN_PSW_LEN -1);

		// 需要改成读取配置
		NetAddress addr("192.168.1.217",3002);
		if (ClientNetApplyManager::getInstance().connectGMServerManager(addr))
		{
			ThreadStatusEventManager::getInstance().setDirty("GM_LOGIN");
			GMAccountOpNetPacketProcesser::getInstance().sendLoginPacketToGMServerManager(name.c_str(),psw.c_str(),CLIENT_VERSION_NUMBER);
			ThreadStatusEventManager::getInstance().waitDirtyOverTime("GM_LOGIN");
		}
		return mLoginResult;
	}
	//-------------------------------------------------------------------------
	void GMManager::logout()
	{
		ClientNetApplyManager::getInstance().closeNet();
	}
	//-------------------------------------------------------------------------
	gm_account_operate_result GMManager::createGM( CChar8* name, CChar8* password, Int auId )
	{
	
		return mCreateResult;
	}
	//-------------------------------------------------------------------------
	gm_account_operate_result GMManager::updateGM( Int gmId, CChar8* name, bool updatePsw, CChar8* oldPsw,CChar8* newPsw, bool updateAu,Int auId )
	{
		return mUpdateResult;
	}
	//-------------------------------------------------------------------------
	gm_account_operate_result GMManager::deleteGM( Int gmId, CChar8* name )
	{
		return mDeleteResult;
	}
	//-------------------------------------------------------------------------
	void GMManager::setLoginResult( gm_account_operate_result result )
	{
		mLoginResult = result;
	}
	//-------------------------------------------------------------------------
	void GMManager::setDeleteGMResult( gm_account_operate_result result )
	{
		mLoginResult = result;
	}
	//-------------------------------------------------------------------------
	void GMManager::setCreateGMResult( gm_account_operate_result result )
	{
		mLoginResult = result;
	}

}
