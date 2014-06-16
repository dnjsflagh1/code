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
		//��̬��ȡchat_tag_name
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
		//û��������Ϣʱ ����ʾ���������ͼ
		IWidget* panel = getLayout()->getWidget("panel_laba");
		panel->setVisible(false);
		
		//�õ���������Ƶ����Ϣ
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
        
		
		//�ж�channelID�ǰ�����ѡ���ı�ǩ��
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
				//ȫ�����Ƚ���λ��
				IWidget* panel = getLayout()->getWidget("panel_laba");
				panel->setVisible(true);
				Int editWidth = getEditBoxWidth(SHOW_PLACE_LABA);
				Str16 temp;
				if (dataSender != L"")
				{
					temp = dataSender;
					temp += L"��";
				}
				temp += data;
				getWidthStrAddBreak(temp,editWidth);
				temp += L"\n";
				//������ɫ����������λ��
				U32 colourPos = getTextLength(SHOW_PLACE_LABA);
				getInstance().getLayout()->getEdit("text_laba")->addText(temp);
				setTextColour(colourPos,WStrLen(temp.c_str()),templeChannelInfo->color,SHOW_PLACE_LABA);

			}
			break;
		case 4:
			{
				// �������λ��
				if (MessageManager::getInstance().getSelectChatTag() != NULL)
				{
					if(MessageManager::getInstance().getSelectChatTag()->channelInfoExist(channelId))
					 {
                          Int editWidth = getEditBoxWidth(SHOW_PLACE_COMMON);
						  Str16 temp;
						  if (dataSender != L"")
						  {
							  temp = dataSender;
							  temp += L"��";
						  }
						  temp += data;
                          getWidthStrAddBreak(temp,editWidth);
						  temp += L"\n";
						  //������ɫ����������λ��
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
				// �������λ��
				if (MessageManager::getInstance().getSelectChatTag() != NULL)
				{
					if(MessageManager::getInstance().getSelectChatTag()->channelInfoExist(channelId))
					{
						Int editWidth = getEditBoxWidth(SHOW_PLACE_COMMON);
						Str16 temp;
						if (dataSender != L"")
						{
							temp = dataSender;
							temp += L"��";
						}
						temp += data;
						getWidthStrAddBreak(temp,editWidth);
						temp += L"\n";
						//������ɫ����������λ��
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
		Str16 temp = L"������Ϣ";
		temp += L"��";
		temp += data;
		//getInstance().getLayout()->getEdit("edtShow")->addText(temp);
		
		//
		Int editWidth = getEditBoxWidth(SHOW_PLACE_COMMON);
		getWidthStrAddBreak(temp,editWidth);
		temp += L"\n";
		//������ɫ����������λ��
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
