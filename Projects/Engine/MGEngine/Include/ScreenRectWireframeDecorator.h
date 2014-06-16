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
    #note:	屏幕矩形线框信息
    -----------------------------------------------------------------------------
    */
    class ScreenRectWireframeDecorator : public IScreenRectWireframeDecorator
    {
    public:
        ScreenRectWireframeDecorator(const String& name, Scene* scene);
        virtual ~ScreenRectWireframeDecorator();

        /// 更新
        virtual void        update(void);

        /// 构造
        virtual void        rebuild(void);

        /// 刷新模型 
        virtual void        refresh(void);

        /// 设置折线模型粗细
        virtual void        setBoldSize(Flt size);
        /// 得到折线模型粗细
        virtual Flt         getBoldSize(void);

        /// 设置颜色
        virtual void        setColour(Color colour);
        /// 得到颜色
        virtual Color       getColour();

        /// 设置可见度
        virtual void        setVisible(Bool visible);
        /// 得到可见度
        virtual Bool        getVisible();

        /// 设置区域
        virtual void        setRect(RectF rect, Bool isOnce=true) ;

        /////////////////////////////////////////////////////////////////////////////

        /// 渲染事件
        virtual    void     postFindVisibleObjects(Ogre::SceneManager* source, 
                                Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v);


    protected:

        /// 创建多边形对象
        void                createOgreManualObject();
        /// 销毁多边形对象
        void                destroyOgreManualObject();

        /// 创建材质 
        void                buildMaterial(void);
        /// 得到材质名字 
        Str                 getMaterialName(void);

        /// 构造Ogre可手动创建模型对象
        void                buildMesh(void);
        /// 构造Ogre可手动创建模型对象
        void                refreshMesh(void);

        /// 构造Ogre可手动创建模型对象
        void                refreshMeshData(void);


    private:

        //////////////////////////////////////////////////////

        //  场景对象
        Scene*      mScene;

        /// 折线模型粗细
        Flt         mBoldSize;
        /// 颜色 
        ColourValue mColour;

        RectF       mRect;

        Int			mIsOnceShow;

        //////////////////////////////////////////////////////

        /// Ogre可手动创建模型对象
        Ogre::ManualObject* mOgreManualObject;
        /// 节点对象
        MGSceneNode* mSceneNode;
        /// Ogre材质接口 
        Ogre::MaterialPtr   mOgreMaterialPtr;

        ////////////////////////////////////////////////////////
    };

}

/******************************************************************************/

#endif