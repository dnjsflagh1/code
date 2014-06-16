/******************************************************************************/
#include "stdafx.h"
#include "CollisionObject.h"
#include "Scene.h"
/******************************************************************************/

namespace MG
{


    /******************************************************************************/
    // CollisionObject
    /******************************************************************************/
    
    //-----------------------------------------------------------------------
    CollisionObject::CollisionObject(Scene* scene)
        :mScene(scene)
        ,mIsRemoved(false)
        ,mEnable(true)
    {

    }

    //-----------------------------------------------------------------------
    CollisionObject::~CollisionObject()
    {

    }

    //-----------------------------------------------------------------------
    void CollisionObject::setEnable(Bool enable)
    {
        mEnable = enable;
    }

    //-----------------------------------------------------------------------
    Bool CollisionObject::getEnable()
    {
        return mEnable ;
    }

    //-----------------------------------------------------------------------
    Bool CollisionObject::isRemoved()
    {
        return mIsRemoved;
    }

    //-----------------------------------------------------------------------
    void CollisionObject::setRemoved()
    {
        mIsRemoved = true;
    }


    /******************************************************************************/
    // MeshCollisionObject
    /******************************************************************************/

    //-----------------------------------------------------------------------
    MeshCollisionObject::MeshCollisionObject( Scene* scene, ISceneNode* node, Str name, Str meshFileName, Str resourceGroupName, Vec3& pos, Qua& orientation, Vec3& scale )
        :CollisionObject(scene)
        ,mNode(node)
        ,mBaseRadius(1)
        ,mBaseDiameter(2)
        ,mRadius(1)
        ,mDiameter(2)
        ,mPos(pos)
        ,mQua(orientation)
        ,mInverseQua(orientation.Inverse()) 
        ,mScale(scale)
		,mWorldTriangle3DListDirty(true)
    {
        loadMesh( name, meshFileName, resourceGroupName );

        scaleMesh(scale);

        if ( mNode )
        {
            // 不需要解除
            mNode->addSceneNodeLisitener( "CollisionObject_Listener", this );
        }
    }

    //-----------------------------------------------------------------------
    MeshCollisionObject::~MeshCollisionObject()
    {
        unloadMesh();
		if ( mNode )
		{
			// 不需要解除
			mNode->removeSceneNodeLisitener( "CollisionObject_Listener" );
		}
    }

    //-----------------------------------------------------------------------
    Bool MeshCollisionObject::isInRect(Vec2 pos)
    {
        if ( isValidDistance( Vec2(mPos.x,mPos.z), pos, mRadius ) == false )
            return false;

        return true;
    }

    //-----------------------------------------------------------------------
    Bool MeshCollisionObject::isIntersect(Vec2 pos, Flt& radius)
    {
        if ( isValidDistance( Vec2(mPos.x,mPos.z), pos, mRadius + radius ) == true )
            return true;
        return false;
    }

    //-----------------------------------------------------------------------
    Bool MeshCollisionObject::isValidDistance(Vec2 pos1, Vec2 pos2, Flt radius)
    {
        Vec2 dist = pos1 - pos2;

        Flt xDist = abs( dist.x );
        Flt yDist = abs( dist.y );

        if ( xDist > radius )
            return false;
        if ( yDist > radius )
            return false;

        return true;
    }

    //-----------------------------------------------------------------------
    Vec3 MeshCollisionObject::getWorldPos(Vec3 localPos)
    {
        Vec3 worldPos = mQua * localPos;

        worldPos = worldPos + mPos;

        return worldPos;
    }

    //-----------------------------------------------------------------------
    Vec3 MeshCollisionObject::getLocalPos(Vec3 worldPos)
    {
        Vec3 localPos = worldPos - mPos;

        localPos = mInverseQua * localPos;

        return localPos;
    }

    //-----------------------------------------------------------------------
    Vec3 MeshCollisionObject::getLocalDir(Vec3 worldDir)
    {
        Vec3 localDir = mInverseQua * worldDir;
        return localDir;
    }

