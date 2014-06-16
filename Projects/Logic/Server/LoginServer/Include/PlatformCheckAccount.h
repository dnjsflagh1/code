/******************************************************************************/
#ifndef _PLATFORMCHECKACCOUNT_H_
#define _PLATFORMCHECKACCOUNT_H_
/******************************************************************************/

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//平台帐号验证
	/******************************************************************************/
//#define USE_PLATFORMCHECKACCOUNT 1
	/*	--------------------------------------
	平台用户登录返回代码
	21	用户验证成功。
	01	账号格式不正确，且不能为空，或不是UTF-8编码，字数范围4-15个字符
	02	密码不规范(长度为32位) (6-15个字符加密的32位)
	03	用户密码错误
	04	用户名不存在
	05	签名错误
	06	超时
	07	合作渠道ID错误
	08	操作选项错误
	09	游戏编号不存在
	10	服务器编号不存在
	--------------------------------------*/
	class PlatformCheckAccount
	{
	public:
		PlatformCheckAccount();
		~PlatformCheckAccount();
		SINGLETON_INSTANCE(PlatformCheckAccount);

	public:
		Int		checkAccount(Char16* accountName,Char16* psw,NetAddress& addr,std::map<Str16,Str16>& values);
		
		Bool	parseResponse(const Str16& response,std::map<Str16,Str16>& value);
	private:
		// # masterIP   
		Str8		mUip;
		// # 平台接口地址    
		Str8		mPlatformURL;		
		// # 请求类型
		Str8		mAction;			
		// # 平台上该游戏的公钥
		Str8		mGameKey;			
		// # 推广平台  
		Str8		mUnid;						  
	};
}
/******************************************************************************/
#endif