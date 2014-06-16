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
    // 场景调试器
    /******************************************************************************/
    class SceneDebuger : public ISceneDebuger
    {
    public:
        SceneDebuger(Scene* scene);
        virtual ~SceneDebuger();

    public:

        /// 渲染事件
        virtual    void     postFindVisibleObjects(Ogre::SceneManager* source, 
                                Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v);

        /// 更新
        void            update( Flt delta );

        /// 清空
        void            clear();

        // 显示系统贴图
        virtual void    showTexture(Str name);
        // 隐藏系统贴图
        virtual void    hideTexture();

    protected:

        /// 创建模型
        void            createOgreManualObject();
        /// 销毁模型
        void            destroyOgreManualObject();

        /// 构建材质
        void            setTexture(Str texName);
        /// 构建材质
        void            buildMaterial();
        /// 构建多边形
        void            buildMesh(Str matName);
        /// 构造Ogre可手动创建模型对象
        void            refreshMeshData(void);

    private:

        // MG Scene
        Scene*  mScene;

        Bool mVisible;

        /// Ogre可手动创建模型对象
        Ogre::ManualObject* mOgreManualObject;
        /// 节点对象
        MGSceneNode*        mSceneNode;
        /// Ogre材质接口 
        Ogre::MaterialPtr   mOgreMaterialPtr;
        // TextureDebugName
        Str                 mTextureDebugName;
        /// 颜色 
        ColourValue         mColour;
    };

}

/******************************************************************************/

#endif
