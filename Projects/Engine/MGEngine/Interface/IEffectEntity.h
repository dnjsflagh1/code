/******************************************************************************/
#ifndef _IEFFECTENTITY_H_
#define _IEFFECTENTITY_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneObject.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //��Чʵ��ӿ�
    /******************************************************************************/
    class IEffectEntity : public ISceneObject
    {
    public:
        
        /// ��ʼһ����Ч
        virtual void start() = NULL;

		virtual void setScale(Vec3 scale) = NULL;

		/// ��һ����Ч��������
		virtual Bool bind(IEntity* entity, Bool attachToParent = false) = NULL;

		virtual Bool initialised() = NULL;

		virtual U32	 getEffectResourceID() = NULL;
        
    };

}

/******************************************************************************/
#endif
