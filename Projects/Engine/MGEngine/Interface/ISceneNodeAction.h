/******************************************************************************/
#ifndef _ISCENENODEACTION_H
#define _ISCENENODEACTION_H
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "LinedState.h"
#include "IPathFinder.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //ISceneNodeLineMoveAction
    /******************************************************************************/
    class ISceneNodeLineMoveToAction : public LinedStateObject, public LinedStateObjectListener
    {
    public:

        ISceneNodeLineMoveToAction(Str name)
            :LinedStateObject( name )
        {
        }
        /// 设置移动速度
        virtual void                    setMoveSpeed( Flt speed ) = 0;
        /// 移动到指定位置
        virtual void                    setMoveToDestination( const Vec3& dest ) = 0;
        /// 设置是否贴地面
        virtual void                    setStickTerrain( Bool isStickTerrain ) = 0;
		// 设置是否忽略高度， 只进行2维距离运算
		virtual void		            setIgnoreHeight( Bool isIgnoreHeight ) = 0;
		// 设置是否启用扰动草
		virtual void		            setPerturbEnable( Bool isPerturb ) = 0;
		// 设置扰动草半径
		virtual void		            setPerturbRadiu( Flt radiu ) = 0;
		// 设置扰动草频率
		virtual void		            setPerturbFrequnce( UInt freq ) = 0;
    };

    /******************************************************************************/
    //ISceneNodeGridLineMoveToAction
    /******************************************************************************/
    class ISceneNodeGridLineMoveToAction : public ISceneNodeLineMoveToAction
    {
    public:
		enum MoveToPathFindType
		{
			PFT_NULL,
			PFT_DYNAMIC,
			PFT_STATIC,
			PFT_NOPATHFIND,
		};


		////////////////////////////////////////////////////////

        ISceneNodeGridLineMoveToAction(Str name)
            :ISceneNodeLineMoveToAction( name )
        {
        }
        /// 设置是否检测碰撞
        virtual void                    setBlockCheck( Bool enable ) = 0;
        /// 设置是否遇到碰撞等待，如果设置false,遇到障碍则退出action
        virtual void                    setIsWait( Bool enable ) = 0;

		virtual void					setMoveToPathFindType( MoveToPathFindType moveToPathFindType ) = 0;

        /// 是否停止中
        virtual Bool                    isBlockStop() = 0;
    };

    /******************************************************************************/
    //ISceneNodeYawToAction
    /******************************************************************************/
    class ISceneNodeYawToAction : public LinedStateObject
    {
    public:
        ISceneNodeYawToAction(Str name)
            :LinedStateObject( name )
        {
        }

        /// 设置Y轴转向速度
        virtual void        setYawSpeed( Flt speed ) = 0;
        /// 围绕Y轴转向指定方向，正数表示逆时针转动，负数表示顺时针转动
        virtual void        setYawToDirection( const Vec3& dir ) = 0;
        /// 围绕Y轴转向指定方向，正数表示逆时针转动，负数表示顺时针转动
        virtual void        setYawToDirection( const Vec3& startPos, const Vec3& endPos ) = 0;
        /// 围绕Y轴转向指定位置
        virtual void        setYawToPosition( const Vec3& pos ) = 0;
        /// 设置是否立即
        virtual void        setIsImmediately( Bool isImmediately ) = 0;
    };

	/******************************************************************************/
	//ISceneNodePitchToAction
	/******************************************************************************/
	class ISceneNodePitchToAction : public LinedStateObject
	{
	public:
		ISceneNodePitchToAction(Str name)
			:LinedStateObject( name )
		{
		}

		/// 设置X轴转向速度
		virtual void        setPitchSpeed( Flt speed ) = 0;
		/// 围绕X轴转向指定位置
		virtual void        setDestAngle( Flt angle ) = 0;
		/// 设是否立即
		virtual void        setIsImmediately( Bool isImmediately ) = 0;
	};

	/******************************************************************************/
	//ISceneNodeLookAtToAction
	/******************************************************************************/
	class ISceneNodeDirectToAction : public LinedStateObject
	{
	public:
		ISceneNodeDirectToAction(Str name)
			:LinedStateObject( name )
		{
		}
		/// 是否结束
		virtual Bool		isFinished() = 0;

		/// 设置转动速度
		virtual void		setShiftSpeed( Flt speed ) = 0;

		/// 获取转动速度
		virtual Flt			getShiftSpeed() = 0;

		/// 设置转动目标
		virtual void		setDestDirection( Vec3 dir ) = 0;

		/// 获取目标方向
		virtual Vec3		getDestDirection() = 0;

		/// 是否立刻生效
		virtual void		setImmediately(bool immediately) = 0;

	};

    /******************************************************************************/
    // ISceneNodePathFindingMoveInAdvanceAction
    // 寻路路径计算
    /******************************************************************************/

    class ISceneNodePathFindingMoveInAdvanceAction
    {
    public:
        /// 设置目标点,
        virtual Bool                setMoveToDestination( Vec3& dest, Bool isAdjuest ) = 0;

        // 计算静态寻路数据
        virtual PathFindingResult   calculateStaticPathFinding() = 0;

        // 计算动态寻路数据
        virtual PathFindingResult   calculateDynamicPathFindingBetweenStaticNode() = 0; 

        // 得到现在的动态目标点
        virtual Vec3                getCurrDynamicDestination() = 0;

		// 得到现在的静态目标点
		virtual Vec3		        getCurrStaticDestination() = 0;

        // 去下一个动态目标点
        virtual Vec3                goNextDynamicDestination() = 0;
		// 是否已经是最后个动态目标点
		virtual Bool		        isLastDynamicDestination() = 0;

		// 去下一个静态目标点
		virtual Vec3		        goNextStaticDestination() = 0;
		// 是否已经是最后个静态目标点
		virtual Bool		        isLastStaticDestination() = 0;


		// 设置现在的静态目标点
		virtual void		        setCurrStaticDestination( Vec3 pos ) = 0;

		// 设置最终的静态目标点
		virtual void		        setFinalStaticDestination( Vec3 pos ) = 0;
    };

	/******************************************************************************/
	// ISceneNodeParabolaMoveToAction
	/******************************************************************************/
	class ISceneNodeParabolaMoveToAction : public LinedStateObject
	{
	public:

		ISceneNodeParabolaMoveToAction(Str name)
			:LinedStateObject( name )
		{
		}
		/// 设置移动速度
		virtual void                setMoveSpeed( Flt speed ) = 0;
		/// 移动到指定位置
		virtual void                setMoveToDestination( const Vec3& dest ) = 0;
	};
    
    


}

/******************************************************************************/
#endif
