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
    //特效实体接口
    /******************************************************************************/
    class IEffectEntity : public ISceneObject
    {
    public:
        
        /// 开始一个特效
        virtual void start() = NULL;

		virtual void setScale(Vec3 scale) = NULL;

		/// 绑定一个特效到物体上
		virtual Bool bind(IEntity* entity, Bool attachToParent = false) = NULL;

		virtual Bool initialised() = NULL;

		virtual U32	 getEffectResourceID() = NULL;
        
    };

}

/******************************************************************************/
#endif
