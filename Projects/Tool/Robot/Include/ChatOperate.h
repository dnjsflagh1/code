/******************************************************************************/
#ifndef _CHATOPERATE_H_
#define _CHATOPERATE_H_
/******************************************************************************/
#include "ChannelInfo.h"

namespace MG
{
        
		class ChatOperate : public BaseOperate
         {
         public:
			 ChatOperate(OperateManager* mgr,CClient* client,CClientMessage* msg,OperateType type);
			 ~ChatOperate(){;}
              
			 virtual Bool        onEnter();
			 virtual Bool		 isFinish();
			 virtual void        onNetEvent(Byte channel,Byte type,void* data);
			 virtual void        onLeave();
			 virtual void		 onCloseByLoginServer();
			 virtual void		 onCloseByFrontServer();
			 //
		 public:
			  U32					 mEnterTick;				//��������ʱ��
			  static U32			 mIntervalTime;			    //��ͨƵ��,����Ƶ��ֵ��ͬ,�ⲿ�趨
			  static I32			 mSize;
			  static ChannelInfo*    mSelectChannelInfo;

         };



}


//
#endif