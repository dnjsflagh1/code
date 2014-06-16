//***************************************************************************************************
#include "stdafx.h"
#include "UIChatSendMsg.h"
#include "ChannelInfo.h"
#include "ChatNetPacket.h"
#include "ChatNetPacketProcesser.h"
#include "MessageManager.h"
#include "CSceneManager.h"
#include "CPlayerCharacterEntity.h"
#include "CPlayer.h"
//***************************************************************************************************
namespace MG
{


UIChatSendMsg::UIChatSendMsg()
          
{

}
//----------------------------------------------------------------------------------------
UIChatSendMsg::~UIChatSendMsg()
{


}

//----------------------------------------------------------------------------------------
MG::Bool UIChatSendMsg::initComboItem(IComboBox* icombo)
{
	std::list<ChannelInfo*>   tempListChannelInfo;
    

	/*判断玩家权限 普通orGM
	
	*/
	//普通玩家权限:

	tempListChannelInfo = MessageManager::getInstance().getChannelInfoByUseType(chat_read_write);
	if (tempListChannelInfo.empty())
	   return false;

	
	for (std::list<ChannelInfo*>::iterator it=tempListChannelInfo.begin();it!=tempListChannelInfo.end();++it)
	{
		//暂时只提供大喊频道 私聊 全服喇叭
		if ((*it)->fullName.compare(L"大喊") == 0)
		{
             icombo->addItem((*it)->fullName);
		}
		else if ((*it)->fullName.compare(L"全服") == 0)
		{
             icombo->addItem((*it)->fullName);
		}
		else if ((*it)->fullName.compare(L"密语") == 0)
		{
             icombo->addItem((*it)->fullName);
		}
        
	}
	icombo->setIndexSelected(0);
	Str16 tempName = icombo->getItemNameAt(0);

	MessageManager::getInstance().setSelectChannel(tempName.c_str());
	return true;

}
//----------------------------------------------------------------------------------------
void UIChatSendMsg::setEvent()
{
   IComboBox* icombobox = getInstance().getLayout()->getComboBox("comboChannelType");
   if (!initComboItem(icombobox))
      return;
   icombobox->setComboAcceptEvent(onComboAccept);
   icombobox->setComboChangePositionEvent(onComboChangePosition);

   getLayout()->getButton("btnSend")->getWidget()->setMouseButtonClickEvent(onSend);
   getLayout()->getEdit("edtMsg")->setSelectAcceptEvent(onSelectAcceptEvent);

}
//----------------------------------------------------------------------------------------
void UIChatSendMsg::onComboChangePosition( void* widget,Int i )
{
	IComboBox* icombobox = getInstance().getLayout()->getComboBox("comboChannelType");
	ChannelInfo * tempChannel=NULL;
	if (widget)
	{
		MG::Str16 channelName = icombobox->getItemNameAt(icombobox->getIndexSelected());
		MessageManager::getInstance().setSelectChannel(channelName.c_str());
	}
	
}
//----------------------------------------------------------------------------------------
void UIChatSendMsg::onComboAccept( void* widget,Int i )
{
}
//----------------------------------------------------------------------------------------
void UIChatSendMsg::onSend( void* widget )
{
	if(widget)
	{ 
		UIChatSendMsg::getInstance().sendMsg();
	}

}

//----------------------------------------------------------------------------------------
void UIChatSendMsg::update(Flt delta)
{

}
//----------------------------------------------------------------------------------------
MG::Bool UIChatSendMsg::openGui()
{
	return UIObject::openGui();
}

void UIChatSendMsg::restore()
{
	IComboBox* icombo = getInstance().getLayout()->getComboBox("comboChannelType");
	//暂时屏蔽频道选择功能
	icombo->setIndexSelected(0);
	Str16 tempName = icombo->getItemNameAt(0);
	MessageManager::getInstance().setSelectChannel(tempName.c_str());


}

void UIChatSendMsg::onSelectAcceptEvent( void* widget )
{
    if (widget)
    {
		UIChatSendMsg::getInstance().sendMsg();
    }

}

void UIChatSendMsg::sendMsg()
{

	
	Str16 chatData = UIChatSendMsg::getInstance().getLayout()->getEdit("edtMsg")->getWidget()->getCaption();
	MessageManager::getInstance().sendChatMsg(chatData);
	UIChatSendMsg::getInstance().getLayout()->getEdit("edtMsg")->clearEditText(false);
	//UIChatSendMsg::getInstance().getLayout()->getEdit("edtMsg")->getWidget()->setCaption(L"");

}
//----------------------------------------------------------------------------------------
void UIChatSendMsg::setIputFocus()
{
	getLayout()->getEdit("edtMsg")->getWidget()->setKeyFocus(true);

}
//----------------------------------------------------------------------------------------


}