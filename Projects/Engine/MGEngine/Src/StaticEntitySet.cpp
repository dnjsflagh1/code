/******************************************************************************/
#include "stdafx.h"
#include "EngineMain.h"
#include "Scene.h"
#include "MGSceneNode.h"
#include "ResourceManager.h"
#include "StaticEntitySet.h"
#include "MaterialManager.h"

/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    StaticEntitySet::StaticEntitySet(U32 modelDeclID, Scene* scene)
        :mOgreEntityTemplate(NULL)
        ,mScene(scene)
        ,mModelDeclID(modelDeclID)
    {
        createEntityTemplate( modelDeclID );
    }

    //-----------------------------------------------------------------------
    StaticEntitySet::~StaticEntitySet()
    {
        destroyEntityTemplate();
        destroyAllStaticGeometry();
    }

    //-----------------------------------------------------------------------
    void StaticEntitySet::update( Flt delta )
    {
        updateMaterialDynamicParameter( delta );
    }
    
    //-----------------------------------------------------------------------
    void StaticEntitySet::createEntityTemplate( U32 modelDeclID )
    {
        ModelDeclaration*  decl = MG::ResourceManager::getSingletonPtr()->getModelDeclaration(modelDeclID);

        std::ostringstream s;
        s << "StaticEntitySet_" << modelDeclID << "_Materail";
        Str matName = s.str();
       
        mOgreEntityTemplate = MG_NEW OgreEntityWrapper(NULL,matName.c_str(),decl,mScene);
        if ( mOgreEntityTemplate )
        {
            mOgreEntityTemplate->createOgreEntity(decl,true,false);
            mOgreEntityTemplate->getSceneNode()->setVisible( false );
        }
    }

    //-----------------------------------------------------------------------
    void StaticEntitySet::applyRenderConfig()
    {
        if ( mOgreEntityTemplate )
        {
            mOgreEntityTemplate->applyRenderConfig();
        }
    }

    //-----------------------------------------------------------------------
    void StaticEntitySet::applyVisibleFlag()
    {
        if ( mOgreEntityTemplate )
        {
            std::map< Str, StaticGeometryInstance >::iterator iter = mStaticGeometryInstanceList.begin();
            for ( ;iter != mStaticGeometryInstanceList.end();iter++ )
            {
                StaticGeometry* staticGeometry = iter->second.staticGeometry;

                StaticGeometry::RegionIterator regs =  staticGeometry->getRegionIterator();
                while (regs.hasMoreElements())
                {
                    StaticGeometry::Region* reg = regs.getNext();
                    uint32 flag = mOgreEntityTemplate->getOgreEntity()->getVisibilityFlags();
                    reg->setVisibilityFlags( flag );
                    reg->setCastShadows( true );
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void StaticEntitySet::updateMaterialDynamicParameter( Flt delta )
    {
        MaterialDynamicParamsObject& dynamicObj = mOgreEntityTemplate->getMaterialDynamicParamsObject();

        //////////////////////////////////////////////////////////////////////////

        MaterialManager::getInstance().updateMaterialGroupDynamicParameter( delta, dynamicObj );

        //////////////////////////////////////////////////////////////////////////

        std::map< Str, StaticGeometryInstance >::iterator iter = mStaticGeometryInstanceList.begin();
        for ( ;iter != mStaticGeometryInstanceList.end();iter++ )
        {
            StaticGeometry* staticGeometry = iter->second.staticGeometry;

            StaticGeometry::RegionIterator regs =  staticGeometry->getRegionIterator();
            while (regs.hasMoreElements())
            {
                StaticGeometry::Region* reg = regs.getNext();
                
                Vec3 center = Vec3( reg->getCentre().x,reg->getCentre().y,reg->getCentre().z ) ;
				
				MaterialManager::getInstance().updateMaterialElementDynamicParameter( delta, dynamicObj, center );

                StaticGeometry::Region::LODIterator lods = reg->getLODIterator();

                while (lods.hasMoreElements())
                {
                    StaticGeometry::LODBucket::MaterialIterator mats = lods.getNext()->getMaterialIterator();

					Int matIndex = 0;

                    while (mats.hasMoreElements())
                    {
                        StaticGeometry::MaterialBucket::GeometryIterator geoms = mats.getNext()->getGeometryIterator();

                        while (geoms.hasMoreElements()) 
                        {
                            MaterialManager::getInstance().applyMaterialDynamicParameter( dynamicObj, geoms.getNext(), matIndex );
                        }

						matIndex++;
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void StaticEntitySet::destroyEntityTemplate()
    {
        MG_SAFE_DELETE( mOgreEntityTemplate );
    }

    //-----------------------------------------------------------------------
    StaticGeometry* StaticEntitySet::createOrRetriveStaticGeometry( Str staticGroup )
    {
        StaticGeometry* staticGeometry = NULL;
        std::map< Str, StaticGeometryInstance >::iterator iter = mStaticGeometryInstanceList.find( staticGroup );
        if ( iter != mStaticGeometryInstanceList.end() )
        {
            staticGeometry =  iter->second.staticGeometry;
        }

        if ( !staticGeometry )
        {
            std::ostringstream s;
            s << "StaticGeometry" << mModelDeclID << "_" << staticGroup;
            Str name = s.str();

            staticGeometry = mScene->getOgreSceneManager()->createStaticGeometry( name );
            StaticGeometryInstance instance;
            instance.staticGeometry = staticGeometry;
            mStaticGeometryInstanceList[ staticGroup ] = instance;

            //TODO:
            //staticGeometry->setRegionDimensions(Vector3(gridSize, 20, gridSize));
            //staticGeometry->setOrigin(Vector3(worldPos.x, 0, worldPos.y));
            //TODO 裁剪
            staticGeometry->setRegionDimensions(Vector3(10000,10000,10000));
            staticGeometry->setOrigin(Vector3(-5000, -5000, -5000));
        }

        return staticGeometry;
    }

    //-----------------------------------------------------------------------
    void StaticEntitySet::destroyAllStaticGeometry()
    {
        std::map< Str, StaticGeometryInstance >::iterator iter = mStaticGeometryInstanceList.begin();
        for ( ;iter != mStaticGeometryInstanceList.end();iter++ )
        {
            mScene->getOgreSceneManager()->destroyStaticGeometry(iter->second.staticGeometry);
        }
        mStaticGeometryInstanceList.clear();
    }

    //-----------------------------------------------------------------------
    void StaticEntitySet::destroyAllStaticGeometryBackupData()
    {
        std::map< Str, StaticGeometryInstance >::iterator iter = mStaticGeometryInstanceList.begin();
        for ( ;iter != mStaticGeometryInstanceList.end();iter++ )
        {
            StaticGeometry* staticGeometry = iter->second.staticGeometry;

            StaticGeometry::RegionIterator regs =  staticGeometry->getRegionIterator();
            while (regs.hasMoreElements())
            {
                StaticGeometry::Region* reg = regs.getNext();

                StaticGeometry::Region::LODIterator lods = reg->getLODIterator();

                while (lods.hasMoreElements())
                {
                    StaticGeometry::LODBucket::MaterialIterator mats = lods.getNext()->getMaterialIterator();

                    while (mats.hasMoreElements())
                    {
                        StaticGeometry::MaterialBucket::GeometryIterator geoms = mats.getNext()->getGeometryIterator();

                        while (geoms.hasMoreElements()) 
                        {
                            Renderable* renderable = geoms.getNext();
                            if ( renderable )
                            {
                                RenderOperation rp;
                                renderable->getRenderOperation( rp );
                                if ( rp.vertexData && rp.vertexData->vertexBufferBinding )
                                {
                                    HardwareVertexBufferSharedPtr destPosbuf = rp.vertexData->vertexBufferBinding->getBuffer( 0 );

                                    if ( destPosbuf.isNull() == false )
                                    {
                                        destPosbuf->freeSystemMemoryBuffer();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void StaticEntitySet::reset()
    {
        std::map< Str, StaticGeometryInstance >::iterator iter = mStaticGeometryInstanceList.begin();
        for ( ;iter != mStaticGeometryInstanceList.end();iter++ )
        {
            StaticGeometry* staticGeometry = iter->second.staticGeometry;

            StaticGeometry::RegionIterator regs =  staticGeometry->getRegionIterator();
            while (regs.hasMoreElements())
            {
                StaticGeometry::Region* reg = regs.getNext();

                StaticGeometry::Region::LODIterator lods = reg->getLODIterator();

                while (lods.hasMoreElements())
                {
                    StaticGeometry::LODBucket::MaterialIterator mats = lods.getNext()->getMaterialIterator();

                    while (mats.hasMoreElements())
                    {
                        StaticGeometry::MaterialBucket::GeometryIterator geoms = mats.getNext()->getGeometryIterator();

                        while (geoms.hasMoreElements()) 
                        {
                            StaticGeometry::GeometryBucket* renderable = geoms.getNext();
                            if ( renderable )
                            {
                                RenderOperation rp;
                                renderable->getRenderOperation( rp );
                                if ( rp.vertexData && rp.vertexData->vertexBufferBinding )
                                {
                                    HardwareVertexBufferSharedPtr destPosbuf = rp.vertexData->vertexBufferBinding->getBuffer( 0 );

                                    if ( destPosbuf.isNull() == false )
                                    {
                                        destPosbuf->createSystemMemoryBuffer();

                                        renderable->build( false );

                                        destPosbuf->freeSystemMemoryBuffer();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    //-----------------------------------------------------------------------
    void StaticEntitySet::addStaticEntity(Vec3& pos, Qua& orientation, Vec3& scale, Bool isRandom, 
        Str staticGroup, Bool isReset)
    {
        StaticGeometry* staticGeometry  = createOrRetriveStaticGeometry( staticGroup );

        if ( staticGeometry && mOgreEntityTemplate && mOgreEntityTemplate->getOgreEntity() )
        {

           Vector3 newPos       = Vector3(pos.x,pos.y,pos.z);
           Quaternion newQua    = Quaternion(orientation.w,orientation.x,orientation.y,orientation.z);
           Vector3 newScale     = Vector3(scale.x,scale.y,scale.z);

            //if ( isRandom )
            //{
            //    //随机位置
            //    //mBatchEntityMapGridSize 0.2
            //    Flt offset_x = Ogre::Math::UnitRandom() * mBatchEntityMapGridSize;
            //    Flt offset_y = Ogre::Math::UnitRandom() * mBatchEntityMapGridSize;

            //    oPos.x += offset_x;
            //    oPos.y += offset_y;

            //    //随机朝向
            //    Radian radian(Ogre::Math::UnitRandom() * Ogre::Math::TWO_PI);

            //    Quaternion q;
            //    q.FromAngleAxis(radian,Vector3::UNIT_Y);
            //    ori = ori * q;

            //    //随机大小
            //    Flt scale = Ogre::Math::RangeRandom( 0.5f, 1.5f );
            //    oScale *= scale;
            //}

            staticGeometry->addEntity(mOgreEntityTemplate->getOgreEntity(),newPos,newQua,newScale);
            pos = Vec3(newPos.x,newPos.y,newPos.z);
            orientation = Qua(newQua.w,newQua.x,newQua.y,newQua.z);
            scale = Vec3(newScale.x,newScale.y,newScale.z);

            if ( isReset )
                staticGeometry->reset();
        }

    }

    //-----------------------------------------------------------------------
    void StaticEntitySet::buildStaticEntity()
    {
        std::map< Str, StaticGeometryInstance >::iterator iter = mStaticGeometryInstanceList.begin();
        for ( ;iter != mStaticGeometryInstanceList.end();iter++ )
        {
            StaticGeometry* staticGeometry  = iter->second.staticGeometry;

            staticGeometry->build();

            applyRenderConfig();

            applyVisibleFlag();
        }

        if ( EngineMain::getInstance().getMode() != EM_EDITOR )
        {
            destroyAllStaticGeometryBackupData();
        }
    }

    //-----------------------------------------------------------------------
    OgreEntityWrapper*  StaticEntitySet::getModelObject()
    {
        return mOgreEntityTemplate;
    }


}