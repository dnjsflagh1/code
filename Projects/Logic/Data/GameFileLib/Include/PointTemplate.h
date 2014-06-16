
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: CharacterTemplate.h
//        Author: xyd
//          Date: 2012-4-20
//          Time: 18:34
// Description: 
//			1.坐标点模板表。
//
// modify History:
//      <author>    <time>        <descript>
//         xyd      2012-4-20      add

//////////////////////////////////////////////////////////////
//******************************************************************************************
#ifndef _H_POINTTEMPLATE_
#define _H_POINTTEMPLATE_
//******************************************************************************************
#include "GameFilePreqs.h"
//******************************************************************************************
namespace MG
{
	//-----------------------------------------------------------------------------
	enum PointUseType
	{
		point_rpg_jump_in					= 1,		//1~RPG地图跳入点
		point_rpg_jump_out					= 2,		//2~RPG地图跳出点
		point_rpg_translate					= 3,		//3~RPG地图传送点
		point_rpg_revive					= 4,		//4~RPG地图复活点
		
		point_slg_born_attacker_general		= 5,		//5~SLG战场进攻方将领出现点
		point_slg_born_attacker_troop		= 6,		//6~SLG战场进攻方军队出现点
		
		point_slg_born_defender_general		= 7,		//7~SLG战场防御方将领出现点
		point_slg_born_defender_troop		= 8,		//8~SLG战场防御方军队出现点
		
		point_slg_born_attacker_camp		= 9,		//9~SLG战场攻方兵营点
		point_slg_relive_attacker_general	= 10,		//10~SLG战场攻方将领复活点
		point_slg_born_defender_camp		= 11,		//11~SLG战场守方兵营点
		point_slg_relivedefender_general	= 12,		//12~SLG战场守方将领复活点
	};

	enum PointShowType
	{
		show_in_game_hide_in_editor = 1,		//在游戏中不显示，在编辑器中不显示
		show_in_game_show_in_editor,			//在游戏中和编辑器中都不显示
	};

	struct PointTempInfo
	{
		U32                PointTemplateId;	  //  角色模板id
		PointUseType	   UseType;           //  用途类型
		PointShowType	   ShowType;          //  显示类型
		U32		           ArtMashId;         //  模型外观Id

		Str16			   Note;			  //  策划备注1~128汉字
		Str16			   Name;              //  点的的中文代称，16汉字内
		Str16			   ListName;		  //  GameMapEditor使用的分类名称，16汉字之内
	};

	//-----------------------------------------------------------------------------
	class  PointTemplate
	{
	public:
		PointTemplate();
		~PointTemplate();
		SINGLETON_INSTANCE(PointTemplate);

	public:
		// MG_CN_MODIFY
		//加载ArtPointRes.csv;
		Bool                                load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
		//根据ID获得角色模板信息
		const PointTempInfo*				getPointTempInfo( U32 Id );
		//根据ID获得角色模板信息
		//根据顺序获得角色模版信息
		const PointTempInfo*				getPointTempInfoByIndex( U32 index );
		//获得角色模版信息的数量
		U32									getNumPointTempInfos() { return mPointTempInfoMap.size(); }

	protected:
		//释放内存
		void                                clear();

	public:
		std::map<U32, PointTempInfo*>		mPointTempInfoMap;
	};
}
//******************************************************************************************
#endif  //_H_CHARACTERTEMPLATE_
//******************************************************************************************