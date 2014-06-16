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
    //��Ϸ�ƹ�ӿ�
    /******************************************************************************/
    class ILight : public ISceneObject
    {
    public:
        /******************************************************************************/
        //��Ϸ�ƹ�����
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

        /// �õ��ռ�ڵ�
        virtual ISceneNode*         getSceneNode() = 0;
        
        /// ����λ������. 
        virtual void                setPosition(Vec3& pos) = 0;

        /// ���÷���. 
        virtual void                setDirection(Vec3& vec) = 0;
        /// �õ�����. 
        virtual Vec3                getDirection() = 0;

        /// ���õƹ�����
        virtual void                setLightType(ILight::LightTypes type) = 0;

        /// �õ��ƹ�����.
        virtual ILight::LightTypes  getLightType(void) = 0;

        /// ���õƹ���������ɫ
        virtual void                setDiffuseColour(const Color& colour) = 0;

        /// �õ��ƹ���������ɫ
        virtual Color               getDiffuseColour(void) const = 0;

        /// ���õƹ⾵�淴����ɫ
        virtual void                setSpecularColour(const Color& colour) = 0;

        /// ���õƹ⾵�淴����ɫ
        virtual Color               getSpecularColour(void) const = 0;

        /// ���þ۹������
        virtual void                setAttenuation(Flt range, Flt constant, Flt linear, Flt quadratic) = 0;
    };

}

/******************************************************************************/
#endif
