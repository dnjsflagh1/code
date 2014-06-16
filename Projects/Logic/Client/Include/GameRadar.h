#ifndef _GAME_RADAR_H
#define _GAME_RADAR_H
/******************************************************************************/
#include "ClientPreqs.h"
#include "IEngineMain.h"
#include "GameMiniMapManager.h"
#include "IImage.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//游戏小地图
	/******************************************************************************/

	class GameRadar : public GameMiniMap
	{
	public:

		////////////////////////////////////////////////////////////////////

		explicit GameRadar( Str name );
		~GameRadar();

		////////////////////////////////////////////////////////////////////

		//初始化
		Bool					init();

		//反初始化
		void					unInit();

		//读取某张地图
		Bool					loadMap( Str name, Str path, Vec2 visibleWorldSize, Vec2 worldCenter );

		//卸载某张地图
		void					unloadMap();

		//更新
		void					update(Flt delta);

		////////////////////////////////////////////////////////////////////

	public:

		//设置显示这个小雷达的UI控件
		void					setContainerWidget(IImage* image);
		//释放UI控件上的小雷达
		void					releaseContainerWidget(IImage* image);

		//从图片位置到世界位置
		Vec2					convertImagePositionToWorldPosition(VecI2 imagePos);
		//从控件上的相对位置到图片位置
		VecI2					convertContainerPositionToImagePosition(VecI2 containerPos);
		//从世界位置到图片位置
		VecI2					convertWorldPositionToImagePosition(Vec3 worldPos);

	protected:

		////////////////////////////////////////////////////////////////////
		//绘制函数
		////////////////////////////////////////////////////////////////////

		//画地图背景
		void					drawBackGround();
		//绘制所有角色
		void					drawAllUnit();
		//绘制所有的角色， 在非战斗状态下;
		void					drawPeaceUnit(IdType mainID);
		//绘制所有的角色， 在战斗状态下;
		void					drawBattleUnit(IdType mainID, FORCE mainForce);
		//单独的绘制角色
		void					drawUnit(Vec3 pos, const Str& iconName, const Str& iconGroup);
		////////////////////////////////////////////////////////////////////

	protected:
		
		//////////////////////////////////////////////////////////////////////
		//控件
		//////////////////////////////////////////////////////////////////////
		VecI2					mContainerSize;

		//////////////////////////////////////////////////////////////////////
		//资源
		//////////////////////////////////////////////////////////////////////

		//地图图片资源
		Str						mWorldMapName;

		Str						mWorldMapGroup;
		
		//玩家自己的图标
		Str						mSelfCharIcon;
		//同伴玩家
		Str						mCompanyCharIcon;
		//对手玩家
		Str						mRivalCharIcon;
		//己方军队
		Str						mCompanyArmyIcon;
		//对方军队
		Str						mRivalArmyIcon;
		//己方攻击建筑
		Str						mCompanyBuildIcon;
		//对方攻击建筑
		Str						mRivalBuildIcon;
		//普通建筑
		Str						mPeaceBuildIcon;
		//NPC
		Str						mNpcIcon;

		//////////////////////////////////////////////////////////////////////
		//计时
		//////////////////////////////////////////////////////////////////////

		//更新间隔
		Flt						mUpdateInterval;
		//更新计时
		Flt						mTimeElapse;
	
	};
}

/******************************************************************************/
#endif