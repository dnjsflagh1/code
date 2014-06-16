//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\MapServerDefine.h
//        Author: yuanlinhu
//          Date: 2012-4-25
//          Time: 9:58
//   Description: 
//			MapServer 工程中 用到的公共定义
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-25      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _MAP_SERVER_DEFINE_H_
#define _MAP_SERVER_DEFINE_H_

/******************************************************************************/
namespace MG
{

#define GRIDSBROADCAST

	//#define MULTI_THREAD		//启动多线程

	enum  FIGHT_ROUND_TYPE
	{
		FIGHT_ROUND_TYPE_NULL,

		FIGHT_ROUND_TYPE_HIT,                   //命中
		FIGHT_ROUND_TYPE_DODGE,                 //躲避
		FIGHT_ROUND_TYPE_THUMP,                 //重击

		FIGHT_ROUND_TYPE_MAX
	};

	enum  TREAT_ROUND_TYPE
	{
		TREAT_ROUND_TYPE_NULL,

		TREAT_ROUND_TYPE_HIT,                   //命中
		TREAT_ROUND_TYPE_THUMP,                 //重击

		TREAT_ROUND_TYPE_MAX
	};

}

#endif	//_MAP_SERVER_DEFINE_H_