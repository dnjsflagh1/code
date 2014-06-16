/******************************************************************************/
#include "stdafx.h"
#include "GameFilePackManager.h"
#include "TreeManager.h"
#include "SpeedTreeSystem.h"
#include "scene.h"
#include "EngineMain.h"
#include "Ogre.h"
#include "OgreD3D9RenderSystem.h"
#include "IResourceManager.h"
#include "ILight.h"
#include "IDisplay.h"

using namespace SpeedTree;

/******************************************************************************/
namespace MG
{
    #define TREE_POOL_CATEGORY 3004
    #define GRASS_POOL_CATEGORY 3005

    Str TreeManager::TREE_CSV_FILE = "";
    Str TreeManager::GRASS_CSV_FILE = "";

    //-----------------------------------------------------------------------
	TreeManager::TreeManager(/*Scene* scene*/)
        //:mScene(scene)
		:mTreeNameGenerator("Tree")
		,mGrassNameGenerator("Grass")
        ,mSpeedTreeSystem(NULL)
		,mGameMode(false)
	{
        mSpeedTreeSystem = MG_NEW SpeedTreeSystem();
	}

    //-----------------------------------------------------------------------
	TreeManager::~TreeManager()
	{
        unload();
        MG_SAFE_DELETE( mSpeedTreeSystem );
	}

	//-----------------------------------------------------------------------
	void TreeManager::setScene(Scene* scene)
	{
		mScene = scene;
	}

    //-----------------------------------------------------------------------
	// CN_MODIFY
    Bool TreeManager::load(CChar* treeListCsv, CChar* grassListCsv, GameFilePackManager* packManager)
    {
        Ogre::Root * root = OgreMainInterface::root;
        IDirect3DDevice9* pd3dDevice = D3D9RenderSystem::getActiveD3D9Device();
        if (pd3dDevice == NULL)
        {
            return false;
        }
		
		//
		if (!loadTreeCSV(treeListCsv))
		{
			return false;
		}

#ifdef ACTIVE_GRASS
		if (!loadGrassCSV(grassListCsv))
		{
			return false;
		}
#endif

        SpeedTreeParam speedParam;
        speedParam.pDevice = pd3dDevice;

		// CN_MODIFY
        if (!mSpeedTreeSystem->initialize(speedParam, packManager))
        {
			PrintSpeedTreeErrors( );
            return false;
        }

        if (!mSpeedTreeSystem->load(mTreeDeclMap, mTreeInstance))
        {
			PrintSpeedTreeErrors( );
            return false;
        }

        return true;
    }

    //-----------------------------------------------------------------------
    void TreeManager::unload()
    {
		mSpeedTreeSystem->clearBaseTree();
		//if (!mGrassInstance.empty())
		{
			mSpeedTreeSystem->clearGrass();
		}
    }

	//-----------------------------------------------------------------------
	void TreeManager::loadCameraParam( CameraParam& cameraParam, Ogre::Camera* pOgreCamera )
	{

		Ogre::Vector3 vecPos	= pOgreCamera->getPosition();
		cameraParam.cameraPos	= SpeedTree::Vec3(vecPos.x, vecPos.y, vecPos.z);
		cameraParam.farClip		= pOgreCamera->getFarClipDistance();
		cameraParam.nearClip	= pOgreCamera->getNearClipDistance();

		Ogre::Matrix4 viewMatrix = pOgreCamera->getViewMatrix();
		//if ( pOgreCamera->isReflected() == false )
		//{
		//	
		//}
		viewMatrix = viewMatrix.transpose();

		Mat4x4& modelviewMatrix = cameraParam.viewMatrix;
		modelviewMatrix.Set(viewMatrix[0][0], viewMatrix[0][1], viewMatrix[0][2], viewMatrix[0][3],
			viewMatrix[1][0], viewMatrix[1][1], viewMatrix[1][2], viewMatrix[1][3],
			viewMatrix[2][0], viewMatrix[2][1], viewMatrix[2][2], viewMatrix[2][3],
			viewMatrix[3][0], viewMatrix[3][1], viewMatrix[3][2], viewMatrix[3][3]);

		const Ogre::Matrix4 ogreProjMatrix = pOgreCamera->getProjectionMatrixWithRSDepth().transpose();
		Mat4x4& projMatrix = cameraParam.projMatrix;
		projMatrix.Set(ogreProjMatrix[0][0], ogreProjMatrix[0][1], ogreProjMatrix[0][2], ogreProjMatrix[0][3],
			ogreProjMatrix[1][0], ogreProjMatrix[1][1], ogreProjMatrix[1][2], ogreProjMatrix[1][3],
			ogreProjMatrix[2][0], ogreProjMatrix[2][1], ogreProjMatrix[2][2], ogreProjMatrix[2][3],
			ogreProjMatrix[3][0], ogreProjMatrix[3][1], ogreProjMatrix[3][2], ogreProjMatrix[3][3]);
	}

