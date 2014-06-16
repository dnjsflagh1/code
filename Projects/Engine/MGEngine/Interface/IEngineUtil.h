/******************************************************************************/
#ifndef _IENGINEUTIL_H_
#define _IENGINEUTIL_H_
/******************************************************************************/
#include "MGEngineInterfacePreqs.h"
/******************************************************************************/

namespace MG
{
	class IEngineUtil
	{
	public:

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//��ͼ�����ӿ�
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//��ͼ�Ƿ����
		virtual Bool			isTextureExist(const Str& name, const Str& group) = 0;

		//���һ����ͼ�Ŀ�͸�
		virtual const VecI2&	getTextureSize(const Str& name, const Str& group, Bool cache = true) = 0;

		//����һ���ֶ���ͼ
		virtual Bool			load2DTexture(const Str& name, const Str& path, const Str& group) = 0;

		//ж����ͼ
		virtual void			unload2DTexture(const Str& name, const Str& group) = 0;

		//����һ���ֶ���ͼ
		virtual Bool			create2DTexture(const Str& name, const Str& group, U32 width, U32 height) = 0;

		//����һ����ͼ������һ��������
		virtual Bool			drawTextureToSurface(const Str& srcName, const Str& srcGroup, VecI2 srcLeftTop, VecI2 srcSize, 
						const Str& destName, const Str& destGroup, VecI2 destLeftTop, VecI2 destSize) = 0;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//ģ�Ͳ��ʲ����ӿ�
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//���ò�����ͼ����
		virtual void			setTextureAnimation(IEntity* entity, Vec2 uv_start, Vec2 uv_speed ) = 0;

		//���ò����Ƿ���ȼ��
		virtual void			setDepthCheck(IEntity* entity, bool enabled) = 0;

		//���ò��ʵĻ�����
		virtual void			setMaterialAmbient(IEntity* entity, MG::Color color) = 0;

		//���ò��ʵĻԶ�
		virtual void			setMaterialShiness(IEntity* entity, Flt shiness) = 0;
	};
}

/******************************************************************************/
#endif