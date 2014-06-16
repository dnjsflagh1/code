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
	//��Ϸ��������������ӿ�
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

		/// �����Ƿ���� 
		virtual void            setEnable(Bool enable) = 0;
		/// �Ƿ��Ѿ����� 
		virtual Bool            getlEnable() = 0;
		
		/// �Ƿ���ѡ�в���
		virtual void			setFocusEnable(Bool focusEnable) = 0;
		/// �Ƿ�ر�ѡ�в���
		virtual Bool			getFocusEnable() = 0;

		/// ���ÿ��ƶ��� 
		virtual void            setFocus( ISceneObject* obj ) = 0;
		/// �õ����ƶ��� 
		virtual ISceneObject*   getFocus() = 0;
		/// ����ѡ�ж���
		virtual void			setIgnoreFocus( ISceneObject* object ) = 0;

		/// �����ѡ������
		virtual void			clearMultiFocus( Bool objectDeleted = false ) = 0;
		/// ��ȡ��ѡ������
		virtual void			getMultiFocusList( std::vector<ISceneObject*>& objectList ) = 0;
		/// ���п�ѡ����
		virtual void			multiSelect( RectF rectF ) = 0;
		/// ����ѡ��
		virtual void			addToMultiSelect ( ISceneObject* object ) = 0;
		/// ���з�ѡ
		virtual void			unSelect( ISceneObject* object ) = 0;

		/// �Ƿ�����˿�ѡ�ƶ�����
		virtual Bool			getObjectOperationDirty() = 0;

        /// �õ����Ʊ仯״̬ 
        virtual Bool            getChangedDirty() = 0;

        /// ���ÿ��Ʒ�ʽ
        virtual void            setControlType( ControlType type ) = 0;

        /// ��ס����
        virtual void            stickTerrain() = 0;

		/// �ж��Ƿ������߶�( �����߶�)
		virtual bool			isTerrainSticked() = 0;

		virtual void			setTerrainSticked(bool terrainSticked ) = 0;
	public:
		std::deque<OperationRecord> mUndoOperations;
		std::deque<OperationRecord> mRedoOperations;
	};

}

/******************************************************************************/
#endif
