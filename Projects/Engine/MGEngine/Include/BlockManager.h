/******************************************************************************/
#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IBlockManager.h"
#include "GridPool.h"
#include "ManualMeshManager.h"
/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//��ײ�����б�
	/******************************************************************************/
	struct CollisionBlockObjectList
	{
		std::vector<DynamicBlockObject*> dynamicBlockObjectList;

		void removeDynamicBlockObject(DynamicBlockObject* dynamicBlockObject)
		{
			for(std::vector<DynamicBlockObject*>::iterator it = dynamicBlockObjectList.begin(); it != dynamicBlockObjectList.end(); ++it)
			{
				if((*it) == dynamicBlockObject)
				{
					dynamicBlockObjectList.erase(it);
					return;
				}
			} 
		}

		void addDynamicBlockObject(DynamicBlockObject* dynamicBlockObject)
		{
			removeDynamicBlockObject(dynamicBlockObject);
			dynamicBlockObjectList.push_back(dynamicBlockObject);
		}
	};

    /******************************************************************************/
    //��ײϵͳ
    /******************************************************************************/
	class BlockManager : public IBlockManager
    {
    public:
        BlockManager( Scene* scene );
        virtual ~BlockManager();

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// ��̬�ϰ������С
        static Real STATIC_BLOCK_GRID_SIZE ;
        /// ��̬�ϰ������С
        static Real DYNAMIC_BLOCK_GRID_SIZE;

        enum BLOCK_FLAG
        {
            BLF_NULL							= 0,		// �޶���,�����Ϊ���ϰ�
            BLF_TERRAIN_BLOCK					= BIT(0),	// ���ξ�̬�ϰ�
            BLF_ENTITY_ALLSIDE_BLOCK			= BIT(1),	// ʵ��ͽ�������������ռ�����ϰ�
			BLF_STRUCTURE_ALLSIDE_BLOCK			= BIT(2),	// 
			BLF_STRUCTURE_INSIDE_BLOCK			= BIT(3),	// �����ڲ��ϰ��������ڽ����ڲ�Ѱ·ʹ�õ��ϰ�
			BLF_STRUCTURE_OUTSIDE_BLOCK			= BIT(4),	// �����ⲿ�ϰ��������ڽ����ⲿѰ·ʹ�õ��ϰ�

			BLF_STRUCTURE_ROAD					= BIT(5),	// �����ڲ���·����������С�������ж��Ƿ����ڽ����ڲ������ⲿ
			BLF_STRUCTURE_PASSAGE				= BIT(6),	// �����뽨����ͨ·��
															// ��������� BLF_STRUCTURE_INSIDE_BLOCK��BLF_STRUCTURE_OUTSIDE_BLOCK
															// ������С�� BLF_ENTITY_STRUCTURE_ALLSIDE_BLOCK
        };

		enum LAYER_FLAG
		{
			LLF_NULL				= 0,		// �޶���
			LLF_STRUCTURE_INSIDE	= BIT(0),	// �ڽ����ڲ�
			LLF_STRUCTURE_OUTSIDE	= BIT(1),	// �ڽ����ⲿ
		};

		/****************************
		//ͨ�÷���
		/****************************/


        /// ���ؾ�̬�ϰ�����
		virtual void            loadStaticBlock( Vec2 leftBottomPos, Vec2 rightUpPos );
        /// ���ض�̬�ϰ�����
		virtual void            loadDynamicBlock( Vec2 leftBottomPos, Vec2 rightUpPos );

        /// ж�������ϰ�����
        virtual void            unLoad();

        /// ����
        void                    update(Flt delta);

		// ���ʵ����ײ
		void                    checkEntityBlock();

		void					clearAllStaticBlock();
		void					clearAllDynamicBlock();
		void					clearMapAllBlock();	

        
        //////////////////////////////////////////////////////////////////////////////////////////////////

		// �õ���̬�����б�
		GridPool<Byte>*			getStaticBlockList();
		// �õ���̬�����б�
		GridPool<Byte>*			getDynamicBlockList();

		// �õ���̬�ϰ���ȣ���λ���һ�ߵ���������
		Int                     getDynamicBlockMapWidth();
		// �õ���̬�ϰ������С
		virtual	Flt				getDynamicBlockGridSize();
        // �õ���̬�ϰ������С
		virtual	Flt				getStaticBlockGridSize();

		/**************************************************************
		//��̬�;�̬�ϰ������������ת������
		/**************************************************************/

		// ���ö�̬�ϰ�ͨ��������
		void                    setDynamicBlockByPoint( Int x, Int z, BLOCK_FLAG flag );
		// ���ö�̬�ϰ�ͨ������
		void                    setDynamicBlockByIndex( UInt index, BLOCK_FLAG flag );
		// ��̬�ϰ�ͨ����������
		void					setDynamicBlockByPos( Vec3 pos, BLOCK_FLAG flag, Int diameterSize = 1 );

		// ��ն�̬�ϰ�ͨ������
		void                    clearDynamicBlock( UInt index, BLOCK_FLAG flag );
		// ��ն�̬�ϰ�ͨ����������
		void                    clearDynamicBlock( Vec3 pos, BLOCK_FLAG flag, Int diameterSize = 1 );

		// �õ���̬�ϰ�����ͨ����������
		UInt					getDynamicBlockIndexByWorldPos( Vec3 pos );
		// �õ���̬�ϰ�������ͨ����������
		void					getDynamicBlockPointByWorldPos( Vec3 pos, Int& x, Int& z );
		// �õ���̬�ϰ�����ͨ��������
		UInt					getDynamicBlockIndexByPoint( Int x, Int z );
		// �õ���̬�����ϰ����ĵ�ͨ������
		Vec3					getDynamicBlockGridCenterPosByIndex( UInt index );

		//////////////////////////////////////////////////////////////////////////////////////////////////

		// ���þ�̬�ϰ�ͨ��������
		void                    setStaticBlockByPoint( Int x, Int z, BLOCK_FLAG flag );
		// ���þ�̬�ϰ�ͨ������
		void                    setStaticBlockByIndex( UInt index, BLOCK_FLAG flag );

		// ��վ�̬�ϰ�ͨ������
		void                    clearStaticBlock( UInt index, BLOCK_FLAG flag );

		// �õ���̬�ϰ���������ͨ����������
		UInt					getStaticBlockIndexByWorldPos( Vec3 pos );
		// �õ���̬������ͨ�����������
		void					getStaticBlockPointByWorldPos( Vec3 pos, Int& x, Int& z );
		// �õ���̬����ͨ��������
		UInt					getStaticBlockIndexByPoint( Int x, Int z );
		// �õ���̬�����ϰ����ĵ�ͨ������
		Vec3					getStaticBlockGridCenterPosByIndex( UInt index );

		/**************************************************************
		//������������
		/**************************************************************/

		// ���ö�̬�;�̬�ϰ�ͨ���������б�
		void					setBlockByTriangle3DList( std::vector<Triangle3D>& worldTriangle3DList, BLOCK_FLAG flag );

		// �õ������������б�ͨ���������б�, ���ݿ����ж��Ƿ�Ϊ��̬��̬�ϰ�����
		void					getBlockGridListByTriangle3DList(  std::map<UInt, VecU2>& gridPointList, std::vector<Triangle3D>&  mWorldTriangle3DList, Bool isStaticBlock );

		// �õ������������б� ͨ�� ��ɨ�� һ�������棬��������
		void					getGridByOneWorldBlockTriangleByRowScan( GridPool<Byte>* mapBlock, Vector3* posList, Vec2 minPoint, Vec2 maxPoint, Int stepSize, std::map<UInt, VecU2>& gridPointList );
		// �õ������������б� ͨ�� ��ɨ�� һ�������棬��������
		void					getGridByOneWorldBlockTriangleByColScan( GridPool<Byte>* mapBlock, Vector3* posList, Vec2 minPoint, Vec2 maxPoint, Int stepSize, std::map<UInt, VecU2>& gridPointList );

		Bool					getLineTriangleIntersectPoint( Vector2 lineP, Vector2 lineD, Vector3* trianglePosList, Vector2* intersectPos );

		/**************************************************************
		//�ж��Ƿ�Ϊ�ϰ���ط���
		/**************************************************************/

        // �Ƿ����ϰ�
        static Bool             isBlockFlag( Byte* flag, LAYER_FLAG layerFlag );
		// �Ƿ��Ƕ�̬�ϰ�
		static Bool             isDynamicBlockFlag( Byte* flag );

        // �Ƿ��о�̬��־λ
        Bool                    hasStaticBlockFlagByIndex( UInt index, Byte flag );

		// �Ƿ�Ϊ��̬�ϰ�ͨ�����������
		virtual Bool			isStaticBlock( Vec3 currPos );
		// �Ƿ�Ϊ��̬�ϰ�ͨ��������
		Bool					isStaticBlock( Int currX, Int currZ );
        // �Ƿ�Ϊ��̬�ϰ�ͨ������
        Bool					isStaticBlockByIndex( UInt index );

        // �Ƿ��ж�̬��־λ
        Bool                    hasDynamicBlockFlagByIndex( UInt index, Byte flag );

        // �Ƿ�Ϊ��̬�ϰ�
        virtual Bool			isDynamicBlockByIndex( UInt index );

		// �Ƿ�Ϊ��̬�ϰ������ݰ뾶
		virtual Bool			isDynamicBlockByRadius( Vec3 currPos, Int findPathObjectCellDiameter, VertexPos vertexPos = VERTEX_MAX, IDynamicBlockObject* ignoreObj = NULL );

        // ��⿪ʼ�㵽������֮���Ƿ����ϰ�
		virtual Bool			isDynamicBlockBetweenTwoPos( IDynamicBlockObject* ignoreObj, Vec3 startPos, Vec3 endPos, UInt& blockIndex, Int findPathObjectCellDiameter = 1, Bool isPrecise = false );

        
		/**************************************************************
		//����������ط���
		/**************************************************************/

        // �õ�����Ŀɽ����, ѡȡ���ĵ���Χ����
        virtual	Bool			getPosNearestAccessiblePos( const Vec3 centerPos, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos, IDynamicBlockObject* ignoreObj );
		// �õ�����Ŀɽ����, ����ѡȡָ������
		virtual	Bool			getPosNearestAccessiblePosForDir( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos );

		virtual	Bool			getPosNearestAccessiblePos( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos );
		// �õ�����Ŀɽ������
		virtual	Bool			getPosNearestAccessibleDis( const Vec3 centerPos, Vec3 dir, Int findPathObjectCellDiameter, Flt& nearestAccessibleDis );

		/*virtual	Bool			getPosNearestAccessiblePosForGridScan( const Vec3 centerPos, Vec3 dir, Flt disLen, Int findPathObjectCellDiameter, Vec3& nearestAccessiblePos );*/

        //////////////////////////////////////////////////////////////////////////////////////////////////
	
		// �õ������ϰ�����
		virtual	Bool			getPassBlockGrid( Vec3 startPos, Vec3 endPos, std::vector<PassGridBlock>& passBlockGridList, UInt diameterSize = 1 );

		virtual	Bool			getPassBlockGrid( Vec3 startPos, Vec3 endPos, std::map<UInt, VecU2>& passBlockGridList );

		//////////////////////////////////////////////////////////////////////////////////////////////////

		// �õ�ָ������Χ���ϰ������б�������ռ�����С
		Bool					getBlockGridListByRect( Vec3 pos, std::map<UInt, UInt>& blockGridList, VecI2& minPoint, VecI2& maxPoint, Int diameterSize = 1, VertexPos vertexPos = VERTEX_MAX );
        // �õ������ӵ��ϰ������б�
        Bool					getNewAddBlockGridListByRect( Vec3 oldPos, Vec3 newPos, std::map<UInt, UInt>& blockGridList, VecI2& minPoint, VecI2& maxPoint, Int diameterSize = 1 );

		Bool					getOldBlockGridListByRect( Vec3 pos, VecI2 minPoint, VecI2 maxPoint, std::map<UInt, UInt>& blockGridList, Int diameterSize = 1, VertexPos vertexPos = VERTEX_MAX );

		//////////////////////////////////////////////////////////////////////////////////////////////////

		VertexPos				getPosNearestVertexPos( Vec3 pos, Vec2& vertexPosPos );
	
		/**************************************************************
		//�ϰ�������ط���
		/**************************************************************/

		// ���������ٶ�̬�ϰ�����
		DynamicBlockObject*     createDynamicBlockObject(Scene* scene, IEntity* sceneObject, Flt objectRadius);
		void                    destroyDynamicBlockObject(DynamicBlockObject* obj);

		// ����һ����̬��������
		void					addDynamicBlockObjectToGridBlock(UInt gridIndex, IDynamicBlockObject* object, Byte flag);
		// �Ƴ�һ��������������
		Bool					removeDynamicBlockObjectFromGridBlock(UInt gridIndex, IDynamicBlockObject* object, Byte flag);

		// �õ��ϰ�����ͨ������
        virtual IDynamicBlockObject*	getDynamicBlockObjectFromGridBlock(UInt gridIndex);
		IDynamicBlockObject*	        getDynamicBlockObjectFromGridBlock(UInt gridIndex, Byte flag);

		//////////////////////////////////////////////////////////////////////////////////////////////////

        // �õ�������ָ��������Ķ�̬������ཻ��
        Bool                    isIntersectionWithDynamicGridByGridIndex( Vec3 startPos, Vec3 endPos, UInt index );
        
        //////////////////////////////////////////////////////////////////////////////////////////////////

        // �õ���̬�ϰ������б�
        typedef std::map<UInt, IDynamicBlockObject*> DynamicBlockObjectList;
        DynamicBlockObjectList& getDynamicBlockObjectList( Byte flag );

		Bool				    isBlockByPointAround(Vec3 pos, UInt findPathObjectCellDiameter);


    private:

        // ��Ϸ����
        Scene*  				mScene;
		GridPool<Byte>			mMapStaticBlock;
		GridPool<Byte>			mMapDynamicBlock;

        std::map<Byte, DynamicBlockObjectList> mDynamicBlockObjectListMap;
    };
}

/******************************************************************************/

#endif
