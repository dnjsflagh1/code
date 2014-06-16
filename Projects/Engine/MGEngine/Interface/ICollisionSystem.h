/******************************************************************************/
#ifndef _ICOLLISIONSYSTEM_H
#define _ICOLLISIONSYSTEM_H
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneObject.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // 碰撞检测类型
    enum CollisionCheckType {
        CCT_NONE,
        CCT_BOUNDING_BOX,
        CCT_GEOMETRY,
    };

    /******************************************************************************/
    struct ICollisionHit 
    {
        // 击中的位置
        Vec3                pos;
        // 击中的对象
        ISceneObject*       sceneObject;
    };

    /******************************************************************************/
    //基础的碰撞回调接口
    /******************************************************************************/
    struct ICollisionCallback
    {
    public:
        // 碰撞检测的类型
        CollisionCheckType              checkType;

        //忽略的对象
        std::vector<ISceneObject*>      ignoreList;

        //是否检测查询标志位
        Bool                            isCheckQueryFlagsMask;
        //查询标志位
        UInt                            queryFlagsMask;

        // 是否只检测一个
        Bool                            isCheckSingle;

    public:

        ICollisionCallback()
            :isCheckSingle( true )
            ,checkType(CCT_BOUNDING_BOX)
            ,queryFlagsMask(0)
            ,isCheckQueryFlagsMask(true)
        {
        }

        // 是否是空的
        virtual Bool isEmpty() = NULL;
        
        // 击中事件
        virtual Bool hit( ICollisionHit &hit ) = NULL;

        // 判断是否允许检测
        virtual Bool isAllow(ISceneObject* obj)
        {
            // 判断是否是忽略的对象
            std::vector<ISceneObject*>::iterator iter = ignoreList.begin();
            for ( ; iter != ignoreList.end(); ++iter)
            {
                if ( *iter == obj )
                    return false;
            }

            // 判断查询标志位
            if ( isCheckQueryFlagsMask )
                if (!(obj->getQueryFlags() & queryFlagsMask))
                    return false;

            return true;
        }
    };

    /******************************************************************************/
    //基础的场景对象碰撞回调接口
    /******************************************************************************/
    struct ISceneObjectCollisionCallback : public ICollisionCallback
    {
    public:

        // 碰撞到的对象
        std::vector<std::pair<Vec3, ISceneObject*>> collisionList;

    public:

        ISceneObjectCollisionCallback()
            :ICollisionCallback()
        {
        }
       
        virtual Bool hit( ICollisionHit &hit )
        {
            if ( hit.sceneObject )
            {
                collisionList.push_back(std::pair<Vec3, ISceneObject*>(hit.pos, hit.sceneObject));
            }
            
            return true;
        }

        virtual Bool isEmpty()
        {
            if( collisionList.size() > 0 )
            {
                return false;
            }
            return true;
        }
    };

    /******************************************************************************/
    //基础的碎片碰撞回调接口
    /******************************************************************************/
    struct IFragmentCollisionCallback : public ICollisionCallback
    {
    public:
        
        // 碰撞到的对象
        std::vector<Vec3> collisionList;

    public:

        IFragmentCollisionCallback()
            :ICollisionCallback()
        {
        }

        virtual Bool hit( ICollisionHit &hit )
        {
            if ( hit.sceneObject )
            {
                collisionList.push_back(hit.pos);
            }
            
            return true;
        }

        virtual Bool isEmpty()
        {
            if( collisionList.size() > 0 )
            {
                return false;
            }
            return true;
        }
    };

    /******************************************************************************/
    //游戏中碰撞对象
    /******************************************************************************/
    class ICollisionSystem 
    {
    public:

        //////////////////////////////////////////////////////////////////////////////

        /// 得到鼠标射线查询结果
        virtual Bool        checkMouseRayCollision(ICollisionCallback* callback,Vec2 offset=Vec2(0,0)) = 0;

        /// 得到射线查询结果
        virtual Bool        checkRayCollision(Vec3 startPos, Vec3 startDir, ICollisionCallback* callback) = 0;
        /// 得到直线查询结果
        virtual Bool        checkLineCollision(Vec3 startPos, Vec3 endPos, ICollisionCallback* callback) = 0;
        /// 得到框选查询结果
        virtual Bool        checkRectCollision(MG::RectF rect, ICollisionCallback* callback) = 0;
        /// 得到圆圈查询结果
        virtual Bool        checkCircleCollision(Vec3 center, Flt radius, ICollisionCallback* callback) = 0;


        //////////////////////////////////////////////////////////////////////////////

        /** 得到鼠标射线交点
			返回值: 0: 没有相交
					1：与地形相交
					2：与模型相交
		*/
        virtual Int        getMouseRayIntersection(Vec3& intersectPos,Bool isPrecise = false) = 0;
		/** 得到射线交点
			返回值: 0: 没有相交
			1：与地形相交
			2：与模型相交
		*/
        virtual Int        getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise = false) = 0;

		/** 得到最低碰撞高度
			返回值: 0: 没有相交
			1：与地形相交
			2：与模型相交
		*/
        virtual Int        getStickHeight( Vec3 worldPos , Flt& height ) = 0;
        virtual Int        getStickHeight( ISceneNode* node, Flt& height ) = 0;

        //////////////////////////////////////////////////////////////////////////////
    };

}

/******************************************************************************/
#endif
