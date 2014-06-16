/******************************************************************************/
#ifndef _GMCLIENT_H_
#define _GMCLIENT_H_
namespace MG
{
	/******************************************************************************/
	//class GMClient 
	/******************************************************************************/
	class GMClient : public IGMClient
	{
	public:
		SINGLETON_INSTANCE(GMClient)
				GMClient();
		virtual ~GMClient();

	public: 

		virtual Bool						initialize(const wchar_t* config);
		virtual Bool						uninitialize();
		virtual Bool						loadData();


		virtual Bool						setNativeTextConfig(const wchar_t* config);

		virtual void            			setErrorMessageOut(IGMCLIENT_CALLBACK_STR callback=NULL) {mErrorMessageOut=callback;}
		virtual void            			setWarningMessageOut(IGMCLIENT_CALLBACK_STR callback=NULL) {mWarningMessageOut=callback;}
		virtual void            			setHintMessageOut(IGMCLIENT_CALLBACK_STR callback=NULL) {mHintMessageOut=callback;}
		virtual void            			setLogOut(IGMCLIENT_CALLBACK_STR callback=NULL){mLogOut=callback;}

		virtual void            			setNativeGroup(std::wstring name);
		virtual std::string&    			getNativeValue(std::wstring name,std::wstring default_value=L"");

		virtual void            			setNativeGroupByC(const wchar_t* name);
		virtual const char*     			getNativeValueByC(const wchar_t* key,const wchar_t* default_value);

		virtual void            			logByC(const wchar_t* group,const wchar_t* key,const wchar_t* default_value);
		virtual void            			log(std::wstring group,std::wstring key,std::wstring default_value=L"");
		virtual void            			showErrorMessageByC(const wchar_t* group,const wchar_t* key,const wchar_t* default_value);
		virtual void            			showErrorMessage(std::wstring group,std::wstring key,std::wstring default_value=L"");
		virtual void            			showWarningMessageByC(const wchar_t* group,const wchar_t* key,const wchar_t* default_value);
		virtual void            			showWarningMessage(std::wstring group,std::wstring key,std::wstring default_value=L"");
		virtual void            			showHintMessageByC(const wchar_t* group,const wchar_t* key,const wchar_t* default_value);
		virtual void            			showHintMessage(std::wstring group,std::wstring key,std::wstring default_value=L"");

		virtual U64          			getCurrTimestamp();
		//Player
		virtual IPlayerManager* 			getPlayerManager();
		virtual IServerManager* 			getServerManager();
		virtual ISystemManager* 			getSystemManager();
		virtual IMessageManager*			getMessageManager();
		virtual IGMManager*     			getGMManager();
	public: 
		static void							gameRun(MG::Ptr manager);

	private:

		OneThreadHandle						mClientThread;    //The Client Thread
		IGMCLIENT_CALLBACK_STR				mErrorMessageOut;
		IGMCLIENT_CALLBACK_STR 				mWarningMessageOut;
		IGMCLIENT_CALLBACK_STR 				mHintMessageOut;
		IGMCLIENT_CALLBACK_STR 				mLogOut;
		UINI                   				mNativeConfig;
		std::wstring           				mnative_text;
		std::string            				mNative_text_string;

		InterLocked							mIsAppRun;
	};
}



/******************************************************************************/

#endif //_GMCLIENT_H_

