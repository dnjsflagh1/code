/******************************************************************************/
#include "stdafx.h"
#include "Light.h"
#include "EngineMain.h"
#include "MGSceneNode.h"
#include "Scene.h"
#include "MGEngineUtility.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    Light::Light(CChar* lightName, Scene* scene)
        :mScene(scene)
    {
        DYNAMIC_ASSERT(mScene!=NULL);

        //�����ƹ����
        mOgreLight = mScene->getOgreSceneManager()->createLight(lightName);

        //����Ͷ����Ӱ
        mOgreLight->setCastShadows(true);

        //�����ƹ�ڵ�
        mSceneNode = MG_NEW MGSceneNode(mScene->getOgreSceneManager()->getRootSceneNode(),mScene);

        //�󶨵ƹ��
        mSceneNode->getOgreSceneNode()->attachObject( mOgreLight );
    }
    //-----------------------------------------------------------------------
    Light::~Light()
    {
        //�������������
        mScene->getOgreSceneManager()->destroyLight(mOgreLight);
        mOgreLight = NULL;

        //����������ڵ�
        MG_SAFE_DELETE( mSceneNode );
    }
    //-----------------------------------------------------------------------
    SceneObjectTypes Light::getType()
    {
        return SOT_LIGHT;
    }
    //-----------------------------------------------------------------------
    ISceneNode* Light::getSceneNode()
    {
        return mSceneNode;
    }
    //-----------------------------------------------------------------------
    void Light::setPosition(Vec3& pos)
    {
        if (mOgreLight)
        {
            mOgreLight->setPosition(Vector3(pos.x,pos.y,pos.z));
        }
    }
    //-----------------------------------------------------------------------
    void Light::setDirection(Vec3& vec)
    {
        if (mOgreLight)
        {
            mOgreLight->setDirection(Vector3(vec.x,vec.y,vec.z));
        }
    }
    //-----------------------------------------------------------------------
    Vec3 Light::getDirection()
    {
        Vec3 dir;

        if (mOgreLight)
        {
            dir = MGEngineUtility::toVec3( mOgreLight->getDirection() );
        }
        return dir;
    }
    //-----------------------------------------------------------------------
    void Light::setLightType(ILight::LightTypes type)
    {
        mOgreLight->setType((Ogre::Light::LightTypes)type);
    }
    //-----------------------------------------------------------------------
    ILight::LightTypes Light::getLightType(void)
    {
        return (MG::ILight::LightTypes)mOgreLight->getType();
    }
    //-----------------------------------------------------------------------
    void Light::setDiffuseColour(const Color& colour)
    {
        ColourValue colourValue(colour.r,colour.g,colour.b,colour.a);
        mOgreLight->setDiffuseColour(colourValue);
    }
    //-----------------------------------------------------------------------
    Color Light::getDiffuseColour(void) const
    {
        ColourValue colourValue = mOgreLight->getDiffuseColour();
        Color color;
        color.r = colourValue.r;
        color.g = colourValue.g;
        color.b = colourValue.b;
        color.a = colourValue.a;
        return color;
    }
    //-----------------------------------------------------------------------
    void Light::setSpecularColour(const Color& colour)
    {
        ColourValue colourValue(colour.r,colour.g,colour.b,colour.a);
        mOgreLight->setSpecularColour(colourValue);
    }
    //-----------------------------------------------------------------------
    Color Light::getSpecularColour(void) const
    {
        ColourValue colourValue = mOgreLight->getSpecularColour();
        Color color;
        color.r = colourValue.r;
        color.g = colourValue.g;
        color.b = colourValue.b;
        color.a = colourValue.a;
        return color;
    }
    //-----------------------------------------------------------------------
    void Light::setAttenuation(Flt range, Flt constant, Flt linear, Flt quadratic)
    {
        mOgreLight->setAttenuation(range, constant, linear, quadratic);
    }

}

