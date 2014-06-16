/******************************************************************************/
#ifndef _CAMERA_H_
#define _CAMERA_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ICamera.h"
#include "LinedState.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//�����
	/******************************************************************************/
    class Camera : public ICamera
	{
        friend class Scene;

	public:
        Camera(CChar* camName, Scene* scene);
        virtual ~Camera();

        /// ����
        void                        update( Flt delta );

        /// �õ�����
        virtual SceneObjectTypes    getType();

        /// ���ú͵õ�Fov 
        virtual void                setFov(Flt degree) ;
        virtual Flt                 getFov() ;

		/// ����Զ�����ƽ��
		virtual void				setFarClipDistance(Flt farDist) ;
		virtual void				setNearClipDistance(Flt nearDist) ;

        /// ���������ת��Ϊ��Ļ�����
        virtual void	            worldPointToScreenPoint(const Vec3& worldPos, Vec2& screenPos) ;

        /// �õ�����������������λ��
        virtual Flt	                getWorldDistance(const Vec3& worldPos) ;

		/// �õ�����ת��Ϊ��������ֵ
		virtual void                getMouseViewportRay(Vec3& pos, Vec3& dir, Vec2 offset=Vec2(0,0));

        /// �õ���������
        virtual IScene*             getScene() {return NULL;};

        ///////////////////////////////////////////////////////////////////////////

		/// ���ÿɼ��� 
		virtual void                setVisible(Bool visible);
        /// �õ��ɼ��� 
        virtual Bool                getVisible();

        ///////////////////////////////////////////////////////////////////////////

        /// ��עĳһ��
        virtual void                focusPosition(Vec3& pos);

		/// ����λ������. 
		virtual void                setPosition(Vec3& pos);
		/// �õ�λ������. 
		virtual void                getPosition(Vec3& pos) ;
		/// ���ó�ʼλ��ƫ��. 
		virtual void				setPositionOffset(const Vec3& offset) { mPositionOffset = offset;};
		/// ��ȡ��ʼλ��ƫ��. 
		virtual const Vec3&			getPositionOffset() const {return mPositionOffset;};
		/// �õ�λ�ñ仯��ǩ. 
		virtual Bool                getPositionDirty(){return mPositionDirty;};

        /// ���λ��. 
        virtual void                translate(Vec3& d, TransformSpace relativeTo = TS_LOCAL) ;

        ///////////////////////////////////////////////////////////////////////////

		/// ��������. 
		virtual void                setScale(Vec3& scale) ;
		/// �õ�����. 
		virtual void                getScale(Vec3& scale) ;
		/// ���ó�ʼ����. 
		virtual void				setInitScale(const Vec3& scale) { mInitScale = scale; };
		/// ��ȡ��ʼ����. 
		virtual const Vec3&			getInitScale() const { return mInitScale; };
		/// �õ����ű仯��ǩ. 
		virtual Bool                getScaleDirty(){return mScaleDirty;};

        ///////////////////////////////////////////////////////////////////////////

		/// ����4Ԫ��. 
		virtual void                setOrientation(Qua& quaternion) ;
		/// �õ�4Ԫ��. 
		virtual void                getOrientation(Qua& quaternion) ;
		/// �õ�4Ԫ���仯��ǩ.  
		virtual Bool                getOrientationDirty(){return mOrientationDirty;};

		/// ���÷���. 
		virtual void                setDirection(Vec3& vec, TransformSpace relativeTo = TS_WORLD) ;
		/// �õ�����. 
		virtual void                getDirection(Vec3& vec);

		/// ����ĳ��. 
		virtual void                lookAt(Vec3& targetPoint, TransformSpace relativeTo = TS_WORLD);

		/// roll��ת. 
		virtual void                roll( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
		/// pitch��ת. 
		virtual void                pitch( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
		/// yaw��ת. 
		virtual void                yaw( Flt angle, TransformSpace relativeTo = TS_LOCAL);
        /// �õ�yaw��ת 
        virtual Flt                 getYaw();
        /// �õ�pitch��ת 
        virtual Flt                 getPitch();

		/// ����ĳ�᷽����ת. 
		virtual void                rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo = TS_LOCAL);

        ///////////////////////////////////////////////////////////////////////////

        /// ��������
        virtual void                stickTerrain() {};

        ///////////////////////////////////////////////////////////////////////////

        /// �õ�Ogre���������
        Ogre::Camera*               getOgreCamera(){return mOgreCamera;};

    protected:
        ///������ڵ����
		MGSceneNode* mSceneNode;
        /// Ogre���������
        Ogre::Camera* mOgreCamera;
        /// ������������
        Scene* mScene;
        //LinedStateManager mLinedStateManager;

        /////////////////////////////////////////////////////////////////////

        Bool 								mPositionDirty;
        Bool 								mScaleDirty;
        Bool 								mOrientationDirty;

		//�߻�����ĳ�ʼλ��ƫ��
		Vec3								mPositionOffset;
		//�߻�����ĳ�ʼ��С����
		Vec3								mInitScale;
	};
	
}

/******************************************************************************/

#endif
