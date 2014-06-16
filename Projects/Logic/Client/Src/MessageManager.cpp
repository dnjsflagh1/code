//***************************************************************************************************
#include "stdafx.h"
#include "MessageManager.h"
#include "ChannelInfo.h"
#include "MessageData.h"
#include "ChatNetPacket.h"
#include "ChatNetPacketProcesser.h"
#include "ChannelInfo.h"
#include "UIChatSendMsg.h"
#include "UIChatCommonShow.h"
#include "BanKeyword.h"

#include "CSceneManager.h"
#include "CPlayerCharacterEntity.h"
#include "CPlayer.h"
#include "UIMessageBox.h"


//***************************************************************************************************
namespace MG
{

	//----------------------------------------------------------------------------------------
	MessageManager::MessageManager()
		:mSelectChannel(NULL),mSelectChatTag(NULL)
	{
            mTestCount = 0;
			mAllServerChatInterval = 0;
			mOneRegionChatInterval = 0;
	}
    //----------------------------------------------------------------------------------------
	MessageManager::~MessageManager()
	{
		clear();

	}
	//----------------------------------------------------------------------------------------
	MG::Bool MessageManager::initialize()
	{
         //TODO 读配置
		 setAllServerChatInterval(1500);
		 setOneRegionChatInterval(1000);


		 return true;

	}

	/***********************************聊天面板标签操作*************************************/
	Bool MessageManager::addChatTag( CChar16* tagName )
	{
		ChatTag *tempChatTag = MG_NEW ChatTag;
		if (!tempChatTag)
			return false;
		if (mChatTagList.empty())
		{
			tempChatTag->tagName = tagName;
			mChatTagList.push_back(tempChatTag);
			//MG_SAFE_DELETE(tempChatTag);
			return true;
		}
		else
		{
			for ( mChatTagIt = mChatTagList.begin(); mChatTagIt != mChatTagList.end(); ++mChatTagIt)
			{
				if (*mChatTagIt&&((*mChatTagIt)->tagName.compare(tagName)==0))
				{
					//标签名称重复
					MG_SAFE_DELETE(tempChatTag);
					return false;
				}
			}
			tempChatTag->tagName = tagName;
			mChatTagList.push_back(tempChatTag);
			//MG_SAFE_DELETE(tempChatTag);
			return true;

		}

	}
    //----------------------------------------------------------------------------------------
	Bool MessageManager::removeChatTag( CChar16* tagName )
	{

		if (mChatTagList.empty())
			return false;
		for ( mChatTagIt = mChatTagList.begin(); mChatTagIt != mChatTagList.end();++mChatTagIt)
		{
			if (*mChatTagIt&&((*mChatTagIt)->tagName.compare(tagName)==0))
			{
				mChatTagList.erase(mChatTagIt);
				return true;
			}
		}
		return false;
	}
    //----------------------------------------------------------------------------------------
	ChatTag* MessageManager::getChatTagByName( CChar16* tagName )
	{
		if (mChatTagList.empty())
			return NULL;
		for ( mChatTagIt = mChatTagList.begin(); mChatTagIt != mChatTagList.end();++mChatTagIt)
		{
			if (*mChatTagIt&&((*mChatTagIt)->tagName.compare(tagName)==0))
			{
				return *mChatTagIt;
			}
		}
		return NULL;

	}
    //----------------------------------------------------------------------------------------
	std::list<ChatTag*> MessageManager::getChatTagList()
	{
		return mChatTagList;

	}
	/****************************************************************************************/

    //----------------------------------------------------------------------------------------
	void MessageManager::setSelectChannel( CChar16* selectChannel )
	{
		ChannelInfo * tempChannel = ChannelInfos::getInstance().getChannelInfo(selectChannel);
		if (tempChannel)
            mSelectChannel = tempChannel;

	}
    //----------------------------------------------------------------------------------------
	void MessageManager::setSelectChatTag( CChar16* selectChatTag )
	{
		ChatTag* tempChatTag  = getChatTagByName(selectChatTag);
		if (tempChatTag)
		{
            mSelectChatTag   = tempChatTag;
		}
		

	}
   //----------------------------------------------------------------------------------------
	 ChannelInfo* MessageManager::getSelectChannel()
	{
          return mSelectChannel;

	}
   //----------------------------------------------------------------------------------------
	ChatTag* MessageManager::getSelectChatTag()
	{
        return mSelectChatTag;
	}
	//----------------------------------------------------------------------------------------
	
