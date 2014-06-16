
/******************************************************************************/
#ifndef __TREE_H__
#define __TREE_H__
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITree.h"
#include "ISceneNode.h"
#include "OgreWireBoundingBox.h"
#include "Forest/Forest.h"

namespace MG
{


	/******************************************************************************/
	// ֲ��OGRE����
	/******************************************************************************/
	class TreeMovable : public MovableObject
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
	// SpeedTree Instance
	/******************************************************************************/

	class TreeInstance : public SpeedTree::CInstance
	{
	
	};

    /******************************************************************************/
    // ֲ������
    /******************************************************************************/

    class Tree : public ITree, public ISceneNode
    {
    public:
		Tree( Scene* scene, TreeManager* mgr, MG::SpeedTreeSystem* speedTreeSys, 
			UInt baseTreeID, CChar* pBaseTreeName);

        virtual ~Tree();
        
    public:

        /// �õ�����
        virtual SceneObjectTypes            getType();
        /// �õ��ռ�ڵ�
        virtual ISceneNode*                 getSceneNode();

		virtual UInt						getBaseTreeId() { return mTreeModelID;}

		virtual	void						setReflect(Bool bReflect);

		virtual Bool						isNeedReflect();

		//virtual Int							getInstanceId() { return mInstanceID; }

		//void								setInstanceId(Int id) { mInstanceID = id; }

		MovableObject*						getOgreMovable();
		
		Bool								init(const Vec3& pos);

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
        virtual void                        setPosition(Vec3& pos) ;
        /// �õ�λ������.
        virtual void                        getPosition(Vec3& pos) ;
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

        // ����ʵ��
		Bool	createInstance( CChar* pBaseTreeName, const Vec3& pos );

        // ����ʵ��
        Bool    destroyInstance();

    private:

		TreeMovable*		mTreeMovable;

		UInt				mTreeModelID;

		std::string			mBaseTreeName;

		TreeInstance		mTreeInstance;
		//Int					mInstanceID;

		AxisAlignedBox		mBoundingBox;

		AxisAlignedBox		mWorldAABB;

		//Ogre::WireBoundingBox*	mWireBoundingBox;

        Scene*				mScene;

        TreeManager*		mMgr;

        SpeedTreeSystem*	mSpeedTreeSystem;

		//�߻�����ĳ�ʼλ��ƫ��
		Vec3				mPositionOffset;
		//�߻�����ĳ�ʼ��С����
		Vec3				mInitScale;
    };
}
#endif