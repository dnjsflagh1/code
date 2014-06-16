/******************************************************************************/
#ifndef _ISCENEOBJECTCONTROLLER_H_
#define _ISCENEOBJECTCONTROLLER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneObject.h"
#include <stack>

/******************************************************************************/

namespace MG
{

	struct ObjectState 
	{
		U32		objectDeclID;
		Str		name;
		SceneObjectTypes type;
		Vec3	pos;
		Qua		qua;
		Vec3	scale;
	};

	struct OperationRecord
	{
		U32				type;
		ObjectState		state;
	};

	/******************************************************************************/
	//游戏场景对象控制器接口
	/******************************************************************************/
	class ISceneObjectController 
	{
	public:
		
        enum ControlType
        {
            SOC_NULL = 0,
            SOC_SLG,
			SOC_POSITION ,
            SOC_ROTATION ,
            SOC_SCALE ,
        };

		/// 设置是否控制 
		virtual void            setEnable(Bool enable) = 0;
		/// 是否已经控制 
		virtual Bool            getlEnable() = 0;
		
		/// 是否开启选中操作
		virtual void			setFocusEnable(Bool focusEnable) = 0;
		/// 是否关闭选中操作
		virtual Bool			getFocusEnable() = 0;

		/// 设置控制对象 
		virtual void            setFocus( ISceneObject* obj ) = 0;
		/// 得到控制对象 
		virtual ISceneObject*   getFocus() = 0;
		/// 忽略选中对像
		virtual void			setIgnoreFocus( ISceneObject* object ) = 0;

		/// 清除框选对象组
		virtual void			clearMultiFocus( Bool objectDeleted = false ) = 0;
		/// 获取框选对象组
		virtual void			getMultiFocusList( std::vector<ISceneObject*>& objectList ) = 0;
		/// 进行框选操作
		virtual void			multiSelect( RectF rectF ) = 0;
		/// 加入选择
		virtual void			addToMultiSelect ( ISceneObject* object ) = 0;
		/// 进行反选
		virtual void			unSelect( ISceneObject* object ) = 0;

		/// 是否进行了框选移动操作
		virtual Bool			getObjectOperationDirty() = 0;

        /// 得到控制变化状态 
        virtual Bool            getChangedDirty() = 0;

        /// 设置控制方式
        virtual void            setControlType( ControlType type ) = 0;

        /// 贴住地面
        virtual void            stickTerrain() = 0;

		/// 判断是否锁定高度( 锁定高度)
		virtual bool			isTerrainSticked() = 0;

		virtual void			setTerrainSticked(bool terrainSticked ) = 0;
	public:
		std::deque<OperationRecord> mUndoOperations;
		std::deque<OperationRecord> mRedoOperations;
	};

}

/******************************************************************************/
#endif
