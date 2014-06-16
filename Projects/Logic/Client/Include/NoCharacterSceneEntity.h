/******************************************************************************/
#ifndef _CNOCHARACTERSCENEENTITY_H_
#define _CNOCHARACTERSCENEENTITY_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "CSceneEntity.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //据点建筑显示对象，只在分块地图中会出现
    /******************************************************************************/
    class CNoCharacterSceneEntity : public CSceneEntity
    {
    public:

        CNoCharacterSceneEntity(IEntity* entity, GAMEOBJ_TYPE type,GAMEOBJ_QUERY_TYPE queryType, NoCharacterEntityData* dynamicData);
        virtual ~CNoCharacterSceneEntity();

    public:

        NoCharacterEntityData*				getDynamicData();

    public:
        // 初始化
        virtual void				        initialize();
        // 反初始化
        virtual void				        unInitialize();

		//---------------------------------------------------------------------------------------
		virtual void						setPos(Vec3 pos);
		virtual void						setDir(Vec3 dir);

		virtual Vec3						getPos(Bool isIgnoreHeight = true);
		virtual Vec3						getDir();
    };
}

#endif