//*************************************************************************************************//
#ifndef _H_LOGINCONFIG_
#define _H_LOGINCONFIG_
//*************************************************************************************************//
namespace MG
{
     
    
	struct LoginConfigInfo
	{
		U32				mMaxLoginCount;							 // 最大登录人数
		
		U32				mMaxLoginWaitCount;						// 最大等待登录人数
		
		U32				mMaxLoginTimeoutValue;					// 登录超时时间(ms)
		
		U32				mUpdateLoginQueueIntervalTime;			 // 通知客户端登录排队信息的更新时间间隔(ms)
		
		U32				mUpdateForbidedLoginIntervalTime;		 // 更新恢复禁止登录帐号的登录权限时间间隔（ms）
		
		U32				mForbidedLoginTime;						// 错误登录上限 禁止登录时间
			
		U32				mMaxErrorLoginCount;					 // 最大登录错误次数

		U32				mMaxFrontServerLoginCount;				 // FrontServer最大登录人数
		
		Bool			mUsePlatformAccount;
		LoginConfigInfo()
			:mMaxLoginCount(0),mMaxLoginWaitCount(0),mMaxLoginTimeoutValue(0),mUpdateLoginQueueIntervalTime(0),
			mUpdateForbidedLoginIntervalTime(0),mForbidedLoginTime(0),mMaxErrorLoginCount(0),mMaxFrontServerLoginCount(0),mUsePlatformAccount(false)
		{

		}

	};

	class LoginConfig
	{
	public:
		LoginConfig()
			:mLoginConfigInfo(NULL)
		{

		}
		~LoginConfig();
        SINGLETON_INSTANCE(LoginConfig);
		Bool	            loadFile(std::wstring fileName, IMGExternalPackManager* packManager = NULL);
		LoginConfigInfo*    getLoginConfigInfo();
        
	protected:
	private:
		
		LoginConfigInfo* mLoginConfigInfo;

	};



}

#endif