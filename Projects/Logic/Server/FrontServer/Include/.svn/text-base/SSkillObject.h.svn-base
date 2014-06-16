/******************************************************************************/
#ifndef _SSKILLOBJECT_H_
#define _SSKILLOBJECT_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SkillObject.h"

/******************************************************************************/
namespace MG
{


	class SSkillObject: public SkillObject
	{
    public:
        SSkillObject( SCharacter* owner );
        virtual ~SSkillObject();

		virtual void								update( Flt delta );

    protected:
		//skill吟唱开始
		virtual void								onSkillStartClant();
		//skill吟唱Update
		virtual void								onSkillUpdateClant( Flt delta );
		//skill吟唱结束
		virtual void								onSkillEndClant();
		//skill吟唱完成
		virtual void                  				onSkillClantFinished();
		//skill发射开始
		virtual void								onSkillStartInject();
		//skill发射Update
		virtual void								onSkillUpdateInject( Flt delta );
		//skill发射结束
		virtual void								onSkillEndInject();
		//skill发射完成
		virtual void                  				onSkillInjectFinished();

	private:
		Flt											mLastTime;
	};
}

#endif