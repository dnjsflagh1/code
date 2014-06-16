/******************************************************************************/
#ifndef _IBLOCKMANAGER_H_
#define _IBLOCKMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//�����������ϰ�
	/******************************************************************************/
	struct PassGridBlock
	{
		UInt passGridBlockIndex;
		Vec3 passGridBlockPos;
	};


	/******************************************************************************/
	//��ϷAction����
	/******************************************************************************/
	class IBlockManager
	{
	public:

		enum VertexPos
		{
			VERTEX_LEFTUP,
			VERTEX_RIGHTUP,
			VERTEX_RIGHTDOWN,
			VERTEX_LEFTDOWN,
			VERTEX_MAX,
		};

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// ���ؾ�̬�ϰ�
        virtual void					loadStaticBlock( Vec2 leftBottomPos, Vec2 rightUpPos ) = 0;
        /// ���ض�̬�ϰ�
        virtual void					loadDynamicBlock( Vec2 leftBottomPos, Vec2 rightUpPos ) = 0;
        /// �ͷ������ϰ�����
        virtual void					unLoad() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// �õ���̬�ϰ������С
		virtual	Flt						getDynamicBlockGridSize() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/// �Ƿ�Ϊ��̬�ϰ�
		virtual Bool					isStaticBlock( Vec3 currPos ) = 0;

		// �Ƿ�Ϊ��̬�ϰ������ݰ뾶
		virtual Bool					isDynamicBlockByRadius( Vec3 currPos, Int findPathObjectCellDiameter, VertexPos vertexPos = VERTEX_MAX, IDynamicBlockObject* ignoreObj = NULL ) = 0;
		
        // ��⿪ʼ�㵽������֮���Ƿ����ϰ�
        virtual Bool					isDynamicBlockBetweenTwoPos( IDynamicBlockObject* ignoreObj, Vec3 startPos, Vec3 endPos, UInt& blockIndex, Int findPathObjectCellDiameter = 1, Bool isPrecise = false  ) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

		virtual	Bool					getPosNearestAccessiblePosForDir( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos ) = 0;

        // �õ�����Ŀɽ����
        virtual	Bool			        getPosNearestAccessiblePos( const Vec3 centerPos, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos, IDynamicBlockObject* ignoreObj ) = 0;
		// �õ�����Ŀɽ����
		virtual Bool					getPosNearestAccessiblePos( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos ) = 0;
		// �õ�����Ŀɽ������
		virtual Bool					getPosNearestAccessibleDis( const Vec3 centerPos, Vec3 dir, Int findPathObjectCellDiameter, Flt& nearestAccessibleDis ) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// �õ������ϰ�����
		virtual Bool					getPassBlockGrid( Vec3 startPos, Vec3 endPos, std::vector<PassGridBlock>& passBlockGridList, UInt diameterSize = 1 ) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		// �õ���̬�ϰ����󣬸�����ָ������������
		virtual IDynamicBlockObject*	getDynamicBlockObjectFromGridBlock(UInt gridIndex) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

}

/******************************************************************************/
#endif