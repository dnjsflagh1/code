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
			  U32					 mEnterTick;				//操作进入时间
			  static U32			 mIntervalTime;			    //普通频道,特殊频道值不同,外部设定
			  static I32			 mSize;
			  static ChannelInfo*    mSelectChannelInfo;

         };



}


//
#endif