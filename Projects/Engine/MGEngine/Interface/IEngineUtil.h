/******************************************************************************/
#ifndef _IENGINEUTIL_H_
#define _IENGINEUTIL_H_
/******************************************************************************/
#include "MGEngineInterfacePreqs.h"
/******************************************************************************/

namespace MG
{
	class IEngineUtil
	{
	public:

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//贴图操作接口
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//贴图是否存在
		virtual Bool			isTextureExist(const Str& name, const Str& group) = 0;

		//获得一张贴图的宽和高
		virtual const VecI2&	getTextureSize(const Str& name, const Str& group, Bool cache = true) = 0;

		//创建一个手动贴图
		virtual Bool			load2DTexture(const Str& name, const Str& path, const Str& group) = 0;

		//卸载贴图
		virtual void			unload2DTexture(const Str& name, const Str& group) = 0;

		//创建一个手动贴图
		virtual Bool			create2DTexture(const Str& name, const Str& group, U32 width, U32 height) = 0;

		//拷贝一张贴图到另外一个表面上
		virtual Bool			drawTextureToSurface(const Str& srcName, const Str& srcGroup, VecI2 srcLeftTop, VecI2 srcSize, 
						const Str& destName, const Str& destGroup, VecI2 destLeftTop, VecI2 destSize) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//模型材质操作接口
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//设置材质贴图动画
		virtual void			setTextureAnimation(IEntity* entity, Vec2 uv_start, Vec2 uv_speed ) = 0;

		//设置材质是否深度检测
		virtual void			setDepthCheck(IEntity* entity, bool enabled) = 0;

		//设置材质的环境光
		virtual void			setMaterialAmbient(IEntity* entity, MG::Color color) = 0;

		//设置材质的辉度
		virtual void			setMaterialShiness(IEntity* entity, Flt shiness) = 0;
	};
}

/******************************************************************************/
#endif