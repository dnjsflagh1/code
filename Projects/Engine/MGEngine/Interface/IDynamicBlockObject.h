/******************************************************************************/
#ifndef _IDYNAMICBLOCKOBJECT_H_
#define _IDYNAMICBLOCKOBJECT_H_
/******************************************************************************/
#include "MGEngineInterfacePreqs.h"
/******************************************************************************/

namespace MG
{

    class IDynamicBlockObject
    {
    public:

        // 得到场景对象
        virtual ISceneObject*               getSceneObject() = 0;

        // 设置有效性
        virtual void						setEnable(Bool enable) = 0;
        // 是否有效性
        virtual Bool						getEnable() = 0;

        // 是否显示障碍
		virtual void						setShowBlock(Bool enable) = 0;

        // 设置是否影响静态障碍
        virtual void						setStaticBlockEnable(Bool enable) = 0;

        // 设置是否是建筑障碍
        virtual void						setStructureMode(Bool enable) = 0;

        // 得到静态碰撞的网格大小
        virtual Int							getStaticBlockGridDiameter() = 0;
        // 设置对象半径长度
		virtual void						setObjectRadius( Flt objectRadius ) = 0;

        // 得到对象的半径
		virtual Flt							getObjectRadius() = 0;

        // 刷新新的障碍点
		virtual void			       		refreshBlock( Vec3 oldPos, Vec3 newPos ) = 0;

        // 得到所占的动态障碍索引列表
        virtual void                        getCurrLocationDynamicBlockIndexList( std::map<UInt, UInt>& list ) = 0;

        // 判断是否属于所占的动态障碍索引
        virtual Bool                        isBelongCurrLocationDynamicBlockIndex( UInt index ) = 0;

        // 判断是否属于所占的静态障碍索引
        virtual Bool                        isBelongCurrLocationStaticBlockIndex( UInt index ) = 0;

  //      // 设置遇到碰撞障碍的索引
		//virtual void						setCollideBlockIndex( UInt index ) = 0;
  //      // 得到遇到碰撞障碍的索引
  //      virtual UInt						getCollideBlockIndex() = 0;

		virtual IDynamicBlockObject*		getCollideBlockObject() = 0;

		virtual void						setCollideBlockObject( IDynamicBlockObject* collideBlockObject ) = 0;

		virtual RectF						getBlockRect() = 0;
    };
}

/******************************************************************************/
#endif