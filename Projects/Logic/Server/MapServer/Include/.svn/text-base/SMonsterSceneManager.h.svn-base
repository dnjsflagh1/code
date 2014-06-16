
/******************************************************************************/

#ifndef _S_MONSTER_SCENEMANAGER_H_
#define _S_MONSTER_SCENEMANAGER_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "SGameObjectFactory.h"
#include "SMonster.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // SMonster 模板对象
    /******************************************************************************/
    class SMonsterXml
    {
    public:

        // 静态不变的属性
        
        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                    initialize( SMonsterSceneManager* owner );
        virtual Bool                    unInitialize();
        virtual void                    clear();
        virtual void                    update(Flt delta);

        //-----------------------------------------------------------------------------------
        // Instance
        //-----------------------------------------------------------------------------------

        void                            getMonster( SMonsterPtr& ptr );
        Bool                            hasMonster();

        //-----------------------------------------------------------------------------------
        // MonsterBorn
        //-----------------------------------------------------------------------------------
    
    protected:

        //通过心跳 检测 是否创建SMonster实例
        void                            checkMonsterBorn();

        void                            createMonster();
        void                            destroyMonster();
        
    private:

        SMonsterSceneManager*   mSMonsterSceneManager;
        SMonsterPtr             mSMonsterPtr;
    };

    /******************************************************************************/
    //  SMonsterSceneManager
    /******************************************************************************/
    class SMonsterSceneManager	
    {
        friend class SMonsterXml;
    public:

        SMonsterSceneManager();
        virtual ~SMonsterSceneManager();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                    initialize( SSceneObject* owner );
        virtual Bool                    unInitialize();
        virtual void                    clear();
        virtual void                    update(Flt delta);
        
        //-----------------------------------------------------------------------------------
        // Base Data
        //-----------------------------------------------------------------------------------

        void					        createMonsterByXml(CharAppearType appearType);
        Bool						    hasMonster( GameObjectIndexIdInSceneType objIndex );
        Bool						    getMonster( SMonsterPtr& ptr, GameObjectIndexIdInSceneType objIndex);
        void						    removeAllMonster();

        //-----------------------------------------------------------------------------------
        // AI Ctrl
        //-----------------------------------------------------------------------------------
        
        void				            calcControlMonsterAIByPlayerListAndSendToClient();
        void				            setIsNeedCalcContorlMonsterAI(Bool need);
        
        //检测这个玩家是否是AI 控制者的列表中的人
        Bool				            hasPlayerInCtrlMonsterAIList(const AccountIdType accountId);	
        void				            addPlayerInCtrlMonsterAIList(SPlayerPtr& playerPtr);
        void				            removePlayerInCtrlMonsterAIList(const AccountIdType accountId);

    private:

        std::map<MonsterIdType,  SMonsterXml> mMonsterXmlList;
        
    protected:

        std::map<GameObjectIndexIdInSceneType,  SMonsterXml*> mMonsterList;		
        RWLocker   				        mMonsterListCs;
        GameObjectIndexIdInSceneType    mMonsterIndexCounter;

        SMonsterFactory				    mSMonsterFactory;

    };
}

#endif	