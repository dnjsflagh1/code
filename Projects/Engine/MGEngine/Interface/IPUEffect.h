/******************************************************************************/
#ifndef _IPUEFFECT_H_
#define _IPUEFFECT_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneObject.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//PU特效接口
	/******************************************************************************/
	class IPUEffect : public ISceneObject
	{
	public:

		/// 开始一个特效
		virtual void start() = NULL;
		/// 停止一个特效
		virtual void stop() = NULL;

		virtual void setScale(Vec3 scale) = NULL;

		virtual Bool update( Flt delta ) = NULL;

		/// 绑定一个特效到物体上
		virtual Bool bind(IEntity* entity, Bool attachToParent = false) = NULL;

		virtual Bool initialised() = NULL;

		virtual U32	 getEffectResourceID() = NULL;

		virtual void setTrailLength(U32 length) = NULL;

		virtual void setTrailWidth(U32 width) = NULL;

		virtual void setTrailLiveTime(Flt time) = NULL;
	};

}

/******************************************************************************/
#endif
