/******************************************************************************/
#ifndef _CAISOLDIERINTROOPMOVE_H_
#define _CAISOLDIERINTROOPMOVE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "SceneEntityAction.h"

/******************************************************************************/

namespace MG
{
	//******************************************************************************

	//******************************************************************************

	class CAISoldierInTroopMove
	{
	public:
		struct MoveToPosRow
		{
			std::vector<Vec3>					moveToPos;
		};

		CAISoldierInTroopMove( CTroopEntity* troopEntity );
		virtual ~CAISoldierInTroopMove();

		//状态名字
		static Str STATE_NAME;

		virtual void									update( Flt delta );

		virtual Bool									isFinished();

		virtual void									onStartMove();
		///离开状态事件
		virtual void									onEndMove();

		void											setIsCheckBlock( Bool isCheckBlock );

		void											setMoveToPathFindType( ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType );


		// 得到或设置全局目标点
		void											setDestination(Vec3 pos);
		Vec3											getDestination();

		// 得到逻辑角色对象
		CCharacterSceneEntity*							getOwner();

		void											clacTroopSoldierPos( Vec3 pos, Vec3 dir, std::map<UInt, MoveToPosRow>& soldierPosList );

		void											clacTroopSoldierPos( Vec3 pos, std::vector<Vec3>& soldierPosList );

		void											clacTroopSoldierMoveToPos( Vec3 pos, Vec3 dir, std::map<UInt, Vec3>& soldierPosList );

	protected:

		// 逻辑层角色
		CTroopEntity*									mTroopEntity;
		// 理论目的地
		Vec3											mDestination;

		Bool											mIsFinished;
		Bool											mIsDestroy;

		Bool											mIsCheckBlock;

		ISceneNodeGridLineMoveToAction::MoveToPathFindType mMoveToPathFindType;

	};
}

#endif