/******************************************************************************/
#include "stdafx.h"
#include "CSkillObject.h"
#include "CSkillEffect.h"
#include "CSkillEffectSystem.h"
#include "CPointSkillEffect.h"
#include "CObjectSkillEffect.h"
#include "CInstantSkillEffect.h"
#include "CEmitterSkillEffect.h"
#include "CSprintSkillEffect.h"
#include "CGoUpAndDownSkillEffect.h"

/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------
    CSkillEffectSystem::CSkillEffectSystem()
    {

    }
    //--------------------------------------------------------------------------
    CSkillEffectSystem::~CSkillEffectSystem()
    {
        clear();
    }
    //--------------------------------------------------------------------------
    Bool CSkillEffectSystem::initialize()
    {

        return true;
    }
    //--------------------------------------------------------------------------
    Bool CSkillEffectSystem::uninitialize()
    {

        return true;
    }
    //--------------------------------------------------------------------------
    void CSkillEffectSystem::update( Flt delta )
    {
		//FUNDETECTION(__MG_FUNC__);
        std::list< CSkillEffect* >::iterator iter = mSkillEffectList.begin();
        for ( ; iter != mSkillEffectList.end(); )
        {
            CSkillEffect* effect = *iter;

            if ( effect->getState() == CSkillEffect::SES_END )
            {
                MG_SAFE_DELETE( effect );
                iter = mSkillEffectList.erase( iter );
            }else
            {
                effect->update( delta );
                iter++;
            }
        }
    }
    //--------------------------------------------------------------------------
    void CSkillEffectSystem::clear()
    {
        std::list< CSkillEffect* >::iterator iter = mSkillEffectList.begin();
        for ( ; iter != mSkillEffectList.end(); iter++)
        {
            CSkillEffect* effect = *iter;
            MG_SAFE_DELETE( effect );
        }
        mSkillEffectList.clear();
    }
    //--------------------------------------------------------------------------
     CPointSkillEffect* CSkillEffectSystem::addPointEffect( CSkillObject* skillObject )
    {
        CPointSkillEffect* effect = MG_NEW CPointSkillEffect(skillObject);
        if ( effect )
            mSkillEffectList.push_back( effect );
        return effect;
    }
    //--------------------------------------------------------------------------
	CObjectSkillEffect*	CSkillEffectSystem::addObjectSkillEffect( CSkillObject* skillObject )
	{
		CObjectSkillEffect* effect = MG_NEW CObjectSkillEffect(skillObject);
		if ( effect )
			mSkillEffectList.push_back( effect );
		return effect;
	}
	//--------------------------------------------------------------------------
    CEmitterSkillEffect* CSkillEffectSystem::addEmitterSkillEffect( CSkillObject* skillObject )
    {
        CEmitterSkillEffect* effect = MG_NEW CEmitterSkillEffect(skillObject);
        if ( effect )
            mSkillEffectList.push_back( effect );
        return effect;
    }
	//--------------------------------------------------------------------------
	CInstantSkillEffect* CSkillEffectSystem::addInstantSkillEffect( CSkillObject* skillObject )
	{
		CInstantSkillEffect* effect = MG_NEW CInstantSkillEffect(skillObject);
		if ( effect )
			mSkillEffectList.push_back( effect );
		return effect;
	}
	//--------------------------------------------------------------------------
	CSprintSkillEffect*	CSkillEffectSystem::addSprintSkillEffect( CSkillObject* skillObject )
	{
		CSprintSkillEffect* effect = MG_NEW CSprintSkillEffect(skillObject);
		if ( effect )
			mSkillEffectList.push_back( effect );
		return effect;
	}
	//--------------------------------------------------------------------------
	CGoUpAndDownSkillEffect*	CSkillEffectSystem::addGoUpAndDownSkillEffect( CSkillObject* skillObject )
	{
		CGoUpAndDownSkillEffect* effect = MG_NEW CGoUpAndDownSkillEffect(skillObject);
		if ( effect )
			mSkillEffectList.push_back( effect );
		return effect;
	}
    //--------------------------------------------------------------------------
    void CSkillEffectSystem::onSkillEnded( CSkillObject* skillObject )
    {
        std::list< CSkillEffect* >::iterator iter = mSkillEffectList.begin();
        for ( ; iter != mSkillEffectList.end(); iter++)
        {
            CSkillEffect* effect = *iter;

            if ( effect->isBelongSkill( skillObject ) )
            {
                if ( effect->isEndOnSkillEned() )
                {
                    effect->end();
                }
            }
        }
    }
}