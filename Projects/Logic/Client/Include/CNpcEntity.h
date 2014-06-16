/******************************************************************************/
#ifndef _CNPCENTITY_H_
#define _CNPCENTITY_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "NoCharacterSceneEntity.h"
/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //Npc实体对象
    /******************************************************************************/
    class CNpcEntity : public CNoCharacterSceneEntity
    {
    public:
        CNpcEntity(IEntity* entity);
        virtual ~CNpcEntity();
     
    public:

        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [主要方法]
        //×××××××××××××××××××××××××××××××××××××××××××××××××

        // 初始化
        virtual void				        initialize();
        // 反初始化
        virtual void				        unInitialize();
        //更新
        void				                update( Flt delta );


        //×××××××××××××××××××××××××××××××××××××××××××××××××
        //  [基础属性]
        //×××××××××××××××××××××××××××××××××××××××××××××××××

        NpcEntityData*                      getDynamicData();

    protected:

        // 初始化实体
        void                                initializeEntity();

        // 更新头顶UI
        void                                updateHeadUI();

		void								checkAndPlayIdleAnim( Flt delta );

	private:

		Flt									mPauseThinkTime;

    };
}

#endif