   //----------------------------------------------------------------------------------------
	void MessageManager::sendChatMsg( Str16& chatData,CChar16* receiveClanName)
	{
		CClan* clan = CPlayer::getInstance().getActiveClan();
		Str16  tempSenderName = clan->getClanHomeLandName() + clan->getName() + Str16(L"氏");
		if (!clan)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		if (chatData.size() < 1)
		{
			return;
		}
        Char16* msg = (Char16*)chatData.c_str();

		if (WStrLen(msg) < 1)
		{
			return;
		}

		ChannelInfo* channelInfo =MessageManager::getInstance().getChannelInfoByInsruct(msg);
		if (!channelInfo)
		{
			//isInsruct = true;
			channelInfo = MessageManager::getInstance().getSelectChannel();
		}

		//根据广播范围进行发包
		switch(channelInfo->broadcast)
		{
		case chat_full_server:
			{   
                //发送间隔判断
				static U32 lastFullServerChatTick = 0;
				static U32 fullServerChatInterval = channelInfo->interval;
				U32   currentFullServerChatTick = 0;
				
                
				if (lastFullServerChatTick > 0)
				{
					currentFullServerChatTick = MGTimeOp::getCurrTick();
					if (currentFullServerChatTick - lastFullServerChatTick <= fullServerChatInterval*100)
					{
                        addChatMsg(channelInfo->id,L"",L"你的聊天速度太快!",9);
						return;
					}

				}
				
				//检查非法字
				 if (BanKeyword<BanKeywordEnter>::getInstance().isBan(msg))
				 {
					 addChatMsg(channelInfo->id,L"",L"输入中有非法字符!",9);
					 return;
				 }
				//过滤屏蔽字
				BanKeyword<BanKeywordShow>::getInstance().EditReplaceBan(msg);
				ChatNetPacketProcesser::getInstance().sendFullServerChatToFrontServer(channelInfo->id,tempSenderName.c_str(),(Char8*)msg,(WStrLen(msg)+1) * sizeof(Char16));

				/*lastFullServerChatTick = MGTimeOp::getCurrTick();*/

			}
			break;
		case chat_one_world:
			{

			}
			break;
		case chat_one_zhou:
			{

			}
			break;
		case chat_one_jun:
			{

			}
			break;
		case chat_one_xian:
			{

			}
			break;
		case chat_one_city:
			{

			}
			break;
		case chat_one_force:
			{

			}
			break;
		case chat_one_alliance:
			{

			}
			break;
		case chat_one_group:
			{

			}
			break;
		case chat_two_person:
			{
				
				//发送间隔判断
				static U32 lastTwoPersonChatTick = 0;
				static U32 lastTwoPersonInterval = channelInfo->interval;
				U32   currentlastTwoPersonChatTick = 0;
				if (lastTwoPersonChatTick > 0)
				{
					currentlastTwoPersonChatTick = MGTimeOp::getCurrTick();
					if (currentlastTwoPersonChatTick - lastTwoPersonChatTick <= lastTwoPersonInterval*100)
					{
						addChatMsg(channelInfo->id,L"",L"你的聊天速度太快!",9);
						return;
					}

				}
				
				//
                I32 tempDataSize = 0;
				I32 tempReceiveClanNameSize = 0;
				Char16 tempReceiveClanName[MAX_CLAN_NAME];
				memset(tempReceiveClanName, 0, sizeof(tempReceiveClanName));
				tempReceiveClanNameSize = WcsStr(msg,L" ") - msg;
				
				if ( tempReceiveClanNameSize <0 )   //没有发送者
				{
					return;
				}

                WStrnCpyS(tempReceiveClanName,msg,tempReceiveClanNameSize);
				//wcscpy(tempReceiveClanName, msg);
				msg = msg + tempReceiveClanNameSize + 1;

				if (msg[0] == 0 || msg == NULL)  //没有内容
				{
					return;
				}
				//检查非法字
				if (BanKeyword<BanKeywordEnter>::getInstance().isBan(msg))
				{
					addChatMsg(channelInfo->id,L"",L"输入中有非法字符!",9);
					return;
				}
				//过滤屏蔽字
				BanKeyword<BanKeywordShow>::getInstance().EditReplaceBan(msg);
                tempDataSize = (WStrLen(msg)+1) * sizeof(Char16);
				
				
				ChatNetPacketProcesser::getInstance().sendTwoPersonChatToFrontServer(
					channelInfo->id,tempSenderName.c_str(),tempReceiveClanName,(Char8*)msg,tempDataSize);

				//本地显示自己所发信息
				addChatMsg(channelInfo->id,tempSenderName.c_str(),msg,tempDataSize);
			}
			break;
		case chat_one_region:
			{
				//发送间隔判断
				static U32 lastOneRegionChatTick = 0;
				static U32 oneRegionInterval = channelInfo->interval;
				U32   currentOneRegionChatTick = 0;
				if (lastOneRegionChatTick > 0)
				{
					currentOneRegionChatTick = MGTimeOp::getCurrTick();
					if (currentOneRegionChatTick - lastOneRegionChatTick <= oneRegionInterval*100)
					{
						addChatMsg(channelInfo->id,L"",L"你的聊天速度太快!",9);
						return;
					}

				}


				//检查非法字
				if (BanKeyword<BanKeywordEnter>::getInstance().isBan(msg))
				{
					addChatMsg(channelInfo->id,L"",L"输入中有非法字符!",9);
					return;
				}
				//过滤屏蔽字
				BanKeyword<BanKeywordShow>::getInstance().EditReplaceBan(msg);
				ChatNetPacketProcesser::getInstance().sendOneRegionChatToFrontServer(
					channelInfo->id,tempSenderName.c_str(),clan->getMainGenreal()->getRegionID(),clan->getMainGenreal()->getRegionType(),(Char8*)msg,(WStrLen(msg)+1) * sizeof(Char16));

				lastOneRegionChatTick = MGTimeOp::getCurrTick();
			}
			break;
		case chat_one_view:
			{

			}
			break;
		default:
			{
				DYNAMIC_ASSERT(false);
			}
			break;
		}

	}

