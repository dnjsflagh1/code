/******************************************************************************/
#include "stdafx.h"
#include "EngineMain.h"
#include "Scene.h"
#include "SceneXmlSerializer.h"
#include "Display.h"
#include "Tree.h"
#include "Grass.h"
#include "TreeManager.h"
#include "ILight.h"
#include "ICollisionObject.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
	
    /** 场景文件节点标签 */
    //@{ 
	    #define SCENE_TAG "Scene"
	    #define TERRAIN_TAG "Terrain"
        #define TREE_TAG "Tree"
		#define ENTITY_TAG "EntityGroup"
		#define EFFECTENTITY_TAG "EffectEntityGroup"
		// CN_MODIFY
		#define EFFECTCOMPONENT_TAG "EffectComponentGroup" 
    //@}

	//-----------------------------------------------------------------------

    /** 场景文件版本号 */
    //@{ 
        //版本 2011.8.11
        #define SCENE_FILE_VERSION_1 "SCENE_FILE_VERSION_1"
    //@}

    /** 场景当前文件版本 */
	#define SCENE_FILE_VERSION_NOW SCENE_FILE_VERSION_1
    


    /******************************************************************************/
    //SceneXmlSerializer
    /******************************************************************************/
	SceneXmlSerializer::SceneXmlSerializer(Scene* scene)
        :mScene(scene)
        ,mCameraFormat(NULL)
        ,mEnvironmentFormat(NULL)
		,mSpeedTreeEnvFormat(NULL)
	{
		mSceneXmlDoc            = MG_NEW tinyxml2::XMLDocument;
        mSubSceneXmlDoc         = MG_NEW tinyxml2::XMLDocument;
		mNodeTrackXmlDoc		= MG_NEW tinyxml2::XMLDocument;
        mTerrainXmlDoc          = MG_NEW tinyxml2::XMLDocument;
        mTreeXmlDoc             = MG_NEW tinyxml2::XMLDocument;

        mEntityFormatGroup      = MG_NEW SceneObjectXmlFormatGroup<EntityXmlFormat,Entity>(mScene,"Entity");
        mSubEntityFormatGroup   = MG_NEW SceneObjectXmlFormatGroup<EntityXmlFormat,Entity>(mScene,"Entity");

        mTreeFormatGroup        = MG_NEW SceneObjectXmlFormatGroup<TreeXmlFormat,Tree>(mScene,"Tree");

		mGrassFormatGroup		= MG_NEW SceneObjectXmlFormatGroup<GrassXmlFormat,Grass>(mScene,"Grass");
		//mEffectEntityFormatGroup = MG_NEW SceneObjectXmlFormatGroup<EffectEntityXmlFormat,EffectEntity>(mScene,"EffectEntity");
		//mSubEffectEntityFormatGroup = MG_NEW SceneObjectXmlFormatGroup<EffectEntityXmlFormat,EffectEntity>(mScene,"EffectEntity");

		// CN_MODIFY
		mEffectComponentFormatGroup = MG_NEW SceneObjectXmlFormatGroup<EffectComponentXmlFormat,EffectComponent>(mScene,"EffectComponent");
		mSubEffectComponentFormatGroup = MG_NEW SceneObjectXmlFormatGroup<EffectComponentXmlFormat,EffectComponent>(mScene,"EffectComponent");
	}
	//-----------------------------------------------------------------------
	SceneXmlSerializer::~SceneXmlSerializer()
	{
        unLoad();

		MG_SAFE_DELETE( mGrassFormatGroup );
        MG_SAFE_DELETE( mTreeFormatGroup );
        MG_SAFE_DELETE( mEntityFormatGroup );
        MG_SAFE_DELETE( mSubEntityFormatGroup );
		//MG_SAFE_DELETE( mEffectEntityFormatGroup );
		//MG_SAFE_DELETE( mSubEffectEntityFormatGroup );

		// CN_MODIFY
		MG_SAFE_DELETE( mEffectComponentFormatGroup );
		MG_SAFE_DELETE( mSubEffectComponentFormatGroup );
 
        MG_SAFE_DELETE( mSceneXmlDoc );
        MG_SAFE_DELETE( mSubSceneXmlDoc );
        MG_SAFE_DELETE( mTerrainXmlDoc );
        MG_SAFE_DELETE( mTreeXmlDoc );
		MG_SAFE_DELETE( mNodeTrackXmlDoc );
	}
    //-----------------------------------------------------------------------
    void SceneXmlSerializer::unLoad()
    {
		mGrassFormatGroup->removeAllFormat();
        mTreeFormatGroup->removeAllFormat();
        mEntityFormatGroup->removeAllFormat();
        mSubEntityFormatGroup->removeAllFormat();
		//mEffectEntityFormatGroup->removeAllFormat();
		//mSubEffectEntityFormatGroup->removeAllFormat();

		//CN_MODIFY
		mEffectComponentFormatGroup->removeAllFormat();
		mSubEffectComponentFormatGroup->removeAllFormat();

        MG_SAFE_DELETE( mCameraFormat );
        MG_SAFE_DELETE( mEnvironmentFormat );
		MG_SAFE_DELETE( mSpeedTreeEnvFormat );

		mSceneXmlDoc->DeleteChildren();
        mSubSceneXmlDoc->DeleteChildren();
        mTerrainXmlDoc->DeleteChildren();
        mTreeXmlDoc->DeleteChildren();
		mNodeTrackXmlDoc->DeleteChildren();

        mTerrDeclare.reset();

		mSceneFilePath.clear();
    }

    //-----------------------------------------------------------------------
    void SceneXmlSerializer::clearIgnoreLoadGroup()
    {
        mIgnoreLoadGroup.clear();
    }
        
    //-----------------------------------------------------------------------
    void SceneXmlSerializer::addIgnoreLoadGroup( Str group )
    {
        mIgnoreLoadGroup[group] = group;
    }

    //-----------------------------------------------------------------------
    Bool SceneXmlSerializer::isIgnoreLoadGroup( Str group )
    {
        std::map<Str,Str>::iterator iter = mIgnoreLoadGroup.find( group );
        if ( iter!=mIgnoreLoadGroup.end() )
        {
            return true;
        }

        return false;
    }

	//-----------------------------------------------------------------------
	Bool SceneXmlSerializer::loadAllContent( CChar* pathName, CChar* subPathName, Bool isCreateFormats /*= false*/ )
	{
		EngineMain::getInstance().lockRender();
		{
			// 清空数据
			unLoad();
			mScene->clear();

			// 保存路径
			mSceneFilePath      = pathName;

			////////////////////////////////////////////////////////////////////////////////////////////////

			// 加载地形文件
			Str terrainFilePath = FileOp::getFullFilePath( Str(mSceneFilePath), Str("Terrain.xml") );
			Str terrainDataPath = FileOp::getFullFilePath( Str(mSceneFilePath), Str("Terrain") );
			if ( loadTerrainData(terrainFilePath.c_str(),terrainDataPath.c_str()) == false )
				return false;

		
			////////////////////////////////////////////////////////////////////////////////////////////////

			//预加载场景文件
			Str sceneFilePath   = FileOp::getFullFilePath( Str(pathName), Str("Scene.xml") );
			if ( preloadSceneFile(sceneFilePath.c_str()) == false )
				return false;

			//预加附属场景文件
			if ( subPathName )
			{		
				if ( preloadSubSceneFile(subPathName) == false )
					return false;
			}
			
			//预加载树文件
			Str treeFilePath   = FileOp::getFullFilePath( Str(pathName), Str("Tree.xml") );
			if ( preloadTreeFile(treeFilePath.c_str()) == false )
			{}

		
			////////////////////////////////////////////////////////////////////////////////////////////////

			// 加载场景文件
			if ( loadSceneFile(sceneFilePath.c_str(), isCreateFormats) == false )
				return false;

			// 加载附属场景文件
			if ( subPathName )
			{
				if ( loadSubSceneFile(subPathName, isCreateFormats) == false )
					return false;
			}
			
			// 加载Tree文件
			if ( loadTreeFile(treeFilePath.c_str(), isCreateFormats) == false )
			{}

			// 加载场景轨迹动画文件
			if ( loadTrackFile(pathName) == false )
			{}

			////////////////////////////////////////////////////////////////////////////////////////////////

			// 后续需要执行的方法
			mScene->buildStaticEntity();

			// SpeedTree
			if ( EngineMain::getInstance().getMode() != EM_EDITOR )
			{
				mScene->getTreeManager()->BuildAllTreeAndGrass();
			}
		}

		EngineMain::getInstance().unLockRender();

		return true;
	}

    //-----------------------------------------------------------------------
    Bool SceneXmlSerializer::loadContent( CChar* pathName, Bool isCreateFormats )
    {
        EngineMain::getInstance().lockRender();
        {
            // 清空数据
            unLoad();
            mScene->clear();

            // 保存路径
            mSceneFilePath      = pathName;

            // 加载地形文件
            Str terrainFilePath = FileOp::getFullFilePath( Str(mSceneFilePath), Str("Terrain.xml") );
            Str terrainDataPath = FileOp::getFullFilePath( Str(mSceneFilePath), Str("Terrain") );
            if ( loadTerrainData(terrainFilePath.c_str(),terrainDataPath.c_str()) == false )
                return false;

			//预加载场景文件
			Str sceneFilePath   = FileOp::getFullFilePath( Str(pathName), Str("Scene.xml") );
			if ( preloadSceneFile(sceneFilePath.c_str()) == false )
				return false;
			
			//预加载树文件
			Str treeFilePath   = FileOp::getFullFilePath( Str(pathName), Str("Tree.xml") );
			if ( preloadTreeFile(treeFilePath.c_str()) == false )
			{}

            // 加载场景文件
            if ( loadSceneFile(sceneFilePath.c_str(), isCreateFormats) == false )
                return false;

            // 加载Tree文件
            if ( loadTreeFile(treeFilePath.c_str(), isCreateFormats) == false )
			{}

			// 加载场景轨迹动画文件
			if ( loadTrackFile(pathName) == false )
			{}

            // 后续需要执行的方法
            mScene->buildStaticEntity();

			// SpeedTree
			if ( EngineMain::getInstance().getMode() != EM_EDITOR )
			{
				mScene->getTreeManager()->BuildAllTreeAndGrass();
			}
        }

        EngineMain::getInstance().unLockRender();

        return true;
    }
    //-----------------------------------------------------------------------
    Bool SceneXmlSerializer::saveContent( CChar* pathName )
    {
        Bool result = true;

        EngineMain::getInstance().lockRender();
        {
            //保存路径
            mSceneFilePath      = pathName;

            // 保存地形资源和文件
            Str terrainFilePath = FileOp::getFullFilePath( Str(mSceneFilePath), Str("Terrain.xml") );
            Str terrainDataPath = FileOp::getFullFilePath( Str(mSceneFilePath), Str("Terrain") );
            if ( saveTerrainData(terrainFilePath.c_str(),terrainDataPath.c_str()) == false )
                result = false;

            // 保存场景文件
            Str sceneFilePath = FileOp::getFullFilePath( Str(pathName), Str("Scene.xml") );
            if ( saveSceneFile(sceneFilePath.c_str()) == false )
                result = false;

            // 保存Tree文件
            Str treeFilePath = FileOp::getFullFilePath( Str(pathName), Str("Tree.xml") );
            if ( saveTreeFile(treeFilePath.c_str()) == false )
                result = false;

        }
        EngineMain::getInstance().unLockRender();
       
        return result;
    }
	//-----------------------------------------------------------------------
	Bool SceneXmlSerializer::clipContent(CChar* pathName, const RectF &clipRect)
	{
		Bool result = true;

		EngineMain::getInstance().lockRender();
		{

			//保存路径
			mSceneFilePath      = pathName;

			// 保存地形资源和文件
			Str terrainFilePath = FileOp::getFullFilePath( Str(mSceneFilePath), Str("Terrain.xml") );
			Str terrainDataPath = FileOp::getFullFilePath( Str(mSceneFilePath), Str("Terrain") );
			clipTerrainData(terrainFilePath.c_str(),terrainDataPath.c_str(),clipRect);

			//根据裁剪的地图偏移地图上的物件
			ITerrainManager* pTerrainMgr = mScene->getTerrainManager();
			Vec3 centerPos = pTerrainMgr->getCenterPosition();
			Dbl terrainWidth = pTerrainMgr->getTerrainWidth();
			Dbl terrainHeight = pTerrainMgr->getTerrainWidth();
			Vec3 curMapTopLeftPos(centerPos.x-terrainWidth/2,centerPos.y,centerPos.z-terrainHeight/2);
			Dbl deltaX = curMapTopLeftPos.x-clipRect.left;
			Dbl deltaZ = clipRect.top - curMapTopLeftPos.z; //z轴方向是朝下的
			Vec3 moveDelta(deltaX, 0, deltaZ);

			std::vector<ISceneObjectXmlFormat*> formatList;
			std::vector<ISceneObjectXmlFormat*>::iterator iter;
			getSceneObjectXmlFormatList(SOT_ENTITY, formatList);

			//trees
			std::vector<ISceneObjectXmlFormat*> treeFormatList;
			getSceneObjectXmlFormatList(SOT_TREE, treeFormatList);
			formatList.insert(formatList.end(),treeFormatList.begin(),treeFormatList.end());

			//grass
			std::vector<ISceneObjectXmlFormat*> grassFormatList;
			getSceneObjectXmlFormatList(SOT_GRASS, grassFormatList);
			formatList.insert(formatList.end(),grassFormatList.begin(),grassFormatList.end());

			//特效
			std::vector<ISceneObjectXmlFormat*> effectFormatList;
			getSceneObjectXmlFormatList(SOT_EFFECTENTITY, effectFormatList);
			formatList.insert(formatList.end(),effectFormatList.begin(),effectFormatList.end());

			for (  iter= formatList.begin(); iter!=formatList.end(); iter++ )
			{
				ISceneObjectXmlFormat* format = *iter;
				ISceneObject* obj = format->getSceneObject();
				ISceneNode* sceneNode = obj->getSceneNode();
				sceneNode->translate(moveDelta,ISceneNode::TS_WORLD);
				format->fill();
			}

			// 保存场景文件
			Str sceneFilePath = FileOp::getFullFilePath( Str(pathName), Str("Scene.xml") );
			if ( saveSceneFile(sceneFilePath.c_str()) == false )
				result = false;

			// 保存Tree文件
			Str treeFilePath = FileOp::getFullFilePath( Str(pathName), Str("Tree.xml") );
			if ( saveTreeFile(treeFilePath.c_str()) == false )
				result = false;

		}
		EngineMain::getInstance().unLockRender();

		return result;
	}
    //-----------------------------------------------------------------------
	Bool SceneXmlSerializer::createSceneContent( )
	{
		unLoad();

		mScene->clear();
		mScene->getTerrainManager()->getTerrainSurfaceManager()->clearGlobleTextureLayer();
		mScene->getTerrainManager()->getTerrainSurfaceManager()->clearGlobleWaterGroups();

		TerrainDeclare decl;
		decl.reset();

		///////////////////////////////////////////////////////////////////////
		
		{
			//创建地形格式化存储文件
			if ( createTerrainFormat( &decl ) == false )
				return false;

			//创建场景格式化存储文件
			if ( createSceneFormat() == false )
				return false;

			//创建树格式化存储文件
			if ( createTreeFormat() == false )
				return false;
		}

		return true;
	}
	//-----------------------------------------------------------------------
	
    Bool SceneXmlSerializer::createSceneContent( TerrainDeclare* decl, Str path, Bool isCreateGameFile )
    {
		unLoad();

		///////////////////////////////////////////////////////////////////////
		mScene->clear();
		mScene->getTerrainManager()->getTerrainSurfaceManager()->clearGlobleTextureLayer();
		mScene->getTerrainManager()->getTerrainSurfaceManager()->clearGlobleWaterGroups();
		///////////////////////////////////////////////////////////////////////

		{
			//创建地形格式化存储文件
			if ( createTerrainFormat( decl ) == false )
				return false;

			//创建场景格式化存储文件
			if ( createSceneFormat() == false )
				return false;

			//创建树格式化存储文件
			if ( createTreeFormat() == false )
				return false;
		}

		///////////////////////////////////////////////////////////////////////
		
		{
			//读取地形格式化存储文件
			if ( loadTerrainFormat( path ) == false )
				return false;

			//读取场景格式化存储文件
			if ( loadSceneFormat() == false )
				return false;

			//读取树格式化存储文件
			if ( loadTreeFormat() == false )
				return false;
		}

		///////////////////////////////////////////////////////////////////////

		return true;
	}
	//-----------------------------------------------------------------------
	Bool SceneXmlSerializer::createSceneFormat()
	{
		//---------------------------------------------------------------------------

		// 销毁原有场景的格式化存储文件
		mEntityFormatGroup->removeAllFormat();
		//mEffectEntityFormatGroup->removeAllFormat();

		// CN_MODIFY
		mEffectComponentFormatGroup->removeAllFormat();
		
		mSceneXmlDoc->DeleteChildren();
		
		MG_SAFE_DELETE( mEnvironmentFormat );
		MG_SAFE_DELETE( mCameraFormat );

		//---------------------------------------------------------------------------

		/*
			创建新的Scene文件格式化存储
		*/

		XMLElement* rootElm = XmlHelper::addChild(mSceneXmlDoc, SCENE_TAG);
		if ( rootElm )
		{
			Str8 version = SCENE_FILE_VERSION_NOW;
			XmlHelper::setAttribute(rootElm, version, "Version");

			//Camera
			XMLElement* cameraElm = XmlHelper::addChild(rootElm, "Camera");
			DYNAMIC_ASSERT(mCameraFormat==NULL);
			mCameraFormat = MG_NEW CameraXmlFormat(mScene,cameraElm,mScene->getActiveCamera());
			mCameraFormat->fill();

			//Environment
			XMLElement* environmentElm = XmlHelper::addChild(rootElm, "Environment");
			DYNAMIC_ASSERT(mEnvironmentFormat==NULL);
			mEnvironmentFormat = MG_NEW EnvironmentXmlFormat(mScene,environmentElm);
			mEnvironmentFormat->fill();

			//EnityGroup
			XMLElement* entityElm =  XmlHelper::addChild(rootElm, ENTITY_TAG);
			if ( entityElm )
			{
				mEntityFormatGroup->setGroupElm( entityElm );
			}
			
			////EffectEntityGroup
			//XMLElement* effectElm = XmlHelper::addChild(rootElm, EFFECTENTITY_TAG);
			//if ( effectElm )
			//{
			//	mEffectEntityFormatGroup->setGroupElm( effectElm );
			//}

			// EffectComponentGroup
			XMLElement* effectcomponentElm = XmlHelper::addChild(rootElm, EFFECTCOMPONENT_TAG);
			if (effectcomponentElm)
			{
				mEffectComponentFormatGroup->setGroupElm(effectcomponentElm);
			}
		}

		return true;
	}
	//---------------------------------------------------------------------------
	Bool SceneXmlSerializer::createTreeFormat()
	{
		mTreeFormatGroup->removeAllFormat();

		MG_SAFE_DELETE( mSpeedTreeEnvFormat );

		mTreeXmlDoc->DeleteChildren();

		/*
		创建新的Tree文件格式化存储
		*/

		XMLElement* rootElm = XmlHelper::addChild(mTreeXmlDoc, TREE_TAG);
		if ( rootElm )
		{
			Str8 version = SCENE_FILE_VERSION_NOW;
			XmlHelper::setAttribute(rootElm, version, "Version");

			//Environment
			XMLElement* environmentElm = XmlHelper::addChild(rootElm, "SpeedTreeEnvFormat");
			DYNAMIC_ASSERT(mSpeedTreeEnvFormat==NULL);
			mSpeedTreeEnvFormat = MG_NEW SpeedTreeEnvXmlFormat(mScene,environmentElm);
			mSpeedTreeEnvFormat->fill();

			//TreeGroup
			XMLElement* treeElm = XmlHelper::addChild(rootElm, "TreeGroup");
			if ( treeElm )
			{
				mTreeFormatGroup->setGroupElm( treeElm );
			}

			//GrassGroup
			XMLElement* grassElm =  XmlHelper::addChild(rootElm, "GrassGroup");
			if ( grassElm )
			{
				mGrassFormatGroup->setGroupElm( grassElm );
			}
		}

		return true;
	}

	//---------------------------------------------------------------------------
	Bool SceneXmlSerializer::createTerrainFormat( TerrainDeclare* decl )
	{
		/////////////////////////////////////////////////////////////////////////////
		
		mTerrainXmlDoc->DeleteChildren();

		/////////////////////////////////////////////////////////////////////////////

		mScene->getTerrainManager()->setConfig(*decl);

		/////////////////////////////////////////////////////////////////////////////

		XMLElement* rootElm = XmlHelper::addChild(mTerrainXmlDoc, TERRAIN_TAG);
		if ( rootElm )
		{
			Str8 version = SCENE_FILE_VERSION_NOW;
			XmlHelper::setAttribute(rootElm, version, "Version");			

			XMLElement* rootElm = mTerrainXmlDoc->RootElement();
			if (rootElm)
			{
				version = XML_GET_ATTRIBUTE(rootElm,"Version");

				XMLNode* parentNode       = rootElm;

				//create component
				{
					////////////////////////////////////////////////////////////////////////////////////

					XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainChunkDeclare" );
					TerrainXmlFormat::fillTerrainChunkDeclare( xmlNode->ToElement(), mScene->getTerrainManager()->getConfig() );

					xmlNode				 = XmlHelper::addChild( parentNode, "TerrainHeightDeclare" );
					TerrainXmlFormat::fillTerrainHeightDeclare( xmlNode->ToElement(), mScene );

					xmlNode				 = XmlHelper::addChild( parentNode, "TerrainGlobleTextureLayerList" );
					TerrainXmlFormat::fillTerrainGlobleTextureLayerList( xmlNode->ToElement(), mScene );

					xmlNode				 = XmlHelper::addChild( parentNode, "TerrainGlobleWaterGroupList" );
					TerrainXmlFormat::fillTerrainGlobleWaterGroupList( xmlNode->ToElement(), mScene );

					////////////////////////////////////////////////////////////////////////////////////

					xmlNode				 = XmlHelper::addChild( parentNode, "TerrainRegionDeclare" );
					TerrainXmlFormat::fillTerrainRegionDeclare( xmlNode->ToElement(), mScene );
				}
			}
		}

		return true;
	}
	//-----------------------------------------------------------------------
	Bool SceneXmlSerializer::loadSceneFormat()
	{
		return true;
	}
	//-----------------------------------------------------------------------

	Bool SceneXmlSerializer::loadTreeFormat()
	{
		return true;
	}
	//-----------------------------------------------------------------------
	Bool SceneXmlSerializer::loadTerrainFormat( Str path )
	{
		mScene->getTerrainManager()->unLoad();

		Str8 version; 
		XMLElement* rootElm = mTerrainXmlDoc->RootElement();

		if (rootElm)
		{
			version = XML_GET_ATTRIBUTE(rootElm,"Version");

			//create component
			{
				XMLNode* parentNode       = rootElm;

				////////////////////////////////////////////////////////////////////////////////////

				{
					XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainChunkDeclare" );
					TerrainXmlFormat::applyTerrainChunkDeclare( xmlNode->ToElement(), mScene );
				}
				{
					XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainHeightDeclare" );
					TerrainXmlFormat::applyTerrainHeightDeclare( xmlNode->ToElement(), mScene );
				}
				{
					XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainGlobleTextureLayerList" );
					TerrainXmlFormat::applyTerrainGlobleTextureList( xmlNode->ToElement(), mScene );
				}
				{
					XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainGlobleWaterGroupList" );
					TerrainXmlFormat::applyTerrainGlobleWaterGroupList( xmlNode->ToElement(), mScene );
				}

				////////////////////////////////////////////////////////////////////////////////////

				{
					XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainRegionDeclare" );
					TerrainXmlFormat::applyTerrainRegionDeclare( xmlNode->ToElement(), mScene );
				}

			}
		}

		// 加载地形资源
		mScene->getTerrainManager()->load( path );

		return true;
	}
	//-----------------------------------------------------------------------
	Bool SceneXmlSerializer::loadTrackFile( CChar* pathName )
	{
		////////////////////////////////////////////////////////////////////////////////////
		mScene->getOgreSceneManager()->destroyAllAnimations();
		////////////////////////////////////////////////////////////////////////////////////

		Str fileName = "Scene.xml";
		Str trackFileFullPath = FileOp::getFullFilePath( Str(pathName), fileName );

		if ( mNodeTrackXmlDoc->LoadFile(trackFileFullPath.c_str()) != XML_NO_ERROR )
		{   
			// MG_CN_MODIFY
			IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
			if (packManager)
			{
				char* buf = NULL;
				int size = 0;
				//packManager->extractPackFile(trackFileFullPath.c_str(), buf, size);
				if (mNodeTrackXmlDoc->LoadFile(trackFileFullPath.c_str()) != XML_NO_ERROR )
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////

		XMLElement* rootElm = mNodeTrackXmlDoc->RootElement();

		if ( rootElm )
		{
			XMLElement* nodesRoot = XmlHelper::getChild(rootElm, "nodes");

			if ( nodesRoot )
			{
				XMLElement* nodeElement = NULL;

				while ( nodeElement = XmlHelper::IterateChildElements( nodesRoot, nodeElement) )
				{
					Str formatType = XML_GET_VALUE(nodeElement);

					if ( formatType.compare("node") == 0 )
					{
						XMLElement* animationsElement = XmlHelper::getChild(nodeElement, "animations");

						if ( animationsElement )
						{
							NodeTrackXmlFormat::applyNodeTrackAnimations( mScene, animationsElement );
						}
					}
				}
			}
		}

		////////////////////////////////////////////////////////////////////////////////////

		return true;

		////////////////////////////////////////////////////////////////////////////////////
	}
	//-----------------------------------------------------------------------
	Bool SceneXmlSerializer::preloadSceneFile( CChar* fileName )
	{
		EntityXmlFormat::applyIndex = 0;
		EntityXmlFormat::applyTotal = 0;

		//EffectEntityXmlFormat::applyIndex = 0;
		//EffectEntityXmlFormat::applyTotal = 0;
		EffectComponentXmlFormat::applyIndex = 0;
		EffectComponentXmlFormat::applyTotal = 0;

		if ( mSceneXmlDoc->LoadFile(fileName) != XML_NO_ERROR )
		{
			// MG_CN_MODIFY
			IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
			if (packManager)
			{				
				char* buf = NULL;
				int size = 0;
				packManager->extractPackFile(fileName, buf, size);
				if (mSceneXmlDoc->LoadFile(buf) != XML_NO_ERROR)
				{
					MG_MESSAGE("loadSceneFile Error!");
					DYNAMIC_ASSERT(false);
					return false;
				}
			}
			else
			{
				MG_MESSAGE("loadSceneFile Error!");
				DYNAMIC_ASSERT(false);
				return false;
			}
		}

		Str8 version;
		XMLElement* rootElm = mSceneXmlDoc->RootElement();
		if ( rootElm )
		{
			version = XML_GET_ATTRIBUTE(rootElm,"Version");

			XMLNode* parent = rootElm;
			XMLNode* currNode = rootElm->FirstChild();
			XMLNode* firstSiblingNode = currNode;
			XMLNode* nextNode = NULL;

			//获取特效以及各种资源的总数
			while ( currNode )
			{
				std::string formatType = XML_GET_VALUE(currNode);

				if (formatType == "EntityGroup")
				{
					UInt entityCount = XmlHelper::getChildCount( currNode );

					EntityXmlFormat::applyTotal = entityCount;
				}
				//else if (formatType == "EffectEntityGroup")
				//{
				//	UInt entityCount = XmlHelper::getChildCount( currNode );

				//	EffectEntityXmlFormat::applyTotal = entityCount;
				//}
				else if (formatType == "EffectComponentGroup")
				{
					UInt effectCount = XmlHelper::getChildCount( currNode );
					EffectComponentXmlFormat::applyTotal = effectCount;
				}

				//@ parallel 
				nextNode = currNode->NextSibling();

				if ( nextNode && nextNode == firstSiblingNode )
				{
					break;
				}

				currNode = nextNode;
			}
		}

		return true;
	}
	//-----------------------------------------------------------------------
	Bool SceneXmlSerializer::preloadSubSceneFile( CChar* fileName )
	{
		if ( mSubSceneXmlDoc->LoadFile(fileName) != XML_NO_ERROR )
		{
			// MG_CN_MODIFY
			IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
			if (packManager)
			{				
				char* buf = NULL;
				int size = 0;
				packManager->extractPackFile(fileName, buf, size);
				if (mSubSceneXmlDoc->LoadFile(buf) != XML_NO_ERROR)
				{
					MG_MESSAGE("loadSceneFile Error!");
					DYNAMIC_ASSERT(false);
					return false;
				}
			}
			else
			{
				MG_MESSAGE("loadSceneFile Error!");
				DYNAMIC_ASSERT(false);
				return false;
			}
		}

		Str8 version;
		XMLElement* rootElm = mSubSceneXmlDoc->RootElement();
		if ( rootElm )
		{
			version = XML_GET_ATTRIBUTE(rootElm,"Version");

			XMLNode* parent = rootElm;
			XMLNode* currNode = rootElm->FirstChild();
			XMLNode* firstSiblingNode = currNode;
			XMLNode* nextNode = NULL;

			//获取特效以及各种资源的总数
			while ( currNode )
			{
				std::string formatType = XML_GET_VALUE(currNode);

				if (formatType == "EntityGroup")
				{
					UInt entityCount = XmlHelper::getChildCount( currNode );

					EntityXmlFormat::applyTotal += entityCount;
				}
				//else if (formatType == "EffectEntityGroup")
				//{
				//	UInt entityCount = XmlHelper::getChildCount( currNode );

				//	EffectEntityXmlFormat::applyTotal += entityCount;
				//}
				else if (formatType == "EffectComponentGroup")
				{
					UInt effectCount = XmlHelper::getChildCount( currNode );
					EffectComponentXmlFormat::applyTotal += effectCount;
				}

				//@ parallel 
				nextNode = currNode->NextSibling();

				if ( nextNode && nextNode == firstSiblingNode )
				{
					break;
				}

				currNode = nextNode;
			}
		}

		return true;
	}
	//-----------------------------------------------------------------------
	Bool SceneXmlSerializer::loadSceneFile( CChar* filename, Bool isCreateFormats )
	{
		if ( !mSceneXmlDoc->RootElement() )
		{
			return false;
		}
		
		Str8 version; 
		XMLElement* rootElm = mSceneXmlDoc->RootElement();

		if (rootElm)
		{
			version = XML_GET_ATTRIBUTE(rootElm,"Version");
		
			//create component
			{
				XMLNode* parentNode       = rootElm;
				XMLNode* currNode         = parentNode->FirstChild();
				XMLNode* firstSiblingNode = currNode;
				XMLNode* nextNode         = NULL;

                //initialize
                XMLElement* camElm = XmlHelper::getChild(parentNode, "Camera");
                if (!camElm)
                {
                    XmlHelper::addChild(parentNode, "Camera");
                }
                XMLElement* envElm = XmlHelper::getChild(parentNode, "Environment");
                if (!envElm)
                {
                    XmlHelper::addChild(parentNode, "Environment");
                }
				XMLElement* entityElm = XmlHelper::getChild(parentNode, ENTITY_TAG);
				if (!entityElm)
				{
					XmlHelper::addChild(parentNode, ENTITY_TAG);
				}
				XMLElement* effectEntityElm = XmlHelper::getChild(parentNode, EFFECTENTITY_TAG);
				if (!effectEntityElm)
				{
					XmlHelper::addChild(parentNode, EFFECTENTITY_TAG);
				}

				while( currNode )
				{
					//TODO:
					std::string formatType = XML_GET_VALUE(currNode);
                    if (formatType == "Camera")
                    {
                        DYNAMIC_ASSERT(mCameraFormat==NULL);
                        mCameraFormat = MG_NEW CameraXmlFormat(mScene,currNode->ToElement(),mScene->getActiveCamera());
                        mCameraFormat->apply();

                    }else
                    if (formatType == "Environment")
                    {
                        DYNAMIC_ASSERT(mEnvironmentFormat==NULL);
                        mEnvironmentFormat = MG_NEW EnvironmentXmlFormat(mScene,currNode->ToElement());
                        mEnvironmentFormat->apply();

                    }else
					if (formatType == "EntityGroup")
					{
                        mEntityFormatGroup->loadGroup( currNode->ToElement(), isCreateFormats );
					}
					//else
					//if (formatType == "EffectEntityGroup")
					//{
					//	mEffectEntityFormatGroup->loadGroup( currNode->ToElement(), isCreateFormats );
					//}
					// CN_MODIFY
					else
					if (formatType == "EffectComponentGroup")
					{
						mEffectComponentFormatGroup->loadGroup( currNode->ToElement(), isCreateFormats );
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

		return true;	
	}
	//-----------------------------------------------------------------------
	Bool SceneXmlSerializer::saveSceneFile( CChar* filename )
	{	
        if ( mCameraFormat )
            mCameraFormat->fill();
        if ( mEnvironmentFormat )
            mEnvironmentFormat->fill();
		mSceneXmlDoc->SaveFile(filename);
        return true;
	}

    //-----------------------------------------------------------------------
    Bool SceneXmlSerializer::loadSubSceneFile( CChar* filename, Bool isCreateFormats )
    {
        if ( mSubSceneXmlDoc->LoadFile(filename) != XML_NO_ERROR )
        {
			// MG_CN_MODIFY
			IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
			if (packManager)
			{				
				wchar_t* buf = NULL;
				int size = 0;
				packManager->extractPackFile(filename, buf);
				std::string str;
				if (mSubSceneXmlDoc->LoadFile(str.c_str()) != XML_NO_ERROR)
				{
					MG_MESSAGE("loadSubSceneFile Error!");
					DYNAMIC_ASSERT(false);
					return false;
				}
			}
			else
			{
				MG_MESSAGE("loadSubSceneFile Error!");
				DYNAMIC_ASSERT(false);
				return false;
			}
        }

        Str8 version; 
        XMLElement* rootElm = mSubSceneXmlDoc->RootElement();
        if (rootElm)
        {
            version = XML_GET_ATTRIBUTE(rootElm,"Version");

            //create component
            {
                XMLNode* parentNode       = rootElm;
                XMLNode* currNode         = parentNode->FirstChild();
                XMLNode* firstSiblingNode = currNode;
                XMLNode* nextNode         = NULL;

				XMLElement* envElm = XmlHelper::getChild(parentNode, "Environment");
				if (!envElm)
				{
					XmlHelper::addChild(parentNode, "Environment");
				}
				XMLElement* entityElm = XmlHelper::getChild(parentNode, ENTITY_TAG);
				if (!entityElm)
				{
					XmlHelper::addChild(parentNode, ENTITY_TAG);
				}
				XMLElement* effectEntityElm = XmlHelper::getChild(parentNode, EFFECTENTITY_TAG);
				if (!effectEntityElm)
				{
					XmlHelper::addChild(parentNode, EFFECTENTITY_TAG);
				}

                while( currNode )
                {
                    //TODO:
                    std::string formatType = XML_GET_VALUE(currNode);

                    if (formatType == "EntityGroup")
                    {
                        mSubEntityFormatGroup->loadGroup( currNode->ToElement(), isCreateFormats );
                    }
					//else if (formatType == "EffectEntityGroup")
					//{
					//	mSubEffectEntityFormatGroup->loadGroup( currNode->ToElement(), isCreateFormats );
					//}
					// CN_MODIFY
					else if (formatType == "EffectComponentGroup")
					{
						UInt effectCount = XmlHelper::getChildCount( currNode );

						EffectComponentXmlFormat::applyIndex = 0;
						EffectComponentXmlFormat::applyTotal = effectCount;

						mSubEffectComponentFormatGroup->loadGroup( currNode->ToElement(), isCreateFormats );
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

        return true;
    }

	//-----------------------------------------------------------------------
	void SceneXmlSerializer::unloadSubScene()
	{
		if (mSubSceneXmlDoc)
		{
			
			if (mSubEntityFormatGroup)
			{
				std::vector<ISceneObjectXmlFormat*> formatList;
				mSubEntityFormatGroup->getFormatList(formatList);
				std::vector<ISceneObjectXmlFormat*>::iterator itr;
				for (itr=formatList.begin(); itr!=formatList.end(); itr++)
				{
					ISceneObject* object = (*itr)->getSceneObject();
					if (object)
						mScene->destroySceneObject( object->getName().c_str(), object->getType() );
				}
				mSubEntityFormatGroup->removeAllFormat();
			}
			
			//if (mSubEffectEntityFormatGroup)
			//{
			//	std::vector<ISceneObjectXmlFormat*> formatList;
			//	mSubEffectEntityFormatGroup->getFormatList(formatList);
			//	std::vector<ISceneObjectXmlFormat*>::iterator itr;
			//	for (itr=formatList.begin(); itr!=formatList.end(); itr++)
			//	{
			//		ISceneObject* object = (*itr)->getSceneObject();
			//		if (object)
			//			mScene->destroySceneObject( object->getName().c_str(), object->getType() );
			//	}
			//	mSubEffectEntityFormatGroup->removeAllFormat();
			//}

			// CN_MODIFY
			if (mSubEffectComponentFormatGroup)
			{
				std::vector<ISceneObjectXmlFormat*> formatList;
				mSubEffectComponentFormatGroup->getFormatList(formatList);
				std::vector<ISceneObjectXmlFormat*>::iterator itr;
				for (itr=formatList.begin(); itr!=formatList.end(); itr++)
				{
					ISceneObject* object = (*itr)->getSceneObject();
					if (object)
						mScene->destroySceneObject( object->getName().c_str(), object->getType() );
				}
				mSubEffectComponentFormatGroup->removeAllFormat();
			}
			
		}
	}

	//----------------------------------------------------------------------
	void SceneXmlSerializer::showSubscene(bool show)
	{
		if (mSubSceneXmlDoc)
		{
			if (mSubEntityFormatGroup)
			{
				std::vector<ISceneObjectXmlFormat*> formatList;
				mSubEntityFormatGroup->getFormatList(formatList);
				std::vector<ISceneObjectXmlFormat*>::iterator itr;
				for (itr=formatList.begin(); itr!=formatList.end(); itr++)
				{
					ISceneObject* object = (*itr)->getSceneObject();
					if (object)
						object->getSceneNode()->setVisible(show);
				}
			}

			//if (mSubEffectEntityFormatGroup)
			//{
			//	std::vector<ISceneObjectXmlFormat*> formatList;
			//	mSubEffectEntityFormatGroup->getFormatList(formatList);
			//	std::vector<ISceneObjectXmlFormat*>::iterator itr;
			//	for (itr=formatList.begin(); itr!=formatList.end(); itr++)
			//	{
			//		ISceneObject* object = (*itr)->getSceneObject();
			//		if (object)
			//			object->getSceneNode()->setVisible(show);
			//	}
			//}

			// CN_MODIFY
			if (mSubEffectComponentFormatGroup)
			{
				std::vector<ISceneObjectXmlFormat*> formatList;
				mSubEffectComponentFormatGroup->getFormatList(formatList);
				std::vector<ISceneObjectXmlFormat*>::iterator itr;
				for (itr=formatList.begin(); itr!=formatList.end(); itr++)
				{
					ISceneObject* object = (*itr)->getSceneObject();
					if (object)
						object->getSceneNode()->setVisible(show);
				}
			}

		}
	}

    //-----------------------------------------------------------------------
    Bool SceneXmlSerializer::saveSubSceneFile( CChar* filename )
    {
		if ( mScene->getResourceSaveListener() )
			mScene->getResourceSaveListener()->preSaveObject();

        mSubSceneXmlDoc->SaveFile(filename);

        return true;
    }

    //-----------------------------------------------------------------------
    Bool SceneXmlSerializer::loadTerrainData( CChar* filename, CChar* dataPath )
    {
        if ( mTerrainXmlDoc->LoadFile(filename) != XML_NO_ERROR )
        {
            //MG_MESSAGE("loadTerrainData Error!");
            //DYNAMIC_ASSERT(false);
			
			// MG_CN_MODIFY
			IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
			if (packManager)
			{
				char* buf = NULL;
				int size = 0;
				packManager->extractPackFile(filename, buf, size);
				if (mTerrainXmlDoc->LoadFile(buf) != XML_NO_ERROR )
				{
					MG_MESSAGE("loadTerrainData Error!");
					MG_MESSAGE(filename);
					DYNAMIC_ASSERT(false);
					return false;
				}
			}
			else
			{
				MG_MESSAGE("loadTerrainData Error!");
				MG_MESSAGE(filename);
				DYNAMIC_ASSERT(false);
				return false;
			}
        }
        
        mScene->getTerrainManager()->unLoad();

        Str8 version; 
        XMLElement* rootElm = mTerrainXmlDoc->RootElement();
        if (rootElm)
        {
            version = XML_GET_ATTRIBUTE(rootElm,"Version");

            //create component
            {
                XMLNode* parentNode       = rootElm;

                ////////////////////////////////////////////////////////////////////////////////////
                
                {
                    XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainChunkDeclare" );
                    TerrainXmlFormat::applyTerrainChunkDeclare( xmlNode->ToElement(), mScene );
                }
                {
                    XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainHeightDeclare" );
                    TerrainXmlFormat::applyTerrainHeightDeclare( xmlNode->ToElement(), mScene );
                }
                {
                    XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainGlobleTextureLayerList" );
                    TerrainXmlFormat::applyTerrainGlobleTextureList( xmlNode->ToElement(), mScene );
                }
                {
                    XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainGlobleWaterGroupList" );
                    TerrainXmlFormat::applyTerrainGlobleWaterGroupList( xmlNode->ToElement(), mScene );
                }

                ////////////////////////////////////////////////////////////////////////////////////

                {
                    XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainRegionDeclare" );
                    TerrainXmlFormat::applyTerrainRegionDeclare( xmlNode->ToElement(), mScene );
                }

            }
        }

        // 加载地形资源
        mScene->getTerrainManager()->load( dataPath );
        
        return true;
    }

    //-----------------------------------------------------------------------
    Bool SceneXmlSerializer::saveTerrainData( CChar* filename, CChar* dataPath )
    {
		/////////////////////////////////////////////////////////////////////////////

		mTerrainXmlDoc->DeleteChildren();

		/////////////////////////////////////////////////////////////////////////////
        XMLElement* rootElm = XmlHelper::addChild(mTerrainXmlDoc, TERRAIN_TAG);
        if (rootElm)
        {
			Str8 version = SCENE_FILE_VERSION_NOW;
			XmlHelper::setAttribute(rootElm, version, "Version");	

            //create component
            {
                XMLNode* parentNode       = rootElm;

                {
                    XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainChunkDeclare" );
                    TerrainXmlFormat::fillTerrainChunkDeclare( xmlNode->ToElement(), mScene );
                }
                {
                    XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainHeightDeclare" );
                    TerrainXmlFormat::fillTerrainHeightDeclare( xmlNode->ToElement(), mScene );
                }
                {
                    XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainRegionDeclare" );
                    TerrainXmlFormat::fillTerrainRegionDeclare( xmlNode->ToElement(), mScene );
                }
                {
                    XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainGlobleTextureLayerList" );
                    TerrainXmlFormat::fillTerrainGlobleTextureLayerList( xmlNode->ToElement(), mScene );
                }
                {
                    XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainGlobleWaterGroupList" );
                    TerrainXmlFormat::fillTerrainGlobleWaterGroupList( xmlNode->ToElement(), mScene );
                }
            }
        }

        {
            mScene->getTerrainManager()->save( dataPath );
            mTerrainXmlDoc->SaveFile(filename);
        }

        return true;
    }
	//-----------------------------------------------------------------------
	Bool SceneXmlSerializer::clipTerrainData( CChar* filename, CChar* dataPath, RectF clipRect)
	{
		/////////////////////////////////////////////////////////////////////////////
		mScene->getTerrainManager()->clip( dataPath, clipRect);


		mTerrainXmlDoc->DeleteChildren();

		/////////////////////////////////////////////////////////////////////////////
		XMLElement* rootElm = XmlHelper::addChild(mTerrainXmlDoc, TERRAIN_TAG);
		if (rootElm)
		{
			Str8 version = SCENE_FILE_VERSION_NOW;
			XmlHelper::setAttribute(rootElm, version, "Version");	

			//create component
			{
				XMLNode* parentNode       = rootElm;

				{
					XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainChunkDeclare" );
					TerrainXmlFormat::fillTerrainChunkDeclare( xmlNode->ToElement(), mScene );
				}
				{
					XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainHeightDeclare" );
					TerrainXmlFormat::fillTerrainHeightDeclare( xmlNode->ToElement(), mScene );
				}
				{
					XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainRegionDeclare" );
					TerrainXmlFormat::fillTerrainRegionDeclare( xmlNode->ToElement(), mScene );
				}
				{
					XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainGlobleTextureLayerList" );
					TerrainXmlFormat::fillTerrainGlobleTextureLayerList( xmlNode->ToElement(), mScene );
				}
				{
					XMLNode* xmlNode     = XmlHelper::addChild( parentNode, "TerrainGlobleWaterGroupList" );
					TerrainXmlFormat::fillTerrainGlobleWaterGroupList( xmlNode->ToElement(), mScene );
				}
			}
		}

		//保存Terrain文件
		mTerrainXmlDoc->SaveFile(filename);

		return true;
	}
	//-----------------------------------------------------------------------
	Bool SceneXmlSerializer::preloadTreeFile( CChar* fileName )
	{
		//预先初始化默认的值
		TreeXmlFormat::applyIndex = 0;
		TreeXmlFormat::applyTotal = 0;

		if ( mTreeXmlDoc->LoadFile(fileName) != XML_NO_ERROR )
		{
			// MG_CN_MODIFY
			IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
			if (packManager)
			{
				char* buf = NULL;
				int size = 0;
				packManager->extractPackFile(fileName, buf, size);
				if (mTreeXmlDoc->LoadFile(buf) != XML_NO_ERROR )
				{
					MG_MESSAGE("preloadTreeFile Error!");
					DYNAMIC_ASSERT(false);
					return false;
				}
			}
			else
			{
				MG_MESSAGE("loadSceneFile Error!");
				DYNAMIC_ASSERT(false);
				return false;
			}
		}

		Str8 version; 
		XMLElement* rootElm = mTreeXmlDoc->RootElement();

		if (rootElm)
		{
			version = XML_GET_ATTRIBUTE(rootElm,"Version");

			///////////////////////////////////////////////////////////////////////////////////

			XmlHelper::addChild( rootElm, "TreeGroup" );
			XmlHelper::addChild( rootElm, "GrassGroup" );

			///////////////////////////////////////////////////////////////////////////////////

			//create component
			{
				XMLNode* parentNode       = rootElm;
				XMLNode* currNode         = parentNode->FirstChild();
				XMLNode* firstSiblingNode = currNode;
				XMLNode* nextNode         = NULL;

				//初始化
				while( currNode )
				{
					//TODO:
					std::string formatType = XML_GET_VALUE(currNode);

					if (formatType == "TreeGroup")
					{
						UInt entityCount = XmlHelper::getChildCount( currNode );

						TreeXmlFormat::applyIndex = 0;
						TreeXmlFormat::applyTotal = entityCount;
					}
					else if (formatType == "GrassGroup")
					{
						UInt entityCout = XmlHelper::getChildCount( currNode );

						GrassXmlFormat::applyIndex = 0;
						GrassXmlFormat::applyTotal = entityCout;
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

		return true;	
	}
    //-----------------------------------------------------------------------
    Bool SceneXmlSerializer::loadTreeFile( CChar* filename, Bool isCreateFormats )
    {
        if ( !mTreeXmlDoc->RootElement() ) 
        {
            // MG_CN_MODIFY
            IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
            if (packManager)
            {				
				char* buf = NULL;
				int size = 0;
				packManager->extractPackFile(filename, buf, size);
                if (mTreeXmlDoc->LoadFile(buf) != XML_NO_ERROR)
                {
                    MG_MESSAGE("loadSceneFile Error!");
                    DYNAMIC_ASSERT(false);
                    return false;
                }
            }
            else
            {
                MG_MESSAGE("loadSceneFile Error!");
                DYNAMIC_ASSERT(false);
                return false;
            }
        }

        Str8 version; 
        XMLElement* rootElm = mTreeXmlDoc->RootElement();
        if (rootElm)
        {
            version = XML_GET_ATTRIBUTE(rootElm,"Version");

            //create component
            {
                XMLNode* parentNode       = rootElm;
                XMLNode* currNode         = parentNode->FirstChild();
                XMLNode* firstSiblingNode = currNode;
                XMLNode* nextNode         = NULL;

				//initialize
				XMLElement* EnvElmt = XmlHelper::getChild(parentNode, "TreeEnvironment");
				if (!EnvElmt)
				{
					XmlHelper::addChild(parentNode, "TreeEnvironment");
				}

                //初始化
                while( currNode )
                {
                    //TODO:
                    std::string formatType = XML_GET_VALUE(currNode);

					if (formatType == "TreeEnvironment")
					{
						DYNAMIC_ASSERT(mSpeedTreeEnvFormat==NULL);
						mSpeedTreeEnvFormat = MG_NEW SpeedTreeEnvXmlFormat(mScene,currNode->ToElement());
						mSpeedTreeEnvFormat->apply();
					}
					else if (formatType == "TreeGroup")
                    {
						if ( EngineMain::getInstance().display()->isDebugNoSpeedTree() == false )
						{
							mTreeFormatGroup->loadGroup( currNode->ToElement(), isCreateFormats );
						}
                    }
					else if (formatType == "GrassGroup")
					{
						if ( EngineMain::getInstance().display()->isDebugNoSpeedGrass() == false )
						{
							mGrassFormatGroup->loadGroup( currNode->ToElement(), isCreateFormats );
						}
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

        return true;	
    }

    //-----------------------------------------------------------------------
    Bool SceneXmlSerializer::saveTreeFile( CChar* filename )
    {
        if ( EngineMain::getInstance().display()->isDebugNoSpeedTree() )
            return true;

		if ( mSpeedTreeEnvFormat )
			mSpeedTreeEnvFormat->fill();

        mTreeXmlDoc->SaveFile(filename);
        return true;
    }

    //-----------------------------------------------------------------------
    Str SceneXmlSerializer::getTypeName( SceneObjectTypes type )
    {
		switch(type)
		{
		case SOT_CAMERA:
			return "Camera";
		case SOT_GROUND:
			return "Ground";
		case SOT_CLIFF:
			return "Cliff";
		case SOT_WATER:
			return "Water";
		case SOT_LIGHT:
			return "Light";
		case SOT_ENTITY:
			return "Entity";
        case SOT_TREE:
            return "Tree";
		case SOT_GRASS:
			return "Grass";
		case SOT_EFFECTENTITY:
			return "EffectEntity";
			// CN_MODIFY
		case SOT_EFFECTCOMPONENT:
			return "EffectComponent";
		}

        return "NULL_TYPE";
    }
    //-----------------------------------------------------------------------
    ISceneObjectXmlFormat* SceneXmlSerializer::addSceneObjectFormat( ISceneObject* object, Bool isSub )
    {
		if ( object->getType() == SOT_ENTITY )
		{
            if ( isSub )
			    return mSubEntityFormatGroup->addFormat( dynamic_cast<MG::Entity*>(object) );
            else
                return mEntityFormatGroup->addFormat( dynamic_cast<MG::Entity*>(object) );
		}
		else if ( object->getType() == SOT_TREE )
        {
            if ( isSub )
                return NULL;
            else
                return mTreeFormatGroup->addFormat( dynamic_cast<MG::Tree*>(object) );
        }
		else if ( object->getType() == SOT_GRASS )
		{
			if ( isSub )
			{
				return NULL;
			}
			else
			{
				return mGrassFormatGroup->addFormat( dynamic_cast<MG::Grass*>(object) );
			}
		}
		//else if ( object->getType() == SOT_EFFECTENTITY )
		//{
		//	if ( isSub )
		//		return mSubEffectEntityFormatGroup->addFormat(dynamic_cast<MG::EffectEntity*>(object));
		//	else
		//		return mEffectEntityFormatGroup->addFormat( dynamic_cast<MG::EffectEntity*>(object) );
		//}
		// CN_MODIFY
		else if ( object->getType() == SOT_EFFECTCOMPONENT)
		{
			if ( isSub )
				return mSubEffectComponentFormatGroup->addFormat(dynamic_cast<MG::EffectComponent*>(object));
			else
				return mEffectComponentFormatGroup->addFormat(dynamic_cast<MG::EffectComponent*>(object));
		}

        return NULL;
    }
    //-----------------------------------------------------------------------
    ISceneObjectXmlFormat* SceneXmlSerializer::getSceneObjectFormat( CChar* name, SceneObjectTypes type, Bool isSub )
    {
		if ( type == SOT_ENTITY )
		{
            if ( isSub )
			    return mSubEntityFormatGroup->getFormat( name );
            else
			    return mEntityFormatGroup->getFormat( name );
		}else
        if ( type == SOT_TREE )
        {
            if ( isSub )
                return NULL;
            else
                return mTreeFormatGroup->getFormat( name );
        }else
		if ( type == SOT_GRASS)
		{
			if ( isSub )
			{
				return NULL;
			}
			else
			{
				return mGrassFormatGroup->getFormat( name );
			}
		}
		//else if ( type == SOT_EFFECTENTITY )
		//{
		//	if ( isSub )
		//		return mSubEffectEntityFormatGroup->getFormat(name);
		//	else
		//		return mEffectEntityFormatGroup->getFormat( name );
		//}
		// CN_MODIFY
		else if ( type == SOT_EFFECTCOMPONENT)
		{
			if ( isSub)
				return mSubEffectComponentFormatGroup->getFormat( name );
			else
				return mEffectComponentFormatGroup->getFormat( name );
		}

        return NULL;
    }
    //-----------------------------------------------------------------------
    void SceneXmlSerializer::removeSceneObjectFormat( ISceneObjectXmlFormat* format, Bool isDestroyEntity, Bool isSub )
    {
		removeSceneObjectFormat( format->getSceneObject()->getName().c_str(), format->getSceneObject()->getType(), isDestroyEntity, isSub );
    }
    //-----------------------------------------------------------------------
    void SceneXmlSerializer::removeSceneObjectFormat( CChar* name, SceneObjectTypes type, Bool isDestroyEntity, Bool isSub )
    {
        switch ( type )
        {
        case SOT_ENTITY:
            if ( isSub )
                mSubEntityFormatGroup->removeFormat( name );
            else
                mEntityFormatGroup->removeFormat( name );
            break;
        case SOT_TREE:
            if ( isSub )
            {

            }
            else
            {
                mTreeFormatGroup->removeFormat( name );
            }
            break;
		case SOT_GRASS:
			if ( isSub )
			{

			}
			else
			{
				mGrassFormatGroup->removeFormat( name );
			}
			break;
		//case SOT_EFFECTENTITY:
		//	if ( isSub )
		//	{
		//		mEffectEntityFormatGroup->removeFormat(name);
		//	}
		//	else
		//	{
		//		mEffectEntityFormatGroup->removeFormat( name );
		//	}
		// CN_MODIFY
		case SOT_EFFECTCOMPONENT:
			if ( isSub )
			{
				mEffectComponentFormatGroup->removeFormat(name);
			}
			else
			{
				mEffectComponentFormatGroup->removeFormat(name);
			}
        }
		if ( isDestroyEntity )
		{
			mScene->destroySceneObject( name, type );
		}
    }
    //-----------------------------------------------------------------------
    void SceneXmlSerializer::getSceneObjectXmlFormatList( SceneObjectTypes type, std::vector<ISceneObjectXmlFormat*>& formatList, Bool isSub ) 
    {
		if ( type == SOT_ENTITY )
		{
            if ( isSub )
                mSubEntityFormatGroup->getFormatList( formatList );
            else
                mEntityFormatGroup->getFormatList( formatList );
		}
		else if ( type == SOT_TREE )
        {
            if ( isSub )
            {

            }
            else
            {
                mTreeFormatGroup->getFormatList( formatList );
            }
        }else
		if (type == SOT_GRASS )
		{
			if ( isSub )
			{
			}
			else
			{
				mGrassFormatGroup->getFormatList( formatList );
			}
		}
		//else if ( type == SOT_EFFECTENTITY )
		//{
		//	if ( isSub )
		//	{
		//		mSubEffectEntityFormatGroup->getFormatList(formatList);
		//	}
		//	else
		//	{
		//		mEffectEntityFormatGroup->getFormatList( formatList );
		//	}
		//}
		// CN_MODIFY
		else if ( type == SOT_EFFECTCOMPONENT)
		{
			if ( isSub )
			{
				mSubEffectComponentFormatGroup->getFormatList(formatList);
			}
			else
			{
				mEffectComponentFormatGroup->getFormatList(formatList);
			}
		}
    }
	/******************************************************************************/
    //TerrainXmlFormat
    /******************************************************************************/

	void TerrainXmlFormat::fillTerrainChunkDeclare(XMLElement * elm, const TerrainDeclare& decl)
	{
		/////////////////////////////////////////////////////////////////

		XmlHelper::setAttribute( elm, decl.gridSideNumInChunk, "GridSideNumInChunk" );
		XmlHelper::setAttribute( elm, decl.gridSideNumInBatch, "GridSideNumInBatch" );
		XmlHelper::setAttribute( elm, decl.gridSize, "GridSize" );
		XmlHelper::setAttribute( elm, decl.lightingMapSize, "LightingMapSize" );
		XmlHelper::setAttribute( elm, (Int)decl.groundMatType, "GroundMaterialType" );

		/////////////////////////////////////////////////////////////////

		UInt count  = decl.trunkIndexList.size();

		for ( UInt index = 0; index < count; index++ )
		{
			VecI2 groupIndex = decl.trunkIndexList[index];

			{	
				XMLElement* chunkElm = XmlHelper::addChild(elm, "TerrainChunk", false);

				XmlHelper::setAttribute( chunkElm, (Int)groupIndex.x, "x");
				XmlHelper::setAttribute( chunkElm, (Int)groupIndex.y, "y");

				//如果是创建新地图的话，取填写值。
				TerrainChunkDeclare chunkDecl = decl.chunkDecl;

				//如果一个grid的边长是n米， 那么blendMap的分辨率也向上提升n倍
				chunkDecl.blendMapSizeInTile *= decl.gridSize;

				XmlHelper::setAttribute( chunkElm, chunkDecl.blendMapSizeInTile, "BlendMapSizeInTile" );
				XmlHelper::setAttribute( chunkElm, chunkDecl.gridSideNumInTile, "GridSideNumInTile"  );
				XmlHelper::setAttribute( chunkElm, chunkDecl.gridSideNumInNode, "GridSideNumInNode"  );
			}
		}

		/////////////////////////////////////////////////////////////////
	}
   
	void TerrainXmlFormat::fillTerrainChunkDeclare(XMLElement * elm, Scene* scene )
	{
		TerrainDeclare& decl = scene->getTerrainManager()->getConfig();
		TerrainChunkDeclare& chunkDecl = decl.chunkDecl;

		/////////////////////////////////////////////////////////////////

		XmlHelper::setAttribute( elm, decl.gridSideNumInChunk, "GridSideNumInChunk" );
		XmlHelper::setAttribute( elm, decl.gridSideNumInBatch, "GridSideNumInBatch" );
		XmlHelper::setAttribute( elm, decl.gridSize, "GridSize" );
		XmlHelper::setAttribute( elm, decl.lightingMapSize, "LightingMapSize" );
		XmlHelper::setAttribute( elm, (Int)decl.groundMatType, "GroundMaterialType" );
		
		/////////////////////////////////////////////////////////////////

		UInt count  = scene->getTerrainManager()->getTerrainChunkCount();

		for ( UInt index = 0; index < count; index++ )
		{
			TerrainChunk* chunk = scene->getTerrainManager()->getTerrainChunkByIndex(index);
			
			if ( chunk )
			{	
				XMLElement* chunkElm = XmlHelper::addChild(elm, "TerrainChunk", false);

				XmlHelper::setAttribute( chunkElm, (Int)chunk->getTerrainGroupIndex().x, "x");
				XmlHelper::setAttribute( chunkElm, (Int)chunk->getTerrainGroupIndex().y, "y");

				//XmlHelper::setAttribute( chunkElm, chunk->getTerrainChunkConfig().blendMapSizeInTile, "BlendMapSizeInTile" );
				//XmlHelper::setAttribute( chunkElm, chunk->getTerrainChunkConfig().gridSideNumInTile, "GridSideNumInTile"  );
				//XmlHelper::setAttribute( chunkElm, chunk->getTerrainChunkConfig().gridSideNumInNode, "GridSideNumInNode"  );
				XmlHelper::setAttribute( chunkElm, chunkDecl.blendMapSizeInTile, "BlendMapSizeInTile" );
				XmlHelper::setAttribute( chunkElm, chunkDecl.gridSideNumInTile, "GridSideNumInTile"  );
				XmlHelper::setAttribute( chunkElm, chunkDecl.gridSideNumInNode, "GridSideNumInNode"  );
			}
		}

		/////////////////////////////////////////////////////////////////
	}

    //-----------------------------------------------------------------------
    void TerrainXmlFormat::applyTerrainChunkDeclare(XMLElement * elm, Scene* scene)
    {
        TerrainDeclare& decl = scene->getTerrainManager()->getConfig();
		decl.trunkIndexList.clear();

        {
            Int num;
            if ( XmlHelper::getAttribute( elm, num, "GroundMaterialType" ) )
                decl.groundMatType = (TerrainGroundMaterialType)num; 
        }

        {
            Int num;
            if ( XmlHelper::getAttribute( elm, num, "GridSideNumInChunk" ) )
                decl.gridSideNumInChunk = num; 
        }

        {
            Int num;
            if ( XmlHelper::getAttribute( elm, num, "GridSideNumInBatch" ) )
                decl.gridSideNumInBatch = num; 
        }
        
        {
            Flt num;
            if ( XmlHelper::getAttribute( elm, num, "GridSize" ) )
                decl.gridSize = num; 
        }
        {
            Flt num;
            if ( XmlHelper::getAttribute( elm, num, "LightingMapSize" ) )
                decl.lightingMapSize = num; 
        }
 
        /////////////////////////////////////////////////////////////////

        TerrainManager* terrainMgr = scene->getTerrainManager();
        terrainMgr->destroyAllTerrainChunk();

        /////////////////////////////////////////////////////////////////

        XMLNode* parentNode       = elm;
        XMLNode* currNode         = parentNode->FirstChild();
        XMLNode* firstSiblingNode = currNode;
        XMLNode* nextNode         = NULL;

        TerrainChunkDeclare chunkDecl = decl.chunkDecl;
		Int     gridSideNumInNode; 
        Int     gridSideNumInTile; 
        Int     blendMapSizeInTile;

		Int     x,y;
		
        while( currNode )
        {
            //TODO:
            std::string formatType = XML_GET_VALUE(currNode);

            Bool isValid = true;

            if (formatType == "TerrainChunk")
            {
                if ( XmlHelper::getAttribute( currNode->ToElement(), x, "x" ) == false )
                    isValid = false;

                if ( XmlHelper::getAttribute( currNode->ToElement(), y, "y" ) == false )
                    isValid = false;

				decl.trunkIndexList.push_back(VecI2(x,y));
                

                if ( XmlHelper::getAttribute( currNode->ToElement(), blendMapSizeInTile, "BlendMapSizeInTile" ) == false )
				{
					blendMapSizeInTile = decl.gridSideNumInChunk;
				}

				if ( XmlHelper::getAttribute( currNode->ToElement(), gridSideNumInTile, "GridSideNumInTile" ) == false )
				{
					gridSideNumInTile = decl.gridSideNumInChunk;
				}

				if ( XmlHelper::getAttribute( currNode->ToElement(), gridSideNumInNode, "GridSideNumInNode" ) == false )
				{
					gridSideNumInNode = gridSideNumInTile;
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				//合法性检测
				if ( decl.gridSideNumInChunk < gridSideNumInNode )
				{
					MG_MESSAGE("GridSideNumInChunk must be more than or equal to GridSideNumInNode!");
					gridSideNumInNode = decl.gridSideNumInChunk;
				}

				if ( decl.gridSideNumInChunk < gridSideNumInTile )
				{
					MG_MESSAGE("GridSideNumInTile must be more than or equal to GridSideNumInNode!");
					gridSideNumInTile = decl.gridSideNumInChunk;
				}
	
				////////////////////////////////////////////////////////////////////////////////////////////////////////////

                if ( isValid )
                {
					chunkDecl.gridSideNumInNode     = gridSideNumInNode;
                    chunkDecl.gridSideNumInTile     = gridSideNumInTile;
                    chunkDecl.blendMapSizeInTile    = blendMapSizeInTile;
					
					terrainMgr->createTerrainChunk( x, y, chunkDecl );
                }
            }

            //@ parallel 
            nextNode    = currNode->NextSibling();
            if (nextNode&&nextNode==firstSiblingNode)
            {
                break;
            }
            currNode = nextNode;
        }
		decl.chunkDecl = chunkDecl;

    }

    //-----------------------------------------------------------------------
    void TerrainXmlFormat::fillTerrainHeightDeclare(XMLElement * elm, Scene* scene)
    {
        TerrainDeclare& decl = scene->getTerrainManager()->getConfig();

        XmlHelper::setAttribute( elm, decl.heightScale, "HeightScale" );
        XmlHelper::setAttribute( elm, decl.minHeight, "MinHeight" );
        XmlHelper::setAttribute( elm, decl.maxHeight, "MaxHeight" );
    }

    //-----------------------------------------------------------------------
    void TerrainXmlFormat::applyTerrainHeightDeclare(XMLElement * elm, Scene* scene)
    {
        TerrainDeclare& decl = scene->getTerrainManager()->getConfig();

        {
            Flt num;
            if ( XmlHelper::getAttribute( elm, num, "HeightScale" ) )
                decl.heightScale = num; 
        }

        {
            Flt num;
            if ( XmlHelper::getAttribute( elm, num, "MinHeight" ) )
                decl.minHeight = num; 
        }
        {
            Flt num;
            if ( XmlHelper::getAttribute( elm, num, "MaxHeight" ) )
                decl.maxHeight = num; 
        }
 
    }

    //-----------------------------------------------------------------------
    void TerrainXmlFormat::fillTerrainRegionDeclare(XMLElement * elm, Scene* scene)
    {
        Int num = scene->getTerrainManager()->getTerrainRegionManager()->getCustomRegionCount();
        XmlHelper::setAttribute( elm, num, "CustomRegionCount" );
    }

    //-----------------------------------------------------------------------
    void TerrainXmlFormat::applyTerrainRegionDeclare(XMLElement * elm, Scene* scene)
    {
        {
            Int num = 0;
            if ( XmlHelper::getAttribute( elm, num, "CustomRegionCount" ) )
            {
                for ( Int i=0; i < num; i++ )
                {
                    scene->getTerrainManager()->getTerrainRegionManager()->addCustomRegion();
                }
            }
        }
    }


    //-----------------------------------------------------------------------
    void TerrainXmlFormat::fillTerrainGlobleTextureLayerList(XMLElement * elm, Scene* scene)
    {
        TerrainSurfaceManager* surfaceMgr = scene->getTerrainManager()->getTerrainSurfaceManager();

        elm->DeleteChildren();

        /////////////////////////////////////////////////////////////////

        UInt count = surfaceMgr->getGlobleTextureLayerMaxCount();

        for ( UInt i=0; i<count; i++ )
        {
            TerrainTextureLayerDeclaration* decl = surfaceMgr->getGlobleTextureLayer( i );

            if (decl)
            {
                XMLElement* newElm = XmlHelper::addChild(elm, "TextureLayer", false);
            
                XmlHelper::setAttribute( newElm, Int(i), "index" );
                XmlHelper::setAttribute( newElm, Str(decl->name), "name" );
            }
        }
    }

    //-----------------------------------------------------------------------
    void TerrainXmlFormat::applyTerrainGlobleTextureList(XMLElement * elm, Scene* scene)
    {
        TerrainSurfaceManager* surfaceMgr = scene->getTerrainManager()->getTerrainSurfaceManager();
        surfaceMgr->clearGlobleTextureLayer();

        /////////////////////////////////////////////////////////////////

        Flt     num = 0;
        Int     layerIndex;
        Str8    layerName;

        XMLNode* parentNode       = elm;
        XMLNode* currNode         = parentNode->FirstChild();
        XMLNode* firstSiblingNode = currNode;
        XMLNode* nextNode         = NULL;
        
        while( currNode )
        {
          //TODO:
          std::string formatType = XML_GET_VALUE(currNode);

          Bool isValid = true;

          if (formatType == "TextureLayer")
          {
              if ( XmlHelper::getAttribute( currNode->ToElement(), layerIndex, "index" ) == false )
                  isValid = false; 

              if ( XmlHelper::getAttribute( currNode->ToElement(), layerName, "name" ) == false )
                  isValid = false; 

              if ( isValid )
              {
                  surfaceMgr->addGlobleTextureLayer( layerIndex,layerName );
              }
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

    //-----------------------------------------------------------------------
    void TerrainXmlFormat::fillTerrainGlobleWaterGroupList(XMLElement * elm, Scene* scene)
    {
        TerrainSurfaceManager* surfaceMgr = scene->getTerrainManager()->getTerrainSurfaceManager();

        elm->DeleteChildren();

        /////////////////////////////////////////////////////////////////

        UInt count = surfaceMgr->getGlobleWaterGroupMaxCount();

        for ( UInt i=0; i<count; i++ )
        {
            TerrainWaterGroupDeclaration* decl = surfaceMgr->getGlobleWaterGroup( i );

            if (decl)
            {
                XMLElement* newElm = XmlHelper::addChild(elm, "WaterGroup", false);

               
                XmlHelper::setAttribute( newElm, Int(decl->groupID), "groupID" );
                XmlHelper::setAttribute( newElm, Int(decl->wMatID), "waterMaterialID" );

                
                Vec3 reflectPostion = decl->reflectPostion;
                Vec3XmlFormat::save(newElm, "reflectPostion", reflectPostion);

                Vec3 reflectDirection = decl->reflectDirection;
                Vec3XmlFormat::save(newElm, "reflectDirection", reflectDirection);
            }
        }

    }

    //-----------------------------------------------------------------------
    void TerrainXmlFormat::applyTerrainGlobleWaterGroupList(XMLElement * elm, Scene* scene)
    {
        TerrainSurfaceManager* surfaceMgr = scene->getTerrainManager()->getTerrainSurfaceManager();
        surfaceMgr->clearGlobleWaterGroups();

        /////////////////////////////////////////////////////////////////

        Flt     num = 0;
        Int     groupID;
        Int     wMatID;
        Vec3    reflectPostion;
        Vec3    reflectDirection;

        XMLNode* parentNode       = elm;
        XMLNode* currNode         = parentNode->FirstChild();
        XMLNode* firstSiblingNode = currNode;
        XMLNode* nextNode         = NULL;

        while( currNode )
        {
            //TODO:
            std::string formatType = XML_GET_VALUE(currNode);

            Bool isValid = true;

            if (formatType == "WaterGroup")
            {
                if ( XmlHelper::getAttribute( currNode->ToElement(), groupID, "groupID" ) == false )
                    isValid = false; 

                if ( XmlHelper::getAttribute( currNode->ToElement(), wMatID, "waterMaterialID" ) == false )
                    isValid = false; 

                if ( Vec3XmlFormat::load(currNode->ToElement(), "reflectPostion", reflectPostion) == false )
                    isValid = false; 

                if ( Vec3XmlFormat::load(currNode->ToElement(), "reflectDirection", reflectDirection) == false )
                    isValid = false; 

                if ( isValid )
                {
                    TerrainWaterGroupDeclaration* decl = surfaceMgr->addGlobleWaterGroup( groupID );
                    decl->groupID = groupID;
                    decl->wMatID = wMatID;
                    decl->reflectPostion = reflectPostion;
                    decl->reflectDirection = reflectDirection;
                }
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

    /******************************************************************************/
    //CameraXmlFormat
    /******************************************************************************/
    CameraXmlFormat::CameraXmlFormat(Scene* scene, XMLElement * elm, Camera* cam)
        :mScene(scene)
        ,mCamera(cam)
    {
        mXmlElm = elm;
    }
    //-----------------------------------------------------------------------
    CameraXmlFormat::~CameraXmlFormat()
    {

    }
    //-----------------------------------------------------------------------
    void CameraXmlFormat::fill()
    {
        if (mCamera&&mXmlElm)
        {
            Str8 name = mCamera->getName();
            XmlHelper::setAttribute( mXmlElm, name, "Name" );
       
            Flt fov = mCamera->getFov();
            XmlHelper::setAttribute( mXmlElm, fov, "Fov" );

            //Vec3 pos ;
            //mCamera->getPosition(pos);
            //Vec3XmlFormat::save(mXmlElm, "Position", pos);

            //Vec3 dir;
            //mCamera->getDirection(dir);
            //Vec3XmlFormat::save(mXmlElm, "Direction", dir);
        }
    }
    //-----------------------------------------------------------------------
    void CameraXmlFormat::apply(Bool isCheckDirty)
    {
        if (mXmlElm)
        {
            mCamera = CameraXmlFormat::apply(mScene, mXmlElm, mCamera, isCheckDirty);
        }
    }
    //-----------------------------------------------------------------------
    Camera* CameraXmlFormat::apply(Scene* scene, XMLElement * elm, Camera* cam, Bool isCheckDirty)
    {
        Str8 name;
        XmlHelper::getAttribute( elm, name, "Name" );

        if ( cam == NULL )
        {
            cam = scene->createCamera( name.c_str() );
        }	

        Flt fov;
        if ( XmlHelper::getAttribute( elm, fov, "Fov" ) )
        {
            cam->setFov(fov);
        }
        
        cam->setPosition(Vec3(0,20,0));
        cam->focusPosition(Vec3(0,0,0));

		if (scene != NULL)
		{
			Flt farClip = cam->getOgreCamera()->getFarClipDistance();
			scene->getTreeManager()->setFarClipDistance(farClip);
		}
		
        //Vec3 pos;
        //if ( Vec3XmlFormat::load(elm, "Position", pos) )
        //    cam->setPosition(pos);

        //Vec3 dir;
        //if ( Vec3XmlFormat::load(elm, "Direction", dir) )
        //    cam->setDirection(dir);

        return cam;
    }

	/******************************************************************************/
	//EnvironmentXmlFormat
	/******************************************************************************/
	SpeedTreeEnvXmlFormat::SpeedTreeEnvXmlFormat(Scene* scene, XMLElement * elm)
		:mScene(scene)
	{
		mXmlElm = elm;
	}

	//-----------------------------------------------------------------------
	SpeedTreeEnvXmlFormat::~SpeedTreeEnvXmlFormat()
	{

	}

	//-----------------------------------------------------------------------
	void SpeedTreeEnvXmlFormat::fill()
	{
		if (mXmlElm)
		{
			////////////////////////////////////////////////////////////////////

			//Speed tree system 
			ITreeManager* speedTreeManager = mScene->getTreeManager();

			if ( speedTreeManager )
			{
				Vec3 dir = speedTreeManager->getGlobalWindDirection();
				Vec3XmlFormat::save(mXmlElm, "TreeWindDirection", dir);

				Vec2 grassLod;
				speedTreeManager->getGrassLod(grassLod.x, grassLod.y);
				XMLElement* elm = XmlHelper::addChild(mXmlElm,"GrassLod");
				XmlHelper::setAttribute(elm,grassLod.x,"start");
				XmlHelper::setAttribute(elm,grassLod.y,"end");

				Flt intensity = speedTreeManager->getGlobalWindStrength();
				XmlHelper::setAttribute(mXmlElm, intensity, "TreeWindIntensity");
			}

			////////////////////////////////////////////////////////////////////

		}
	}

	//-----------------------------------------------------------------------
	void SpeedTreeEnvXmlFormat::apply(Bool isCheckDirty)
	{
		if (mXmlElm)
		{
			SpeedTreeEnvXmlFormat::apply(mScene, mXmlElm, isCheckDirty);
		}
	}

	//-----------------------------------------------------------------------
	void SpeedTreeEnvXmlFormat::apply(Scene* scene, XMLElement * elm, Bool isCheckDirty)
	{
		/*
		apply plant
		*/

		ITreeManager* speedTreeManager = NULL;

		if ( scene )
			speedTreeManager = scene->getTreeManager();

		if ( speedTreeManager )
		{
			////////////////////////////////////////////////////////////////////

			//Global wind direction
			Vec3 dir = speedTreeManager->getGlobalWindDirection();
			Vec3XmlFormat::load( elm, "TreeWindDirection", dir );
			speedTreeManager->setGlobalWindDirection(dir);

			Vec2 grassLod(100.f, 200.f);
			XMLElement* childElm = XmlHelper::getChild(elm,"GrassLod");
			XmlHelper::getAttribute(childElm,grassLod.x,"start");
			XmlHelper::getAttribute(childElm,grassLod.y,"end");
			speedTreeManager->setGrassLod(grassLod.x,grassLod.y);

			//Global wind intensity
			Flt	intensity = speedTreeManager->getGlobalWindStrength();
			XmlHelper::getAttribute( elm, intensity, "TreeWindIntensity" );
			speedTreeManager->setGlobalWindStrength(intensity);
		}

	}

	/******************************************************************************/
	//NodeTrackXmlFormat
	/******************************************************************************/

	void NodeTrackXmlFormat::applyNodeTrackAnimations(Scene* scene, XMLElement * elm, Bool isCheckDirty)
	{
		if ( elm )
		{
			XMLElement* childElement = NULL;

			while ( childElement = XmlHelper::IterateChildElements(elm, childElement) )
			{
				Str formatType = XML_GET_VALUE( childElement );

				if ( formatType.compare("animation") == 0 )
				{
					applyNodeTrackAnimation( scene, childElement, isCheckDirty );
				}
			}
		}
	}

	//-----------------------------------------------------------------------
	void NodeTrackXmlFormat::applyNodeTrackAnimation(Scene* scene, XMLElement * elm, Bool isCheckDirty)
	{
		if ( elm )
		{
			Str8 name;
			Str8 enable;
			Str8 isloop;

			///////////////////////////////////////////////////////////////////////////////////////////

			//Animation name
			XmlHelper::getAttribute( elm, name, "name" );

			//Get enabled and looping states
			XmlHelper::getAttribute( elm, enable, "enable" );
			XmlHelper::getAttribute( elm, isloop, "loop");

			MGStrOp::makeLower(enable);
			MGStrOp::makeLower(isloop);

			//Return if animation exist
			if ( scene->getOgreSceneManager()->hasAnimation( name ) )
				return;

			///////////////////////////////////////////////////////////////////////////////////////////

			//Length
			Flt length = 0.0f;
			XmlHelper::getAttribute(elm, length, "length");

			//Interpolation mode
			Str8 interpolationModeText;
			XmlHelper::getAttribute(elm, interpolationModeText, "interpolationMode");

			Animation::InterpolationMode interpolationMode = Animation::IM_LINEAR;
			MGStrOp::makeLower(interpolationModeText);
			if (interpolationModeText == "spline")
				interpolationMode = Animation::IM_SPLINE;

			//rotationInterpolation mode
			Str8 rotationInterpolationModeText;
			XmlHelper::getAttribute(elm, rotationInterpolationModeText, "rotationInterpolationMode");

			Animation::RotationInterpolationMode rotationInterpolationMode = Animation::RIM_LINEAR;
			MGStrOp::makeLower(rotationInterpolationModeText);
			if (rotationInterpolationModeText == "spherical")
				rotationInterpolationMode = Animation::RIM_SPHERICAL;

			//Create animation
			Animation* animation = scene->getOgreSceneManager()->createAnimation(name, length);
			animation->setInterpolationMode(interpolationMode);
			animation->setRotationInterpolationMode(rotationInterpolationMode);

			///////////////////////////////////////////////////////////////////////////////////////////

			//Create animation track for node
			NodeAnimationTrack* animationTrack = animation->createNodeTrack(1);
			if ( animationTrack )
			{
				//Load animation keyframes
				Str8 elementName;
				XMLElement* childElement = NULL;
				while (childElement = XmlHelper::IterateChildElements(elm, childElement))
				{
					elementName = XML_GET_VALUE(childElement);

					if (elementName == "keyframe")
					{
						Flt keyTime = 0.0f;
						XmlHelper::getAttribute(childElement, keyTime, "time");

						Vec3 translate;
						Vec3XmlFormat2::load( childElement, "translation",translate );

						Qua rotation;
						QuaXmlFormat::load( childElement, "rotation", rotation );

						Vec3 scale;
						Vec3XmlFormat2::load( childElement, "scale",scale );

						//Create the key frame
						TransformKeyFrame* keyFrame = animationTrack->createNodeKeyFrame(keyTime);

						keyFrame->setTranslate(Ogre::Vector3(translate.x, translate.y, translate.z));
						keyFrame->setRotation(Ogre::Quaternion(rotation.w, rotation.x, rotation.y, rotation.z));
						keyFrame->setScale(Ogre::Vector3(scale.x, scale.y, scale.z));
					}
				}
			}

			///////////////////////////////////////////////////////////////////////////////////////////
		}
	}

    /******************************************************************************/
    //EnvironmentXmlFormat
    /******************************************************************************/
    EnvironmentXmlFormat::EnvironmentXmlFormat(Scene* scene, XMLElement * elm)
        :mScene(scene)
    {
        mXmlElm = elm;
    }

    //-----------------------------------------------------------------------
    EnvironmentXmlFormat::~EnvironmentXmlFormat()
    {

    }

    //-----------------------------------------------------------------------
    void EnvironmentXmlFormat::fill()
    {
        if (mXmlElm)
        {
            Vector3 ogreVec3;
            ColourValue ogreColor;

            //ambient
            ogreColor = mScene->getOgreSceneManager()->getAmbientLight();
            Color ambient = Color(ogreColor.r,ogreColor.g,ogreColor.b,ogreColor.a);
            ColorXmlFormat::save(mXmlElm, "AmbientColor", ambient);
            
            ILight* light = mScene->getDefaultLight();

            //LightDirection
            Vec3 lightDir = light->getDirection();
            Vec3XmlFormat::save(mXmlElm, "LightDirection", lightDir);

            //LightDiffuseColour
            Color diffuseColour = light->getDiffuseColour();
            ColorXmlFormat::save(mXmlElm, "LightDiffuseColour", diffuseColour);
      
            //LightSpecularColour
            Color specularColour = light->getSpecularColour();
            ColorXmlFormat::save(mXmlElm, "LightSpecularColour", specularColour);
            
            ////////////////////////////////////////////////////////////////////

            //FogColour
            Color fogColour = Display::getSingleton().getFogColor();
            ColorXmlFormat::save(mXmlElm, "FogColour", fogColour);

            //FogExpDensity
            Flt expExpDensity = Display::getSingleton().getFogExpDensity();
            XmlHelper::setAttribute( mXmlElm, expExpDensity, "FogExpDensity" );

            //FogLinearStart
            Flt linearStart = Display::getSingleton().getFogLinearStart();
            XmlHelper::setAttribute( mXmlElm, linearStart, "FogLinearStart" );

            //FogLinearEnd
            Flt linearEnd = Display::getSingleton().getFogLinearEnd();
            XmlHelper::setAttribute( mXmlElm, linearEnd, "FogLinearEnd" );

            ////////////////////////////////////////////////////////////////////

            //TerrainLightingParameter
            Vec4 tp = Display::getSingleton().getTerrainLightingParameter();
            Vec4XmlFormat::save(mXmlElm, "TerrainLightingParameter", tp);

            //ShadowParameter
            Vec4 sp = Display::getSingleton().getShadowParameter();
            Vec4XmlFormat::save(mXmlElm, "ShadowParameter", sp);

			////////////////////////////////////////////////////////////////////

			//Speed tree system 
			ITreeManager* speedTreeManager = mScene->getTreeManager();

			if ( speedTreeManager )
			{
				//wind
				Vec3 dir = speedTreeManager->getGlobalWindDirection();
				Vec3XmlFormat::save(mXmlElm, "TreeWindDirection", dir);

				Flt intensity = speedTreeManager->getGlobalWindStrength();
				XmlHelper::setAttribute(mXmlElm, intensity, "TreeWindDirection");

				WorldEnvironment env = speedTreeManager->getWorldEnv();
				//SpeedTree tree ambient
				ColorXmlFormat::save(mXmlElm, "STAmbient", env.cLightAmbient);

				//SpeedTree tree diffuse
				ColorXmlFormat::save(mXmlElm, "STDiffuse", env.cLightDiffuse);

				//SpeedTree tree specular
				ColorXmlFormat::save(mXmlElm, "STSpecular", env.cLightSpecular);

				//SpeedTree grass ambient
				ColorXmlFormat::save(mXmlElm, "SGAmbient", env.cGrassLightAmbient);

				//SpeedTree grassdiffuse
				ColorXmlFormat::save(mXmlElm, "SGDiffuse", env.cGrassLightDiffuse);

				//SpeedTree grassspecular
				ColorXmlFormat::save(mXmlElm, "SGSpecular", env.cGrassLightSpecular);
			}
		
        }
    }

    //-----------------------------------------------------------------------
    void EnvironmentXmlFormat::apply(Bool isCheckDirty)
    {
        if (mXmlElm)
        {
            EnvironmentXmlFormat::apply(mScene, mXmlElm, isCheckDirty);
        }
    }

    //-----------------------------------------------------------------------
    void EnvironmentXmlFormat::apply(Scene* scene, XMLElement * elm, Bool isCheckDirty)
    {
		WorldEnvironment worldEnv;
		/*
			apply light
		*/
        Color ambient;
        if ( ColorXmlFormat::load(elm, "AmbientColor", ambient) )
        {
            scene->setAmbientLight(ambient);
        }
		else
        {
			ambient = Color(0.2,0.2,0.2,1);
            scene->setAmbientLight(ambient);
        }

        MG::ILight* light = scene->getDefaultLight();
 
        if ( light )
        {
            //LightDirection
            Vec3 lightDir;
            if ( Vec3XmlFormat::load(elm, "LightDirection", lightDir) )
            {
                light->setDirection(lightDir);
            }else
            {
				lightDir = Vec3(0.55f,-0.3f,0.75f);
                light->setDirection(lightDir);
            }
			worldEnv.vLightDir = lightDir;

            //LightDiffuseColour
            Color diffuseColour;
            if ( ColorXmlFormat::load(elm, "LightDiffuseColour", diffuseColour) )
            {
                light->setDiffuseColour(diffuseColour);
            }else
            {
				diffuseColour = Color(1,1,1,1);
                light->setDiffuseColour(diffuseColour);
            }

            //LightSpecularColour
            Color speculaColour;
            if ( ColorXmlFormat::load(elm, "LightSpecularColour", speculaColour) )
            {
                light->setSpecularColour(speculaColour);
            }else
            {
				speculaColour = Color(0.4,0.4,0.4,1);
                light->setSpecularColour(speculaColour);
            }
        }

		/*
			apply Fog
		*/
        {
            ////////////////////////////////////////////////////////////////////

            //FogColor
            Color fogColour = Display::getSingleton().getFogColor();
            ColorXmlFormat::load(elm, "FogColour", fogColour);
			worldEnv.cFogColor = fogColour;

            //FogExpDensity
            Flt expExpDensity = Display::getSingleton().getFogExpDensity();
            XmlHelper::getAttribute( elm, expExpDensity, "FogExpDensity" );
			
            //FogLinearStart
            Flt linearStart = Display::getSingleton().getFogLinearStart();
            XmlHelper::getAttribute( elm, linearStart, "FogLinearStart" );
			worldEnv.fFogStart = linearStart;

            //FogLinearEnd
            Flt linearEnd = Display::getSingleton().getFogLinearEnd();
            XmlHelper::getAttribute( elm, linearEnd, "FogLinearEnd" );
			worldEnv.fFogEnd = linearEnd;

            FogLevel fogLevel = Display::getSingleton().getFogLevel();
            Display::getSingleton().setFogLevel( fogLevel, fogColour, expExpDensity, linearStart, linearEnd);
        }

		/*
			apply Terrain
		*/
        {
			////////////////////////////////////////////////////////////////////

            //TerrainLightingParameter
            Vec4 tp = Display::getSingleton().getTerrainLightingParameter();
            Vec4XmlFormat::load( elm, "TerrainLightingParameter" , tp );
            Display::getSingleton().setTerrainLightingParameter(tp);
          
            //ShadowParameter
            Vec4 sp = Display::getSingleton().getShadowParameter();
            Vec4XmlFormat::load( elm, "ShadowParameter", sp );
            Display::getSingleton().setShadowParameter(sp);
        }

		/*
			apply plant
		*/

		ITreeManager* speedTreeManager = NULL;

		if ( scene )
			speedTreeManager = scene->getTreeManager();

		if ( speedTreeManager )
		{
			////////////////////////////////////////////////////////////////////

			//Global wind direction
			Vec3 dir = speedTreeManager->getGlobalWindDirection();
			Vec3XmlFormat::load( elm, "TreeWindDirection", dir );
			speedTreeManager->setGlobalWindDirection(dir);
			
			//Global wind intensity
			Flt	intensity = speedTreeManager->getGlobalWindStrength();
			XmlHelper::getAttribute( elm, intensity, "TreeWindIntensity" );
			speedTreeManager->setGlobalWindStrength(intensity);

			WorldEnvironment env = speedTreeManager->getWorldEnv();
			env.vLightDir = worldEnv.vLightDir;
			env.cFogColor = worldEnv.cFogColor;
			env.fFogStart = worldEnv.fFogStart;
			env.fFogEnd = worldEnv.fFogEnd;
			//SpeedTree tree Ambient light
			ColorXmlFormat::load(elm, "STAmbient", env.cLightAmbient);

			//SpeedTree tree diffuse light
			ColorXmlFormat::load(elm, "STDiffuse", env.cLightDiffuse);

			//SpeedTree tree Specular light
			ColorXmlFormat::load(elm, "STSpecular", env.cLightSpecular);

			//SpeedTree grass Ambient light
			ColorXmlFormat::load(elm, "SGAmbient", env.cGrassLightAmbient);

			//SpeedTree grass diffuse light
			ColorXmlFormat::load(elm, "SGDiffuse", env.cGrassLightDiffuse);

			//SpeedTree grass Specular light
			ColorXmlFormat::load(elm, "SGSpecular", env.cGrassLightSpecular);

			speedTreeManager->setWorldEnv(env);
		}
        
        //创建天空
        //scene->getOgreSceneManager()->setSkyDome(true, "MG/Dome/CloudySky");
        //scene->getOgreSceneManager()->setSkyDome(true, "Examples/CloudySky");
        //scene->getOgreSceneManager()->setSkyPlane(true, Plane(0, -1, 0, 200), "MG/Dome/CloudySky", 5000, 500, true , 0.2, 10, 10);
		//Examples/SpaceSkyPlane
        //scene->getOgreSceneManager()->setSkyBox(true, "MG/Box/CloudySky");
    }

    /******************************************************************************/
    //EntityXmlFormat
    /******************************************************************************/

    UInt EntityXmlFormat::applyIndex = 0;
    UInt EntityXmlFormat::applyTotal = 0;

    EntityXmlFormat::EntityXmlFormat( Scene* scene, XMLElement * elm, Entity* entity )
        :mScene(scene)
        ,mEntity(entity)
    {
		mXmlElm = elm;
    }
    //-----------------------------------------------------------------------
    EntityXmlFormat::~EntityXmlFormat()
    {
        
    }
    //-----------------------------------------------------------------------
	void EntityXmlFormat::fill()
    {
        if (mEntity&&mXmlElm)
		{
            // 组
            Str8 groupName = mEntity->getGroup();
            XmlHelper::setAttribute( mXmlElm, groupName, "Group" );

            //名字
			Str8 name = mEntity->getName();
			XmlHelper::setAttribute( mXmlElm, name, "Name" );

            //模型模板名
			U32 modelDeclID = mEntity->getModelObject()->getModelDeclarationID();
			XmlHelper::setAttribute( mXmlElm, modelDeclID, "ModelDeclID" );

            //设置批次处理类型
            Str8 batchGroup = mEntity->getDeclaration().batchGroup;
            XmlHelper::setAttribute( mXmlElm, batchGroup, "BatchGroup" ); 
            
            //设置是否加载在游戏中
            Int isLoadWhenGame = mEntity->getDeclaration().isLoadWhenGame ? 1 : 0;
            XmlHelper::setAttribute( mXmlElm, isLoadWhenGame, "IsLoadWhenGame" ); 

            //---------------------------------------------------------

            // 位置
			Vec3 pos ;
			mEntity->getSceneNode()->getPosition(pos);
			Vec3XmlFormat::save(mXmlElm, "Position", pos);

            // 朝向
			Qua orientation;
			mEntity->getSceneNode()->getOrientation(orientation);
			Vec4XmlFormat::save(mXmlElm, "Orientation", Vec4(orientation.w,orientation.x,orientation.y,orientation.z) );

            //缩放
			Vec3 scale;
			mEntity->getSceneNode()->getScale(scale);
			Vec3XmlFormat::save(mXmlElm, "Scale", scale);

            //可见度
            {
                XMLElement* elm = XmlHelper::addChild( mXmlElm, "Visible" );
                {
                    if ( XmlHelper::hasAttribute( elm,"Value" ) == false )
                    {
                        XmlHelper::setAttribute( elm, "1", "Value" ); 
                    }
                }
            }

			//设置是否加载在某种类型的场景中
			{
				XMLElement* elm = XmlHelper::addChild( mXmlElm, "AppearParam" );
				{
					if ( XmlHelper::hasAttribute( elm,"Value" ) == false )
					{
						XmlHelper::setAttribute( elm, "0", "Value" ); 
					}
				}
			}

            //投射阴影
            {
                Int castShadowsType = (Int)mEntity->getModelObject()->getShadowCastType();
                XmlHelper::setAttribute( mXmlElm, castShadowsType, "CastShadowsType" );
            }

			//接受动态阴影
			{
				Int receiveDynamicShadows = (Int)mEntity->getModelObject()->getDynamicShadowReceiveEnable();
				XmlHelper::setAttribute( mXmlElm, receiveDynamicShadows, "ReceiveDynamicShadow" );
			}

			//接受静态阴影
			{
				Int receiveStaticShadows = (Int)mEntity->getModelObject()->getStaticShadowReceiveEnable();
				XmlHelper::setAttribute( mXmlElm, receiveStaticShadows, "ReceiveStaticShadow" );
			}

            //反射
            {
                Int reflectEnable = (Int)mEntity->getModelObject()->getReflectEnable();
                XmlHelper::setAttribute( mXmlElm, reflectEnable, "ReflectEnable" );
            }
            
            //折射
            {
                Int refractEnable = (Int)mEntity->getModelObject()->getRefractEnable();
                XmlHelper::setAttribute( mXmlElm, refractEnable, "RefractEnable" );
            }

            // 动画
            {
                XMLElement* elm = XmlHelper::addChild( mXmlElm, "Animation" );
                {
                    //设置动画
                    Str animation = mEntity->getDeclaration().autoAnimation;
                    XmlHelper::setAttribute( elm, animation, "Name" ); 
                }
            }

			// 自发光
			{
				XMLElement* elm = XmlHelper::addChild( mXmlElm, "Emissive" );
				{
					//设置动画
					Color color = mEntity->getModelObject()->getEmissive();
					
					XmlHelper::setAttribute( elm, color.r, "r" ); 
					XmlHelper::setAttribute( elm, color.g, "g" ); 
					XmlHelper::setAttribute( elm, color.b, "b" ); 
					XmlHelper::setAttribute( elm, color.a, "a" ); 
				}
			}

            //自定义参数
            {
                XMLElement* elm = XmlHelper::addChild( mXmlElm, "CustomAttrs" );
                {
                    elm->DeleteChildren();

                    std::map<Str,Str>& attrList = mEntity->getCustomAttrList();

                    std::map<Str,Str>::iterator iter = attrList.begin();
                    for ( ;iter!=attrList.end(); iter++)
                    {
                        Str strName  = iter->first;
                        Str strValue = iter->second;

                        XMLElement* newElm = XmlHelper::addChild(elm, strName, true);
                        XmlHelper::setAttribute( newElm, strValue, "Value" );
                    }
                }
            }
		}
    }
    //-----------------------------------------------------------------------
    void EntityXmlFormat::apply(Bool isCheckDirty)
    {
        if (mXmlElm)
		{
			mEntity = EntityXmlFormat::apply(mScene, mXmlElm, mEntity);
		}
    }
    //-----------------------------------------------------------------------
    Entity* EntityXmlFormat::apply(Scene* scene, XMLElement * elm, Entity* entity, Bool isCheckDirty)
    {
        ResourceLoadListener* listener = scene->getResourceLoadListener();

        if ( listener )
        {
			//U32 loadCount = EntityXmlFormat::applyIndex + EffectEntityXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			//U32 loadTotal = EntityXmlFormat::applyTotal + EffectEntityXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

			// CN_MODIFY
			U32 loadCount = EntityXmlFormat::applyIndex + EffectComponentXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			U32 loadTotal = EntityXmlFormat::applyTotal + EffectComponentXmlFormat::applyTotal + TreeXmlFormat::applyTotal;
			
			listener->preloadObject( loadCount, loadTotal);
        }


        ////////////////////////////////////////////////////////////////////////////////////////////////

        {
            //组名
            Str8 groupName;
            if ( XmlHelper::getAttribute( elm, groupName, "Group" ) )
            {
                if ( scene->getXmlSerializer()->isIgnoreLoadGroup( groupName ) )
                    return NULL;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////


        // 之后加载，先跳过	
        Int isLoadWhenGame;
        XmlHelper::getAttribute( elm, isLoadWhenGame, "IsLoadWhenGame" );
        
        if ( ( EngineMain::getInstance().getMode() != EM_EDITOR ) && ( isLoadWhenGame == false ) )
		{
			if ( listener )
			{
				EntityXmlFormat::applyIndex++;

				//U32 loadCount = EntityXmlFormat::applyIndex + EffectEntityXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
				//U32 loadTotal = EntityXmlFormat::applyTotal + EffectEntityXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

				// CN_MODIFY
				U32 loadCount = EntityXmlFormat::applyIndex + EffectComponentXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
				U32 loadTotal = EntityXmlFormat::applyTotal + EffectComponentXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

				listener->postloadObject( NULL, loadCount, loadTotal);
			}

            return NULL ;
		}
        
        ////////////////////////////////////////////////////////////////////////////////////////////////

        // 名字
		Str8 name;
		XmlHelper::getAttribute( elm, name, "Name" );

        // 模型编号
		U32 modelDeclID = 0;
		XmlHelper::getAttribute( elm, modelDeclID, "ModelDeclID" );

		// 那种类型的场景下加载
		Int appearMode = 0;
		XmlHelper::getAttribute( elm, appearMode, "AppearMode" );

        // 批次处理组
        Str8 batchGroup;
        XmlHelper::getAttribute( elm, batchGroup, "BatchGroup" );

        // 模型效果
        Int modelEffect = 0;
        XmlHelper::getAttribute( elm, modelEffect, "ModelEffect" );
        
        // 位置
		Vec3 pos = Vec3(0,0,0);
        Vec3XmlFormat::load(elm, "Position", pos);

        // 朝向
		Vec4 orientation = Vec4(1,0,0,0);
        Vec4XmlFormat::load(elm, "Orientation", orientation);

        // 缩放
		Vec3 scale = Vec3(1,1,1);
        Vec3XmlFormat::load(elm, "Scale", scale);
		  
        ////////////////////////////////////////////////////////////////////////////////////////////////

        StaticEntitySet* entitySet = NULL;

        // 创建实体
        if ( entity == NULL )
        {
            if ( (batchGroup.empty()==false) && 
                 (EngineMain::getInstance().getMode() != EM_EDITOR)
				)
            {
                if ( EngineMain::getInstance().display()->isDebugNoStaticEntity() ) 
                    return NULL;
                
                scene->addStaticEntity( modelDeclID, pos, Qua(orientation.w,orientation.x,orientation.y,orientation.z), scale, false, 
                    batchGroup, false );

                entitySet = scene->getStaticEntitySet( modelDeclID );
            }else
            {
                if ( EngineMain::getInstance().display()->isDebugNoEntity() ) 
                    return NULL;

				if ( scene->getEntity(name.c_str()) == NULL )
				{
					entity = scene->createEntity( name.c_str(), modelDeclID );
				}else
				{
					entity = scene->createEntity( modelDeclID, name.c_str() );
					name = entity->getName();
					XmlHelper::setAttribute( elm, name, "Name" );
				}
                scene->createEntityStaticAccessorys( entity, modelDeclID );

				ICollisionObject* collisionObject = entity->createOrRetrieveCollisionObject();
				if(collisionObject)
				{
					collisionObject->setEnable(true);
				}
            }
        }	

        ////////////////////////////////////////////////////////////////////////////////////////////////

        if ( entity )
        {
            // 设置基本参数
            entity->getSceneNode()->setPosition(pos);
            entity->getSceneNode()->setOrientation(Qua(orientation.w,orientation.x,orientation.y,orientation.z));
            entity->getSceneNode()->setScale(scale);

            // 设置声明
            entity->getDeclaration().batchGroup     = batchGroup;
            entity->getDeclaration().isLoadWhenGame = isLoadWhenGame;
			//entity->getDeclaration().appearMode		= appearMode;

            //组名
            Str8 groupName;
            if ( XmlHelper::getAttribute( elm, groupName, "Group" ) )
                entity->setGroup( groupName );

            //可见度
            {
                if ( EngineMain::getInstance().getMode() != EM_EDITOR )
                {
                    XMLElement* visbleAttrs = XmlHelper::getChild(elm, "Visible");
                    Int visible = 1;
                    if ( XmlHelper::getAttribute( visbleAttrs, visible, "Value" ) )
                    {
                        entity->getSceneNode()->setVisible(visible!=0);
                    }
                }
            }

            //动画
            {
                XMLElement* animAttrs = XmlHelper::getChild(elm, "Animation");
                Str8 animName;
                if ( XmlHelper::getAttribute( animAttrs, animName, "Name" ) )
                {
                    //TODO:
                    if ( animName.empty() == false )
                    {
                        entity->getAnimationController()->stopAll();

                        //entity->getAnimationController()->setIsIdle( true, "qiang_none_stand" );

                        //entity->getDeclaration().autoAnimation = animName;

						entity->getAnimationController()->play( animName.c_str() );

						entity->getDeclaration().autoAnimation = animName;
                    }
                }
            }

			// 测试换色
			{
				XMLElement* emissAttrs = XmlHelper::getChild(elm, "Emissive");
				if ( emissAttrs )
				{
					Color color;
					XmlHelper::getAttribute( emissAttrs, color.r, "r");
					XmlHelper::getAttribute( emissAttrs, color.g, "g");
					XmlHelper::getAttribute( emissAttrs, color.b, "b");
					XmlHelper::getAttribute( emissAttrs, color.a, "a");

					entity->getModelObject()->setEmissive(color, true);
				}		
			}

            // 自定义参数
            {
                XMLElement* customAttrs = XmlHelper::getChild(elm, "CustomAttrs");
                entity->clearCustomAttr();
                if (customAttrs)
                {
                    XMLNode* parentNode       = customAttrs;
                    XMLNode* currNode         = parentNode->FirstChild();
                    XMLNode* firstSiblingNode = currNode;
                    XMLNode* nextNode         = NULL;

                    while( currNode )
                    {
                        //TODO:
                        std::string formatType  = XML_GET_VALUE(currNode);
                        std::string attr        = XML_GET_ATTRIBUTE(currNode->ToElement(),"Value");

                        entity->setCustomAttr(formatType,attr);

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

        ////////////////////////////////////////////////////////////////////////////////////////////////

        OgreEntityWrapper* modelObject = NULL;
        if ( entity )
        {
            modelObject = entity->getModelObject();
        }else
        if ( entitySet )
        {
            modelObject = entitySet->getModelObject();
        }
        
        if ( modelObject )
        {
            //投射阴影
            {
                Int castShadowsType = 1;
                XmlHelper::getAttribute( elm, castShadowsType, "CastShadowsType" );
                modelObject->setShadowCastType(ShadowCasterType(castShadowsType));
            }

            //接受动态阴影
            {
                Int receiveDynamicShadows = 0;
                XmlHelper::getAttribute( elm, receiveDynamicShadows, "ReceiveDynamicShadow" );
                modelObject->setDynamicShadowReceiveEnable(receiveDynamicShadows);
            }

            //接受静态阴影
            {
                Int receiveStaticShadows = 0;
                XmlHelper::getAttribute( elm, receiveStaticShadows, "ReceiveStaticShadow" );
                modelObject->setStaticShadowReceiveEnable(receiveStaticShadows);
            }

            //反射
            {
                Int reflectEnable = 0;
                XmlHelper::getAttribute( elm, reflectEnable, "ReflectEnable" );
                modelObject->setReflectEnable(reflectEnable);
            }

            //折射
            {
                Int refractEnable = 0;
                XmlHelper::getAttribute( elm, refractEnable, "RefractEnable" );
                modelObject->setRefractEnable(refractEnable);
            }

        }
        
        ////////////////////////////////////////////////////////////////////////////////////////////////

        if ( listener )
        {
			EntityXmlFormat::applyIndex ++;

			//U32 loadCount = EntityXmlFormat::applyIndex + EffectEntityXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			//U32 loadTotal = EntityXmlFormat::applyTotal + EffectEntityXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

			// CN_MODIFY
			U32 loadCount = EntityXmlFormat::applyIndex + EffectComponentXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			U32 loadTotal = EntityXmlFormat::applyTotal + EffectComponentXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

			listener->postloadObject( entity, loadCount, loadTotal);
        }

		return entity;
    }


    /******************************************************************************/
    //TreeXmlFormat
    /******************************************************************************/

    UInt TreeXmlFormat::applyIndex = 0;
    UInt TreeXmlFormat::applyTotal = 0;

    //-----------------------------------------------------------------------
    TreeXmlFormat::TreeXmlFormat(Scene* scene, XMLElement * elm, Tree* tree)
        :mScene(scene)
        ,mTree(tree)
    {
        mXmlElm = elm;
        
    }

    //-----------------------------------------------------------------------
    TreeXmlFormat::~TreeXmlFormat()
    {
        
    }

    //-----------------------------------------------------------------------
    void TreeXmlFormat::fill()
    {
        if (mTree&&mXmlElm)
        {
            // 组
            Str8 groupName = mTree->getGroup();
            XmlHelper::setAttribute( mXmlElm, groupName, "Group" );

            //名字
            Str8 name = mTree->getName();
            XmlHelper::setAttribute( mXmlElm, name, "Name" );

            //模型模板名
            //TODO:
            U32 treeDeclID = mTree->getBaseTreeId();
            XmlHelper::setAttribute( mXmlElm, treeDeclID, "TreeDeclID" );

            //---------------------------------------------------------

            // 位置
            Vec3 pos ;
            mTree->getSceneNode()->getPosition(pos);
            Vec3XmlFormat::save(mXmlElm, "Position", pos);

            // 朝向
            Qua orientation;
            mTree->getSceneNode()->getOrientation(orientation);
            Vec4XmlFormat::save(mXmlElm, "Orientation", Vec4(orientation.w,orientation.x,orientation.y,orientation.z) );

            //缩放
            Vec3 scale;
            mTree->getSceneNode()->getScale(scale);
            Vec3XmlFormat::save(mXmlElm, "Scale", scale);

            //可见度
            {
                XMLElement* elm = XmlHelper::addChild( mXmlElm, "Visible" );
                {
                    if ( XmlHelper::hasAttribute( elm,"Value" ) == false )
                    {
                        XmlHelper::setAttribute( elm, "1", "Value" ); 
                    }
                }
            }

            //投射阴影
            {
                //TODO:
                Int castShadowsType = 2; 
                XmlHelper::setAttribute( mXmlElm, castShadowsType, "CastShadowsType" );
            }

            //接受动态阴影
            {
                //TODO:
                Int receiveDynamicShadows = 1;
                XmlHelper::setAttribute( mXmlElm, receiveDynamicShadows, "ReceiveDynamicShadow" );
            }

            //接受静态阴影
            {
                //TODO:
                Int receiveStaticShadows = 1;
                XmlHelper::setAttribute( mXmlElm, receiveStaticShadows, "ReceiveStaticShadow" );
            }

			//接受反射
			{
				Int receiveReflect = (Int)mTree->isNeedReflect();
				XmlHelper::setAttribute( mXmlElm, receiveReflect, "receiveReflect");
			}
            //自定义参数
            {
                XMLElement* elm = XmlHelper::addChild( mXmlElm, "CustomAttrs" );
                {
                    elm->DeleteChildren();

                    std::map<Str,Str>& attrList = mTree->getCustomAttrList();

                    std::map<Str,Str>::iterator iter = attrList.begin();
                    for ( ;iter!=attrList.end(); iter++)
                    {
                        Str strName  = iter->first;
                        Str strValue = iter->second;

                        XMLElement* newElm = XmlHelper::addChild(elm, strName, true);
                        XmlHelper::setAttribute( newElm, strValue, "Value" );
                    }
                }
            }
        }
    }

    //-----------------------------------------------------------------------
    ISceneObject* TreeXmlFormat::getSceneObject()
    {
        return mTree;
    }

    //-----------------------------------------------------------------------
    void TreeXmlFormat::apply(Bool isCheckDirty)
    {
        if (mXmlElm)
        {
            mTree = TreeXmlFormat::apply(mScene, mXmlElm, mTree);
        }
    }

    //-----------------------------------------------------------------------
    Tree* TreeXmlFormat::apply(Scene* scene, XMLElement * elm, Tree* tree, Bool isCheckDirty)
    {
        ResourceLoadListener* listener = scene->getResourceLoadListener();

        if ( listener )
        {
			//U32 loadCount = EntityXmlFormat::applyIndex + EffectEntityXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			//U32 loadTotal = EntityXmlFormat::applyTotal + EffectEntityXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

			// CN_MODIFY
			U32 loadCount = EntityXmlFormat::applyIndex + EffectComponentXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			U32 loadTotal = EntityXmlFormat::applyTotal + EffectComponentXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

			listener->preloadObject( loadCount, loadTotal );
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////

        // 名字
        Str8 name;
        XmlHelper::getAttribute( elm, name, "Name" );

        // 模型编号
        U32 treeDeclID = 0;
        XmlHelper::getAttribute( elm, treeDeclID, "TreeDeclID" );

        // 位置
        Vec3 pos = Vec3(0,0,0);
        Vec3XmlFormat::load(elm, "Position", pos);

        // 朝向
        Vec4 orientation = Vec4(1,0,0,0);
        Vec4XmlFormat::load(elm, "Orientation", orientation);

        // 缩放
        Vec3 scale = Vec3(1,1,1);
        Vec3XmlFormat::load(elm, "Scale", scale);

        ////////////////////////////////////////////////////////////////////////////////////////////////

        // 创建实体
        if ( tree == NULL )
        {
			if ( EngineMain::getInstance().getMode() == EM_EDITOR )
            {
                if ( scene->getTreeManager()->getTree(name.c_str()) == NULL )
                {
                    tree = scene->getTreeManager()->createTree( name.c_str(), treeDeclID, pos);
                }else
                {
                    tree = scene->getTreeManager()->createTree( treeDeclID, pos);
                    name = tree->getName();
                    XmlHelper::setAttribute( elm, name, "Name" );
                }
			}else
			{
				//TODO:
				STree tree;
				tree.uID = treeDeclID;
				tree.vPos = pos;
				tree.vOrientation = orientation;
				tree.vScale = scale;

				scene->getTreeManager()->AddTreeDelay(tree);
			}
        }	

        ////////////////////////////////////////////////////////////////////////////////////////////////

        if ( tree )
        {
            // 设置基本参数
            tree->getSceneNode()->setPosition(pos);
            tree->getSceneNode()->setOrientation(Qua(orientation.w,orientation.x,orientation.y,orientation.z));
            tree->getSceneNode()->setScale(scale);

            //组名
            Str8 groupName;
            if ( XmlHelper::getAttribute( elm, groupName, "Group" ) )
                tree->setGroup( groupName );

            //可见度
            {
                if ( EngineMain::getInstance().getMode() != EM_EDITOR )
                {
                    XMLElement* visbleAttrs = XmlHelper::getChild(elm, "Visible");
                    Int visible = 1;
                    if ( XmlHelper::getAttribute( visbleAttrs, visible, "Value" ) )
                    {
                        tree->getSceneNode()->setVisible(visible!=0);
                    }
                }
            }

            // 自定义参数
            {
                XMLElement* customAttrs = XmlHelper::getChild(elm, "CustomAttrs");
                tree->clearCustomAttr();
                if (customAttrs)
                {
                    XMLNode* parentNode       = customAttrs;
                    XMLNode* currNode         = parentNode->FirstChild();
                    XMLNode* firstSiblingNode = currNode;
                    XMLNode* nextNode         = NULL;

                    while( currNode )
                    {
                        //TODO:
                        std::string formatType  = XML_GET_VALUE(currNode);
                        std::string attr        = XML_GET_ATTRIBUTE(currNode->ToElement(),"Value");

                        tree->setCustomAttr(formatType,attr);

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

        ////////////////////////////////////////////////////////////////////////////////////////////////

        if ( tree )
        {
            //投射阴影
            {
                Int castShadowsType = 1;
                XmlHelper::getAttribute( elm, castShadowsType, "CastShadowsType" );
                
                // TODO:


            }

            //接受动态阴影
            {
                Int receiveDynamicShadows = 0;
                XmlHelper::getAttribute( elm, receiveDynamicShadows, "ReceiveDynamicShadow" );

                // TODO:


            }

            //接受静态阴影
            {
                Int receiveStaticShadows = 0;
                XmlHelper::getAttribute( elm, receiveStaticShadows, "ReceiveStaticShadow" );

                // TODO:

            }

			{
				Int receiveReflect = 0;
				XmlHelper::getAttribute( elm, receiveReflect, "receiveReflect");
				tree->setReflect(receiveReflect);
			}
        }

            ////////////////////////////////////////////////////////////////////////////////////////////////

        if ( listener )
        {
			TreeXmlFormat::applyIndex++;

			//U32 loadCount = EntityXmlFormat::applyIndex + EffectEntityXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			//U32 loadTotal = EntityXmlFormat::applyTotal + EffectEntityXmlFormat::applyTotal + TreeXmlFormat::applyTotal;
			// CN_MODIFY
			U32 loadCount = EntityXmlFormat::applyIndex + EffectComponentXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			U32 loadTotal = EntityXmlFormat::applyTotal + EffectComponentXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

			listener->postloadObject( tree, loadCount, loadTotal );
        }

        return tree;
    }

	/******************************************************************************/
	//GrassXmlFormat
	/******************************************************************************/
	UInt GrassXmlFormat::applyIndex = 0;
	UInt GrassXmlFormat::applyTotal = 0;

	//-----------------------------------------------------------------------
	GrassXmlFormat::GrassXmlFormat(Scene* scene, XMLElement * elm, Grass* grass)
		:mScene(scene)
		,mGrass(grass)
	{
		mXmlElm = elm;

	}

	//-----------------------------------------------------------------------
	GrassXmlFormat::~GrassXmlFormat()
	{

	}

	//-----------------------------------------------------------------------
	void GrassXmlFormat::fill()
	{
		if (mGrass && mXmlElm)
		{
			// 组
			Str8 groupName = mGrass->getGroup();
			XmlHelper::setAttribute( mXmlElm, groupName, "Group" );

			//名字
			Str8 name = mGrass->getName();
			XmlHelper::setAttribute( mXmlElm, name, "Name" );

			//模型模板名
			//TODO:
			U32 grassDeclID = mGrass->getBaseGrassId();
			XmlHelper::setAttribute( mXmlElm, grassDeclID, "GrassDeclID" );

			//---------------------------------------------------------

			// 位置
			Vec3 pos ;
			mGrass->getSceneNode()->getPosition(pos);
			Vec3XmlFormat::save(mXmlElm, "Position", pos);

			// 朝向
			Qua orientation;
			mGrass->getSceneNode()->getOrientation(orientation);
			Vec4XmlFormat::save(mXmlElm, "Orientation", Vec4(orientation.w,orientation.x,orientation.y,orientation.z) );

			//缩放
			Vec3 scale;
			mGrass->getSceneNode()->getScale(scale);
			Vec3XmlFormat::save(mXmlElm, "Scale", scale);

			//可见度
			{
				XMLElement* elm = XmlHelper::addChild( mXmlElm, "Visible" );
				{
					if ( XmlHelper::hasAttribute( elm,"Value" ) == false )
					{
						XmlHelper::setAttribute( elm, "1", "Value" ); 
					}
				}
			}

			//投射阴影
			{
				//TODO:
				Int castShadowsType = 2; 
				XmlHelper::setAttribute( mXmlElm, castShadowsType, "CastShadowsType" );
			}

			//接受动态阴影
			{
				//TODO:
				Int receiveDynamicShadows = 1;
				XmlHelper::setAttribute( mXmlElm, receiveDynamicShadows, "ReceiveDynamicShadow" );
			}

			//接受静态阴影
			{
				//TODO:
				Int receiveStaticShadows = 1;
				XmlHelper::setAttribute( mXmlElm, receiveStaticShadows, "ReceiveStaticShadow" );
			}

			//自定义参数
			{
				XMLElement* elm = XmlHelper::addChild( mXmlElm, "CustomAttrs" );
				{
					elm->DeleteChildren();

					std::map<Str,Str>& attrList = mGrass->getCustomAttrList();

					std::map<Str,Str>::iterator iter = attrList.begin();
					for ( ;iter!=attrList.end(); iter++)
					{
						Str strName  = iter->first;
						Str strValue = iter->second;

						XMLElement* newElm = XmlHelper::addChild(elm, strName, true);
						XmlHelper::setAttribute( newElm, strValue, "Value" );
					}
				}
			}
		}
	}

	//-----------------------------------------------------------------------
	ISceneObject* GrassXmlFormat::getSceneObject()
	{
		return mGrass;
	}

	//-----------------------------------------------------------------------
	void GrassXmlFormat::apply(Bool isCheckDirty)
	{
		if (mXmlElm)
		{
			mGrass = GrassXmlFormat::apply(mScene, mXmlElm, mGrass);
		}
	}

	//-----------------------------------------------------------------------
	Grass* GrassXmlFormat::apply(Scene* scene, XMLElement * elm, Grass* grass, Bool isCheckDirty)
	{
		ResourceLoadListener* listener = scene->getResourceLoadListener();

		if ( listener )
		{
			//U32 loadCount = EntityXmlFormat::applyIndex + EffectEntityXmlFormat::applyIndex + TreeXmlFormat::applyIndex + GrassXmlFormat::applyIndex;
			//U32 loadTotal = EntityXmlFormat::applyTotal + EffectEntityXmlFormat::applyTotal + TreeXmlFormat::applyTotal + GrassXmlFormat::applyTotal;

			// CN_MODIFY
			U32 loadCount = EntityXmlFormat::applyIndex + EffectComponentXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			U32 loadTotal = EntityXmlFormat::applyTotal + EffectComponentXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

			listener->preloadObject( loadCount, loadTotal );
		}

		////////////////////////////////////////////////////////////////////////////////////////////////

		// 名字
		Str8 name;
		XmlHelper::getAttribute( elm, name, "Name" );

		// 模型编号
		U32 grassDeclID = 0;
		XmlHelper::getAttribute( elm, grassDeclID, "GrassDeclID" );

		// 位置
		Vec3 pos = Vec3(0,0,0);
		Vec3XmlFormat::load(elm, "Position", pos);

		// 朝向
		Vec4 orientation = Vec4(1,0,0,0);
		Vec4XmlFormat::load(elm, "Orientation", orientation);

		// 缩放
		Vec3 scale = Vec3(1,1,1);
		Vec3XmlFormat::load(elm, "Scale", scale);

		////////////////////////////////////////////////////////////////////////////////////////////////

		// 创建实体
		if ( grass == NULL )
		{
			if ( EngineMain::getInstance().getMode() == EM_EDITOR )
			{
				if ( scene->getTreeManager()->getGrass(name.c_str()) == NULL )
				{
					grass = scene->getTreeManager()->createGrass( name.c_str(), grassDeclID, pos);
				}else
				{
					grass = scene->getTreeManager()->createGrass( grassDeclID, pos);
					name = grass->getName();
					XmlHelper::setAttribute( elm, name, "Name" );
				}
			}
			else
			{
				STree tree;
				tree.uID = grassDeclID;
				tree.vPos = pos;
				tree.vOrientation = orientation;
				tree.vScale = scale;

				scene->getTreeManager()->AddGrassDelay(tree);
			}
		}	

		////////////////////////////////////////////////////////////////////////////////////////////////

		if ( grass )
		{
			// 设置基本参数
			grass->getSceneNode()->setPosition(pos);
			grass->getSceneNode()->setOrientation(Qua(orientation.w,orientation.x,orientation.y,orientation.z));
			grass->getSceneNode()->setScale(scale);

			//组名
			Str8 groupName;
			if ( XmlHelper::getAttribute( elm, groupName, "Group" ) )
				grass->setGroup( groupName );

			//可见度
			{
				if ( EngineMain::getInstance().getMode() != EM_EDITOR )
				{
					XMLElement* visbleAttrs = XmlHelper::getChild(elm, "Visible");
					Int visible = 1;
					if ( XmlHelper::getAttribute( visbleAttrs, visible, "Value" ) )
					{
						grass->getSceneNode()->setVisible(visible!=0);
					}
				}
			}

			// 自定义参数
			{
				XMLElement* customAttrs = XmlHelper::getChild(elm, "CustomAttrs");
				grass->clearCustomAttr();
				if (customAttrs)
				{
					XMLNode* parentNode       = customAttrs;
					XMLNode* currNode         = parentNode->FirstChild();
					XMLNode* firstSiblingNode = currNode;
					XMLNode* nextNode         = NULL;

					while( currNode )
					{
						//TODO:
						std::string formatType  = XML_GET_VALUE(currNode);
						std::string attr        = XML_GET_ATTRIBUTE(currNode->ToElement(),"Value");

						grass->setCustomAttr(formatType,attr);

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

		////////////////////////////////////////////////////////////////////////////////////////////////

		if ( grass )
		{
			//投射阴影
			{
				Int castShadowsType = 1;
				XmlHelper::getAttribute( elm, castShadowsType, "CastShadowsType" );

				// TODO:


			}

			//接受动态阴影
			{
				Int receiveDynamicShadows = 0;
				XmlHelper::getAttribute( elm, receiveDynamicShadows, "ReceiveDynamicShadow" );

				// TODO:


			}

			//接受静态阴影
			{
				Int receiveStaticShadows = 0;
				XmlHelper::getAttribute( elm, receiveStaticShadows, "ReceiveStaticShadow" );

				// TODO:

			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////

		if ( listener )
		{
			TreeXmlFormat::applyIndex++;

			//U32 loadCount = EntityXmlFormat::applyIndex + EffectEntityXmlFormat::applyIndex + TreeXmlFormat::applyIndex + GrassXmlFormat::applyIndex;
			//U32 loadTotal = EntityXmlFormat::applyTotal + EffectEntityXmlFormat::applyTotal + TreeXmlFormat::applyTotal + GrassXmlFormat::applyTotal;

			// CN_MODIFY
			U32 loadCount = EntityXmlFormat::applyIndex + EffectComponentXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			U32 loadTotal = EntityXmlFormat::applyTotal + EffectComponentXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

			listener->postloadObject( grass, loadCount, loadTotal );
		}
		return grass;
	}

	/******************************************************************************/
	//EffectXmlFormat
	/******************************************************************************/

	//UInt EffectEntityXmlFormat::applyIndex = 0;
	//UInt EffectEntityXmlFormat::applyTotal = 0;

	////-----------------------------------------------------------------------
	//// CN_MODIFY
	//EffectEntityXmlFormat::EffectEntityXmlFormat(Scene* scene, XMLElement * elm, EffectComponent* effectEntity)
	////EffectEntityXmlFormat::EffectEntityXmlFormat(Scene* scene, XMLElement * elm, EffectEntity* effectEntity)
	//	:mScene(scene)
	//	,mEffectEntity(effectEntity)
	//{
	//	mXmlElm = elm;
	//}

	////-----------------------------------------------------------------------
	//EffectEntityXmlFormat::~EffectEntityXmlFormat()
	//{

	//}

	////-----------------------------------------------------------------------
	//void EffectEntityXmlFormat::fill()
	//{
	//	if ( mEffectEntity && mXmlElm )
	//	{
	//		// 组
	//		Str8 groupName = mEffectEntity->getGroup();
	//		XmlHelper::setAttribute( mXmlElm, groupName, "Group" );

	//		//名字
	//		Str8 name = mEffectEntity->getName();
	//		XmlHelper::setAttribute( mXmlElm, name, "Name" );

	//		//特效模板
	//		U32 effectResID = mEffectEntity->getEffectResourceID();
	//		XmlHelper::setAttribute( mXmlElm, effectResID, "EffectResID" );

	//		// 位置
	//		Vec3 pos ;
	//		mEffectEntity->getSceneNode()->getPosition(pos);
	//		Vec3XmlFormat::save(mXmlElm, "Position", pos);

	//		// 朝向
	//		Qua orientation;
	//		mEffectEntity->getSceneNode()->getOrientation(orientation);
	//		Vec4XmlFormat::save(mXmlElm, "Orientation", Vec4(orientation.w,orientation.x,orientation.y,orientation.z) );

	//		//缩放
	//		Vec3 scale;
	//		mEffectEntity->getSceneNode()->getScale(scale);
	//		Vec3XmlFormat::save(mXmlElm, "Scale", scale);

	//		//可见度
	//		{
	//			XMLElement* elm = XmlHelper::addChild( mXmlElm, "Visible" );
	//			{
	//				if ( XmlHelper::hasAttribute( elm,"Value" ) == false )
	//				{
	//					XmlHelper::setAttribute( elm, "1", "Value" ); 
	//				}
	//			}
	//		}
	//	}
	//}
	////-----------------------------------------------------------------------
	//void EffectEntityXmlFormat::apply(Bool isCheckDirty)
	//{
	//	if (mXmlElm)
	//	{
	//		mEffectEntity = EffectEntityXmlFormat::apply(mScene, mXmlElm, mEffectEntity);
	//	}
	//}
	////-----------------------------------------------------------------------
	//ISceneObject* EffectEntityXmlFormat::getSceneObject()
	//{
	//	return mEffectEntity;
	//}
	////-----------------------------------------------------------------------
	//// CN_MODIFY
	//EffectComponent* EffectEntityXmlFormat::apply(Scene* scene, XMLElement * elm, EffectComponent* effectEntity, Bool isCheckDirty)
	////EffectEntity* EffectEntityXmlFormat::apply(Scene* scene, XMLElement * elm, EffectEntity* effectEntity, Bool isCheckDirty)
	//{

	//	ResourceLoadListener* listener = scene->getResourceLoadListener();

	//	if ( listener )
	//	{
	//		U32 loadCount = EntityXmlFormat::applyIndex + EffectEntityXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
	//		U32 loadTotal = EntityXmlFormat::applyTotal + EffectEntityXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

	//		listener->preloadObject(loadCount, loadTotal);
	//	}

	//	////////////////////////////////////////////////////////////////////////////////////////////////

	//	// 名字
	//	Str8 name;
	//	XmlHelper::getAttribute( elm, name, "Name" );

	//	// 模型编号
	//	U32 effectResID = 0;
	//	XmlHelper::getAttribute( elm, effectResID, "EffectResID" );

	//	// 位置
	//	Vec3 pos = Vec3(0,0,0);
	//	Vec3XmlFormat::load(elm, "Position", pos);

	//	// 朝向
	//	Vec4 orientation = Vec4(1,0,0,0);
	//	Vec4XmlFormat::load(elm, "Orientation", orientation);

	//	// 缩放
	//	Vec3 scale = Vec3(1,1,1);
	//	Vec3XmlFormat::load(elm, "Scale", scale);

	//	////////////////////////////////////////////////////////////////////////////////////////////////
	//	// 创建特效

	//	if ( effectEntity == NULL )
	//	{
	//		if ( scene->getEffectEntity(name.c_str()) == NULL )
	//		{
	//			// CN_MODIFY
	//			effectEntity = scene->createEffectComponent( name.c_str(), effectResID, false, true );
	//			//effectEntity = scene->createEffectEntity( name.c_str(), effectResID, false, true );
	//		}
	//		else
	//		{
	//			// CN_MODIFY
	//			effectEntity = scene->createEffectComponent( effectResID, false, true );
	//			//effectEntity = scene->createEffectEntity( effectResID, false, true );
	//			name = effectEntity->getName();
	//			XmlHelper::setAttribute( elm, name, "Name" );
	//		}
	//	}	


	//	if ( effectEntity )
	//	{
	//		// 设置基本参数
	//		effectEntity->getSceneNode()->setPosition(pos);
	//		effectEntity->getSceneNode()->setOrientation(Qua(orientation.w,orientation.x,orientation.y,orientation.z));
	//		effectEntity->getSceneNode()->setScale(scale);	

 //          // effectEntity->update( 0 );
	//	}

	//	if ( listener )
	//	{
	//		EffectEntityXmlFormat::applyIndex++;

	//		U32 loadCount = EntityXmlFormat::applyIndex + EffectEntityXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
	//		U32 loadTotal = EntityXmlFormat::applyTotal + EffectEntityXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

	//		listener->postloadObject( effectEntity, loadCount, loadTotal );
	//	}

	//	return effectEntity;
	//}
	/******************************************************************************/
	//EffectComponentXmlFormat
	/******************************************************************************/

	UInt EffectComponentXmlFormat::applyIndex = 0;
	UInt EffectComponentXmlFormat::applyTotal = 0;

	EffectComponentXmlFormat::EffectComponentXmlFormat( Scene* scene, XMLElement * elm, EffectComponent* effectComponent )
		:mScene(scene)
		,mEffectComponent(effectComponent)
	{
		mXmlElm = elm;
	}

	EffectComponentXmlFormat::~EffectComponentXmlFormat()
	{

	}

	void EffectComponentXmlFormat::fill()
	{
		if ( mEffectComponent && mXmlElm )
		{
			// 组
			Str8 groupName = mEffectComponent->getGroup();
			XmlHelper::setAttribute( mXmlElm, groupName, "Group" );

			//名字
			Str8 name = mEffectComponent->getName();
			XmlHelper::setAttribute( mXmlElm, name, "Name" );

			//特效模板
			U32 effectResID = mEffectComponent->getEffectResourceID();
			XmlHelper::setAttribute( mXmlElm, effectResID, "EffectResID" );

			// 位置
			Vec3 pos ;
			mEffectComponent->getSceneNode()->getPosition(pos);
			Vec3XmlFormat::save(mXmlElm, "Position", pos);

			// 朝向
			Qua orientation;
			mEffectComponent->getSceneNode()->getOrientation(orientation);
			Vec4XmlFormat::save(mXmlElm, "Orientation", Vec4(orientation.w,orientation.x,orientation.y,orientation.z) );

			//缩放
			Vec3 scale;
			mEffectComponent->getSceneNode()->getScale(scale);
			Vec3XmlFormat::save(mXmlElm, "Scale", scale);

			//可见度
			{
				XMLElement* elm = XmlHelper::addChild( mXmlElm, "Visible" );
				{
					if ( XmlHelper::hasAttribute( elm,"Value" ) == false )
					{
						XmlHelper::setAttribute( elm, "1", "Value" ); 
					}
				}
			}
		}
	}

	void EffectComponentXmlFormat::apply( Bool isCheckDirty/*=false*/ )
	{
		if (mXmlElm)
		{
			mEffectComponent = EffectComponentXmlFormat::apply(mScene, mXmlElm, mEffectComponent);
		}
	}

	EffectComponent* EffectComponentXmlFormat::apply( Scene* scene, XMLElement * elm, EffectComponent* effectComponent/*=NULL*/, Bool isCheckDirty/*=false*/ )
	{
		ResourceLoadListener* listener = scene->getResourceLoadListener();

		if ( listener )
		{
			//U32 loadCount = EntityXmlFormat::applyIndex + EffectEntityXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			//U32 loadTotal = EntityXmlFormat::applyTotal + EffectEntityXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

			// CN_MODIFY
			U32 loadCount = EntityXmlFormat::applyIndex + EffectComponentXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			U32 loadTotal = EntityXmlFormat::applyTotal + EffectComponentXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

			listener->preloadObject(loadCount, loadTotal);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////

		// 名字
		Str8 name;
		XmlHelper::getAttribute( elm, name, "Name" );

		// 模型编号
		U32 effectResID = 0;
		XmlHelper::getAttribute( elm, effectResID, "EffectResID" );

		// 位置
		Vec3 pos = Vec3(0,0,0);
		Vec3XmlFormat::load(elm, "Position", pos);

		// 朝向
		Vec4 orientation = Vec4(1,0,0,0);
		Vec4XmlFormat::load(elm, "Orientation", orientation);

		// 缩放
		Vec3 scale = Vec3(1,1,1);
		Vec3XmlFormat::load(elm, "Scale", scale);

		////////////////////////////////////////////////////////////////////////////////////////////////
		// 创建特效

		if ( effectComponent == NULL )
		{
            if ( EngineMain::getInstance().display()->isDebugNoStaticEffect() ) 
                return NULL;

			if ( scene->getEffectEntity(name.c_str()) == NULL )
			{
				effectComponent = scene->createEffectComponent( name.c_str(), effectResID, false, true );
			}
			else
			{
				effectComponent = scene->createEffectComponent( effectResID, false, true );
				name = effectComponent->getName();
				XmlHelper::setAttribute( elm, name, "Name" );
			}
		}	

		////////////////////////////////////////////////////////////////////////////////////////////////

		if ( effectComponent )
		{
			// 设置基本参数
			effectComponent->getSceneNode()->setPosition(pos);
			effectComponent->getSceneNode()->setOrientation(Qua(orientation.w,orientation.x,orientation.y,orientation.z));
			effectComponent->getSceneNode()->setScale(scale);	

			// effectEntity->update( 0 );
		}

		if ( listener )
		{
			//EffectEntityXmlFormat::applyIndex++;
			EffectComponentXmlFormat::applyIndex++;

			//U32 loadCount = EntityXmlFormat::applyIndex + EffectEntityXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			//U32 loadTotal = EntityXmlFormat::applyTotal + EffectEntityXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

			// CN_MODIFY
			U32 loadCount = EntityXmlFormat::applyIndex + EffectComponentXmlFormat::applyIndex + TreeXmlFormat::applyIndex;
			U32 loadTotal = EntityXmlFormat::applyTotal + EffectComponentXmlFormat::applyTotal + TreeXmlFormat::applyTotal;

			listener->postloadObject( effectComponent, loadCount, loadTotal );
		}

		return effectComponent;
	}

	ISceneObject* EffectComponentXmlFormat::getSceneObject()
	{
		return mEffectComponent;
	}
}


