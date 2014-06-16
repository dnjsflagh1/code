/******************************************************************************/
#ifndef _IENTITY_H_
#define _IENTITY_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneObject.h"
#include "IAnimationController.h"
#include "IResourceManager.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //游戏实体声明
    /******************************************************************************/
	struct  EntityDeclaration
	{
		Str     autoAnimation;
		Str     batchGroup;
		Bool    isLoadWhenGame;

		EntityDeclaration()
			:batchGroup("DefaultStaticGroup")
			,isLoadWhenGame(true)
		{
		}
	};
    
    
    /******************************************************************************/
    //游戏实体接口
    /******************************************************************************/
    class IEntity : public ISceneObject
    {
    public:

        /// 得到模型对象
        virtual EntityDeclaration&          getDeclaration(){return mEntityDeclaration;};
        
        /// 得到模型对象
        virtual IModelObject*               getModelObject() = 0;

        /// 得到动画控制器
        virtual IAnimationController*       getAnimationController() = 0;

        /// 得到附属物管理对象
        virtual IEntityAccessoryCollection* getEntityAccessoryCollection() = 0;

		/// 是否被渲染
		virtual Bool						isRendering() = 0;

		virtual void						setRenderGroup(U8 group, U8 priority = 100) {};

    protected:

        // 声明
        EntityDeclaration               mEntityDeclaration;
    };

}

/******************************************************************************/
#endif