    //-----------------------------------------------------------------------
    void TreeManager::update(Bool bUpdate)
    {
        if (!mSpeedTreeSystem->isReadyRender() || !bUpdate)
        {
            return;
        }

		CameraParam cameraParam;
		{
			Ogre::Camera* pOgreCamera = mScene->getActiveCamera()->getOgreCamera();
			if (pOgreCamera == NULL)
			{
				return;
			}
			loadCameraParam( cameraParam, pOgreCamera );
		}

		CameraParam lightCameraParam;
		{
			Ogre::String camName = mScene->getActiveShadowCameraName();
			if (mScene->getOgreSceneManager()->hasCamera(camName))
			{
				Ogre::Camera* pOgreCamera = mScene->getOgreSceneManager()->getCamera(camName);
				loadCameraParam( lightCameraParam, pOgreCamera );
			}
			else
			{
				lightCameraParam = cameraParam;
			}
		}

		CameraParam reflectCameraParam;
		{

		}

        mSpeedTreeSystem->update(cameraParam,lightCameraParam,reflectCameraParam);
    }

    //-----------------------------------------------------------------------
    void TreeManager::render(Int renderPass, Ogre::Camera* cam)
    {
		if ( !mSpeedTreeSystem->isReadyRender() )
		{
			return;
		}

        if (cam == NULL)
        {
            return;
        }

		CameraParam cameraParam;
		loadCameraParam( cameraParam, cam );

        OGRE_GPUEVENT_BEGIN(L"SpeedTree");
        mSpeedTreeSystem->render(renderPass, cameraParam);
		OGRE_GPUEVENT_END();
    }
    //-----------------------------------------------------------------------
    void TreeManager::onResetDevice()
    {
        Ogre::Camera* pOgreCamera = mScene->getActiveCamera()->getOgreCamera();
        if (pOgreCamera == NULL)
        {
            return;
        }
        mSpeedTreeSystem->onResetDevice(pOgreCamera->getAspectRatio());
    }

    //-----------------------------------------------------------------------
    void TreeManager::onLostDevice()
    {
        mSpeedTreeSystem->onLostDevice();
    }

    //-----------------------------------------------------------------------
    void TreeManager::clear()
    {
		destroyAllTree();
        destroyAllGrass();
        //TODO: treeSystem clear
    }

	//-----------------------------------------------------------------------
	void TreeManager::applyRenderConfig()
	{
		Color aColor = mScene->getAmbientLight();
		ILight* pLight = mScene->getDefaultLight();
		if (pLight == NULL)
		{
			return;
		}

		WorldEnvironment we = getWorldEnv();
		we.vLightDir = pLight->getDirection();
		we.cEmissive = Color(1.f, 1.f, 1.f, 1.f);

		IDisplay* display = EngineMain::getInstance().display();

		we.cFogColor = display->getFogColor();
		we.fFogStart = display->getFogLinearStart();
		we.fFogEnd = display->getFogLinearEnd();

		setWorldEnv(we);
	}

    //-----------------------------------------------------------------------
    Tree* TreeManager::createTree(CChar* name, U32 baseTreeID, const Vec3& pos)
    {   
        Tree* newEntity = getTree( name );
        DYNAMIC_ASSERT(newEntity==NULL);
        if ( newEntity )
            return NULL;

		std::map<UInt, TreeDeclaration>::iterator it = mTreeDeclMap.find(baseTreeID);
		if (it == mTreeDeclMap.end())
		{
			return NULL;
		}
		MG::Str& treePath = (*it).second.strPath;
		if (treePath.empty())
		{
			return NULL;
		}
		newEntity = MG_POOL_NEW_T(Tree, TREE_POOL_CATEGORY)(mScene, this, mSpeedTreeSystem, baseTreeID, treePath.c_str());
		if (newEntity != NULL)
		{
			if (!newEntity->init(pos))
			{
				return NULL;
			}
		}
        newEntity->setName(name);
        mTrees[name] = newEntity;
        return newEntity;    
    }

