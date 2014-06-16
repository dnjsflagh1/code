//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\MapServerDefine.h
//        Author: yuanlinhu
//          Date: 2012-4-25
//          Time: 9:58
//   Description: 
//			MapServer ������ �õ��Ĺ�������
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

	//#define MULTI_THREAD		//�������߳�

	enum  FIGHT_ROUND_TYPE
	{
		FIGHT_ROUND_TYPE_NULL,

		FIGHT_ROUND_TYPE_HIT,                   //����
		FIGHT_ROUND_TYPE_DODGE,                 //���
		FIGHT_ROUND_TYPE_THUMP,                 //�ػ�

		FIGHT_ROUND_TYPE_MAX
	};

	enum  TREAT_ROUND_TYPE
	{
		TREAT_ROUND_TYPE_NULL,

		TREAT_ROUND_TYPE_HIT,                   //����
		TREAT_ROUND_TYPE_THUMP,                 //�ػ�

		TREAT_ROUND_TYPE_MAX
	};

}

#endif	//_MAP_SERVER_DEFINE_H_