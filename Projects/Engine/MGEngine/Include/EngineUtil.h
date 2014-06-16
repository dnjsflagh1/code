/******************************************************************************/
#ifndef _ENGINEUTIL_H_
#define _ENGINEUTIL_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "IEngineUtil.h"

/******************************************************************************/

namespace MG
{
	class EngineUtil: public IEngineUtil
	{
	public:

		SINGLETON_INSTANCE(EngineUtil);

	public:


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//��ͼ�����ӿ�
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//��ͼ��Դ�Ƿ����
		Bool			isTextureExist(const Str& name, const Str& group );

		//���һ����ͼ�Ŀ�͸�
		const VecI2&	getTextureSize(const Str& name, const Str& group, Bool cache = true);

		//�Ӵ��̶�ȡ��ͼ
		Bool			load2DTexture(const Str& name, const Str& path, const Str& group);

		//ж����ͼ
		void			unload2DTexture(const Str& name, const Str& group);

		//����һ���ֶ���ͼ
		Bool			create2DTexture(const Str& name, const Str& group, U32 width, U32 height);

		//����һ����ͼ������һ��������
		Bool			drawTextureToSurface(const Str& srcName, const Str& srcGroup, VecI2 srcLeftTop, VecI2 srcSize, 
					const Str& destName, const Str& destGroup, VecI2 destLeftTop, VecI2 destSize);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//ģ�Ͳ��ʲ����ӿ�
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//���ò�����ͼ����
		void			setTextureAnimation(IEntity* entity, Vec2 uv_start, Vec2 uv_speed );

		//���ò����Ƿ���ȼ��
		void			setDepthCheck(IEntity* entity, bool enabled);

		//���ò��ʵĻ�����
		void			setMaterialAmbient(IEntity* entity, MG::Color color);

		//���ò��ʵĻԶ�
		void			setMaterialShiness(IEntity* entity, Flt shiness);

	};
}

/******************************************************************************/
#endif