/******************************************************************************/
#ifndef _IMODELOBJECT_H_
#define _IMODELOBJECT_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "IShadow.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //模型效果类型
    /******************************************************************************/
    enum ModelEffectType
    {
        MET_NULL    = 0, 
    };

    /******************************************************************************/
    //模型对象
    /******************************************************************************/
    class IModelObject 
    {
    public:

        ////////////////////////////////////////////////////////////////////////////////////////////

        /// 获取资源ID
        virtual U32						getModelDeclarationID() = 0;
        ///	碰撞盒的size 
        virtual Vec3					getBoundingBoxSize() = 0;
        /// 寻路半径
        virtual Flt						getPatherRadius() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////

        // 设置阴影投射类型
        virtual void                    setShadowCastType(ShadowCasterType type) = 0;
        // 得到阴影投射类型
        virtual ShadowCasterType        getShadowCastType() = 0;

        // 设置是否接受动态阴影
        virtual void                    setDynamicShadowReceiveEnable(Bool enable) = 0;
        // 得到是否接受动态阴影
        virtual Bool                    getDynamicShadowReceiveEnable() = 0;

        // 设置是否接受静态阴影
        virtual void                    setStaticShadowReceiveEnable(Bool enable) = 0;
        // 得到是否接受静态阴影
        virtual Bool                    getStaticShadowReceiveEnable() = 0;


        ////////////////////////////////////////////////////////////////////////////////////////////

        // 设置是否能被反射
        virtual void                    setReflectEnable(Bool enable) = 0;
        // 得到是否能被反射
        virtual Bool                    getReflectEnable() = 0;

        // 设置是否能被折射
        virtual void                    setRefractEnable(Bool enable) = 0;
        // 得到是否能被折射
        virtual Bool                    getRefractEnable() = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////

        /// 得到骨骼的相对位置
        virtual Vec3                    getBonePosition(CChar* boneName) = 0;
        /// 得到骨骼的世界位置
        virtual Vec3                    getBoneWorldPosition(CChar* boneName) = 0;
		/// 得到骨骼的相对角位移
		virtual Qua                     getBoneOrientation(CChar* boneName) = 0;
		/// 得到骨骼的世界角位移
		virtual Qua                     getBoneWorldOrientation(CChar* boneName) = 0;

		////////////////////////////////////////////////////////////////////////////////////////////

		/// 通过一个值获取人物中心位置
		virtual Vec3					getCenterPosition(Flt center = 0.0f, Bool isLocal = true) = 0;

        ////////////////////////////////////////////////////////////////////////////////////////////

        /// 得到高度
        virtual Flt                     getHeight() = 0;
        /// 得到宽度
        virtual Flt                     getWidth() = 0;


        ////////////////////////////////////////////////////////////////////////////////////////////

        /// 设置高亮
        virtual void                    setHightLight(Flt shine, Bool useDirty=true) = 0;
        /// 设置自发光
        virtual void                    setEmissive(Color color, Bool toAccessory = false) = 0;
		/// 获得自发光颜色
		virtual Color					getEmissive() = 0;

    };

}

/******************************************************************************/
#endif
