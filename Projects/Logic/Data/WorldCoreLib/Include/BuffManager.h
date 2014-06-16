//******************************************************************************************************
#ifndef _H_BUFF_MANAGER_
#define _H_BUFF_MANAGER_
//******************************************************************************************************
#include "WorldCorePreqs.h"
//******************************************************************************************************
#define  BUFF_OBJ_NUM 24
namespace MG
{
	class BuffManager
	{
	public:
		BuffManager(void* parent);
		virtual ~BuffManager();

	public:
		void	init();
		void	update(Flt delta);
		void	clear();			

	public:
		virtual BuffObject* 
				createBuff(STATUS_TYPE type) = 0;
		//此函数是用来新添加BUff。
		void	addNewBuff(UInt buffId, UInt addNum, UInt objLvl);
		//此函数是添加已经确定的buff，不需要做任何判断。
		void	addOldBuff(UInt buffId, UInt timeUse, UInt addNum);
		//根据Id来删除buff。
		void	deleteBuff(UInt buffId);
		
		//----------------------------------------------------------------------------------
		template <typename T>
		T*		findBuffBySlotId(UInt buffSlotId)
		{
			DYNAMIC_ASSERT(buffSlotId > 0  &&  buffSlotId <=BUFF_OBJ_NUM);
			
			std::map<UInt, BuffObject*>::iterator iter = mMapBuffObject.find(buffSlotId);
			if ( iter != mMapBuffObject.end() )
				return dynamic_cast<T*>(iter->second);

			return NULL;
		}
		//----------------------------------------------------------------------------------
		template <typename T>
		T*		findBuffByBuffId(UInt buffId)
		{
			const StatusData* pStatusData = StatusList::getInstance().getStatusData(buffId);
			DYNAMIC_ASSERT(pStatusData);

			std::map<UInt, BuffObject*>::iterator iter = mMapBuffObject.find(pStatusData->mpStatusBaseInfo->SlotNum);
			if ( iter != mMapBuffObject.end() )
				return dynamic_cast<T*>(iter->second);

			return NULL;
		}

	public:
		template <typename T>
		T*	getParent()
		{
			DYNAMIC_ASSERT(mParent);

			return (T*)mParent;
		}

	protected:
		void* getVoidParent(){return mParent;}
		void	deleteBuff(std::map<UInt, BuffObject*>::iterator& iter, Bool isCal = true);

	protected:
		std::map<UInt, BuffObject*>			mMapBuffObject;
		void*								mParent;
	};
}
//******************************************************************************************************
#endif
//******************************************************************************************************