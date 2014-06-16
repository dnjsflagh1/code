//***************************************************************************************
#ifndef _H_STATUSBASEINFO_
#define _H_STATUSBASEINFO_
//***************************************************************************************
#include "GameFilePreqs.h"
//***************************************************************************************
namespace MG
{
	
	//----------------------------------------------------------------------
	struct StatusBaseInfo 
	{
		UInt				StatusListId			;
		UInt				GroupId					;
		UInt				GroupLevel				;		//需要检查状态的等级，1--12.
		UInt				TargetLevel				;		
		Str16				Name					;
		Str16				Text					;
		Str16				KindName				;
		UInt				ArtIconId				;
		STATUS_SHOWTYPE		ShowType				;		//需要检查状态的显示类型，1--3.
		STATUS_STYLETYPE	StyleType				;		//需要检查状态的分组类型，1--4.
		UInt				SlotNum					;		//需要检查状态格位。最大为24，最小为1.
		UInt				SlotPriority			;		//需要检查状态优先级，1--100.
		STATUS_TIMETYPE		TimeType				;		//需要检查状态的时间类型，0--3.
		UInt				HoldTime				;
		UInt				DisappearType			;		//需要检查状态消失方式，0--255.
		UInt				MaxAddNum				;		//需要检查状态重叠次数，1--100.
		UInt				AbilityAppendId			;

	};
}

//***************************************************************************************
#endif
//***************************************************************************************