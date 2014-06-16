/******************************************************************************/
#ifndef _NpcEntity_H_
#define _NpcEntity_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "INpcEntity.h"
#include "ILogicBinder.h"
#include "OgreEntityWrapper.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //游戏NpcEntity对象
    /******************************************************************************/
    class NpcEntity : public INpcEntity
    {
        friend class Scene;
    public:
        NpcEntity(CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene);
        virtual ~NpcEntity();

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
