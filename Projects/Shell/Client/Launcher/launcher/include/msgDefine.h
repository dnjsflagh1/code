/***************************************************
** Copyright (C) 2006-2010 Orsh
** This file is part of the "Game Launcher".
** All rights reserved
****************************************************/

#ifndef _MSGDEFINE_LUANCHER_H_
#define _MSGDEFINE_LUANCHER_H_
enum ENetMessageFlag
{
	ENM_VERSION_CHECK = 1,				// 版本检测
	ENM_GET_DOWNLOAD_URL,				// 获取下载地址列表
	ENM_TEST_1,
	ENM_TEST_2,
	ENM_TEST_3
};

enum EURLType
{
	EUT_NONE,
	EUT_HTTP,
	EUT_FTP,
	EUT_HTTPS,
};

const int g_addrPort = 6000;
#endif