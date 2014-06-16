/******************************************************************************/
#ifndef _OPERATIONMANAGER_H_
#define _OPERATIONMANAGER_H_
/******************************************************************************/



/******************************************************************************/

namespace EffectEditor 
{
	/******************************************************************************/
	class OperationManager
	{
	public:
		enum OperationType
		{
			OT_NULL	 = 0,
			OT_CREATE_ENTITY,				// 创建模型
			OT_CREATE_EFFECTENTITY,			// 创建特效

			OT_DESTROY_ENTITY,				// 删除模型
			OT_DESTROY_EFFECTENTITY,		// 删除特效

			OT_HIDE_ENTITY,					// 隐藏模型
			OT_HIDE_EFFECTENTITY,			// 隐藏特效
			//////////////////////////////////////////////////////////////////////
		};
	public:
		SINGLETON_INSTANCE(OperationManager)
			OperationManager();
		~OperationManager();
		void update( Dbl delta );

	public:
		///还原摄像机
		void revertCamera();

		void addEntity(U32 id);

		void addEffect(Str8 templatename);

		void addEvent(const Str name, float eventTiming);

		bool loadEffectComponentFile(const Str filename, Str componentName);

		bool newEffectComponentFile();
	protected:
		///更新摄像机操作
		void updateCameraOp( Dbl delta );

		//*********************************************************
	private:
		Int             mCurrModelDeclID;
		Int				mCurrEffectDeclID;

		Flt             mCameraSpeed;
	};

}

/******************************************************************************/
#endif

