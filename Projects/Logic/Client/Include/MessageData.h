/******************************************************************************/
#ifndef	_MessageData_H_
#define	_MessageData_H_
/******************************************************************************/

/******************************************************************************/
namespace MG
{
     
	//聊天面板结构
	struct ChatTag
	{              
		Str16             tagName;
		std::vector<U32>  channelList;

		ChatTag():tagName(L""){}
		Bool channelInfoExist(U32 channelid)
		{
			if (channelList.empty())
				return false;
			for (std::vector<U32>::iterator it=channelList.begin();it!=channelList.end();it++)
			{
				if ((*it)==channelid)
					return true;
			}
			return false;
		}
		void addChatInfoID(U32 channelid)
		{
			if (channelList.empty())
			{   
				channelList.push_back(channelid);
			}
			else
			{
				if (!channelInfoExist(channelid))
					channelList.push_back(channelid);
			}
		}
	};
/*
	struct HyperLink
	{
         Str16   name;
		 U32     id;
		 Byte    type;
	};
*/
	//存储服接收到的聊天信息结构
#pragma pack (push)
#pragma pack (1)
	struct RecChatData
	{
        Byte      channelid;
		Char16    dataSender[MAX_CLAN_NAME];
		U16		  dataSize;
		Char8	  data[1];
	};

#pragma pack (pop)


}

#endif