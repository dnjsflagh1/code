
/******************************************************************************/
#include "stdafx.h"
// CN_MODIFY
#include "GameFilePackManager.h"
#include "SpeedTreeSystem.h"
#include "EngineMain.h"
#include "Scene.h"
// CN_MODIFY
#include "ExternalSTPackManager.h"
/******************************************************************************/

using namespace SpeedTree;

namespace
{
	//const MG::Int		MAX_GRASS_PRE_CELLS		= 1000;
	const MG::Int		MAX_NUM_VISIBLE_CELLS	= 75;
	MG::CChar*			SHADER_PATH				= "Media\\Core\\Tree\\";
	MG::CChar*			GRASS_PHOTO_PATH		= "Media\\SpeedTree\\Forests\\Grass\\";
	MG::CChar*			GRASS_PHOTO_NAME		= "PhotoGrass0.dds";
	const MG::Flt		FARCLIP					= 2000.f;
	const MG::Flt		EDITOR_FOREST_CELL_SIZE = 500.f;
	const MG::Flt		GAME_FOREST_CELL_SIZE   = 80.f;
	const MG::Flt		GLOBAL_WIND_STRENGTH	= 0.25f;
	const MG::Flt		DEFAULT_GAMMA			= 1.2f;

	const MG::Flt		DEFAULT_GRASS_CELL_SIZE	= 10.f;
	const MG::Flt		DEFAULT_GRASS_W			= 7.5f;
	const MG::Flt		DEFAULT_GRASS_H			= 5.5f;
	const MG::Flt		DEFAULT_GRASS_AO		= 0.f;
	//const float		DEFAULT_GRASS_NP0		= 0.024f;
	//const float		DEFAULT_GRASS_NP1		= 0.046f;
	const MG::Bool		BHORZBILLBOARDS			= FALSE;
}

namespace MG
{
	//-----------------------------------------------------------------------
	SGrassBoard::SGrassBoard()
	{
		m_vertex[0].m_vPosition = SpeedTree::Vec3(0.f, 0.f, 0.f);
		m_vertex[0].m_fCornerIndex = 0.f;
		m_vertex[0].m_afTexCoords[0] = 1.f;
		m_vertex[0].m_afTexCoords[1] = 0.f;
		m_vertex[0].m_afTerrainTexCoords[0] = 0.f;
		m_vertex[0].m_afTerrainTexCoords[1] = 0.f;
		m_vertex[0].m_fWidth = DEFAULT_GRASS_W;
		m_vertex[0].m_fHeight = DEFAULT_GRASS_H;
		m_vertex[0].m_fWindWeight = 0.5f;
		m_vertex[0].m_fAmbientOcclusion = DEFAULT_GRASS_AO;
		//m_vertex[0].m_afNormalPerturb[0] = DEFAULT_GRASS_NP0;
		//m_vertex[0].m_afNormalPerturb[1] = DEFAULT_GRASS_NP1;
		m_vertex[0].m_fPerturb[0] = 0.0f;
		m_vertex[0].m_fPerturb[1] = 0.0f;
		m_vertex[0].m_fPerturb[2] = 0.0f;
		m_vertex[0].m_fPerturb[3] = 0.0f;

		m_vertex[1].m_vPosition = SpeedTree::Vec3(0.f, 0.f, 0.f);
		m_vertex[1].m_fCornerIndex = 1.f;
		m_vertex[1].m_afTexCoords[0] = 0.f;
		m_vertex[1].m_afTexCoords[1] = 0.f;
		m_vertex[1].m_afTerrainTexCoords[0] = 0.f;
		m_vertex[1].m_afTerrainTexCoords[1] = 0.f;
		m_vertex[1].m_fWidth = DEFAULT_GRASS_W;
		m_vertex[1].m_fHeight = DEFAULT_GRASS_H;
		m_vertex[1].m_fWindWeight = 0.5f;
		m_vertex[1].m_fAmbientOcclusion = DEFAULT_GRASS_AO;
		//m_vertex[1].m_afNormalPerturb[0] = DEFAULT_GRASS_NP0;
		//m_vertex[1].m_afNormalPerturb[1] = DEFAULT_GRASS_NP1;
		m_vertex[1].m_fPerturb[0] = 0.0f;
		m_vertex[1].m_fPerturb[1] = 0.0f;
		m_vertex[1].m_fPerturb[2] = 0.0f;
		m_vertex[1].m_fPerturb[3] = 0.0f;

		m_vertex[2].m_vPosition = SpeedTree::Vec3(0.f, 0.f, 0.f);
		m_vertex[2].m_fCornerIndex = 2.f;
		m_vertex[2].m_afTexCoords[0] = 0.f;
		m_vertex[2].m_afTexCoords[1] = 0.5f;
		m_vertex[2].m_afTerrainTexCoords[0] = 0.f;
		m_vertex[2].m_afTerrainTexCoords[1] = 0.f;
		m_vertex[2].m_fWidth = DEFAULT_GRASS_W;
		m_vertex[2].m_fHeight = DEFAULT_GRASS_H;
		m_vertex[2].m_fWindWeight = 0.f;
		m_vertex[2].m_fAmbientOcclusion = DEFAULT_GRASS_AO;
		//m_vertex[2].m_afNormalPerturb[0] = DEFAULT_GRASS_NP0;
		//m_vertex[2].m_afNormalPerturb[1] = DEFAULT_GRASS_NP1;
		m_vertex[2].m_fPerturb[0] = 0.0f;
		m_vertex[2].m_fPerturb[1] = 0.0f;
		m_vertex[2].m_fPerturb[2] = 0.0f;
		m_vertex[2].m_fPerturb[3] = 0.0f;

		m_vertex[3].m_vPosition = SpeedTree::Vec3(0.f, 0.f, 0.f);
		m_vertex[3].m_fCornerIndex = 3.f;
		m_vertex[3].m_afTexCoords[0] = 1.f;
		m_vertex[3].m_afTexCoords[1] = 0.5f;
		m_vertex[3].m_afTerrainTexCoords[0] = 0.f;
		m_vertex[3].m_afTerrainTexCoords[1] = 0.f;
		m_vertex[3].m_fWidth = DEFAULT_GRASS_W;
		m_vertex[3].m_fHeight = DEFAULT_GRASS_H;
		m_vertex[3].m_fWindWeight = 0.f;
		m_vertex[3].m_fAmbientOcclusion = DEFAULT_GRASS_AO;
		//m_vertex[3].m_afNormalPerturb[0] = DEFAULT_GRASS_NP0;
		//m_vertex[3].m_afNormalPerturb[1] = DEFAULT_GRASS_NP1;
		m_vertex[3].m_fPerturb[0] = 0.0f;
		m_vertex[3].m_fPerturb[1] = 0.0f;
		m_vertex[3].m_fPerturb[2] = 0.0f;
		m_vertex[3].m_fPerturb[3] = 0.0f;

	}

	//-----------------------------------------------------------------------
	SGrassBoard::~SGrassBoard() {}

	//-----------------------------------------------------------------------
	void SGrassBoard::pos(const MG::Vec3& vPos)
	{
		m_vertex[0].m_vPosition = m_vertex[1].m_vPosition = m_vertex[2].m_vPosition 
			= m_vertex[3].m_vPosition = SpeedTree::Vec3(vPos.x, vPos.y, vPos.z);
	}

	//-----------------------------------------------------------------------
	MG::Vec3 SGrassBoard::pos()
	{
		SpeedTree::Vec3 vPos = m_vertex[0].m_vPosition;
		return MG::Vec3(vPos.x, vPos.y, vPos.z);
	}

	//-----------------------------------------------------------------------
	void SGrassBoard::uv(Flt u0, Flt v0, Flt u1, Flt v1, Flt u2, Flt v2, Flt u3, Flt v3)
	{
		m_vertex[0].m_afTexCoords[0] = u0;
		m_vertex[0].m_afTexCoords[1] = v0;
		m_vertex[1].m_afTexCoords[0] = u1;
		m_vertex[1].m_afTexCoords[1] = v1;
		m_vertex[2].m_afTexCoords[0] = u2;
		m_vertex[2].m_afTexCoords[1] = v2;
		m_vertex[3].m_afTexCoords[0] = u3;
		m_vertex[3].m_afTexCoords[1] = v3;
	}

	//-----------------------------------------------------------------------
	void SGrassBoard::size(Flt w, Flt h)
	{
		m_vertex[0].m_fWidth = w;
		m_vertex[0].m_fHeight = h;
		m_vertex[1].m_fWidth = w;
		m_vertex[1].m_fHeight = h;
		m_vertex[2].m_fWidth = w;
		m_vertex[2].m_fHeight = h;
		m_vertex[3].m_fWidth = w;
		m_vertex[3].m_fHeight = h;
	}

	//-----------------------------------------------------------------------
	void SGrassBoard::width(Flt w)
	{
		m_vertex[0].m_fWidth = m_vertex[1].m_fWidth = m_vertex[2].m_fWidth = w;
	}

	//-----------------------------------------------------------------------
	void SGrassBoard::height(Flt h)
	{
		m_vertex[0].m_fHeight = m_vertex[1].m_fHeight = m_vertex[2].m_fHeight = h;
	}

	//-----------------------------------------------------------------------
	Flt	SGrassBoard::width() const
	{
		return m_vertex[0].m_fWidth;
	}

	//-----------------------------------------------------------------------
	Flt SGrassBoard::height() const
	{
		return m_vertex[0].m_fHeight;
	}

	//-----------------------------------------------------------------------
	void SGrassBoard::windWeight(Flt rtw, Flt ltw, Flt lbw, Flt rbw)
	{
		m_vertex[0].m_fWindWeight = rtw;
		m_vertex[1].m_fWindWeight = ltw;
		m_vertex[2].m_fWindWeight = lbw;
		m_vertex[3].m_fWindWeight = rbw;
	}

	//-----------------------------------------------------------------------
	void SGrassBoard::updatePerturb(const Flt perturb)
	{
		m_vertex[0].m_fPerturb[3] = perturb;
		m_vertex[1].m_fPerturb[3] = perturb;
		m_vertex[2].m_fPerturb[3] = perturb;
		m_vertex[3].m_fPerturb[3] = perturb;
	}

	//-----------------------------------------------------------------------
	UInt DataCell::addGrassBoard(const SGrassBoard& grassBoard)
	{
		UInt uIndex = m_grassBoardList.size();
		if (uIndex >= MAX_GRASS_PRE_CELLS)
		{
			return /*INVALID_GRASS*/0xFFFFFFFF;
		}
		m_grassBoardList.push_back(grassBoard);
		return uIndex;
	}

	//-----------------------------------------------------------------------
	Bool DataCell::deleteGrassBoard(UInt uIndex)
	{
		if (uIndex == 0xFFFFFFFF/*INVALID_GRASS*/)
		{
			return true;
		}

		std::list<SGrassBoard>::iterator it = gotoBoradIter(uIndex);
		if (it != m_grassBoardList.end())
		{
			m_grassBoardList.erase(it);
			return true;
		}
		else
		{
			return false;
		}
	}

	//-----------------------------------------------------------------------
	Bool DataCell::getPos(UInt uIndex, MG::Vec3& vPos)
	{
		std::list<SGrassBoard>::iterator it = gotoBoradIter(uIndex);
		if (it != m_grassBoardList.end())
		{
			vPos = it->pos();
			return true;
		}
		else
		{
			return false;
		}
		
	}

	//-----------------------------------------------------------------------
	Bool DataCell::setPos(UInt uIndex, const MG::Vec3& vPos)
	{
		std::list<SGrassBoard>::iterator it = gotoBoradIter(uIndex);
		if (it != m_grassBoardList.end())
		{
			it->pos(vPos);
			return true;
		}
		else
		{
			return false;
		}
	}

	//-----------------------------------------------------------------------
	Bool DataCell::setSize(UInt uIndex, Flt w, Flt h)
	{
		std::list<SGrassBoard>::iterator it =  gotoBoradIter(uIndex);
		if (it != m_grassBoardList.end())
		{
			it->size(w, h);
			return true;
		}
		else
		{
			return false;
		}
	}

	//-----------------------------------------------------------------------
	Bool DataCell::width(UInt uIndex, Flt w)
	{
		std::list<SGrassBoard>::iterator it =  gotoBoradIter(uIndex);
		if (it != m_grassBoardList.end())
		{
			it->width(w);
			return true;
		}
		else
		{
			return false;
		}
	}

