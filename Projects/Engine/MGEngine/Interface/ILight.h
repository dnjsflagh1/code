/******************************************************************************/
#ifndef _ILIGHT_H_
#define _ILIGHT_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneObject.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //游戏灯光接口
    /******************************************************************************/
    class ILight : public ISceneObject
    {
    public:
        /******************************************************************************/
        //游戏灯光类型
        /******************************************************************************/
        enum LightTypes
        {
            /// Point light sources give off light equally in all directions, so require only position not direction
            LT_POINT = 0,
            /// Directional lights simulate parallel light beams from a distant source, hence have direction but no position
            LT_DIRECTIONAL = 1,
            /// Spotlights simulate a cone of light from a source so require position and direction, plus extra values for falloff
            LT_SPOTLIGHT = 2
        };
        
    public:

        /// 得到空间节点
        virtual ISceneNode*         getSceneNode() = 0;
        
        /// 设置位置坐标. 
        virtual void                setPosition(Vec3& pos) = 0;

        /// 设置方向. 
        virtual void                setDirection(Vec3& vec) = 0;
        /// 得到方向. 
        virtual Vec3                getDirection() = 0;

        /// 设置灯光类型
        virtual void                setLightType(ILight::LightTypes type) = 0;

        /// 得到灯光类型.
        virtual ILight::LightTypes  getLightType(void) = 0;

        /// 设置灯光满反射颜色
        virtual void                setDiffuseColour(const Color& colour) = 0;

        /// 得到灯光满反射颜色
        virtual Color               getDiffuseColour(void) const = 0;

        /// 设置灯光镜面反射颜色
        virtual void                setSpecularColour(const Color& colour) = 0;

        /// 设置灯光镜面反射颜色
        virtual Color               getSpecularColour(void) const = 0;

        /// 设置聚光灯属性
        virtual void                setAttenuation(Flt range, Flt constant, Flt linear, Flt quadratic) = 0;
    };

}

/******************************************************************************/
#endif
