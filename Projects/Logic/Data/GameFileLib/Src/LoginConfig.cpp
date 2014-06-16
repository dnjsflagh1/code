//*************************************************************************************************//
#include "stdafx.h"
#include "LoginConfig.h"
#include "Ini.h"
//*************************************************************************************************//
namespace MG
{

	//--------------------------------------------------------------------------
	MG::Bool LoginConfig::loadFile( std::wstring fileName, IMGExternalPackManager* packManager /*= NULL*/ )
	{
		DYNAMIC_ASSERT(fileName.length() > 4);
		UINI ini;
		// MG_CN_MODIFY
		if (ini.create(fileName, packManager))
		{
             //Configuration
			if (ini.hasGroup(L"Configuration"))
			{
				ini.setGroup(L"Configuration");
				if (mLoginConfigInfo == NULL)
				     mLoginConfigInfo = MG_NEW LoginConfigInfo;
				Int subGroupCount = ini.getSubGroupCount(L"Configuration");
				
				MGStrOp::toU32(ini.getValue(L"maxLoginCount",L"").c_str(),mLoginConfigInfo->mMaxLoginCount);
				MGStrOp::toU32(ini.getValue(L"maxWaitLoginCount",L"").c_str(),mLoginConfigInfo->mMaxLoginWaitCount);
				MGStrOp::toU32(ini.getValue(L"loginTimeoutValue",L"").c_str(),mLoginConfigInfo->mMaxLoginTimeoutValue);
				MGStrOp::toU32(ini.getValue(L"updateLoginQueueIntervalTime",L"").c_str(),mLoginConfigInfo->mUpdateLoginQueueIntervalTime);
				MGStrOp::toU32(ini.getValue(L"updateForbidedLoginIntervalTime",L"").c_str(),mLoginConfigInfo->mUpdateForbidedLoginIntervalTime);
				MGStrOp::toU32(ini.getValue(L"forbidedLoginTime",L"").c_str(),mLoginConfigInfo->mForbidedLoginTime);
				MGStrOp::toU32(ini.getValue(L"maxErrorLoginCount",L"").c_str(),mLoginConfigInfo->mMaxErrorLoginCount);
				MGStrOp::toU32(ini.getValue(L"maxFrontServerLoginCount",L"").c_str(),mLoginConfigInfo->mMaxFrontServerLoginCount);
				I32 temp = 0;
				MGStrOp::toI32(ini.getValue(L"usePlatfromAccount",L"").c_str(),temp);
				temp == 0 ? mLoginConfigInfo->mUsePlatformAccount = false : mLoginConfigInfo->mUsePlatformAccount = true;
			}
			return true;
		}
        
        return false;

	}
	//--------------------------------------------------------------------------
	LoginConfig::~LoginConfig()
	{
          MG_SAFE_DELETE(mLoginConfigInfo);
	}
	//--------------------------------------------------------------------------
	LoginConfigInfo* LoginConfig::getLoginConfigInfo()
	{
         return mLoginConfigInfo;
	}

}