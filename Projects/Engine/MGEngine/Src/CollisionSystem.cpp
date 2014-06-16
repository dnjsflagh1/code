/******************************************************************************/
#include "stdafx.h"
#include "Scene.h"
#include "CollisionSystem.h"
#include "MGEngineUtility.h"
#include "OgreSceneQuery.h"
#include "EngineMain.h"
#include "DynamicBlockObject.h"
#include "CollisionObject.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //MGRaySceneQuery
    /******************************************************************************/
    MGRaySceneQuery::MGRaySceneQuery(SceneManager* creator)
        : RaySceneQuery(creator)
        ,mCallback(NULL)
    {
        // No world geometry results supported
        mSupportedWorldFragments.insert(SceneQuery::WFT_NONE);
    }
    //-----------------------------------------------------------------------
    MGRaySceneQuery::~MGRaySceneQuery()
    {

    }
    //-----------------------------------------------------------------------
    void MGRaySceneQuery::setCallback(ICollisionCallback* callback)
    {
        mCallback = callback;
    }
    //-----------------------------------------------------------------------
    RaySceneQueryResult& MGRaySceneQuery::execute(void)
    {
        return RaySceneQuery::execute();
    }
    //-----------------------------------------------------------------------
    void MGRaySceneQuery::execute(RaySceneQueryListener* listener)
    {
        if ( mCallback == NULL )
            return;

        // Note that becuase we have no scene partitioning, we actually
        // perform a complete scene search even if restricted results are
        // requested; smarter scene manager queries can utilise the paritioning 
        // of the scene in order to reduce the number of intersection tests 
        // required to fulfil the query

        // Iterate over all movable types
        Root::MovableObjectFactoryIterator factIt = 
            Root::getSingleton().getMovableObjectFactoryIterator();
        while(factIt.hasMoreElements())
        {
            SceneManager::MovableObjectIterator objItA = 
                mParentSceneMgr->getMovableObjectIterator(
                factIt.getNext()->getType());
            while (objItA.hasMoreElements())
            {
                MovableObject* a = objItA.getNext();
                if ( checkMovableObject( listener, a ) )
                {
                    if ( mCallback->isCheckSingle )
                        return;
                }
            }
        }

        Scene* scene =  EngineMain::getInstance().getFirstScene();
        if ( scene )
        {
            std::map<String, EntityGroup*>::iterator iter = scene->mEntityGroup.begin();
            std::map<String, EntityGroup*>::iterator end_iter = scene->mEntityGroup.end();
            for( ; iter != end_iter; iter++ )
            {
                EntityGroup* group = iter->second;

                InstancedGeometry::BatchInstanceMap::iterator jter = group->mInstancedGeometry->mBatchInstanceMap.begin();
                for ( ;jter!=group->mInstancedGeometry->mBatchInstanceMap.end(); jter++ )
                {
                    InstancedGeometry::BatchInstance* batchInstance = jter->second;
                    if (batchInstance)
                    {
                        if ( checkMovableObject( NULL, batchInstance) )
                        {
                            InstancedGeometry::BatchInstance::InstancedObjectIterator instancedObjIter = batchInstance->getObjectIterator();
                            while(instancedObjIter.hasMoreElements())
                            {
                                InstancedGeometry::InstancedObject* instancedObject = instancedObjIter.getNext();
                                
                                const AxisAlignedBox& aabb = instancedObject->getBoundingBox();

                                if ( checkBoundingBox(listener,aabb,batchInstance) )
                                {
                                    if ( mCallback->isCheckSingle )
                                        return;
                                }
                            }
                        }
                    }
                }
            }

			//
			TreeManager* pTreeMgr = scene->getTreeManager();
			if (pTreeMgr != NULL)
			{
				//tree
				const std::map<String, Tree*>& pTreeMap = pTreeMgr->getAllTrees();
				for (std::map<String, Tree*>::const_iterator it = pTreeMap.begin(); it != pTreeMap.end(); ++it)
				{
					const AxisAlignedBox& aabb = it->second->getWorldBoundingBox();
					MovableObject* obj = it->second->getOgreMovable();
					if ( checkMovableObject(listener, obj) )
					{
						if ( mCallback->isCheckSingle )
							return;
					}
				}

				//grass
				const std::map<String, Grass*>& pGrassMap = pTreeMgr->getAllGrasses();
				for (std::map<String, Grass*>::const_iterator it = pGrassMap.begin(); it != pGrassMap.end(); ++it)
				{
					const AxisAlignedBox& aabb = it->second->getWorldBoundingBox();
					MovableObject* obj = it->second->getOgreMovable();
					if ( checkMovableObject(listener, obj) )
					{
						if ( mCallback->isCheckSingle )
							return;
					}
				}
			}
        }

        setCallback(NULL);
    }

    //-----------------------------------------------------------------------
    Bool MGRaySceneQuery::checkMovableObject(RaySceneQueryListener* listener,MovableObject* obj)
    {
        ISceneObject* sceneObj = NULL;
        MovableObject* a = obj;

        // skip whole group if type doesn't match
        if (!(a->getTypeFlags() & mQueryTypeMask))
            return false;

        if( (a->getQueryFlags() & mQueryMask) &&
            a->isInScene())
        {

            // check sceneObject allowable 
            if ( a->getUserAny().isEmpty()==false ) 
            {
                sceneObj = any_cast<ISceneObject*>( a->getUserAny() ) ;

                if ( sceneObj )
                {
                    if ( mCallback->isAllow( sceneObj ) )
                    {
                        // Do ray / box test
                        return checkBoundingBox(listener,a->getWorldBoundingBox(),a);
                    }
                }
            }
        }
        return false;
    }

    //-----------------------------------------------------------------------
    Bool MGRaySceneQuery::checkBoundingBox(RaySceneQueryListener* listener,const AxisAlignedBox& aabb,MovableObject* obj)
    {
        // Do ray / box test
        std::pair<bool, Real> result =
            mRay.intersects(aabb);

        if (result.first)
        {
            if ( listener && obj )
            {
                if (listener->queryResult(obj, result.second))
                {
                    return true;
                }
            }else
            {
                return true;
            }
        }
        return false;
    }

    /******************************************************************************/
    //CollisionSystem
    /******************************************************************************/
    //-----------------------------------------------------------------------
    CollisionSystem::CollisionSystem( Scene* scene )
        :mScene(scene)
        ,mRayQuery(NULL)
        ,mOgreScene(NULL)
        ,mCollisionNameGenerator("CollisionEntity")
    {
        
    }

    //-----------------------------------------------------------------------
    CollisionSystem::~CollisionSystem()
    {
        unInitialize();
    }

    //-----------------------------------------------------------------------
    void CollisionSystem::initialize( Ogre::SceneManager* ogreScene )
    {
        ///创建射线查询
        mRayQuery = MG_NEW MGRaySceneQuery( ogreScene );
        mRayQuery->setSortByDistance(true,10);
        mOgreScene = ogreScene;
    }
    
    //-----------------------------------------------------------------------
    void CollisionSystem::unInitialize()
    {
        MG_SAFE_DELETE( mRayQuery );
        mOgreScene = NULL;
    }

    //-----------------------------------------------------------------------
    void CollisionSystem::clear()
    {
        destroyAllCollisionObject();
        mCollisionNameGenerator.reset();
    }

    //-----------------------------------------------------------------------
    void CollisionSystem::update( Flt delta ) 
    {
    }

    //-----------------------------------------------------------------------
    Scene* CollisionSystem::getScene()
    {
        return mScene;
    }

    //-----------------------------------------------------------------------
    CollisionObject* CollisionSystem::createCollisionObject( IEntity* entity )
    {
        CollisionObject* result = NULL;

        if ( entity )
        {
            ISceneNode* node = entity->getSceneNode();
            if ( node )
            {
                U32 modelDeclID = entity->getModelObject()->getModelDeclarationID();

                ModelDeclaration* modelDecl = MG::ResourceManager::getSingletonPtr()->getModelDeclaration(modelDeclID);

                if( !modelDecl )
                {
					return result;
                }

				if ( ( modelDecl->RoadMeshFileName/*blockAllSideMeshFileName*/  != "0" ) &&
					( modelDecl->RoadMeshFileName.empty()/*blockAllSideMeshFileName.empty()*/ == false ) )
				{

					Vec3 pos;
					Qua orientation;
					Vec3 scale;
					entity->getSceneNode()->getPosition( pos );
					entity->getSceneNode()->getOrientation( orientation );
					entity->getSceneNode()->getScale( scale );

					result = createMeshCollisionObject( node, modelDecl->RoadMeshFileName/*blockAllSideMeshFileName*/, 
						modelDecl->path, pos, orientation, scale );
					return result;
				}

				if ( ( modelDecl->PassageMeshFileName/*blockAllSideMeshFileName*/  != "0" ) &&
					( modelDecl->PassageMeshFileName.empty()/*blockAllSideMeshFileName.empty()*/ == false ) )
				{

					Vec3 pos;
					Qua orientation;
					Vec3 scale;
					entity->getSceneNode()->getPosition( pos );
					entity->getSceneNode()->getOrientation( orientation );
					entity->getSceneNode()->getScale( scale );

					result = createMeshCollisionObject( node, modelDecl->PassageMeshFileName/*blockAllSideMeshFileName*/, 
						modelDecl->path, pos, orientation, scale );
					return result;
				}
            }
        }

        return result;
    }
    
    //-----------------------------------------------------------------------
    MeshCollisionObject* CollisionSystem::createMeshCollisionObject( ISceneNode* node, Str meshFileName, Str resourceGroupName, Vec3& pos, Qua& orientation, Vec3& scale )
    {
        Str name = Str("MeshCollisionObject_") + mCollisionNameGenerator.generate();

        MeshCollisionObject* obj = MG_NEW MeshCollisionObject( mScene, node, name, meshFileName, resourceGroupName, pos, orientation, scale );
        
        // 保存
        mCollisionObjectList.push_back( obj );

        return obj;
    }

    //-----------------------------------------------------------------------
    void CollisionSystem::destroyCollisionObject( CollisionObject* obj )
    {
        if ( obj==NULL )
            return ;

        Bool isExist = false;
        std::list<CollisionObject*>::iterator iter = mCollisionObjectList.begin();
        for ( ;iter != mCollisionObjectList.end(); iter++ )
        {
            if ( obj == *iter )
            {
                mCollisionObjectList.erase( iter );
                isExist = true;
                break;
            }
        }

        DYNAMIC_ASSERT( isExist );

        MG_SAFE_DELETE(obj);
    }

    //-----------------------------------------------------------------------
    void CollisionSystem::destroyAllCollisionObject()
    {
        std::list<CollisionObject*>::iterator iter = mCollisionObjectList.begin();
        for ( ;iter != mCollisionObjectList.end(); iter++ )
        {
            MG_SAFE_DELETE(*iter);
        }
        mCollisionObjectList.clear();
    }

    //-----------------------------------------------------------------------
    Bool CollisionSystem::checkMouseRayCollision(ICollisionCallback* callback,Vec2 offset)
    {
        Vec3 pos,dir;

        mScene->getActiveCamera()->getMouseViewportRay(pos,dir,Vec2(0,0));
        if ( checkRayCollision( pos, dir, callback ) )
        {
            return true;
        }

        mScene->getActiveCamera()->getMouseViewportRay(pos,dir,Vec2(offset.x,0));
        if ( checkRayCollision( pos, dir, callback ) )
        {
            return true;
        }

        mScene->getActiveCamera()->getMouseViewportRay(pos,dir,Vec2(0,offset.y));
        if ( checkRayCollision( pos, dir, callback ) )
        {
            return true;
        }

        mScene->getActiveCamera()->getMouseViewportRay(pos,dir,Vec2(offset.x,offset.y));
        if ( checkRayCollision( pos, dir, callback ) )
        {
            return true;
        }

        mScene->getActiveCamera()->getMouseViewportRay(pos,dir,Vec2(offset.x*0.5,offset.y*0.5));
        if ( checkRayCollision( pos, dir, callback ) )
        {
            return true;
        }
        
        return false;
    }

    //-----------------------------------------------------------------------
    Bool CollisionSystem::checkRayCollision(Vec3 startPos, Vec3 startDir, ICollisionCallback* callback)
    {
        if ( mRayQuery == NULL )
            return false;

        Ogre::Ray ray(Vector3(startPos.x,startPos.y,startPos.z),Vector3(startDir.x,startDir.y,startDir.z));
        mRayQuery->setRay(ray);
        mRayQuery->setQueryMask( SceneManager::ENTITY_TYPE_MASK );
        mRayQuery->setQueryTypeMask( SceneManager::ENTITY_TYPE_MASK );
        mRayQuery->setCallback( callback );

        RaySceneQueryResult& queryOgreRes = mRayQuery->execute();

        if ( queryOgreRes.size() == 0 )
            return false;

        ICollisionHit physCollision;
        Ogre::vector<RaySceneQueryResultEntry>::type::iterator iter = queryOgreRes.begin();
        Ogre::vector<RaySceneQueryResultEntry>::type::iterator iter_end = queryOgreRes.end();
        ISceneObject* sceneObj = NULL;
        MovableObject* movableObject = NULL;
        for ( ;iter!=iter_end; iter++ )
        {
            RaySceneQueryResultEntry& queryResult = (*iter);
            movableObject = queryResult.movable;
            if ( movableObject  )
            {
                if ( movableObject->getUserAny().isEmpty()==false ) 
                {
                    sceneObj = any_cast<ISceneObject*>( movableObject->getUserAny() ) ;
                
                    if ( sceneObj )
                    {
                        physCollision.pos           = MGEngineUtility::toVec3( ray.getPoint( queryResult.distance ) );
                        physCollision.sceneObject   = sceneObj;
                        callback->hit( physCollision );
                    }
                }
            }
        }
		
		if( callback->isEmpty() )
		{
			return false;
		}

        return true;
    }   

    //-----------------------------------------------------------------------
    Bool CollisionSystem::checkLineCollision(Vec3 startPos, Vec3 endPos, ICollisionCallback* callback)
    {
        if ( mRayQuery == NULL )
            return false;
        
        Vector3 rayDir = MGEngineUtility::toVec3(  endPos - startPos );
        Flt linedLength = rayDir.length();
        Ogre::Ray ray(MGEngineUtility::toVec3(startPos),rayDir);

        mRayQuery->setRay(ray);
        mRayQuery->setRay(ray);
        mRayQuery->setQueryMask( SceneManager::ENTITY_TYPE_MASK );
        mRayQuery->setQueryTypeMask( SceneManager::ENTITY_TYPE_MASK );
        mRayQuery->setCallback( callback );

        RaySceneQueryResult& queryOgreRes = mRayQuery->execute();

        if ( queryOgreRes.size() == 0 )
            return false;
        
        ICollisionHit physCollision;
        Ogre::vector<RaySceneQueryResultEntry>::type::iterator iter = queryOgreRes.begin();
        Ogre::vector<RaySceneQueryResultEntry>::type::iterator iter_end = queryOgreRes.end();
        ISceneObject* sceneObj = NULL;
        MovableObject* movableObject = NULL;
        for ( ;iter!=iter_end; iter++ )
        {
            RaySceneQueryResultEntry& queryResult = (*iter);
            
            // 如果超过线段长度则退出
            if ( queryResult.distance > linedLength )
                break;

            movableObject = queryResult.movable;
            if ( movableObject )
            {
                sceneObj = any_cast<ISceneObject*>( movableObject->getUserAny() ) ;

                if ( sceneObj )
                {
                    physCollision.pos           = MGEngineUtility::toVec3( ray.getPoint( queryResult.distance ) );
                    physCollision.sceneObject   = sceneObj;
                    callback->hit( physCollision );
                }
            }
        }

        if( callback->isEmpty() )
        {
            return false;
        }

        return true;
    }

    //-----------------------------------------------------------------------
    Bool CollisionSystem::checkRectCollision(MG::RectF rect, ISceneObject* obj, ICollisionCallback* callback)
    {
        ////////////////////////////////////////////

        if ( obj->getSceneNode()->getVisible() == false )
            return false;
 
        if( callback->isAllow(obj) == false )
            return false;

        ////////////////////////////////////////////

        Vec3 pos;
        obj->getSceneNode()->getPosition(pos);

        ////////////////////////////////////////////

		//MG引擎的坐标系统是：x向右为正，z向屏幕外为正
        //if(pos.z  >= rect.top)
		if(pos.z  <= rect.top)
        {
            return false;
        }
        else 
        //if(pos.z  <= rect.bottom)
		if(pos.z  >= rect.bottom)
        {
            return false;
        }
        else 
        if(pos.x  <= rect.left)
        {
            return false;
        }
        else 
        if(pos.x  >= rect.right)
        {
            return false;
        }
        
        ////////////////////////////////////////////

        ICollisionHit physCollision;
        physCollision.pos = pos;
        physCollision.sceneObject = obj;

        callback->hit( physCollision );

        return true;
    }


    //-----------------------------------------------------------------------
    Bool CollisionSystem::checkRectCollision(MG::RectF rect, ICollisionCallback* callback)
    {
        {
            std::map<String, Entity*>::iterator iter = mScene->mEntitys.begin();
            for ( ; iter != mScene->mEntitys.end(); iter++ )
            {
                checkRectCollision( rect, iter->second, callback);
            }
        }

		{
			TreeManager* treeMgr = mScene->getTreeManager();
			std::map<String, Tree*> trees = treeMgr->getAllTrees();
			std::map<String, Tree*>::iterator iter = trees.begin();
			for ( ; iter != trees.end(); iter++ )
			{
				checkRectCollision( rect, iter->second, callback);
			}
		}

		{
			TreeManager* treeMgr = mScene->getTreeManager();
			std::map<String, Grass*> grasses = treeMgr->getAllGrasses();
			std::map<String, Grass*>::iterator iter = grasses.begin();
			for ( ; iter != grasses.end(); iter++ )
			{
				checkRectCollision( rect, iter->second, callback);
			}
		}

        {
            std::map<String, EntityGroup*>::iterator iter = mScene->mEntityGroup.begin();
            for ( ; iter != mScene->mEntityGroup.end(); iter++ )
            {
                EntityGroup::EntityGroupInstancesMap::iterator kter = iter->second->mEntityGroupInstanceMap.begin();
                for (;kter!=iter->second->mEntityGroupInstanceMap.end();kter++)
                {
                    EntityGroup::EntityGroupInstancesList& list = kter->second;
                    for ( UInt i=0;i<list.size();i++)
                    {
                        EntityGroupInstance* instance = list[i];
                        checkRectCollision( rect, instance, callback);
                    }
                }
            }
        }

		if( callback->isEmpty() )
		{
			return false;
		}

		return true;
    }

    //-----------------------------------------------------------------------
    Bool CollisionSystem::checkCircleCollision(Vec3 center, Flt radius, ISceneObject* obj, ICollisionCallback* callback)
    {
        ////////////////////////////////////////////

        if ( obj->getSceneNode()->getVisible() == false )
            return false;

        if( callback->isAllow(obj) == false )
            return false;

        ////////////////////////////////////////////

        Vec3 pos;
        obj->getSceneNode()->getPosition(pos);

        ////////////////////////////////////////////

        Vec3 dist = pos - center;

        Flt xDist = abs( dist.x );
        Flt zDist = abs( dist.z );

        if ( xDist > radius )
            return false;
        if ( zDist > radius )
            return false;

        ////////////////////////////////////////////

		dist.y = 0;
		Flt disLen = dist.length();

        if ( disLen > radius )
            return false;

        ////////////////////////////////////////////

        ICollisionHit physCollision;
        physCollision.pos = pos;
        physCollision.sceneObject = obj;

        callback->hit( physCollision );

        return true;
    }

    //-----------------------------------------------------------------------
    Bool CollisionSystem::checkCircleCollision(Vec3 center, Flt radius, ICollisionCallback* callback)
    {
        {
            std::map<String, Entity*>::iterator iter = mScene->mEntitys.begin();
            for ( ; iter != mScene->mEntitys.end(); iter++ )
            {
                checkCircleCollision( center, radius, iter->second, callback);
            }
        }

		{
			TreeManager* treeMgr = mScene->getTreeManager();
			std::map<String, Tree*> trees = treeMgr->getAllTrees();
			std::map<String, Tree*>::iterator iter = trees.begin();
			for ( ; iter != trees.end(); iter++ )
			{
				checkCircleCollision( center, radius, iter->second, callback);
			}
		}

		{
			TreeManager* treeMgr = mScene->getTreeManager();
			std::map<String, Grass*> grasses = treeMgr->getAllGrasses();
			std::map<String, Grass*>::iterator iter = grasses.begin();
			for ( ; iter != grasses.end(); iter++ )
			{
				checkCircleCollision( center, radius, iter->second, callback);
			}
		}

        {
            std::map<String, EntityGroup*>::iterator iter = mScene->mEntityGroup.begin();
            for ( ; iter != mScene->mEntityGroup.end(); iter++ )
            {
                EntityGroup::EntityGroupInstancesMap::iterator kter = iter->second->mEntityGroupInstanceMap.begin();
                for (;kter!=iter->second->mEntityGroupInstanceMap.end();kter++)
                {
                    EntityGroup::EntityGroupInstancesList& list = kter->second;
                    for ( UInt i=0;i<list.size();i++)
                    {
                        EntityGroupInstance* instance = list[i];
                        checkCircleCollision( center, radius, instance, callback);
                    }
                }
            }
        }

        if( callback->isEmpty() )
        {
            return false;
        }

        return true;
	}

    //-----------------------------------------------------------------------
    Int CollisionSystem::getMouseRayIntersection(Vec3& intersectPos,Bool isPrecise)
    {
        Int result = 0;

        Vec3 pos,dir;
        mScene->getActiveCamera()->getMouseViewportRay(pos,dir);
        result = getRayIntersection(pos, dir, intersectPos,isPrecise );

        return result;
    }

    //-----------------------------------------------------------------------
    Int CollisionSystem::getRayIntersection(Vec3& pos, Vec3& dir, Vec3& intersectPos,Bool isPrecise)
    {
        ////////////////////////////////////////////////////

        Vec3 terrainPos;
        Bool hasTerrain = mScene->getTerrainManager()->getRayIntersection( pos, dir, terrainPos, isPrecise );

        ////////////////////////////////////////////////////

        Ogre::Ray ray(Vector3(pos.x,pos.y,pos.z),Vector3(dir.x,dir.y,dir.z));

        ////////////////////////////////////////////////////

        Plane zeroPlane;
        zeroPlane = Plane( Vector3(0,1,0), Vector3( 0, 0, 0) );

        std::pair< bool, Real > intersectResult = ray.intersects(zeroPlane);

        if ( intersectResult.first == false )
        {
            return 0;
        }
        Vector3  zeroIntersectPos   = ray.getPoint( intersectResult.second );	
        Vec2  zeroIntersect2DPos    = Vec2( zeroIntersectPos.x, zeroIntersectPos.z ) ;
        Flt checkRadius = 10;

        ////////////////////////////////////////////////////

        Vec3 meshPos;
        Bool hasMesh = false;

        std::list<CollisionObject*>::iterator iter = mCollisionObjectList.begin();
        CollisionObject* collObj = NULL;
        for ( ;iter != mCollisionObjectList.end(); iter++ )
        {
            collObj = *iter;

            if ( collObj->isIntersect( zeroIntersect2DPos, checkRadius ) )
            {
                if ( collObj->getRayIntersection(pos,dir,meshPos) )
                {
                    hasMesh = true;
                    break;
                }
            }
        }

        ////////////////////////////////////////////////////

        if ( hasTerrain && hasMesh )
        {
            if ( hasMesh )
            {
                intersectPos = meshPos;
            }
            else
            {
                intersectPos = terrainPos;
            }
        }else
        {
            if ( hasTerrain )
                intersectPos = terrainPos;
            if ( hasMesh )
                intersectPos = meshPos;
        }

        ////////////////////////////////////////////////////

		if ( hasMesh )
			return 2;
		if ( hasTerrain )
			return 1;

        return 0;
    }

    //-----------------------------------------------------------------------
    Int CollisionSystem::getStickHeight( Vec3 worldPos , Flt& height )
    {
        return getStickHeight( NULL, worldPos, height );
    }

    //-----------------------------------------------------------------------
    Int CollisionSystem::getStickHeight( ISceneNode* node, Flt& height )
    {
        Vec3 worldPos;
        node->getPosition( worldPos );
        return getStickHeight( node, worldPos, height );
    }

    //-----------------------------------------------------------------------
    Int CollisionSystem::getStickHeight( ISceneNode* node,Vec3 worldPos, Flt& height )
    {
        ////////////////////////////////////////////////////

        Flt terrainHeight = 0;
        Bool hasTerrain = mScene->getTerrainManager()->getStickHeight( Vec2(worldPos.x,worldPos.z), terrainHeight );

        ////////////////////////////////////////////////////

        Flt meshHeight = 0;
        Bool hasMesh = false;

        std::list<CollisionObject*>::iterator iter = mCollisionObjectList.begin();
        CollisionObject* collObj = NULL;
        for ( ;iter != mCollisionObjectList.end(); iter++ )
        {
            collObj = *iter;
            if ( node )
            {
                if ( collObj->getStickHeight(node,meshHeight) )
                {
                    hasMesh = true;
                    break;
                }
            }else
            {
                if ( collObj->getStickHeight(worldPos,meshHeight) )
                {
                    hasMesh = true;
                    break;
                }
            }
        }

        ////////////////////////////////////////////////////

        if ( hasTerrain && hasMesh )
        {
            if ( meshHeight > terrainHeight )
            {
                height = meshHeight;
            }
            else
            {
                height = terrainHeight;
            }
        }else
        {
            if ( hasTerrain )
                height = terrainHeight;
            if ( hasMesh )
                height = meshHeight;
        }

        ////////////////////////////////////////////////////


		if ( hasMesh )
			return 2;
		if ( hasTerrain )
			return 1;


		return 0;
    }

}