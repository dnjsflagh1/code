//***************************************************************************************************
#include "stdafx.h"
#include "UIChatMenu.h"
#include "ChannelInfo.h"
#include "ChatNetPacket.h"
#include "ChatNetPacketProcesser.h"

#include "CSceneManager.h"
#include "CPlayerCharacterEntity.h"
#include "CPlayer.h"
#include "HeadDes.h"
//***************************************************************************************************
namespace MG
{
    UIChatMenu::UIChatMenu()
		:mSelectChannel(NULL)
    {
		
    }
    //----------------------------------------------------------------------------------------
    UIChatMenu::~UIChatMenu()
    {

    }
    //----------------------------------------------------------------------------------------
    void UIChatMenu::setEvent()
    {
		IEdit* input = getLayout()->getEdit("edt_input");
		input->setSelectAcceptEvent(onSend);
    }
	//----------------------------------------------------------------------------------------
	void UIChatMenu::onSend( void* widget )
	{
		if (widget)
		{	
			Clan* clan = CPlayer::getInstance().getActiveClan();
			if (!clan)
			{
				DYNAMIC_ASSERT(false);
				return;
			}
			//---------------------------------------------------------------
			// �Ժ����� ���� ��ʾ �ỻ�ɸ����򣬻�õ�����ҲӦ�����
			// eg: Stream s = UIChatMenu::getInstance().getLayout()->getEdit("edt_input")->getWidget()->getCaption();
			// Ȼ��������н��������������У� ���ָ��,������ ������������ʱ��� ���йص�����
			// ...
			//---------------------------------------------------------------
			Str16 chatData = UIChatMenu::getInstance().getLayout()->getEdit("edt_input")->getWidget()->getCaption();
			
			Char16* msg = (Char16*)chatData.c_str();
			// ����������
			// ...
			ChannelInfo* channelInfo = UIChatMenu::getInstance().getChannelInfoByInsruct(msg);
			
			if (!channelInfo && !UIChatMenu::getInstance().mSelectChannel)
			{
				// ��ȡƵ�����ó���
				return;
			}
			// ����Ƶ�� ����Ȩ��,�ȼ�,��Ʒ ������
			// ...
			// ���ݹ㲥��Χ���з���
			

			switch(channelInfo->broadcast)
			{
			case chat_full_server:
				{

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
					if (channelInfo && channelInfo != UIChatMenu::getInstance().getSelectChannelInfo())
					{
						UIChatMenu::getInstance().setCurrentChannel(channelInfo);
						return;
					}
					Str16 name = UIChatMenu::getInstance().getLayout()->getEdit("edt_name")->getWidget()->getCaption();
					if (name.empty())
					{
						//����������
						//...
					}
					ChatNetPacketProcesser::getInstance().sendTwoPersonChatToFrontServer(
						channelInfo->id,clan->getName().c_str(),name.c_str(),(Char8*)msg,(chatData.size() - channelInfo->instruct.size() + 1) * sizeof(Char16));
				}
				break;
			case chat_one_region:
				{

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
	}
	//----------------------------------------------------------------------------------------
	Bool UIChatMenu::openGui()
	{
		return UIObject::openGui();
	}
	//----------------------------------------------------------------------------------------
	void UIChatMenu::addChatMsg( Byte channelId,CChar16* senderName,Char16* data, I32 count)
	{
		//����Ƶ���ڶ�Ӧ�� �������������Ϣ
		Str16 temp = senderName;
		temp += L"˵��";
		temp += data;
		temp += L"\n";
		getInstance().getLayout()->getEdit("edt_ChatPain")->addText(temp);
	
			//TODO: TEST
			//
			/*CClan* clan = CPlayer::getInstance().getActiveClan();
			if (clan)
			{
				CPlayerCharacter* charcter = clan->getMainGenreal();
				if (charcter)
				{
					if (charcter && charcter->getID())
					{
						CPlayerCharacterEntity* entry = CSceneManager::getInstance().getPlayerCharacterEntity(charcter->getID());
						if (entry)
						{
							HeadDes* headDes = entry->getHeadDes();
							if (headDes)
							{
								headDes->setSpeakContent(temp);
							}
						}
						
					}
				}
			}*/	


	}
	//----------------------------------------------------------------------------------------
	void UIChatMenu::onClickChannel( void* widget )
	{
		//mSelectChannel = 
	}
	//----------------------------------------------------------------------------------------
	ChannelInfo* UIChatMenu::getChannelInfoByInsruct( Char16* &msg )
	{
		return ChannelInfos::getInstance().getChatInfoByInstruct(msg);
	}
	//----------------------------------------------------------------------------------------
	ChannelInfo* UIChatMenu::getChannelInfo( Byte channel )
	{
		return ChannelInfos::getInstance().getChannelInfo(channel);
	}
	//----------------------------------------------------------------------------------------
	void UIChatMenu::setCurrentChannel( ChannelInfo* channelInfo )
	{
		mSelectChannel = channelInfo;
		
		//�����������
		//...
	}
	//----------------------------------------------------------------------------------------
	ChannelInfo* UIChatMenu::getSelectChannelInfo()
	{
		return mSelectChannel;
	}
	//----------------------------------------------------------------------------------------
}