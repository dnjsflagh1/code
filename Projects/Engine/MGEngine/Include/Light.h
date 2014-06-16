/******************************************************************************/
#ifndef _LIGHT_H_
#define _LIGHT_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ILight.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //灯光
    /******************************************************************************/
    class Light : public ILight
    {
        friend class Scene;
    public:
        Light(CChar* lightName, Scene* scene);
        virtual ~Light();

        ///得到类型
        virtual SceneObjectTypes    getType();

        /// 得到空间节点
        virtual ISceneNode*         getSceneNode();

        /// 设置位置坐标. 
        virtual void                setPosition(Vec3& pos);

        /// 设置方向. 
        virtual void                setDirection(Vec3& vec);
        /// 得到方向 
        virtual Vec3                getDirection();

        /// 设置灯光类型
        virtual void                setLightType(ILight::LightTypes type);

        /// 得到灯光类型.
        virtual ILight::LightTypes  getLightType(void);

        /// 设置灯光满反射颜色
        virtual void                setDiffuseColour(const Color& colour);

        /// 得到灯光满反射颜色
        virtual Color               getDiffuseColour(void) const;

        /// 设置灯光镜面反射颜色
        virtual void                setSpecularColour(const Color& colour);

        /// 设置灯光镜面反射颜色
        virtual Color               getSpecularColour(void) const;

        /// 设置聚光灯属性
        virtual void                setAttenuation(Flt range, Flt constant, Flt linear, Flt quadratic);

    protected:
        ///摄像机节点对象
        MGSceneNode* mSceneNode;
        /// Ogre灯光对象
        Ogre::Light* mOgreLight;
        /// 所属场景对象
        Scene* mScene;
    };

}

/******************************************************************************/

#endif
