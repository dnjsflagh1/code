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

		//״̬����
		static Str STATE_NAME;

		virtual void									update( Flt delta );

		virtual Bool									isFinished();

		virtual void									onStartMove();
		///�뿪״̬�¼�
		virtual void									onEndMove();

		void											setIsCheckBlock( Bool isCheckBlock );

		void											setMoveToPathFindType( ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType );


		// �õ�������ȫ��Ŀ���
		void											setDestination(Vec3 pos);
		Vec3											getDestination();

		// �õ��߼���ɫ����
		CCharacterSceneEntity*							getOwner();

		void											clacTroopSoldierPos( Vec3 pos, Vec3 dir, std::map<UInt, MoveToPosRow>& soldierPosList );

		void											clacTroopSoldierPos( Vec3 pos, std::vector<Vec3>& soldierPosList );

		void											clacTroopSoldierMoveToPos( Vec3 pos, Vec3 dir, std::map<UInt, Vec3>& soldierPosList );

	protected:

		// �߼����ɫ
		CTroopEntity*									mTroopEntity;
		// ����Ŀ�ĵ�
		Vec3											mDestination;

		Bool											mIsFinished;
		Bool											mIsDestroy;

		Bool											mIsCheckBlock;

		ISceneNodeGridLineMoveToAction::MoveToPathFindType mMoveToPathFindType;

	};
}

#endif