/******************************************************************************/
#ifndef _CSPRINTSKILLEFFECT_H_
#define _CSPRINTSKILLEFFECT_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CSkillEffect.h"

/******************************************************************************/

namespace MG
{
	class CSprintSkillEffect : public CSkillEffect
	{
	public:
		CSprintSkillEffect( CSkillObject* object );
		virtual ~CSprintSkillEffect();

		virtual				void start();

		virtual				void end();

		virtual				void update( Flt delta );

		virtual void			setPos( Vec3 pos );
		virtual void			setDis( UInt dis);

	protected:
		Vec3					mPos;
		Vec3					mStartPos;
		UInt					mDis;

	protected:

		IEffectEntity*      mEffectEntity;
		Vec3				mEffectEntityLastPos;

	private:
		IEngineUtil*		mEngineUtil;
		Vec3				mLastClickTerrainPos;
		CCharacterSceneEntity*			mUseCharacter;
		Flt					mAlreadyMoveDis;
		Flt					mCurrMoveDis;
		IdType				mMapId;
		
	};
}

/******************************************************************************/

#endif