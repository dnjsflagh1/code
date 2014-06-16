/******************************************************************************/
#ifndef _STEAM_H_
#define _STEAM_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "Team.h"

/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//客户端军队小组对象
	/******************************************************************************/
	class STeam : public Team
	{
	public:
		STeam();
		STeam(IDType id);
		virtual ~STeam();

	public:
		void			setFrontServerID(I32 FrontID)				{ mFrontID = FrontID;}
		I32				getFrontServerID() const					{ return mFrontID;	}

	public:
		/// 减少血
		virtual void					reduceHP(UInt num, DAMAGE_TYPE attackType = DAMAGE_TYPE_NULL);
		/// 减少蓝
		virtual void					reduceMP(UInt num, DAMAGE_TYPE attackType = DAMAGE_TYPE_NULL);
		/// 减少怒气值
		virtual void                    reduceSP(UInt num, DAMAGE_TYPE attackType = DAMAGE_TYPE_NULL); 

	private:
		//对应FrontServer的编号
		I32				mFrontID;
	};
}
#endif	//_STEAM_H_