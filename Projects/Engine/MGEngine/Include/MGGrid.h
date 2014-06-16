/******************************************************************************/
#ifndef _MGGRIDS_H_
#define _MGGRIDS_H_
/******************************************************************************/

#include "EnginePreqs.h"


/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //游戏栅格管理
    /*
        Grid Data 的分布方向 和 世界坐标系的关系

        1
        |
        |       -Z
        |       | 
        |  -X---0---X
        |       |  
        |       Z       
        0----------------1
    */
    /******************************************************************************/
    template <typename TYPE0> class GridManager 
    {
    private:
        
        /// 中心点在世界坐标系中的位置
        Vec2    mCenterPos;
        /// 左下角在世界坐标系中的位置
        Vec2    mLeftBottomPos;

        /// 世界大小,沿着栅格一边
        Real    mWorldSize;
        /// 世界一半大小, 沿着栅格一边
        Real    mWorldHalfSize;

        /// 栅格大小
        Flt     mGridSize;
        /// 栅格一半大小
        Flt     mGridHalfSize;

        /// 栅格一边的数量
        UInt    mGridsSideNum;
        /// 栅格总数量
        UInt    mGridsNum;
        /// 栅格数据
        TYPE0*  mGridData;	
        
    private:

        /// 是否创建了栅格
        Bool    mIsGridCreated;

    public:

        GridManager()
            :mCenterPos(Vec2(0,0))
            ,mLeftBottomPos(Vec2(0,0))
            ,mWorldSize(0)
            ,mWorldHalfSize(0)
            ,mGridsSideNum(0)
            ,mGridSize(0)
            ,mIsGridCreated(false)
            ,mGridsNum(0)
            ,mGridData(NULL){};
        virtual ~GridManager(){};

        /// 创建栅格
        virtual void        createGrids(Int gridsSideNum, Flt gridSize,  Vec2 centerPos);
        /// 销毁栅格
        virtual void        destroyGrids();
        /// 是否有栅格
                Bool        isHasGrids(){ return mIsGridCreated; };

        /// 得到栅格数据集
        virtual TYPE0*&     getGrids(){return mGridData;};

    public:

        /// 得到中心点位置
        Vec2                getCenterPos(){return mCenterPos;};

        /// 得到左下角位置
        Vec2                getLeftBottomPos(){return mLeftBottomPos;};

        /// 得到区域大小
        Flt                 getWorldSize(){return mWorldSize;};

        /// 得到区域一半大小
        Flt                 getWorldHalfSize(){return mWorldHalfSize;};

        /// 得到栅格大小
        Flt                 getGridSize(){return mGridSize;};

        /// 得到栅格一边的数量 
        Int                 getGridSideNum(){return mGridsSideNum;};

        /// 得到栅格对象
        TYPE0*              getGridData(){return mGridData;};

        //////////////////////////////////////////////////////////////////////////////////

        /// 得到栅格对象,通过索引
        inline TYPE0*       getGridDataByIndex( UInt x, UInt y )
        {
            if ( mGridsSideNum == 1 )
            {
                x = 0;
                y = 0;
            }else
            {
                x = Ogre::Math::Clamp(x,UInt(0),(UInt)mGridsSideNum-1);
                y = Ogre::Math::Clamp(y,UInt(0),(UInt)mGridsSideNum-1);
            }

            TYPE0* data = mGridData;
            data += mGridsSideNum * y + x;
         
            return data;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////

        /// 得到栅格对象,通过世界坐标坐标
        inline TYPE0*       getGridByWorldPosition( Flt x, Flt y )
        {
            Vec2 worldPos = Vec2(x,y);
            Vec2 gridPoint;
            convertWorldPositionToGridPoint(worldPos,gridPoint);

            return  getGridDataByIndex( gridPoint.x, gridPoint.y );
        }

        /////////////////////////////////////////////////////////////////////////////////////////

        /// 转换世界坐标到地形坐标
        inline void      convertWorldPositionToGridPoint( Vec2 worldPos, Vec2& gridPoint )
        {
            worldPos = worldPos - mLeftBottomPos;

            gridPoint.x = UInt( ( worldPos.x ) / mGridSize); 
            gridPoint.y = UInt( ( -worldPos.y ) / mGridSize);
            
            if ( mGridsSideNum == 1 )
            {
                gridPoint.x = 0;
                gridPoint.y = 0;
            }else
            {
                gridPoint.x = Ogre::Math::Clamp(gridPoint.x,Flt(0),(Flt)mGridsSideNum-1);
                gridPoint.y = Ogre::Math::Clamp(gridPoint.y,Flt(0),(Flt)mGridsSideNum-1);
            }
        }

        /////////////////////////////////////////////////////////////////////////////////////////

        /// 转换地形坐标到世界坐标
        inline void      convertGridPointToWorldPosition( Vec2 gridPoint, Vec2&worldPos  )
        {
            if ( mGridsSideNum == 1 )
            {
                gridPoint.x = 0;
                gridPoint.y = 0;
            }else
            {
                gridPoint.x = Ogre::Math::Clamp(gridPoint.x,Flt(0),(Flt)mGridsSideNum-1);
                gridPoint.y = Ogre::Math::Clamp(gridPoint.y,Flt(0),(Flt)mGridsSideNum-1);
            }


            worldPos.x =   mGridSize * gridPoint.x + mGridHalfSize  + mLeftBottomPos.x;
            worldPos.y = -(mGridSize * gridPoint.y + mGridHalfSize) + mLeftBottomPos.y;
        }
        
    };

    //-----------------------------------------------------------------------
    template<typename TYPE0>
    void GridManager<TYPE0>::createGrids(Int gridsSideNum, Flt gridSize, Vec2 centerPos)
    {   
        destroyGrids();

        mGridsSideNum   = gridsSideNum;
        mGridsNum       = mGridsSideNum * mGridsSideNum;
        mGridSize       = gridSize;
        mGridHalfSize   = mGridSize * Flt(0.5);

        mWorldSize      = mGridsSideNum * gridSize;
        mWorldHalfSize  = mWorldSize * Flt(0.5);

        mCenterPos      = centerPos;
        mLeftBottomPos  = centerPos + Vec2( -mWorldHalfSize, mWorldHalfSize );

        mGridData = (TYPE0*)RamAlloc::getInstance().get(sizeof(TYPE0)*mGridsNum + 1);
        mIsGridCreated = true;
    }
    //-----------------------------------------------------------------------
    template<typename TYPE0>
    void GridManager<TYPE0>::destroyGrids(void)
    {
        if (mIsGridCreated)
        {
            RamAlloc::getInstance().release(mGridData);
            mGridData = NULL;
            mIsGridCreated = false;
        }
    }
}

/******************************************************************************/

#endif
