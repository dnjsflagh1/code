/******************************************************************************/
#ifndef _TERRAINDECAL_H
#define _TERRAINDECAL_H
/******************************************************************************/

#include "EnginePreqs.h"
#include "IDecal.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    /**地形的贴花
    */
    /******************************************************************************/
    class TerrainDecal : public IDecal
    {
    public:
        TerrainDecal(Scene* scene, TerrainDecalSet* set);
        virtual ~TerrainDecal();

        /// 设置位置
        virtual void        setPosition(Vec3& pos);
        /// 设置位置
        virtual Vec3&       getPosition();
		/// 设置法线
		virtual void		setNormal(Vec3& normal);
		/// 得到法线
		virtual Vec3&		getNormal();
        /// 设置可见度
        virtual void        setVisible(Bool visible);
        /// 设置可见度
        virtual Bool        getVisible();
		/// 获得贴花类型
		virtual IDecalType	getType(); 
		/// 设置大小
				void        setSize(int size);
		/// 得到大小
				int         getSize();
        //设置改变标志位
                void        setChangeDirty();
        //得到改变标志位
                Bool        getChangeDirty();
        //清空改变标志位
                void        clearChangeDirty();
    
        //构造ManualObject
                void        buildVertex(Ogre::ManualObject* manualObject);
                void        buildIndex(Ogre::ManualObject* manualObject,UInt index);

        //得到平面高度
                Flt         getPlaneHeight(Vec3& pos, Plane& plane, Flt defaultHeight);
    private:

                void        buildVertex1(Ogre::ManualObject* manualObject);
                void        buildVertex2(Ogre::ManualObject* manualObject);

                void        buildIndex1(Ogre::ManualObject* manualObject,UInt index);
                void        buildIndex2(Ogre::ManualObject* manualObject,UInt index);

    private:
        
        Scene*              mScene;
        Bool                mDirty;
        TerrainDecalSet*    mTerrainDecalSet;
        Flt                 mSize;
        Flt                 mHalfSize;
        Vec3                mPos;
        Bool                mVisible;

        Vec3                mBuildVertexPos[9];
        Vec2                mBuildVertexUV[9];
    };


    /******************************************************************************/
    /**地形的贴花集合
    */
    /******************************************************************************/
    class TerrainDecalSet : public IDecalSet
    {
    public:
        TerrainDecalSet(CChar* name, CChar* texFileName, UInt num, Scene* scene);
        virtual ~TerrainDecalSet();

        /// 得到贴花接口
        virtual TerrainDecal*           getDecal(UInt index);
        /// 得到贴花数量
        virtual UInt                    getDecalNum();
		/// 设置大小
		virtual void					setSize(int size);
		/// 获取大小
		virtual int						getSize();
		/// 更新
		virtual void                    update( Flt delta );

		virtual void					preRendering();

		virtual void					postRendering();
    protected:
        
        /// 创建模型
                void                    createOgreManualObject();
        /// 销毁模型
                void                    destroyOgreManualObject();

        /// 构建材质
                void                    buildMaterial();
        /// 构建多边形
                void                    buildMesh();

        /// 更新多边形
                void                    updateMesh();

    protected:

        /// 创建贴花对象
                void                    createTerrainDecals();
        /// 销毁贴花对象
                void                    destroyTerrainDecals();

    private:

        Scene*      mScene;

        Str         mName;
        Str         mTexFileName;
        UInt        mDecalNum;

        ///节点对象
        MGSceneNode*        mSceneNode;

        /// Ogre材质接口
        Ogre::MaterialPtr   mOgreMaterialPtr;
        /// Ogre的位置显示节点对象
        Ogre::SceneNode*    mOgreDisplaySceneNode;
        /// Ogre可手动创建模型对象
        Ogre::ManualObject* mOgreManualObject;

        /// 贴花对象
        std::vector<TerrainDecal*> mTerrainDecals;
    };


}


/******************************************************************************/

#endif