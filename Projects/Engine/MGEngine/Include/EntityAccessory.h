/******************************************************************************/
#ifndef _ENTITYACCESSORY_H_
#define _ENTITYACCESSORY_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IEntityAccessory.h"
#include "ISceneNode.h"
#include "AnimationController.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    // ʵ�帽���Ｏ��
    /******************************************************************************/
    class EntityAccessoryCollection : public IEntityAccessoryCollection, public IAnimationControllerListener, public ISceneNodeLisitener
    {
    public:

        EntityAccessoryCollection( IEntity* parent, Scene* scene );
        virtual ~EntityAccessoryCollection();


        // ����
        void                                update( Flt delta );

		// �������е�λ�������Ϣ
		void								postFindVisibleObjects();

        /////////////////////////////////////////////////////////////////////

        // ��ʵ��
        virtual void                        attachObject( Str name, IEntityAccessory& accessory );
        // �Ƴ�ʵ��
        virtual void                        detachObject( Str name );

        // �õ���ʵ��
        virtual IEntityAccessory*           getAttachObject( Str name );

        // �õ���ʵ������
        virtual UInt                        getAttachObjectCount();
        virtual IEntityAccessory*           getAttachObject(UInt index);

    protected:

        // ����λ��
        void                                updateObjectLocation( IEntityAccessory& accessory );
		// ���´�С
		void								updateObjectScale( IEntityAccessory& accessory );

        // �������ʵ�����
        void                                detachAllObject();

        // ׼����ʵ�� 
        void                                prepareAttachObject( IEntityAccessory& accessory );
        // ׼���Ƴ�ʵ��
        void                                prepareDetachObject( IEntityAccessory& accessory );

        // �Ƿ�����Ч�ĸ�����
        Bool                                isValidAttachObject( IEntityAccessory& accessory );

    protected:

        virtual void                        onAnimationStart(CChar* animName);
        virtual void                        onAnimationStop(CChar* animName);
        virtual void                        onAnimationLoop(CChar* animName);

		virtual void						onRemove( ISceneNode* node );

    protected:

        IEntity*        mParent;
        Scene*          mScene;

        std::map< Str, IEntityAccessory >  mAttachs;

    };
}

/******************************************************************************/

#endif