    //-----------------------------------------------------------------------
    Bool MeshCollisionObject::getStickHeight(ISceneNode* node, Flt& height)
    {
        if ( mNode == node )
            return false;

        Vec3 pos;
        node->getPosition( pos );

        return getStickHeight( pos , height );
    }

    //-----------------------------------------------------------------------
    Bool MeshCollisionObject::getRayIntersection(  Vec3& pos, Vec3& dir, Vec3& intersectPos )
    {
        if ( getEnable() == false )
            return false;

        if ( isRemoved() )
            return false;

        //////////////////////////////////////////////////////

        Vec3 localPos = getLocalPos( pos );
        Vec3 localDir = getLocalDir( dir );

        Ogre::Ray ray(Vector3(localPos.x,localPos.y,localPos.z),Vector3(localDir.x,localDir.y,localDir.z));

        //////////////////////////////////////////////////////

        std::pair< bool, Real > intersect;
        UInt triCount =  mTriangle3DList.size();
        for (UInt i = 0; i < triCount; i++)
        {
            Triangle3D& tri = mTriangle3DList[i];

            intersect = ray.intersects( tri.plane );

            if ( intersect.first )
            {
                Vector3 tempIntersectPos = ray.getPoint( intersect.second );	

                if ( Math::pointInTri3D(tempIntersectPos,tri.t0,tri.t1,tri.t2,tri.plane.normal) )
                {
                    intersectPos = getWorldPos( Vec3(tempIntersectPos.x,tempIntersectPos.y,tempIntersectPos.z) );
                    return true;
                }
            }
        }

        return false;
    }

    //-----------------------------------------------------------------------
    Bool MeshCollisionObject::getStickHeight(Vec3 pos, Flt& height)
    {
        if ( getEnable() == false )
            return false;

        if ( isRemoved() )
            return false;

        if ( isInRect(Vec2(pos.x,pos.z)) == false )
            return false;

        //////////////////////////////////////////////////////

        Vec3 localPos = getLocalPos( pos );

        Vec2 pos2D = Vec2( localPos.x, localPos.z );   
        Flt checkHeight = mDiameter + 10;
        localPos.y = checkHeight;

        //////////////////////////////////////////////////////

        std::pair< bool, Real > intersect;
        Ogre::Ray ray;
        ray.setOrigin( Vector3(localPos.x, localPos.y, localPos.z ) );
        ray.setDirection( -Vector3::UNIT_Y );
        UInt triCount =  mTriangle3DList.size();
        for (UInt i = 0; i < triCount; i++)
        {
            Triangle3D& tri = mTriangle3DList[i];

            if ( isValidDistance( Vec2(tri.t0.x,tri.t0.z), pos2D, mRadius ) == false )
                continue;
            if ( isValidDistance( Vec2(tri.t1.x,tri.t1.z), pos2D, mRadius ) == false )
                continue;
            if ( isValidDistance( Vec2(tri.t2.x,tri.t2.z), pos2D, mRadius ) == false )
                continue;
            
            intersect = ray.intersects( tri.plane );

            if ( intersect.first )
            {
                Vector3 tempIntersectPos = ray.getPoint( intersect.second );	

                if ( Math::pointInTri3D(tempIntersectPos,tri.t0,tri.t1,tri.t2,tri.plane.normal) )
                {
                    Vec3 intersectPos = getWorldPos( Vec3(tempIntersectPos.x,tempIntersectPos.y,tempIntersectPos.z) );
                    height = intersectPos.y;
                    return true;
                }
            }
        }
        
        return false;
    }
    
    //-----------------------------------------------------------------------
    void MeshCollisionObject::loadMesh( Str name , Str meshFileName, Str resourceGroupName )
    {
        mMesh = MeshManager::getSingleton().load( meshFileName,resourceGroupName );

        const AxisAlignedBox& box = mMesh->getBounds();
        Vector3 halfSize = box.getHalfSize();
        halfSize.y = 0;

        mBaseRadius     = halfSize.length();
        mBaseDiameter   = mRadius * 2;
        mRadius         = mBaseRadius;
        mDiameter       = mBaseDiameter;
        //mRadius = mMesh->getBoundingSphereRadius();

        ManualMeshManager::getInstance().getTriangle3DList( mMesh, mBaseTriangle3DList );
    }

