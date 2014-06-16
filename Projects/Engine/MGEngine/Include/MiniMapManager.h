/******************************************************************************/
#ifndef _MINIMAPMANAGER_H_
#define _MINIMAPMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IMiniMap.h"
#include "IImage.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //��Ӱ����
    /******************************************************************************/
    class MiniMapManager : public IMiniMapManager, public Ogre::RenderTargetListener
    {
    public:
        MiniMapManager(Scene* scene);
        virtual ~MiniMapManager();

    public:

        /////////////////////////////////////////////////////////////////

        // ����MiniMap
        virtual void            genarateMiniMap(Vec2 center, Vec2 size, Str savePath, Vec2 mapSize);

        /////////////////////////////////////////////////////////////////

        // �Ƿ���
        Bool                    isActive();
        // �Ƿ���
        Bool                    isTest();

        /////////////////////////////////////////////////////////////////

        /// ��Ӧ���ø���
        void                    applyCameraConfig();
        // ���泡��״̬
        void                    saveSceneState();
        // ��ԭ����״̬
        void                    revertSceneState();

        /////////////////////////////////////////////////////////////////

        // ������Ⱦ��ͼ
        void                    loadRenderTexture();
        // ж����Ⱦ��ͼ
        void                    unLoadRenderTexture();

        /////////////////////////////////////////////////////////////////

        // ����miniMap
        void                    startGenarateMiniMap(Vec2 center, Vec2 size, Str savePath, Vec2 mapSize);

    protected:

        /// Overridden from RenderTargetListener
        virtual void			preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
        virtual void			postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);

    private:

        Scene*  mScene;
        Bool	mActive;
        Bool    mIsTest;

		Ogre::String			mGroupName;

        TexturePtr              mRenderLightingMapTexture;
        Viewport*               mRenderLightingMapTextureViewport;

        ShadowTechnique         mCurrShadowTechnique;
        Bool                    mCurrAutoAspectRatio;
        Flt                     mCurrAspectRatio;
        Radian                  mCurrFov;
        Ogre::Quaternion        mCurrCamQua;
        Ogre::Vector3           mCurrCamPos;




    };

}

/******************************************************************************/

#endif
