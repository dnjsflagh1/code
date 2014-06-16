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
    //阴影管理
    /******************************************************************************/
    class MiniMapManager : public IMiniMapManager, public Ogre::RenderTargetListener
    {
    public:
        MiniMapManager(Scene* scene);
        virtual ~MiniMapManager();

    public:

        /////////////////////////////////////////////////////////////////

        // 生成MiniMap
        virtual void            genarateMiniMap(Vec2 center, Vec2 size, Str savePath, Vec2 mapSize);

        /////////////////////////////////////////////////////////////////

        // 是否活动中
        Bool                    isActive();
        // 是否活动中
        Bool                    isTest();

        /////////////////////////////////////////////////////////////////

        /// 响应配置更改
        void                    applyCameraConfig();
        // 保存场景状态
        void                    saveSceneState();
        // 还原场景状态
        void                    revertSceneState();

        /////////////////////////////////////////////////////////////////

        // 加载渲染贴图
        void                    loadRenderTexture();
        // 卸载渲染贴图
        void                    unLoadRenderTexture();

        /////////////////////////////////////////////////////////////////

        // 生成miniMap
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
