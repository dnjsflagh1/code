//*************************************************************************************

#ifndef _UI_ALIVE_RPG_H_
#define _UI_ALIVE_RPG_H_

//*************************************************************************************

#include "ClientPreqs.h"
#include "UIObject.h"

//*************************************************************************************

namespace MG
{
	//-------------------------------------------------------------------------------
	class UIAliveRpg : public UIObject
	{
	public:
		UIAliveRpg();
		~UIAliveRpg();
		SINGLETON_INSTANCE(UIAliveRpg);

	public:
		virtual void setEvent();
		virtual Bool openGui();
	public:
		void UIShowGeneralInfo();
	public:
		//原地复活
		static void onClickButtonAliveCurPos(void* widget);
		//复活点复活
		static void onClickButtonAliveRelivePos(void* widget);
	};
}

#endif	//_UI_ALIVE_RPG_H_