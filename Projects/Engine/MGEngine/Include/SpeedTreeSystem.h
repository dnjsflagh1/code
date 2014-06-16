/******************************************************************************/
#ifndef __SPEEDTREESYSTEM_H__
#define __SPEEDTREESYSTEM_H__
/******************************************************************************/

#include "EnginePreqs.h"
#include "SpeedTreeUtility.h"
#include "SpeedTreeDefine.h"
#include "StatsReporter.h"
#include "ITree.h"
#include "RenderInterface/ForestRI.h"
/******************************************************************************/
// CN_MODIFY
class GameFilePackManager;
//using namespace SpeedTree;
#define ACTIVE_GRASS

namespace MG
{

	struct SGrassBoard 
	{
		SGrassBoard();
		~SGrassBoard();
		
		void pos(const MG::Vec3& vPos);

		MG::Vec3 pos();
		
		void uv(Flt u0, Flt v0, Flt u1, Flt v1, Flt u2, Flt v2, Flt u3, Flt v3);

		void size(Flt w, Flt h);
		
		void width(Flt w);

		void height(Flt h);
		
		Flt	width() const;

		Flt height() const;

		void windWeight(Flt rtw, Flt ltw, Flt lbw, Flt rbw);

		void updatePerturb(const Flt perturb);

		SGrassVertex			m_vertex[4];
	};

	class DataCell : public SpeedTree::CCell
	{
	public:

		DataCell() {}

		virtual ~DataCell() {}

		UInt addGrassBoard(const SGrassBoard& grassBoard);
		
		Bool deleteGrassBoard(UInt uIndex);
		
		Bool getPos(UInt uIndex, MG::Vec3& vPos);

		Bool setPos(UInt uIndex, const MG::Vec3& vPos);

		Bool setSize(UInt uIndex, Flt w, Flt h);
		
		Bool width(UInt uIndex, Flt w);
		
		Flt width(UInt uIndex);

		Bool height(UInt uIndex, Flt h);

		Flt height(UInt uIndex);
		
		Bool windWeight(UInt uIndex, Flt rtw, Flt ltw, Flt lbw, Flt rbw);

		void updatePerturb(const Flt perturb);

		std::list<SGrassBoard>::iterator gotoBoradIter(UInt uIndex);

		std::list<SGrassBoard>	m_grassBoardList;
	};


	///////////////////////////////////////////////////////////////////////  
	//  SGrassVertex declaration to be used with the CGeometryBuffer class

	static const SpeedTree::SVertexAttribDesc g_asGrassVertexFormat[ ] =
	{
		{ SpeedTree::VERTEX_ATTRIB_SEMANTIC_POS, SpeedTree::VERTEX_ATTRIB_TYPE_FLOAT, 4 },
		{ SpeedTree::VERTEX_ATTRIB_SEMANTIC_TEXCOORD0,SpeedTree:: VERTEX_ATTRIB_TYPE_FLOAT, 4 },
		{ SpeedTree::VERTEX_ATTRIB_SEMANTIC_TEXCOORD1, SpeedTree::VERTEX_ATTRIB_TYPE_FLOAT, 4 },
		//{ SpeedTree::VERTEX_ATTRIB_SEMANTIC_TEXCOORD2, SpeedTree::VERTEX_ATTRIB_TYPE_FLOAT, 2 },
		{ SpeedTree::VERTEX_ATTRIB_SEMANTIC_TEXCOORD2, SpeedTree::VERTEX_ATTRIB_TYPE_FLOAT, 4 },
		{ SpeedTree::VERTEX_ATTRIB_SEMANTIC_END, SpeedTree::VERTEX_ATTRIB_TYPE_FLOAT, 0 }
	};


	/******************************************************************************/
	//SpeedTreeSystem
	//PS:
	/******************************************************************************/
	class SpeedTreeSystem
	{
	public:
		SpeedTreeSystem();
		~SpeedTreeSystem();
		// CN_MODIFY
		Bool initialize(const SpeedTreeParam& param, GameFilePackManager* packManager);
		void unInitialize();

		Bool isReadyRender() const { return m_bReadyToRender; }

		void setTreeTemplateList(std::vector<std::string>* pBaseTreeList) { m_pTreeTemplateList = pBaseTreeList; }

		Bool load(std::map<UInt, TreeDeclaration>& treeDeclMap, std::map<UInt, std::vector<STree>>& treeInstanceMap);