	 ChannelInfo* MessageManager::getChannelInfoByInsruct( Char16* &msg )
	{
          return ChannelInfos::getInstance().getChatInfoByInstruct(msg);
         
	}

	MG::Bool MessageManager::addRecChatDateToList( RecChatData *data )
	{
         if (!data)
			 return false;
        if (mRecChatDataList.empty()||(mRecChatDataList.size()<MAX_CHAT_CONTENT_ROW_COUNT))
        {
			mRecChatDataList.push_back(data);

			/*测试
            mRecChatDataIt = mRecChatDataList.begin();
			CChar16* msg = (CChar16*)((*mRecChatDataIt)->data);
			int i = 0;*/
        }
		else
		{
			deletecContentRow();
            mRecChatDataList.push_back(data);
			refreshChatData(true);
            
         
		} 
		 return true;

	}

	void MessageManager::addChatMsg( U32 channelid,CChar16* dataSender,Char16* data,I32 count )
	{
		
		UIChatCommonShow::getInstance().addChatMsg(channelid,dataSender,data,count);
		
	}

	std::list<RecChatData*> MessageManager::getRefreshChatData()
	{
         std::list<RecChatData*>  tempRecChatDataList;
		 if (mSelectChatTag)
		 {
             std::vector<U32>  tempChannelList = mSelectChatTag->channelList;
			 for (std::vector<U32>::iterator It = tempChannelList.begin(); It != tempChannelList.end(); ++It)
             {
                   for (mRecChatDataIt = mRecChatDataList.begin();mRecChatDataIt != mRecChatDataList.end(); ++mRecChatDataIt)
                   {
                          if ((*It)==(*mRecChatDataIt)->channelid)
                          { 
                              tempRecChatDataList.push_back(*mRecChatDataIt);
                          }
                   }
             }
		 }

		 return tempRecChatDataList;

	}

    //----------------------------------------------------------------------------------------
	std::list<ChannelInfo*> MessageManager::getChannelInfoByUseType( const I32& useType )
 	{
		return ChannelInfos::getInstance().getChannelInfoByUseType(useType);
	}

	ChannelInfo* MessageManager::getChannelInfo( CChar16 *channelName )
	{
		return ChannelInfos::getInstance().getChannelInfo(channelName);

	}

	ChannelInfo* MessageManager::getChannelInfo( U32 chatId )
	{
		return ChannelInfos::getInstance().getChannelInfo(chatId);

	}
	std::list<ChannelInfo*> MessageManager::getChannelInfoByShowType( const I32& useType )
	{
      return ChannelInfos::getInstance().getChannelInfoByShowType(useType);
	}
     //----------------------------------------------------------------------------------------


