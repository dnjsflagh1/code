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
    //��ϷNpcEntity����
    /******************************************************************************/
    class NpcEntity : public INpcEntity
    {
        friend class Scene;
    public:
        NpcEntity(CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene);
        virtual ~NpcEntity();

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