	public:

		void onResetDevice(float aspectRatio);
		void onLostDevice();

	public:

		void update(const CameraParam& cameraParam, const CameraParam& lightCameraParam,const CameraParam& reflectCameraParam);

		void render(Int renderPass, const CameraParam& vpCameraParam);
		void renderToMainScene(const CameraParam& vpCameraParam);
        void renderToReflectMap(const CameraParam& vpCameraParam);
        void renderToRefractMap(const CameraParam& vpCameraParam);
		void renderToShadowMap(const CameraParam& vpCameraParam);
		void renderZPass(const CameraParam& cameraParam);

	public:

		//
		void setAspectRatio(Flt aspectRatio) { m_fAspectRatio = aspectRatio; }

	public:

		//Tree
		Flt  getBaseTreeHeight(Int baseTreeID);
		
		Bool addInstance(Int baseTreeID, const MG::Vec3& pos, SpeedTree::CInstance& cInstance);

		Bool deleteInstance(Int baseTreeID, SpeedTree::CInstance& cInstance);

		Bool instancePosition(Int baseTreeID, SpeedTree::CInstance& cInstance, const MG::Vec3& pos);

		Bool instanceRotate(Int baseTreeID,  SpeedTree::CInstance& cInstance, Flt fRadians);

		Bool instanceScale(Int baseTreeID, SpeedTree::CInstance& cInstance, Flt& scale);

		void getTreeExtents(Int baseTreeID, Vec3& vMin, Vec3& vMax);
		//
		Flt getBaseTreeHeight(CChar* pBaseTreeName);

		Bool addInstance(CChar* pBaseTreeName, const MG::Vec3& pos, SpeedTree::CInstance& cInstance);

		Bool deleteInstance(CChar* pBaseTreeName, SpeedTree::CInstance& cInstance);

		Bool instancePosition(CChar* pBaseTreeName, SpeedTree::CInstance& cInstance, const MG::Vec3& pos);

		Bool instanceRotate(CChar* pBaseTreeName, SpeedTree::CInstance& cInstance, Flt fRadians);

		Bool instanceScale(CChar* pBaseTreeName, SpeedTree::CInstance& cInstance, Flt& scale);
		
		void getTreeExtents(CChar* pBaseTreeName, Vec3& vMin, Vec3& vMax);
		
		Bool addExceptTreeInstance(Int baseTreeID, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass);

		Bool addExceptTreeInstance(CChar* pBaseTreeName, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass);

		Bool addExceptTreeInstance(SpeedTree::CTree* pBaseTree, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass);

		Bool delExceptTreeInstance(Int baseTreeID, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass);

		Bool delExceptTreeInstance(CChar* pBaseTreeName, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass);

		Bool delExceptTreeInstance(SpeedTree::CTree* pBaseTree, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass);

		Bool isExceptTreeInstance(SpeedTree::CTree* pBaseTree, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass);

		Bool isExceptTreeInstance(Int baseTreeID, SpeedTree::CInstance& cInstance, SpeedTree::ERenderPassType renderPass);

		void getGrassListByPosRadiu(const MG::Vec3& vPos, const MG::Flt fRadiu, std::list<SGrassBoard>& grassList);

		void getGrassCellPtrsByPosRadiu(const MG::Vec3& vPos, const MG::Flt fRadiu, std::vector<const DataCell*>& grassCells);

	private:
		Bool addInstance(SpeedTree::CTree* pBaseTree, const MG::Vec3& pos, SpeedTree::CInstance& cInstance);
		
		Bool deleteInstance(SpeedTree::CTree* pBaseTree, SpeedTree::CInstance& cInstance);

		Bool instancePosition(SpeedTree::CTree* pBaseTree, SpeedTree::CInstance& cInstance, const MG::Vec3& pos);

		Bool instanceRotate(SpeedTree::CTree* pBaseTree,  SpeedTree::CInstance& cInstance, Flt fRadians);

		Bool instanceScale(SpeedTree::CTree* pBaseTree, SpeedTree::CInstance& cInstance, Flt& scale);

	public:

		//Grass
		void setGrassImageRowCol(UInt row, UInt col);

		void setGrassPerturbCircle(const Vec3& vPos, const Flt fRadiu);