	//-----------------------------------------------------------------------
	Flt DataCell::width(UInt uIndex)
	{
		std::list<SGrassBoard>::iterator it =  gotoBoradIter(uIndex);
		if (it != m_grassBoardList.end())
		{
			return it->width();
		}
		else
		{
			return 0.f;
		}
	}

	//-----------------------------------------------------------------------
	Bool DataCell::height(UInt uIndex, Flt h)
	{
		std::list<SGrassBoard>::iterator it =  gotoBoradIter(uIndex);
		if (it != m_grassBoardList.end())
		{
			it->height(h);
			return true;
		}
		else
		{
			return false;
		}
	}

	//-----------------------------------------------------------------------
	Flt DataCell::height(UInt uIndex)
	{
		std::list<SGrassBoard>::iterator it =  gotoBoradIter(uIndex);
		if (it != m_grassBoardList.end())
		{
			return it->height();
		}
		else
		{
			return 0.f;
		}
	}

	//-----------------------------------------------------------------------
	Bool DataCell::windWeight(UInt uIndex, Flt rtw, Flt ltw, Flt lbw, Flt rbw)
	{
		std::list<SGrassBoard>::iterator it =  gotoBoradIter(uIndex);
		if (it != m_grassBoardList.end())
		{
			it->windWeight(rtw, ltw, lbw, rbw);
			return true;
		}
		else
		{
			return false;
		}
	}

	//-----------------------------------------------------------------------
	std::list<SGrassBoard>::iterator DataCell::gotoBoradIter(UInt uIndex)
	{
		if (uIndex >= m_grassBoardList.size())
		{
			return m_grassBoardList.end();
		}
		std::list<SGrassBoard>::iterator it = m_grassBoardList.begin();
		UInt iCount = 0;
		while (iCount < uIndex)
		{
			it++;
			iCount++;
		}
		return it;
	}

	//-----------------------------------------------------------------------
	SpeedTreeSystem::SpeedTreeSystem():
	m_perturbSpeed(6.0f),
	m_needPerturRadin(MG_PI*12),
	m_BitmapArrayRects(0)
	{
		CCoordSys::SetCoordSys(CCoordSys::COORD_SYS_RIGHT_HANDED_Y_UP);

		m_fAspectRatio				= 4.f / 3.f;
		m_fCurrentTime				= 0.0f;
		m_fFrameTime				= 0.0f;
		m_fTimeMarker				= 0.0f;
		m_nSecondaryShadowIndex		= 1;
		m_nSecondaryShadowInterval	= 1;
		m_bReadyToRender			= false;
		m_bRenderBranches			= true;
		m_bRenderFronds				= true;
		m_bRenderLeafCards			= true;
		m_bRenderLeafMeshes			= true;
		m_bRenderBillboards			= true;
		m_bCameraChanged			= true;
		m_bForestPopulationChanged	= true;
		m_bShowDepthOnlyPrePass		= false;
		m_bUpdateShadowMaps			= true;

		//m_uiTransparentTextureRenderMode = TRANS_TEXTURE_ALPHA_TO_COVERAGE;
		m_uiTransparentTextureRenderMode = TRANS_TEXTURE_ALPHA_TESTING;

		m_fLightAngleHorz			= c_fHalfPi;
		m_fLightAngleVert			= c_fQuarterPi;
		//m_fShadowSplitScalar		= 1.0f;

		m_bRenderGrass				= true;

		m_bGrassDirty				= false;
		
		m_bEditorMode				= false;
		m_grassImageRow				= 2;
		m_grassImageCol				= 1;
		m_cForest.TransparentTextureModeNotify(ETextureAlphaRenderMode(m_uiTransparentTextureRenderMode));
		m_pTreeTemplateList			= NULL;
		m_pTreeDecl					= NULL;

		// CN_MODIFY
		mSTPackManager				= NULL;

		m_bNotRender				= false;
		memset((void*)m_tmpGrassVertex, 0, sizeof(m_tmpGrassVertex));
	}

	//-----------------------------------------------------------------------
	SpeedTreeSystem::~SpeedTreeSystem()
	{
		//setGamma(1.0f);
		CRenderState::Destroy( );
		CCore::ShutDown( );
	}

