
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
    // SMonster ģ�����
    /******************************************************************************/
    class SMonsterXml
    {
    public:

        // ��̬���������
        
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

        //ͨ������ ��� �Ƿ񴴽�SMonsterʵ��
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
        
        //����������Ƿ���AI �����ߵ��б��е���
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