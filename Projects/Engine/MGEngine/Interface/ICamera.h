/******************************************************************************/
#ifndef _ICAMERA_H_
#define _ICAMERA_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "ISceneNode.h"
#include "ISceneObject.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//��Ϸ��������Ʒ���
	/******************************************************************************/
	enum CameraOpCtrlTypes
	{
		COC_NULL = 0, 
		COC_SLG = 1, 
		COC_EDITOR = 2
	};

    /******************************************************************************/
	//��Ϸ������ӿ�
	/******************************************************************************/
	class ICamera : public ISceneNode, public ISceneObject
	{
	public:

        // ���������ת��Ϊ��Ļ�����
        virtual void	        worldPointToScreenPoint(const Vec3& worldPos, Vec2& screenPos) = 0;

        /// �õ�����������������λ��
        virtual Flt             getWorldDistance(const Vec3& worldPos) = 0;

		/// �õ�����ת��Ϊ��������ֵ
		virtual void            getMouseViewportRay(Vec3& pos, Vec3& dir, Vec2 offset=Vec2(0,0)) = 0;

        /// �õ��ڵ����
        virtual ISceneNode*     getSceneNode(){return this;};

        /// ��עĳһ��
        virtual void            focusPosition(Vec3& pos) = 0;

        /// ����Fov
        virtual void            setFov(Flt degree) = 0;
        virtual Flt             getFov() = 0;

		/// ���ý�ƽ���Զƽ��
		virtual	void			setNearClipDistance(Flt nearDist) = 0;
		virtual void			setFarClipDistance(Flt farDist) = 0;
	};

}

/******************************************************************************/
#endif
