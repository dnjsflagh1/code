/******************************************************************************/
#ifndef _IDECAL_H_
#define _IDECAL_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	// 贴花类型
	/******************************************************************************/
	enum IDecalType
	{
		DT_SIMPLE,
		DT_HIGHLEVEL,
	};
	

	/******************************************************************************/
	//贴花接口
	/******************************************************************************/
	class IDecal
	{
	public:

		/// 得到类型
		virtual IDecalType				getType() = 0; 

		/// 设置位置
		virtual void                    setPosition(Vec3& pos) = 0;
		/// 得到位置
		virtual Vec3&                   getPosition() = 0;
		/// 设置法线
		virtual void					setNormal(Vec3& normal) = 0;
		/// 得到法线
		virtual Vec3&					getNormal() = 0;

		/// 设置可见度
		virtual void                    setVisible(Bool visible) = 0;
	};

	/******************************************************************************/
	//地形贴花集
	/******************************************************************************/
	class IDecalSet
	{
	public:

		/// 得到贴花接口
		virtual IDecal*					getDecal(UInt index) = 0;
		/// 得到贴花数量
		virtual UInt                    getDecalNum() = 0;
		/// 设置大小
		virtual void					setSize(int size) = 0;
		/// 获取大小
		virtual int						getSize() = 0;
		/// 更新贴花
		virtual void					update(Flt delta) = 0;

		virtual void					preRendering() = 0;

		virtual void					postRendering() = 0;
	};



}

/******************************************************************************/
#endif