    //-----------------------------------------------------------------------
    Tree* TreeManager::createTree(U32 baseTreeID, const Vec3& pos)
    {
        Int i = 0;
        while( i++<1000 )
        {    
            String name = mTreeNameGenerator.generate();
            if ( getTree(name.c_str()) == NULL )
            {
                return createTree( name.c_str(), baseTreeID, pos );
            }
        }
        return NULL;
    }

   //-----------------------------------------------------------------------
    Tree* TreeManager::getTree(CChar* name)
    {
        std::map<String, Tree*>::iterator iter = mTrees.find(name);
        if ( iter != mTrees.end() )
        {
            return iter->second;
        }
        return NULL;
    }

    //-----------------------------------------------------------------------
    void TreeManager::destroyTree(CChar* name)
    {
        std::map<String, Tree*>::iterator iter = mTrees.find(name);
        if ( iter != mTrees.end() )
        {
			Tree* pTree = iter->second;
            MG_POOL_DELETE_T( pTree, Tree, TREE_POOL_CATEGORY );
            mTrees.erase(iter);
			//updateTreesInstanceId(baseTreeId, delId);
        }
    }

    //-----------------------------------------------------------------------
    void TreeManager::destroyAllTree()
    {
        std::map<String, Tree*>::iterator iter = mTrees.begin();
        std::map<String, Tree*>::iterator end_iter = mTrees.end();
        for( ; iter != end_iter; iter++ )
        {
            MG_POOL_DELETE_T( iter->second, Tree, TREE_POOL_CATEGORY );
        }
        mTrees.clear();

        mTreeNameGenerator.reset();
    }

    //-----------------------------------------------------------------------
	bool TreeManager::loadTreeCSV(CChar* csvName)
	{
		CsvReader csv_reader;

		Str16 wstrfileName;
		MG::MGStrOp::toString(csvName, wstrfileName);

		// MG_CN_MODIFY
		IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
		if(!csv_reader.create(wstrfileName, packManager))
		{
			MG_MESSAGE("ResourceManager::loadTreeDeclarations ERROR");
			DYNAMIC_ASSERT(false);
			return false;
		}

		Int row_count = csv_reader.count();
		//mTreeDeclVec.resize(row_count);
		//mBaseTreesList.resize(row_count);
		for ( int i = 0; i < row_count; i++ )
		{
			CsvData* csv_data = csv_reader.findValue(i);

			if (!csv_data)
			{
				continue;
			}
			TreeDeclaration treeDecl;
			MGStrOp::toU32(csv_data->mData[TREE_ID].c_str(), treeDecl.uId);
			MGStrOp::toString(csv_data->mData[TREE_NAME].c_str(), treeDecl.strName);
			MGStrOp::toString(csv_data->mData[TREE_PATH].c_str(), treeDecl.strPath);
			MGStrOp::toFlt(csv_data->mData[TREE_LOD_START].c_str(), treeDecl.fLodStart);
			MGStrOp::toFlt(csv_data->mData[TREE_LOD_END].c_str(), treeDecl.fLodEnd);
			MGStrOp::toString(csv_data->mData[TREE_NOTE].c_str(), treeDecl.strNote);

			mTreeDeclMap[treeDecl.uId] = treeDecl;
			//mBaseTreesList[i] = mTreeDeclVec[i].strPath;
		}

		//mSpeedTreeSystem->setTreeTemplateList(&mBaseTreesList);

		return true;
	}

