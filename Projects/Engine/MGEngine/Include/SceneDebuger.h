/******************************************************************************/
#ifndef _SCENEDEBUGER_H_
#define _SCENEDEBUGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ISceneDebuger.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    // ����������
    /******************************************************************************/
    class SceneDebuger : public ISceneDebuger
    {
    public:
        SceneDebuger(Scene* scene);
        virtual ~SceneDebuger();

    public:

        /// ��Ⱦ�¼�
        virtual    void     postFindVisibleObjects(Ogre::SceneManager* source, 
                                Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v);

        /// ����
        void            update( Flt delta );

        /// ���
        void            clear();

        // ��ʾϵͳ��ͼ
        virtual void    showTexture(Str name);
        // ����ϵͳ��ͼ
        virtual void    hideTexture();

    protected:

        /// ����ģ��
        void            createOgreManualObject();
        /// ����ģ��
        void            destroyOgreManualObject();

        /// ��������
        void            setTexture(Str texName);
        /// ��������
        void            buildMaterial();
        /// ���������
        void            buildMesh(Str matName);
        /// ����Ogre���ֶ�����ģ�Ͷ���
        void            refreshMeshData(void);

    private:

        // MG Scene
        Scene*  mScene;

        Bool mVisible;

        /// Ogre���ֶ�����ģ�Ͷ���
        Ogre::ManualObject* mOgreManualObject;
        /// �ڵ����
        MGSceneNode*        mSceneNode;
        /// Ogre���ʽӿ� 
        Ogre::MaterialPtr   mOgreMaterialPtr;
        // TextureDebugName
        Str                 mTextureDebugName;
        /// ��ɫ 
        ColourValue         mColour;
    };

}

/******************************************************************************/

#endif
