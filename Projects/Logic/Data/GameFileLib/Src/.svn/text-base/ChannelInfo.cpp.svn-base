#include "stdafx.h"
#include "ChannelInfo.h"
namespace MG
{
	//-----------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool ChannelInfos::loadFile( CChar16* fileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(fileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}
			ChannelInfo* chatInfo = MG_NEW ChannelInfo;
			MGStrOp::toU32(csvdata->mData[chatid].c_str(), chatInfo->id);
			chatInfo->fullName = csvdata->mData[chatfullname];
			chatInfo->shortName = csvdata->mData[chatshortname];
			chatInfo->instruct = csvdata->mData[chatinstruct];
            
			//process color  vector0,1,2 = r,g,b
			std::vector<Str16> colorTemp;
			MGStrOp::split<Str16>(csvdata->mData[chatcolor],'.',colorTemp);
			MGStrOp::toFlt(colorTemp[0].c_str(),(chatInfo->color).r);
			MGStrOp::toFlt(colorTemp[1].c_str(),(chatInfo->color).g);
			MGStrOp::toFlt(colorTemp[2].c_str(),(chatInfo->color).b);

			I32 temp = 0;
			MGStrOp::toI32(csvdata->mData[chatuse].c_str(),temp);
			chatInfo->useType = (chatusetype)temp;
			MGStrOp::toI32(csvdata->mData[chatbroadcast].c_str(),temp);
			chatInfo->broadcast = (chatbroadcasttpye)temp;
			MGStrOp::toI32(csvdata->mData[chatshutdown].c_str(),chatInfo->shutDown);
			MGStrOp::toI32(csvdata->mData[chatshowplace].c_str(),chatInfo->showPlace);
			MGStrOp::toI32(csvdata->mData[chatshowsender].c_str(),chatInfo->showSenderName);
			MGStrOp::toU32(csvdata->mData[chatuselevel].c_str(),chatInfo->useLevel);
			MGStrOp::toU32(csvdata->mData[chatinterval].c_str(),chatInfo->interval);
			MGStrOp::toU32(csvdata->mData[chatconsumeitemid].c_str(),chatInfo->consumeItemId);
			MGStrOp::toU32(csvdata->mData[chatconsumeitemnum].c_str(),chatInfo->consumeItemNum);
			MGStrOp::toI32(csvdata->mData[chatsupport].c_str(),chatInfo->support);
			MGStrOp::toU32(csvdata->mData[maxchar].c_str(),chatInfo->maxChar);
            
			mListChatInfo.push_back(chatInfo);
			//mMapChatInfo[chatInfo->instruct] = chatInfo;
		}

		return true;
	}
	//-----------------------------------------------------------------------------
	ChannelInfo* ChannelInfos::getChannelInfo( U32 chatId )
	{
		if (mListChatInfo.empty())
		{
			return NULL;
		}

		ChatInfoIt it = mListChatInfo.begin();
		for (; it != mListChatInfo.end(); ++it)
		{
			if (*it && (*it)->id == chatId)
			{
				return *it;
			}
		}

		return NULL;
		
	}
	//-----------------------------------------------------------------------------
	ChannelInfo* ChannelInfos::getChannelInfo( CChar16* chatName )
	{
		if (mListChatInfo.empty())
		{
			return NULL;
		}

		ChatInfoIt it = mListChatInfo.begin();
		for (; it != mListChatInfo.end(); ++it)
		{
			if (*it && ((*it)->fullName.compare(chatName)==0))
			{
				return *it;
			}
		}

		return NULL; 
	}
	//-----------------------------------------------------------------------------
	ChannelInfo* ChannelInfos::getChatInfoByInstruct( Char16* &msg )
	{	
		ChannelInfo* channelInfo = NULL;
		if (msg[0] != L'/')
		{
			return channelInfo;
		}
        
		//第一个空前面有多少个字符
		I32 firstBlankPos = WcsStr(msg,L" ") - msg;
		Str16 tempStr(msg,0,firstBlankPos);
		I32 pos = -1;
		for(ChatInfoIt it = mListChatInfo.begin(); it != mListChatInfo.end(); ++it)
		{	
			pos = tempStr.find((*it)->instruct);
			if(pos != -1)
			{
				//pos!=-1 即为0 快捷指令加一个空格后为具体内容
				pos += (*it)->instruct.size()+1;
				msg = msg + pos;
				return *it;
			}
		}
		return NULL;
	}
	//-----------------------------------------------------------------------------
	ChannelInfos::ChannelInfos()
	{
		
	}
	//-----------------------------------------------------------------------------
	ChannelInfos::~ChannelInfos()
	{
		if (mListChatInfo.empty())
		{
			return;
		}

		ChannelInfo* channelInfo = NULL;
		for(ChatInfoIt it = mListChatInfo.begin(); it != mListChatInfo.end(); ++it)
		{
			channelInfo = *it;
			if(channelInfo)
			{
				MG_SAFE_DELETE(channelInfo);
			}
		}
		mListChatInfo.clear();
	}
    //-----------------------------------------------------------------------------
	std::list<ChannelInfo*> ChannelInfos::getChannelInfoByUseType( const Int& type )
	{
		std::list<ChannelInfo*>    channelInfoList;
		if (mListChatInfo.empty())
		   return channelInfoList;
		for (ChatInfoIt it=mListChatInfo.begin();it!=mListChatInfo.end();++it)
		{
             if ((*it)->useType==type)
               channelInfoList.push_back(*it);
		}
		return channelInfoList;

	}

	std::list<ChannelInfo*> ChannelInfos::getChannelInfoByShowType( const Int& showType )
	{
		std::list<ChannelInfo*>    channelInfoList;
		if (mListChatInfo.empty())
			return channelInfoList;
		for (ChatInfoIt it=mListChatInfo.begin();it!=mListChatInfo.end();++it)
		{
			if ((*it)->showPlace==showType)
				channelInfoList.push_back(*it);
		}
		return channelInfoList;
	}

}