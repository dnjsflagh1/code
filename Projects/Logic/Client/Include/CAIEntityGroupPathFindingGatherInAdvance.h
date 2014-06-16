/******************************************************************************/
#ifndef _CAIENTITYGROUPPATHFINDINGGATHERINADVANCE_H_
#define _CAIENTITYGROUPPATHFINDINGGATHERINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "CAIGroup.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // ʵ����Ѱ·�ۼ�AI
    /******************************************************************************/
    class CAIEntityGroupPathFindingGatherInAdvance : public CAIEntityGroup
    {
    public:
        CAIEntityGroupPathFindingGatherInAdvance();
        virtual ~CAIEntityGroupPathFindingGatherInAdvance();
        
        //״̬����
        static Str STATE_NAME;
    
        ///�����¼�
        virtual void        update( Flt delta );
        ///�Ƿ������
        virtual Bool        isFinished();
        ///��ȥ״̬�¼�
        virtual void        onEnter();
        ///�뿪״̬�¼�
        virtual void        onLeave();

    protected:


    };
}

#endif