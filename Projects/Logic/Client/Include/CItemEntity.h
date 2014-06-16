/******************************************************************************/
#ifndef _CITEMENTITY_H_
#define _CITEMENTITY_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "NoCharacterSceneEntity.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//Item
	/******************************************************************************/
	class CItemEntity : public CNoCharacterSceneEntity
	{
	public:
		CItemEntity( IEntity* entity );
		virtual ~CItemEntity();

	public:

		//×××××××××××××××××××××××××××××××××××××××××××××××××
		//  [主要方法]
		//×××××××××××××××××××××××××××××××××××××××××××××××××

		// 初始化
		virtual void				        initialize();
		// 反初始化
		virtual void				        unInitialize();

		//×××××××××××××××××××××××××××××××××××××××××××××××××
		//  [基础属性]
		//×××××××××××××××××××××××××××××××××××××××××××××××××

		// 得到数据
		ItemEntityData*						getDynamicData();

		void								parabolaDrop( Vec3 dropStartPos );

	};
}

#endif