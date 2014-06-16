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
    //��Ϸʵ�����
    /******************************************************************************/
    class PlaceEntity : public IPlaceEntity
    {
        friend class Scene;
    public:
        PlaceEntity(CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene);
        virtual ~PlaceEntity();

        /// ����
        virtual void                    update( Flt delta );

        /// �õ�����
        virtual SceneObjectTypes        getType();

        /// �õ��ռ�ڵ�
        virtual ISceneNode*             getSceneNode();

        /// �õ�ģ��ʵ��
        virtual OgreEntityWrapper*      getModelObject();

    protected:

        OgreEntityWrapper*              mOgreEntityWrapper;

    };

}

/******************************************************************************/

#endif
