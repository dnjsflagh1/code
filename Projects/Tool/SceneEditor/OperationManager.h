/******************************************************************************/
#ifndef _OPERATIONMANAGER_H_
#define _OPERATIONMANAGER_H_
/******************************************************************************/



/******************************************************************************/

namespace SceneEditor 
{
    /******************************************************************************/
	class OperationManager
    {
    public:
        enum OperationType
        {
            OT_NULL	 = 0,
            OT_CREATE_ENTITY,				// 创建模型
			OT_CREATE_EFFECTENTITY,			// 创建特效
            OT_CREATE_TREE,					// 创建树木系统

            //////////////////////////////////////////////////////////////////////

            OT_TERRAIN_HEIGHT_LEVEL,        // 地形高度 上升下降 
            OT_TERRAIN_HEIGHT_UNIFORM,      // 地形高度 统一
            OT_TERRAIN_HEIGHT_NOISE,        // 地形高度 噪音
            OT_TERRAIN_HEIGHT_FLAT,         // 地形高度 平滑

            //////////////////////////////////////////////////////////////////////

            OT_TERRAIN_TEXTURE_ADD,         // 地形材质 增加
            OT_TERRAIN_TEXTURE_REMOVE,      // 地形材质 减少
            OT_TERRAIN_TEXTURE_UNIFORM,     // 地形材质 统一
            OT_TERRAIN_TEXTURE_MOP,         // 地形材质 抹涂
            OT_TERRAIN_TEXTURE_BLUR,        // 地形材质 模糊

            //////////////////////////////////////////////////////////////////////

            OT_TERRAIN_BATCH_ADD,           // 地形批量实体 增加
            OT_TERRAIN_BATCH_REMOVE,        // 地形批量实体 减少
			OT_TERRAIN_BATCH_DEFINE,        // 地形批量实体 噪音分布

            //////////////////////////////////////////////////////////////////////

            OT_TERRAIN_TREE_ADD,            // 地形批量植被 增加
            OT_TERRAIN_TREE_REMOVE,         // 地形批量植被 减少
            OT_TERRAIN_TREE_DEFINE,         // 地形批量植被 噪音分布

            //////////////////////////////////////////////////////////////////////

            OT_TERRAIN_REGION_ADD,          // 地形障碍 增加
            OT_TERRAIN_REGION_REMOVE,       // 地形障碍 减少

            //////////////////////////////////////////////////////////////////////
    
            OT_TERRAIN_WATER_HEIGHT_LEVEL,      // 地形水高度 上升下降 
            OT_TERRAIN_WATER_HEIGHT_UNIFORM,    // 地形水高度 统一
            OT_TERRAIN_WATER_HEIGHT_FLAT,       // 地形水高度 平滑
            OT_TERRAIN_WATER_SHOW,              // 地形水显示
            OT_TERRAIN_WATER_HIDE,              // 地形水隐藏

        };

		enum
		{
			TYPE_TREE,
			TYPE_GRASS,
		};
    public:
        SINGLETON_INSTANCE(OperationManager)
        OperationManager();
        ~OperationManager();
        void update( Dbl delta );

    //*********************************************************
    //【编辑操作】
    public:     
        //设置当前操作
        void setActiveEditorOp(OperationType type); 

		void setTreeType(Int type) { mTreeType = type; }

        //清空准备的操作
        void clearEditorOp();

		//撤销操作
		void undoOp();

		//重做操作
		void redoOp();

    protected:
        //清空准备的操作
        void updateEditorOp( Dbl delta );

    ///////////////////////////////////////
    public://模型和植被元素操作

        //准备创建模型
        void prepareCreateObject( Int objectDeclID );

		//创建更新和摧毁跟随鼠标的准备模型样本
		void createSampleObject( Int objectDeclID );
		void updateSampleObject();
		void destroySampleObject();

		//创建跟随鼠标的对象
		ISceneObject* createCursorElement(Int objectDeclID);
		//销毁跟随鼠标的对象
		void destroyCursorElement(void);
		//更新跟随鼠标的对象的位置
		void updateCursorElement();
		//显示跟随鼠标的对象
		void showCursorElement();
		//隐藏跟随鼠标的对象
		void hideCursorElement();
		//添加物体到场景
		void dropCursorElement();
		//拷贝物体到鼠标
		void copyElementToCursor();

    private:

