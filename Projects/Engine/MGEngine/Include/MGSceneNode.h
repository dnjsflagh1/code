/******************************************************************************/
#ifndef _MGSCENENODE_H_
#define _MGSCENENODE_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ISceneNode.h"
#include "LinedState.h"
#include "OgreAnimationState.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//��Ϸ�����ڵ�
	/******************************************************************************/
    class MGSceneNode : public ISceneNode 
	{
	public:
        MGSceneNode( Ogre::SceneNode* parent, Scene* scene );
        virtual ~MGSceneNode();

        /// �õ���������
        virtual IScene*     				getScene();

        ////////////////////////////////////////////////////////////////////////////////////////


        /// ��ʱ���ÿɼ���
                void        				tempSetVisible(Bool visible) ;
                void        				revertVisible() ;

        /// ���ÿɼ���
        virtual void        				setVisible(Bool visible) ;
        /// �õ��ɼ��� 
        virtual Bool        				getVisible();

        ////////////////////////////////////////////////////////////////////////////////////////


        /// ����λ������.
        virtual void        				setPosition(Vec3& pos) ;
        /// �õ�λ������.
		virtual void        				getPosition(Vec3& pos) ;
		/// ���ó�ʼλ��ƫ��. 
		virtual void						setPositionOffset(const Vec3& offset);
		/// ��ȡ��ʼλ��ƫ��. 
		virtual const Vec3&					getPositionOffset() const;
		/// �����Ļ����
		virtual void						getScreenPosition(Vec2& screenPos);
		/// �õ�λ�ñ仯��ǩ. 
		virtual Bool						getPositionDirty();
        /// ���λ�ñ仯��ǩ. 
        virtual void						clearPositionDirty();

        /// ���λ��.
        virtual void        				translate(Vec3& d, TransformSpace relativeTo = TS_PARENT) ;


        ////////////////////////////////////////////////////////////////////////////////////////


        /// ��������.
        virtual void        				setScale(Vec3& scale) ;
        /// �õ�����.
		virtual void        				getScale(Vec3& scale) ;
		/// ���ó�ʼ����. 
		virtual void						setInitScale(const Vec3& scale);
		/// ��ȡ��ʼ����. 
		virtual const Vec3&					getInitScale() const;
		/// �õ����ű仯��ǩ. 
		virtual Bool        				getScaleDirty();
        /// ������ű仯��ǩ. 
        virtual void       			 		clearScaleDirty() ;

        ////////////////////////////////////////////////////////////////////////////////////////


        /// ����4Ԫ��.
        virtual void       			 		setOrientation(Qua& quaternion) ;
        /// �õ�4Ԫ��.
		virtual void       			 		getOrientation(Qua& quaternion) ;
		/// �õ�4Ԫ���仯��ǩ.  
		virtual Bool						getOrientationDirty();
        /// �õ�4Ԫ���仯��ǩ.  
        virtual void        				clearOrientationDirty();


        ////////////////////////////////////////////////////////////////////////////////////////

        /// ���÷���.
        virtual void        				setDirection(Vec3& vec, TransformSpace relativeTo = TS_WORLD) ;
        /// �õ�����.
		virtual void        				getDirection(Vec3& vec);

        /// ����ĳ��.
        virtual void        				lookAt(Vec3& targetPoint, TransformSpace relativeTo = TS_WORLD) ;

        /// roll��ת.
		virtual void        				roll( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
        /// pitch��ת.
		virtual void        				pitch( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
        /// yaw��ת.
		virtual void        				yaw( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;

        /// ����ĳ�᷽����ת.
		virtual void						rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo = TS_LOCAL) ;


		////////////////////////////////////////////////////////////////////////////////////////

		virtual void						playNodeAnimation( Str8 name, Bool isLoop = false, Bool isReverse = false );

		virtual void						updateNodeAnimations(Flt delta);

		virtual void						clearNodeAnimations();

        ////////////////////////////////////////////////////////////////////////////////////////

        /// ��������
        virtual void        				stickTerrain() ;
        virtual void        				setStickTerrainEnable(Bool enable);

        ////////////////////////////////////////////////////////////////////////////////////////


        /// ����
        void                				update( Flt delta );

	    ////////////////////////////////////////////////////////////////////////////////////////

	public:

        Ogre::SceneNode*					getOgreSceneNode();

    protected:

        /// ���ñ��������е�ǰ��Եķ���, dirΪlocal transform, Ĭ��Z��
        void								setLocalDirectionVector( const Vector3& dir );
        /// �õ����������е�ǰ��Եķ���
        const Vector3&						getLocalDirectionVector();
        /// �õ����������е�ǰ��Եķ��� 
        const Vector3&						getWorldDirectionVector();
        
    protected:

        Scene*								mScene;

        ///Ogre��������ڵ����
		Ogre::SceneNode*					mOgreParentSceneNode;
        ///Ogre��������ڵ����
		Ogre::SceneNode*					mOgreSceneNode;

        /////////////////////////////////////////////////////////////////////

		Bool 								mPositionDirty;
		Bool 								mScaleDirty;
		Bool 								mOrientationDirty;


        /////////////////////////////////////////////////////////////////////

        //������
        Vector3 							mLocalDirectionVector;
        Vector3 							mWorldDirectionNormalisedVector;

        /// �������߷���
        Vec3								mTerrainRayDir1;
        /// �������߷���
        Vec3								mTerrainRayDir2;
        
        /////////////////////////////////////////////////////////////////////

		//�߻�����ĳ�ʼλ��ƫ��
		Vec3								mPositionOffset;

		//�߻�����ĳ�ʼ��С����
		Vec3								mInitScale;

		/////////////////////////////////////////////////////////////////////

        // �ɼ���
        Bool 								mVisible;

        // �Ƿ�����
        Bool 								mStickTerrainEnable;

        // ʵ���б�
		std::vector<IEntity*>				mEntityList;

        /////////////////////////////////////////////////////////////////////

		/// �����б� 
		typedef std::map<Str, AnimationState*> AnimationMap;
		typedef AnimationMap::iterator AnimationMap_iter;
		typedef AnimationMap::const_iterator AnimationMap_constIter;
		AnimationMap						mAnimations;

		/////////////////////////////////////////////////////////////////////

	};
}

/******************************************************************************/

#endif
