//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SPlayerNew.h
//        Author: yuanlinhu
//          Date: 2012-3-13
//          Time: 15:44
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-13      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _SPLAYER_H_
#define _SPLAYER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "HeartBeatObject.h"
#include "SPlayerIdentifyInfo.h"
#include "SSceneObjectPtr.h"

/******************************************************************************/
namespace MG
{
    // SPlayer
    class SPlayer : public HeartBeatObject
	{
	public:

		SPlayer();
		virtual ~SPlayer();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                    initialize();
        virtual Bool                    unInitialize();

		virtual Bool                    update(Flt delta);

        virtual void                    clear();

        //-----------------------------------------------------------------------------------
        // Debug
        //-----------------------------------------------------------------------------------

        void				            print();

        //-----------------------------------------------------------------------------------
        // Base Info
        //-----------------------------------------------------------------------------------

        // 得到标识信息
        SPlayerIdentifyInfo*            getIdentifyInfo();
        // 得到是否看得见摄像机
        Bool			                getCanSeeByCamera() const;
        // 设置是否看得见摄像机
        void			                setCanSeeByCamera(Bool canSee);

        //-----------------------------------------------------------------------------------
        // PlayerCharacter
        //-----------------------------------------------------------------------------------

		void                            createPlayerCharacter(  SPlayerCharacterPtr charPtr, PlayerCharacterIdType playerCharacterId, PlayerCharacterData& data );
		Bool                            retrievePlayerCharacter( SPlayerCharacterPtr& ptr, PlayerCharacterIdType id );
        Bool				            hasPlayerCharacter( PlayerCharacterIdType id );
        void			                destroyPlayerCharacter( PlayerCharacterIdType id );
		void			                destroyAllPlayerCharacters();

		Bool        	                getMainPlayerCharacter(SPlayerCharacterPtr& ptr);
		void				            setMainPlayerCharacter(PlayerCharacterIdType id);

        //-----------------------------------------------------------------------------------
        // Region
        //-----------------------------------------------------------------------------------

        // 设置和得到所属场景
        void                            setBelongScene( SSceneObjectPtr& ptr );
        void                            getBelongScene( SSceneObjectPtr& ptr );

        //-----------------------------------------------------------------------------------
        // AI
        //-----------------------------------------------------------------------------------

		void                            addControlAIMonsterId(GameObjectIdType monsterId);
		void                            clearControlAIMonsterId();
		std::vector<GameObjectIdType>*  getControlAIMonsterIdList();
        
        //-----------------------------------------------------------------------------------
        // CD
        //-----------------------------------------------------------------------------------

		SCDManager*			            getSCDManager();


		//-----------------------------------------------------------------------------------
		// 标识信息
		//-----------------------------------------------------------------------------------
		AccountIdType	                getAccountId();
		NetIdType 		                getFrontServerId(); 
		NetIdType 		                getClientNetIdInFrontServer(); 
		ClanIdType		                getClanId();

	private:

        // 标识信息
        SPlayerIdentifyInfo mSPlayerIdentifyInfo;
       
		//通过镜头激活对象
        Bool	    mCanSeeByCamera;

        // 角色工厂
        SPlayerCharacterFactory* mSPlayerCharacterFactory;

        //玩家角色列表
        std::map<PlayerCharacterIdType,SPlayerCharacterPtr> mPlayerCharacterList;
        RWLocker    mPlayerCharacterListCs;
        PlayerCharacterIdType mMainSPlayerCharacterID;

		//当前所在地区的指针
		SSceneObjectPtr		mSceneObjectPtr;
		
		//CD
		SCDManager* mSCDManager;
       
		//玩家所控制的怪物AI列表
		std::vector<GameObjectIdType>   mControlAIMonster; 
	};


    /******************************************************************************/
    //客户端玩家智能指针
    /******************************************************************************/

    class SPlayerPtr : public SharedPtr<SPlayer> 
    {
        friend class SPlayerFactory;

    protected:

        SPlayerFactory* mFactory;
  
    public:

        virtual ~SPlayerPtr() { release(); }
        SPlayerPtr() : SharedPtr<SPlayer>(),mFactory(NULL){}
        explicit SPlayerPtr(SPlayer* rep) : SharedPtr<SPlayer>(rep),mFactory(NULL){}
        SPlayerPtr(const SPlayerPtr& r) : SharedPtr<SPlayer>(r),mFactory(r.mFactory) {} 

        SPlayerPtr& operator=(const SPlayerPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            SPlayerPtr tmp(r);
            if ( isNull() == false )
            {
                tmp.mFactory = mFactory;
            }

            swap(tmp);

            mFactory = r.mFactory;

            return *this;
        }

    protected:

        virtual void    destroy(void);

    };


}
#endif	//_SPLAYER_H_