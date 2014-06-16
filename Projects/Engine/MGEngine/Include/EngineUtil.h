/******************************************************************************/
#ifndef _ENGINEUTIL_H_
#define _ENGINEUTIL_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IEngineUtil.h"

/******************************************************************************/

namespace MG
{
	class EngineUtil: public IEngineUtil
	{
	public:

		SINGLETON_INSTANCE(EngineUtil);

	public:


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//贴图操作接口
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//贴图资源是否存在
		Bool			isTextureExist(const Str& name, const Str& group );

		//获得一张贴图的宽和高
		const VecI2&	getTextureSize(const Str& name, const Str& group, Bool cache = true);

		//从磁盘读取贴图
		Bool			load2DTexture(const Str& name, const Str& path, const Str& group);

		//卸载贴图
		void			unload2DTexture(const Str& name, const Str& group);

		//创建一个手动贴图
		Bool			create2DTexture(const Str& name, const Str& group, U32 width, U32 height);

		//拷贝一张贴图到另外一个表面上
		Bool			drawTextureToSurface(const Str& srcName, const Str& srcGroup, VecI2 srcLeftTop, VecI2 srcSize, 
					const Str& destName, const Str& destGroup, VecI2 destLeftTop, VecI2 destSize);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//模型材质操作接口
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//设置材质贴图动画
		void			setTextureAnimation(IEntity* entity, Vec2 uv_start, Vec2 uv_speed );

		//设置材质是否深度检测
		void			setDepthCheck(IEntity* entity, bool enabled);

		//设置材质的环境光
		void			setMaterialAmbient(IEntity* entity, MG::Color color);

		//设置材质的辉度
		void			setMaterialShiness(IEntity* entity, Flt shiness);

	};
}

/******************************************************************************/
#endif