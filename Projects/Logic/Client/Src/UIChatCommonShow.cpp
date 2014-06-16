//***************************************************************************************************
#include "stdafx.h"
#include "UIChatCommonShow.h"
#include "ChannelInfo.h"
#include "ChatNetPacket.h"
#include "ChatNetPacketProcesser.h"
#include "MessageManager.h"
#include "MessageData.h"
#include "CSceneManager.h"
#include "CPlayerCharacterEntity.h"
#include "CPlayer.h"
#include "ClientMain.h"
//***************************************************************************************************
namespace MG
{

    //----------------------------------------------------------------------------------------
	UIChatCommonShow::UIChatCommonShow()
		:mChatfplatecfg(NULL)
	{
		

	}
	//----------------------------------------------------------------------------------------
	UIChatCommonShow::~UIChatCommonShow()
	{
        MG_SAFE_DELETE(mChatfplatecfg);
	}
	//----------------------------------------------------------------------------------------
	void UIChatCommonShow::setEvent()
	{

       InitDefaultFaceplate();
	   getLayout()->getButton("btnComplex")->getWidget()->setMouseButtonClickEvent(onChangeTag);

	}

	//----------------------------------------------------------------------------------------
	void UIChatCommonShow::onChangeTag( void* widget )
	{
		//动态获取chat_tag_name
		Str16 chatTagName = L"ZH";
		MessageManager::getInstance().setSelectChatTag(chatTagName.c_str());
		std::list<RecChatData*>  tempRecChatDataList = MessageManager::getInstance().getRefreshChatData();
		if (!tempRecChatDataList.empty())
		{
			for (std::list<RecChatData*>::iterator It = tempRecChatDataList.begin(); It != tempRecChatDataList.end();++It)
				UIChatCommonShow::getInstance().addChatMsg((*It)->channelid,(CChar16*)((*It)->dataSender),((Char16*)((*It)->data)),(*It)->dataSize);    
		}


	}

	//----------------------------------------------------------------------------------------
	void UIChatCommonShow::onRightClickTag( void* widget )
	{

	}

	//----------------------------------------------------------------------------------------
	Bool UIChatCommonShow::openGui()
	{
		return UIObject::openGui();

	} 

