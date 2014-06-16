//******************************************************************************************
#include "stdafx.h"
#include "AttributeFormula.h"
#include "AttributeSet.h"
#include "MGRandom.h"
//******************************************************************************************
namespace MG
{
    //-------------------------------------------------------------------------------
    AttributeFormula::AttributeFormula()
    {
        loadFormula();
    }
    //-------------------------------------------------------------------------------
	MG::Int AttributeFormula::calValue( const AttributeSet* pMaster ,const CharacterData* pCharacterMaster ,const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM] ,U32 formulaID ,const AttributeSet* pReceiver /*= NULL */,const Flt otherPara[FORMULA_PARA_NUM] /*= NULL */,const CharacterData* pCharacterReceiver )
	{
		DYNAMIC_ASSERT(pMaster);
		DYNAMIC_ASSERT(para);
		DYNAMIC_ASSERT(attrID);

		return attrFormulaMap[formulaID]( pCharacterMaster, pCharacterReceiver, pMaster , pReceiver , para , attrID , otherPara );
	}
	//-------------------------------------------------------------------------------
    void AttributeFormula::loadFormula()
    {
        //基本公式
        attrFormulaMap[1] = attrFormula1;
        attrFormulaMap[2] = attrFormula2;
        attrFormulaMap[3] = attrFormula3;
        attrFormulaMap[4] = attrFormula4;
        attrFormulaMap[5] = attrFormula5;
        attrFormulaMap[6] = attrFormula6;
        attrFormulaMap[7] = attrFormula7;
        attrFormulaMap[8] = attrFormula8;
        attrFormulaMap[9] = attrFormula9;
        attrFormulaMap[10] = attrFormula10;
        //伤害公式
        attrFormulaMap[11] = attrFormula11;
        attrFormulaMap[12] = attrFormula12;
        attrFormulaMap[13] = attrFormula13;
        attrFormulaMap[14] = attrFormula14;
        attrFormulaMap[15] = attrFormula15;
        attrFormulaMap[16] = attrFormula16;
        attrFormulaMap[17] = attrFormula17;
        attrFormulaMap[18] = attrFormula18;
        attrFormulaMap[19] = attrFormula19;
        attrFormulaMap[20] = attrFormula20;
        attrFormulaMap[21] = attrFormula21;
        attrFormulaMap[22] = attrFormula22;
        attrFormulaMap[23] = attrFormula23;
        attrFormulaMap[24] = attrFormula24;
        attrFormulaMap[25] = attrFormula25;
        //技能治疗公式
        attrFormulaMap[51] = attrFormula51;
        attrFormulaMap[52] = attrFormula52;
        attrFormulaMap[53] = attrFormula53;
        attrFormulaMap[54] = attrFormula54;
		attrFormulaMap[55] = attrFormula55;
		attrFormulaMap[56] = attrFormula56;
		attrFormulaMap[57] = attrFormula57;
		attrFormulaMap[58] = attrFormula58;
		attrFormulaMap[59] = attrFormula59;
        //道具治疗公式
        attrFormulaMap[91] = attrFormula91;
        attrFormulaMap[92] = attrFormula92;
        attrFormulaMap[93] = attrFormula93;
        attrFormulaMap[94] = attrFormula94;
        attrFormulaMap[95] = attrFormula95;
    }
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula1( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return (Int)(( pMaster->getFanalValue(attrID[0]) + pMaster->getFanalValue(attrID[1]) )*( pMaster->getFanalValue(attrID[2]) + para[0] )*para[1]); 
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula2( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return (Int)( pMaster->getFanalValue(attrID[0]) + ( pMaster->getFanalValue(attrID[1])*pCharacterMaster->mLevel )*para[0] + ( pMaster->getFanalValue(attrID[2]) * pCharacterMaster->mLineageNum )*para[1]);
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula3( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return (Int)(pMaster->getFanalValue(attrID[0])*para[0] + pMaster->getFanalValue(attrID[1])*para[1] + pMaster->getFanalValue(attrID[2])*para[2] + pCharacterMaster->mLevel*para[3] + para[4]);
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula4( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		DYNAMIC_ASSERT(( pCharacterMaster->mLevel*para[1] + para[2] ));
		Flt val = ( pMaster->getFanalValue(attrID[0]) + pMaster->getFanalValue(attrID[1]) )*para[0]/( pCharacterMaster->mLevel*para[1] + para[2] ) + pMaster->getFanalValue(attrID[2]);
		if ( val < para[3] )
			return (Int)para[3];
		else if ( val > para[4] )
			return (Int)para[4];
		else
			return (Int)val;

	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula5( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return Int( ( pMaster->getFanalValue(attrID[0]) + ( pMaster->getFanalValue(attrID[1])*pCharacterMaster->mLevel )*para[0] ) * ( pCharacterMaster->mLineageNum*para[1] + para[2] ) * para[3] );
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula6( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return Int( pMaster->getFanalValue(attrID[0])*para[0] + pMaster->getFanalValue(attrID[1])*para[1] + pMaster->getFanalValue(attrID[2])*para[2] + pCharacterMaster->mLevel*para[3] + para[4] + 
			( pMaster->getFanalValue(attrID[3])*para[0] + pMaster->getFanalValue(attrID[4])*para[1] + pMaster->getFanalValue(attrID[5])*para[2] ) * pCharacterMaster->mLineageNum * para[5] );
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula7( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return 0;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula8( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return 0;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula9( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return 0;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula10( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return 0;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula11( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{	
		return (Int)(otherPara[0]*para[0]*(pMaster->getFanalValue(attrID[0]) + para[1])*para[2]);
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula12( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return (Int)(pMaster->getFanalValue(attrID[0])*para[0] + pMaster->getFanalValue(attrID[1])*para[1] + pMaster->getFanalValue(attrID[2])*para[2] + para[3]);
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula13( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Int lvlgap = pCharacterMaster->mLevel - pCharacterReceiver->mLevel;

		if ( lvlgap < para[0] )
			return (Int)para[0];
		else if ( lvlgap > para[1] )
			return (Int)para[1];
		else
			return lvlgap;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula14( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return 0;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula15( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt  regionDodge = pReceiver->getFanalValue(attrID[0])*para[0] - pMaster->getFanalValue(attrID[1])*para[1] - otherPara[0]*para[2] + para[3];
		
		if ( regionDodge < para[4] )
			regionDodge = para[4];

		if ( regionDodge + otherPara[1] + otherPara[2] + otherPara[3] > para[5] )
			return (Int)(para[5] - ( otherPara[1] + otherPara[2] + otherPara[3] ));
		else
			return (Int)regionDodge;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula16( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt regionThump = pMaster->getFanalValue(attrID[0])*para[0] - pReceiver->getFanalValue(attrID[1])*para[1] + otherPara[0]*para[2] + para[3];

		if ( regionThump < para[4] )
			regionThump = para[4];

		if ( regionThump + otherPara[1] + otherPara[2] + otherPara[3] + otherPara[4] > para[5] )
			return (Int)(para[5] - ( otherPara[1] + otherPara[2] + otherPara[3] + otherPara[4] ));
		else
			return (Int)regionThump;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula17( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt regionOther = para[0] - ( otherPara[0] + otherPara[1] + otherPara[2] + otherPara[3] + otherPara[4] );

		if ( regionOther < para[1] )
			return (Int)para[1];
		else
			return (Int)regionOther;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula18( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return (Int)MGRandom::getInstance().rand_ab_One((Int)para[0], (Int)para[1]);
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula19( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt attackVal = otherPara[0] * para[0];

		if ( attackVal < para[1] )
			return (Int)para[1];
		else
			return (Int)attackVal;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula20( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt val = pMaster->getFanalValue(attrID[0]) + pReceiver->getFanalValue(attrID[1]) + para[0];
		if ( val < para[2] )
			val = para[2];

		return (Int)(otherPara[0]*val*para[1]);
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula21( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt val = otherPara[0]*otherPara[0]*para[0]/( otherPara[0]*para[1] + pReceiver->getFanalValue(attrID[0])*para[2] + para[3] ) + pMaster->getFanalValue(attrID[1] ) + pReceiver->getFanalValue(attrID[2]);
		if ( val < para[4] )
			return (Int)para[4];
		else
			return (Int)val;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula22( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt val = otherPara[0]*(para[0] + pMaster->getFanalValue(attrID[0]) + pReceiver->getFanalValue(attrID[1]))*para[1];
		if ( val < para[2] )
			return (Int)para[2];
		else
			return (Int)val;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula23( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt val = otherPara[0]*( para[0] + pMaster->getFanalValue(attrID[0]) + pReceiver->getFanalValue(attrID[1]) )*para[1];
		if ( val < para[2] )
			return (Int)para[2];
		else
			return (Int)val;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula24( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt val = ( otherPara[0]*para[0] + otherPara[1]*para[1] )*( pMaster->getFanalValue(attrID[0]) + para[2] )*para[3];
		if ( val < para[4] )
			return (Int)para[4];
		else
			return (Int)val;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula25( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return 0;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula51( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return (Int)(otherPara[0]*para[0]*( pMaster->getFanalValue(attrID[0]) + para[1] )*para[2]);
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula52( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return 0;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula53( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt val = pMaster->getFanalValue(attrID[0])*para[0] + para[1];

		if ( val < para[2] )
			return val = para[2];

		if ( otherPara[0] + otherPara[1] + val > para[3] )
			return (Int)( para[3] - (otherPara[0] + otherPara[1] + val) );
		else
			return (Int)val;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula54( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt val = para[0] - (otherPara[0] + otherPara[1] + otherPara[2]);
		if ( val < para[1] )
			return (Int)para[1];
		else
			return (Int)val;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula55( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return (Int)MGRandom::getInstance().rand_ab_One((Int)para[0], (Int)para[1]);
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula56( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt val = otherPara[0]*para[0];
		if ( val < para[1] )
			return (Int)para[1];
		else
			return (Int)val;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula57( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt val = pMaster->getFanalValue(attrID[0]) + pReceiver->getFanalValue(attrID[1]) + para[0];
		if ( val < para[2] )
			val = para[2];

		return (Int)(otherPara[0]*val*para[1]);
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula58( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt val = ( otherPara[0] + pMaster->getFanalValue(attrID[0]) + pReceiver->getFanalValue(attrID[1]) )*( pMaster->getFanalValue(attrID[2]) + pReceiver->getFanalValue(attrID[3]) + para[0] )*para[1];
		if ( val < para[2] )
			return (Int)para[2];
		else
			return (Int)val;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula59( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		Flt val = ( otherPara[0]*para[0] + otherPara[1]*para[1] )*( pMaster->getFanalValue(attrID[0]) + para[2] )*para[3];
		if ( val < para[4] )
			return (Int)para[4];
		else
			return (Int)val;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula91( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return 0;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula92( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return 0;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula93( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return 0;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula94( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return 0;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::attrFormula95( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver, const AttributeSet* pMaster,const AttributeSet* pReceiver, const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], const Flt otherPara[FORMULA_PARA_NUM] )
	{
		return 0;
	}
	//-------------------------------------------------------------------------------
	MG::Int AttributeFormula::calValueCharacterAge( U32 _age, U32 _year, U32 _day )
	{
		DYNAMIC_ASSERT(_day);
		DYNAMIC_ASSERT(_year);

		return _age*_day/_year;
	}
}