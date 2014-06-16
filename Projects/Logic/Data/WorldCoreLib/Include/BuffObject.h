//******************************************************************************************************
#ifndef _H_BUFF_Object_
#define _H_BUFF_Object_
//******************************************************************************************************
#include "WorldCorePreqs.h"
#include "BuffData.h"
//******************************************************************************************************
namespace MG
{
	class BuffObject
	{
	public:
		BuffObject(){;}
		virtual ~BuffObject(){;}

	public:
		void			init( const StatusData* pStatusData, Int timeUse, Int addNum );
		void			clear(Bool isCal = true);
		Bool			update(Flt delta);

	public:
		//此函数是用来新添加BUff。
		void			addBuff( const StatusData* pStatusData, UInt addNum );
		//此函数是添加已经确定的buff，不需要做任何判断。
		void			addBuff( const StatusData* pStatusData, Int timeUse, Int addNum );

		BuffData*		getBuffData(){return &mBuffData;}

		template		<typename T>
		const T*		getBuffTmpData()
		{
			return mBuffData.getStatusBaseInfo<T>();
		}

		Bool			isClear(){return mBuffData.isClear();}
		//计算属性
		virtual void	calAttrBase(){;}

	protected:
		virtual	void	updateBuffOther(Flt delta) = 0;
		virtual void	clearBuffOther(Bool isCal = true) = 0;
		virtual void	addBuffOther() = 0;
		virtual void	initBuffOther(const StatusData* pStatusData, Int timeUse) = 0;

	private:
		Bool			checkCanAdd( const StatusData* pStatusData, UInt& addNum );

	private:
		BuffData				mBuffData;

	};
}
//******************************************************************************************************
#endif
//******************************************************************************************************