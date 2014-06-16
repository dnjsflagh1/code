/******************************************************************************/
#ifndef _ENGINEPREQS_H_
#define _ENGINEPREQS_H_
/******************************************************************************/

/******************************************************************************/
namespace MG
{
	
	//////////////////////////////////////////////////////////////////////////
	class MGFileSystem;
	class GuiFuction;

    //////////////////////////////////////////////////////////////////////////
    //System
    class Application;
    class MGCapabilities;
    class InputManager;
    class SoundALManager;
    class Display;
    //////////////////////////////////////////////////////////////////////////
    //GUI
    class DEMixTree;
    class DEMixTreeNode;

    class Gui;
    class MGPointer;
	class DEFont;
    class Layout;
    class GuiDgElmPool;
    class GuiDgElmPoolEx;
    class GuiDgElmPoolOut;

    class DEWidget;
    class DEButton;
    class DEEdit;
    class DEForm;
    class DEImage;
    class DEProgress;
    class DEText;
    class DEViewScroll;
    class DEList;
    class DETab;
    class DETabItem;
    class DEIcon;
    class DEComboBox;
    class DERollingText;
    class DEMixList;
    class DEMixListRow;

    //////////////////////////////////////////////////////////////////////////
    //Scene
    class DynamicBlockObject;
    class MGSceneNode;
    class SceneNodeLisitener;
    class SceneNodeLineMoveToAction;
    class SceneNodeYawToAction;
	class SceneNodeDirectToAction;

    /////////////////////////////////////////////////////////////

	struct ModelDeclaration;
	struct MaterialDeclaration;

    /////////////////////////////////////////////////////////////

	class SceneObjectController;
    class AnimationController;
    class EntityAccessoryCollection;

    /////////////////////////////////////////////////////////////

    class OgreEntityWrapper;

    class Camera;
    class Light;
    class Entity;
	class EntityGroup;
    class PlaceEntity;
    class NpcEntity;
    class EffectEntity;
	// CN_MODIFY
	class EffectComponent;
	class EffectComponentSerialization;
	class EffectComponentTimeLine;
	class PUEffect;

    /////////////////////////////////////////////////////////////

    class CompositorManager;
    class ScreenRectWireframeDecorator;
    class WireframeManager;
    class Polyline;

    /////////////////////////////////////////////////////////////

	class TerrainManager;
    class TerrainChunk;

    class TerrainRegionManager;
    class TerrainRegion;

    class TerrainNode;

    class TerrainEntityBatchManager;
    class TerrainEntityBatch;

    class TerrainSurfaceManager;
    class TerrainSurface;

    class TerrainRegionManager;
    class TerrainChunkRegions;
    class TerrainRegion;

    class DefaultTerrainTilesGpuBufferAllocator;

    class TerrainSurface;
    class TerrainTile;
    class TerrainTileRender;
    class TerrainBatch;
    class TerrainLayerBlendMap;

    class TerrainGroundSurface;
    class TerrainGroundTile;
    class TerrainGroundTileRender;
    class TerrainGroundBatch;

    class TerrainBBGroundSurface;
    class TerrainSBGroundSurface;

    class TerrainBBGroundTileRender;
    class TerrainSBGroundTileRender;

    class TerrainSBGroundBatch;

    class TerrainWaterSurface;
    class TerrainWaterTile;
    class TerrainWaterTileRender;
    class TerrainWaterBatch;

    class TerrainWaterMaterial;

    class TerrainDecalSet;
    class TerrainDecal;

	class HighLevelDecalSet;
	class HighLevelDecal;
    /////////////////////////////////////////////////////////////

    class CollisionSystem;

    /////////////////////////////////////////////////////////////

    class ActionManager;

    /////////////////////////////////////////////////////////////

    class Scene;
	class ResourceLoadListener;

    /////////////////////////////////////////////////////////////

    class SceneXmlSerializer;
	class EffectXmlSerializer;
    class EntityXmlFormat;
	class EffectEntityXmlFormat;

    /////////////////////////////////////////////////////////////

    class MiniMapManager;

    class LightingMapMaker;
    class ShadowManager;
	class DynamicShadowMaker;

    /////////////////////////////////////////////////////////////

    class TreeManager;
    class Tree;
	class Grass;
    class SpeedTreeSystem;

    /////////////////////////////////////////////////////////////

    class MeshCollisionObject;
    class CollisionObject;

    /////////////////////////////////////////////////////////////

	class BlockManager;
	struct PassGridBlock;

	/////////////////////////////////////////////////////////////

	struct BlockScope;

    /////////////////////////////////////////////////////////////

    class SceneDebuger;

	class BlockObject;

	class BlockObjectSceneManager;

	struct RegionGrid;
}

#include "MGStd.h"
#include "MGTypes.h"
#include "MGDefine.h"

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

#endif
