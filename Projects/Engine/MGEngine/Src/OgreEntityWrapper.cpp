/******************************************************************************/
#include "stdafx.h"
#include "OgreEntityWrapper.h"
#include "EngineMain.h"
#include "Scene.h"
#include "ISceneObject.h"
#include "IEntityAccessory.h"
#include "ResourceManager.h"
#include "AnimationController.h"
#include "MaterialManager.h"
#include "Display.h"
/******************************************************************************/

namespace MG
{

    #define MGSCENENODE_POOL_CATEGORY 3104

    //-----------------------------------------------------------------------
    OgreEntityWrapper::OgreEntityWrapper(ISceneObject* sceneObject,CChar* entityName, ModelDeclaration* modelDeclaration, Scene* scene)
        :mScene(scene)
        ,mSceneObject(sceneObject)
        ,mOgreEntity(NULL)
        ,mSceneNode(NULL)
        ,mModelDeclarationName(modelDeclaration->name)
		,mModelDeclarationID(modelDeclaration->id)
        ,mUseHightLightDirty(true)
        ,mHightLightDirty(false)
        ,mIsBatch(false)
        ,mShiness(1)
        ,mEmissive(0.0f,0.0f,0.0f)
		,mPatherRadius(0.0f)
        ,mName(entityName)
        ,mShadowCasterType(SCT_STATIC)
        ,mDynamicShadowReceiveEnable(false)
        ,mStaticShadowReceiveEnable(false)
        ,mReflectEnable(false)
        ,mRefractEnable(false)
        ,mMaterialChangeDirty(false)
    {
        DYNAMIC_ASSERT(modelDeclaration!=NULL);
        DYNAMIC_ASSERT(mScene!=NULL);
        
        mMaterialMGGroupName = modelDeclaration->path + "\\" + modelDeclaration->materialFileName;
		mResourceGroupName = modelDeclaration->path;

		mPatherRadius = modelDeclaration->patherRadius;
    }

    //-----------------------------------------------------------------------
    OgreEntityWrapper::OgreEntityWrapper(ISceneObject* sceneObject,CChar* entityName, CChar* groupName, CChar* modelName, Scene* scene)
        :mScene(scene)
        ,mSceneObject(sceneObject)
        ,mOgreEntity(NULL)
        ,mSceneNode(NULL)
        ,mModelDeclarationName("")
		,mModelDeclarationID()
        ,mIsBatch(false)
        ,mEmissive(0,0,0)
		,mPatherRadius(0.0f)
        ,mName(entityName)
		,mDynamicShadowReceiveEnable(false)
		,mStaticShadowReceiveEnable(false)
		,mMaterialChangeDirty(false)
		,mShadowCasterType(SCT_NULL)
    {
        DYNAMIC_ASSERT(mScene!=NULL);

        mResourceGroupName = groupName;
    }