    //-----------------------------------------------------------------------
	bool TreeManager::loadGrassCSV(CChar* csvName)
	{
		CsvReader csv_reader;

		Str16 wstrfileName;
		MG::MGStrOp::toString(csvName, wstrfileName);

		// MG_CN_MODIFY
		IMGExternalPackManager *packManager = EngineMain::getInstance().getPackManager();
		if(!csv_reader.create(wstrfileName, packManager))
		{
			MG_MESSAGE("ResourceManager::loadTreeDeclarations ERROR");
			DYNAMIC_ASSERT(false);
			return false;
		}

		Int row_count = csv_reader.count();
		for ( int i = 0; i < row_count; i++ )
		{
			CsvData* csv_data = csv_reader.findValue(i);

			if (!csv_data)
			{
				continue;
			}

			GrassDeclaration grassDecl;
			MGStrOp::toU32(csv_data->mData[GRASS_ID].c_str(), grassDecl.uId);
			MGStrOp::toU32(csv_data->mData[GRASS_IMAGE_ID].c_str(), grassDecl.uImageId);
			MGStrOp::toString(csv_data->mData[GRASS_NAME].c_str(), grassDecl.strName);
			MGStrOp::toU32(csv_data->mData[GRASS_TOTAL_COL].c_str(), grassDecl.uTotalCol);
			MGStrOp::toU32(csv_data->mData[GRASS_TOTAL_ROW].c_str(), grassDecl.uTotalRow);
			MGStrOp::toFlt(csv_data->mData[GRASS_WIDTH].c_str(), grassDecl.fWidth);
			MGStrOp::toFlt(csv_data->mData[GRASS_HEIGHT].c_str(), grassDecl.fHeight);
			MGStrOp::toFlt(csv_data->mData[GRASS_WMIN].c_str(), grassDecl.fWMin);
			MGStrOp::toFlt(csv_data->mData[GRASS_WMAX].c_str(), grassDecl.fWMax);
			MGStrOp::toFlt(csv_data->mData[GRASS_HMIN].c_str(), grassDecl.fHMin);
			MGStrOp::toFlt(csv_data->mData[GRASS_HMAX].c_str(), grassDecl.fHMax);
			MGStrOp::toFlt(csv_data->mData[GRASS_RTWINDWEIGHT].c_str(), grassDecl.fRTWindWeight);
			MGStrOp::toFlt(csv_data->mData[GRASS_LTWINDWEIGHT].c_str(), grassDecl.fLTWindWeight);
			MGStrOp::toFlt(csv_data->mData[GRASS_LBWINDWEIGHT].c_str(), grassDecl.fLBWindWeight);
			MGStrOp::toFlt(csv_data->mData[GRASS_RBWINDWEIGHT].c_str(), grassDecl.fRBWindWeight);
			MGStrOp::toString(csv_data->mData[GRASS_NOTE].c_str(), grassDecl.strNote);

			mGrassDeclMap[grassDecl.uId] = grassDecl;

			if (i == 0)
			{
				mSpeedTreeSystem->setGrassImageRowCol(grassDecl.uTotalRow, grassDecl.uTotalCol);
			}
		}
				
		return true;
	}

    //-----------------------------------------------------------------------
	UInt TreeManager::getTreeDeclarationCount()
	{
		return (UInt)mTreeDeclMap.size();
	}

    //-----------------------------------------------------------------------
	TreeDeclaration* TreeManager::getTreeDeclarationByIndex( UInt index)
	{
		std::map<MG::UInt, TreeDeclaration>::iterator it = mTreeDeclMap.find(index);
		if (it == mTreeDeclMap.end())
		{
			return NULL;
		}
		return &it->second;
	}

	//-----------------------------------------------------------------------
	const std::map<MG::UInt, TreeDeclaration>& TreeManager::getTreeDeclMap()
	{
		return mTreeDeclMap;
	}

    //-----------------------------------------------------------------------
	Grass* TreeManager::createGrass(CChar* name, U32 grassID, const Vec3& vPos)
	{
		Grass* newEntity = getGrass( name );
		DYNAMIC_ASSERT(newEntity==NULL);
		if ( newEntity )
			return NULL;

		GrassDeclaration* pGrassDecl = getGrassDeclarationByIndex(grassID);
		if (pGrassDecl == NULL)
		{
			return NULL;
		}

		newEntity = MG_POOL_NEW_T(Grass, GRASS_POOL_CATEGORY)(mScene, this, mSpeedTreeSystem, grassID, vPos, 
			pGrassDecl->fWidth, pGrassDecl->fHeight);

		if ( newEntity->init(pGrassDecl->fWidth, pGrassDecl->fHeight) == false )
		{
			MG_POOL_DELETE_T( newEntity, Grass, GRASS_POOL_CATEGORY );
			return NULL;
		}

		newEntity->setName(name);
		mGrasses[name] = newEntity;

		return newEntity;
	}

