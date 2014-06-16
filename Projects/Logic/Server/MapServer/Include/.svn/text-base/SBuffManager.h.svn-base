//***************************************************************************************
#ifndef _H_SBUFFMANAGER_
#define _H_SBUFFMANAGER_
//***************************************************************************************
#include "MapServerPreqs.h"
#include "BuffManager.h"
//***************************************************************************************
namespace MG
{
	class SBuffManager : public BuffManager
	{
	public:
		SBuffManager(void* parent);
		~SBuffManager();

	public:
		//根据相应类型创建buff对象。
		virtual BuffObject* createBuff(STATUS_TYPE type);

	public:
		//根据消失事件删除Buff
		void	deleteBuffByDisappearTypeEvent(STATUS_DISAPPEARTYPE type);
		//是否有特殊效果
		Bool	isHaveSpecialEffect(STATUS_STATUSSYSTYPE type);
		//是否某一类型免伤
		Bool	isHaveVitiateFlag(STATUS_VITIATEFLAG type);
		//某类型护盾值耗尽
		void	deleteBuffByAbsorbType(STATUS_ABSORBTYPE type);
		//获得buffData表。
		void	getBuffData(std::map<U32, BuffData>& vecBuffData);
		//重新计算所有buff的属性
		void	calAttrAllBase();

	protected:
	private:

	};
}
//***************************************************************************************
#endif
//***************************************************************************************