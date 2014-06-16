//*************************************************************************************

#ifndef _UI_ALIVE_SLG_H_
#define _UI_ALIVE_SLG_H_

//*************************************************************************************

#include "ClientPreqs.h"
#include "UIObject.h"

//*************************************************************************************

namespace MG
{
	//-------------------------------------------------------------------------------
	class UIAliveSlg : public UIObject
	{
	public:
		UIAliveSlg();
		~UIAliveSlg();
		SINGLETON_INSTANCE(UIAliveSlg);

	public:
		virtual void setEvent();
		virtual Bool openGui();

	public:
		void	UIShowGeneralInfo();
	public:
		//Ô­µØ¸´»î
		static void onClickButtonAliveCurPos(void* widget);
	};
}

#endif	//_UI_ALIVE_SLG_H_