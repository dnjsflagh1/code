/******************************************************************************/
#include "stdafx.h"
#include "ResourceManager.h"
#include "EngineMain.h"
/******************************************************************************/

namespace MG
{
    SINGLETON_DEFINE( MG::ResourceManager )
    //-----------------------------------------------------------------------
    ResourceManager::ResourceManager()
    {
        //mModelXmlDoc = MG_NEW XMLDocument;
        mTerrainTextureXmlDoc = MG_NEW tinyxml2::XMLDocument;
    }
    //-----------------------------------------------------------------------
    ResourceManager::~ResourceManager()
    {
        unloadAll();
    }
	//-----------------------------------------------------------------------
	void ResourceManager::unloadAll()
	{
		EffectResourceConfig::getInstance().unLoad();
		ActionResourceConfig::getInstance().unLoad();

		mTerrainTextureXmlDoc->DeleteChildren();
		MG_SAFE_DELETE( mTerrainTextureXmlDoc );	
	}
    //-----------------------------------------------------------------------
    /*void ResourceManager::loadDeclarationsXML( CChar* filename )
    {*/
        //mModelXmlDoc->Clear();
        //
        //if ( mModelXmlDoc->LoadFile(filename) == false )
        //{
        //    MG_MESSAGE("ResourceManager::loadModelDeclarations ERROR");
        //    DYNAMIC_ASSERT(false);
        //    return;
        //}

        //XMLElement* rootElm = mModelXmlDoc->RootElement();
        //if (rootElm)
        //{
        //    //create component
        //    {
        //        XMLNode* parentNode       = rootElm;
        //        XMLNode* currNode         = parentNode->FirstChild();
        //        XMLNode* firstSiblingNode = currNode;
        //        XMLNode* nextNode         = NULL;
        //        XMLElement* element        = NULL;

        //        Str8 name;
        //        Str8 path;
        //        Str8 modelFileName;
        //        Str8 thumbnailsFileName;
        //        Str8 describe;
        //        Flt width;
        //        Flt height;
        //        
        //        while( currNode )
        //        {
        //            //TODO:
        //            Str formatType = XML_GET_VALUE(currNode);
        //            if (formatType == "Model")
        //            {
        //                element = currNode->ToElement();

        //                XmlHelper::getAttribute( element, name, "name");
        //                XmlHelper::getAttribute( element, path, "path");
        //                XmlHelper::getAttribute( element, modelFileName, "modelFileName");
        //                XmlHelper::getAttribute( element, thumbnailsFileName, "thumbnailsFileName");
        //                XmlHelper::getAttribute( element, describe, "describe");
        //                XmlHelper::getAttribute( element, width, "width");
        //                XmlHelper::getAttribute( element, height, "height");

        //                ModelDeclaration& decl = mModelDecls[name];
        //                decl.name = name;
        //                decl.path = path;
        //                decl.modelFileName = modelFileName;
        //                decl.thumbnailsFileName = thumbnailsFileName;
        //                decl.describe = describe;
        //                decl.width = width;
        //                decl.height = height;
        //            }

        //            //@ tree
        //            nextNode = currNode->FirstChild();
        //            if (!nextNode)
        //            {
        //                firstSiblingNode = currNode->Parent()->FirstChild();
        //                nextNode         = currNode->NextSibling();
        //                if (nextNode&&nextNode==firstSiblingNode)
        //                    nextNode = NULL;
        //            }
        //            if (!nextNode)
        //            {
        //                nextNode = currNode->Parent();
        //                if (nextNode == parentNode)
        //                    break;

        //                firstSiblingNode = nextNode->Parent()->FirstChild();
        //                nextNode         = nextNode->NextSibling();
        //                if (nextNode&&nextNode==firstSiblingNode)
        //                    nextNode = NULL;
        //            }
        //            currNode = nextNode;
        //        }
        //    }
        //}
    //}

    //-----------------------------------------------------------------------
    void ResourceManager::loadDeclarations( const EngineInitConfig& config )
    {
		mMaterialDeclsGroups.clear();

		EffectResourceConfig::getInstance().unLoad();
		ActionResourceConfig::getInstance().unLoad();

		ModelResourceConfig::getInstance().load(config.modelDeclFileName);
		EffectResourceConfig::getInstance().load(config.effectDeclFileName, config.waterEffectDeclFileName,
												 config.grassEffectDeclFileName, config.effectComponentDeclFileName);
		EntityAccessoryResourceConfig::getInstance().load(config.accessoryDeclFileName);
    }
    
