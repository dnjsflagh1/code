/******************************************************************************/
#ifndef _MGENGINEINTERFACEPREQS_H_
#define _MGENGINEINTERFACEPREQS_H_
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace MG
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class IApplication;
    class ISoundManager;
    class IInput;
    class IDisplay;
    class IEngineUtil;
    class ISceneDebuger;

	/// MG_CN_MODIFY
	class ExOgreResourceManager;
    //////////////////////////////////////////////////////////////////////////

    class IEditorSystem;
    class IEditorOperation;
    class IBrushSystem;

    class ITerrainRaiseHeightOperationManager;
    class ITerrainLowerHeightOperationManager;
    class ITerrainUniformHeightOperationManager;
    class ITerrainNoiseHeightOperationManager;
    class ITerrainSmoothHeightOperationManager;

    class ITerrainAddTextureOperationManager;
    class ITerrainRemoveTextureOperationManager;
    class ITerrainUniformTextureOperationManager;
    class ITerrainMopTextureOperationManager;
    class ITerrainBlurTextureOperationManager;
	class ITerrainReorderTextureOperationManager;

    class ITerrainTreeOperationManager;
    class ITerrainAddTreeOperationManager;
    class ITerrainRemoveTreeOperationManager;
    class ITerrainDefineTreeOperationManager;

    class ITerrainAddRegionOperationManager;
    class ITerrainRemoveRegionOperationManager;

    class ITerrainWaterShowOperationManager;
    class ITerrainWaterHideOperationManager;

    class IBrushShape;
    class IBrushRhombusShape;
    class IBrushRectShape;
    class IBrushCircleShape;

    class IBrushStyle;
    class IBrushAirStyle;
    class IBrushPaintStyle;
    class IBrushNoiseStyle;
    class IBrushFractalStyle;

    //////////////////////////////////////////////////////////////////////////

    class MGTextDs;

    class IMixTree;
    class IMixTreeNode;
    class ITextDs;
    class IAny;
    class IGui;
    class IPointer;
	class IFont;
    class ILayout;
    class IWidget;
    class IButton;
    class IForm;
    class IEdit;
    class IProgress;
    class IImage;
    class IText;
    class IViewScroll;
    class IList;
    class ITab;
    class ITabItem;
    class IIcon;
    class IComboBox;
    class IRollingText;
    class IMixList;
    class IMixListRow;
	class IHScroll;
	class IVScroll;
	class ITimeText;

    //////////////////////////////////////////////////////////////////////////

    struct ILogicBinder;
    class ICollisionObject;
    class IDynamicBlockObject;
    class ISceneNode;
    class ISceneNodeLisitener;
    class ISceneObjectController;
    class IAnimationController;
    class IEntityAccessory;
    class IEntityAccessoryCollection;

    class ISceneObject;
    class IModelObject;
    class ICamera;
    class ILight;
    class IEntity;
    class IEntityGroup;
    class IPlaceEntity;
    class INpcEntity;
    class IEffectEntity;
	// CN_MODIFY
	class IEffectComponent;
	class IEffectEvent;
	class IEffectComponentTimeLine;
	class IPUEffect;
    class IScreenRectWireframeDecorator;
    class IPolyline;
	class IEffectXmlSerializer;

    class IPathFindingManager;

    class ITerrainDecalSet;
    class ITerrainDecal;

	class IDecalSet;

    class ICollisionSystem;
    struct ICollisionCallback;

    class IBlockManager;
    class IActionManager;
    class IScene;

    class ISceneXmlSerializer;
    class ISceneObjectXmlFormat;

    class IMiniMapManager;
    class IShadowManager;
    class IPathFinder;

    class IWireframeManager;
    class ICompositorManager;

    class ITree;
    class ITreeManager;

	class IBlockObjectSceneManager;

	struct PassGridBlock;

}

#include "MGEngineCommonDefine.h"

/******************************************************************************/
#endif