		Bool addGrass(UInt uGrassImageID, const MG::Vec3& vPos, Flt w, Flt h, Flt rtw, Flt ltw, Flt lbw, Flt rbw,
			UInt& uIndex, Int& row, Int& col);
		
		//Bool deleteGrass(const MG::Vec3& vPos, UInt uGrassId);

		void updateDirtyGrass();

		Bool deleteGrass(Int iRow, Int iCol, UInt uGrassId);

		Bool deleteAllGrass();

		Bool grassPosition(Int iRow, Int iCol, UInt uGrassId, MG::Vec3& vPos);

		Bool setGrassPosition(Int iRow, Int iCol, UInt uGrassId, const MG::Vec3& vPos);

		Bool setGrassSize(Int iRow, Int iCol, UInt uGrassId, Flt w, Flt h);

		Flt getGrassW(Int iRow, Int iCol, UInt uGrassId);

		Bool setGrassW(Int iRow, Int iCol, UInt uGrassId, Flt w);

		Flt getGrassH(Int iRow, Int iCol, UInt uGrassId);

		Bool setGrassH(Int iRow, Int iCol, UInt uGrassId, Flt h);

		Bool setGrassWindWeight(Int iRow, Int iCol, UInt uGrassId, Flt rtw, Flt ltw, Flt lbw, Flt rbw);

		DataCell* getCellPtrByPos_Add(const MG::Vec3& vPos);

	public:

		//灯光方向
		void setLightDir(const MG::Vec3& vDir);

		//
		void setLightMtl(const MG::Color& cAmbient, const MG::Color& cDiffuse, const MG::Color& cSpecular, const MG::Color& cEmissive);

		//
		void setGrassLightMtl(const MG::Color& cAmbient, const MG::Color& cDiffuse, const MG::Color& cSpecular, const MG::Color& cEmissive);

		//
		void setFog(const MG::Color& color, Flt fStartDistance, Flt fEndDistance);

		//摄像机FarClip，可见范围
		void setFarClip(float farClip);

		//开关风
		void setWindEnable(Bool bEnable);

		//是否开启风
		Bool isWindEnabled();

		//设置风的强度
		void setGlobalWindStrength(float fStrength);

		//获取风的强度
		Flt getGlobalWindStrength(void) const;

		//设置风的方向
		void setGlobalWindDirection(const MG::Vec3& vDir);

		//获取风的方向
		MG::Vec3 getGlobalWindDirection(void) const;

		//
		Bool EnableSpecularLight();

		//
		void EnableSpecularLight(Bool bEnable);

		//
		Bool EnableTransmissionLight();

		//
		void EnableTransmissionLight(Bool bEnable);

		//
		Bool EnableDetailLayer();

		//
		void EnableDetailLayer(Bool bEnable);

		//
		Bool EnableDetailNormalMap();

		//
		void EnableDetailNormalMap(Bool bEnable);

		//
		Bool EnableAmbientContrast();

		//
		void EnableAmbientContrast(Bool bEnable);
		
		Bool loadAndRegisterTree(const std::map<UInt, TreeDeclaration>& treeDeclMap, const std::map<UInt, std::vector<STree>>& treeInstanceMap, Bool bSetInstance);

		//游戏模式
		void clearBaseTree();
		
		void clearGrass();

		void setGrassLod(Flt fStartFade, Flt fEndFade);

		void getGrassLod(Flt& fStartFade, Flt& fEndFade);

	private:

		Bool initGraphics(IDirect3DDevice9* pDevice);

		void parseTaiFile(const MG::CChar* filePath);

		void loadConfig();

		
		void adjustBaseTreeLodProfile(SpeedTree::CTreeRender* pBaseTree, Flt LodHigh, Flt LodLow);

		SpeedTree::st_bool setForestCullReserves(SpeedTree::st_int32 nMaxNumVisibleCells, SpeedTree::st_int32 nMaxInstancesByCellPerBase);

		void advance();

		void cull();

		// render state management
		void setTransparentTextureMode(SpeedTree::ETextureAlphaRenderMode eMode) const;

		SpeedTree::CView getView(const CameraParam& cameraParam);

		void updateLightDir(void);

		SpeedTree::st_bool renderForest(SpeedTree::ERenderPassType eRenderPass);

        // the main forest render function; includes shadow mapping pass
        SpeedTree::st_bool renderForestIntoOneShadowMaps(SpeedTree::CView& view);

