/******************************************************************************/
#ifndef _PlaceEntity_H_
#define _PlaceEntity_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IPlaceEntity.h"
#include "ILogicBinder.h"
#include "OgreEntityWrapper.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //游戏实体对象
    /******************************************************************************/
    class PlaceEntity : public IPlaceEntity
    {
        friend class Scene;
    public:
        PlaceEntity(CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene);
        virtual ~PlaceEntity();

        /// 更新
        virtual void                    update( Flt delta );

        /// 得到类型
        virtual SceneObjectTypes        getType();

        /// 得到空间节点
        virtual ISceneNode*             getSceneNode();

        /// 得到模型实体
        virtual OgreEntityWrapper*      getModelObject();

    protected:

        OgreEntityWrapper*              mOgreEntityWrapper;

    };

}

/******************************************************************************/

#endif
