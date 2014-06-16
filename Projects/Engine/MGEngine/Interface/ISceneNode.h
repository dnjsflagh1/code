/******************************************************************************/
#ifndef _ISCENENODE_H_
#define _ISCENENODE_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "LinedState.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //
    /******************************************************************************/
    class ISceneNodeLisitener
    {
    public:

        virtual void    onRemove(ISceneNode* node){};

        virtual void    onPositionChanged( Vec3& oldPos, Vec3 newPos ){};
        virtual void    onOrientationChanged( Qua& oldQua, Qua newQua ){};
        virtual void    onScaleChanged( Vec3& oldScale, Vec3 newPosScale ){};
        virtual void    onVisibleChanged( Bool visible ){};
    };


    /******************************************************************************/
	//��Ϸ�����нڵ�
	/******************************************************************************/
	class ISceneNode
	{
	public:
        /// �ռ�����
        enum TransformSpace
        {
            /// Transform is relative to the local space
            TS_LOCAL,
            /// Transform is relative to the space of the parent node
            TS_PARENT,
            /// Transform is relative to world space
            TS_WORLD
        };
	public:

        //////////////////////////////////////////////////////////////////////////////////////////////////

        virtual ~ISceneNode()
        {
            notifyRemove();
        }
        
        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// �õ���������
        virtual IScene*                 getScene() = 0;
        /// ���ÿɼ��� 
		virtual void                    setVisible(Bool visible) = 0;
        /// �õ��ɼ��� 
        virtual Bool                    getVisible() = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// ����λ������. 
        virtual void                    setPosition(Vec3& pos) = 0;
        /// �õ�λ������. 
		virtual void                    getPosition(Vec3& pos) = 0;
		/// ���ó�ʼλ��ƫ��. 
		virtual void                    setPositionOffset(const Vec3& offset) = 0;
		/// ��ȡ��ʼλ��ƫ��. 
		virtual const Vec3&				getPositionOffset() const = 0;
		/// �����Ļ����
		virtual void					getScreenPosition(Vec2& outPos){};
		/// �õ�λ�ñ仯��ǩ. 
		virtual Bool                    getPositionDirty() = 0;
		/// ���λ�ñ仯��ǩ. 
		virtual void                    clearPositionDirty(){};

        /// ���λ��. 
        virtual void                    translate(Vec3& d, TransformSpace relativeTo = TS_LOCAL) = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// ��������. 
        virtual void                    setScale(Vec3& scale) = 0;
        /// �õ�����. 
		virtual void                    getScale(Vec3& scale) = 0;
		/// ���ó�ʼ����. 
		virtual void                    setInitScale(const Vec3& scale) = 0;
		/// ��ȡ��ʼ����. 
		virtual const Vec3&				getInitScale() const = 0;
		/// �õ����ű仯��ǩ. 
		virtual Bool                    getScaleDirty() = 0;
        /// ������ű仯��ǩ. 
        virtual void                    clearScaleDirty(){};


        //////////////////////////////////////////////////////////////////////////////////////////////////


        /// ����4Ԫ��. 
        virtual void                    setOrientation(Qua& quaternion) = 0;
        /// �õ�4Ԫ��. 
		virtual void                    getOrientation(Qua& quaternion) = 0;
        /// �õ�4Ԫ���仯��ǩ.  
		virtual Bool                    getOrientationDirty() = 0;
        /// ���4Ԫ���仯��ǩ. 
        virtual void                    clearOrientationDirty(){};

        /// ���÷���. 
        virtual void                    setDirection(Vec3& vec, TransformSpace relativeTo = TS_WORLD) = 0;
        /// �õ�����. 
		virtual void                    getDirection(Vec3& vec) = 0;

        /// ����ĳ��. 
        virtual void                    lookAt(Vec3& targetPoint, TransformSpace relativeTo = TS_WORLD) = 0;


        //////////////////////////////////////////////////////////////////////////////////////////////////


        /// roll��ת. 
		virtual void                    roll( Flt angle, TransformSpace relativeTo = TS_LOCAL) = 0;
        /// pitch��ת. 
		virtual void                    pitch( Flt angle, TransformSpace relativeTo = TS_LOCAL) = 0;
        /// yaw��ת. 
		virtual void                    yaw( Flt angle, TransformSpace relativeTo = TS_LOCAL) = 0;
        /// �õ�yaw��ת 
        virtual Flt                     getYaw() {return 0;};
        /// �õ�pitch��ת 
        virtual Flt                     getPitch() {return 0;};
        
        /// ����ĳ�᷽����ת. 
		virtual void                    rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo = TS_LOCAL) = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

		virtual void					playNodeAnimation( Str8 name, Bool isLoop = false, Bool isReverse = false ){};

		//////////////////////////////////////////////////////////////////////////////////////////////////


        /// ��������
        virtual void                    stickTerrain() = 0;
        /// ������������
        virtual void                    setStickTerrainEnable(Bool enable){};

        //////////////////////////////////////////////////////////////////////////////////////////////////

        // �õ�״̬������, ��Ҫ�������״̬������
        LinedStateManager*              getLinedStateManager() { return &mLinedStateManager; };

        //////////////////////////////////////////////////////////////////////////////////////////////////

        // ���Ӽ�����
        void                            addSceneNodeLisitener( Str name, ISceneNodeLisitener* lisitener )
        {
            mLisiteners[name] = lisitener;
        }
        
        // �Ƴ�������
        void                            removeSceneNodeLisitener( Str name )
        {
            std::map<Str,ISceneNodeLisitener*>::iterator iter = mLisiteners.find( name );
            if ( iter!=mLisiteners.end() )
            {
                mLisiteners.erase( iter );
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////

    protected:

        // ֪ͨ�¼����������
        void    notifyPositionChanged( Vec3& oldPos, Vec3 newPos )
        {
            std::map<Str,ISceneNodeLisitener*>::iterator iter = mLisiteners.begin();
            for ( ;iter!=mLisiteners.end(); iter++)
            {
				if ( iter->second )
					iter->second->onPositionChanged( oldPos, newPos );
            }
        }
        void    notifyOrientationChanged( Qua& oldQua, Qua newQua )
        {
            std::map<Str,ISceneNodeLisitener*>::iterator iter = mLisiteners.begin();
            for ( ;iter!=mLisiteners.end(); iter++)
            {
				if ( iter->second )
					iter->second->onOrientationChanged( oldQua, newQua );
            }
        }
        void    notifyScaleChanged( Vec3& oldScale, Vec3 newPosScale )
        {
            std::map<Str,ISceneNodeLisitener*>::iterator iter = mLisiteners.begin();
            for ( ;iter!=mLisiteners.end(); iter++)
            {
				if ( iter->second )
					iter->second->onScaleChanged( oldScale, newPosScale );
            }
        }
        void    notifyVisibleChanged( Bool visible )
        {
            std::map<Str,ISceneNodeLisitener*>::iterator iter = mLisiteners.begin();
            for ( ;iter!=mLisiteners.end(); iter++)
            {
				if ( iter->second )
					iter->second->onVisibleChanged( visible );
            }
        }
        void    notifyRemove()
        {
            std::map<Str,ISceneNodeLisitener*>::iterator iter = mLisiteners.begin();
            for ( ;iter!=mLisiteners.end(); iter++)
            {
				if ( iter->second )
					iter->second->onRemove(this);
            }
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////

    protected:

        LinedStateManager                   mLinedStateManager;

        std::map<Str,ISceneNodeLisitener*>  mLisiteners;

	};


}

/******************************************************************************/
#endif
