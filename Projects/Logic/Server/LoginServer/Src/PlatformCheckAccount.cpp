/******************************************************************************/
#include "stdafx.h"
#include "PlatformCheckAccount.h"
/******************************************************************************/
namespace MG
{
	//----------------------------------------------------------------------
	PlatformCheckAccount::PlatformCheckAccount()
	{
		/*mUip			= "127.0.0.1";
		mPlatformURL	= "http://api.kx1d.com/query?";
		mAction			= "login";
		mGameKey		= "3fd0fcf80e10024063f8fd65ddf1e3a5";
		mUnid			= "shz";*/
		mUip			= "127.0.0.1";
		mPlatformURL	= "http://api.kx1d.com/query?";
		mAction			= "login";
		mGameKey		= "1703a1ce8fa79272ebec6fb4b7bc04b5";
		mUnid			= "yxz";
		//mGId = 15
	}
	//----------------------------------------------------------------------
	PlatformCheckAccount::~PlatformCheckAccount()
	{
	
	}
	//----------------------------------------------------------------------
	Int PlatformCheckAccount::checkAccount( Char16* accountName,Char16* psw,NetAddress& addr,std::map<Str16,Str16>& values )
	{
		// 拼接url
		Str8 tempName;
		Str8 tempPsw;
		MGStrOp::toString(accountName,tempName);
		MGStrOp::toString(psw,tempPsw);
		tempPsw =  MGMd5::md5Str((char*)tempPsw.c_str());
		
		Char8	paraList[256]	= {0};
		Int		currTick		= MGTimeOp::getCurrTick();
		MGStrOp::sprintf(paraList,256,"uname=%s&pwd=%s&time=%d&uip=%s&action=%s&unid=%s",tempName.c_str(), tempPsw.c_str(), currTick, addr.getIPStrA(), mAction.c_str(), mUnid.c_str());

		Str8 key;
		key += paraList;
		key += "&key=";
		key += mGameKey;
		key = MGMd5::md5Str((char*)key.c_str());
		
		Char8 sign[128] = {0};
		sprintf_s(sign,"&sign=%s&fcm=1&gid=15",key.c_str());

		Str8 url;
		url += mPlatformURL;
		url += paraList;
		url += sign;
		
		Str16 wurl;
		MGStrOp::toString(url.c_str(),wurl);

		// 向平台验证
		MGWinHttpClient httpClient;
		Str16 response;
		if (httpClient.sendHttpQuest(wurl,response))
		{
			Int ret;
			//解析返回值
			parseResponse(response,values);
			MGStrOp::toI32(values[L"success"].c_str(),ret);
			return ret;
		}
		return -1;
	}
	//----------------------------------------------------------------------
	Bool PlatformCheckAccount::parseResponse(const Str16& response, std::map<Str16,Str16>& values)
	{
		//解析的格式
		//如果参数 $isuser $gid $sid $fcm $sync $isun 不为空成功返回值：
		//{"uname":flash165,"pwd":e397557b2862bdc856df81f7f5f8d055,"islock":1,"isadult":1,”isun”:”76564”,"sync":*****,"success":21}
		
		
		if (std::wstring::npos != response.find(L'{'))
		{
			Str16 tempResponse = response.substr(1,response.size() - 2);
			std::vector<Str16> tempValues;
			char symbol = ',';
			MGStrOp::split<Str16>(tempResponse,symbol,tempValues);
			std::vector<Str16> keyValue;
			symbol = ':';
			for (std::vector<Str16>::iterator it = tempValues.begin(); it != tempValues.end(); it++)
			{
				keyValue.clear();
				MGStrOp::split<Str16>(*it,symbol,keyValue);
				if (keyValue.size() != 2)
				{
					DYNAMIC_ASSERT(false);
					continue;
				}
				values[keyValue[0].substr(1,keyValue[0].size() - 2)] = keyValue[1];
			}

			return true;
		}
		else
		{
			values[L"success"] = response;
			return false;
		}
		

	}
	//----------------------------------------------------------------------
}