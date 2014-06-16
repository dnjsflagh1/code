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
	// ʵ���齻��AI
	/******************************************************************************/
	class CAIEntityGroupInteractiveInAdvance : public CAIEntityGroup
	{
	public:
		CAIEntityGroupInteractiveInAdvance();
		virtual ~CAIEntityGroupInteractiveInAdvance();

		//״̬����
		static Str STATE_NAME;

		///�����¼�
		virtual void        update( Flt delta );
		///�Ƿ������
		virtual Bool        isFinished();
		///��ȥ״̬�¼�
		virtual void        onEnter();
		///�뿪״̬�¼�
		virtual void        onLeave();

		////////////////////////////////////////////////////////////////////////

		void				setTargetSceneEntity(CSceneEntity* sceneEntity);

	protected:

		Vec3				mDestination;
		
		CSceneEntity*		mSceneEntity;
	};
}

#endif