/******************************************************************************/
#include "stdafx.h"
#include "CActionManager.h"
/******************************************************************************/
namespace MG
{

    //--------------------------------------------------------------------------
    CActionManager::CActionManager()
    {

    }

    //--------------------------------------------------------------------------

    CActionManager::~CActionManager()
    {

    }

    //--------------------------------------------------------------------------
    void CActionManager::revert()
    {

    }

    //--------------------------------------------------------------------------
    CCSEntityLineMoveAcion* CActionManager::createCCSEntityLineMoveAcion( CSceneEntity* entity, Vec3 startPos, Vec3 endPos, Flt startTime )
    {
        CCSEntityLineMoveAcion* action = MG_POOL_NEW(mCCSEntityLineMoveAcionPool, CCSEntityLineMoveAcion, (entity,startPos,endPos,startTime));

        action->setManagedLifeTime( false );
        action->addListener( this );

        return action;
    }

    //--------------------------------------------------------------------------
    void CActionManager::destroyCCSEntityLineMoveAcion(CCSEntityLineMoveAcion* action)
    {
        MG_POOL_DELETE(mCCSEntityLineMoveAcionPool, action);
    }

    //--------------------------------------------------------------------------
    CCSEntityRequestInteractAcion* CActionManager::createCCSEntityRequestInteractAcion( CSceneEntity* requestEntity, CSceneEntity* desEntity )
    {
        CCSEntityRequestInteractAcion* action = MG_POOL_NEW(mCCSEntityRequestInteractAcionPool, CCSEntityRequestInteractAcion, (requestEntity,desEntity));

        action->setManagedLifeTime( false );
        action->addListener( this );

        return action;
    }

    //--------------------------------------------------------------------------
    void CActionManager::destroyCCSEntityRequestInteractAcion(CCSEntityRequestInteractAcion* action)
    {
        MG_POOL_DELETE(mCCSEntityRequestInteractAcionPool, action);
    }

    //--------------------------------------------------------------------------
    CCSEntityClantSkillAcion* CActionManager::createCCSEntityClantSkillAcion(CSkillObject* object)
    {
        CCSEntityClantSkillAcion* action = MG_POOL_NEW(mCCSEntityClantSkillAcionPool, CCSEntityClantSkillAcion, (object));

        action->setManagedLifeTime( false );
        action->addListener( this );

        return action;
    }

    //--------------------------------------------------------------------------
    void CActionManager::destroyCCSEntityClantSkillAcion(CCSEntityClantSkillAcion* action)
    {
        MG_POOL_DELETE(mCCSEntityClantSkillAcionPool, action);
    }

    //--------------------------------------------------------------------------
    CCSEntityInjectSkillAcion* CActionManager::createCCSEntityInjectSkillAcion(CSkillObject* object)
    {
        CCSEntityInjectSkillAcion* action = MG_POOL_NEW(mCCSEntityInjectSkillAcionPool, CCSEntityInjectSkillAcion, (object));

        action->setManagedLifeTime( false );
        action->addListener( this );

        return action;
    }

    //--------------------------------------------------------------------------
    void CActionManager::destroyCCSEntityInjectSkillAcion(CCSEntityInjectSkillAcion* action)
    {
        MG_POOL_DELETE(mCCSEntityInjectSkillAcionPool, action);
    }

    //--------------------------------------------------------------------------
    void CActionManager::onLinedStateLifeTimeOver(LinedStateObject* obj)
    {
        if ( obj->getName() == CCSEntityLineMoveAcion::STATE_NAME )
        {
            destroyCCSEntityLineMoveAcion((CCSEntityLineMoveAcion*)obj);
        }else
        if ( obj->getName() == CCSEntityRequestInteractAcion::STATE_NAME )
        {
            destroyCCSEntityRequestInteractAcion((CCSEntityRequestInteractAcion*)obj);
        }else
        if ( obj->getName() == CCSEntityClantSkillAcion::STATE_NAME )
        {
            destroyCCSEntityClantSkillAcion((CCSEntityClantSkillAcion*)obj);
        }else
        if ( obj->getName() == CCSEntityInjectSkillAcion::STATE_NAME )
        {
            destroyCCSEntityInjectSkillAcion((CCSEntityInjectSkillAcion*)obj);
        }
    }

}