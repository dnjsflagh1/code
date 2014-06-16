/******************************************************************************/
#ifndef _SCENEOBJECTCONTROLLER_H_
#define _SCENEOBJECTCONTROLLER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ISceneObjectController.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//��Ϸ��������������ӿ�
	/******************************************************************************/
	class SceneObjectController : public ISceneObjectController, public ISceneNodeLisitener
	{
        friend class Scene;
	public:
		SceneObjectController(Scene* scene);
		~SceneObjectController();

		/// ����
		void                    update( Flt delta );

		/// �����Ƿ���� 
		virtual void            setEnable(Bool enable);
		/// �Ƿ��Ѿ����� 
		virtual Bool            getlEnable();

		/// �ر�ѡ�в���
		virtual void			setFocusEnable( Bool enable );
		/// ��ȡ�Ƿ�ѡ�в���
		virtual Bool			getFocusEnable() { return mFocusEnable; };

		/// ���ÿ��ƶ��� 
		virtual void            setFocus( ISceneObject* obj );
		/// �õ����ƶ��� 
		virtual ISceneObject*   getFocus();
		/// ����ѡ�еĶ���
		virtual void			setIgnoreFocus( ISceneObject* obj );

		/// �����ѡ������
		virtual void			clearMultiFocus( Bool objectDeleted = false );
		/// ��ȡ��ѡ������
		virtual void			getMultiFocusList( std::vector<ISceneObject*>& objectList );
		/// ���п�ѡ����
		virtual void			multiSelect( RectF rectF );
		/// ����ѡ��
		virtual void			addToMultiSelect ( ISceneObject* object );
		/// ���з�ѡ
		virtual void			unSelect( ISceneObject* object );

		/// �Ƿ�����˿�ѡ�ƶ�����
		virtual Bool			getObjectOperationDirty() { return mObjectOperationDirty; }

        /// ������ײ����ʾ
        virtual void            setBoundingBoxVisible( Bool isVisible );

        /// �õ����Ʊ仯״̬ 
        virtual Bool            getChangedDirty(){return mChangedDirty;};

        /// ���ÿ��Ʒ�ʽ
        virtual void            setControlType( ControlType type );

        /// ��ס����
        virtual void            stickTerrain();

		/// �ж��Ƿ������߶�( �����߶�)
		virtual bool			isTerrainSticked() { return mTerrainSticked; };

		virtual void			setTerrainSticked(bool terrainSticked ) { mTerrainSticked = terrainSticked; };

	protected:

        /// ��ⳡ������ѡ��
        Bool                    updateSceneObjectFocus();
        Bool                    updateSceneObjectRectFocus();

        /// ��Ⱦ�¼�
        void                    postFindVisibleObjects(Ogre::SceneManager* source, 
            Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v);

		//@{ AxisObjects 

			/// �������깤�߶��� 
			void    createUtilObjects();
			/// �������깤�߶��� 
			void    destroyUtilObjects();

            /// ��⹤�߶���ѡ��
            Bool    updateUtilObjectFocus();
            /// �������깤�߶���λ�� 
            void    updateUtilObjectsLocation();
			/// �������깤�߶������� 
			void	updateUtilObjectsScale();
            /// �������깤�߶������ 
            void    updateUtilObjectsOp();

			/// ���ÿɼ���
			void    setUtilObjectsVisible( Bool visible );
			/// �ж��Ƿ����������
			Bool    isUtilObject( ISceneObject* obj );
            
			/// ���³�ʼ�����³��ֵ�������������
			void	reinitAllUtilObjectsScale();
            /// ���ñ�ѡ�к�����깤�߶���Ĳ��� 
            void    setFocusedUtilObjectMaterial( Int index );
            /// ��ԭ���е����깤�߶���Ĳ��� 
            void    restoreAllUtilObjectsMaterial();

		//@{ 
            ///  ���������ʽSLG. ���������ƶ����������λ�ã��߶ȣ���������ת
            void    updateSLGOp();

			/// �������ֲ�����ʽ����Ч�Ĳ���
			void	updateCommonOp();

			/// 
			void	beginUpdateMultiFocusObjects();

			void	endUpdateMultiFocusObjects();

		//@}

	protected:

		/// ��sceneNodeListener�̳й���
			void	onRemove(ISceneNode* node);

	protected:

		///��������
		Scene* mScene;
		///�Ƿ���
		Bool mEnable;
		///�Ƿ���ѡ�в���
		Bool mFocusEnable;
		///���Ʊ仯״̬ 
		Bool mChangedDirty;
		///����λ��ת��仯״̬;
		Bool mObjectOperationDirty;
		///�Ƿ�����߶Ȳ���;����߶Ȳ��������� ��ô�������ɿ�������ĸ߶ȡ� �������ŵر�仯�߶�
		Bool mTerrainSticked;

		///��Ҫ���ԵĶ���
		ISceneObject* mIgnoreObject;
		///��ǰ���ƶ���
		ISceneObject* mSceneObject;
		///��ѡ����( ���߲�ѯ�ص���� )
		std::vector<ISceneObject*> mRayQueryRes;
		///��ѡ����
		std::vector<ISceneObject*> mMultiSelectRes;

        Vec3 mMouseRayTerrainIntersection;
        Bool mIsMouseRayTerrainIntersectionValid;
		Bool mIsMovingSceneObject;

	protected:

		///���깤������
		enum AxisUtilType
		{
			Axis_X = 0,
			Axis_Y,
			Axis_Z,
			Axis_XY,
			Axis_XZ,
			Axis_YZ
		};
		static const Int AxisUtilCount = 6;
		/// �������ģ��������
		static const String AxisUtilObjectsMeshName[AxisUtilCount];
		/// ������������� 
		static const String AxisUtilObjectsName[AxisUtilCount];
		/// �����������
		MG::Entity* mAxisUtilObjects[AxisUtilCount];
        /// ѡ�е������������
        Int mSelectUtilIndex;
		/// ����XYZ���ԭʼ����
		Flt mUtilAxisLength;
		/// XY�棬YZ�棬XZ��ı߳�
		Flt	mUtilPlaneSize;
		/// ����XYZ���ԭʼ����
		Flt mUtilAxisBaseScale;

        /// ��������
        ControlType mControlType;
        /// ���깤���ƶ��ٶ�
        Flt mMoveSpeed;
        /// ���깤����ת�ٶ�
        Flt mYawRotateSpeed;
        /// ����ѡ��������λ�� 
        Vector3 mLastMouse3DWorldPos;

        // �Ƿ��ѡ��
        Bool isFocusRect;
		Vec2 mRectPressedMousePos;
		Vec2 mRectPressedScreenPos;
        Vec2 mRectHoldMousePos;
		Vec2 mRectHoldScreenPos;

		/// ѡ�е�λ��λ�ñ仯
		Qua  mLastFrameSingleFocusOrientation;
		Vec3 mLastFrameSingleFocusPosition;
		Vec3 mLastFrameSingleFocusScale;

		Ogre::SceneNode* mTreeBoundingBoxRenderNode;
	};

}

/******************************************************************************/
#endif
