#ifndef __GRASS_H__
#define __GRASS_H__

#include "EnginePreqs.h"
#include "ITree.h"
#include "ISceneNode.h"
#include "OgreWireBoundingBox.h"

namespace MG
{

#define INVALID_ROWCOL	INT_MAX
#define INVALID_GRASS	0xFFFFFFFF
	/******************************************************************************/
	// ֲ��OGRE����
	/******************************************************************************/
	class GrassMovable : public MovableObject
	{
	public:
		virtual const String& getMovableType(void) const;
		virtual const AxisAlignedBox& getBoundingBox(void) const ;
		virtual const AxisAlignedBox& getWorldBoundingBox(bool derive = false) const;
		virtual bool isInScene() const { return true; };
		virtual Real getBoundingRadius(void) const ;
		virtual void _updateRenderQueue(RenderQueue* queue);
		virtual void visitRenderables(Renderable::Visitor* visitor, bool debugRenderables = false);

	protected:

		AxisAlignedBox mAABB;
	};


	/******************************************************************************/
	// ֲ������
	/******************************************************************************/

	class Grass : public IGrass, public ISceneNode
	{
	public:

		Grass( Scene* scene, TreeManager* mgr, SpeedTreeSystem* speedTreeSys, 
			UInt grassID, const Vec3& vPos, Flt w, Flt h );
		virtual ~Grass();

	public:
		///��ʼ��
		bool								init(Flt w, Flt h);
		/// �õ�����
		virtual SceneObjectTypes            getType();
		/// �õ��ռ�ڵ�
		virtual ISceneNode*                 getSceneNode();

		virtual UInt						getBaseGrassId() { return mGrassID;}

		virtual Flt							width();

		virtual void						width(Flt w);

		virtual Flt							height();

		virtual void						height(Flt h);
		//virtual Int							getInstanceId() { return mInstanceID; }

		//void								setInstanceId(Int id) { mInstanceID = id; }

		MovableObject*						getOgreMovable();

		Int									row() const { return mRow; }

		Int									col() const { return mCol; }

		UInt								grassID() const { return mGrassIndex; }
		
		void								grassID(UInt grassId) { mGrassIndex = grassId; }

	protected:

		void								createOgreMovable();
		void								destroyOgreMovable();

	public:

		/// �õ���������
		virtual IScene*                     getScene();

		/// ���ÿɼ���
		virtual void                        setVisible(Bool visible) ;
		/// �õ��ɼ���
		virtual Bool                        getVisible() ;

		/////////////////////////////////////////////////////////////////////////////////////

		/// ����λ������.
		virtual void                        setPosition(Vec3& vPos) ;
		/// �õ�λ������.
		virtual void                        getPosition(Vec3& vPos) ;
		/// ���ó�ʼλ��ƫ��. 
		virtual void						setPositionOffset(const Vec3& offset) { mPositionOffset = offset; };
		/// ��ȡ��ʼλ��ƫ��. 
		virtual const Vec3&					getPositionOffset() const { return mPositionOffset; };
		/// �õ���Ļ����
		virtual void                        getScreenPosition(Vec2& outPos) ;

		/// �õ�λ�ñ仯��ǩ. 
		virtual Bool                        getPositionDirty();
		/// ���λ�ñ仯��ǩ. 
		virtual void                        clearPositionDirty();

		/// ���λ��.
		virtual void                        translate(Vec3& d, TransformSpace relativeTo = TS_PARENT) ;

		/////////////////////////////////////////////////////////////////////////////////////

		/// ��������.
		virtual void                        setScale(Vec3& scale) ;
		/// �õ�����.
		virtual void                        getScale(Vec3& scale) ;
		/// ���ó�ʼ����. 
		virtual void						setInitScale(const Vec3& scale) { mInitScale = scale; };
		/// ��ȡ��ʼ����. 
		virtual const Vec3&					getInitScale() const { return mInitScale; };
		/// �õ����ű仯��ǩ. 
		virtual Bool                        getScaleDirty();
		/// ������ű仯��ǩ. 
		virtual void                        clearScaleDirty() ;

		/////////////////////////////////////////////////////////////////////////////////////

		/// ����4Ԫ��.
		virtual void                        setOrientation(Qua& quaternion) ;
		/// �õ�4Ԫ��.
		virtual void                        getOrientation(Qua& quaternion) ;
		/// �õ�4Ԫ���仯��ǩ.  
		virtual Bool                        getOrientationDirty();
		/// �õ�4Ԫ���仯��ǩ.  
		virtual void                        clearOrientationDirty();

		/// ���÷���.
		virtual void                        setDirection(Vec3& vec, TransformSpace relativeTo = TS_WORLD) ;
		/// �õ�����.
		virtual void                        getDirection(Vec3& vec);

		/// ����ĳ��.
		virtual void                        lookAt(Vec3& targetPoint, TransformSpace relativeTo = TS_WORLD) ;

		/// roll��ת.
		virtual void                        roll( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
		/// pitch��ת.
		virtual void                        pitch( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
		/// yaw��ת��������ת����Ϊ��
		virtual void                        yaw( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;

		/// ����ĳ�᷽����ת.
		virtual void                        rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo = TS_LOCAL) ;

		/////////////////////////////////////////////////////////////////////////////////////

		/// ��������
		virtual void                        stickTerrain();

		//void								updateBox(AxisAlignedBox& aabb);

		//void								renderBox();

		const AxisAlignedBox&				getWorldBoundingBox(void);

		const AxisAlignedBox&				getBoundingBox(void) const { return mBoundingBox; }

	protected:

		

	private:

		GrassMovable*		mGrassMovable;

		UInt				mGrassID;
		
		Int					mRow;

		Int					mCol;

		UInt				mGrassIndex;

		AxisAlignedBox		mBoundingBox;

		AxisAlignedBox		mWorldAABB;
		
		Vec3				mPos;
		
		Vec3				mScale;

		//�߻�����ĳ�ʼλ��ƫ��
		Vec3				mPositionOffset;
		//�߻�����ĳ�ʼ��С����
		Vec3				mInitScale;

		Scene*				mScene;

		TreeManager*		mMgr;

		SpeedTreeSystem*	mSpeedTreeSystem;
	};
}
#endif