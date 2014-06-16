/******************************************************************************/
#ifndef _S_SSCENE_GRID_H_
#define _S_SSCENE_GRID_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "STroop.h"
/******************************************************************************/

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	// Player In Grid
	/******************************************************************************/

	struct PlayerInGrid
	{
        NetIdType clientNetIdInFrontServer;
	};

	struct PlayerListInGrid
	{
        typedef std::map<PlayerIdType, PlayerInGrid
            ,less<PlayerIdType>, 
            StlSoloAllocator<PlayerInGrid>> PlayerInGridListMap;  
        
		PlayerInGridListMap mPlayerList;
	};

	class STroopPtr;
    /******************************************************************************/
    // ����ͬ���������
    /******************************************************************************/
	class SSceneGrid
	{
	public:

		SSceneGrid(){}
		virtual ~SSceneGrid(){}


        //-----------------------------------------------------------------------------------
        // Player
        //-----------------------------------------------------------------------------------

		void                addPlayerInteraction( SPlayerPtr& player );
		void                removePlayerInteraction( SPlayerPtr& player );
		void                removeAllPlayerInteraction();
		void                getPlayerInteractionListList( std::map<NetIdType, PlayerListInGrid>& list );

        //-----------------------------------------------------------------------------------
        // PlayerCharacter
        //-----------------------------------------------------------------------------------

		void                addPlayerCharacter( SPlayerCharacterPtr& playercharacter );
		void                removePlayerCharacter( GameObjectIndexIdInSceneType index );
        void                removeAllPlayerCharacter();
		void                getPlayerCharacterList( std::vector<SPlayerCharacterPtr>& list );

        //-----------------------------------------------------------------------------------
        // Monster
        //-----------------------------------------------------------------------------------

		void                addMonster( SMonsterPtr& monster );
		void                removeMonster( GameObjectIndexIdInSceneType index );
		void                removeAllMonster();
        void                getMonsterList( std::vector<SMonsterPtr>& list );

        //-----------------------------------------------------------------------------------
        // Building
        //-----------------------------------------------------------------------------------

		void                addBuilding( SBuildingPtr& building );
		void                removeBuilding( GameObjectIndexIdInSceneType index );
		void                removeAllBuilding();
        void                getMonsterList( std::vector<SBuildingPtr>& list );

        //-----------------------------------------------------------------------------------
        // Item
        //-----------------------------------------------------------------------------------

		void                addDropItem( SItemPtr& dropItem );
		void                removeDropItem( GameObjectIndexIdInSceneType index );
		void                removeAllDropItem();
        void                getMonsterList( std::vector<SItemPtr>& list );


		//-----------------------------------------------------------------------------


		//--------------------------------------------------------------------------
		void				removeAllCharacter(){}
		void				removeAll(){}

		void                setSceneGridManager( SSceneGridManager* regionGridManager ){}
		SSceneGridManager*  getSceneGridManager(){ return NULL; }


		//void 				addCharacter( SPlayerCharacter* playercharacter );
		//void 				addCharacter( SPlayerCharacter* playercharacter );

	protected:
        
        SSceneGridManager*										        mSceneGridManager;

        //-----------------------------------------------------------------------------

		std::map<NetIdType, PlayerListInGrid>					            mPlayerListInGridDivideByFrontServer;
        Critical    mPlayerListInGridDivideByFrontServerCs;

        //-----------------------------------------------------------------------------

/*        typedef std::map< GameObjectIndexIdInSceneType, SPlayerCharacterPtr
                          ,less<GameObjectIndexIdInSceneType>
                          ,StlSoloAllocator<SPlayerCharacterPtr> >           PlayerCharacterListInGridMap; */ 

		//PlayerCharacterListInGridMap    mPlayercharacterList;
		//std::map< GameObjectIndexIdInSceneType, SPlayerCharacterPtr> mPlayercharacterList;
        Critical    mPlayercharacterListCs;


        //-----------------------------------------------------------------------------

        //typedef std::map< GameObjectIndexIdInSceneType, STroopPtr
        //                  ,less<GameObjectIndexIdInSceneType>
        //                  ,StlSoloAllocator<STroopPtr>>                     TroopListInGridMap; 

		//TroopListInGridMap  mTroopList;
		//std::map< GameObjectIndexIdInSceneType, STroopPtr>	mTroopList;
        Critical    mTroopListCs;

        //-----------------------------------------------------------------------------

        //typedef std::map< GameObjectIndexIdInSceneType, SMonsterPtr
        //                ,less<GameObjectIndexIdInSceneType>
        //                ,StlSoloAllocator<SMonsterPtr>>                     MonsterListInGridMap; 

        //std::map< GameObjectIndexIdInSceneType, SMonsterPtr>            mMonsterList;
        Critical    mMonsterListCs;

        //-----------------------------------------------------------------------------

        //typedef std::map< GameObjectIndexIdInSceneType, SBuildingPtr
        //    ,less<GameObjectIndexIdInSceneType>
        //    ,StlSoloAllocator<SBuildingPtr>>                                 BuildingListInGridMap; 

        //BuildingListInGridMap           mBuildingList;
        Critical    mBuildingListCs;

        //-----------------------------------------------------------------------------

        //typedef std::map< GameObjectIndexIdInSceneType, SItemPtr
        //    ,less<GameObjectIndexIdInSceneType>
        //    ,StlSoloAllocator<SItemPtr> >                                    ItemListInGridMap; 

        //ItemListInGridMap                mDropItemList;
        Critical    mDropItemListCs;

        //-----------------------------------------------------------------------------
    

	};
}


#endif	