		void populateGrassCells(void);

		SpeedTree::st_bool renderGrass(void);

		void initLightMtl(SpeedTree::SMaterial& mtl);

		void initGrassWind();

		SpeedTree::CTree* getBaseTree(Int baseTreeID);

		SpeedTree::CTree* getBaseTree(CChar* baseTreeName);

	private:
		SpeedTree::CForestRender			m_cForest;
		SpeedTree::st_uint32				m_uiTransparentTextureRenderMode;   // alpha testing, alpha-to-coverage toggle
		SpeedTree::st_bool					m_bReadyToRender;
		SpeedTree::st_float32				m_fAspectRatio;

		SpeedTree::st_bool					m_bCameraChanged;
		SpeedTree::st_bool					m_bForestPopulationChanged;

		SpeedTree::st_bool					m_bRenderBranches;          // toggle rendering of branch geometry
		SpeedTree::st_bool					m_bRenderFronds;            // toggle rendering of frond geometry
		SpeedTree::st_bool					m_bRenderLeafCards;         // toggle rendering of leaf card geometry
		SpeedTree::st_bool					m_bRenderLeafMeshes;        // toggle rendering of leaf mesh geometry
		SpeedTree::st_bool					m_bRenderBillboards;        // toggle rendering of billboards

		SpeedTree::st_float32				m_fLightAngleHorz;          // used as to control light direction
		SpeedTree::st_float32				m_fLightAngleVert;          // used as to control light direction
		SpeedTree::Vec3						m_vLightDir;                // light direction

		//grass
		SpeedTree::CGrassRender				m_cGrass;
		SpeedTree::SGrassCullResults		m_sVisibleGrass;
		std::set<DataCell*>					m_dirtyGrassCellset;
		SpeedTree::st_float32				m_needPerturRadin;			//需要晃动的弧度
		SpeedTree::st_float32				m_perturbSpeed;				//草晃动速度(多少弧度每秒)

		SpeedTree::st_bool					m_bRenderGrass;             // toggle rendering of grass
		SpeedTree::CCellContainer<DataCell>	m_grassCellMap;
		UInt								m_grassImageRow;
		UInt								m_grassImageCol;
		std::vector<RectF>					m_BitmapArrayRects;

		// culling
		SpeedTree::CView					m_cView;
		SpeedTree::CView					m_cLightView;
		SpeedTree::CView					m_cReflectView;

		SpeedTree::SForestCullResultsRender	m_sVisibleTrees;
		SpeedTree::SForestCullResultsRender	m_asLightCullResults[SpeedTree::c_nMaxNumShadowMaps];
		SpeedTree::CView					m_acLightViews[SpeedTree::c_nMaxNumShadowMaps];

		SpeedTree::st_bool					m_bShowDepthOnlyPrePass;    //
		SpeedTree::st_bool					m_bUpdateShadowMaps;

		// time management
		SpeedTree::st_float32				m_fCurrentTime;             // time since initialization in seconds
		SpeedTree::st_float32				m_fFrameTime;               // time it took to render the last frame in seconds
		SpeedTree::st_float32				m_fTimeMarker;              // used to calculate m_fFrameTime in Advance()
		SpeedTree::CTimer					m_cTimer;                   // real-time wall clock
		SpeedTree::st_int32					m_nSecondaryShadowIndex;    // tracking which secondary shadow map gets updated next
		SpeedTree::st_int32					m_nSecondaryShadowInterval;
		Bool								m_bGrassDirty;
		Bool								m_bEditorMode;

		//Wind
		SpeedTree::CWind::SParams			m_grassWindParam;
		//
		std::vector<std::string>*			m_pTreeTemplateList;

		std::map<UInt, TreeDeclaration>*	m_pTreeDecl;
		SpeedTree::TBaseToInstanceMap		m_exceptTreeInstanceMap[SpeedTree::RENDER_PASS_NUM_TYPES];
		SpeedTree::CStatsReporter			m_cStatsReporter;

		// CN_MODIFY
		// SpeedTree打包系统
		SpeedTree::IExternalSTPackManager*	mSTPackManager;
		SpeedTree::st_bool					m_bNotRender;

		SGrassVertex						m_tmpGrassVertex[MAX_GRASS_PRE_CELLS*4];
	};
}
#endif