
//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: AttributeFormmula.h
//        Author: xkc
//          Date: 2011-10-25
//          Time: 18:34
// Description: 
//			1.所有属性相关的公式。
//
// modify History:
//      <author>    <time>        <descript>
//         xkc      2011-10-25      add

//////////////////////////////////////////////////////////////
//******************************************************************************************
#ifndef _H_ATTRIBUTEFORMULA_
#define _H_ATTRIBUTEFORMULA_
//******************************************************************************************

#include "WorldCorePreqs.h"
//******************************************************************************************
namespace MG
{
#define FORMULA_PARA_NUM 6
    class AttributeFormula
    {
    public:
        AttributeFormula();
        ~AttributeFormula(){;}
        SINGLETON_INSTANCE(AttributeFormula);
        enum
        {
            FORMULA_NUM = 32+1   //公式的总数
        };

    public:     
        Int     calValue(
            const AttributeSet*  pMaster 
			,const CharacterData* pCharacterMaster
            ,const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM]
            ,U32 formulaID
            ,const AttributeSet* pReceiver = NULL
			,const Flt otherPara[FORMULA_PARA_NUM] = NULL
			,const CharacterData* pCharacterReceiver = NULL
            );

		Int		calValueCharacterAge(U32 _age, U32 _year, U32 _day);

    private:
        typedef Int (*attrFormula)( const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
			const AttributeSet*  pMaster,const AttributeSet* pReceiver,
			const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]);
        //----------------------------------------------------------------------------------
        //基本公式
        static Int attrFormula1(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula2(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula3(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM],
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula4(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula5(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula6(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM],
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula7(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula8(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula9(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula10(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        //----------------------------------------------------------------------------------
        //伤害公式
        static Int attrFormula11(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula12(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula13(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula14(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula15(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM],
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula16(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM],
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula17(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
		static Int attrFormula18(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula19(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula20(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM],
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula21(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula22(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula23(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM],
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula24(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula25(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        //----------------------------------------------------------------------------------
        //技能治疗公式
        static Int attrFormula51(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula52(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula53(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula54(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
		static Int attrFormula55(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
			const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
			const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
		);
		static Int attrFormula56(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
			const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
			const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
		);
		static Int attrFormula57(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
			const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
			const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
		);
		static Int attrFormula58(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
			const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
			const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
		);
		static Int attrFormula59(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
			const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
			const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
		);
        //----------------------------------------------------------------------------------
        //道具治疗公式
        static Int attrFormula91(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula92(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula93(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula94(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        static Int attrFormula95(
			const CharacterData* pCharacterMaster, const CharacterData* pCharacterReceiver,
            const AttributeSet*  pMaster,const AttributeSet* pReceiver, 
            const Flt para[FORMULA_PARA_NUM] , const U32 attrID[FORMULA_PARA_NUM], 
			const Flt otherPara[FORMULA_PARA_NUM]
        );
        //----------------------------------------------------------------------------------

    private:
        void    loadFormula();

    private:
        std::map<U32, attrFormula> attrFormulaMap;

    };
}
//******************************************************************************************
#endif //_H_ATTRIBUTEFORMULA_
//******************************************************************************************