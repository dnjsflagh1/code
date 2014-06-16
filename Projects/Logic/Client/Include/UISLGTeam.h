//***************************************************************************************************
#ifndef _H_UISLGTEAM_
#define _H_UISLGTEAM_
//***************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//***************************************************************************************************
namespace MG
{


	class UISLGTeam  : public UIObject
	{
		public:
			UISLGTeam();
			~UISLGTeam();
			SINGLETON_INSTANCE(UISLGTeam);
		public:
			virtual	void	restore();
			virtual void	setEvent();
		public:
			void			init();
			void			UIFresh();
			void			UIFreshByIndex(POSITION pos);
			void			UIDeleteMemberByIndex(POSITION pos);
			static	void	onClickHeadEvent( void* widget );

		public:
			void		clear();
			void		addTeamMember(Byte pos, Int playerCharId);
			void		deleteTeamMember(Byte pos);
			POSITION	findShowPosition(POSITION pos);


			std::map<POSITION, Int>	mTeamList;   //characterIdΪkey
	};
}
#endif