	//----------------------------------------------------------------------------------------
	void UIChatCommonShow::InitDefaultFaceplate()
	{
		//没有喇叭信息时 不显示喇叭区域底图
		IWidget* panel = getLayout()->getWidget("panel_laba");
		panel->setVisible(false);
		
		//得到所有聊天频道信息
		std::list<ChannelInfo*> tempChannelInfoList = MessageManager::getInstance().getChannelInfoByShowType(4);
		 if (MessageManager::getInstance().addChatTag(L"ZH"))
		 {
			 if (tempChannelInfoList.empty())
				 return;
			 else
			 {
                 ChatTag *tempChatTag=MessageManager::getInstance().getChatTagByName(L"ZH");
				 for (std::list<ChannelInfo*>::iterator it=tempChannelInfoList.begin();it!=tempChannelInfoList.end();it++)
				 {
					 if (*it)
					 {

						tempChatTag->addChatInfoID((*it)->id);
					 }
				 }

				 MessageManager::getInstance().setSelectChatTag(tempChatTag->tagName.c_str());
			 }
		 }

	}
	//----------------------------------------------------------------------------------------
	void UIChatCommonShow::addChatMsg( Byte channelId,CChar16* dataSender,Char16* data,I32 count )
	{
        
		
		//判断channelID是包含在选定的标签内
		ChannelInfo* templeChannelInfo = MessageManager::getInstance().getChannelInfo(channelId);
        switch(templeChannelInfo->showPlace)
		{
		case 1:
			{

			}
			break;
		case 2:
			{

			}
			break;
		case 3:
			{
				//全服喇叭界面位置
				IWidget* panel = getLayout()->getWidget("panel_laba");
				panel->setVisible(true);
				Int editWidth = getEditBoxWidth(SHOW_PLACE_LABA);
				Str16 temp;
				if (dataSender != L"")
				{
					temp = dataSender;
					temp += L"：";
				}
				temp += data;
				getWidthStrAddBreak(temp,editWidth);
				temp += L"\n";
				//计算颜色特征码插入的位置
				U32 colourPos = getTextLength(SHOW_PLACE_LABA);
				getInstance().getLayout()->getEdit("text_laba")->addText(temp);
				setTextColour(colourPos,WStrLen(temp.c_str()),templeChannelInfo->color,SHOW_PLACE_LABA);

			}
			break;
		case 4:
			{
				// 聊天界面位置
				if (MessageManager::getInstance().getSelectChatTag() != NULL)
				{
					if(MessageManager::getInstance().getSelectChatTag()->channelInfoExist(channelId))
					 {
                          Int editWidth = getEditBoxWidth(SHOW_PLACE_COMMON);
						  Str16 temp;
						  if (dataSender != L"")
						  {
							  temp = dataSender;
							  temp += L"：";
						  }
						  temp += data;
                          getWidthStrAddBreak(temp,editWidth);
						  temp += L"\n";
						  //计算颜色特征码插入的位置
						  U32 colourPos = getTextLength(SHOW_PLACE_COMMON);
						  getInstance().getLayout()->getEdit("edtShow")->addText(temp);
						  setTextColour(colourPos,WStrLen(temp.c_str()),templeChannelInfo->color,SHOW_PLACE_COMMON);

					 }
				}

			}
			break;
		default:
			{
				//DYNAMIC_ASSERT(false);
				// 聊天界面位置
				if (MessageManager::getInstance().getSelectChatTag() != NULL)
				{
					if(MessageManager::getInstance().getSelectChatTag()->channelInfoExist(channelId))
					{
						Int editWidth = getEditBoxWidth(SHOW_PLACE_COMMON);
						Str16 temp;
						if (dataSender != L"")
						{
							temp = dataSender;
							temp += L"：";
						}
						temp += data;
						getWidthStrAddBreak(temp,editWidth);
						temp += L"\n";
						//计算颜色特征码插入的位置
						U32 colourPos = getTextLength(SHOW_PLACE_COMMON);
						getInstance().getLayout()->getEdit("edtShow")->addText(temp);
						setTextColour(colourPos,WStrLen(temp.c_str()),templeChannelInfo->color,SHOW_PLACE_COMMON);

					}
				}
			}
			break;
		}	

	}
	//----------------------------------------------------------------------------------------
	void UIChatCommonShow::restore()
	{
		MessageManager::getInstance().clear();
		clearCommonArea();
		clearLaBaArea();
        InitDefaultFaceplate();
 
	}
	//----------------------------------------------------------------------------------------
	void UIChatCommonShow::addChatMsgForTest( Char16* data )
	{
		Str16 temp = L"测试信息";
		temp += L"：";
		temp += data;
		//getInstance().getLayout()->getEdit("edtShow")->addText(temp);
		
		//
		Int editWidth = getEditBoxWidth(SHOW_PLACE_COMMON);
		getWidthStrAddBreak(temp,editWidth);
		temp += L"\n";
		//计算颜色特征码插入的位置
		U32 colourPos = getTextLength(SHOW_PLACE_COMMON);
		U32 maxTextLenght = getInstance().getLayout()->getEdit("edtShow")->getMaxTextLength();
		if (colourPos + editWidth >= maxTextLenght)
		{
			getInstance().getLayout()->getEdit("edtShow")->clearEditText(false);
			//getInstance().getLayout()->getEdit("edtShow")->getWidget()->setCaption(L"");
		}
		getInstance().getLayout()->getEdit("edtShow")->addText(temp);
		Color color(255,0,0);
		setTextColour(colourPos,WStrLen(temp.c_str()),color,SHOW_PLACE_COMMON);

	}
	//----------------------------------------------------------------------------------------
	void UIChatCommonShow::clearCommonArea()
	{
		//getInstance().getLayout()->getEdit("edtShow")->getWidget()->setCaption(L"");
		getInstance().getLayout()->getEdit("edtShow")->clearEditText(false);

	}
	//----------------------------------------------------------------------------------------
	void UIChatCommonShow::clearLaBaArea()
	{
		//getInstance().getLayout()->getEdit("text_laba")->getWidget()->setCaption(L"");
		getInstance().getLayout()->getEdit("text_laba")->clearEditText(false);
	}
    //----------------------------------------------------------------------------------------
	void UIChatCommonShow::setTextColour( Int _start, Int _count, const Color& value,SHOW_PLACE _showplace )
	{
         if (_showplace == SHOW_PLACE_COMMON )
         {
             getInstance().getLayout()->getEdit("edtShow")->setTextIntervalColour(_start,_count,value);
         }
		 else if (_showplace == SHOW_PLACE_LABA )
		 {
			getInstance().getLayout()->getEdit("text_laba")->setTextIntervalColour(_start,_count,value);
		 }

	}
	 //----------------------------------------------------------------------------------------
	MG::U32 UIChatCommonShow::getTextLength( SHOW_PLACE _showplace )
	{
        if (_showplace == SHOW_PLACE_COMMON )
		{
           return getInstance().getLayout()->getEdit("edtShow")->getTextLength();
		}
		 else if (_showplace == SHOW_PLACE_LABA )
		 {
			return getInstance().getLayout()->getEdit("text_laba")->getTextLength();
		}
	}
	 //----------------------------------------------------------------------------------------
	MG::U32 UIChatCommonShow::getWidthStrAddBreak( Str16& src, Int width, Str8 fontName )
	{
		IGui* igui = ClientMain::getInstance().getGui();
		return igui->getHeightStrAddBreak(src,width,fontName);

	}
	 //----------------------------------------------------------------------------------------
	MG::Int UIChatCommonShow::getEditBoxWidth( SHOW_PLACE _showplace )
	{
		if (_showplace == SHOW_PLACE_COMMON )
		{
			return (static_cast<Int>(getInstance().getLayout()->getEdit("edtShow")->getWidget()->getSize().x) - 30);
		}
		else if (_showplace == SHOW_PLACE_LABA )
		{
			return (static_cast<Int>(getInstance().getLayout()->getEdit("text_laba")->getWidget()->getSize().x) - 30);
		}
	}
	 //----------------------------------------------------------------------------------------
	MG::Int UIChatCommonShow::getEditBoxHeight( SHOW_PLACE _showplace )
	{
		if (_showplace == SHOW_PLACE_COMMON )
		{
			return static_cast<Int>(getInstance().getLayout()->getEdit("edtShow")->getWidget()->getSize().y);
		}
		else if (_showplace == SHOW_PLACE_LABA )
		{
			return static_cast<Int>(getInstance().getLayout()->getEdit("text_laba")->getWidget()->getSize().y);
		}
	}

	void UIChatCommonShow::addChatResultMsg( U32 channelid,Byte result,Char16* data,I32 count )
	{
       switch(result)
	   {
	   case chat_result_success:

		   break;
	   case chat_result_unknown:

		   break;
	   case chat_result_no_money:

		   break;
	   case chat_result_no_item:

		   break;
	   case chat_result_lack_of_item:

		   break;
	   case  chat_result_no_permission:

		   break;
	   case chat_result_level_limit:

		   break;
	   case chat_result_friend_absence:

		   break;
	   default:
		   {
			   DYNAMIC_ASSERT(0);
		   }
		   break;
	   }

	}
}
