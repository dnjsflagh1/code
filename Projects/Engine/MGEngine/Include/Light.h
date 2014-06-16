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
    //�ƹ�
    /******************************************************************************/
    class Light : public ILight
    {
        friend class Scene;
    public:
        Light(CChar* lightName, Scene* scene);
        virtual ~Light();

        ///�õ�����
        virtual SceneObjectTypes    getType();

        /// �õ��ռ�ڵ�
        virtual ISceneNode*         getSceneNode();

        /// ����λ������. 
        virtual void                setPosition(Vec3& pos);

        /// ���÷���. 
        virtual void                setDirection(Vec3& vec);
        /// �õ����� 
        virtual Vec3                getDirection();

        /// ���õƹ�����
        virtual void                setLightType(ILight::LightTypes type);

        /// �õ��ƹ�����.
        virtual ILight::LightTypes  getLightType(void);

        /// ���õƹ���������ɫ
        virtual void                setDiffuseColour(const Color& colour);

        /// �õ��ƹ���������ɫ
        virtual Color               getDiffuseColour(void) const;

        /// ���õƹ⾵�淴����ɫ
        virtual void                setSpecularColour(const Color& colour);

        /// ���õƹ⾵�淴����ɫ
        virtual Color               getSpecularColour(void) const;

        /// ���þ۹������
        virtual void                setAttenuation(Flt range, Flt constant, Flt linear, Flt quadratic);

    protected:
        ///������ڵ����
        MGSceneNode* mSceneNode;
        /// Ogre�ƹ����
        Ogre::Light* mOgreLight;
        /// ������������
        Scene* mScene;
    };

}

/******************************************************************************/

#endif
