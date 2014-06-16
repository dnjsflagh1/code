/******************************************************************************/
#ifndef _ITERRAINTREEOPERATIONMANAGER_H_
#define _ITERRAINTREEOPERATIONMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "IEditorOperation.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //游戏植被操作接口
    /******************************************************************************/
    class ITerrainTreeOperationManager : public IEditorOperationManager
    {
    public:

        //设置操作物件ID
        virtual U32		getOpModel() = NULL;

        //得到操作物件ID
        virtual void	setOpModel(U32 modelID) = NULL;

		//设置Tree类型
		virtual void	setTreeType(U32 tType) = NULL;

		//获取Tree类型
		virtual U32		getTreeType() = NULL;

    };

    /******************************************************************************/
    //游戏植被增加接口
    /******************************************************************************/
    class ITerrainAddTreeOperationManager : public IEditorOperationManager
    {
    public:

        //得到密度
        virtual Flt		getDensity() = NULL;

        //设置密度
        virtual void	setDensity(Flt density) = NULL;

        //设置概率
        virtual Flt		getClumping() = NULL;

        //得到概率
        virtual void	setClumping(Flt clumping) = NULL;

        //设置高度变化率
        virtual void	setScaleVariable(Flt variable) = NULL;

        //得到高度变化率
        virtual Flt		getScaleVariable() = NULL;

        //设置高度
        virtual Flt		getScale() = NULL;

        //得到高度
        virtual void	setScale(Flt scale) = NULL;

		//获取草间距
		virtual Flt		getGrassDistance() = NULL;

		//设置草间距
		virtual void	setGrassDistance(Flt dis) = NULL;

		//获取树间距
		virtual Flt		getTreeDistance() = NULL;

		//设置树间距
		virtual void	setTreeDistance(Flt dis) = NULL;

		//获取最小縮放倍数
		virtual Flt		getMinScale() = NULL;

		//设置最小縮放倍数
		virtual void	setMinScale(Flt scale) = NULL;

		//获取最大縮放倍数
		virtual Flt		getMaxScale() = NULL;

		//设置最大縮放倍数
		virtual void	setMaxScale(Flt scale) = NULL;

		//获取是否对齐网格
		virtual bool	getAlign() = NULL;

		//设置是否对齐网格
		virtual void	setAlign(bool align) = NULL;

		//获取位置偏移百分比
		virtual Flt		getPositionOffset() = NULL;

		//设置位置偏移百分比
		virtual void	setPositionOffset(Flt offset) = NULL;

		//获取分布方式
		virtual U32		getDistribute() = NULL;

		//设置分布方式
		virtual void	setDistribute(U32 disType) = NULL;
		
    };

    /******************************************************************************/
    //游戏植被移除接口
    /******************************************************************************/
    class ITerrainRemoveTreeOperationManager: public IEditorOperationManager
    {
    public:

    };
    /******************************************************************************/
    //植被批次刷接口
    /******************************************************************************/
    class ITerrainDefineTreeOperationManager: public IEditorOperationManager
    {
    public:

        enum
        {
            /*@
            一次操作，如果操作范围中有物件， 
            选择这些物件中最大的批次组作为所有选中物件的批次组。
            如果这个范围内没有物件，自己创建一个批次。
            @*/
            DEFINE_BATCH_MODE_COMMON,

            /*@
            根据选中物件所在的区域确定物件所在的批次组。
            @*/
            DEFINE_BATCH_MODE_REGION,

            /*@
            讲所有选中的物体设置为所指定的批次组。
            @*/
            DEFINE_BATCH_MODE_SPECIALIZE,
        };

    public:

        //设置批次指定模式
        virtual void	setMode( U32 mode ) = NULL;

        //设置批次指定模式
        virtual U32		getMode() = NULL;

        //设置批次组名
        virtual void	setGroupName( const Str& group ) = NULL;

        //设置批次组名
        virtual Str		getGroupName() = NULL;

        //设置批次锁定
        virtual void	lock(bool islock) = NULL;

        //设置批次锁定
        virtual bool	isLocked() = NULL;

    };
}

/******************************************************************************/
#endif
