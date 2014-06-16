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
    //��ײģ��
    /******************************************************************************/
    class CollisionObject : public ICollisionObject
    {
    public:
        CollisionObject( Scene* scene );
        virtual ~CollisionObject();
    
        // �Ƿ񱻼���
        virtual void    setEnable(Bool enable);
        virtual Bool    getEnable();

        // �Ƿ��Ƴ�
        virtual Bool    isRemoved();
        // �����Ƴ�״̬
        virtual void    setRemoved();

        /// �Ƿ���������
        virtual Bool    isInRect(Vec2 pos) = 0;
        /// �Ƿ���������
        virtual Bool    isIntersect(Vec2 pos, Flt& radius) = 0;

        /// �õ����߲�ѯ
        virtual Bool    getRayIntersection( Vec3& pos, Vec3& dir, Vec3& intersectPos ) = 0;

        /// �õ���͸߶�ͨ����������
        virtual Bool    getStickHeight(Vec3 pos, Flt& height) = 0;
        virtual Bool    getStickHeight(ISceneNode* node, Flt& height) = 0;

    protected:

        Bool    mIsRemoved;
        Scene*  mScene;
        Bool    mEnable;
    };

    /******************************************************************************/
    // ��ײģ��
    /******************************************************************************/
    class MeshCollisionObject : public CollisionObject, public ISceneNodeLisitener
    {
    public:
        MeshCollisionObject( Scene* scene, ISceneNode* node, Str name, Str meshFileName, Str resourceGroupName, Vec3& pos, Qua& orientation, Vec3& scale );
        virtual ~MeshCollisionObject();

		//////////////////////////////////////////////////////////////////////////////////

        /// �Ƿ���������
        virtual Bool    isInRect(Vec2 pos);
        /// �Ƿ���������
        virtual Bool    isIntersect(Vec2 pos, Flt& radius);

        /// �õ����߲�ѯ
        virtual Bool    getRayIntersection( Vec3& pos, Vec3& dir, Vec3& intersectPos );
        /// �õ���͸߶�ͨ����������
        virtual Bool    getStickHeight(Vec3 pos, Flt& height);
        virtual Bool    getStickHeight(ISceneNode* node, Flt& height);


		//////////////////////////////////////////////////////////////////////////////////

		// ���������ϰ�ģ��
		void                        refreshWorldCollisionTriangle();
		// �õ���������
		Vector3                     getWorldPos(Vector3 localPos);
		// �õ�����������ײ��Ƭ�б�
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
