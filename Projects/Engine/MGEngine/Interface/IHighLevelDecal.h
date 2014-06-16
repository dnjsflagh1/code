/******************************************************************************/
#ifndef _IHIGHLEVELDECAL_H_
#define _IHIGHLEVELDECAL_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //地形贴花接口
    /******************************************************************************/
    class IHighLevelDecal
    {
    public:

        /// 设置位置
        virtual void                    setPosition(Vec3& pos) = 0;
        /// 得到位置
        virtual Vec3&                   getPosition() = 0;
        
        /// 设置大小
        virtual void                    setSize(Flt size) = 0;
        /// 得到大小
        virtual Flt                     getSize() = 0;
        
		/// 设置法线
		virtual void					setNormal(Vec3& normal) = 0;
		/// 得到法线
		virtual Vec3&					getNormal() = 0;

        /// 设置可见度
        virtual void                    setVisible(Bool visible) = 0;
    };
    
    /******************************************************************************/
    //地形贴花集
    /******************************************************************************/
    class IHighLevelDecalSet
    {
    public:

        /// 得到贴花接口
        virtual IHighLevelDecal*        getDecal(UInt index) = 0;
        /// 得到贴花数量
        virtual UInt                    getDecalNum() = 0;

		virtual void					update( Flt delta ) = 0;
    };



}

/******************************************************************************/
#endif
