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
    //对象吟唱技能行为
    /******************************************************************************/
    class CCSEntityClantSkillAcion : public LinedStateObject
    {
    public:
        CCSEntityClantSkillAcion(CSkillObject* object);
        virtual ~CCSEntityClantSkillAcion();

    public:

        //状态名字
        static Str STATE_NAME;

        ///更新事件
        virtual void        update( Flt delta );
        ///是否结束了
        virtual Bool        isFinished();
        ///进去状态事件
        virtual void        onEnter();
        ///离开状态事件
        virtual void        onLeave();

    private:

        CSkillObject* mSkillObject;

        // 是否属与我自己
        Bool mIsBelongSelf;
    };


    

    /******************************************************************************/
    //对象发射技能行为
    /******************************************************************************/
    class CCSEntityInjectSkillAcion : public LinedStateObject
    {
    public:
        CCSEntityInjectSkillAcion(CSkillObject* object);
        virtual ~CCSEntityInjectSkillAcion();

    public:

        //状态名字
        static Str STATE_NAME;

        ///更新事件
        virtual void        update( Flt delta );
        ///是否结束了
        virtual Bool        isFinished();
        ///进去状态事件
        virtual void        onEnter();
        ///离开状态事件
        virtual void        onLeave();

    private:

        CSkillObject* mSkillObject;
        Bool mIsBelongSelf;
    };


}


/******************************************************************************/

#endif //