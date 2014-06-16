/******************************************************************************/
#ifndef _CAIENTITYFIGHTTRIGGER_H_
#define _CAIENTITYFIGHTTRIGGER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "FightManager.h"
#include "AIFightTrigger.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	/******************************************************************************/

	/////////////////////////////////////////////////////////////////////////////////////////////

	//class FightTriggerListener
	//{
	//public:
	//	virtual void onFightTrigger( FightTriggerEvent& fightTriggerEvent ){};
	//};

	/////////////////////////////////////////////////////////////////////////////////////////////

	class CAIEntityFightTrigger : public AIFightTrigger, public LinedStateObject
	{
	public:
		CAIEntityFightTrigger( CCharacterSceneEntity*	characterSceneEntity );
		virtual ~CAIEntityFightTrigger();

		//状态名字
		static Str STATE_NAME;

		///更新事件
		virtual void        						update( Flt delta );
		///是否结束了
		virtual Bool        						isFinished();
		///进去状态事件
		virtual void        						onEnter();
		///离开状态事件
		virtual void        						onLeave();

		/////////////////////////////////////////////////////////////////////////////////////////////

		//void										addFightTriggerListener( FightTriggerListener* listener );

		//void										removeFightTriggerListener( FightTriggerListener* listener );

		//void										clearAllFightTriggerListener();

		/////////////////////////////////////////////////////////////////////////////////////////////

	protected:

		////////////////////////////////////////////////////////////////////////////////////////////

		void										getCharacterForContactCharType( FightAIInfo* fightAIInfo, GAMEOBJ_TYPE& gameObjType, IdType& gameObjId );

		void										getCharacterForEventCharType( FightAIInfo* fightAIInfo, std::vector<FightEventGameObj>& fightEventGameObjList );

		////////////////////////////////////////////////////////////////////////////////////////////

		Bool										checkContactType1( FightAIInfo* fightAIInfo );

		Bool										checkContactType2( FightAIInfo* fightAIInfo );

		Bool										checkContactType3( FightAIInfo* fightAIInfo );

		Bool										checkContactType4( FightAIInfo* fightAIInfo );

		Bool										checkContactType5( FightAIInfo* fightAIInfo );

		Bool										checkContactType6( FightAIInfo* fightAIInfo );

		Bool										checkContactType7( FightAIInfo* fightAIInfo );

		Bool										checkContactType8( FightAIInfo* fightAIInfo );

		////////////////////////////////////////////////////////////////////////////////////////////

		UInt										getFightAITriggerCount( UInt fightAIId );

	protected:

		/*std::list<FightTriggerListener*>			mListenerList;*/

		CCharacterSceneEntity*						mCharacterSceneEntity;
		GAMEOBJ_TYPE								mCurrTargetType;
		IdType										mCurrTargetId;
		const FightAIGroup*							mFightAIGroup;
		Flt											mPauseThinkTime;
	};
}

#endif