    //-----------------------------------------------------------------------
	Grass* TreeManager::createGrass(U32 textureID, const Vec3& vPos)
	{
		Int i = 0;
		while( i++<100000 )
		{    
			String name = mGrassNameGenerator.generate();
			if ( getGrass(name.c_str()) == NULL )
			{
				return createGrass( name.c_str(), textureID, vPos);
			}
		}
		MG_MESSAGE("分配不到名字，所以创造失败");
		return NULL;
	}

    //-----------------------------------------------------------------------
	Grass* TreeManager::getGrass(CChar* name)
	{
		std::map<String, Grass*>::iterator iter = mGrasses.find(name);
		if ( iter != mGrasses.end() )
		{
			return iter->second;
		}
		return NULL;
	}

	//-----------------------------------------------------------------------
	void TreeManager::setGrassPerturbCircle( const Vec3& vPos, const Flt& radiu )
	{
		mSpeedTreeSystem->setGrassPerturbCircle(vPos, radiu);
	}

    //-----------------------------------------------------------------------
	void TreeManager::destroyGrass(CChar* name)
	{
		std::map<String, Grass*>::iterator iter = mGrasses.find(name);
		if ( iter != mGrasses.end() )
		{
			Grass* pGrass = iter->second;
			MG_POOL_DELETE_T( pGrass, Grass, GRASS_POOL_CATEGORY );
			mGrasses.erase(iter);
			
			updateGrassIndex(pGrass->row(), pGrass->col(), pGrass->grassID());
		}
	}

    //-----------------------------------------------------------------------
	void TreeManager::destroyAllGrass()
	{

        std::map<String, Grass*>::iterator iter = mGrasses.begin();
        std::map<String, Grass*>::iterator end_iter = mGrasses.end();
        for( ; iter != end_iter; iter++ )
        {
            //Grass* pGrass = iter->second;
            //updateGrassIndex(pGrass->row(), pGrass->col(), pGrass->grassID());

            MG_POOL_DELETE_T( iter->second, Grass, GRASS_POOL_CATEGORY );
        }
        mGrasses.clear();
        mGrassNameGenerator.reset();
		mSpeedTreeSystem->deleteAllGrass();
	}

    //-----------------------------------------------------------------------
	void TreeManager::updateGrassIndex(Int iRow, Int iCol, UInt uGrassId)
	{
		std::map<String, Grass*>::iterator iter = mGrasses.begin();
		while ( iter != mGrasses.end() )
		{
			Grass* pGrass = iter->second;
			if (pGrass != NULL)
			{
				if (pGrass->row() == iRow && pGrass->col() == iCol)
				{
					UInt uFixedGrassID = pGrass->grassID();
					if (uFixedGrassID > uGrassId)
					{
						pGrass->grassID(uFixedGrassID - 1);
					}
				}
			}
			iter++;
		}
	}

    //-----------------------------------------------------------------------
	UInt TreeManager::getGrassDeclarationCount()
	{
		return (UInt)mTreeDeclMap.size();
	}

    //-----------------------------------------------------------------------
	GrassDeclaration* TreeManager::getGrassDeclarationByIndex( UInt index )
	{
		std::map<UInt, GrassDeclaration>::iterator it = mGrassDeclMap.find(index);
		if (it == mGrassDeclMap.end())
		{
			return NULL;
		}
		return &it->second;
	}

	//-----------------------------------------------------------------------
	const std::map<MG::UInt, GrassDeclaration>& TreeManager::getGrassDeclMap()
	{
		return mGrassDeclMap;
	}
    //-----------------------------------------------------------------------
	void TreeManager::renderTreesBox()
	{
		//for (std::map<String, Tree*>::iterator it = mTrees.begin(); it != mTrees.end(); ++it)
		//{
		//	it->second->renderBox();
		//}
	}

