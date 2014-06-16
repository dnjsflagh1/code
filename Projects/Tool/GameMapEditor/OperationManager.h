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
    //���༭������
    public:     
        //���õ�ǰ����
        void setActiveEditorOp(OperationType type); 

        //���׼���Ĳ���
        void clearEditorOp();

    protected:
        //���׼���Ĳ���
        void updateEditorOp( Dbl delta );

    ///////////////////////////////////////
    public://�����������

        //׼�������������
        void prepareCreateSceneObject( U32 objectDeclID );

    private:

		//������嵽����
		void dropCursorElement();
		//�������嵽���
		void copyElementToCursor();
		//�������
		IEntity* createObject();
		//����Npc
		IEntity* createNpc();
		//����ս����λ
		IEntity* createMonster();
		//���������
		IEntity* createPoint();
		//�����ݵ�
		IEntity* createPlace();
		//��������
		IEntity* createTroop();
		//��������
		IEntity* createRegion();
		//������̬����
		IEntity* createStaticObject();
		//����������
		IEntity* createBuilding();
		//������Ч
		ISceneObject* execCreateOrCopyEffectEntity( Vec3 pos , IEffectEntity* srcEntity,Int effectDeclID );
		
		//����Ƿ�����ȷ��CustomEntity��ʽ
		bool isCustomAttributeComplete(IEntity* entity);
		//����ʵ�������Ϣ
		void copyEntityBaseAttribute(IEntity* targetObj, IEntity* srcObj);
		//������Ч������Ϣ
		void copyEffectEntityBaseAttribute(IEffectEntity* targetObj, IEffectEntity* srcObj);
        ///ѡ��Ԫ��λ������
        void stickSelectElementToTerrain();
        //����ѡ��Ķ���
        void destroySelectElement();

	public:
		//�����������Ķ���
		ISceneObject* createCursorElement(U32 objectDeclID);
		//���ٸ������Ķ���
		void destroyCursorElement(void);
		//���¸������Ķ����λ��
		void updateCursorElement();
		//��ʾ�������Ķ���
		void showCursorElement();
		//���ظ������Ķ���
		void hideCursorElement();

    //*********************************************************
    //�������������
    public:
        ///��ԭ�����
        void revertCamera();
		///�۽���ĳλ��, �ڵ�ͼ�趨�ķ�Χ��
		void focusCamera(Vec3 pos);

    protected:
        ///�������������
        void updateCameraOp( Dbl delta );

		void updateFreeCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );
		void updateGameCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );


        ///�л��ӽ�����
        void switchViewportLock();

		///����һ���Ϸ��������localλ��
		Vec3 getValidCameraDelta(Vec3 pos, Qua orientation, Vec3 delta, bool isLocal = true);

	public:
			///���þ�ͷ�˶�����
		void setCameraDefaultPitch( Flt degree );
		void setCameraPitchRange( Flt degreeMin, Flt degreeMax );
		void setCameraDefaultPos( Vec3 pos );
		void setCameraMoveBoard( Vec3 minBoard, Vec3 maxBoard );
		void setCameraSpeed( Flt transSpeed, Flt rollSpeed );

    //*********************************************************
    private:
        
		//����ģʽ
		OperationType   mOpType;	
		//���ֵ������ģ���б��ID�� ���ǽ�ɫID�� ������תID�� ��Ҫ����ǰ�Ĳ���ģʽ
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

		//�������Ķ���(Ŀǰֻ��Entity��EffectEntity)
		ISceneObject*   mCursorObject;
    };

}

/******************************************************************************/
#endif

