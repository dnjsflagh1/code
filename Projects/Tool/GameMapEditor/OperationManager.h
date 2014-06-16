/******************************************************************************/
#ifndef _OPERATIONMANAGER_H_
#define _OPERATIONMANAGER_H_
/******************************************************************************/
#include "IScene.h"
/******************************************************************************/

namespace GameMapEditor {

    /******************************************************************************/
	class OperationManager : public MG::ResourceSaveListener
    {
    public:
        enum OperationType
        {
            OT_NULL,
			OT_CREATE_STATIC_OBJECT,
			OT_CREATE_TROOP,
			OT_CREATE_BUILDING,
			OT_CREATE_MONSTER,
			OT_CREATE_NPC,
            OT_CREATE_OBJECT,
			OT_CREATE_POINT,			
			OT_CREATE_PLACE,
			OT_CREATE_REGION,
			OT_CREATE_EFFECT,
        };
    public:
        SINGLETON_INSTANCE(OperationManager)
        OperationManager();
        ~OperationManager();
        void update( Dbl delta );

	public:

		void preSaveEntity();

    //*********************************************************
    //【编辑操作】
    public:     
        //设置当前操作
        void setActiveEditorOp(OperationType type); 

        //清空准备的操作
        void clearEditorOp();

    protected:
        //清空准备的操作
        void updateEditorOp( Dbl delta );

    ///////////////////////////////////////
    public://场景物件操作

        //准备创建场景物件
        void prepareCreateSceneObject( U32 objectDeclID );

    private:

		//添加物体到场景
		void dropCursorElement();
		//拷贝物体到鼠标
		void copyElementToCursor();
		//创建物件
		IEntity* createObject();
		//创建Npc
		IEntity* createNpc();
		//创建战斗单位
		IEntity* createMonster();
		//创建坐标点
		IEntity* createPoint();
		//创建据点
		IEntity* createPlace();
		//创建军队
		IEntity* createTroop();
		//创建区域
		IEntity* createRegion();
		//创建静态景观
		IEntity* createStaticObject();
		//创建建筑物
		IEntity* createBuilding();
		//创建特效
		ISceneObject* execCreateOrCopyEffectEntity( Vec3 pos , IEffectEntity* srcEntity,Int effectDeclID );
		
		//检查是否是正确的CustomEntity格式
		bool isCustomAttributeComplete(IEntity* entity);
		//复制实体基本信息
		void copyEntityBaseAttribute(IEntity* targetObj, IEntity* srcObj);
		//复制特效基本信息
		void copyEffectEntityBaseAttribute(IEffectEntity* targetObj, IEffectEntity* srcObj);
        ///选中元素位置贴地
        void stickSelectElementToTerrain();
        //销毁选择的对象
        void destroySelectElement();

	public:
		//创建跟随鼠标的对象
		ISceneObject* createCursorElement(U32 objectDeclID);
		//销毁跟随鼠标的对象
		void destroyCursorElement(void);
		//更新跟随鼠标的对象的位置
		void updateCursorElement();
		//显示跟随鼠标的对象
		void showCursorElement();
		//隐藏跟随鼠标的对象
		void hideCursorElement();

    //*********************************************************
    //【摄像机操作】
    public:
        ///还原摄像机
        void revertCamera();
		///聚焦于某位置, 在地图设定的范围内
		void focusCamera(Vec3 pos);

    protected:
        ///更新摄像机操作
        void updateCameraOp( Dbl delta );

		void updateFreeCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );
		void updateGameCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );


        ///切换视角锁定
        void switchViewportLock();

		///返回一个合法的摄像机local位移
		Vec3 getValidCameraDelta(Vec3 pos, Qua orientation, Vec3 delta, bool isLocal = true);

	public:
			///设置镜头运动参数
		void setCameraDefaultPitch( Flt degree );
		void setCameraPitchRange( Flt degreeMin, Flt degreeMax );
		void setCameraDefaultPos( Vec3 pos );
		void setCameraMoveBoard( Vec3 minBoard, Vec3 maxBoard );
		void setCameraSpeed( Flt transSpeed, Flt rollSpeed );

    //*********************************************************
    private:
        
		//操作模式
		OperationType   mOpType;	
		//这个值到底是模型列表的ID， 还是角色ID， 还是跳转ID， 需要看当前的操作模式
		Int             mCurrOperationID;
		Flt             mCameraSpeed;
		Bool            mViewportLock;
		Vec3            mLastMouseTerrainIntersection;

		Flt				mTimeMouseHold;
		Flt				mOpInterval;
		Bool			mIsMouseStateCheck;

		Bool            mRaiseOrLowHeight;
		Bool            mMoveHeight;

		std::vector<Flt> mCameraHeightSet;

		Flt             mCamMaxPitch;
		Flt             mCamMinPitch;
		Flt				mCamDefaultPitch;

		Vec3			mCamMinBoard;
		Vec3			mCamMaxBoard;
		Vec3			mCamDefaultPos;

		UInt			mAutoMoveSize;

		Flt				mCamGameRollSpeed;
		Flt				mCamGameMoveSpeed;

		//跟随鼠标的对象(目前只有Entity和EffectEntity)
		ISceneObject*   mCursorObject;
    };

}

/******************************************************************************/
#endif

