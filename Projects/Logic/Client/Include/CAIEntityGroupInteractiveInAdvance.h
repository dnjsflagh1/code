/******************************************************************************/
#ifndef _CAIENTITYGROUPINTERACTIVEINADVANCE_H_
#define _CAIENTITYGROUPINTERACTIVEINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CAIGroup.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	// 实体组交互AI
	/******************************************************************************/
	class CAIEntityGroupInteractiveInAdvance : public CAIEntityGroup
	{
	public:
		CAIEntityGroupInteractiveInAdvance();
		virtual ~CAIEntityGroupInteractiveInAdvance();

		//状态名字
		static Str STATE_NAME;

		///更新事件
		virtual void        update( Flt delta );
		///是否结束了
		virtual Bool        isFinished();
		///进去状态事件
		virtual void        onEnter();
		///离开状态事件
		virtual void        onLeave();

		////////////////////////////////////////////////////////////////////////

		void				setTargetSceneEntity(CSceneEntity* sceneEntity);

	protected:

		Vec3				mDestination;
		
		CSceneEntity*		mSceneEntity;
	};
}

#endif