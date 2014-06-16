/******************************************************************************/
#ifndef _MGGRIDS_H_
#define _MGGRIDS_H_
/******************************************************************************/

#include "EnginePreqs.h"


/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //��Ϸդ�����
    /*
        Grid Data �ķֲ����� �� ��������ϵ�Ĺ�ϵ

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
        
        /// ���ĵ�����������ϵ�е�λ��
        Vec2    mCenterPos;
        /// ���½�����������ϵ�е�λ��
        Vec2    mLeftBottomPos;

        /// �����С,����դ��һ��
        Real    mWorldSize;
        /// ����һ���С, ����դ��һ��
        Real    mWorldHalfSize;

        /// դ���С
        Flt     mGridSize;
        /// դ��һ���С
        Flt     mGridHalfSize;

        /// դ��һ�ߵ�����
        UInt    mGridsSideNum;
        /// դ��������
        UInt    mGridsNum;
        /// դ������
        TYPE0*  mGridData;	
        
    private:

        /// �Ƿ񴴽���դ��
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

        /// ����դ��
        virtual void        createGrids(Int gridsSideNum, Flt gridSize,  Vec2 centerPos);
        /// ����դ��
        virtual void        destroyGrids();
        /// �Ƿ���դ��
                Bool        isHasGrids(){ return mIsGridCreated; };

        /// �õ�դ�����ݼ�
        virtual TYPE0*&     getGrids(){return mGridData;};

    public:

        /// �õ����ĵ�λ��
        Vec2                getCenterPos(){return mCenterPos;};

        /// �õ����½�λ��
        Vec2                getLeftBottomPos(){return mLeftBottomPos;};

        /// �õ������С
        Flt                 getWorldSize(){return mWorldSize;};

        /// �õ�����һ���С
        Flt                 getWorldHalfSize(){return mWorldHalfSize;};

        /// �õ�դ���С
        Flt                 getGridSize(){return mGridSize;};

        /// �õ�դ��һ�ߵ����� 
        Int                 getGridSideNum(){return mGridsSideNum;};

        /// �õ�դ�����
        TYPE0*              getGridData(){return mGridData;};

        //////////////////////////////////////////////////////////////////////////////////

        /// �õ�դ�����,ͨ������
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

        /// �õ�դ�����,ͨ��������������
        inline TYPE0*       getGridByWorldPosition( Flt x, Flt y )
        {
            Vec2 worldPos = Vec2(x,y);
            Vec2 gridPoint;
            convertWorldPositionToGridPoint(worldPos,gridPoint);

            return  getGridDataByIndex( gridPoint.x, gridPoint.y );
        }

        /////////////////////////////////////////////////////////////////////////////////////////

        /// ת���������굽��������
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

        /// ת���������굽��������
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
