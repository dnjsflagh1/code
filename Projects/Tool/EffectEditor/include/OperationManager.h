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
			OT_CREATE_ENTITY,				// ����ģ��
			OT_CREATE_EFFECTENTITY,			// ������Ч

			OT_DESTROY_ENTITY,				// ɾ��ģ��
			OT_DESTROY_EFFECTENTITY,		// ɾ����Ч

			OT_HIDE_ENTITY,					// ����ģ��
			OT_HIDE_EFFECTENTITY,			// ������Ч
			//////////////////////////////////////////////////////////////////////
		};
	public:
		SINGLETON_INSTANCE(OperationManager)
			OperationManager();
		~OperationManager();
		void update( Dbl delta );

	public:
		///��ԭ�����
		void revertCamera();

		void addEntity(U32 id);

		void addEffect(Str8 templatename);

		void addEvent(const Str name, float eventTiming);

		bool loadEffectComponentFile(const Str filename, Str componentName);

		bool newEffectComponentFile();
	protected:
		///�������������
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

