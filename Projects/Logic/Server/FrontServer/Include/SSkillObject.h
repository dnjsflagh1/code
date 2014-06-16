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
		//skill������ʼ
		virtual void								onSkillStartClant();
		//skill����Update
		virtual void								onSkillUpdateClant( Flt delta );
		//skill��������
		virtual void								onSkillEndClant();
		//skill�������
		virtual void                  				onSkillClantFinished();
		//skill���俪ʼ
		virtual void								onSkillStartInject();
		//skill����Update
		virtual void								onSkillUpdateInject( Flt delta );
		//skill�������
		virtual void								onSkillEndInject();
		//skill�������
		virtual void                  				onSkillInjectFinished();

	private:
		Flt											mLastTime;
	};
}

#endif