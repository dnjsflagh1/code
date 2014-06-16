/******************************************************************************/
#ifndef _COLLISIONOBJECT_H_
#define _COLLISIONOBJECT_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ISceneNode.h"
#include "ICollisionObject.h"
#include "ManualMeshManager.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //碰撞模型
    /******************************************************************************/
    class CollisionObject : public ICollisionObject
    {
    public:
        CollisionObject( Scene* scene );
        virtual ~CollisionObject();
    
        // 是否被激活
        virtual void    setEnable(Bool enable);
        virtual Bool    getEnable();

        // 是否被移除
        virtual Bool    isRemoved();
        // 设置移除状态
        virtual void    setRemoved();

        /// 是否在区域内
        virtual Bool    isInRect(Vec2 pos) = 0;
        /// 是否在区域内
        virtual Bool    isIntersect(Vec2 pos, Flt& radius) = 0;

        /// 得到射线查询
        virtual Bool    getRayIntersection( Vec3& pos, Vec3& dir, Vec3& intersectPos ) = 0;

        /// 得到最低高度通过世界坐标
        virtual Bool    getStickHeight(Vec3 pos, Flt& height) = 0;
        virtual Bool    getStickHeight(ISceneNode* node, Flt& height) = 0;

    protected:

        Bool    mIsRemoved;
        Scene*  mScene;
        Bool    mEnable;
    };

    /******************************************************************************/
    // 碰撞模型
    /******************************************************************************/
    class MeshCollisionObject : public CollisionObject, public ISceneNodeLisitener
    {
    public:
        MeshCollisionObject( Scene* scene, ISceneNode* node, Str name, Str meshFileName, Str resourceGroupName, Vec3& pos, Qua& orientation, Vec3& scale );
        virtual ~MeshCollisionObject();

		//////////////////////////////////////////////////////////////////////////////////

        /// 是否在区域内
        virtual Bool    isInRect(Vec2 pos);
        /// 是否在区域内
        virtual Bool    isIntersect(Vec2 pos, Flt& radius);

        /// 得到射线查询
        virtual Bool    getRayIntersection( Vec3& pos, Vec3& dir, Vec3& intersectPos );
        /// 得到最低高度通过世界坐标
        virtual Bool    getStickHeight(Vec3 pos, Flt& height);
        virtual Bool    getStickHeight(ISceneNode* node, Flt& height);


		//////////////////////////////////////////////////////////////////////////////////

		// 更新世界障碍模型
		void                        refreshWorldCollisionTriangle();
		// 得到世界坐标
		Vector3                     getWorldPos(Vector3 localPos);
		// 得到世界坐标碰撞面片列表
		std::vector< Triangle3D >&  getWorldCollisionTriangleList();

    protected:

                void    loadMesh( Str name , Str meshFileName, Str resourceGroupName );
                void    unloadMesh();
                void    scaleMesh(Vec3 scale);

                Bool    isValidDistance(Vec2 pos1, Vec2 pos2, Flt radius);
                Vec3    getWorldPos(Vec3 localPos);
                Vec3    getLocalPos(Vec3 worldPos);
                Vec3    getLocalDir(Vec3 worldDir);

    protected:

        virtual void    onRemove();
        virtual void    onPositionChanged( Vec3& oldPos, Vec3 newPos );
        virtual void    onOrientationChanged( Qua& oldQua, Qua newQua );
        virtual void    onScaleChanged( Vec3& oldScale, Vec3 newPosScale );
        virtual void    onVisibleChanged( Bool visible );

    private:

        MeshPtr     mMesh;
        ISceneNode* mNode;

        std::vector< Triangle3D > mBaseTriangle3DList;
        std::vector< Triangle3D > mTriangle3DList;
		std::vector< Triangle3D > mWorldTriangle3DList;
        Bool                    mWorldTriangle3DListDirty;

        Rect    mRect;
        Rect    mWorldFullRect;
        
        Vec3    mPos;
        Qua     mQua;
        Qua     mInverseQua;
        Vec3    mScale;
        Flt     mBaseRadius;
        Flt     mBaseDiameter;
        Flt     mRadius;
        Flt     mDiameter;
    };



}

/******************************************************************************/

#endif