    //-----------------------------------------------------------------------
    void MeshCollisionObject::scaleMesh(Vec3 scale)
    {
        UInt triCount =  mBaseTriangle3DList.size();
        mTriangle3DList.clear();
        mTriangle3DList.resize( triCount );
        for (UInt i = 0; i < triCount; i++)
        {
            Triangle3D& baseTri         = mBaseTriangle3DList[i];
            Triangle3D& scaleTri    = mTriangle3DList[i];

            scaleTri.t0 = baseTri.t0 * Vector3(scale.x,scale.y,scale.z);
            scaleTri.t1 = baseTri.t1 * Vector3(scale.x,scale.y,scale.z);
            scaleTri.t2 = baseTri.t2 * Vector3(scale.x,scale.y,scale.z);
            scaleTri.plane = Plane( scaleTri.t0, scaleTri.t1, scaleTri.t2 );
        }
        mRadius     = mBaseRadius * scale.length();
        mDiameter   = mBaseDiameter * scale.length();
    }

    //-----------------------------------------------------------------------
    void MeshCollisionObject::unloadMesh()
    {
        mBaseTriangle3DList.clear();
        mTriangle3DList.clear();
    }

    //-----------------------------------------------------------------------
    void MeshCollisionObject::onRemove()
    {
        setRemoved();
    }

    //-----------------------------------------------------------------------
    void MeshCollisionObject::onPositionChanged( Vec3& oldPos, Vec3 newPos )
    {
        mPos = newPos;
		mWorldTriangle3DListDirty = true;
    }

    //-----------------------------------------------------------------------
    void MeshCollisionObject::onOrientationChanged( Qua& oldQua, Qua newQua )
    {
        mQua.w = newQua.w;
        mQua.x = newQua.x;
        mQua.y = newQua.y;
        mQua.z = newQua.z;

        mInverseQua = mQua.Inverse();

		mWorldTriangle3DListDirty = true;
    }

    //-----------------------------------------------------------------------
    void MeshCollisionObject::onScaleChanged( Vec3& oldScale, Vec3 newPosScale )
    {
        mScale = newPosScale;
        scaleMesh(mScale);
    }

    //-----------------------------------------------------------------------
    void MeshCollisionObject::onVisibleChanged( Bool visible )
    {
        
    }

	//-----------------------------------------------------------------------
	void MeshCollisionObject::refreshWorldCollisionTriangle()
	{
		if ( mWorldTriangle3DListDirty )
		{
			UInt triCount =  mTriangle3DList.size();

			if ( triCount > 0 )
			{
				if ( mWorldTriangle3DList.size() != triCount )
				{
					/*mWorldTriangle3DList.reserve( triCount );*/
					mWorldTriangle3DList.resize( triCount );
				}

				for (UInt i = 0; i < triCount; i++)
				{
					Triangle3D& tri     = mTriangle3DList[i];
					Triangle3D& wTri    = mWorldTriangle3DList[i];

					wTri.t0 = getWorldPos(tri.t0);
					wTri.t1 = getWorldPos(tri.t1);
					wTri.t2 = getWorldPos(tri.t2);
				}
			}

			mWorldTriangle3DListDirty = false;
		}
	}

	//-----------------------------------------------------------------------
	Vector3 MeshCollisionObject::getWorldPos(Vector3 localPos)
	{
		Vec3 worldPos = mQua * Vec3(localPos.x,localPos.y,localPos.z);

		worldPos = worldPos + mPos;

		return Vector3(worldPos.x,worldPos.y,worldPos.z);
	}

	//-----------------------------------------------------------------------
	std::vector< Triangle3D >& MeshCollisionObject::getWorldCollisionTriangleList()
	{
		refreshWorldCollisionTriangle();
		return mWorldTriangle3DList;
	}

}