    //-----------------------------------------------------------------------
	void ResourceManager::unLoadActionDecls()
	{
		for ( ActionDeclsInfos::iterator iter_infos = mActionDeclInfos.begin(); iter_infos != mActionDeclInfos.end(); iter_infos++ )
		{
			ActionDecls& _decls = iter_infos->second.decls;

			for ( ActionDecls::iterator iter_decls = _decls.begin(); iter_decls != _decls.end(); iter_decls++ )
			{
				MG_DELETE( iter_decls->second );
			}
			_decls.clear();
		}

		mActionDeclInfos.clear();
	}
	//-----------------------------------------------------------------------
	ActionDeclaration* ResourceManager::getActionDeclaration( U32 modelDeclID, Str action_name )
	{
		std::list<Str> actionlist;
		ActionDeclsInfos::iterator iter = mActionDeclInfos.find(modelDeclID);

		if ( iter != mActionDeclInfos.end() )
		{
			ActionDecls& decls = iter->second.decls;
			ActionDecls::iterator iter_decls = decls.find( action_name );

			if ( iter_decls != decls.end() )
			{
				ActionDeclaration* action_decl = iter_decls->second;
				return action_decl;
			}

		}

		return NULL;
	}
	//-----------------------------------------------------------------------
	void ResourceManager::getBoneList(U32 modelDeclID, std::vector<Str>& boneList)
	{
		boneList.clear();

		ModelDeclaration* decl = getModelDeclaration(modelDeclID);
		if ( !decl )
			return;

		SkeletonPtr skeleton = SkeletonManager::getSingletonPtr()->getByName( decl->skeletonFileName, decl->path );
		if ( skeleton.isNull() )
		{
			loadResourceGroup( decl->path, decl->path, true );

			if ( ResourceGroupManager::getSingletonPtr()->resourceExists( decl->path, decl->skeletonFileName ) )
			{
				skeleton = SkeletonManager::getSingletonPtr()->load( decl->skeletonFileName, decl->path );
			}
		}

		if ( !skeleton.isNull() )
		{
			Skeleton::BoneIterator boneIter = skeleton->getBoneIterator();

			while ( boneIter.hasMoreElements() )
			{
				Bone* bone = boneIter.getNext();
				if ( bone )
				{
					boneList.push_back( bone->getName() ); 
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void  ResourceManager::getActionList(U32 modelDeclID, std::vector<Str>& actionList)
	{
		actionList.clear();
		ActionDeclsInfos::iterator iter = mActionDeclInfos.find(modelDeclID);

		if ( iter != mActionDeclInfos.end() )
		{
			ActionDecls& decls = iter->second.decls;
			ActionDecls::iterator iter_decls = decls.begin();
			for (; iter_decls != decls.end(); iter_decls++)
			{
				actionList.push_back(iter_decls->first);
			}
		}

	}
	//-----------------------------------------------------------------------
	EffectComponentResourceDeclaration* ResourceManager::getEffectComponentResourceDeclaration( U32 effectElemResID, bool isLoad /*= true */ )
	{
		EffectComponentResourceDeclaration* decl = NULL;

		EffectComponentElementResDeclsMaps::iterator iter = mEffectComponentElementResDecls.find( effectElemResID );
		if ( iter != mEffectComponentElementResDecls.end() )
		{
			decl = &(iter->second);
		}

		if ( decl && isLoad )
		{
			loadResourceGroup( decl->filePath, decl->filePath );
		}

		return decl;
	}
	//-----------------------------------------------------------------------
	EffectComponentResourceDeclaration* ResourceManager::getEffectComponentResourceDeclarationByIndex( UInt index, bool isLoad /*= true */ )
	{
		EffectComponentResourceDeclaration* decl = NULL;

		EffectComponentElementResDeclsMaps::iterator iter = mEffectComponentElementResDecls.begin();
		std::advance(iter, index);

		if ( iter != mEffectComponentElementResDecls.end() )
			decl = &(iter->second);

		if ( decl && isLoad )
		{
			loadResourceGroup( decl->filePath, decl->filePath );
		}

		return decl;
	}
	//-----------------------------------------------------------------------
	U32 ResourceManager::getEffectComponentResourceDeclarationCount()
	{
		return mEffectComponentElementResDecls.size();
	}
	//-----------------------------------------------------------------------
	EffectResourceDeclaration* ResourceManager::getEffectResourceDeclaration( U32 effectElemResID, Bool isLoad /* = true */ )
	{
		EffectResourceDeclaration* decl = NULL;

		EffectElementResDeclsMaps::iterator iter = mEffectElementResDecls.find( effectElemResID );
		if ( iter != mEffectElementResDecls.end() )
		{
			decl = &(iter->second);
		}

		if ( decl && isLoad )
		{
			loadResourceGroup( decl->filePath, decl->filePath, true );
		}

		return decl;
	}
	//-----------------------------------------------------------------------
	EffectResourceDeclaration* ResourceManager::getEffectResourceDeclarationByIndex( UInt index, bool isLoad /*= true */ )
	{
		EffectResourceDeclaration* decl = NULL;

		EffectElementResDeclsMaps::iterator iter = mEffectElementResDecls.begin();
		std::advance(iter, index);

		if ( iter != mEffectElementResDecls.end() )
			decl = &(iter->second);

		if ( decl && isLoad )
		{
			loadResourceGroup( decl->filePath, decl->filePath, true );
		}

		return decl;
	}
	//-----------------------------------------------------------------------
	U32 ResourceManager::getEffectResourceDeclarationCount()
	{
		return mEffectElementResDecls.size();
	}

	//-----------------------------------------------------------------------
	GrassEffectResourceDeclaration*	ResourceManager::getGrassEffectResourceDeclaration( U32 grassEffectID )
	{
		GrassEffectResDeclsMap::iterator iter = mGrassEffectResDecls.find( grassEffectID );
		if ( iter != mGrassEffectResDecls.end() )
		{
			return &iter->second;
		}
		return NULL;
	}

    //-----------------------------------------------------------------------
    WaterEffectResourceDeclaration*	ResourceManager::getWaterEffectResourceDeclaration( U32 waterEffectID )
    {
        WaterEffectResDeclsMap::iterator iter = mWaterEffectResDecls.find( waterEffectID );
        if ( iter != mWaterEffectResDecls.end() )
        {
            return &iter->second;
        }
        return NULL;
    }

	//-----------------------------------------------------------------------
	WaterEffectResourceDeclaration*	ResourceManager::getWaterEffectResourceDeclarationByIndex( U32 index )
	{
        if ( (index+1) > mWaterEffectResDecls.size() )
            return NULL;

        WaterEffectResDeclsMap::iterator iter = mWaterEffectResDecls.begin();
        std::advance( iter, index );

		return &iter->second;
	}
	//-----------------------------------------------------------------------
	U32	ResourceManager::getNumWaterEffectResourceDeclaration()
	{
		return mWaterEffectResDecls.size();
	}
	//-----------------------------------------------------------------------
	void ResourceManager::saveWaterEffectResourceDeclaration( U32 waterEffectID )
	{
		EffectResourceConfig::getInstance().modifyWaterEffect( waterEffectID );
		EffectResourceConfig::getInstance().saveWaterEffect();
	}
	//-----------------------------------------------------------------------
	bool ResourceManager::reloadWaterEffectResourceDeclaration()
	{
		return EffectResourceConfig::getInstance().reloadWaterEffect();
	}
	//-----------------------------------------------------------------------
    ModelDeclaration* ResourceManager::getModelDeclaration( U32 modelDeclID, Bool isLoad )
    {
		ModelDeclaration* decl = NULL;
        
		std::map<U32, ModelDeclaration>::iterator iter = mModelDecls.find( modelDeclID );
        if ( iter != mModelDecls.end() )
		{
			decl = &(iter->second);
		}

		if ( !decl )

		{
			std::map<U32, ModelDeclaration>::iterator iter = mModelDecls.begin();
			if ( iter != mModelDecls.end() )
			{
				decl = &(iter->second);
			}
		}

		if ( decl && isLoad )
		{
			loadResourceGroup( decl->path, decl->path, true );
		}

        return decl;
    }
	//-----------------------------------------------------------------------
	U32 ResourceManager::getNumEntityAccessories( U32 accessoryID )
	{
		EntityAcessoryDeclMap::iterator iter = mEntityAccessoryDeclMap.find( accessoryID );

		if ( iter != mEntityAccessoryDeclMap.end() )
		{
			EntityAccessoryDecls& decls = iter->second;
			return decls.size();
		}

		return 0;
	}
	//-----------------------------------------------------------------------
	const EntityAccessoryDeclaration* ResourceManager::getEntityAccessoryDeclaration( U32 accessoryID, U32 index, Bool isLoad/* = true */)
	{
		EntityAcessoryDeclMap::iterator iter = mEntityAccessoryDeclMap.find( accessoryID );

		if ( iter != mEntityAccessoryDeclMap.end() )
		{
			EntityAccessoryDecls& decls = iter->second;

			if ( index < decls.size() )
				return &decls[index];
		}

		return NULL;
	}
    //-----------------------------------------------------------------------
    UInt ResourceManager::getModelDeclarationCount( )
    {
        return mModelDecls.size();
    }

    //-----------------------------------------------------------------------
    ModelDeclaration* ResourceManager::getModelDeclarationByIndex( UInt index, Bool isLoad  )
    {
        std::map<U32, ModelDeclaration>::iterator iter = mModelDecls.begin();
        while ( (index--) > 0 )
        {
            iter++;
        }
        return &(iter->second);
    }

    //-----------------------------------------------------------------------
    void ResourceManager::loadTerrainTextureLayerDeclarations( CChar* filename )
    {
        if ( mTerrainTextureXmlDoc->LoadFile(filename) != XML_NO_ERROR )
        {
			// MG_CN_MODIFY
			IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
			if (packManager)
			{				
				char* buf = NULL;
				int size = 0;
				packManager->extractPackFile(filename, buf, size);
				if (mTerrainTextureXmlDoc->LoadFile(buf, size) != XML_NO_ERROR)
				{
					MG_MESSAGE("ResourceManager::loadTerrainTextureLayerDeclarations ERROR");
					DYNAMIC_ASSERT(false);
					return;
				}
			}
			else
			{
				MG_MESSAGE("ResourceManager::loadTerrainTextureLayerDeclarations ERROR");
				DYNAMIC_ASSERT(false);
				return;
			}
        }

        XMLElement* rootElm = mTerrainTextureXmlDoc->RootElement();
        if (rootElm)
        {
            //create component
            {
                XMLNode* parentNode       = rootElm;
                XMLNode* currNode         = parentNode->FirstChild();
                XMLNode* firstSiblingNode = currNode;
                XMLNode* nextNode         = NULL;
                XMLElement* element       = NULL;

                Str8    name;
                Str8    thumbnailsFileName;
                Str8    describe;
                Flt     worldSize;

                Bool    hasDiffuseSpecular;
                Str8    diffuseSpecularFileName;

                Bool    hasNormalHeight;
                Str8    normalHeightFileName;

                while( currNode )
                {
                    std::string formatType = XML_GET_VALUE(currNode);
                    if (formatType == "TextureLayer")
                    {
                        element = currNode->ToElement();

                        XmlHelper::getAttribute( element, name, "name");
                        XmlHelper::getAttribute( element, thumbnailsFileName, "thumbnailsFileName");
                        XmlHelper::getAttribute( element, describe, "describe");
                        XmlHelper::getAttribute( element, worldSize, "worldSize");

                        XMLNode* dsNode = XmlHelper::getChild(currNode, "DiffuseSpecular");
                        if ( dsNode )
                        {
                            hasDiffuseSpecular = true;
                            element = dsNode->ToElement();

                            XmlHelper::getAttribute( element, diffuseSpecularFileName, "fileName");
                        }else
                        {
                            hasDiffuseSpecular = false;
                        }

                        XMLNode* nhNode = XmlHelper::getChild(currNode, "NormalHeight");
                        if ( nhNode )
                        {
                            hasNormalHeight = true;
                            element = nhNode->ToElement();

                            XmlHelper::getAttribute( element, normalHeightFileName, "fileName");
                        }else
                        {
                            hasNormalHeight = false;
                        }

                        TerrainTextureLayerDeclaration& decl = mTerrainTextureDecls[name];
                        decl.name                       = name;
                        decl.thumbnailsFileName         = thumbnailsFileName;
                        decl.describe                   = describe;
                        decl.worldSize                  = worldSize;

                        decl.hasDiffuseSpecular         = hasDiffuseSpecular;
                        decl.diffuseSpecularFileName    = diffuseSpecularFileName;

                        decl.hasNormalHeight            = hasNormalHeight;
                        decl.normalHeightFileName       = normalHeightFileName;
                    }

                    //@ parallel 
                    nextNode    = currNode->NextSibling();
                    if (nextNode&&nextNode==firstSiblingNode)
                    {
                        break;
                    }
                    currNode = nextNode;
                }
            }
        }
    }

	//-----------------------------------------------------------------------
	MaterialDeclaration* ResourceManager::getMaterialDeclaration(Str materialGroup, U32 index, bool isLoad)
	{
		MaterialDeclsMap::iterator iter = mMaterialDeclsGroups.find( materialGroup );
		if ( iter != mMaterialDeclsGroups.end() )
		{
			MaterialDecls& matDecls = (iter->second);
			if ( index < matDecls.size() )
			{
				MaterialDeclaration* matDecl = &matDecls[index];
				if ( matDecl && isLoad )
				{
					loadResourceGroup( matDecl->texturePath, matDecl->texturePath, true );
				}
				return matDecl;
			}
		}
		return NULL;
	}
	//-----------------------------------------------------------------------
	MaterialParamDeclaration* ResourceManager::getMaterialParamDeclaration( U32 materialID )
	{
		/*std::map<U32, MaterialParamDeclaration>::iterator iter = mMaterialParamDecls.find( materialID );
		if ( iter != mMaterialParamDecls.end() )
		{
			return &(iter->second);
		}*/
		return NULL;
	}
	//-----------------------------------------------------------------------
	void ResourceManager::getMaterialDeclsByModelDeclID( U32 modelDeclID, std::vector<MaterialDeclaration*>& matDecls )
	{
		matDecls.clear();

		ModelDeclaration* model_decl = getModelDeclaration( modelDeclID );
		if ( model_decl )
		{
			Str materialGroupName = model_decl->path + "\\" + model_decl->materialFileName;
			
			Int meshIndex = 0;
			MaterialDeclaration* matDecl = NULL;
			while ( NULL != ( matDecl = getMaterialDeclaration( materialGroupName, meshIndex, false) ) )
			{
				matDecls.push_back(matDecl);
				meshIndex++;
			}
		}
	}
    //-----------------------------------------------------------------------
    TerrainTextureLayerDeclaration* ResourceManager::getTerrainTextureLayerDeclaration( CChar* name, Bool isLoad )
    {
        std::map<Str, TerrainTextureLayerDeclaration>::iterator iter = mTerrainTextureDecls.find( name );
        if ( iter!=mTerrainTextureDecls.end() )
        {
            return &(iter->second);
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    Int ResourceManager::getTerrainTextureLayerDeclarationCount()
    {
        return mTerrainTextureDecls.size();
    }

    //-----------------------------------------------------------------------
    TerrainTextureLayerDeclaration* ResourceManager::getTerrainTextureLayerDeclaration( Int index)
    {
        std::map<Str, TerrainTextureLayerDeclaration>::iterator iter =  mTerrainTextureDecls.begin();
        std::advance(iter, index);

        if ( iter != mTerrainTextureDecls.end() )
            return &(iter->second);

        return NULL;
    }

    //-----------------------------------------------------------------------
    void ResourceManager::loadResourceGroup(  Str group, Str path, Bool isReloaded )
    {
        if ( Ogre::ResourceGroupManager::getSingleton().resourceGroupExists(group) == false )
        {
            Ogre::ResourceGroupManager::getSingleton().createResourceGroup(group,false);

			if ( !path.empty() )
			{
				 Ogre::ResourceGroupManager::getSingleton().addResourceLocation(path, "FileSystem", group, false);
			}
           
            Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(group);
        }

        if ( isReloaded )
            mResourceMap[group] = path;
    }

    //-----------------------------------------------------------------------
    void ResourceManager::unLoadAllResource()
    {
        unLoadAllSkeletonResource();
        unLoadAllTextureResource();
        unLoadAllMeshResource();
        unLoadAllMaterialResource();

        unLoadAllResourceGroup();
    }

    //-----------------------------------------------------------------------
    void ResourceManager::unLoadAllResourceGroup()
    {
        std::map<Str,Str>::iterator iter = mResourceMap.begin();
        for ( ;iter!=mResourceMap.end(); iter++ )
        {
            Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup( iter->first, true );
            //Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup( iter->first );
        }
        mResourceMap.clear();
    }
    
    //-----------------------------------------------------------------------
    void ResourceManager::unLoadAllSkeletonResource()
    {
        mValidSkeletonGroupMap.clear();
        //SkeletonManager::getSingleton().unloadAll();
    }

    //-----------------------------------------------------------------------
    void ResourceManager::unLoadAllTextureResource()
    {
        
    }

    //-----------------------------------------------------------------------
    void ResourceManager::unLoadAllMeshResource()
    {

    }

    //-----------------------------------------------------------------------
    void ResourceManager::unLoadAllMaterialResource()
    {
        
    }

    //-----------------------------------------------------------------------
    SkeletonPtr ResourceManager::getSkeletonPtr(U32 parentModelDeclID, const String& name)
    {
		Str path;
		Str animation;

        SkeletonPtr skeletonPtr;
        skeletonPtr.setNull();

		//通过模型声明ID中寻找合适的动画组
		ActionDeclsInfos::iterator iter_infos = mActionDeclInfos.find(parentModelDeclID);
		
		if ( iter_infos != mActionDeclInfos.end() )
		{
			ActionDecls& _decls = iter_infos->second.decls;
			
			ActionDecls::iterator iter_decls = _decls.find(name);

			if ( iter_decls != _decls.end() )
			{
				animation = iter_decls->second->resource;
				path	  = iter_decls->second->resourcePath;

				//////////////////////////////////////////////////////////////////////////////////////////////////////

				if ( !path.empty() )
				{
					// load resource group if alternative path is specified;
					loadResourceGroup( path, path, true );
				}
				else
				{
					// if action resource path has not been specified in action CSV, use model path instead;
					ModelDeclaration* modelDecl = getModelDeclaration( parentModelDeclID, false );
					if ( modelDecl )
						path = modelDecl->path;
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////
			}
			else
			{
#ifdef _DEBUG
				//char error[64];
				//sprintf_s( error, _countof(error), "Can't load [%s] for model which id is [%d]", name.c_str(), parentModelDeclID );

				//MG_MESSAGE(error);
#endif
			}
		}
		else
		{
			/*wchar_t error[64];
			swprintf_s( error, _countof(error), L"Can't load action csv resource of the model which id is %d", parentModelDeclID );

			MG_MESSAGE(error);*/
		}

		if ( path.empty() || animation.empty() )
			return skeletonPtr;

        std::map<U32, SkeletonMap>::iterator iter;
        std::map<Str, SkeletonPtr>::iterator jter;

        //查找时候是否无效的骨骼
		Str skeleton_name = animation;

        {
            iter =  mInvalidSkeletonGroupMap.find(parentModelDeclID);
            if ( iter!=mInvalidSkeletonGroupMap.end() )
            {
                jter = iter->second.skeletonMap.find(skeleton_name);
                if ( jter != iter->second.skeletonMap.end() )
                    return skeletonPtr;
            }
        }

        //查找有效骨骼
        //如果有则返回
        {
            iter =  mValidSkeletonGroupMap.find(parentModelDeclID);
            if ( iter!=mValidSkeletonGroupMap.end() )
            {
                jter = iter->second.skeletonMap.find(skeleton_name);
                if ( jter != iter->second.skeletonMap.end() )
                {
                    return jter->second;
                }
            }
        }
	
        //如果没有则加载
        {
            // 加载骨骼
            try {
                skeletonPtr = SkeletonManager::getSingleton().load(animation, path);
            }
            catch (...)
            {
                skeletonPtr.setNull();
                // Log this error
                String msg = "Unable to load skeleton ";
                msg += name;
                LogManager::getSingleton().logMessage(msg);
            }
        }

        // 加载成功
        if (skeletonPtr.isNull()==false)
        {
            SkeletonMap& skeletonMap = mValidSkeletonGroupMap[parentModelDeclID];
            skeletonMap.skeletonMap[skeleton_name] = skeletonPtr;

        }
		else
        //加载失败
        {
            SkeletonMap& skeletonMap = mInvalidSkeletonGroupMap[parentModelDeclID];
            skeletonMap.skeletonMap[skeleton_name] = skeletonPtr;
        }

        return skeletonPtr;
    }

}

