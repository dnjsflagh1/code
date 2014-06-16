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
    //��Ϸʵ������
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
    //��Ϸʵ��ӿ�
    /******************************************************************************/
    class IEntity : public ISceneObject
    {
    public:

        /// �õ�ģ�Ͷ���
        virtual EntityDeclaration&          getDeclaration(){return mEntityDeclaration;};
        
        /// �õ�ģ�Ͷ���
        virtual IModelObject*               getModelObject() = 0;

        /// �õ�����������
        virtual IAnimationController*       getAnimationController() = 0;

        /// �õ�������������
        virtual IEntityAccessoryCollection* getEntityAccessoryCollection() = 0;

		/// �Ƿ���Ⱦ
		virtual Bool						isRendering() = 0;

		virtual void						setRenderGroup(U8 group, U8 priority = 100) {};

    protected:

        // ����
        EntityDeclaration               mEntityDeclaration;
    };

}

/******************************************************************************/
#endif
