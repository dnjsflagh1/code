/******************************************************************************/
#ifndef _GMMANAGER_H_
#define _GMMANAGER_H_
/******************************************************************************/
#include "GMClientInterface.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//class GMManager 
	/******************************************************************************/
	class GMManager : public IGMManager
	{
	public:
		SINGLETON_INSTANCE(GMManager)
				GMManager();
		virtual ~GMManager();
		virtual std::map<U32,GMClientInfo*>*getGMDataSet();
		virtual std::map<Int,std::string>&	getAuthorityList();
		virtual Int							getAuthorityID(CChar8* name);
		virtual	CChar8*						getAuthorityName(Int auId);
		virtual void                        setUpdateAllGMCallback(IGMCLIENT_CALLBACK callback);
		virtual void                        setUpdateGMCallback(IGMCLIENT_CALLBACK_ULONGLONG callback);

		virtual gm_account_operate_result	login(CChar8* username, CChar8* password);
		virtual void						logout();

		virtual gm_account_operate_result   createGM(CChar8* name, CChar8* password, Int auId);
		virtual gm_account_operate_result   updateGM(Int gmId, CChar8* name, 
			bool updatePsw, CChar8* oldPsw,CChar8* newPsw, 
			bool updateAu,Int auId);
		virtual gm_account_operate_result   deleteGM(Int gmId, CChar8* name);

		void								setLoginResult(gm_account_operate_result result);
		void								setCreateGMResult(gm_account_operate_result result);
		void								setDeleteGMResult(gm_account_operate_result result);


	public: 
		//callBack
		IGMCLIENT_CALLBACK				mUpdateAllGmcallback;
		IGMCLIENT_CALLBACK_ULONGLONG	mUpdateGmcallback;

		std::map<U32,GMClientInfo*>		mGMDataSet;
		std::map<Int,std::string>		mAuthorityList;

		gm_account_operate_result		mCreateResult;
		gm_account_operate_result		mUpdateResult;
		gm_account_operate_result		mDeleteResult;
		gm_account_operate_result		mLoginResult;
		
		GMClientInfo*					mLoginData;
		//GMLogDataSetForSendItem			mLogsForSendItem;

	};
}



/******************************************************************************/

#endif //_GMMANAGER_H_