/******************************************************************************/
#ifndef _DYNAMICBLOCKOBJECT_H_
#define _DYNAMICBLOCKOBJECT_H_
/******************************************************************************/
#include "EnginePreqs.h"
#include "IDynamicBlockObject.h"
#include "ISceneNode.h"
#include "ManualMeshManager.h"
#include "BlockObject.h"

/******************************************************************************/

namespace MG
{
    class DynamicBlockObject : public IDynamicBlockObject, public BlockObject, public ISceneNodeLisitener
    {
    public:
		DynamicBlockObject( Scene* scene, IEntity* entity, Flt objectRadius );
        virtual ~DynamicBlockObject();

        ///////////////////////////////////////////////////////////

        virtual ISceneObject*   	getSceneObject();
        virtual void	        	setEnable(Bool enable);
        virtual Bool                getEnable();
		virtual void				setShowBlock(Bool enable);
        virtual void                setStaticBlockEnable(Bool enable);
        virtual void                setStructureMode(Bool enable);
		virtual void				setObjectRadius( Flt objectRadius );
        virtual Int                 getStaticBlockGridDiameter();
		virtual Flt                 getObjectRadius();

		virtual RectF				getBlockRect();

        // ˢ������
		virtual void                refreshBlock( Vec3 oldPos, Vec3 newPos );

				void                update( Flt delta );

    protected:

        // ����ģ����Ϣ
        struct StrutureMeshs
        {
            Byte                        mFlag;

            MeshPtr                     mMesh;
            std::vector< Triangle3D >   mTriangle3DList;
            std::vector< Triangle3D >   mWorldTriangle3DList;

            std::map<UInt, UInt>		mCurrLocationDynamicBlockIndexList;
            std::vector<UInt>			mCurrLocationStaticBlockIndexList;

			VecI2						mMinPoint;
			VecI2						mMaxPoint;

			BlockScope*					mCurrLocationDynamicBlockScope;

			StrutureMeshs():mCurrLocationDynamicBlockScope(NULL)
			{
			}
        };

        ///////////////////////////////////////////////////////////

        // �õ�����ģ����Ϣ
        StrutureMeshs*					getStrutureMeshs( Byte flag );
        
        ///////////////////////////////////////////////////////////

        // �����ϰ�ģ��
        void							loadLocalBlockTriangle();

        // ���������ϰ�ģ��
        void                        	refreshWorldBlockTriangle();
        void                        	refreshWorldBlockTriangle(StrutureMeshs* strutureMeshs);

        // �õ���������
        Vector3							getWorldPos(Vector3 localPos);

        ///////////////////////////////////////////////////////////

        // ������ײ
        void			       			addBlock( Vec3 oldPos, Vec3 pos );
        void			       			addBlock( Vec3 oldPos, Vec3 pos, Byte flag );

        // �Ƴ���ײ
        void			       			removeBlock( Vec3 newPos = Vec3(0,0,0));

        ///////////////////////////////////////////////////////////

		//virtual UInt					getCollideBlockIndex();
		//void							setCollideBlockIndex( UInt index );

		virtual IDynamicBlockObject*	getCollideBlockObject();
		void							setCollideBlockObject( IDynamicBlockObject* collideBlockObject );

        // �ж��Ƿ�������ռ�Ķ�̬�ϰ�����
        virtual Bool                	isBelongCurrLocationDynamicBlockIndex( UInt index, Byte flag );
        virtual Bool                	isBelongCurrLocationDynamicBlockIndex( UInt index );

        // �ж��Ƿ�������ռ�ľ�̬�ϰ�����
        virtual Bool                	isBelongCurrLocationStaticBlockIndex( UInt index, Byte flag );
        virtual Bool                	isBelongCurrLocationStaticBlockIndex( UInt index );

        // �õ���ռ�Ķ�̬�ϰ������б�
        void                        	getCurrLocationDynamicBlockIndexList( std::map<UInt, UInt>& list );
        void                        	getCurrLocationDynamicBlockIndexList( std::map<UInt, UInt>& list, Byte flag );

        ///////////////////////////////////////////////////////////

    protected:

        virtual void                	onPositionChanged( Vec3& oldPos, Vec3 newPos );
        virtual void                	onOrientationChanged( Qua& oldQua, Qua newQua );
        virtual void                	onVisibleChanged( Bool visible );

    private:
        
        /////////////////////////////////////////////////////////////////////////////

        Scene*          				mScene;
        Bool							mEnable;
		Bool							mShowBlock;
		BlockManager*					mBlockManager;
		IEntity*	            		mEntity;

        Int								mStaticBlockGridDiameter;
		Flt								mObjectRadius;

        /////////////////////////////////////////////////////////////////////////////

        //UInt							mCollideBlockIndex;
		IDynamicBlockObject*			mCollideBlockObject;
        
        /////////////////////////////////////////////////////////////////////////////

        Bool                            mStaticBlockEnable;

        std::map<Byte, StrutureMeshs>   mStrutureMeshMap;
        Bool                            mStructureMode;
        Bool                            mBlockDirty;

		std::map<UInt, IEntity*>		mTestEntityList;

        /////////////////////////////////////////////////////////////////////////////

        Vec3                   			 mPos;
		Vec3                   			 mOldPos;
        Qua                    			 mQua;
        Qua                    			 mInverseQua;

    };
}

/******************************************************************************/
#endif