/******************************************************************************/
#ifndef _EFFECTEVENTUTIL_H_
#define _EFFECTEVENTUTIL_H_
/******************************************************************************/
#include "EnginePreqs.h"
#include "ParticleUniverseSystemManager.h"

namespace MG
{
	/***************************************************************/
	// 特效事件公用函数
	/***************************************************************/
	class EffectEventUtil
	{
	public:

		EffectEventUtil(EffectComponent* component);
		virtual ~EffectEventUtil();
		
		/// 模型绑模型
		Bool	execModelbindModel(Entity* childEntity, Entity* parentEntity, Bool attachToParent = false, Int bindBoxHeightRate = 500, Str8 boneName ="");
		/// 模型绑PU
		Bool	execModelbindPU(Entity* childEntity, PUEffect* parentPU);
		/// PU绑模型
		Bool	execPUbindModel(PUEffect* childPU, Entity* parentEntity, Bool attachToParent = false, Int bindBoxHeightRate = 500, Str8 boneName ="");
		/// PU绑PU
		Bool	execPUbindPU(PUEffect* childPU, PUEffect* parentPU);
		
	private:
		EffectComponent* mComponent;
		
	};


}

#endif