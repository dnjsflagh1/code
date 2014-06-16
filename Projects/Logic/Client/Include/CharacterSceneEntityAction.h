/******************************************************************************/
#ifndef _CHARACTERSCENEENTITYACTION_H_
#define _CHARACTERSCENEENTITYACTION_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"

/******************************************************************************/

namespace MG
{


    

   
    /******************************************************************************/
    //��������������Ϊ
    /******************************************************************************/
    class CCSEntityClantSkillAcion : public LinedStateObject
    {
    public:
        CCSEntityClantSkillAcion(CSkillObject* object);
        virtual ~CCSEntityClantSkillAcion();

    public:

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

    private:

        CSkillObject* mSkillObject;

        // �Ƿ��������Լ�
        Bool mIsBelongSelf;
    };


    

    /******************************************************************************/
    //�����似����Ϊ
    /******************************************************************************/
    class CCSEntityInjectSkillAcion : public LinedStateObject
    {
    public:
        CCSEntityInjectSkillAcion(CSkillObject* object);
        virtual ~CCSEntityInjectSkillAcion();

    public:

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

    private:

        CSkillObject* mSkillObject;
        Bool mIsBelongSelf;
    };


}


/******************************************************************************/

#endif //