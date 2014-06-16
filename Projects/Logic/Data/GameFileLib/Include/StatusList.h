//***************************************************************************************
#ifndef _H_STATUSLIST_
#define _H_STATUSLIST_
//***************************************************************************************
#include "GameFilePreqs.h"
//***************************************************************************************
namespace MG
{
	
	//----------------------------------------------------------------------
	struct StatusData 
	{
		UInt					StatusId;
		STATUS_TYPE				StatusType;
		UInt					StatusListId;
		const StatusBaseInfo*	mpStatusBaseInfo;
	};
	//----------------------------------------------------------------------
	class StatusList
	{
	public:
		StatusList(){;}
		~StatusList();
		SINGLETON_INSTANCE(StatusList);

	public:
		Bool				load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
		const StatusData*	getStatusData(UInt id);
		const StatusData*	getStatusData(UInt id, UInt objLvl);

	private:
		void				clear();
		void				setStatusBaseInfo(StatusData* pStatusData);
		void				setStatusData(StatusData* pStatusData);
		const StatusData*	getStatusDataByTypeListId(STATUS_TYPE type, UInt listId);

	private:
		std::map<UInt, StatusData*> mMapStatusData;
		std::map<STATUS_TYPE, std::map<UInt, StatusData*>*> mMapStatusTypeStatusData;

	};
}

//***************************************************************************************
#endif
//***************************************************************************************