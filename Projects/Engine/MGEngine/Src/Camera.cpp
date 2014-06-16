/******************************************************************************/
#include "stdafx.h"
#include "Camera.h"
#include "EngineMain.h"
#include "MGSceneNode.h"
#include "Scene.h"
#include "InputManager.h"
#include "SceneNodeAction.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    Camera::Camera(CChar* camName, Scene* scene)
        :mScene(scene)
        ,mPositionDirty(false)
        ,mScaleDirty(false)
        ,mOrientationDirty(false)
    {
        DYNAMIC_ASSERT(mScene!=NULL);

        mName = camName;

        //创建摄像机对象
        mOgreCamera = mScene->mOgreSceneManager->createCamera(camName);
        mOgreCamera->setNearClipDistance(2);
        mOgreCamera->setFarClipDistance(2000);

        //mOgreCamera->setProjectionType( Ogre::PT_ORTHOGRAPHIC );

        //创建摄像机节点
        mSceneNode = MG_NEW MGSceneNode(mScene->mOgreSceneManager->getRootSceneNode(),mScene);

        //绑定摄像机
		mSceneNode->getOgreSceneNode()->attachObject( mOgreCamera );

		mSceneNode->getOgreSceneNode()->setFixedYawAxis(true, Vector3::UNIT_Y);
		mOgreCamera->setFixedYawAxis(true, Vector3::UNIT_Y);

		mPositionOffset = Vec3(0,0,0);
		mInitScale = Vec3(1,1,1);
    }
    
    //-----------------------------------------------------------------------
    Camera::~Camera()
    {
        //销毁摄像机对象
        mScene->mOgreSceneManager->destroyCamera(mOgreCamera);
        mOgreCamera = NULL;

        //销毁摄像机节点
        MG_SAFE_DELETE( mSceneNode );
    }
    //-----------------------------------------------------------------------
    void Camera::update( Flt delta )
    {

        mPositionDirty = false;
        mScaleDirty = false;
        mOrientationDirty = false;

		mLinedStateManager.update(delta);
    }
    //-----------------------------------------------------------------------
    SceneObjectTypes Camera::getType()
    {
        return SOT_CAMERA;
    }
    //-----------------------------------------------------------------------
    void Camera::setFov(Flt degree)
    {
        Ogre::Radian rad = Ogre::Degree(degree);
        getOgreCamera()->setFOVy(rad);
    }
    //-----------------------------------------------------------------------
    Flt Camera::getFov()
    {
        return getOgreCamera()->getFOVy().valueDegrees();
    }
	//-----------------------------------------------------------------------
	void Camera::setFarClipDistance(Flt farDist)
	{
		getOgreCamera()->setFarClipDistance( farDist );
	}
	//-----------------------------------------------------------------------
	void Camera::setNearClipDistance(Flt nearDist)
	{
		getOgreCamera()->setNearClipDistance( nearDist );
	}
    //-----------------------------------------------------------------------
    void Camera::worldPointToScreenPoint(const Vec3& worldPos, Vec2& screenPos)
    {
        Ogre::Vector3 pos = Vector3(worldPos.x,worldPos.y,worldPos.z);
        Matrix4  viewProjMatrix = mOgreCamera->getProjectionMatrix() * mOgreCamera->getViewMatrix();
        pos = viewProjMatrix * pos;
        
        screenPos.x = (pos.x + 1) / 2.0f;
        screenPos.y = (1-pos.y) / 2.0f;
    }
    //-----------------------------------------------------------------------
    Flt Camera::getWorldDistance(const Vec3& worldPos) 
    {
        Ogre::Vector3 pos = Vector3(worldPos.x,worldPos.y,worldPos.z);
        Ogre::Vector3 dir = mOgreCamera->getPosition() - pos;
        return dir.length();
    }
	//-----------------------------------------------------------------------
	void Camera::getMouseViewportRay(Vec3& pos, Vec3& dir, Vec2 offset)
	{
		Vec2 mousePos = InputManager::getSingleton().getMousePos();
        mousePos = mousePos + offset;

		Int screenWidth = OgreMainInterface::renderWindow->getWidth();
		Int screenHeight = OgreMainInterface::renderWindow->getHeight();
		Flt screenx = mousePos.x / Flt( screenWidth );
		Flt screeny = mousePos.y / Flt( screenHeight );
		Ogre::Ray ray;
		mOgreCamera->getCameraToViewportRay( screenx, screeny, &ray );	
		
		pos = Vec3(ray.getOrigin().x,ray.getOrigin().y,ray.getOrigin().z);
		dir = Vec3(ray.getDirection().x,ray.getDirection().y,ray.getDirection().z);
	}
	//-----------------------------------------------------------------------
	void Camera::setVisible(Bool visible)
	{

	}
    //-----------------------------------------------------------------------
    Bool Camera::getVisible()
    {
        return true;
    }
    //-----------------------------------------------------------------------
    void Camera::focusPosition(Vec3& pos)
    {
        Vector3 focusPos    = Vector3(pos.x,pos.y,pos.z);
        Vector3 camDir      = mOgreCamera->getDirection();
        Vector3 camPos      = mOgreCamera->getPosition();

        Flt yDis            = abs(camPos.y-focusPos.y);

        Radian radian       = camDir.angleBetween(-Vector3::UNIT_Y);
        Real   cos          = Math::Cos( radian );

        if (abs(cos) >= 0.001)
        {
            Flt dis = yDis / cos ; 
            Vector3 movePos = focusPos - camDir.normalisedCopy() * dis;
            movePos.y = camPos.y;
            mOgreCamera->setPosition( movePos );
        }
    }
	//-----------------------------------------------------------------------
	void Camera::setPosition(Vec3& pos)
	{
		mOgreCamera->setPosition(pos.x,pos.y,pos.z);
        mPositionDirty = true;
	}
	//-----------------------------------------------------------------------
	void Camera::getPosition(Vec3& pos)
	{
        Vector3 ogreVec3 = mOgreCamera->getPosition();
        pos.x = ogreVec3.x;
        pos.y = ogreVec3.y;
        pos.z = ogreVec3.z;
	}
	//-----------------------------------------------------------------------
	void Camera::setScale(Vec3& scale)
	{
		
	}
	//-----------------------------------------------------------------------
	void Camera::getScale(Vec3& scale)
	{

	}
	//-----------------------------------------------------------------------
	void Camera::setOrientation(Qua& quaternion)
	{
        Quaternion ogreQua(quaternion.w, quaternion.x, quaternion.y, quaternion.z);
        mOgreCamera->setOrientation(ogreQua);
        mOrientationDirty = true;
	}
	//-----------------------------------------------------------------------
	void Camera::getOrientation(Qua& quaternion)
	{
        Quaternion ogreQua = mOgreCamera->getOrientation();
        quaternion.w = ogreQua.w;
        quaternion.x = ogreQua.x;
        quaternion.y = ogreQua.y;
        quaternion.z = ogreQua.z;
	}
	//-----------------------------------------------------------------------
	void Camera::setDirection(Vec3& vec, TransformSpace relativeTo )
	{
		mOgreCamera->setDirection(Vector3(vec.x,vec.y,vec.z));
        mOrientationDirty = true;
	}
	//-----------------------------------------------------------------------
	void Camera::getDirection(Vec3& vec)
	{
        Vector3 ogreVec3 = mOgreCamera->getDirection();
        vec.x = ogreVec3.x;
        vec.y = ogreVec3.y;
        vec.z = ogreVec3.z;
	}
	//-----------------------------------------------------------------------
	void Camera::lookAt(Vec3& targetPoint, TransformSpace relativeTo )
	{
        mOgreCamera->lookAt(targetPoint.x,targetPoint.y,targetPoint.z);
        mOrientationDirty = true;
	}
	//-----------------------------------------------------------------------
	void Camera::translate(Vec3& d, TransformSpace relativeTo )
	{
		if (relativeTo == Node::TS_LOCAL)
		{
			mOgreCamera->moveRelative(Vector3(d.x,d.y,d.z));
		}else
		{
			mOgreCamera->move(Vector3(d.x,d.y,d.z));
		}
        mPositionDirty = true;
	}
	//-----------------------------------------------------------------------
	void Camera::roll( Flt angle, TransformSpace relativeTo )
	{
		mOgreCamera->roll(Ogre::Radian(angle));
        mOrientationDirty = true;
	}
	//-----------------------------------------------------------------------
	void Camera::pitch( Flt angle, TransformSpace relativeTo )
	{
		mOgreCamera->pitch(Ogre::Radian(angle));
        mOrientationDirty = true;
	}
	//-----------------------------------------------------------------------
	void Camera::yaw( Flt angle, TransformSpace relativeTo )
	{
		mOgreCamera->yaw(Ogre::Radian(angle));
        mOrientationDirty = true;
	}
    //-----------------------------------------------------------------------
    Flt Camera::getPitch()
    {
        return mOgreCamera->getOrientation().getPitch().valueRadians();
    }
    //-----------------------------------------------------------------------
    Flt Camera::getYaw()
    {
        return mOgreCamera->getOrientation().getYaw().valueRadians();
    }
	//-----------------------------------------------------------------------
	void Camera::rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo )
	{

	}
    
}

