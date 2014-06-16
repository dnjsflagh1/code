/******************************************************************************/
#ifndef _SCREENRECTWIREFRAMEDECORATOR_H_
#define _SCREENRECTWIREFRAMEDECORATOR_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ManualMeshManager.h"
#include "IWireframeManager.h"

/******************************************************************************/

namespace MG
{

    /**
    -----------------------------------------------------------------------------
    #note:	��Ļ�����߿���Ϣ
    -----------------------------------------------------------------------------
    */
    class ScreenRectWireframeDecorator : public IScreenRectWireframeDecorator
    {
    public:
        ScreenRectWireframeDecorator(const String& name, Scene* scene);
        virtual ~ScreenRectWireframeDecorator();

        /// ����
        virtual void        update(void);

        /// ����
        virtual void        rebuild(void);

        /// ˢ��ģ�� 
        virtual void        refresh(void);

        /// ��������ģ�ʹ�ϸ
        virtual void        setBoldSize(Flt size);
        /// �õ�����ģ�ʹ�ϸ
        virtual Flt         getBoldSize(void);

        /// ������ɫ
        virtual void        setColour(Color colour);
        /// �õ���ɫ
        virtual Color       getColour();

        /// ���ÿɼ���
        virtual void        setVisible(Bool visible);
        /// �õ��ɼ���
        virtual Bool        getVisible();

        /// ��������
        virtual void        setRect(RectF rect, Bool isOnce=true) ;

        /////////////////////////////////////////////////////////////////////////////

        /// ��Ⱦ�¼�
        virtual    void     postFindVisibleObjects(Ogre::SceneManager* source, 
                                Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v);


    protected:

        /// ��������ζ���
        void                createOgreManualObject();
        /// ���ٶ���ζ���
        void                destroyOgreManualObject();

        /// �������� 
        void                buildMaterial(void);
        /// �õ��������� 
        Str                 getMaterialName(void);

        /// ����Ogre���ֶ�����ģ�Ͷ���
        void                buildMesh(void);
        /// ����Ogre���ֶ�����ģ�Ͷ���
        void                refreshMesh(void);

        /// ����Ogre���ֶ�����ģ�Ͷ���
        void                refreshMeshData(void);


    private:

        //////////////////////////////////////////////////////

        //  ��������
        Scene*      mScene;

        /// ����ģ�ʹ�ϸ
        Flt         mBoldSize;
        /// ��ɫ 
        ColourValue mColour;

        RectF       mRect;

        Int			mIsOnceShow;

        //////////////////////////////////////////////////////

        /// Ogre���ֶ�����ģ�Ͷ���
        Ogre::ManualObject* mOgreManualObject;
        /// �ڵ����
        MGSceneNode* mSceneNode;
        /// Ogre���ʽӿ� 
        Ogre::MaterialPtr   mOgreMaterialPtr;

        ////////////////////////////////////////////////////////
    };

}

/******************************************************************************/

#endif