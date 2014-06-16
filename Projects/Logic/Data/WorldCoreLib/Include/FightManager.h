/******************************************************************************/
#ifndef _FIGHTMANAGER_H_
#define _FIGHTMANAGER_H_
/******************************************************************************/

#include "FightInfo.h"

#define FIGHTINFOINTERVALTIME  16000

/******************************************************************************/

/******************************************************************************/
//ս������
/******************************************************************************/

namespace MG
{
	class FightManagerListener
	{
	public:
		virtual void onEnterFight( GameObject* fightObject ){};

		virtual void onFightInfoChanged( GameObject* fightObject ){};

		virtual void onEndFight( GameObject* fightObject ){};
	};

	class FightManager
	{
	public:
		enum HateType
		{
			HT_NULL,
			HT_MAX,
			HT_SEC,
		};

	public:
		FightManager( GameObject* owner );
		~FightManager();

	public:
		//���ս����Ϣ
		virtual void						addAndUpdateFightInfo( GameObject* fightObject, IdType addHateGameObjID, UInt hateVal );
		//ɾ��ս����Ϣ
		virtual void						delFightInfo( GameObject* fightObject );

		//ɾ������ս����Ϣ
		virtual void						delAllFightInfo();

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		
		virtual FightInfo*					getFightInfo( GameObject* fightObject );

		virtual FightInfo*					getFightInfo( IdType fightInfoID );

		virtual FightInfo*					getFightInfoForIndex( UInt index );

			void							delFightInfo( IdType fightInfoID );


		//////////////////////////////////////////////////////////////////////////////////////////////////////

		std::map<IdType, FightInfo>*		getFightInfoList();

		UInt								getFightInfoNum();

		//////////////////////////////////////////////////////////////////////////////////////////////////////

		FightInfo*							getFightInfoByHate( HateType hateType );

		U64									getFightBeginTime();


		//////////////////////////////////////////////////////////////////////////////////////////////////////

		void								addListener( FightManagerListener* listener );

		void								removeListener( FightManagerListener* listener );

		void								clearAllListener();

		//////////////////////////////////////////////////////////////////////////////////////////////////////

		Bool								isEnterFight();

		//////////////////////////////////////////////////////////////////////////////////////////////////////

		Vec3								getEnterFightPos();
			
	public:
		virtual void						update();

		////////////////////////////////////////////////////////////////////////////////////////////////////

		virtual void						notifyEnterFight( GameObject* fightObject );
		//�㲥ս����Ϣ�иĶ�
		virtual void						notifyChanged( GameObject* fightObject );

		virtual void						notifyEndFight( GameObject* fightObject );

	protected:

		////////////////////////////////////////////////////////////////////////////////////////////////////

		virtual FightInfo*					addFightInfo( IdType fightInfoID, GameObject* fightObject, UInt hateVal );

	protected:
		std::map<IdType, FightInfo>			mFightList;
		std::list<FightManagerListener*>    mListenerList;

		GameObject*							mOwner;

		U64									mFightBeginTime; 

		Vec3								mEnterFightPos;
	};

}

#endif