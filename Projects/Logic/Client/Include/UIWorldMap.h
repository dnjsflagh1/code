//*************************************************************************************************************************
#ifndef _H_UIWORLDMAP_
#define _H_UIWORLDMAP_
//*************************************************************************************************************************
#include "ClientPreqs.h"
#include "UIObject.h"
//*************************************************************************************************************************
namespace MG
{
	class CWorldMap : public UIObject
	{
	public:
		CWorldMap(){;}
		~CWorldMap(){;}

	public:
		virtual		void	setEvent();		

	protected:
					void	init(const Str& filename);
	private:
		static		void	onClickEnterDistribution(void* widget);

	private:
					void	handleEnterDistribution(MapDistributionIdType id);

	};
	//--------------------------------------------------------------------------------------------
	class UIWorldMap
	{
	public:
		UIWorldMap();
		~UIWorldMap(){;}
		SINGLETON_INSTANCE(UIWorldMap);

	public:
		Bool		initialize();
		void		unInitialize();
		void		openGui(MapIdType mapIdType);
		void		closeGui();

	protected:
	private:
		std::map<MapIdType, CWorldMap*> mMapCWorldMap;
		CWorldMap*						mCurOpenCWorldMap;

	};
}
//*************************************************************************************************************************
#endif
//*************************************************************************************************************************