    //-----------------------------------------------------------------------
    OgreEntityWrapper::~OgreEntityWrapper()
    {
        destroyOgreEntity();
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::createOgreEntity(ModelDeclaration* modelDecl ,Bool isCreateNode, Bool isBatch)
    {
        createOgreEntity( modelDecl->meshFileName, isCreateNode, isBatch );
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::createOgreEntity(Str modelName,Bool isCreateNode,Bool isBatch)
    {
        // 设置是否是批量处理
        mIsBatch = isBatch;

        //创建实体对象
        if (mResourceGroupName.empty())
            mOgreEntity = mScene->getOgreSceneManager()->createEntity(mName,modelName);
        else
            mOgreEntity = mScene->getOgreSceneManager()->createEntity(mName,modelName,mResourceGroupName);

        DYNAMIC_ASSERT(mOgreEntity!=NULL);

        if ( mOgreEntity )
        {
            //设置材质材质
            applyMaterial();

            // 设置可见组
            applyVisibleFlag();

            // 设置投射阴影为false
            mOgreEntity->setCastShadows( false );

            if ( mSceneObject )
            {
                //设置绑定实体对象的管理者
                mOgreEntity->setUserAny( Any((ISceneObject*)mSceneObject) );
                ////设置查询标志位
                mOgreEntity->setQueryFlags(Scene::getQueryMask(mSceneObject->getType()));
            }

            if ( isCreateNode )
            {
                //创建实体节点
                //mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);
                mSceneNode = MG_POOL_NEW_T(MGSceneNode, MGSCENENODE_POOL_CATEGORY)(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

                //绑定实体
                mSceneNode->getOgreSceneNode()->attachObject( mOgreEntity );
            }


            // TODO:
			// add by xyd
			// LOD临时全部关闭
            {
                ModelDeclaration* model_decl = ResourceManager::getSingleton().getModelDeclaration( mModelDeclarationID, false );
                {
                    MeshPtr pMesh = mOgreEntity->getMesh();
                    if ( !pMesh.isNull() )
                        pMesh->removeLodLevels();
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::destroyOgreEntity()
    {
        //销毁实体对象
        if ( mOgreEntity )
        {
            mScene->getOgreSceneManager()->destroyEntity(mOgreEntity);
            mOgreEntity = NULL;
        }
        //销毁实体节点
        //MG_SAFE_DELETE( mSceneNode );
        MG_POOL_DELETE_T(mSceneNode, MGSceneNode, MGSCENENODE_POOL_CATEGORY);
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::destroyOgreEntityBackupData()
    {
        if ( mOgreEntity )
        {
            for ( U32 i = 0 ; i < mOgreEntity->getNumSubEntities(); i++ )
            {
                // 得到子模型
                Ogre::SubEntity* sub_entity = mOgreEntity->getSubEntity(i);
                if ( sub_entity )
                {
                    HardwareVertexBufferSharedPtr destPosbuf = sub_entity->getVertexDataForBinding()->vertexBufferBinding->getBuffer( 0 );

                    if ( destPosbuf.isNull() == false )
                    {
                        destPosbuf->freeSystemMemoryBuffer();
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    MGSceneNode* OgreEntityWrapper::getSceneNode()
    {
        return mSceneNode;
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::applyRenderConfig()
    {
        applyMaterial();
    }

    //-----------------------------------------------------------------------
    Vec3 OgreEntityWrapper::getBonePosition(CChar* boneName)
    {
        Ogre::Vector3 pos = Vector3(0,0,0);

        if (mOgreEntity)
        {
            Ogre::SkeletonInstance * skeleton = mOgreEntity->getSkeleton();
            if (skeleton)
            {
                if ( skeleton->hasBone(boneName) )
                {
                    Ogre::Bone* bone = skeleton->getBone(boneName);
                    if (bone)
                    {
                        pos = bone->_getDerivedPosition();
                    }
                }
            }
        }

        return Vec3(pos.x,pos.y,pos.z);
    }

	//-----------------------------------------------------------------------
	Qua OgreEntityWrapper::getBoneOrientation(CChar* boneName)
	{
		Ogre::Quaternion qua;

		if (mOgreEntity)
		{
			Ogre::SkeletonInstance * skeleton = mOgreEntity->getSkeleton();
			if (skeleton)
			{
				if ( skeleton->hasBone(boneName) )
				{
					Ogre::Bone* bone = skeleton->getBone(boneName);
					if (bone)
					{
						qua = bone->_getDerivedOrientation();
					}
				}
			}
		}

		return Qua(qua.w,qua.x,qua.y,qua.z);
	}
	//-----------------------------------------------------------------------
	Vec3 OgreEntityWrapper::getCenterPosition(Flt center, Bool isLocal)
	{
		Vec3 pos = Vec3(0,0,0);

		if ( mSceneNode )
		{
			if ( !isLocal )
			{
				mSceneNode->getPosition(pos);
			}
			pos.y += center * getBoundingBoxSize().y;
		}

		return pos;
	}
	//-----------------------------------------------------------------------
	Qua OgreEntityWrapper::getBoneWorldOrientation(CChar* boneName)
	{
		Qua boneQua = getBoneOrientation(boneName);

		if (mSceneNode)
		{
			Qua parentQua;
			mSceneNode->getOrientation(parentQua);

			boneQua = parentQua * boneQua;
		}

		return boneQua;
	}

    //-----------------------------------------------------------------------
    Vec3 OgreEntityWrapper::getBoneWorldPosition(CChar* boneName)
    {
		Vec3 bonePosition = getBonePosition(boneName);

		if (mSceneNode)
		{
			Qua parentQua;
			Vec3 parentPosition;

			mSceneNode->getPosition(parentPosition);
			mSceneNode->getOrientation(parentQua);

			bonePosition = parentPosition + parentQua * bonePosition;
		}

		return bonePosition;
    }

    //-----------------------------------------------------------------------
    Flt OgreEntityWrapper::getHeight()
    {
        return mOgreEntity->getBoundingBox().getMaximum().y - mOgreEntity->getBoundingBox().getMinimum().y;
    }

    //-----------------------------------------------------------------------
    Flt OgreEntityWrapper::getWidth()
    {
        return mOgreEntity->getBoundingBox().getHalfSize().length();
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::update( Flt delta )
    {
        if ( mSceneNode )
        {
            mSceneNode->update( delta ); 
        }

        if ( mMaterialChangeDirty )
        {
            applyMaterial();
            mMaterialChangeDirty = false;
        }

        updateHightLight();
    }   

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::applyVisibleFlag()
    {
        if ( mOgreEntity )
        {
            UInt visibleFlags = SOV_NULL;

            if ( mShadowCasterType == SCT_NULL )
            {
                visibleFlags = SOV_ENTITY;
            }else
            if ( mShadowCasterType == SCT_STATIC )
            {
                visibleFlags = SOV_ENTITY | SOV_STATIC_SHADOW ;
            }else
            if ( mShadowCasterType == SCT_DYNAMIC )
            {
                visibleFlags = SOV_ENTITY |  SOV_DYNAMIC_SHADOW ;
            }

            if ( getReflectEnable() )
            {
                visibleFlags |= SOV_REFLECT;
            }

            if ( getRefractEnable() )
            {
                visibleFlags |= SOV_REFRACT;
            }

            mOgreEntity->setVisibilityFlags( visibleFlags );
        }
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::applyMaterial()
    {
        if ( !mOgreEntity )
            return;

        /////////////////////////////////////////////////////////////////////////////////////////

        mMaterialDynamicParams.clearDynamicParams();
       
        mMaterialDynamicParams.params.isBatch                   = mIsBatch;

        mMaterialDynamicParams.params.isCasterShadow            = mShadowCasterType != SCT_NULL;
        mMaterialDynamicParams.params.isDynamiShadowcReceive    = mDynamicShadowReceiveEnable;
        mMaterialDynamicParams.params.isStaticShadowReceive     = mStaticShadowReceiveEnable;

        mMaterialDynamicParams.params.hasSkeleton       = mOgreEntity->hasSkeleton();
        mMaterialDynamicParams.params.suffixName        = mOgreEntity->getName();
        mMaterialDynamicParams.params.shiness           = mShiness;
        mMaterialDynamicParams.params.emissive          = mEmissive;

        Vector3 size = mOgreEntity->getBoundingBox().getSize();
        mMaterialDynamicParams.params.boundingSize.x = size.x;
        mMaterialDynamicParams.params.boundingSize.y = size.y;
        mMaterialDynamicParams.params.boundingSize.z = size.z;
		
		//mMaterialDynamicParams.params.isOpenGlow = true;
        /////////////////////////////////////////////////////////////////////////////////////////

        for ( U32 i = 0 ; i < mOgreEntity->getNumSubEntities(); i++ )
        {
            MaterialDeclaration* mat_decls = MaterialManager::getInstance().getMaterialDeclaration(mMaterialMGGroupName, i);

			if ( !mat_decls )
				continue;

            // 增加动态参数
            mMaterialDynamicParams.addDynamicParams( mat_decls, i );

            // 创建或取回材质
            MaterialPtr applyMat = MaterialManager::getInstance().createOrRetriveMaterial( mScene, mat_decls, mMaterialDynamicParams.params );

            // 得到子模型
            Ogre::SubEntity* sub_entity = mOgreEntity->getSubEntity(i);
            if ( sub_entity )
            {
                // 设置材质
                sub_entity->setMaterial(applyMat);
                // 响应动态参数
                MaterialManager::getInstance().applyMaterialDynamicParameter( mMaterialDynamicParams, sub_entity, i );
            }
        }

        //////////////////////////////////////////////////////////////////////////
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::setEmissive(Color color, Bool toAccessory )
    {
        mEmissive = Ogre::ColourValue(color.r,color.g,color.b,color.a);
        UInt num = mOgreEntity->getNumSubEntities();
        for( UInt i=0; i<num ; i++ )
        {
            MaterialPtr mat = mOgreEntity->getSubEntity(i)->getMaterial();
            if (mat.isNull()==false)
            {
                mat->setSelfIllumination(mEmissive);
            }
        }

		if ( toAccessory && 
			mSceneObject && 
			mSceneObject->getType() == SOT_ENTITY  )
		{
			IEntity* entity = dynamic_cast<IEntity*>(mSceneObject);
			if ( entity )
			{
				IEntityAccessoryCollection* entityAccessoryCollection = entity->getEntityAccessoryCollection();
				if ( entityAccessoryCollection )
				{
					Int count = entityAccessoryCollection->getAttachObjectCount();
					for ( int index = 0; index < count; index++ )
					{
						IEntityAccessory* entityAccessory = entityAccessoryCollection->getAttachObject(index);
						if ( entityAccessory && entityAccessory->sceneObject )
						{
							if ( entityAccessory->sceneObject->getType() == SOT_ENTITY )
							{
								IEntity* sub_entity = dynamic_cast<IEntity*>(entityAccessory->sceneObject);
								IModelObject* model = NULL;
								if ( sub_entity && (model = sub_entity->getModelObject()) )
								{
									model->setEmissive( color );
								}
							}
						}
					}
				}

			}
		}
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::setHightLight(Flt shine, Bool useDirty)
    {
        mUseHightLightDirty = useDirty;
        mHightLightDirty = true;
        
        //mShiness = shine;

        applyHightLight( shine );
    }
    //-----------------------------------------------------------------------
    void OgreEntityWrapper::updateHightLight()
    {
        if ( mUseHightLightDirty )
        {
            if ( mHightLightDirty )
            {
                applyHightLight( 1 );
                mHightLightDirty = false;
            }
        }
    }
    //-----------------------------------------------------------------------
    void OgreEntityWrapper::applyHightLight(Flt shine)
    {
        UInt num = mOgreEntity->getNumSubEntities();
        for( UInt i=0; i<num ; i++ )
        {
            MaterialPtr mat = mOgreEntity->getSubEntity(i)->getMaterial();
            if (mat.isNull()==false)
            {
                mat->setShininess(shine);
            }
        }
    }
	//-----------------------------------------------------------------------
	Vec3 OgreEntityWrapper::getBoundingBoxSize()
	{
		Vec3 result;
		Ogre::Entity* ogre_entity = getOgreEntity();

		if ( ogre_entity )
		{
			Vector3 size = ogre_entity->getBoundingBox().getSize();
			result.x = size.x;
			result.y = size.y;
			result.z = size.z;
		}

		return result;
	}

	//-----------------------------------------------------------------------
	Flt OgreEntityWrapper::getPatherRadius()
	{
		return mPatherRadius;
	}

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::setShadowCastType(ShadowCasterType type)
    {
		if ( mShadowCasterType != type )
			mMaterialChangeDirty = true;
        mShadowCasterType = type;
        if ( mOgreEntity )
        {
            mOgreEntity->setCastShadows( mShadowCasterType != SCT_NULL );
        }
        applyVisibleFlag();
    }

    //-----------------------------------------------------------------------
    ShadowCasterType OgreEntityWrapper::getShadowCastType()
    {
        return mShadowCasterType;
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::setDynamicShadowReceiveEnable(Bool enable)
    {
		if ( mDynamicShadowReceiveEnable != enable )
			mMaterialChangeDirty = true;
        mDynamicShadowReceiveEnable = enable;
    }

    //-----------------------------------------------------------------------
    Bool OgreEntityWrapper::getDynamicShadowReceiveEnable()
    {
        return mDynamicShadowReceiveEnable;
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::setStaticShadowReceiveEnable(Bool enable)
    {
		if ( mDynamicShadowReceiveEnable != enable )
			mMaterialChangeDirty = true;
        mStaticShadowReceiveEnable = enable;
    }

    //-----------------------------------------------------------------------
    Bool OgreEntityWrapper::getStaticShadowReceiveEnable()
    {
        return mStaticShadowReceiveEnable;
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::setReflectEnable(Bool enable)
    {
        mReflectEnable = enable;
        applyVisibleFlag();
    }

    //-----------------------------------------------------------------------
    Bool OgreEntityWrapper::getReflectEnable()
    {
        return mReflectEnable;
    }

    //-----------------------------------------------------------------------
    void OgreEntityWrapper::setRefractEnable(Bool enable)
    {
        mRefractEnable = enable;
        applyVisibleFlag();
    }

    //-----------------------------------------------------------------------
    Bool OgreEntityWrapper::getRefractEnable()
    {
        return mRefractEnable;
    }


  
}

