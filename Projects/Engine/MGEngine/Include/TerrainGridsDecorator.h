/******************************************************************************/
#ifndef _TERRAINGRIDSDECORATOR_H_
#define _TERRAINGRIDSDECORATOR_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IWireframeManager.h"

/******************************************************************************/

namespace MG
{

    
    /**
    -----------------------------------------------------------------------------
    #note: 地形网格线框线列表
    -----------------------------------------------------------------------------
    */
    class TerrainChunkGridsLineList
    {
    public:
        TerrainChunkGridsLineList();

        void    build( TerrainManager* terrainMgr );
        std::vector<Vec3> mLinePointList;
    };


    /**
    -----------------------------------------------------------------------------
    #note: 地形网格逻辑线框线列表
    -----------------------------------------------------------------------------
    */
    class TerrainLogicGridsLineList
    {
    public:
        TerrainLogicGridsLineList();

        void    build( TerrainManager* terrainMgr );
        std::vector<Vec3> mLinePointList;
    };

    /**
    -----------------------------------------------------------------------------
    #note: 地形网格线框线列表
    -----------------------------------------------------------------------------
    */
    class TerrainTileGridsLineList
    {
    public:
        TerrainTileGridsLineList();

        void    build( TerrainManager* terrainMgr );
        std::vector<Vec3> mLinePointList;
    };


    /**
    -----------------------------------------------------------------------------
    #note: 地形网格线框显示
    -----------------------------------------------------------------------------
    */
    class TerrainGridsDecorator : public ITerrainGridsDecorator
    {
    public:
        TerrainGridsDecorator(const String& name, Scene* scene);
        virtual ~TerrainGridsDecorator();

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

        /// 设置颜色
        virtual void        setChunkColour(Color colour);
        /// 设置颜色
        virtual void        setTileColour(Color colour);

        /// 设置可见度
        virtual void        setVisible(Bool visible);
        /// 得到可见度
        virtual Bool        getVisible();


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

        //////////////////////////////////////////////////////

    private:

        //  场景对象
        Scene*                      mScene;
        /// 折线模型粗细
        Flt                         mBoldSize;

        /// 颜色 
        ColourValue                 mChunkColour;
        /// 颜色 
        ColourValue                 mTileColour;
        /// 颜色 
        ColourValue                 mLogicColour;

        //////////////////////////////////////////////////////

        /// Ogre可手动创建模型对象
        Ogre::ManualObject*         mOgreManualObject;
        /// 节点对象
        MGSceneNode*                mSceneNode;
        /// Ogre材质接口 
        Ogre::MaterialPtr           mOgreMaterialPtr;                   

        ////////////////////////////////////////////////////////

        TerrainChunkGridsLineList   mTerrainChunkGridsLineList;
        Int                         mTerrainChunkGridsLineBuildPointCount;

        ////////////////////////////////////////////////////////

        TerrainTileGridsLineList    mTerrainTileGridsLineList;
        Int                         mTerrainTileGridsLineBuildPointCount;

        ////////////////////////////////////////////////////////

        TerrainLogicGridsLineList   mTerrainLogicGridsLineList;
        Int                         mTerrainLogicGridsLineBuildPointCount;

    };

}

/******************************************************************************/

#endif