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
	//PU��Ч�ӿ�
	/******************************************************************************/
	class IPUEffect : public ISceneObject
	{
	public:

		/// ��ʼһ����Ч
		virtual void start() = NULL;
		/// ֹͣһ����Ч
		virtual void stop() = NULL;

		virtual void setScale(Vec3 scale) = NULL;

		virtual Bool update( Flt delta ) = NULL;

		/// ��һ����Ч��������
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