	//-----------------------------------------------------------------------
	// CN_MODIFY
	Bool SpeedTreeSystem::initialize(const SpeedTreeParam& param, GameFilePackManager* packManager)
	{
		m_bReadyToRender = false;

		if (param.pDevice == NULL)
		{
			return false;
		}

		// CN_MODIFY
		mSTPackManager = new MG::ExternalSTPackManager(packManager);

		loadConfig();

		return initGraphics(param.pDevice);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::load(std::map<UInt, TreeDeclaration>& treeDeclMap, std::map<UInt, std::vector<STree>>& treeInstanceMap)
	{
		if ( EngineMain::getInstance().getMode() == EM_EDITOR )
		{
			//load trees
			loadAndRegisterTree(treeDeclMap, treeInstanceMap, false);
		}

		m_pTreeDecl = &treeDeclMap;

		(void) CCore::DeleteAllTmpHeapBlocks(1024 * 256); // delete any blocks larger than 256 KB
		m_cTimer.Start( );

		m_bReadyToRender = true;

		return true;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::onResetDevice(float aspectRatio)
	{
		setAspectRatio(aspectRatio);
		m_cForest.OnResetDevice();

		// enable anisotropic filtering on the samplers in case we're not using fx files
		//for (unsigned int i = 0; i < 12; ++i)
		//{
		//	DX9::Device( )->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		//	DX9::Device( )->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		//	DX9::Device( )->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

  //          Int m_nMaxAnisotropy = 5;
		//	if (m_nMaxAnisotropy > 0 && i < 5)
		//	{
		//	    DX9::Device( )->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		//	    DX9::Device( )->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, m_nMaxAnisotropy);
		//	}
		//	else
		//	    DX9::Device( )->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		//}
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::onLostDevice()
	{
		m_cForest.OnLostDevice();
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::update(const CameraParam& cameraParam, const CameraParam& lightCameraParam,const CameraParam& reflectCameraParam)
	{
		if (!m_bReadyToRender)
		{
			return;
		}

		// frame's over; update a few things
		m_bCameraChanged = false;
		m_bForestPopulationChanged = false;

		// updating the view is an important step because the forest population or positions
		// may have changed (normally happens if the SDK is embedded in a world-building app)
		m_cView			= getView(cameraParam);
		m_cLightView	= getView(lightCameraParam);
		m_cReflectView	= getView(reflectCameraParam);
		m_bCameraChanged = true;

		advance();
		cull();

#ifdef ACTIVE_GRASS
		updateDirtyGrass();
#endif

		m_bNotRender = false;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::updateDirtyGrass()
	{
		TGrassCellArray* pCells = NULL;
		//if (isEditorMode())
		{
			pCells = &m_sVisibleGrass.m_aVisibleCells;
		}
		//else
		//{
		//	pCells = &m_sVisibleGrass.m_aCellsToUpdate;
		//}
		// gather some working parameters
		const st_int32 c_nNumCells = int(pCells->size( ));

		for (st_int32 nCell = 0; nCell < c_nNumCells; ++nCell)
		{
			// cell the cell and associated VBO
			CGrassCell* pCell = (*pCells)[nCell];
			assert(pCell);
			DataCell* pDataCell = (DataCell*)m_grassCellMap.GetCellPtrByRowCol(pCell->Row(), pCell->Col());
			if (pDataCell == NULL)
			{
				continue;
			}

			//查看当前Datacell是否是脏的
			std::set<DataCell*>::iterator dirtCellItr = m_dirtyGrassCellset.find(pDataCell);
			if (dirtCellItr == m_dirtyGrassCellset.end())
				continue;

			bool bCellDirty = false;

			CGeometryBuffer* pVbo = (CGeometryBuffer*) pCell->GetVbo( );
			if (pVbo)
			{
				std::list<SGrassBoard>& grassBoardList = pDataCell->m_grassBoardList;
				assert((Int)grassBoardList.size() < MAX_GRASS_PRE_CELLS);
				if ((Int)grassBoardList.size() >= MAX_GRASS_PRE_CELLS)
				{
					continue;
				}
				memset((void*)m_tmpGrassVertex, 0, sizeof(m_tmpGrassVertex));
				SGrassVertex* grassVertexArray = m_tmpGrassVertex;
				int iGrassBoardCount = 0;
				for (std::list<SGrassBoard>::iterator it = grassBoardList.begin(); it != grassBoardList.end(); ++it)
				{
					Flt lastUpdateTime = it->m_vertex[0].m_fPerturb[0];
					if (lastUpdateTime > 0)
					{
						Flt t = clock()/(float)CLOCKS_PER_SEC;
						Flt elapsedSecond = t - lastUpdateTime;
						Flt increaseRadian = elapsedSecond*m_perturbSpeed;
						Flt curPerturbRadian = it->m_vertex[0].m_fPerturb[1]+increaseRadian;

						Flt needPerturbRadian = it->m_vertex[0].m_fPerturb[2];

						Flt perturbSpeed = 1.0/6.28;
						Flt decreasePerturb = elapsedSecond*perturbSpeed;

						if (curPerturbRadian <= needPerturbRadian)
						{
							it->m_vertex[0].m_fPerturb[0] = t;
							it->m_vertex[1].m_fPerturb[0] = t;
							it->m_vertex[2].m_fPerturb[0] = t;
							it->m_vertex[3].m_fPerturb[0] = t;

							it->m_vertex[0].m_fPerturb[1] = curPerturbRadian;
							it->m_vertex[1].m_fPerturb[1] = curPerturbRadian;
							it->m_vertex[2].m_fPerturb[1] = curPerturbRadian;
							it->m_vertex[3].m_fPerturb[1] = curPerturbRadian;

							it->m_vertex[0].m_fPerturb[3] -= decreasePerturb;
							it->m_vertex[1].m_fPerturb[3] -= decreasePerturb;
							it->m_vertex[2].m_fPerturb[3] -= decreasePerturb;
							it->m_vertex[3].m_fPerturb[3] -= decreasePerturb;

							bCellDirty = true;
						}
						else
						{
							it->m_vertex[0].m_fPerturb[0] = 0.0f;
							it->m_vertex[1].m_fPerturb[0] = 0.0f;
							it->m_vertex[2].m_fPerturb[0] = 0.0f;
							it->m_vertex[3].m_fPerturb[0] = 0.0f;

							it->m_vertex[0].m_fPerturb[1] = 0.0f;
							it->m_vertex[1].m_fPerturb[1] = 0.0f;
							it->m_vertex[2].m_fPerturb[1] = 0.0f;
							it->m_vertex[3].m_fPerturb[1] = 0.0f;

							it->m_vertex[0].m_fPerturb[2] = 0.0f;
							it->m_vertex[1].m_fPerturb[2] = 0.0f;
							it->m_vertex[2].m_fPerturb[2] = 0.0f;
							it->m_vertex[3].m_fPerturb[2] = 0.0f;

							it->m_vertex[0].m_fPerturb[3] = 0.0f;
							it->m_vertex[1].m_fPerturb[3] = 0.0f;
							it->m_vertex[2].m_fPerturb[3] = 0.0f;
							it->m_vertex[3].m_fPerturb[3] = 0.0f;
						}

					}

					grassVertexArray[iGrassBoardCount * 4 + 0] = (*it).m_vertex[0];
					grassVertexArray[iGrassBoardCount * 4 + 1] = (*it).m_vertex[1];
					grassVertexArray[iGrassBoardCount * 4 + 2] = (*it).m_vertex[2];
					grassVertexArray[iGrassBoardCount * 4 + 3] = (*it).m_vertex[3];

					iGrassBoardCount++;
				}
				pCell->SetNumBlades(iGrassBoardCount);

				void* pVoid = NULL;
				if (iGrassBoardCount > 0)
				{
					pVoid = grassVertexArray;
				}
				pVbo->OverwriteVertices(pVoid, iGrassBoardCount * 4, 0);

				if (!bCellDirty)
					m_dirtyGrassCellset.erase(dirtCellItr);
			}
		}
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::render(Int renderPass, const CameraParam& vpCameraParam)
	{
		if (m_bNotRender /*|| true*/)
		{
			return;
		}

		if (renderPass == RENDER_PASS_STANDARD)
		{
			m_cView			= getView(vpCameraParam);
			renderToMainScene(vpCameraParam);
		}
		else if (renderPass == RENDER_PASS_SHADOW)
		{
			m_cLightView	= getView(vpCameraParam);
			//m_cView			= m_cLightView;
			renderToShadowMap(vpCameraParam);
		}
		else if (renderPass == RENDER_PASS_REFLECT)
        {
			m_cView			= getView(vpCameraParam);
            renderToReflectMap(vpCameraParam);
        }
        else if (renderPass == RENDER_PASS_REFRACT)
        {
            renderToRefractMap(vpCameraParam);
        }
        else if (renderPass == RENDER_PASS_DEPTH_ONLY)
		{
			//depth only
			renderZPass(vpCameraParam);
		}
		PrintSpeedTreeErrors("End of SpreedTree::Render");
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::renderToMainScene(const CameraParam& vpCameraParam)
	{
		if (!m_sVisibleTrees.m_pBaseTrees || !m_bReadyToRender)
		{
			return;
		}

		// set render states
		CRenderState::SetAlphaFunction(ALPHAFUNC_GREATER, 0.0f);
		CRenderState::SetDepthTestFunc(DEPTHTEST_LESS);
		setTransparentTextureMode(ETextureAlphaRenderMode(m_uiTransparentTextureRenderMode));

		// start the forest render
		m_cForest.StartRender( );
		{
			m_cForest.UploadViewShaderParameters(m_cView);
#ifdef ACTIVE_GRASS
            OGRE_GPUEVENT_BEGIN(L"RenderGrass");
            {
                renderGrass();
            }
            OGRE_GPUEVENT_END();
#endif
            OGRE_GPUEVENT_BEGIN(L"RenderTree");
            {
                (void) renderForest(RENDER_PASS_STANDARD);
            }
            OGRE_GPUEVENT_END();
		}
		m_cForest.EndRender( );
	}

    //-----------------------------------------------------------------------
    void SpeedTreeSystem::renderToReflectMap(const CameraParam& vpCameraParam)
    {
        if (!m_sVisibleTrees.m_pBaseTrees || !m_bReadyToRender)
        {
            return;
        }

        // set render states
        CRenderState::SetAlphaFunction(ALPHAFUNC_GREATER, 0.0f);
        CRenderState::SetDepthTestFunc(DEPTHTEST_LESS);
        setTransparentTextureMode(ETextureAlphaRenderMode(m_uiTransparentTextureRenderMode));

        // start the forest render
        m_cForest.StartRender( );
        {
			CView cReflectView;
			cReflectView.Set(vpCameraParam.cameraPos, vpCameraParam.projMatrix, vpCameraParam.viewMatrix, 
				vpCameraParam.nearClip, vpCameraParam.farClip);

            m_cForest.UploadViewShaderParameters(cReflectView);
#ifdef ACTIVE_GRASS
            OGRE_GPUEVENT_BEGIN(L"RenderGrass Reflect");
            {
                renderGrass();
            }
            OGRE_GPUEVENT_END();
#endif
            OGRE_GPUEVENT_BEGIN(L"RenderTree Reflect");
            {
                (void) renderForest(RENDER_PASS_REFLECT);
            }
            OGRE_GPUEVENT_END();
        }
        m_cForest.EndRender( );
    }

    //-----------------------------------------------------------------------
    void SpeedTreeSystem::renderToRefractMap(const CameraParam& vpCameraParam)
    {
        //if (!m_sVisibleTrees.m_pBaseTrees || !m_bReadyToRender)
        //{
        //    return;
        //}

        //// set render states
        //CRenderState::SetAlphaFunction(ALPHAFUNC_GREATER, 0.0f);
        //CRenderState::SetDepthTestFunc(DEPTHTEST_LESS);
        //setTransparentTextureMode(ETextureAlphaRenderMode(m_uiTransparentTextureRenderMode));

        //// start the forest render
        //m_cForest.StartRender( );
        //{
        //    m_cForest.UploadViewShaderParameters(m_cView);

        //    OGRE_GPUEVENT_BEGIN(L"RenderGrass");
        //    {
        //        renderGrass();
        //    }
        //    OGRE_GPUEVENT_END();

        //    OGRE_GPUEVENT_BEGIN(L"RenderTree");
        //    {
        //        (void) renderForest(RENDER_PASS_STANDARD);
        //    }
        //    OGRE_GPUEVENT_END();
        //}
        //m_cForest.EndRender( );
    }

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::renderToShadowMap(const CameraParam& vpCameraParam)
	{
		if (!m_sVisibleTrees.m_pBaseTrees || !m_bReadyToRender)
		{
			return;
		}

		// set render states
		CRenderState::SetAlphaFunction(ALPHAFUNC_GREATER, 0.0f);
		CRenderState::SetDepthTestFunc(DEPTHTEST_LESS);
		setTransparentTextureMode(ETextureAlphaRenderMode(m_uiTransparentTextureRenderMode));

		// start the forest render
		m_cForest.StartRender( );
		{
			CView cShadowView;
			cShadowView.Set(vpCameraParam.cameraPos, vpCameraParam.projMatrix, vpCameraParam.viewMatrix, 
				vpCameraParam.nearClip, vpCameraParam.farClip);

			OGRE_GPUEVENT_BEGIN(L"ShadowMap");
			{
				// this call will change the current shader view parameters
				renderForestIntoOneShadowMaps( cShadowView );
			}
			OGRE_GPUEVENT_END();

			(void) m_cForest.ClearBoundTextures( );
		}
		m_cForest.EndRender( );
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::renderZPass(const CameraParam& cameraParam)
	{
		//// normally color writing should be disabled, but keep enabled if render of depth-only pass is requested
		////if (!m_bShowDepthOnlyPrePass)
		////	CRenderState::SetColorMask(false, false, false, false);

		//CView cView;
		//cView.Set(cameraParam.cameraPos, cameraParam.projMatrix, cameraParam.viewMatrix, cameraParam.nearClip, cameraParam.farClip);
		//m_cForest.UploadViewShaderParameters(cView);

		//(void) renderForest(RENDER_PASS_DEPTH_ONLY);
		//(void) m_cForest.ClearBoundTextures( );

		//// setup states for next pass
		////CRenderState::SetDepthMask(false);
		////CRenderState::SetColorMask(true, true, true, true);
		////CRenderState::SetDepthTestFunc(DEPTHTEST_EQUAL);

		//CRenderState::SetDepthTestFunc(DEPTHTEST_LESS);
		//CRenderState::SetDepthMask(true);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::initGraphics(IDirect3DDevice9* pDevice)
	{
		CCore::SetTextureFlip(true);
		CCore::SetClipSpaceDepthRange(0.0f, 1.0f);
		SpeedTree::DX9::SetDevice(pDevice);
		CRenderState::Initialize();
		onResetDevice(m_fAspectRatio);

		//载入树的shader
		// CN_MODIFY
		if (!m_cForest.InitGraphics(false, mSTPackManager))
		{
			PrintSpeedTreeErrors( );
			Error("The SpeedTree Render Interface failed to initialize; check the console for an error report");
			return false;
		}

#ifdef ACTIVE_GRASS
        //grass init
        m_cGrass.SetHint(CGrass::HINT_MAX_NUM_VISIBLE_CELLS, MAX_NUM_VISIBLE_CELLS);
        m_cGrass.SetHint(CGrass::HINT_MAX_GRASS_BLADES_PER_CELL, MAX_GRASS_PRE_CELLS);
        m_sVisibleGrass.Reserve(MAX_NUM_VISIBLE_CELLS);

		//载入草的shader
		m_cGrass.SetShaderLoader(m_cForest.GetShaderLoader());
		MG::Str fullFileName = MG::Str(GRASS_PHOTO_PATH) + MG::Str(GRASS_PHOTO_NAME);
		// CN_MODIFY
		m_cGrass.Init(fullFileName.c_str(), m_grassImageRow, m_grassImageCol, DEFAULT_GRASS_CELL_SIZE, g_asGrassVertexFormat, mSTPackManager);

		//解释草UV
		parseTaiFile(GRASS_PHOTO_PATH);

		//用来算草属于哪行哪列
		m_grassCellMap.SetCellSize(DEFAULT_GRASS_CELL_SIZE);
#endif

		// 草的风参数设置
		m_cGrass.GetWind( ).SetParams(m_grassWindParam);

		// 草的LOD范围
		m_cGrass.SetLodRange(50.f, 100.f);

		// max number of cells in forest frustum (used for billboard system)
		m_cForest.SetHint(CForest::HINT_MAX_NUM_VISIBLE_CELLS, MAX_NUM_VISIBLE_CELLS);
		
		return true;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::parseTaiFile(const MG::CChar* path)
	{
		Str fileName = "PhotoGrass.tai";
		Str fullName = Str(path) + fileName;

		fstream file(fullName.c_str());

		char line[CHAR_MAX];

		//start parse------------------------
		while (file.getline(line,CHAR_MAX))
		{
			Str s(line);
			if (!s.empty())
			{
				if (s[0] != '#')
				{
					RectF rect;

					//height
					size_t pos = s.rfind(',');
					float height = atof(Str(s,pos+1,s.size()-pos).c_str());
					s.assign(s, 0, pos-1);

					//width
					pos = s.rfind(',');
					float width = atof(Str(s,pos+1,s.size()-pos).c_str());
					s.assign(s, 0, pos-1);

					//depth
					pos = s.rfind(',');
					s.assign(s, 0, pos-1);

					//top
					pos = s.rfind(',');
					float top = atof(Str(s,pos+1,s.size()-pos).c_str());
					s.assign(s, 0, pos-1);

					//left
					pos = s.rfind(',');
					float left = atof(Str(s,pos+1,s.size()-pos).c_str());
					s.assign(s, 0, pos-1);

					//修正值(去掉边上的像素)
					float delta = 0.0015;

					rect.left = left+delta;
					rect.top = top+delta;
					rect.right = left + width - delta;
					rect.bottom = top + height - delta;

					m_BitmapArrayRects.push_back(rect);
				}
			}
		}

		//--end parse

		file.close();
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::loadConfig()
	{
		SForestRenderInfo sRenderInfo;

		//
		{
			// general rendering
			sRenderInfo.m_strShaderPath = SHADER_PATH;
			sRenderInfo.m_nMaxAnisotropy = 5;
			sRenderInfo.m_bHorizontalBillboards = BHORZBILLBOARDS;
			sRenderInfo.m_fAlphaTestScalar = 0.57f;
			sRenderInfo.m_bZPrePass = true;
			sRenderInfo.m_nMaxBillboardImagesByBase = 20;
			sRenderInfo.m_fVisibility = FARCLIP;
			// lighting
			sRenderInfo.m_fGlobalLightScalar = 3.f;
			initLightMtl(sRenderInfo.m_sLightMaterial);
			sRenderInfo.m_bSpecularLighting = true;
			sRenderInfo.m_bTransmissionLighting = true;
			sRenderInfo.m_bDetailLayer = false;
			sRenderInfo.m_bDetailNormalMapping = false;
			sRenderInfo.m_bAmbientContrast = true;
			// fog
			sRenderInfo.m_vFogColor = SpeedTree::Vec3(0.95f, 0.95f, 0.75f);
			sRenderInfo.m_fFogStartDistance = 500;
			sRenderInfo.m_fFogEndDistance = 5000;
			// sky
			sRenderInfo.m_vSkyColor = SpeedTree::Vec3(0.38f, 0.52f, 0.75f);
			sRenderInfo.m_fSkyFogMin = -0.15f;
			sRenderInfo.m_fSkyFogMax = 0.65f;
			// sun
			sRenderInfo.m_vSunColor = SpeedTree::Vec3(1.f, 1.f, 0.85f);
			sRenderInfo.m_fSunSize = 0.008f;
			sRenderInfo.m_fSunSpreadExponent = 100.f;
			sRenderInfo.m_fSunFogBloom = 0.f;
			// shadows
			sRenderInfo.m_nNumShadowMaps = 1;
			sRenderInfo.m_nShadowMapResolution = 1;
			sRenderInfo.m_bSmoothShadows = false;
			sRenderInfo.m_bShowShadowSplitsOnTerrain = false;
			// wind
			sRenderInfo.m_bWindEnabled = true;
			sRenderInfo.m_bFrondRippling = true;
			sRenderInfo.m_lightModel = LIGHTMODE_ORIGINAL;
			m_cForest.SetRenderInfo(sRenderInfo);
		}
		

		// grass render info
		{
			// shader
			SGrassRenderInfo sInfo;
			sInfo.m_strShaderPath = SHADER_PATH;

			SMaterial sGrassMaterial; // default material settings

			// lighting and material
			sGrassMaterial.m_fLightScalar *= 1.2f;
			sInfo.m_sMaterial = sGrassMaterial;

			m_cGrass.SetRenderInfo(sInfo);

			//
			initGrassWind();
		}

		// set transparent texture render mode based on multisampling
		//if (m_sEnvSettings.m_nSampleCount > 0)
		//	m_uiTransparentTextureRenderMode = TRANS_TEXTURE_ALPHA_TO_COVERAGE;
		//else
		//m_uiTransparentTextureRenderMode = TRANS_TEXTURE_ALPHA_TO_COVERAGE;
		m_uiTransparentTextureRenderMode = TRANS_TEXTURE_ALPHA_TESTING;
		m_cForest.TransparentTextureModeNotify(ETextureAlphaRenderMode(m_uiTransparentTextureRenderMode));

        // set forest cell size
        Scene* scene = EngineMain::getInstance().getFirstScene();
        if ( EngineMain::getInstance().getMode() == EM_EDITOR )
        {
		    m_cForest.SetCullCellSize(EDITOR_FOREST_CELL_SIZE);
        }else
        {
		    m_cForest.SetCullCellSize(GAME_FOREST_CELL_SIZE);
        }

		// wind
		setGlobalWindStrength(GLOBAL_WIND_STRENGTH);
		//setWindEnable(false);

		// lighting
		setLightDir(MG::Vec3(0.707f, 0.f, -0.707f));

		updateLightDir( );

		PrintSpeedTreeErrors("SpreedTree::Init");
	}

	Bool SpeedTreeSystem::loadAndRegisterTree(const std::map<UInt, TreeDeclaration>& treeDeclMap, const std::map<UInt, std::vector<STree>>& treeInstanceMap, Bool bSetInstance)
	{
		if (treeDeclMap.empty())
		{
			return true;
		}

		if (bSetInstance && treeInstanceMap.empty())
		{
			return true;
		}

		// 向CForest载入和注册树
		std::vector<std::pair<UInt, CTreeRender*>> loadedBaseTrees;
		// CN_MODIFY
		std::map<CTreeRender*, CFixedString> loadedBaseTreesPath;
		
		if (bSetInstance)
		{
			for (std::map<UInt, std::vector<STree>>::const_iterator it = treeInstanceMap.begin(); it != treeInstanceMap.end(); ++it)
			{
				std::map<UInt, TreeDeclaration>::const_iterator itConst = treeDeclMap.find((*it).first);
				if (itConst == treeDeclMap.end())
				{
					continue;
				}
				//获取树资源路径
				const char* pSrtFilename = itConst->second.strPath.c_str( );
				if (pSrtFilename == NULL || strlen(pSrtFilename) <= 0)
				{
					continue;
				}
				// 创建CTreeRender对象
				CTreeRender* pBaseTree = (CTreeRender*)m_cForest.AllocateTree();
				if (pBaseTree->LoadTree(pSrtFilename))
				{
					if (!m_cForest.RegisterTree(pBaseTree))
					{
						st_delete<CTreeRender>(pBaseTree);
						continue;
					}
					// 设置树的LOD
					adjustBaseTreeLodProfile(pBaseTree, (*itConst).second.fLodStart, (*itConst).second.fLodEnd);
				}
				// CN_MODIFY
				else if (mSTPackManager)
				{
					char* buf = NULL;
					int size = 0;
					mSTPackManager->extractPackFile(pSrtFilename, buf, size);
					if (pBaseTree->LoadTree((st_byte*)buf, size, false))
					{
						if (!m_cForest.RegisterTree(pBaseTree))
						{
							st_delete<CTreeRender>(pBaseTree);
							continue;
						}
						// 设置树的LOD
						adjustBaseTreeLodProfile(pBaseTree, (*itConst).second.fLodStart, (*itConst).second.fLodEnd);
					}
				}
				else
				{
					st_delete<CTreeRender>(pBaseTree);
					continue;
				}
				loadedBaseTrees.push_back(std::make_pair((*it).first, pBaseTree));
				// CN_MODIFY
				loadedBaseTreesPath.insert(std::make_pair(pBaseTree, pSrtFilename));
			}
			PrintSpeedTreeErrors( );
		}
		else
		{
			for (std::map<UInt, TreeDeclaration>::const_iterator it = treeDeclMap.begin(); it != treeDeclMap.end(); ++it)
			{
				//获取树资源路径
				const char* pSrtFilename = (*it).second.strPath.c_str();
				if (pSrtFilename == NULL || strlen(pSrtFilename) <= 0)
				{
					continue;
				}
				// 创建CTreeRender对象
				CTreeRender* pBaseTree = (CTreeRender*)m_cForest.AllocateTree();
				if (pBaseTree->LoadTree(pSrtFilename))
				{
					if (!m_cForest.RegisterTree(pBaseTree))
					{
						st_delete<CTreeRender>(pBaseTree);
						continue;
					}
					// 设置树的LOD
					adjustBaseTreeLodProfile(pBaseTree, (*it).second.fLodStart, (*it).second.fLodEnd);
				}
				// CN_MODIFY
				else if (mSTPackManager)
				{
					char* buf = NULL;
					int size = 0;
					mSTPackManager->extractPackFile(pSrtFilename, buf, size);
					if (pBaseTree->LoadTree((st_byte*)buf, size, false))
					{
						if (!m_cForest.RegisterTree(pBaseTree))
						{
							st_delete<CTreeRender>(pBaseTree);
							continue;
						}
						// 设置树的LOD
						adjustBaseTreeLodProfile(pBaseTree, (*it).second.fLodStart, (*it).second.fLodEnd);
					}
				}
				else
				{
					st_delete<CTreeRender>(pBaseTree);
					continue;
				}
				loadedBaseTrees.push_back(std::make_pair((*it).first, pBaseTree));
				// CN_MODIFY
				loadedBaseTreesPath.insert(std::make_pair(pBaseTree, pSrtFilename));
			}
		}

		//载入树的实例
		st_bool	bSuccess = false;

		// copy CArray<CTreeRender*> array to CArray<CTree*>
		const st_int32 numBaseTrees = st_int32(loadedBaseTrees.size( ));
		CLocalArray<CTree*> aBaseTreesCopy(numBaseTrees, "PopulateForest");
		for (st_int32 i = 0; i < numBaseTrees; ++i)
		{
			aBaseTreesCopy[i] = (CTree*) loadedBaseTrees[i].second;
		}
		
		// copy tree instance
		CArray<TInstanceArray> aaInstances;
		if (bSetInstance)
		{
			aaInstances.resize(numBaseTrees);

			for (st_int32 i = 0; i < numBaseTrees; ++i)
			{
				std::map<UInt, std::vector<STree>>::const_iterator itInst = treeInstanceMap.find(loadedBaseTrees[i].first);
				if (itInst != treeInstanceMap.end())
				{
					const std::vector<STree>& vecInstance = (*itInst).second;
					Int instanceNr = (Int)vecInstance.size();
					aaInstances[i].resize(instanceNr);
					for (Int j = 0; j < instanceNr; ++j)
					{
						CInstance& instance = aaInstances[i][j];
						instance.SetPos(SpeedTree::Vec3(vecInstance[j].vPos.x, vecInstance[j].vPos.y, vecInstance[j].vPos.z));
						Vec4 vOrin = vecInstance[j].vOrientation;
						MG::Vec3 axis;
						MG::Flt angle;
						Qua qua(vOrin.w ,vOrin.x, vOrin.y, vOrin.z);
						qua.ToAngleAxis(angle,axis);
						instance.SetRotation(angle);
						instance.SetScale(vecInstance[j].vScale.x);
					}
				}
			}
		}

		// setup a single population object
		CForest::SCompletePopulation sWholePop(numBaseTrees);

		// set base trees array
		sWholePop.m_aBaseTrees = aBaseTreesCopy;
		// set instances
		if (bSetInstance)
		{
			sWholePop.m_aaInstances = aaInstances;
		}

		bSuccess = m_cForest.PopulateAtOnce(sWholePop);

		// if population was successfully, a few CRITICAL CForest updates are necessary
		if (bSuccess)
		{
			// to avoid recomputing the forest's extents each time an instance is added, it's done at the end
			m_cForest.UpdateTreeCellExtents( );

			// set all cell's ContentsChanged flags to false)
			m_cForest.EndInitialPopulation( );
		}
		else
		{
			assert(0);
		}

		// gather and print forest stats
		CForest::SPopulationStats sPopulationStats;
		m_cForest.GetPopulationStats(sPopulationStats);
		//PrintForestStats(sPopulationStats);

		// setup billboard caps based on instances-per-cell stats
		st_int32 nMaxInstancesByCellPerBase = 1;
		for (st_int32 i = 0; i < st_int32(loadedBaseTrees.size( )); ++i)
		{
			CTreeRender* pTree = loadedBaseTrees[i].second;
			if (pTree == NULL)
			{
				continue;
			}
			st_int32 nMaxInstances = 1;
			CMap<const CTree*, st_int32>::const_iterator iFind = sPopulationStats.m_mMaxNumInstancesPerCellPerBase.find(pTree);
			if (iFind != sPopulationStats.m_mMaxNumInstancesPerCellPerBase.end( ))
			{
				nMaxInstances = st_max(nMaxInstances, iFind->second);
			}
			// CN_MODIFY
			CFixedString treefilename = loadedBaseTreesPath[pTree];
			CFixedString treepath = treefilename.Path();
			m_cForest.InitTreeGraphics(pTree, nMaxInstances, BHORZBILLBOARDS, treepath.c_str());
			nMaxInstancesByCellPerBase = st_max(nMaxInstancesByCellPerBase, nMaxInstances);
		}

		setForestCullReserves(MAX_NUM_VISIBLE_CELLS, nMaxInstancesByCellPerBase);

		const TTreeArray& aBaseTrees = m_cForest.GetBaseTrees( );
		if (!aBaseTrees.empty( ) && aBaseTrees[0] != NULL)
		{
			//m_cForest.SetWindLeader(&aBaseTrees[0]->GetWind( ));
			//m_cGrass.GetWind( ).SetWindLeader(&aBaseTrees[0]->GetWind( ));
		}

		return true;
	}

	void SpeedTreeSystem::clearBaseTree()
	{
		const TTreeArray& baseTreeArray = m_cForest.GetBaseTrees();
		Int iBaseCount = (Int)baseTreeArray.size();
		if (iBaseCount <= 0)
		{
			return;
		}

		std::vector<CTree*> baseTreeCopy;
		baseTreeCopy.resize(iBaseCount);
		
		for (Int i = 0; i < iBaseCount; ++i)
		{
			baseTreeCopy[i] = baseTreeArray[i];	
		}

		m_cForest.ClearInstances();
		for (Int i = 0; i < iBaseCount; ++i)
		{
			m_cForest.UnregisterTree(baseTreeCopy[i]);
			CTreeRender* pTree = (CTreeRender*)baseTreeCopy[i];
			pTree->DeleteGeometry(false);
			pTree->DeleteAllTmpHeapBlocks();
			pTree->ShutDown();
			st_delete<CTreeRender>(pTree);
			//st_uint32 heapSize = (st_int32)SpeedTreeSystem::g_siHeapMemoryUsed;
			//printf("%d\n", heapSize);
		}
		m_bForestPopulationChanged	= true;
	}
	//-----------------------------------------------------------------------
	void SpeedTreeSystem::clearGrass()
	{
/*
		TGrassCellArray* pCells = NULL;
		pCells = &m_sVisibleGrass.m_aVisibleCells;
		
		// gather some working parameters
		const st_int32 c_nNumCells = int(pCells->size( ));

		for (st_int32 nCell = 0; nCell < c_nNumCells; ++nCell)
		{
			// cell the cell and associated VBO
			CGrassCell* pCell = (*pCells)[nCell];
			assert(pCell);
			pCell->SetNumBlades(0);
			void* pVb = pCell->GetVbo();
			if (pVb != NULL)
			{
				delete[] pVb ;
			}
			pCell->SetVbo(NULL);
		}*/

		deleteAllGrass();
		m_bNotRender = true;
		//cull();
	}
	//-----------------------------------------------------------------------
	void SpeedTreeSystem::setGrassLod(Flt fStartFade, Flt fEndFade)
	{
		m_cGrass.SetLodRange(fStartFade, fEndFade);
	}
	//-----------------------------------------------------------------------
	void SpeedTreeSystem::getGrassLod(Flt& fStartFade, Flt& fEndFade)
	{
		m_cGrass.GetLodRange(fStartFade, fEndFade);
	}
	//-----------------------------------------------------------------------
	void SpeedTreeSystem::adjustBaseTreeLodProfile(CTreeRender* pBaseTree, Flt LodHigh, Flt LodLow)
	{
		SLodProfile sLodProfile = pBaseTree->GetLodProfile( );
		sLodProfile.m_fHighDetail3dDistance = LodHigh;
		sLodProfile.m_fLowDetail3dDistance = LodLow;
		//sLodProfile.Scale(fLodScale);
		(void) pBaseTree->SetLodProfile(sLodProfile);
	}

	//-----------------------------------------------------------------------
	st_bool SpeedTreeSystem::setForestCullReserves(st_int32 nMaxNumVisibleCells, st_int32 nMaxInstancesByCellPerBase)
	{
		st_bool bSuccess = true;

		// reserve memory in these SForestCullResults objects now to avoid 
		// allocations during the render loop
		bSuccess &= m_sVisibleTrees.Reserve(m_cForest.GetBaseTrees( ), 
			st_int32(m_cForest.GetBaseTrees( ).size( )), 
			nMaxNumVisibleCells, 
			nMaxInstancesByCellPerBase,
			BHORZBILLBOARDS);
		if (m_cForest.ShadowsAreEnabled( ))
		{
			for (st_int32 nShadowMap = 0; nShadowMap < c_nMaxNumShadowMaps; ++nShadowMap)
				bSuccess &= m_asLightCullResults[nShadowMap].Reserve(m_cForest.GetBaseTrees( ), 
				st_int32(m_cForest.GetBaseTrees( ).size( )), 
				nMaxNumVisibleCells, 
				nMaxInstancesByCellPerBase,
				BHORZBILLBOARDS);
		}

		return bSuccess;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::advance()
	{
		// update timer data
		m_cTimer.Stop( );
		m_fCurrentTime = m_cTimer.GetSec( );
		m_fFrameTime = m_fCurrentTime - m_fTimeMarker;
		m_fTimeMarker = m_fCurrentTime;

		// advance wind
		m_cForest.SetGlobalTime(m_fCurrentTime);
		m_cForest.AdvanceGlobalWind( );
#ifdef ACTIVE_GRASS
		m_cGrass.AdvanceWind(m_fCurrentTime);
#endif
		if (m_cStatsReporter.Update(m_fCurrentTime))
		{
			printf("\n%s", m_cStatsReporter.Report(m_cForest.GetRenderStats( ), true));
		}
		m_cForest.GetRenderStats( ).Reset( );
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::cull()
	{
		if (!m_bForestPopulationChanged && !m_bCameraChanged && !m_cForest.LightDirChanged( ) && !m_bGrassDirty)
			return;

		// statistics gathering
		CTimer cTimer;
		cTimer.Start( );
		SRenderStats& sRenderStats = m_cForest.GetRenderStats( );

#ifdef ACTIVE_GRASS
		if (m_cGrass.IsEnabled( ))
		{
			m_cGrass.Cull(m_cView, m_sVisibleGrass);
		}
#endif
		//trees
		m_cForest.CullAndComputeLOD(m_cView, m_sVisibleTrees, true);

		// shadow
		{
			(void) m_cForest.ComputeLightView(m_cForest.GetLightDir( ), m_cView.GetFrustumPoints( ), 0, m_acLightViews[0], 0.0f);
			m_acLightViews[0].SetLodRefPoint(m_cView.GetCameraPos( ));
			//m_acLightViews[0] = m_cLightView;
			//m_acLightViews[0].SetLodRefPoint(m_cView.GetCameraPos( ));
			m_cForest.CullAndComputeLOD(m_acLightViews[0], m_asLightCullResults[0], false);
		}

#ifdef ACTIVE_GRASS
		//Grass
		if (m_bRenderGrass && m_cGrass.IsEnabled( ) && !m_sVisibleGrass.m_aCellsToUpdate.empty( ) || m_bGrassDirty)
		{
			populateGrassCells( );
			m_bGrassDirty = false;
		}
#endif

		// records the total time to cull the forest, terrain, and grass, as well as populate
		// VB/IB buffers with billboards, terrain, and grass; normally stable but can cause
		// CPU spikes during heavy population events (e.g. where new grass, terrain, and billboard
		// buffer all need repopulation)
		cTimer.Stop( );
		sRenderStats.m_fCullAndPopulateTime += cTimer.GetMicroSec( );
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::setTransparentTextureMode(ETextureAlphaRenderMode eMode) const
	{
		// turn all modes off (no telling what render state the client application might be in before this call)
		CRenderState::SetBlending(false);
		CRenderState::SetAlphaTesting(false);
		CRenderState::SetAlphaToCoverage(false);

		switch (eMode)
		{
		case TRANS_TEXTURE_ALPHA_TESTING:
			CRenderState::SetAlphaTesting(true);
			break;
		case TRANS_TEXTURE_ALPHA_TO_COVERAGE:
			CRenderState::SetAlphaToCoverage(true);
			break;
		case TRANS_TEXTURE_BLENDING:
			CRenderState::SetBlending(true);
			break;
		default:
			// intentionally do nothing (TRANS_TEXTURE_NOTHING)
			break;
		}
	}

	//-----------------------------------------------------------------------
	SpeedTree::CView SpeedTreeSystem::getView(const CameraParam& cameraParam)
	{
		SpeedTree::CView view ;
		view.Set(cameraParam.cameraPos, cameraParam.projMatrix, cameraParam.viewMatrix, 
			cameraParam.nearClip, cameraParam.farClip);
		return view;
	}

	//-----------------------------------------------------------------------
	st_bool SpeedTreeSystem::renderForest(ERenderPassType eRenderPass)
	{
        // enable anisotropic filtering on the samplers in case we're not using fx files
        for (unsigned int i = 0; i < 12; ++i)
        {
        	DX9::Device( )->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        	DX9::Device( )->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
        	DX9::Device( )->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
            DX9::Device( )->SetSamplerState(i, D3DSAMP_MAXMIPLEVEL, 0);
            DX9::Device( )->SetSamplerState(i, D3DSAMP_MIPMAPLODBIAS, 1);
            Int m_nMaxAnisotropy = 5;
        	if (m_nMaxAnisotropy > 0 && i < 5)
        	{
        	    DX9::Device( )->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
        	    DX9::Device( )->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, m_nMaxAnisotropy);
        	}
        	else
        	    DX9::Device( )->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        }

		st_bool bSuccess = true;
		// forest
		{
			// set transparency state
			setTransparentTextureMode(ETextureAlphaRenderMode(m_uiTransparentTextureRenderMode));

			if (m_bRenderBranches)
				bSuccess &= m_cForest.RenderBranches(m_sVisibleTrees, eRenderPass, m_exceptTreeInstanceMap[eRenderPass]);

			if (m_bRenderFronds)
				bSuccess &= m_cForest.RenderFronds(m_sVisibleTrees, eRenderPass, m_exceptTreeInstanceMap[eRenderPass]);

			if (m_bRenderLeafMeshes)
				bSuccess &= m_cForest.RenderLeafMeshes(m_sVisibleTrees, eRenderPass, m_exceptTreeInstanceMap[eRenderPass]);

			if (m_bRenderLeafCards)
				bSuccess &= m_cForest.RenderLeafCards(m_sVisibleTrees, eRenderPass, m_cView, m_exceptTreeInstanceMap[eRenderPass]);

			if (m_bRenderBillboards)
				bSuccess &= m_cForest.RenderBillboards(m_sVisibleTrees, eRenderPass, m_cView, m_exceptTreeInstanceMap[eRenderPass]);
		}

		return bSuccess;
	}

	//-----------------------------------------------------------------------
    st_bool SpeedTreeSystem::renderForestIntoOneShadowMaps(CView& view)
    {
        st_bool bSuccess = true;

		// d3d10 allows A2C on render targets, so make sure to turn it off
		CRenderState::SetMultisampling(false);
		CRenderState::SetAlphaToCoverage(false);

		//const CView& cLightView = view/*m_acLightViews[0]*/;
		const CView& cLightView = view;	 //m_acLightViews[0];

		const SForestCullResults& cLightCull = m_asLightCullResults[0];

		if (m_cForest.BeginShadowMap(0, cLightView))
		{
			bSuccess &= m_cForest.UploadViewShaderParameters(cLightView);

			// branch geometry can be rendered with backfacing triangle removed, so a closer
			// tolerance can be used
			CRenderState::SetPolygonOffset(1.0f, 0.125f);

			if (m_bRenderBranches)
				bSuccess &= m_cForest.RenderBranches(cLightCull, SpeedTree::ERenderPassType(RENDER_PASS_SHADOW), m_exceptTreeInstanceMap[RENDER_PASS_SHADOW]);

			// the remaining geometry types cannot be backface culled, so we need a much
			// more aggressive offset
			CRenderState::SetPolygonOffset(10.0f, 1.0f);

			if (m_bRenderFronds)
				bSuccess &= m_cForest.RenderFronds(cLightCull, SpeedTree::ERenderPassType(RENDER_PASS_SHADOW), m_exceptTreeInstanceMap[RENDER_PASS_SHADOW]);
			if (m_bRenderLeafMeshes)
				bSuccess &= m_cForest.RenderLeafMeshes(cLightCull, SpeedTree::ERenderPassType(RENDER_PASS_SHADOW), m_exceptTreeInstanceMap[RENDER_PASS_SHADOW]);
			if (m_bRenderLeafCards)
				bSuccess &= m_cForest.RenderLeafCards(cLightCull, SpeedTree::ERenderPassType(RENDER_PASS_SHADOW), cLightView, m_exceptTreeInstanceMap[RENDER_PASS_SHADOW]);
		}

		CRenderState::SetMultisampling(false);
		setTransparentTextureMode(ETextureAlphaRenderMode(m_uiTransparentTextureRenderMode));
            
        return bSuccess;
    }

	//-----------------------------------------------------------------------
	Flt SpeedTreeSystem::getBaseTreeHeight(Int baseTreeID)
	{
		CTree* pBaseTree = getBaseTree(baseTreeID);
		if (pBaseTree == NULL)
		{
			return 0.f;
		}
		const CExtents& cTreeExtents = pBaseTree->GetExtents( );
		return CCoordSys::UpComponent(cTreeExtents.Max( ));
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::addInstance(Int baseTreeID, const MG::Vec3& pos, CInstance& cInstance)
	{
		CTree* pTree = getBaseTree(baseTreeID);
/*
		if (pTree == NULL)
		{
			return false;
			if (m_pTreeTemplateList == NULL || baseTreeID >= (Int)m_pTreeTemplateList->size())
			{
				return false;
			}

			const TTreeArray& treeArray = m_cForest.GetBaseTrees();
			
			Int oldBaseTreeCount = (Int)treeArray.size();
			Int newSize = oldBaseTreeCount + 1;
			TTreeArray allTreeArray(newSize);
			CArray<SpeedTree::TInstanceArray> allInstance(newSize);

			if (oldBaseTreeCount != 0)
			{	
				for (Int i = 0; i < oldBaseTreeCount; ++i)
				{
					allTreeArray[i] = treeArray[i];
					m_cForest.GetInstances(treeArray[i], allInstance[i]);
				}
			}

			CTreeRender* pBaseTree = (CTreeRender*)m_cForest.AllocateTree();
			// load it and register it with the CForest class
			const char* pSrtFilename = (*m_pTreeTemplateList)[baseTreeID].c_str( );
			if (pBaseTree->LoadTree(pSrtFilename))
			{
				if (!m_cForest.RegisterTree(pBaseTree))
				{
					return false;
				}
				adjustBaseTreeLodProfile(pBaseTree, m_sEnvSettings.m_fLodScale, 2.f);
			}
			else
			{
				return false;
			}

			
			allTreeArray[oldBaseTreeCount] = pBaseTree;
			CForest::SCompletePopulation sWholePop(newSize);
			sWholePop.m_aBaseTrees = allTreeArray;
			sWholePop.m_aaInstances = allInstance;

			if (m_cForest.PopulateAtOnce(sWholePop))
			{
				m_cForest.UpdateTreeCellExtents( );
			}
			else
			{
				return false;
			}
			cInstance.SetPos(SpeedTree::Vec3(pos.x, pos.y, pos.z));
			AddParam ap(pBaseTree, &cInstance);
			//ap.pBaseTree = pBaseTree;
			//ap.instance = &cInstance;
			m_vecAddInstance.push_back(ap);

			m_cForest.InitTreeGraphics(pBaseTree, 1, false);

			return true;
		}
*/

		return addInstance(pTree, pos, cInstance);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::instancePosition(Int baseTreeID, CInstance& cInstance, const MG::Vec3& pos)
	{
		CTree* pTree = getBaseTree(baseTreeID);

		return instancePosition(pTree, cInstance, pos);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::instanceRotate(Int baseTreeID,  CInstance& cInstance, Flt fRadians)
	{
		CTree* pTree = getBaseTree(baseTreeID);

		return instanceRotate(pTree, cInstance, fRadians);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::instanceScale(Int baseTreeID, CInstance& cInstance, Flt& scale)
	{
		CTree* pTree = getBaseTree(baseTreeID);

		return instanceScale(pTree, cInstance, scale);
	}

	void SpeedTreeSystem::getTreeExtents(Int baseTreeID, Vec3& vMin, Vec3& vMax)
	{
		CTree* pBaseTree = getBaseTree(baseTreeID);
		if (pBaseTree == NULL)
		{
			return;
		}
		const CExtents& cTreeExtents = pBaseTree->GetExtents( );
		const SpeedTree::Vec3& vsMin = cTreeExtents.Min();
		const SpeedTree::Vec3& vsMax = cTreeExtents.Max();
		vMin.x = vsMin.x; vMin.y = vsMin.y; vMin.z = vsMin.z;
		vMax.x = vsMax.x; vMax.y = vsMax.y; vMax.z = vsMax.z;
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::addInstance(CChar* pBaseTreeName, const MG::Vec3& pos, SpeedTree::CInstance& cInstance)
	{
		return addInstance(getBaseTree(pBaseTreeName), pos, cInstance);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::deleteInstance(CChar* pBaseTreeName, SpeedTree::CInstance& cInstance)
	{
		return deleteInstance(getBaseTree(pBaseTreeName), cInstance);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::instancePosition(CChar* pBaseTreeName, SpeedTree::CInstance& cInstance, const MG::Vec3& pos)
	{
		return instancePosition(getBaseTree(pBaseTreeName), cInstance, pos);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::instanceRotate(CChar* pBaseTreeName, SpeedTree::CInstance& cInstance, Flt fRadians)
	{
		return instanceRotate(getBaseTree(pBaseTreeName), cInstance, fRadians);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::instanceScale(CChar* pBaseTreeName, SpeedTree::CInstance& cInstance, Flt& scale)
	{
		return instanceScale(getBaseTree(pBaseTreeName), cInstance, scale);
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::getTreeExtents(CChar* pBaseTreeName, Vec3& vMin, Vec3& vMax)
	{
		CTree* pBaseTree = getBaseTree(pBaseTreeName);
		if (pBaseTree == NULL)
		{
			return;
		}
		const CExtents& cTreeExtents = pBaseTree->GetExtents( );
		const SpeedTree::Vec3& vsMin = cTreeExtents.Min();
		const SpeedTree::Vec3& vsMax = cTreeExtents.Max();
		vMin.x = vsMin.x; vMin.y = vsMin.y; vMin.z = vsMin.z;
		vMax.x = vsMax.x; vMax.y = vsMax.y; vMax.z = vsMax.z;
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::addExceptTreeInstance(Int baseTreeID, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass)
	{
		return addExceptTreeInstance(getBaseTree(baseTreeID), cInstance, renderPass);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::addExceptTreeInstance(CChar* pBaseTreeName, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass)
	{
		SpeedTree::CTree* pTree = getBaseTree(pBaseTreeName);

		return addExceptTreeInstance(pTree, cInstance, renderPass);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::addExceptTreeInstance(SpeedTree::CTree* pBaseTree, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass)
	{
		if (renderPass < RENDER_PASS_STANDARD || renderPass >= RENDER_PASS_NUM_TYPES)
		{
			return false;
		}

		m_exceptTreeInstanceMap[renderPass][pBaseTree].push_back(cInstance);

		return true;
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::delExceptTreeInstance(Int baseTreeID, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass)
	{
		return delExceptTreeInstance(getBaseTree(baseTreeID), cInstance, renderPass);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::delExceptTreeInstance(CChar* pBaseTreeName, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass)
	{
		SpeedTree::CTree* pTree = getBaseTree(pBaseTreeName);

		return delExceptTreeInstance(pTree, cInstance, renderPass);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::delExceptTreeInstance(SpeedTree::CTree* pBaseTree, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass)
	{
		if (renderPass < RENDER_PASS_STANDARD || renderPass >= RENDER_PASS_NUM_TYPES)
		{
			return false;
		}

		TBaseToInstanceMap::iterator it = m_exceptTreeInstanceMap[renderPass].find(pBaseTree);
		if (it == m_exceptTreeInstanceMap[renderPass].end())
		{
			return false;
		}

		TInstanceArray& instArray = it->second;
		for (TInstanceArray::iterator itInst = instArray.begin(); itInst != instArray.end(); )
		{
			if (cInstance == *itInst)
			{
				itInst = instArray.erase(itInst);
			}
			else
			{
				++itInst;
			}
		}

		return true;
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::deleteInstance(Int baseTreeID, CInstance& cInstance)
	{
		CTree* pTree = getBaseTree(baseTreeID);

		return deleteInstance(pTree, cInstance);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::isExceptTreeInstance(Int baseTreeID, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass)
	{
		CTree* pTree = getBaseTree(baseTreeID);

		return isExceptTreeInstance(pTree, cInstance, renderPass);
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::getGrassListByPosRadiu(const MG::Vec3& vPos, const MG::Flt fRadiu, std::list<SGrassBoard>& grassList)
	{
		grassList.clear();

		std::vector<const DataCell*> grassCells;
		getGrassCellPtrsByPosRadiu(vPos, fRadiu, grassCells);
		if (!grassCells.empty())
		{
			std::vector<const DataCell*>::iterator cellItr= grassCells.begin();
			for (; cellItr!=grassCells.end(); ++cellItr)
			{
				if (!(*cellItr)->m_grassBoardList.empty())
				{
					grassList.insert(grassList.begin(), (*cellItr)->m_grassBoardList.begin(), (*cellItr)->m_grassBoardList.end());
				}
			}
		}
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::getGrassCellPtrsByPosRadiu(const MG::Vec3& vPos, const MG::Flt fRadiu, std::vector<const DataCell*>& grassCells)
	{
		SpeedTree::Vec3 centerPos(vPos.x, vPos.y, vPos.z);

		Flt cellSize = (Flt)m_grassCellMap.GetCellSize();
		Flt halfCellSize = cellSize/2.0f;
		if (2*fRadiu > cellSize)
		{
			MG::U32 sideCellNum = floor(2*fRadiu/cellSize);
			MG::Flt offset = (sideCellNum-1)*cellSize + halfCellSize;
			SpeedTree::Vec3 topLeftPos = SpeedTree::Vec3(centerPos.x- offset, centerPos.y, centerPos.z - offset);
			for (int i=0; i<sideCellNum; ++i)
			{
				for (int j=0; j<sideCellNum; ++j)
				{
					SpeedTree::Vec3 pos(topLeftPos.x+i*cellSize+halfCellSize, topLeftPos.y, topLeftPos.z+j*cellSize+halfCellSize);

					st_float32 distance = centerPos.Distance(pos);
					if (distance <= fRadiu)
					{
						const DataCell* pCell = m_grassCellMap.GetCellPtrByPos(pos);
						if (pCell != NULL)
							grassCells.push_back(pCell);
					}
				}
			}
		}
		else
		{
			const DataCell* pCell = m_grassCellMap.GetCellPtrByPos(centerPos);
			if (pCell != NULL)
				grassCells.push_back(pCell);
		}
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::isExceptTreeInstance(SpeedTree::CTree* pBaseTree, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass)
	{
		if (renderPass < RENDER_PASS_STANDARD || renderPass >= RENDER_PASS_NUM_TYPES)
		{
			return true;
		}

		TBaseToInstanceMap::iterator it = m_exceptTreeInstanceMap[renderPass].find(pBaseTree);
		if (it == m_exceptTreeInstanceMap[renderPass].end())
		{
			return true;
		}

		TInstanceArray& instArray = it->second;
		for (TInstanceArray::iterator itInst = instArray.begin(); itInst != instArray.end(); ++itInst)
		{
			if (cInstance == *itInst)
			{
				return true;
			}
		}

		return false;
	}

	//-----------------------------------------------------------------------
	Flt SpeedTreeSystem::getBaseTreeHeight(CChar* pBaseTreeName)
	{
		CTree* pBaseTree = getBaseTree(pBaseTreeName);
		if (pBaseTree == NULL)
		{
			return 0.f;
		}
		const CExtents& cTreeExtents = pBaseTree->GetExtents( );
		return CCoordSys::UpComponent(cTreeExtents.Max( ));
	}

	Bool SpeedTreeSystem::addInstance(CTree* pBaseTree, const MG::Vec3& pos, SpeedTree::CInstance& cInstance)
	{
		if (pBaseTree == NULL)
		{
			return false;
		}

		cInstance.SetPos(SpeedTree::Vec3(pos.x, pos.y, pos.z));
		st_bool bAdded = m_cForest.AddInstances(pBaseTree, &cInstance, 1);

		m_cForest.UpdateTreeCellExtents();

		m_bForestPopulationChanged = true;

		//addExceptTreeInstance(pBaseTree, cInstance);

		return bAdded;
	}

	Bool SpeedTreeSystem::deleteInstance(CTree* pBaseTree, SpeedTree::CInstance& cInstance)
	{
		if (pBaseTree == NULL)
		{
			return false;
		}

		st_bool bDelSuccess = m_cForest.DeleteInstances(pBaseTree, &cInstance, 1, true);
		// force cull engine to adjust to the changes
		m_cForest.UpdateTreeCellExtents( );

		m_bForestPopulationChanged = true;

		return bDelSuccess;
	}

	Bool SpeedTreeSystem::instancePosition(CTree* pBaseTree, SpeedTree::CInstance& cInstance, const MG::Vec3& pos)
	{
		if (pBaseTree == NULL)
		{
			return false;
		}

		CInstance newInstance = cInstance;
		newInstance.SetPos(SpeedTree::Vec3(pos.x, pos.y, pos.z));
		Bool bChangedSuccess = m_cForest.ChangeInstance(pBaseTree, cInstance, newInstance);

		cInstance.SetPos(SpeedTree::Vec3(pos.x, pos.y, pos.z));

		return bChangedSuccess;
	}

	Bool SpeedTreeSystem::instanceRotate(CTree* pBaseTree,  SpeedTree::CInstance& cInstance, Flt fRadians)
	{
		if (pBaseTree == NULL)
		{
			return false;
		}

		CInstance newInstance = cInstance;
		newInstance.SetRotation(fRadians);
		Bool bChangeSuccess = m_cForest.ChangeInstance(pBaseTree, cInstance, newInstance);

		cInstance.SetRotation(fRadians);

		return bChangeSuccess;
	}

	Bool SpeedTreeSystem::instanceScale(CTree* pBaseTree, SpeedTree::CInstance& cInstance, Flt& scale)
	{
		if (pBaseTree == NULL)
		{
			return false;
		}

		CInstance newInstance = cInstance;
		newInstance.SetScale(scale);
		bool bChangeSuccess = m_cForest.ChangeInstance(pBaseTree, cInstance, newInstance);

		cInstance.SetScale(scale);

		return bChangeSuccess;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::setGrassImageRowCol(UInt row, UInt col)
	{
		m_grassImageRow = row;
		m_grassImageCol = col;
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::addGrass(UInt uGrassImageID, const MG::Vec3& vPos, Flt w, Flt h, Flt rtw, Flt ltw, Flt lbw, Flt rbw,
		UInt& uIndex, Int& row, Int& col)
	{	
		DataCell* pCell = m_grassCellMap.GetCellPtrByPos_Add(SpeedTree::Vec3(vPos.x, vPos.y, vPos.z));
		if (pCell == NULL)
		{
			return false;
		}
		
		if (!m_cGrass.IsEnabled())
		{
			MG_LOG(out_error, "Grass Image not exist\n");
			return false;
		}

		//const Flt* pTexCoords = m_cGrass.GetBladeTexCoords(uGrassImageID, false);
		//if (pTexCoords != NULL)
		if (m_BitmapArrayRects.size() > uGrassImageID)
		{
			MG::RectF grassRect = m_BitmapArrayRects[uGrassImageID];

			SGrassBoard grassBoard;
			grassBoard.pos(vPos);
			//grassBoard.uv(pTexCoords[0], pTexCoords[1], pTexCoords[2], pTexCoords[1], pTexCoords[2], pTexCoords[3], pTexCoords[0], pTexCoords[3]);
			bool bMirror = rand()%1;
			if (bMirror)
			{
				grassBoard.uv(grassRect.right, grassRect.top, grassRect.left, grassRect.top, grassRect.left, grassRect.bottom, grassRect.right, grassRect.bottom); //逆时针0,1,2,3
			}
			else
			{
				grassBoard.uv(grassRect.left, grassRect.top, grassRect.right, grassRect.top, grassRect.right, grassRect.bottom, grassRect.left, grassRect.bottom); //顺时针0,1,2,3
			}
			
			grassBoard.size(w, h);
			grassBoard.windWeight(rtw, ltw, lbw, rbw);
			uIndex = pCell->addGrassBoard(grassBoard);
			if (uIndex == 0xFFFFFFFF)
			{
				return false;
			}
			row = pCell->Row();
			col = pCell->Col();

			m_bGrassDirty = true;

			return true;
		}
		else
		{
			MG_LOG(out_error, "GrassImageID:%d UV is not exist\n", uGrassImageID);
		}

		return false;
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::deleteGrass(Int iRow, Int iCol, UInt uGrassId)
	{
		DataCell* pCell = (DataCell*)m_grassCellMap.GetCellPtrByRowCol(iRow, iCol);
		if (pCell == NULL)
		{
			assert(0);
			return false;
		}

		m_bGrassDirty = true;

		return pCell->deleteGrassBoard(uGrassId);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::deleteAllGrass()
	{
		for (CCellContainer<DataCell>::TCellIterator it = m_grassCellMap.begin(); it != m_grassCellMap.end(); ++it)
		{
			DataCell& dataCell = it->second;
			dataCell.m_grassBoardList.clear();
		}
		m_grassCellMap.clear();
		m_bGrassDirty = true;
		return true;
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::grassPosition(Int iRow, Int iCol, UInt uGrassId, MG::Vec3& vPos)
	{
		DataCell* pCell = (DataCell*)m_grassCellMap.GetCellPtrByRowCol(iRow, iCol);
		if (pCell == NULL)
		{
			return false;
		}

		return pCell->getPos(uGrassId, vPos);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::setGrassPosition(Int iRow, Int iCol, UInt uGrassId, const MG::Vec3& vPos)
	{
		DataCell* pCell = (DataCell*)m_grassCellMap.GetCellPtrByRowCol(iRow, iCol);
		if (pCell == NULL)
		{
			return false;
		}

		pCell->setPos(uGrassId, vPos);

		m_bGrassDirty = true;

		return true;
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::setGrassSize(Int iRow, Int iCol, UInt uGrassId, Flt w, Flt h)
	{
		DataCell* pCell = (DataCell*)m_grassCellMap.GetCellPtrByRowCol(iRow, iCol);
		if (pCell == NULL)
		{
			return false;
		}

		pCell->setSize(uGrassId, w, h);

		m_bGrassDirty = true;

		return true;
	}
	
	//-----------------------------------------------------------------------
	Flt SpeedTreeSystem::getGrassW(Int iRow, Int iCol, UInt uGrassId)
	{
		DataCell* pCell = (DataCell*)m_grassCellMap.GetCellPtrByRowCol(iRow, iCol);
		if (pCell == NULL)
		{
			return 0.f;
		}

		return pCell->width(uGrassId);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::setGrassW(Int iRow, Int iCol, UInt uGrassId, Flt w)
	{
		DataCell* pCell = (DataCell*)m_grassCellMap.GetCellPtrByRowCol(iRow, iCol);
		if (pCell == NULL)
		{
			return false;
		}

		pCell->width(uGrassId, w);

		m_bGrassDirty = true;

		return true;
	}

	//-----------------------------------------------------------------------
	Flt SpeedTreeSystem::getGrassH(Int iRow, Int iCol, UInt uGrassId)
	{
		DataCell* pCell = (DataCell*)m_grassCellMap.GetCellPtrByRowCol(iRow, iCol);
		if (pCell == NULL)
		{
			return 0.f;
		}

		return pCell->height(uGrassId);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::setGrassH(Int iRow, Int iCol, UInt uGrassId, Flt h)
	{
		DataCell* pCell = (DataCell*)m_grassCellMap.GetCellPtrByRowCol(iRow, iCol);
		if (pCell == NULL)
		{
			return false;
		}

		pCell->height(uGrassId, h);

		m_bGrassDirty = true;

		return true;
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::setGrassWindWeight(Int iRow, Int iCol, UInt uGrassId, Flt rtw, Flt ltw, Flt lbw, Flt rbw)
	{
		DataCell* pCell = (DataCell*)m_grassCellMap.GetCellPtrByRowCol(iRow, iCol);
		if (pCell == NULL)
		{
			return false;
		}

		pCell->windWeight(uGrassId, rtw, ltw, lbw,rbw);

		m_bGrassDirty = true;

		return true;
	}

	//-----------------------------------------------------------------------
	DataCell* SpeedTreeSystem::getCellPtrByPos_Add(const MG::Vec3& vPos)
	{
		return m_grassCellMap.GetCellPtrByPos_Add(SpeedTree::Vec3(vPos.x, vPos.y, vPos.z));
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::populateGrassCells(void)
	{
		TGrassCellArray* pCells = NULL;
		if ( EngineMain::getInstance().getMode() == EM_EDITOR )
		{
			//MG_LOG(out_error, "Cell Editor Mode\n");
			pCells = &m_sVisibleGrass.m_aVisibleCells;
		}
		else
		{
			pCells = &m_sVisibleGrass.m_aCellsToUpdate;
			//MG_LOG(out_error, "Cell Game Mode\n");
		}
		// gather some working parameters
		const st_int32 c_nNumCells = int(pCells->size( ));
		//MG_LOG(out_error, "Cell Nr:%d\n", c_nNumCells);
		//if (c_nNumCells >= MAX_NUM_VISIBLE_CELLS)
		//{
			//MG_LOG(out_error, "Cell Nr:%d\n", c_nNumCells);
			//return;
		//}

		for (st_int32 nCell = 0; nCell < c_nNumCells; ++nCell)
		{
			// cell the cell and associated VBO
			CGrassCell* pCell = (*pCells)[nCell];
			assert(pCell);
			DataCell* pDataCell = (DataCell*)m_grassCellMap.GetCellPtrByRowCol(pCell->Row(), pCell->Col());
			if (pDataCell == NULL)
			{
				continue;
			}
			
			CGeometryBuffer* pVbo = (CGeometryBuffer*) pCell->GetVbo( );
			if (pVbo)
			{
				//MG_LOG(out_error, "Cell Row:%d Col:%d\n", pCell->Row(), pCell->Col());
				std::list<SGrassBoard>& grassBoardList = pDataCell->m_grassBoardList;
				assert((Int)grassBoardList.size() < MAX_GRASS_PRE_CELLS);
				if ((Int)grassBoardList.size() >= MAX_GRASS_PRE_CELLS)
				{
					continue;
				}
				memset((void*)m_tmpGrassVertex, 0, sizeof(m_tmpGrassVertex));
				SGrassVertex* grassVertexArray = m_tmpGrassVertex;
				int iGrassBoardCount = 0;
				for (std::list<SGrassBoard>::iterator it = grassBoardList.begin(); it != grassBoardList.end(); ++it)
				{
					grassVertexArray[iGrassBoardCount * 4 + 0] = (*it).m_vertex[0];
					grassVertexArray[iGrassBoardCount * 4 + 1] = (*it).m_vertex[1];
					grassVertexArray[iGrassBoardCount * 4 + 2] = (*it).m_vertex[2];
					grassVertexArray[iGrassBoardCount * 4 + 3] = (*it).m_vertex[3];

					iGrassBoardCount++;
				}
				pCell->SetNumBlades(iGrassBoardCount);
				
				void* pVoid = NULL;
				if (iGrassBoardCount > 0)
				{
					pVoid = grassVertexArray;
				}
				pVbo->OverwriteVertices(pVoid, iGrassBoardCount * 4, 0);
			}
		}
	}

	//-----------------------------------------------------------------------
	st_bool SpeedTreeSystem::renderGrass(void)
	{
		st_bool bSuccess = false;

		if (m_bRenderGrass && m_cGrass.IsEnabled( ))
		{
            // enable anisotropic filtering on the samplers in case we're not using fx files
            for (unsigned int i = 0; i < 12; ++i)
            {
                DX9::Device( )->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
                DX9::Device( )->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
                DX9::Device( )->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
                DX9::Device( )->SetSamplerState(i, D3DSAMP_MAXMIPLEVEL, 0);
                DX9::Device( )->SetSamplerState(i, D3DSAMP_MIPMAPLODBIAS, 15);

                Int m_nMaxAnisotropy = 5;
                if (m_nMaxAnisotropy > 0 && i < 5)
                {
                    DX9::Device( )->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
                    DX9::Device( )->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, m_nMaxAnisotropy);
                }
                else
                    DX9::Device( )->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
            }

			// set grass render states
			setTransparentTextureMode(ETextureAlphaRenderMode(m_uiTransparentTextureRenderMode));

			// grass isn't part of the z-prepass; should always use DEPTHTEST_LESS
			CRenderState::SetDepthTestFunc(DEPTHTEST_LESS);
			CRenderState::SetDepthMask(true);

			// update grass wind parameters
			m_cForest.UploadWindParams(m_cGrass.GetWind( ));

			// draw all of the grass cells in one call
			bSuccess = m_cGrass.Render(m_sVisibleGrass, RENDER_PASS_STANDARD, m_vLightDir, m_cForest.GetRenderInfo( ).m_sGrassLightMaterial, &m_cForest.GetRenderStats( ));

			// restore default forest rendering states
			CRenderState::SetDepthTesting(true);
			setTransparentTextureMode(ETextureAlphaRenderMode(m_uiTransparentTextureRenderMode));
		}

		return bSuccess;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::setLightDir(const MG::Vec3& vDir)
	{
		m_vLightDir = SpeedTree::Vec3(vDir.x, vDir.y, vDir.z);
		m_fLightAngleHorz = atan2(m_vLightDir.y, m_vLightDir.x) + c_fPi;
		m_fLightAngleVert = -asin(m_vLightDir.z);

		m_cForest.SetLightDir(m_vLightDir);
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::updateLightDir(void)
	{
		// keep the light above the horizon
		m_fLightAngleVert = Clamp(m_fLightAngleVert, 0.0f, c_fPi);

		// light direction is specified as it is in DirectX and OpenGL: the vector is the direction the light's
		// pointing; however, the vertex shaders expect a negated value during the actual constant upload
		m_vLightDir = CCoordSys::ConvertFromStd(-cosf(m_fLightAngleHorz) * cosf(m_fLightAngleVert), -sinf(m_fLightAngleHorz) * cosf(m_fLightAngleVert), -sinf(m_fLightAngleVert));
		m_vLightDir.Normalize( );

		m_cForest.SetLightDir(m_vLightDir);
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::setLightMtl(const MG::Color& cAmbient, const MG::Color& cDiffuse, const MG::Color& cSpecular, const MG::Color& cEmissive)
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();

		renderInfo.m_sLightMaterial.m_vAmbient.Set(cAmbient.r, cAmbient.g, cAmbient.b);
		renderInfo.m_sLightMaterial.m_vDiffuse.Set(cDiffuse.r, cDiffuse.g, cDiffuse.b);
		renderInfo.m_sLightMaterial.m_vSpecular.Set(cSpecular.r, cSpecular.g, cSpecular.b);
		renderInfo.m_sLightMaterial.m_vEmissive.Set(cEmissive.r, cEmissive.g, cEmissive.b);

		m_cForest.SetRenderInfo(renderInfo);
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::setGrassLightMtl(const MG::Color& cAmbient, const MG::Color& cDiffuse, const MG::Color& cSpecular, const MG::Color& cEmissive)
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();

		renderInfo.m_sGrassLightMaterial.m_vAmbient.Set(cAmbient.r, cAmbient.g, cAmbient.b);
		renderInfo.m_sGrassLightMaterial.m_vDiffuse.Set(cDiffuse.r, cDiffuse.g, cDiffuse.b);
		renderInfo.m_sGrassLightMaterial.m_vSpecular.Set(cSpecular.r, cSpecular.g, cSpecular.b);
		renderInfo.m_sGrassLightMaterial.m_vEmissive.Set(cEmissive.r, cEmissive.g, cEmissive.b);

		m_cForest.SetRenderInfo(renderInfo);
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::setFog(const MG::Color& color, Flt fStartDistance, Flt fEndDistance)
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();

		renderInfo.m_vFogColor.Set(color.r, color.g, color.b);
		renderInfo.m_fFogStartDistance = fStartDistance;
		renderInfo.m_fFogEndDistance = fEndDistance;

		m_cForest.SetRenderInfo(renderInfo);
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::setFarClip(float farClip)
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();
		renderInfo.m_fVisibility = farClip;
		m_cForest.SetRenderInfo(renderInfo);
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::initLightMtl(SMaterial& mtl)
	{
		mtl.m_vAmbient.Set(1.0f, 1.0f, 1.0f, 1.0f);
		mtl.m_vDiffuse.Set(1.0f, 1.0f, 1.0f, 1.0f);
		mtl.m_vSpecular.Set(1.0f, 1.0f, 1.0f, 1.0f);
		mtl.m_vEmissive.Set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::initGrassWind()
	{
		CWind::SParams& grassPara = m_grassWindParam;
		grassPara.m_fStrengthResponse = 6.f;
		grassPara.m_fDirectionResponse = 1.f;
		grassPara.m_fWindHeightOffset = 0.05f;
		grassPara.m_afOscillationValues[CWind::PRIMARY][CWind::DISTANCE_LOW_WIND] = 0.5f;
		grassPara.m_afOscillationValues[CWind::PRIMARY][CWind::DISTANCE_HIGH_WIND] = 1.0f;
		grassPara.m_afOscillationValues[CWind::PRIMARY][CWind::FREQ_LOW_WIND] = 1.f;
		grassPara.m_afOscillationValues[CWind::PRIMARY][CWind::FREQ_HIGH_WIND] = 2.f;
		grassPara.m_afOscillationValues[CWind::SECONDARY][CWind::DISTANCE_LOW_WIND] = 0.2f;
		grassPara.m_afOscillationValues[CWind::SECONDARY][CWind::DISTANCE_HIGH_WIND] = 0.1f;
		grassPara.m_afOscillationValues[CWind::SECONDARY][CWind::FREQ_LOW_WIND] = 5.f;
		grassPara.m_afOscillationValues[CWind::SECONDARY][CWind::FREQ_HIGH_WIND] = 14.f;
		grassPara.m_fGustFrequency = 0.4f;
		grassPara.m_fGustPrimaryDistance = 2.f;
		grassPara.m_fGustStrengthMin = 0.35f;
		grassPara.m_fGustStrengthMax = 0.65f;
		grassPara.m_fGustDurationMin = 0.1f;
		grassPara.m_fGustDurationMax = 1.5f;
		grassPara.m_afExponents[CWind::PRIMARY] = 2.f;
		grassPara.m_afExponents[CWind::SECONDARY] = 1.f;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::setWindEnable(Bool bEnable)
	{
		m_cForest.EnableWind(bEnable);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::isWindEnabled()
	{
		return m_cForest.IsWindEnabled();
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::setGlobalWindStrength(float fStrength)
	{
		m_cForest.SetGlobalWindStrength(fStrength);
	}

	//-----------------------------------------------------------------------
	Flt SpeedTreeSystem::getGlobalWindStrength(void) const
	{
		return m_cForest.GetGlobalWindStrength();
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::setGlobalWindDirection(const MG::Vec3& vDir)
	{
		m_cForest.SetGlobalWindDirection(SpeedTree::Vec3(vDir.x, vDir.y, vDir.z));
	}

	//-----------------------------------------------------------------------
	MG::Vec3 SpeedTreeSystem::getGlobalWindDirection(void) const
	{
		const SpeedTree::Vec3 vDir = m_cForest.GetGlobalWindDirection();
		return MG::Vec3(vDir.x, vDir.y, vDir.z);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::EnableSpecularLight()
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();
		return renderInfo.m_bSpecularLighting;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::EnableSpecularLight(Bool bEnable)
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();
		renderInfo.m_bSpecularLighting = bEnable;
		m_cForest.SetRenderInfo(renderInfo);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::EnableTransmissionLight()
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();
		return renderInfo.m_bTransmissionLighting;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::EnableTransmissionLight(Bool bEnable)
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();
		renderInfo.m_bTransmissionLighting = bEnable;
		m_cForest.SetRenderInfo(renderInfo);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::EnableDetailLayer()
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();
		return renderInfo.m_bDetailLayer;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::EnableDetailLayer(Bool bEnable)
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();
		renderInfo.m_bDetailLayer = bEnable;
		m_cForest.SetRenderInfo(renderInfo);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::EnableDetailNormalMap()
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();
		return renderInfo.m_bDetailNormalMapping;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::EnableDetailNormalMap(Bool bEnable)
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();
		renderInfo.m_bDetailNormalMapping = bEnable;
		m_cForest.SetRenderInfo(renderInfo);
	}

	//-----------------------------------------------------------------------
	Bool SpeedTreeSystem::EnableAmbientContrast()
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();
		return renderInfo.m_bAmbientContrast;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::EnableAmbientContrast(Bool bEnable)
	{
		SForestRenderInfo renderInfo = m_cForest.GetRenderInfo();
		renderInfo.m_bAmbientContrast = bEnable;
		m_cForest.SetRenderInfo(renderInfo);
	}

	//-----------------------------------------------------------------------
	CTree* SpeedTreeSystem::getBaseTree(Int baseTreeID)
	{
		if (m_pTreeDecl == NULL)
		{
			return NULL;
		}

		std::map<UInt, TreeDeclaration>::iterator it = (*m_pTreeDecl).find(baseTreeID);
		if (it == (*m_pTreeDecl).end())
		{
			return NULL;
		}
		return getBaseTree(it->second.strPath.c_str());

		/*
		const TTreeArray& treeArray = m_cForest.GetBaseTrees();
		if (baseTreeID >= (int)treeArray.size())
		{
			return false;
		}

		return treeArray[baseTreeID];
*/
	}

	//-----------------------------------------------------------------------
	SpeedTree::CTree* SpeedTreeSystem::getBaseTree(CChar* baseTreeName)
	{
		const TTreeArray& treeArray = m_cForest.GetBaseTrees();
		for (Int i = 0; i < (Int)treeArray.size(); ++i)
		{
			//CTree* pBaseTree = treeArray[i];
			const st_char* pFileName = treeArray[i]->GetFilename();
			if (strcmp(pFileName, baseTreeName) == 0)
			{
				return treeArray[i];
			}
		}
		return NULL;
	}

	//-----------------------------------------------------------------------
	void SpeedTreeSystem::setGrassPerturbCircle( const Vec3& vPos, const Flt fRadiu )
	{
		//std::list<SGrassBoard> grassList;
		//getGrassListByPosRadiu(vPos, fRadiu, grassList);

		//std::list<SGrassBoard>::iterator itr = grassList.begin();
		//for (; itr!=grassList.end(); ++itr)
		//{
		//	SpeedTree::Vec3 grassPos;
		//	grassPos = itr->m_vertex[0].m_vPosition;
		//	Flt distance = grassPos.Distance(SpeedTree::Vec3(vPos.x,vPos.y,vPos.z));
		//	if (distance < fRadiu)
		//	{
		//		Flt perturb = (fRadiu-distance)/fRadiu; //离扰动点越远受到影响越小
		//		itr->updatePerturb(perturb);
		//	}
		//}

		//if (grassList.size() > 0)
		//{
		//	m_bGrassDirty = true;
		//}

		TGrassCellArray* pCells = NULL;
		//if (isEditorMode())
		{
			pCells = &m_sVisibleGrass.m_aVisibleCells;
		}
		//else
		//{
		//	pCells = &m_sVisibleGrass.m_aCellsToUpdate;
		//}
		// gather some working parameters
		const st_int32 c_nNumCells = int(pCells->size( ));

		for (st_int32 nCell = 0; nCell < c_nNumCells; ++nCell)
		{
			// cell the cell and associated VBO
			CGrassCell* pCell = (*pCells)[nCell];
			if (pCell == NULL)
				continue;
			DataCell* pDataCell = (DataCell*)m_grassCellMap.GetCellPtrByRowCol(pCell->Row(), pCell->Col());
			if (pDataCell == NULL)
			{
				continue;
			}

			//先判断cell在不在影响范围内
			SpeedTree::CExtents externs = pCell->GetExtents();
			st_float32 cellRadiu = externs.ComputeRadiusFromCenter2D();
			SpeedTree::Vec3 cellPos = pCell->GetCenter();
			Flt dis = cellPos.Distance(SpeedTree::Vec3(vPos.x,vPos.y,vPos.z));
			Flt needDis = fRadiu + cellRadiu;
			if (dis > needDis)
			{
				continue;
			}

			//保存脏的草格子
			m_dirtyGrassCellset.insert(pDataCell);

			CGeometryBuffer* pVbo = (CGeometryBuffer*) pCell->GetVbo( );
			if (pVbo)
			{
				std::vector<SGrassVertex> grassVertexArray;
				std::list<SGrassBoard>& grassBoardList = pDataCell->m_grassBoardList;
				grassVertexArray.resize(grassBoardList.size() * 4);
				int iGrassBoardCount = 0;
				for (std::list<SGrassBoard>::iterator it = grassBoardList.begin(); it != grassBoardList.end(); ++it)
				{
					SpeedTree::Vec3 centerPos(vPos.x,vPos.y,vPos.z) ;
					SpeedTree::Vec3 grassPos;
					grassPos = it->m_vertex[0].m_vPosition;
					Flt distance = grassPos.Distance(centerPos);

					clock_t curTime = (Flt)clock()/(Flt)CLOCKS_PER_SEC ;

					//判断草是否在影响范围内，并且上一次扰动是在0.3秒前(避免频繁扰动)
					//if (distance < fRadiu && (curTime - startPerturbTime) > 0.3)
					if (distance < fRadiu)
					{
						Flt scale = 1.0f;
						Flt perturb = (fRadiu-distance)/fRadiu*scale; //离扰动点越远受到影响越小
						//it->updatePerturb(perturb);

						Flt curPerturbRadian = it->m_vertex[0].m_fPerturb[1];
						Flt oldPerturb = it->m_vertex[0].m_fPerturb[3];

						//更新晃动开始时间
						Flt lastUpdateTime = curTime;

						//如果当前草是静止的则直接写入晃动信息,否则更新晃动信息
						if (COMPARE_FLOAT(oldPerturb,0.0f))
						{
							it->m_vertex[0].m_fPerturb[0] = lastUpdateTime;
							it->m_vertex[1].m_fPerturb[0] = lastUpdateTime;
							it->m_vertex[2].m_fPerturb[0] = lastUpdateTime;
							it->m_vertex[3].m_fPerturb[0] = lastUpdateTime;

							it->m_vertex[0].m_fPerturb[2] = m_needPerturRadin*perturb;
							it->m_vertex[1].m_fPerturb[2] = m_needPerturRadin*perturb;
							it->m_vertex[2].m_fPerturb[2] = m_needPerturRadin*perturb;
							it->m_vertex[3].m_fPerturb[2] = m_needPerturRadin*perturb;

							//更新晃动系数
							it->m_vertex[0].m_fPerturb[3] = perturb;
							it->m_vertex[1].m_fPerturb[3] = perturb;
							it->m_vertex[2].m_fPerturb[3] = perturb;
							it->m_vertex[3].m_fPerturb[3] = perturb;
						}
						//如果当前晃动系数比旧的大则更新需要晃动的角度
						else if (oldPerturb < perturb)
						{
							Flt newNeedPerturbRadin = m_needPerturRadin*perturb+curPerturbRadian;
							it->m_vertex[0].m_fPerturb[2] = newNeedPerturbRadin;
							it->m_vertex[1].m_fPerturb[2] = newNeedPerturbRadin;
							it->m_vertex[2].m_fPerturb[2] = newNeedPerturbRadin;
							it->m_vertex[3].m_fPerturb[2] = newNeedPerturbRadin;

							//更新晃动系数
							it->m_vertex[0].m_fPerturb[3] = perturb;
							it->m_vertex[1].m_fPerturb[3] = perturb;
							it->m_vertex[2].m_fPerturb[3] = perturb;
							it->m_vertex[3].m_fPerturb[3] = perturb;
						}

					}
					grassVertexArray[iGrassBoardCount * 4 + 0] = (*it).m_vertex[0];
					grassVertexArray[iGrassBoardCount * 4 + 1] = (*it).m_vertex[1];
					grassVertexArray[iGrassBoardCount * 4 + 2] = (*it).m_vertex[2];
					grassVertexArray[iGrassBoardCount * 4 + 3] = (*it).m_vertex[3];

					iGrassBoardCount++;
				}
				pCell->SetNumBlades((st_int32)grassBoardList.size());

				void* pVoid = NULL;
				if (!grassVertexArray.empty())
				{
					pVoid = &grassVertexArray[0];
				}
				pVbo->OverwriteVertices(pVoid, (st_int32)grassVertexArray.size(), 0);
			}
		}
	}
}