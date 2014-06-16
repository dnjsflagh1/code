/******************************************************************************/
#ifndef _EFFECTEVENTUTIL_H_
#define _EFFECTEVENTUTIL_H_
/******************************************************************************/
#include "EnginePreqs.h"
#include "ParticleUniverseSystemManager.h"

namespace MG
{
	/***************************************************************/
	// ��Ч�¼����ú���
	/***************************************************************/
	class EffectEventUtil
	{
	public:

		EffectEventUtil(EffectComponent* component);
		virtual ~EffectEventUtil();
		
		/// ģ�Ͱ�ģ��
		Bool	execModelbindModel(Entity* childEntity, Entity* parentEntity, Bool attachToParent = false, Int bindBoxHeightRate = 500, Str8 boneName ="");
		/// ģ�Ͱ�PU
		Bool	execModelbindPU(Entity* childEntity, PUEffect* parentPU);
		/// PU��ģ��
		Bool	execPUbindModel(PUEffect* childPU, Entity* parentEntity, Bool attachToParent = false, Int bindBoxHeightRate = 500, Str8 boneName ="");
		/// PU��PU
		Bool	execPUbindPU(PUEffect* childPU, PUEffect* parentPU);
		
	private:
		EffectComponent* mComponent;
		
	};


}

#endif