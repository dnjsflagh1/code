/******************************************************************************/
#ifndef _AIFIGHTTRIGGER_H_
#define _AIFIGHTTRIGGER_H_
/******************************************************************************/

#include "AI.h"
#include "WorldCorePreqs.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	/******************************************************************************/

	struct FightEventGameObj
	{
		GAMEOBJ_TYPE gameObjType;
		IdType		 gameObjId;

		FightEventGameObj():
		gameObjType(GOT_UNKNOWN),
		gameObjId(0)
		{

		}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////

	enum FightTriggerEventType
	{
		FTET_NULL,
		FTET_BUFF,
		FTET_SKILL,	
	};

	/////////////////////////////////////////////////////////////////////////////////////////////

	struct FightTriggerEvent
	{
		FightTriggerEventType				fightTriggerEventType;
		U64									eventParam1;
		std::vector<FightEventGameObj>		fightEventGameObjList;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////

	//class FightTriggerListener
	//{
	//public:
	//	virtual void onFightTrigger( FightTriggerEvent& fightTriggerEvent ){};
	//};

	/////////////////////////////////////////////////////////////////////////////////////////////

	class AIFightTrigger : public AI
	{
	public:
		AIFightTrigger();
		virtual ~AIFightTrigger();


		/////////////////////////////////////////////////////////////////////////////////////////////

		virtual void										update( Flt delta );

		/////////////////////////////////////////////////////////////////////////////////////////////

		virtual UInt										getFightAITriggerCount( UInt aiFightId );

		//void										addFightTriggerListener( FightTriggerListener* listener );

		//void										removeFightTriggerListener( FightTriggerListener* listener );

		//void										clearAllFightTriggerListener();

		/////////////////////////////////////////////////////////////////////////////////////////////

		void												notifyFightTrigger( FightTriggerEvent& fightTriggerEvent );

		/////////////////////////////////////////////////////////////////////////////////////////////

		void												setCurrTarget( GAMEOBJ_TYPE gameObjType, IdType gameObjId );

	protected:

		////////////////////////////////////////////////////////////////////////////////////////////

		virtual void										getCharacterForContactCharType( FightAIInfo* fightAIInfo, GAMEOBJ_TYPE& gameObjType, IdType& gameObjId );

		virtual void										getCharacterForEventCharType( FightAIInfo* fightAIInfo, std::vector<FightEventGameObj>& fightEventGameObjList );

		////////////////////////////////////////////////////////////////////////////////////////////

		virtual FightAIInfo*								checkFightTrigger( const FightAIGroup* fightAIInfoGroup );

		virtual Bool										checkContactType1( FightAIInfo* fightAIInfo );

		virtual Bool										checkContactType2( FightAIInfo* fightAIInfo );

		virtual Bool										checkContactType3( FightAIInfo* fightAIInfo );

		virtual Bool										checkContactType4( FightAIInfo* fightAIInfo );

		virtual Bool										checkContactType5( FightAIInfo* fightAIInfo );

		virtual Bool										checkContactType6( FightAIInfo* fightAIInfo );

		virtual Bool										checkContactType7( FightAIInfo* fightAIInfo );

		virtual Bool										checkContactType8( FightAIInfo* fightAIInfo );

		void												setFightEvent( FightAIInfo* fightAIInfo );

		////////////////////////////////////////////////////////////////////////////////////////////

	protected:

		/*std::list<FightTriggerListener*>			mListenerList;*/

		GAMEOBJ_TYPE										mCurrTargetType;
		IdType												mCurrTargetId;
		const FightAIGroup*									mFightAIGroup;
		Flt													mPauseThinkTime;
	};
}

#endif