        //执行创建模型或者拷贝已经生成的模型
        void execCreateOrCopyModel();

        //执行创建静态模型或者拷贝已经生成的模型
        ISceneObject* execCreateOrCopyEntity( Vec3 pos , IEntity* srcEntity,Int modelDeclID );
		//拷贝模型的属性
		void copyEntityBaseAttribute(IEntity* targetObj, IEntity* srcObj);

		//执行创建静态模型或者拷贝已经生成的模型
		ISceneObject* execCreateOrCopyEffectEntity( Vec3 pos , IEffectEntity* srcEntity,Int effectDeclID );
		//拷贝模型的属性
		void copyEffectEntityBaseAttribute(IEffectEntity* targetObj, IEffectEntity* srcObj);

        //执行创建模型或者拷贝已经生成的树模型
        ISceneObject* execCreateOrCopyTree( Vec3 pos , ITree* srcTree,Int modelDeclID );

		ISceneObject* execCreateOrCopyGrass( Vec3 pos , IGrass* srcGrass,Int textureID );
        ///选中元素位置贴地
        void stickSelectElementToTerrain();
        //销毁选择的对象
        void destroySelectElement();

    //////////////////////////////////////		

    private://笔刷操作

        ///更新笔刷操作
        void updateBrushOp( IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys );

	private:

		//判断当前的输入是否会激发一个编辑操作
		bool isUpdateTerrainOperation(Flt delta);

    //////////////////////////////////////
    private://地形高度操作

        //更新增加地形高度操作
        void updateTerrainHeightDeformOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
        //更新统一地形高度操作
        void updateTerrainHeightUniformOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
        //更新噪音地形高度操作
        void updateTerrainHeightNoiseOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
        //更新平滑地形高度操作
        void updateTerrainHeightFlatOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);

    //////////////////////////////////////
    private://地形材质操作

        //更新增加地形贴图操作
        void updateTerrainTextureAddOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
        //更新降低地形贴图操作
        void updateTerrainTextureRemoveOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
        //更新统一地形贴图操作
        void updateTerrainTextureUniformOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
        //更新噪音地形贴图操作
        void updateTerrainTextureMopOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
        //更新平滑地形贴图操作
        void updateTerrainTextureBlurOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);

    //////////////////////////////////////
    private://地形批量实体操作
        //更新批量实体增加操作
        void updateTerrainBatchAddOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
        //更新批量实体移除操作
        void updateTerrainBatchRemoveOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
		//批量实体噪音分布的操作
		void updateTerrainBatchDefineOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);


    //////////////////////////////////////
    private://地形障碍操作
        //更新障碍增加操作
        void updateTerrainBlockAddOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
        //更新障碍移除操作
        void updateTerrainBlockRemoveOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);

    //////////////////////////////////////
    private://地形水操作
        //更新增加水高度操作
        void updateTerrainWaterHeightDeformOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
        //更新统一水高度操作
        void updateTerrainWaterHeightUniformOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
        //更新平滑水高度操作
        void updateTerrainWaterHeightFlatOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);

        //更新水显示操作
        void updateTerrainWaterShowOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);
        //更新水隐藏操作
        void updateTerrainWaterHideOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys);


    //////////////////////////////////////
    //TODO:








    //*********************************************************
    //【摄像机操作】
    public:
        ///还原摄像机
        void revertCamera();

    protected:
        ///更新摄像机操作
        void updateCameraOp( Dbl delta );

        void updateFreeCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );
        void updateGameCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );

        ///切换视角锁定
        void switchViewportLock();


    //*********************************************************
    private:

        OperationType   mOpType;

        ISceneObject*   mSampleSceneObj;

        Int             mCurrModelDeclID;
        Int             mCurrTreeDeclID;
		Int				mCurrEffectDeclID;
		Int				mCurrentGrassID;

        Flt             mCameraSpeed;
        Bool            mViewportLock;
        Vec3            mLastMouseTerrainIntersection;

		Flt				mTimeMouseHold;
		Flt				mOpInterval;
        Bool			mIsMouseStateCheck;

        Bool            mRaiseOrLowHeight;
        Bool            mMoveHeight;

        std::vector<Flt> mCameraHeightSet;
        Flt mMaxPitch;
        Flt mMinPitch;
		int				mTreeType;
    };

}

/******************************************************************************/
#endif

