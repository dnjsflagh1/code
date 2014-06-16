/******************************************************************************/
#ifndef _POLYLINEWIREFRAMEDECORATOR_H_
#define _POLYLINEWIREFRAMEDECORATOR_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ManualMeshManager.h"
#include "IWireframeManager.h"
#include "Polyline.h"

/******************************************************************************/

namespace MG
{


    /**
    -----------------------------------------------------------------------------
    #note:	描述折线外形模型信息
    每条折线中的线段和控制点由TwistyBoxMeshData描述外观
    -----------------------------------------------------------------------------
    */
    class PolylineWireframeDecorator : public PolylineListener, public IPolylineWireframeDecorator
    {
    public:
        PolylineWireframeDecorator(const String& name, Scene* scene);
        virtual ~PolylineWireframeDecorator();

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

        /// 得到被装饰的Polyline
        virtual Polyline*   getPolyline(void);

    protected:

        /// 创建多边形对象
        void                createOgreManualObject();
        /// 销毁多边形对象
        void                destroyOgreManualObject();

        /// 创建材质 
        String              createOrRetrieveOgreMaterial(void);

        /// 构造模型数据
        void                buildMeshData(void);

        /// 构造Ogre可手动创建模型对象
        void                buildOgreManualObject(void);
        
        /// 构造Ogre可手动创建模型对象
        void                refreshOgreManualObject(void);

        /// 设置是否与折线对象保持改动的同步
        void                setSyncEnable(bool enable);

    private:

        /// 填充mesh数据到Ogre可手动创建模型对象中
        void                fillMeshDataInOgreManualObject(void);

    private:

        //  场景对象
        Scene*      mScene;
        //  折线对象
        Polyline*   mPolyline;
        //  是否保持改动同步
        Bool        mSyncEnable;
        /// 折线模型粗细
        Flt         mBoldSize;
        /// 颜色 
        ColourValue mColour;

        //////////////////////////////////////////////////////

        /// Ogre可手动创建模型对象
        Ogre::ManualObject* mOgreManualObject;
        /// 节点对象
        MGSceneNode* mSceneNode;
        /// Ogre材质接口 
        Ogre::MaterialPtr   mOgreMaterialPtr;

        ////////////////////////////////////////////////////////

        /// 组成折线模型的TwistyBoxMeshData对象列表
        typedef std::list<TwistyBoxMeshData> TwistyBoxMeshDataList;
        TwistyBoxMeshDataList mTwistyBoxMeshDatas;
    };

}

/******************************************************************************/

#endif