	void MessageManager::clear()
	{
        if (!mChatTagList.empty())
        {
			for( mChatTagIt = mChatTagList.begin();mChatTagIt != mChatTagList.end(); ++mChatTagIt )
			{
				MG_SAFE_DELETE(*mChatTagIt);
			}
            mChatTagList.clear();

        }
		if (!mRecChatDataList.empty())
		{
			for ( mRecChatDataIt = mRecChatDataList.begin(); mRecChatDataIt != mRecChatDataList.end(); ++mRecChatDataIt)
			{
				MG_SAFE_DELETE(*mRecChatDataIt);
			}
            mRecChatDataList.clear();
		}
	}
	//----------------------------------------------------------------------------------------
	void MessageManager::addChatMsgForTest( Char* data, ... )
	{
		va_list vl;
		static Char msg[1024*40] = { 0 }; 

		va_start( vl, data );
		vsprintf_s( msg, sizeof(msg), data, vl );
		va_end( vl );
       
		Str16 sendData;
		MGStrOp::toString(msg,sendData);
        		
		UIChatCommonShow::getInstance().addChatMsgForTest( const_cast<Char16*>(sendData.c_str()));
	}

	void MessageManager::addChatMsgForTest( Char16* data, ... )
	{
		va_list vl;
		static Char16 msg[1024*4];

		va_start( vl, data );
		vswprintf_s( msg, sizeof(msg), data, vl );
		va_end( vl );

		Str16 sendData = msg;

		UIChatCommonShow::getInstance().addChatMsgForTest( const_cast<Char16*>(sendData.c_str()));
	}

   //----------------------------------------------------------------------------------------
	void MessageManager::deletecContentRow()
	{
		U32 i = 0;
		std::list<RecChatData*>::iterator front = mRecChatDataList.begin();
		std::list<RecChatData*>::iterator back = mRecChatDataList.end();
        std::list<RecChatData*>::iterator tempIterator;
		while( front != back && i< CHAT_CONTENT_ONCE_DELETE_COUNT )
		{
            
			MG_SAFE_DELETE(*front);
			tempIterator = front;
			front++;
			mRecChatDataList.erase(tempIterator);
			i++;
		}
	}
	//----------------------------------------------------------------------------------------
	void MessageManager::refreshChatData( Bool isAuto )
	{
		if(isAuto)
		{
            UIChatCommonShow::getInstance().clearCommonArea();
            UIChatCommonShow::getInstance().clearLaBaArea();
			_refreshChatData(isAuto);
		}
		else
		{
           UIChatCommonShow::getInstance().clearCommonArea();
		   _refreshChatData(isAuto);

		}

	}
	//----------------------------------------------------------------------------------------
	void MessageManager::_refreshChatData(Bool isAuto)
	{
		std::list<RecChatData*>::iterator front = mRecChatDataList.begin(); 
		std::list<RecChatData*>::iterator back = mRecChatDataList.end();
		while( front != back)
		{
			if (isAuto)    //更新普通显示区域 和 喇叭显示区域
			{
                
				UIChatCommonShow::getInstance().addChatMsg((*front)->channelid,(*front)->dataSender,(Char16*)((*front)->data),(*front)->dataSize);
			}
			else         //只更新普通区域
			{
                ChannelInfo* templeChannelInfo = MessageManager::getInstance().getChannelInfo((*front)->channelid);
				if (templeChannelInfo->showPlace != 3)  //排除喇叭频道
				{
                   UIChatCommonShow::getInstance().addChatMsg((*front)->channelid,(*front)->dataSender,(Char16*)((*front)->data),(*front)->dataSize);
				}


			}
			front++;
		}

	}
	//----------------------------------------------------------------------------------------
	MG::Int MessageManager::getRecChatDataListSize() const
	{
		return mRecChatDataList.size();
	}
	//----------------------------------------------------------------------------------------
	void MessageManager::addChatResultMsg( U32 channelid,Byte result,Char16* data,I32 count )
	{
      

	}
	//----------------------------------------------------------------------------------------
	void MessageManager::setAllServerChatInterval( const U32 serverChatInterval )
	{
		mAllServerChatInterval = serverChatInterval;
	}
	//----------------------------------------------------------------------------------------
	void MessageManager::setOneRegionChatInterval( const U32 oneRegionChatInterval )
	{
       mOneRegionChatInterval = oneRegionChatInterval;
	}
	//----------------------------------------------------------------------------------------
	MG::U32 MessageManager::getAllServerChatInterval() const
	{
            return mAllServerChatInterval;
	}
	//----------------------------------------------------------------------------------------
	MG::U32 MessageManager::getOneRegionChatInterval() const
	{
            return mOneRegionChatInterval;
	}

}

