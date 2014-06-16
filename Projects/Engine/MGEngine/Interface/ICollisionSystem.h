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
    // ��ײ�������
    enum CollisionCheckType {
        CCT_NONE,
        CCT_BOUNDING_BOX,
        CCT_GEOMETRY,
    };

    /******************************************************************************/
    struct ICollisionHit 
    {
        // ���е�λ��
        Vec3                pos;
        // ���еĶ���
        ISceneObject*       sceneObject;
    };

    /******************************************************************************/
    //��������ײ�ص��ӿ�
    /******************************************************************************/
    struct ICollisionCallback
    {
    public:
        // ��ײ��������
        CollisionCheckType              checkType;

        //���ԵĶ���
        std::vector<ISceneObject*>      ignoreList;

        //�Ƿ����ѯ��־λ
        Bool                            isCheckQueryFlagsMask;
        //��ѯ��־λ
        UInt                            queryFlagsMask;

        // �Ƿ�ֻ���һ��
        Bool                            isCheckSingle;

    public:

        ICollisionCallback()
            :isCheckSingle( true )
            ,checkType(CCT_BOUNDING_BOX)
            ,queryFlagsMask(0)
            ,isCheckQueryFlagsMask(true)
        {
        }

        // �Ƿ��ǿյ�
        virtual Bool isEmpty() = NULL;
        
        // �����¼�
        virtual Bool hit( ICollisionHit &hit ) = NULL;

        // �ж��Ƿ�������
        virtual Bool isAllow(ISceneObject* obj)
        {
            // �ж��Ƿ��Ǻ��ԵĶ���
            std::vector<ISceneObject*>::iterator iter = ignoreList.begin();
            for ( ; iter != ignoreList.end(); ++iter)
            {
                if ( *iter == obj )
                    return false;
            }

            // �жϲ�ѯ��־λ
            if ( isCheckQueryFlagsMask )
                if (!(obj->getQueryFlags() & queryFlagsMask))
                    return false;

            return true;
        }
    };

    /******************************************************************************/
    //�����ĳ���������ײ�ص��ӿ�
    /******************************************************************************/
    struct ISceneObjectCollisionCallback : public ICollisionCallback
    {
    public:

        // ��ײ���Ķ���
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
    //��������Ƭ��ײ�ص��ӿ�
    /******************************************************************************/
    struct IFragmentCollisionCallback : public ICollisionCallback
    {
    public:
        
        // ��ײ���Ķ���
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
    //��Ϸ����ײ����
    /******************************************************************************/
    class ICollisionSystem 
    {
    public:

        //////////////////////////////////////////////////////////////////////////////

        /// �õ�������߲�ѯ���
        virtual Bool        checkMouseRayCollision(ICollisionCallback* callback,Vec2 offset=Vec2(0,0)) = 0;

        /// �õ����߲�ѯ���
        virtual Bool        checkRayCollision(Vec3 startPos, Vec3 startDir, ICollisionCallback* callback) = 0;
        /// �õ�ֱ�߲�ѯ���
        virtual Bool        checkLineCollision(Vec3 startPos, Vec3 endPos, ICollisionCallback* callback) = 0;
        /// �õ���ѡ��ѯ���
        virtual Bool        checkRectCollision(MG::RectF rect, ICollisionCallback* callback) = 0;
        /// �õ�ԲȦ��ѯ���
        virtual Bool        checkCircleCollision(Vec3 center, Flt radius, ICollisionCallback* callback) = 0;


        //////////////////////////////////////////////////////////////////////////////

        /** �õ�������߽���
			����ֵ: 0: û���ཻ
					1��������ཻ
					2����ģ���ཻ
		*/
        virtual Int        getMouseRayIntersection(Vec3& intersectPos,Bool isPrecise = false) = 0;
		/** �õ����߽���
			����ֵ: 0: û���ཻ
			1��������ཻ
			2����ģ���ཻ
		*/
        virtual Int        getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise = false) = 0;

		/** �õ������ײ�߶�
			����ֵ: 0: û���ཻ
			1��������ཻ
			2����ģ���ཻ
		*/
        virtual Int        getStickHeight( Vec3 worldPos , Flt& height ) = 0;
        virtual Int        getStickHeight( ISceneNode* node, Flt& height ) = 0;

        //////////////////////////////////////////////////////////////////////////////
    };

}

/******************************************************************************/
#endif
