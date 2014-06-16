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
    //�ݵ㽨����ʾ����ֻ�ڷֿ��ͼ�л����
    /******************************************************************************/
    class CNoCharacterSceneEntity : public CSceneEntity
    {
    public:

        CNoCharacterSceneEntity(IEntity* entity, GAMEOBJ_TYPE type,GAMEOBJ_QUERY_TYPE queryType, NoCharacterEntityData* dynamicData);
        virtual ~CNoCharacterSceneEntity();

    public:

        NoCharacterEntityData*				getDynamicData();

    public:
        // ��ʼ��
        virtual void				        initialize();
        // ����ʼ��
        virtual void				        unInitialize();

		//---------------------------------------------------------------------------------------
		virtual void						setPos(Vec3 pos);
		virtual void						setDir(Vec3 dir);

		virtual Vec3						getPos(Bool isIgnoreHeight = true);
		virtual Vec3						getDir();
    };
}

#endif