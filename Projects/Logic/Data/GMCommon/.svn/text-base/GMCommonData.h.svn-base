/******************************************************************************/
#ifndef _GMDATASET_H_
#define _GMDATASET_H_
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
//struct IGMData 
/******************************************************************************/
namespace MG
{
	////////////////////////////////////////////////////////////////////////////////
	struct GMClientInfo
	{
		Int				gmId;
		Int				netId;
		Int   			authority;
		Bool			isOnline;
		Char16			name[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16			password[MAX_ACCOUNT_LONGIN_PSW_LEN];
		//------------------------------------------------------------------------
		GMClientInfo()
		{
			gmId		= 0;
			netId		= -1;
			authority	= 0;
			isOnline	= false;
			memset(name,0,sizeof(name));
			memset(password,0,sizeof(password));
		}
		//------------------------------------------------------------------------
		GMClientInfo(const GMClientInfo& gmData)
		{
			gmId		= gmData.gmId;	
			netId		= gmData.netId;	
			authority	= gmData.authority;
			isOnline	= gmData.isOnline;	
			WStrnCpyS(name,gmData.name,MAX_ACCOUNT_LONGIN_NAME_LEN - 1);
			WStrnCpyS(password,gmData.password,MAX_ACCOUNT_LONGIN_PSW_LEN -1);
		}
		//------------------------------------------------------------------------
		GMClientInfo& operator = (const GMClientInfo& gmData)
		{
			gmId		= gmData.gmId;	
			netId		= gmData.netId;	
			authority	= gmData.authority;
			isOnline	= gmData.isOnline;	
			WStrnCpyS(name,gmData.name,MAX_ACCOUNT_LONGIN_NAME_LEN - 1);
			WStrnCpyS(password,gmData.password,MAX_ACCOUNT_LONGIN_PSW_LEN -1);
			return *this;
		}
		//------------------------------------------------------------------------
	};
	////////////////////////////////////////////////////////////////////////////////
	
}
#endif 

