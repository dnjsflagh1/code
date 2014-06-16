//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SPlayerNew.h
//        Author: yuanlinhu
//          Date: 2012-3-13
//          Time: 15:44
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-13      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _S_PLAYER_IDENTIFY_INFO_H_
#define _S_PLAYER_IDENTIFY_INFO_H_
/******************************************************************************/

#include "MapServerPreqs.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//�ͻ�����Ҷ������
	//��Ҫ���ڰ󶨵�ͼ����Ϳͻ������֮��Ĺ�ϵ���ͻ�����Һ�FrontServer֮��Ĺ�ϵ
	//����ͬ������ز���
	/******************************************************************************/

	// SPlayer ��ʶ����
	struct SPlayerIdentifyInfo
	{
		// �ʺ�
		AccountIdType accountId;
		// ��ӦFrontServer�ı��
		NetIdType frontServerId;
		// ��ӦFrontServer��ClientNetID
		NetIdType clientNetIdInFrontServer;
		// ����id
		ClanIdType clanId;

		void clear()
		{
			accountId = 0;
			frontServerId = -1;
			clientNetIdInFrontServer = -1;
			clanId = 0;
		}
	};

}

#endif	//namespace MG