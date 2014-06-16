/******************************************************************************/
#ifndef _COLLISIONSYSTEM_H_
#define _COLLISIONSYSTEM_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "OgreSceneQuery.h"
#include "ICollisionSystem.h"

/******************************************************************************/
namespace MG
{


    /******************************************************************************/
    //射线查询对象
    /******************************************************************************/
    class MGRaySceneQuery : public RaySceneQuery
    {
    public:
        MGRaySceneQuery(SceneManager* creator);
        virtual ~MGRaySceneQuery();

        // 设置回调对象
                void        setCallback(ICollisionCallback* callback);
        // 执行
    RaySceneQueryResult&    execute(void);
                void        execute(RaySceneQueryListener* listener);

                Bool        checkMovableObject(RaySceneQueryListener* listener,MovableObject* obj);
                Bool        checkBoundingBox(RaySceneQueryListener* listener,const AxisAlignedBox& aabb,MovableObject* obj);  
    private:

        ICollisionCallback* mCallback;
    };


    /******************************************************************************/
    //碰撞系统
    /******************************************************************************/
    class CollisionSystem : public ICollisionSystem
    {
    public:
        CollisionSystem( Scene* scene );
        virtual ~CollisionSystem();

        /// 初始化
        virtual void            initialize( Ogre::SceneManager* ogreScene );
        /// 反初始化
		virtual void            unInitialize();

        /// 清空
        virtual void            update( Flt delta );
        /// 清空
        virtual void            clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// 得到场景对象
        virtual Scene*          getScene();
        /// 设置查询标志
                void            setQueryMask(ICollisionCallback* callback);

        //////////////////////////////////////////////////////////////////////////////////////////////////
        
        // 创建碰撞对象
        CollisionObject*        createCollisionObject( IEntity* entity );

        MeshCollisionObject*    createMeshCollisionObject( ISceneNode* node, Str meshFileName, Str resourceGroupName, Vec3& pos, Qua& orientation, Vec3& scale );
        void                    destroyMeshCollisionObject( MeshCollisionObject* obj );

        // 销毁碰撞对象
        void                    destroyCollisionObject( CollisionObject* obj );
        void                    destroyAllCollisionObject();

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// 得到鼠标射线查询结果
        virtual Bool            checkMouseRayCollision(ICollisionCallback* callback,Vec2 offset=Vec2(0,0));
        /// 得到射线查询结果
        virtual Bool            checkRayCollision(Vec3 startPos, Vec3 startDir, ICollisionCallback* callback) ;
        /// 得到直线查询结果
        virtual Bool            checkLineCollision(Vec3 startPos, Vec3 endPos, ICollisionCallback* callback);
        /// 得到框选查询结果
        virtual Bool            checkRectCollision(MG::RectF rect, ICollisionCallback* callback);
        virtual Bool            checkRectCollision(MG::RectF rect, ISceneObject* obj, ICollisionCallback* callback);
        /// 得到圆圈查询结果
        virtual Bool            checkCircleCollision(Vec3 center, Flt radius, ICollisionCallback* callback);
        virtual Bool            checkCircleCollision(Vec3 center, Flt radius, ISceneObject* obj, ICollisionCallback* callback);
    
        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// 得到鼠标射线交点
        virtual Int				getMouseRayIntersection(Vec3& intersectPos,Bool isPrecise = false);
        /// 得到射线交点
        virtual Int				getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise = false);

        /// 得到高度
        virtual Int				getStickHeight( Vec3 worldPos , Flt& height );
        virtual Int				getStickHeight( ISceneNode* node, Flt& height );
                Int				getStickHeight( ISceneNode* node,Vec3 worldPos, Flt& height );

        //////////////////////////////////////////////////////////////////////////////////////////////////

    private:

        // 游戏场景
        Scene*                      mScene;
        Ogre::SceneManager*         mOgreScene;
        /// 射线查询
        MGRaySceneQuery*            mRayQuery;

        /// 碰撞对象
        std::list<CollisionObject*> mCollisionObjectList;
        /// 碰撞实体名字
        NameGenerator               mCollisionNameGenerator;

    };
}

/******************************************************************************/

#endif