	//void TreeManager::updateTreesInstanceId(int treeModelId, int delId)
	//{
	//	for (std::map<String, Tree*>::iterator it = mTrees.begin(); it != mTrees.end(); ++it)
	//	{
	//		Tree* pTree = it->second;
	//		if (pTree->getBaseTreeId() != treeModelId)
	//		{
	//			continue;
	//		}
	//		int iId = pTree->getInstanceId();
	//		ASSERT(delId != iId);
	//		if (iId >= delId)
	//		{
	//			pTree->setInstanceId(iId - 1);
	//		}
	//	}
	//}

    //-----------------------------------------------------------------------
	void TreeManager::setFarClipDistance(Flt farDistance)
	{
		mSpeedTreeSystem->setFarClip(farDistance);
	}

    //-----------------------------------------------------------------------
	void TreeManager::setWorldEnv(const WorldEnvironment& env)
	{
		mWorldEnvironment = env;
		mSpeedTreeSystem->setLightDir(env.vLightDir);
		mSpeedTreeSystem->setLightMtl(env.cLightAmbient, env.cLightDiffuse, env.cLightSpecular, env.cEmissive);
		mSpeedTreeSystem->setGrassLightMtl(env.cGrassLightAmbient, env.cGrassLightDiffuse, env.cGrassLightSpecular, env.cGrassEmissive);
		mSpeedTreeSystem->setFog(env.cFogColor, env.fFogStart, env.fFogEnd);
	}

    //-----------------------------------------------------------------------
	const WorldEnvironment& TreeManager::getWorldEnv()
	{
		return mWorldEnvironment;
	}

    //-----------------------------------------------------------------------
	void TreeManager::setFog(Color cFogColor, Flt fFogStart, Flt fFogEnd)
	{
		mSpeedTreeSystem->setFog(cFogColor, fFogStart, fFogEnd);
	}

    //-----------------------------------------------------------------------
	void TreeManager::setWindEnable(Bool bEnable)
	{
		mSpeedTreeSystem->setWindEnable(bEnable);
	}
	
    //-----------------------------------------------------------------------
	Bool TreeManager::isWindEnabled()
	{
		return mSpeedTreeSystem->isWindEnabled();
	}

    //-----------------------------------------------------------------------
	void TreeManager::setGlobalWindStrength(float fStrength)
	{
		mSpeedTreeSystem->setGlobalWindStrength(fStrength);
	}

    //-----------------------------------------------------------------------
	float TreeManager::getGlobalWindStrength(void) const
	{
		return mSpeedTreeSystem->getGlobalWindStrength();
	}

    //-----------------------------------------------------------------------
	void TreeManager::setGlobalWindDirection(Vec3& vDir)
	{
		mSpeedTreeSystem->setGlobalWindDirection(vDir);
	}

    //-----------------------------------------------------------------------
	Vec3 TreeManager::getGlobalWindDirection(void) const
	{
		return mSpeedTreeSystem->getGlobalWindDirection();
	}

    //-----------------------------------------------------------------------
	Bool TreeManager::EnableSpecularLight()
	{
		return mSpeedTreeSystem->EnableSpecularLight();
	}

    //-----------------------------------------------------------------------
	void TreeManager::EnableSpecularLight(Bool bEnable)
	{
		mSpeedTreeSystem->EnableSpecularLight(bEnable);
	}

    //-----------------------------------------------------------------------
	Bool TreeManager::EnableTransmissionLight()
	{
		return mSpeedTreeSystem->EnableTransmissionLight();
	}

    //-----------------------------------------------------------------------
	void TreeManager::EnableTransmissionLight(Bool bEnable)
	{
		mSpeedTreeSystem->EnableTransmissionLight(bEnable);
	}

	//-----------------------------------------------------------------------
	Bool TreeManager::EnableDetailLayer()
	{
		return mSpeedTreeSystem->EnableDetailLayer();
	}

	//-----------------------------------------------------------------------
	void TreeManager::EnableDetailLayer(Bool bEnable)
	{
		mSpeedTreeSystem->EnableDetailLayer(bEnable);
	}

	//-----------------------------------------------------------------------
	Bool TreeManager::EnableDetailNormalMap()
	{
		return mSpeedTreeSystem->EnableDetailNormalMap();
	}

	//-----------------------------------------------------------------------
	void TreeManager::EnableDetailNormalMap(Bool bEnable)
	{
		mSpeedTreeSystem->EnableDetailNormalMap(bEnable);
	}

