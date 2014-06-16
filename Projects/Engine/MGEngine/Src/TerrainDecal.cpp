/******************************************************************************/
#include "stdafx.h"
#include "TerrainDecal.h"
#include "Scene.h"
#include "MGSceneNode.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //    TerrainDecal
    /******************************************************************************/
    //---------------------------------------------------------------------
    TerrainDecal::TerrainDecal(Scene* scene, TerrainDecalSet* set)
        :mTerrainDecalSet(set)
        ,mScene(scene)
        ,mSize(0.5)
        ,mHalfSize(0.25)
        ,mDirty(false)
        ,mPos(Vec3(0,0,0))
        ,mVisible(true)
    {
        for (Int i=0;i<9;i++)
        {
            mBuildVertexPos[i] = Vec3(0,0,0);
        }

        for (Int i=0;i<9;i++)
        {
            mBuildVertexUV[i] = Vec2(0,0);
        }
    }

    //---------------------------------------------------------------------
    TerrainDecal::~TerrainDecal()
    {
        
    }

    //---------------------------------------------------------------------
    void TerrainDecal::setPosition(Vec3& pos)
    {
        mPos = pos;
        setChangeDirty();
    }

    //---------------------------------------------------------------------
    Vec3& TerrainDecal::getPosition()
    {
        return mPos;
    }

    //---------------------------------------------------------------------
    void TerrainDecal::setSize(int size)
    {
        mSize = size;
        mHalfSize = mSize * 0.5;
        setChangeDirty();
    }

    //---------------------------------------------------------------------
    int TerrainDecal::getSize()
    {
        return mSize;
    }
	//---------------------------------------------------------------------
	void TerrainDecal::setNormal( Vec3& normal )
	{

	}
	//---------------------------------------------------------------------
	Vec3& TerrainDecal::getNormal()
	{
		return Vec3(0, 1, 0);
	}
    //---------------------------------------------------------------------
    void TerrainDecal::setVisible(Bool visible)
    {
        mVisible = visible;
    }

    //---------------------------------------------------------------------
    Bool TerrainDecal::getVisible()
    {
        return mVisible;
    }

	//---------------------------------------------------------------------
	IDecalType TerrainDecal::getType()
	{
		return DT_SIMPLE;
	}

    //---------------------------------------------------------------------
    void TerrainDecal::setChangeDirty()
    {
        mDirty = true;
    }

    //---------------------------------------------------------------------
    Bool TerrainDecal::getChangeDirty()
    {
        return mDirty;
    }

    //---------------------------------------------------------------------
    void TerrainDecal::clearChangeDirty()
    {
        mDirty = false;
    }

    //---------------------------------------------------------------------
    Flt TerrainDecal::getPlaneHeight(Vec3& pos, Plane& plane, Flt defaultHeight)
    {
        if (plane.normal.y!=0)
        {
            return (-plane.normal.x * pos.x  -plane.normal.z * pos.z  - plane.d) / plane.normal.y;
        }
        return defaultHeight;
    }

    //---------------------------------------------------------------------
    void TerrainDecal::buildVertex(Ogre::ManualObject* manualObject)
    {
        buildVertex1(manualObject);
    }

    //---------------------------------------------------------------------
    void TerrainDecal::buildIndex(Ogre::ManualObject* manualObject,UInt index)
    {
        buildIndex1(manualObject,index);
    }

    //---------------------------------------------------------------------
    void TerrainDecal::buildVertex1(Ogre::ManualObject* manualObject)
    {

        /*
        0    1
        *----*
        |    | 
        2    3 
        *----*
        */

        if ( getChangeDirty() )
        {
            clearChangeDirty();

            Flt cx,cy,cz;
            cx = mPos.x;
            cy = mPos.y;
            cz = mPos.z;

            ///////////////////////////////////////////////////////////////

            mBuildVertexPos[0] = Vec3(cx-mSize, cy, cz-mSize);
            mBuildVertexPos[1] = Vec3(cx+mSize, cy, cz-mSize);
            mBuildVertexPos[2] = Vec3(cx-mSize, cy, cz+mSize);
            mBuildVertexPos[3] = Vec3(cx+mSize, cy, cz+mSize);

            ///////////////////////////////////////////////////////////////

            mBuildVertexUV[0] = Vec2(0, 0);
            mBuildVertexUV[1] = Vec2(1, 0);
            mBuildVertexUV[2] = Vec2(0, 1);
            mBuildVertexUV[3] = Vec2(1, 1);

            mScene->getCollisionSystem()->getStickHeight( mBuildVertexPos[0], mBuildVertexPos[0].y );
            mScene->getCollisionSystem()->getStickHeight( mBuildVertexPos[1], mBuildVertexPos[1].y );
            mScene->getCollisionSystem()->getStickHeight( mBuildVertexPos[2], mBuildVertexPos[2].y );
            mScene->getCollisionSystem()->getStickHeight( mBuildVertexPos[3], mBuildVertexPos[3].y );

            // 偏移一定位置
            
            mBuildVertexPos[0].y  = Ogre::Math::Clamp( mBuildVertexPos[0].y,    (Flt)(cy-mHalfSize), (Flt)(cy+mHalfSize));
            mBuildVertexPos[1].y  = Ogre::Math::Clamp( mBuildVertexPos[1].y,    (Flt)(cy-mHalfSize), (Flt)(cy+mHalfSize));
            mBuildVertexPos[2].y  = Ogre::Math::Clamp( mBuildVertexPos[2].y,    (Flt)(cy-mHalfSize), (Flt)(cy+mHalfSize));
            mBuildVertexPos[3].y  = Ogre::Math::Clamp( mBuildVertexPos[3].y,    (Flt)(cy-mHalfSize), (Flt)(cy+mHalfSize));

            mBuildVertexPos[0].y += 0.2;
            mBuildVertexPos[1].y += 0.2;
            mBuildVertexPos[2].y += 0.2;
            mBuildVertexPos[3].y += 0.2;

            //TerrainManager* terrain = mScene->getTerrainManager();
            //Plane plane;
            //if ( terrain )
            //{
            //    TerrainChunk* chunk = terrain->getTerrainChunkByWorldPos( Vec2(mPos.x, mPos.z) );
            //    if ( chunk )
            //    {
            //        TerrainGroundSurface* surface = chunk->getTerrainGroundSurface();
            //        Vector3 p0, p1, p2, p3;

            //        // 0 
            //        surface->getTerrainPlaneByWorldPosition(mBuildVertexPos[0].x, mBuildVertexPos[0].z, p0, p1, p2, p3);
            //        plane.redefine(p0,p1,p2);
            //        mBuildVertexPos[0].y = getPlaneHeight(mBuildVertexPos[0],plane,p0.y);

            //        // 1
            //        surface->getTerrainPlaneByWorldPosition(mBuildVertexPos[1].x, mBuildVertexPos[1].z, p0, p1, p2, p3);
            //        plane.redefine(p0,p1,p2);
            //        mBuildVertexPos[1].y = getPlaneHeight(mBuildVertexPos[1],plane,p0.y);

            //        // 2
            //        surface->getTerrainPlaneByWorldPosition(mBuildVertexPos[2].x, mBuildVertexPos[2].z, p0, p1, p2, p3);
            //        plane.redefine(p0,p1,p2);
            //        mBuildVertexPos[2].y = getPlaneHeight(mBuildVertexPos[2],plane,p0.y);

            //        // 3
            //        surface->getTerrainPlaneByWorldPosition(mBuildVertexPos[3].x, mBuildVertexPos[3].z, p0, p1, p2, p3);
            //        plane.redefine(p0,p1,p2);
            //        mBuildVertexPos[3].y = getPlaneHeight(mBuildVertexPos[3],plane,p0.y);

            //        ////////////////////////////////////////////////////////////////////////////
            //    }
            //}

            ///////////////////////////////////////////////////////////////////////////////
        }

        /////////////////////////////////////////////////////////////////////////////

        for (Int i=0;i<4;i++)
        {
            Vec3& pos   = mBuildVertexPos[i];
            Vec2& uv    = mBuildVertexUV[i];

            manualObject->position( Vector3(pos.x, pos.y + 0.01, pos.z) );
            manualObject->textureCoord( uv.x, uv.y );
        }
    }

   
    //---------------------------------------------------------------------
    void TerrainDecal::buildVertex2(Ogre::ManualObject* manualObject)
    {
        /*
            0    1    2
            *----*----*
            |    |    |
            3    4    5
            *----*----*
            |    |    |
            6    7    8
            *----*----*
        */
        /////////////////////////////////////////////////////////////////////////////

        //if ( getChangeDirty() )
        //{
        //    clearChangeDirty();

        //    Flt cx,cy,cz;
        //    cx = mPos.x;
        //    cy = mPos.y;
        //    cz = mPos.z;

        //    ///////////////////////////////////////////////////////////////
        //    
        //    mBuildVertexPos[0] = Vec3(cx-mSize, cy, cz-mSize);
        //    mBuildVertexPos[1] = Vec3(cx,       cy, cz-mSize);
        //    mBuildVertexPos[2] = Vec3(cx+mSize, cy, cz-mSize);

        //    mBuildVertexPos[3] = Vec3(cx-mSize, cy, cz);
        //    mBuildVertexPos[4] = Vec3(cx,       cy, cz);
        //    mBuildVertexPos[5] = Vec3(cx+mSize, cy, cz);

        //    mBuildVertexPos[6] = Vec3(cx-mSize, cy, cz+mSize);
        //    mBuildVertexPos[7] = Vec3(cx,       cy, cz+mSize);
        //    mBuildVertexPos[8] = Vec3(cx+mSize, cy, cz+mSize);

        //    ///////////////////////////////////////////////////////////////

        //    mBuildVertexUV[0] = Vec2(0,     0);
        //    mBuildVertexUV[1] = Vec2(0.5,   0);
        //    mBuildVertexUV[2] = Vec2(1,     0);

        //    mBuildVertexUV[3] = Vec2(0,     0.5);
        //    mBuildVertexUV[4] = Vec2(0.5,   0.5);
        //    mBuildVertexUV[5] = Vec2(1,     0.5);

        //    mBuildVertexUV[6] = Vec2(0,     1);
        //    mBuildVertexUV[7] = Vec2(0.5,   1);
        //    mBuildVertexUV[8] = Vec2(1,     1);


        //    TerrainManager* terrain = mScene->getTerrainManager();
        //    Plane plane;
        //    if ( terrain )
        //    {
        //        TerrainSurface* tileMgr = terrain->getTerrainSurface();
        //        if ( tileMgr )
        //        {
        //            Vector3 p0, p1, p2, p3, p4, p5, p6, p7, p8, p9;

        //            // 0 
        //            tileMgr->getTerrainPlaneByWorldPosition(mBuildVertexPos[0].x, mBuildVertexPos[0].z, p0, p1, p3, p4);
        //            // 2
        //            tileMgr->getTerrainPlaneByWorldPosition(mBuildVertexPos[2].x, mBuildVertexPos[2].z, p1, p2, p4, p5);
        //            // 6
        //            tileMgr->getTerrainPlaneByWorldPosition(mBuildVertexPos[6].x, mBuildVertexPos[6].z, p3, p4, p6, p7);
        //            // 8
        //            tileMgr->getTerrainPlaneByWorldPosition(mBuildVertexPos[8].x, mBuildVertexPos[8].z, p4, p5, p7, p8);

        //            ////////////////////////////////////////////////////////////////////////////

        //            // 0
        //            plane.redefine(p0,p3,p1);
        //            mBuildVertexPos[0].y = getPlaneHeight(mBuildVertexPos[0],plane,p0.y);
        //            
        //            // 1
        //            if ( (p1.x > mBuildVertexPos[0].x)&&(p1.x < mBuildVertexPos[2].x) )
        //            {
        //                mBuildVertexPos[1].x = p1.x;
        //                mBuildVertexUV[1].x = abs(mBuildVertexPos[1].x - mBuildVertexPos[0].x) / (mSize * 2);
        //            }
        //            plane.redefine(p0,p3,p1);
        //            mBuildVertexPos[1].y = getPlaneHeight(mBuildVertexPos[1],plane,p0.y);
        //            
        //            // 2
        //            plane.redefine(p1,p0,p2);
        //            mBuildVertexPos[2].y = getPlaneHeight(mBuildVertexPos[2],plane,p1.y);
        //            
        //    
        //            ////////////////////////////////////////////////////////////////////////////

        //            // 3
        //            if ( (p3.z > mBuildVertexPos[3].z)&&(p3.z < mBuildVertexPos[6].z) )
        //            {
        //                mBuildVertexPos[3].z = p3.z;
        //                mBuildVertexUV[3].y = abs(mBuildVertexPos[3].z - mBuildVertexPos[0].z) / (mSize * 2);
        //            }
        //            plane.redefine(p0,p3,p1);
        //            mBuildVertexPos[3].y = getPlaneHeight(mBuildVertexPos[3],plane,p0.y);
        //            
        //            // 4
        //            mBuildVertexPos[4].x = mBuildVertexPos[1].x;
        //            mBuildVertexPos[4].z = mBuildVertexPos[3].z;
        //            plane.redefine(p1,p3,p4);
        //            mBuildVertexPos[4].y = getPlaneHeight(mBuildVertexPos[4],plane,p0.y);

        //            mBuildVertexUV[4].x = mBuildVertexUV[1].x;
        //            mBuildVertexUV[4].y = mBuildVertexUV[3].y;
        //            // 5
        //            mBuildVertexPos[5].z = mBuildVertexPos[3].z;
        //            plane.redefine(p2,p4,p5);
        //            mBuildVertexPos[5].y = getPlaneHeight(mBuildVertexPos[5],plane,p1.y);

        //            mBuildVertexUV[5].y = mBuildVertexUV[3].y;

        //            ////////////////////////////////////////////////////////////////////////////

        //            // 6
        //            plane.redefine(p3,p6,p4);
        //            mBuildVertexPos[6].y = getPlaneHeight(mBuildVertexPos[6],plane,p3.y);
        //            // 7
        //            mBuildVertexPos[7].x = mBuildVertexPos[1].x;
        //            plane.redefine(p4,p6,p7);
        //            mBuildVertexPos[7].y = getPlaneHeight(mBuildVertexPos[7],plane,p3.y);

        //            mBuildVertexUV[7].x = mBuildVertexUV[1].x;
        //            // 8
        //            plane.redefine(p5,p7,p8);
        //            mBuildVertexPos[8].y = getPlaneHeight(mBuildVertexPos[8],plane,p4.y);

        //        }
        //    }
        //    
        //    ///////////////////////////////////////////////////////////////////////////////
        //}


        ///////////////////////////////////////////////////////////////////////////////

        //for (Int i=0;i<9;i++)
        //{
        //    Vec3& pos   = mBuildVertexPos[i];
        //    Vec2& uv    = mBuildVertexUV[i];

        //    manualObject->position( Vector3(pos.x, pos.y, pos.z) );
        //    manualObject->textureCoord( uv.x, uv.y );
        //}
    }

    //---------------------------------------------------------------------
    void TerrainDecal::buildIndex1(Ogre::ManualObject* manualObject,UInt index)
    {
        Int indexAccumulate = index * 4;

        manualObject->index( indexAccumulate+0 );
        manualObject->index( indexAccumulate+2 );
        manualObject->index( indexAccumulate+1 );

        manualObject->index( indexAccumulate+1 );
        manualObject->index( indexAccumulate+2 );
        manualObject->index( indexAccumulate+3 );
    }

    //---------------------------------------------------------------------
    void TerrainDecal::buildIndex2(Ogre::ManualObject* manualObject,UInt index)
    {
        Int indexAccumulate = index * 9;
        
        manualObject->index( indexAccumulate+0 );
        manualObject->index( indexAccumulate+3 );
        manualObject->index( indexAccumulate+1 );

        manualObject->index( indexAccumulate+1 );
        manualObject->index( indexAccumulate+3 );
        manualObject->index( indexAccumulate+4 );

        /////////////////////////////////////////////////////////////////////////////

        manualObject->index( indexAccumulate+1 );
        manualObject->index( indexAccumulate+4 );
        manualObject->index( indexAccumulate+2 );

        manualObject->index( indexAccumulate+2 );
        manualObject->index( indexAccumulate+4 );
        manualObject->index( indexAccumulate+5 );

        /////////////////////////////////////////////////////////////////////////////

        manualObject->index( indexAccumulate+3 );
        manualObject->index( indexAccumulate+6 );
        manualObject->index( indexAccumulate+4 );

        manualObject->index( indexAccumulate+4 );
        manualObject->index( indexAccumulate+6 );
        manualObject->index( indexAccumulate+7 );

        /////////////////////////////////////////////////////////////////////////////

        manualObject->index( indexAccumulate+4 );
        manualObject->index( indexAccumulate+7 );
        manualObject->index( indexAccumulate+5 );

        manualObject->index( indexAccumulate+5 );
        manualObject->index( indexAccumulate+7 );
        manualObject->index( indexAccumulate+8 );
       
    }
	/******************************************************************************/
    //    TerrainDecalSet
    /******************************************************************************/
    TerrainDecalSet::TerrainDecalSet(CChar* name, CChar* texFileName, UInt num, Scene* scene)
        :mOgreDisplaySceneNode(NULL)
        ,mOgreManualObject(NULL)
        ,mSceneNode(NULL)
        ,mScene(scene)
        ,mName(name)
        ,mTexFileName(texFileName)
        ,mDecalNum(num)
    {
        createTerrainDecals();

        buildMaterial();
        createOgreManualObject();
        buildMesh();
    }
    
    //---------------------------------------------------------------------
    TerrainDecalSet::~TerrainDecalSet()
    {
        destroyTerrainDecals();

        destroyOgreManualObject();
    }
    
    //---------------------------------------------------------------------
    void TerrainDecalSet::update( Flt delta )
    {
       
    }
	//---------------------------------------------------------------------
	void TerrainDecalSet::preRendering()
	{
		updateMesh();
	}
	//---------------------------------------------------------------------
	void TerrainDecalSet::postRendering()
	{

	}
    //---------------------------------------------------------------------
    TerrainDecal* TerrainDecalSet::getDecal(UInt index)
    {
        if ( (index >=0) && (index < mDecalNum) )
            return mTerrainDecals[index];

        return NULL;
    }

    //---------------------------------------------------------------------
    UInt TerrainDecalSet::getDecalNum()
    {
        return mDecalNum;
    }

    //---------------------------------------------------------------------
    void TerrainDecalSet::createTerrainDecals()
    {
        for ( UInt i=0; i<mDecalNum; i++ )
        {
            TerrainDecal* decal = MG_NEW TerrainDecal(mScene,this);
            mTerrainDecals.push_back(decal);
        }
    }

    //---------------------------------------------------------------------
    void TerrainDecalSet::destroyTerrainDecals()
    {
        for ( UInt i=0; i<mDecalNum; i++ )
        {
            MG_SAFE_DELETE(mTerrainDecals[i]);
        }
        mTerrainDecals.clear();
    }

    //---------------------------------------------------------------------
    void TerrainDecalSet::buildMaterial()
    {
        Str matName = "DecalSet_Material_" + mName;

        /// 得到或创建材质
        mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().getByName(matName);
        if (mOgreMaterialPtr.isNull())
        {
            mOgreMaterialPtr = Ogre::MaterialManager::getSingleton().create(matName, 
                Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            mOgreMaterialPtr->setReceiveShadows( false );
        }

        /// 得到渲染通道
        Ogre::Pass* pass = mOgreMaterialPtr->getTechnique(0)->getPass(0);
        pass->setLightingEnabled(false);
        pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        pass->setSceneBlending(Ogre::SBF_SOURCE_ALPHA,Ogre::SBF_ONE_MINUS_SOURCE_ALPHA);
        pass->setCullingMode(Ogre::CULL_NONE);
        pass->setDepthCheckEnabled(true);
        pass->setDepthWriteEnabled(true);
        pass->setDepthBias(0.005);

        /// 得到或创建贴图单元
        Ogre::TextureUnitState* textureUnitState = NULL;
        if ( pass->getNumTextureUnitStates() == 0 )
        {
            textureUnitState = pass->createTextureUnitState( mTexFileName );
            textureUnitState->setTextureAddressingMode( TextureUnitState::TAM_CLAMP );
        }else
        {
            textureUnitState = pass->getTextureUnitState(0);
            textureUnitState->setTextureName( mTexFileName );
			textureUnitState->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
        }
    }

    //---------------------------------------------------------------------
    void TerrainDecalSet::createOgreManualObject()
    {
        mOgreManualObject = mScene->getOgreSceneManager()->createManualObject( mName );
		mOgreManualObject->setCastShadows(false);
        //mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_3);
        mOgreManualObject->setRenderQueueGroup(Ogre::RENDER_QUEUE_6);

        //创建实体节点
        mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);
        //绑定实体
        mSceneNode->getOgreSceneNode()->attachObject( mOgreManualObject );
    }

    //---------------------------------------------------------------------
    void TerrainDecalSet::destroyOgreManualObject()
    {
        //销毁实体对象
        if ( mOgreManualObject )
        {
            mScene->getOgreSceneManager()->destroyManualObject(mOgreManualObject);
            mOgreManualObject = NULL;
        }

        //销毁实体节点
        MG_SAFE_DELETE( mSceneNode );
    }

    //---------------------------------------------------------------------
    void TerrainDecalSet::buildMesh()
    {
        mOgreManualObject->clear();

        mOgreManualObject->setDynamic(true);

        mOgreManualObject->begin(  mOgreMaterialPtr->getName(), Ogre::RenderOperation::OT_TRIANGLE_LIST );

        {
            // vertex
            TerrainDecal* decal = NULL;
            for (UInt i=0; i < mDecalNum; i++ )
            {
                decal = mTerrainDecals[i];
                if (decal->getVisible())
                {
                    decal->buildVertex(mOgreManualObject);
                }
            }
            
            // index
            UInt index = 0;
            for ( UInt i=0; i < mDecalNum; i++ )
            {
                decal = mTerrainDecals[i];
                if (decal->getVisible())
                {
                    decal->buildIndex(mOgreManualObject,index);
                    index++;
                }
            }
        }

        mOgreManualObject->end();
    }

    //---------------------------------------------------------------------
    void TerrainDecalSet::updateMesh()
    {
        if ( mOgreManualObject )
        {
            mOgreManualObject->beginUpdate(0);

            // vertex
            TerrainDecal* decal = NULL;
            for ( UInt i=0; i<mDecalNum; i++ )
            {
                decal = mTerrainDecals[i];
                if (decal->getVisible())
                {
                    decal->buildVertex(mOgreManualObject);
                }
            }

            // index
            UInt index = 0;
            for ( UInt i=0; i < mDecalNum; i++ )
            {
                decal = mTerrainDecals[i];
                if (decal->getVisible())
                {
                    decal->buildIndex(mOgreManualObject,index);
                    index++;
                }
            }

            mOgreManualObject->end();
        }
    }

	void TerrainDecalSet::setSize( int size )
	{
		for ( UInt i=0; i<mDecalNum; i++ )
		{
			if (size <= 0)
			{
				mTerrainDecals[i]->setSize(1);
			}
			else
				mTerrainDecals[i]->setSize(size);
		}
	}

	int TerrainDecalSet::getSize()
	{
		if (mDecalNum)
		{
			return mTerrainDecals[0]->getSize();
		}
		else 
			return 0;
	}


}