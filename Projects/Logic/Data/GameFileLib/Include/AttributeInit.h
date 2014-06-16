//////////////////////////////////////////////////////////////
//******************************************************************************************
#ifndef _H_ATTRIBUTEINIT_
#define _H_ATTRIBUTEINIT_
//******************************************************************************************
#include "GameFilePreqs.h"
//******************************************************************************************
namespace MG
{
	//数据名称	        类型	长度	应用	说明
	//AbilityAppendId	u int	32	    客/服	通用非战斗属性附加的id
	//Notes	            string	32	    None	策划备注，16个汉字以内
	//AbilityListId1	u int	32	    客/服	附加的属性1
	//Num1	            int	    32	    客/服	属性1附加的数值，可为负
	//AbilityListId2	u int	32	    客/服	附加的属性2
	//Num2	            int	    32	    客/服	属性2附加的数值，可为负
	//AbilityListId3	u int	32	    客/服	附加的属性3
	//Num3	            int	    32	    客/服	属性3附加的数值，可为负
	//AbilityListId4	u int	32	    客/服	附加的属性4
	//Num4	            int 	32	    客/服	属性4附加的数值，可为负
	//AbilityListId5	u int	32	    客/服	附加的属性5
	//Num5	            int	    32	    客/服	属性5附加的数值，可为负
	//AbilityListId6	u int	32	    客/服	附加的属性6
	//Num6	            int	    32	    客/服	属性6附加的数值，可为负
	//AbilityListId7	u int	32	    客/服	附加的属性7
	//Num7	            int	    32	    客/服	属性7附加的数值，可为负
	//AbilityListId8	u int	32	    客/服	附加的属性8
	//Num8	            int	    32	    客/服	属性8附加的数值，可为负
	//AbilityListId9	u int	32	    客/服	附加的属性9
	//Num9	            int	    32	    客/服	属性9附加的数值，可为负
	//AbilityListId10	u int	32	    客/服	附加的属性10
	//Num10	            int	    32	    客/服	属性10附加的数值，可为负

	//-----------------------------------------------------------------------------
	struct AttributeInitInfo
	{
		U32             AbilityInitId                                 ; //通用非战斗属性附加的id
		AppendAttr      AppendAttrList[APPENDATTR_NUM]                ; //附加属性表
	};
	//-----------------------------------------------------------------------------
	class AttributeInit
	{
	public:
		AttributeInit(){;}
		~AttributeInit();
		SINGLETON_INSTANCE(AttributeInit);

	public:
		// MG_CN_MODIFY
		//加载AttributeInit.csv表
		Bool						load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
		//根据ID获得附加属性表
		const AttributeInitInfo*	getAttributeInitInfo(U32 id);
		
	protected:
		void						clear();
		void						setAttributeId(AttributeInitInfo* pInfo);
		
	private:
		std::map<UInt, AttributeInitInfo*>  mMapAttributeInitInfo;

	};

}
//******************************************************************************************
#endif
//******************************************************************************************