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
    //���߲�ѯ����
    /******************************************************************************/
    class MGRaySceneQuery : public RaySceneQuery
    {
    public:
        MGRaySceneQuery(SceneManager* creator);
        virtual ~MGRaySceneQuery();

        // ���ûص�����
                void        setCallback(ICollisionCallback* callback);
        // ִ��
    RaySceneQueryResult&    execute(void);
                void        execute(RaySceneQueryListener* listener);

                Bool        checkMovableObject(RaySceneQueryListener* listener,MovableObject* obj);
                Bool        checkBoundingBox(RaySceneQueryListener* listener,const AxisAlignedBox& aabb,MovableObject* obj);  
    private:

        ICollisionCallback* mCallback;
    };


    /******************************************************************************/
    //��ײϵͳ
    /******************************************************************************/
    class CollisionSystem : public ICollisionSystem
    {
    public:
        CollisionSystem( Scene* scene );
        virtual ~CollisionSystem();

        /// ��ʼ��
        virtual void            initialize( Ogre::SceneManager* ogreScene );
        /// ����ʼ��
		virtual void            unInitialize();

        /// ���
        virtual void            update( Flt delta );
        /// ���
        virtual void            clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// �õ���������
        virtual Scene*          getScene();
        /// ���ò�ѯ��־
                void            setQueryMask(ICollisionCallback* callback);

        //////////////////////////////////////////////////////////////////////////////////////////////////
        
        // ������ײ����
        CollisionObject*        createCollisionObject( IEntity* entity );

        MeshCollisionObject*    createMeshCollisionObject( ISceneNode* node, Str meshFileName, Str resourceGroupName, Vec3& pos, Qua& orientation, Vec3& scale );
        void                    destroyMeshCollisionObject( MeshCollisionObject* obj );

        // ������ײ����
        void                    destroyCollisionObject( CollisionObject* obj );
        void                    destroyAllCollisionObject();

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// �õ�������߲�ѯ���
        virtual Bool            checkMouseRayCollision(ICollisionCallback* callback,Vec2 offset=Vec2(0,0));
        /// �õ����߲�ѯ���
        virtual Bool            checkRayCollision(Vec3 startPos, Vec3 startDir, ICollisionCallback* callback) ;
        /// �õ�ֱ�߲�ѯ���
        virtual Bool            checkLineCollision(Vec3 startPos, Vec3 endPos, ICollisionCallback* callback);
        /// �õ���ѡ��ѯ���
        virtual Bool            checkRectCollision(MG::RectF rect, ICollisionCallback* callback);
        virtual Bool            checkRectCollision(MG::RectF rect, ISceneObject* obj, ICollisionCallback* callback);
        /// �õ�ԲȦ��ѯ���
        virtual Bool            checkCircleCollision(Vec3 center, Flt radius, ICollisionCallback* callback);
        virtual Bool            checkCircleCollision(Vec3 center, Flt radius, ISceneObject* obj, ICollisionCallback* callback);
    
        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// �õ�������߽���
        virtual Int				getMouseRayIntersection(Vec3& intersectPos,Bool isPrecise = false);
        /// �õ����߽���
        virtual Int				getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise = false);

        /// �õ��߶�
        virtual Int				getStickHeight( Vec3 worldPos , Flt& height );
        virtual Int				getStickHeight( ISceneNode* node, Flt& height );
                Int				getStickHeight( ISceneNode* node,Vec3 worldPos, Flt& height );

        //////////////////////////////////////////////////////////////////////////////////////////////////

    private:

        // ��Ϸ����
        Scene*                      mScene;
        Ogre::SceneManager*         mOgreScene;
        /// ���߲�ѯ
        MGRaySceneQuery*            mRayQuery;

        /// ��ײ����
        std::list<CollisionObject*> mCollisionObjectList;
        /// ��ײʵ������
        NameGenerator               mCollisionNameGenerator;

    };
}

/******************************************************************************/

#endif
