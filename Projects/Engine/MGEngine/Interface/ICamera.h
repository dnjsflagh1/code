/******************************************************************************/
#ifndef _ICAMERA_H_
#define _ICAMERA_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneNode.h"
#include "ISceneObject.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//游戏摄像机控制方法
	/******************************************************************************/
	enum CameraOpCtrlTypes
	{
		COC_NULL = 0, 
		COC_SLG = 1, 
		COC_EDITOR = 2
	};

    /******************************************************************************/
	//游戏摄像机接口
	/******************************************************************************/
	class ICamera : public ISceneNode, public ISceneObject
	{
	public:

        // 世界坐标点转换为屏幕坐标点
        virtual void	        worldPointToScreenPoint(const Vec3& worldPos, Vec2& screenPos) = 0;

        /// 得到世界坐标点离摄像机位置
        virtual Flt             getWorldDistance(const Vec3& worldPos) = 0;

		/// 得到鼠标点转换为世界射线值
		virtual void            getMouseViewportRay(Vec3& pos, Vec3& dir, Vec2 offset=Vec2(0,0)) = 0;

        /// 得到节点对象
        virtual ISceneNode*     getSceneNode(){return this;};

        /// 关注某一点
        virtual void            focusPosition(Vec3& pos) = 0;

        /// 设置Fov
        virtual void            setFov(Flt degree) = 0;
        virtual Flt             getFov() = 0;

		/// 设置近平面和远平面
		virtual	void			setNearClipDistance(Flt nearDist) = 0;
		virtual void			setFarClipDistance(Flt farDist) = 0;
	};

}

/******************************************************************************/
#endif
