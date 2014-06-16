//****************************************************************************************************
#ifndef _H_NEWFUCTION_
#define _H_NEWFUCTION_
//****************************************************************************************************
#include "EnginePreqs.h"
//****************************************************************************************************
namespace MG
{
	struct closeCallBack
	{
		Flt				mLastTime;
		PVOID_CALLBACK	mpCallBack;
		MyGUI::Widget*			mpWidget;
	};

	class GuiFuction
	{
	public:
		GuiFuction(){;}
		~GuiFuction(){;}
		SINGLETON_INSTANCE(GuiFuction);

	public:
		void			update(Flt delta);

	//----------------------------------------------------------------------------------------
	//CloseEvent.
	public:
		void			setCloseEvent(MyGUI::Widget* pWidget, Flt lastTime, PVOID_CALLBACK func);
		void			setCloseTime(MyGUI::Widget* pWidget, Flt lastTime);

	private:
		void			checkCloseEvent(Flt delta);
		void			handleCloseEvent(closeCallBack* pcloseCallBack);
	
	//End
	//----------------------------------------------------------------------------------------

	private:
		std::list<closeCallBack>					mListCallBack;
		std::map<MyGUI::Widget*, closeCallBack>		mMapcloseCallBack;
			
	};
}
//****************************************************************************************************
#endif
//****************************************************************************************************