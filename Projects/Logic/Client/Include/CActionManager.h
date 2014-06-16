/******************************************************************************/
#ifndef _CACTIONMANAGER_H_
#define _CACTIONMANAGER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "ObjectPool.h"

#include "CharacterSceneEntityAction.h"

#include "SceneEntityAction.h"

/******************************************************************************/

namespace MG
{


    /******************************************************************************/
    // 实体组AI管理
    /******************************************************************************/
    class CActionManager : public LinedStateObjectListener
    {
    public:
        CActionManager();
        virtual ~CActionManager();
        SINGLETON_INSTANCE(CActionManager)

        void        revert();

        ///////////////////////////////////////////////////////////////////////////////////

        CCSEntityLineMoveAcion*		    createCCSEntityLineMoveAcion( CSceneEntity* entity, Vec3 startPos, Vec3 endPos, Flt startTime );
        void		                    destroyCCSEntityLineMoveAcion(CCSEntityLineMoveAcion* action);

        CCSEntityRequestInteractAcion*  createCCSEntityRequestInteractAcion(CSceneEntity* requestEntity, CSceneEntity* desEntity);
        void		                    destroyCCSEntityRequestInteractAcion(CCSEntityRequestInteractAcion* action);

        CCSEntityClantSkillAcion*       createCCSEntityClantSkillAcion(CSkillObject* object);
        void		                    destroyCCSEntityClantSkillAcion(CCSEntityClantSkillAcion* action);

        CCSEntityInjectSkillAcion*      createCCSEntityInjectSkillAcion(CSkillObject* object);
        void		                    destroyCCSEntityInjectSkillAcion(CCSEntityInjectSkillAcion* action);

        ///////////////////////////////////////////////////////////////////////////////////

    protected:

        virtual void    onLinedStateLifeTimeOver(LinedStateObject* obj);

    protected:
        
        ObjectPool<CCSEntityLineMoveAcion>          mCCSEntityLineMoveAcionPool;

        ObjectPool<CCSEntityRequestInteractAcion>   mCCSEntityRequestInteractAcionPool;

        ObjectPool<CCSEntityClantSkillAcion>        mCCSEntityClantSkillAcionPool;

        ObjectPool<CCSEntityInjectSkillAcion>       mCCSEntityInjectSkillAcionPool;

    };
}


#endif	