	//-----------------------------------------------------------------------
	Bool TreeManager::EnableAmbientContrast()
	{
		return mSpeedTreeSystem->EnableAmbientContrast();
	}

	//-----------------------------------------------------------------------
	void TreeManager::EnableAmbientContrast(Bool bEnable)
	{
		mSpeedTreeSystem->EnableAmbientContrast(bEnable);
	}

	void TreeManager::setGrassLod(Flt fStartFade, Flt fEndFade)
	{
		mSpeedTreeSystem->setGrassLod(fStartFade, fEndFade);
	}

	void TreeManager::getGrassLod(Flt& fStartFade, Flt& fEndFade)
	{
		mSpeedTreeSystem->getGrassLod(fStartFade, fEndFade);
	}

	void TreeManager::AddTreeDelay(const STree& sTree)
	{
		mTreeInstance[sTree.uID].push_back(sTree);
	}

	void TreeManager::AddGrassDelay(const STree& sTree)
	{
		mGrassInstance[sTree.uID].push_back(sTree);
	}

	void TreeManager::BuildAllTreeAndGrass()
	{
		//tree

		if (!mTreeInstance.empty())
		{
			/*
			std::vector<std::string> baseTreeListName;
			for (std::map<UInt, std::vector<STree>>::iterator it = mTreeInstance.begin(); it != mTreeInstance.end(); ++it)
			{
				if (it->first < mBaseTreesList.size())
				{
					baseTreeListName.push_back(mBaseTreesList[it->first]);
				}
				else
				{
					//
					//assert(0);
				}
			}

			SpeedTree::CArray<SpeedTree::TInstanceArray> aaInstances;
			aaInstances.resize(baseTreeListName.size());
			Int i = 0;
			for (std::map<UInt, std::vector<STree>>::iterator it = mTreeInstance.begin(); it != mTreeInstance.end(); ++it)
			{
				if (it->first >= mBaseTreesList.size())
				{
					continue;
				}
				std::vector<STree>& vecInstance = it->second;
				Int instanceNr = (Int)vecInstance.size();
				aaInstances[i].resize(instanceNr);
				for (Int j = 0; j < instanceNr; ++j)
				{
					CInstance& instance = aaInstances[i][j];
					instance.SetPos(SpeedTree::Vec3(vecInstance[j].vPos.x, vecInstance[j].vPos.y, vecInstance[j].vPos.z));
					Vec4 vOrin = vecInstance[j].vOrientation;
					instance.SetRotation(Qua(vOrin.w, vOrin.x, vOrin.y, vOrin.z).getYaw());
					instance.SetScale(vecInstance[j].vScale.x);
				}
				++i;
			}*/
			//DYNAMIC_ASSERT_LOG
			//mSpeedTreeSystem->loadTreesAll(baseTreeListName, aaInstances);
			mSpeedTreeSystem->loadAndRegisterTree(mTreeDeclMap, mTreeInstance, true);
		}
		
		//grass
		for (std::map<UInt, std::vector<STree>>::iterator it = mGrassInstance.begin(); it != mGrassInstance.end(); ++it)
		{
			std::vector<STree>& vecInstance = it->second;
			for (size_t i = 0; i < vecInstance.size(); ++i)
			{
				GrassDeclaration* pGrassDecl = getGrassDeclarationByIndex(vecInstance[i].uID);
				if (pGrassDecl != NULL)
				{
					UInt uIndex;
					Int row, col;
					mSpeedTreeSystem->addGrass(pGrassDecl->uImageId, vecInstance[i].vPos, pGrassDecl->fWidth, pGrassDecl->fHeight,
						pGrassDecl->fRTWindWeight, pGrassDecl->fLTWindWeight, pGrassDecl->fLBWindWeight, pGrassDecl->fRBWindWeight,
						uIndex, row, col);
				}
			}
		}
	}

	void TreeManager::ClearBuildAllTreeAndGrass()
	{
		mSpeedTreeSystem->clearBaseTree();
		//if (!mGrassInstance.empty())
		//{
			mSpeedTreeSystem->clearGrass();
		//}
		mTreeInstance.clear();
		mGrassInstance.clear();
	}

}