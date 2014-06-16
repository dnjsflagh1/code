/******************************************************************************/
#ifndef _TERRAINTREEOPERATIONMANAGER_H_
#define _TERRAINTREEOPERATIONMANAGER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITerrainTreeOperationManager.h"

/******************************************************************************/
namespace MG
{


    class TerrainTreeOperationManager : public ITerrainTreeOperationManager
    {
	public:
		enum TreeType
		{
			TREE,
			GRASS
		};
    public:
        SINGLETON_INSTANCE(TerrainTreeOperationManager)
        TerrainTreeOperationManager();
        virtual ~TerrainTreeOperationManager();

        ///创建一个操作
        IEditorOperation*    createOneOperation(){ return NULL; };

    public:

        //设置操作物件ID
        U32		getOpModel();

        //得到操作物件ID
        void	setOpModel(U32 modelID);

		//设置Tree类型
		void	setTreeType(U32 tType);

		//获取Tree类型
		U32		getTreeType();

    protected:

        //操作的物件ID
        U32		mOpModelID;
		//树类型
		U32		mTreeType;
    };


    /******************************************************************************/
    //游戏TREE增加实体接口
    /******************************************************************************/
    class TerrainAddTreeOperationManager : public ITerrainAddTreeOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainAddTreeOperationManager)
        TerrainAddTreeOperationManager();
        virtual ~TerrainAddTreeOperationManager();

        ///创建一个操作
        virtual IEditorOperation*   createOneOperation();

    public:

        //得到密度
        Flt		getDensity();

        //设置密度
        void	setDensity(Flt density);

        //设置聚合
        Flt		getClumping();

        //得到聚合
        void	setClumping(Flt clumping);

        //设置高度
        Flt		getScale();

        //得到高度
        void	setScale(Flt scale);

        //设置高度变化率
        Flt		getScaleVariable();

        //得到高度变化率
        void	setScaleVariable(Flt variable);

		//获取是否对齐网格
		bool	getAlign();

		//设置是否对齐网格
		void	setAlign(bool align);

		//获取草间距
		Flt		getGrassDistance();

		//设置草间距
		void	setGrassDistance(Flt dis);

		//获取树间距
		Flt		getTreeDistance();

		//设置树间距
		void	setTreeDistance(Flt dis);

		//获取最小縮放倍数
		Flt		getMinScale();

		//设置最小縮放倍数
		void	setMinScale(Flt scale);

		//获取最大縮放倍数
		Flt		getMaxScale();

		//设置最大縮放倍数
		void	setMaxScale(Flt scale);

		//获取位置偏移百分比
		Flt		getPositionOffset();

		//设置位置偏移百分比
		void	setPositionOffset(Flt offset);

		//获取分布方式
		U32		getDistribute();

		//设置分布方式
		void	setDistribute(U32 disType);

    protected:

        //密度
        Flt		mDensity;
        //聚合
        Flt		mClumping;
        //获取高度变化
        Flt		mScale;
        //高度变化率
        Flt		mScaleVariable;
		//是否对齐网格
		Flt		mAlign;
		//位置偏移百分比
		Flt mPositionOffset;
		//草间离
		Flt		mGrassDistance;
		//树间距
		Flt		mTreeDistance;
		//最小缩放倍数
		Flt		mMinScale;
		//最大缩放倍数
		Flt		mMaxScale;
		//分布方式
		U32		mDistributeType;
    };


    /******************************************************************************/
    //游戏TREE移除实体接口
    /******************************************************************************/
    class TerrainRemoveTreeOperationManager : public ITerrainRemoveTreeOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainRemoveTreeOperationManager)
        TerrainRemoveTreeOperationManager();
        virtual ~TerrainRemoveTreeOperationManager();

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation( );
    };

    /******************************************************************************/
    //游戏TREE刷实体接口
    /******************************************************************************/
    class TerrainDefineTreeOperationManager: public ITerrainDefineTreeOperationManager
    {
    public:
        SINGLETON_INSTANCE(TerrainDefineTreeOperationManager)
        TerrainDefineTreeOperationManager();
        virtual ~TerrainDefineTreeOperationManager();

        ///创建一个操作
        virtual IEditorOperation*       createOneOperation( );

    public:

        virtual void	setMode( U32 mode ) { mDefineMode = mode; }

        virtual U32		getMode() { return mDefineMode; };

        virtual void	setGroupName( const Str& group ) { mDefineGroup = group; }

        virtual Str		getGroupName() { return mDefineGroup; };

        virtual void	lock(bool islock) { mLocked = islock; };

        virtual bool	isLocked() { return mLocked; }

    protected:

        //定义批次的方式
        U32				mDefineMode;

        //定义批次的组名
        Str				mDefineGroup;

        //锁定批次组名
        bool			mLocked;
    };
}

/******************************************************************************/

#endif

