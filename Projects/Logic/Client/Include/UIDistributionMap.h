//*************************************************************************************************************************
#ifndef _H_UIDISTRIBUTIONMAP_
#define _H_UIDISTRIBUTIONMAP_
//*************************************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************************************************
namespace MG
{
	class CDistributionMap : public UIObject
	{
	public:
		CDistributionMap(){;}
		~CDistributionMap(){;}

	public:
		virtual		void	setEvent();		

	protected:
					void	init(const Str& filename);
	private:
		static		void	onClickEnterPlaceMap(void* widget);
		static		void	onClickReturnWorldMap(void* widget);

	private:
					void	handleEnterPlaceMap(PlaceIdType id);
					void	handleReturnWorldMap(RegionIdType id);

	};
	//--------------------------------------------------------------------------------------------
	class UIDistributionMap
	{
	public:
		UIDistributionMap();
		~UIDistributionMap(){;}
		SINGLETON_INSTANCE(UIDistributionMap);

	public:
		Bool		initialize();
		void		unInitialize();
		void		openGui(MapDistributionIdType mapIdType);
		void		closeGui();

	protected:
	private:
		std::map<MapDistributionIdType, CDistributionMap*>	mMapCDistributionMap;
		CDistributionMap*									mCurOpenCDistributionMap;

	};
}
//*************************************************************************************************************************
#endif
//*************************************************************************************************************************